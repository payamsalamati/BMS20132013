/**
 * @file testerSerialNumber.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define TESTER_SERIAL_NUMBER_STRING_LENGTH 44u

typedef struct
{
    char testerSerialNumber[TESTER_SERIAL_NUMBER_STRING_LENGTH];
    uint32_t dummy_buffer_crc32;
} TesterSerialNumberNvmData;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

const char* testerSerialNumber_getTesterSerialNumber(void);

void testerSerialNumber_setTesterSerialNumber(const char* string);
