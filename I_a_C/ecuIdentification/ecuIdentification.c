/**
 * @file ecuIdentification.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <string.h>

#include "ecuIdentification.h"
#include "fut_string.h"
#include "task_cfg.h"
#include "debug.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

#define ECU_HARDWARE_VERSION_STRING_LENGTH 8u

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static void copyStringAndTerminateIfOverflow(char* dst, const char* src, uint8_t dstLength);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_APPLICATION EcuIdentificationNvmData ecuIdentificationNvm;

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
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

uint16_t ecuIdentification_getEcuHardwareVersionNumber(void)
{
    return ecuIdentificationNvm.ecuHardwareVersionNumber;
}

char* ecuIdentification_getEcuHardwareVersionNumberByString(uint16_t* maxStringLength)
{
    *maxStringLength = ECU_HARDWARE_VERSION_STRING_LENGTH;

    MEM_SHAREDATA static char ecuHwVersionNumberString[ECU_HARDWARE_VERSION_STRING_LENGTH] = "";

    memset(ecuHwVersionNumberString, 0, sizeof(ecuHwVersionNumberString));

    uint8_t highByte = (uint8_t)(ecuIdentificationNvm.ecuHardwareVersionNumber >> 8u);
    string_convertDecToStr(highByte, ecuHwVersionNumberString);

    string_addDotToString(ecuHwVersionNumberString);

    uint8_t lowByte = (uint8_t)ecuIdentificationNvm.ecuHardwareVersionNumber;
    string_convertDecToStr(lowByte, ecuHwVersionNumberString);

    return ecuHwVersionNumberString;
}

void ecuIdentification_setEcuHardwareVersionNumber(uint16_t newValue)
{
    ecuIdentificationNvm.ecuHardwareVersionNumber = newValue;
}

const char* ecuIdentification_getVehicleManufacturerEcuHardwareNumber(uint8_t* maxStringLength)
{
    *maxStringLength = ECU_IDENTIFICATION_VEHICLE_MANUFACTURER_ECU_HARDWARE_NUMBER;
    return ecuIdentificationNvm.vehicleManufacturerEcuHardwareNumber;
}

void ecuIdentification_setVehicleManufacturerEcuHardwareNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(ecuIdentificationNvm.vehicleManufacturerEcuHardwareNumber, newString, ECU_IDENTIFICATION_VEHICLE_MANUFACTURER_ECU_HARDWARE_NUMBER);
}

const char* ecuIdentification_getSystemNameOrEngineType(uint8_t* maxStringLength)
{
    *maxStringLength = ECU_IDENTIFICATION_SYSTEM_NAME_OR_ENGINE_TYPE;
    return ecuIdentificationNvm.systemNameOrEngineType;
}

void ecuIdentification_setSystemNameOrEngineType(const char* newString)
{
    copyStringAndTerminateIfOverflow(ecuIdentificationNvm.systemNameOrEngineType, newString, ECU_IDENTIFICATION_SYSTEM_NAME_OR_ENGINE_TYPE);
}

const char* ecuIdentification_getEcuManufacturingDate(uint8_t* maxStringLength)
{
    *maxStringLength = ECU_IDENTIFICATION_ECU_MANUFACTURING_DATE;
    return ecuIdentificationNvm.ecuManufacturingDate;
}

void ecuIdentification_setEcuManufacturingDate(const char* newString)
{
    memcpy(ecuIdentificationNvm.ecuManufacturingDate, newString, ECU_IDENTIFICATION_ECU_MANUFACTURING_DATE);
}

const char* ecuIdentification_getEcuSerialNumber(uint8_t* maxStringLength)
{
    *maxStringLength = ECU_IDENTIFICATION_ECU_SERIAL_NUMBER;
    return ecuIdentificationNvm.ecuSerialNumber;
}

void ecuIdentification_setEcuSerialNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(ecuIdentificationNvm.ecuSerialNumber, newString, ECU_IDENTIFICATION_ECU_SERIAL_NUMBER);
}

const char* ecuIdentification_getVehicleManufacturerSparePartNumber(uint8_t* maxStringLength)
{
    *maxStringLength = ECU_IDENTIFICATION_VEHICLE_MANUFACTURER_SPARE_PART_NUMBER;
    return ecuIdentificationNvm.vehicleManufacturerSparePartNumber;
}

void ecuIdentification_setVehicleManufacturerSparePartNumber(const char* newString)
{
    copyStringAndTerminateIfOverflow(ecuIdentificationNvm.vehicleManufacturerSparePartNumber, newString, ECU_IDENTIFICATION_VEHICLE_MANUFACTURER_SPARE_PART_NUMBER);
}

uint16_t ecuIdentification_getBrandId(void)
{
    return ecuIdentificationNvm.brandId;
}

void ecuIdentification_setBrandId(uint16_t newValue)
{
    ecuIdentificationNvm.brandId = newValue;
}
