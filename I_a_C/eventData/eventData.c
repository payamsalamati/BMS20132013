/**
 * @file eventData.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "eventData.h"

#include <limits.h>

#include "task_cfg.h"
#if defined(UNIT_TEST)
#include "eventData_config.h"
#include "nvm_config_id.h"
#else
#include "bms_config.h"
#endif
#include "fut_math.h"
#include "stringCurrentMeasurement.h"
#include "stateFunctions.h"
#include "highVoltageMeasurement.h"
#include "cellVoltageMeasurement.h"
#include "cellTemperatureMeasurement.h"
#include "nvm.h"
#include "debug.h"

#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
#include "alternativeMemFunctions.h"
#endif

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    int32_t highestPositiveCurrentDriveModeMaster;
    int32_t highestNegativeCurrentDriveModeMaster;
    int32_t highestPositiveCurrentChargeModeMaster;
    uint16_t highestBatteryVoltageMaster;
    uint16_t lowestBatteryVoltageMaster;
    uint16_t highestCellVoltageMaster;
    uint16_t lowestCellVoltageMaster;
    int8_t highestFuSiTemperatureMaster;
    int8_t lowestFuSiTemperatureMaster;
    uint16_t highestImbalanceCellVoltageMaster;
} EventDataNvm;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static void calculateCurrentEvents(void);
static void calculateHighVoltageEvents(void);
static void calculateCellVoltageEvents(void);
static void calculateCellTemperatureEvents(void);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_NVM EventDataNvm eventData = {
    .highestPositiveCurrentDriveModeMaster  = INT_MIN,
    .highestNegativeCurrentDriveModeMaster  = INT_MAX,
    .highestPositiveCurrentChargeModeMaster = INT_MIN,
    .highestBatteryVoltageMaster            = 0u,
    .lowestBatteryVoltageMaster             = USHRT_MAX,
    .highestCellVoltageMaster               = 0u,
    .lowestCellVoltageMaster                = USHRT_MAX,
    .highestFuSiTemperatureMaster           = SCHAR_MIN,
    .lowestFuSiTemperatureMaster            = SCHAR_MAX,
    .highestImbalanceCellVoltageMaster      = 0u,
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static void calculateCurrentEvents(void)
{
    int32_t current = stringCurrentMeasurement_getValue();
    if(stmFct_getBatteryStateGlobal() == State_Drive_Mode_Active)
    {
        eventData.highestPositiveCurrentDriveModeMaster = (current > eventData.highestPositiveCurrentDriveModeMaster) ? current : eventData.highestPositiveCurrentDriveModeMaster;
        eventData.highestNegativeCurrentDriveModeMaster = (current < eventData.highestNegativeCurrentDriveModeMaster) ? current : eventData.highestNegativeCurrentDriveModeMaster;
    }
    if(stmFct_getBatteryStateGlobal() == State_Charge_Mode_Active)
    {
        eventData.highestPositiveCurrentChargeModeMaster = (current > eventData.highestPositiveCurrentChargeModeMaster) ? current : eventData.highestPositiveCurrentChargeModeMaster;
    }
}

static void calculateHighVoltageEvents(void)
{
    // cppcheck-suppress misra-c2012-18.8 ; define is constant.
    int32_t hvVoltages[BMS_CONFIG_MAX_NUMBER_OF_HV_MEASUREMENTS];
    for(uint8_t i = 0; i < BMS_CONFIG_NUMBER_OF_HV_MEASUREMENTS; i++)
    {
        hvVoltages[i] = highVoltageMeasurement_getMasterHvVoltagesValue(i);
    }
    MaxMin_s32 hvVoltagesMaxMin = maxMin_s32(hvVoltages, BMS_CONFIG_NUMBER_OF_HV_MEASUREMENTS);

    eventData.highestBatteryVoltageMaster = (hvVoltagesMaxMin.max > eventData.highestBatteryVoltageMaster) ? hvVoltagesMaxMin.max : eventData.highestBatteryVoltageMaster;
    eventData.lowestBatteryVoltageMaster  = (hvVoltagesMaxMin.min < eventData.lowestBatteryVoltageMaster) ? hvVoltagesMaxMin.min : eventData.lowestBatteryVoltageMaster;
}

static void calculateCellVoltageEvents(void)
{
    uint16_t cellVoltageMax            = cellVoltageMeasurement_getMaxValue();
    eventData.highestCellVoltageMaster = (cellVoltageMax > eventData.highestCellVoltageMaster) ? cellVoltageMax : eventData.highestCellVoltageMaster;
    uint16_t cellVoltageMin            = cellVoltageMeasurement_getMinValue();
    eventData.lowestCellVoltageMaster  = (cellVoltageMin < eventData.lowestCellVoltageMaster) ? cellVoltageMin : eventData.lowestCellVoltageMaster;

    eventData.highestImbalanceCellVoltageMaster = ((cellVoltageMax - cellVoltageMin) > eventData.highestImbalanceCellVoltageMaster) ? (cellVoltageMax - cellVoltageMin) : eventData.highestImbalanceCellVoltageMaster;
}

static void calculateCellTemperatureEvents(void)
{
    uint16_t cellTemperatureMax            = cellTemperatureMeasurement_getMaxValue();
    eventData.highestFuSiTemperatureMaster = (cellTemperatureMax > eventData.highestFuSiTemperatureMaster) ? cellTemperatureMax : eventData.highestFuSiTemperatureMaster;
    uint16_t cellTemperatureMin            = cellTemperatureMeasurement_getMinValue();
    eventData.lowestFuSiTemperatureMaster  = (cellTemperatureMin < eventData.lowestFuSiTemperatureMaster) ? cellTemperatureMin : eventData.lowestFuSiTemperatureMaster;
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void eventData_mainFunction(void)
{
    calculateCurrentEvents();
    calculateHighVoltageEvents();
    calculateCellVoltageEvents();
    calculateCellTemperatureEvents();
}

void eventData_checkNvm(const uint8_t* mirror, uint16_t length)
{
    DEBUG_ASSERT(sizeof(EventDataNvm) == length);

    if(NVM_REQ_OK == nvm_getErrorStatus((NVM_EVENT_DATA_BLOCK_ID)))
    {
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
        alternativeMemFunctions_memcpy(&eventData, mirror, sizeof(EventDataNvm));
#else
        memcpy(&eventData, mirror, sizeof(EventDataNvm));
#endif
    }
}

void eventData_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
    alternativeMemFunctions_memcpy(mirror, (uint8_t*)&eventData, sizeof(EventDataNvm));
#else
    memcpy(mirror, (uint8_t*)&eventData, sizeof(EventDataNvm));
#endif
}

void eventData_resetEventData(void)
{
    eventData.highestPositiveCurrentDriveModeMaster  = INT_MIN;
    eventData.highestNegativeCurrentDriveModeMaster  = INT_MAX;
    eventData.highestPositiveCurrentChargeModeMaster = INT_MIN;
    eventData.highestBatteryVoltageMaster            = 0u;
    eventData.lowestBatteryVoltageMaster             = USHRT_MAX;
    eventData.highestCellVoltageMaster               = 0u;
    eventData.lowestCellVoltageMaster                = USHRT_MAX;
    eventData.highestFuSiTemperatureMaster           = SCHAR_MIN;
    eventData.lowestFuSiTemperatureMaster            = SCHAR_MAX;
    eventData.highestImbalanceCellVoltageMaster      = 0u;
}

int32_t eventData_getHighestPositiveCurrentDriveModeMaster(void)
{
    return eventData.highestPositiveCurrentDriveModeMaster;
}

int32_t eventData_getHighestNegativeCurrentDriveModeMaster(void)
{
    return eventData.highestNegativeCurrentDriveModeMaster;
}

int32_t eventData_getHighestPositiveCurrentChargeModeMaster(void)
{
    return eventData.highestPositiveCurrentChargeModeMaster;
}

uint16_t eventData_getHighestBatteryVoltageMaster(void)
{
    return eventData.highestBatteryVoltageMaster;
}

uint16_t eventData_getLowestBatteryVoltageMaster(void)
{
    return eventData.lowestBatteryVoltageMaster;
}

uint16_t eventData_getHighestCellVoltageMaster(void)
{
    return eventData.highestCellVoltageMaster;
}

uint16_t eventData_getLowestCellVoltageMaster(void)
{
    return eventData.lowestCellVoltageMaster;
}

int8_t eventData_getHighestFuSiTemperatureMaster(void)
{
    return eventData.highestFuSiTemperatureMaster;
}

int8_t eventData_getLowestFuSiTemperatureMaster(void)
{
    return eventData.lowestFuSiTemperatureMaster;
}

uint16_t eventData_getHighestImbalanceCellVoltageMaster(void)
{
    return eventData.highestImbalanceCellVoltageMaster;
}
