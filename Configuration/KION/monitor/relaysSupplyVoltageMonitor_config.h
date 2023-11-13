/**
 * @file relaysSupplyVoltageMonitor_config.h
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

/**@def RELAY_SUPPLY_VOLTAGE_MAX
 * @brief Maximum allowed voltage of relay supply in mV
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define RELAY_SUPPLY_VOLTAGE_DEFAULT_MAX_WARN_DETECT_VAL 15000  //@req CB-88945

/**@def RELAY_SUPPLY_VOLTAGE_MIN
 * @brief Minimum allowed relay supply voltage in mV
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define RELAY_SUPPLY_VOLTAGE_DEFAULT_MIN_WARN_DETECT_VAL 5000  //@req CB-77302

/**@def RELAY_SUPPLY_VOLTAGE_MIN_WARN_DETECT_TIME
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define RELAY_SUPPLY_VOLTAGE_DEFAULT_MIN_WARN_DETECT_TIME 0u

/**@def RELAY_SUPPLY_VOLTAGE_MAX_WARN_DETECT_TIME
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: ms
 */
#define RELAY_SUPPLY_VOLTAGE_DEFAULT_MAX_WARN_DETECT_TIME 0u

/**@def RELAY_SUPPLY_VOLTAGE_MIN_WARN_RELEASE_TIME
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: ms
 */
#define RELAY_SUPPLY_VOLTAGE_DEFAULT_MIN_WARN_RELEASE_TIME 0u

/**@def RELAY_SUPPLY_VOLTAGE_MAX_WARN_RELEASE_TIME
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: ms
 */
#define RELAY_SUPPLY_VOLTAGE_DEFAULT_MAX_WARN_RELEASE_TIME 0u

/**@def RELAY_SUPPLY_VOLTAGE_MIN_WARN_RELEASE_VAL
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: ms
 */
#define RELAY_SUPPLY_VOLTAGE_DEFAULT_MIN_WARN_RELEASE_VAL 11000  //@req CB-77302

/**@def RELAY_SUPPLY_VOLTAGE_MAX_WARN_RELEASE_VAL
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define RELAY_SUPPLY_VOLTAGE_DEFAULT_MAX_WARN_RELEASE_VAL 15000  //@req CB-88945

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
