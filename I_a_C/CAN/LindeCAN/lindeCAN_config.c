/**
 *
 * @file lindeCAN_config.c
 * @modulenumber 0x0D
 * @author Generated File with DPCParser release-1.3.4 Commit 1347995
 * @created on Mon Jan 16 10:46:58 CET 2023
 * @brief  This file contains all the CAN message objects definitions for CAN NODE 1
 * @copyright  Futavis GmbH, Aachen 2023 - alle Rechte vorbehalten
 * @details Generated from file "linde.sym"
 * @par Global variables
 * - slaveID (R)
 * @par changes
 * - first creation  Mon Jan 16 10:46:58 CET 2023
 */

//**************************INCLUDES ******************************//
#include "lindeCAN.h"
//#include "dataInterface.h"
#include "can_config.h"

#include "osIf.h"
#include "protocolSelection.h"

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//
//const CANGlobalConfig canGlobalConfig =
//{
//	.canFrequency = LINDECAN_NODE_FREQUENCY
//};

MEM_CAN CANMessageObject lindeCANTransmitLiIoBMS_SDOresp_TractionHandler;
MEM_CAN CANMessageObject lindeCANTransmitLiIoBMS_SDOresp_LiIoChargerHandler;
MEM_CAN CANMessageObject lindeCANTransmitLiIoBMS_PDO5Handler;
MEM_CAN CANMessageObject lindeCANTransmitLiIoBMS_PDO4Handler;
MEM_CAN CANMessageObject lindeCANTransmitLiIoBMS_PDO3Handler;
MEM_CAN CANMessageObject lindeCANTransmitLiIoBMS_PDO2Handler;
MEM_CAN CANMessageObject lindeCANTransmitLiIoBMS_PDO1Handler;
MEM_CAN CANMessageObject lindeCANTransmitLiIoBMS_HeartbeatHandler;

MEM_CAN CANMessageObject lindeCANReceiveTraction_SDOreq_LiIoBMSHandler;
MEM_CAN CANMessageObject lindeCANReceiveLiIoCharger_SDOreq_LiIoBMSHandler;
MEM_CAN CANMessageObject lindeCANReceiveLiIoCharger_PDO1Handler;
MEM_CAN CANMessageObject lindeCANReceiveTraction_PDO4Handler;
MEM_CAN CANMessageObject lindeCANReceiveTimeStampHandler;
MEM_CAN CANMessageObject lindeCANReceiveHeartbeatHandler;
MEM_CAN CANMessageObject lindeCANReceiveSYNCHandler;
MEM_CAN CANMessageObject lindeCANReceiveModuleControlHandler;

//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//

void lindeCAN_configBeforeProtocolSelection()
{
    const CANMessageObjectConfig receiveSYNC = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = LINDE_CAN_ID_SYNC,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE
    };
    lindeCANReceiveSYNCHandler = canIf_configMessageObject(&receiveSYNC);

    const CANMessageObjectConfig receiveTractionSdoReq = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = LINDE_CAN_ID_TRACTION_SDOREQ_LIIOBMS,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE
    };
    lindeCANReceiveTraction_SDOreq_LiIoBMSHandler = canIf_configMessageObject(&receiveTractionSdoReq);

    const CANMessageObjectConfig receiveChargerSdoReq = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = LINDE_CAN_ID_LIIOCHARGER_SDOREQ_LIIOBMS,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE
    };
    lindeCANReceiveLiIoCharger_SDOreq_LiIoBMSHandler = canIf_configMessageObject(&receiveChargerSdoReq);

    const CANMessageObjectConfig receiveHeartbeat = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = LINDE_CAN_ID_LIIOBMS_HEARTBEAT,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE
    };
    lindeCANReceiveHeartbeatHandler = canIf_configMessageObject(&receiveHeartbeat);

    const CANMessageObjectConfig receiveModuleControl = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = LINDE_CAN_ID_MODULE_CONTROL,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE
    };
    lindeCANReceiveModuleControlHandler = canIf_configMessageObject(&receiveModuleControl);
}

void lindeCAN_configCharger()
{
    const CANMessageObjectConfig receiveChargerPDO1 = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = LINDE_CAN_ID_LIIOCHARGER_PDO1,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE
    };
    lindeCANReceiveLiIoCharger_PDO1Handler = canIf_configMessageObject(&receiveChargerPDO1);
}

void lindeCAN_configTruck()
{
    const CANMessageObjectConfig receiveTractionPDO4 = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = LINDE_CAN_ID_TRACTION_PDO4,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE
    };
    lindeCANReceiveTraction_PDO4Handler = canIf_configMessageObject(&receiveTractionPDO4);
}

void lindeCAN_config()
{
    const CANMessageObjectConfig receiveTimestamp = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = LINDE_CAN_ID_TIMESTAMP,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE
    };
    lindeCANReceiveTimeStampHandler = canIf_configMessageObject(&receiveTimestamp);
}


void lindeCAN_configSendBeforeProtocolSelection()
{

    //************************** Message Config LIIOBMS_SDORESP_TRACTION*****************************************//
    CANMessageObjectConfig transmitLiIoBMS_SDOresp_TractionConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x58d,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    lindeCANTransmitLiIoBMS_SDOresp_TractionHandler = canIf_configMessageObject(&transmitLiIoBMS_SDOresp_TractionConfig);

    //************************** Message Config LIIOBMS_SDORESP_LIIOCHARGER*****************************************//
    CANMessageObjectConfig transmitLiIoBMS_SDOresp_LiIoChargerConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x5dd,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    lindeCANTransmitLiIoBMS_SDOresp_LiIoChargerHandler = canIf_configMessageObject(&transmitLiIoBMS_SDOresp_LiIoChargerConfig);

    //************************** Message Config LIIOBMS_HEARTBEAT*****************************************//
    CANMessageObjectConfig transmitLiIoBMS_HeartbeatConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x70d,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE,
        .dlc       = MESSAGE_DLC_1
    };

    lindeCANTransmitLiIoBMS_HeartbeatHandler = canIf_configMessageObject(&transmitLiIoBMS_HeartbeatConfig);
}

/**
 * @brief config function for sending CAN message
 */
void lindeCAN_configSend()
{
    //************************** Message Config LIIOBMS_PDO5*****************************************//
    CANMessageObjectConfig transmitLiIoBMS_PDO5Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x301,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    lindeCANTransmitLiIoBMS_PDO5Handler = canIf_configMessageObject(&transmitLiIoBMS_PDO5Config);


    //************************** Message Config LIIOBMS_PDO4*****************************************//
    CANMessageObjectConfig transmitLiIoBMS_PDO4Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x48d,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    lindeCANTransmitLiIoBMS_PDO4Handler = canIf_configMessageObject(&transmitLiIoBMS_PDO4Config);


    //************************** Message Config LIIOBMS_PDO3*****************************************//
    CANMessageObjectConfig transmitLiIoBMS_PDO3Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x38d,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    lindeCANTransmitLiIoBMS_PDO3Handler = canIf_configMessageObject(&transmitLiIoBMS_PDO3Config);


    //************************** Message Config LIIOBMS_PDO2*****************************************//
    CANMessageObjectConfig transmitLiIoBMS_PDO2Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x28d,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    lindeCANTransmitLiIoBMS_PDO2Handler = canIf_configMessageObject(&transmitLiIoBMS_PDO2Config);


    //************************** Message Config LIIOBMS_PDO1*****************************************//
    CANMessageObjectConfig transmitLiIoBMS_PDO1Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x18d,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = LINDECAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    lindeCANTransmitLiIoBMS_PDO1Handler = canIf_configMessageObject(&transmitLiIoBMS_PDO1Config);
}

void lindeCAN_init(void)
{
    lindeCAN_config();
    lindeCAN_configSend();
}
