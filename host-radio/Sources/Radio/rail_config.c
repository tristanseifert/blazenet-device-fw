/***************************************************************************//**
 * @brief RAIL Configuration
 * @details
 *   WARNING: Auto-Generated Radio Config  -  DO NOT EDIT
 *   Radio Configurator Version: 2022.5.2
 *   RAIL Adapter Version: 2.4.19
 *   RAIL Compatibility: 2.x
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "em_device.h"
#include "rail_config.h"

uint32_t RAILCb_CalcSymbolRate(RAIL_Handle_t railHandle)
{
  (void) railHandle;
  return 0U;
}

uint32_t RAILCb_CalcBitRate(RAIL_Handle_t railHandle)
{
  (void) railHandle;
  return 0U;
}

void RAILCb_ConfigFrameTypeLength(RAIL_Handle_t railHandle,
                                  const RAIL_FrameType_t *frameType)
{
  (void) railHandle;
  (void) frameType;
}

static const uint8_t irCalConfig[] = {
  20, 41, 2, 0, 0, 49, 17, 0, 0, 0, 1, 0, 2, 100, 0, 1, 1, 47, 0, 0, 7
};

static const int32_t timingConfig[] = {
  144000, 144000, 0
};

static const uint8_t hfxoRetimingConfigEntries[] = {
  1, 0, 0, 0, 0xc0, 0x17, 0x53, 0x02, 4, 12, 0, 0, 0xe0, 0x02, 0, 0, 0, 0, 0x3c, 0x03, 1, 2, 5, 4, 0x98, 0x03, 1, 2, 5, 5, 0xf4, 0x03, 1, 2, 6, 5
};

static RAIL_ChannelConfigEntryAttr_t channelConfigEntryAttr = {
#if RAIL_SUPPORTS_OFDM_PA
  {
#ifdef RADIO_CONFIG_ENABLE_IRCAL_MULTIPLE_RF_PATHS
    { 0xFFFFFFFFUL, 0xFFFFFFFFUL, },
#else
    { 0xFFFFFFFFUL },
#endif // RADIO_CONFIG_ENABLE_IRCAL_MULTIPLE_RF_PATHS
    { 0xFFFFFFFFUL, 0xFFFFFFFFUL }
  }
#else // RAIL_SUPPORTS_OFDM_PA
#ifdef RADIO_CONFIG_ENABLE_IRCAL_MULTIPLE_RF_PATHS
  { 0xFFFFFFFFUL, 0xFFFFFFFFUL, },
#else
  { 0xFFFFFFFFUL },
#endif // RADIO_CONFIG_ENABLE_IRCAL_MULTIPLE_RF_PATHS
#endif // RAIL_SUPPORTS_OFDM_PA
};

static const uint32_t phyInfo[] = {
  13UL,
  0x01333333UL, // 307.2
  (uint32_t) NULL,
  (uint32_t) irCalConfig,
  (uint32_t) timingConfig,
  0x00000000UL,
  0UL,
  0UL,
  2000000UL,
  0x00F62004UL,
  0x0650D4ADUL,
  (uint32_t) NULL,
  (uint32_t) hfxoRetimingConfigEntries,
  (uint32_t) NULL,
  0UL,
  0UL,
  2000050UL,
  (uint32_t) NULL,
  (uint32_t) NULL,
};

const uint32_t blazenet_modemConfigBase[] = {
  0x0002400CUL, 0x00008001UL,
  /*    4010 */ 0x000040FFUL,
  0x00024020UL, 0x00000000UL,
  /*    4024 */ 0x00000000UL,
  0x00074030UL, 0x00000000UL,
  /*    4034 */ 0x00000108UL,
  /*    4038 */ 0x000001F0UL,
  /*    403C */ 0x00000001UL,
  /*    4040 */ 0x00000000UL,
  /*    4044 */ 0x00004000UL,
  /*    4048 */ 0x000007A4UL,
  0x00014050UL, 0x00000000UL,
  0x0002405CUL, 0x00000000UL,
  /*    4060 */ 0x00000000UL,
  0x000140A8UL, 0x00000007UL,
  0x000440BCUL, 0x00000000UL,
  /*    40C0 */ 0x00000000UL,
  /*    40C4 */ 0x00000000UL,
  /*    40C8 */ 0x00000000UL,
  0x00044108UL, 0x00004800UL,
  /*    410C */ 0x00004CFFUL,
  /*    4110 */ 0x00004900UL,
  /*    4114 */ 0x00004DFFUL,
  0x1001C020UL, 0x0007F800UL,
  0x3001C020UL, 0x002801FEUL,
  0x0009C024UL, 0x00001300UL,
  /*    C028 */ 0x03B380ECUL,
  /*    C02C */ 0x51407543UL,
  /*    C030 */ 0xB8000FA0UL,
  /*    C034 */ 0x00004030UL,
  /*    C038 */ 0x0007AAA8UL,
  /*    C03C */ 0x00000000UL,
  /*    C040 */ 0x00000000UL,
  /*    C044 */ 0x00000000UL,
  0x0014C054UL, 0x00302187UL,
  /*    C058 */ 0xE60D000EUL,
  /*    C05C */ 0x0000002AUL,
  /*    C060 */ 0x0D0C0B08UL,
  /*    C064 */ 0x0000000DUL,
  /*    C068 */ 0x0002C688UL,
  /*    C06C */ 0x000005C0UL,
  /*    C070 */ 0x000010BAUL,
  /*    C074 */ 0x003F0000UL,
  /*    C078 */ 0x00EE008DUL,
  /*    C07C */ 0x03AC01F6UL,
  /*    C080 */ 0x079604F5UL,
  /*    C084 */ 0x0D9C09DEUL,
  /*    C088 */ 0x179311C3UL,
  /*    C08C */ 0x26F51DFEUL,
  /*    C090 */ 0x3FFF32BDUL,
  /*    C094 */ 0x1BF815FEUL,
  /*    C098 */ 0x2DB423DCUL,
  /*    C09C */ 0x3FFF39D0UL,
  /*    C0A0 */ 0x00003FFFUL,
  0x0005C0A8UL, 0x15724BBDUL,
  /*    C0AC */ 0x0518A311UL,
  /*    C0B0 */ 0x76543210UL,
  /*    C0B4 */ 0x00000A98UL,
  /*    C0B8 */ 0x00000000UL,
  0x0004C0CCUL, 0x00000000UL,
  /*    C0D0 */ 0x00000000UL,
  /*    C0D4 */ 0x000A0001UL,
  /*    C0D8 */ 0x00280001UL,
  0x01010008UL, 0x000007C4UL,
  0x01010018UL, 0x0000FFFFUL,
  0x01010020UL, 0x00008408UL,
  0x01264040UL, 0x00000000UL,
  /*    4044 */ 0x00000000UL,
  /*    4048 */ 0x00000010UL,
  /*    404C */ 0x0413F920UL,
  /*    4050 */ 0x0052C007UL,
  /*    4054 */ 0x00000000UL,
  /*    4058 */ 0x00000000UL,
  /*    405C */ 0x03000000UL,
  /*    4060 */ 0x20000000UL,
  /*    4064 */ 0x00000000UL,
  /*    4068 */ 0x00F00249UL,
  /*    406C */ 0x00000841UL,
  /*    4070 */ 0x00000002UL,
  /*    4074 */ 0x00100792UL,
  /*    4078 */ 0x0000006FUL,
  /*    407C */ 0x00000000UL,
  /*    4080 */ 0x08A03145UL,
  /*    4084 */ 0x744AC39BUL,
  /*    4088 */ 0x000F0018UL,
  /*    408C */ 0x60000000UL,
  /*    4090 */ 0x00000000UL,
  /*    4094 */ 0x30100101UL,
  /*    4098 */ 0x7F7F7050UL,
  /*    409C */ 0x00000000UL,
  /*    40A0 */ 0x00000000UL,
  /*    40A4 */ 0x00000000UL,
  /*    40A8 */ 0x00000000UL,
  /*    40AC */ 0x00000000UL,
  /*    40B0 */ 0x00000000UL,
  /*    40B4 */ 0x00000000UL,
  /*    40B8 */ 0x00000000UL,
  /*    40BC */ 0x00000000UL,
  /*    40C0 */ 0x00000000UL,
  /*    40C4 */ 0x00000000UL,
  /*    40C8 */ 0x00000000UL,
  /*    40CC */ 0x00000000UL,
  /*    40D0 */ 0x00000000UL,
  /*    40D4 */ 0x00000000UL,
  0x110140E0UL, 0x000001F8UL,
  0x310140E0UL, 0x00000201UL,
  0x01024110UL, 0x00051E33UL,
  /*    4114 */ 0x00000000UL,
  0x010E411CUL, 0x8BE66000UL,
  /*    4120 */ 0x00000000UL,
  /*    4124 */ 0x078304FFUL,
  /*    4128 */ 0x3AC81388UL,
  /*    412C */ 0x0C6606FFUL,
  /*    4130 */ 0x078304FFUL,
  /*    4134 */ 0x03FF1388UL,
  /*    4138 */ 0xF00A20BCUL,
  /*    413C */ 0x00523723UL,
  /*    4140 */ 0x00000000UL,
  /*    4144 */ 0x123556B7UL,
  /*    4148 */ 0x50000000UL,
  /*    414C */ 0x00003B80UL,
  /*    4150 */ 0x00000000UL,
  0x01024158UL, 0x00000000UL,
  /*    415C */ 0x00000000UL,
  0x01014164UL, 0x0000010CUL,
  0x010B416CUL, 0x40000000UL,
  /*    4170 */ 0x00000000UL,
  /*    4174 */ 0x00000000UL,
  /*    4178 */ 0x00000000UL,
  /*    417C */ 0x00000000UL,
  /*    4180 */ 0x00000000UL,
  /*    4184 */ 0x00000101UL,
  /*    4188 */ 0x00000000UL,
  /*    418C */ 0x00000000UL,
  /*    4190 */ 0x00000000UL,
  /*    4194 */ 0x00000000UL,
  0x010241A4UL, 0x00000000UL,
  /*    41A8 */ 0x00000000UL,
  0x010C41B0UL, 0x00000000UL,
  /*    41B4 */ 0x00200000UL,
  /*    41B8 */ 0x00000000UL,
  /*    41BC */ 0x00000000UL,
  /*    41C0 */ 0x003C0000UL,
  /*    41C4 */ 0x0006AAAAUL,
  /*    41C8 */ 0x00000000UL,
  /*    41CC */ 0x00000000UL,
  /*    41D0 */ 0x00000000UL,
  /*    41D4 */ 0x000000D0UL,
  /*    41D8 */ 0x00020000UL,
  /*    41DC */ 0x00000000UL,
  0x011541E4UL, 0x3BBEE3E3UL,
  /*    41E8 */ 0x000BA049UL,
  /*    41EC */ 0x00131A92UL,
  /*    41F0 */ 0x00C38003UL,
  /*    41F4 */ 0x0F11B9CFUL,
  /*    41F8 */ 0x049C8539UL,
  /*    41FC */ 0x23321E63UL,
  /*    4200 */ 0x3BBEE3E3UL,
  /*    4204 */ 0x000BA049UL,
  /*    4208 */ 0x00131A92UL,
  /*    420C */ 0x00C38003UL,
  /*    4210 */ 0x0F11B9CFUL,
  /*    4214 */ 0x049C8539UL,
  /*    4218 */ 0x23321E63UL,
  /*    421C */ 0x00000000UL,
  /*    4220 */ 0x00000000UL,
  /*    4224 */ 0x0000002CUL,
  /*    4228 */ 0x3675EE07UL,
  /*    422C */ 0x40001860UL,
  /*    4230 */ 0x00000000UL,
  /*    4234 */ 0x00000000UL,
  0x0101423CUL, 0x00000000UL,
  0x01034244UL, 0x00000014UL,
  /*    4248 */ 0x00000000UL,
  /*    424C */ 0x04000008UL,
  0x010F4330UL, 0x00000000UL,
  /*    4334 */ 0x00000000UL,
  /*    4338 */ 0x00000000UL,
  /*    433C */ 0x00000000UL,
  /*    4340 */ 0x00000000UL,
  /*    4344 */ 0x00000000UL,
  /*    4348 */ 0x00000000UL,
  /*    434C */ 0x00000000UL,
  /*    4350 */ 0x00000000UL,
  /*    4354 */ 0x00000000UL,
  /*    4358 */ 0x00000000UL,
  /*    435C */ 0x38000000UL,
  /*    4360 */ 0x00000000UL,
  /*    4364 */ 0x00000000UL,
  /*    4368 */ 0x58FF0000UL,
  0x01018010UL, 0x00000003UL,
  0x01028038UL, 0x0010D4ADUL,
  /*    803C */ 0x00000003UL,
  0x0103809CUL, 0x00000000UL,
  /*    80A0 */ 0x0003B870UL,
  /*    80A4 */ 0x0002C0FFUL,
  0x110180A8UL, 0x000001F6UL,
  0x310180A8UL, 0x01014201UL,
  0x110180ACUL, 0x000001F6UL,
  0x310180ACUL, 0x000D0A01UL,
  0x010280B0UL, 0x02000300UL,
  /*    80B4 */ 0x01000037UL,
  0x02030098UL, 0x00000000UL,
  /*    009C */ 0x04000C00UL,
  /*    00A0 */ 0x0000044CUL,
  0x020200D8UL, 0xAA400005UL,
  /*    00DC */ 0x00000188UL,
  0x120100ECUL, 0x00000FE0UL,
  0x320100ECUL, 0x1151200DUL,
  0x020100F0UL, 0x0000052BUL,
  0x02010100UL, 0x00000110UL,
  0x12010104UL, 0x00000000UL,
  0x32010104UL, 0x00000110UL,
  0x12010110UL, 0x000FFF00UL,
  0x32010110UL, 0x42000002UL,
  0x1201012CUL, 0x001FFC00UL,
  0x3201012CUL, 0x008000A9UL,
  0x02010140UL, 0x0000003FUL,
  0x12010150UL, 0x0000C000UL,
  0x32010150UL, 0x00510060UL,
  0x02020168UL, 0x00060010UL,
  /*    016C */ 0x00012000UL,
  0x02010174UL, 0x019B8169UL,
  0x12010178UL, 0x001C0000UL,
  0x32010178UL, 0x1FE00440UL,
  0x12010180UL, 0x00000779UL,
  0x32010180UL, 0x00000002UL,
  0x02020188UL, 0x00000050UL,
  /*    018C */ 0x00000000UL,
  0x120101ACUL, 0x000001F8UL,
  0x320101ACUL, 0x00011804UL,
  0x020101B0UL, 0x00000000UL,
  0x03014FFCUL, (uint32_t) &phyInfo,
  0xFFFFFFFFUL,
};

const RAIL_ChannelConfigEntry_t blazenet_channels[] = {
  {
    .phyConfigDeltaAdd = NULL,
    .baseFrequency = 915000000,
    .channelSpacing = 1000000,
    .physicalChannelOffset = 0,
    .channelNumberStart = 0,
    .channelNumberEnd = 20,
    .maxPower = RAIL_TX_POWER_MAX,
    .attr = &channelConfigEntryAttr,
#ifdef RADIO_CONFIG_ENABLE_CONC_PHY
    .entryType = 0,
#endif
#ifdef RADIO_CONFIG_ENABLE_STACK_INFO
    .stackInfo = NULL,
#endif
  },
};

const RAIL_ChannelConfig_t blazenet_channelConfig = {
  .phyConfigBase = blazenet_modemConfigBase,
  .phyConfigDeltaSubtract = NULL,
  .configs = blazenet_channels,
  .length = 1U,
  .signature = 0UL,
};

const RAIL_ChannelConfig_t *channelConfigs[] = {
  &blazenet_channelConfig,
  NULL
};


#ifdef RADIO_CONFIG_ENABLE_STACK_INFO
#endif // RADIO_CONFIG_ENABLE_STACK_INFO

uint32_t blazenetAccelerationBuffer[467];
