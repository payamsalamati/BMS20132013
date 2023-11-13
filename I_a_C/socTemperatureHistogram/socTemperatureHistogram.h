

/**
 * @file socTemperatureHistogram.h
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
#include "socTemperatureHistogram_config.h"
#include "nvm_config_id.h"
#include "histogramBins_config.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef struct
{
    int32_t* socTemperatureHistogramSocLimits;
    int32_t* socTemperatureHistogramTemperatureLimits;
} SocTemperatureHistogramBins;

typedef struct
{
    SocTemperatureHistogramBins* limits;
    uint32_t* counters;
    uint16_t counterSize;
} SocTemperatureHistogram;

typedef struct
{
    uint32_t counters[SOC_TEMPERATURE_HISTOGRAM_COUNTER_SIZE];
} SocTemperatureHistogramNvm;


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void socTemperatureHistogram_mainFunction(void);

const uint8_t* socTemperatureHistogram_getHistogram(uint16_t* size);

void socTemperatureHistogram_resetHistogram(void);

int32_t* socTemperatureHistogram_getTemperatureBins(uint16_t* size);

int32_t* socTemperatureHistogram_getSocBins(uint16_t* size);

void socTemperatureHistogram_checkNvm(const uint8_t* mirror, uint16_t length);

void socTemperatureHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length);
