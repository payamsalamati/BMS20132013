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

#include "pwm.h"
#include "ePWM_TMS570LS.h"

//***************************************************************************/
//************************** PUBLIC TYPEDEFS ********************************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC VARIABLE DEFINITIONS ********************/
//***************************************************************************/

extern const PwmSignalConfig* const pwmSignals[];

//***************************************************************************/
//************************** PUBLIC FUNCTION DECLARATIONS *******************/
//***************************************************************************/
PWM_STATUS pwm_Relai_startSignal(uint8_t relayId);

PWM_STATUS pwm_Relai_stopSignal(uint8_t relayId);

PWM_STATUS pwm_Relai_setDutyCycle(uint8_t relayId, uint8_t dutyCycle);

PWM_STATUS pwm_Relai_setSignal(uint8_t relayId, uint8_t dutyCycle, uint32_t period);  // dutyCycle = %, period = us

PWM_STATUS pwmRelay_setAndStartSignal(uint8_t relayId, uint8_t dutyCycle);
PWM_STATUS pwmRelay_setDutyCycle(uint8_t relayId, uint8_t dutyCycle);
PWM_STATUS epwmRelay1_setDutyCycle(uint8_t dutyCycle);
PWM_STATUS epwmRelay2_setDutyCycle(uint8_t dutyCycle);
PWM_STATUS epwmRelay3_setDutyCycle(uint8_t dutyCycle);
PWM_STATUS pwmRelay_init(void);
