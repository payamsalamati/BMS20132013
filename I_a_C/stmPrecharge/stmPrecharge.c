/**
 * @file stmPrecharge.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "stmPrecharge.h"
#include "task_cfg.h"
#include "highVoltageMeasurement.h"

#if defined(UNIT_TEST)
#include "test_stmPrecharge_config.h"
#else
#include "stmPrecharge_config.h"
#endif

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SEC_PARAMETER StmPrechargeConfig stmPrechargeConfig = {
    .s2Precharge_Method               = STM_PRECHARGE_CONFIG_DEFAULT_S2_PRECHARGE_METHOD,
    .s2VoltageBasedPrechargeCondition = STM_PRECHARGE_CONFIG_DEFAULT_S2_PRECHARGE_VOLTAGE_BASED_RATIO,
    .s2VoltageBasedPrechargeTimeout   = STM_PRECHARGE_CONFIG_DEFAULT_S2_PRECHARGE_VOLTAGE_BASED_TIMEOUT,
    .s2TimeBasedPrechargeTime         = STM_PRECHARGE_CONFIG_DEFAULT_S2_PRECHARGE_TIME_BASED_TIME,
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

// @req CB-92399
bool stmPrecharge_isPrechargeVoltageS2Reached(void)
{
    int32_t voltageBeforeContactorS1 = highVoltageMeasurement_getMasterHvVoltagesValue(0);
    int32_t voltageAfterContactorsS1 = highVoltageMeasurement_getMasterHvVoltagesValue(1);
    // 200 -> normalizing factor for 0.5%
    return ((voltageAfterContactorsS1 * 200) > (voltageBeforeContactorS1 * STM_PRECHARGE_CONFIG_S2_PRECHARGE_VOLTAGE_BASED_RATIO));
}


bool stmPrecharge_setS2PrechargeMethod(uint8_t newValue)
{
    bool result = false;
    if((newValue == (uint8_t)PrechargeTimeBased)
       || (newValue == (uint8_t)PrechargeVoltageBased))
    {
        result                                = true;
        stmPrechargeConfig.s2Precharge_Method = (PrechargeMethod)newValue;
    }
    return result;
}

PrechargeMethod stmPrecharge_getS2PrechargeMethod(void)
{
    return stmPrechargeConfig.s2Precharge_Method;
}

bool stmPrecharge_setS2VoltageBasedPrechargeCondition(uint8_t newValue)
{
    bool result = false;
    if(newValue <= STM_PRECHARGE_CONFIG_S2_PRECHARGE_VOLTAGE_BASED_MAX_RATIO)
    {
        stmPrechargeConfig.s2VoltageBasedPrechargeCondition = newValue;
        result                                              = true;
    }
    return result;
}

uint8_t stmPrecharge_getS2VoltageBasedPrechargeCondition(void)
{
    return stmPrechargeConfig.s2VoltageBasedPrechargeCondition;
}

bool stmPrecharge_setS2VoltageBasedPrechargeTimeout(uint16_t newValue)
{
    bool result = false;
    if(newValue <= STM_PRECHARGE_CONFIG_S2_PRECHARGE_VOLTAGE_BASED_MAX_TIMEOUT)  // min value is 0, no validation required
    {
        stmPrechargeConfig.s2VoltageBasedPrechargeTimeout = newValue;
        result                                            = true;
    }
    return result;
}

uint16_t stmPrecharge_getS2VoltageBasedPrechargeTimeout(void)
{
    return stmPrechargeConfig.s2VoltageBasedPrechargeTimeout;
}

bool stmPrecharge_setS2TimeBasedPrechargeTime(uint16_t newValue)
{
    bool result = false;
    if(newValue <= STM_PRECHARGE_CONFIG_S2_PRECHARGE_TIME_BASED_MAX_TIME)  // min value is 0, no validation required
    {
        stmPrechargeConfig.s2TimeBasedPrechargeTime = newValue;
        result                                      = true;
    }
    return result;
}

uint16_t stmPrecharge_getS2TimeBasedPrechargeTime(void)
{
    return stmPrechargeConfig.s2TimeBasedPrechargeTime;
}
