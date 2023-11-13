/**
 * @file     safetyBalancing_config_default.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Enable/disable cell balancing
 * @details
 *   Interfaces to other modules:
 *   - safetyMeasurements
 *   - idAllocation_Slave ( CAN_Slave only )
 */


#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

//#include "safetyDataIf.h"

//***************************************************************************//
//************************** DEFINES ****************************************//
//***************************************************************************//

//#define safetyAfeValueMeasurement_getBalancingTemperaturesValue(i,j)            safetyDataIf_getBalancingTemperaturesValue(i,j)


#define SAFETY_BALANCING_TEMP_MAX 60

#define SAFETY_BALANCING_TEMP_MIN 0
