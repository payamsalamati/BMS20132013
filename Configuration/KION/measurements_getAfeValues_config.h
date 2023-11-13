/**
 * @file     measurements_getAfeValues_config_KION.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Configuration for measurements submodule getBatteryCurrent
 * @details
 *	 Interfaces to other modules:

 */

#pragma once


//***************************************************************************/
//**************************** DEFINES **************************************/
//***************************************************************************/


/**@def MEASUREMENTS_GET_AFE_VALUES_TEMPERATURES_VALID_MAX_COUNTER
 * @brief counter for invalid cell voltage to become valid, for timing see cycling time limitCheckTask
 * @details
 *
 * (Fix value)
 * @unit: uint8_t
 */
#define MEASUREMENTS_GET_AFE_VALUES_TEMPERATURES_VALID_MAX_COUNTER 5

/**@def MEASUREMENTS_GET_AFE_VALUES_TEMPERATURE_VALID_MAX
 * @brief borders for a valid temperature in °C
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 1.1
 * @calculation: ({{CELL_MAX_TEMPERATURE_SHUT_DOWN = 60}} *  {{TEMPERATURE_VALID_MAX = 1.1}})
 * @unit: °C
 */
#define MEASUREMENTS_GET_AFE_VALUES_TEMPERATURE_VALID_MAX 90

/**@def MEASUREMENTS_GET_AFE_VALUES_TEMPERATURE_VALID_MIN
 * @brief borders for a valid temperature in °C
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 1.1
 * @calculation: ({{CELL_MIN_TEMPERATURE_SHUT_DOWN = -30}} *  {{TEMPERATURE_VALID_MIN = 1.1}})
 * @unit: °C
 */
#define MEASUREMENTS_GET_AFE_VALUES_TEMPERATURE_VALID_MIN -33
