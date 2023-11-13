/**
 *
 * @file icdaCAN_config.h
 * @created on Mon Nov 16 10:15:18 CET 2020
 * @brief This file contains all the CAN message objects definitions for CAN NODE 1
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - slaveID (R)
 */
#pragma once


#include "icdaCAN.h"
#include "canIf.h"
#include "canId_config.h"
#include "can_config.h"


#define ICDACAN_NODE CAN_NODE_0
// #define DTC_CAN_CT_ROLL_INCORRECT        DTC_CAN0_CT_ROLL_INCORRECT
// #define DTC_CAN_CRC_INCORRECT            DTC_CAN0_CRC_INCORRECT
#define CAN_CURRENTSENSOR_SEND_UDS(x)   icdaCAN_sendBMS_SCU_UDSout(x)
#define CAN_CURRENTSENSOR_CONFIG()      icdaCAN_config()
#define CAN_CURRENTSENSOR_RECEIVE(x)    icdaCAN_receive(x)
#define CAN_CURRENTSENSOR_CONFIG_STRUCT icdaCANConfig
#define CAN_CURRENTSENSOR_CONFIG_SEND() icdaCAN_configSend()


/******************** CANMessageHandle declaration ************************************/

/**
 * @var icdaCANTransmitBMS_ICDA_RequestHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject icdaCANTransmitBMS_ICDA_RequestHandler;


/**
 * @var icdaCANTransmitICDA_BMS_ResultHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject icdaCANTransmitICDA_BMS_ResultHandler;


/**
 * @var icdaCANTransmitICDA_BMS_ResponseHandler
 * @brief Handler for CAN message
 */
extern CANMessageObject icdaCANTransmitICDA_BMS_ResponseHandler;

extern CANNodeConfig icdaCANConfig;
