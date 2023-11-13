/**
 * @file     highVoltageMeasurement_config.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Configuration for measurements submodule getSupplyVoltage
 * @details
 *	 Interfaces to other modules:

 */

#pragma once


#include "config_enable.h"

//***************************************************************************/
//************************ Schnittstellen ***********************************/
//***************************************************************************/


//***************************************************************************/
//**************************   Defines   ************************************/
//***************************************************************************/

/**@def MEASUREMENTS_TRY_NUMBER
 * @brief number of tries for a measurement (AFE)
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_TRY_NUMBER 5

/**@def MEASUREMENTS_GET_HIGH_VOLTAGES_VALID_MAX
 * @brief borders for a valid High Voltage Measurement in V
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 0.0011
 * @calculation: ({{CELL_MAX_VOLTAGE_SHUT_DOWN = 4250}} *  {{CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL = 13U}} *  {{CELL_MODULE_CONFIG_STRING_NO_OF_MODULES_SERIAL = 2U}} *  {{HV_VOLTAGE_VALID_MAX = 0.0011}})
 * @unit: V
 */
#define MEASUREMENTS_GET_HIGH_VOLTAGES_VALID_MAX 121.55

/**@def HMEASUREMENTS_GET_HIGH_VOLTAGES_VALID_COUNTER_LIMIT
 * @brief
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_GET_HIGH_VOLTAGES_VALID_COUNTER_LIMIT 5

/**@def MEASUREMENTS_GET_HIGH_VOLTAGES_VALID_MIN
 * @brief borders for a valid High Voltage Measurement in V

 * @details
 * the voltage is also valid for 0 (open contactors) or for smaller voltages (precharge process
 * (Fix value)
 * @unit: V
 */
#define MEASUREMENTS_GET_HIGH_VOLTAGES_VALID_MIN 0

/**@def MEASUREMENTS_GET_HIGH_VOLTAGES_IN_V
 * @brief enables High Voltage Measurement in V, if disabled High Voltage Measurement in mV
 */
#define MEASUREMENTS_GET_HIGH_VOLTAGES_IN_V CONFIG_DISABLED

#if MEASUREMENTS_GET_HIGH_VOLTAGES_IN_V == CONFIG_ENABLED
#define MEASUREMENTS_GET_HIGH_VOLTAGES_FAKTOR 1000
#else
#define MEASUREMENTS_GET_HIGH_VOLTAGES_FAKTOR 1
#endif
