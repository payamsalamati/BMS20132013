/**
 * @file heatingCurrentMeasurement.h
 * @copyright (c) Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
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


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

/**
 * @brief this function shall calculate the average heating current from multiple Cscs
 *
 */
void heatingCurrentMeasurement_mainFunction(void);

const int32_t* heatingCurrentMeasurement_getCurrents(uint16_t* size);

int32_t heatingCurrentMeasurement_getCurrentValue(uint8_t cscIndex);
