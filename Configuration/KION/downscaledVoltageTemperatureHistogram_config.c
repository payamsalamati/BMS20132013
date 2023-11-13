/**
 * @file downscaledVoltageTemperatureHistogram_config.c
 * @copyright (c) Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
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
//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include "downscaledVoltageTemperatureHistogram.h"
#include "downscaledVoltageTemperatureHistogram_config.h"
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

// @req CB-89420
const int32_t downscaledvoltageTemperatureHistogramLimitsCellVoltage[] = {
    3300,
    4070
};

// @req CB-89420
const int32_t downscaledvoltageTemperatureHistogramLimitsCellTemperature[] = {
    0,
    30
};

// @req CB-89418
MEM_WARRANTYDATA DownscaledVoltageTemperatureHistogramNvm downscaledVoltageTemperatureHistogramCountersModule[BMS_CONFIG_MAX_NUMBER_OF_SLAVES] = { 0 };

// @req CB-89419
const DownscaledVoltageTemperatureHistogram downscaledVoltageTemperatureHistograms[] = {
#if !defined(BMS_CONFIG_MAX_NUMBER_OF_SLAVES)
// cppcheck-suppress preprocessorErrorDirective ; BMS_CONFIG_MAX_NUMBER_OF_SLAVES is defined
#error missing or wrong configuration
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 1u


    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[0].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[0].countersDownscaledVoltageTemperatureHistogram[0] },

#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 2u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[1].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[1].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 3u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[2].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[2].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 4u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[3].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[3].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 5u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[4].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[4].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 6u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[5].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[5].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 7u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[6].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[6].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 8u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[7].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[7].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 9u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[8].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[8].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 10u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[9].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[9].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 11u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[10].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[10].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 12u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[11].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[11].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 13u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[12].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[12].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 14u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[13].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[13].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 15u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[14].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[14].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 16u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[15].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[15].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 17u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[16].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[16].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 18u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[17].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[17].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 19u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[18].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[18].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 20u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[19].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[19].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 21u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[20].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[20].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 22u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[21].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[21].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 23u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[22].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[22].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 24u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[23].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[23].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 25u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[24].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[24].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 26u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[25].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[25].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 27u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[26].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[26].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 28u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[27].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[27].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 29u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[28].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[28].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 30u
    { .downscaledVoltageTemperatureCellVoltageLimits           = &downscaledvoltageTemperatureHistogramLimitsCellVoltage[0],
      .downscaledVoltageTemperatureCellVoltageLimitsLength     = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellVoltage) / sizeof(int32_t)) + 1U,
      .downscaledVoltageTemperatureCellTemperatureLimits       = &downscaledvoltageTemperatureHistogramLimitsCellTemperature[0],
      .downscaledVoltageTemperatureCellTemperatureLimitsLength = (sizeof(downscaledvoltageTemperatureHistogramLimitsCellTemperature) / sizeof(int32_t)) + 1U,
      .counterSize                                             = sizeof(downscaledVoltageTemperatureHistogramCountersModule[29].countersDownscaledVoltageTemperatureHistogram) / sizeof(uint32_t),
      .counters                                                = &downscaledVoltageTemperatureHistogramCountersModule[29].countersDownscaledVoltageTemperatureHistogram[0] },
#endif
};

const DownscaledVoltageTemperatureHistogramConfig downscaledVoltageTemperatureHistogramConfig = {
    .histograms         = downscaledVoltageTemperatureHistograms,
    .numberOfHistograms = sizeof(downscaledVoltageTemperatureHistograms) / sizeof(DownscaledVoltageTemperatureHistogram)
};

#endif
//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
