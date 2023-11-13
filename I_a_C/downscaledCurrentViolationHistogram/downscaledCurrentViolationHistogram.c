/**
 * @file downscaledCurrentViolationHistogram.c
 * @copyright (c) Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
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
#include "downscaledCurrentViolationHistogram.h"

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
#include "cscNvm_config.h"


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
static bool checkConfiguration(void);
static void getModuleTemperatures(int16_t* data, uint16_t moduleNumber);
static void incrementCounter(uint8_t module, bool cont);
static uint16_t getCounterPos(const DownscaledCurrentViolationHistogram* histogram, int8_t temperature);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

extern const DownscaledCurrentViolationHistogramConfig downscaledCurrentViolationHistogramConfig;
extern DownscaledCurrentViolationHistogramNvm downscaledCurrentViolationHistogramCountersModule[BMS_CONFIG_MAX_NUMBER_OF_SLAVES];

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static bool checkConfiguration(void)
{
    bool retVal = true;
    for(uint8_t i = 0; i < downscaledCurrentViolationHistogramConfig.numberOfHistograms; i++)
    {
        const DownscaledCurrentViolationHistogram* histogram = &downscaledCurrentViolationHistogramConfig.histograms[i];
        if((histogram == NULL) || (histogram->counters == NULL) || (histogram->downscaledCurrentViolationCellTemperatureLimits == NULL) || (histogram->counterSize != DOWNSCALED_CURRENT_VIOLATION_HISTOGRAM_COUNTER_SIZE))
        {
            retVal = false;
        }
    }
    return retVal;
}

static void getModuleTemperatures(int16_t* data, uint16_t moduleNumber)
{
    DEBUG_ASSERT(moduleNumber <= BMS_CONFIG_NUMBER_OF_SLAVES);
    for(uint16_t i = 0u; i < BMS_CONFIG_NUMBER_OF_TEMPERATURE_SENSORS; i++)
    {
        data[i] = cellTemperatureMeasurement_getValue(moduleNumber, i);
    }
}

static uint16_t getCounterPos(const DownscaledCurrentViolationHistogram* histogram, int8_t temperature)
{
    bool found              = false;
    uint16_t returnPosition = 0u;
    uint16_t length         = histogram->counterSize / 2u;
    for(uint8_t i = 1u; (i < (length - 1u)) && (!found); i++)
    {
        if((temperature >= histogram->downscaledCurrentViolationCellTemperatureLimits[i - 1u]) && (temperature < histogram->downscaledCurrentViolationCellTemperatureLimits[i]))
        {
            returnPosition = i;
            found          = true;
        }
    }
    if(found == false)
    {
        if(temperature > histogram->downscaledCurrentViolationCellTemperatureLimits[length - 2u])
        {
            returnPosition = length - 1u;
        }
    }
    return returnPosition;
}

static void incrementCounter(uint8_t module, bool cont)
{
    const DownscaledCurrentViolationHistogram* histogram = &downscaledCurrentViolationHistogramConfig.histograms[module];
    // cppcheck-suppress misra-c2012-18.8 ; define is constant.
    int16_t moduleTemperatures[BMS_CONFIG_MAX_NUMBER_OF_TEMPERATURE_SENSORS] = { 0 };
    getModuleTemperatures(moduleTemperatures, module);
    int16_t avgTemperatures = average_s16(moduleTemperatures, BMS_CONFIG_NUMBER_OF_TEMPERATURE_SENSORS);
    if(cont)
    {
        histogram->counters[(getCounterPos(histogram, avgTemperatures) * 2u) + 1u]++;
    }
    else
    {
        histogram->counters[getCounterPos(histogram, avgTemperatures) * 2u]++;
    }
    const DownscaledCurrentViolationHistogramNvm* histogramsNvm = (const DownscaledCurrentViolationHistogramNvm*)&downscaledCurrentViolationHistogramCountersModule;
    cscNvm_setDownscaledCurrentViolationHistogramCounters(histogramsNvm[module], module + 1u);
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

void downscaledCurrentViolationHistogram_init(void)
{
    for(uint8_t cscAddress = 1; cscAddress <= BMS_CONFIG_MAX_NUMBER_OF_SLAVES; cscAddress++)
    {
        DownscaledCurrentViolationHistogramNvm nvmHistogram = cscNvm_getDownscaledCurrentViolationHistogramCounters(cscAddress);
        memcpy(&downscaledCurrentViolationHistogramCountersModule[cscAddress - 1], &nvmHistogram, sizeof(DownscaledCurrentViolationHistogramNvm));
    }
    checkConfiguration();
}

// @req CB-89441
void downscaledCurrentViolationHistogram_addValues(bool cont)
{
    for(uint8_t i = 0u; i < BMS_CONFIG_NUMBER_OF_SLAVES; i++)
    {
        incrementCounter(i, cont);
    }
}


const uint8_t* downscaledCurrentViolationHistogram_getHistogram(uint16_t moduleNumber, uint16_t* size)
{
    *size = (uint16_t)DOWNSCALED_CURRENT_VIOLATION_HISTOGRAM_COUNTER_SIZE;
    DEBUG_API_CHECK(moduleNumber < downscaledCurrentViolationHistogramConfig.numberOfHistograms);
    const uint8_t* retVal = NULL;
    if(moduleNumber < downscaledCurrentViolationHistogramConfig.numberOfHistograms)
    {
        retVal = (const uint8_t*)downscaledCurrentViolationHistogramConfig.histograms[moduleNumber].counters;
    }
    return retVal;
}


void downscaledCurrentViolationHistogram_resetModuleHistogram(uint8_t moduleNumber)
{
    if(moduleNumber < BMS_CONFIG_NUMBER_OF_SLAVES)
    {
        memset(downscaledCurrentViolationHistogramConfig.histograms[moduleNumber].counters, 0, downscaledCurrentViolationHistogramConfig.histograms[moduleNumber].counterSize * sizeof(downscaledCurrentViolationHistogramConfig.histograms[moduleNumber].counters[0]));
    }
}
