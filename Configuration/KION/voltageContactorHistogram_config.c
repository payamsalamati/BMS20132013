/**
 * @file voltageContactorHistogram_config.c
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
#include "voltageContactorHistogram.h"
#include "voltageContactorHistogram_config.h"
#include "task_cfg.h"
#include <stdint.h>


//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_WARRANTYDATA VoltageContactorHistogramNvm voltageContactorHistogramNvm   = { 0 };
MEM_WARRANTYDATA VoltageContactorHistogramData voltageContactorHistogramData = { 0 };

#if defined(SIL_DEBUG)
__attribute__((section("A2L"))) int32_t voltageContactorHistogramLimits[VOLTAGE_CONTACTOR_HISTOGRAM_LIMITS_SIZE] = {
#else
MEM_SEC_PARAMETER int32_t voltageContactorHistogramLimits[VOLTAGE_CONTACTOR_HISTOGRAM_LIMITS_SIZE] = {
#endif
    0,
    1,
    2,
    3,
    5,
};

const VoltageContactorHistogram voltageContactorHistogram = {
    .deviationLimits     = &voltageContactorHistogramLimits[0],
    .deviationLimitsSize = sizeof(voltageContactorHistogramLimits) / sizeof(voltageContactorHistogramLimits[0]),
    .counters            = &voltageContactorHistogramNvm.counters[0],
    .counterSize         = sizeof(voltageContactorHistogramNvm.counters) / sizeof(voltageContactorHistogramNvm.counters[0]),
    .voltageBeforeEvent  = &voltageContactorHistogramData.voltageBeforeEvent,
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
