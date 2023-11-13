/**
 * @file lindeProtocol.h
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

void lindeProtocol_setCloseContactorsChargeMode(bool newSetting);
void lindeProtocol_setCloseContactorsDriveMode(bool newSetting);
void lindeProtocol_setOpenContactors(bool newSetting);

bool lindeProtocol_getCloseContactorsChargeMode(void);
bool lindeProtocol_getCloseContactorsDriveMode(void);
bool lindeProtocol_getOpenContactors(void);
