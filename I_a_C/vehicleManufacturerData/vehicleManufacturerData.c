/**
 * @file vehicleManufacturerData.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "vehicleManufacturerData.h"
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

MEM_APPLICATION VehicleManufacturerNvmData vehicleManufacturerNvm;

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
        dst[dstLength - 1u] = '\0';
    }
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

uint8_t vehicleManufacturerData_getVehicleIdentificationNumberAvailability(void)
{
    return vehicleManufacturerNvm.vinAvailability;
}

bool vehicleManufacturerData_setVehicleIdentificationNumberAvailability(uint8_t newValue)
{
    bool retVal = false;
    if(newValue <= (uint8_t)1)
    {
        vehicleManufacturerNvm.vinAvailability               = newValue;
        retVal                                               = true;
        vehicleManufacturerNvm.vinAvailabilityWrittenAlready = true;
    }
    return retVal;
}

const char* vehicleManufacturerData_getVehicleIdentificationNumber(uint8_t* maxStringLength)
{
    DEBUG_API_CHECK(maxStringLength != NULL);
    *maxStringLength = VEHICLE_MANUFACTURER_DATA_VEHICLE_IDENTIFICATION_NUMBER_SIZE;
    return vehicleManufacturerNvm.vehicleIdentificationNumber;
}

void vehicleManufacturerData_setVehicleIdentificationNumber(const char* newString)
{
    DEBUG_API_CHECK(newString != NULL);
    copyStringAndTerminateIfOverflow(vehicleManufacturerNvm.vehicleIdentificationNumber, newString, VEHICLE_MANUFACTURER_DATA_VEHICLE_IDENTIFICATION_NUMBER_SIZE);
    vehicleManufacturerNvm.vinWrittenAlready = true;
}

bool vehicleManufacturerData_getVinWrittenAlready()
{
    return vehicleManufacturerNvm.vinWrittenAlready;
}

bool vehicleManufacturerData_getVinAvailabilityWrittenAlready()
{
    return vehicleManufacturerNvm.vinAvailabilityWrittenAlready;
}

#if defined(HIL_CONFIGURATION) || defined(SIL_DEBUG)
void vehicleManufacturerData_resetVinAvailabilityWrittenAlready()
{
    vehicleManufacturerNvm.vinAvailabilityWrittenAlready = false;
    vehicleManufacturerNvm.vinWrittenAlready             = false;
}
#endif
