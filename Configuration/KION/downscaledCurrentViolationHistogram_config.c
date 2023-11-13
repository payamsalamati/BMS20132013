/**
 * @file downscaledCurrentViolationHistogram_config.c
 * @copyright (c) Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include "downscaledCurrentViolationHistogram.h"
#include "downscaledCurrentViolationHistogram_config.h"
#include "task_cfg.h"
#include <stdint.h>

#if !defined(UNIT_TEST)
#include "module_config.h"
#endif


//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//
#if !defined(UNIT_TEST)

// @req CB-89443
const int32_t downscaledCurrentViolationHistogramLimitsCellTemperature[] = {
    0,
    30
};

// @req CB-89418
MEM_NVM DownscaledCurrentViolationHistogramNvm downscaledCurrentViolationHistogramCountersModule[BMS_CONFIG_MAX_NUMBER_OF_SLAVES] = { 0 };

// @req CB-89445
const DownscaledCurrentViolationHistogram downscaledCurrentViolationHistograms[] = {
#if !defined(BMS_CONFIG_MAX_NUMBER_OF_SLAVES)
// cppcheck-suppress preprocessorErrorDirective ; BMS_CONFIG_MAX_NUMBER_OF_SLAVES is defined
#error missing or wrong configuration
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 1u


    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[0].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[0].countersDownscaledCurrentViolationHistogram[0] },

#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 2u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[1].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[1].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 3u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[2].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[2].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 4u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[3].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[3].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 5u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[4].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[4].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 6u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[5].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[5].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 7u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[6].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[6].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 8u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[7].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[7].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 9u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[8].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[8].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 10u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[9].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[9].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 11u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[10].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[10].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 12u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[11].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[11].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 13u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[12].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[12].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 14u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[13].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[13].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 15u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[14].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[14].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 16u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[15].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[15].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 17u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[16].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[16].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 18u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[17].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[17].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 19u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[18].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[18].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 20u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[19].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[19].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 21u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[20].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[20].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 22u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[21].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[21].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 23u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[22].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[22].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 24u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[23].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[23].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 25u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[24].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[24].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 26u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[25].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[25].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 27u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[26].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[26].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 28u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[27].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[27].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 29u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[28].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[28].countersDownscaledCurrentViolationHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 30u
    { .downscaledCurrentViolationCellTemperatureLimits       = &downscaledCurrentViolationHistogramLimitsCellTemperature[0],
      .downscaledCurrentViolationCellTemperatureLimitsLength = (sizeof(downscaledCurrentViolationHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                           = sizeof(downscaledCurrentViolationHistogramCountersModule[29].countersDownscaledCurrentViolationHistogram) / sizeof(uint32_t),
      .counters                                              = &downscaledCurrentViolationHistogramCountersModule[29].countersDownscaledCurrentViolationHistogram[0] },
#endif
};

const DownscaledCurrentViolationHistogramConfig downscaledCurrentViolationHistogramConfig = {
    .histograms         = downscaledCurrentViolationHistograms,
    .numberOfHistograms = sizeof(downscaledCurrentViolationHistograms) / sizeof(DownscaledCurrentViolationHistogram)
};

#endif
//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
