/**
 * @file systemMasterBalancing.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "systemMasterBalancing.h"
#include "task_cfg.h"
#include "debug.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    bool masterBalancing;  // @req BMS-10059
} SystemMasterBalancingStruct;

#define BALANCING_TEMPERATURE_MAX 85  //@req CB-88950

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_BALANCING STATIC SystemMasterBalancingStruct systemMasterBalancingVariables = { 0 };

MEM_SEC_PARAMETER BalancingConfig balancingConfigParameter = {
    .maxTemperature = BALANCING_TEMPERATURE_MAX,
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

bool systemMasterBalancing_getMasterBalancing(void)
{
    return systemMasterBalancingVariables.masterBalancing;
}

void systemMasterBalancing_setMasterBalancing(bool value)
{
    systemMasterBalancingVariables.masterBalancing = value;
}
