
/**
 * @file downscaledCurrentViolationHistogram.h
 * @copyright (c) Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
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
#if defined(UNIT_TEST)
#include "test_downscaledCurrentViolationHistogram_config.h"
#else
#include "downscaledCurrentViolationHistogram_config.h"
#include "module_config.h"
#endif

#include "nvm_config_id.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//
typedef struct
{
    const int32_t* downscaledCurrentViolationCellTemperatureLimits;
    uint8_t downscaledCurrentViolationCellTemperatureLimitsLength;
    uint32_t* counters;
    uint16_t counterSize;
} DownscaledCurrentViolationHistogram;

typedef struct
{
    const DownscaledCurrentViolationHistogram* const histograms;
    uint8_t numberOfHistograms;
} DownscaledCurrentViolationHistogramConfig;

typedef struct
{
    uint32_t countersDownscaledCurrentViolationHistogram[DOWNSCALED_CURRENT_VIOLATION_HISTOGRAM_COUNTER_SIZE];
} DownscaledCurrentViolationHistogramNvm;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

/**
 * @brief getter function for histogram
 *
 * @param size
 * @return const uint8_t*
 */
const uint8_t* downscaledCurrentViolationHistogram_getHistogram(uint16_t moduleNumber, uint16_t* size);


/**
 * @brief init function for module
 *
 */
void downscaledCurrentViolationHistogram_init(void);

/**
 * @brief sets histogram counters of the given module to zero
 * @param moduleNumber number of the module, starting at 0
 */
void downscaledCurrentViolationHistogram_resetModuleHistogram(uint8_t moduleNumber);


void downscaledCurrentViolationHistogram_addValues(bool cont);
