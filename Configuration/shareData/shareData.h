/**
 * @file shareData.h
 * @copyright (c) Futavis GmbH, Aachen 2021 - all rights reserved
 * @brief Sharing data between Bootloader and Application
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>
#include "logicalBlock.h"
#include "uds_ecuReset.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef struct
{
    uint8_t crc[0x20];
    LogicalBlock logicalBlock[4];
    LogicalBlockTable logicalBlockTable[5];
    char bootloaderIdentification[15];
} ShareData;

#if defined(BOOTLOADER_ACTIVE)
#define BOOTLOADER_READABLE_FLASH_START 0x4000u
#else
#define BOOTLOADER_READABLE_FLASH_START 0x10000u
#endif
#define BOOTLOADER_READABLE_FLASH_SIZE 0x4000u

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//

extern const ShareData* const shareData;

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
