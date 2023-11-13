/**
 * @file     measurements_config_KION.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Configuration for measurements module
 * @details
 *	 Interfaces to other modules:

 */

#pragma once

//***************************************************************************/
//************************ INCLUDES *****************************************/
//***************************************************************************/

#include "config_enable.h"

//***************************************************************************/
//*************************** DEFINES ***************************************/
//***************************************************************************/

/**@def MEASUREMENTS_USE_AUXILIARY_RELAYS
 * @brief For Relays with auxilary contacts
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_USE_AUXILIARY_RELAYS CONFIG_ENABLED

/**@def MEASUREMENTS_USE_HV_INTERLOCK
 * @brief For HV Interlock state
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_USE_HV_INTERLOCK CONFIG_DISABLED

/**@def MEASUREMENTS_USE_TERMINALS
 * @brief For Terminal input state (kl.15, kl.x, hv enable, charge enable)
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_USE_TERMINALS CONFIG_DISABLED

/**@def MEASUREMENTS_USE_AFE_VALUES
 * @brief For AFE values
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_USE_AFE_VALUES CONFIG_ENABLED

/**@def MEASUREMENTS_USE_HIGH_VOLTAGES
 * @brief For high voltage measurements
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_USE_HIGH_VOLTAGES CONFIG_ENABLED

/**@def MEASUREMENTS_USE_BATTERY_CURRENT
 * @brief For battery current measurements
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_USE_BATTERY_CURRENT CONFIG_ENABLED

/**@def MEASUREMENTS_USE_STRINGS_CLOSED
 * @brief For string closed states
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_USE_STRINGS_CLOSED CONFIG_DISABLED

/**@def MEASUREMENTS_USE_ON_BOARD_TEMPERATURE
 * @brief For onboard temperature measurement
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_USE_ON_BOARD_TEMPERATURE CONFIG_ENABLED

/**@def MEASUREMENTS_USE_PROXIMITY_PILOT
 * @brief For proximity pilot state
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_USE_PROXIMITY_PILOT CONFIG_DISABLED

/**@def MEASUREMENTS_USE_SUPPLY_VOLTAGES
 * @brief For supply voltage measurements
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_USE_SUPPLY_VOLTAGES CONFIG_ENABLED

/**@def MEASUREMENTS_USE_MOSFET_DIAG
 * @brief For mosfet diag voltage measurements
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_USE_MOSFET_DIAG CONFIG_DISABLED

#define MEASUREMENTS_GETAFEVALUES_CONFIG_HEADER "measurements_getAfeValues_config_KION.h"

#define MEASUREMENTS_GETBATTERYCURRENT_CONFIG_HEADER "measurements_getBatteryCurrent_config_KION.h"

#define MEASUREMENTS_GETONBOARDTEMPERATURE_CONFIG_HEADER "measurements_getOnBoardTemperature_config_KION.h"

#define MEASUREMENTS_GETSTRINGSCLOSED_CONFIG_HEADER "measurements_getStringsClosed_config_KION.h"

/**@def MEASUREMENTS_GET_HIGH_VOLTAGES_VALID_MAX
 * @brief borders for a valid High Voltage Measurement in V
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 0.0011
 * @calculation: ({{CELL_MAX_VOLTAGE_SHUT_DOWN = 4250}} *  {{CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL = 13U}} *  {{CELL_MODULE_CONFIG_STRING_NO_OF_MODULES_SERIAL = 2U}} *  {{HV_VOLTAGE_VALID_MAX = 0.0011}})
 * @unit: V
 */
#define MEASUREMENTS_MASTER_VOLTAGE_VALID_MAX 121.55

/**@def HMEASUREMENTS_GET_HIGH_VOLTAGES_VALID_COUNTER_LIMIT
 * @brief
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_MASTER_VOLTAGE_VALID_COUNTER_LIMIT 5

/**@def MEASUREMENTS_GET_HIGH_VOLTAGES_VALID_MIN
 * @brief borders for a valid High Voltage Measurement in V

 * @details
 * the voltage is also valid for 0 (open contactors) or for smaller voltages (precharge process
 * (Fix value)
 * @unit: V
 */
#define MEASUREMENTS_MASTER_VOLTAGE_VALID_MIN 0
