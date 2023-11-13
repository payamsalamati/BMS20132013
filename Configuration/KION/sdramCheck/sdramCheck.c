/**
 * @file sdram_c.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include "task_cfg.h"
#include "osIf.h"
#include "sdramCheck.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

#define SDRAM_SIZE_TESTING          0x1000000u
#define SDRAM_NUMBER_OF_SUBROUTINES 2u
#define SDRAM_SUB_SIZE_TESTING      (SDRAM_SIZE_TESTING / SDRAM_NUMBER_OF_SUBROUTINES)
#define SDRAM_WRITE_DATA_SWITCHING  (SDRAM_SUB_SIZE_TESTING / 2u)
#define SDRAM_MAX_ERROR_COUNTER     UINT16_MAX


typedef struct
{
    uint16_t writeErrorCount;
    uint16_t readErrorCount;
    bool writeErrorOverflow;
    bool readErrorOverflow;
    bool initialErrorOverflow;
    uint8_t subroutine;
    uint8_t fullTestedCounter;
} SdramError;
//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//


MEM_SHAREDATA SdramError sdramError = { 0 };

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

void sdRam_checkFunction(void)
{
    uint8_t* sdramAddress = (uint8_t*)0x80000000;
    uint8_t data[]        = { 0x00, 0xAA, 0x55 };
    uint8_t dataIDx       = 0;

    // write and check data
    for(uint32_t j = SDRAM_SUB_SIZE_TESTING * sdramError.subroutine; j < SDRAM_SUB_SIZE_TESTING * (sdramError.subroutine + 1u); j++)
    {
        if(j % SDRAM_WRITE_DATA_SWITCHING == 0u)
        {
            dataIDx++;
        }

        sdramAddress[j] = data[dataIDx];
        if(sdramAddress[j] != data[dataIDx])
        {
            sdramError.writeErrorCount++;
            if(sdramError.writeErrorCount == SDRAM_MAX_ERROR_COUNTER)
            {
                sdramError.writeErrorOverflow = true;
            }
        }
    }

    //read again after all data has been written
    dataIDx = 0;
    for(uint32_t i = SDRAM_SUB_SIZE_TESTING * sdramError.subroutine; i < SDRAM_SUB_SIZE_TESTING * (sdramError.subroutine + 1u); i++)
    {
        if(i % SDRAM_WRITE_DATA_SWITCHING == 0u)
        {
            dataIDx++;
        }
        if(sdramAddress[i] != data[dataIDx])
        {
            sdramError.readErrorCount++;
            if(sdramError.readErrorCount == SDRAM_MAX_ERROR_COUNTER)
            {
                sdramError.readErrorOverflow = true;
            }
        }
    }

    sdramError.subroutine++;
    if(sdramError.subroutine >= SDRAM_NUMBER_OF_SUBROUTINES)
    {
        sdramError.subroutine = 0u;

        sdramError.fullTestedCounter = (sdramError.fullTestedCounter < (uint8_t)UINT8_MAX) ? (sdramError.fullTestedCounter + 1u) : 0u;
    }
}

uint16_t sdram_getWriteErrorCounter(void)
{
    return sdramError.writeErrorCount;
}
uint16_t sdram_getReadErrorCounter(void)
{
    return sdramError.readErrorCount;
}
bool sdram_getWriteOverflow(void)
{
    return sdramError.writeErrorOverflow;
}
bool sdram_getReadOverflow(void)
{
    return sdramError.readErrorOverflow;
}

uint8_t sdram_getSubroutine(void)
{
    return sdramError.subroutine;
}
uint8_t sdram_getFullTestedCounter(void)
{
    return sdramError.fullTestedCounter;
}

void sdram_resetError(void)
{
    sdramError.writeErrorCount    = 0;
    sdramError.readErrorCount     = 0;
    sdramError.writeErrorOverflow = 0;
    sdramError.readErrorOverflow  = 0;
    sdramError.subroutine         = 0;
    sdramError.fullTestedCounter  = 0;
}
