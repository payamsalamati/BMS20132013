/**
 * @file temperatureHistogram.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */
/* Related Requirements: */
/**@req WHBMS-12986*/
/**@req WHBMS-12987*/
/**@req WHBMS-14362*/
/**@req WHBMS-14357*/
/**@req WHBMS-14358*/
/**@req WHBMS-14359*/
/**@req WHBMS-14362*/
/**@req WHBMS-14363*/
/**@req WHBMS-14364*/
/**@req WHBMS-14365*/
/**@req WHBMS-14366*/
/**@req WHBMS-14369*/
/**@req WHBMS-32721*/

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include "temperatureHistogram.h"
#include "temperatureHistogram_config.h"
#include <stdint.h>
#include "histogram.h"

#include "idAllocation.h"
#include "cellTemperatureMeasurement.h"
#include "fut_math.h"
#include "debug.h"
#include "canOpenStmFct.h"

#if !defined(UNIT_TEST)
#include "module_config.h"
#include "stateFunctions.h"
#include "master_config.h"
#else
#include "temperatureHistogram/test/bms_config.h"
#include "temperatureHistogram/test/stateFunctions.h"
#endif

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//
static void addValueToHistogram(uint16_t moduleNumber);
static uint8_t checkForOperationMode(void);
static void getModuleTemperatures(int16_t* data, uint16_t moduleNumber);
#if defined(DEBUG)
static void checkConfiguration(void);
#endif
//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//
extern const TemperatureHistogramConfig temperatureHistogramConfig;

extern const uint16_t WARRANTY_DATA_MIN_TEMPERATURE_OPERATION_SIZE;
extern const uint16_t WARRANTY_DATA_MAX_TEMPERATURE_OPERATION_SIZE;
extern const uint16_t WARRANTY_DATA_AVG_TEMPERATURE_OPERATION_SIZE;
extern const uint16_t WARRANTY_DATA_MIN_TEMPERATURE_STORAGE_SIZE;
extern const uint16_t WARRANTY_DATA_MAX_TEMPERATURE_STORAGE_SIZE;
extern const uint16_t WARRANTY_DATA_AVG_TEMPERATURE_STORAGE_SIZE;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//
#if defined(DEBUG)
static void checkConfiguration(void)
{
    DEBUG_ASSERT(MASTER_CONFIG_MAX_NUMBER_OF_RELAIS <= (temperatureHistogramConfig.numberOfHistograms / TEMPERATURE_HISTOGRAM_COUNTER_SIZE));

    for(uint8_t i = 0; i < temperatureHistogramConfig.numberOfHistograms; i++)
    {
        const TemperatureHistogram* histogram = &temperatureHistogramConfig.histograms[i];

        DEBUG_ASSERT_NOT_NULL(histogram->counters);
        DEBUG_ASSERT_NOT_NULL(histogram->systemTemperatureLimits);
        DEBUG_ASSERT_NOT_NULL(histogram->systemTemperatureLimitsLength);
        DEBUG_ASSERT(histogram->systemTemperatureLimitsLength == histogram->counterSize);
    }
}
#endif
// @req CB-89321 CB-89320
static void addValueToHistogram(uint16_t moduleNumber)
{
    uint16_t histogramOffset = moduleNumber * TEMPERATURE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE;
    // cppcheck-suppress misra-c2012-18.8 ; define is constant.
    int16_t moduleTemperatures[BMS_CONFIG_MAX_NUMBER_OF_TEMPERATURE_SENSORS] = { 0 };
    getModuleTemperatures(moduleTemperatures, moduleNumber);
    MaxMin_s16 maxMinTemperatures                        = maxMin_s16(moduleTemperatures, BMS_CONFIG_NUMBER_OF_TEMPERATURE_SENSORS);
    int16_t avgTemperatures                              = average_s16(moduleTemperatures, BMS_CONFIG_NUMBER_OF_TEMPERATURE_SENSORS);
    const TemperatureHistogram* minTemperatureHistogram  = &temperatureHistogramConfig.histograms[TEMPERATURE_HISTOGRAM_MIN_TEMPERATURE_POSITION + checkForOperationMode() + histogramOffset];
    const int32_t* const limitsHistogramMinTemperature[] = {
        &minTemperatureHistogram->systemTemperatureLimits[0],
    };
    const uint8_t lengthsMinTemperature[] = {
        minTemperatureHistogram->systemTemperatureLimitsLength,
    };
    const Histogram_t histogramMinCellTemperature = {
        .counters   = minTemperatureHistogram->counters,
        .dimensions = sizeof(limitsHistogramMinTemperature) / sizeof(int32_t*),
        .lengths    = &lengthsMinTemperature[0],
        .limits     = (const int32_t**)&limitsHistogramMinTemperature[0]
    };
    int32_t temperatureBuffer = maxMinTemperatures.min;
    histogram_addValue(&histogramMinCellTemperature, &temperatureBuffer);

    const TemperatureHistogram* maxTemperatureHistogram  = &temperatureHistogramConfig.histograms[TEMPERATURE_HISTOGRAM_MAX_TEMPERATURE_POSITION + checkForOperationMode() + histogramOffset];
    const int32_t* const limitsHistogramMaxTemperature[] = {
        &maxTemperatureHistogram->systemTemperatureLimits[0],
    };
    const uint8_t lengthsMaxTemperature[] = {
        maxTemperatureHistogram->systemTemperatureLimitsLength,
    };
    const Histogram_t histogramMaxCellTemperature = {
        .counters   = maxTemperatureHistogram->counters,
        .dimensions = sizeof(limitsHistogramMaxTemperature) / sizeof(int32_t*),
        .lengths    = &lengthsMaxTemperature[0],
        .limits     = (const int32_t**)&limitsHistogramMaxTemperature[0]
    };
    temperatureBuffer = maxMinTemperatures.max;
    histogram_addValue(&histogramMaxCellTemperature, &temperatureBuffer);

    const TemperatureHistogram* avgTemperatureHistogram  = &temperatureHistogramConfig.histograms[TEMPERATURE_HISTOGRAM_AVG_TEMPERATURE_POSITION + checkForOperationMode() + histogramOffset];
    const int32_t* const limitsHistogramAvgTemperature[] = {
        &avgTemperatureHistogram->systemTemperatureLimits[0],
    };
    const uint8_t lengthsAvgTemperature[] = {
        avgTemperatureHistogram->systemTemperatureLimitsLength,
    };
    const Histogram_t histogramAvgCellTemperature = {
        .counters   = avgTemperatureHistogram->counters,
        .dimensions = sizeof(limitsHistogramAvgTemperature) / sizeof(int32_t*),
        .lengths    = &lengthsAvgTemperature[0],
        .limits     = (const int32_t**)&limitsHistogramAvgTemperature[0]
    };
    temperatureBuffer = avgTemperatures;
    histogram_addValue(&histogramAvgCellTemperature, &temperatureBuffer);
}

// @req CB-89322
static uint8_t checkForOperationMode(void)
{
    uint8_t returnValue = 0u;
    if(stmFct_getDataloggingSelftest() == true)
    {
        returnValue = TEMPERATURE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET;
    }
    return returnValue;
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
void temperatureHistogram_mainFunction(void)
{
    for(uint16_t moduleCount = 0u; moduleCount < BMS_CONFIG_NUMBER_OF_SLAVES; moduleCount++)
    {
        addValueToHistogram(moduleCount);
    }
}

void temperatureHistogram_init(void)
{
#if defined(DEBUG)
    checkConfiguration();
#endif
}

const uint8_t* temperatureHistogram_getMinTemperatureOperationHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t histogramOffset = moduleNumber * TEMPERATURE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE;
    *size                    = WARRANTY_DATA_MIN_TEMPERATURE_OPERATION_SIZE;
    uint8_t index            = TEMPERATURE_HISTOGRAM_MIN_TEMPERATURE_POSITION + histogramOffset;
    DEBUG_API_CHECK(index < temperatureHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < temperatureHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)temperatureHistogramConfig.histograms[TEMPERATURE_HISTOGRAM_MIN_TEMPERATURE_POSITION + histogramOffset].counters;
    }
    return retVal;
}

const uint8_t* temperatureHistogram_getMaxTemperatureStoragenHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t histogramOffset = moduleNumber * TEMPERATURE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE;
    *size                    = WARRANTY_DATA_MIN_TEMPERATURE_STORAGE_SIZE;
    uint8_t index            = (TEMPERATURE_HISTOGRAM_MAX_TEMPERATURE_POSITION + TEMPERATURE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET) + histogramOffset;
    DEBUG_API_CHECK(index < temperatureHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < temperatureHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)temperatureHistogramConfig.histograms[index].counters;
    }
    return retVal;
}

const uint8_t* temperatureHistogram_getAvgTemperatureOperationHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t histogramOffset = moduleNumber * TEMPERATURE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE;
    *size                    = WARRANTY_DATA_MAX_TEMPERATURE_OPERATION_SIZE;
    uint8_t index            = TEMPERATURE_HISTOGRAM_AVG_TEMPERATURE_POSITION + histogramOffset;
    DEBUG_API_CHECK(index < temperatureHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < temperatureHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)temperatureHistogramConfig.histograms[index].counters;
    }
    return retVal;
}

const uint8_t* temperatureHistogram_getMinTemperatureStoragenHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t histogramOffset = moduleNumber * TEMPERATURE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE;
    *size                    = WARRANTY_DATA_MAX_TEMPERATURE_STORAGE_SIZE;
    uint8_t index            = (TEMPERATURE_HISTOGRAM_MIN_TEMPERATURE_POSITION + TEMPERATURE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET) + histogramOffset;
    DEBUG_API_CHECK(index < temperatureHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < temperatureHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)temperatureHistogramConfig.histograms[index].counters;
    }
    return retVal;
}

const uint8_t* temperatureHistogram_getMaxTemperatureOperationHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t histogramOffset = moduleNumber * TEMPERATURE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE;
    *size                    = WARRANTY_DATA_AVG_TEMPERATURE_OPERATION_SIZE;
    uint8_t index            = TEMPERATURE_HISTOGRAM_MAX_TEMPERATURE_POSITION + histogramOffset;
    DEBUG_API_CHECK(index < temperatureHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < temperatureHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)temperatureHistogramConfig.histograms[index].counters;
    }
    return retVal;
}

const uint8_t* temperatureHistogram_getAvgTemperatureStoragenHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t histogramOffset = moduleNumber * TEMPERATURE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE;
    *size                    = WARRANTY_DATA_AVG_TEMPERATURE_STORAGE_SIZE;
    uint8_t index            = (TEMPERATURE_HISTOGRAM_AVG_TEMPERATURE_POSITION + TEMPERATURE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET) + histogramOffset;
    DEBUG_API_CHECK(index < temperatureHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < temperatureHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)temperatureHistogramConfig.histograms[index].counters;
    }
    return retVal;
}

int32_t* temperatureHistogram_getHistogramLimitsOperation(uint16_t* size)
{
    DEBUG_API_CHECK((TEMPERATURE_HISTOGRAM_AVG_TEMPERATURE_POSITION + TEMPERATURE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET) <= temperatureHistogramConfig.numberOfHistograms);
    *size = temperatureHistogramConfig.histograms[TEMPERATURE_HISTOGRAM_AVG_TEMPERATURE_POSITION + TEMPERATURE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET].systemTemperatureLimitsLength - 1u;
    return temperatureHistogramConfig.histograms[TEMPERATURE_HISTOGRAM_AVG_TEMPERATURE_POSITION + TEMPERATURE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET].systemTemperatureLimits;
}

bool temperatureHistogram_setHistogramLimits(int32_t newValue, uint16_t binIndex)
{
    bool success = false;
    if(binIndex < (temperatureHistogramConfig.histograms[0].systemTemperatureLimitsLength - 1u))
    {
        temperatureHistogramConfig.histograms[0].systemTemperatureLimits[binIndex] = newValue;
        success                                                                    = true;
    }
    return success;
}

void temperatureHistogram_resetModuleHistograms(uint8_t moduleNumber)
{
    uint16_t moduleHistogramOffset = (moduleNumber * TEMPERATURE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE);

    if(moduleNumber < BMS_CONFIG_NUMBER_OF_SLAVES)
    {
        for(uint16_t i = moduleHistogramOffset; i < (moduleHistogramOffset + TEMPERATURE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE); i++)
        {
            memset(temperatureHistogramConfig.histograms[i].counters, 0, temperatureHistogramConfig.histograms[i].counterSize * sizeof(temperatureHistogramConfig.histograms[i].counters[0]));
        }
    }
}
