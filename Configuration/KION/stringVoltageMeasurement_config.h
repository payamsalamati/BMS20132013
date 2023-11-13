/**
 * @file stringVoltageMeasurement_config.h
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

/**@def MEASUREMENTS_STRING_VOLTAGE_VALID_MAX
 * @brief borders for a valid High Voltage Measurement in V
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 0.0011
 * @calculation: ({{CELL_MAX_VOLTAGE_SHUT_DOWN = 4250}} *  {{MODULE_NO_OF_CELLS_SERIAL = 13U}} *  {{STRING_NO_OF_MODULES_SERIAL = 2U}} *  {{HV_VOLTAGE_VALID_MAX = 0.0011}})
 * @unit: V
 */
#define MEASUREMENTS_STRING_VOLTAGE_VALID_MAX 121.55

/**@def MEASUREMENTS_STRING_VOLTAGE_VALID_COUNTER_LIMIT
 * @brief
 * @details
 *
 * (Fix value)
 */
#define MEASUREMENTS_STRING_VOLTAGE_VALID_COUNTER_LIMIT 5

/**@def MEASUREMENTS_STRING_VOLTAGE_VALID_MIN
 * @brief borders for a valid High Voltage Measurement in V

 * @details
 * the voltage is also valid for 0 (open contactors) or for smaller voltages (precharge process
 * (Fix value)
 * @unit: V
 */
#define MEASUREMENTS_STRING_VOLTAGE_VALID_MIN 0
