/**
 *
 * @file kionCAN_config.c
 * @created on Tue Feb 16 14:15:58 CET 2021
 * @brief  This file contains all the CAN message objects definitions for CAN NODE 1
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - slaveID (R)
 */

//**************************INCLUDES ******************************//


#include "kionCAN.h"

#include "canIf.h"
#include "osIf.h"
#include "task_cfg.h"

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//

MEM_CAN CANMessageObject kionCANTransmitdebugDTCHandler;
#if defined(SW_RESET_ANALYSIS_CAN_DATA)
MEM_CAN CANMessageObject kionCANTransmitdebugTaskCurrentTimeHandler;
MEM_CAN CANMessageObject kionCANTransmitdebugTaskMaxTimeHandler;
MEM_CAN CANMessageObject kionCANTransmitdebugSBCStatusHandler;
MEM_CAN CANMessageObject kionCANTransmitMutexPendFailedHandler;
MEM_CAN CANMessageObject kionCANTransmitMutexPostFailedHandler;
#endif
MEM_CAN CANMessageObject kionCANTransmitlib_udsHandler;
MEM_CAN CANMessageObject kionCANTransmitlib_sdo_txHandler;
MEM_CAN CANMessageObject kionCANTransmitlib_pdo_tx8Handler;
MEM_CAN CANMessageObject kionCANTransmitlib_pdo_tx7Handler;
MEM_CAN CANMessageObject kionCANTransmitlib_pdo_tx6Handler;
MEM_CAN CANMessageObject kionCANTransmitlib_pdo_tx5Handler;
MEM_CAN CANMessageObject kionCANTransmitlib_pdo_tx4Handler;
MEM_CAN CANMessageObject kionCANTransmitlib_pdo_tx3Handler;
MEM_CAN CANMessageObject kionCANTransmitlib_pdo_tx2Handler;
MEM_CAN CANMessageObject kionCANTransmitlib_pdo_tx1Handler;
MEM_CAN CANMessageObject kionCANTransmitlib_heartbeatHandler;
MEM_CAN CANMessageObject kionCANTransmitlib_emergencyHandler;
MEM_CAN CANMessageObject kionCANTransmitcps_udsHandler;
MEM_CAN CANMessageObject kionCANTransmitDiagRespBmsHandler;
MEM_CAN CANMessageObject xcpCanTransmitHandler;  // kionCANTransmitlib_xcp_resHandler

MEM_CAN CANMessageObject kionCANReceivedtu_udsHandler;
MEM_CAN CANMessageObject kionCANReceivetimeHandler;
MEM_CAN CANMessageObject kionCANReceiveobc_heartbeatHandler;
MEM_CAN CANMessageObject kionCANReceivemodule_controlHandler;
MEM_CAN CANMessageObject kionCANReceivelib_sdo_rxHandler;
MEM_CAN CANMessageObject kionCANReceivelib_pdo_rx4Handler;
MEM_CAN CANMessageObject kionCANReceivelib_pdo_rx1Handler;
MEM_CAN CANMessageObject kionCANReceivekwpc_heartbeatHandler;
MEM_CAN CANMessageObject kionCANReceiveexc_heartbeatHandler;
MEM_CAN CANMessageObject kionCANReceiveTimeStampHandler;
MEM_CAN CANMessageObject kionCANReceiveSYNCHandler;
MEM_CAN CANMessageObject kionCANReceiveHeartbtLiionChargerHandler;
MEM_CAN CANMessageObject kionCANReceiveDiagReqBmsHandler;
MEM_CAN CANMessageObject xcpCanReceiveHandler;  // kionCANReceivelib_xcp_cmdHandler

MEM_CAN CANMessageObject kionCANTransmitdebugValues1Handler;

//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
void kionCAN_config(void)
{
    //************************** Message Config TIME*****************************************//
    static const CANMessageObjectConfig receivetimeConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x100,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANReceivetimeHandler = canIf_configMessageObject(&receivetimeConfig);


    //************************** Message Config OBC_HEARTBEAT*****************************************//
    static const CANMessageObjectConfig receiveobc_heartbeatConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x751,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceiveobc_heartbeatHandler = canIf_configMessageObject(&receiveobc_heartbeatConfig);


    //************************** Message Config MODULE_CONTROL*****************************************//
    static const CANMessageObjectConfig receivemodule_controlConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x0,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceivemodule_controlHandler = canIf_configMessageObject(&receivemodule_controlConfig);


    //************************** Message Config LIB_SDO_RX*****************************************//
    static const CANMessageObjectConfig receivelib_sdo_rxConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x627,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceivelib_sdo_rxHandler = canIf_configMessageObject(&receivelib_sdo_rxConfig);


    //************************** Message Config LIB_PDO_RX4*****************************************//
    static const CANMessageObjectConfig receivelib_pdo_rx4Config = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x527,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceivelib_pdo_rx4Handler = canIf_configMessageObject(&receivelib_pdo_rx4Config);


    //************************** Message Config LIB_PDO_RX1*****************************************//
    static const CANMessageObjectConfig receivelib_pdo_rx1Config = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x227,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceivelib_pdo_rx1Handler = canIf_configMessageObject(&receivelib_pdo_rx1Config);


    //************************** Message Config KWPC_HEARTBEAT*****************************************//
    // @req CB-75003
    static const CANMessageObjectConfig receivekwpc_heartbeatConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x701,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceivekwpc_heartbeatHandler = canIf_configMessageObject(&receivekwpc_heartbeatConfig);


    //************************** Message Config EXC_HEARTBEAT*****************************************//
    static const CANMessageObjectConfig receiveexc_heartbeatConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x74a,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceiveexc_heartbeatHandler = canIf_configMessageObject(&receiveexc_heartbeatConfig);


    //************************** Message Config TIMESTAMP*****************************************//
    static const CANMessageObjectConfig receiveTimeStampConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0xff,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceiveTimeStampHandler = canIf_configMessageObject(&receiveTimeStampConfig);


    //************************** Message Config SYNC*****************************************//
    static const CANMessageObjectConfig receiveSYNCConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x80,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceiveSYNCHandler = canIf_configMessageObject(&receiveSYNCConfig);


    //************************** Message Config HEARTBTLIIONCHARGER*****************************************//
    static const CANMessageObjectConfig receiveHeartbtLiionChargerConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x705,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceiveHeartbtLiionChargerHandler = canIf_configMessageObject(&receiveHeartbtLiionChargerConfig);


    //************************** Message Config DIAGREQBMS*****************************************//
    static const CANMessageObjectConfig receiveDiagReqBmsConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x78d,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceiveDiagReqBmsHandler = canIf_configMessageObject(&receiveDiagReqBmsConfig);

    //************************** Message Config DTU_UDS*****************************************//
    static const CANMessageObjectConfig receivedtu_udsConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x680,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceivedtu_udsHandler = canIf_configMessageObject(&receivedtu_udsConfig);

    //************************** Message Config lib_xcp_cmd*****************************************//
    static const CANMessageObjectConfig receivelib_xcp_cmdConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x1CFF27FD,
        .idMask    = 0x1fffffff,
        .ideMask   = 1,
        .mode      = CAN_EXTENDED_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    xcpCanReceiveHandler = canIf_configMessageObject(&receivelib_xcp_cmdConfig);
}

void kionCAN_configBeforeProtocolSelection(void)
{
    //************************** Message Config TIME*****************************************//
    static const CANMessageObjectConfig receivetimeConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x100,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANReceivetimeHandler = canIf_configMessageObject(&receivetimeConfig);


    //************************** Message Config OBC_HEARTBEAT*****************************************//
    static const CANMessageObjectConfig receiveobc_heartbeatConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x751,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceiveobc_heartbeatHandler = canIf_configMessageObject(&receiveobc_heartbeatConfig);


    //************************** Message Config MODULE_CONTROL*****************************************//
    static const CANMessageObjectConfig receivemodule_controlConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x0,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceivemodule_controlHandler = canIf_configMessageObject(&receivemodule_controlConfig);


    //************************** Message Config LIB_SDO_RX*****************************************//
    static const CANMessageObjectConfig receivelib_sdo_rxConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x627,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceivelib_sdo_rxHandler = canIf_configMessageObject(&receivelib_sdo_rxConfig);

    //************************** Message Config KWPC_HEARTBEAT*****************************************//
    // @req CB-75003
    static const CANMessageObjectConfig receivekwpc_heartbeatConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x701,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceivekwpc_heartbeatHandler = canIf_configMessageObject(&receivekwpc_heartbeatConfig);


    //************************** Message Config EXC_HEARTBEAT*****************************************//
    static const CANMessageObjectConfig receiveexc_heartbeatConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x74a,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceiveexc_heartbeatHandler = canIf_configMessageObject(&receiveexc_heartbeatConfig);


    //************************** Message Config TIMESTAMP*****************************************//
    static const CANMessageObjectConfig receiveTimeStampConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0xff,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceiveTimeStampHandler = canIf_configMessageObject(&receiveTimeStampConfig);

    //************************** Message Config DTU_UDS*****************************************//
    static const CANMessageObjectConfig receivedtu_udsConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x680,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE
    };

    kionCANReceivedtu_udsHandler = canIf_configMessageObject(&receivedtu_udsConfig);

    //************************** Message Config lib_xcp_cmd*****************************************//
    static const CANMessageObjectConfig receivelib_xcp_cmdConfig = {
        .direction = CAN_DIRECTION_RECEIVE,
        .id        = 0x1CFF27FD,
        .idMask    = 0x1fffffff,
        .ideMask   = 1,
        .mode      = CAN_EXTENDED_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    xcpCanReceiveHandler = canIf_configMessageObject(&receivelib_xcp_cmdConfig);
}


/**
 * @brief config function for sending CAN message
 */
void kionCAN_configSend(void)
{
    //************************** Message Config LIB_PDO_TX8*****************************************//
    // @req CB-74933
    static const CANMessageObjectConfig transmitlib_pdo_tx8Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x4f7,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitlib_pdo_tx8Handler = canIf_configMessageObject(&transmitlib_pdo_tx8Config);

    //************************** Message Config LIB_PDO_TX7*****************************************//
    // @req CB-74930
    static const CANMessageObjectConfig transmitlib_pdo_tx7Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x3f7,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitlib_pdo_tx7Handler = canIf_configMessageObject(&transmitlib_pdo_tx7Config);


    //************************** Message Config LIB_PDO_TX6*****************************************//
    // @req CB-74926
    static const CANMessageObjectConfig transmitlib_pdo_tx6Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x2f7,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitlib_pdo_tx6Handler = canIf_configMessageObject(&transmitlib_pdo_tx6Config);


    //************************** Message Config LIB_PDO_TX5*****************************************//
    // @req CB-74923
    static const CANMessageObjectConfig transmitlib_pdo_tx5Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x1f7,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitlib_pdo_tx5Handler = canIf_configMessageObject(&transmitlib_pdo_tx5Config);


    //************************** Message Config LIB_PDO_TX4*****************************************//
    // @req CB-74931
    static const CANMessageObjectConfig transmitlib_pdo_tx4Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x4a7,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitlib_pdo_tx4Handler = canIf_configMessageObject(&transmitlib_pdo_tx4Config);


    //************************** Message Config LIB_PDO_TX3*****************************************//
    // @req CB-74928
    static const CANMessageObjectConfig transmitlib_pdo_tx3Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x3a7,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitlib_pdo_tx3Handler = canIf_configMessageObject(&transmitlib_pdo_tx3Config);


    //************************** Message Config LIB_PDO_TX2*****************************************//
    // @req CB-74924
    static const CANMessageObjectConfig transmitlib_pdo_tx2Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x2a7,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitlib_pdo_tx2Handler = canIf_configMessageObject(&transmitlib_pdo_tx2Config);


    //************************** Message Config LIB_PDO_TX1*****************************************//
    // @req CB-74922
    static const CANMessageObjectConfig transmitlib_pdo_tx1Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x1a7,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitlib_pdo_tx1Handler = canIf_configMessageObject(&transmitlib_pdo_tx1Config);
}

void kionCAN_configSendBeforeProtocolSelection(void)
{
    //************************** Message Config DEBUGDTC*****************************************//
    static const CANMessageObjectConfig transmitdebugDTCConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x14,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_5
    };

    kionCANTransmitdebugDTCHandler = canIf_configMessageObject(&transmitdebugDTCConfig);

#if defined(SW_RESET_ANALYSIS_CAN_DATA)
    static const CANMessageObjectConfig kionCANTransmitdebugTaskCurrentTimeConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x78,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitdebugTaskCurrentTimeHandler = canIf_configMessageObject(&kionCANTransmitdebugTaskCurrentTimeConfig);

    static const CANMessageObjectConfig kionCANTransmitdebugTaskMaxTimeConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x79,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitdebugTaskMaxTimeHandler = canIf_configMessageObject(&kionCANTransmitdebugTaskMaxTimeConfig);

    static const CANMessageObjectConfig kionCANTransmitdebugSBCStatusConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x7A,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_3
    };

    kionCANTransmitdebugSBCStatusHandler = canIf_configMessageObject(&kionCANTransmitdebugSBCStatusConfig);

    static const CANMessageObjectConfig kionCANTransmitMutexPendFailedConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x7B,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };
    kionCANTransmitMutexPendFailedHandler = canIf_configMessageObject(&kionCANTransmitMutexPendFailedConfig);


    static const CANMessageObjectConfig kionCANTransmitMutexPostFailedConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x7C,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };
    kionCANTransmitMutexPostFailedHandler = canIf_configMessageObject(&kionCANTransmitMutexPostFailedConfig);


#endif
    //************************** Message Config LIB_UDS*****************************************//
    // @req CB-74934
    static const CANMessageObjectConfig transmitlib_udsConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x6a7,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitlib_udsHandler = canIf_configMessageObject(&transmitlib_udsConfig);


    //************************** Message Config LIB_SDO_TX*****************************************//
    // @req CB-74932
    static const CANMessageObjectConfig transmitlib_sdo_txConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x5a7,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitlib_sdo_txHandler = canIf_configMessageObject(&transmitlib_sdo_txConfig);

    //************************** Message Config LIB_HEARTBEAT*****************************************//
    // @req CB-74935
    static const CANMessageObjectConfig transmitlib_heartbeatConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x727,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_1
    };

    kionCANTransmitlib_heartbeatHandler = canIf_configMessageObject(&transmitlib_heartbeatConfig);


    //************************** Message Config LIB_EMERGENCY*****************************************//
    // @req CB-74921
    static const CANMessageObjectConfig transmitlib_emergencyConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0xa7,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };
    kionCANTransmitlib_emergencyHandler = canIf_configMessageObject(&transmitlib_emergencyConfig);


    //************************** Message Config CPS_UDS*****************************************//
    static const CANMessageObjectConfig transmitcps_udsConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x6df,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitcps_udsHandler = canIf_configMessageObject(&transmitcps_udsConfig);


    //************************** Message Config DIAGRESPBMS*****************************************//
    static const CANMessageObjectConfig transmitDiagRespBmsConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x79d,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitDiagRespBmsHandler = canIf_configMessageObject(&transmitDiagRespBmsConfig);

    //************************** Message Config lib_xcp_res*****************************************//
    // @req CB-74936
    // @req CB-18851
    static const CANMessageObjectConfig receivelib_xcp_resConfig = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x1CFFA7FD,
        .idMask    = 0x1fffffff,
        .ideMask   = 1,
        .mode      = CAN_EXTENDED_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    xcpCanTransmitHandler = canIf_configMessageObject(&receivelib_xcp_resConfig);

    //************************** Message Config DEBUGVALUES1*****************************************//
    static const CANMessageObjectConfig transmitdebugValues1Config = {
        .direction = CAN_DIRECTION_TRANSMIT,
        .id        = 0x15,
        .idMask    = 0xfff,
        .ideMask   = 1,
        .mode      = CAN_STANDARD_ID,
        .node      = KIONCAN_NODE,
        .dlc       = MESSAGE_DLC_8
    };

    kionCANTransmitdebugValues1Handler = canIf_configMessageObject(&transmitdebugValues1Config);
}

void kionCAN_init(void)
{
    kionCAN_config();
    kionCAN_configSend();
}
