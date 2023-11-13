/**
 * @file afeComProcedure_config.h
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

#define AFECOMPROCEDURE_MAX_NR_OF_AFEINIT_FAILURES 3u
#define AFECOMPROCEDURE_MAX_TRY_AFE_REINIT         3U

/**
 * @def AFE_SET_GPIO_CONFIG
 * @brief config to enable the method, which sets GPIO states
 */
#define AFE_SET_GPIO_CONFIG CONFIG_ENABLED

/**
 * @def AFE_SET_CSC_NVM_CONFIG
 * @brief config to enable the method, which set and read the csc nvm
 */
#define AFE_SET_CSC_NVM_CONFIG CONFIG_ENABLED

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
