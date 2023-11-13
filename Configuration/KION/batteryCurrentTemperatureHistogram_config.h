/**
 * @file batteryCurrentTemperatureHistogram_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */

#include "nvm_config_id.h"
#include <stdint.h>

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//
#define BATTERY_CURRENT_TEMPERATURE_HISTOGRAM_TEMPERATURE_POSITION 0
#define BATTERY_CURRENT_TEMPERATURE_HISTOGRAM_CURRENT_POSITION     1
#define BATTERY_CURRENT_TEMPERATURE_DISCHARGE_HISTOGRAM_POSITION   0
#define BATTERY_CURRENT_TEMPERATURE_CHARGE_HISTOGRAM_POSITION      1


#define BATTERY_CURRENT_TEMPERATURE_HISTOGRAM_COUNTER_SIZE 192


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
