/**
 * @file kionProtocol.h
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

#include <stdbool.h>
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

void kionProtocol_setCloseContactorsChargeMode(bool newSetting);
void kionProtocol_setCloseContactorsDriveMode(bool newSetting);
void kionProtocol_setOpenContactors(bool newSetting);

bool kionProtocol_getCloseContactorsChargeMode(void);
bool kionProtocol_getCloseContactorsDriveMode(void);
bool kionProtocol_getOpenContactors(void);

void kionProtocol_setNominalVoltageConfig(uint8_t newValue);
uint8_t kionProtocol_getNominalVoltageConfig(void);
