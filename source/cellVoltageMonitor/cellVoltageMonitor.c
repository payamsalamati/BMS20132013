/**
 * @file cellVoltageMonitor.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Checks all plausible cell voltage values against the warning, alert and error limits.
 * @details
 *   Interfaces to other modules:
 *   - cellVoltageMeasurement
 *   - errorDetection
 *   - dem
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "cellVoltageMonitor.h"
#include "voltageMonitor_config.h"
#include "task_cfg.h"
#include "monitoring_config.h"


#include "cellVoltageMeasurement.h"
#include "errorDetection.h"
#include "dem.h"
#include "batteryCurrentMeasurement.h"
#include "cscNvm_config.h"
#if defined(UNIT_TEST)
#include "test_cellVoltageMonitor_config.h"
#else
#include "module_config.h"
#endif

#include "debug.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

#define CELL_VOLTAGE_MAX_WARN_DETECT_TIME  voltageMonitorConfigParameter.voltageWarningMaxDetectTime
#define CELL_VOLTAGE_MAX_WARN_DETECT_VAL   voltageMonitorConfigParameter.voltageWarningMaxDetectVal
#define CELL_VOLTAGE_MAX_WARN_RELEASE_TIME voltageMonitorConfigParameter.voltageWarningMaxReleaseTime
#define CELL_VOLTAGE_MAX_WARN_RELEASE_VAL  voltageMonitorConfigParameter.voltageWarningMaxReleaseVal

#define CELL_VOLTAGE_MIN_WARN_DETECT_VAL   voltageMonitorConfigParameter.voltageWarningMinDetectVal
#define CELL_VOLTAGE_MIN_WARN_DETECT_TIME  voltageMonitorConfigParameter.voltageWarningMinDetectTime
#define CELL_VOLTAGE_MIN_WARN_RELEASE_TIME voltageMonitorConfigParameter.voltageWarningMinReleaseTime
#define CELL_VOLTAGE_MIN_WARN_RELEASE_VAL  voltageMonitorConfigParameter.voltageWarningMinReleaseVal

#define CELL_VOLTAGE_MAX_ALERT_DETECT_TIME  voltageMonitorConfigParameter.voltageAlertMaxDetectTime
#define CELL_VOLTAGE_MAX_ALERT_DETECT_VAL   voltageMonitorConfigParameter.voltageAlertMaxDetectVal
#define CELL_VOLTAGE_MAX_ALERT_RELEASE_TIME voltageMonitorConfigParameter.voltageAlertMaxReleaseTime
#define CELL_VOLTAGE_MAX_ALERT_RELEASE_VAL  voltageMonitorConfigParameter.voltageAlertMaxReleaseVal

#define CELL_VOLTAGE_MIN_ALERT_DETECT_TIME  voltageMonitorConfigParameter.voltageAlertMinDetectTime
#define CELL_VOLTAGE_MIN_ALERT_DETECT_VAL   voltageMonitorConfigParameter.voltageAlertMinDetectVal
#define CELL_VOLTAGE_MIN_ALERT_RELEASE_TIME voltageMonitorConfigParameter.voltageAlertMinReleaseTime
#define CELL_VOLTAGE_MIN_ALERT_RELEASE_VAL  voltageMonitorConfigParameter.voltageAlertMinReleaseVal

#define CELL_VOLTAGE_MAX_ERR_DETECT_TIME  voltageMonitorConfigParameter.voltageErrorMaxDetectTime
#define CELL_VOLTAGE_MAX_ERR_DETECT_VAL   voltageMonitorConfigParameter.voltageErrorMaxDetectVal
#define CELL_VOLTAGE_MAX_ERR_RELEASE_TIME voltageMonitorConfigParameter.voltageErrorMaxReleaseTime
#define CELL_VOLTAGE_MAX_ERR_RELEASE_VAL  voltageMonitorConfigParameter.voltageErrorMaxReleaseVal

#define CELL_VOLTAGE_MIN_ERR_DETECT_TIME  voltageMonitorConfigParameter.voltageErrorMinDetectTime
#define CELL_VOLTAGE_MIN_ERR_DETECT_VAL   voltageMonitorConfigParameter.voltageErrorMinDetectVal
#define CELL_VOLTAGE_MIN_ERR_RELEASE_TIME voltageMonitorConfigParameter.voltageErrorMinReleaseTime
#define CELL_VOLTAGE_MIN_ERR_RELEASE_VAL  voltageMonitorConfigParameter.voltageErrorMinReleaseVal

#define CELL_VOLTAGE_DEEP_DISCHARGE_DETECT_VAL  voltageMonitorConfigParameter.voltageDeepDischargeDetectVal
#define CELL_VOLTAGE_DEEP_DISCHARGE_RELEASE_VAL voltageMonitorConfigParameter.voltageDeepDischargeReleaseVal

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

void cellVoltageMonitor_postMainFunctionHook(void);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SEC_PARAMETER CellVoltageMonitorConfig voltageMonitorConfigParameter = {
    .voltageWarningMaxDetectVal     = CELL_VOLTAGE_DEFAULT_MAX_WARN_DETECT_VAL,
    .voltageWarningMaxDetectTime    = CELL_VOLTAGE_DEFAULT_MAX_WARN_DETECT_TIME,
    .voltageWarningMaxReleaseVal    = CELL_VOLTAGE_DEFAULT_MAX_WARN_RELEASE_VAL,
    .voltageWarningMaxReleaseTime   = CELL_VOLTAGE_DEFAULT_MAX_WARN_RELEASE_TIME,
    .voltageAlertMaxDetectVal       = CELL_VOLTAGE_DEFAULT_MAX_ALERT_DETECT_VAL,
    .voltageAlertMaxDetectTime      = CELL_VOLTAGE_DEFAULT_MAX_ALERT_DETECT_TIME,
    .voltageAlertMaxReleaseVal      = CELL_VOLTAGE_DEFAULT_MAX_ALERT_RELEASE_VAL,
    .voltageAlertMaxReleaseTime     = CELL_VOLTAGE_DEFAULT_MAX_ALERT_RELEASE_TIME,
    .voltageErrorMaxDetectVal       = CELL_VOLTAGE_DEFAULT_MAX_ERR_DETECT_VAL,
    .voltageErrorMaxDetectTime      = CELL_VOLTAGE_DEFAULT_MAX_ERR_DETECT_TIME,
    .voltageErrorMaxReleaseVal      = CELL_VOLTAGE_DEFAULT_MAX_ERR_RELEASE_VAL,
    .voltageErrorMaxReleaseTime     = CELL_VOLTAGE_DEFAULT_MAX_ERR_RELEASE_TIME,
    .voltageWarningMinDetectVal     = CELL_VOLTAGE_DEFAULT_MIN_WARN_DETECT_VAL,
    .voltageWarningMinDetectTime    = CELL_VOLTAGE_DEFAULT_MIN_WARN_DETECT_TIME,
    .voltageWarningMinReleaseVal    = CELL_VOLTAGE_DEFAULT_MIN_WARN_RELEASE_VAL,
    .voltageWarningMinReleaseTime   = CELL_VOLTAGE_DEFAULT_MIN_WARN_RELEASE_TIME,
    .voltageAlertMinDetectVal       = CELL_VOLTAGE_DEFAULT_MIN_ALERT_DETECT_VAL,
    .voltageAlertMinDetectTime      = CELL_VOLTAGE_DEFAULT_MIN_ALERT_DETECT_TIME,
    .voltageAlertMinReleaseVal      = CELL_VOLTAGE_DEFAULT_MIN_ALERT_RELEASE_VAL,
    .voltageAlertMinReleaseTime     = CELL_VOLTAGE_DEFAULT_MIN_ALERT_RELEASE_TIME,
    .voltageErrorMinDetectVal       = CELL_VOLTAGE_DEFAULT_MIN_ERR_DETECT_VAL,
    .voltageErrorMinDetectTime      = CELL_VOLTAGE_DEFAULT_MIN_ERR_DETECT_TIME,
    .voltageErrorMinReleaseVal      = CELL_VOLTAGE_DEFAULT_MIN_ERR_RELEASE_VAL,
    .voltageErrorMinReleaseTime     = CELL_VOLTAGE_DEFAULT_MIN_ERR_RELEASE_TIME,
    .voltageDeepDischargeDetectVal  = CELL_VOLTAGE_DEFAULT_DEEP_DISCHARGE_DETECT_VAL,
    .voltageDeepDischargeReleaseVal = CELL_VOLTAGE_DEFAULT_DEEP_DISCHARGE_RELEASE_VAL,
};

const static uint32_t DEFAULT_ZERO_VALUE = 0;

static const ErrorConfig lowWarningConfig = {
    .type           = ErrorType_Min,
    .detectionValue = &CELL_VOLTAGE_MIN_WARN_DETECT_VAL,
    .detectionTime  = &CELL_VOLTAGE_MIN_WARN_DETECT_TIME,
    .releaseValue   = &CELL_VOLTAGE_MIN_WARN_RELEASE_VAL,
    .releaseTime    = &CELL_VOLTAGE_MIN_WARN_RELEASE_TIME,
};

// @req CB-76999
MEM_SAFETY static Error lowWarning = {
    .currentErrorTime   = 0,
    .currentReleaseTime = 0,
    .faultCode          = DTC_CELL_UNDER_VOLTAGE_WARNING,
    .config             = &lowWarningConfig
};

static const ErrorConfig lowAlertConfig = {
    .type           = ErrorType_Min,
    .detectionValue = &CELL_VOLTAGE_MIN_ALERT_DETECT_VAL,
    .detectionTime  = &CELL_VOLTAGE_MIN_ALERT_DETECT_TIME,
    .releaseValue   = &CELL_VOLTAGE_MIN_ALERT_RELEASE_VAL,
    .releaseTime    = &CELL_VOLTAGE_MIN_ALERT_RELEASE_TIME
};

// @req CB-77000
MEM_SAFETY static Error lowAlert = {
    .currentErrorTime   = 0,
    .currentReleaseTime = 0,
    .faultCode          = DTC_CELL_UNDER_VOLTAGE_ALERT,
    .config             = &lowAlertConfig
};

static const ErrorConfig lowErrorConfig = {
    .type           = ErrorType_Min,
    .detectionValue = &CELL_VOLTAGE_MIN_ERR_DETECT_VAL,
    .detectionTime  = &CELL_VOLTAGE_MIN_ERR_DETECT_TIME,
    .releaseValue   = &CELL_VOLTAGE_MIN_ERR_RELEASE_VAL,
    .releaseTime    = &CELL_VOLTAGE_MIN_ERR_RELEASE_TIME
};

// @req CB-77002
MEM_SAFETY static Error lowError = {
    .currentErrorTime   = 0,
    .currentReleaseTime = 0,
    .faultCode          = DTC_CELL_UNDER_VOLTAGE_ERROR,
    .config             = &lowErrorConfig
};

static const ErrorConfig highWarningConfig = {
    .type           = ErrorType_Max,
    .detectionValue = &CELL_VOLTAGE_MAX_WARN_DETECT_VAL,
    .detectionTime  = &CELL_VOLTAGE_MAX_WARN_DETECT_TIME,
    .releaseValue   = &CELL_VOLTAGE_MAX_WARN_RELEASE_VAL,
    .releaseTime    = &CELL_VOLTAGE_MAX_WARN_RELEASE_TIME
};

// @req CB-76996
MEM_SAFETY static Error highWarning = {
    .currentErrorTime   = 0,
    .currentReleaseTime = 0,
    .faultCode          = DTC_CELL_OVER_VOLTAGE_WARNING,
    .config             = &highWarningConfig
};

static const ErrorConfig highAlertConfig = {
    .type           = ErrorType_Max,
    .detectionValue = &CELL_VOLTAGE_MAX_ALERT_DETECT_VAL,
    .detectionTime  = &CELL_VOLTAGE_MAX_ALERT_DETECT_TIME,
    .releaseValue   = &CELL_VOLTAGE_MAX_ALERT_RELEASE_VAL,
    .releaseTime    = &CELL_VOLTAGE_MAX_ALERT_RELEASE_TIME
};

// @req CB-76997
MEM_SAFETY static Error highAlert = {
    .currentErrorTime   = 0,
    .currentReleaseTime = 0,
    .faultCode          = DTC_CELL_OVER_VOLTAGE_ALERT,
    .config             = &highAlertConfig
};

static const ErrorConfig highErrorConfig = {
    .type           = ErrorType_Max,
    .detectionValue = &CELL_VOLTAGE_MAX_ERR_DETECT_VAL,
    .detectionTime  = &CELL_VOLTAGE_MAX_ERR_DETECT_TIME,
    .releaseValue   = &CELL_VOLTAGE_MAX_ERR_RELEASE_VAL,
    .releaseTime    = &CELL_VOLTAGE_MAX_ERR_RELEASE_TIME
};

// @req CB-76998
MEM_SAFETY static Error highError = {
    .currentErrorTime   = 0,
    .currentReleaseTime = 0,
    .faultCode          = DTC_CELL_OVER_VOLTAGE_ERROR,
    .config             = &highErrorConfig
};

static const ErrorConfig deepDischargeConfig = {
    .type           = ErrorType_Min,
    .detectionValue = &CELL_VOLTAGE_DEEP_DISCHARGE_DETECT_VAL,
    .detectionTime  = &DEFAULT_ZERO_VALUE,
    .releaseValue   = &CELL_VOLTAGE_DEEP_DISCHARGE_RELEASE_VAL,
    .releaseTime    = &DEFAULT_ZERO_VALUE,
};

MEM_SAFETY static Error deepDischarge = {
    .currentErrorTime   = 0,
    .currentReleaseTime = 0,
    .faultCode          = DTC_DEEP_DISCHARGE,
    .config             = &deepDischargeConfig
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

void cellVoltageMonitor_postMainFunctionHook(void)
{
    // @req CB-80078
    if(dem_isFaultActive(DTC_DEEP_DISCHARGE, false) == true)
    {
        for(uint8_t cscAddress = 1; cscAddress <= BMS_CONFIG_NUMBER_OF_SLAVES; cscAddress++)
        {
            if(cellVoltageMeasurement_getMinValueCSC(cscAddress) < CELL_VOLTAGE_DEEP_DISCHARGE_DETECT_VAL)
            {
                // @req CB-80080
                cscNvm_setDeepDischargeFlag(true, cscAddress);
            }
        }
        // @req CB-77004 CB-77005
        dem_reportFault(DTC_DEEP_DISCHARGE_CELL_DAMAGE_ERROR);
    }
    for(uint8_t cscAddress = 1; cscAddress <= BMS_CONFIG_NUMBER_OF_SLAVES; cscAddress++)
    {
        // @req CB-80083
        if(cscNvm_getDeepDischargeFlag(cscAddress) == true)
        {
            dem_reportFault(DTC_DEEP_DISCHARGE_CELL_DAMAGE_ERROR);
        }
    }
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void cellVoltageMonitor_mainFunction(void)
{
    // read input
    int32_t maxVoltage = (int32_t)cellVoltageMeasurement_getMaxValue();
    int32_t minVoltage = (int32_t)cellVoltageMeasurement_getMinValue();

    int32_t current = batteryCurrentMeasurement_getValue();
    if(current < 0)
    {
        errorDetection(&lowWarning, minVoltage, MONITORING_CYCLE_TIME);
        errorDetection(&lowAlert, minVoltage, MONITORING_CYCLE_TIME);
        // @req CB-15657
        errorDetection(&lowError, minVoltage, MONITORING_CYCLE_TIME);
        // @req CB-15653
        errorDetection(&deepDischarge, minVoltage, MONITORING_CYCLE_TIME);
    }
    else
    {
        lowWarning.currentErrorTime = 0;
        lowAlert.currentErrorTime   = 0;
        lowError.currentErrorTime   = 0;
        dem_clearFault(DTC_CELL_UNDER_VOLTAGE_WARNING);
        dem_clearFault(DTC_CELL_UNDER_VOLTAGE_ALERT);
        dem_clearFault(DTC_CELL_UNDER_VOLTAGE_ERROR);
    }

    errorDetection(&highWarning, maxVoltage, MONITORING_CYCLE_TIME);
    errorDetection(&highAlert, maxVoltage, MONITORING_CYCLE_TIME);
    // @req CB-15656
    errorDetection(&highError, maxVoltage, MONITORING_CYCLE_TIME);
    cellVoltageMonitor_postMainFunctionHook();
}

int32_t cellVoltageMonitor_getMaxWarnDetectVal(void)
{
    return CELL_VOLTAGE_MAX_WARN_DETECT_VAL;
}

uint32_t cellVoltageMonitor_getMaxWarnDetectTime(void)
{
    return CELL_VOLTAGE_MAX_WARN_DETECT_TIME;
}

int32_t cellVoltageMonitor_getMaxWarnReleaseVal(void)
{
    return CELL_VOLTAGE_MAX_WARN_RELEASE_VAL;
}

uint32_t cellVoltageMonitor_getMaxWarnReleaseTime(void)
{
    return CELL_VOLTAGE_MAX_WARN_RELEASE_TIME;
}

int32_t cellVoltageMonitor_getMaxAlertDetectVal(void)
{
    return CELL_VOLTAGE_MAX_ALERT_DETECT_VAL;
}

uint32_t cellVoltageMonitor_getMaxAlertDetectTime(void)
{
    return CELL_VOLTAGE_MAX_ALERT_DETECT_TIME;
}

int32_t cellVoltageMonitor_getMaxAlertReleaseVal(void)
{
    return CELL_VOLTAGE_MAX_ALERT_RELEASE_VAL;
}

uint32_t cellVoltageMonitor_getMaxAlertReleaseTime(void)
{
    return CELL_VOLTAGE_MAX_ALERT_RELEASE_TIME;
}


int32_t cellVoltageMonitor_getMaxErrDetectVal(void)
{
    return CELL_VOLTAGE_MAX_ERR_DETECT_VAL;
}

uint32_t cellVoltageMonitor_getMaxErrDetectTime(void)
{
    return CELL_VOLTAGE_MAX_ERR_DETECT_TIME;
}

int32_t cellVoltageMonitor_getMaxErrReleaseVal(void)
{
    return CELL_VOLTAGE_MAX_ERR_RELEASE_VAL;
}

uint32_t cellVoltageMonitor_getMaxErrReleaseTime(void)
{
    return CELL_VOLTAGE_MAX_ERR_RELEASE_TIME;
}

int32_t cellVoltageMonitor_getMinWarnDetectVal(void)
{
    return CELL_VOLTAGE_MIN_WARN_DETECT_VAL;
}

uint32_t cellVoltageMonitor_getMinWarnDetectTime(void)
{
    return CELL_VOLTAGE_MIN_WARN_DETECT_TIME;
}

int32_t cellVoltageMonitor_getMinWarnReleaseVal(void)
{
    return CELL_VOLTAGE_MIN_WARN_RELEASE_VAL;
}

uint32_t cellVoltageMonitor_getMinWarnReleaseTime(void)
{
    return CELL_VOLTAGE_MIN_WARN_RELEASE_TIME;
}

int32_t cellVoltageMonitor_getMinAlertDetectVal(void)
{
    return CELL_VOLTAGE_MIN_ALERT_DETECT_VAL;
}

uint32_t cellVoltageMonitor_getMinAlertDetectTime(void)
{
    return CELL_VOLTAGE_MIN_ALERT_DETECT_TIME;
}

int32_t cellVoltageMonitor_getMinAlertReleaseVal(void)
{
    return CELL_VOLTAGE_MIN_ALERT_RELEASE_VAL;
}

uint32_t cellVoltageMonitor_getMinAlertReleaseTime(void)
{
    return CELL_VOLTAGE_MIN_ALERT_RELEASE_TIME;
}

int32_t cellVoltageMonitor_getMinErrDetectVal(void)
{
    return CELL_VOLTAGE_MIN_ERR_DETECT_VAL;
}

uint32_t cellVoltageMonitor_getMinErrDetectTime(void)
{
    return CELL_VOLTAGE_MIN_ERR_DETECT_TIME;
}

int32_t cellVoltageMonitor_getMinErrReleaseVal(void)
{
    return CELL_VOLTAGE_MIN_ERR_RELEASE_VAL;
}

uint32_t cellVoltageMonitor_getMinErrReleaseTime(void)
{
    return CELL_VOLTAGE_MIN_ERR_RELEASE_TIME;
}

int32_t cellVoltageMonitor_getDeepDischargeDetectVal(void)
{
    return CELL_VOLTAGE_DEEP_DISCHARGE_DETECT_VAL;
}

int32_t cellVoltageMonitor_getDeepDischargeReleaseVal(void)
{
    return CELL_VOLTAGE_DEEP_DISCHARGE_RELEASE_VAL;
}

#if defined(UNIT_TEST)
void cellVoltageMonitor_reset(void)
{
    highWarning.currentErrorTime   = 0;
    highWarning.currentReleaseTime = 0;
    highAlert.currentErrorTime     = 0;
    highAlert.currentReleaseTime   = 0;
    highError.currentErrorTime     = 0;
    highError.currentReleaseTime   = 0;
    lowWarning.currentErrorTime    = 0;
    lowWarning.currentReleaseTime  = 0;
    lowAlert.currentErrorTime      = 0;
    lowAlert.currentReleaseTime    = 0;
    lowError.currentErrorTime      = 0;
    lowError.currentReleaseTime    = 0;
}
#endif
