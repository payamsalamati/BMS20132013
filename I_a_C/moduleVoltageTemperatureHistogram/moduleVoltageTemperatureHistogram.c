

/**
 * @file moduleVoltageTemperatureHistogram.c
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
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

#include "moduleVoltageTemperatureHistogram.h"
#include "moduleVoltageTemperatureHistogram_config.h"

#include "moduleVoltageMeasurement.h"
#include "cellTemperatureMeasurement.h"

#include "submasterVoltageMeasurement.h"
#include "canOpenStmFct.h"
#include "histogram.h"
#include "debug.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//
static void addValueToHistogram(const ModuleVoltageTemperatureHistogram* histogram);


#if defined(DEBUG)
static void checkConfiguration(void);
#endif

static bool isCanOpenState_Operational(void);


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

extern const ModuleVoltageTemperatureHistogramConfig moduleVoltageTemperatureHistogramConfig;
extern const uint16_t WARRANTY_DATA_MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_SIZE;
extern const CANopen canOpenConfigKion;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//
#if defined(DEBUG)
static void checkConfiguration(void)
{
    for(uint8_t i = 0; i < moduleVoltageTemperatureHistogramConfig.numberOfHistograms; i++)
    {
        const ModuleVoltageTemperatureHistogram* histogram = moduleVoltageTemperatureHistogramConfig.histograms[i];

        DEBUG_ASSERT_NOT_NULL(histogram->counters);
        DEBUG_ASSERT_NOT_NULL(histogram->moduleVoltageTemperatureVoltageLimits);
        DEBUG_ASSERT_NOT_NULL(histogram->moduleVoltageTemperatureTemperatureLimits);
        DEBUG_ASSERT_NOT_NULL(histogram->moduleVoltageTemperatureVoltageLimitsLength);
        DEBUG_ASSERT_NOT_NULL(histogram->moduleVoltageTemperatureTemperatureLimitsLength);
        uint32_t counterSize = histogram->moduleVoltageTemperatureVoltageLimitsLength * histogram->moduleVoltageTemperatureTemperatureLimitsLength;
        DEBUG_ASSERT(counterSize == histogram->counterSize);
    }
}
#endif

static void addValueToHistogram(const ModuleVoltageTemperatureHistogram* histogram)
{
    const int32_t* const limitsHistogramModuleVoltageTemperature[] = {
        &histogram->moduleVoltageTemperatureTemperatureLimits[0],
        &histogram->moduleVoltageTemperatureVoltageLimits[0],
    };
    const uint8_t lengths[] = {
        histogram->moduleVoltageTemperatureTemperatureLimitsLength,
        histogram->moduleVoltageTemperatureVoltageLimitsLength,
    };
    const Histogram_t histo = {
        .counters   = histogram->counters,
        .dimensions = sizeof(limitsHistogramModuleVoltageTemperature) / sizeof(int32_t*),
        .lengths    = &lengths[0],
        .limits     = (const int32_t**)&limitsHistogramModuleVoltageTemperature[0]
    };
    int32_t histogramValues[2]                                                 = { 0 };
    histogramValues[MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_TEMPERATURE_POSITION] = cellTemperatureMeasurement_getAverageValue();
    histogramValues[MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_VOLTAGE_POSITION]     = submasterVoltageMeasurement_getValue();

    histogram_addValue(&histo, histogramValues);
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
void moduleVoltageTemperatureHistogram_mainFunction(void)
{

    if(isCanOpenState_Operational())
    {
        const ModuleVoltageTemperatureHistogram* histogram = moduleVoltageTemperatureHistogramConfig.histograms[MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_POSITION];
        addValueToHistogram(histogram);
    }
    else
    {
        /* do nothning */
    }
}

void moduleVoltageTemperatureHistogram_init(void)
{
#if defined(DEBUG)
    checkConfiguration();
#endif
}


const uint8_t* moduleVoltageTemperatureHistogram_getHistogram(uint16_t* size)
{
    *size = WARRANTY_DATA_MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_SIZE;
    return (const uint8_t*)moduleVoltageTemperatureHistogramConfig.histograms[MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_POSITION]->counters;
}


void moduleVoltageTemperatureHistogram_resetHistograms(void)
{
    for(uint8_t i = 0; i < moduleVoltageTemperatureHistogramConfig.numberOfHistograms; i++)
    {
        memset(moduleVoltageTemperatureHistogramConfig.histograms[i]->counters, 0, moduleVoltageTemperatureHistogramConfig.histograms[i]->counterSize * sizeof(moduleVoltageTemperatureHistogramConfig.histograms[i]->counters[0]));
    }
}


const int32_t* moduleVoltageTemperatureHistogram_getTemperatureLimits(uint16_t* size)
{
    *size = moduleVoltageTemperatureHistogramConfig.histograms[MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_POSITION]->moduleVoltageTemperatureTemperatureLimitsLength - 1u;
    return moduleVoltageTemperatureHistogramConfig.histograms[MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_POSITION]->moduleVoltageTemperatureTemperatureLimits;
}


const int32_t* moduleVoltageTemperatureHistogram_getVoltageLimits(uint16_t* size)
{
    *size = moduleVoltageTemperatureHistogramConfig.histograms[MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_POSITION]->moduleVoltageTemperatureVoltageLimitsLength - 1u;
    return moduleVoltageTemperatureHistogramConfig.histograms[MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_POSITION]->moduleVoltageTemperatureVoltageLimits;
}

static bool isCanOpenState_Operational(void)
{
#if defined(UNIT_TEST)
    return true;
#else
    return (canOpenStm_getCanOpenState(&canOpenConfigKion) == canOpen_State_Operational) ? true : false;
#endif
}
