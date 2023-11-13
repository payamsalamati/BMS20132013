/**
 * @file multi_master_config.h
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
// ************************* Multi String Configuration ********************************************** /
// *************************************************************************************************** /


#define BMS_CONFIG_DEFAULT_NUMBER_OF_MASTER 1u
#define BMS_CONFIG_NUMBER_OF_MASTER         bmsConfigParameter.numberOfMaster

#define BMS_CONFIG_MAX_MULTISTRING_NO_OF_STRINGS_SERIAL     1U
#define BMS_CONFIG_DEFAULT_MULTISTRING_NO_OF_STRINGS_SERIAL 1U
#define BMS_CONFIG_MULTISTRING_NO_OF_STRINGS_SERIAL         bmsConfigParameter.multistrinNoOfStringsSerial

#define BMS_CONFIG_MAX_MULTISTRING_NO_OF_STRING_PARALLEL     1U
#define BMS_CONFIG_DEFAULT_MULTISTRING_NO_OF_STRING_PARALLEL 1U
#define BMS_CONFIG_MULTISTRING_NO_OF_STRING_PARALLEL         bmsConfigParameter.multistrinNoOfStringsParallel
