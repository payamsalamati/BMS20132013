/**
 * @file eCAPIf_config.c
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief This module contains the signals for eCAP
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include "eCAP_TMS570LS.h"
#include "eCAPIf_config.h"
#include "ioIf_signals.h"
//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

const ECAPSignalConfig ecapBCMnRDy_config = {
    .ecapModule = ECAP_MODULE_1,  // use ECAP_MODULE enum only! (ECAP_MODULE_1 - ECAP_MODULE_6)
    .maxPeriode = 300000U,        // 3* (1)/(9,3Hz) ~= 300000µs; factor 3 is taken as buffer margin.
    .inverted   = true,
};

const ECAPSignalConfig ecapSpeedFan_config = {
    .ecapModule = ECAP_MODULE_5,  // use ECAP_MODULE enum only! (ECAP_MODULE_1 - ECAP_MODULE_6)
    .maxPeriode = 3000000U,       // 3* (1)/(1Hz) ~= 3000000µs ; factor 3 is taken as buffer margin.

};

const ECAPSignalConfig* ecapSignals[] = {
    &ecapBCMnRDy_config,
    &ecapSpeedFan_config,
};

const uint8_t ECAP_SIGNAL_CONFIG_LENGTH = sizeof(ecapSignals) / sizeof(ECAPSignalConfig*);


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

uint32_t eCapIf_getSpeedFanFrequency(void)
{
    float frequency = 0;
    if(eCAP_TMS570LS_getFrequency(&ecapSpeedFan_config, &frequency) != ECAP_STATUS_SUCCESS)
    {
        frequency = 0.0f;
    }
    return frequency;
}

uint8_t eCapIf_getBCMnRDyDutyCycle(void)
{
    uint8_t dutyCycle = 0xFF;                                                               // Set dutyCycle to an ErrorValue
    if(eCAP_TMS570LS_getDutyCycle(&ecapBCMnRDy_config, &dutyCycle) != ECAP_STATUS_SUCCESS)  // ECAP cant calculate the dutyCycle, if DC == 100% or 0%
    {
        IO_VAL_t state = IO_UNDEFINED_STATE;
        if(io_getBCM_nReady(&state) == IO_SUCCESS)
        {
            dutyCycle = (state == IO_LOW_STATE) ? 100u : 0u;  // state is inverted-> lowstate -> 100% DutyCycle
        }
        else
        {
            dutyCycle = 0xFFu;  // Set dutyCycle to an ErrorValue
        }
    }

    return dutyCycle;
}
