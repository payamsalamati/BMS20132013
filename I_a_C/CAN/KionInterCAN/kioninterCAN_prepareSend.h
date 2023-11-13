/**
 *
 * @file kioninterCAN_prepareSend.h
 *
 * @created on Mon Nov 16 10:15:18 CET 2020
 * @brief This module write data from the data interface into the
             CAN messages
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

#pragma once

//******************* INCLUDES ********************************//
#include <stdint.h>


/**
 * @brief prepare the BMS_CPS_PDO_TX3 CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_prepareBMS_CPS_PDO_TX3(KIONINTER_BMS_CPS_PDO_TX3_t* kioninter_bms_cps_pdo_tx3);

/**
 * @brief prepare the BMS_CPS_PDO_TX2 CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_prepareBMS_CPS_PDO_TX2(KIONINTER_BMS_CPS_PDO_TX2_t* kioninter_bms_cps_pdo_tx2);

/**
 * @brief prepare the BMS_Heartbeat CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_prepareBMS_Heartbeat(KIONINTER_BMS_HEARTBEAT_t* kioninter_bms_heartbeat);

/**
 * @brief prepare the BMS_TimeStamp CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_prepareBMS_TimeStamp(KIONINTER_BMS_TIMESTAMP_t* kioninter_bms_timestamp);

/**
 * @brief prepare the BMS_CPS_SDO_REQ CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_prepareBMS_CPS_SDO_REQ(KIONINTER_BMS_CPS_SDO_REQ_t* kioninter_bms_cps_sdo_req);

/**
 * @brief prepare the BMS_ModuleCotrol CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_prepareBMS_ModuleCotrol(KIONINTER_BMS_MODULECOTROL_t* kioninter_bms_modulecotrol);

/**
 * @brief prepare the BMS_CPS_PDO_TX1 CAN message
 * @details
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_prepareBMS_CPS_PDO_TX1(KIONINTER_BMS_CPS_PDO_TX1_t* kioninter_bms_cps_pdo_tx1);

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
/**
 * @brief	: prepare the StrPM_SyM_Val1 CAN message
 * @detailsValues from Pack and String Master
 * @par Global variables
 */
__attribute__((weak)) void kioninterCAN_prepareStrPM_SyM_Val1(KIONSTRPM_SYM_VAL1_t* kioninter_strpm_sym_val1_t);
#endif
