/**
 * @file canopen_config.h
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

#include "canOpen.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define CANOPEN_NUMBER_OF_NODES 3u

#define CANOPEN_MAX_NUMBER_OF_NODES 127u

#define CANOPEN_NODE_ID_KION          0x27u
#define CANOPEN_NODE_ID_LINDE         0x0Du
#define CANOPEN_NODE_ID_LINDE_CHARGER 0x5Du
#define CANOPEN_NODE_ID_STILL         0x3Cu

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//

extern const CANopen canOpenConfigKion;
extern const CANopen canOpenConfigLinde;
extern const CANopen canOpenConfigLindeCharger;

// cppcheck-suppress misra-c2012-8.11 ; size is given by SDO_READ_TABLE_SIZE
extern const CANopen* const canOpenConfigs[];
extern const uint8_t CAN_OPEN_CONFIG_SIZE;

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
