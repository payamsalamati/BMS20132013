/**
 * @file softwareversionKion.h
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief Short description
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define SOFTWARE_VERSION_KION_STRING_LENGTH 26u
#define SOFTWARE_VERSION_KION_VARIANT       0x0400u

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

const char* softwareversionKion_getVersionByString(uint16_t* maxStringLength);

uint16_t softwareversionKion_getVariant(void);
uint8_t softwareversionKion_getReleaseStatus(void);

uint16_t softwareversionKion_getGenerationParameter(void);
uint16_t softwareversionKion_getVersionParameter(void);
uint16_t softwareversionKion_getBugfixParameter(void);
uint16_t softwareversionKion_getVariantParameter(void);
uint8_t softwareversionKion_getReleaseStatusParameter(void);
uint16_t softwareversionKion_getAlgorithmGenerationParameter(void);
uint16_t softwareversionKion_getAlgorithmVersionParameter(void);
uint16_t softwareversionKion_getAlgorithmBugfixParameter(void);
uint16_t softwareversionKion_getAlgorithmVariantParameter(void);
uint8_t softwareversionKion_getAlgorithmReleaseStatusParameter(void);
