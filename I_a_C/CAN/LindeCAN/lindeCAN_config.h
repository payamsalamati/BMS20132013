/**
 *
 * @file lindeCAN_config.h
 * @modulenumber 0x0D
 * @author Generated File with DPCParser release-1.3.4 Commit 1347995
 * @created on Mon Jan 16 10:46:58 CET 2023
 * @brief This file contains all the CAN message objects definitions for CAN NODE 1
 * @copyright Futavis GmbH, Aachen 2023 - alle Rechte vorbehalten
 * @details Generated from file "linde.sym"
 * @par Global variables
 * - slaveID (R)
 * @par changes
 * - first creation Mon Jan 16 10:46:58 CET 2023
 */
#ifndef INTERFACELAYER_LINDECAN_CONFIG_H_
#define INTERFACELAYER_LINDECAN_CONFIG_H_

#include "canIf.h"
#include "can_config.h"
#include "lindeCAN.h"
#include "config_enable.h"


/******************** Defines for CAN variable values calibration ************************************/

#define LINDE_LIIOCHARGER_CHARGINGVOLTAGE_FACTOR (1.0 / 0.025)
#define LINDE_LIIOCHARGER_CHARGINGVOLTAGE_OFFSET (0)

#define LINDE_LIIOCHARGER_CHARGINGCURRENT_FACTOR (0.001 / 0.025)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define LINDE_LIIOCHARGER_CHARGINGCURRENT_OFFSET (0)

#define LINDE_LIIOBMS_MAXDISCHARGEPOWER2_FACTOR (1000.0 / 10)  //power factor as defined in the corresponding dbc file, values from kW to W"
#define LINDE_LIIOBMS_MAXDISCHARGEPOWER2_OFFSET (0)

#define LINDE_LIIOBMS_MAXCHARGEPOWER2_FACTOR (1000.0 / 10)  //power factor as defined in the corresponding dbc file, values from kW to W"
#define LINDE_LIIOBMS_MAXCHARGEPOWER2_OFFSET (0)

#define LINDE_LIIOBMS_OUTPUTVOLTAGE_FACTOR (1.0 / 0.001)
#define LINDE_LIIOBMS_OUTPUTVOLTAGE_OFFSET (0)

#define LINDE_LIIOBMS_MAXCHARGEVOLTAGE_FACTOR (1.0 / 0.001)
#define LINDE_LIIOBMS_MAXCHARGEVOLTAGE_OFFSET (0)

#define LINDE_LIIOBMS_MINDISCHARGEVOLTAGE_FACTOR (1.0 / 0.001)
#define LINDE_LIIOBMS_MINDISCHARGEVOLTAGE_OFFSET (0)

#define LINDE_LIIOBMS_MAXCHARGECURRENT2_FACTOR (0.001 / 0.25)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define LINDE_LIIOBMS_MAXCHARGECURRENT2_OFFSET (0)

#define LINDE_LIIOBMS_MAXDISCHARGECURRENT2_FACTOR (0.001 / 0.25)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define LINDE_LIIOBMS_MAXDISCHARGECURRENT2_OFFSET (0)

#define LINDE_LIIOBMS_MAXDISCHARGECURRENT100_FACTOR (0.001 / 0.25)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define LINDE_LIIOBMS_MAXDISCHARGECURRENT100_OFFSET (0)

#define LINDE_LIIOBMS_MAXCHARGECURRENT100_FACTOR (0.001 / 0.25)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define LINDE_LIIOBMS_MAXCHARGECURRENT100_OFFSET (0)

#define LINDE_LIIOBMS_BATTERYCURRENT_FACTOR (0.001 / 0.001)  //current factor as defined in the corresponding dbc file, values from mA to A"
#define LINDE_LIIOBMS_BATTERYCURRENT_OFFSET (0)

#define LINDE_LIIOBMS_BATTERYVOLTAGE_FACTOR (1.0 / 0.001)
#define LINDE_LIIOBMS_BATTERYVOLTAGE_OFFSET (0)


/********************  NEW CAN_include_config  *************************************************/

//TODO: Linde - config not complete

#define LINDE_CAN CONFIG_ENABLED

#define LINDECAN_NODE CAN_NODE_2
//#define DTC_CAN_CT_ROLL_INCORRECT DTC_CAN1_CT_ROLL_INCORRECT
//#define DTC_CAN_CRC_INCORRECT     DTC_CAN1_CRC_INCORRECT
#define LINDE_CAN_SEND_UDS(x) lindeCAN_sendBMS_SCU_UDSout(x)
//#define LINDE_CAN_CONFIG_SEND(x) lindeCAN_configSend()


/******************** extern CANMessageHandle declaration ************************************/

/**
 * @var lindeCANTransmitmodule_controlHandler
 * @brief Handler for CAN message network management (NMT)
 */
extern CANMessageObject lindeCANTransmitmodule_controlHandler;


/**
 * @var lindeCANTransmitXCP_DTO_LiIoBMSHandler
 * @brief Handler for CAN message XCP responses from LIB with Linde BMZ protocol
 */
extern CANMessageObject lindeCANTransmitXCP_DTO_LiIoBMSHandler;


/**
 * @var lindeCANTransmitXCP_CTO_LiIoBMSHandler
 * @brief Handler for CAN message XCP commands for LIB with Linde BMZ protocol
 */
extern CANMessageObject lindeCANTransmitXCP_CTO_LiIoBMSHandler;


/**
 * @var lindeCANTransmitTraction_SDOreq_LiIoBMSHandler
 * @brief Handler for CAN message SDO Rx, node 0x0D (LIB with Linde BMZ protocol)
 */
extern CANMessageObject lindeCANTransmitTraction_SDOreq_LiIoBMSHandler;


/**
 * @var lindeCANTransmitTraction_PDO4Handler
 * @brief Handler for CAN message PDO 4 (Tx), node 0x01 (KMC) (for LIB with Linde BMZ protocol)
 */
extern CANMessageObject lindeCANTransmitTraction_PDO4Handler;


/**
 * @var lindeCANTransmitLiIoCharger_SDOreq_LiIoBMSHandler
 * @brief Handler for CAN message SDO Rx, node 0x5D (LIB with Linde BMZ protocol), SDO clients: OBC, EXC
 */
extern CANMessageObject lindeCANTransmitLiIoCharger_SDOreq_LiIoBMSHandler;


/**
 * @var lindeCANTransmitLiIoCharger_PDO1Handler
 * @brief Handler for CAN message PDO 1 (Tx), node 0x5D (OBC, EXC)
 */
extern CANMessageObject lindeCANTransmitLiIoCharger_PDO1Handler;


/**
 * @var lindeCANTransmitLiIoBMS_SDOresp_TractionHandler
 * @brief Handler for CAN message SDO Tx, node 0x0D (LIB with Linde BMZ protocol), SDO client: KMC
 */
extern CANMessageObject lindeCANTransmitLiIoBMS_SDOresp_TractionHandler;


/**
 * @var lindeCANTransmitLiIoBMS_SDOresp_LiIoChargerHandler
 * @brief Handler for CAN message SDO Tx, node 0x5D (LIB with Linde BMZ protocol), SDO client: OBC, EXC
 */
extern CANMessageObject lindeCANTransmitLiIoBMS_SDOresp_LiIoChargerHandler;


/**
 * @var lindeCANTransmitLiIoBMS_PDO5Handler
 * @brief Handler for CAN message PDO5 (Tx), node 0x01 (LIB with Linde BMZ prototol)
 */
extern CANMessageObject lindeCANTransmitLiIoBMS_PDO5Handler;


/**
 * @var lindeCANTransmitLiIoBMS_PDO4Handler
 * @brief Handler for CAN message PDO4 (Tx), node 0x0D (LIB with Linde BMZ prototol)
 */
extern CANMessageObject lindeCANTransmitLiIoBMS_PDO4Handler;


/**
 * @var lindeCANTransmitLiIoBMS_PDO3Handler
 * @brief Handler for CAN message PDO3 (Tx), node 0x0D (LIB with Linde BMZ prototol)
 */
extern CANMessageObject lindeCANTransmitLiIoBMS_PDO3Handler;


/**
 * @var lindeCANTransmitLiIoBMS_PDO2Handler
 * @brief Handler for CAN message PDO2 (Tx), node 0x0D (LIB with Linde BMZ prototol)
 */
extern CANMessageObject lindeCANTransmitLiIoBMS_PDO2Handler;


/**
 * @var lindeCANTransmitLiIoBMS_PDO1Handler
 * @brief Handler for CAN message PDO1 (Tx), node 0x0D (LIB with Linde BMZ protocol)
 */
extern CANMessageObject lindeCANTransmitLiIoBMS_PDO1Handler;


/**
 * @var lindeCANTransmitLiIoBMS_HeartbeatHandler
 * @brief Handler for CAN message heartbeat (NMT error control), node 0x0D (LIB with Linde BMZ protocol)
 */
extern CANMessageObject lindeCANTransmitLiIoBMS_HeartbeatHandler;


/**
 * @var lindeCANTransmitLiIoBMS_DiagResponseHandler
 * @brief Handler for CAN message KWP2000 responses from LIB with Linde BMZ protocol
 */
extern CANMessageObject lindeCANTransmitLiIoBMS_DiagResponseHandler;


#endif /* INTERFACELAYER_LINDECAN_CONFIG_H_ */
