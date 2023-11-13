/**
 * @file protocolInterface.h
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

typedef enum
{
    TRUCK   = 0x0,
    CHARGER = 0x1,
    ERROR   = 0xFF,
} ConnectedDevice;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void protocolInterface_setConnectedDevice(ConnectedDevice newSetting);

ConnectedDevice protocolInterface_getConnectedDevice(void);

void protocolInterface_setCloseContactorsChargeMode(bool newSetting);

void protocolInterface_setCloseContactorsDriveMode(bool newSetting);

void protocolInterface_setOpenContactors(bool newSetting);

bool protocolInterface_getCloseContactorsChargeMode(void);

bool protocolInterface_getCloseContactorsDriveMode(void);

bool protocolInterface_getOpenContactors(void);

void protocolInterface_setNominalVoltageConfig(uint8_t newValue);

uint8_t protocolInterface_getNominalVoltageConfig(void);
