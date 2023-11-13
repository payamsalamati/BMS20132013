/**
 * @file crcIf_config.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


#pragma once


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "crc.h"
#include <stdint.h>

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//

extern const uint32_t _paramram_sizeIn64Bit;

const crcConfig_t crcConfiguration[] = {
    { CRC_CH1, CRC_SEMI_CPU, (uint32_t)&_paramram_sizeIn64Bit, 1u, 0u, 0u },
};

const uint8_t CRC_CONFIGURATION_SIZE = sizeof(crcConfiguration) / sizeof(crcConfig_t);

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
