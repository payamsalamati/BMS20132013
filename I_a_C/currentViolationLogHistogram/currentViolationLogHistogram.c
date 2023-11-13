/**
 * @file currentViolationLogHistogram.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "currentViolationLogHistogram.h"
#if defined(UNIT_TEST)
#include "test/test_currentViolationLogHistogram_config.h"
#else
#include "currentViolationLogHistogram_config.h"
#endif

#include "histogram.h"
#include "batteryCurrentMeasurement.h"
#include "timestamp.h"
#include "debug.h"
#include "task_cfg.h"
#include "nvm.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    CurrentViolationLogHistogramRing rings[CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_RINGS];
    bool initialized;
} CurrentViolationLogHistogramData;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static uint8_t getSectionIndex(const int32_t* limits, uint8_t limitSize, int32_t batteryCurrent);
static void initializeRingValues(void);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_WARRANTYDATA CurrentViolationLogHistogramData curentViolationLogHistogramData = { 0 };
MEM_WARRANTYDATA CurrentViolationLogHistogramNvm currentViolationLogHistogramNvm;
extern MEM_SEC_PARAMETER int32_t currentViolationLogHistogramCurrentBinsInA[CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_LIMITS];

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static uint8_t getSectionIndex(const int32_t* limits, uint8_t limitSize, int32_t batteryCurrent)
{
    uint8_t index = 0u;
    while((index < limitSize) && (batteryCurrent >= (limits[index] * 1000)))
    {
        index++;
    }
    return (index - 1u);
}

static void initializeRingValues(void)
{
    for(uint8_t ringIndex = 0u; ringIndex < CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_RINGS; ringIndex++)
    {
        for(uint8_t valueIndex = 0u; valueIndex < CURRENT_VIOLATION_LOG_HISTOGRAM_VALUES_IN_RING; valueIndex++)
        {
            uint8_t nvmCopyIndex                                                             = ((ringIndex * CURRENT_VIOLATION_LOG_HISTOGRAM_VALUES_IN_RING) + valueIndex);
            curentViolationLogHistogramData.rings[ringIndex].ringValues[valueIndex].value    = currentViolationLogHistogramNvm.events[nvmCopyIndex];
            curentViolationLogHistogramData.rings[ringIndex].ringValues[valueIndex].addIndex = (valueIndex + 1u);
        }
        curentViolationLogHistogramData.rings[ringIndex].ring.values = &(curentViolationLogHistogramData.rings[ringIndex].ringValues[0u]);
        curentViolationLogHistogramData.rings[ringIndex].ring.index  = 1u;
        curentViolationLogHistogramData.rings[ringIndex].ring.length = CURRENT_VIOLATION_LOG_HISTOGRAM_VALUES_IN_RING;
    }
    curentViolationLogHistogramData.initialized = true;
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

// @req CB-89452 CB-89455
void currentViolationLogHistogram_mainFunction(void)
{
    if(curentViolationLogHistogramData.initialized == true)
    {
        int32_t batteryCurrent = batteryCurrentMeasurement_getValue();
        if(batteryCurrent >= (currentViolationLogHistogramCurrentBinsInA[0] * 1000))
        {
            uint16_t sectionIndex = getSectionIndex(&currentViolationLogHistogramCurrentBinsInA[0], CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_LIMITS, batteryCurrent);
            uint32_t timestamp    = timestamp_getUnixTime();
            ringbuffer_insertToRing_uint32_t(&curentViolationLogHistogramData.rings[sectionIndex].ring, timestamp);
        }
    }
    else
    {
        initializeRingValues();
    }
}

CurrentViolationLogHistogramRing* currentViolationLogHistogram_getHistogram(uint16_t* size)
{
    *size = CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_RINGS;
    return (&curentViolationLogHistogramData.rings[0]);
}

void currentViolationLogHistogram_resetHistogram(void)
{
    memset(&currentViolationLogHistogramNvm, 0, sizeof(CurrentViolationLogHistogramNvm));
    curentViolationLogHistogramData.initialized = false;
}

int32_t* currentViolationLogHistogram_getHistogramLimits(uint8_t* size)
{
    *size = CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_LIMITS;
    return &(currentViolationLogHistogramCurrentBinsInA[0]);
}

bool currentViolationLogHistogram_setHistogramLimits(int32_t newValue, uint8_t binIndex)
{
    bool success = false;
    if(binIndex < CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_LIMITS)
    {
        currentViolationLogHistogramCurrentBinsInA[binIndex] = newValue;
        success                                              = true;
    }
    return success;
}

void currentViolationLogHistogram_checkNvm(const uint8_t* mirror, uint16_t length)
{
    DEBUG_API_CHECK(length == sizeof(CurrentViolationLogHistogramNvm));
    if((nvm_getErrorStatus(NVM_CURRENT_VIOLATION_LOG_HISTOGRAM_BLOCK_ID) == NVM_REQ_OK) && (sizeof(CurrentViolationLogHistogramNvm) == length))
    {
        memcpy((uint8_t*)&currentViolationLogHistogramNvm, mirror, sizeof(CurrentViolationLogHistogramNvm));
    }
    else
    {
        currentViolationLogHistogram_resetHistogram();
    }
    initializeRingValues();
}

void currentViolationLogHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
    for(uint8_t ringIndex = 0u; ringIndex < CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_RINGS; ringIndex++)
    {
        for(uint8_t valueIndex = 0u; valueIndex < CURRENT_VIOLATION_LOG_HISTOGRAM_VALUES_IN_RING; valueIndex++)
        {
            uint8_t nvmCopyIndex                                 = ((ringIndex * CURRENT_VIOLATION_LOG_HISTOGRAM_VALUES_IN_RING) + valueIndex);
            currentViolationLogHistogramNvm.events[nvmCopyIndex] = curentViolationLogHistogramData.rings[ringIndex].ringValues[valueIndex].value;
        }
    }
    memcpy(mirror, (uint8_t*)&currentViolationLogHistogramNvm, sizeof(CurrentViolationLogHistogramNvm));
}
