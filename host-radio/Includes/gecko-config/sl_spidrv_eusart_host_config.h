/***************************************************************************//**
 * @file
 * @brief SPIDRV_EUSART Config
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_SPIDRV_EUSART_HOST_CONFIG_H
#define SL_SPIDRV_EUSART_HOST_CONFIG_H

#include "spidrv.h"

// <<< Use Configuration Wizard in Context Menu >>>
// <h> SPIDRV settings

// <o SL_SPIDRV_EUSART_HOST_BITRATE> SPI bitrate
// <i> Default: 1000000
#define SL_SPIDRV_EUSART_HOST_BITRATE           8000000

// <o SL_SPIDRV_EUSART_HOST_FRAME_LENGTH> SPI frame length <7-16>
// <i> Default: 8
#define SL_SPIDRV_EUSART_HOST_FRAME_LENGTH      8

// <o SL_SPIDRV_EUSART_HOST_TYPE> SPI mode
// <spidrvMaster=> Master
// <spidrvSlave=> Slave
#define SL_SPIDRV_EUSART_HOST_TYPE              spidrvSlave

// <o SL_SPIDRV_EUSART_HOST_BIT_ORDER> Bit order on the SPI bus
// <spidrvBitOrderLsbFirst=> LSB transmitted first
// <spidrvBitOrderMsbFirst=> MSB transmitted first
#define SL_SPIDRV_EUSART_HOST_BIT_ORDER         spidrvBitOrderMsbFirst

// <o SL_SPIDRV_EUSART_HOST_CLOCK_MODE> SPI clock mode
// <spidrvClockMode0=> SPI mode 0: CLKPOL=0, CLKPHA=0
// <spidrvClockMode1=> SPI mode 1: CLKPOL=0, CLKPHA=1
// <spidrvClockMode2=> SPI mode 2: CLKPOL=1, CLKPHA=0
// <spidrvClockMode3=> SPI mode 3: CLKPOL=1, CLKPHA=1
#define SL_SPIDRV_EUSART_HOST_CLOCK_MODE        spidrvClockMode0

// <o SL_SPIDRV_EUSART_HOST_CS_CONTROL> SPI master chip select (CS) control scheme.
// <spidrvCsControlAuto=> CS controlled by the SPI driver
// <spidrvCsControlApplication=> CS controlled by the application
#define SL_SPIDRV_EUSART_HOST_CS_CONTROL        spidrvCsControlAuto

// <o SL_SPIDRV_EUSART_HOST_SLAVE_START_MODE> SPI slave transfer start scheme
// <spidrvSlaveStartImmediate=> Transfer starts immediately
// <spidrvSlaveStartDelayed=> Transfer starts when the bus is idle (CS deasserted)
// <i> Only applies if instance type is spidrvSlave
#define SL_SPIDRV_EUSART_HOST_SLAVE_START_MODE  spidrvSlaveStartImmediate
// </h>
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <eusart signal=TX,RX,SCLK,(CS)> SL_SPIDRV_EUSART_HOST
// $[EUSART_SL_SPIDRV_EUSART_HOST]
#define SL_SPIDRV_EUSART_HOST_PERIPHERAL         EUSART0
#define SL_SPIDRV_EUSART_HOST_PERIPHERAL_NO      0

// EUSART0 TX on PA05
#define SL_SPIDRV_EUSART_HOST_RX_PORT            gpioPortA
#define SL_SPIDRV_EUSART_HOST_RX_PIN             5

// EUSART0 RX on PA06
#define SL_SPIDRV_EUSART_HOST_TX_PORT            gpioPortA
#define SL_SPIDRV_EUSART_HOST_TX_PIN             6

// EUSART0 SCLK on PA04
#define SL_SPIDRV_EUSART_HOST_SCLK_PORT          gpioPortA
#define SL_SPIDRV_EUSART_HOST_SCLK_PIN           4

// EUSART0 CS on PA07
#define SL_SPIDRV_EUSART_HOST_CS_PORT            gpioPortA
#define SL_SPIDRV_EUSART_HOST_CS_PIN             7
// [EUSART_SL_SPIDRV_EUSART_HOST]$
// <<< sl:end pin_tool >>>

#endif // SL_SPIDRV_EUSART_HOST_CONFIG_HEUSART_
