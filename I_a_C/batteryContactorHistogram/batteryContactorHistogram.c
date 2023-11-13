/**
 * @file batteryContactorHistogram.c
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
#include <stdbool.h>
#include <stdlib.h>
#include "batteryContactorHistogram.h"
#include "task_cfg.h"
#include <stdint.h>
#include "histogram.h"
#include "stateFunctions.h"
#include "idAllocation.h"

#include "cellTemperatureMeasurement.h"
#include "warrantyData_config.h"
#include "batteryCurrentMeasurement.h"
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
extern const BatteryContactorHistogram batteryContactorHistogram;
extern BatteryContactorHistogramNvm batteryContactorHistogramNvm;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static uint16_t getCounterPos(const int32_t* bins, uint16_t length, int32_t value)
{
    bool found              = false;
    uint16_t returnPosition = 0u;
    for(uint8_t i = 1u; (i < (length - 1u)) && (!found); i++)
    {
        if((value >= bins[i - 1u]) && (value < bins[i]))
        {
            returnPosition = i;
            found          = true;
        }
    }
    if(found == false)
    {
        if(value >= bins[length - 2u])
        {
            returnPosition = length - 1u;
        }
    }
    return returnPosition;
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

// @req CB-89560 CB-89559 CB-89561 CB-16486
void batteryContactorHistogram_incrementCounter(uint8_t contactor)
{
    if(contactor <= 1u)
    {
        int32_t current = batteryCurrentMeasurement_getValue();
        uint16_t bin    = getCounterPos(batteryContactorHistogram.currentLimits, BATTERY_CONTACTOR_HISTOGRAM_LIMITS_SIZE + 1u, current);
        batteryContactorHistogram.counters[(bin * (BATTERY_CONTACTOR_HISTOGRAM_COUNTER_SIZE / (BATTERY_CONTACTOR_HISTOGRAM_LIMITS_SIZE + 1u))) + contactor]++;
    }
}

const uint8_t* batteryContactorHistogram_getHistogram(uint16_t* size)
{
    *size = BATTERY_CONTACTOR_HISTOGRAM_COUNTER_SIZE;
    return (const uint8_t*)batteryContactorHistogram.counters;
}

void batteryContactorHistogram_resetHistogram(void)
{
    memset(batteryContactorHistogram.counters, 0, batteryContactorHistogram.counterSize * sizeof(batteryContactorHistogram.counters[0]));
}

int32_t* batteryContactorHistogram_getHistogramBins(uint16_t* size)
{
    *size = BATTERY_CONTACTOR_HISTOGRAM_LIMITS_SIZE;
    return batteryContactorHistogram.currentLimits;
}

void batteryContactorHistogram_checkNvm(const uint8_t* mirror, uint16_t length)
{
    DEBUG_API_CHECK(length == sizeof(BatteryContactorHistogramNvm));

    if((nvm_getErrorStatus(NVM_BATTERY_CONTACTOR_HISTOGRAM_BLOCK_ID) == NVM_REQ_OK) && (sizeof(BatteryContactorHistogramNvm) == length))
    {
        memcpy((uint8_t*)&batteryContactorHistogramNvm, mirror, sizeof(BatteryContactorHistogramNvm));
    }
}

void batteryContactorHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
    memcpy(mirror, &batteryContactorHistogramNvm, sizeof(BatteryContactorHistogramNvm));
}
