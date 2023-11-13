/**
 * @file cpsMonitor.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <math.h>
#include "cpsMonitor.h"
#include "dem.h"
#include "demUDS.h"
#include "task_cfg.h"
#include "cpsMonitor_config.h"
#include "nvm.h"
#include "demUDS.h"

#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
#include "alternativeMemFunctions.h"
#endif

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    uint8_t CPS_CPSout;
    uint8_t BMS_REQ_CPSout;
    uint16_t errorCounter;
    uint16_t validCounter;
    bool faultActive;
} CPSout;

typedef struct CPSMonitorConfig
{
    uint16_t errorLimit;
    uint16_t validLimit;
} CPSMonitorConfig;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static bool cpsMonitor_checkCpsOutAndIncreaseCounters(void);
static void cpsMonitor_checkLimitAndThrowError(void);
static void cpsMonitor_checkLimitAndClearError(void);
static void cpsMonitor_storeCpsOutDtcTimestamp(uint32_t timestamp, uint8_t occurrenceCounter);
static uint32_t cpsMonitor_getMaxTimestampDifferenceIns();
static void cpsMonitor_checkCpsOutOverload(void);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SEC_PARAMETER CPSMonitorConfig cpsMonitorConfig = {
    .errorLimit = CPS_MONITOR_DEFAULT_CPS_OUT_ERROR_LIMIT,
    .validLimit = CPS_MONITOR_DEFAULT_CPS_OUT_VALID_LIMIT
};

static MEM_SHAREDATA CPSout data = {
    .CPS_CPSout     = 0u,
    .BMS_REQ_CPSout = 0u,
    .errorCounter   = 0u,
    .validCounter   = 0u,
    .faultActive    = false,
};

MEM_APPLICATION CPSoutNvm cpsOutNvm = {
    .cpsOutDtcTimestamps = { 0 }
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static bool cpsMonitor_checkCpsOutAndIncreaseCounters(void)
{
    bool retVal = false;
    if(data.CPS_CPSout == data.BMS_REQ_CPSout)
    {
        retVal            = true;
        data.errorCounter = 0u;
        data.validCounter++;
    }
    else
    {
        data.errorCounter++;
        data.validCounter = 0;
    }
    return retVal;
}

static void cpsMonitor_checkLimitAndThrowError(void)
{
    if(data.errorCounter >= cpsMonitorConfig.errorLimit)
    {
        DEM_FaultCode fault = DTC_BMS_CPSOUT_STATUS_NOT_CORRECT;
        data.faultActive    = true;
        data.errorCounter   = 0u;
        dem_reportFaultFromApp(fault);
        cpsMonitor_checkCpsOutOverload();
    }
}

static void cpsMonitor_checkLimitAndClearError(void)
{
    if(data.faultActive == true)
    {
        if(data.validCounter >= cpsMonitorConfig.validLimit)
        {
            DEM_FaultCode fault = DTC_BMS_CPSOUT_STATUS_NOT_CORRECT;
            data.faultActive    = false;
            data.validCounter   = 0u;
            dem_clearFaultFromApp(fault);
        }
    }
}

static void cpsMonitor_storeCpsOutDtcTimestamp(uint32_t timestamp, uint8_t occurrenceCounter)
{
    uint8_t index                        = (uint8_t)((occurrenceCounter - 1u) % 3u);
    cpsOutNvm.cpsOutDtcTimestamps[index] = timestamp;
}

static uint32_t cpsMonitor_getMaxTimestampDifferenceIns()
{
    uint32_t maxValue = 0;
    for(uint8_t i = 0; i < 2u; i++)
    {
        for(uint8_t j = i + 1u; j < 3u; j++)
        {
            uint32_t timeDifferenceInms = abs(cpsOutNvm.cpsOutDtcTimestamps[i] - cpsOutNvm.cpsOutDtcTimestamps[j]);
            if(timeDifferenceInms > maxValue)
            {
                maxValue = timeDifferenceInms;
            }
        }
    }
    return maxValue;
}

static void cpsMonitor_checkCpsOutOverload(void)
{
    DTCExtendedData buffer;
    demUDS_getLastLoadedExtendedBuffer(&buffer);

    DTCExtendedKion* extendedKion = (DTCExtendedKion*)&buffer.data;
    cpsMonitor_storeCpsOutDtcTimestamp(extendedKion->lastOccurenceTime, extendedKion->totalOccurences);
    if(extendedKion->totalOccurences >= BMS_CPSOUT_OVERLOAD_MAX_NUMBER_OF_OCCURRENCE)
    {
        uint32_t timeDifferenceInh = (uint32_t)(cpsMonitor_getMaxTimestampDifferenceIns() / (uint32_t)3600);
        if(timeDifferenceInh < BMS_CPSOUT_OVERLOAD_MAX_TIME_IN_HOURS)
        {
            DEM_FaultCode fault = DTC_BMS_CPSOUT_OVERLOAD;
            dem_reportFaultFromApp(fault);
        }
    }
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//


void cpsMonitor_checkNvm(const uint8_t* mirror, uint16_t length)
{
    if((nvm_getErrorStatus(NVM_CPS_MONITOR_BLOCK_ID) == NVM_REQ_OK) && (sizeof(CPSoutNvm) == length))
    {
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
        alternativeMemFunctions_memcpy((uint8_t*)&cpsOutNvm, mirror, sizeof(CPSoutNvm));
#else
        memcpy((uint8_t*)&cpsOutNvm, mirror, sizeof(CPSoutNvm));
#endif
    }
}

void cpsMonitor_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
    alternativeMemFunctions_memcpy(mirror, (uint8_t*)&cpsOutNvm, sizeof(CPSoutNvm));
#else
    memcpy(mirror, (uint8_t*)&cpsOutNvm, sizeof(CPSoutNvm));
#endif
}

void cpsMonitor_setCPSout(uint8_t newValue)
{
    data.CPS_CPSout    = newValue;
    bool cpsOutSuccess = cpsMonitor_checkCpsOutAndIncreaseCounters();

    if(cpsOutSuccess == false)
    {
        cpsMonitor_checkLimitAndThrowError();
    }
    else
    {
        cpsMonitor_checkLimitAndClearError();
    }
}

void cpsMonitor_setBMS_REQ_CPSout(uint8_t newValue)
{
    data.BMS_REQ_CPSout = newValue;
}

void cpsMonitor_setErrorLimit(uint16_t newValue)
{
    cpsMonitorConfig.errorLimit = newValue;
}
