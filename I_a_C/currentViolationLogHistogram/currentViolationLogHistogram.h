/**
 * @file currentViolationLogHistogram.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdbool.h>
#include <stdint.h>
#include "ringbuffer.h"
#include "currentViolationLogHistogram_config.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef struct
{
    RingValue_uint32_t ringValues[CURRENT_VIOLATION_LOG_HISTOGRAM_VALUES_IN_RING];
    Ring_uint32_t ring;
} CurrentViolationLogHistogramRing;

typedef struct
{
    uint32_t events[CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_EVENTS];
    uint8_t reserve[12];
} CurrentViolationLogHistogramNvm;


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void currentViolationLogHistogram_mainFunction(void);

CurrentViolationLogHistogramRing* currentViolationLogHistogram_getHistogram(uint16_t* size);
void currentViolationLogHistogram_resetHistogram(void);
int32_t* currentViolationLogHistogram_getHistogramLimits(uint8_t* size);
bool currentViolationLogHistogram_setHistogramLimits(int32_t newValue, uint8_t binIndex);

void currentViolationLogHistogram_checkNvm(const uint8_t* mirror, uint16_t length);
void currentViolationLogHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length);
