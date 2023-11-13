/**
 * @file componentsPowerConsumption.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "componentsPowerConsumption.h"
#include "task_cfg.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    uint16_t averageMasterConsumption;
    uint16_t averageCscConsumption;
    uint16_t averageCpsConsumption;
} ComponentsPowerConsumption;

#define COMPONENTS_POWER_CONSUMPTION_DEFAULT_AVERAGE_MASTER_CONSUMPTION 1u   // WHBMS-24894
#define COMPONENTS_POWER_CONSUMPTION_DEFAULT_AVERAGE_CSC_CONSUMPTION    80u  // WHBMS-24895
#define COMPONENTS_POWER_CONSUMPTION_DEFAULT_AVERAGE_CPS_CONSUMPTION    1u   // WHBMS-24896

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SEC_PARAMETER ComponentsPowerConsumption componentsPowerConsumption = {
    .averageMasterConsumption = COMPONENTS_POWER_CONSUMPTION_DEFAULT_AVERAGE_MASTER_CONSUMPTION,
    .averageCscConsumption    = COMPONENTS_POWER_CONSUMPTION_DEFAULT_AVERAGE_CSC_CONSUMPTION,
    .averageCpsConsumption    = COMPONENTS_POWER_CONSUMPTION_DEFAULT_AVERAGE_CPS_CONSUMPTION
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

uint16_t componentsPowerConsumption_getAverageOfMaster(void)
{
    return componentsPowerConsumption.averageMasterConsumption;
}

void componentsPowerConsumption_setAverageOfMaster(uint16_t newValue)
{
    componentsPowerConsumption.averageMasterConsumption = newValue;
}


uint16_t componentsPowerConsumption_getAverageOfCsc(void)
{
    return componentsPowerConsumption.averageCscConsumption;
}

void componentsPowerConsumption_setAverageOfCsc(uint16_t newValue)
{
    componentsPowerConsumption.averageCscConsumption = newValue;
}


uint16_t componentsPowerConsumption_getAverageOfCps(void)
{
    return componentsPowerConsumption.averageCpsConsumption;
}

void componentsPowerConsumption_setAverageOfCps(uint16_t newValue)
{
    componentsPowerConsumption.averageCpsConsumption = newValue;
}
