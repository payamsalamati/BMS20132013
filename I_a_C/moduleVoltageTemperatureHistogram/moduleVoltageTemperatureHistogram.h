/**
 * @file moduleVoltageTemperatureHistogram.h
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
#include "nvm_config_id.h"
#include "moduleVoltageTemperatureHistogram_config.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


#if defined(UNIT_TEST)
#define MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_TEMPERATURE_POSITION 0
#define MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_VOLTAGE_POSITION     1
#define MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_POSITION             0
#define MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_COUNTER_SIZE         56
#endif

typedef struct
{
    const int32_t* moduleVoltageTemperatureVoltageLimits;
    uint8_t moduleVoltageTemperatureVoltageLimitsLength;
    const int32_t* moduleVoltageTemperatureTemperatureLimits;
    uint8_t moduleVoltageTemperatureTemperatureLimitsLength;
    uint32_t* counters;
    uint16_t counterSize;
} ModuleVoltageTemperatureHistogram;

typedef struct
{
    const ModuleVoltageTemperatureHistogram* const* histograms;
    uint8_t numberOfHistograms;
} ModuleVoltageTemperatureHistogramConfig;


typedef struct
{
    uint32_t countersModuleVoltageTemperatureHistogram[MODULE_VOLTAGE_TEMPERATURE_HISTOGRAM_COUNTER_SIZE];
    uint8_t reserve[472];
    uint32_t dummy_reserve_for_crc;
} ModuleVoltageTemperatureHistogramNvm;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

/**
 * @brief init function for module
 *
 */
void moduleVoltageTemperatureHistogram_init(void);


/**
 * @brief increment histogramcounters of the voltage histogram
 *
 */
void moduleVoltageTemperatureHistogram_mainFunction(void);


/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* moduleVoltageTemperatureHistogram_getHistogram(uint16_t* size);


/**
 * @brief sets histogram counters to zero
 */
void moduleVoltageTemperatureHistogram_resetHistograms(void);


/**
 * @brief getter function for histogram temperature limits
 *
 * @param size
 * @return int32_t*
 */
const int32_t* moduleVoltageTemperatureHistogram_getTemperatureLimits(uint16_t* size);


/**
 * @brief getter function for histogram voltage limits
 *
 * @param size
 * @return int32_t*
 */
const int32_t* moduleVoltageTemperatureHistogram_getVoltageLimits(uint16_t* size);
