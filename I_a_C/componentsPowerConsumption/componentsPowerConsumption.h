/**
 * @file componentsPowerConsumption.h
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

uint16_t componentsPowerConsumption_getAverageOfMaster(void);
void componentsPowerConsumption_setAverageOfMaster(uint16_t newValue);

uint16_t componentsPowerConsumption_getAverageOfCsc(void);
void componentsPowerConsumption_setAverageOfCsc(uint16_t newValue);

uint16_t componentsPowerConsumption_getAverageOfCps(void);
void componentsPowerConsumption_setAverageOfCps(uint16_t newValue);
