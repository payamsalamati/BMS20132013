/**
 * @file subMasterBalancing.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "subMasterBalancing.h"
#include "task_cfg.h"
#if !defined(UNIT_TEST)
#include "bms.h"
#include "csc_config.h"
#include "cell_module.h"
#else
#include "test_subMasterBalancing.h"
#endif
#include "debug.h"
#include "dem.h"
#include "afeCheck.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    // @req BMS-11576
    uint16_t cellBalancingStatus[BMS_CONFIG_MAX_NUMBER_OF_SLAVES];  // bitmask for cell balancing status
} SubMasterBalancingStruct;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_BALANCING STATIC SubMasterBalancingStruct subMasterBalancingVariables;

MEM_BALANCING uint16_t cellBalancingStatusMasked[BMS_CONFIG_MAX_NUMBER_OF_SLAVES] = { 0 };  // stores bitmasks of cell balancing status that are dependent on DTCs


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

// @req CB-91234 CB-91244 CB-91253
void subMasterBalancing_mainFunction(void)
{
    uint8_t demFaultListSize      = 0u;
    const DEM_Fault* demFaultList = dem_getFaultInfo(&demFaultListSize);

    for(uint8_t cscAddress = 0u; cscAddress < BMS_CONFIG_NUMBER_OF_SLAVES; cscAddress++)
    {
        cellBalancingStatusMasked[cscAddress] = subMasterBalancing_getCellBalancingStatusValue(cscAddress);
    }

    for(uint8_t index = 0u; ((index < demFaultListSize) && (index < DEM_FAULT_CODES_MAX)); index++)
    {
        DEM_FaultCode currentFaultCode = demFaultList[index].fault;
        if(currentFaultCode == DTC_BALANCING_OVER_TEMPERATURE_ALERT)
        {
            memset(&cellBalancingStatusMasked[0], 0, (sizeof(uint16_t) * BMS_CONFIG_MAX_NUMBER_OF_SLAVES));
        }
    }
}

void subMasterBalancing_setCellBalancingStatusValueByCell(uint8_t state, uint8_t cscIndex, uint8_t cellNumber)
{
    DEBUG_ASSERT(cscIndex < BMS_CONFIG_NUMBER_OF_SLAVES);
    if((state == 0u) && (cellNumber < CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL))
    {
        subMasterBalancingVariables.cellBalancingStatus[cscIndex] &= ~(0x01u << cellNumber);
    }
    else if((state == 1u) && (cellNumber < CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL))
    {
        subMasterBalancingVariables.cellBalancingStatus[cscIndex] |= 0x01u << cellNumber;
    }
    else
    {
        // do nothing
    }
}

uint16_t subMasterBalancing_getCellBalancingStatusValue(uint16_t i)
{
    DEBUG_API_CHECK(i < BMS_CONFIG_NUMBER_OF_SLAVES);
    return (i < BMS_CONFIG_NUMBER_OF_SLAVES) ? subMasterBalancingVariables.cellBalancingStatus[i] : 0u;
}

uint16_t subMasterBalancing_getCellBalancingStatusValueMasked(uint16_t cscAddress)
{
    uint16_t retVal = 0u;
    if(cscAddress < BMS_CONFIG_NUMBER_OF_SLAVES)
    {
        retVal = cellBalancingStatusMasked[cscAddress];
    }
    return retVal;
}
