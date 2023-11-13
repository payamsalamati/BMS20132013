/**
 * @file masterCurrentMeasurement_config.h
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

/**@def MASTER_CURRENT_MEASUREMENT_WATCHDOG_MAX_VALUE
 * @brief External Current Measurment watchdog
 * @details
 * External Current Measurment watchdog maximal value
 * (Fix value)
 */
#define MASTER_CURRENT_MEASUREMENT_WATCHDOG_MAX_VALUE 300


/**@def MASTER_CURRENT_MEASUREMENT_VALID_MAX
 * @brief borders for a valid Current Measurement Discharge in mA
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 1.5
 * @calculation: ({{Module Capacity in Ah = 62.722}} *  {{CELL_MAX_C_RATE_DISCHARGE_SHUT_DOWN = 3.2}} * 1000 *  {{CURRENT_VALID_MAX = 1.5}})
 * @unit: mA
 */
#define MASTER_CURRENT_MEASUREMENT_VALID_MAX 47041.5

/**@def CURRENT_VALID_MAX_COUNTER
 * @brief
 * @details
 *
 * (Fix value)
 */
#define MASTER_CURRENT_MEASUREMENT_VALID_COUNTER_LIMIT 5

/**@def MASTER_CURRENT_MEASUREMENT_VALID_MIN
 * @brief borders for a valid Current Measurement Charge in mA
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @setValue: 1.5
 * @calculation: ((-1) * {{Module Capacity in Ah = 62.722}} *  {{CELL_MAX_C_RATE_CHARGE_SHUT_DOWN = 3.2}} * 1000 *  {{CURRENT_VALID_MIN = 1.5}})
 * @unit: mA
 */
#define MASTER_CURRENT_MEASUREMENT_VALID_MIN -28224.9


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
