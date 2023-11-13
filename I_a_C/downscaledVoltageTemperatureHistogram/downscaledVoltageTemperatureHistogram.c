/**
 * @file downscaledVoltageTemperatureHistogram.c
 * @copyright (c) Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */
/* Related SW-Requirements : */
/**@req WHBMS-12988*/
/**@req WHBMS-14818*/
/**@req WHBMS-14821*/
/**@req WHBMS-14822*/
/**@req WHBMS-14823*/
/**@req WHBMS-14824*/
/**@req WHBMS-14939*/

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include "downscaledVoltageTemperatureHistogram.h"

#include <stdint.h>
#include <stdbool.h>
#include "histogram.h"

#include "debug.h"
#include "idAllocation.h"
#include "stateFunctions.h"
#include "cellVoltageMeasurement.h"
#include "cellTemperatureMeasurement.h"
#include "canOpenStmFct.h"
#include "fut_math.h"


#if !defined(UNIT_TEST)
#include "module_config.h"
#include "csc_config.h"
#endif


//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//
static void addValuesToHistogram(uint16_t module);
static void getModuleVoltages(uint16_t* data, uint16_t moduleNumber);
#if defined(DEBUG)
static void checkConfiguration(void);
#endif
static void getModuleVoltages(uint16_t* data, uint16_t moduleNumber);
static void getModuleTemperatures(int16_t* data, uint16_t moduleNumber);
//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

extern const DownscaledVoltageTemperatureHistogramConfig downscaledVoltageTemperatureHistogramConfig;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//
#if defined(DEBUG)
static void checkConfiguration(void)
{
    for(uint8_t i = 0; i < downscaledVoltageTemperatureHistogramConfig.numberOfHistograms; i++)
    {
        const DownscaledVoltageTemperatureHistogram* histogram = &downscaledVoltageTemperatureHistogramConfig.histograms[i];

        DEBUG_ASSERT_NOT_NULL(histogram->counters);
        DEBUG_ASSERT_NOT_NULL(histogram->downscaledVoltageTemperatureCellVoltageLimits);
        DEBUG_ASSERT_NOT_NULL(histogram->downscaledVoltageTemperatureCellVoltageLimitsLength);
        DEBUG_ASSERT_NOT_NULL(histogram->downscaledVoltageTemperatureCellTemperatureLimits);
        DEBUG_ASSERT_NOT_NULL(histogram->downscaledVoltageTemperatureCellTemperatureLimitsLength);
        DEBUG_ASSERT(histogram->downscaledVoltageTemperatureCellVoltageLimitsLength == histogram->counterSize / 2);
        DEBUG_ASSERT(histogram->downscaledVoltageTemperatureCellTemperatureLimitsLength == histogram->counterSize / 2);
    }
}
#endif
static void addValuesToHistogram(uint16_t module)
{
    // cppcheck-suppress misra-c2012-18.8 ; define is constant.
    uint16_t moduleVoltages[CELL_MODULE_CONFIG_MAX_MODULE_NO_OF_CELLS_SERIAL] = { 0 };
    // cppcheck-suppress misra-c2012-18.8 ; define is constant.
    int16_t moduleTemperatures[BMS_CONFIG_MAX_NUMBER_OF_TEMPERATURE_SENSORS] = { 0 };
    getModuleVoltages(moduleVoltages, module);
    getModuleTemperatures(moduleTemperatures, module);
    uint32_t avgVoltage     = average_u16(moduleVoltages, CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL);
    int32_t avgTemperatures = average_s16(moduleTemperatures, BMS_CONFIG_NUMBER_OF_TEMPERATURE_SENSORS);


    const DownscaledVoltageTemperatureHistogram* downscaledVoltageTemperatureHistogram = &downscaledVoltageTemperatureHistogramConfig.histograms[module];

    const int32_t* const limitDownscaledVoltageTemperatureCellVoltage[] = {
        &downscaledVoltageTemperatureHistogram->downscaledVoltageTemperatureCellVoltageLimits[0],
    };
    const int32_t* const limitDownscaledVoltageTemperatureCellTemperature[] = {
        &downscaledVoltageTemperatureHistogram->downscaledVoltageTemperatureCellTemperatureLimits[0],
    };
    const uint8_t lengthDownscaledVoltageTemperatureCellVoltageLimits[] = {
        downscaledVoltageTemperatureHistogram->downscaledVoltageTemperatureCellVoltageLimitsLength,
    };
    const uint8_t lengthDownscaledVoltageTemperatureCellTemperatureLimits[] = {
        downscaledVoltageTemperatureHistogram->downscaledVoltageTemperatureCellTemperatureLimitsLength,
    };
    const Histogram_t histogramAvgCellVoltage = {
        .counters   = downscaledVoltageTemperatureHistogram->counters,
        .dimensions = sizeof(limitDownscaledVoltageTemperatureCellVoltage) / sizeof(int32_t*),
        .lengths    = &lengthDownscaledVoltageTemperatureCellVoltageLimits[0],
        .limits     = (const int32_t**)&limitDownscaledVoltageTemperatureCellVoltage[0]
    };

    const Histogram_t histogramAvgCellTemperature = {
        .counters   = downscaledVoltageTemperatureHistogram->counters + DOWNSCALED_TEMPERATURE_HISTOGRAMM_COUNTER_OFFSET,
        .dimensions = sizeof(limitDownscaledVoltageTemperatureCellTemperature) / sizeof(int32_t*),
        .lengths    = &lengthDownscaledVoltageTemperatureCellTemperatureLimits[0],
        .limits     = (const int32_t**)&limitDownscaledVoltageTemperatureCellTemperature[0]
    };
    int32_t voltageBuffer     = avgVoltage;
    int32_t TemperatureBuffer = avgTemperatures;
    histogram_addValue(&histogramAvgCellVoltage, &voltageBuffer);
    histogram_addValue(&histogramAvgCellTemperature, &TemperatureBuffer);
}


static void getModuleVoltages(uint16_t* data, uint16_t moduleNumber)
{
    DEBUG_ASSERT(moduleNumber <= BMS_CONFIG_NUMBER_OF_SLAVES);
    for(uint16_t i = 0u; i < CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL; i++)
    {
        data[i] = cellVoltageMeasurement_getValue(moduleNumber, i);
    }
}

static void getModuleTemperatures(int16_t* data, uint16_t moduleNumber)
{
    DEBUG_ASSERT(moduleNumber <= BMS_CONFIG_NUMBER_OF_SLAVES);
    for(uint16_t i = 0u; i < BMS_CONFIG_NUMBER_OF_TEMPERATURE_SENSORS; i++)
    {
        data[i] = cellTemperatureMeasurement_getValue(moduleNumber, i);
    }
}


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
void downscaledVoltageTemperatureHistogram_mainFunction(void)
{
    for(uint16_t moduleNumber = 0u; moduleNumber < BMS_CONFIG_NUMBER_OF_SLAVES; moduleNumber++)
    {
        addValuesToHistogram(moduleNumber);
    }
}

void downscaledVoltageTemperatureHistogram_init(void)
{
#if defined(DEBUG)
    checkConfiguration();
#endif
}


const uint8_t* downscaledVoltageTemperatureHistogram_getHistogram(uint16_t moduleNumber, uint16_t* size)
{
    *size = (uint16_t)DOWNSCALED_VOLTAGE_TEMPERATURE_HISTOGRAMM_COUNTER_SIZE;
    DEBUG_API_CHECK(moduleNumber < downscaledVoltageTemperatureHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(moduleNumber < downscaledVoltageTemperatureHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)downscaledVoltageTemperatureHistogramConfig.histograms[moduleNumber].counters;
    }
    return retVal;
}


void downscaledVoltageTemperatureHistogram_resetModuleHistogram(uint8_t moduleNumber)
{
    if(moduleNumber < BMS_CONFIG_NUMBER_OF_SLAVES)
    {
        memset(downscaledVoltageTemperatureHistogramConfig.histograms[moduleNumber].counters, 0, downscaledVoltageTemperatureHistogramConfig.histograms[moduleNumber].counterSize * sizeof(downscaledVoltageTemperatureHistogramConfig.histograms[moduleNumber].counters[0]));
    }
}
