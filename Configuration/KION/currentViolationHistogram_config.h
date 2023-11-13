/**
 * @file currentViolationHistogram_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
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
#define CURRENT_VIOLATION_HISTOGRAM_TIME_REGEN_POSITION     0
#define CURRENT_VIOLATION_HISTOGRAM_TIME_DISCHARGE_POSITION 1
#define CURRENT_VIOLATION_HISTOGRAM_TIME_CHARGE_POSITION    2

#define CURRENT_VIOLATION_HISTOGRAM_PULSE_HISTOGRAM_POSITION 0
#define CURRENT_VIOLATION_HISTOGRAM_CONT_HISTOGRAM_POSITION  1

#define CURRENT_VIOLATION_HISTOGRAM_NUMBER_OF_DRIVE_DISCHARGE_RING_VALUES 10
#define CURRENT_VIOLATION_HISTOGRAM_NUMBER_OF_DRIVE_CHARGE_RING_VALUES    15
#define CURRENT_VIOLATION_HISTOGRAM_NUMBER_OF_CHARGE_RING_VALUES          100

#define CURRENT_VIOLATION_HISTOGRAM_HISTOGRAM_CHARGE_OFFSET 8u

#define CURRENT_VIOLATION_HISTOGRAM_PULSE_COUNTER_SIZE 18
#define CURRENT_VIOLATION_HISTOGRAM_CONT_COUNTER_SIZE  18

#define CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_REGENERATION_RMS_LIMIT_IN_S 10
#define CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_DISCHARGING_LIMIT_IN_S      15
#define CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_CHARGING_RMS_LIMIT_IN_S     100
#define CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_DISCHARGING_RMS_LIMIT_IN_S  100
#define CURRENT_VIOLATION_DEFAULT_HISTOGRAM_VIOLATION_COEFFICIENT            110

#define CURRENT_VIOLATION_MAX_HISTOGRAM_VIOLATION_COEFFICIENT 253

#define BATTERY_CURRENT_RING_LENGTH        CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_DISCHARGING_RMS_LIMIT_IN_S
#define MAX_CHARGE_2S_PULSE_RING_LENGTH    CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_REGENERATION_RMS_LIMIT_IN_S
#define MAX_DISCHARGE_2S_PULSE_RING_LENGTH CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_DISCHARGING_RMS_LIMIT_IN_S

#define MEAN_BATTERY_CURRENT_CONT_RING_LENGTH    CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_CHARGING_RMS_LIMIT_IN_S / 4
#define MEAN_MAX_CHARGE_100S_CONT_RING_LENGTH    CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_CHARGING_RMS_LIMIT_IN_S / 4
#define MEAN_MAX_DISCHARGE_100S_CONT_RING_LENGTH CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_DISCHARGING_RMS_LIMIT_IN_S / 4
#define CURRENT_VIOLATION_CONT_MEAN_RANGE        4

#define CURRENT_VIOLATION_HISTOGRAM_I_CONT_CHARGE_OFFSET    15000
#define CURRENT_VIOLATION_HISTOGRAM_I_CONT_DISCHARGE_OFFSET 15000

#define CURRENT_VIOLATION_HISTOGRAM_I_PULSE_CHARGE_OFFSET    15000
#define CURRENT_VIOLATION_HISTOGRAM_I_PULSE_DISCHARGE_OFFSET 15000

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
