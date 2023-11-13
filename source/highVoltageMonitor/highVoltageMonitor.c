/**
 * @file highVoltageMonitor.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Checks the high voltage against the error limits.
 * @details
 *   Interfaces to other modules:
 *   - measurements
 *   - highVoltageMeasurement
 *   - subMasterInfoSend
 *   - errorDetection
 *   - dem
 *
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdlib.h>

#include "highVoltageMonitor.h"
#include "highVoltageMonitor_config.h"


#include "task_cfg.h"
#include "monitoring_config.h"
#include "highVoltageMeasurement.h"
#include "submasterVoltageMeasurement.h"
#include "subMasterInfoSend.h"
#include "errorDetection.h"
#include "dem.h"


//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

#define HV_VOLTAGE_DIFFERENCE_MAX_ERR_DETECT_VAL  hvVoltageMonitorConfigParameter.hvVoltageDifferenceMaxDetectVal
#define HV_VOLTAGE_DIFFERENCE_MAX_ERR_RELEASE_VAL hvVoltageMonitorConfigParameter.hvVoltageDifferenceMaxReleaseVal

#define HV_IN_FRONT_OF_CONTACTORS 0
#define HV_AFTER_CONTACTORS       2


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SEC_PARAMETER HvVoltageMonitorConfig hvVoltageMonitorConfigParameter = {
    .hvVoltageDifferenceMaxDetectVal  = HV_VOLTAGE_DEFAULT_DIFFERENCE_MAX_ERR_DETECT_VAL,
    .hvVoltageDifferenceMaxReleaseVal = HV_VOLTAGE_DEFAULT_DIFFERENCE_MAX_ERR_RELEASE_VAL,
};

const static uint32_t DEFAULT_ZERO_VALUE = 0;

static const ErrorConfig hvVoltageBatteryErrorConfig = {
    .type           = ErrorType_Max,
    .detectionValue = &HV_VOLTAGE_DIFFERENCE_MAX_ERR_DETECT_VAL,
    .detectionTime  = &DEFAULT_ZERO_VALUE,
    .releaseValue   = &HV_VOLTAGE_DIFFERENCE_MAX_ERR_RELEASE_VAL,
    .releaseTime    = &DEFAULT_ZERO_VALUE,
};

MEM_LIMITCHECK static Error hvVoltageVehicleError = {
    .currentErrorTime   = 0,
    .currentReleaseTime = 0,
    .faultCode          = DTC_SYSTEM_VOLTAGE_MONITOR_ERROR,
    .config             = &hvVoltageBatteryErrorConfig
};


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

// @req CB-15671 CB-15672 CB-15691
void highVoltageMonitor_mainFunction(void)
{
    int32_t voltageBattery = submasterVoltageMeasurement_getValue();

    if((subMasterInfoSend_isRelayOfTypeClosed(RELAYPOSTYPE_MAIN_PLUS) == true)
       && ((subMasterInfoSend_isRelayOfTypeClosed(RELAYPOSTYPE_MAIN_PLUS_2) == true)))
    {
        int32_t hvAfterOfContactors = highVoltageMeasurement_getMasterHvVoltagesValue(HV_AFTER_CONTACTORS);
        errorDetectionFromApp(&hvVoltageVehicleError, abs(voltageBattery - hvAfterOfContactors), MONITORING_CYCLE_TIME);
    }
    else
    {
        int32_t hvInFrontOfContactors = highVoltageMeasurement_getMasterHvVoltagesValue(HV_IN_FRONT_OF_CONTACTORS);
        errorDetectionFromApp(&hvVoltageVehicleError, abs(voltageBattery - hvInFrontOfContactors), MONITORING_CYCLE_TIME);
    }
}
