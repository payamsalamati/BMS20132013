
/**
 * @file voltageHistogram.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  creates a histogram, that documents the cell voltage of the system
 *
 */

/**@req WHBMS-12982*/
/**@req WHBMS-12983*/
/**@req WHBMS-14339*/
/**@req WHBMS-14340*/
/**@req WHBMS-14341*/
/**@req WHBMS-14343*/
/**@req WHBMS-14346*/
/**@req WHBMS-14349*/
/**@req WHBMS-14350*/
/**@req WHBMS-14351*/
/**@req WHBMS-14355*/
/**@req WHBMS-24774*/
/**@req WHBMS-39776*/

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include <stdint.h>
#include <stdbool.h>
#include "voltageHistogram_config.h"
#include "nvm_config_id.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//
typedef struct
{
    int32_t* systemVoltageLimits;
    uint8_t systemVoltageLimitsLength;
    uint32_t* counters;
    uint16_t counterSize;
} VoltageHistogram;

typedef struct
{
    const VoltageHistogram* const histograms;
    uint8_t numberOfHistograms;
} VoltageHistogramConfig;

typedef struct
{
    uint32_t countershistogramMinVoltageOperational[VOLTAGE_HISTOGRAMM_COUNTER_SIZE];
    uint32_t countershistogramMaxVoltageOperational[VOLTAGE_HISTOGRAMM_COUNTER_SIZE];
    uint32_t countershistogramAvgVoltageOperational[VOLTAGE_HISTOGRAMM_COUNTER_SIZE];
    uint32_t countershistogramMinVoltageStorage[VOLTAGE_HISTOGRAMM_COUNTER_SIZE];
    uint32_t countershistogramMaxVoltageStorage[VOLTAGE_HISTOGRAMM_COUNTER_SIZE];
    uint32_t countershistogramAvgVoltageStorage[VOLTAGE_HISTOGRAMM_COUNTER_SIZE];
} VoltageHistogramCounter;

typedef struct
{
    VoltageHistogramCounter counters;
    uint32_t dummy_reserve_for_crc;
} VoltageHistogramNvm;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
/**
 * @brief increment histogramcounters of the voltage histogram
 *
 * ## Requirements:
 * **Requirement**  |**Description**
 * :---------------:|:--------------
 * **VHis_00001**   |used histogram depends on current operationstate
 */
void voltageHistogram_mainFunction(void);


/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* voltageHistogram_getMinVoltageOperationHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* voltageHistogram_getMaxVoltageStorageHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* voltageHistogram_getAvgVoltageOperationHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* voltageHistogram_getMinVoltageStorageHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* voltageHistogram_getMaxVoltageOperationHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* voltageHistogram_getAvgVoltageStorageHistogram(uint16_t moduleNumber, uint16_t* size);

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
int32_t* voltageHistogram_getHistogramLimits(uint16_t* size);

/**
 * @brief setter function for histogram limits
 */
bool voltageHistogram_setHistogramLimits(int32_t newValue, uint16_t binIndex);

/**
 * @brief init function for module
 *
 */
void voltageHistogram_init(void);

/**
 * @brief sets histogram counters of the given module to zero
 * @param moduleNumber number of the module, starting at 0
 */
void voltageHistogram_resetModuleHistogram(uint8_t moduleNumber);
