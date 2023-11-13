
/**
 * @file downscaledVoltageTemperatureHistogram.h
 * @copyright (c) Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  creates a histogram, that documents the downscaled cell voltage and temperature of the system
 *
 */
/* Related SW-Requirements : */
/**@req WHBMS-12988*/
/**@req WHBMS-14818*/
/**@req WHBMS-14821*/
/**@req WHBMS-14822*/
/**@req WHBMS-14823*/
/**@req WHBMS-14824*/
/**@req WHBMS-14939*/
#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include <stdint.h>

#if defined(UNIT_TEST)
#include "test_downscaledVoltageTemperatureHistogram_config.h"
#else
#include "downscaledVoltageTemperatureHistogram_config.h"
#include "module_config.h"
#endif

#include "nvm_config_id.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//
typedef struct
{
    const int32_t* downscaledVoltageTemperatureCellVoltageLimits;
    uint8_t downscaledVoltageTemperatureCellVoltageLimitsLength;
    const int32_t* downscaledVoltageTemperatureCellTemperatureLimits;
    uint8_t downscaledVoltageTemperatureCellTemperatureLimitsLength;
    uint32_t* counters;
    uint16_t counterSize;
} DownscaledVoltageTemperatureHistogram;

typedef struct
{
    const DownscaledVoltageTemperatureHistogram* const histograms;
    uint8_t numberOfHistograms;
} DownscaledVoltageTemperatureHistogramConfig;


typedef struct
{
    uint32_t countersDownscaledVoltageTemperatureHistogram[DOWNSCALED_VOLTAGE_TEMPERATURE_HISTOGRAMM_COUNTER_SIZE];
    uint32_t dummy_reserve_for_crc;
} DownscaledVoltageTemperatureHistogramNvm;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
/**
 * @brief increment histogramcounters of the downscaled voltage temperature histogram
 *
 */
void downscaledVoltageTemperatureHistogram_mainFunction(void);


/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* downscaledVoltageTemperatureHistogram_getHistogram(uint16_t moduleNumber, uint16_t* size);


/**
 * @brief init function for module
 *
 */
void downscaledVoltageTemperatureHistogram_init(void);

/**
 * @brief sets histogram counters of the given module to zero
 * @param moduleNumber number of the module, starting at 0
 */
void downscaledVoltageTemperatureHistogram_resetModuleHistogram(uint8_t moduleNumber);
