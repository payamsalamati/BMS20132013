/**
 * @file cell_module_config.h
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

#include "cell_module.h"
#include "module_config.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

extern CellModuleConfig cellModuleConfigParameter;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

/**@def CELL_MAX_VOLTAGE_CHARGE_BOL
 * @brief voltage maximum for charge beginning of life in mV
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define CELL_MODULE_CONFIG_CELL_MAX_VOLTAGE_CHARGE_BOL 4100

/**@def CELL_MAX_VOLTAGE_CHARGE_EOL
 * @brief voltage maximum for charge end of life in mV
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define CELL_MODULE_CONFIG_CELL_MAX_VOLTAGE_CHARGE_EOL 4100

/**@def CELL_MIN_VOLTAGE_OPERATION
 * @brief voltage operating minimum in mV, SOC 0%
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define CELL_MODULE_CONFIG_CELL_MIN_VOLTAGE_OPERATION 3600

/**@def CELL_NOMINAL_CAPACITY
 * @brief Nominal cell capacity in mAs
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @calculation: ({{Cell capacity = 2851}} * 3600)
 * @unit: mAs
 */
#define CELL_MODULE_CONFIG_DEFAULT_CELL_NOMINAL_CAPACITY 4800
#define CELL_MODULE_CONFIG_CELL_NOMINAL_CAPACITY         cellModuleConfigParameter.nominalCellCapacity

/**@def MODULE_NOMINAL_ENERGY
 * @brief Nominal battery module energy in mWh
 * @details
 *
 * How this value was calculated. References to other defines are surrounded by '{{' and '}}' with the resulting value in it.
 * @calculation: ({{MODUL_NOMINAL_CAPACITY = 225799200}} *  {{MODUL_NOMINAL_VOLTAGE = 47450}} / 1000 / 3600)
 * @unit: mWh
 */
#define CELL_MODULE_CONFIG_MODULE_NOMINAL_ENERGY 3500000u

/**@def MODULE_NO_OF_CELLS_PARALLEL
 * @brief number of cells of one module in parallel
 * @details
 *
 * (Fix value)
 * @unit: uint8_t
 */
#define CELL_MODULE_CONFIG_MAX_MODULE_NO_OF_CELLS_PARALLEL     28u
#define CELL_MODULE_CONFIG_MIN_MODULE_NO_OF_CELLS_PARALLEL     1u
#define CELL_MODULE_CONFIG_DEFAULT_MODULE_NO_OF_CELLS_PARALLEL 1u
#define CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_PARALLEL         cellModuleConfigParameter.numberOfParallelCells

/**@def CELL_NOMINAL_VOLTAGE
 * @brief nominal cell voltage in mV
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define CELL_MODULE_CONFIG_MAX_CELL_NOMINAL_VOLTAGE     5000u
#define CELL_MODULE_CONFIG_MIN_CELL_NOMINAL_VOLTAGE     0u
#define CELL_MODULE_CONFIG_DEFAULT_CELL_NOMINAL_VOLTAGE 3640u
#define CELL_MODULE_CONFIG_CELL_NOMINAL_VOLTAGE         cellModuleConfigParameter.nominalCellVoltage

/**@def CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL
 * @brief number of cells of one module in serial
 * @details
 *
 * (Fix value)
 * @unit: uint8_t
 */
#define CELL_MODULE_CONFIG_MAX_MODULE_NO_OF_CELLS_SERIAL     14u
#define CELL_MODULE_CONFIG_MIN_MODULE_NO_OF_CELLS_SERIAL     7u
#define CELL_MODULE_CONFIG_DEFAULT_MODULE_NO_OF_CELLS_SERIAL 14u


/**@def STRING_NO_OF_MODULES_SERIAL
 * @brief number of modules of one string in serial
 * @details
 *
 * (Fix value)
 * @unit: uint8_t
 */
#if !defined(EMV_TEST)
#define CELL_MODULE_CONFIG_MAX_STRING_NO_OF_MODULES_SERIAL     2U
#define CELL_MODULE_CONFIG_MIN_STRING_NO_OF_MODULES_SERIAL     1U
#define CELL_MODULE_CONFIG_DEFAULT_STRING_NO_OF_MODULES_SERIAL 2U
#else
#define CELL_MODULE_CONFIG_MAX_STRING_NO_OF_MODULES_SERIAL     3U
#define CELL_MODULE_CONFIG_MIN_STRING_NO_OF_MODULES_SERIAL     1U
#define CELL_MODULE_CONFIG_DEFAULT_STRING_NO_OF_MODULES_SERIAL 3U
#endif

/**@def STRING_NO_OF_MODULES_PARALLEL
 * @brief number of modules of one string in parallel
 * @details
 *
 * (Fix value)
 * @unit: uint8_t
 */
#define CELL_MODULE_CONFIG_MAX_STRING_NO_OF_MODULES_PARALLEL 15U
#define CELL_MODULE_CONFIG_MIN_STRING_NO_OF_MODULES_PARALLEL 1U

#if defined(SIL_DEBUG)
#define CELL_MODULE_CONFIG_DEFAULT_STRING_NO_OF_MODULES_PARALLEL 15U
#elif defined(HIL_CONFIGURATION)
#define CELL_MODULE_CONFIG_DEFAULT_STRING_NO_OF_MODULES_PARALLEL 4U
#elif defined(EMV_TEST)
#define CELL_MODULE_CONFIG_DEFAULT_STRING_NO_OF_MODULES_PARALLEL 1U
#else
#define CELL_MODULE_CONFIG_DEFAULT_STRING_NO_OF_MODULES_PARALLEL (BMS_CONFIG_DEFAULT_NUMBER_OF_SLAVES / CELL_MODULE_CONFIG_DEFAULT_STRING_NO_OF_MODULES_SERIAL)
#endif
#if CELL_MODULE_CONFIG_DEFAULT_STRING_NO_OF_MODULES_PARALLEL > CELL_MODULE_CONFIG_MAX_STRING_NO_OF_MODULES_PARALLEL
#error "CELL_MODULE_CONFIG_DEFAULT_STRING_NO_OF_MODULES_PARALLEL is too high"
#endif
