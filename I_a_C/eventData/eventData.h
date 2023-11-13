/**
 * @file eventData.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void eventData_mainFunction(void);
void eventData_checkNvm(const uint8_t* mirror, uint16_t length);
void eventData_copyNvmForWrite(uint8_t* mirror, uint16_t length);
void eventData_resetEventData(void);

int32_t eventData_getHighestPositiveCurrentDriveModeMaster(void);
int32_t eventData_getHighestNegativeCurrentDriveModeMaster(void);
int32_t eventData_getHighestPositiveCurrentChargeModeMaster(void);
uint16_t eventData_getHighestBatteryVoltageMaster(void);
uint16_t eventData_getLowestBatteryVoltageMaster(void);
uint16_t eventData_getHighestCellVoltageMaster(void);
uint16_t eventData_getLowestCellVoltageMaster(void);
int8_t eventData_getHighestFuSiTemperatureMaster(void);
int8_t eventData_getLowestFuSiTemperatureMaster(void);
uint16_t eventData_getHighestImbalanceCellVoltageMaster(void);
