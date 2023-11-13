/**
 *
 * @file kioninterCAN_config.c
 * @created on Mon Nov 16 10:15:18 CET 2020
 * @brief  This file contains all the CAN message objects definitions for CAN NODE 2
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - slaveID (R)
 */

//**************************INCLUDES ******************************//
#include "kioninterCAN.h"
#include "canIf.h"
#include "can_config.h"

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//
//const CANGlobalConfig canGlobalConfig =
//{
//	.canFrequency = KIONINTERCAN_NODE_FREQUENCY
//};

MEM_CAN CANNodeConfig kioninterCanConfig = {
    .canFrequency             = CAN_NODE1_FREQUENCY,
    .baudrate                 = 500,  // @req CB-10291
    .samplePoint              = CAN_NODE1_SAMPLE_POINT,
    .synchronizationJumpWidth = CAN_NODE1_SYNCHRONIZATION_JUMP_WIDTH,
    .receiveISRHandler        = (CANInterruptHandler)kioninterCAN_receiveInterrupt,
    .transmitISRHandler       = (CANInterruptHandler)kioninterCAN_transmitISRHandler,
    .alertISRHandler          = (CANInterruptErrorHandler)kioninterCAN_alertInterrupt,
    .node                     = KIONINTERCAN_NODE
};

MEM_CAN CANMessageObject kioninterCANTransmitBMS_CPS_UDS_REQHandler;
MEM_CAN CANMessageObject kioninterCANTransmitBMS_CPS_PDO_TX3Handler;
MEM_CAN CANMessageObject kioninterCANTransmitBMS_CPS_PDO_TX2Handler;
MEM_CAN CANMessageObject kioninterCANTransmitBMS_HeartbeatHandler;
MEM_CAN CANMessageObject kioninterCANTransmitBMS_TimeStampHandler;
MEM_CAN CANMessageObject kioninterCANTransmitBMS_CPS_SDO_REQHandler;
MEM_CAN CANMessageObject kioninterCANTransmitBMS_ModuleCotrolHandler;
MEM_CAN CANMessageObject kioninterCANTransmitBMS_CPS_PDO_TX1Handler;
MEM_CAN CANMessageObject kioninterCANTransmitBMS_ICDA_RequestHandler;
MEM_CAN CANMessageObject kioninterCANReceiveCPS_BMS_UDS_RESPHandler;
MEM_CAN CANMessageObject kioninterCANReceiveCH_CPS_WakeUpHandler;
MEM_CAN CANMessageObject kioninterCANReceiveCPS_VEHICLE_UDS_RESPHandler;
MEM_CAN CANMessageObject kioninterCANReceiveCPS_BMS_EmergencyHandler;
MEM_CAN CANMessageObject kioninterCANReceiveCPS_HeartbeatHandler;
MEM_CAN CANMessageObject kioninterCANReceiveCPS_BMS_SDO_RESPHandler;
MEM_CAN CANMessageObject kioninterCANReceiveCPS_BMS_PDO_TX2Handler;
MEM_CAN CANMessageObject kioninterCANReceiveCPS_BMS_PDO_TX3Handler;
MEM_CAN CANMessageObject kioninterCANReceiveCPS_BMS_PDO_TX1Handler;
MEM_CAN CANMessageObject kioninterCANReceiveICDA_BMS_ResultHandler;
MEM_CAN CANMessageObject kioninterCANReceiveICDA_BMS_ResponseHandler;

MEM_CAN CANMessageObject kioninterCANReceiveStandardHandler;
MEM_CAN CANMessageObject kioninterCANReceiveExtendedHandler;

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
MEM_CAN CANMessageObject kioninterCANTransmitStrPM_SyM_Val1Handler;
#endif
//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
void kioninterCAN_config(void)
{
    //************************** Message Config CPS_BMS_UDS_RESP*****************************************//
    static const CANMessageObjectConfig receiveCPS_BMS_UDS_RESPConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x6e6,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANReceiveCPS_BMS_UDS_RESPHandler = canIf_configMessageObject(&receiveCPS_BMS_UDS_RESPConfig);


    //************************** Message Config CH_CPS_WAKEUP*****************************************//
    static const CANMessageObjectConfig receiveCH_CPS_WakeUpConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x1fffffff,
        .idMask    = 0xffffffff,
        .ideMask   = 0,
        .mode      = CAN_EXTENDED_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANReceiveCH_CPS_WakeUpHandler = canIf_configMessageObject(&receiveCH_CPS_WakeUpConfig);


    //************************** Message Config CPS_VEHICLE_UDS_RESP*****************************************//
    static const CANMessageObjectConfig receiveCPS_VEHICLE_UDS_RESPConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x6df,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANReceiveCPS_VEHICLE_UDS_RESPHandler = canIf_configMessageObject(&receiveCPS_VEHICLE_UDS_RESPConfig);


    //************************** Message Config CPS_BMS_EMERGENCY*****************************************//
    static const CANMessageObjectConfig receiveCPS_BMS_EmergencyConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x82,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANReceiveCPS_BMS_EmergencyHandler = canIf_configMessageObject(&receiveCPS_BMS_EmergencyConfig);


    //************************** Message Config CPS_HEARTBEAT*****************************************//
    static const CANMessageObjectConfig receiveCPS_HeartbeatConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x702,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANReceiveCPS_HeartbeatHandler = canIf_configMessageObject(&receiveCPS_HeartbeatConfig);


    //************************** Message Config CPS_BMS_SDO_RESP*****************************************//
    static const CANMessageObjectConfig receiveCPS_BMS_SDO_RESPConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x582,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANReceiveCPS_BMS_SDO_RESPHandler = canIf_configMessageObject(&receiveCPS_BMS_SDO_RESPConfig);


    //************************** Message Config CPS_BMS_PDO_TX2*****************************************//
    static const CANMessageObjectConfig receiveCPS_BMS_PDO_TX2Config = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x282,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANReceiveCPS_BMS_PDO_TX2Handler = canIf_configMessageObject(&receiveCPS_BMS_PDO_TX2Config);


    //************************** Message Config CPS_BMS_PDO_TX3*****************************************//
    static const CANMessageObjectConfig receiveCPS_BMS_PDO_TX3Config = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x382,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANReceiveCPS_BMS_PDO_TX3Handler = canIf_configMessageObject(&receiveCPS_BMS_PDO_TX3Config);


    //************************** Message Config CPS_BMS_PDO_TX1*****************************************//
    static const CANMessageObjectConfig receiveCPS_BMS_PDO_TX1Config = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x182,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANReceiveCPS_BMS_PDO_TX1Handler = canIf_configMessageObject(&receiveCPS_BMS_PDO_TX1Config);


    //************************** Message Config ICDA_BMS_RESULT*****************************************//
    static const CANMessageObjectConfig receiveICDA_BMS_ResultConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x502,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANReceiveICDA_BMS_ResultHandler = canIf_configMessageObject(&receiveICDA_BMS_ResultConfig);


    //************************** Message Config ICDA_BMS_RESPONSE*****************************************//
    static const CANMessageObjectConfig receiveICDA_BMS_ResponseConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x501,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANReceiveICDA_BMS_ResponseHandler = canIf_configMessageObject(&receiveICDA_BMS_ResponseConfig);

    canIf_configNode(&kioninterCanConfig);
}

void kioninterCAN_reset(void)
{
    canIf_swReset(KIONINTERCAN_NODE);
    kioninterCAN_config();
    kioninterCAN_configSend(0u);
}

/**
 * @brief config function for sending CAN message
 */
void kioninterCAN_configSend(uint8_t masterId)
{
    //************************** Message Config BMS_CPS_UDS_REQ*****************************************//
    static const CANMessageObjectConfig transmitBMS_CPS_UDS_REQConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x680,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kioninterCANTransmitBMS_CPS_UDS_REQHandler = canIf_configMessageObject(&transmitBMS_CPS_UDS_REQConfig);


    //************************** Message Config BMS_CPS_PDO_TX3*****************************************//
    static const CANMessageObjectConfig transmitBMS_CPS_PDO_TX3Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x381,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kioninterCANTransmitBMS_CPS_PDO_TX3Handler = canIf_configMessageObject(&transmitBMS_CPS_PDO_TX3Config);


    //************************** Message Config BMS_CPS_PDO_TX2*****************************************//
    static const CANMessageObjectConfig transmitBMS_CPS_PDO_TX2Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x281,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kioninterCANTransmitBMS_CPS_PDO_TX2Handler = canIf_configMessageObject(&transmitBMS_CPS_PDO_TX2Config);


    //************************** Message Config BMS_HEARTBEAT*****************************************//
    static const CANMessageObjectConfig transmitBMS_HeartbeatConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x701,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE,
        .dlc       = MESSAGE_DLC_1
    };

    kioninterCANTransmitBMS_HeartbeatHandler = canIf_configMessageObject(&transmitBMS_HeartbeatConfig);


    //************************** Message Config BMS_TIMESTAMP*****************************************//
    static const CANMessageObjectConfig transmitBMS_TimeStampConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x100,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kioninterCANTransmitBMS_TimeStampHandler = canIf_configMessageObject(&transmitBMS_TimeStampConfig);


    //************************** Message Config BMS_CPS_SDO_REQ*****************************************//
    static const CANMessageObjectConfig transmitBMS_CPS_SDO_REQConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x602,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kioninterCANTransmitBMS_CPS_SDO_REQHandler = canIf_configMessageObject(&transmitBMS_CPS_SDO_REQConfig);


    //************************** Message Config BMS_MODULECOTROL*****************************************//
    static const CANMessageObjectConfig transmitBMS_ModuleCotrolConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x0,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE,
        .dlc       = MESSAGE_DLC_2
    };

    kioninterCANTransmitBMS_ModuleCotrolHandler = canIf_configMessageObject(&transmitBMS_ModuleCotrolConfig);


    //************************** Message Config BMS_CPS_PDO_TX1*****************************************//
    static const CANMessageObjectConfig transmitBMS_CPS_PDO_TX1Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x181,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kioninterCANTransmitBMS_CPS_PDO_TX1Handler = canIf_configMessageObject(&transmitBMS_CPS_PDO_TX1Config);


    //************************** Message Config BMS_ICDA_REQUEST*****************************************//
    static const CANMessageObjectConfig transmitBMS_ICDA_RequestConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x500,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kioninterCANTransmitBMS_ICDA_RequestHandler = canIf_configMessageObject(&transmitBMS_ICDA_RequestConfig);
#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
    //************************** Message Config STRPM_SYM_VAL1*****************************************//
    CANMessageObjectConfig transmitStrPM_SyM_Val1Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x300U + masterId,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONINTERCAN_NODE
    };

    kioninterCANTransmitStrPM_SyM_Val1Handler = canIf_configMessageObject(&transmitStrPM_SyM_Val1Config);
#endif
}
