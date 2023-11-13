/**
 *
 * @file lindeCAN_followUpReceive.h
 * @modulenumber 0x0D
 * @author Generated File with DPCParser release-1.3.4 Commit 1347995
 * @created on  Thu Mar 30 17:16:56 CEST 2023
 * @brief This module provides an interface to the data interface and other functions
             for the received CAN messages
 * @copyright Futavis GmbH, Aachen 2023 - alle Rechte vorbehalten
 * @details Generated from file "lindeCAN.sym"
 * @par Global variables
 * @par changes
 * - first creation Thu Mar 30 17:16:56 CEST 2023
 */

#ifndef INTERFACELAYER_LINDECAN_FOLLOWUPRECEIVE_H_
#define INTERFACELAYER_LINDECAN_FOLLOWUPRECEIVE_H_

//******************* INCLUDES ********************************//
#include "stdint.h"


/**
 * @brief interface function for module_control CAN message
 * @details network management (NMT)
 * @param data Message data
 * @param msg CAN frame data (id, dlc, etc.)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_followUpmodule_control(const LINDE_MODULE_CONTROL_t* data, const CANMessage* msg);
/**
 * @brief interface function for Traction_SDOreq_LiIoBMS CAN message
 * @details SDO Rx, node 0x0D (LIB with Linde BMZ protocol)
 * @param data Message data
 * @param msg CAN frame data (id, dlc, etc.)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_followUpTraction_SDOreq_LiIoBMS(const LINDE_TRACTION_SDOREQ_LIIOBMS_t* data, const CANMessage* msg);
/**
 * @brief interface function for Traction_PDO4 CAN message
 * @details PDO 4 (Tx), node 0x01 (KMC) (for LIB with Linde BMZ protocol)
 * @param data Message data
 * @param msg CAN frame data (id, dlc, etc.)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_followUpTraction_PDO4(const LINDE_TRACTION_PDO4_t* data, const CANMessage* msg);
/**
 * @brief interface function for TimeStamp CAN message
 * @details Linde proprietary timestamp message (for LIB with Linde BMZ protocol)
 * @param data Message data
 * @param msg CAN frame data (id, dlc, etc.)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_followUpTimeStamp(const LINDE_TIMESTAMP_t* data, const CANMessage* msg);
/**
 * @brief interface function for SYNC CAN message
 * @details CANopen SYNC message (for LIB with Linde BMZ protocol)
 * @param data Message data
 * @param msg CAN frame data (id, dlc, etc.)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_followUpSYNC(const LINDE_SYNC_t* data, const CANMessage* msg);
/**
 * @brief interface function for LiIoCharger_SDOreq_LiIoBMS CAN message
 * @details SDO Rx, node 0x5D (LIB with Linde BMZ protocol), SDO clients: OBC, EXC
 * @param data Message data
 * @param msg CAN frame data (id, dlc, etc.)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_followUpLiIoCharger_SDOreq_LiIoBMS(const LINDE_LIIOCHARGER_SDOREQ_LIIOBMS_t* data, const CANMessage* msg);
/**
 * @brief interface function for LiIoCharger_PDO1 CAN message
 * @details PDO 1 (Tx), node 0x5D (OBC, EXC)
 * @param data Message data
 * @param msg CAN frame data (id, dlc, etc.)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_followUpLiIoCharger_PDO1(const LINDE_LIIOCHARGER_PDO1_t* data, const CANMessage* msg);


#endif /* INTERFACELAYER_LINDECAN_FOLLOWUPRECEIVE_H_ */
