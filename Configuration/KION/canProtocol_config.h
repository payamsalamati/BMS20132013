/**
 * @file canProtocol_config.h
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

#include "task_cfg.h"
#include "stdint.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define EXTERNAL_CAN_NODE                       CAN_NODE_2
#define EXTERNALCAN_MAX_MISSING_ACK_ERROR_COUNT 3u

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//

typedef enum CAN_PROTOCOL
{
    CAN_PROTOCOL_DISABLED = 0,
    CAN_PROTOCOL_BASE     = 1,
    CAN_PROTOCOL_LINDE    = 2,
    CAN_PROTOCOL_KION     = 3
} CAN_PROTOCOL;

extern MEM_CAN uint16_t missingAckErrorCntExternal;
extern MEM_CAN uint16_t missingAckErrorCntInternal;

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
