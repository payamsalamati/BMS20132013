/**
 *
 * @file lindeCAN.h
 * @modulenumber 0x0D
 * @author Generated File with DPCParser release-1.3.4 Commit 1347995
 * @created on Thu Mar 30 17:16:56 CEST 2023
 * @brief This module writes an interrupt to process the CAN messages
 * @copyright Futavis GmbH, Aachen 2023 - alle Rechte vorbehalten
 * @details Generated from file "lindeCAN.sym"
 * @par Global variables
 * @par changes
 * - first creation Thu Mar 30 17:16:56 CEST 2023
 */

#ifndef INTERFACELAYER_LINDECAN_H_
#define INTERFACELAYER_LINDECAN_H_

//******************* INCLUDES ********************************//

#include "lindeCAN_config.h"
#include "lindeCAN_sendReceive.h"
#include "lindeCAN_prepareSend.h"
#include "lindeCAN_followUpReceive.h"
#include "task_cfg.h"
#include "dem.h"
#include "canIf.h"

//******************* TYPEDEFS ********************************//


//******************* FUNCTION DECLARATIONS ********************************//
/**
 * @brief Main function of this modul. Depending on the messageID this
 *			function processes the received CAN messages
 * @details
 * @par Global variable
 */
void lindeCAN_receive(const CANMessage* msg);
/**
 * @brief initializes the CAN bus node and the receive message
 * @details
 * @par Global variables
 */
void lindeCAN_config();

/**
 * @brief config function for sending CAN message
 */
void lindeCAN_configSend();
/**
 * @brief	: This function writes received messages into the canMessageQueue
 * @details
 * @par Global variables
 */
extern void lindeCAN_receiveInterrupt();

/**
 * @brief Diagnosis of the CAN interface
 * @details
 * @par Global variables
 */
extern void lindeCAN_alertInterrupt();

/**
 * @brief
 * @details
 * @par Global variables
 */
void lindeCAN_reset();

/**
 * @brief send function for LiIoBMS_SDOresp_Traction
 * @details SDO Tx, node 0x0D (LIB with Linde BMZ protocol), SDO client: KMC
 * @par Global variables
 */
void lindeCAN_sendLiIoBMS_SDOresp_Traction();

/**
 * @brief send function for LiIoBMS_SDOresp_LiIoCharger
 * @details SDO Tx, node 0x5D (LIB with Linde BMZ protocol), SDO client: OBC, EXC
 * @par Global variables
 */
void lindeCAN_sendLiIoBMS_SDOresp_LiIoCharger();

/**
 * @brief send function for LiIoBMS_PDO5
 * @details PDO5 (Tx), node 0x01 (LIB with Linde BMZ prototol)
 * @par Global variables
 */
void lindeCAN_sendLiIoBMS_PDO5();

/**
 * @brief send function for LiIoBMS_PDO4
 * @details PDO4 (Tx), node 0x0D (LIB with Linde BMZ prototol)
 * @par Global variables
 */
void lindeCAN_sendLiIoBMS_PDO4();

/**
 * @brief send function for LiIoBMS_PDO3
 * @details PDO3 (Tx), node 0x0D (LIB with Linde BMZ prototol)
 * @par Global variables
 */
void lindeCAN_sendLiIoBMS_PDO3();

/**
 * @brief send function for LiIoBMS_PDO2
 * @details PDO2 (Tx), node 0x0D (LIB with Linde BMZ prototol)
 * @par Global variables
 */
void lindeCAN_sendLiIoBMS_PDO2();

/**
 * @brief send function for LiIoBMS_PDO1
 * @details PDO1 (Tx), node 0x0D (LIB with Linde BMZ protocol)
 * @par Global variables
 */
void lindeCAN_sendLiIoBMS_PDO1();

/**
 * @brief send function for LiIoBMS_Heartbeat
 * @details heartbeat (NMT error control), node 0x0D (LIB with Linde BMZ protocol)
 * @par Global variables
 */
void lindeCAN_sendLiIoBMS_Heartbeat();

/**
 * @brief send function for module_control
 * @details network management (NMT)
 * @par Global variables
 */
void lindeCAN_sendModule_control();

/**
 * @brief send function for Traction_SDOreq_LiIoBMS
 * @details SDO Rx, node 0x0D (LIB with Linde BMZ protocol)
 * @par Global variables
 */
void lindeCAN_sendTraction_SDOreq_LiIoBMS();

/**
 * @brief send function for Traction_PDO4
 * @details PDO 4 (Tx), node 0x01 (KMC) (for LIB with Linde BMZ protocol)
 * @par Global variables
 */
void lindeCAN_sendTraction_PDO4();

/**
 * @brief send function for TimeStamp
 * @details Linde proprietary timestamp message (for LIB with Linde BMZ protocol)
 * @par Global variables
 */
void lindeCAN_sendTimeStamp();

/**
 * @brief send function for SYNC
 * @details CANopen SYNC message (for LIB with Linde BMZ protocol)
 * @param msg Message to send
 * @par Global variables
 */
void lindeCAN_sendSYNC(CANMessage* msg);

/**
 * @brief send function for LiIoCharger_SDOreq_LiIoBMS
 * @details SDO Rx, node 0x5D (LIB with Linde BMZ protocol), SDO clients: OBC, EXC
 * @par Global variables
 */
void lindeCAN_sendLiIoCharger_SDOreq_LiIoBMS();

/**
 * @brief send function for LiIoCharger_PDO1
 * @details PDO 1 (Tx), node 0x5D (OBC, EXC)
 * @par Global variables
 */
void lindeCAN_sendLiIoCharger_PDO1(void);

void lindeCANSend40(void);

void lindeCANSend10(void);

void lindeCAN_configBeforeProtocolSelection(void);

void lindeCAN_configSendBeforeProtocolSelection(void);

void lindeCAN_init(void);


#endif /* INTERFACELAYER_LINDECAN_H_ */
