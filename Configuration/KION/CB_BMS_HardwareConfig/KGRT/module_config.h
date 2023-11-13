/**
 * @file bms_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */

#pragma once

#include "bms.h"
#include "config_enable.h"

#if !defined(UNIT_TEST)
#include "icdaDefault_config.h"
#endif


// *************************************************************************************************** /
// ************************* Module Configuration **************************************************** /
// *************************************************************************************************** /

/**@def BMS_CONFIG_NUMBER_OF_SLAVES
 * @brief number of slaves
 * @details
 *
 * @unit: uint8_t
 */
#define BMS_CONFIG_MIN_NUMBER_OF_SLAVES 2u

#if(defined(HIL_CONFIGURATION) || defined(SIL_DEBUG))
// Define needed for SM04 - contactor resistance measurement.
#define BMS_CONFIG_NUMBER_OF_CSC_WITH_OWN_SIMBA 2u
#if defined(SIL_DEBUG)
#define BMS_CONFIG_DEFAULT_NUMBER_OF_SLAVES 30u
#else
#define BMS_CONFIG_DEFAULT_NUMBER_OF_SLAVES 8u
#endif
#elif defined(EMV_TEST)
// Define needed for SM04 - contactor resistance measurement.
#define BMS_CONFIG_NUMBER_OF_CSC_WITH_OWN_SIMBA 2u
#define BMS_CONFIG_DEFAULT_NUMBER_OF_SLAVES     2u

#else
#define BMS_CONFIG_DEFAULT_NUMBER_OF_SLAVES 2u
#endif


/**@def NUMBER_OF_TEMPERATURE_SENSORS
 * @brief number of connected temperature sensors per slave
 * @details
 *
 * @unit: uint8_t
 */
#define BMS_CONFIG_MAX_NUMBER_OF_TEMPERATURE_SENSORS     3U
#define BMS_CONFIG_DEFAULT_NUMBER_OF_TEMPERATURE_SENSORS 3U
#define BMS_CONFIG_NUMBER_OF_TEMPERATURE_SENSORS         bmsConfigParameter.numberOfTempSensors

/**@def BMS_CONFIG_NUMBER_OF_BALANCING_TEMPERATURE_SENSORS
 * @brief number of connected balancing temperature sensors per slave
 * @details
 *
 * @unit: uint8_t
 */
#define BMS_CONFIG_MAX_NUMBER_OF_BALANCING_TEMPERATURE_SENSORS     0U
#define BMS_CONFIG_DEFAULT_NUMBER_OF_BALANCING_TEMPERATURE_SENSORS 0U
#define BMS_CONFIG_NUMBER_OF_BALANCING_TEMPERATURE_SENSORS         bmsConfigParameter.numberOfBalTempSensors

/**@def BMS_CONFIG_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS
 * @brief number of connected additional non safety temperature sensors per slave
 * @details
 *
 * @unit: uint8_t
 */
#define BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS     2U
#define BMS_CONFIG_DEFAULT_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS 2U
#define BMS_CONFIG_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS         bmsConfigParameter.numberOfAppTempSensors

#if(defined(EMV_TEST) || defined(HIL_CONFIGURATION))
#define BMS_CONFIG_DYNAMIC_NUMBER_OF_CSC_ENABLE CONFIG_DISABLED
#else
#define BMS_CONFIG_DYNAMIC_NUMBER_OF_CSC_ENABLE CONFIG_DISABLED
#endif
//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
