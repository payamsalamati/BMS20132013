/**
 * @file voltageContactorHistogram.h
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
#include "voltageContactorHistogram_config.h"
#include "nvm_config_id.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//
typedef struct
{
    int32_t* deviationLimits;
    uint16_t deviationLimitsSize;
    uint32_t* counters;
    uint16_t counterSize;
    uint16_t* voltageBeforeEvent;
} VoltageContactorHistogram;

typedef struct
{
    uint32_t counters[VOLTAGE_CONTACTOR_HISTOGRAM_COUNTER_SIZE];
} VoltageContactorHistogramNvm;

typedef struct
{
    uint16_t voltageBeforeEvent;
} VoltageContactorHistogramData;

typedef enum
{
    VOLTAGE_CONTACTOR_HISTOGRAM_BEFORE_CONTACTOR_CLOSED = 0x0,
    VOLTAGE_CONTACTOR_HISTOGRAM_AFTER_CONTACTOR_CLOSED  = 0x1,
} VoltageContactorHistogramEvent;


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void voltageContactorHistogram_mainFunction(uint8_t contactor, VoltageContactorHistogramEvent event);

const uint8_t* voltageContactorHistogram_getHistogram(uint16_t* size);

const int32_t* voltageContactorHistogram_getHistogramBins(uint16_t* size);

void voltageContactorHistogram_resetHistogram(void);

void voltageContactorHistogram_checkNvm(const uint8_t* mirror, uint16_t length);

void voltageContactorHistogram_copyNvmForWrite(uint8_t* mirror, uint16_t length);
