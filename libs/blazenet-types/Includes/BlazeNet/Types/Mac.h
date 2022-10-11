#ifndef BLAZENET_TYPES_MAC_H
#define BLAZENET_TYPES_MAC_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief MAC headers and footers
 */
namespace BlazeNet::Types::Mac {
/// @{ @name Primary MAC headers
/**
 * @brief Short device address
 *
 * Devices exchange their EUI-64 addresses for short, 16-bit identifiers when they associate to a
 * network. This saves air time and makes packets more compact. Most identifier values can be
 * freely assigned.
 *
 * Reserved short addresses:
 *
 * - 0xFF00 - 0xFF7F: Network management
 * - 0xFF80 - 0xFFFF: Broadcast/multicast
 *      - 0xFF00 - 0xFF3F: Reserved for multicast groups
 *      - 0xFFFF: Broadcast message
 */
using ShortAddress = uint16_t;

/**
 * @brief Broadcast address
 */
constexpr static const ShortAddress kBroadcastAddress{0xffff};



/**
 * @brief MAC header flags
 *
 * The flags field consists of a bitwise-OR of various flags in this enumeration.
 */
enum HeaderFlags: uint8_t {
    /// Number of bits to shift the endpoint value
    EndpointShift                       = 3,
    /**
     * @brief Endpoint mask
     *
     * Each packet contains a 3-bit endpoint that indicates how the contents of the packet, beyond
     * the MAC header, and any bonus headers, should be handled.
     */
    EndpointMask                        = (0b111 << EndpointShift),

    /**
     * @brief Network control endpoint
     */
    EndpointNetControl                  = (0b000 << EndpointShift),
    /**
     * @brief Acknowledgement response
     *
     * Used to acknowledge a packet with the "ack request" field set. This packet type has no
     * actual payload.
     */
    EndpointAckResponse                 = (0b001 << EndpointShift),
    /**
     * @brief User data
     *
     * Raw data packets passed upwards to the user's stack.
     */
    EndpointUserData                    = (0b010 << EndpointShift),

    /**
     * @brief Acknowledge request
     *
     * When set, the recipient should generate an acknowledgement response (iff the packet is not
     * already an acknowledgement) upon successful receipt.
     */
    AckRequest                          = (1 << 2),

    /**
     * @brief Data pending
     *
     * Indicates the source of the message has additional data buffered and ready to send to the
     * device. This is used by coordinators to indicate to low power devices that they have
     * buffered data.
     */
    DataPending                         = (1 << 1),

    /**
     * @brief Security enabled
     *
     * Packet payload may be encrypted, authenticated, or both.
     *
     * Immediately following the MAC header will be a security header, with further information
     * about the security scheme of the frame.
     */
    SecurityEnabled                     = (1 << 0),
};

/**
 * @brief Primary MAC header
 *
 * This is the fixed header that's the first payload byte of all packets.
 */
struct Header {
    /**
     * @brief Packet flags
     *
     * @seeAlso MacPacketFlags
     */
    uint8_t flags;

    /**
     * @brief Sequence number (tag)
     *
     * Used to correlate acknowledgements and replies to a particular message. Has no other
     * defined meaning.
     *
     * @remark The suggested implementation is a monotonically increasing counter, which starts at
     *         a randomly selected value; reset the counter on every association.
     */
    uint8_t sequence;

    /**
     * @brief Source address
     *
     * Short address of the device that originated this message.
     */
    ShortAddress source;

    /**
     * @brief Destination address
     *
     * Short address of the device this message is destined for
     */
    ShortAddress destination;
} __attribute__((packed));

/// @}

//// @{ @name Security headers
/**
 * @brief Packet security schemes
 */
enum class SecurityScheme: uint8_t {
    /**
     * @brief No additional security
     *
     * This scheme provides only anti-replay protection, by checking the incoming counter value
     * against an internal counter.
     */
    None                                = 0x00,

    /**
     * @brief AES-128 (encryption, authentication)
     *
     * Encrypts and authenticates the packet with AES-CCM-128.
     *
     * Security header is followed by a key identifier, and the payload has a 16-byte
     * authentication tag trailer.
     */
    AesCcm128                           = 0x01,

    /**
     * @brief AES-128 (encryption only)
     *
     * Encrypts the packet only; there is **no** protection against tampering.
     *
     * Security header is followed by a key identifier.
     */
    AesCtr128                           = 0x02,

    /**
     * @brief ChaCha20-Poly1305 (encryption, authentication)
     *
     * Encrypts the packet with ChaCha20, and authenticates the packet using Poly1305.
     *
     * Security header is followed by a key identifier, and the payload has a 16-byte
     * authentication tag trailer.
     */
    ChaCha20Poly1305                    = 0x03,
};

/**
 * @brief Security header
 *
 * This header follows the primary MAC header if the packet has some security scheme enaabled, as
 * indicated by the `SecurityEnabled` flag in the MAC header.
 */
struct SecurityHeader {
    /**
     * @brief Security type
     *
     * Indicates the security scheme used to protect the remainder of the packet. This defines
     * which of the payloads follows the security header.
     */
    SecurityScheme type;

    /**
     * @brief Frame counter
     *
     * Used for anti-replay protection; for algorithms requiring it, it's used as a nonce to
     * protect the packet.
     *
     * @remark This counter _must_ be implemented as a monotonically increasing counter, which
     *         _must_ be initialized to a random value.
     */
    uint32_t counter;
} __attribute__((packed));

/**
 * @brief Key identity header
 *
 * For all security schemes requiring a key, this header follows. It defines which key to use for
 * operations.
 *
 * @seeAlso SecurityKeyIdLong
 */
struct SecurityKeyId {
    /**
     * @brief Fixed key id and flags
     *
     * This field has two meanings, which are alternated by whether the most significant bit is
     * set:
     *
     * - When clear: A per-association key
     * - When set: a 4-byte key identifier follows
     */
    uint8_t index;
} __attribute__((packed));

/**
 * @brief Key identity header (with key id)
 */
struct SecurityKeyIdLong {
    /**
     * @brief Key identifier header
     *
     * This header must have the msb of the index set.
     */
    SecurityKeyId header;

    /**
     * @brief Extended key identifier
     */
    uint32_t keyId;
} __attribute__((packed));

/// @}

};

#endif
