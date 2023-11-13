/**
 * @file     udsDiagnosticSessionControl_DEFAULT.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <string.h>

#include "uds.h"
#include "uds_diagnosticSessionControl.h"
#include "uds_diagnosticSessionControl_config.h"
#include "uds_routineControl_config.h"
#include "uds_ecuReset.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//**************************  VARIABLE DECLARATIONS *************************//
//***************************************************************************//

// @req CB-73613
const UDS_Session_Entry uds_sessionTable[] = {
    /**  {Session, Preconditions, Hook}  */
    { UDS_SESSION_DEFAULT, NULL, NULL },
    { UDS_SESSION_PROGRAMMING, uds_routineControl_getPreconditionsChecked, uds_ecuReset_resetAndStayInBoot },
    { UDS_SESSION_EXTENDED, NULL, NULL },
    { UDS_SESSION_DEV, NULL, NULL }
};
const uint8_t UDS_SESSION_TABLE_SIZE = sizeof(uds_sessionTable) / sizeof(UDS_Session_Entry);

const uint8_t uds_devSessionList[] = {
    UDS_SESSION_DEV
};
const uint8_t UDS_DEVSESSIONLIST_SIZE = sizeof(uds_devSessionList) / sizeof(uint8_t);

const uint8_t uds_extendedSessionList[] = {
    UDS_SESSION_DEV,
    UDS_SESSION_EXTENDED
};
const uint8_t UDS_EXTENDEDSESSIONLIST_SIZE = sizeof(uds_extendedSessionList) / sizeof(uint8_t);


const uint8_t uds_programmingSessionOnly[] = {
    UDS_SESSION_PROGRAMMING
};
const uint8_t UDS_PROGRAMMINGSESSIONONLY_SIZE = sizeof(uds_programmingSessionOnly) / sizeof(uint8_t);

const uint8_t uds_extendedSessionOnly[] = {
    UDS_SESSION_EXTENDED
};
const uint8_t UDS_EXTENDEDSESSIONONLY_SIZE = sizeof(uds_extendedSessionOnly) / sizeof(uint8_t);

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//
