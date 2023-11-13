/**
 * @file master_config.h
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


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//


/**@def MAX_NUMBER_OF_CURRENT_SENSORS
 * @brief max number of connected current sensors
 * @details
 *
 * @unit: uint8_t
 */
#define MASTER_CONFIG_MAX_NUMBER_OF_CURRENT_SENSORS 2U

/**@def MAX_NUMBER_OF_HV_MEASUREMENTS
 * @brief max number of high voltage measurements
 * @details
 *
 * @unit: uint8_t
 */
#define MASTER_CONFIG_MAX_NUMBER_OF_HV_MEASUREMENTS 3U

/**@def MAX_NUMBER_OF_RELAIS
 * @brief max number of relais
 * @details
 *
 * @unit: uint8_t
 */
#define MASTER_CONFIG_MAX_NUMBER_OF_RELAIS 3U
