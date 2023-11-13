/**
 * @file masterPcbTemperatureHistogram_config.c
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
#include <stdint.h>
#include "masterPcbTemperatureHistogram.h"
#include "masterPcbTemperatureHistogram_config.h"
#include "task_cfg.h"


//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

extern int16_t pcbHistogramLimits[];

MEM_WARRANTYDATA MasterPcbTemperatureHistogramNvm masterPcbTemperatureHistogramNvm = { 0 };

const MasterPcbTemperatureHistogram masterPcbTemperatureHistogram = {
    .temperatureLimits = &pcbHistogramLimits[0],
    .counters          = &masterPcbTemperatureHistogramNvm.counters[0],
    .counterSize       = sizeof(masterPcbTemperatureHistogramNvm.counters) / sizeof(uint32_t),
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
