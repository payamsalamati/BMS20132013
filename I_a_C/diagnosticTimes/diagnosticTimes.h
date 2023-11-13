/**
 * @file diagnosticTimes.h
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
#include "nvm_config_id.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef struct
{
    uint32_t diagnosticTotalOperatingTimeIns;
    uint32_t diagnosticDriveOperatingTimeIns;
    uint32_t diagnosticChargeOperatingTimeIns;
    uint32_t diagnosticPeriodicWakeUpTimeIns;
    uint32_t diagnosticTotalBalancingTimeIns;
    uint8_t reserveBytes[8];
} DiagnosticTimesNvm;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void diagnosticTimes_checkNvm(const uint8_t* mirror, uint16_t length);
void diagnosticTimes_copyNvmForWrite(uint8_t* mirror, uint16_t length);

void diagnosticTimes_mainFunction(void);

uint32_t diagnosticTimes_getDiagnosticTotalOperatingTimeIns(void);
uint32_t diagnosticTimes_getDiagnosticDriveOperatingTimeIns(void);
uint32_t diagnosticTimes_getDiagnosticChargeOperatingTimeIns(void);
uint32_t diagnosticTimes_getDiagnosticPeriodicWakeUpTimeIns(void);
uint32_t diagnosticTimes_getDiagnosticTotalBalancingTimeIns(void);

void diagnosticTimes_clearAll(void);
