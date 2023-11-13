/**
 * @file heatingCurrentHistogram_config.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
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

#include "heatingCurrentHistogram.h"
#include "task_cfg.h"
#include "module_config.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

// @req CB-89415
MEM_SEC_PARAMETER int32_t heatingCurrentHistogramCurrentLimits[] = {
    0,
    1000,
    2000,
    3000,
    4000,
    5000,
};

// @req CB-78747 CB-78748
MEM_WARRANTYDATA HeatingCurrentHistogramNvm heatingCurrentHistogramCountersModule[BMS_CONFIG_MAX_NUMBER_OF_SLAVES] = { 0 };

const uint16_t WARRANTY_DATA_HEATING_CURRENT_HISTOGRAM_SIZE = HEATING_CURRENT_HISTOGRAM_COUNTER_SIZE;

// @req CB-89414
const HeatingCurrentHistogram heatingCurrentHistograms[] = {
#if !defined(BMS_CONFIG_MAX_NUMBER_OF_SLAVES)
// cppcheck-suppress preprocessorErrorDirective ; BMS_CONFIG_MAX_NUMBER_OF_SLAVES is defined
#error missing or wrong configuration
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 1u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[0].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[0].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 2u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[1].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[1].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 3u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[2].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[2].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 4u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[3].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[3].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 5u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[4].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[4].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 6u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[5].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[5].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 7u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[6].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[6].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 8u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[7].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[7].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 9u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[8].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[8].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 10u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[9].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[9].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 11u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[10].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[10].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 12u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[11].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[11].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 13u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[12].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[12].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 14u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[13].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[13].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 15u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[14].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[14].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 16u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[15].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[15].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 17u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[16].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[16].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 18u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[17].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[17].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 19u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[18].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[18].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 20u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[19].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[19].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 21u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[20].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[20].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 22u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[21].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[21].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 23u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[22].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[22].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 24u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[23].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[23].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 25u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[24].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[24].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 26u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[25].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[25].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 27u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[26].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[26].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 28u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[27].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[27].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 29u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[28].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[28].counters.countersHeatingCurrentHistogram[0] },
#endif
#if BMS_CONFIG_MAX_NUMBER_OF_SLAVES >= 30u
    { .heatingCurrentLimits       = &heatingCurrentHistogramCurrentLimits[0],
      .heatingCurrentLimitsLength = (sizeof(heatingCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
      .counterSize                = sizeof(heatingCurrentHistogramCountersModule[29].counters.countersHeatingCurrentHistogram) / sizeof(uint32_t),
      .counters                   = &heatingCurrentHistogramCountersModule[29].counters.countersHeatingCurrentHistogram[0] },
#endif
};

const HeatingCurrentHistogramConfig heatingCurrentHistogramConfig = {
    .histograms         = heatingCurrentHistograms,
    .numberOfHistograms = sizeof(heatingCurrentHistograms) / sizeof(HeatingCurrentHistogram)
};


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
