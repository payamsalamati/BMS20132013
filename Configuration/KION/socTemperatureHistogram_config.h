/**
 * @file socTemperatureHistogram_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "histogramBins_config.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//

#define SOC_TEMPERATURE_HISTOGRAM_COUNTER_SIZE (BATTERY_TEMPERATURE_LIMITS_SIZE + 1u) * (SOC_HISTOGRAM_LIMITS_SIZE + 1u)


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//