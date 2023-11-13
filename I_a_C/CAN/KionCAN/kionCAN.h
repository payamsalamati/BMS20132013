/**
 *
 * @file kionCAN.h
 * @created on Tue Feb 16 14:15:58 CET 2021
 * @brief This module writes an interrupt to process the CAN messages
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

#pragma once

//******************* INCLUDES ********************************//

#include "kionCAN_config.h"
#include "kionCAN_sendReceive.h"
#include "kionCAN_prepareSend.h"
#include "kionCAN_followUpReceive.h"
#include "task_cfg.h"
#include "dem.h"
#include "mutexMonitor.h"

//******************* TYPEDEFS ********************************//


//******************* FUNCTION DECLARATIONS ********************************//
/**
 * @brief Main function of this modul. Depending on the messageID this
 *			function processes the received CAN messages
 * @details
 * @par Global variable
 */
void kionCAN_receive(const CANMessage* msg);
/**
 * @brief initializes the CAN bus node and the receive message
 * @details
 * @par Global variables
 */
void kionCAN_config(void);

/**
 * @brief config function for sending CAN message
 */
void kionCAN_configSend(void);
/**
 * @brief	: This function writes received messages into the canMessageQueue
 * @details
 * @par Global variables
 */
extern void kionCAN_receiveInterrupt(CANMessageObject msgObj);

/**
 * @brief  Set semaphore after a CAN TX interrupt.
 * @details
 * @par
 */
extern void kionCAN_transmitISRHandler(CANMessageObject msgObj);

/**
 * @brief Diagnosis of the CAN interface
 * @details
 * @par Global variables
 */
extern void kionCAN_alertInterrupt(CAN_STATUS status);

uint16_t kionCAN_getMissingAckErrorCounter(void);


/**
 * @brief get function for lib_pdo_tx7_message_counter
 * @details
 * @par Global variables
 */
uint8_t kionCAN_getLib_pdo_tx7_message_counter(void);

/**
 * @brief reset function for lib_pdo_tx7_message_counter
 * @details
 * @par Global variables
 */
void kionCAN_resetLib_pdo_tx7_message_counter(void);

/**
 * @brief send function for debugDTC
 * @details
 * @par Global variables
 */
void kionCAN_sendDebugDTC(DTC dtc, DEM_Severity severity);

/**
 * @brief send function for lib_uds
 * @details UDS responses from LIB with KION protocol
 * @par Global variables
 */
void kionCAN_sendLib_uds(const CANMessage* msg);

/**
 * @brief send function for lib_sdo_tx
 * @details SDO Tx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC
 * @par Global variables
 */
void kionCAN_sendLib_sdo_tx(const CANMessage* msg);

/**
 * @brief send function for lib_pdo_tx8
 * @details PDO 8 (Tx), node 0x77 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_pdo_tx8(void);

/**
 * @brief send function for lib_pdo_tx7
 * @details PDO 7 (Tx), node 0x77 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_pdo_tx7(void);

/**
 * @brief send function for lib_pdo_tx6
 * @details PDO 6 (Tx), node 0x77 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_pdo_tx6(void);

/**
 * @brief send function for lib_pdo_tx5
 * @details PDO 5 (Tx), node 0x77 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_pdo_tx5(void);

/**
 * @brief send function for lib_pdo_tx4
 * @details PDO 4 (Tx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_pdo_tx4(void);

/**
 * @brief send function for lib_pdo_tx3
 * @details PDO 3 (Tx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_pdo_tx3(void);

/**
 * @brief send function for lib_pdo_tx2
 * @details PDO 2 (Tx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_pdo_tx2(void);

/**
 * @brief send function for lib_pdo_tx1
 * @details PDO 1 (Tx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_pdo_tx1(void);

/**
 * @brief send function for lib_heartbeat
 * @details heartbeat (NMT error control), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_heartbeat(void);

/**
 * @brief send function for lib_emergency
 * @details emergency (EMCY), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_emergency(const uint8_t* emcyData);

/**
 * @brief send function for cps_uds
 * @details UDS responses from CPS in LIB with KION protocol
 * @par Global variables
 */
void kionCAN_sendCps_uds(const CANMessage* msg);

/**
 * @brief send function for DiagRespBms
 * @details
 * @par Global variables
 */
void kionCAN_sendDiagRespBms(void);

/**
 * @brief send function for BmsSDOtx
 * @details CAN Open: Data for Service data object (SDO) send by BMS
 * @par Global variables
 */
void kionCAN_sendBmsSDOtx(const CANMessage* msg);

/**
 * @brief send function for time
 * @details time stamp (TIME)
 * @par Global variables
 */
void kionCAN_sendTime(void);

/**
 * @brief send function for obc_heartbeat
 * @details heartbeat (NMT error control), node 0x51 (OBC)
 * @par Global variables
 */
void kionCAN_sendObc_heartbeat(void);

/**
 * @brief send function for module_control
 * @details network management (NMT)
 * @par Global variables
 */
void kionCAN_sendModule_control(void);

/**
 * @brief send function for lib_sdo_rx
 * @details SDO Rx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC
 * @par Global variables
 */
void kionCAN_sendLib_sdo_rx(void);

/**
 * @brief send function for lib_pdo_rx4
 * @details PDO 4 (Rx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_pdo_rx4(void);

/**
 * @brief send function for lib_pdo_rx1
 * @details PDO 1 (Rx), node 0x27 (LIB with KION protocol)
 * @par Global variables
 */
void kionCAN_sendLib_pdo_rx1(void);

/**
 * @brief send function for kwpc_heartbeat
 * @details heartbeat (NMT error control), node 0x01 (KWPC)
 * @par Global variables
 */
void kionCAN_sendKwpc_heartbeat(void);

/**
 * @brief send function for exc_heartbeat
 * @details heartbeat (NMT error control), node 0x4A (EXC)
 * @par Global variables
 */
void kionCAN_sendExc_heartbeat(void);

/**
 * @brief send function for TimeStamp
 * @details Linde proprietary timestamp message (for LIB with Linde SAFT protocol)
 * @par Global variables
 */
void kionCAN_sendTimeStamp(void);

/**
 * @brief send function for SYNC
 * @details CANopen SYNC message (for LIB with Linde BMZ protocol)
 * @par Global variables
 */
void kionCAN_sendSYNC(CANMessage* msg);

/**
 * @brief send function for HeartbtLiionCharger
 * @details Network Management, Error Control,  liion battery charger Heartbeat
 * @par Global variables
 */
void kionCAN_sendHeartbtLiionCharger(void);

/**
 * @brief send function for DiagReqBms
 * @details
 * @par Global variables
 */
void kionCAN_sendDiagReqBms(void);

/**
 * @brief send function for BmsSDOrx
 * @details CAN Open: Service data object (SDO) send by KWPC
 * @par Global variables
 */
void kionCAN_sendBmsSDOrx(void);

/**
 * @brief send function for EMCY message
 * @details send EMCY message every 10ms if one is avaiable
 */
void kionCAN_processEmcyMsg(void);

/**
 * @brief send function for all 100ms messages kion project
 * @details send CAN messages each 100ms
 */
void kionCANSend100(void);

/**
 * @brief send function for all 100ms messages kion project
 * @details send CAN messages each 100ms
 */
void kionCANSendInterleaved(void);

/**
 * @brief send function for all 1000ms messages kion project
 * @details send CAN messages each 1000ms
 */
void kionCANSend1000(void);

/**
 * @brief send function for kion heartbeat
 * @details send CAN messages each 40ms
 */
void kionCANSendHeartbeat(void);

/**
 * @brief send function for all 10ms messages kion project
 * @details send CAN messages each 10ms
 */
void kionCANSend10(void);

void kionCANSend40(void);

void kionCANSendDebug10(void);

void kionCAN_configBeforeProtocolSelection(void);

void kionCAN_configSendBeforeProtocolSelection(void);

void kionCAN_init(void);

#if defined(SW_RESET_ANALYSIS_CAN_DATA)
void kionCAN_sendTaskCurrentTimes(void);
void kionCAN_sendTaskMaxTimes(void);
void kionCAN_sendSBCStatus(uint8_t watchdogRefreshState, uint8_t idCounter);
void kionCAN_sendMutexPendFailedSignal(MutexAnalysisData pendingMutexAnalysis, uint8_t mutexPendingSource, uint8_t mutexRequestingSource, OSIf_Error error);
void kionCAN_sendMutexPostFailedSignal(uint8_t mutexPostSource, OSIf_Error error);
#endif
