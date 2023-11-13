

/**
 * @file cellTemperatureMeasurement_config.h
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

/**@def CELL_TEMPERATURE_MEASUREMENT_VALID_COUNTER
 * @brief counter for invalid cell voltage to become valid, for timing see cycling time limitCheckTask
 * @details
 *
 * (Fix value)
 * @unit: uint8_t
 */
#define TEMPERATURE_MEASUREMENT_VALID_COUNTER 5

/**@def CELL_TEMPERATURE_MEASUREMENT_VALID_MAX
 * @brief borders for a valid temperature in °C
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 1.1
 * @calculation: ({{CELL_MAX_TEMPERATURE_SHUT_DOWN = 60}} *  {{TEMPERATURE_VALID_MAX = 1.1}})
 * @unit: °C
 */
#define TEMPERATURE_MEASUREMENT_VALID_MAX 90

/**@def CELL_TEMPERATURE_MEASUREMENT_VALID_MIN
 * @brief borders for a valid temperature in °C
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 1.1
 * @calculation: ({{CELL_MIN_TEMPERATURE_SHUT_DOWN = -30}} *  {{TEMPERATURE_VALID_MIN = 1.1}})
 * @unit: °C
 */
#define TEMPERATURE_MEASUREMENT_VALID_MIN -33

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
