

/**
 * @file periodicWakeUp.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "periodicWakeUp.h"

#include <stdbool.h>

#include "task_cfg.h"
#include "measurements_getOnBoardTemperature.h"
#include "nvm.h"
#if defined(UNIT_TEST)
#include "test/nvm_config_id.h"
#else
#include "nvm_config_id.h"
#endif
#include "debug.h"
#include "timestamp.h"

#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
#include "alternativeMemFunctions.h"
#endif

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//
typedef struct
{
    bool resetWakeUpCounter;
    /*  time to next wake up in s*/
    uint32_t timeToWakeUp;
} PeriodicWakeUp;

typedef struct
{
    uint16_t wakeUpCounter;
    uint8_t reserve[14];
} PeriodicWakeUpNvm;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static void calculateNextSbcSleepTime(void);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

extern PeriodicWakeUpConfig periodicWakeUpConfig;

MEM_APPLICATION PeriodicWakeUpNvm periodicWakeUpNVM = {
    .wakeUpCounter = 0
};

MEM_APPLICATION PeriodicWakeUp periodicWakeUpData = {
    .resetWakeUpCounter = false,
    .timeToWakeUp       = 0
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static void calculateNextSbcSleepTime(void)
{
    if(periodicWakeUpNVM.wakeUpCounter <= periodicWakeUpConfig.maxNumberOfFastWakeUps)
    {
        periodicWakeUpData.timeToWakeUp = periodicWakeUpConfig.shortInterval;
    }
    else if(measurements_getOnBoardTemperature_getTSensorOnMaster() > periodicWakeUpConfig.temperatureThreshold)
    {
        periodicWakeUpData.timeToWakeUp = periodicWakeUpConfig.middleInterval;
    }
    else
    {
        periodicWakeUpData.timeToWakeUp = periodicWakeUpConfig.longInterval;
    }
    timestamp_setNextSleepInterval(periodicWakeUpData.timeToWakeUp);
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

void periodicWakeUp_init(void)
{
    nvm_readBlock(NVM_PERIODIC_WAKE_UP_BLOCK_ID, NULL);
}

void periodicWakeUp_incrementWakeUpCounter(void)
{
    // this can only overflow for maxNumberOfFastWakeups == UINT32_MAX,
    // in which case the function should always use short interval,
    // which would also happen in case of overflow
    if(periodicWakeUpNVM.wakeUpCounter <= periodicWakeUpConfig.maxNumberOfFastWakeUps)
    {
        periodicWakeUpNVM.wakeUpCounter++;
    }
    calculateNextSbcSleepTime();
}

void periodicWakeUp_resetWakeUpCounter(void)
{
    periodicWakeUpData.resetWakeUpCounter = true;
    periodicWakeUpNVM.wakeUpCounter       = 0;
    calculateNextSbcSleepTime();
}

uint32_t periodicWakeUp_getTimeToWakeUp(void)
{
    return periodicWakeUpData.timeToWakeUp;
}

void periodicWakeUp_checkNvm(const uint8_t* mirror, uint16_t length)
{
    DEBUG_ASSERT(sizeof(PeriodicWakeUpNvm) == length);
    if((nvm_getErrorStatus(NVM_PERIODIC_WAKE_UP_BLOCK_ID) != NVM_REQ_OK)
       || (periodicWakeUpData.resetWakeUpCounter == true))
    {
        periodicWakeUpNVM.wakeUpCounter = 0;
        calculateNextSbcSleepTime();
    }
    else if(periodicWakeUpNVM.wakeUpCounter <= periodicWakeUpConfig.maxNumberOfFastWakeUps)
    {
        // wakeUpcounter should at most be 1 here
        DEBUG_ASSERT((periodicWakeUpNVM.wakeUpCounter == 0) || (periodicWakeUpNVM.wakeUpCounter == 1));
        // cppcheck-suppress misra-c2012-11.3 ; safe since length is checked
        const PeriodicWakeUpNvm* periodicWakeUpMirror = (const PeriodicWakeUpNvm*)mirror;
        periodicWakeUpNVM.wakeUpCounter += periodicWakeUpMirror->wakeUpCounter;
    }
    else
    {
        // misra required
    }
    calculateNextSbcSleepTime();
}

void periodicWakeUp_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
    alternativeMemFunctions_memcpy(mirror, (uint8_t*)&periodicWakeUpNVM, sizeof(periodicWakeUpNVM));
#else
    memcpy(mirror, (uint8_t*)&periodicWakeUpNVM, sizeof(periodicWakeUpNVM));
#endif
}

uint16_t periodicWakeUp_getWakeUpCounter(void)
{
    return periodicWakeUpNVM.wakeUpCounter;
}

uint32_t periodicWakeUp_getMaxNumberOfFastWakeUps(void)
{
    return periodicWakeUpConfig.maxNumberOfFastWakeUps;
}

int8_t periodicWakeUp_getTemperatureThreshold(void)
{
    return periodicWakeUpConfig.temperatureThreshold;
}

uint32_t periodicWakeUp_getShortInterval(void)
{
    return periodicWakeUpConfig.shortInterval;
}

uint32_t periodicWakeUp_getMiddleInterval(void)
{
    return periodicWakeUpConfig.middleInterval;
}

uint32_t periodicWakeUp_getLongInterval(void)
{
    return periodicWakeUpConfig.longInterval;
}

void periodicWakeUp_setMaxNumberOfFastWakeUps(uint32_t newValue)
{
    periodicWakeUpConfig.maxNumberOfFastWakeUps = newValue;
}

void periodicWakeUp_setTemperatureThreshold(int8_t newValue)
{
    periodicWakeUpConfig.temperatureThreshold = newValue;
}

void periodicWakeUp_setShortInterval(uint32_t newValue)
{
    periodicWakeUpConfig.shortInterval = newValue;
}

void periodicWakeUp_setMiddleInterval(uint32_t newValue)
{
    periodicWakeUpConfig.middleInterval = newValue;
}

void periodicWakeUp_setLongInterval(uint32_t newValue)
{
    periodicWakeUpConfig.longInterval = newValue;
}
