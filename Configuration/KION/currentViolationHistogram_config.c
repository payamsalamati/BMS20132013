/**
 * @file currentViolationHistogram_config.c
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
#include "currentViolationHistogram.h"
#include "currentViolationHistogram_config.h"
#include "task_cfg.h"


//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

// @req CB-89422 CB-89423
const int8_t histogramDataTemperatureBins[] = {
    -20,
    -10,
    0,
    10,
    25,
    40,
    50,
    60,
};

MEM_WARRANTYDATA CurrentViolationHistogramNvm currentViolationHistogramNvm;

const uint16_t WARRANTY_DATA_CURRENT_VIOLATION_PULSE_SIZE = CURRENT_VIOLATION_HISTOGRAM_PULSE_COUNTER_SIZE;
const uint16_t WARRANTY_DATA_CURRENT_VIOLATION_CONT_SIZE  = CURRENT_VIOLATION_HISTOGRAM_CONT_COUNTER_SIZE;

const CurrentViolationHistogram currentViolationHistogramPulse = {
    .currentViolationTemperatureLimits       = &histogramDataTemperatureBins[0],
    .currentViolationTemperatureLimitsLength = (sizeof(histogramDataTemperatureBins) / sizeof(int8_t)) + 1U,
    .counterSize                             = sizeof(currentViolationHistogramNvm.counters.countersHistogramPulse) / sizeof(uint32_t),
    .counters                                = &currentViolationHistogramNvm.counters.countersHistogramPulse[0],
};

const CurrentViolationHistogram currentViolationHistogramCont = {
    .currentViolationTemperatureLimits       = &histogramDataTemperatureBins[0],
    .currentViolationTemperatureLimitsLength = (sizeof(histogramDataTemperatureBins) / sizeof(int8_t)) + 1U,
    .counterSize                             = sizeof(currentViolationHistogramNvm.counters.countersHistogramCont) / sizeof(uint32_t),
    .counters                                = &currentViolationHistogramNvm.counters.countersHistogramCont[0],
};

const CurrentViolationHistogram* const currentViolationHistograms[] = {
    &currentViolationHistogramPulse,
    &currentViolationHistogramCont,
};

const CurrentViolationHistogramConfig currentViolationHistogramConfig = {
    .histograms         = &currentViolationHistograms[0],
    .numberOfHistograms = sizeof(currentViolationHistograms) / sizeof(CurrentViolationHistogram*),
};


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
