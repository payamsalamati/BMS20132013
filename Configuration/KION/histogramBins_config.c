/**
 * @file histogramBins_config.c
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

#include "task_cfg.h"
#include <stdint.h>
#include <stdbool.h>
#include "histogramBins_config.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

// @req CB-78700
MEM_SEC_PARAMETER int32_t iHistogramLimits[I_HISTOGRAM_LIMITS_SIZE] = {
    -700000,
    -500000,
    -400000,
    -350000,
    -300000,
    -250000,
    -200000,
    -150000,
    -100000,
    -50000,
    -5000,
    0,
    5000,
    50000,
    100000,
    150000,
    200000,
    250000,
    300000,
    350000,
    400000,
    500000,
    700000,
};

// @req CB-78702
#if defined(SIL_DEBUG)
__attribute__((section("A2L"))) int16_t pcbHistogramLimits[PCB_HISTOGRAM_LIMITS_SIZE] = {
#else
MEM_SEC_PARAMETER int16_t pcbHistogramLimits[PCB_HISTOGRAM_LIMITS_SIZE]             = {
#endif
    -20,
    -10,
    0,
    10,
    20,
    30,
    40,
    50,
    60,
};

// @req CB-78697
#if defined(SIL_DEBUG)
__attribute__((section("A2L"))) int32_t batteryTemperatureLimits[BATTERY_TEMPERATURE_LIMITS_SIZE] = {
#else
MEM_SEC_PARAMETER int32_t batteryTemperatureLimits[BATTERY_TEMPERATURE_LIMITS_SIZE] = {
#endif
    -20,
    -10,
    0,
    10,
    25,
    40,
    50,
};

// @req CB-89834
#if defined(SIL_DEBUG)
__attribute__((section("A2L"))) int32_t socHistogramLimits[SOC_HISTOGRAM_LIMITS_SIZE] = {
#else
MEM_SEC_PARAMETER int32_t socHistogramLimits[SOC_HISTOGRAM_LIMITS_SIZE]             = {
#endif
    200,
    500,
    700,
    850,
    900,
    950,
};
