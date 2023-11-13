/**
 * @file currentViolationLogHistogram_config.h
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


//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//

#define CURRENT_VIOLATION_LOG_HISTOGRAM_VALUES_IN_RING  5u
#define CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_RINGS 2u

#define CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_LIMITS (CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_RINGS)
#define CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_EVENTS (CURRENT_VIOLATION_LOG_HISTOGRAM_VALUES_IN_RING * CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_RINGS)

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
