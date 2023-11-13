/**
 * @file     afe_MC33771_C_config_default.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
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
#include "afe_MC33771_private.h"
#include "voltageMonitor_config.h"
#include "temperatureMonitor_config.h"
#include "safetyBalancing_config.h"
#include "config_enable.h"
#include "csc_config.h"
#include "afe_multibuffer_config.h"
//***************************************************************************/
//************************** PUBLIC TYPEDEFS ********************************/
//***************************************************************************/
#if defined(EMV_TEST)
#define BMS_CONFIG_ENABLE_AFE_TRAFFIC_REDUCTION
#define BALANCING_ALWAYS_ON CONFIG_DISABLED
#endif
// Define needed for 15s CSC version with 2 AFEs on ohne CSC
#define AFE_TWO_AFES_ON_ONE_CSC   CONFIG_ENABLED
#define AFE_NUMBER_OF_AFE_PER_CSC 2u

#define AFE_MC33771_TX_CHIP_SELECT_BITMASK SPI_CHIP_SELECT_1
#define AFE_MC33771_RX_CHIP_SELECT_BITMASK SPI_CHIP_SELECT_3


#define AFE_MAX_NUMBER_OF_CELLS 14u

/** If some GPIO that are configured as analog inputs are used to measure the same temperature of the
 * cells, then a congruence or plausibility check in the pack controller must be used as a safety
 * mechanism.*/
#define AFE_CHECK_TEMP_IMBALANCE CONFIG_DISABLED

#define AFE_INTERNAL_OV_UV_DETECTION DISABLED

#define AFE_V_STACK_THRE             3000  // V_stack_thre may be in the range of a few hundred mV. See V_VPWR_CT in data sheet
#define AFE_CELL_IMBALANCE_TH        200
#define AFE_BALANCING_RESISTOR_VALUE 19u

#define AFE_MC33771_CTx_UV_TH_diag            AFE_MC33771_CTx_UV_TH_HIGH
#define AFE_MC33771_CTx_OV_TH_diag            AFE_MC33771_CTx_UV_TH_HIGH
#define AFE_MC33771_OPEN_LOAD_DETECTION_VALUE AFE_MC33771_V_OL_Detect_HIGH
#define AFE_MC33771_VCELL_MIN                 2500.0  //[mV] according to data sheet

#define AFE_MC33771_Vleak_DIAG 27.0  // mV
#if((defined(DEBUG) && !defined(UNIT_TEST)) || defined(HIL_CONFIGURATION))
#define AFE_MC33771_DIAG_DV 465u  // mV
#else
#define AFE_MC33771_DIAG_DV 33u  // mV
#endif

#define AFE_OV CELL_VOLTAGE_MAX_ERR_DETECT_VAL
#define AFE_UV CELL_VOLTAGE_MIN_ERR_DETECT_VAL

#define AFE_MAX_GPIO_TEMPERATURE 70
#define AFE_MIN_GPIO_TEMPERATURE -40

#define AFE_MAX_BAL_NTC_TEMPERATURE SAFETY_BALANCING_TEMP_MAX
#define AFE_MIN_BAL_NTC_TEMPERATURE SAFETY_BALANCING_TEMP_MIN

#define AFE_MAX_APP_NTC_TEMPERATURE 105
#define AFE_MIN_APP_NTC_TEMPERATURE -40


// The cell configuration corresponds to the BIT position in a uint16_t
#define AFE_CONNECTED_CELLS                    ((uint16_t)0b0011100000001111)
#define AFE_CONNECTED_TEMPSENS                 ((uint8_t)0b0111110)  // @req CB-79076
#define AFE_CONNECTED_BAL_TEMPSENS             ((uint8_t)0b0000000)  // @req CB-79076
#define AFE_CONNECTED_APP_TEMPSENS             ((uint8_t)0b0000000)
#define AFE_CONNECTED_GPIO_OUTPUTS             ((uint8_t)0b1000001)
#define AFE_NUM_CONNECTED_CELLS_1ST_AFE        7u
#define AFE_NUM_CONNECTED_TEMPSENS_1ST_AFE     5u
#define AFE_NUM_CONNECTED_BAL_TEMPSENS_1ST_AFE 0u

/********* GPIO_CFG1 *********/
#define AFE_NUM_CONNECTED_APP_TEMPSENS_1ST_AFE 0u
/**
 * description: Register controls the configuration of the GPIO port
 * 00: GPIOx configured as analog input for radiometric measurement
 * 01: GPIOx configured as analog input for absolute measurement
 * 10: GPIOx configured as digital input
 * 11: GPIOx configured as digital output
 **/
#define GPIO0_ANALOG_INPUT_RATIOMETRIC 0b00u
#define GPIO0_ANALOG_INPUT_ABSOLUTE    0b01u
#define GPIO0_ANALOG_DIGITAL_INPUT     0b10u
#define GPIO0_ANALOG_DIGITAL_OUTPUT    0b11u

#define AFE_GPIO_CFG1_CONFIG (((uint16_t)GPIO0_ANALOG_DIGITAL_OUTPUT << AFE_MC33771_GPIO0_CFG_POS)      \
                              | ((uint16_t)GPIO0_ANALOG_INPUT_RATIOMETRIC << AFE_MC33771_GPIO1_CFG_POS) \
                              | ((uint16_t)GPIO0_ANALOG_INPUT_RATIOMETRIC << AFE_MC33771_GPIO2_CFG_POS) \
                              | ((uint16_t)GPIO0_ANALOG_INPUT_RATIOMETRIC << AFE_MC33771_GPIO3_CFG_POS) \
                              | ((uint16_t)GPIO0_ANALOG_INPUT_RATIOMETRIC << AFE_MC33771_GPIO4_CFG_POS) \
                              | ((uint16_t)GPIO0_ANALOG_INPUT_RATIOMETRIC << AFE_MC33771_GPIO5_CFG_POS) \
                              | ((uint16_t)GPIO0_ANALOG_DIGITAL_OUTPUT << AFE_MC33771_GPIO6_CFG_POS))


/********* SYS_CFG1 *********/
#define AFE_MC33771_SYS_CFG1_CYCLIC_TIMER 0b000u  // Bit 13 - 15 --> Timer to trigger cyclic measurements in normal mode or sleep mode; 0 = off
#define AFE_MC33771_SYS_CFG1_DIAG_TIMEOUT 0b101u  // Bit 10 - 12 --> Length of time the device is allowed to be in diag mode before being forced to \
                                                  // normal mode. 0b100 = 1s
#define AFE_MC33771_SYS_CFG1_I_MEAS_ON    0b1u    // Bit 9 --> Enable for current measurement chain; 1 = on
#define AFE_MC33771_SYS_CFG1_I_MEAS_OFF   0b0u    // Bit 9 --> Enable for current measurement chain; 0 = off
#define AFE_MC33771_SYS_CFG1_CB_DRVEN     0b1u    // Bit 7 --> General enable or disable for all cell balance drivers; 1 = enabled \
                                                  // Bit 6 = GO2DIAG, Bit 5 = CB_MANUAL_PAUSE, Bit 4 = SOFT_RST
#define AFE_MC33771_SYS_CFG1_FAULTWAVE    0b0u    // Bit 3 --> FAULT pin wave form control bit; 1 = FAULT pin has high or low level behavior
#define AFE_MC33771_SYS_CFG1_WAVE_DC_BITx 0b00u   // Bit 1 - 2 --> Controls the off time of the heart beat pulse.

#define AFE_SYS_CFG1_CONFIG (((uint16_t)AFE_MC33771_SYS_CFG1_CYCLIC_TIMER << AFE_MC33771x_CYCLIC_TIMER_POSITION)     \
                             | ((uint16_t)AFE_MC33771_SYS_CFG1_DIAG_TIMEOUT << AFE_MC33771x_DIAG_TIMEOUT_POSITION)   \
                             | ((uint16_t)AFE_MC33771_SYS_CFG1_I_MEAS_ON << AFE_MC33771_SYS_CFG1_I_MEAS_EN_POSITION) \
                             | ((uint16_t)AFE_MC33771_SYS_CFG1_CB_DRVEN << AFE_MC33771x_CB_DRVEN_POSITION)           \
                             | ((uint16_t)AFE_MC33771_SYS_CFG1_FAULTWAVE << AFE_MC33771_SYS_CFG1_FAULTWAVE_POSITION))
/***************************/

/********* SYS_CFG2 *********/
// Bit 13 - 15 -- > reserved, Bit 10 - 12 -- > PREVIOUS_STATE
#define AFE_MC33771_SYS_CFG2_FLT_RST_CFG  AFE_MC33771_FLT_RST_CFG5  // Bit 6 - 9 --> Fault reset configuration\
                                                                    // 0b1010 = Enabled COM timeout (1024 ms) reset and OSC fault monitoring
#define AFE_MC33771_SYS_CFG2_TIMEOUT_COMM 0b11u                     // Bit 4 - 5 --> No communication timeout; 0b11 = 256ms\
                                                                    // Bit 2 - 3 --> Reserved
#define AFE_MC33771_SYS_CFG2_NUMB_ODD     0b1u                      // Bit 1 --> Odd number of cells in the cluster; 1 = Odd configuration
#define AFE_MC33771_SYS_CFG2_NUMB_EVEN    0b0u                      // Bit 1 --> Odd number of cells in the cluster; 1 = Odd configuration
#define AFE_MC33771_SYS_CFG2_HAMM_EMCOD   0b0u                      // Bit 0 --> Hamming encoders; 1 = Decode - the DED Hamming decoders fulfill their job
#define AFE_SYS_CFG2_CONFIG               (((uint16_t)AFE_MC33771_SYS_CFG2_FLT_RST_CFG << AFE_MC33771x_FLT_RST_CFG_POSITION) \
                             | ((uint16_t)AFE_MC33771_SYS_CFG2_TIMEOUT_COMM << AFE_MC33771x_TIMEOUT_COMM_POSITION)           \
                             | ((uint16_t)AFE_MC33771_SYS_CFG2_NUMB_ODD << AFE_MC33771x_NUMB_ODD_POSITION)                   \
                             | ((uint16_t)AFE_MC33771_SYS_CFG2_HAMM_EMCOD))
/***************************/

/********* SYS_CFG2 (OSC monitoring disabled) *********/
#define AFE_MC33771_SYS_CFG2_FLT_RST_CFG_ONLY_COM_TIMEOUT_RESET AFE_MC33771_FLT_RST_CFG4
#define AFE_SYS_CFG2_CONFIG_OSC_MONITORING_DISABLED             (((uint16_t)AFE_MC33771_SYS_CFG2_FLT_RST_CFG_ONLY_COM_TIMEOUT_RESET << AFE_MC33771x_FLT_RST_CFG_POSITION) \
                                                     | ((uint16_t)AFE_MC33771_SYS_CFG2_TIMEOUT_COMM << AFE_MC33771x_TIMEOUT_COMM_POSITION)                                \
                                                     | ((uint16_t)AFE_MC33771_SYS_CFG2_NUMB_ODD << AFE_MC33771x_NUMB_ODD_POSITION)                                        \
                                                     | ((uint16_t)AFE_MC33771_SYS_CFG2_HAMM_EMCOD))
/***************************/


/********* Cell select register – OV_UV_EN *********/
/**
 * CTx_OVUV_EN
 * description: Enable or disable ADC data to be compared with thresholds for OV/UV. If disabled no OVUV fault is set.
 * 0: OVUV disabled
 * 1: OVUV enabled
 **/
#define AFE_MC33771_OV_UV_EN_CTx_OVUV_EN AFE_CONNECTED_CELLS
#define AFE_OV_UV_EN_CONFIG(x)           ((uint16_t)AFE_MC33771_OV_UV_EN_CTx_OVUV_EN << AFE_MC33771_OV_UV_EN_CTx_OVUV_EN_POSITION) \
                                   | ((uint16_t)AFE_MC33771_OV_UV_EN_COMMON_UV_TH << AFE_MC33771_OV_UV_EN_COMMON_UV_TH_POSITION)   \
                                   | ((uint16_t)AFE_MC33771_OV_UV_EN_COMMON_OV_TH << AFE_MC33771_OV_UV_EN_COMMON_OV_TH_POSITION)


#if defined(AFE_TWO_AFES_ON_ONE_CSC) && AFE_TWO_AFES_ON_ONE_CSC == CONFIG_ENABLED

#define AFE_CONNECTED_CELLS_2ND_AFE        ((uint16_t)0b0011110000001111)
#define AFE_CONNECTED_TEMPSENS_2ND_AFE     ((uint8_t)0b1000001)
#define AFE_CONNECTED_BAL_TEMPSENS_2ND_AFE ((uint8_t)0b0000000)
#define AFE_CONNECTED_APP_TEMPSENS_2ND_AFE ((uint8_t)0b0000000)
#define AFE_CONNECTED_GPIO_OUTPUTS_2ND_AFE ((uint8_t)0b0111110)

/********* GPIO_CFG1 *********/
/**
 * description: Register controls the configuration of the GPIO port
 * 00: GPIOx configured as analog input for radiometric measurement
 * 01: GPIOx configured as analog input for absolute measurement
 * 10: GPIOx configured as digital input
 * 11: GPIOx configured as digital output
 **/

#define AFE_GPIO_CFG1_CONFIG_2ND_AFE (((uint16_t)GPIO0_ANALOG_INPUT_RATIOMETRIC << AFE_MC33771_GPIO0_CFG_POS) \
                                      | ((uint16_t)GPIO0_ANALOG_DIGITAL_OUTPUT << AFE_MC33771_GPIO1_CFG_POS)  \
                                      | ((uint16_t)GPIO0_ANALOG_DIGITAL_OUTPUT << AFE_MC33771_GPIO2_CFG_POS)  \
                                      | ((uint16_t)GPIO0_ANALOG_DIGITAL_OUTPUT << AFE_MC33771_GPIO3_CFG_POS)  \
                                      | ((uint16_t)GPIO0_ANALOG_DIGITAL_OUTPUT << AFE_MC33771_GPIO4_CFG_POS)  \
                                      | ((uint16_t)GPIO0_ANALOG_DIGITAL_OUTPUT << AFE_MC33771_GPIO5_CFG_POS)  \
                                      | ((uint16_t)GPIO0_ANALOG_INPUT_RATIOMETRIC << AFE_MC33771_GPIO6_CFG_POS))

/********* SYS_CFG1 *********/
#define AFE_SYS_CFG1_CONFIG_2ND_AFE (((uint16_t)AFE_MC33771_SYS_CFG1_CYCLIC_TIMER << AFE_MC33771x_CYCLIC_TIMER_POSITION)      \
                                     | ((uint16_t)AFE_MC33771_SYS_CFG1_DIAG_TIMEOUT << AFE_MC33771x_DIAG_TIMEOUT_POSITION)    \
                                     | ((uint16_t)AFE_MC33771_SYS_CFG1_I_MEAS_OFF << AFE_MC33771_SYS_CFG1_I_MEAS_EN_POSITION) \
                                     | ((uint16_t)AFE_MC33771_SYS_CFG1_CB_DRVEN << AFE_MC33771x_CB_DRVEN_POSITION)            \
                                     | ((uint16_t)AFE_MC33771_SYS_CFG1_FAULTWAVE << AFE_MC33771_SYS_CFG1_FAULTWAVE_POSITION))
/***************************/

/********* SYS_CFG2 *********/
// Bit 13 - 15 -- > reserved, Bit 10 - 12 -- > PREVIOUS_STATE
#define AFE_SYS_CFG2_CONFIG_2ND_AFE (((uint16_t)AFE_MC33771_SYS_CFG2_FLT_RST_CFG << AFE_MC33771x_FLT_RST_CFG_POSITION)     \
                                     | ((uint16_t)AFE_MC33771_SYS_CFG2_TIMEOUT_COMM << AFE_MC33771x_TIMEOUT_COMM_POSITION) \
                                     | ((uint16_t)AFE_MC33771_SYS_CFG2_NUMB_EVEN << AFE_MC33771x_NUMB_ODD_POSITION)        \
                                     | ((uint16_t)AFE_MC33771_SYS_CFG2_HAMM_EMCOD))
/***************************/

/********* Cell select register – OV_UV_EN *********/
/**
 * CTx_OVUV_EN
 * description: Enable or disable ADC data to be compared with thresholds for OV/UV. If disabled no OVUV fault is set.
 * 0: OVUV disabled
 * 1: OVUV enabled
 **/
#define AFE_MC33771_OV_UV_EN_CTx_OVUV_EN_2ND_AFE AFE_CONNECTED_CELLS_2ND_AFE
#define AFE_OV_UV_EN_CONFIG_2ND_AFE              ((uint16_t)AFE_MC33771_OV_UV_EN_CTx_OVUV_EN_2ND_AFE << AFE_MC33771_OV_UV_EN_CTx_OVUV_EN_POSITION) \
                                        | ((uint16_t)AFE_MC33771_OV_UV_EN_COMMON_UV_TH << AFE_MC33771_OV_UV_EN_COMMON_UV_TH_POSITION)              \
                                        | ((uint16_t)AFE_MC33771_OV_UV_EN_COMMON_OV_TH << AFE_MC33771_OV_UV_EN_COMMON_OV_TH_POSITION)
/***************************/
#endif


/********* Fault mask register x – FAULT_MASKx *********/
/**
 * description: Prevent the corresponding flags in FAULTx_STATUS to activate the FAULT_PIN
 * 0: The flag in position (x) activates the fault pin
 * 1: no activation
 **/
#define AFE_FAULT_MASK1_CONFIG 0b0001111111111111u  // bit 0: MASK_0_F, bit 12: MASK_12_F
#define AFE_FAULT_MASK2_CONFIG 0b1111111001111111u  // bit 0-6: MASK_0_F-MASK_6_F, bit 7-8: reserve, bit 9-15: MASK_9_F-MASK_15_F
#define AFE_FAULT_MASK3_CONFIG 0b1111111111111111u  // bit 0: MASK_0_F, bit15: MASK_15_F

/********* Wake-up mask register x - WAKEUP_MASKx *********/
/**
 * description: Prevent the corresponding flags in FAULTx_STATUS to wake up the device
 * 0: The flag in position (x) wakes the device up, when active
 * 1: No wake-up is possible by this source
 **/
#define AFE_WAKEUP_MASK1_CONFIG 0b0001100110011111  // bit 0-4: MASK_0_F-MASK_4_F, bit 7-8: MASK_7_F-MASK_8_F, bit 11-12: MASK_11_FK-MASK_12_F
#define AFE_WAKEUP_MASK2_CONFIG 0b1111111100110110  // bit 1-2: MASK_1_F-MASK_2_F, bit 4-5: MASK-4_F-MASK_5_F, bit 8-15: MASK_8_F-MASK1_F
#define AFE_WAKEUP_MASK3_CONFIG 0b1011111111111111  // bit 0-13: MASK_0_F-MASK_13_F, bit_15_F: MASK_15_F


#define AFE_TEMP_IMBALANCE_TH 20

#define AFE_R_SHUNT                    0.020
#define AFE_MC33771_ISENSE_GAIN_FACTOR 2.034  // Hardware-related amplification factor of the current measurement. For further details see schematics

/**@def AFE_ISENSE_MEASUREMENT_CONFIG
 * @brief  config to enable Isense Measurement from AFE
 */
#define AFE_ISENSE_MEASUREMENT_CONFIG CONFIG_ENABLED

/**
 * @def AFE_ECHO_VALIDATION_CONFIG
 * @brief config to enable the validation of the echo frame
 *
 */
#define AFE_ECHO_VALIDATION_CONFIG CONFIG_ENABLED

//***************************************************************************/
//************************** PUBLIC VARIABLE DEFINITIONS ********************/
//***************************************************************************/

//***************************************************************************/
//************************** PUBLIC FUNCTION DECLARATIONS *******************/
//***************************************************************************/
