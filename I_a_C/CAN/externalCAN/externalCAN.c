/**
 *
 * @file  externalCAN.c
 * @brief This module configures the message boxes for external CAN communication
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

//******************* INCLUDES ********************************//

#include "externalCAN.h"
#include "kionCAN.h"
#include "lindeCAN.h"
#include "protocolSelection.h"
#include "semaphores.h"
#include "canIf.h"
#include "udsTask.h"
#include "mutexMonitor.h"

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//

MEM_CAN CANNodeConfig externalCanConfig = {
    .canFrequency             = CAN_NODE2_FREQUENCY,
    .baudrate                 = 500,
    .samplePoint              = CAN_NODE2_SAMPLE_POINT,
    .synchronizationJumpWidth = CAN_NODE2_SYNCHRONIZATION_JUMP_WIDTH,
    .receiveISRHandler        = (CANInterruptHandler)externalCAN_receiveInterrupt,
    .transmitISRHandler       = (CANInterruptHandler)externalCAN_transmitISRHandler,
    .alertISRHandler          = (CANInterruptErrorHandler)externalCAN_alertInterrupt,
    .node                     = EXTERNALCAN_NODE
};

MEM_CAN uint16_t missingAckErrorCntExternal = 0;
MEM_CAN uint16_t missingAckErrorCntInternal = 0;
MEM_CAN bool sendConfigInitialized          = false;
MEM_CAN bool receiveConfigInitialized       = false;

//************************** PRIVATE FUNCTION DEFINITIONS *****************************************//


//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//

void externalCAN_receiveMessage(CANMessage* msg)
{
    kionCAN_receive(msg);
    lindeCAN_receive(msg);
}

void externalCAN_setMessageBoxesBeforeProtocol(void)
{
    kionCAN_configBeforeProtocolSelection();
    lindeCAN_configBeforeProtocolSelection();
    canIf_configNode(&externalCanConfig);
}

void externalCAN_setMessageBoxesKion(void)
{
    if(receiveConfigInitialized == false)
    {
        receiveConfigInitialized = true;
        kionCAN_config();
    }
}

void externalCAN_setMessageBoxesLinde(void)
{
    if(receiveConfigInitialized == false)
    {
        receiveConfigInitialized = true;
        lindeCAN_config();
    }
}

void externalCAN_setTransmitMessageBoxesBeforeProtocol(void)
{
    kionCAN_configSendBeforeProtocolSelection();
    lindeCAN_configSendBeforeProtocolSelection();
}

void externalCAN_setTransmitMessageBoxesKion(void)
{
    if(sendConfigInitialized == false)
    {
        sendConfigInitialized = true;
        kionCAN_configSend();
    }
}

void externalCAN_setTransmitMessageBoxesLinde(void)
{
    if(sendConfigInitialized == false)
    {
        sendConfigInitialized = true;
        lindeCAN_configSend();
    }
}

void externalCAN_send_1000(void)
{
    if(sendConfigInitialized == true)
    {
        if(protocolSelection_getBrand() == Protocol_KION)
        {
            kionCANSend1000();
        }
    }
}

void externalCAN_send_100(void)
{
    if(sendConfigInitialized == true)
    {
        if(protocolSelection_getBrand() == Protocol_KION)
        {
            kionCANSend100();
        }
    }
}

void externalCAN_send_40(void)
{
    kionCANSendHeartbeat();
    lindeCANSend40();
}

void externalCAN_send_20(void)
{
    if(sendConfigInitialized == true)
    {
        if(protocolSelection_getBrand() == Protocol_KION)
        {
            kionCAN_processEmcyMsg();
        }
    }
}

void externalCAN_send_10(void)
{
    kionCANSendDebug10();
    if(sendConfigInitialized == true)
    {
        if(protocolSelection_getBrand() == Protocol_KION)
        {
            kionCANSend10();
        }
        if(protocolSelection_getBrand() == Protocol_LINDE)
        {
            lindeCANSend10();
        }
    }
}

void externalCAN_send_emcy_msg(uint8_t* emcyData)
{
    if(sendConfigInitialized == true)
    {
        if(protocolSelection_getBrand() == Protocol_KION)
        {
            kionCAN_sendLib_emergency(emcyData);
        }
    }
}

void externalCAN_receiveInterrupt(CANMessageObject msgObj)
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

void externalCAN_transmitISRHandler(CANMessageObject msgObj)
{
    canIf_setTxBusStatusReady(CAN_NODE_1);
}

void externalCAN_alertInterrupt(CAN_STATUS status)
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

void externalCAN_reset(void)
{
    sendConfigInitialized    = false;
    receiveConfigInitialized = false;
    canIf_swReset(EXTERNALCAN_NODE);
    externalCAN_setMessageBoxesBeforeProtocol();
    externalCAN_setTransmitMessageBoxesBeforeProtocol();
}

uint16_t externalCAN_getMissingAckErrorCounterExternal(void)
{
    return missingAckErrorCntExternal;
}
