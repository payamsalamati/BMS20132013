

/**
 * @file highVoltageMonitor_config.h
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

/**@def HV_VOLTAGE_DIFFERENCE_MAX
 * @brief Maximum allowed difference between battery voltage measurement and hv voltage measurements. used also to detect blown fuse
 * @details
 *
 * (Fix value)
 * @unit: V
 */
#define HV_VOLTAGE_DEFAULT_DIFFERENCE_MAX_ERR_DETECT_VAL 5

/**@def HV_VOLTAGE_DIFFERENCE_MAX_ERR_RELEASE_VAL
 * @brief release value for HV Voltage Difference Max Error
 * @details
 *
 * (Fix value)
 * @unit: V
 */
#define HV_VOLTAGE_DEFAULT_DIFFERENCE_MAX_ERR_RELEASE_VAL 5
