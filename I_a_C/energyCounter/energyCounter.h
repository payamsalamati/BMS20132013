/**
 * @file     energyCounter.h
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef struct ENERGY_COUNTER_NVM
{
    uint64_t diagnosticCoulombCountPositiveCharge;
    uint64_t diagnosticCoulombCountPositiveDischarge;
    uint64_t diagnosticCoulombCountNegativeDischarge;
} ENERGY_COUNTER_NVM;


//***************************************************************************//
//************************* PUBLIC FUNCTIONS DECLARATION *******************//
//***************************************************************************//

void energyCounter_mainFunction(void);
const ENERGY_COUNTER_NVM* energyCounter_getCoulombCounterData(void);
void energyCounter_checkNvm(const uint8_t* mirror, uint16_t length);
void energyCounter_copyNvmForWrite(uint8_t* mirror, uint16_t length);
void energyCounter_resetDiagnosticCoulombCount(void);
