/**
 * @file     canIf_config_default.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 */

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "canIf.h"
#include "osIf.h"
#include "canSendTask.h"

#include "TMS570/can_TMS570LS.h"

#include "canWakeupIf.h"
#include "TJA1145/can_TJA1145.h"
#include "debug.h"
#include "task_cfg.h"
//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/

#define CAN_USED_DEVICE (uint8_t) CAN_DEVICE_TMS570LS

//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/


const CANType* const canTypes[] = {
    &can_TMS570LS,
};
const uint8_t CAN_TYPES_LENGTH = sizeof(canTypes) / sizeof(CANType*);


//***************************************************************************/
//************************** PRIVATE FUNCTION DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DEFINITIONS *******************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DEFINITIONS ********************/
//***************************************************************************/

CAN_STATUS canIf_send(CANMessageObject msgObj, uint8_t dlc, const uint8_t* data)
{
    return canTypes[CAN_USED_DEVICE]->send(msgObj, dlc, data);
}

CAN_STATUS canIf_receive(CANMessageObject msgObj, CANMessage* can_msg)
{
    return canTypes[CAN_USED_DEVICE]->receive(msgObj, can_msg);
}

CAN_STATUS canIf_configNode(const CANNodeConfig* const config)
{
    return canTypes[CAN_USED_DEVICE]->configNode(config);
}

CANMessageObject canIf_configMessageObject(const CANMessageObjectConfig* config)
{
    return canTypes[CAN_USED_DEVICE]->configMessageObject(config);
}

CAN_STATUS canIf_setFilter(CANMessageObject msgObj, uint16_t can_id, uint16_t mask)
{
    return canTypes[CAN_USED_DEVICE]->setMessageFilter(msgObj, can_id, mask);
}

CAN_STATUS canIf_disableNode(CANNode node)
{
    return canTypes[CAN_USED_DEVICE]->disableNode(node);
}

CAN_STATUS canIf_busOffDetection(CANNode node)
{
    return canTypes[CAN_USED_DEVICE]->getBusOffDetection(node);
}

CAN_STATUS canIf_getLastErrorCode(CANNode node)
{
    return canTypes[CAN_USED_DEVICE]->getLastErrorCode(node);
}

CAN_STATUS canIf_init(void)
{
    CAN_STATUS result = CAN_FAILURE;

    for(uint8_t i = 0; i < CAN_TYPES_LENGTH; i++)
    {
        result = canTypes[i]->init();
        if(result == CAN_FAILURE)
        {
            break;
        }
    }

    if(result == CAN_SUCCESS)
    {
        result = canWakeUpIf_init();
    }

    return result;
}

void canIf_waitForTxBusReadyStatus(uint8_t nodeNr)
{
    canTypes[CAN_USED_DEVICE]->waitForTXBusReady(nodeNr);
}

void canIf_setTxBusStatusReady(uint8_t nodeNr)
{
    canTypes[CAN_USED_DEVICE]->setTxBusStatusReady(nodeNr);
}

void canIf_swReset(CANNode node)
{
    canTypes[CAN_USED_DEVICE]->swReset(node);
}
