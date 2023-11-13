/**
 * @file voltageHistogram.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */
/**@req WHBMS-12982*/
/**@req WHBMS-12983*/
/**@req WHBMS-14339*/
/**@req WHBMS-14340*/
/**@req WHBMS-14341*/
/**@req WHBMS-14343*/
/**@req WHBMS-14346*/
/**@req WHBMS-14349*/
/**@req WHBMS-14350*/
/**@req WHBMS-14351*/
/**@req WHBMS-14355*/
/**@req WHBMS-24774*/
/**@req WHBMS-39776*/

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include "voltageHistogram.h"
#include "voltageHistogram_config.h"
#include <stdint.h>
#include <stdbool.h>
#include "histogram.h"

#include "debug.h"
#include "idAllocation.h"
#include "stateFunctions.h"
#include "cellVoltageMeasurement.h"
#include "canOpenStmFct.h"
#include "fut_math.h"

#if !defined(UNIT_TEST)
#include "csc_config.h"
#include "module_config.h"
#include "master_config.h"
#else
#include "voltageHistogram/test/bms_config.h"
#include "voltageHistogram/test/cell_module_config.h"
#endif

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//
static void addValuesToHistogram(uint16_t module);
static uint8_t checkForOperationMode(void);
static void getModuleVoltages(uint16_t* data, uint16_t moduleNumber);
#if defined(DEBUG)
static void checkConfiguration(void);
#endif
//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//
extern uint16_t length_of_countershistogramVoltageStorage;
extern const VoltageHistogramConfig voltageHistogramConfig;
extern const uint16_t WARRANTY_DATA_MIN_CELL_VOLTAGE_OPERATION_SIZE;
extern const uint16_t WARRANTY_DATA_MAX_CELL_VOLTAGE_OPERATION_SIZE;
extern const uint16_t WARRANTY_DATA_AVG_CELL_VOLTAGE_OPERATION_SIZE;
extern const uint16_t WARRANTY_DATA_MIN_CELL_VOLTAGE_STORAGE_SIZE;
extern const uint16_t WARRANTY_DATA_MAX_CELL_VOLTAGE_STORAGE_SIZE;
extern const uint16_t WARRANTY_DATA_AVG_CELL_VOLTAGE_STORAGE_SIZE;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//
#if defined(DEBUG)
static void checkConfiguration(void)
{
    DEBUG_ASSERT(MASTER_CONFIG_MAX_NUMBER_OF_RELAIS <= (voltageHistogramConfig.numberOfHistograms / VOLTAGE_HISTOGRAMM_COUNTER_SIZE));

    for(uint8_t i = 0; i < voltageHistogramConfig.numberOfHistograms; i++)
    {
        const VoltageHistogram* histogram = &voltageHistogramConfig.histograms[i];

        DEBUG_ASSERT_NOT_NULL(histogram->counters);
        DEBUG_ASSERT_NOT_NULL(histogram->systemVoltageLimits);
        DEBUG_ASSERT_NOT_NULL(histogram->systemVoltageLimitsLength);
        DEBUG_ASSERT(histogram->systemVoltageLimitsLength == histogram->counterSize);
    }
}
#endif
// @req CB-78712 CB-16491
static void addValuesToHistogram(uint16_t module)
{
    // cppcheck-suppress misra-c2012-18.8 ; define is constant.
    uint16_t moduleVoltages[CELL_MODULE_CONFIG_MAX_MODULE_NO_OF_CELLS_SERIAL] = { 0 };
    getModuleVoltages(moduleVoltages, module);
    MaxMin_u16 maxMinVoltages                        = maxMin_u16(moduleVoltages, CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL);
    uint16_t avgVoltage                              = average_u16(moduleVoltages, CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL);
    uint16_t moduleHistogramOffset                   = (module * VOLTAGE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE);
    const VoltageHistogram* minVoltageHistogram      = &voltageHistogramConfig.histograms[(
                                                                                         VOLTAGE_HISTOGRAM_MIN_CELL_VOLTAGE_POSITION + checkForOperationMode())
                                                                                     + moduleHistogramOffset];
    const int32_t* const limitsHistogramMinVoltage[] = {
        &minVoltageHistogram->systemVoltageLimits[0],
    };
    const uint8_t lengthsMinVoltage[] = {
        minVoltageHistogram->systemVoltageLimitsLength,
    };
    const Histogram_t histogramMinCellVoltage = {
        .counters   = minVoltageHistogram->counters,
        .dimensions = sizeof(limitsHistogramMinVoltage) / sizeof(int32_t*),
        .lengths    = &lengthsMinVoltage[0],
        .limits     = (const int32_t**)&limitsHistogramMinVoltage[0]
    };
    int32_t voltageBuffer = maxMinVoltages.min;
    histogram_addValue(&histogramMinCellVoltage, &voltageBuffer);

    const VoltageHistogram* maxVoltageHistogram      = &voltageHistogramConfig.histograms[(
                                                                                         VOLTAGE_HISTOGRAM_MAX_CELL_VOLTAGE_POSITION + checkForOperationMode())
                                                                                     + moduleHistogramOffset];
    const int32_t* const limitsHistogramMaxVoltage[] = {
        &maxVoltageHistogram->systemVoltageLimits[0],
    };
    const uint8_t lengthsMaxVoltage[] = {
        maxVoltageHistogram->systemVoltageLimitsLength,
    };
    const Histogram_t histogramMaxCellVoltage = {
        .counters   = maxVoltageHistogram->counters,
        .dimensions = sizeof(limitsHistogramMaxVoltage) / sizeof(int32_t*),
        .lengths    = &lengthsMaxVoltage[0],
        .limits     = (const int32_t**)&limitsHistogramMaxVoltage[0]
    };
    voltageBuffer = maxMinVoltages.max;
    histogram_addValue(&histogramMaxCellVoltage, &voltageBuffer);

    const VoltageHistogram* avgVoltageHistogram      = &voltageHistogramConfig.histograms[(
                                                                                         VOLTAGE_HISTOGRAM_AVG_CELL_VOLTAGE_POSITION + checkForOperationMode())
                                                                                     + moduleHistogramOffset];
    const int32_t* const limitsHistogramAvgVoltage[] = {
        &avgVoltageHistogram->systemVoltageLimits[0],
    };
    const uint8_t lengthsAvgVoltage[] = {
        avgVoltageHistogram->systemVoltageLimitsLength,
    };
    const Histogram_t histogramAvgCellVoltage = {
        .counters   = avgVoltageHistogram->counters,
        .dimensions = sizeof(limitsHistogramAvgVoltage) / sizeof(int32_t*),
        .lengths    = &lengthsAvgVoltage[0],
        .limits     = (const int32_t**)&limitsHistogramAvgVoltage[0]
    };
    voltageBuffer = avgVoltage;
    histogram_addValue(&histogramAvgCellVoltage, &voltageBuffer);
}

// @req CB-89325
static uint8_t checkForOperationMode(void)
{
    return stmFct_getDataloggingSelftest() ? VOLTAGE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET : 0u;
}

static void getModuleVoltages(uint16_t* data, uint16_t moduleNumber)
{
    DEBUG_ASSERT(moduleNumber <= BMS_CONFIG_NUMBER_OF_SLAVES);
    for(uint16_t i = 0u; i < CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL; i++)
    {
        data[i] = cellVoltageMeasurement_getValue(moduleNumber, i);
    }
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

// @req CB-89326
void voltageHistogram_mainFunction(void)
{
    for(uint16_t moduleNumber = 0u; moduleNumber < BMS_CONFIG_NUMBER_OF_SLAVES; moduleNumber++)
    {
        addValuesToHistogram(moduleNumber);
    }
}

void voltageHistogram_init(void)
{
#if defined(DEBUG)
    checkConfiguration();
#endif
}

const uint8_t* voltageHistogram_getMinVoltageOperationHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t moduleHistogramOffset = (moduleNumber * VOLTAGE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE);
    *size                          = WARRANTY_DATA_MIN_CELL_VOLTAGE_OPERATION_SIZE;
    uint8_t index                  = VOLTAGE_HISTOGRAM_MIN_CELL_VOLTAGE_POSITION + moduleHistogramOffset;
    DEBUG_API_CHECK(index < voltageHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < voltageHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)voltageHistogramConfig.histograms[index].counters;
    }
    return retVal;
}

const uint8_t* voltageHistogram_getMaxVoltageStorageHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t moduleHistogramOffset = (moduleNumber * VOLTAGE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE);
    *size                          = WARRANTY_DATA_MIN_CELL_VOLTAGE_STORAGE_SIZE;
    uint8_t index                  = (VOLTAGE_HISTOGRAM_MAX_CELL_VOLTAGE_POSITION + VOLTAGE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET) + moduleHistogramOffset;
    DEBUG_API_CHECK(index < voltageHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < voltageHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)voltageHistogramConfig.histograms[index].counters;
    }
    return retVal;
}

const uint8_t* voltageHistogram_getAvgVoltageOperationHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t moduleHistogramOffset = (moduleNumber * VOLTAGE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE);
    *size                          = WARRANTY_DATA_MAX_CELL_VOLTAGE_OPERATION_SIZE;
    uint8_t index                  = VOLTAGE_HISTOGRAM_AVG_CELL_VOLTAGE_POSITION + moduleHistogramOffset;
    DEBUG_API_CHECK(index < voltageHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < voltageHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)voltageHistogramConfig.histograms[index].counters;
    }
    return retVal;
}

const uint8_t* voltageHistogram_getMinVoltageStorageHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t moduleHistogramOffset = (moduleNumber * VOLTAGE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE);
    *size                          = WARRANTY_DATA_MAX_CELL_VOLTAGE_STORAGE_SIZE;
    uint8_t index                  = (VOLTAGE_HISTOGRAM_MIN_CELL_VOLTAGE_POSITION + VOLTAGE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET) + moduleHistogramOffset;
    DEBUG_API_CHECK(index < voltageHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < voltageHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)voltageHistogramConfig.histograms[index].counters;
    }
    return retVal;
}

const uint8_t* voltageHistogram_getMaxVoltageOperationHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t moduleHistogramOffset = (moduleNumber * VOLTAGE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE);
    *size                          = WARRANTY_DATA_AVG_CELL_VOLTAGE_OPERATION_SIZE;
    uint8_t index                  = VOLTAGE_HISTOGRAM_MAX_CELL_VOLTAGE_POSITION + moduleHistogramOffset;
    DEBUG_API_CHECK(index < voltageHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < voltageHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)voltageHistogramConfig.histograms[index].counters;
    }
    return retVal;
}

const uint8_t* voltageHistogram_getAvgVoltageStorageHistogram(uint16_t moduleNumber, uint16_t* size)
{
    uint16_t moduleHistogramOffset = (moduleNumber * VOLTAGE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE);
    *size                          = WARRANTY_DATA_AVG_CELL_VOLTAGE_STORAGE_SIZE;
    uint8_t index                  = (VOLTAGE_HISTOGRAM_AVG_CELL_VOLTAGE_POSITION + VOLTAGE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET) + moduleHistogramOffset;
    DEBUG_API_CHECK(index < voltageHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(index < voltageHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)voltageHistogramConfig.histograms[index].counters;
    }
    return retVal;
}

int32_t* voltageHistogram_getHistogramLimits(uint16_t* size)
{
    DEBUG_API_CHECK((VOLTAGE_HISTOGRAM_AVG_CELL_VOLTAGE_POSITION + VOLTAGE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET) <= voltageHistogramConfig.numberOfHistograms);
    *size = voltageHistogramConfig.histograms[VOLTAGE_HISTOGRAM_AVG_CELL_VOLTAGE_POSITION + VOLTAGE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET].systemVoltageLimitsLength - 1u;
    return voltageHistogramConfig.histograms[VOLTAGE_HISTOGRAM_AVG_CELL_VOLTAGE_POSITION + VOLTAGE_HISTOGRAM_STORAGE_HISTOGRAM_OFFSET].systemVoltageLimits;
}

bool voltageHistogram_setHistogramLimits(int32_t newValue, uint16_t binIndex)
{
    bool success = false;
    if(binIndex < (voltageHistogramConfig.histograms[0].systemVoltageLimitsLength - 1u))
    {
        voltageHistogramConfig.histograms[0].systemVoltageLimits[binIndex] = newValue;
        success                                                            = true;
    }
    return success;
}

void voltageHistogram_resetModuleHistogram(uint8_t moduleNumber)
{
    uint16_t moduleHistogramOffset = (moduleNumber * VOLTAGE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE);

    if(moduleNumber < BMS_CONFIG_NUMBER_OF_SLAVES)
    {
        for(uint16_t i = moduleHistogramOffset; i < (moduleHistogramOffset + VOLTAGE_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE); i++)
        {
            memset(voltageHistogramConfig.histograms[i].counters, 0, voltageHistogramConfig.histograms[i].counterSize * sizeof(voltageHistogramConfig.histograms[i].counters[0]));
        }
    }
}
