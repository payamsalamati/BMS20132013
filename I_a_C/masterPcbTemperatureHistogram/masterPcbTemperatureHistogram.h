/**
 * @file masterPcbTemperatureHistogram.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *
 *
 *
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include <stdint.h>
#include <stdbool.h>
#include "masterPcbTemperatureHistogram_config.h"
#include "nvm_config_id.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef struct
{
    int16_t* temperatureLimits;
    uint32_t* counters;
    uint16_t counterSize;
} MasterPcbTemperatureHistogram;

typedef struct
{
    uint32_t counters[MASTER_PCB_TEMPERATURE_HISTOGRAM_COUNTER_SIZE];
} MasterPcbTemperatureHistogramNvm;


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void masterPcbTemperatureHistogram_mainFunction(void);

const uint8_t* masterPcbTemperatureHistogram_getHistogram(uint16_t* size);

void masterPcbTemperatureHistogram_resetHistogram();

int16_t* masterPcbTemperatureHistogram_getHistogramBins(uint16_t* size);

void masterPcbTemperatureHistogram_checkNvm(const uint8_t* mirror, uint16_t length);

void masterPcbTemperatureHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length);
