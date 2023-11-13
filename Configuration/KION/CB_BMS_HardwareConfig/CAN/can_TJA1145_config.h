/**
 * @file     can_TJA1145_config_default.h
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

#include <stdint.h>

//***************************************************************************/
//************************** PUBLIC TYPEDEFS ********************************/
//***************************************************************************/

// System Event Capture Configuration
#define CAN_TJA1145_SYSTEM_EVENT_CAPTURE_ENABLE_OTWE_CONFIG  0b0u  // Enable / Disable Overtemperature Warning
#define CAN_TJA1145_SYSTEM_EVENT_CAPTURE_ENABLE_SPIFE_CONFIG 0b0u  // Enable / Disable SPI Failure detection
#define CAN_TJA1145_SYSTEM_EVENT_CAPTURE_ENABLE_CONFIG       (uint8_t)((CAN_TJA1145_SYSTEM_EVENT_CAPTURE_ENABLE_OTWE_CONFIG << CAN_TJA1145_SYSTEM_EVENT_ENABLE_OTWE_POS) | (CAN_TJA1145_SYSTEM_EVENT_CAPTURE_ENABLE_SPIFE_CONFIG << CAN_TJA1145_SYSTEM_EVENT_ENABLE_SPIFE_POS))

// Transceiver event capture enable register Configuration (address 23h)
#define CAN_TJA1145_TRANSCEIVER_EVENT_CAPTURE_ENABLE_CBSE_CONFIG 0b0u  // CAN-bus silence detection Enable / Disable
#define CAN_TJA1145_TRANSCEIVER_EVENT_CAPTURE_ENABLE_CFE_CONFIG  0b0u  // CAN failure detection Enable / Disable
#define CAN_TJA1145_TRANSCEIVER_EVENT_CAPTURE_ENABLE_CWE_CONFIG  0b1u  // CAN wake-up detection Enable / Disable
#define CAN_TJA1145_TRANSCEIVER_EVENT_CAPTURE_ENABLE_CONFIG      (uint8_t)((CAN_TJA1145_TRANSCEIVER_EVENT_CAPTURE_ENABLE_CBSE_CONFIG << CAN_TJA1145_TRANSCEIVER_EVENT_ENABLE_CBSE_POS) | (CAN_TJA1145_TRANSCEIVER_EVENT_CAPTURE_ENABLE_CFE_CONFIG << CAN_TJA1145_TRANSCEIVER_EVENT_ENABLE_CFE_POS) | (CAN_TJA1145_TRANSCEIVER_EVENT_CAPTURE_ENABLE_CWE_CONFIG << CAN_TJA1145_TRANSCEIVER_EVENT_ENABLE_CWE_POS))

// WAKE pin event capture enable register Configuration (address 4Ch)
#define CAN_TJA1145_WAKE_PIN_EVENT_CAPTURE_ENABLE_WPRE_CONFIG 0b0u  // Enable / Disable wake-pin rising detection
#define CAN_TJA1145_WAKE_PIN_EVENT_CAPTURE_ENABLE_WPFE_CONFIG 0b0u  // Enable / Disable wake-pin falling detection
#define CAN_TJA1145_WAKE_PIN_EVENT_CAPTURE_ENABLE_CONFIG      (uint8_t)((CAN_TJA1145_WAKE_PIN_EVENT_CAPTURE_ENABLE_WPRE_CONFIG << CAN_TJA1145_WAKE_PIN_ENABLE_WPRE_POS) | (CAN_TJA1145_WAKE_PIN_EVENT_CAPTURE_ENABLE_WPFE_CONFIG << CAN_TJA1145_WAKE_PIN_ENABLE_WPFE_POS))

// Can Control Configuration
#define CAN_TJA1145_CAN_CONTROL_CFDC_CONFIG  0b0u   // Enable / Disable CAN FD Tolerance
#define CAN_TJA1145_CAN_CONTROL_PNCOK_CONFIG 0b0u   // CAN partial networking configuration
#define CAN_TJA1145_CAN_CONTROL_CPNC_CONFIG  0b0u   // Enable / Disable CAN selective wake-up
#define CAN_TJA1145_CAN_CONTROL_CMC_CONFIG   0b01u  // CAN Tranceiver Operation Mode (00 = Offline, 01: Active Mode VCC 90% undervoltage detection active, 10: Active Mode No undervoltage detection, 11: Listen Only Mode)
#define CAN_TJA1145_CAN_CONTROL_CONFIG       (uint8_t)((CAN_TJA1145_CAN_CONTROL_CFDC_CONFIG << CAN_TJA1145_CAN_CONTROL_CFDC_POS) | (CAN_TJA1145_CAN_CONTROL_PNCOK_CONFIG << CAN_TJA1145_CAN_CONTROL_PNCOK_POS) | (CAN_TJA1145_CAN_CONTROL_CPNC_CONFIG << CAN_TJA1145_CAN_CONTROL_CPNC_POS) | (CAN_TJA1145_CAN_CONTROL_CMC_CONFIG << CAN_TJA1145_CAN_CONTROL_CMC_POS))

// Lock control Configuration
#define CAN_TJA1145_LOCK_CONTROL_LK6C_CONFIG 0b0u  // Enable / Disable write protection for address area 0x68 to 0x6F
#define CAN_TJA1145_LOCK_CONTROL_LK5C_CONFIG 0b0u  // Enable / Disable write protection for address area 0x50 to 0x5F
#define CAN_TJA1145_LOCK_CONTROL_LK4C_CONFIG 0b0u  // Enable / Disable write protection for address area 0x40 to 0x4F
#define CAN_TJA1145_LOCK_CONTROL_LK3C_CONFIG 0b0u  // Enable / Disable write protection for address area 0x30 to 0x3F
#define CAN_TJA1145_LOCK_CONTROL_LK2C_CONFIG 0b0u  // Enable / Disable write protection for address area 0x20 to 0x2F
#define CAN_TJA1145_LOCK_CONTROL_LK1C_CONFIG 0b0u  // Enable / Disable write protection for address area 0x10 to 0x1F
#define CAN_TJA1145_LOCK_CONTROL_LK0C_CONFIG 0b0u  // Enable / Disable write protection for address area 0x06 to 0x09
#define CAN_TJA1145_LOCK_CONTROL_CONFIG      (uint8_t)((CAN_TJA1145_LOCK_CONTROL_LK6C_CONFIG << CAN_TJA1145_LOCK_CONTROL_LK6C_POS) | (CAN_TJA1145_LOCK_CONTROL_LK5C_CONFIG << CAN_TJA1145_LOCK_CONTROL_LK5C_POS) | (CAN_TJA1145_LOCK_CONTROL_LK4C_CONFIG << CAN_TJA1145_LOCK_CONTROL_LK4C_POS) | (CAN_TJA1145_LOCK_CONTROL_LK3C_CONFIG << CAN_TJA1145_LOCK_CONTROL_LK3C_POS) | (CAN_TJA1145_LOCK_CONTROL_LK2C_CONFIG << CAN_TJA1145_LOCK_CONTROL_LK2C_POS) | (CAN_TJA1145_LOCK_CONTROL_LK1C_CONFIG << CAN_TJA1145_LOCK_CONTROL_LK1C_POS) | (CAN_TJA1145_LOCK_CONTROL_LK0C_CONFIG << CAN_TJA1145_LOCK_CONTROL_LK0C_POS))

// Data Rate Configuration
#define CAN_TJA1145_DATA_RATE_CONFIG 0b101  // CAN Data Rate selection

// Mode Control Configuration
#define CAN_TJA1145_MODE_CONTROL_CONFIG 0b111  // operating mode of the tranceiver (001: sleep mode, 100: standby mode, 111: normal mode)

// Reset System Event Status Register Configuration (address 61h)
#define CAN_TJA1145_SYSTEM_EVENT_STATUS_RESET_VALUE 0x00u

//***************************************************************************/
//************************** PUBLIC VARIABLE DEFINITIONS ********************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DECLARATIONS *******************/
//***************************************************************************/
