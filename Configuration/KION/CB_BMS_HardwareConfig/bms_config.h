/**
 * @file bms_config.h
 * @copyright (c) Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
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
#include "bms.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//
extern BmsConfig bmsConfigParameter;

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

// *************************************************************************************************** /
// ************************* Battery Hardware Configuration ****************************************** /
// *************************************************************************************************** /
/**@def NUMBER_OF_CURRENT_SENSORS
 * @brief number of connected current sensors
 * @details
 *
 * @unit: uint8_t
 */
#define BMS_CONFIG_MAX_NUMBER_OF_CURRENT_SENSORS     2U
#define BMS_CONFIG_DEFAULT_NUMBER_OF_CURRENT_SENSORS 2U
#define BMS_CONFIG_NUMBER_OF_CURRENT_SENSORS         bmsConfigParameter.numberOfCurrentSensors

/**@def NUMBER_OF_HV_MEASUREMENTS
 * @brief number of high voltage measurements
 * @details
 *
 * @unit: uint8_t
 */
#define BMS_CONFIG_MAX_NUMBER_OF_HV_MEASUREMENTS     3U
#define BMS_CONFIG_DEFAULT_NUMBER_OF_HV_MEASUREMENTS 3U
#define BMS_CONFIG_NUMBER_OF_HV_MEASUREMENTS         bmsConfigParameter.numberOfHvMeasurements

/**@def NUMBER_OF_RELAIS
 * @brief number of relais
 * @details
 *
 * @unit: uint8_t
 */
#define BMS_CONFIG_DEFAULT_NUMBER_OF_RELAIS 3U
#define BMS_CONFIG_NUMBER_OF_RELAIS         bmsConfigParameter.numberOfRelais

/**@def BAT_CONFIG_SERPAR
 * @brief config for the positioning of the masters
 * @details
 * serial and parallel positioning information
 * (Fix value)
 */
#define BAT_CONFIG_SERPAR \
    {                     \
        0                 \
    }

/**@def BMS_CONFIG_ICDA_SENSORS
 * @brief ICDA sensors are used in this project
 * @details
 * Activates the watchdogs and receive functions
 * (Fix value)
 */
#define BMS_CONFIG_ICDA_SENSORS CONFIG_ENABLED

/**@def BMS_CONFIG_MAINTANCE_MONITOR
 * @brief enable config if maintance Monitor is used
 * @details
 */
#define BMS_CONFIG_MAINTANCE_MONITOR CONFIG_DISABLED
