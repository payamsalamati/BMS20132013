/**
 * @file voltageContactorHistogram.c
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
#include "voltageContactorHistogram.h"
#include "task_cfg.h"
#include <stdint.h>
#include "histogram.h"
#include "stateFunctions.h"
#include "nvm.h"
#include "nvm_config_id.h"

#include "debug.h"
#include "cellVoltageMeasurement.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static uint16_t getCounterPos(const int32_t* bins, uint16_t length, int16_t value);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//
extern const VoltageContactorHistogram voltageContactorHistogram;
extern VoltageContactorHistogramNvm voltageContactorHistogramNvm;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static uint16_t getCounterPos(const int32_t* bins, uint16_t length, int16_t value)
{
    uint16_t pos = 0;
    bool found   = false;
    for(uint16_t i = 0u; (i < length) && (!found); i++)
    {
        if((100 + bins[length - i - 1u]) <= value)
        {
            pos   = i;
            found = true;
        }
    }
    for(uint16_t j = 1u; (j < length) && (!found); j++)
    {
        if((100 - bins[j]) <= value)
        {
            pos   = j + length - 1u;
            found = true;
        }
    }

    if(!found)
    {
        pos = (length * 2u) - 1u;
    }
    return pos;
}

static int16_t calculateDeviation(uint16_t voltageBeforeEvent, uint16_t voltageAfterEvent)
{
    return abs((int16_t)(((1.0f - (((float)voltageBeforeEvent - (float)voltageAfterEvent) / (float)voltageBeforeEvent)) * 100.0f) + 0.5f));
}

static void increaseCounter(int16_t deviation, uint8_t contactor)
{
    uint16_t counterPos = getCounterPos(voltageContactorHistogram.deviationLimits, voltageContactorHistogram.deviationLimitsSize, deviation);
    if(counterPos < voltageContactorHistogram.counterSize)
    {
        voltageContactorHistogram.counters[counterPos + (contactor * (voltageContactorHistogram.counterSize / 2))]++;
    }
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

// @req CB-89771 CB-89835 CB-91615 CB-91618
void voltageContactorHistogram_mainFunction(uint8_t contactor, VoltageContactorHistogramEvent event)
{
    DEBUG_ASSERT(contactor <= 1u);
    if(event == VOLTAGE_CONTACTOR_HISTOGRAM_BEFORE_CONTACTOR_CLOSED)
    {
        *voltageContactorHistogram.voltageBeforeEvent = cellVoltageMeasurement_getAverageValue();
    }
    else if(event == VOLTAGE_CONTACTOR_HISTOGRAM_AFTER_CONTACTOR_CLOSED)
    {
        uint16_t voltageAfterEvent = cellVoltageMeasurement_getAverageValue();
        int16_t deviation          = calculateDeviation(*voltageContactorHistogram.voltageBeforeEvent, voltageAfterEvent);
        increaseCounter(deviation, contactor);
    }
    else
    {
    }
}

const uint8_t* voltageContactorHistogram_getHistogram(uint16_t* size)
{
    *size = voltageContactorHistogram.counterSize;
    return (const uint8_t*)voltageContactorHistogram.counters;
}

const int32_t* voltageContactorHistogram_getHistogramBins(uint16_t* size)
{
    *size = voltageContactorHistogram.deviationLimitsSize;
    return (const int32_t*)voltageContactorHistogram.deviationLimits;
}

void voltageContactorHistogram_resetHistogram(void)
{
    memset(voltageContactorHistogram.counters, 0, voltageContactorHistogram.counterSize * sizeof(voltageContactorHistogram.counters[0]));
}

void voltageContactorHistogram_checkNvm(const uint8_t* mirror, uint16_t length)
{
    DEBUG_API_CHECK(length == sizeof(VoltageContactorHistogramNvm));

    if((nvm_getErrorStatus(NVM_VOLTAGE_CONTACTOR_HISTOGRAM_BLOCK_ID) == NVM_REQ_OK) && (sizeof(VoltageContactorHistogramNvm) == length))
    {
        memcpy((uint8_t*)&voltageContactorHistogramNvm, mirror, sizeof(VoltageContactorHistogramNvm));
    }
}

void voltageContactorHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
    memcpy(mirror, &voltageContactorHistogramNvm, sizeof(VoltageContactorHistogramNvm));
}
