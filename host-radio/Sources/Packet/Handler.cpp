#include <rail.h>
#include <stdlib.h>

#include <BlazeNet/Types.h>

#include "HostIf/Commands.h"
#include "HostIf/IrqManager.h"
#include "Log/Logger.h"
#include "Radio/Task.h"
#include "Handler.h"

using namespace Packet;

bool Handler::gRxOverflowFlag{false};
size_t Handler::gRxAllocBytes{0}, Handler::gRxQueueDiscarded{0}, Handler::gRxBufferDiscarded{0},
       Handler::gRxBufferAllocFailed{0};
Handler::RxQueueType *Handler::gRxQueue;

bool Handler::gTxOverflowFlag{false};
size_t Handler::gTxAllocBytes{0}, Handler::gTxQueueDiscarded{0}, Handler::gTxBufferDiscarded{0},
       Handler::gTxBufferAllocFailed{0}, Handler::gTxPacketsPending{0};

etl::array<Handler::TxQueueType *, 4> Handler::gTxQueues;

/**
 * @brief Initialize the packet handler
 */
void Handler::Init() {
    gRxQueue = new RxQueueType;
    REQUIRE(!!gRxQueue, "failed to allocate %s", "rx packet queue");

    for(size_t i = 0; i < gTxQueues.size(); i++) {
        gTxQueues[i] = new TxQueueType;
        REQUIRE(!!gTxQueues[i], "failed to allocate %s (%u)", "tx packet queue", i);
    }
}

/**
 * @brief Enqueue a new packet into the receive buffer
 *
 * We'll allocate a buffer structure for this packet, copy the payload into it, then insert it at
 * the end of the receive queue. Interrupt and status flags are updated as well.
 *
 * @return Pointer to packet buffer, or `nullptr` if out of resources
 *
 * @TODO make this thread safe
 */
Handler::RxPacketBuffer *Handler::HandleRxPacket(const struct RAIL_RxPacketInfo &info,
        const struct RAIL_RxPacketDetails &details) {
    // ensure we've queue space
    if(gRxQueue->full()) {
        gRxOverflowFlag = true;
        gRxQueueDiscarded++;
        UpdateRxQueueState();

        if(kLogRxRejects) {
            Logger::Warning("RX queue full!");
        }
        return nullptr;
    }

    // calculate the size of the packet buffer structure, validate space vacancy and allocate
    const auto requiredBytes = sizeof(RxPacketBuffer) + info.packetBytes;

    if((gRxAllocBytes + requiredBytes) > kMaxRxBufferSize) {
        gRxOverflowFlag = true;
        gRxBufferDiscarded++;
        UpdateRxQueueState();

        if(kLogRxRejects) {
            Logger::Warning("%s: Buffer alloc overflow (%u alloc)", "rx", gRxAllocBytes);
        }
        return nullptr;
    }

    auto buffer = reinterpret_cast<RxPacketBuffer *>(malloc(requiredBytes));
    if(!buffer) {
        gRxOverflowFlag = true;
        gRxBufferAllocFailed++;
        UpdateRxQueueState();

        if(kLogRxRejects) {
            Logger::Warning("%s: failed to alloc %u bytes", "rx", requiredBytes);
        }
        return nullptr;
    }

    memset(buffer, 0, sizeof(*buffer));
    new (buffer) RxPacketBuffer();

    gRxAllocBytes += requiredBytes;

    // fill in the buffer
    buffer->packetSize = info.packetBytes;
    buffer->rssi = details.rssi;
    buffer->lqi = details.lqi;

    RAIL_CopyRxPacket(buffer->data, &info);

    // inspect the header to see if we want auto-ack
    if(buffer->packetSize >= sizeof(BlazeNet::Types::Mac::Header)) {
        auto hdr = reinterpret_cast<const BlazeNet::Types::Mac::Header *>(buffer->data);

        // address should match our radio address
        auto ourAddr = Radio::Task::GetAddress();

        buffer->autoAck = (hdr->flags & BlazeNet::Types::Mac::HeaderFlags::AckRequest) &&
            (hdr->destination == ourAddr);
    }

    // enqueue it
    gRxQueue->emplace(buffer);

    if(kLogRx) {
        Logger::Trace("%s: queue %u/%u (%p)", "rx", gRxQueue->available(), gRxQueue->capacity(),
                buffer);
    }

    UpdateRxQueueState();

    return buffer;
}

/**
 * @brief Releases resources associated with this receive packet buffer
 *
 * If the packet should have an acknowledgement auto-generated, we'll queue this here as well.
 *
 * @param ack Whether the packet should be positively acknowledged (if desired)
 */
void Handler::DiscardRxPacket(RxPacketBuffer *buffer, const bool ack) {
    // queue auto-ack
    if(buffer->autoAck && ack) {
        Radio::Task::QueueAck({buffer->data, buffer->packetSize});
    }

    // release the packet buffer
    const auto numBytes = sizeof(*buffer) + buffer->packetSize;

    free(buffer);
    gRxAllocBytes -= numBytes;
}

/**
 * @brief Update the state of the receive queue
 *
 * This updates the various flags and interrupts.
 */
void Handler::UpdateRxQueueState() {
    // update interrupt state
    if(!gRxQueue->empty()) {
        HostIf::IrqManager::Assert(HostIf::Interrupt::PacketReceived);
    }
}



/**
 * @brief Enqueue a pre-allocated packet
 *
 * Add a previously queued packet (which was declared sticky) to the transmit queue
 *
 * @param priority Queue to insert the packet into
 * @param packet Packet to add to the queue
 *
 * @return 0 on success or negative error code
 */
int Handler::QueueTxPacket(const TxPacketPriority priority, TxPacketBuffer *packet) {
    // ensure the appropriate queue has space
    auto queue = gTxQueues[static_cast<size_t>(priority)];
    if(queue->full()) {
        gTxOverflowFlag = true;
        gTxQueueDiscarded++;
        UpdateTxQueueState();

        if(kLogTxRejects) {
            Logger::Warning("TX queue %u full!", static_cast<size_t>(priority));
        }

        return -1;
    }

    // insert it boiiii
    return QueueTxPacketFinal(queue, packet);
}

/**
 * @brief Allocate a transmit packet buffer
 *
 * Given the specified payload, copy it into a packet buffer we've allocated.
 *
 * @param payload Packet payload
 *
 *
 * @return Packet buffer structure, or `nullptr` on error
 */
Handler::TxPacketBuffer *Handler::AllocTxPacket(etl::span<const uint8_t> payload,
        const bool isSticky) {
    // calculate the size of the packet buffer structure, validate space vacancy
    const auto requiredBytes = sizeof(TxPacketBuffer) + payload.size();

    if((gTxAllocBytes + requiredBytes) > kMaxTxBufferSize) {
        gTxOverflowFlag = true;
        gTxBufferDiscarded++;
        UpdateTxQueueState();

        if(kLogTxRejects) {
            Logger::Warning("%s: Buffer alloc overflow (%u alloc)", "tx", gTxAllocBytes);
        }
        return nullptr;
    }

    // allocate the buffer
    auto buffer = reinterpret_cast<TxPacketBuffer *>(malloc(requiredBytes));
    if(!buffer) {
        gTxOverflowFlag = true;
        gTxBufferAllocFailed++;
        UpdateTxQueueState();

        if(kLogTxRejects) {
            Logger::Warning("%s: failed to alloc %u bytes", "tx", requiredBytes);
        }
        return nullptr;
    }

    // keep track of the allocation
    gTxAllocBytes += requiredBytes;

    // buffer was allocated, so initialize it with the payload
    memset(buffer, 0, sizeof(*buffer));
    new (buffer) TxPacketBuffer();

    buffer->packetSize = payload.size();
    buffer->isSticky = isSticky;

    memcpy(buffer->data, payload.data(), payload.size());

    // success - the buffer was initialized fully
    return buffer;
}

/**
 * @brief Queue a packet for transmission
 *
 * Insert the packet into our internal transmit queue.
 *
 * If no packets are currently pending, we'll immediately request transmission.
 *
 * @param priority Queue to insert the packet into
 * @param payload Packet payload
 * @param isSticky Whether the packet buffer is sticky (reusable)
 */
Handler::TxPacketBuffer *Handler::QueueTxPacket(const TxPacketPriority priority,
        etl::span<const uint8_t> payload, const bool isSticky) {
    int err;

    // ensure the appropriate queue has space
    auto queue = gTxQueues[static_cast<size_t>(priority)];
    if(queue->full()) {
        gTxOverflowFlag = true;
        gTxQueueDiscarded++;
        UpdateTxQueueState();

        if(kLogTxRejects) {
            Logger::Warning("TX queue %u full!", static_cast<size_t>(priority));
        }
        return nullptr;
    }

    // try to allocate the packet
    auto buffer = AllocTxPacket(payload, isSticky);
    if(!buffer) {
        return nullptr;
    }

    // either enqueue packet or transmit it
    err = QueueTxPacketFinal(queue, buffer);
    if(err) {
        Logger::Warning("%s failed: %d", "EnqueueTxPacket", err);

        // clean up resources
        DiscardTxPacket(buffer, true);
        return nullptr;
    }

    return buffer;
}

/**
 * @brief Enqueue the specified packet
 *
 * This is the common "footer" to all transmit packet submission functions.
 *
 * @param queue Queue to add the packet to
 * @param buffer Packet to enqueue
 *
 * @return 0 on success or a negative error code
 */
int Handler::QueueTxPacketFinal(TxQueueType *queue, TxPacketBuffer *buffer) {
    int err{0};

    // clear state on sticky bit
    if(buffer->isSticky) {
        buffer->csmaFailCount = 0;
    }

    // if there are no packets pending, skip the queue and transmit it right away
    if(!gTxPacketsPending++) {
        err = Radio::Task::TxPacketImmediate(buffer);
    }
    // otherwise, insert into appropriate queue
    else {
        queue->emplace(buffer);

        if(kLogTx) {
            Logger::Trace("%s: queue %u/%u (%p)", "tx", queue->available(), queue->capacity(),
                    buffer);
        }
    }

    UpdateTxQueueState();
    return err;
}

/**
 * @brief Discard a previously queued transmit packet
 *
 * Invoke this once the packet has been transmitted, to release its associated resources.
 *
 * @param packet Packet to be released
 * @param force When set, the packet is deallocated even if it's sticky
 */
void Handler::DiscardTxPacket(TxPacketBuffer *buffer, const bool force) {
    // free the packet if it's not sticky
    if(!buffer->isSticky || force) {
        const auto numBytes = sizeof(*buffer) + buffer->packetSize;

        free(buffer);

        gTxAllocBytes -= numBytes;
    }

    // update generic bookkeeping
    --gTxPacketsPending;
    UpdateTxQueueState();
}

/**
 * @brief Update the state of the transmit queue
 *
 * This updates various interrupts.
 */
void Handler::UpdateTxQueueState() {
    // update interrupt state
    if(!gTxPacketsPending) {
        HostIf::IrqManager::Assert(HostIf::Interrupt::TxQueueEmpty);
    }
}

/**
 * @brief Read out reset performance counters
 *
 * @param packet Packet to receive the performance counter data
 */
void Handler::ReadCounters(HostIf::Response::GetCounters *packet) {
    // rx counters
    packet->rxQueue.bufferDiscards = etl::exchange(gRxBufferDiscarded, 0);
    packet->rxQueue.bufferAllocFails = etl::exchange(gRxBufferAllocFailed, 0);
    packet->rxQueue.queueDiscards = etl::exchange(gRxQueueDiscarded, 0);

    packet->rxQueue.packetsPending = gRxQueue->size();
    packet->rxQueue.bufferSize = gRxAllocBytes;

    // tx counters
    packet->txQueue.packetsPending = gTxPacketsPending;
    packet->txQueue.bufferSize = gTxAllocBytes;

    packet->txQueue.bufferDiscards = etl::exchange(gTxBufferDiscarded, 0);
    packet->txQueue.bufferAllocFails = etl::exchange(gTxBufferAllocFailed, 0);
    packet->txQueue.queueDiscards = etl::exchange(gTxQueueDiscarded, 0);
}
