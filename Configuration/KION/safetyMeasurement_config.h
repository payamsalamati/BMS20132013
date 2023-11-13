/**
 * @file     safetyMeasurement_config_default.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Cellvoltage, temperature and current measurement
 * @details
 *   Interfaces to other modules:
 *   - afeIf
 *   - adcIf
 *   - isensorIf
 *   - safetyDataIf
 *   - safetyRelayInterface
 *
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//


//***************************************************************************//
//************************** DEFINES ****************************************//
//***************************************************************************//

#define SAFETYMEASUREMENT_NUMBER_OF_CURRENT_MEASUREMENTS 3

#define SAFETYMEASUREMENT_NUMBER_OF_TRYS_TO_GET_AFEVALUES 2

#define SAFETY_MAX_NUMBER_OF_CURRENT_SENSORS 6
