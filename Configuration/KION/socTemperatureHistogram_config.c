/**
 * @file socTemperatureHistogram_config.c
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
#include "socTemperatureHistogram.h"
#include "socTemperatureHistogram_config.h"
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
#if !defined(UNIT_TEST)

MEM_WARRANTYDATA SocTemperatureHistogramNvm socTemperatureHistogramNvm = { 0 };

extern int32_t batteryTemperatureLimits[BATTERY_TEMPERATURE_LIMITS_SIZE];
extern int32_t socHistogramLimits[SOC_HISTOGRAM_LIMITS_SIZE];

SocTemperatureHistogramBins limits = {
    .socTemperatureHistogramTemperatureLimits = &batteryTemperatureLimits[0],
    .socTemperatureHistogramSocLimits         = &socHistogramLimits[0],
};

const SocTemperatureHistogram socTemperatureHistogram = {
    .limits      = &limits,
    .counterSize = sizeof(socTemperatureHistogramNvm.counters) / sizeof(uint32_t),
    .counters    = &socTemperatureHistogramNvm.counters[0],
};

#endif
//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//
