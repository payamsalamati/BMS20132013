/**
 * @file logicalBlock.h
 * @copyright Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>
#include <stdbool.h>

#include "fingerprint.h"
#include "task_cfg.h"
#include "logicalBlock_config.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef enum
{
    PRIOR_TO_ERASURE = 0x00,
    ERASED           = 0x01,
    PROGRAMMED       = 0x02,
    VALIDATED        = 0x03
} ProgrammingState;

typedef struct
{
    uint8_t logicalBlockNumber;
    bool validationFlag;
    ProgrammingState programmingState;
    uint16_t programmingCounter;
    uint16_t programmingLimit;
    Fingerprint fingerprint;
} LogicalBlock;

typedef struct
{
    uint8_t logicalBlockNumber;
    uint8_t applicationNumber;
    uint8_t configuration;
    uint8_t memoryType;
    uint32_t memoryStartAddress;
    uint32_t memoryLength;
} LogicalBlockTable;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void logicalBlock_init(void);

void logicalBlock_setProgrammingState(uint8_t blockNumber, ProgrammingState state);
ProgrammingState logicalBlock_getProgrammingState(uint8_t blockNumber);

bool logicalBlock_isValid(uint8_t blockNumber);
void logicalBlock_setValidationFlag(uint8_t blockNumber, bool flag);

uint8_t logicalBlock_getCounter(uint8_t blockNumber);
void logicalBlock_increaseCounter(uint8_t blockNumber);

uint8_t logicalBlock_getLimit(uint8_t blockNumber);

void logicalBlock_storeFingerprint(uint8_t blockNumber);

uint8_t logicalBlock_getBlockNumberFromAddress(uint32_t address);
uint32_t logicalBlock_getAddressLengthFromAddress(uint32_t address);

void logicalBlock_writeApplicationIdentificationBackup(uint8_t blockNumber);
