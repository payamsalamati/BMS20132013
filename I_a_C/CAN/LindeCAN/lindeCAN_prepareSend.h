/**
 *
 * @file lindeCAN_prepareSend.h
 * @modulenumber 0x0D
 *
 * @author Generated File with DPCParser release-1.3.4 Commit 1347995
 * @created on Thu Mar 30 17:16:56 CEST 2023
 * @brief This module write data from the data interface into the
             CAN messages
 * @copyright Futavis GmbH, Aachen 2023 - alle Rechte vorbehalten
 * @details Generated from file "lindeCAN.sym"
 * @par Global variables
 * @par changes
 * - first creation Thu Mar 30 17:16:56 CEST 2023
 */

#ifndef INTERFACELAYER_LINDECAN_PREPARESEND_H_
#define INTERFACELAYER_LINDECAN_PREPARESEND_H_

//******************* INCLUDES ********************************//
#include "stdint.h"


/**
 * @brief prepare the LiIoBMS_SDOresp_Traction CAN message
 * @details SDO Tx, node 0x0D (LIB with Linde BMZ protocol), SDO client: KMC
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_prepareLiIoBMS_SDOresp_Traction(LINDE_LIIOBMS_SDORESP_TRACTION_t* linde_liiobms_sdoresp_traction);

/**
 * @brief prepare the LiIoBMS_SDOresp_LiIoCharger CAN message
 * @details SDO Tx, node 0x5D (LIB with Linde BMZ protocol), SDO client: OBC, EXC
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_prepareLiIoBMS_SDOresp_LiIoCharger(LINDE_LIIOBMS_SDORESP_LIIOCHARGER_t* linde_liiobms_sdoresp_liiocharger);

/**
 * @brief prepare the LiIoBMS_PDO5 CAN message
 * @details PDO5 (Tx), node 0x01 (LIB with Linde BMZ prototol)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_prepareLiIoBMS_PDO5(LINDE_LIIOBMS_PDO5_t* linde_liiobms_pdo5);

/**
 * @brief prepare the LiIoBMS_PDO4 CAN message
 * @details PDO4 (Tx), node 0x0D (LIB with Linde BMZ prototol)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_prepareLiIoBMS_PDO4(LINDE_LIIOBMS_PDO4_t* linde_liiobms_pdo4);

/**
 * @brief prepare the LiIoBMS_PDO3 CAN message
 * @details PDO3 (Tx), node 0x0D (LIB with Linde BMZ prototol)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_prepareLiIoBMS_PDO3(LINDE_LIIOBMS_PDO3_t* linde_liiobms_pdo3);

/**
 * @brief prepare the LiIoBMS_PDO2 CAN message
 * @details PDO2 (Tx), node 0x0D (LIB with Linde BMZ prototol)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_prepareLiIoBMS_PDO2(LINDE_LIIOBMS_PDO2_t* linde_liiobms_pdo2);

/**
 * @brief prepare the LiIoBMS_PDO1 CAN message
 * @details PDO1 (Tx), node 0x0D (LIB with Linde BMZ protocol)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_prepareLiIoBMS_PDO1(LINDE_LIIOBMS_PDO1_t* linde_liiobms_pdo1);

/**
 * @brief prepare the LiIoBMS_Heartbeat CAN message
 * @details heartbeat (NMT error control), node 0x0D (LIB with Linde BMZ protocol)
 * @par Global variables
 */
__attribute__((weak)) void lindeCAN_prepareLiIoBMS_Heartbeat(LINDE_LIIOBMS_HEARTBEAT_t* linde_liiobms_heartbeat);


#endif /* INTERFACELAYER_LINDECAN_PREPARESEND_H_ */
