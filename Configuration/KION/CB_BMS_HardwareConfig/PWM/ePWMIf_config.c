/**
 * @file ePWMIf_config.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include "ePWM_TMS570LS.h"
#include "ePWM_TMS570LS_helper.h"
#include "pwm.h"
#include "bms_config.h"
//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//
// PIN E19: ePWM4AA output
const EPWMSignalConfig contactorEnable1_config = {
    .ePwmModule       = EPWM_MODULE_4,     // use EPWM_MODULE enum only! (EPWM_MODULE_1 - EPWM_MODULE_7)
    .highSpeedClkDiv  = EPWM_HSPCLKDIV_1,  // Use EPWM_HighSpeedClockDivider enum only!
    .clkDiv           = EPWM_CLKDIV_1,     // use EPWM_ClockDivider enum only!
    .frequency        = 16000,             // [Hz]
    .dutyCycle_ePWMxA = 50,                // [%] shall be set to 0 if not used
    .dutyCycle_ePWMxB = 0,                 // [%] shall be set to 0 if not used
    .channelOutput    = EPWMxA,            // use EPWM_ChannelOutput only
};
// PIN V7 ePWM7A output
const EPWMSignalConfig contactorEnable2_config = {
    .ePwmModule       = EPWM_MODULE_7,     // use EPWM_MODULE enum only! (EPWM_MODULE_1 - EPWM_MODULE_7)
    .highSpeedClkDiv  = EPWM_HSPCLKDIV_1,  // Use EPWM_HighSpeedClockDivider enum only!
    .clkDiv           = EPWM_CLKDIV_1,     // use EPWM_ClockDivider enum only!
    .frequency        = 16000,             // [Hz]
    .dutyCycle_ePWMxA = 50,                // [%] shall be set to 0 if not used
    .dutyCycle_ePWMxB = 0,                 // [%] shall be set to 0 if not used
    .channelOutput    = EPWMxA,            // use EPWM_ChannelOutput only

};

// PIN B12: epwm4B output // same ePWMmodule as contactorEnable1_config
const EPWMSignalConfig contactorEnable3_config = {
    .ePwmModule       = EPWM_MODULE_4,     // use EPWM_MODULE enum only! (EPWM_MODULE_1 - EPWM_MODULE_7)
    .highSpeedClkDiv  = EPWM_HSPCLKDIV_1,  // Use EPWM_HighSpeedClockDivider enum only!
    .clkDiv           = EPWM_CLKDIV_1,     // use EPWM_ClockDivider enum only!
    .frequency        = 16000,             // [Hz]
    .dutyCycle_ePWMxA = 0,                 // [%] shall be set to 0 if not used
    .dutyCycle_ePWMxB = 50,                // [%] shall be set to 0 if not used
    .channelOutput    = EPWMxB,            //  use EPWM_ChannelOutput only

};

const EPWMSignalConfig* const ePwmSignals[] = {
    &contactorEnable1_config,
    &contactorEnable2_config,
    &contactorEnable3_config,
};

const uint8_t EPWM_SIGNAL_CONFIG_LENGTH = sizeof(ePwmSignals) / sizeof(EPWMSignalConfig*);
//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
PWM_STATUS epwmRelay1_setDutyCycle(uint8_t dutyCycle)
{
    return ePWM_TMS570_setDutyCycle_ePWMx(contactorEnable1_config.ePwmModule, contactorEnable1_config.channelOutput, dutyCycle);
}

PWM_STATUS epwmRelay2_setDutyCycle(uint8_t dutyCycle)
{
    return ePWM_TMS570_setDutyCycle_ePWMx(contactorEnable2_config.ePwmModule, contactorEnable2_config.channelOutput, dutyCycle);
}

PWM_STATUS epwmRelay3_setDutyCycle(uint8_t dutyCycle)
{
    return ePWM_TMS570_setDutyCycle_ePWMx(contactorEnable3_config.ePwmModule, contactorEnable3_config.channelOutput, dutyCycle);
}

PWM_STATUS pwmRelay_setDutyCycle(uint8_t relayId, uint8_t dutyCycle)
{
    PWM_STATUS result = PWM_STATUS_FAILURE;
    switch(relayId)
    {
        case 0:
            result = ePWM_TMS570_setDutyCycle_ePWMx(contactorEnable1_config.ePwmModule, contactorEnable1_config.channelOutput, dutyCycle);
            break;
        case 1:
            result = ePWM_TMS570_setDutyCycle_ePWMx(contactorEnable2_config.ePwmModule, contactorEnable2_config.channelOutput, dutyCycle);
            break;
        case 2:
            result = ePWM_TMS570_setDutyCycle_ePWMx(contactorEnable3_config.ePwmModule, contactorEnable3_config.channelOutput, dutyCycle);
            break;
        default:
            break;
    }
    return result;
}

PWM_STATUS pwmRelay_setAndStartSignal(uint8_t relayId, uint8_t dutyCycle)
{
    return pwmRelay_setDutyCycle(relayId, dutyCycle);
}

PWM_STATUS pwmRelay_init(void)
{
    PWM_STATUS result = ePWM_TMS570LS_init();

    if(result == PWM_STATUS_SUCCESS)
    {
        for(uint8_t relayID = 0; (relayID < BMS_CONFIG_NUMBER_OF_RELAIS) && (result == PWM_STATUS_SUCCESS); relayID++)
        {
            result = pwmRelay_setDutyCycle(relayID, 0u);
        }
    }
    if(result == PWM_STATUS_SUCCESS)
    {
        ePWM_TMS570_pwmStart();
    }
    return result;
}
