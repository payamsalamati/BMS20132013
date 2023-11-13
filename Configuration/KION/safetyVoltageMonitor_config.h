/**
 * @file     safetyVoltageMonitor_config_KION.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Second protection for voltage monitoring
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

//***************************************************************************//
//************************** DEFINES ****************************************//
//***************************************************************************//

//CELL DATA
#define SAFETYVOLTAGEMONITOR_CELL_VOLTAGE_MAX 4250
/**second protection. Time needs to be higher than in appl. config**/
#define SAFETYVOLTAGEMONITOR_CELL_VOLTAGE_MAX_DETECT_TIME 4000  //in ms
#define SAFETYVOLTAGEMONITOR_CELL_VOLTAGE_MIN             1950
/**second protection. Time needs to be higher than in appl. config**/
#define SAFETYVOLTAGEMONITOR_CELL_VOLTAGE_MIN_DETECT_TIME 4000  //in ms
