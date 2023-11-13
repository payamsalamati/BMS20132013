/**
 * @file identification.c
 * @copyright (c) Futavis GmbH, Aachen 2021 - all rights reserved
 * @brief Sharing data between Bootloader and Application
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "task_cfg.h"
#include "identification.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

static const char applicationSoftwareIdentification[IDENTIFICATION_LENGTH]               = IDENTIFICATION;
MEM_SEC_PARAMETER static const char applicationDataIdentification[IDENTIFICATION_LENGTH] = IDENTIFICATION;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

const char* identification_getApplicationSoftwareIdentification(void)
{
    return applicationSoftwareIdentification;
}

const char* identification_getApplicationDataIdentification(void)
{
    return applicationDataIdentification;
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//
