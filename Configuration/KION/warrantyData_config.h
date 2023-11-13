/**
 * @file     warrantyData_config.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "config_enable.h"
#include "systemMasterData.h"
#include "idAllocation.h"
#include "nvm_config_id.h"

#include "cellVoltageMeasurement.h"
#include "cellTemperatureMeasurement.h"
#define DATA_INCLUDE "dataInterface.h"

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//
/**
 * @brief defines for histogram for cell voltages depending on cell temperature
 */
#define WARRANTY_DATA_CELL_VOLTAGE_TEMP_HISTOGRAM_ENABLED CONFIG_ENABLED

/**
 * @brief defines for histogram for cell voltages depending on cell temperature
 */
#define WARRANTY_DATA_CELL_VOLTAGE_EXCEEDED_HISTOGRAM_ENABLED CONFIG_ENABLED

/**
 * @brief defines for histogram for the battery current depending on cell temperature
 * only applicable for the software knowing the current of the whole battery and
 * the corresponding state
 */
#define WARRANTY_DATA_BATTERY_CURRENT_HISTOGRAM_ENABLED CONFIG_ENABLED

#define WARRANTY_DATA_PEAK_CURRENT_HISTOGRAM_ENABLED              CONFIG_DISABLED
#define WARRANTY_DATA_RELAY_HISTOGRAM_ENABLED                     CONFIG_ENABLED
#define WARRANTY_DATA_CURRENT_SAFETY_VIOLATIONS_HISTOGRAM_ENABLED CONFIG_DISABLED
#define WARRANTY_DATA_PROJECT_SPECIFIC_HISTOGRAMS                 CONFIG_ENABLED


/**
 * as soon as relays are closed system needs to be either in state Charge or Discharge
 */
#define warrantyData_getDischargeState() ((stateFct_getSuperBmsState() == SuperState_Discharge) ? true : false)
#define warrantyData_getChargeState()    ((stateFct_getSuperBmsState() == SuperState_DC_Charge || stateFct_getSuperBmsState() == SuperState_Charge) ? true : false)

#if WARRANTY_DATA_CELL_VOLTAGE_EXCEEDED_HISTOGRAM_ENABLED == CONFIG_ENABLED
/**
 * @brief histogram position (boundary) between charge and discharge limits
 */
#define CELL_VOLTAGE_EXCEEDED_HISTOGRAM_BOUNDARY  2
#define CELL_VOLTAGE_EXCEEDED_HISTOGRAM_MIN_VALUE CELL_VOLTAGE_MIN_VALUE_WARRANTY
#define CELL_VOLTAGE_EXCEEDED_HISTOGRAM_MAX_VALUE CELL_VOLTAGE_MAX_VALUE_WARRANTY
#endif

#if !defined(WARRANTY_DATA_COUNTER_HISTOGRAM_CELL_VOLTAGE_EXCEEDED_LENGTH)
#define WARRANTY_DATA_COUNTER_HISTOGRAM_CELL_VOLTAGE_EXCEEDED_LENGTH 20
#endif
#if !defined(WARRANTY_DATA_COUNTER_HISTOGRAM_CELL_VOLTAGE_TEMP_LENGTH)
#define WARRANTY_DATA_COUNTER_HISTOGRAM_CELL_VOLTAGE_TEMP_LENGTH 110
#endif
#if !defined(WARRANTY_DATA_COUNTER_HISTOGRAM_BATTERY_CURRENT_LENGTH)
#define WARRANTY_DATA_COUNTER_HISTOGRAM_BATTERY_CURRENT_LENGTH 162
#endif


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
