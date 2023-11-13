

/**
 * @file temperatureHistogram.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  creates a histogram, that documents the temperature of system
 *
 */

/* Related Requirements: */
/**@req WHBMS-12986*/
/**@req WHBMS-12987*/
/**@req WHBMS-14362*/
/**@req WHBMS-14357*/
/**@req WHBMS-14358*/
/**@req WHBMS-14359*/
/**@req WHBMS-14362*/
/**@req WHBMS-14363*/
/**@req WHBMS-14364*/
/**@req WHBMS-14365*/
/**@req WHBMS-14366*/
/**@req WHBMS-14369*/
/**@req WHBMS-32721*/

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include <stdint.h>
#include <stdbool.h>
#include "nvm_config_id.h"
#include "temperatureHistogram_config.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define COUNTERSHISTOGRAMTEMPERATURESTORAGELENGTH 9U

typedef struct
{
    int32_t* systemTemperatureLimits;
    uint8_t systemTemperatureLimitsLength;
    uint32_t* counters;
    uint16_t counterSize;
} TemperatureHistogram;

typedef struct
{
    const TemperatureHistogram* histograms;
    uint8_t numberOfHistograms;
} TemperatureHistogramConfig;

typedef struct
{
    uint32_t countershistogramMinTemperatureOperational[TEMPERATURE_HISTOGRAM_COUNTER_SIZE];
    uint32_t countershistogramMaxTemperatureOperational[TEMPERATURE_HISTOGRAM_COUNTER_SIZE];
    uint32_t countershistogramAvgTemperatureOperational[TEMPERATURE_HISTOGRAM_COUNTER_SIZE];
    uint32_t countershistogramMinTemperatureStorage[TEMPERATURE_HISTOGRAM_COUNTER_SIZE];
    uint32_t countershistogramMaxTemperatureStorage[TEMPERATURE_HISTOGRAM_COUNTER_SIZE];
    uint32_t countershistogramAvgTemperatureStorage[TEMPERATURE_HISTOGRAM_COUNTER_SIZE];
} TemperatureHistogramCounter;

typedef struct
{
    TemperatureHistogramCounter counters;
    uint32_t dummy_reserve_for_crc;
} TemperatureHistogramNvm;


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
/**
 * @brief increment histogramcounters of the temperature histogram
 *
 */
void temperatureHistogram_mainFunction(void);


/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* temperatureHistogram_getMinTemperatureOperationHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* temperatureHistogram_getMaxTemperatureStoragenHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* temperatureHistogram_getAvgTemperatureOperationHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* temperatureHistogram_getMinTemperatureStoragenHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* temperatureHistogram_getMaxTemperatureOperationHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* temperatureHistogram_getAvgTemperatureStoragenHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
int32_t* temperatureHistogram_getHistogramLimitsOperation(uint16_t* size);

/**
 * @brief setter function for histogram limits
 */
bool temperatureHistogram_setHistogramLimits(int32_t newValue, uint16_t binIndex);

/**
 * @brief init function for module
 *
 */
void temperatureHistogram_init(void);

/**
 * @brief sets histogram counters of the given module to zero
 * @param moduleNumber number of the module, starting at 0
 */
void temperatureHistogram_resetModuleHistograms(uint8_t moduleNumber);
