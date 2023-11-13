/**
 * @file     voltageMonitor_config_default.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Configuration for voltage monitoring
 * @details
 *	 Interfaces to other modules:

 */

#pragma once

#include "cellVoltageMonitor.h"

//***************************************************************************/
//*************************** DEFINES ***************************************/
//***************************************************************************/

#define DEFAULT_TIME 0u

extern CellVoltageMonitorConfig voltageMonitorConfigParameter;

// times are basically disabled and Timing from DEM Module is used
#define CELL_VOLTAGE_DEFAULT_MAX_WARN_DETECT_TIME   DEFAULT_TIME
#define CELL_VOLTAGE_DEFAULT_MIN_WARN_DETECT_TIME   DEFAULT_TIME
#define CELL_VOLTAGE_DEFAULT_MAX_WARN_RELEASE_TIME  DEFAULT_TIME
#define CELL_VOLTAGE_DEFAULT_MIN_WARN_RELEASE_TIME  DEFAULT_TIME
#define CELL_VOLTAGE_DEFAULT_MAX_ALERT_DETECT_TIME  DEFAULT_TIME
#define CELL_VOLTAGE_DEFAULT_MAX_ALERT_RELEASE_TIME DEFAULT_TIME
#define CELL_VOLTAGE_DEFAULT_MIN_ALERT_DETECT_TIME  DEFAULT_TIME
#define CELL_VOLTAGE_DEFAULT_MIN_ALERT_RELEASE_TIME DEFAULT_TIME
#define CELL_VOLTAGE_DEFAULT_MAX_ERR_DETECT_TIME    DEFAULT_TIME
#define CELL_VOLTAGE_DEFAULT_MAX_ERR_RELEASE_TIME   DEFAULT_TIME
#define CELL_VOLTAGE_DEFAULT_MIN_ERR_DETECT_TIME    DEFAULT_TIME
#define CELL_VOLTAGE_DEFAULT_MIN_ERR_RELEASE_TIME   DEFAULT_TIME


// release is alwys same value as detect
#define CELL_VOLTAGE_DEFAULT_MAX_WARN_RELEASE_VAL  CELL_VOLTAGE_DEFAULT_MAX_WARN_DETECT_VAL
#define CELL_VOLTAGE_DEFAULT_MIN_WARN_RELEASE_VAL  CELL_VOLTAGE_DEFAULT_MIN_WARN_DETECT_VAL
#define CELL_VOLTAGE_DEFAULT_MAX_ALERT_RELEASE_VAL CELL_VOLTAGE_DEFAULT_MAX_ALERT_DETECT_VAL
#define CELL_VOLTAGE_DEFAULT_MIN_ALERT_RELEASE_VAL CELL_VOLTAGE_DEFAULT_MIN_ALERT_DETECT_VAL
#define CELL_VOLTAGE_DEFAULT_MIN_ERR_RELEASE_VAL   CELL_VOLTAGE_DEFAULT_MIN_ERR_DETECT_VAL
#define CELL_VOLTAGE_DEFAULT_MAX_ERR_RELEASE_VAL   CELL_VOLTAGE_DEFAULT_MAX_ERR_DETECT_VAL

// *************************************************************************************************** /
// ************************* MAX Values ************************************************************** /
// *************************************************************************************************** /

// @req CB-19047
#define CELL_VOLTAGE_DEFAULT_MAX_WARN_DETECT_VAL 3800

// @req CB-19045
#define CELL_VOLTAGE_DEFAULT_MAX_ALERT_DETECT_VAL 3900

// @req CB-19042
#define CELL_VOLTAGE_DEFAULT_MAX_ERR_DETECT_VAL 4000

// *************************************************************************************************** /
// ************************* MIN Values ************************************************************** /
// *************************************************************************************************** /

// @req CB-19046
#define CELL_VOLTAGE_DEFAULT_MIN_WARN_DETECT_VAL 2400

// @req CB-19044
#define CELL_VOLTAGE_DEFAULT_MIN_ALERT_DETECT_VAL 2200

// @req CB-19043
#define CELL_VOLTAGE_DEFAULT_MIN_ERR_DETECT_VAL 1800


#define CELL_VOLTAGE_MIN_ERR_DETECT_VAL voltageMonitorConfigParameter.voltageErrorMinDetectVal
#define CELL_VOLTAGE_MAX_ERR_DETECT_VAL voltageMonitorConfigParameter.voltageErrorMaxDetectVal


// *************************************************************************************************** /
// ************************* DEEP_DISCHARGE ************************************************************** /
// *************************************************************************************************** /

#define CELL_VOLTAGE_DEFAULT_DEEP_DISCHARGE_DETECT_VAL  2000
#define CELL_VOLTAGE_DEFAULT_DEEP_DISCHARGE_RELEASE_VAL 2000
