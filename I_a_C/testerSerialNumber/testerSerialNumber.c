/**
 * @file testerSerialNumber.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "testerSerialNumber.h"
#include <string.h>
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

MEM_APPLICATION TesterSerialNumberNvmData testerSerialNumberNvm;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

// @req CB-74449
// @req CB-74450
// @req CB-91824
const char* testerSerialNumber_getTesterSerialNumber(void)
{
    return testerSerialNumberNvm.testerSerialNumber;
}

void testerSerialNumber_setTesterSerialNumber(const char* string)
{
    strncpy(testerSerialNumberNvm.testerSerialNumber, string, TESTER_SERIAL_NUMBER_STRING_LENGTH);
}
