/**
 * @file     safetyVoltageMonitor_config_default.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Second protection for temperature monitoring
 * @details
 *   Interfaces to other modules:
 *   - safetyMeasurement
 *   - safetyDataIf
 *
 */


#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

//#include "safetyDataIf.h"
//
//
//#define safetyAfeValueMeasurement_getTemperaturesValue(i, j)            safetyDataIf_getTemperaturesValue(i, j)

//***************************************************************************//
//************************** DEFINES ****************************************//
//***************************************************************************//

//CELL DATA
#define SAFETYTEMPERATUREMONITOR_CELL_TEMP_MIN -39
/**second protection. Time needs to be higher than in appl. config**/
#define SAFETYTEMPERATUREMONITOR_CELL_TEMP_MIN_DETECT_TIME 4000  //in ms
#define SAFETYTEMPERATUREMONITOR_CELL_TEMP_MAX             70
/**second protection. Time needs to be higher than in appl. config**/
#define SAFETYTEMPERATUREMONITOR_CELL_TEMP_MAX_DETECT_TIME 4000  //in ms
