/**
 * @file     configuration_callbacks.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * *  Detaillierte Beschreibung des Moduls
 *
 *
 */
//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "warrantyData.h"

#include "systemMasterData.h"
#include "cellTemperatureMeasurement.h"
#include "contactorHistogram.h"
#include "submasterVoltageMeasurement.h"
#include "batteryCurrentMeasurement.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//


void safety_relayOpenedCallback(uint8_t relayNumber, int32_t current, uint32_t systemVoltage, int8_t maxTemperature)
{
    contactorHistogram_reportOpening(relayNumber, current, systemVoltage, maxTemperature);
}

int32_t safety_getBatteryCurrent(void)
{
    return batteryCurrentMeasurement_getValue();
}

uint32_t safety_getSystemVoltage(void)
{
    return submasterVoltageMeasurement_getValue();
}


int8_t safety_getMaxTemperature(void)
{
    return cellTemperatureMeasurement_getMaxValue();
}

bool safety_getWarrantyStopped(void)
{
    return warrantyData_getStopped();
}

void safety_relayClosedCallback(uint8_t relayNumber)
{
}
