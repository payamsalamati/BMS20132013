/**
 * @file ecuDateData.h
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

typedef struct
{
    uint8_t ecuInstallationDateYear;
    uint8_t ecuInstallationDateMonth;
    uint8_t ecuInstallationDateDay;
    uint8_t ecuManufacturingDateYear;
    uint8_t ecuManufacturingDateMonth;
    uint8_t ecuManufacturingDateDay;
    uint8_t writeBlockOnce;
    uint8_t dummy_for_crc_8;
} EcuDateNvmData;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void ecuDateData_checkNvm(const uint8_t* mirror, uint16_t length);
void ecuDateData_copyNvmForWrite(uint8_t* mirror, uint16_t length);

uint8_t ecuDateData_getEcuInstallationDateYear(void);
uint8_t ecuDateData_getEcuInstallationDateMonth(void);
uint8_t ecuDateData_getEcuInstallationDateDay(void);

void ecuDateData_setEcuInstallationDateYear(uint8_t newValue);
void ecuDateData_setEcuInstallationDateMonth(uint8_t newValue);
void ecuDateData_setEcuInstallationDateDay(uint8_t newValue);

/**
 * @brief function to read out the write block once indicatior of the NVM block
 *
 * @return uint8_t
 */
uint8_t ecuDateData_getWriteBlockOnceIndicator(void);

#if defined(UNIT_TEST)
void ecuDateData_clearAll();
#endif
