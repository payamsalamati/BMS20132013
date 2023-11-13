/**
 *
 * @file kioninterCAN_followUpReceive.h
 * @created on  Mon Nov 16 10:15:18 CET 2020
 * @brief This module provides an interface to the data interface and other functions
             for the received CAN messages
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

#pragma once

//******************* INCLUDES ********************************//
#include <stdint.h>


/**
 * @brief interface function for CPS_BMS_UDS_RESP CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_followUpCPS_BMS_UDS_RESP(const KIONINTER_CPS_BMS_UDS_RESP_t* data, const CANMessage* msg);
/**
 * @brief interface function for CH_CPS_WakeUp CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_followUpCH_CPS_WakeUp(const KIONINTER_CH_CPS_WAKEUP_t* data, const CANMessage* msg);
/**
 * @brief interface function for CPS_VEHICLE_UDS_RESP CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_followUpCPS_VEHICLE_UDS_RESP(const CANMessage* msg);
/**
 * @brief interface function for CPS_BMS_Emergency CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_followUpCPS_BMS_Emergency(const KIONINTER_CPS_BMS_EMERGENCY_t* data, const CANMessage* msg);
/**
 * @brief interface function for CPS_Heartbeat CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_followUpCPS_Heartbeat(const KIONINTER_CPS_HEARTBEAT_t* data, const CANMessage* msg);
/**
 * @brief interface function for CPS_BMS_SDO_RESP CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_followUpCPS_BMS_SDO_RESP(const KIONINTER_CPS_BMS_SDO_RESP_t* data, const CANMessage* msg);
/**
 * @brief interface function for CPS_BMS_PDO_TX2 CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_followUpCPS_BMS_PDO_TX2(const KIONINTER_CPS_BMS_PDO_TX2_t* data, const CANMessage* msg);
/**
 * @brief interface function for CPS_BMS_PDO_TX3 CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_followUpCPS_BMS_PDO_TX3(const KIONINTER_CPS_BMS_PDO_TX3_t* data, const CANMessage* msg);
/**
 * @brief interface function for CPS_BMS_PDO_TX1 CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_followUpCPS_BMS_PDO_TX1(const KIONINTER_CPS_BMS_PDO_TX1_t* data, const CANMessage* msg);
/**
 * @brief interface function for ICDA_BMS_Result CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_followUpICDA_BMS_Result(const CANMessage* msg, bool synchronizedValue);
/**
 * @brief interface function for ICDA_BMS_Response CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_followUpICDA_BMS_Response(const CANMessage* msg);
