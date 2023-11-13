/**
 * @file cellVoltageMonitor.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Checks all plausible cell voltage values against the warning, alert and error limits.
 * @details
 *   Interfaces to other modules:
 *   - cellVoltageMeasurement
 *   - errorDetection
 *   - dem
 *
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef struct
{
    int32_t voltageWarningMaxDetectVal;
    uint32_t voltageWarningMaxDetectTime;
    int32_t voltageWarningMaxReleaseVal;
    uint32_t voltageWarningMaxReleaseTime;
    int32_t voltageAlertMaxDetectVal;
    uint32_t voltageAlertMaxDetectTime;
    int32_t voltageAlertMaxReleaseVal;
    uint32_t voltageAlertMaxReleaseTime;
    int32_t voltageErrorMaxDetectVal;
    uint32_t voltageErrorMaxDetectTime;
    int32_t voltageErrorMaxReleaseVal;
    uint32_t voltageErrorMaxReleaseTime;
    int32_t voltageWarningMinDetectVal;
    uint32_t voltageWarningMinDetectTime;
    int32_t voltageWarningMinReleaseVal;
    uint32_t voltageWarningMinReleaseTime;
    int32_t voltageAlertMinDetectVal;
    uint32_t voltageAlertMinDetectTime;
    int32_t voltageAlertMinReleaseVal;
    uint32_t voltageAlertMinReleaseTime;
    int32_t voltageErrorMinDetectVal;
    uint32_t voltageErrorMinDetectTime;
    int32_t voltageErrorMinReleaseVal;
    uint32_t voltageErrorMinReleaseTime;
    int32_t voltageDeepDischargeDetectVal;
    int32_t voltageDeepDischargeReleaseVal;
} CellVoltageMonitorConfig;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

/**
 * @brief Main function of the module.
 * @details This function checks all plausible cell voltage values against the warning, alert and error limits.
 * ##Requirements:
 * **Requirement**     |**Description**
 * :------------------:|:-----------------
 * **CelVolMon_00010** |The function shall get the master ID by calling the function idAllocation_getMasterId.
 * **CelVolMon_00011** |The function shall get the maximum cell voltage value by calling the function
 *            ^        |cellVoltageMeasurement_getMaxValue with the master ID.
 * **CelVolMon_00012** |The function shall get the minimum cell voltage value by calling the function
 *            ^        |cellVoltageMeasurement_getMinValue with the master ID.
 * **CelVolMon_00013** |The function shall detect the correct error by calling the function errorDetection
 *            ^        |with the minimum and maximum cell voltage, the configuration variable MONITORING_CYCLE_TIME
 *            ^        |and all possible warning, alert and error configurations.
 */
void cellVoltageMonitor_mainFunction(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_WARN_DETECT_VAL
 * @return int32_t CELL_VOLTAGE_MAX_WARN_DETECT_VAL
 */
int32_t cellVoltageMonitor_getMaxWarnDetectVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_WARN_DETECT_TIME
 * @return uint32_t CELL_VOLTAGE_MAX_WARN_DETECT_TIME
 */
uint32_t cellVoltageMonitor_getMaxWarnDetectTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_WARN_RELEASE_VAL
 * @return int32_t CELL_VOLTAGE_MAX_WARN_RELEASE_VAL
 */
int32_t cellVoltageMonitor_getMaxWarnReleaseVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_WARN_RELEASE_TIME
 * @return uint32_t CELL_VOLTAGE_MAX_WARN_RELEASE_TIME
 */
uint32_t cellVoltageMonitor_getMaxWarnReleaseTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_ALERT_DETECT_VAL
 * @return int32_t CELL_VOLTAGE_MAX_ALERT_DETECT_VAL
 */
int32_t cellVoltageMonitor_getMaxAlertDetectVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_ALERT_DETECT_TIME
 * @return uint32_t CELL_VOLTAGE_MAX_ALERT_DETECT_TIME
 */
uint32_t cellVoltageMonitor_getMaxAlertDetectTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_ALERT_RELEASE_VAL
 * @return int32_t CELL_VOLTAGE_MAX_ALERT_RELEASE_VAL
 */
int32_t cellVoltageMonitor_getMaxAlertReleaseVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_ALERT_RELEASE_TIME
 * @return uint32_t CELL_VOLTAGE_MAX_ALERT_RELEASE_TIME
 */
uint32_t cellVoltageMonitor_getMaxAlertReleaseTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_ERR_DETECT_VAL
 * @return int32_t CELL_VOLTAGE_MAX_ERR_DETECT_VAL
 */
int32_t cellVoltageMonitor_getMaxErrDetectVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_ERR_DETECT_TIME
 * @return uint32_t CELL_VOLTAGE_MAX_ERR_DETECT_TIME
 */
uint32_t cellVoltageMonitor_getMaxErrDetectTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_ERR_RELEASE_VAL
 * @return int32_t CELL_VOLTAGE_MAX_ERR_RELEASE_VAL
 */
int32_t cellVoltageMonitor_getMaxErrReleaseVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MAX_ERR_RELEASE_TIME
 * @return uint32_t CELL_VOLTAGE_MAX_ERR_RELEASE_TIME
 */
uint32_t cellVoltageMonitor_getMaxErrReleaseTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_WARN_DETECT_VAL
 * @return int32_t CELL_VOLTAGE_MIN_WARN_DETECT_VAL
 */
int32_t cellVoltageMonitor_getMinWarnDetectVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_WARN_DETECT_TIME
 * @return uint32_t CELL_VOLTAGE_MIN_WARN_DETECT_TIME
 */
uint32_t cellVoltageMonitor_getMinWarnDetectTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_WARN_RELEASE_VAL
 * @return int32_t CELL_VOLTAGE_MIN_WARN_RELEASE_VAL
 */
int32_t cellVoltageMonitor_getMinWarnReleaseVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_WARN_RELEASE_TIME
 * @return uint32_t CELL_VOLTAGE_MIN_WARN_RELEASE_TIME
 */
uint32_t cellVoltageMonitor_getMinWarnReleaseTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_ALERT_DETECT_VAL
 * @return int32_t CELL_VOLTAGE_MIN_ALERT_DETECT_VAL
 */
int32_t cellVoltageMonitor_getMinAlertDetectVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_ALERT_DETECT_TIME
 * @return uint32_t CELL_VOLTAGE_MIN_ALERT_DETECT_TIME
 */
uint32_t cellVoltageMonitor_getMinAlertDetectTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_ALERT_RELEASE_VAL
 * @return int32_t CELL_VOLTAGE_MIN_ALERT_RELEASE_VAL
 */
int32_t cellVoltageMonitor_getMinAlertReleaseVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_ALERT_RELEASE_TIME
 * @return uint32_t CELL_VOLTAGE_MIN_ALERT_RELEASE_TIME
 */
uint32_t cellVoltageMonitor_getMinAlertReleaseTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_ERR_DETECT_VAL
 * @return int32_t CELL_VOLTAGE_MIN_ERR_DETECT_VAL
 */
int32_t cellVoltageMonitor_getMinErrDetectVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_ERR_DETECT_TIME
 * @return uint32_t CELL_VOLTAGE_MIN_ERR_DETECT_TIME
 */
uint32_t cellVoltageMonitor_getMinErrDetectTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_ERR_RELEASE_VAL
 * @return int32_t CELL_VOLTAGE_MIN_ERR_RELEASE_VAL
 */
int32_t cellVoltageMonitor_getMinErrReleaseVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_MIN_ERR_RELEASE_TIME
 * @return uint32_t CELL_VOLTAGE_MIN_ERR_RELEASE_TIME
 */
uint32_t cellVoltageMonitor_getMinErrReleaseTime(void);

/**
 * @brief Getter for CELL_VOLTAGE_DEEP_DISCHARGE_DETECT_VAL
 * @return uint32_t CELL_VOLTAGE_DEEP_DISCHARGE_DETECT_VAL
 */
int32_t cellVoltageMonitor_getDeepDischargeDetectVal(void);

/**
 * @brief Getter for CELL_VOLTAGE_DEEP_DISCHARGE_RELEASE_VAL
 * @return uint32_t CELL_VOLTAGE_DEEP_DISCHARGE_RELEASE_VAL
 */
int32_t cellVoltageMonitor_getDeepDischargeReleaseVal(void);


#if defined(UNIT_TEST)
void cellVoltageMonitor_reset(void);
#endif
