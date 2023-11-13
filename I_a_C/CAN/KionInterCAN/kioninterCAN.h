/**
 *
 * @file kioninterCAN.h
 * @created on Wed Feb 19 10:47:50 CET 2020
 * @brief This module writes an interrupt to process the CAN messages
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

#pragma once

//******************* INCLUDES ********************************//

#include "kioninterCAN_config.h"
#include "kioninterCAN_sendReceive.h"
#include "kioninterCAN_prepareSend.h"
#include "kioninterCAN_followUpReceive.h"
#include "task_cfg.h"
#include "dem.h"
#include "canIf.h"

//******************* TYPEDEFS ********************************//


//******************* FUNCTION DECLARATIONS ********************************//
uint8_t kionInterCAN_getTrySendHeartBeatCounter();
/**
 * @brief Main function of this modul. Depending on the messageID this
 *			function processes the received CAN messages
 * @details
 * @par Global variable
 */
void kioninterCAN_receive(CANMessage* msg);
/**
 * @brief initializes the CAN bus node and the receive message
 * @details
 * @par Global variables
 */
void kioninterCAN_config(void);

/**
 * @brief config function for sending CAN message
 */
void kioninterCAN_configSend(uint8_t masterId);
/**
 * @brief	: This function writes received messages into the canMessageQueue
 * @details
 * @par Global variables
 */
extern void kioninterCAN_receiveInterrupt(CANMessageObject msgObj);

/**
 * @brief  Set semaphore after a CAN TX interrupt.
 * @details
 * @par
 */
extern void kioninterCAN_transmitISRHandler(CANMessageObject msgObj);

/**
 * @brief Diagnosis of the CAN interface
 * @details
 * @par Global variables
 */
extern void kioninterCAN_alertInterrupt(CAN_STATUS status);

uint16_t kioninterCAN_getMissingAckErrorCounter(void);

/**
 * @brief
 * @details
 * @par Global variables
 */
void kioninterCAN_reset(void);

/**
 * @brief get function for BMS_CPS_PDO_TX1RollingCounter
 * @details
 * @par Global variables
 */
uint8_t kioninterCAN_getBMS_CPS_PDO_TX1RollingCounter(void);

/**
 * @brief send function for BMS_CPS_UDS_REQ
 * @details
 * @par Global variables
 */
void kioninterCAN_sendBMS_CPS_UDS_REQ(const CANMessage* msg);

/**
 * @brief send function for BMS_CPS_PDO_TX3
 * @details
 * @par Global variables
 */
void kioninterCAN_sendBMS_CPS_PDO_TX3(void);

/**
 * @brief send function for BMS_CPS_PDO_TX2
 * @details
 * @par Global variables
 */
void kioninterCAN_sendBMS_CPS_PDO_TX2(void);

/**
 * @brief send function for BMS_Heartbeat
 * @details
 * @par Global variables
 */
void kioninterCAN_sendBMS_Heartbeat(void);

/**
 * @brief send function for BMS_TimeStamp
 * @details
 * @par Global variables
 */
void kioninterCAN_sendBMS_TimeStamp(void);

/**
 * @brief send function for BMS_CPS_SDO_REQ
 * @details
 * @par Global variables
 */
void kioninterCAN_sendBMS_CPS_SDO_REQ(void);

/**
 * @brief send function for BMS_ModuleCotrol
 * @details
 * @par Global variables
 */
void kioninterCAN_sendBMS_ModuleCotrol(void);

/**
 * @brief send function for BMS_CPS_PDO_TX1
 * @details
 * @par Global variables
 */
void kioninterCAN_sendBMS_CPS_PDO_TX1(void);

/**
 * @brief send function for BMS_ICDA_Request
 * @details
 * @par Global variables
 */
void kioninterCAN_sendBMS_ICDA_Request(const uint8_t* data);

/**
 * @brief send function for CPS_BMS_UDS_RESP
 * @details
 * @par Global variables
 */
void kioninterCAN_sendCPS_BMS_UDS_RESP();

/**
 * @brief send function for CH_CPS_WakeUp
 * @details
 * @par Global variables
 */
void kioninterCAN_sendCH_CPS_WakeUp(void);

/**
 * @brief send function for CPS_VEHICLE_UDS_RESP
 * @details
 * @par Global variables
 */
void kioninterCAN_sendCPS_VEHICLE_UDS_RESP(void);

/**
 * @brief send function for CPS_BMS_Emergency
 * @details
 * @par Global variables
 */
void kioninterCAN_sendCPS_BMS_Emergency(void);

/**
 * @brief send function for CPS_Heartbeat
 * @details
 * @par Global variables
 */
void kioninterCAN_sendCPS_Heartbeat(void);

/**
 * @brief send function for CPS_BMS_SDO_RESP
 * @details
 * @par Global variables
 */
void kioninterCAN_sendCPS_BMS_SDO_RESP(void);

/**
 * @brief send function for CPS_BMS_PDO_TX2
 * @details
 * @par Global variables
 */
void kioninterCAN_sendCPS_BMS_PDO_TX2(void);

/**
 * @brief send function for CPS_BMS_PDO_TX3
 * @details
 * @par Global variables
 */
void kioninterCAN_sendCPS_BMS_PDO_TX3(void);

/**
 * @brief send function for CPS_BMS_PDO_TX1
 * @details
 * @par Global variables
 */
void kioninterCAN_sendCPS_BMS_PDO_TX1(void);

/**
 * @brief send function for ICDA_BMS_Result
 * @details
 * @par Global variables
 */
void kioninterCAN_sendICDA_BMS_Result(void);

/**
 * @brief send function for ICDA_BMS_Response
 * @details
 * @par Global variables
 */
void kioninterCAN_sendICDA_BMS_Response(void);

/**
 * @brief send function for all 100ms messages kioninter project
 * @details send CAN messages each 100ms
 */
void kioninterCANSendInterleaved(void);

/**
 * @brief send function for all 40ms messages kioninter project
 * @details send CAN messages each 40ms
 */
void kioninterCANSend40(void);

/**
 * @brief send function for all 10ms messages kioninter project
 * @details send CAN messages each 10ms
 */
void kioninterCANSend10(void);

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
void kioninterCAN_sendStrPM_SyM_Val1(void);
#endif
