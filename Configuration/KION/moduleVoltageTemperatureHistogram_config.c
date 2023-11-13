/**
 * @file moduleVoltageTemperatureHistogram_config.c
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
#include "moduleVoltageTemperatureHistogram.h"
#include "moduleVoltageTemperatureHistogram_config.h"
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


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

MEM_SEC_PARAMETER int32_t temperatureHistogramLimits[] = {
    -20,
    -10,
    0,
    10,
    25,
    40,
    50,
    60
};


extern int32_t batteryTemperatureLimits[BATTERY_TEMPERATURE_LIMITS_SIZE];

MEM_WARRANTYDATA ModuleVoltageTemperatureHistogramNvm moduleVoltageTemperatureHistogramCounters = { 0 };

const uint16_t WARRANTY_DATA_MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_SIZE = sizeof(moduleVoltageTemperatureHistogramCounters.countersModuleVoltageTemperatureHistogram) / sizeof(uint32_t);

const ModuleVoltageTemperatureHistogram moduleVoltageTemperatureHistogram = {
    .moduleVoltageTemperatureVoltageLimits           = &batteryTemperatureLimits[0],
    .moduleVoltageTemperatureVoltageLimitsLength     = (sizeof(batteryTemperatureLimits) / sizeof(int32_t)) + 1U,
    .moduleVoltageTemperatureTemperatureLimits       = &temperatureHistogramLimits[0],
    .moduleVoltageTemperatureTemperatureLimitsLength = (sizeof(temperatureHistogramLimits) / sizeof(int32_t)) + 1U,
    .counters                                        = &moduleVoltageTemperatureHistogramCounters.countersModuleVoltageTemperatureHistogram[0],
    .counterSize                                     = sizeof(moduleVoltageTemperatureHistogramCounters.countersModuleVoltageTemperatureHistogram) / sizeof(uint32_t),
};

const ModuleVoltageTemperatureHistogram* const moduleVoltageTemperatureHistograms[] = {
    &moduleVoltageTemperatureHistogram,
};

const ModuleVoltageTemperatureHistogramConfig moduleVoltageTemperatureHistogramConfig = {
    .histograms         = &moduleVoltageTemperatureHistograms[0],
    .numberOfHistograms = sizeof(moduleVoltageTemperatureHistograms) / sizeof(ModuleVoltageTemperatureHistogram*)
};
