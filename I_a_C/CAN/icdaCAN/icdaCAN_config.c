/**
 *
 * @file icdaCAN_config.c
 * @created on Mon Nov 16 10:15:18 CET 2020
 * @brief  This file contains all the CAN message objects definitions for CAN NODE 2
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - slaveID (R)
 */

//**************************INCLUDES ******************************//
#include "icdaCAN.h"
#include "canIf.h"
#include "can_config.h"

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//
//const CANGlobalConfig canGlobalConfig =
//{
//	.canFrequency = ICDACAN_NODE_FREQUENCY
//};

MEM_CAN CANNodeConfig icdaCANConfig = {
    .canFrequency             = CAN_NODE0_FREQUENCY,
    .baudrate                 = 500,
    .samplePoint              = CAN_NODE0_SAMPLE_POINT,
    .synchronizationJumpWidth = CAN_NODE0_SYNCHRONIZATION_JUMP_WIDTH,
    .receiveISRHandler        = (CANInterruptHandler)icdaCAN_receiveInterrupt,
    .transmitISRHandler       = (CANInterruptHandler)icdaCAN_transmitISRHandler,
    .alertISRHandler          = (CANInterruptErrorHandler)icdaCAN_alertInterrupt,
    .node                     = ICDACAN_NODE
};


MEM_CAN CANMessageObject icdaCANTransmitBMS_ICDA_RequestHandler;

MEM_CAN CANMessageObject icdaCANReceiveICDA_BMS_ResultHandler;
MEM_CAN CANMessageObject icdaCANReceiveICDA_BMS_ResponseHandler;


//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
void icdaCAN_config(void)
{
    //************************** Message Config ICDA_BMS_RESULT*****************************************//
    static const CANMessageObjectConfig receiveICDA_BMS_ResultConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x502,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = ICDACAN_NODE
    };

    icdaCANReceiveICDA_BMS_ResultHandler = canIf_configMessageObject(&receiveICDA_BMS_ResultConfig);


    //************************** Message Config ICDA_BMS_RESPONSE*****************************************//
    static const CANMessageObjectConfig receiveICDA_BMS_ResponseConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x501,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = ICDACAN_NODE
    };

    icdaCANReceiveICDA_BMS_ResponseHandler = canIf_configMessageObject(&receiveICDA_BMS_ResponseConfig);

    canIf_configNode(&icdaCANConfig);
}

void icdaCAN_reset(void)
{
    canIf_swReset(ICDACAN_NODE);
    icdaCAN_config();
    icdaCAN_configSend();
}

/**
 * @brief config function for sending CAN message
 */
void icdaCAN_configSend(void)
{
    //************************** Message Config BMS_ICDA_REQUEST*****************************************//
    static const CANMessageObjectConfig transmitBMS_ICDA_RequestConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x500,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = ICDACAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    icdaCANTransmitBMS_ICDA_RequestHandler = canIf_configMessageObject(&transmitBMS_ICDA_RequestConfig);
}
