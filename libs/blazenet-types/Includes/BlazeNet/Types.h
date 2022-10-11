/**
 * @file
 *
 * @brief BlazeNet protocol types
 *
 * This header (by including other headers) provides definitions for all BlazeNet protocol types,
 * used to structure the over the air packets.
 *
 * @section Conventions
 *
 * When packets contain multi-byte values (such as integers, but not including blobs or UUIDs) the
 * values will be stored in little-endian byte order. This reduces the energy impact on devices,
 * which are likely all ARM-based and thus little endian.
 */
#ifndef BLAZENET_TYPES_H
#define BLAZENET_TYPES_H

#include <BlazeNet/Types/Shared.h>

#include <BlazeNet/Types/Phy.h>
#include <BlazeNet/Types/Mac.h>

#include <BlazeNet/Types/Beacon.h>

#endif
