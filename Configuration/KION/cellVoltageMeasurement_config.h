

/**
 * @file cellVoltageMeasurement_config.h
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

/**@def CELL_VOLTAGE_MEASUREMENT_VALID_MAX
 * @brief borders for a valid cell voltage in mV
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 1.1
 * @calculation: ({{CELL_MAX_VOLTAGE_SHUT_DOWN = 4250}} *  {{CELL_VOLTAGE_VALID_MAX = 1.1}})
 * @unit: mV
 */
#define CELL_VOLTAGE_MEASUREMENT_VALID_MAX 4675u

/**@def CELL_VOLTAGE_MEASUREMENT_VALID_MIN
 * @brief borders for a valid cell voltage in mV
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 0.9
 * @calculation: ({{CELL_MIN_VOLTAGE_SHUT_DOWN = 2500}} *  {{CELL_VOLTAGE_VALID_MIN = 0.9}})
 * @unit: mV
 */
#define CELL_VOLTAGE_MEASUREMENT_VALID_MIN 2250u

/**@def CELL_VOLTAGE_MEASUREMENT_VALID_COUNTER_LIMIT
 * @brief counter for invalid cell voltage to become valid,  for timing see cycling time limitCheckTask
 * @details
 *
 * (Fix value)
 * @unit: uint8_t
 */
#define CELL_VOLTAGE_MEASUREMENT_VALID_COUNTER_LIMIT 5u


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
