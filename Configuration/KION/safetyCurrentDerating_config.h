/**
 * @file safetyCurrentDerating_config.h
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

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
#define CURRENT_DERATING_CHG_MAX_CONT_SAFETY_TIME_DEFAULT 40000
#else
#define CURRENT_DERATING_CHG_MAX_CONT_SAFETY_TIME_DEFAULT 10000
#endif
#define CURRENT_DERATING_CHG_MAX_CONT_WARN_TIME_DEFAULT 2000

#define CURRENT_DERATING_CHG_MAX_PEAK_SAFETY_TIME_DEFAULT 10000
#define CURRENT_DERATING_CHG_MAX_PEAK_WARN_TIME_DEFAULT   2000

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
#define CURRENT_DERATING_DSG_MAX_CONT_SAFETY_TIME_DEFAULT 40000
#else
#define CURRENT_DERATING_DSG_MAX_CONT_SAFETY_TIME_DEFAULT 10000
#endif
#define CURRENT_DERATING_DSG_MAX_CONT_WARN_TIME_DEFAULT 2000

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
#define CURRENT_DERATING_DSG_MAX_PEAK_SAFETY_TIME_DEFAULT 20000
#else
#define CURRENT_DERATING_DSG_MAX_PEAK_SAFETY_TIME_DEFAULT 10000
#endif
#define CURRENT_DERATING_DSG_MAX_PEAK_WARN_TIME_DEFAULT 2000
