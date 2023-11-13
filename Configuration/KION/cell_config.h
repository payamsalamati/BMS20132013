/**
 * @file cell_config.h
 * @copyright Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
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

/**@def CELL_MIN_VOLTAGE_OPERATION
 * @brief voltage operating minimum in mV, SOC 0%
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define CELL_CONFIG_CELL_MIN_VOLTAGE_OPERATION 3600u

/**@def CELL_NOMINAL_VOLTAGE
 * @brief nominal cell voltage in mV
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define CELL_CONFIG_CELL_NOMINAL_VOLTAGE 3640u

/**@def CELL_NOMINAL_CAPACITY
 * @brief Nominal cell capacity in mAs
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @calculation: ({{Cell capacity = 4800}} * 3600)
 * @unit: mAs
 */
#define CELL_CONFIG_CELL_NOMINAL_CAPACITY 17280000
