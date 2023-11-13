/**
 * @file contactorHistogram.c
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
#include "module_config.h"
#include "contactorHistogram.h"
// #include "contactorHistogram_config.h"

#include <stdint.h>
#include "task_cfg.h"
#include "warrantyData_config.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS *******************************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

const int32_t relayHistogramCurrentLimits[] = {
    -700,
    -500,
    -400,
    -350,
    -300,
    -250,
    -200,
    -150,
    -100,
    -50,
    -25,
    0,
    25,
    50,
    100,
    150,
    200,
    250,
    300,
    350,
    400,
    500,
    700,
};

const int32_t relayHistogramMaxTemperatureLimits[] = {};

const int32_t relayHistogramSystemVoltageLimits[] = {};

MEM_WARRANTYDATA ContactorHistogramNvm contactorHistogramCounters;

const ContactorHistogram contactorHistogram1 = {
    .currentLimits             = &relayHistogramCurrentLimits[0],
    .temperatureLimits         = &relayHistogramMaxTemperatureLimits[0],
    .systemVoltageLimits       = &relayHistogramSystemVoltageLimits[0],
    .currentLimitsLength       = (sizeof(relayHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
    .systemVoltageLimitsLength = (sizeof(relayHistogramSystemVoltageLimits) / sizeof(int32_t)) + 1U,
    .temperatureLimitsLength   = (sizeof(relayHistogramMaxTemperatureLimits) / sizeof(int32_t)) + 1U,
    .counterSize               = sizeof(contactorHistogramCounters.countershistogramRelay1) / sizeof(uint32_t),
    .counters                  = &contactorHistogramCounters.countershistogramRelay1[0]
};

const ContactorHistogram contactorHistogram2 = {
    .currentLimits             = &relayHistogramCurrentLimits[0],
    .temperatureLimits         = &relayHistogramMaxTemperatureLimits[0],
    .systemVoltageLimits       = &relayHistogramSystemVoltageLimits[0],
    .currentLimitsLength       = (sizeof(relayHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
    .systemVoltageLimitsLength = (sizeof(relayHistogramSystemVoltageLimits) / sizeof(int32_t)) + 1U,
    .temperatureLimitsLength   = (sizeof(relayHistogramMaxTemperatureLimits) / sizeof(int32_t)) + 1U,
    .counterSize               = sizeof(contactorHistogramCounters.countershistogramRelay2) / sizeof(uint32_t),
    .counters                  = &contactorHistogramCounters.countershistogramRelay2[0]
};
const ContactorHistogram contactorHistogram3 = {
    .currentLimits             = &relayHistogramCurrentLimits[0],
    .temperatureLimits         = &relayHistogramMaxTemperatureLimits[0],
    .systemVoltageLimits       = &relayHistogramSystemVoltageLimits[0],
    .currentLimitsLength       = (sizeof(relayHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
    .systemVoltageLimitsLength = (sizeof(relayHistogramSystemVoltageLimits) / sizeof(int32_t)) + 1U,
    .temperatureLimitsLength   = (sizeof(relayHistogramMaxTemperatureLimits) / sizeof(int32_t)) + 1U,
    .counterSize               = sizeof(contactorHistogramCounters.countershistogramRelay3) / sizeof(uint32_t),
    .counters                  = &contactorHistogramCounters.countershistogramRelay3[0]
};

const ContactorHistogram* const histograms[] = {
    &contactorHistogram1,
    &contactorHistogram2,
    &contactorHistogram3,
};

const ContactorHistogramConfig contactorHistogramConfig = {
    .histograms         = &histograms[0],
    .numberOfHistograms = sizeof(histograms) / sizeof(ContactorHistogram*)
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
