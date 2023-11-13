/**
 * @file limitCheckTask_config.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "limitCheckTask.h"
#include "limitCheckTask_config.h"
#include "diagnosticTimes.h"
#include "module_config.h"
#include "safetyTask.h"
#include "energyCounter.h"

#include "boardSupplyVoltageMonitor.h"
#include "onBoardTemperatureMonitor.h"
#include "KBSInterface.h"

#if BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS > 0u
#include "terminalTemperatureMeasurement.h"
#include "terminalTemperatureMonitor.h"
#endif
#include "cps.h"
#include "eventData.h"
#include "serviceRequirement.h"
#include "subMasterBalancing.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

extern MEM_SEC_PARAMETER_KBS KBSInput kbsInput;
extern MEM_SEC_PARAMETER_KBS KBSOutput kbsOutput;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void limitCheckTask_projectSpecificProcess(void)
{

    if(safetyTask_isSecondarySafetyLayerRunning() == true)
    {
        energyCounter_mainFunction();
        diagnosticTimes_mainFunction();
#if BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS > 0u
        terminalTemperatureMeasurement_mainFunction();
        terminalTemperatureMonitor_mainFunction();
#endif
        boardSupplyVoltageMonitor_mainFunction();
        onBoardTemperatureMonitor_mainFunction();
        eventData_mainFunction();
        subMasterBalancing_mainFunction();
    }
    cps_enableWakeUp();
}
