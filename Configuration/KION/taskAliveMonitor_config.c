/**
 * @file taskAliveMonitor_config.c
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
#include "taskAliveMonitor.h"
#include "task_cfg.h"
#include "debug.h"
#include "signalWatchdog.h"
#include "kionCAN.h"
//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

extern SignalWatchdog cycleTimeLimitcheck10;
extern SignalWatchdog cycleTimeLimitcheck100;
extern SignalWatchdog cycleTimeLimitcheck1000;
extern SignalWatchdog cycleTimeWarrantyData;
extern SignalWatchdog cycleTimeCANReceive;
extern SignalWatchdog cycleTimeCANSend;
extern SignalWatchdog cycleTimeTaskMonitor;
extern SignalWatchdog cycleTimeAFE;
extern SignalWatchdog cycleTimeSafety;
extern SignalWatchdog cycleTimeIO;
extern SignalWatchdog cycleTimeNvm;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//
const TaskAliveMonitor_ConfigTable taskAliveMonitorDataConfig[] = {
    //  Id                          minCycletime    maxCycletime    cycleTimeBuffer
    {
        TASK_LIMITCHECK10_PRIO,
        0,
        20,
        &cycleTimeLimitcheck10,
        { "LIMITCHECK10ms" },
    },
    {
        TASK_LIMITCHECK100_PRIO,
        0,
        200,
        &cycleTimeLimitcheck100,
        { "LIMITCHECK100ms" },
    },
    {
        TASK_LIMITCHECK1000_PRIO,
        0,
        2000,
        &cycleTimeLimitcheck1000,
        { "LIMITCHECK1000ms" },
    },
    {
        TASK_CANRECEIVE_PRIO,
        0,
        1100,
        &cycleTimeCANReceive,
        { "CANRECEIVE" },
    },
    {
        TASK_CANSEND_PRIO,
        0,
        200,
        &cycleTimeCANSend,
        { "CANSEND" },
    },
    {
        TASK_AFE_PRIO,
        0,
        600,
        &cycleTimeAFE,
        { "AFE" },
    },
    {
        TASK_SAFETY_PRIO,
        0,
        500,
        &cycleTimeSafety,
        { "SAFETY" },
    },
    {
        TASK_IO_PRIO,
        0,
        1000,
        &cycleTimeIO,
        { "IO" },
    },
    {
        TASK_NVM_PRIO,
        0,
        24000,
        &cycleTimeNvm,
        { "NVM" },
    },
};


const uint8_t TASK_ALIVE_MONITOR_DATA_SIZE = (sizeof(taskAliveMonitorDataConfig) / sizeof(TaskAliveMonitor_ConfigTable));


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
void taskAliveMonitor_taskNotAliveHook(uint16_t taskId)
{
#if defined(SW_RESET_ANALYSIS_CAN_DATA)
    kionCAN_sendTaskCurrentTimes();
    kionCAN_sendTaskMaxTimes();
#endif
}

void taskAliveMonitor_sbcDebugHook(uint8_t watchdogStatus, uint8_t idCounter)
{
#if defined(SW_RESET_ANALYSIS_CAN_DATA)
    kionCAN_sendSBCStatus(watchdogStatus, idCounter);
#endif
}
