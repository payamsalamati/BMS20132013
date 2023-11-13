/**
 * @file socTemperatureHistogram.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */

// REQUIREMENTS
// @req CB-89766 CB-89776 CB-10384 CB-89766 CB-89647

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include <stdbool.h>
#include <stdlib.h>
#include "socTemperatureHistogram.h"
#include "task_cfg.h"
#include <stdint.h>
#include "histogram.h"
#include "stateFunctions.h"
#include "idAllocation.h"

#include "cellTemperatureMeasurement.h"
#include "warrantyData_config.h"
#include "batteryCurrentMeasurement.h"
#include "kbsIntegration.h"
#include "logging.h"
#include "debug.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static uint16_t getCounterPos(const int32_t* bins, uint16_t length, int32_t value);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//
extern const SocTemperatureHistogram socTemperatureHistogram;
extern SocTemperatureHistogramNvm socTemperatureHistogramNvm;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static uint16_t getCounterPos(const int32_t* bins, uint16_t length, int32_t value)
{
    uint16_t retVal = length - 1u;
    for(uint16_t i = 0; i < (length - 1u); i++)
    {
        if(value < bins[i])
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

void socTemperatureHistogram_mainFunction(void)
{
    int32_t soc            = kbsIntegration_getSocWithoutSOH_Internal();
    int32_t temperature    = cellTemperatureMeasurement_getAverageValue();
    uint8_t socBin         = getCounterPos(socTemperatureHistogram.limits->socTemperatureHistogramSocLimits, SOC_HISTOGRAM_LIMITS_SIZE + 1u, soc);
    uint8_t temperatureBin = getCounterPos(socTemperatureHistogram.limits->socTemperatureHistogramTemperatureLimits, BATTERY_TEMPERATURE_LIMITS_SIZE + 1u, temperature);
    socTemperatureHistogram.counters[temperatureBin + (socBin * (BATTERY_TEMPERATURE_LIMITS_SIZE + 1u))]++;
}

const uint8_t* socTemperatureHistogram_getHistogram(uint16_t* size)
{
    *size = SOC_TEMPERATURE_HISTOGRAM_COUNTER_SIZE;
    return (const uint8_t*)socTemperatureHistogram.counters;
}

void socTemperatureHistogram_resetHistogram(void)
{
    memset(socTemperatureHistogram.counters, 0, socTemperatureHistogram.counterSize * sizeof(socTemperatureHistogram.counters[0]));
}

int32_t* socTemperatureHistogram_getTemperatureBins(uint16_t* size)
{
    *size = BATTERY_TEMPERATURE_LIMITS_SIZE;
    return socTemperatureHistogram.limits->socTemperatureHistogramTemperatureLimits;
}

int32_t* socTemperatureHistogram_getSocBins(uint16_t* size)
{
    *size = SOC_HISTOGRAM_LIMITS_SIZE;
    return socTemperatureHistogram.limits->socTemperatureHistogramSocLimits;
}


void socTemperatureHistogram_checkNvm(const uint8_t* mirror, uint16_t length)
{
    DEBUG_API_CHECK(length == sizeof(SocTemperatureHistogramNvm));

    if((nvm_getErrorStatus(NVM_SOC_TEMPERATURE_HISTOGRAM_BLOCK_ID) == NVM_REQ_OK) && (sizeof(SocTemperatureHistogramNvm) == length))
    {
        memcpy((uint8_t*)&socTemperatureHistogramNvm, mirror, sizeof(SocTemperatureHistogramNvm));
    }
    else
    {
        // do nothing
    }
}

void socTemperatureHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
    memcpy(mirror, (uint8_t*)&socTemperatureHistogramNvm, sizeof(SocTemperatureHistogramNvm));
}
