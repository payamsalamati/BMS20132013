/**
 * @file processUDSMessage.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "processUDSMessage.h"

#include "cps.h"
#include "uds.h"
#include "uds_config.h"
#include "isotp_config.h"

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
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void processUDSMessage_customerCAN(const CANMessage* msg)
{
    if(msg->data[0] == ISOTP_BROADCAST_REMOTE_ADDRESS)
    {
        cps_tunnelCpsVehicleUdsRequest(msg);
        uds_forwardMsgToIsotp(msg);
    }
    else if(msg->data[0] == CPS_VEHICLE_EXTENDED_ADDRESS_RX)
    {
        cps_tunnelCpsVehicleUdsRequest(msg);
    }
    else if(msg->data[0] == UDS_CAN_DEFAULT_EXT_ADDRESS_RX)
    {  // Master is referenced
        uds_forwardMsgToIsotp(msg);
    }
    else
    {
        /*do nothing*/
    }
}

void processUDSMessage_internalCAN(const CANMessage* msg)
{
    /* do nothing */
}
