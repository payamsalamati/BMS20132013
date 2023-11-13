/**
 * @file    : hwVersion_config.h
 * @copyright (c) Futavis GmbH, Aachen 2018 - alle Rechte vorbehalten
 * @brief   :
 */

#pragma once

#include "config_enable.h"


/**
 * @brief
 */

#define HARDWAREVERSION_1v0 1u
#define HARDWAREVERSION_1v3 2u
#define HARDWAREVERSION_1v4 3u
#define HARDWAREVERSION_1v5 4u

#define USED_HARDWARE_VERSION HARDWAREVERSION_1v5

#define HW_VERSION_MIN_HARDWARE_VERSION 1
#define HW_VERSION_MAX_HARDWARE_VERSION 24

/**
 * @brief defines the number of hardware versions of the project
 */
#define HW_VERSION_EXISTING_NUMBERS 4  //

#define USE_FIX_HARDWARE_CONFIGURATION CONFIG_ENABLED

#define HW_VERSION_CONST_VOLTAG_DIFF_START_VOLTAGE 3000   // mV
#define HW_VERSION_CONST_VOLTAG_DIFF_VOLTAGE_DIFF  200.0  // mV

#define HWVERSION_NUMBER_OF_MEASUREMENTS 9u
