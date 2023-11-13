/**
 *
 * @file  icdaCAN.c
 * @created on Wed Feb 19 10:47:50 CET 2020
 * @brief This module contains interrupts to process the CAN messages
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

//******************* INCLUDES ********************************//
#include "icdaCAN.h"
#include "osIf.h"
#include "semaphores.h"

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//

//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
/**
 * @brief Writes message received via CAN into Queue when called by an interrupt.
 * @details
 * @par Global variables
 */
void icdaCAN_receiveInterrupt(CANMessageObject msgObj)
{
    CANMessage message;
    int8_t err           = OSIF_ERR_QUEUE_FULL;
    CAN_STATUS statusCAN = CAN_SUCCESS;
    statusCAN            = canIf_receive(msgObj, &message);
    if(statusCAN == CAN_SUCCESS)
    {
        BaseType_t higherPriorityTaskWoken;
        err = osIf_queueSendFromISR(canMessageQueue, (void*)&message, OSIF_POST_OPT_BACK, &higherPriorityTaskWoken);
        if(err == OSIF_ERR_QUEUE_FULL)
        {
            dem_reportFaultFromISR(DTC_CAN_QUEUE_FULL);
        }
        osIf_yieldFromIsr(higherPriorityTaskWoken);
    }
}

/**
 * @brief Set semaphore after a CAN TX interrupt.
 * @details
 * @par
 */
void icdaCAN_transmitISRHandler(CANMessageObject msgObj)
{
    canIf_setTxBusStatusReady(CAN_NODE_0);
}

/**
 * @brief Will be called in case of an error on the CAN connection
 * @details
 * @par Global variables
 */
void icdaCAN_alertInterrupt(CAN_STATUS status)
{
    if((status == CAN_ACK_ERROR) || (status == CAN_BUS_OFF_ERROR) || (status == CAN_STUFF_ERROR) || (status == CAN_TX_REINITIALIZED))
    {
        canIf_setTxBusStatusReady(CAN_NODE_0);
    }
}
