

/**
 * @file protocolSelection.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "protocolSelection.h"
#include "canopen_config.h"
#include "canOpenStm_types.h"
#include "protocolInterface.h"
#include "canProtocol.h"
#include "canProtocol_config.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


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
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

void protocolSelection_authentificationCompleteHook(Protocol newProtocol)
{
    switch(newProtocol)
    {
        case Protocol_AUTOMATIC:
            break;
        case Protocol_KION:
            canOpenConfigLinde.stateMachineHandle->iface.canOpenState.transition        = canOpen_transition_stopNode;
            canOpenConfigLindeCharger.stateMachineHandle->iface.canOpenState.transition = canOpen_transition_stopNode;
            canProtocol_switch(CAN_PROTOCOL_KION);
            canProtocol_init();
            break;
        case Protocol_LINDE:
            canOpenConfigKion.stateMachineHandle->iface.canOpenState.transition = canOpen_transition_stopNode;
            if(protocolInterface_getConnectedDevice() == TRUCK)
            {
                canOpenConfigLindeCharger.stateMachineHandle->iface.canOpenState.transition = canOpen_transition_stopNode;
            }
            else
            {
                canOpenConfigLinde.stateMachineHandle->iface.canOpenState.transition = canOpen_transition_stopNode;
            }
            canProtocol_switch(CAN_PROTOCOL_LINDE);
            canProtocol_init();
            break;
        default:
            break;
    }
}
