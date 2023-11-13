/**
 * @file     temperatureMonitor_config_default.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Configuration for temperature monitoring
 * @details
 *	 Interfaces to other modules:

 */

#pragma once


//***************************************************************************/
//*************************** DEFINES ***************************************/
//***************************************************************************/
#define CELL_TEMP_DEFAULT_MAX_WARN_DETECT_TIME   0u
#define CELL_TEMP_DEFAULT_MIN_WARN_DETECT_TIME   0u
#define CELL_TEMP_DEFAULT_MIN_WARN_RELEASE_TIME  0u
#define CELL_TEMP_DEFAULT_MAX_ALERT_DETECT_TIME  0u
#define CELL_TEMP_DEFAULT_MAX_ALERT_RELEASE_TIME 0u
#define CELL_TEMP_DEFAULT_MIN_ALERT_DETECT_TIME  0u
#define CELL_TEMP_DEFAULT_MIN_ALERT_RELEASE_TIME 0u
#define CELL_TEMP_DEFAULT_MAX_ERR_DETECT_TIME    0u
#define CELL_TEMP_DEFAULT_MAX_ERR_RELEASE_TIME   0u
#define CELL_TEMP_DEFAULT_MIN_ERR_DETECT_TIME    0u
#define CELL_TEMP_DEFAULT_MIN_ERR_RELEASE_TIME   0u
#define CELL_TEMP_DEFAULT_MAX_WARN_RELEASE_TIME  0u

#define CELL_TEMP_DEFAULT_MAX_WARN_RELEASE_VAL  CELL_TEMP_DEFAULT_MAX_WARN_DETECT_VAL
#define CELL_TEMP_DEFAULT_MAX_ALERT_RELEASE_VAL CELL_TEMP_DEFAULT_MAX_ALERT_DETECT_VAL
#define CELL_TEMP_DEFAULT_MAX_ERR_RELEASE_VAL   CELL_TEMP_DEFAULT_MAX_ERR_DETECT_VAL
#define CELL_TEMP_DEFAULT_MIN_ERR_RELEASE_VAL   CELL_TEMP_DEFAULT_MIN_ERR_DETECT_VAL
#define CELL_TEMP_DEFAULT_MIN_ALERT_RELEASE_VAL CELL_TEMP_DEFAULT_MIN_ALERT_DETECT_VAL
#define CELL_TEMP_DEFAULT_MIN_WARN_RELEASE_VAL  CELL_TEMP_DEFAULT_MIN_WARN_DETECT_VAL


// *************************************************************************************************** /
// ************************* MAX VALUES ************************************************ /
// *************************************************************************************************** /

// @req CB-19052
#define CELL_TEMP_DEFAULT_MAX_WARN_DETECT_VAL 50

// @req CB-19051
#define CELL_TEMP_DEFAULT_MAX_ALERT_DETECT_VAL 55

// @req CB-19053
#define CELL_TEMP_DEFAULT_MAX_ERR_DETECT_VAL 60

// *************************************************************************************************** /
// ************************* MIN VALUES ************************************************ /
// *************************************************************************************************** /

// @req CB-19048
#define CELL_TEMP_DEFAULT_MIN_WARN_DETECT_VAL -10

// @req CB-19049
#define CELL_TEMP_DEFAULT_MIN_ALERT_DETECT_VAL -15

// @req CB-19050
#define CELL_TEMP_DEFAULT_MIN_ERR_DETECT_VAL -20
