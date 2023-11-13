

/**
 * @file protocolSelection.h
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
#include <stdbool.h>

#include "canIf.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef enum
{
    Protocol_KION,
    Protocol_LINDE,
    Protocol_AUTOMATIC,
    Protocol_ERROR,
} Protocol;

typedef struct
{
    Protocol brandIdConfig;
} ProtocolSelectionConfig;

extern ProtocolSelectionConfig protocolSelectionConfigParameter;

#define PROTOCOL_SELECTION_CONFIG_BRAND_ID_DETECTION protocolSelectionConfigParameter.brandIdConfig

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void protocolSelection_checkNvm(const uint8_t* mirror, uint16_t length);
void protocolSelection_copyNvmForWrite(uint8_t* mirror, uint16_t length);
void protocolSelection_init(void);
bool protocolSelection_isNvmRead(void);

void protocolSelection_setBrand(Protocol newSetting);
Protocol protocolSelection_getLastBrand(void);
Protocol protocolSelection_getBrand(void);
bool protocolSelection_getAuthentificationComplete(void);
void protocolSelection_resetBrand(void);

bool protocolSelection_setBrandIdConfig(uint16_t newValue);

#if defined(UNIT_TEST)
void protocolSelection_resetAll(void);
#endif
