/**
 *
 * @file kioninterCAN_config.h
 * @created on Mon Nov 16 10:15:18 CET 2020
 * @brief This file contains all the CAN message objects definitions for CAN NODE 1
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - slaveID (R)
 */
#pragma once


#include "kioninterCAN.h"
#include "canIf.h"
#include "canId_config.h"
#include "can_config.h"

/******************** Defines for CAN variable values calibration ************************************/

#define KIONINTER_BMS_REQ_CPSOUTBOOST_I_FACTOR (0.001 / 0.01)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KIONINTER_BMS_REQ_CPSOUTBOOST_I_OFFSET (0)

#define KIONINTER_BMS_REQ_CPSOUT_I_FACTOR (0.001 / 0.01)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KIONINTER_BMS_REQ_CPSOUT_I_OFFSET (0)

#define KIONINTER_BMS_REQ_MIN_V_FACTOR (1.0 / 100.0)
#define KIONINTER_BMS_REQ_MIN_V_OFFSET (0)

#define KIONINTER_CPS_TEMPCPSOUT_FACTOR (1)
#define KIONINTER_CPS_TEMPCPSOUT_OFFSET (-40.0)

#define KIONINTER_CPS_CPSOUT_I_FACTOR (0.001 / 0.01)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KIONINTER_CPS_CPSOUT_I_OFFSET (0)

#define KIONINTER_CPS_CPSOUTVOLTAGE_FACTOR (1 / 0.025)
#define KIONINTER_CPS_CPSOUTVOLTAGE_OFFSET (0)

#define KIONINTER_CPS_VOLTAGEINPUT_FACTOR (1 / 0.025)
#define KIONINTER_CPS_VOLTAGEINPUT_OFFSET (0)


/********************  NEW CAN_include_config  *************************************************/

#if CAN_EXTERNAL_ID == KIONINTERCAN_ID

#define KIONINTERCAN_NODE           CAN_NODE_2
#define DTC_CAN_CT_ROLL_INCORRECT   DTC_CAN1_CT_ROLL_INCORRECT
#define DTC_CAN_CRC_INCORRECT       DTC_CAN1_CRC_INCORRECT
#define CAN_EXTERNAL_SEND_UDS(x)    kioninterCAN_sendBMS_SCU_UDSout(x)
#define CAN_EXTERNAL_CONFIG()       kioninterCAN_config()
#define CAN_EXTERNAL_RECEIVE(x)     kioninterCAN_receive(x)
#define CAN_EXTERNAL_CONFIG_STRUCT  kioninterCanConfig
#define CAN_EXTERNAL_CONFIG_SEND(x) kioninterCAN_configSend(x)
#define CAN_EXTERNAL_SEND_100()     kioninterCANSend100()
#define CAN_EXTERNAL_SEND_40()      kioninterCANSend40()

#elif CAN_INTERNAL_ID == KIONINTERCAN_ID

#define KIONINTERCAN_NODE           CAN_NODE_0
#define DTC_CAN_CT_ROLL_INCORRECT   DTC_CAN0_CT_ROLL_INCORRECT
#define DTC_CAN_CRC_INCORRECT       DTC_CAN0_CRC_INCORRECT
#define CAN_INTERNAL_SEND_UDS(x)    kioninterCAN_sendBMS_SCU_UDSout(x)
#define CAN_INTERNAL_CONFIG()       kioninterCAN_config()
#define CAN_INTERNAL_RECEIVE(x)     kioninterCAN_receive(x)
#define CAN_INTERNAL_CONFIG_STRUCT  kioninterCanConfig
#define CAN_INTERNAL_CONFIG_SEND(x) kioninterCAN_configSend(x)
#define CAN_INTERNAL_SEND_40()      kioninterCANSend40()
#define CAN_INTERNAL_SEND_10()      kioninterCANSend10()
#else

/* This prevents "undefined" errors while building other projects.
 * There is probably a more beautiful way TODO this...
 */
#define DTC_CAN_CT_ROLL_INCORRECT 0
#define DTC_CAN_CRC_INCORRECT     0
#define KIONINTERCAN_NODE         0

#endif

#define KIONINTERCAN_MAX_MISSING_ACK_ERROR_COUNT 3u

/******************** extern CANMessageHandle declaration ************************************/

/**
 * @var kioninterCANTransmitBMS_CPS_UDS_REQHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitBMS_CPS_UDS_REQHandler;


/**
 * @var kioninterCANTransmitBMS_CPS_PDO_TX3Handler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitBMS_CPS_PDO_TX3Handler;


/**
 * @var kioninterCANTransmitBMS_CPS_PDO_TX2Handler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitBMS_CPS_PDO_TX2Handler;


/**
 * @var kioninterCANTransmitBMS_HeartbeatHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitBMS_HeartbeatHandler;


/**
 * @var kioninterCANTransmitBMS_TimeStampHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitBMS_TimeStampHandler;


/**
 * @var kioninterCANTransmitBMS_CPS_SDO_REQHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitBMS_CPS_SDO_REQHandler;


/**
 * @var kioninterCANTransmitBMS_ModuleCotrolHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitBMS_ModuleCotrolHandler;


/**
 * @var kioninterCANTransmitBMS_CPS_PDO_TX1Handler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitBMS_CPS_PDO_TX1Handler;


/**
 * @var kioninterCANTransmitBMS_ICDA_RequestHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitBMS_ICDA_RequestHandler;


/**
 * @var kioninterCANTransmitCPS_BMS_UDS_RESPHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitCPS_BMS_UDS_RESPHandler;


/**
 * @var kioninterCANTransmitCH_CPS_WakeUpHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitCH_CPS_WakeUpHandler;


/**
 * @var kioninterCANTransmitCPS_VEHICLE_UDS_RESPHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitCPS_VEHICLE_UDS_RESPHandler;


/**
 * @var kioninterCANTransmitCPS_BMS_EmergencyHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitCPS_BMS_EmergencyHandler;


/**
 * @var kioninterCANTransmitCPS_HeartbeatHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitCPS_HeartbeatHandler;


/**
 * @var kioninterCANTransmitCPS_BMS_SDO_RESPHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitCPS_BMS_SDO_RESPHandler;


/**
 * @var kioninterCANTransmitCPS_BMS_PDO_TX2Handler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitCPS_BMS_PDO_TX2Handler;


/**
 * @var kioninterCANTransmitCPS_BMS_PDO_TX3Handler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitCPS_BMS_PDO_TX3Handler;


/**
 * @var kioninterCANTransmitCPS_BMS_PDO_TX1Handler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitCPS_BMS_PDO_TX1Handler;


/**
 * @var kioninterCANTransmitICDA_BMS_ResultHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitICDA_BMS_ResultHandler;


/**
 * @var kioninterCANTransmitICDA_BMS_ResponseHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kioninterCANTransmitICDA_BMS_ResponseHandler;


/**
 * @var kioninterCANReceiveStandardHandler
 * @brief Handler for received CAN messages with standard ids
 */
extern CANMessageObject kioninterCANReceiveStandardHandler;

/**
 * @var kioninterCANReceiveExtendedHandler
 * @brief Handler for received CAN messages with extended ids
 */
extern CANMessageObject kioninterCANReceiveExtendedHandler;

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
/**
 * @var interCANTransmitStrPM_SyM_Val1Handler
 * @brief Handler for CAN message Values from Pack and String Master
 */
extern CANMessageObject kioninterCANTransmitStrPM_SyM_Val1Handler;
#endif

extern CANNodeConfig kioninterCanConfig;
