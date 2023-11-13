/**
 * @file     sdo_config_KION.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief SDO config
 * @details
 */

// *************************************************************************************************** /
// ************************* Includes **************************************************************** /
// *************************************************************************************************** /


#include "canId_config.h"
#include "sdo_config.h"
#include "kionCAN.h"
#include "lindeCAN.h"

void sdo_sendMessage(const CANMessage* message)
{
    switch(message->id)
    {
        case 0x5A7:
            kionCAN_sendLib_sdo_tx(message);
            break;
        case 0x58d:
            lindeCAN_sendLiIoBMS_SDOresp_Traction(message);
            break;
        case 0x5dd:
            lindeCAN_sendLiIoBMS_SDOresp_LiIoCharger(message);
            break;
        default:
            break;
    }
}
