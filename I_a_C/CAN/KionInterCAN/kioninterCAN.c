/**
 *
 * @file  kioninterCAN.c
 * @created on Wed Feb 19 10:47:50 CET 2020
 * @brief This module contains interrupts to process the CAN messages
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

//******************* INCLUDES ********************************//
#include "kioninterCAN.h"
#include "kioninterCAN_config.h"
#include "kioninterCAN_followUpReceive.h"
#include "osIf.h"
#include "semaphores.h"
#include "icdaSensor_requestMessages.h"

#if defined(SYNC_AFE_AND_ICDA_MEASUREMENTS)
#include "synchronizedMeasurements.h"
#endif

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//

extern uint16_t missingAckErrorCntInternal;

//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
/**
 * @brief Writes message received via CAN into Queue when called by an interrupt.
 * @details
 * @par Global variables
 */
void kioninterCAN_receiveInterrupt(CANMessageObject msgObj)
{
    CANMessage message;
    int8_t err           = OSIF_ERR_QUEUE_FULL;
    CAN_STATUS statusCAN = CAN_SUCCESS;
    statusCAN            = canIf_receive(msgObj, &message);
    if(statusCAN == CAN_SUCCESS)
    {
        BaseType_t higherPriorityTaskWoken = false;
        if(message.id == 0x501u)
        {
            err = icdaSensor_requestSendIntoQueueFromISR(&message, &higherPriorityTaskWoken);
        }
#if defined(SYNC_AFE_AND_ICDA_MEASUREMENTS)
        else if(message.id == 0x502u)
        {
            err = synchronizedMeasurements_receivedIcdaResultHandler(&message, &higherPriorityTaskWoken);
        }
#endif
        else
        {
            err = osIf_queueSendFromISR(canMessageQueue, (void*)&message, OSIF_POST_OPT_BACK, &higherPriorityTaskWoken);
        }

        if(err == OSIF_ERR_QUEUE_FULL)
        {
            dem_reportFaultFromISR(DTC_CAN_QUEUE_FULL);
        }
        missingAckErrorCntInternal = 0;
        osIf_yieldFromIsr(higherPriorityTaskWoken);
    }
}

/**
 * @brief Set semaphore after a CAN TX interrupt.
 * @details
 * @par
 */
void kioninterCAN_transmitISRHandler(CANMessageObject msgObj)
{
    canIf_setTxBusStatusReady(KIONINTERCAN_NODE);
}

/**
 * @brief Will be called in case of an error on the CAN connection
 * @details
 * @par Global variables
 */
void kioninterCAN_alertInterrupt(CAN_STATUS status)
{
    if((status == CAN_ACK_ERROR) || (status == CAN_BUS_OFF_ERROR) || (status == CAN_STUFF_ERROR) || (status == CAN_TX_REINITIALIZED))
    {
        canIf_setTxBusStatusReady(KIONINTERCAN_NODE);
    }

    if(status == CAN_ACK_ERROR)
    {
        missingAckErrorCntInternal++;
    }
}

uint16_t kioninterCAN_getMissingAckErrorCounter(void)
{
    return missingAckErrorCntInternal;
}
