/**
 * @file     pwmIf_config.h
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
#include "pwmRelaisIf.h"
#include "pwmIf_config.h"

//***************************************************************************/
//************************** PUBLIC TYPEDEFS ********************************/
//***************************************************************************/
#define PWM_RELAIS_CONTROL_GLOBAL CONFIG_ENABLED

#define PWM_RELAYS_CALCULATE_DUTY_CYCLE_VIA_LSS_COC_Kx_VOL CONFIG_ENABLED

#define PWM_RELAYS_VOLTAGE_HOLD_PHASE_mV       296  // Uhold = Icoil*20*39mR, recommended coil current: 0.38A => 296mV
#define PWM_RELAYS_VOLTAGE_TOLERANCE_mV        10   // prevents duty cycle to toggle between two values, determined with a trace at the hardware
#define PWM_RELAYS_FIRST_DUTY_CYCLE_HOLD_PHASE 29   // duty cycle for 11V supply voltage, determined with a trace at the hardware

#define PWM_RELAYS_MAX_DUTY_CYCLE_HOLD_PHASE 40  // this value should not be reachable in regular operation, determined with a trace at the hardware
#define PWM_RELAYS_MIN_DUTY_CYCLE_HOLD_PHASE 5   // this value should not be reachable in regular operation, determined with a trace at the hardware

//***************************************************************************/
//************************** PUBLIC VARIABLE DEFINITIONS ********************/
//***************************************************************************/
extern const PWMRelayControlConfig pwmControl_VoltageControlConfig;
extern const uint8_t PWM_CONTROLED_RELAIS_TABLE_LENGTH;

//***************************************************************************/
//************************** PUBLIC FUNCTION DECLARATIONS *******************/
//***************************************************************************/
