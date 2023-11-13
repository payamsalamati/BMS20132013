/**
 * @file lindeProtocol.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "lindeProtocol.h"
#include "protocolSettings.h"
#include "task_cfg.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


MEM_SHAREDATA ProtocolSettings lindeProtocolSettings = {
    .closeContactorsCharge = false,
    .closeContactorsDrive  = false,
    .openContactors        = false
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//


void lindeProtocol_setCloseContactorsChargeMode(bool newSetting)
{
    lindeProtocolSettings.closeContactorsCharge = newSetting;
    if(newSetting == true)
    {
        lindeProtocolSettings.closeContactorsDrive = !newSetting;
        lindeProtocolSettings.openContactors       = !newSetting;
    }
}

void lindeProtocol_setCloseContactorsDriveMode(bool newSetting)
{
    lindeProtocolSettings.closeContactorsDrive = newSetting;
    if(newSetting == true)
    {
        lindeProtocolSettings.openContactors        = !newSetting;
        lindeProtocolSettings.closeContactorsCharge = !newSetting;
    }
}

void lindeProtocol_setOpenContactors(bool newSetting)
{
    lindeProtocolSettings.openContactors = newSetting;
    if(newSetting == true)
    {
        lindeProtocolSettings.closeContactorsCharge = !newSetting;
        lindeProtocolSettings.closeContactorsDrive  = !newSetting;
    }
}

bool lindeProtocol_getCloseContactorsChargeMode(void)
{
    return lindeProtocolSettings.closeContactorsCharge;
}

bool lindeProtocol_getCloseContactorsDriveMode(void)
{
    return lindeProtocolSettings.closeContactorsDrive;
}

bool lindeProtocol_getOpenContactors(void)
{
    return lindeProtocolSettings.openContactors;
}
