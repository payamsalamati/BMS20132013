/**
 * @file postBuildConfiguration_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
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
#if defined(TMS570LS1224)
#define POST_BUILD_CONFIGURATION_DATA_SECTOR_NUMBER 15u
#elif defined(TMS570LS0914) || defined(TMS570LS1114)
#define POST_BUILD_CONFIGURATION_DATA_SECTOR_NUMBER 13u
#else
#error "WRONG MCU"
#endif

#define INFINITYLOOP() for(;;)

typedef uint32_t address_size;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
