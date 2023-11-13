/**
 * @file ecuIdentification.h
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

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define ECU_IDENTIFICATION_VEHICLE_MANUFACTURER_ECU_HARDWARE_NUMBER 16U
#define ECU_IDENTIFICATION_SYSTEM_NAME_OR_ENGINE_TYPE               16U
#define ECU_IDENTIFICATION_ECU_MANUFACTURING_DATE                   3U
#define ECU_IDENTIFICATION_ECU_SERIAL_NUMBER                        16U
#define ECU_IDENTIFICATION_VEHICLE_MANUFACTURER_SPARE_PART_NUMBER   16U

typedef struct
{
    uint16_t ecuHardwareVersionNumber;
    char vehicleManufacturerEcuHardwareNumber[ECU_IDENTIFICATION_VEHICLE_MANUFACTURER_ECU_HARDWARE_NUMBER];
    char systemNameOrEngineType[ECU_IDENTIFICATION_SYSTEM_NAME_OR_ENGINE_TYPE];
    char ecuManufacturingDate[ECU_IDENTIFICATION_ECU_MANUFACTURING_DATE];
    char ecuSerialNumber[ECU_IDENTIFICATION_ECU_SERIAL_NUMBER];
    char vehicleManufacturerSparePartNumber[ECU_IDENTIFICATION_VEHICLE_MANUFACTURER_SPARE_PART_NUMBER];
    uint16_t brandId;
    uint8_t reserve[23];
    uint32_t dummy_reserve_for_crc;
} EcuIdentificationNvmData;
//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

uint16_t ecuIdentification_getEcuHardwareVersionNumber(void);
char* ecuIdentification_getEcuHardwareVersionNumberByString(uint16_t* maxStringLength);
void ecuIdentification_setEcuHardwareVersionNumber(uint16_t newValue);

const char* ecuIdentification_getVehicleManufacturerEcuHardwareNumber(uint8_t* maxStringLength);
void ecuIdentification_setVehicleManufacturerEcuHardwareNumber(const char* newString);

const char* ecuIdentification_getSystemNameOrEngineType(uint8_t* maxStringLength);
void ecuIdentification_setSystemNameOrEngineType(const char* newString);

const char* ecuIdentification_getEcuManufacturingDate(uint8_t* maxStringLength);
void ecuIdentification_setEcuManufacturingDate(const char* newString);

const char* ecuIdentification_getEcuSerialNumber(uint8_t* maxStringLength);
void ecuIdentification_setEcuSerialNumber(const char* newString);

const char* ecuIdentification_getVehicleManufacturerSparePartNumber(uint8_t* maxStringLength);
void ecuIdentification_setVehicleManufacturerSparePartNumber(const char* newString);

uint16_t ecuIdentification_getBrandId(void);
void ecuIdentification_setBrandId(uint16_t newValue);
