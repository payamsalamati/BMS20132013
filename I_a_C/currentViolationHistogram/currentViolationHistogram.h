

/**
 * @file currentViolationHistogram.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  creates a histogram, that documents, if the cellvoltage is crossing the defined
 *  borders depending on the current batterystate
 *
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include <stdint.h>
#include <stdbool.h>
#include "currentViolationHistogram_config.h"
#include "nvm_config_id.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef struct
{
    uint8_t t_regen_limit;
    uint8_t t_dch_limit;
    uint16_t t_ch_rms_limit;
    uint16_t t_dch_rms_limit;
    uint8_t c_violation;
    uint16_t iContChargeOffset;
    uint16_t iContDischargeOffset;
    uint16_t iPulseChargeOffset;
    uint16_t iPulseDischargeOffset;
} CurrentViolationConditionParameters;
typedef struct
{
    uint8_t* currentViolationTimes;
    uint8_t currentViolationTimesLength;
    const int8_t* currentViolationTemperatureLimits;
    uint8_t currentViolationTemperatureLimitsLength;
    uint32_t* counters;
    uint16_t counterSize;
} CurrentViolationHistogram;

typedef struct
{
    const CurrentViolationHistogram* const* histograms;
    uint8_t numberOfHistograms;
} CurrentViolationHistogramConfig;

typedef struct
{
    uint32_t countersHistogramPulse[CURRENT_VIOLATION_HISTOGRAM_PULSE_COUNTER_SIZE];
    uint32_t countersHistogramCont[CURRENT_VIOLATION_HISTOGRAM_CONT_COUNTER_SIZE];
} CurrentViolationHistogramCounter;

typedef struct
{
    CurrentViolationHistogramCounter counters;
} CurrentViolationHistogramNvm;


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
/**
 * @brief increment histogramcounters of the voltage histogram
 *
 */
void currentViolationHistogram_mainFunction(void);

/**
 * @brief get histogram counters from NVM
 *
 */
void currentViolationHistogram_init(void);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* currentViolationHistogram_getPulseViolationHistogram(uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* currentViolationHistogram_getContViolationHistogram(uint16_t* size);

/**
 * @brief sets histogram counters to zero
 */
void currentViolationHistogram_resetHistograms(void);

bool currentViolationHistogram_setConditionParameters(CurrentViolationConditionParameters parameters);

CurrentViolationConditionParameters currentViolationHistogram_getConditionParameters();

void currentViolationHistogram_checkNvm(const uint8_t* mirror, uint16_t length);

void currentViolationHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length);
