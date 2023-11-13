/**
 * @file     supplyVoltageMeasurement_config.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Configuration for measurements submodule getSupplyVoltage
 * @details
 *	 Interfaces to other modules:

 */

#pragma once

//***************************************************************************/
//*************************** DEFINES ***************************************/
//***************************************************************************/

/**@def NUMBER_OF_RELAY_SUPPLY_VOLTAGE_MEASUREMENTS
 * @brief For relay supply voltage measurements
 * @details
 *
 * (Fix value)
 */
#if defined(EMV_TEST)
#define NUMBER_OF_RELAY_SUPPLY_VOLTAGE_MEASUREMENTS 3u
#else
#define NUMBER_OF_RELAY_SUPPLY_VOLTAGE_MEASUREMENTS 2u
#endif
#define MEASUREMENTS_GET_BOARD_SUPPLY_VOLTAGES_VALID_COUNTER_LIMIT 3u

#define MEASUREMENTS_GET_BOARD_SUPPLY_VOLTAGES_VALID_MIN 8000u

#define MEASUREMENTS_GET_BOARD_SUPPLY_VOLTAGES_VALID_MAX 15000u

#define MEASUREMENTS_GET_RELAY_SUPPLY_VOLTAGES_VALID_COUNTER_LIMIT 3u

#define MEASUREMENTS_GET_RELAY_SUPPLY_VOLTAGES_VALID_MIN 8000u

#define MEASUREMENTS_GET_RELAY_SUPPLY_VOLTAGES_VALID_MAX 15000u

#define MEASUREMENTS_GET_RELAY_SUPPLY_VOLTAGES_3V3 CONFIG_ENABLED
#define MEASUREMENTS_GET_RELAY_SUPPLY_VOLTAGES_5V  CONFIG_ENABLED

//***************************************************************************/
//************************ Schnittstellen ***********************************/
//***************************************************************************/
