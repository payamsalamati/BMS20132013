/**
 * @file masterPcbTemperatureHistogram.c
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
#include "masterPcbTemperatureHistogram.h"

#include <stdint.h>
#include <stdbool.h>
#include "histogram.h"

#include "debug.h"
#include "idAllocation.h"
#include "stateFunctions.h"
#include "fut_math.h"
#include "measurements_getOnBoardTemperature.h"


//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//

static void incrementCounter();
static uint16_t getCounterPos(const int16_t* bins, uint16_t length, int16_t value);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

extern const MasterPcbTemperatureHistogram masterPcbTemperatureHistogram;
extern const MasterPcbTemperatureHistogramNvm masterPcbTemperatureHistogramNvm;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static uint16_t getCounterPos(const int16_t* bins, uint16_t length, int16_t value)
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


static void incrementCounter()
{
    int16_t temperature = measurements_getOnBoardTemperature_getTSensorOnMaster();
    uint16_t bin        = getCounterPos(masterPcbTemperatureHistogram.temperatureLimits, MASTER_PCB_TEMPERATURE_HISTOGRAM_LIMITS_SIZE + 1u, temperature);
    masterPcbTemperatureHistogram.counters[bin]++;
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

// @req CB-89562 CB-89563 CB-89564 CB-16489 CB-78693
void masterPcbTemperatureHistogram_mainFunction(void)
{
    incrementCounter();
}


const uint8_t* masterPcbTemperatureHistogram_getHistogram(uint16_t* size)
{
    *size = masterPcbTemperatureHistogram.counterSize;
    return (const uint8_t*)masterPcbTemperatureHistogram.counters;
}


void masterPcbTemperatureHistogram_resetHistogram()
{
    memset(masterPcbTemperatureHistogram.counters, 0, masterPcbTemperatureHistogram.counterSize * sizeof(masterPcbTemperatureHistogram.counters[0]));
}

int16_t* masterPcbTemperatureHistogram_getHistogramBins(uint16_t* size)
{
    *size = MASTER_PCB_TEMPERATURE_HISTOGRAM_LIMITS_SIZE;
    return masterPcbTemperatureHistogram.temperatureLimits;
}


void masterPcbTemperatureHistogram_checkNvm(const uint8_t* mirror, uint16_t length)
{
    DEBUG_API_CHECK(length == sizeof(MasterPcbTemperatureHistogramNvm));
    if((nvm_getErrorStatus(NVM_MASTER_PCB_TEMPERATURE_HISTOGRAM_BLOCK_ID) == NVM_REQ_OK) && (sizeof(MasterPcbTemperatureHistogramNvm) == length))
    {
        memcpy((uint8_t*)&masterPcbTemperatureHistogramNvm, mirror, sizeof(MasterPcbTemperatureHistogramNvm));
    }
}

void masterPcbTemperatureHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
    memcpy(mirror, &masterPcbTemperatureHistogramNvm, sizeof(MasterPcbTemperatureHistogramNvm));
}
