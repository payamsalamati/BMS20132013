/**
 * @file subMasterBalancing.h
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


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void subMasterBalancing_mainFunction(void);

void subMasterBalancing_setCellBalancingStatusValueByCell(uint8_t state, uint8_t slaveNumber, uint8_t cellNumber);

uint16_t subMasterBalancing_getCellBalancingStatusValue(uint16_t i);

uint16_t subMasterBalancing_getCellBalancingStatusValueMasked(uint16_t cscAddress);
