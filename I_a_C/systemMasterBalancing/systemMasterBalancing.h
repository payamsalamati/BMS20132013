/**
 * @file systemMasterBalancing.h
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

#include <stdbool.h>
#include <stdint.h>
#include "task_cfg.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef struct
{
    int8_t maxTemperature;
} BalancingConfig;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//

extern MEM_SEC_PARAMETER BalancingConfig balancingConfigParameter;

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

bool systemMasterBalancing_getMasterBalancing(void);

void systemMasterBalancing_setMasterBalancing(bool value);
