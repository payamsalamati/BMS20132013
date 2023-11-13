/**
 * @file     warrantyData_config.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "warrantyData.h"
#include "warrantyData_config.h"

#include "task_cfg.h"

#include "voltageHistogram.h"
#include "temperatureHistogram.h"

#include "voltageViolationHistogram.h"
#include "currentViolationHistogram.h"

#include "batteryCurrentTemperatureHistogram.h"
#include "downscaledVoltageTemperatureHistogram.h"
#include "heatingCurrentHistogram.h"
#include "currentViolationLogHistogram.h"
#include "downscaledCurrentViolationHistogram.h"
#include "masterPcbTemperatureHistogram.h"
#include "socTemperatureHistogram.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

extern WarrantyDataNvm warrantyNVM;

const int32_t cellVoltageTempHistogramVoltageLimits[] = {
    2000,
    2500,
    3300,
    3700,
    4050,
    4100,
};

/**
 * @unit: °C
 */
const int32_t cellVoltageTempHistogramTemperatureLimits[] = {
    -20,
    -10,
    0,
    10,
    25,
    40,
    50,
    60
};

const int32_t cellVoltageExceededHistogramVoltageLimits[] = {
    2500,
    2800,
    4150,
    4200
};

/**
 * @brief duration of the exceeded voltage
 * @unit ms
 */
const int32_t cellVoltageExceededHistogramTimeLimits[] = {
    2000,
    3000,
    4000
};

const int32_t batteryCurrentHistogramDirectionsLimits[] = {
    1
};

/**
 * @unit: mA
 */
const int32_t batteryCurrentHistogramCurrentLimits[] = {
    -290000,
    -180000,
    -100000,
    -50000,
    50000,
    100000,
    180000,
    290000
};


/**
 * @unit: °C
 */
const int32_t batteryCurrentHistogramTemperatureLimits[] = {
    -30,
    -20,
    -10,
    0,
    25,
    40,
    50,
    60
};


/**
 * @brief: Cell Voltage Temperature Histogram
 */


#if WARRANTY_DATA_CELL_VOLTAGE_TEMP_HISTOGRAM_ENABLED == CONFIG_ENABLED


// DO NOT CHANGE
const uint8_t lengthsHistogramCellVoltageTemp[] = {
    (sizeof(cellVoltageTempHistogramVoltageLimits) / sizeof(int32_t)) + 1U,
    (sizeof(cellVoltageTempHistogramTemperatureLimits) / sizeof(int32_t)) + 1U
};

const int32_t length_of_countershistogramCellVoltageTemp = ((sizeof(cellVoltageTempHistogramVoltageLimits) / sizeof(int32_t)) + 1U) * ((sizeof(cellVoltageTempHistogramTemperatureLimits) / sizeof(int32_t)) + 1U);


// Size in bytes!
// cppcheck-suppress misra-c2012-5.5 ; cppcheck issue
const uint16_t WARRANTY_DATA_VOLTAGE_TEMP_SIZE = sizeof(warrantyNVM.countershistogramCellVoltageTemp);


#endif

/**
 * @brief: Cell Voltage Exceeded Histogram
 */
#if WARRANTY_DATA_CELL_VOLTAGE_EXCEEDED_HISTOGRAM_ENABLED == CONFIG_ENABLED


const int32_t length_of_cellVoltageExceededHistogramVoltageLimits = ((sizeof(cellVoltageExceededHistogramVoltageLimits) / sizeof(int32_t)) + 1U) * ((sizeof(cellVoltageExceededHistogramTimeLimits) / sizeof(int32_t)) + 1U);
// DO NOT CHANGE
const uint8_t lengthsHistogramCellVoltageExceeded[] = {
    (sizeof(cellVoltageExceededHistogramVoltageLimits) / sizeof(int32_t)) + 1U,
    (sizeof(cellVoltageExceededHistogramTimeLimits) / sizeof(int32_t)) + 1U,
};


// Size in bytes!
// cppcheck-suppress misra-c2012-5.5 ; cppcheck issue
const uint16_t WARRANTY_DATA_CELL_VOLTAGE_EXCEEDED_SIZE = sizeof(warrantyNVM.countershistogramCellVoltageExceeded);

#endif

/**
 * @brief: Battery Current Histogram
 */
#if WARRANTY_DATA_BATTERY_CURRENT_HISTOGRAM_ENABLED == CONFIG_ENABLED


// DO NOT CHANGE AFTER THIS
const uint8_t lengthsHistogramBatteryCurrent[] = {
    (sizeof(batteryCurrentHistogramDirectionsLimits) / sizeof(int32_t)) + 1U,
    (sizeof(batteryCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U,
    (sizeof(batteryCurrentHistogramTemperatureLimits) / sizeof(int32_t)) + 1U
};
const int32_t length_of_countershistogramBatteryCurrent = ((sizeof(batteryCurrentHistogramDirectionsLimits) / sizeof(int32_t)) + 1U)
                                                          * ((sizeof(batteryCurrentHistogramCurrentLimits) / sizeof(int32_t)) + 1U)
                                                          * ((sizeof(batteryCurrentHistogramTemperatureLimits) / sizeof(int32_t)) + 1U);

// Size in bytes!
// cppcheck-suppress misra-c2012-5.5 ; cppcheck issue
const uint16_t WARRANTY_DATA_BATTERY_CURRENT_SIZE = sizeof(warrantyNVM.countershistogramBatteryCurrent);
#endif


// this raises a warning :(
//_Static_assert(NVM_WARRANTY_DATA_SECTION_END < NVM_UDS_SECTION_START, "NVM_WARRANTY_DATA_SECTION too big");


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void warrantyData_projectSpecificHistograms_init(void)
{
    voltageHistogram_init();
    temperatureHistogram_init();

    voltageViolationHistogram_init();
    currentViolationHistogram_init();

    batteryCurrentTemperatureHistogram_init();
    downscaledVoltageTemperatureHistogram_init();

    // TODO MPU Verletzung (Issue: https://gitlab.futavis.de/futavis/software/futavis-bms/cbbms/-/issues/472)
    // downscaledCurrentViolationHistogram_init();
}

void warrantyData_projectSpecificHistograms_mainFunction(void)
{
    voltageHistogram_mainFunction();
    temperatureHistogram_mainFunction();

    voltageViolationHistogram_mainFunction();
    currentViolationHistogram_mainFunction();

    batteryCurrentTemperatureHistogram_mainFunction();
    downscaledVoltageTemperatureHistogram_mainFunction();
    heatingCurrentHistogram_mainFunction();
    currentViolationLogHistogram_mainFunction();
    masterPcbTemperatureHistogram_mainFunction();
    socTemperatureHistogram_mainFunction();
}
