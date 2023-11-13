/**
 * @file     uds_readTable.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Manually added UDS read by identifier messages.
 * @details
 * To add a new UDS message, first choose a high byte ID according to the message subject.
 * If a table for that high byte ID exists, DCFunction Entry to it and increase the counter
 * in udsFunctionTables_manual for that table.
 * otherwise create a new table of the format "static DCFunction table_hbXXX[]" where XXX is
 * the High Byte ID in Decimals. Also add this to the udsFunctionTables_manual array. Also
 * increment uds_read_highByteCount_manual
 *
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "uds_readData/uds_readData.h"
#include "uds.h"
#include "softwareversion.h"
#include "dem.h"
#include "stateFunctions.h"
#include "cps.h"
#include "diagnosticsCommunication.h"
#include "debug.h"
#include "taskPerformanceMeasurement.h"
#include "stackUsageMonitor.h"
#include "taskAliveMonitor.h"
#include "bufferMethods.h"
#include "afeComProcedure.h"
#include "afeCheck.h"
#include "limitCheckTask.h"
#include "safetyTask.h"

// *************************************************************************************************** /
// ************************* PRIVATE FUNCTIONS DECLARATION ******************************************* /
// *************************************************************************************************** /
static void uds_readTable_getTaskAliveMonitorMinCycleTime(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskAliveMonitorMaxCycleTime(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskAliveMonitorAvgCycleTime(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskAliveMonitorMinCycleTimeStartup(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskAliveMonitorMaxCycleTimeStartup(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskAliveMonitorMinCycleTimeIdle(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskAliveMonitorMaxCycleTimeIdle(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskAliveMonitorMinCycleTimeShutdown(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskAliveMonitorMaxCycleTimeShutdown(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskAliveMonitorGetTaskNameByID(uint8_t* buffer, uint16_t length, uint16_t id);
static void uds_readTable_getMaxCpuUsageShortCycleSystem(uint8_t* buffer, uint16_t length, uint16_t id);
static void uds_readTable_getMinCpuUsageShortCycleSystem(uint8_t* buffer, uint16_t length, uint16_t id);
static void uds_readTable_getCurrentTaskPerformanceMeasurementDutyShortCycle(uint8_t* buffer, uint16_t length);
static void uds_readTable_getMinTaskPerformanceMeasurementDutyShortCycle(uint8_t* buffer, uint16_t length);
static void uds_readTable_getMaxTaskPerformanceMeasurementDutyShortCycle(uint8_t* buffer, uint16_t length);
static void uds_readTable_getCurrentTaskPerformanceMeasurementDutyLongCycle(uint8_t* buffer, uint16_t length);
static void uds_readTable_getMinTaskPerformanceMeasurementDutyLongCycle(uint8_t* buffer, uint16_t length);
static void uds_readTable_getMaxTaskPerformanceMeasurementDutyLongCycle(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskCpuUsageForMaxOverallUsageShortCycle(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskCpuUsageForMaxOverallUsageLongCycle(uint8_t* buffer, uint16_t length);
static void uds_readTable_get_getFreeStackSizeInPercent(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskPerformanceMeasurementDutyCycleSinceStartup(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskPerformanceMeasurementTaskRunningTimeSinceStartup(uint8_t* buffer, uint16_t length);
static void uds_readTable_getStackUsageMonitorMaxFreeStackUsageByTask(uint8_t* buffer, uint16_t length);
static void uds_readTable_getStackUsageMonitorMinFreeStackUsageByTask(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskRunningCycleTimeMin(uint8_t* buffer, uint16_t length);
static void uds_readTable_getTaskRunningCycleTimeMax(uint8_t* buffer, uint16_t length);
static void uds_readTable_getSafetyTaskSubCycleTimes(uint8_t* buffer, uint16_t length);

// *************************************************************************************************** /
// ************************* PRIVATE FUNCTIONS DEFINITIONS ******************************************* /
// *************************************************************************************************** /

/* ************************************** TaskAliveMonitor ******************************************** */
static void uds_readTable_getTaskAliveMonitorMinCycleTime(uint8_t* buffer, uint16_t length)
{
    DEBUG_API_CHECK(length == 80u);
    for(uint16_t i = 0u; i < (length / sizeof(uint32_t)); i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskAliveMonitor_getMinCycleTime(i), buffer);
    }
}

static void uds_readTable_getTaskAliveMonitorMaxCycleTime(uint8_t* buffer, uint16_t length)
{
    DEBUG_API_CHECK(length == 80u);
    for(uint16_t i = 0u; i < (length / sizeof(uint32_t)); i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskAliveMonitor_getMaxCycleTime(i), buffer);
    }
}

static void uds_readTable_getTaskAliveMonitorAvgCycleTime(uint8_t* buffer, uint16_t length)
{
    DEBUG_API_CHECK(length == 80u);
    for(uint16_t i = 0u; i < (length / sizeof(uint32_t)); i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskAliveMonitor_getAvgCycleTime(i), buffer);
    }
}

static void uds_readTable_getTaskRunningCycleTimeMin(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 240u);
    uint8_t taskPrios = (uint8_t)(configTIMER_TASK_PRIORITY + 1u);
    DEBUG_ASSERT((taskPrios * 4u) == 80u);
    DEBUG_ASSERT((TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES * 80u) == length);
    for(uint8_t stateIndex = 0u; stateIndex < (uint8_t)TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES; stateIndex++)
    {
        for(uint8_t i = 0u; i < taskPrios; i++)
        {
            buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getTaskRunningTimeFullCycleMin(i, stateIndex), buffer);
        }
    }
}


static void uds_readTable_getTaskRunningCycleTimeMax(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 240u);
    uint8_t taskPrios = (uint8_t)(configTIMER_TASK_PRIORITY + 1u);
    DEBUG_ASSERT((taskPrios * 4u) == 80u);
    DEBUG_ASSERT((TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES * 80u) == length);
    for(uint8_t stateIndex = 0u; stateIndex < (uint8_t)TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES; stateIndex++)
    {
        for(uint8_t i = 0u; i < taskPrios; i++)
        {
            buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getTaskRunningTimeFullCycleMax(i, stateIndex), buffer);
        }
    }
}

static void uds_readTable_getSafetyTaskSubCycleTimes(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);

    TaskPerformanceMeasurement_SubroutineDiagnosisInfo submoduleTimings = *safetyTask_getSubmoduleTimings(SAFETY_SUBROUTINE_10ms);
    buffer                                                              = bufferMethods_copyValueToBufferBigEndian_u32(submoduleTimings.subroutineMinMeasuredTime, buffer);
    buffer                                                              = bufferMethods_copyValueToBufferBigEndian_u32(submoduleTimings.subroutineMaxMeasuredTime, buffer);

    submoduleTimings = *safetyTask_getSubmoduleTimings(SAFETY_SUBROUTINE_100ms);
    buffer           = bufferMethods_copyValueToBufferBigEndian_u32(submoduleTimings.subroutineMinMeasuredTime, buffer);
    bufferMethods_copyValueToBufferBigEndian_u32(submoduleTimings.subroutineMaxMeasuredTime, buffer);
}

static void uds_readTable_getTaskAliveMonitorMinCycleTimeStartup(uint8_t* buffer, uint16_t length)
{
    DEBUG_API_CHECK(length == 80u);
    for(uint16_t i = 0u; i < (length / sizeof(uint32_t)); i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskAliveMonitor_getMinCycleTimeStartup(i), buffer);
    }
}

static void uds_readTable_getTaskAliveMonitorMaxCycleTimeStartup(uint8_t* buffer, uint16_t length)
{
    DEBUG_API_CHECK(length == 80u);
    for(uint16_t i = 0u; i < (length / sizeof(uint32_t)); i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskAliveMonitor_getMaxCycleTimeStartup(i), buffer);
    }
}

static void uds_readTable_getTaskAliveMonitorMinCycleTimeIdle(uint8_t* buffer, uint16_t length)
{
    DEBUG_API_CHECK(length == 80u);
    for(uint16_t i = 0u; i < (length / sizeof(uint32_t)); i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskAliveMonitor_getMinCycleTimeIdle(i), buffer);
    }
}

static void uds_readTable_getTaskAliveMonitorMaxCycleTimeIdle(uint8_t* buffer, uint16_t length)
{
    DEBUG_API_CHECK(length == 80u);
    for(uint16_t i = 0u; i < (length / sizeof(uint32_t)); i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskAliveMonitor_getMaxCycleTimeIdle(i), buffer);
    }
}

static void uds_readTable_getTaskAliveMonitorMSECycleTimeIdle(uint8_t* buffer, uint16_t length)
{
    DEBUG_API_CHECK(length == 80u);
    for(uint16_t i = 0u; i < (length / sizeof(uint32_t)); i++)
    {
        //cppcheck-suppress misra-c2012-17.8
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskAliveMonitor_getMSECycleTimeIdle(i), buffer);
    }
}

static void uds_readTable_getTaskAliveMonitorMinCycleTimeShutdown(uint8_t* buffer, uint16_t length)
{
    DEBUG_API_CHECK(length == 80u);
    for(uint16_t i = 0u; i < (length / sizeof(uint32_t)); i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskAliveMonitor_getMinCycleTimeShutdown(i), buffer);
    }
}

static void uds_readTable_getTaskAliveMonitorMaxCycleTimeShutdown(uint8_t* buffer, uint16_t length)
{
    DEBUG_API_CHECK(length == 80u);
    for(uint16_t i = 0u; i < (length / sizeof(uint32_t)); i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskAliveMonitor_getMaxCycleTimeShutdown(i), buffer);
    }
}

static void uds_readTable_getTaskAliveMonitorGetTaskNameByID(uint8_t* buffer, uint16_t length, uint16_t id)
{
    DEBUG_API_CHECK(length == 20u);
    taskAliveMonitor_getTaskNameById(buffer, id);
}

static void uds_readTable_getMaxCpuUsageShortCycleSystem(uint8_t* buffer, uint16_t length, uint16_t id)
{
    DEBUG_API_CHECK(length == 12u);
    for(uint8_t stateIndex = 0u; stateIndex < (uint8_t)TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES; stateIndex++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getMaxCpuUsageShortCycleSystem(stateIndex), buffer);
    }
}

static void uds_readTable_getMinCpuUsageShortCycleSystem(uint8_t* buffer, uint16_t length, uint16_t id)
{
    DEBUG_API_CHECK(length == 12u);
    for(uint8_t stateIndex = 0u; stateIndex < (uint8_t)TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES; stateIndex++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getMinCpuUsageShortCycleSystem(stateIndex), buffer);
    }
}

static void uds_readTable_getCurrentTaskPerformanceMeasurementDutyShortCycle(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 80u);
    uint8_t taskPrios = (uint8_t)(configTIMER_TASK_PRIORITY + 1u);
    DEBUG_ASSERT((taskPrios * 4u) == 80u);
    for(uint8_t i = 0u; i < taskPrios; i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getCurrentCpuUsageShortCycleByTask(i), buffer);
    }
}

static void uds_readTable_getMinTaskPerformanceMeasurementDutyShortCycle(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 240u);
    uint8_t taskPrios = (uint8_t)(configTIMER_TASK_PRIORITY + 1u);
    DEBUG_ASSERT((taskPrios * 4u) == 80u);
    DEBUG_ASSERT((TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES * 80u) == length);

    for(uint8_t stateIndex = 0u; stateIndex < (uint8_t)TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES; stateIndex++)
    {
        for(uint8_t i = 0u; i < taskPrios; i++)
        {
            buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getMinCpuUsageShortCycleByTask(i, stateIndex), buffer);
        }
    }
}

static void uds_readTable_getMaxTaskPerformanceMeasurementDutyShortCycle(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 240u);
    uint8_t taskPrios = (uint8_t)(configTIMER_TASK_PRIORITY + 1u);
    DEBUG_ASSERT((taskPrios * 4u) == 80u);
    DEBUG_ASSERT((TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES * 80u) == length);

    for(uint8_t stateIndex = 0u; stateIndex < (uint8_t)TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES; stateIndex++)
    {
        for(uint8_t i = 0u; i < taskPrios; i++)
        {
            buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getMaxCpuUsageShortCycleByTask(i, stateIndex), buffer);
        }
    }
}

static void uds_readTable_getCurrentTaskPerformanceMeasurementDutyLongCycle(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 80u);
    uint8_t taskPrios = (uint8_t)(configTIMER_TASK_PRIORITY + 1u);
    DEBUG_ASSERT((taskPrios * 4u) == 80u);
    for(uint8_t i = 0u; i < taskPrios; i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getCurrentCpuUsageLongCycleByTask(i), buffer);
    }
}

static void uds_readTable_getMinTaskPerformanceMeasurementDutyLongCycle(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 240u);
    uint8_t taskPrios = (uint8_t)(configTIMER_TASK_PRIORITY + 1u);
    DEBUG_ASSERT((taskPrios * 4u) == 80u);
    DEBUG_ASSERT((TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES * 80u) == length);
    for(uint8_t stateIndex = 0u; stateIndex < (uint8_t)TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES; stateIndex++)
    {
        for(uint8_t i = 0u; i < taskPrios; i++)
        {
            buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getMinCpuUsageLongCycleByTask(i, stateIndex), buffer);
        }
    }
}

static void uds_readTable_getMaxTaskPerformanceMeasurementDutyLongCycle(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 240u);
    uint8_t taskPrios = (uint8_t)(configTIMER_TASK_PRIORITY + 1u);
    DEBUG_ASSERT((taskPrios * 4u) == 80u);
    DEBUG_ASSERT((TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES * 80u) == length);
    for(uint8_t stateIndex = 0u; stateIndex < (uint8_t)TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES; stateIndex++)
    {
        for(uint8_t i = 0u; i < taskPrios; i++)
        {
            buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getMaxCpuUsageLongCycleByTask(i, stateIndex), buffer);
        }
    }
}

static void uds_readTable_getTaskCpuUsageForMaxOverallUsageShortCycle(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 240u);
    uint8_t taskPrios = (uint8_t)(configTIMER_TASK_PRIORITY + 1u);
    DEBUG_ASSERT((taskPrios * 4u) == 80u);
    DEBUG_ASSERT((TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES * 80u) == length);
    for(uint8_t stateIndex = 0u; stateIndex < (uint8_t)TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES; stateIndex++)
    {
        for(uint8_t i = 0u; i < taskPrios; i++)
        {
            buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getTaskCpuUsageForMaxOverallUsageShortCycle(i, stateIndex), buffer);
        }
    }
}

static void uds_readTable_getTaskCpuUsageForMaxOverallUsageLongCycle(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 240u);
    uint8_t taskPrios = (uint8_t)(configTIMER_TASK_PRIORITY + 1u);
    DEBUG_ASSERT((taskPrios * 4u) == 80u);
    DEBUG_ASSERT((TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES * 80u) == length);
    for(uint8_t stateIndex = 0u; stateIndex < (uint8_t)TASK_PERFORMANCE_MEASUREMENT_NUMBER_OF_MEASUREMENT_STATES; stateIndex++)
    {
        for(uint8_t i = 0u; i < taskPrios; i++)
        {
            buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getTaskCpuUsageForMaxOverallUsageLongCycle(i, stateIndex), buffer);
        }
    }
}

static void uds_readTable_get_getFreeStackSizeInPercent(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 19u);
    for(uint8_t i = 0u; i < length; i++)
    {
        buffer = bufferMethods_copyValueToBuffer_u8(stackUsageMonitor_getFreeStackSizePercentById(i + 1u), buffer);
    }
}

static void uds_readTable_getTaskPerformanceMeasurementDutyCycleSinceStartup(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 80u);
    uint8_t taskPrios = (uint8_t)(configTIMER_TASK_PRIORITY + 1u);
    DEBUG_ASSERT((taskPrios * 4u) == 80u);
    for(uint8_t i = 0u; i < taskPrios; i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u32(taskPerformanceMeasurement_getDutyCycleSinceStartup(i), buffer);
    }
}

static void uds_readTable_getTaskPerformanceMeasurementTaskRunningTimeSinceStartup(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 152u);
    for(uint8_t i = 0u; i < (length / 8u); i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u64(taskPerformanceMeasurement_getTaskRunningTimeSinceStartup(i + 1u), buffer);
    }
}

static void uds_readTable_getStackUsageMonitorMaxFreeStackUsageByTask(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 18u);
    for(uint8_t i = 0u; i < length; i++)
    {
        buffer = bufferMethods_copyValueToBuffer_u8(stackUsageMonitor_getMaxFreeStackSizeByTask(i + 1u), buffer);
    }
}
static void uds_readTable_getStackUsageMonitorMinFreeStackUsageByTask(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 18u);
    for(uint8_t i = 0u; i < length; i++)
    {
        buffer = bufferMethods_copyValueToBuffer_u8(stackUsageMonitor_getMinFreeStackSizeByTask(i + 1u), buffer);
    }
}
static void uds_readTable_getAfeTimings(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 48u);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(afeComProcedure_getFunctionAvgCycletime(2), buffer);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(afeComProcedure_getFunctionAvgRuntime(2), buffer);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(afeComProcedure_getFunctionMaxCycletime(2), buffer);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(afeComProcedure_getFunctionMaxRuntime(2), buffer);
    for(uint8_t i = 0u; i < afeCheck_getNumGroups(); i++)
    {
        buffer = bufferMethods_copyValueToBufferLittleEndian_u16(afeCheck_getGroupAvgCycletime(i), buffer);
        buffer = bufferMethods_copyValueToBufferLittleEndian_u16(afeCheck_getGroupAvgRuntime(i), buffer);
        buffer = bufferMethods_copyValueToBufferLittleEndian_u16(afeCheck_getGroupMaxCycletime(i), buffer);
        buffer = bufferMethods_copyValueToBufferLittleEndian_u16(afeCheck_getGroupMaxRuntime(i), buffer);
    }
}

// *************************************************************************************************** /
// ************************* UDS Tables ************************************************************** /
// *************************************************************************************************** /


const static DCFunction table_hb140[] = {
    /** {ID, Function Pointer, Return Type, Function Type, P1, P2}  */
    { 0, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 0, 0 },
    { 1, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 1, 0 },
    { 2, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 2, 0 },
    { 3, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 3, 0 },
    { 4, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 4, 0 },
    { 5, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 5, 0 },
    { 6, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 6, 0 },
    { 7, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 7, 0 },
    { 8, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 8, 0 },
    { 9, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 9, 0 },
    { 10, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 10, 0 },
    { 11, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 11, 0 },
    { 12, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 12, 0 },
    { 13, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 13, 0 },
    { 14, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 14, 0 },
    { 15, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 15, 0 },
    { 16, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 16, 0 },
    { 17, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 17, 0 },
    { 18, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 18, 0 },
    { 19, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 19, 0 },
    { 20, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 20, 0 },
    { 21, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 21, 0 },
    { 22, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 22, 0 },
    { 23, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 23, 0 },
    { 24, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 24, 0 },
    { 25, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 25, 0 },
    { 26, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 26, 0 },
    { 27, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 27, 0 },
    { 28, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 28, 0 },
    { 29, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 29, 0 },
    { 30, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 30, 0 },
    { 31, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 31, 0 },
    { 32, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 32, 0 },
    { 33, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 33, 0 },
    { 34, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 34, 0 },
    { 35, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 35, 0 },
    { 36, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 36, 0 },
    { 37, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 37, 0 },
    { 38, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 38, 0 },
    { 39, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 39, 0 },
    { 40, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 40, 0 },
    { 41, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 41, 0 },
    { 42, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 42, 0 },
    { 43, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 43, 0 },
    { 44, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 44, 0 },
    { 45, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 45, 0 },
    { 46, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 46, 0 },
    { 47, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 47, 0 },
    { 48, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 48, 0 },
    { 49, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 49, 0 },
    { 50, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 50, 0 },
    { 51, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 51, 0 },
    { 52, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 52, 0 },
    { 53, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 53, 0 },
    { 54, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 54, 0 },
    { 55, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 55, 0 },
    { 56, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 56, 0 },
    { 57, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 57, 0 },
    { 58, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 58, 0 },
    { 59, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 59, 0 },
    { 60, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 60, 0 },
    { 61, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 61, 0 },
    { 62, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 62, 0 },
    { 63, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 63, 0 },
    { 64, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 64, 0 },
    { 65, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 65, 0 },
    { 66, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 66, 0 },
    { 67, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 67, 0 },
    { 68, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 68, 0 },
    { 69, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 69, 0 },
    { 70, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 70, 0 },
    { 71, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 71, 0 },
    { 72, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 72, 0 },
    { 73, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 73, 0 },
    { 74, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 74, 0 },
    { 75, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 75, 0 },
    { 76, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 76, 0 },
    { 77, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 77, 0 },
    { 78, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 78, 0 },
    { 79, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 79, 0 },
    { 80, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 80, 0 },
    { 81, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 81, 0 },
    { 82, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 82, 0 },
    { 83, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 83, 0 },
    { 84, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 84, 0 },
    { 85, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 85, 0 },
    { 86, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 86, 0 },
    { 87, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 87, 0 },
    { 88, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 88, 0 },
    { 89, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 89, 0 },
    { 90, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 90, 0 },
    { 91, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 91, 0 },
    { 92, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 92, 0 },
    { 93, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 93, 0 },
    { 94, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 94, 0 },
    { 95, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 95, 0 },
    { 96, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 96, 0 },
    { 97, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 97, 0 },
    { 98, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 98, 0 },
    { 99, (void*)dem_getFaultInfoValue, DCReturnType_DEM_FAULTINFO, DCFunctionType_Array1D, 99, 0 },
};

const static DCFunction table_hb141[] = {
    { 0, (void*)softwareversion_getCommit_app, DCReturnType_UINT32, DCFunctionType_Var, 0, 0 },
    { 1, (void*)softwareversion_getMajor_app, DCReturnType_UINT16, DCFunctionType_Var, 0, 0 },
    { 2, (void*)softwareversion_getMinor_app, DCReturnType_UINT16, DCFunctionType_Var, 0, 0 },
    { 3, (void*)softwareversion_getPatch_app, DCReturnType_UINT16, DCFunctionType_Var, 0, 0 },
    { 4, (void*)softwareversion_getTimestamp_app, DCReturnType_String, DCFunctionType_Var, 0, 0 },
    { 5, (void*)softwareversion_getTag_app, DCReturnType_String, DCFunctionType_Var, 0, 0 },
    { 6, (void*)softwareversion_getProjectName_app, DCReturnType_String, DCFunctionType_Var, 0, 0 },
    //		{7, (void*)softwareversion_getReleaseStatus, DCReturnType_String, DCFunctionType_Var, 0,0},
};

const static DCFunction table_hb142[] = {
    { 0, (void*)uds_getBufferSize, DCReturnType_UINT16, DCFunctionType_Var, 0, 0 },
};

const static DCFunction table_hb145[] = {
    { 200, (void*)taskPerformanceMeasurement_getCurrentCpuUsageShortCycleSystem, DCReturnType_UINT32, DCFunctionType_Var, 0, 0, 0b0 },
    { 201, (void*)uds_readTable_getMaxCpuUsageShortCycleSystem, DCReturnType_Buffer, DCFunctionType_Var, 12, 0, 0b0 },
    { 202, (void*)uds_readTable_getMinCpuUsageShortCycleSystem, DCReturnType_Buffer, DCFunctionType_Var, 12, 0, 0b0 },
    { 203, (void*)uds_readTable_getCurrentTaskPerformanceMeasurementDutyShortCycle, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 204, (void*)uds_readTable_getMinTaskPerformanceMeasurementDutyShortCycle, DCReturnType_Buffer, DCFunctionType_Var, 240, 0, 0b0 },
    { 205, (void*)uds_readTable_getMaxTaskPerformanceMeasurementDutyShortCycle, DCReturnType_Buffer, DCFunctionType_Var, 240, 0, 0b0 },
    { 206, (void*)uds_readTable_getCurrentTaskPerformanceMeasurementDutyLongCycle, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 207, (void*)uds_readTable_getMinTaskPerformanceMeasurementDutyLongCycle, DCReturnType_Buffer, DCFunctionType_Var, 240, 0, 0b0 },
    { 208, (void*)uds_readTable_getMaxTaskPerformanceMeasurementDutyLongCycle, DCReturnType_Buffer, DCFunctionType_Var, 240, 0, 0b0 },
    { 209, (void*)uds_readTable_getTaskCpuUsageForMaxOverallUsageShortCycle, DCReturnType_Buffer, DCFunctionType_Var, 240, 0, 0b0 },
    { 210, (void*)uds_readTable_getTaskCpuUsageForMaxOverallUsageLongCycle, DCReturnType_Buffer, DCFunctionType_Var, 240, 0, 0b0 },
    { 211, (void*)uds_readTable_getTaskPerformanceMeasurementDutyCycleSinceStartup, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 212, (void*)uds_readTable_getTaskPerformanceMeasurementTaskRunningTimeSinceStartup, DCReturnType_Buffer, DCFunctionType_Var, 152, 0, 0b0 },
    { 213, (void*)uds_readTable_get_getFreeStackSizeInPercent, DCReturnType_Buffer, DCFunctionType_Var, 19, 0, 0b0 },
    { 214, (void*)uds_readTable_getStackUsageMonitorMaxFreeStackUsageByTask, DCReturnType_Buffer, DCFunctionType_Var, 18, 0, 0b0 },
    { 215, (void*)uds_readTable_getStackUsageMonitorMinFreeStackUsageByTask, DCReturnType_Buffer, DCFunctionType_Var, 18, 0, 0b0 },
    { 216, (void*)stackUsageMonitor_getMaxFreeStackSizeBySystem, DCReturnType_UINT8, DCFunctionType_Var, 0, 0, 0b0 },
    { 217, (void*)stackUsageMonitor_getMinFreeStackSizeBySystem, DCReturnType_UINT8, DCFunctionType_Var, 0, 0, 0b0 },
    { 218, (void*)uds_readTable_getTaskAliveMonitorMinCycleTime, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 219, (void*)uds_readTable_getTaskAliveMonitorMaxCycleTime, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 220, (void*)uds_readTable_getTaskAliveMonitorAvgCycleTime, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 221, (void*)uds_readTable_getTaskRunningCycleTimeMin, DCReturnType_Buffer, DCFunctionType_Var, 240, 0, 0b0 },
    { 222, (void*)uds_readTable_getTaskRunningCycleTimeMax, DCReturnType_Buffer, DCFunctionType_Var, 240, 0, 0b0 },
    { 224, (void*)uds_readTable_getSafetyTaskSubCycleTimes, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 225, (void*)uds_readTable_getTaskAliveMonitorMinCycleTimeStartup, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 226, (void*)uds_readTable_getTaskAliveMonitorMaxCycleTimeStartup, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 227, (void*)uds_readTable_getTaskAliveMonitorMinCycleTimeIdle, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 228, (void*)uds_readTable_getTaskAliveMonitorMaxCycleTimeIdle, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 229, (void*)uds_readTable_getTaskAliveMonitorMinCycleTimeShutdown, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 230, (void*)uds_readTable_getTaskAliveMonitorMaxCycleTimeShutdown, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
    { 231, (void*)uds_readTable_getAfeTimings, DCReturnType_Buffer, DCFunctionType_Var, 48, 0, 0b0 },
    { 232, (void*)afeComProcedure_getBalancingPercentage, DCReturnType_UINT32, DCFunctionType_Var, 0, 0, 0b0 },
    { 233, (void*)uds_readTable_getTaskAliveMonitorMSECycleTimeIdle, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },
};

const static DCFunction table_hb146[] = {
    { 200, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 0, 0b0 },
    { 201, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 1, 0b0 },
    { 202, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 2, 0b0 },
    { 203, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 3, 0b0 },
    { 204, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 4, 0b0 },
    { 205, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 5, 0b0 },
    { 206, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 6, 0b0 },
    { 207, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 7, 0b0 },
    { 208, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 8, 0b0 },
    { 209, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 9, 0b0 },
    { 210, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 10, 0b0 },
    { 211, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 11, 0b0 },
    { 212, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 12, 0b0 },
    { 213, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 13, 0b0 },
    { 214, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 14, 0b0 },
    { 215, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 15, 0b0 },
    { 216, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 16, 0b0 },
    { 217, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 17, 0b0 },
    { 218, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 18, 0b0 },
    { 219, (void*)uds_readTable_getTaskAliveMonitorGetTaskNameByID, DCReturnType_Buffer, DCFunctionType_Array1D, 20, 19, 0b0 },
};

const UDSFunctionTable udsFunctionTables_manual[] = {
    { 140, sizeof(table_hb140) / sizeof(DCFunction), table_hb140 },
    { 141, sizeof(table_hb141) / sizeof(DCFunction), table_hb141 },
    { 142, sizeof(table_hb142) / sizeof(DCFunction), table_hb142 },
    { 145, sizeof(table_hb145) / sizeof(DCFunction), table_hb145 },
    { 146, sizeof(table_hb146) / sizeof(DCFunction), table_hb146 }
};

const uint8_t uds_read_highByteCount_manual = sizeof(udsFunctionTables_manual) / sizeof(UDSFunctionTable);

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
