/**
 * @file mosfetDiagMeasurement_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


#pragma once
//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "config_enable.h"
#include "adcIf_signals.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define measurements_getFetDiagnostic_1(X) adc_getFetDiagnostic_Fet1(X)
#define measurements_getFetDiagnostic_2(X) adc_getFetDiagnostic_Fet2(X)


#define MOSFET_DIAG_MEASUREMENTS_VOLTAGES_VALID_COUNTER_LIMIT 3u

#define MOSFET_DIAG_MEASUREMENTS_VOLTAGES_VALID_MIN 50u

#define MOSFET_DIAG_MEASUREMENTS_VOLTAGES_VALID_MAX 36000u


#define MOSFET_DIAG_MEASUREMENTS_ECONEMIZER_CONFIGURATION CONFIG_ENABLED

#define measurements_getEconemizerDiagnostic_1(X) adc_getFetDiagnostic_SafetyFet1(X)
#define measurements_getEconemizerDiagnostic_2(X) adc_getFetDiagnostic_SafetyFet2(X)

#define MOSFET_DIAG_MEASUREMENTS_ECONEMIZER_VOLTAGES_VALID_COUNTER_LIMIT 3u

#define MOSFET_DIAG_MEASUREMENTS_ECONEMIZER_VOLTAGES_VALID_MIN 50u

#define MOSFET_DIAG_MEASUREMENTS_ECONEMIZER_VOLTAGES_VALID_MAX 5000u
//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
