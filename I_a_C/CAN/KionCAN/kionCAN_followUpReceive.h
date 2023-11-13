/**
 *
 * @file kionCAN_followUpReceive.h
 * @created on  Tue Feb 16 14:15:58 CET 2021
 * @brief This module provides an interface to the data interface and other functions
             for the received CAN messages
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

#pragma once

//******************* INCLUDES ********************************//

#include <stdint.h>

/**
 * @brief interface function for dtu_uds CAN message
 * @details UDS requests from DTU
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUpdtu_uds(const KION_DTU_UDS_t* data, const CANMessage* msg);
/**
 * @brief interface function for time CAN message
 * @details time stamp (TIME)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUptime(const KION_TIME_t* data, const CANMessage* msg);
/**
 * @brief interface function for obc_heartbeat CAN message
 * @details heartbeat (NMT error control), node 0x51 (OBC)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUpobc_heartbeat(const KION_OBC_HEARTBEAT_t* data, const CANMessage* msg);
/**
 * @brief interface function for module_control CAN message
 * @details network management (NMT)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUpmodule_control(const KION_MODULE_CONTROL_t* data, const CANMessage* msg);
/**
 * @brief interface function for lib_sdo_rx CAN message
 * @details SDO Rx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUplib_sdo_rx(const KION_LIB_SDO_RX_t* data, const CANMessage* msg);
/**
 * @brief interface function for lib_pdo_rx4 CAN message
 * @details PDO 4 (Rx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUplib_pdo_rx4(const KION_LIB_PDO_RX4_t* data, const CANMessage* msg);
/**
 * @brief interface function for lib_pdo_rx1 CAN message
 * @details PDO 1 (Rx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUplib_pdo_rx1(const KION_LIB_PDO_RX1_t* data, const CANMessage* msg);
/**
 * @brief interface function for kmc_heartbeat CAN message
 * @details heartbeat (NMT error control), node 0x01 (KMC)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUpKmc_heartbeat(const KION_KMC_HEARTBEAT_t* data, const CANMessage* msg);
/**
 * @brief interface function for exc_heartbeat CAN message
 * @details heartbeat (NMT error control), node 0x4A (EXC)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUpexc_heartbeat(const KION_EXC_HEARTBEAT_t* data, const CANMessage* msg);
/**
 * @brief interface function for TimeStamp CAN message
 * @details Linde proprietary timestamp message (for LIB with Linde SAFT protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUpTimeStamp(const KION_TIMESTAMP_t* data, const CANMessage* msg);
/**
 * @brief interface function for SYNC CAN message
 * @details CANopen SYNC message (for LIB with Linde BMZ protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUpSYNC(const KION_SYNC_t* data, const CANMessage* msg);
/**
 * @brief interface function for HeartbtLiionCharger CAN message
 * @details Network Management, Error Control,  liion battery charger Heartbeat
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUpHeartbtLiionCharger(const KION_HEARTBTLIIONCHARGER_t* data, const CANMessage* msg);
/**
 * @brief interface function for DiagReqBms CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUpDiagReqBms(const KION_DIAGREQBMS_t* data, const CANMessage* msg);
/**
 * @brief interface function for BmsSDOrx CAN message
 * @details CAN Open: Service data object (SDO) send by KWPC
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUpBmsSDOrx(const CANMessage* msg);

#if defined(EMV_TEST) || defined(HIL_CONFIGURATION)
/**
 * @brief interface function for debug control variables
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_followUpDebugControl(const CANMessage* msg);
#endif
