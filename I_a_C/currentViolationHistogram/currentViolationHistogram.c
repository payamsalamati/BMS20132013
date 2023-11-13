/**
 * @file currentViolationHistogram.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */

// REQUIREMENTS
// @req CB-89428 CB-89438 CB-89444 CB-89426 CB-89427 CB-89430 CB-89432 CB-89433 CB-89434 CB-89435 CB-89436 CB-89439 CB-93119 CB-93120 CB-93121 CB-93129 CB-93130 CB-93131

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include <stdbool.h>
#include <stdlib.h>
#include "currentViolationHistogram.h"
#include "currentViolationHistogram_config.h"
#include "task_cfg.h"
#include "ringbuffer.h"
#include <stdint.h>
#include "histogram.h"
#include "stateFunctions.h"
#include "idAllocation.h"
#include "downscaledCurrentViolationHistogram.h"

#include "cellTemperatureMeasurement.h"
#include "warrantyData_config.h"
#include "batteryCurrentMeasurement.h"
#include "kbsIntegration.h"
#include "logging.h"
#include "debug.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//
typedef struct
{
    RingValue_int32_t batteryCurrentRingValues[BATTERY_CURRENT_RING_LENGTH];
    RingValue_int32_t maxCharge2sPulseRingValues[MAX_CHARGE_2S_PULSE_RING_LENGTH];
    RingValue_int32_t maxDischarge2sPulseRingValues[MAX_DISCHARGE_2S_PULSE_RING_LENGTH];
    RingValue_int32_t maxCharge100sContRingValues[CURRENT_VIOLATION_CONT_MEAN_RANGE];
    RingValue_int32_t maxDischarge100sContRingValues[CURRENT_VIOLATION_CONT_MEAN_RANGE];
    RingValue_int32_t meanBatteryCurrentContRingValues[MEAN_BATTERY_CURRENT_CONT_RING_LENGTH];
    RingValue_int32_t meanCharge100sContRingValues[MEAN_MAX_CHARGE_100S_CONT_RING_LENGTH];
    RingValue_int32_t meanDischarge100sContRingValues[MEAN_MAX_DISCHARGE_100S_CONT_RING_LENGTH];
    Ring_int32_t batteryCurrentRing;
    Ring_int32_t maxCharge2sPulseRing;
    Ring_int32_t maxDischarge2sPulseRing;
    Ring_int32_t maxCharge100sContRing;
    Ring_int32_t maxDischarge100sContRing;
    Ring_int32_t meanBatteryCurrentContRing;
    Ring_int32_t meanCharge100sContRing;
    Ring_int32_t meanDischarge100sContRing;
} CurrentViolationHistogramData;


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//
static void initializeRingbuffer(void);
static uint16_t getCounterPos(const CurrentViolationHistogram* histogram, int8_t temperature);
static void checkPulseViolation(int32_t batteryCurrent);
static void checkContViolation(int32_t batteryCurrent);
static int32_t calculateMean(Ring_int32_t ring);
static int32_t getCurrentSum(Ring_int32_t CurrentRing, uint16_t length);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//
extern const CurrentViolationHistogramConfig currentViolationHistogramConfig;
MEM_SHAREDATA CurrentViolationHistogramData currentViolationHistogramData;
extern const uint16_t WARRANTY_DATA_CURRENT_VIOLATION_PULSE_SIZE;
extern const uint16_t WARRANTY_DATA_CURRENT_VIOLATION_CONT_SIZE;
MEM_APPLICATION uint8_t contCalculationCounter = 0u;
MEM_APPLICATION bool wasCharging               = false;
extern CurrentViolationHistogramNvm currentViolationHistogramNvm;
MEM_SEC_PARAMETER CurrentViolationConditionParameters currentViolationConditionParameters = {
    .t_regen_limit         = CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_REGENERATION_RMS_LIMIT_IN_S,
    .t_dch_limit           = CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_DISCHARGING_LIMIT_IN_S,
    .t_ch_rms_limit        = CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_CHARGING_RMS_LIMIT_IN_S,
    .t_dch_rms_limit       = CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_DISCHARGING_RMS_LIMIT_IN_S,
    .c_violation           = CURRENT_VIOLATION_DEFAULT_HISTOGRAM_VIOLATION_COEFFICIENT,
    .iContChargeOffset     = CURRENT_VIOLATION_HISTOGRAM_I_CONT_CHARGE_OFFSET,
    .iContDischargeOffset  = CURRENT_VIOLATION_HISTOGRAM_I_CONT_DISCHARGE_OFFSET,
    .iPulseChargeOffset    = CURRENT_VIOLATION_HISTOGRAM_I_PULSE_CHARGE_OFFSET,
    .iPulseDischargeOffset = CURRENT_VIOLATION_HISTOGRAM_I_PULSE_DISCHARGE_OFFSET,
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static void addRingValues()
{
    ringbuffer_insertToRing_int32_t(&currentViolationHistogramData.maxCharge2sPulseRing, kbsIntegration_getDeratingChargeLimit() / 10);
    ringbuffer_insertToRing_int32_t(&currentViolationHistogramData.maxDischarge2sPulseRing, kbsIntegration_getDeratingDischargeLimit() / 10);

    ringbuffer_insertToRing_int32_t(&currentViolationHistogramData.maxCharge100sContRing, kbsIntegration_getDeratingChargeLimitContinous() / 10);
    ringbuffer_insertToRing_int32_t(&currentViolationHistogramData.maxDischarge100sContRing, kbsIntegration_getDeratingDischargeLimitContinous() / 10);
    contCalculationCounter++;
    if(contCalculationCounter >= 4)
    {
        ringbuffer_insertToRing_int32_t(&currentViolationHistogramData.meanBatteryCurrentContRing, calculateMean(currentViolationHistogramData.batteryCurrentRing));
        ringbuffer_insertToRing_int32_t(&currentViolationHistogramData.meanCharge100sContRing, calculateMean(currentViolationHistogramData.maxCharge100sContRing));
        ringbuffer_insertToRing_int32_t(&currentViolationHistogramData.meanDischarge100sContRing, calculateMean(currentViolationHistogramData.maxDischarge100sContRing));
        contCalculationCounter = 0;
    }
}

static void checkPulseViolation(int32_t batteryCurrent)
{
    int32_t batteryCurrentSum       = 0;
    int32_t deratingCurrentLimitSum = 0;
    bool batteryCurrentZero         = false;

    if(batteryCurrent > (currentViolationConditionParameters.iPulseChargeOffset / 1000))
    {
        batteryCurrentSum       = getCurrentSum(currentViolationHistogramData.batteryCurrentRing, currentViolationConditionParameters.t_regen_limit);
        deratingCurrentLimitSum = getCurrentSum(currentViolationHistogramData.maxCharge2sPulseRing, currentViolationConditionParameters.t_regen_limit);
    }
    else if(abs(batteryCurrent) > (currentViolationConditionParameters.iPulseDischargeOffset / 1000))
    {
        batteryCurrentSum       = getCurrentSum(currentViolationHistogramData.batteryCurrentRing, currentViolationConditionParameters.t_dch_limit);
        deratingCurrentLimitSum = getCurrentSum(currentViolationHistogramData.maxDischarge2sPulseRing, currentViolationConditionParameters.t_dch_limit);
    }
    else
    {
        batteryCurrentZero = true;
    }

    deratingCurrentLimitSum *= (float)currentViolationConditionParameters.c_violation * .01;
    if(!batteryCurrentZero && ((batteryCurrentSum >= deratingCurrentLimitSum)))
    {
        int8_t temperature                         = cellTemperatureMeasurement_getAverageValue();
        const CurrentViolationHistogram* histogram = currentViolationHistogramConfig.histograms[CURRENT_VIOLATION_HISTOGRAM_PULSE_HISTOGRAM_POSITION];
        if(batteryCurrent > 0)
        {
            histogram->counters[getCounterPos(histogram, temperature) * 2u]++;
        }
        else
        {
            histogram->counters[(getCounterPos(histogram, temperature) * 2u) + 1u]++;
        }
        downscaledCurrentViolationHistogram_addValues(false);
    }
}

static void checkContViolation(int32_t batteryCurrent)
{
    int32_t batteryCurrentSum       = 0;
    int32_t deratingCurrentLimitSum = 0;
    bool batteryCurrentZero         = false;

    if(batteryCurrent > (currentViolationConditionParameters.iContChargeOffset / 1000))
    {
        batteryCurrentSum       = getCurrentSum(currentViolationHistogramData.meanBatteryCurrentContRing, currentViolationConditionParameters.t_ch_rms_limit / 4u);
        deratingCurrentLimitSum = getCurrentSum(currentViolationHistogramData.meanCharge100sContRing, currentViolationConditionParameters.t_ch_rms_limit / 4u);
    }
    else if(abs(batteryCurrent) > (currentViolationConditionParameters.iContDischargeOffset / 1000))
    {
        batteryCurrentSum       = getCurrentSum(currentViolationHistogramData.meanBatteryCurrentContRing, currentViolationConditionParameters.t_dch_rms_limit / 4u);
        deratingCurrentLimitSum = getCurrentSum(currentViolationHistogramData.meanDischarge100sContRing, currentViolationConditionParameters.t_dch_rms_limit / 4u);
    }
    else
    {
        batteryCurrentZero = true;
    }

    deratingCurrentLimitSum *= (float)currentViolationConditionParameters.c_violation * .01;
    if(!batteryCurrentZero && (batteryCurrentSum >= deratingCurrentLimitSum))
    {
        int8_t temperature                         = cellTemperatureMeasurement_getAverageValue();
        const CurrentViolationHistogram* histogram = currentViolationHistogramConfig.histograms[CURRENT_VIOLATION_HISTOGRAM_CONT_HISTOGRAM_POSITION];
        if(batteryCurrent > 0)
        {
            histogram->counters[getCounterPos(histogram, temperature) * 2u]++;
        }
        else
        {
            histogram->counters[(getCounterPos(histogram, temperature) * 2u) + 1u]++;
        }
        downscaledCurrentViolationHistogram_addValues(true);
    }
}

static int32_t calculateMean(Ring_int32_t ring)
{
    int32_t mean = 0;
    if(ring.index > CURRENT_VIOLATION_CONT_MEAN_RANGE)
    {
        for(int8_t i = ring.index - 2; i > (ring.index - 2 - CURRENT_VIOLATION_CONT_MEAN_RANGE); i--)
        {
            mean += abs(ring.values[i].value);
        }
    }
    else
    {
        int temp = CURRENT_VIOLATION_CONT_MEAN_RANGE - (ring.index - 1);
        for(int8_t i = ring.index - 2; i >= 0; i--)
        {
            mean += abs(ring.values[i].value);
        }
        for(int8_t j = ring.length - 1; j > (ring.length - 1 - temp); j--)
        {
            mean += abs(ring.values[j].value);
        }
    }
    mean /= 4;
    return mean;
}

static int32_t getCurrentSum(Ring_int32_t currentRing, uint16_t length)
{
    int32_t CurrentSum = 0;
    if(currentRing.index > length)
    {
        for(int8_t i = currentRing.index - 2; i > (currentRing.index - 2 - length); i--)
        {
            CurrentSum += currentRing.values[i].value * currentRing.values[i].value;
        }
    }
    else
    {
        int temp = length - (currentRing.index - 1);
        for(int8_t i = currentRing.index - 2; i >= 0; i--)
        {
            CurrentSum += currentRing.values[i].value * currentRing.values[i].value;
        }
        for(int8_t j = currentRing.length - 1; j > (currentRing.length - 1 - temp); j--)
        {
            CurrentSum += currentRing.values[j].value * currentRing.values[j].value;
        }
    }
    return CurrentSum;
}

static void initializeRingbuffer(void)
{
    ringbuffer_init_int32_t(&currentViolationHistogramData.batteryCurrentRing,
                            &currentViolationHistogramData.batteryCurrentRingValues[0],
                            sizeof(currentViolationHistogramData.batteryCurrentRingValues) / sizeof(currentViolationHistogramData.batteryCurrentRingValues[0]));

    ringbuffer_init_int32_t(&currentViolationHistogramData.maxCharge2sPulseRing,
                            &currentViolationHistogramData.maxCharge2sPulseRingValues[0],
                            sizeof(currentViolationHistogramData.maxCharge2sPulseRingValues) / sizeof(currentViolationHistogramData.maxCharge2sPulseRingValues[0]));
    ringbuffer_init_int32_t(&currentViolationHistogramData.maxDischarge2sPulseRing,
                            &currentViolationHistogramData.maxDischarge2sPulseRingValues[0],
                            sizeof(currentViolationHistogramData.maxDischarge2sPulseRingValues) / sizeof(currentViolationHistogramData.maxDischarge2sPulseRingValues[0]));
    ringbuffer_init_int32_t(&currentViolationHistogramData.maxCharge100sContRing,
                            &currentViolationHistogramData.maxCharge100sContRingValues[0],
                            sizeof(currentViolationHistogramData.maxCharge100sContRingValues) / sizeof(currentViolationHistogramData.maxCharge100sContRingValues[0]));
    ringbuffer_init_int32_t(&currentViolationHistogramData.maxDischarge100sContRing,
                            &currentViolationHistogramData.maxDischarge100sContRingValues[0],
                            sizeof(currentViolationHistogramData.maxDischarge100sContRingValues) / sizeof(currentViolationHistogramData.maxDischarge100sContRingValues[0]));
    ringbuffer_init_int32_t(&currentViolationHistogramData.meanBatteryCurrentContRing,
                            &currentViolationHistogramData.meanBatteryCurrentContRingValues[0],
                            sizeof(currentViolationHistogramData.meanBatteryCurrentContRingValues) / sizeof(currentViolationHistogramData.meanBatteryCurrentContRingValues[0]));
    ringbuffer_init_int32_t(&currentViolationHistogramData.meanCharge100sContRing,
                            &currentViolationHistogramData.meanCharge100sContRingValues[0],
                            sizeof(currentViolationHistogramData.meanCharge100sContRingValues) / sizeof(currentViolationHistogramData.meanCharge100sContRingValues[0]));
    ringbuffer_init_int32_t(&currentViolationHistogramData.meanDischarge100sContRing,
                            &currentViolationHistogramData.meanDischarge100sContRingValues[0],
                            sizeof(currentViolationHistogramData.meanDischarge100sContRingValues) / sizeof(currentViolationHistogramData.meanDischarge100sContRingValues[0]));
}

static uint16_t getCounterPos(const CurrentViolationHistogram* histogram, int8_t temperature)
{
    bool found              = false;
    uint16_t returnPosition = 0u;
    uint16_t length         = histogram->counterSize / 2u;
    for(uint8_t i = 1u; (i < (length - 1u)) && (!found); i++)
    {
        if((temperature >= histogram->currentViolationTemperatureLimits[i - 1u]) && (temperature < histogram->currentViolationTemperatureLimits[i]))
        {
            returnPosition = i;
            found          = true;
        }
    }
    if(found == false)
    {
        if(temperature >= histogram->currentViolationTemperatureLimits[length - 2u])
        {
            returnPosition = length - 1u;
        }
    }
    return returnPosition;
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

void currentViolationHistogram_mainFunction(void)
{
    int32_t batteryCurrent = batteryCurrentMeasurement_getValue() / 1000;
    ringbuffer_insertToRing_int32_t(&currentViolationHistogramData.batteryCurrentRing, batteryCurrent);
    addRingValues();
    checkPulseViolation(batteryCurrent);
    checkContViolation(batteryCurrent);
}

void currentViolationHistogram_init(void)
{
    initializeRingbuffer();
}

const uint8_t* currentViolationHistogram_getPulseViolationHistogram(uint16_t* size)
{
    *size = WARRANTY_DATA_CURRENT_VIOLATION_PULSE_SIZE;
    return (const uint8_t*)currentViolationHistogramConfig.histograms[CURRENT_VIOLATION_HISTOGRAM_PULSE_HISTOGRAM_POSITION]->counters;
}

const uint8_t* currentViolationHistogram_getContViolationHistogram(uint16_t* size)
{
    *size = WARRANTY_DATA_CURRENT_VIOLATION_CONT_SIZE;
    return (const uint8_t*)currentViolationHistogramConfig.histograms[CURRENT_VIOLATION_HISTOGRAM_CONT_HISTOGRAM_POSITION]->counters;
}

void currentViolationHistogram_resetHistograms(void)
{
    for(uint8_t i = 0; i < currentViolationHistogramConfig.histograms[CURRENT_VIOLATION_HISTOGRAM_PULSE_HISTOGRAM_POSITION]->counterSize; i++)
    {
        *(currentViolationHistogramConfig.histograms[CURRENT_VIOLATION_HISTOGRAM_PULSE_HISTOGRAM_POSITION]->counters + i) = 0u;
    }

    for(uint8_t j = 0; j < currentViolationHistogramConfig.histograms[CURRENT_VIOLATION_HISTOGRAM_CONT_HISTOGRAM_POSITION]->counterSize; j++)
    {
        *(currentViolationHistogramConfig.histograms[CURRENT_VIOLATION_HISTOGRAM_CONT_HISTOGRAM_POSITION]->counters + j) = 0u;
    }

    currentViolationConditionParameters.t_regen_limit   = CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_REGENERATION_RMS_LIMIT_IN_S;
    currentViolationConditionParameters.t_dch_limit     = CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_DISCHARGING_LIMIT_IN_S;
    currentViolationConditionParameters.t_ch_rms_limit  = CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_CHARGING_RMS_LIMIT_IN_S;
    currentViolationConditionParameters.t_dch_rms_limit = CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_DISCHARGING_RMS_LIMIT_IN_S;
    currentViolationConditionParameters.c_violation     = CURRENT_VIOLATION_DEFAULT_HISTOGRAM_VIOLATION_COEFFICIENT;
}

bool currentViolationHistogram_setConditionParameters(CurrentViolationConditionParameters parameters)
{
    bool retVal = false;
    if((parameters.t_regen_limit <= CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_REGENERATION_RMS_LIMIT_IN_S)
       && (parameters.t_dch_limit <= CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_DISCHARGING_LIMIT_IN_S)
       && (parameters.t_ch_rms_limit <= CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_CHARGING_RMS_LIMIT_IN_S)
       && (parameters.t_dch_rms_limit <= CURRENT_VIOLATION_DEFAULT_HISTOGRAM_TIME_DISCHARGING_RMS_LIMIT_IN_S)
       && (parameters.c_violation <= CURRENT_VIOLATION_MAX_HISTOGRAM_VIOLATION_COEFFICIENT))
    {
        currentViolationConditionParameters.t_regen_limit   = parameters.t_regen_limit;
        currentViolationConditionParameters.t_dch_limit     = parameters.t_dch_limit;
        currentViolationConditionParameters.t_ch_rms_limit  = parameters.t_ch_rms_limit;
        currentViolationConditionParameters.t_dch_rms_limit = parameters.t_dch_rms_limit;
        currentViolationConditionParameters.c_violation     = parameters.c_violation;
        retVal                                              = true;
    }
    return retVal;
}

CurrentViolationConditionParameters currentViolationHistogram_getConditionParameters()
{
    return currentViolationConditionParameters;
}

void currentViolationHistogram_checkNvm(const uint8_t* mirror, uint16_t length)
{
    DEBUG_API_CHECK(length == sizeof(CurrentViolationHistogramNvm));
    if((nvm_getErrorStatus(NVM_CURRENT_VIOLATION_HISTOGRAM_BLOCK_ID) == NVM_REQ_OK) && (sizeof(CurrentViolationHistogramNvm) == length))
    {
        memcpy((uint8_t*)&currentViolationHistogramNvm, mirror, sizeof(CurrentViolationHistogramNvm));
    }
    else
    {
        // do nothing
    }
}

void currentViolationHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
    memcpy(mirror, (uint8_t*)&currentViolationHistogramNvm, sizeof(CurrentViolationHistogramNvm));
}
