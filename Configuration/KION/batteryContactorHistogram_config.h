/**
 * @file batteryContactorHistogram.h
 * @copyright (c) Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
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

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//

#define BATTERY_CONTACTOR_HISTOGRAM_CONFIG CONFIG_ENABLED

#define BATTERY_CONTACTOR_HISTOGRAM_LIMITS_SIZE  23u
#define BATTERY_CONTACTOR_HISTOGRAM_COUNTER_SIZE 48u

#define BATTERY_CONTACTOR_HISTOGRAM_CURRENT_MIN_LIMIT -1000
#define BATTERY_CONTACTOR_HISTOGRAM_CURRENT_MAX_LIMIT 1000

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
