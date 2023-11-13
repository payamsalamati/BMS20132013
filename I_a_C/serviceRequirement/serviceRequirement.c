/**
 * @file serviceRequirement.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "serviceRequirement.h"
#include "dem.h"
#include "task_cfg.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

const DTC serviceRequiredDtcs[] = {
    DTC_DEEP_DISCHARGE_CELL_DAMAGE_ERROR,
    DTC_CELL_OVER_VOLTAGE_ERROR,
    DTC_KBS_INTERFACE_MONITOR_21,
    DTC_KBS_INTERFACE_MONITOR_22,
};

const uint8_t SERVICE_REQUIRED_DTCS_SIZE = sizeof(serviceRequiredDtcs) / sizeof(DTC);

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

// @req CB-75098
bool serviceRequirement_getServiceRequired(void)
{
    bool isServiceRequired = false;
    for(uint8_t i = 0; (i < SERVICE_REQUIRED_DTCS_SIZE) && (!isServiceRequired); i++)
    {
        if(dem_isFaultActive(serviceRequiredDtcs[i], true) == true)
        {
            isServiceRequired = true;
        }
    }
    return isServiceRequired;
}
