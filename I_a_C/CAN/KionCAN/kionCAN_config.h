/**
 *
 * @file kionCAN_config.h
 * @created on Tue Feb 16 14:15:58 CET 2021
 * @brief This file contains all the CAN message objects definitions for CAN NODE 1
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - slaveID (R)
 */
#pragma once


#include "kionCAN.h"
#include "canIf.h"
#include "canId_config.h"
#include "can_config.h"
#include "config_enable.h"

/******************** Defines for CAN variable values calibration ************************************/

#define KION_LIB_MAX_CHARGING_CURRENT_2S_FACTOR (0.001 / 0.01)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KION_LIB_MAX_CHARGING_CURRENT_2S_OFFSET (0)

#define KION_LIB_MAX_CHARGING_CURRENT_100S_FACTOR (0.001 / 0.01)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KION_LIB_MAX_CHARGING_CURRENT_100S_OFFSET (0)

#define KION_LIB_MAX_DISCHARGING_CURRENT_2S_FACTOR (0.001 / 0.01)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KION_LIB_MAX_DISCHARGING_CURRENT_2S_OFFSET (0)

#define KION_LIB_MAX_DISCHARGING_CURRENT_100S_FACTOR (0.001 / 0.01)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KION_LIB_MAX_DISCHARGING_CURRENT_100S_OFFSET (0)

#define KION_LIB_SOC_WITHOUT_SOH_FACTOR (1.0 / 5.0)
#define KION_LIB_SOC_WITHOUT_SOH_OFFSET (0)

#define KION_LIB_SOC_WITHOUT_SOH_FINE_FACTOR (1 / 0.1)
#define KION_LIB_SOC_WITHOUT_SOH_FINE_OFFSET (0)

#define KION_LIB_MAX_CHARGING_VOLTAGE_FACTOR (1.0 / 0.01)
#define KION_LIB_MAX_CHARGING_VOLTAGE_OFFSET (0)

#define KION_LIB_MIN_DISCHARGING_VOLTAGE_FACTOR (1.0 / 0.01)
#define KION_LIB_MIN_DISCHARGING_VOLTAGE_OFFSET (0)

#define KION_LIB_SOC_WITH_SOH_FACTOR (1.0 / 5.0)
#define KION_LIB_SOC_WITH_SOH_OFFSET (0)

#define KION_LIB_POWER_FACTOR (1)  //power factor as defined in the corresponding dbc file, values from kW to W"
#define KION_LIB_POWER_OFFSET (-524286.0)

#define KION_LIB_VOLTAGE_AFTER_CONTACTOR_FACTOR (1.0 / 0.01)
#define KION_LIB_VOLTAGE_AFTER_CONTACTOR_OFFSET (0)

#define KION_LIB_STATE_OF_HEALTH_FACTOR (1.0 / 0.5)
#define KION_LIB_STATE_OF_HEALTH_OFFSET (0)

#define KION_LIB_VOLTAGE_IN_FRONT_OF_CONTACTO_FACTOR (1.0 / 0.01)
#define KION_LIB_VOLTAGE_IN_FRONT_OF_CONTACTO_OFFSET (0)

#define KION_LIB_TEMPERATURE_MIN_FACTOR (1)
#define KION_LIB_TEMPERATURE_MIN_OFFSET (-40.0)

#define KION_LIB_TEMPERATURE_MAX_FACTOR (1)
#define KION_LIB_TEMPERATURE_MAX_OFFSET (-40.0)

#define KION_LIB_TEMPERATURE_AVG_FACTOR (1)
#define KION_LIB_TEMPERATURE_AVG_OFFSET (-40.0)

#define KION_LIB_CURRENT_FACTOR (0.001 / 0.01)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KION_LIB_CURRENT_OFFSET (-2621.42 / 0.01)

#define KION_BMSDISVOLTMIN_FACTOR (1.0 / 25.0)  //voltage factor as defined in the corresponding dbc file, values from V to mV"
#define KION_BMSDISVOLTMIN_OFFSET (0)

#define KION_BMSCHARVOLTHIGH_FACTOR (1.0 / 25.0)  //voltage factor as defined in the corresponding dbc file, values from V to mV"
#define KION_BMSCHARVOLTHIGH_OFFSET (0)

#define KION_BMSPOWFORCHAR_FACTOR (1.0 / 10)  //power factor as defined in the corresponding dbc file, values from kW to W"
#define KION_BMSPOWFORCHAR_OFFSET (0)

#define KION_BMSPOWFORDIS_FACTOR (1.0 / 10.0)  //power factor as defined in the corresponding dbc file, values from kW to W"
#define KION_BMSPOWFORDIS_OFFSET (0)

#define KION_BMSNORMCHARCURR_FACTOR (0.001 / 0.25)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KION_BMSNORMCHARCURR_OFFSET (0)

#define KION_BMSMAXCHARCURR_FACTOR (0.001 / 0.25)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KION_BMSMAXCHARCURR_OFFSET (0)

#define KION_BMSMAXDIRCURR_FACTOR (0.001 / 0.25)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KION_BMSMAXDIRCURR_OFFSET (0)

#define KION_BMSBATVOLT_FACTOR (1.0 / 2.0)  //voltage factor as defined in the corresponding dbc file, values from V to mV"
#define KION_BMSBATVOLT_OFFSET (0)

#define KION_LIB_POWER_CONSUMPTION_AVERAGE_FACTOR (1.0 / 0.05)
#define KION_LIB_POWER_CONSUMPTION_AVERAGE_OFFSET (-102.3 / 0.05)

#define KION_TRUCK_OPERATING_HOURS_FACTOR (1)
#define KION_TRUCK_OPERATING_HOURS_OFFSET (-36000.0)

#define KION_LIB_CHARGING_VOLTAGE_FACTOR (1 / 0.01)
#define KION_LIB_CHARGING_VOLTAGE_OFFSET (0)

#define KION_LIB_CHARGING_CURRENT_FACTOR (0.001 / 0.01)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define KION_LIB_CHARGING_CURRENT_OFFSET (0)

#define KION_CELL1_FACTOR (1.0 / 10.0)
#define KION_CELL1_OFFSET (0)

#define KION_CELL2_FACTOR (1.0 / 10.0)
#define KION_CELL2_OFFSET (0)

#define KION_CELL3_FACTOR (1.0 / 10.0)
#define KION_CELL3_OFFSET (0)

#define KION_CELL4_FACTOR (1.0 / 10.0)
#define KION_CELL4_OFFSET (0)

#define KION_CELL5_FACTOR (1.0 / 10.0)
#define KION_CELL5_OFFSET (0)

#define KION_CELL6_FACTOR (1.0 / 10.0)
#define KION_CELL6_OFFSET (0)

#define KION_CELL7_FACTOR (1.0 / 10.0)
#define KION_CELL7_OFFSET (0)


/********************  NEW CAN_include_config  *************************************************/

#if CAN_EXTERNAL_ID == KIONCAN_ID

#define KIONCAN_NODE CAN_NODE_2
// #define DTC_CAN_CT_ROLL_INCORRECT   DTC_CAN2_CT_ROLL_INCORRECT
// #define DTC_CAN_CRC_INCORRECT       DTC_CAN2_CRC_INCORRECT
#define CAN_EXTERNAL_SEND_UDS(x) kionCAN_sendLib_uds(x)

#elif CAN_INTERNAL_ID == KIONCAN_ID

#define KIONCAN_NODE                CAN_NODE_0
// #define DTC_CAN_CT_ROLL_INCORRECT   DTC_CAN0_CT_ROLL_INCORRECT
// #define DTC_CAN_CRC_INCORRECT       DTC_CAN0_CRC_INCORRECT
#define CAN_INTERNAL_SEND_UDS(x)    kionCAN_sendBMS_SCU_UDSout(x)
#define CAN_INTERNAL_CONFIG()       kionCAN_config()
#define CAN_INTERNAL_RECEIVE(x)     kionCAN_receive(x)
#define CAN_INTERNAL_CONFIG_STRUCT  kionCanConfig
#define CAN_INTERNAL_CONFIG_SEND(x) kionCAN_configSend(x)
#define CAN_INTERNAL_SEND_100()     kionCANSend100()

#else

/* This prevents "undefined" errors while building other projects.
 * There is probably a more beautiful way TODO this...
 */
#define DTC_CAN_CT_ROLL_INCORRECT 0
#define DTC_CAN_CRC_INCORRECT     0
#define KIONCAN_NODE              0

#endif

/******************** extern CANMessageHandle declaration ************************************/

/**
 * @var kionCANTransmitlib_udsHandler
 * @brief Handler for CAN message UDS responses from LIB with KION protocol
 */
extern CANMessageObject kionCANTransmitlib_udsHandler;


/**
 * @var kionCANTransmitlib_sdo_txHandler
 * @brief Handler for CAN message SDO Tx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC
 */
extern CANMessageObject kionCANTransmitlib_sdo_txHandler;


/**
 * @var kionCANTransmitlib_pdo_tx8Handler
 * @brief Handler for CAN message PDO 8 (Tx), node 0x77 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_pdo_tx8Handler;


/**
 * @var kionCANTransmitlib_pdo_tx7Handler
 * @brief Handler for CAN message PDO 7 (Tx), node 0x77 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_pdo_tx7Handler;


/**
 * @var kionCANTransmitlib_pdo_tx6Handler
 * @brief Handler for CAN message PDO 6 (Tx), node 0x77 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_pdo_tx6Handler;


/**
 * @var kionCANTransmitlib_pdo_tx5Handler
 * @brief Handler for CAN message PDO 5 (Tx), node 0x77 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_pdo_tx5Handler;


/**
 * @var kionCANTransmitlib_pdo_tx4Handler
 * @brief Handler for CAN message PDO 4 (Tx), node 0x27 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_pdo_tx4Handler;


/**
 * @var kionCANTransmitlib_pdo_tx3Handler
 * @brief Handler for CAN message PDO 3 (Tx), node 0x27 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_pdo_tx3Handler;


/**
 * @var kionCANTransmitlib_pdo_tx2Handler
 * @brief Handler for CAN message PDO 2 (Tx), node 0x27 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_pdo_tx2Handler;


/**
 * @var kionCANTransmitlib_pdo_tx1Handler
 * @brief Handler for CAN message PDO 1 (Tx), node 0x27 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_pdo_tx1Handler;


/**
 * @var kionCANTransmitlib_heartbeatHandler
 * @brief Handler for CAN message heartbeat (NMT error control), node 0x27 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_heartbeatHandler;


/**
 * @var kionCANTransmitlib_emergencyHandler
 * @brief Handler for CAN message emergency (EMCY), node 0x27 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_emergencyHandler;


/**
 * @var kionCANTransmitcps_udsHandler
 * @brief Handler for CAN message UDS responses from CPS in LIB with KION protocol
 */
extern CANMessageObject kionCANTransmitcps_udsHandler;


/**
 * @var kionCANTransmitDiagRespBmsHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kionCANTransmitDiagRespBmsHandler;

/**
 * @var kionCANTransmitdtu_udsHandler
 * @brief Handler for CAN message UDS requests from DTU
 */
extern CANMessageObject kionCANTransmitdtu_udsHandler;


/**
 * @var kionCANTransmittimeHandler
 * @brief Handler for CAN message time stamp (TIME)
 */
extern CANMessageObject kionCANTransmittimeHandler;


/**
 * @var kionCANTransmitobc_heartbeatHandler
 * @brief Handler for CAN message heartbeat (NMT error control), node 0x51 (OBC)
 */
extern CANMessageObject kionCANTransmitobc_heartbeatHandler;


/**
 * @var kionCANTransmitmodule_controlHandler
 * @brief Handler for CAN message network management (NMT)
 */
extern CANMessageObject kionCANTransmitmodule_controlHandler;


/**
 * @var kionCANTransmitlib_sdo_rxHandler
 * @brief Handler for CAN message SDO Rx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC
 */
extern CANMessageObject kionCANTransmitlib_sdo_rxHandler;


/**
 * @var kionCANTransmitlib_pdo_rx4Handler
 * @brief Handler for CAN message PDO 4 (Rx), node 0x27 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_pdo_rx4Handler;


/**
 * @var kionCANTransmitlib_pdo_rx1Handler
 * @brief Handler for CAN message PDO 1 (Rx), node 0x27 (LIB with KION protocol)
 */
extern CANMessageObject kionCANTransmitlib_pdo_rx1Handler;


/**
 * @var kionCANTransmitkwpc_heartbeatHandler
 * @brief Handler for CAN message heartbeat (NMT error control), node 0x01 (KWPC)
 */
extern CANMessageObject kionCANTransmitkwpc_heartbeatHandler;


/**
 * @var kionCANTransmitexc_heartbeatHandler
 * @brief Handler for CAN message heartbeat (NMT error control), node 0x4A (EXC)
 */
extern CANMessageObject kionCANTransmitexc_heartbeatHandler;


/**
 * @var kionCANTransmitTimeStampHandler
 * @brief Handler for CAN message Linde proprietary timestamp message (for LIB with Linde SAFT protocol)
 */
extern CANMessageObject kionCANTransmitTimeStampHandler;


/**
 * @var kionCANTransmitSYNCHandler
 * @brief Handler for CAN message CANopen SYNC message (for LIB with Linde BMZ protocol)
 */
extern CANMessageObject kionCANTransmitSYNCHandler;


/**
 * @var kionCANTransmitHeartbtLiionChargerHandler
 * @brief Handler for CAN message Network Management, Error Control,  liion battery charger Heartbeat
 */
extern CANMessageObject kionCANTransmitHeartbtLiionChargerHandler;


/**
 * @var kionCANTransmitDiagReqBmsHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kionCANTransmitDiagReqBmsHandler;


/**
 * @var kionCANTransmitBmsSDOrxHandler
 * @brief Handler for CAN message CAN Open: Service data object (SDO) send by KWPC
 */
extern CANMessageObject kionCANTransmitBmsSDOrxHandler;

/**
 * @var kionCANTransmitdebugDTCHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject kionCANTransmitdebugDTCHandler;

/**
 * @var kionCANReceiveStandardHandler
 * @brief Handler for received CAN messages with standard ids
 */
extern CANMessageObject kionCANReceiveStandardHandler;

extern CANMessageObject xcpCanTransmitHandler;

extern CANNodeConfig kionCanConfig;

#if defined(SW_RESET_ANALYSIS_CAN_DATA)
extern CANMessageObject kionCANTransmitdebugTaskCurrentTimeHandler;
extern CANMessageObject kionCANTransmitdebugTaskMaxTimeHandler;
extern CANMessageObject kionCANTransmitdebugSBCStatusHandler;
extern CANMessageObject kionCANTransmitMutexPendFailedHandler;
extern CANMessageObject kionCANTransmitMutexPostFailedHandler;
#endif

extern CANMessageObject kionCANTransmitdebugValues1Handler;
