

/**
 * @file moduleVoltageMeasurement_config.h
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


/**@def MODULE_VOLTAGE_MEASUREMENT_VALID_MAX
 * @brief borders for a valid Module voltage in mV
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 1.1
 * @calculation: ({{CELL_MAX_VOLTAGE_SHUT_DOWN = 4250}} *  {{CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL = 13U}} *  {{MODULE_VOLTAGE_VALID_MAX = 1.1}})
 * @unit: mV
 */
#define MODULE_VOLTAGE_MEASUREMENT_VALID_MAX 30100

/**@def MODULE_VOLTAGE_MEASUREMENT_VALID_COUNTER_LIMIT
 * @brief
 * @details
 *
 * (Fix value)
 */
#define MODULE_VOLTAGE_MEASUREMENT_VALID_COUNTER_LIMIT 5

/**@def MODULE_VOLTAGE_MEASUREMENT_VALID_MIN
 * @brief borders for a valid Module voltage in mV
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 0.9
 * @calculation: ({{CELL_MIN_VOLTAGE_SHUT_DOWN = 2500}} *  {{CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL = 13U}} *  {{MODULE_VOLTAGE_VALID_MIN = 0.9}})
 * @unit: mV
 */
#define MODULE_VOLTAGE_MEASUREMENT_VALID_MIN 14700

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
