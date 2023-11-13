/**
 *
 * @file  baseCAN.c
 * @brief
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

//******************* INCLUDES ********************************//

#include "baseCAN.h"
#include "osIf.h"
#include "udsTask.h"
#include "canReceiveTask.h"
#include "canIf.h"
#include "semaphores.h"
#include "mutexMonitor.h"

#include "kionCAN.h"
#include "lindeCAN.h"

extern uint16_t missingAckErrorCntExternal;

//************************** PUBLIC FUNCTION DEFINITIONS ******************************//

void baseCAN_receiveInterrupt(CANMessageObject msgObj)
{
    CANMessage message;
    int8_t err           = OSIF_ERR_QUEUE_FULL;
    CAN_STATUS statusCAN = CAN_SUCCESS;
    statusCAN            = canIf_receive(msgObj, &message);
    if(statusCAN == CAN_SUCCESS)
    {
        BaseType_t higherPriorityTaskWoken;
        if(message.id == 0x680u)
        {
            err = udsTask_sendIntoQueueFromISR(&message, &higherPriorityTaskWoken);
        }
        else
        {
            err = osIf_queueSendFromISR(canMessageQueue, (void*)&message, OSIF_POST_OPT_BACK, &higherPriorityTaskWoken);
        }

        if(err == OSIF_ERR_QUEUE_FULL)
        {
            dem_reportFaultFromISR(DTC_CAN_QUEUE_FULL);
        }
        missingAckErrorCntExternal = 0u;
        osIf_yieldFromIsr(higherPriorityTaskWoken);
    }
}

void baseCAN_transmitISRHandler(CANMessageObject msgObj)
{
    canIf_setTxBusStatusReady(CAN_NODE_1);
}

void baseCAN_alertInterrupt(CAN_STATUS status)
{
    if((status == CAN_ACK_ERROR) || (status == CAN_BUS_OFF_ERROR) || (status == CAN_STUFF_ERROR) || (status == CAN_TX_REINITIALIZED))
    {
        canIf_setTxBusStatusReady(CAN_NODE_1);
    }

    if(status == CAN_ACK_ERROR)
    {
        missingAckErrorCntExternal++;
    }
}


void baseCAN_send10ms()
{
    kionCANSendDebug10();
}

void baseCAN_send20ms()
{
}

void baseCAN_send40ms()
{
    kionCANSendHeartbeat();
    lindeCANSend40();
}

void baseCAN_send100ms()
{
}

void baseCAN_send1000ms()
{
}

void baseCAN_receive(const CANMessage* msg)
{
    kionCAN_receive(msg);
    lindeCAN_receive(msg);
}
