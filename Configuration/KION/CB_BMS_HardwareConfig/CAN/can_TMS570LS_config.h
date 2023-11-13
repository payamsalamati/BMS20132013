/**
 * @file     can_TMS570LS_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

#pragma once

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC TYPEDEFS ********************************/
//***************************************************************************/

#define CAN_TMS570LS_MAX_NODE_DELAY_TIME         0.000000100  // s
#define CAN_TMS570LS_INFORMATION_PROCESSING_TIME 0.000000100  // s

#define CAN_TMS570LS_CTL_REGISTER 0x00021643

#define CAN_TMS570LS_NODE_TIOC_REGISTER 0x4000Eu

#define CAN_TMS570LS_NODE_RIOC_REGISTER 0x40008u

#define CAN_TMS570LS_LEVEL_RX_OK 0x10u
#define CAN_TMS570LS_LEVEL_TX_OK 0x08u

#if SYSTEM_FREQUENCY == 180
#define CAN_BIT_TIMING_REGISTER_125KBAUT  (uint32_t)(0x00012399)
#define CAN_BIT_TIMING_REGISTER_250KBAUT  (uint32_t)(0x000036DD)
#define CAN_BIT_TIMING_REGISTER_500KBAUT  (uint32_t)(0x0000278E)
#define CAN_BIT_TIMING_REGISTER_1000KBAUT (uint32_t)(0x00000708)
#elif SYSTEM_FREQUENCY == 120
#define CAN_BIT_TIMING_REGISTER_125KBAUT  (uint32_t)(0x5A9Au)
#define CAN_BIT_TIMING_REGISTER_250KBAUT  (uint32_t)(0x594Du)
#define CAN_BIT_TIMING_REGISTER_500KBAUT  (uint32_t)(0x2789u)
#define CAN_BIT_TIMING_REGISTER_1000KBAUT (uint32_t)(0x0705u)
#else
#warning "baudrate not configured"
#endif

#define CAN_TMS570LS_IFxCMD_CONFIG_INTERN_OBJ 0xF8

#define CAN_TMS570LS_IFxMCTL_CONFIG_INTERN_OBJ_RECEIVE  (uint32_t)0x00001408U
#define CAN_TMS570LS_IFxMCTL_CONFIG_INTERN_OBJ_TRANSMIT (uint32_t)0x00001808U
//***************************************************************************/
//************************** PUBLIC VARIABLE DEFINITIONS ********************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DECLARATIONS *******************/
//***************************************************************************/
