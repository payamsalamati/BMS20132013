/**
 * @file cscNvm_config.c
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stddef.h>
#include "cscNvm_config.h"
#include "cscNvm.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

bool cscNvm_getDeepDischargeFlag(uint8_t cscAddress)
{
    bool retVal              = false;
    const CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        retVal = cscPtr->deepDischargeFlag;
    }
    return retVal;
}

void cscNvm_setDeepDischargeFlag(uint8_t newValue, uint8_t cscAddress)
{
    CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        cscPtr->deepDischargeFlag = newValue;
    }
}

void cscNvm_getCSCPcbKbsSerialNumber(uint8_t* buffer, uint8_t cscAddress)
{
    const CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        memcpy(buffer, (void*)&(cscPtr->cscPcbKbsSerialNumber[0]), CSC_NVM_CSC_PCB_KBS_SERIAL_NUMBER_LENGTH);
    }
}

bool cscNvm_setCSCPcbKbsSerialNumber(const uint8_t* buffer, uint16_t length, uint8_t cscAddress)
{
    bool retVal = true;
    if(length != CSC_NVM_CSC_PCB_KBS_SERIAL_NUMBER_LENGTH)
    {
        retVal = false;
    }
    if(retVal != false)
    {
        CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
        if(cscPtr == NULL)
        {
            retVal = false;
        }
        if(retVal != false)
        {
            memcpy(&(cscPtr->cscPcbKbsSerialNumber[0]), buffer, length);
        }
    }
    return retVal;
}

uint16_t cscNvm_getModuleNominalVoltage(uint8_t cscAddress)
{
    uint16_t retVal          = 0u;
    const CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        retVal = cscPtr->moduleNominalVoltage;
    }
    return retVal;
}

bool cscNvm_setModuleNominalVoltage(uint16_t newValue, uint8_t cscAddress)
{
    bool retVal        = false;
    CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        cscPtr->moduleNominalVoltage = newValue;
        retVal                       = true;
    }
    return retVal;
}

void cscNvm_setCscPcbHardwareVersion(uint16_t newValue, uint8_t cscAddress)
{
    CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        cscPtr->cscPcbHardwareVersion = newValue;
    }
}

uint16_t cscNvm_getCscPcbHardwareVersion(uint8_t cscAddress)
{
    uint16_t retVal    = 0;
    CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        retVal = cscPtr->cscPcbHardwareVersion;
    }
    return retVal;
}

uint8_t cscNvm_getEolTestResult(uint8_t cscAddress)
{
    uint8_t retVal           = 0u;
    const CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        retVal = cscPtr->eolTestResult;
    }
    return retVal;
}

bool cscNvm_setEolTestResult(uint8_t newValue, uint8_t cscAddress)
{
    bool retVal        = false;
    CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        cscPtr->eolTestResult = newValue;
        retVal                = true;
    }
    return retVal;
}


DownscaledCurrentViolationHistogramNvm cscNvm_getDownscaledCurrentViolationHistogramCounters(uint8_t cscAddress)
{
    DownscaledCurrentViolationHistogramNvm retVal = { 0 };
    const CscNvmData* cscPtr                      = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        retVal = cscPtr->downscaledCurrentViolationHistogramCounters;
    }
    return retVal;
}

bool cscNvm_setDownscaledCurrentViolationHistogramCounters(DownscaledCurrentViolationHistogramNvm newValue, uint8_t cscAddress)
{
    bool retVal        = false;
    CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        cscPtr->downscaledCurrentViolationHistogramCounters = newValue;
        retVal                                              = true;
    }
    return retVal;
}


void cscNvm_getKbsCscNvmData(uint8_t* buffer, uint8_t cscAddress)
{
    const CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
    if(cscPtr != NULL)
    {
        memcpy(buffer, (void*)&(cscPtr->kbsCscNvmData[0]), CSC_NVM_KBS_CSC_NVM_DATA_LENGTH);
    }
}

bool cscNvm_setKbsCscNvmData(const uint8_t* buffer, uint16_t length, uint8_t cscAddress)
{
    bool retVal = true;
    if(length != CSC_NVM_KBS_CSC_NVM_DATA_LENGTH)
    {
        retVal = false;
    }
    if(retVal != false)
    {
        CscNvmData* cscPtr = cscNvm_getNvmData(cscAddress);
        if(cscPtr == NULL)
        {
            retVal = false;
        }
        if(retVal != false)
        {
            memcpy(&(cscPtr->kbsCscNvmData[0]), buffer, length);
        }
    }
    return retVal;
}
