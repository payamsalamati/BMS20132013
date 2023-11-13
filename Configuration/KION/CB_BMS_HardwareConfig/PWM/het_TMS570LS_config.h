/**
 * @file     het_tms570_config.h
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


//***************************************************************************/
//************************** PUBLIC TYPEDEFS ********************************/
//***************************************************************************/

// N2HET 1 channel allocation
#define RELAIS_CONTROL_1 (PWM_Channel) PWM_CHANNEL_0
#define RELAIS_CONTROL_2 (PWM_Channel) PWM_CHANNEL_1

#define HET_MAX_NUMBER_OF_CHANNEL 8

// N2 HET channel configuration
#define N2HET_1_PWM_0_PIN                  30u  // N2HET port pin
#define N2HET_1_PWM_0_SWITCHED_ON_AT_START 0u   // 0: disable, 1: enable
#define N2HET_1_PWM_0_INTERRUPT_ENABLE     0u   // 3: disable, 1: enable
#define N2HET_1_PWM_0_POLARITY             1u   // 3: High Polarity, 1: Low Polarity
#define N2HET_1_PWM_0_DIR_OUTPUT           1U

#define N2HET_1_PWM_1_PIN                  14u  // N2HET port pin
#define N2HET_1_PWM_1_SWITCHED_ON_AT_START 0u   // 0: disable, 1: enable
#define N2HET_1_PWM_1_INTERRUPT_ENABLE     0u   // 0: disable, 1: enable
#define N2HET_1_PWM_1_POLARITY             1u   // 3: High Polarity, 1: Low Polarity
#define N2HET_1_PWM_1_DIR_OUTPUT           1U

#define N2HET_1_PWM_2_PIN                  1u  // N2HET port pin
#define N2HET_1_PWM_2_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_1_PWM_2_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_1_PWM_2_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_1_PWM_2_DIR_OUTPUT           0U

#define N2HET_1_PWM_3_PIN                  2u  // N2HET port pin
#define N2HET_1_PWM_3_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_1_PWM_3_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_1_PWM_3_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_1_PWM_3_DIR_OUTPUT           0U

#define N2HET_1_PWM_4_PIN                  3u  // N2HET port pin
#define N2HET_1_PWM_4_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_1_PWM_4_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_1_PWM_4_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_1_PWM_4_DIR_OUTPUT           0U

#define N2HET_1_PWM_5_PIN                  4u  // N2HET port pin
#define N2HET_1_PWM_5_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_1_PWM_5_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_1_PWM_5_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_1_PWM_5_DIR_OUTPUT           0U

#define N2HET_1_PWM_6_PIN                  5u  // N2HET port pin
#define N2HET_1_PWM_6_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_1_PWM_6_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_1_PWM_6_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_1_PWM_6_DIR_OUTPUT           0U

#define N2HET_1_PWM_7_PIN                  6u  // N2HET port pin
#define N2HET_1_PWM_7_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_1_PWM_7_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_1_PWM_7_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_1_PWM_7_DIR_OUTPUT           0U
// N2HET 2 channel allocation


// N2 HET channel configuration
#define N2HET_2_PWM_0_PIN                  0u  // N2HET port pin
#define N2HET_2_PWM_0_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_2_PWM_0_INTERRUPT_ENABLE     0u  // 3: disable, 1: enable
#define N2HET_2_PWM_0_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_2_PWM_0_DIR_OUTPUT           0U

#define N2HET_2_PWM_1_PIN                  0u  // N2HET port pin
#define N2HET_2_PWM_1_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_2_PWM_1_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_2_PWM_1_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_2_PWM_1_DIR_OUTPUT           0U

#define N2HET_2_PWM_2_PIN                  1u  // N2HET port pin
#define N2HET_2_PWM_2_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_2_PWM_2_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_2_PWM_2_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_2_PWM_2_DIR_OUTPUT           0U

#define N2HET_2_PWM_3_PIN                  2u  // N2HET port pin
#define N2HET_2_PWM_3_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_2_PWM_3_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_2_PWM_3_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_2_PWM_3_DIR_OUTPUT           0U

#define N2HET_2_PWM_4_PIN                  3u  // N2HET port pin
#define N2HET_2_PWM_4_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_2_PWM_4_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_2_PWM_4_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_2_PWM_4_DIR_OUTPUT           0U

#define N2HET_2_PWM_5_PIN                  4u  // N2HET port pin
#define N2HET_2_PWM_5_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_2_PWM_5_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_2_PWM_5_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_2_PWM_5_DIR_OUTPUT           0U

#define N2HET_2_PWM_6_PIN                  5u  // N2HET port pin
#define N2HET_2_PWM_6_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_2_PWM_6_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_2_PWM_6_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_2_PWM_6_DIR_OUTPUT           0U

#define N2HET_2_PWM_7_PIN                  6u  // N2HET port pin
#define N2HET_2_PWM_7_SWITCHED_ON_AT_START 0u  // 0: disable, 1: enable
#define N2HET_2_PWM_7_INTERRUPT_ENABLE     0u  // 0: disable, 1: enable
#define N2HET_2_PWM_7_POLARITY             1u  // 3: High Polarity, 1: Low Polarity
#define N2HET_2_PWM_7_DIR_OUTPUT           0U
//***************************************************************************/
//************************** PUBLIC VARIABLE DEFINITIONS ********************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DECLARATIONS *******************/
//***************************************************************************/
uint8_t het_getPinFromConfig(uint8_t pwmUnit, uint8_t pwmChannel);

uint8_t het_getSwitchOnStartFromConfig(uint8_t pwmUnit, uint8_t pwmChannel);

uint8_t het_getPolarityFromConfig(uint8_t pwmUnit, uint8_t pwmChannel);

bool het_ispwmDirOutput(uint8_t pwmUnit, uint8_t pwmChannel);
