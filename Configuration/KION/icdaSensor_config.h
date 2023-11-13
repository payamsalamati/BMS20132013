/**
 * @file icdaSensor_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


#pragma once
//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include "icdaSensor.h"
#include "canId_config.h"
#include "config_enable.h"
#include CAN_INTERNAL_HEADER

extern ICDASensor_Config icdaSensorConfig;
//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

/************/

#define ICDA_MAX_INIT_ERROR_COUNTER 3u  // @req CB-10245

#if defined(HIL_CONFIGURATION)
// give more time for HIL because battery simulation cycle time is 360ms and it needs to detect the IO low state
#define ICDA_SUPPLY_VOLTAGE_RESTART_IO_LOW_CYCLES  6u
#define ICDA_SUPPLY_VOLTAGE_RESTART_TIMEOUT_CYCLES 9u
#else
// @req CB-92045
#define ICDA_SUPPLY_VOLTAGE_RESTART_IO_LOW_CYCLES  3u  // number of cycles in which voltage supply to ICDA should be turned off during hard reset (=300ms with 100ms cycle time)
#define ICDA_SUPPLY_VOLTAGE_RESTART_TIMEOUT_CYCLES 6u  // number of cycles that the total duration of hard reset can max. take (=600ms with 100ms cycle time)
#endif

#define ICDA_MAIN_FUNCTION_CYCLE_TIME_IN_MS 100u
// @req CB-94155
#define ICDA_DEFAULT_STARTUP_MESSAGE_TIMEOUT_IN_MS 1000u  // max. time to wait for startup message from ICDA after power on

#define ICDA_MAX_CYCLE_TIME             100u
#define ICDA_MAX_MISSING_RESPONSES      5u
#define ICDA_MAX_SHUTDOWN_ERROR_COUNTER 10u


// @req CB-10268
/************/
#define ICDA_CLEAR_STATUS_ERROR_REPEAT_TIME 2000u  // CB-10268: "If the error does not disappear the BMS shall repeat the request after 2000ms."
#define ICDA_MAX_CLEAR_STATUS_ERROR_COUNTER 3u     // CB-10268: "The BMS shall not try to clear the status more than 3 times for each newly reported fault."
/************/

// @req CB-10277
/************/
#define ICDA_WAKEUP_SOURCE    0b00000001u  // <Wakeup source as bitfield> = 0x01 (timer)
#define ICDA_WAKEUP_THRESHOLD 65000u       // <Timer value [1s]> = 65000
/************/

#define ICDA_MAX_RC_ERROR_COUNTER 5u

#define ICDA_OPERATION_MODE              (uint8_t)0x01u   // 0x00 = stop, 0x01 = continuous, 0x02 = triggered
#define ICDA_OPERATION_OUTPUT_RATE_IN_MS (uint16_t)0x05u  // max value = uint16_t

// Default config parameter
// @req CB-10263 https://polarion.futavis.de/polarion/#/project/CB_BMS/workitem?id=CB-10263
#define ICDA_OPERATION_DEFAULT_CURRENT_DIRECTION (uint8_t)0x01u  // 0x01 = invert current, 0x00 = non-inverted current
#define ICDA_OPERATION_DEFAULT_AVARAGE           (uint8_t)0x01u  // 0x01
#define ICDA_OPERATION_DEFAULT_CH_CURRENT        (uint32_t)300u  // [A]
#define ICDA_OPERATION_DEFAULT_DCH_CURRENT       (uint32_t)300u  // [A]

// @req CB-10297
#define ICDA_ERROR_STATUS_OCS_IGNORED CONFIG_ENABLED

#define ICDA_CURRENT_SENSOR_ACTIVATED 5u
#define ICDA_CURRENT_SENSOR_DISABLED  0u
// @req CB-10263 CB-93246
#define ICDA_DEFAULT_PARAM_CURRENT_SENSOR_CONFIG ICDA_CURRENT_SENSOR_ACTIVATED

#define ICDA_GLOBAL_USAGE icdaSensorConfig.PARAM_Current_Sensor_Config

#define ICDA_CAN_NODE_HANDLER kioninterCANTransmitBMS_ICDA_RequestHandler
//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//

#define ICDA_SEND_REQUEST_MSG(x) kioninterCAN_sendBMS_ICDA_Request(x)

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
