/**
 * @file vehicleManufacturerData.h
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
#include <stdbool.h>

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define VEHICLE_MANUFACTURER_DATA_VEHICLE_IDENTIFICATION_NUMBER_SIZE 16u

typedef struct
{
    uint8_t vinAvailability;
    char vehicleIdentificationNumber[VEHICLE_MANUFACTURER_DATA_VEHICLE_IDENTIFICATION_NUMBER_SIZE];
    bool vinWrittenAlready;
    bool vinAvailabilityWrittenAlready;
    uint8_t reserveBytes[1];
} VehicleManufacturerNvmData;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

uint8_t vehicleManufacturerData_getVehicleIdentificationNumberAvailability(void);
bool vehicleManufacturerData_setVehicleIdentificationNumberAvailability(uint8_t newValue);

const char* vehicleManufacturerData_getVehicleIdentificationNumber(uint8_t* maxStringLength);
void vehicleManufacturerData_setVehicleIdentificationNumber(const char* newString);

bool vehicleManufacturerData_getVinWrittenAlready();
bool vehicleManufacturerData_getVinAvailabilityWrittenAlready();

#if defined(HIL_CONFIGURATION) || defined(SIL_DEBUG)
void vehicleManufacturerData_resetVinAvailabilityWrittenAlready();
#endif
