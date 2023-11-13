/**
 * @file cscNvm_config.h
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
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

#include <stdint.h>
#include <stdbool.h>

#include "downscaledCurrentViolationHistogram.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define CSC_NVM_CSC_PCB_KBS_SERIAL_NUMBER_LENGTH 6u
#define CSC_NVM_KBS_CSC_NVM_DATA_LENGTH          44u
typedef struct
{
    bool deepDischargeFlag;
    uint16_t cscPcbHardwareVersion;
    uint8_t cscPcbKbsSerialNumber[CSC_NVM_CSC_PCB_KBS_SERIAL_NUMBER_LENGTH];
    uint16_t moduleNominalVoltage;
    uint32_t moduleKbsSerialNumber;
    uint8_t eolTestResult;
    DownscaledCurrentViolationHistogramNvm downscaledCurrentViolationHistogramCounters;
    uint8_t kbsCscNvmData[CSC_NVM_KBS_CSC_NVM_DATA_LENGTH];
    uint8_t remainingSpace[8];  // total size of this struct can max. be 100 bytes. Take space away from this to add new variables.
    uint32_t dummy_for_crc32;
} CscNvmData;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

bool cscNvm_getDeepDischargeFlag(uint8_t cscAddress);
void cscNvm_setDeepDischargeFlag(uint8_t newValue, uint8_t cscAddress);

void cscNvm_getCSCPcbKbsSerialNumber(uint8_t* buffer, uint8_t cscAddress);
bool cscNvm_setCSCPcbKbsSerialNumber(const uint8_t* buffer, uint16_t length, uint8_t cscAddress);

uint16_t cscNvm_getModuleNominalVoltage(uint8_t cscAddress);
bool cscNvm_setModuleNominalVoltage(uint16_t newValue, uint8_t cscAddress);

uint8_t cscNvm_getEolTestResult(uint8_t cscAddress);
bool cscNvm_setEolTestResult(uint8_t newValue, uint8_t cscAddress);

uint16_t cscNvm_getCscPcbHardwareVersion(uint8_t cscAddress);
void cscNvm_setCscPcbHardwareVersion(uint16_t newValue, uint8_t cscAddress);

DownscaledCurrentViolationHistogramNvm cscNvm_getDownscaledCurrentViolationHistogramCounters(uint8_t cscAddress);
bool cscNvm_setDownscaledCurrentViolationHistogramCounters(DownscaledCurrentViolationHistogramNvm newValue, uint8_t cscAddress);

void cscNvm_getKbsCscNvmData(uint8_t* buffer, uint8_t cscAddress);
bool cscNvm_setKbsCscNvmData(const uint8_t* buffer, uint16_t length, uint8_t cscAddress);
