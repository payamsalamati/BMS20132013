/**
 * @file adc_signal_config.c
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

#include <stdint.h>
#include "adcIf_signals.h"
#include "adc_signal_config.h"
#include "debug.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

extern const ADC_Signals adc_signals_HW1V0;
extern const ADC_Signals adc_signals_HW1V3;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

#if !defined(UNIT_TEST)
const ADC_Signals* adc_getAdcHardwareConfig(HWVERSION_STATUS hwVersion)
{
    const ADC_Signals* pointer;
    switch(hwVersion)
    {
        case(HWVERSION1v0):
            pointer = &adc_signals_HW1V0;
            break;
        case(HWVERSION1v3):
            pointer = &adc_signals_HW1V3;
            break;
        default:
            break;
    }

    return pointer;
}
#endif
