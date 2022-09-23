#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include <stddef.h>
#include <stdint.h>

#include <etl/array.h>
#include <etl/intrusive_links.h>
#include <etl/intrusive_queue.h>
#include <etl/queue.h>

namespace Packet {
/**
 * @brief Packet receive and transmit handler
 *
 * Implements scheduling of packets for transmission (based on different virtual queues for
 * priority) and buffering of received packets for read-out by the host.
 *
 * It doesn't know anything about the actual contents of the packets: this is handled in another
 * upper protocol layer.
 */
class Handler {
    private:
        /// Log information about rejected receive packets
        constexpr static const bool kLogRxRejects{false};

        /**
         * @brief Maximum packet data size
         *
         * This is fixed in the BlazeNet protocol: a packet may be up to 255 bytes in length.
         */
        constexpr static const size_t kMaxPacketSize{255};

        /**
         * @brief Maximum size to reserve for receive buffers
         *
         * Defines the maximum number of bytes to be allocated for use as a receive packet buffer.
         * This is approximate, as this does not include the overhead of heap allocations'
         * metadata.
         */
        constexpr static const size_t kMaxRxBufferSize{8*1024};

        /**
         * @brief Maximum number of queue slots to reserve
         *
         * This is the maximum number of packets that may be queued for reading by the host at a
         * given time.
         */
        constexpr static const size_t kMaxRxQueueSize{64};

    public:

        /**
         * @brief Packet buffer structure
         *
         * Types of this structure are allocated to hold received packets. They contain a small
         * bit of metadata, as well as the actual packet payload.
         */
        struct RxPacketBuffer {
            /**
             * @brief Packet length
             *
             * Size of the packet, in bytes
             */
            uint16_t packetSize;

            /**
             * @brief Received signal strength
             *
             * RSSI of the packet, in full integer dBm
             */
            int8_t rssi;

            /**
             * @brief Link quality indication
             *
             * A relative value indicating the quality of the link on which the packet was
             * received, where 0 is really shitty and 255 is the absolute best.
             */
            uint8_t lqi;

            /**
             * @brief Payload
             *
             * This array contains the actual payload of the received packet, excluding any
             * preambles or PHY headers.
             */
            uint8_t data[];
        };

    private:
        using RxQueueType = etl::queue<RxPacketBuffer *, kMaxRxQueueSize,
              etl::memory_model::MEMORY_MODEL_SMALL>;

    public:
        static void Init();

        static RxPacketBuffer *EnqueueRxPacket(const struct RAIL_RxPacketInfo &,
                const struct RAIL_RxPacketDetails &);
        static void DiscardRxPacket(RxPacketBuffer *);

        /**
         * @brief Peek at the first packet in the receive queue
         *
         * Returns the first (oldest) packet in the receive queue, without popping it.
         */
        static inline RxPacketBuffer *PeekRxQueue() {
            return gRxQueue->front();
        }

        /**
         * @brief Pop the first packet from the receive queue
         *
         * Returns the first (oldest) packet in the receive queue, and then removes it from the
         * queue.
         *
         * @remark Be sure to call DiscardRxPacket when done to release the packet's memory.
         */
        static inline auto PopRxQueue() {
            RxPacketBuffer *buf = gRxQueue->front();
            gRxQueue->pop();
            UpdateRxQueueState();

            return buf;
        }

        /**
         * @brief Get the receive queue overflow flag
         */
        static inline bool GetRxOverflowFlag() {
            return gRxOverflowFlag;
        }
        /**
         * @brief Is the receive queue empty?
         */
        static inline bool GetRxEmptyFlag() {
            return gRxQueue->empty();
        }
        /**
         * @brief Is the receive queue full?
         */
        static inline bool GetRxFullFlag() {
            return gRxQueue->full();
        }

    private:
        static void UpdateRxQueueState();

    private:
        /// Rx queue overflow flag (sticky)
        static bool gRxOverflowFlag;
        /// Total number of bytes allocated for receive packet buffers
        static size_t gRxAllocBytes;
        /// Number of rx packets discarded because the buffer alloc limit has been reached
        static size_t gRxBufferDiscarded;
        /// Number of rx packets discarded because of allocation failures
        static size_t gRxBufferAllocFailed;
        /// Number of rx packets discarded because rx queue is full
        static size_t gRxQueueDiscarded;
        /// Queue holding pointers to all received packets
        static RxQueueType *gRxQueue;
};
}

#endif
