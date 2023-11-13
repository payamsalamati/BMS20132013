/**
 *
 * @file kionCAN_prepareSend.h
 *
 * @created on Tue Feb 16 14:15:58 CET 2021
 * @brief This module write data from the data interface into the
             CAN messages
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

#pragma once

//******************* INCLUDES ********************************//
#include <stdint.h>

/**
 * @brief prepare the lib_uds CAN message
 * @details UDS responses from LIB with KION protocol
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_uds(KION_LIB_UDS_t* kion_lib_uds);

/**
 * @brief prepare the lib_sdo_tx CAN message
 * @details SDO Tx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_sdo_tx(KION_LIB_SDO_TX_t* kion_lib_sdo_tx);

/**
 * @brief prepare the lib_pdo_tx8 CAN message
 * @details PDO 8 (Tx), node 0x77 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_pdo_tx8(KION_LIB_PDO_TX8_t* kion_lib_pdo_tx8);

/**
 * @brief prepare the lib_pdo_tx7 CAN message
 * @details PDO 7 (Tx), node 0x77 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_pdo_tx7(KION_LIB_PDO_TX7_t* kion_lib_pdo_tx7);

/**
 * @brief prepare the lib_pdo_tx6 CAN message
 * @details PDO 6 (Tx), node 0x77 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_pdo_tx6(KION_LIB_PDO_TX6_t* kion_lib_pdo_tx6);

/**
 * @brief prepare the lib_pdo_tx5 CAN message
 * @details PDO 5 (Tx), node 0x77 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_pdo_tx5(KION_LIB_PDO_TX5_t* kion_lib_pdo_tx5);

/**
 * @brief prepare the lib_pdo_tx4 CAN message
 * @details PDO 4 (Tx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_pdo_tx4(KION_LIB_PDO_TX4_t* kion_lib_pdo_tx4);

/**
 * @brief prepare the lib_pdo_tx3 CAN message
 * @details PDO 3 (Tx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_pdo_tx3(KION_LIB_PDO_TX3_t* kion_lib_pdo_tx3);

/**
 * @brief prepare the lib_pdo_tx2 CAN message
 * @details PDO 2 (Tx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_pdo_tx2(KION_LIB_PDO_TX2_t* kion_lib_pdo_tx2);

/**
 * @brief prepare the lib_pdo_tx1 CAN message
 * @details PDO 1 (Tx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_pdo_tx1(KION_LIB_PDO_TX1_t* kion_lib_pdo_tx1);

/**
 * @brief prepare the lib_heartbeat CAN message
 * @details heartbeat (NMT error control), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_heartbeat(KION_LIB_HEARTBEAT_t* kion_lib_heartbeat);

/**
 * @brief prepare the lib_emergency CAN message
 * @details emergency (EMCY), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_preparelib_emergency(KION_LIB_EMERGENCY_t* kion_lib_emergency);

/**
 * @brief prepare the HeartbtBms CAN message
 * @details Network Management, Error Control, Battery management system Heartbeat
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_prepareHeartbtBms(KION_HEARTBTBMS_t* kion_heartbtbms);

/**
 * @brief prepare the DiagRespBms CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_prepareDiagRespBms(KION_DIAGRESPBMS_t* kion_diagrespbms);

/**
 * @brief prepare the BmsSDOtx CAN message
 * @details CAN Open: Data for Service data object (SDO) send by BMS
 * @par Global variables
 */
__attribute__((weak)) void kionCAN_prepareBmsSDOtx(KION_BMSSDOTX_t* kion_bmssdotx);

#if defined(SW_RESET_ANALYSIS_CAN_DATA)
__attribute__((weak)) void kionCAN_prepareTaskMaxTimes(KION_MAXTASKTIMES_t* kion_maxTasktimes);
__attribute__((weak)) void kionCAN_prepareTaskCurrentTimes(KION_CURRENTTASKTIMES_t* kion_currentTasktimes);
__attribute__((weak)) void kionCAN_prepareSBCStatus(KION_SBCSTATUS_t* kion_sbcStatus);
#endif

__attribute__((weak)) void kionCAN_preparedebugValues1(KION_DEBUGVALUES1_t* kion_debugvalues1);
