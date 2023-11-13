

/**
 * @file libIdentification.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
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

#include "libIdentification.h"

#include "task_cfg.h"
#include "debug.h"
#include <string.h>

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static void copyStringAndTerminateIfOverflow(char* dst, const char* src, uint8_t dstLength);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_APPLICATION LibIdentificationNvmData libIdentificationNvm;

MEM_SEC_PARAMETER LibIdentificationParameterData libIdentificationParameter;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static void copyStringAndTerminateIfOverflow(char* dst, const char* src, uint8_t dstLength)
{
    DEBUG_API_CHECK(dst != NULL);
    DEBUG_API_CHECK(src != NULL);
    if((dst != NULL) && (src != NULL))
    {
        strncpy(dst, src, dstLength);
        if(dst[dstLength - 1u] != '\0')
        {
            dst[dstLength - 1u] = '\0';
        }
    }
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

const char* libIdentification_getLibManufacturerName(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_MANUFACTURER_NAME_STRING_LENGTH;
    return libIdentificationNvm.libManufacturerName;
}

void libIdentification_setLibManufacturerName(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libManufacturerName, newString, LIB_IDENTIFICATION_MANUFACTURER_NAME_STRING_LENGTH);
}

uint32_t libIdentification_getLibManufacturingDate(void)
{
    return libIdentificationNvm.libManufacturingDate;
}

void libIdentification_setLibManufacturingDate(uint32_t newValue)
{
    libIdentificationNvm.libManufacturingDate = newValue;
}

const char* libIdentification_getLibDeviceName(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_DEVICE_NAME_STRING_LENGTH;
    return libIdentificationNvm.libDeviceName;
}

void libIdentification_setLibDeviceName(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libDeviceName, newString, LIB_IDENTIFICATION_DEVICE_NAME_STRING_LENGTH);
}

const char* libIdentification_getLibTrayVariant(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_TRAY_VARIANT_STRING_LENGTH;
    return libIdentificationNvm.libTrayVariant;
}

void libIdentification_setLibTrayVariant(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libTrayVariant, newString, LIB_IDENTIFICATION_TRAY_VARIANT_STRING_LENGTH);
}

const char* libIdentification_getLibCellTypeName(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_CELL_TYPE_NAME_STRING_LENGTH;
    return libIdentificationNvm.libCellTypeName;
}

void libIdentification_setLibCellTypeName(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libCellTypeName, newString, LIB_IDENTIFICATION_CELL_TYPE_NAME_STRING_LENGTH);
}

const char* libIdentification_getLibKionHardwareNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_KION_HW_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.libKionHardwareNumber;
}

void libIdentification_setLibKionHardwareNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libKionHardwareNumber, newString, LIB_IDENTIFICATION_KION_HW_NUMBER_STRING_LENGTH);
}

const char* libIdentification_getLibKionPartNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_KION_PART_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.libKionPartNumber;
}

void libIdentification_setLibKionPartNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libKionPartNumber, newString, LIB_IDENTIFICATION_KION_PART_NUMBER_STRING_LENGTH);
}

const char* libIdentification_getLibKionZsbNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_KION_ZSB_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.libKionZsbNumber;
}

void libIdentification_setLibKionZsbNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libKionZsbNumber, newString, LIB_IDENTIFICATION_KION_ZSB_NUMBER_STRING_LENGTH);
}

const char* libIdentification_getLibKionOrderNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_KION_ORDER_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.libKionOrderNumber;
}

void libIdentification_setLibKionOrderNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libKionOrderNumber, newString, LIB_IDENTIFICATION_KION_ORDER_NUMBER_STRING_LENGTH);
}

const char* libIdentification_getLibKionCustomerOrderNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_KION_CUSTOMER_ORDER_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.libKionCustomerOrderNumber;
}

void libIdentification_setLibKionCustomerOrderNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libKionCustomerOrderNumber, newString, LIB_IDENTIFICATION_KION_CUSTOMER_ORDER_NUMBER_STRING_LENGTH);
}

const char* libIdentification_getLibKionSequenceNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_KION_SEQUENCE_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.libKionSequenceNumber;
}

void libIdentification_setLibKionSequenceNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libKionSequenceNumber, newString, LIB_IDENTIFICATION_KION_SEQUENCE_NUMBER_STRING_LENGTH);
}

const char* libIdentification_getLibKbsBpn(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_KION_BPN_STRING_LENGTH;
    return libIdentificationNvm.libKbsBpn;
}

void libIdentification_setLibKbsBpn(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libKbsBpn, newString, LIB_IDENTIFICATION_KION_BPN_STRING_LENGTH);
}

const char* libIdentification_getLibKbsSerialNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_KION_SERIAL_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.libKbsSerialNumber;
}

void libIdentification_setLibKbsSerialNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libKbsSerialNumber, newString, LIB_IDENTIFICATION_KION_SERIAL_NUMBER_STRING_LENGTH);
}

const char* libIdentification_getLibKbsPartNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_KION_PART_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.libKbsPartNumber;
}

void libIdentification_setLibKbsPartNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.libKbsPartNumber, newString, LIB_IDENTIFICATION_KION_PART_NUMBER_STRING_LENGTH);
}

uint32_t libIdentification_getLibParameterVersion(void)
{
    return libIdentificationNvm.libParameterVersion;
}

void libIdentification_setLibParameterVersion(uint32_t newValue)
{
    libIdentificationNvm.libParameterVersion = newValue;
}

uint8_t libIdentification_getLibEolTestResult(void)
{
    return libIdentificationNvm.libEolTestResult;
}

void libIdentification_setLibEolTestResult(uint8_t newValue)
{
    libIdentificationNvm.libEolTestResult = newValue;
}

uint32_t libIdentification_getLibNameplateNominalVoltage(void)
{
    return libIdentificationParameter.libNameplateNominalVoltage;
}

void libIdentification_setLibNameplateNominalVoltage(uint32_t newValue)
{
    libIdentificationParameter.libNameplateNominalVoltage = newValue;
}

uint16_t libIdentification_getLibNameplateNumberOfParallelConnectedCells(void)
{
    return libIdentificationParameter.libNameplateNumberOfParallelConnectedCells;
}

void libIdentification_setLibNameplateNumberOfParallelConnectedCells(uint16_t newValue)
{
    libIdentificationParameter.libNameplateNumberOfParallelConnectedCells = newValue;
}

uint16_t libIdentification_getLibNameplateNumberOfSerialConnectedCells(void)
{
    return libIdentificationParameter.libNameplateNumberOfSerialConnectedCells;
}

void libIdentification_setLibNameplateNumberOfSerialConnectedCells(uint16_t newValue)
{
    libIdentificationParameter.libNameplateNumberOfSerialConnectedCells = newValue;
}

uint32_t libIdentification_getLibNameplateMaxChargeCurrent(void)
{
    return libIdentificationParameter.libNameplateMaxChargeCurrent;
}

void libIdentification_setLibNameplateMaxChargeCurrent(uint32_t newValue)
{
    libIdentificationParameter.libNameplateMaxChargeCurrent = newValue;
}

uint32_t libIdentification_getLibNameplateMaxDischargeCurrent(void)
{
    return libIdentificationParameter.libNameplateMaxDischargeCurrent;
}

void libIdentification_setLibNameplateMaxDischargeCurrent(uint32_t newValue)
{
    libIdentificationParameter.libNameplateMaxDischargeCurrent = newValue;
}

uint32_t libIdentification_getLibNameplateMaxChargeVoltage(void)
{
    return libIdentificationParameter.libNameplateMaxChargeVoltage;
}

void libIdentification_setLibNameplateMaxChargeVoltage(uint32_t newValue)
{
    libIdentificationParameter.libNameplateMaxChargeVoltage = newValue;
}

uint32_t libIdentification_getLibNameplateMaxDischargeVoltage(void)
{
    return libIdentificationParameter.libNameplateMaxDischargeVoltage;
}

void libIdentification_setLibNameplateMaxDischargeVoltage(uint32_t newValue)
{
    libIdentificationParameter.libNameplateMaxDischargeVoltage = newValue;
}

uint16_t libIdentification_getLibNameplateCapacity(void)
{
    return libIdentificationParameter.libNameplateCapacity;
}

void libIdentification_setLibNameplateCapacity(uint16_t newValue)
{
    libIdentificationParameter.libNameplateCapacity = newValue;
}

uint16_t libIdentification_getLibNameplateCapacityEquivalentLab(void)
{
    return libIdentificationParameter.libNameplateCapacityEquivalentLab;
}

void libIdentification_setLibNameplateCapacityEquivalentLab(uint16_t newValue)
{
    libIdentificationParameter.libNameplateCapacityEquivalentLab = newValue;
}

uint32_t libIdentification_getLibNameplateEnergyContent(void)
{
    return libIdentificationParameter.libNameplateEnergyContent;
}

void libIdentification_setLibNameplateEnergyContent(uint32_t newValue)
{
    libIdentificationParameter.libNameplateEnergyContent = newValue;
}

uint16_t libIdentification_getLibNameplateWeight(void)
{
    return libIdentificationParameter.libNameplateWeight;
}

void libIdentification_setLibNameplateWeight(uint16_t newValue)
{
    libIdentificationParameter.libNameplateWeight = newValue;
}

const char* libIdentification_getMasterPcbManufacturer(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_MASTER_PCB_MANUFACTURER_STRING_LENGTH;
    return libIdentificationNvm.masterPcbManufacturer;
}

void libIdentification_setMasterPcbManufacturer(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.masterPcbManufacturer, newString, LIB_IDENTIFICATION_MASTER_PCB_MANUFACTURER_STRING_LENGTH);
}

uint32_t libIdentification_getMasterPcbManufacturingDate(void)
{
    return libIdentificationNvm.masterPcbManufacturingDate;
}

void libIdentification_setMasterPcbManufacturingDate(uint32_t newValue)
{
    libIdentificationNvm.masterPcbManufacturingDate = newValue;
}

const char* libIdentification_getMasterPcbDeviceName(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_MASTER_PCB_DEVICE_NAME_STRING_LENGTH;
    return libIdentificationNvm.masterPcbDeviceName;
}

void libIdentification_setMasterPcbDeviceName(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.masterPcbDeviceName, newString, LIB_IDENTIFICATION_MASTER_PCB_DEVICE_NAME_STRING_LENGTH);
}

const char* libIdentification_getMasterPcbKbsSerialNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_MASTER_PCB_KBS_SERIAL_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.masterPcbKbsSerialNumber;
}

void libIdentification_setMasterPcbKbsSerialNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.masterPcbKbsSerialNumber, newString, LIB_IDENTIFICATION_MASTER_PCB_KBS_SERIAL_NUMBER_STRING_LENGTH);
}

const char* libIdentification_getMasterPcbKbsPartNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_MASTER_PCB_KBS_PART_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.masterPcbKbsPartNumber;
}

void libIdentification_setMasterPcbKbsPartNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.masterPcbKbsPartNumber, newString, LIB_IDENTIFICATION_MASTER_PCB_KBS_PART_NUMBER_STRING_LENGTH);
}

uint8_t libIdentification_getMasterPcbEolTestResult(void)
{
    return libIdentificationNvm.masterPcbEolTestResult;
}

void libIdentification_setMasterPcbEolTestResult(uint8_t newValue)
{
    libIdentificationNvm.masterPcbEolTestResult = newValue;
}

const char* libIdentification_getCpsPcbManufacturer(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_CPS_PCB_MANUFACTURER_STRING_LENGTH;
    return libIdentificationNvm.cpsPcbManufacturer;
}

void libIdentification_setCpsPcbManufacturer(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.cpsPcbManufacturer, newString, LIB_IDENTIFICATION_CPS_PCB_MANUFACTURER_STRING_LENGTH);
}

uint32_t libIdentification_getCpsPcbManufacturingDate(void)
{
    return libIdentificationNvm.cpsPcbManufacturingDate;
}

void libIdentification_setCpsPcbManufacturingDate(uint32_t newValue)
{
    libIdentificationNvm.cpsPcbManufacturingDate = newValue;
}

const char* libIdentification_getCpsPcbDeviceName(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_CPS_PCB_DEVICE_NAME_STRING_LENGTH;
    return libIdentificationNvm.cpsPcbDeviceName;
}

void libIdentification_setCpsPcbDeviceName(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.cpsPcbDeviceName, newString, LIB_IDENTIFICATION_CPS_PCB_DEVICE_NAME_STRING_LENGTH);
}

const char* libIdentification_getCpsPcbKbsSerialNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_CPS_PCB_KBS_SERIAL_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.cpsPcbKbsSerialNumber;
}

void libIdentification_setCpsPcbKbsSerialNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.cpsPcbKbsSerialNumber, newString, LIB_IDENTIFICATION_CPS_PCB_KBS_SERIAL_NUMBER_STRING_LENGTH);
}

const char* libIdentification_getCpsPcbKbsPartNumber(uint8_t* maxStringLength)
{
    *maxStringLength = LIB_IDENTIFICATION_CPS_PCB_KBS_PART_NUMBER_STRING_LENGTH;
    return libIdentificationNvm.cpsPcbKbsPartNumber;
}

void libIdentification_setCpsPcbKbsPartNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(libIdentificationNvm.cpsPcbKbsPartNumber, newString, LIB_IDENTIFICATION_CPS_PCB_KBS_PART_NUMBER_STRING_LENGTH);
}

uint8_t libIdentification_getCpsPcbEolTestResult(void)
{
    return libIdentificationNvm.cpsPcbEolTestResult;
}

void libIdentification_setCpsPcbEolTestResult(uint8_t newValue)
{
    libIdentificationNvm.cpsPcbEolTestResult = newValue;
}

const char* libIdentification_getListOfConnectedModuleSerialNumbers(uint8_t cscNumber, uint8_t* maxStringLength)
{
    DEBUG_API_CHECK(cscNumber < BMS_CONFIG_MAX_NUMBER_OF_SLAVES);
    DEBUG_API_CHECK(maxStringLength != NULL);
    char* retVal = NULL;
    if((cscNumber < BMS_CONFIG_MAX_NUMBER_OF_SLAVES) && (maxStringLength != NULL))
    {
        *maxStringLength = LIB_IDENTIFICATION_MODULE_SERIAL_NUMBER_STRING_LENGTH;
        retVal           = libIdentificationNvm.listOfConnectedModuleSerialNumbers[cscNumber];
    }
    return retVal;
}

void libIdentification_setListOfConnectedModuleSerialNumbers(uint8_t cscNumber, const char* newString)
{
    DEBUG_API_CHECK(cscNumber < BMS_CONFIG_MAX_NUMBER_OF_SLAVES);
    DEBUG_API_CHECK(newString != NULL);
    if((cscNumber < BMS_CONFIG_MAX_NUMBER_OF_SLAVES) && (newString != NULL))
    {
        copyStringAndTerminateIfOverflow(libIdentificationNvm.listOfConnectedModuleSerialNumbers[cscNumber], newString, LIB_IDENTIFICATION_MODULE_SERIAL_NUMBER_STRING_LENGTH);
    }
}

const char* libIdentification_getListOfConnectedModulePcbSerialNumbers(uint8_t cscNumber, uint8_t* maxStringLength)
{
    DEBUG_API_CHECK(cscNumber < BMS_CONFIG_MAX_NUMBER_OF_SLAVES);
    DEBUG_API_CHECK(maxStringLength != NULL);
    char* retVal = NULL;
    if((cscNumber < BMS_CONFIG_MAX_NUMBER_OF_SLAVES) && (maxStringLength != NULL))
    {
        *maxStringLength = LIB_IDENTIFICATION_MODULE_PCB_SERIAL_NUMBER_STRING_LENGTH;
        retVal           = libIdentificationNvm.listOfConnectedModulePcbSerialNumbers[cscNumber];
    }
    return retVal;
}

void libIdentification_setListOfConnectedModulePcbSerialNumbers(uint8_t cscNumber, const char* newString)
{
    DEBUG_API_CHECK(cscNumber < BMS_CONFIG_MAX_NUMBER_OF_SLAVES);
    DEBUG_API_CHECK(newString != NULL);
    if((cscNumber < BMS_CONFIG_MAX_NUMBER_OF_SLAVES) && (newString != NULL))
    {
        copyStringAndTerminateIfOverflow(libIdentificationNvm.listOfConnectedModulePcbSerialNumbers[cscNumber], newString, LIB_IDENTIFICATION_MODULE_PCB_SERIAL_NUMBER_STRING_LENGTH);
    }
}

const char* libIdentification_getVehicleIdentificationNumber(uint8_t index, uint8_t* maxStringLength)
{
    DEBUG_API_CHECK(maxStringLength != NULL);
    uint8_t ringBufferIndex;
    if(index > libIdentificationNvm.ringBufferVinsIndex)
    {
        ringBufferIndex = LIB_IDENTIFICATION_NUMBERS_OF_VINS_TO_STORE - index + libIdentificationNvm.ringBufferVinsIndex;
    }
    else
    {
        ringBufferIndex = libIdentificationNvm.ringBufferVinsIndex - index;
    }
    char* retVal = NULL;
    if(maxStringLength != NULL)
    {
        *maxStringLength = LIB_IDENTIFICATION_VIN_STRING_LENGTH;
        retVal           = libIdentificationNvm.listOfConnectedVins[ringBufferIndex];
    }
    return retVal;
}

void libIdentification_insertToRingVehicleIdentificationNumber(const char* newString)
{
    DEBUG_API_CHECK(newString != NULL);
    if(newString != NULL)
    {
        if(memcmp(newString, libIdentificationNvm.listOfConnectedVins[libIdentificationNvm.ringBufferVinsIndex], (LIB_IDENTIFICATION_VIN_STRING_LENGTH - 1u)) != 0)
        {
            libIdentificationNvm.ringBufferVinsIndex++;
            if(libIdentificationNvm.ringBufferVinsIndex >= LIB_IDENTIFICATION_NUMBERS_OF_VINS_TO_STORE)
            {
                libIdentificationNvm.ringBufferVinsIndex = 0u;
            }
            memcpy(libIdentificationNvm.listOfConnectedVins[libIdentificationNvm.ringBufferVinsIndex], newString, LIB_IDENTIFICATION_VIN_STRING_LENGTH);
        }
    }
}
