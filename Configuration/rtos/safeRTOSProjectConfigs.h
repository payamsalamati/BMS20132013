/**
 * @file safeRTOSProjectConfigs.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Project dependent SafeRTOS configs.
 *
 */


#pragma once


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include <stdint.h>


//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

/* This constant represents the RTI clock speed. For this demo application,
 * the PLL is configured to generate a CPU clock of 143MHz which is used as
 * the HCLK source, and RTI1CLK = ( HCLK / 2).
 */
#define configCPU_CLOCK_HZ (90000000UL)

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
