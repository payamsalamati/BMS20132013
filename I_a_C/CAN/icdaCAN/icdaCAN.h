/**
 *
 * @file icdaCAN.h
 * @created on Wed Feb 19 10:47:50 CET 2020
 * @brief This module writes an interrupt to process the CAN messages
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

#pragma once

//******************* INCLUDES ********************************//

#include "icdaCAN_config.h"
#include "icdaCAN_sendReceive.h"
#include "icdaCAN_prepareSend.h"
#include "icdaCAN_followUpReceive.h"
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
void icdaCAN_receive(CANMessage* msg);

/**
 * @brief initializes the CAN bus node and the receive message
 * @details
 * @par Global variables
 */
void icdaCAN_config();

/**
 * @brief config function for sending CAN message
 */
void icdaCAN_configSend();

/**
 * @brief	: This function writes received messages into the canMessageQueue
 * @details
 * @par Global variables
 */
extern void icdaCAN_receiveInterrupt(CANMessageObject msgObj);

/**
 * @brief  Set semaphore after a CAN TX interrupt.
 * @details
 * @par
 */
extern void icdaCAN_transmitISRHandler(CANMessageObject msgObj);

/**
 * @brief Diagnosis of the CAN interface
 * @details
 * @par Global variables
 */
extern void icdaCAN_alertInterrupt(CAN_STATUS status);

/**
 * @brief
 * @details
 * @par Global variables
 */
void icdaCAN_reset(void);


/**
 * @brief send function for BMS_ICDA_Request
 * @details
 * @par Global variables
 */
void icdaCAN_sendBMS_ICDA_Request(void);

/**
 * @brief send function for ICDA_BMS_Result
 * @details
 * @par Global variables
 */
void icdaCAN_sendICDA_BMS_Result(void);

/**
 * @brief send function for ICDA_BMS_Response
 * @details
 * @par Global variables
 */
void icdaCAN_sendICDA_BMS_Response(void);
