/**
 * @file limitCheckTask_config.h
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

#include "config_enable.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

/**@def LIMIT_CHECK_CAN_WDT
 * @brief watchdog for CAN
 * @details
 *
 * (Fix value)
 */
#define LIMIT_CHECK_CAN_WDT CONFIG_DISABLED

/**@def LIMIT_CHECK_COUNT_STRING_ERRORS
 * @brief strings can be in error
 * @details
 * when enabled it is possible that strings are in error while the whole battery is still functioning
 * (Fix value)
 */
#define LIMIT_CHECK_COUNT_STRING_ERRORS CONFIG_DISABLED

/**@def LIMIT_CHECK_INTERLOCK
 * @brief enable interlock error
 * @details
 * when enabled an interlock open will result into an error
 * (Fix value)
 */
#define LIMIT_CHECK_INTERLOCK CONFIG_DISABLED

/**@def LIMIT_CHECK_MAX_RUNTIME
 * @brief enabled the BMS goes into an error after a defined ontime
 * @details
 *
 * (Fix value)
 */
#define LIMIT_CHECK_MAX_RUNTIME CONFIG_DISABLED

/**@def LIMIT_CHECK_OFFSET_CALIBRATION
 * @brief Checks if the offset of the current sensors is too high
 * @details
 *
 * (Fix value)
 */
#define LIMIT_CHECK_OFFSET_CALIBRATION CONFIG_DISABLED

/**@def LIMIT_CHECK_AUX_ERROR
 * @brief checks the auxiliary of the relays with the state set in the software.
 * @details
 * In case they do not match an error is set
 * (Fix value)
 */
#define LIMIT_CHECK_AUX_ERROR CONFIG_ENABLED

/**@def LIMIT_CHECK_HV_VOLTAGES
 * @brief enable hv voltage check
 * @details
 *
 * (Fix value)
 */
#define LIMIT_CHECK_HV_VOLTAGES CONFIG_ENABLED

/**@def LIMIT_CHECK_CANOPEN_WATCHDOG
 * @brief enable CANopen watchdog
 * @details
 *
 * (Fix value)
 */
#define LIMIT_CHECK_CANOPEN_WATCHDOG CONFIG_DISABLED

/**@def LIMIT_CHECK_RELAY_SUPPLY
 * @brief enable relayssupply monitor
 * @details
 *
 * (Fix value)
 */
#define LIMIT_CHECK_RELAY_SUPPLY CONFIG_ENABLED

/**@def LIMIT_CHECK_DIAGNOSTIC_TIME_MEASUREMENT
 * @brief enable diagnostic time measurement
 * @details
 *
 * (Fix value)
 */
#define LIMIT_CHECK_DIAGNOSTIC_TIME_MEASUREMENT CONFIG_ENABLED

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
