/**
 * @file softwareversionKion.c
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief Short description
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <string.h>

#include "softwareversionKion.h"
#include "softwareversion.h"
#include "softwareversion_commit.h"
#include "fut_string.h"
#include "task_cfg.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef enum
{
    SOFTWAREVERSION_RELEASE_STATUS_DEVELOPMENT                          = 0x00u,
    SOFTWAREVERSION_RELEASE_STATUS_RELEASED_SOFTWARE_FOR_PRODUCTION_USE = 0x01u,
    SOFTWAREVERSION_RELEASE_STATUS_RELEASE_CANDIDATE                    = 0x02u,
    SOFTWAREVERSION_RELEASE_STATUS_TESTING                              = 0x03u
} SOFTWAREVERSION_RELEASE_STATUS;

typedef struct
{
    uint16_t generation;
    uint16_t version;
    uint16_t bugfix;
    uint16_t variant;
    uint8_t releaseStatus;
} SoftwareVersionParameter;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SEC_PARAMETER SoftwareVersionParameter swVersionParameter = {
    .generation    = 0,
    .version       = 0,
    .bugfix        = 0,
    .variant       = 0x0401,
    .releaseStatus = SOFTWAREVERSION_RELEASE_STATUS_DEVELOPMENT
};

// 0xff = not available value (has to be set via A2L)
MEM_SEC_PARAMETER SoftwareVersionParameter algorithmVersionParameter = {
    .generation    = 0xffffu,
    .version       = 0xffffu,
    .bugfix        = 0xffffu,
    .variant       = 0xffffu,
    .releaseStatus = 0xffu,
};

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

const char* softwareversionKion_getVersionByString(uint16_t* maxStringLength)
{
    *maxStringLength = SOFTWARE_VERSION_KION_STRING_LENGTH;

    MEM_SHAREDATA static char softwareversionString[SOFTWARE_VERSION_KION_STRING_LENGTH] = "";

    memset(softwareversionString, 0, sizeof(softwareversionString));

    uint16_t generation = softwareversion_getMajor();
    string_convertDecToStr(generation, softwareversionString);

    string_addDotToString(softwareversionString);

    uint16_t version = softwareversion_getMinor();
    string_convertDecToStr(version, softwareversionString);

    string_addDotToString(softwareversionString);

    uint16_t bugfix = softwareversion_getPatch();
    string_convertDecToStr(bugfix, softwareversionString);

    string_addDotToString(softwareversionString);

    uint16_t variant = softwareversionKion_getVariant();
    string_convertDecToStr(variant, softwareversionString);

    string_addDotToString(softwareversionString);

    uint8_t releaseStatus = softwareversionKion_getReleaseStatus();
    string_convertDecToStr(releaseStatus, softwareversionString);

    return softwareversionString;
}

uint16_t softwareversionKion_getVariant(void)
{
    return SOFTWARE_VERSION_KION_VARIANT;
}

uint8_t softwareversionKion_getReleaseStatus(void)
{
    uint8_t releaseStatus;

    if(strcmp(SOFTWARE_VERSION_RELEASE_STATUS, "Release") == 0)
    {
        releaseStatus = SOFTWAREVERSION_RELEASE_STATUS_RELEASED_SOFTWARE_FOR_PRODUCTION_USE;
    }
    else if(strcmp(SOFTWARE_VERSION_RELEASE_STATUS, "PreRelease") == 0)
    {
        releaseStatus = SOFTWAREVERSION_RELEASE_STATUS_RELEASE_CANDIDATE;
    }
    else if(strcmp(SOFTWARE_VERSION_RELEASE_STATUS, "Testing") == 0)
    {
        releaseStatus = SOFTWAREVERSION_RELEASE_STATUS_TESTING;
    }
    else /* default: */
    {
        releaseStatus = SOFTWAREVERSION_RELEASE_STATUS_DEVELOPMENT;
    }
    return releaseStatus;
}

uint16_t softwareversionKion_getGenerationParameter(void)
{
    return swVersionParameter.generation;
}

uint16_t softwareversionKion_getVersionParameter(void)
{
    return swVersionParameter.version;
}

uint16_t softwareversionKion_getBugfixParameter(void)
{
    return swVersionParameter.bugfix;
}

uint16_t softwareversionKion_getVariantParameter(void)
{
    return swVersionParameter.variant;
}

uint8_t softwareversionKion_getReleaseStatusParameter(void)
{
    return swVersionParameter.releaseStatus;
}

uint16_t softwareversionKion_getAlgorithmGenerationParameter(void)
{
    return algorithmVersionParameter.generation;
}

uint16_t softwareversionKion_getAlgorithmVersionParameter(void)
{
    return algorithmVersionParameter.version;
}

uint16_t softwareversionKion_getAlgorithmBugfixParameter(void)
{
    return algorithmVersionParameter.bugfix;
}

uint16_t softwareversionKion_getAlgorithmVariantParameter(void)
{
    return algorithmVersionParameter.variant;
}

uint8_t softwareversionKion_getAlgorithmReleaseStatusParameter(void)
{
    return algorithmVersionParameter.releaseStatus;
}
