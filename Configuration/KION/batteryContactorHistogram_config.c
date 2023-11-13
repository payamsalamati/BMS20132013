/**
 * @file batteryContactorHistogram_config.c
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
#include "batteryContactorHistogram.h"
#include "batteryContactorHistogram_config.h"
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

extern int32_t iHistogramLimits[];

// @req CB-89561
MEM_WARRANTYDATA BatteryContactorHistogramNvm batteryContactorHistogramNvm = { 0 };


// @req CB-89559
const BatteryContactorHistogram batteryContactorHistogram = {
    .currentLimits        = &iHistogramLimits[0],
    .counters             = &batteryContactorHistogramNvm.counters[0],
    .counterSize          = sizeof(batteryContactorHistogramNvm.counters) / sizeof(batteryContactorHistogramNvm.counters[0]),
    .defaultCurrentLimits = {
        -700,
        -500,
        -400,
        -350,
        -300,
        -250,
        -200,
        -150,
        -100,
        -50,
        -25,
        0,
        25,
        50,
        100,
        150,
        200,
        250,
        300,
        350,
        400,
        500,
        700,
    },
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
