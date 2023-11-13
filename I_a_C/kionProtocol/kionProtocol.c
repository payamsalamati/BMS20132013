/**
 * @file kionProtocol.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "kionProtocol.h"
#include "protocolSettings.h"
#include "task_cfg.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    uint8_t nominalVoltageConfig;
} KionProtocolConfig;

#define KION_PROTOCOL_DEFAULT_NOMINAL_VOLTAGE 80u

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SEC_PARAMETER KionProtocolConfig kionProtocolConfigParameter = {
    .nominalVoltageConfig = KION_PROTOCOL_DEFAULT_NOMINAL_VOLTAGE,
};

MEM_SHAREDATA static ProtocolSettings kionProtocolSettings = {
    .closeContactorsCharge = false,
    .closeContactorsDrive  = false,
    .openContactors        = false
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void kionProtocol_setCloseContactorsChargeMode(bool newSetting)
{
    kionProtocolSettings.closeContactorsCharge = newSetting;
    if(newSetting == true)
    {
        kionProtocolSettings.closeContactorsDrive = !newSetting;
        kionProtocolSettings.openContactors       = !newSetting;
    }
}

void kionProtocol_setCloseContactorsDriveMode(bool newSetting)
{
    kionProtocolSettings.closeContactorsDrive = newSetting;
    if(newSetting == true)
    {
        kionProtocolSettings.openContactors        = !newSetting;
        kionProtocolSettings.closeContactorsCharge = !newSetting;
    }
}

void kionProtocol_setOpenContactors(bool newSetting)
{
    kionProtocolSettings.openContactors = newSetting;
    if(newSetting == true)
    {
        kionProtocolSettings.closeContactorsCharge = !newSetting;
        kionProtocolSettings.closeContactorsDrive  = !newSetting;
    }
}

bool kionProtocol_getCloseContactorsChargeMode(void)
{
    return kionProtocolSettings.closeContactorsCharge;
}

bool kionProtocol_getCloseContactorsDriveMode(void)
{
    return kionProtocolSettings.closeContactorsDrive;
}

bool kionProtocol_getOpenContactors(void)
{
    return kionProtocolSettings.openContactors;
}

void kionProtocol_setNominalVoltageConfig(uint8_t newValue)
{
    kionProtocolConfigParameter.nominalVoltageConfig = newValue;
}

uint8_t kionProtocol_getNominalVoltageConfig(void)
{
    return kionProtocolConfigParameter.nominalVoltageConfig;
}
