/**
 * @file onBoardTemperatureMonitor.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "onBoardTemperatureMonitor.h"
#include "onBoardTemperatureMonitor_config.h"

#include "measurements_getOnBoardTemperature.h"
#include "task_cfg.h"
#include "dem.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    int32_t onBoardTemperatureMonitorMax;
} OnBoardTemperatureMonitorConfig;

#define DTC_BMS_ONBOARD_TEMPERATURE_SENSOR_OVER_TEMPERATURE_IN_CELSIUS onBoardTemperatureMonitorConfig.onBoardTemperatureMonitorMax

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SEC_PARAMETER static OnBoardTemperatureMonitorConfig onBoardTemperatureMonitorConfig = {
    .onBoardTemperatureMonitorMax = DTC_BMS_ONBOARD_TEMPERATURE_SENSOR_DEFAULT_OVER_TEMPERATURE_IN_CELSIUS,
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void onBoardTemperatureMonitor_mainFunction(void)
{
    uint8_t onBoardTemperatureMaster = measurements_getOnBoardTemperature_getTSensorOnMaster();

    if(onBoardTemperatureMaster >= DTC_BMS_ONBOARD_TEMPERATURE_SENSOR_OVER_TEMPERATURE_IN_CELSIUS)
    {
        dem_reportFaultFromApp(DTC_BMS_ONBOARD_TEMP_SENSOR_OVER_TEMPERATURE);
    }
    else
    {
        dem_clearFaultFromApp(DTC_BMS_ONBOARD_TEMP_SENSOR_OVER_TEMPERATURE);
    }
}
