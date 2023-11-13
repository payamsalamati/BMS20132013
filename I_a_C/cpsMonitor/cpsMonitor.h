/**
 * @file cpsMonitor.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>
#include <string.h>

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef struct
{
    uint32_t cpsOutDtcTimestamps[3];
    uint8_t reserve[2];
    uint16_t dummy_reserve_crc;
} CPSoutNvm;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void cpsMonitor_checkNvm(const uint8_t* mirror, uint16_t length);
void cpsMonitor_copyNvmForWrite(uint8_t* mirror, uint16_t length);

void cpsMonitor_setCPSout(uint8_t newValue);
void cpsMonitor_setBMS_REQ_CPSout(uint8_t newValue);
void cpsMonitor_setErrorLimit(uint16_t newValue);
