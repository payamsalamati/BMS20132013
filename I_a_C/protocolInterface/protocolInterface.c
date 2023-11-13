/**
 * @file protocolInterface.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "protocolInterface.h"
#include "protocolSettings.h"
#include "task_cfg.h"
#include "protocolSelection.h"
#include "kionProtocol.h"
#include "lindeProtocol.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    ConnectedDevice connectedDevice;
} ProtocolInterfaceConfig;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SHAREDATA static ProtocolInterfaceConfig ProtocolInterfaceConfigParameter = {
    // cppcheck-suppress misra-c2012-13.4 ; cppcheck issue
    .connectedDevice = ERROR,
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void protocolInterface_setConnectedDevice(ConnectedDevice newSetting)
{
    ProtocolInterfaceConfigParameter.connectedDevice = newSetting;
}

ConnectedDevice protocolInterface_getConnectedDevice(void)
{
    return ProtocolInterfaceConfigParameter.connectedDevice;
}

void protocolInterface_setCloseContactorsChargeMode(bool newSetting)
{
    if(newSetting == true)
    {
        ProtocolInterfaceConfigParameter.connectedDevice = CHARGER;
    }
    switch(protocolSelection_getBrand())
    {
        case Protocol_KION:
            kionProtocol_setCloseContactorsChargeMode(newSetting);
            break;
        case Protocol_LINDE:
            lindeProtocol_setCloseContactorsChargeMode(newSetting);
            break;
        default:
            break;
    }
}

void protocolInterface_setCloseContactorsDriveMode(bool newSetting)
{
    if(newSetting == true)
    {
        ProtocolInterfaceConfigParameter.connectedDevice = TRUCK;
    }
    switch(protocolSelection_getBrand())
    {
        case Protocol_KION:
            kionProtocol_setCloseContactorsDriveMode(newSetting);
            break;
        case Protocol_LINDE:
            lindeProtocol_setCloseContactorsDriveMode(newSetting);
            break;
        default:
            break;
    }
}

void protocolInterface_setOpenContactors(bool newSetting)
{
    switch(protocolSelection_getBrand())
    {
        case Protocol_KION:
            kionProtocol_setOpenContactors(newSetting);
            break;
        case Protocol_LINDE:
            lindeProtocol_setOpenContactors(newSetting);
            break;
        default:
            break;
    }
}

bool protocolInterface_getCloseContactorsChargeMode(void)
{
    switch(protocolSelection_getBrand())
    {
        case Protocol_KION:
            return kionProtocol_getCloseContactorsChargeMode();
        case Protocol_LINDE:
            return lindeProtocol_getCloseContactorsChargeMode();
        default:
            return false;
    }
}

bool protocolInterface_getCloseContactorsDriveMode(void)
{
    switch(protocolSelection_getBrand())
    {
        case Protocol_KION:
            return kionProtocol_getCloseContactorsDriveMode();
        case Protocol_LINDE:
            return lindeProtocol_getCloseContactorsDriveMode();
        default:
            return false;
    }
}

bool protocolInterface_getOpenContactors(void)
{
    switch(protocolSelection_getBrand())
    {
        case Protocol_KION:
            return kionProtocol_getOpenContactors();
        case Protocol_LINDE:
            return lindeProtocol_getOpenContactors();
        default:
            return false;
    }
}

void protocolInterface_setNominalVoltageConfig(uint8_t newValue)
{
    kionProtocol_setNominalVoltageConfig(newValue);
}

uint8_t protocolInterface_getNominalVoltageConfig(void)
{
    return kionProtocol_getNominalVoltageConfig();
}
