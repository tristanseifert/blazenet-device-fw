#ifndef BLAZENET_TYPES_PHY_H
#define BLAZENET_TYPES_PHY_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief PHY headers and footers
 */
namespace BlazeNet::Types::Phy {
/**
 * @brief PHY header
 *
 * Some radios do not automatically generate the PHY header, which indicates to the radio modem
 * how long the packet is.
 */
struct Header {
    /**
     * @brief Total packet size, in bytes
     *
     * Indicates how many bytes of payload data follow the PHY header.
     */
    uint8_t length;

    /**
     * @brief Packet payload
     */
    uint8_t payload[];
} __attribute__((packed));
};

#endif
