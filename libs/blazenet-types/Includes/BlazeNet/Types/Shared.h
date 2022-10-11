#ifndef BLAZENET_TYPES_SHARED_H
#define BLAZENET_TYPES_SHARED_H

#include <stdint.h>

/**
 * @brief BlazeNet packet types
 */
namespace BlazeNet::Types {
/**
 * @brief Current protocol version
 *
 * Defines the version of the BlazeNet frame structures defined in these headers; this is used to
 * ensure we can communicate with a network when receiving its beacon frame.
 */
constexpr static const uint8_t kProtocolVersion{0x01};
};

#endif
