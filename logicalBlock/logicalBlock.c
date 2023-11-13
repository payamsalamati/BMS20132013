/**
 * @file logicalBlock.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <string.h>

#include "logicalBlock.h"
#include "postBuildConfiguration.h"

#include "eepromIf.h"
#include "memory_config.h"
#include "configuration.h"
#include "debug.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static uint8_t getLogicalBlockIndexByBlockName(uint8_t blockNumber);
static void setFingerprintFromIdentification(uint8_t blockNumber);
static void writeBootloaderIdentificationBackup(void);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

extern MEM_SEC_PARAMETER LogicalBlock logicalBlock[];
extern const uint16_t LOGICAL_BLOCK_SIZE;
extern MEM_SEC_PARAMETER const LogicalBlockTable logicalBlockTable[];
extern const uint16_t LOGICAL_BLOCK_TABLE_SIZE;

extern MEM_SEC_PARAMETER char bootloaderIdentification[15];

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static uint8_t getLogicalBlockIndexByBlockName(uint8_t blockNumber)
{
    uint8_t blockIndex = 0xFF;
    for(uint8_t i = 0; i < LOGICAL_BLOCK_SIZE; i++)
    {
        if(blockNumber == logicalBlock[i].logicalBlockNumber)
        {
            blockIndex = i;
            break;
        }
    }
    DEBUG_ASSERT(blockIndex < LOGICAL_BLOCK_SIZE);
    return blockIndex;
}

static void setFingerprintFromIdentification(uint8_t blockNumber)
{
    uint8_t blockIndex                              = getLogicalBlockIndexByBlockName(blockNumber);
    logicalBlock[blockIndex].fingerprint.date.year  = ((IDENTIFICATION[2] - 48u) * 16) + (IDENTIFICATION[3] - 48u);
    logicalBlock[blockIndex].fingerprint.date.month = ((IDENTIFICATION[4] - 48u) * 16) + (IDENTIFICATION[5] - 48u);
    logicalBlock[blockIndex].fingerprint.date.day   = ((IDENTIFICATION[6] - 48u) * 16) + (IDENTIFICATION[7] - 48u);
    char fingerprintName[44]                        = "Created during Bootloader flash";
    for(uint8_t i = 0; i < 44u; i++)
    {
        logicalBlock[blockIndex].fingerprint.testerSerialNumber[i] = fingerprintName[i];
    }
}

static void writeBootloaderIdentificationBackup(void)
{
    eepromIf_write(0u, EXT_FLASH_ADDR_BOOTLOADER_IDENTIFICATION_BACKUP_START, (uint8_t*)&bootloaderIdentification, EXT_FLASH_ADDR_BOOTLOADER_IDENTIFICATION_BACKUP_LENGTH);
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void logicalBlock_init(void)
{
    setFingerprintFromIdentification(LOGICAL_BLOCK_BOOTLOADER);
    setFingerprintFromIdentification(LOGICAL_BLOCK_LOGICAL_BLOCK_TABLE);
    writeBootloaderIdentificationBackup();
}

ProgrammingState logicalBlock_getProgrammingState(uint8_t blockNumber)
{
    return logicalBlock[getLogicalBlockIndexByBlockName(blockNumber)].programmingState;
}

void logicalBlock_setProgrammingState(uint8_t blockNumber, ProgrammingState state)
{
    logicalBlock[getLogicalBlockIndexByBlockName(blockNumber)].programmingState = state;
    postBuildConfiguration_setCalibrationChanged();
}

bool logicalBlock_isValid(uint8_t blockNumber)
{
    return logicalBlock[getLogicalBlockIndexByBlockName(blockNumber)].validationFlag;
}

void logicalBlock_setValidationFlag(uint8_t blockNumber, bool flag)
{
    logicalBlock[getLogicalBlockIndexByBlockName(blockNumber)].validationFlag = flag;
    postBuildConfiguration_setCalibrationChanged();
}

uint8_t logicalBlock_getCounter(uint8_t blockNumber)
{
    return logicalBlock[getLogicalBlockIndexByBlockName(blockNumber)].programmingCounter;
}

void logicalBlock_increaseCounter(uint8_t blockNumber)
{
    logicalBlock[getLogicalBlockIndexByBlockName(blockNumber)].programmingCounter++;
    postBuildConfiguration_setCalibrationChanged();
}

uint8_t logicalBlock_getLimit(uint8_t blockNumber)
{
    return logicalBlock[getLogicalBlockIndexByBlockName(blockNumber)].programmingLimit;
}

void logicalBlock_storeFingerprint(uint8_t blockNumber)
{
    logicalBlock[getLogicalBlockIndexByBlockName(blockNumber)].fingerprint = fingerprint_getFingerprint();
    postBuildConfiguration_setCalibrationChanged();
}

uint8_t logicalBlock_getBlockNumberFromAddress(uint32_t address)
{
    uint8_t blockNumber = LOGICAL_BLOCK_NOT_FOUND;

    for(uint8_t i = 0; i < LOGICAL_BLOCK_TABLE_SIZE; i++)
    {
        if((logicalBlockTable[i].memoryStartAddress <= address) && (address < (logicalBlockTable[i].memoryStartAddress + logicalBlockTable[i].memoryLength)))
        {
            blockNumber = logicalBlockTable[i].logicalBlockNumber;
            break;
        }
    }

    return blockNumber;
}

uint32_t logicalBlock_getAddressLengthFromAddress(uint32_t address)
{
    uint32_t addressLength = 0;

    for(uint8_t i = 0; i < LOGICAL_BLOCK_TABLE_SIZE; i++)
    {
        if((logicalBlockTable[i].memoryStartAddress <= address) && (address < (logicalBlockTable[i].memoryStartAddress + logicalBlockTable[i].memoryLength)))
        {
            addressLength = logicalBlockTable[i].memoryLength;
            break;
        }
    }

    return addressLength;
}

void logicalBlock_writeApplicationIdentificationBackup(uint8_t blockNumber)
{
    switch(blockNumber)
    {
        case LOGICAL_BLOCK_APPLICATION:
            eepromIf_write(0u, EXT_FLASH_ADDR_APPLICATION_SOFTWARE_IDENTIFICATION_BACKUP_START, (uint8_t*)(char*)APP_SOFTWARE_IDENTIFICATION_ADDRESS, EXT_FLASH_ADDR_APPLICATION_SOFTWARE_IDENTIFICATION_BACKUP_LENGTH);
            break;

        case LOGICAL_BLOCK_DATA:
            eepromIf_write(0u, EXT_FLASH_ADDR_APPLICATION_DATA_IDENTIFICATION_BACKUP_START, (uint8_t*)(char*)APP_DATA_IDENTIFICATION_ADDRESS, EXT_FLASH_ADDR_APPLICATION_DATA_IDENTIFICATION_BACKUP_LENGTH);
            break;

        default:
            break;
    }
}
