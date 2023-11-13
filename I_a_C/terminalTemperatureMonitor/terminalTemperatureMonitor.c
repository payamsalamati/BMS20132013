/**
 * @file terminalTemperatureMonitor.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "terminalTemperatureMonitor.h"
#include "terminalTemperatureMonitor_config.h"
#include "terminalTemperatureMeasurement.h"
#include "dem.h"
#include "task_cfg.h"
#if !defined(UNIT_TEST)
#include "bms_config.h"
#endif

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


#define DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1_VALUE     terminalTemperatureMonitorConfigParameter.terminalTemperaturePlusThreshold1
#define DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2_VALUE     terminalTemperatureMonitorConfigParameter.terminalTemperaturePlusThreshold2
#define DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1_VALUE terminalTemperatureMonitorConfigParameter.terminalTemperatureNegativeThreshold1
#define DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2_VALUE terminalTemperatureMonitorConfigParameter.terminalTemperatureNegativeThreshold2

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SEC_PARAMETER static TerminalTemperatureMonitorConfig terminalTemperatureMonitorConfigParameter = {
    .terminalTemperaturePlusThreshold1     = DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1_DEFAULT,
    .terminalTemperaturePlusThreshold2     = DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2_DEFAULT,
    .terminalTemperatureNegativeThreshold1 = DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1_DEFAULT,
    .terminalTemperatureNegativeThreshold2 = DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2_DEFAULT
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

// @req CB-77017 CB-77018 CB-77019 CB-77020
void terminalTemperatureMonitor_mainFunction(void)
{
    int16_t maxTempPlusTerminal     = -128;
    int16_t maxTempNegativeTerminal = -128;

    for(uint8_t i = 0; i < BMS_CONFIG_NUMBER_OF_SLAVES; i++)
    {
        int16_t temp        = terminalTemperatureMeasurement_getPlusTerminalTemperature(i);
        maxTempPlusTerminal = (temp > maxTempPlusTerminal) ? temp : maxTempPlusTerminal;

        temp                    = terminalTemperatureMeasurement_getMinusTerminalTemperature(i);
        maxTempNegativeTerminal = (temp > maxTempNegativeTerminal) ? temp : maxTempNegativeTerminal;
    }


    (maxTempPlusTerminal > DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1_VALUE) ? dem_reportFaultFromApp(DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1) : dem_clearFaultFromApp(DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1);
    (maxTempPlusTerminal > DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2_VALUE) ? dem_reportFaultFromApp(DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2) : dem_clearFaultFromApp(DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2);

    (maxTempNegativeTerminal > DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1_VALUE) ? dem_reportFaultFromApp(DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1) : dem_clearFaultFromApp(DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1);
    (maxTempNegativeTerminal > DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2_VALUE) ? dem_reportFaultFromApp(DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2) : dem_clearFaultFromApp(DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2);
}
