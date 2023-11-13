/**
 * @file     het_signal_config.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "hwversion_config.h"
#include "pwmIf_config.h"
#include "config_enable.h"
#include "het_TMS570LS.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/


const PwmSignalConfig* const pwmSignals[] = {};

const uint8_t PWM_SIGNAL_CONFIG_LENGTH = sizeof(pwmSignals) / sizeof(PwmSignalConfig*);

extern const PwmType* const pwmTypes[];

//***************************************************************************/
//************************** PRIVATE FUNCTION DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DEFINITIONS *******************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DEFINITIONS * ******************/
//***************************************************************************/

PWM_STATUS pwm_Relai_startSignal(uint8_t relayId)
{
    DEBUG_ASSERT(relayId <= PWM_SIGNAL_CONFIG_LENGTH);
    return pwmTypes[pwmSignals[relayId]->device]->start(pwmSignals[relayId]);
}

PWM_STATUS pwm_Relai_stopSignal(uint8_t relayId)
{
    DEBUG_ASSERT(relayId <= PWM_SIGNAL_CONFIG_LENGTH);
    return pwmTypes[pwmSignals[relayId]->device]->stop(pwmSignals[relayId]);
}

PWM_STATUS pwm_Relai_setDutyCycle(uint8_t relayId, uint8_t dutyCycle)
{
    DEBUG_ASSERT(relayId <= PWM_SIGNAL_CONFIG_LENGTH);
    return pwmTypes[pwmSignals[relayId]->device]->setDutyCycle(pwmSignals[relayId], dutyCycle);
}

PWM_STATUS pwm_Relai_setSignal(uint8_t relayId, uint8_t dutyCycle, uint32_t period)
{
    DEBUG_ASSERT(relayId <= PWM_SIGNAL_CONFIG_LENGTH);
    return pwmTypes[pwmSignals[relayId]->device]->setSignal(pwmSignals[relayId], period, dutyCycle);
}
