/**
 * @file batteryCurrentTemperatureHistogram_config.c
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
#include "batteryCurrentTemperatureHistogram.h"
#include "task_cfg.h"

#include "histogramBins_config.h"


//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

// @req CB-89407
const int32_t batteryCurrentTemperatureHistogramTemperatureLimits[] = {
    -20,
    -10,
    0,
    10,
    25,
    40,
    50
};

// @req CB-89407
extern int32_t iHistogramLimits[];

MEM_WARRANTYDATA BatteryCurrentTemperatureHistogramNvm batteryCurrentTemperatureHistogramCounters;

const uint16_t WARRANTY_DATA_BATTERY_CURRENT_TEMPERATURE_DISCHARGE_SIZE = sizeof(batteryCurrentTemperatureHistogramCounters.countersBatteryCurrentTemperatureHistogramDischarge) / sizeof(uint32_t);
const uint16_t WARRANTY_DATA_BATTERY_CURRENT_TEMPERATURE_CHARGE_SIZE    = sizeof(batteryCurrentTemperatureHistogramCounters.countersBatteryCurrentTemperatureHistogramCharge) / sizeof(uint32_t);

// @req CB-89408
const BatteryCurrentTemperatureHistogram batteryCurrentTemperatureHistogramDischarge = {
    .systemTemperatureLimits       = &batteryCurrentTemperatureHistogramTemperatureLimits[0],
    .systemCurrentLimits           = &iHistogramLimits[0],
    .systemTemperatureLimitsLength = (sizeof(batteryCurrentTemperatureHistogramTemperatureLimits) / sizeof(int32_t)) + 1U,
    .systemCurrentLimitsLength     = I_HISTOGRAM_LIMITS_SIZE + 1U,
    .counterSize                   = sizeof(batteryCurrentTemperatureHistogramCounters.countersBatteryCurrentTemperatureHistogramDischarge) / sizeof(uint32_t),
    .counters                      = &batteryCurrentTemperatureHistogramCounters.countersBatteryCurrentTemperatureHistogramDischarge[0]
};

const BatteryCurrentTemperatureHistogram batteryCurrentTemperatureHistogramCharge = {
    .systemTemperatureLimits       = &batteryCurrentTemperatureHistogramTemperatureLimits[0],
    .systemCurrentLimits           = &iHistogramLimits[0],
    .systemTemperatureLimitsLength = (sizeof(batteryCurrentTemperatureHistogramTemperatureLimits) / sizeof(int32_t)) + 1U,
    .systemCurrentLimitsLength     = I_HISTOGRAM_LIMITS_SIZE + 1U,
    .counterSize                   = sizeof(batteryCurrentTemperatureHistogramCounters.countersBatteryCurrentTemperatureHistogramCharge) / sizeof(uint32_t),
    .counters                      = &batteryCurrentTemperatureHistogramCounters.countersBatteryCurrentTemperatureHistogramCharge[0]
};

const BatteryCurrentTemperatureHistogram* const batteryCurrentTemperatureHistograms[] = {
    &batteryCurrentTemperatureHistogramDischarge,
    &batteryCurrentTemperatureHistogramCharge
};

const BatteryCurrentTemperatureHistogramConfig batteryCurrentTemperatureHistogramConfig = {
    .histograms         = &batteryCurrentTemperatureHistograms[0],
    .numberOfHistograms = sizeof(batteryCurrentTemperatureHistograms) / sizeof(BatteryCurrentTemperatureHistogram*)
};


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
