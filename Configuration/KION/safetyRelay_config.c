/**
 * @file safetyRelayCfg_ELOCITY.c
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

#include "relayTable.h"
#include "multi_master_config.h"
//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

// clang-format off
const RelayTable relayConfigSystemMaster[] = {
    // relayPos -               PreferredDirection           - AUX -    Safety  - HV_index      - Currentthreshold
    { RELAYPOSTYPE_MAIN_PLUS,       PREFDIRECTION_NONE, RELAYAUX_NOPEN,  true,  HIGH_VOLTAGE_1,             0},
    { RELAYPOSTYPE_MAIN_PLUS_2,     PREFDIRECTION_NONE, RELAYAUX_NOPEN,  true,  HIGH_VOLTAGE_2,             0},
    { RELAYPOSTYPE_NOT_CONNECTED,   PREFDIRECTION_NONE, RELAYAUX_NOPEN,  false, HIGH_VOLTAGE_NOT_CONNECTED, 0},
};
// clang-format on

const RelayTable relayConfigSubmaster[]          = {};
const uint16_t RELAY_CONFIG_SUBMASTER_TABLE_SIZE = sizeof(relayConfigSubmaster) / sizeof(RelayTable);

const uint16_t RELAY_CONFIG_SYSTEMMASTER_TABLE_SIZE = sizeof(relayConfigSystemMaster) / sizeof(RelayTable);

const uint16_t SAFETY_RELAY_CFG_STRING_TABLE_SIZE = 0u;

const RelayTable* const masterRelayCfgsTable[BMS_CONFIG_MAX_NUMBER_OF_MASTER] = {
    relayConfigSystemMaster,
};

const uint8_t RELAY_CONFIG_STRING_RELAY = 0u;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
