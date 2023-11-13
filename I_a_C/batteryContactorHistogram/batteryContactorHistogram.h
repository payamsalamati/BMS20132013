/**
 * @file batteryContactorHistogram.h
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
#include "batteryContactorHistogram_config.h"
#include "nvm_config_id.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//
typedef struct
{
    int32_t* currentLimits;
    uint32_t* counters;
    uint16_t counterSize;
    int32_t defaultCurrentLimits[BATTERY_CONTACTOR_HISTOGRAM_LIMITS_SIZE];
} BatteryContactorHistogram;

typedef struct
{
    uint32_t counters[BATTERY_CONTACTOR_HISTOGRAM_COUNTER_SIZE];
} BatteryContactorHistogramNvm;


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void batteryContactorHistogram_incrementCounter(uint8_t contactor);

const uint8_t* batteryContactorHistogram_getHistogram(uint16_t* size);

void batteryContactorHistogram_resetHistogram(void);

void batteryContactorHistogram_checkNvm(const uint8_t* mirror, uint16_t length);

void batteryContactorHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length);

int32_t* batteryContactorHistogram_getHistogramBins(uint16_t* size);
