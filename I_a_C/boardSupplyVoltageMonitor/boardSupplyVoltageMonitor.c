/**
 * @file boardSupplyVoltageMonitor.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "boardSupplyVoltageMonitor.h"
#include "boardSupplyVoltageMonitor_config.h"

#include "task_cfg.h"

#include "supplyVoltageMeasurement.h"
#include "dem.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    int32_t boardSupplyVoltageMonitorMaxDetectVal;
    int32_t boardSupplyVoltageMonitorMinDetectVal;
} BoardSupplyVoltageMonitorParameter;

#define BOARD_SUPPLY_VOLTAGE_MONITOR_MAX_WARN_DETECT_VAL boardSupplyVoltageMonitorConfigParameter.boardSupplyVoltageMonitorMaxDetectVal
#define BOARD_SUPPLY_VOLTAGE_MONITOR_MIN_WARN_DETECT_VAL boardSupplyVoltageMonitorConfigParameter.boardSupplyVoltageMonitorMinDetectVal

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SEC_PARAMETER static BoardSupplyVoltageMonitorParameter boardSupplyVoltageMonitorConfigParameter = {
    .boardSupplyVoltageMonitorMaxDetectVal = BOARD_SUPPLY_VOLTAGE_MONITOR_DEFAULT_MAX_DETECT_VAL,
    .boardSupplyVoltageMonitorMinDetectVal = BOARD_SUPPLY_VOLTAGE_MONITOR_DEFAULT_MIN_DETECT_VAL,
};


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void boardSupplyVoltageMonitor_mainFunction(void)
{
    int32_t boardSupplyVoltage = supplyVoltageMeasurement_getBoardSupply();

    if(boardSupplyVoltage >= BOARD_SUPPLY_VOLTAGE_MONITOR_MAX_WARN_DETECT_VAL)
    {
        dem_reportFaultFromApp(DTC_BMS_SUPPLY_OVER_VOLTAGE_FAULT);
    }
    else
    {
        dem_clearFaultFromApp(DTC_BMS_SUPPLY_OVER_VOLTAGE_FAULT);
    }

    if(boardSupplyVoltage <= BOARD_SUPPLY_VOLTAGE_MONITOR_DEFAULT_MIN_DETECT_VAL)
    {
        dem_reportFaultFromApp(DTC_BMS_SUPPLY_LOW_VOLTAGE_FAULT);
    }
    else
    {
        dem_clearFaultFromApp(DTC_BMS_SUPPLY_LOW_VOLTAGE_FAULT);
    }
}
