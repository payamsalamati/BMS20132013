/**
 * @file uds_routineControl_config.c
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>

#include "uds_routineControl.h"
#include "uds_protected.h"
#include "debug.h"
#include "types.h"
#include "cps.h"
#include "memIf.h"
#include "voltageHistogram.h"
#include "temperatureHistogram.h"
#include "contactorHistogram.h"
#include "currentViolationHistogram.h"
#include "voltageViolationHistogram.h"
#include "cellVoltageMeasurement.h"
#include "moduleVoltageMeasurement.h"
#include "moduleVoltageTemperatureHistogram.h"
#include "batteryCurrentTemperatureHistogram.h"
#include "cellTemperatureMeasurement.h"
#include "afeTemperatureMeasurement.h"
#include "systemMasterInfoReceive.h"
#include "downscaledVoltageTemperatureHistogram.h"
#include "safetyAfeValueMeasurement.h"
#include "diagnosticTimes.h"

#include "uds_routineControl_config.h"
#include "uds_diagnosticSessionControl_config.h"
#include "task_cfg.h"
#include "csc_config.h"
#include "afe_MC33771_config.h"
#include "afe_MC33771_private.h"
#include "cscNvm_config.h"
#include "bufferMethods.h"
#include "afeComProcedure.h"
#include "subMasterBalancing.h"
#include "icdaSensor_requestMessages.h"
#include "icdaSensor.h"
#include "icdaSensor_private.h"
#include "taskAliveMonitor.h"
#include "stackUsageMonitor.h"
#include "eventData.h"
#include "voltageContactorHistogram.h"

#if defined(BMS_CONFIG_TASK_PERFORMACE_MEASUREMENT)
#include "afeTask.h"
#include "taskPerformanceMeasurement.h"
#include "afeCheck.h"
#endif

#if defined(BMS_EXTERNAL_INTERFACE)
#include "kbsIntegration.h"
#endif

#if defined(HIL_CONFIGURATION) || defined(SIL_DEBUG)
#include "vehicleManufacturerData.h"
#endif

#include "energyCounter.h"
#include "heatingCurrentHistogram.h"
#include "currentViolationLogHistogram.h"
#include "downscaledCurrentViolationHistogram.h"
#include "batteryContactorHistogram.h"
#include "masterPcbTemperatureHistogram.h"
#include "socTemperatureHistogram.h"
#include "terminalTemperatureMeasurement.h"
#include "heatingCurrentMeasurement.h"

#if defined(SYNC_AFE_AND_ICDA_MEASUREMENTS)
#include "synchronizedMeasurements.h"
#endif
//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef enum
{
    UDS_ROUTINE_ERASE_USER_MEMORY_DTCS                        = 0xFF02,
    UDS_ROUTINE_RESET_TO_DEFAULT_SETTINGS                     = 0x0201,
    UDS_ROUTINE_CHECK_PROGRAMMING_PRECONDITIONS               = 0x0203,
    UDS_ROUTINE_RESET_TO_FACTORY_SETTINGS                     = 0x0204,
    UDS_ROUTINE_ERASE_EEPROM                                  = 0x0205,
    UDS_ROUTINE_CLEAR_TASK_PERFORMANCE_DATA_NVM               = 0x020B,
    UDS_ROUTINE_MASTER_RESET_BATTERY_HISTOGRAMS               = 0x0400,
    UDS_ROUTINE_MASTER_RESET_MODULE_HISTOGRAMS                = 0x0401,
    UDS_ROUTINE_MASTER_ROUTINE_RESET_TIMER_DATA               = 0x0402,
    UDS_ROUTINE_MASTER_ROUTINE_RESET_EVENT_DATA               = 0x0403,
    UDS_ROUTINE_MASTER_ROUTINE_RESET_COUNTER_DATA             = 0x0404,
    UDS_ROUTINE_MASTER_ROUTINE_RESET_CYCLE_DATA               = 0x0405,
    UDS_ROUTINE_MASTER_ROUTINE_RESET_ENERGY_DATA              = 0x0406,
    UDS_ROUTINE_MASTER_ROUTINE_RESET_ERROR_COUNTER            = 0x0407,
    UDS_ROUTINE_MASTER_ROUTINE_RESET_COMPLETE                 = 0x0408,
    UDS_ROUTINE_MASTER_ROUTINE_RESET_IRREVERSIBLE_ERROR       = 0x0409,
    UDS_ROUTINE_MASTER_RESET_CONTACTOR_HISTOGRAMS             = 0x0410,
    UDS_ROUTINE_MASTER_ROUTINE_CAPACITY_MEASUREMENT           = 0x0420,
    UDS_ROUTINE_MASTER_ROUTINE_POWERPATH_CONNECTION_ANALYSIS  = 0x0421,
    UDS_ROUTINE_MASTER_ROUTINE_INITIATE_DATA_RECOVERY_BATTERY = 0x0422,
    UDS_ROUTINE_MASTER_ROUTINE_UPDATE_RECOVERY_DATA           = 0x0423,
    UDS_ROUTINE_MASTER_ROUTINE_SOC_REFERENCE                  = 0x0424,
    UDS_ROUTINE_LIB_TURN_ON_KION                              = 0x0425,
    UDS_ROUTINE_LIB_TURN_OFF_KION                             = 0x0426,
    UDS_ROUTINE_MASTER_START_CPS_OUT_CONTROL                  = 0x0427,
    UDS_ROUTINE_MASTER_START_CPS_POWER_DOWN                   = 0x0428,
    UDS_ROUTINE_MASTER_ROUTINE_REST_SOH                       = 0x0429,
    UDS_ROUTINE_MASTER_SET_TO_DEFAULT                         = 0x0430,
    UDS_ROUTINE_SLAVE_RESET_HISTOGRAMS                        = 0x0700,
    UDS_ROUTINE_SLAVE_ROUTINE_RESET_EVENT_DATA                = 0x0701,
    UDS_ROUTINE_SLAVE_ROUTINE_RESET_CYCLE_DATA                = 0x0702,
    UDS_ROUTINE_SLAVE_ROUTINE_RESET_ENERGY_DATA               = 0x0703,
    UDS_ROUTINE_SLAVE_ROUTINE_RESET_DEEP_DISCHARGE_FLAG       = 0x0704,
    UDS_ROUTINE_SLAVE_ROUTINE_RESET_COMPLETE                  = 0x0705,
    UDS_ROUTINE_CYCLE_COUNTER                                 = 0x0730,
    UDS_ROUTINE_ENERGY_COUNTER                                = 0x0731,
    UDS_ROUTINE_DEEP_DISCHARGE_FLAG                           = 0x0732,
    UDS_ROUTINE_CELL_VOLTAGES                                 = 0x0733,
    UDS_ROUTINE_TEMPERATURES                                  = 0x0734,
    UDS_ROUTINE_BALANCING_STATUS                              = 0x0735,
    UDS_ROUTINE_HEATING_CURRENT                               = 0x0736,
    UDS_ROUTINE_READ_CSC_PCB_IDENTIFICATION                   = 0x0737,
    UDS_ROUTINE_READ_CSC_PARAMETER_BANDENDE                   = 0x0738,
    UDS_ROUTINE_READ_MODULE_AGING                             = 0x0739,
    UDS_ROUTINE_WRITE_CSC_PCB_IDENTIFICATION                  = 0x073A,
    UDS_ROUTINE_WRITE_CSC_PARAMETER_BANDENDE                  = 0x073B,
    UDS_ROUTINE_WRITE_MODULE_AGING                            = 0x073C,
    UDS_ROUTINE_HEATING_FOIL                                  = 0x073D,
    UDS_ROUTINE_LIB_HEATING_MANUAL_CONTROL_ACTIVATE           = 0x0740,
    UDS_ROUTINE_LIB_HEATING_MANUAL_CONTROL_DEACTIVATE         = 0x0741,
    UDS_ROUTINE_U_CELL_HISTOGRAM_OP                           = 0x0750,
    UDS_ROUTINE_U_CELL_HISTOGRAM_ST                           = 0x0751,
    UDS_ROUTINE_U_LOW_VIOLATION_HISTOGRAM                     = 0x0752,
    UDS_ROUTINE_U_HIGH_VIOLATION_HISTOGRAM                    = 0x0753,
    UDS_ROUTINE_T_HISTOGRAM_OP                                = 0x0754,
    UDS_ROUTINE_T_HISTOGRAM_ST                                = 0x0755,
    UDS_ROUTINE_U_T_MODULE_HISTOGRAM_DOWNSCALED               = 0x0756,
    UDS_ROUTINE_HEATING_HISTOGRAM                             = 0x0757,
    UDS_ROUTINE_HEATING_HISTOGRAM_DOWNSCALED                  = 0x0758,
    UDS_ROUTINE_I_T_HISTOGRAM                                 = 0x0759,
    // ICD-A routines
    UDS_ROUTINE_ICD_GET_EVENT_COUNTER   = 0x0432,
    UDS_ROUTINE_ICD_CLEAR_EVENT_COUNTER = 0x0433,
    UDS_ROUTINE_ICD_CLEAR_STATUS        = 0x0434,
    UDS_ROUTINE_ICD_RESET               = 0x0435,
#if defined(BMS_CONFIG_TASK_PERFORMACE_MEASUREMENT)
    // taskPerformanceMeasurement subroutine data only for debug purpose on Hil/Sil build
    UDS_ROUTINE_AFE_TASK_SUBROUTINE_TIMINGS    = 0x1234,  // get min, max & avg value of afeTask submodule time
    UDS_ROUTINE_AFE_TASK_SUBROUTINE_OS_TIMINGS = 0x1235,  // get min, max & avg value of afeTask submodule time considering OS delays
#endif
#if defined(HIL_CONFIGURATION) || defined(SIL_DEBUG)
    UDS_ROUTINE_RESET_WRITE_ONCE_DATA               = 0x1236,
    UDS_ROUTINE_RESET_ICDA_AFE_SYNCHRONIZATION_DATA = 0x1237,
#endif
} UDS_ROUTINE_CONTROL_ID;

typedef enum
{
    CORRECT_RESULT   = 0x00,
    INCORRECT_RESULT = 0x01
} ROUTINE_STATUS;

typedef enum
{
    ENGINE_SPEED_NOT_ZERO              = 0x01,
    IMMOBILISER_NOT_ENABLED            = 0x02,
    TRANSMISSION_INPUT_SPEED_NOT_ZERO  = 0x03,
    TRANSMISSION_OUTPUT_SPEED_NOT_ZERO = 0x04,
    VEHICLE_SPEED_NOT_ZERO             = 0x05,
    CONTROL_ACTIVE                     = 0x06,
    IGNITION_OFF_ON_REQUIRED           = 0x07,
    NO_PROGRAMMING_VOLTAGE             = 0x08,
    IGNITION_NOT_SWITCHED_ON           = 0x09,
    ON_BOARD_POWER_SUPPLY_TOO_LOW      = 0x0A,
    TEMPERATURE_TOO_HIGH               = 0x0B,
    TEMPERATURE_TOO_LOW                = 0x0C,
    IGNITION_SWITCHED_ON_TERMINAL_15   = 0x80,
    BATTERY_CURRENTLY_BEING_CHARGED    = 0x81,
    BATTERY_MAIN_CONTACTOR_CLOSED      = 0x82
} PROGRAMMING_CONDITION_ID;

#define EEPROM_START_ADDRESS 0x00000u

#define MODULE_COUNTING_OFFSET 1u  // customer starts counting the modules at 1, whereas we start at 0 for the histograms

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_UDS static bool preconditionsChecked = false;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static UDS_ErrorCode dummy_routine_control(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);

static UDS_ErrorCode udsRoutineControlEraseEepromStart(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineControlClearTaskPerformanceNvmData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineMasterRoutineResetBatteryHistogramData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineMasterRoutineResetModuleHistogramData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineMasterRoutineResetContactorHistograms(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineMasterRoutineResetTimerData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineMasterRoutineResetEventData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineMasterRoutineResetEnergyCounter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineMasterRoutineStartCPSoutControl(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
// @req CB-79188
static UDS_ErrorCode udsRoutineMasterRoutineStartCPSPowerDown(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
// @req CB-78709
static UDS_ErrorCode startRoutineU_cell_histogram_op(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
// @req CB-78717
static UDS_ErrorCode startRoutineU_cell_histogram_st(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineU_low_violation_histogram(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineU_high_violation_histogram(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
// @req CB-78731
static UDS_ErrorCode startRoutineT_histogram_op(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
// @req CB-78739
static UDS_ErrorCode startRoutineT_histogram_st(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
// @req CB-78755
static UDS_ErrorCode startRoutineU_t_module_histogram_downscaled(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
// @req CB-78746
static UDS_ErrorCode startRoutineHeating_histogram(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineHeating_histogram_downscaled(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineI_T_histogram(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineCycle_counter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineEnergy_counter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineDeep_discharge_flag(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineCell_voltages(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
// @req CB-79129
static UDS_ErrorCode startRoutineTemperatures(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineBalancing_status(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
// @req CB-79132
static UDS_ErrorCode startRoutineHeating_current(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineRead_csc_pcb_identification(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineRead_csc_parameter_bandende(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineWrite_csc_pcb_identification(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineWrite_csc_parameter_bandende(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineWrite_module_aging(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
// @req CB-79133
static UDS_ErrorCode startRoutine_lib_heating_manual_control_activate(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
// @req CB-79135
static UDS_ErrorCode startRoutine_lib_heating_manual_control_deactivate(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineSlaveRoutineResetModuleHistogramData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineSlaveRoutineResetEventData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineResetCycle_counter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineCscRoutineResetEnergyData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineResetDeepDischarge(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode udsRoutineSlaveRoutineResetComplete(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode uds_routineControl_CheckProgrammingPreconditions(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode uds_routineControl_EraseUserMemoryDTCs(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode uds_routineControl_ResetToDefaultSettings(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode uds_routineControl_ResetToFactorySettings(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);

// @req CB-10246
// @req CB-10269
// @req CB-88857
static UDS_ErrorCode startRoutineICDreset(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);

// @req CB-10247 https://polarion.futavis.de/polarion/#/project/CB_BMS/workitem?id=CB-10247
// @req CB-10270 https://polarion.futavis.de/polarion/#/project/CB_BMS/workitem?id=CB-10270
static UDS_ErrorCode startRoutineICDClearStatus(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);

// @req CB-10248 https://polarion.futavis.de/polarion/#/project/CB_BMS/workitem?id=CB-10248
static UDS_ErrorCode startRoutineICDClearEventCounter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);

// @req CB-10251 https://polarion.futavis.de/polarion/#/project/CB_BMS/workitem?id=CB-10251
static UDS_ErrorCode startRoutineICDGetEventCounter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);

#if defined(BMS_CONFIG_TASK_PERFORMACE_MEASUREMENT)
static UDS_ErrorCode startRoutineAfeTaskSubmoduleTimings(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineAfeTaskSubmoduleOSTimings(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
#endif

#if defined(HIL_CONFIGURATION) || defined(SIL_DEBUG)
static UDS_ErrorCode startRoutineResetWriteOnceData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
static UDS_ErrorCode startRoutineResetIcdaAfeSynchronizationData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex);
#endif

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static UDS_ErrorCode dummy_routine_control(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    return UDS_ERR_CODE_SERVICE_NOT_SUPPORTED;
}

static UDS_ErrorCode udsRoutineControlEraseEepromStart(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode error        = UDS_ERR_CODE_OK;
    EEPROM_Status eepromStatus = memIf_eraseDirect(EEPROM_START_ADDRESS, eepromIf_getTotalMemorySize(0));

    if(eepromStatus != EEPROM_SUCCESS)
    {
        error = UDS_ERR_CODE_GENERAL_PROGRAMM_ERR;
    }
    return error;
}

static UDS_ErrorCode udsRoutineControlClearTaskPerformanceNvmData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    taskAliveMonitor_clearNVM();
#if defined(BMS_CONFIG_TASK_PERFORMACE_MEASUREMENT)
    taskPerformanceMeasurement_clearNVM();
#endif
    stackUsageMonitor_clearNVM();
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode udsRoutineMasterRoutineResetBatteryHistogramData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        batteryCurrentTemperatureHistogram_resetHistograms();
        currentViolationHistogram_resetHistograms();
        moduleVoltageTemperatureHistogram_resetHistograms();
        currentViolationLogHistogram_resetHistogram();
        masterPcbTemperatureHistogram_resetHistogram();
        socTemperatureHistogram_resetHistogram();
    }

    return errorCode;
}

static UDS_ErrorCode udsRoutineMasterRoutineResetModuleHistogramData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    uint8_t moduleNumber    = *option;
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if(optionLength != 1u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if(moduleNumber == 0u)
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    else if(moduleNumber == 255u)
    { /* 255 is supposed to reset the histograms of all slaves */
        for(uint8_t i = 0u; i < BMS_CONFIG_NUMBER_OF_SLAVES; i++)
        {
            voltageHistogram_resetModuleHistogram(i);
            voltageViolationHistogram_resetModuleHistogram(i);
            temperatureHistogram_resetModuleHistograms(i);
            downscaledVoltageTemperatureHistogram_resetModuleHistogram(i);
            heatingCurrentHistogram_resetHistograms(i);
            downscaledCurrentViolationHistogram_resetModuleHistogram(i);
        }
    }
    else if(moduleNumber <= BMS_CONFIG_NUMBER_OF_SLAVES)
    {
        voltageHistogram_resetModuleHistogram(moduleNumber - MODULE_COUNTING_OFFSET);
        voltageViolationHistogram_resetModuleHistogram(moduleNumber - MODULE_COUNTING_OFFSET);
        temperatureHistogram_resetModuleHistograms(moduleNumber - MODULE_COUNTING_OFFSET);
        downscaledVoltageTemperatureHistogram_resetModuleHistogram(moduleNumber - MODULE_COUNTING_OFFSET);
        heatingCurrentHistogram_resetHistograms(moduleNumber - MODULE_COUNTING_OFFSET);
        downscaledCurrentViolationHistogram_resetModuleHistogram(moduleNumber - MODULE_COUNTING_OFFSET);
    }
    else
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    return errorCode;
}

static UDS_ErrorCode udsRoutineMasterRoutineResetContactorHistograms(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        contactorHistogram_resetHistograms();
        batteryContactorHistogram_resetHistogram();
        voltageContactorHistogram_resetHistogram();
    }

    return errorCode;
}

// @req CB-79172
static UDS_ErrorCode udsRoutineMasterRoutineResetTimerData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        diagnosticTimes_clearAll();
    }

    return errorCode;
}

// @req CB-89026
static UDS_ErrorCode udsRoutineMasterRoutineResetEventData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        eventData_resetEventData();
    }

    return errorCode;
}

// @req CB-79177
static UDS_ErrorCode udsRoutineMasterRoutineResetEnergyCounter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        energyCounter_resetDiagnosticCoulombCount();
    }

    return errorCode;
}

static UDS_ErrorCode udsRoutineMasterRoutineStartCPSoutControl(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;
    if(optionLength != 1u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if(*option == 1u)
    {
        cps_setCpsOutBmsReq(true);
    }
    else if(*option == 2u)
    {
        cps_setCpsOutBmsReq(false);
    }
    else
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    return errorCode;
}

static UDS_ErrorCode udsRoutineMasterRoutineStartCPSPowerDown(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        cps_setCpsPowerDownRegularShutdown();
    }

    return errorCode;
}

// @req CB-78709
static UDS_ErrorCode startRoutineU_cell_histogram_op(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength >= 145u);
        *responseIndex += 145u;
        const uint8_t cscAddress = *option - 1u;
        if(cscAddress >= BMS_CONFIG_NUMBER_OF_SLAVES)
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            uint16_t min_size                  = 0;
            uint16_t max_size                  = 0;
            uint16_t avg_size                  = 0;
            const uint32_t* minHistogramBuffer = (uint32_t*)voltageHistogram_getMinVoltageOperationHistogram(cscAddress, &min_size);
            const uint32_t* maxHistogramBuffer = (uint32_t*)voltageHistogram_getMaxVoltageOperationHistogram(cscAddress, &max_size);
            const uint32_t* avgHistogramBuffer = (uint32_t*)voltageHistogram_getAvgVoltageOperationHistogram(cscAddress, &avg_size);
            if((min_size > CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL)
               || (max_size > CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL)
               || (avg_size > CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL)
               || ((((min_size + max_size + avg_size) * sizeof(uint32_t)) + optionLength) > 145u))
            {
                errorCode = UDS_ERR_CODE_RESP_TOO_LONG;
            }
            else
            {
                response = bufferMethods_copyValueToBuffer_u8(*option, response);
                for(uint16_t index = 0u; index < (uint16_t)min_size; index++)
                {
                    response = bufferMethods_copyValueToBufferBigEndian_u32(minHistogramBuffer[index], response);
                    response = bufferMethods_copyValueToBufferBigEndian_u32(maxHistogramBuffer[index], response);
                    response = bufferMethods_copyValueToBufferBigEndian_u32(avgHistogramBuffer[index], response);
                }
            }
        }
    }
    return errorCode;
}

// @req CB-78717
static UDS_ErrorCode startRoutineU_cell_histogram_st(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength >= 145u);
        *responseIndex += 145u;
        const uint8_t cscAddress = *option - 1u;
        if(cscAddress >= BMS_CONFIG_NUMBER_OF_SLAVES)
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            uint16_t min_size                  = 0;
            uint16_t max_size                  = 0;
            uint16_t avg_size                  = 0;
            const uint32_t* minHistogramBuffer = (uint32_t*)voltageHistogram_getMinVoltageStorageHistogram(cscAddress, &min_size);
            const uint32_t* maxHistogramBuffer = (uint32_t*)voltageHistogram_getMaxVoltageStorageHistogram(cscAddress, &max_size);
            const uint32_t* avgHistogramBuffer = (uint32_t*)voltageHistogram_getAvgVoltageStorageHistogram(cscAddress, &avg_size);
            if((min_size > CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL)
               || (max_size > CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL)
               || (avg_size > CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL)
               || ((((min_size + max_size + avg_size) * sizeof(uint32_t)) + optionLength) > 145u))
            {
                errorCode = UDS_ERR_CODE_RESP_TOO_LONG;
            }
            else
            {
                response = bufferMethods_copyValueToBuffer_u8(*option, response);
                for(uint16_t index = 0u; index < (uint16_t)min_size; index++)
                {
                    response = bufferMethods_copyValueToBufferBigEndian_u32(minHistogramBuffer[index], response);
                    response = bufferMethods_copyValueToBufferBigEndian_u32(maxHistogramBuffer[index], response);
                    response = bufferMethods_copyValueToBufferBigEndian_u32(avgHistogramBuffer[index], response);
                }
            }
        }
    }
    return errorCode;
}

static UDS_ErrorCode startRoutineU_low_violation_histogram(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength >= 8u);
        *responseIndex += 8u;
        const uint8_t cscAddress = *option - 1u;
        if(cscAddress >= BMS_CONFIG_NUMBER_OF_SLAVES)
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            uint16_t size                  = 0u;
            const uint8_t* histogramBuffer = voltageViolationHistogram_getLowViolationHistogram(cscAddress, &size);
            DEBUG_ASSERT((size * sizeof(uint32_t)) == 8u);
            memcpy(&response[0], histogramBuffer, (size * sizeof(uint32_t)));
        }
    }
    return errorCode;
}

static UDS_ErrorCode startRoutineU_high_violation_histogram(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength >= 8u);
        *responseIndex += 8u;
        const uint8_t cscAddress = *option - 1u;
        if(cscAddress >= BMS_CONFIG_NUMBER_OF_SLAVES)
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            uint16_t size                  = 0;
            const uint8_t* histogramBuffer = voltageViolationHistogram_getHighViolationHistogram(cscAddress, &size);
            DEBUG_ASSERT((size * sizeof(uint32_t)) == 8u);
            memcpy(&response[0], histogramBuffer, (size * sizeof(uint32_t)));
        }
    }
    return errorCode;
}

// @req CB-78731
static UDS_ErrorCode startRoutineT_histogram_op(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength >= 109u);
        *responseIndex += 109u;
        const uint8_t cscAddress = *option - 1u;
        if(cscAddress >= BMS_CONFIG_NUMBER_OF_SLAVES)
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            uint16_t min_size                  = 0;
            uint16_t max_size                  = 0;
            uint16_t avg_size                  = 0;
            const uint32_t* minHistogramBuffer = (const uint32_t*)temperatureHistogram_getMinTemperatureOperationHistogram(cscAddress, &min_size);
            const uint32_t* maxHistogramBuffer = (const uint32_t*)temperatureHistogram_getMaxTemperatureOperationHistogram(cscAddress, &max_size);
            const uint32_t* avgHistogramBuffer = (const uint32_t*)temperatureHistogram_getAvgTemperatureOperationHistogram(cscAddress, &avg_size);
            if((min_size > TEMPERATURE_HISTOGRAM_COUNTER_SIZE)
               || (max_size > TEMPERATURE_HISTOGRAM_COUNTER_SIZE)
               || (avg_size > TEMPERATURE_HISTOGRAM_COUNTER_SIZE)
               || ((((min_size + max_size + avg_size) * sizeof(uint32_t)) + optionLength) > 109u))
            {
                errorCode = UDS_ERR_CODE_RESP_TOO_LONG;
            }
            else
            {
                response = bufferMethods_copyValueToBuffer_u8(*option, response);
                for(uint16_t index = 0u; index < (uint16_t)TEMPERATURE_HISTOGRAM_COUNTER_SIZE; index++)
                {
                    response = bufferMethods_copyValueToBufferBigEndian_u32(minHistogramBuffer[index], response);
                    response = bufferMethods_copyValueToBufferBigEndian_u32(maxHistogramBuffer[index], response);
                    response = bufferMethods_copyValueToBufferBigEndian_u32(avgHistogramBuffer[index], response);
                }
            }
        }
    }
    return errorCode;
}

// @req CB-78739
static UDS_ErrorCode startRoutineT_histogram_st(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength >= 109u);
        *responseIndex += 109u;
        const uint8_t cscAddress = *option - 1u;
        if(cscAddress >= BMS_CONFIG_NUMBER_OF_SLAVES)
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            uint16_t min_size                  = 0;
            uint16_t max_size                  = 0;
            uint16_t avg_size                  = 0;
            const uint32_t* minHistogramBuffer = (const uint32_t*)temperatureHistogram_getMinTemperatureStoragenHistogram(cscAddress, &min_size);
            const uint32_t* maxHistogramBuffer = (const uint32_t*)temperatureHistogram_getMaxTemperatureStoragenHistogram(cscAddress, &max_size);
            const uint32_t* avgHistogramBuffer = (const uint32_t*)temperatureHistogram_getAvgTemperatureStoragenHistogram(cscAddress, &avg_size);
            if((min_size > TEMPERATURE_HISTOGRAM_COUNTER_SIZE)
               || (max_size > TEMPERATURE_HISTOGRAM_COUNTER_SIZE)
               || (avg_size > TEMPERATURE_HISTOGRAM_COUNTER_SIZE)
               || ((((min_size + max_size + avg_size) * sizeof(uint32_t)) + optionLength) > 109u))
            {
                errorCode = UDS_ERR_CODE_RESP_TOO_LONG;
            }
            else
            {
                response = bufferMethods_copyValueToBuffer_u8(*option, response);
                for(uint16_t index = 0u; index < (uint16_t)TEMPERATURE_HISTOGRAM_COUNTER_SIZE; index++)
                {
                    response = bufferMethods_copyValueToBufferBigEndian_u32(minHistogramBuffer[index], response);
                    response = bufferMethods_copyValueToBufferBigEndian_u32(maxHistogramBuffer[index], response);
                    response = bufferMethods_copyValueToBufferBigEndian_u32(avgHistogramBuffer[index], response);
                }
            }
        }
    }
    return errorCode;
}

// @req CB-78755
static UDS_ErrorCode startRoutineU_t_module_histogram_downscaled(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode error = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(error == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength >= 25u);
        *responseIndex += 25u;
        const uint8_t cscAddress = *option - 1u;
        if(cscAddress >= BMS_CONFIG_NUMBER_OF_SLAVES)
        {
            error = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            uint16_t size                   = 0;
            const uint32_t* histogramBuffer = (const uint32_t*)downscaledVoltageTemperatureHistogram_getHistogram(cscAddress, &size);
            if((size > DOWNSCALED_VOLTAGE_TEMPERATURE_HISTOGRAMM_COUNTER_SIZE)
               || (((size * sizeof(uint32_t)) + optionLength) > 25u))
            {
                error = UDS_ERR_CODE_RESP_TOO_LONG;
            }
            else
            {
                response = bufferMethods_copyValueToBuffer_u8(*option, response);
                for(uint16_t index = 0u; index < (uint16_t)DOWNSCALED_VOLTAGE_TEMPERATURE_HISTOGRAMM_COUNTER_SIZE; index++)
                {
                    response = bufferMethods_copyValueToBufferBigEndian_u32(histogramBuffer[index], response);
                }
            }
        }
    }
    return error;
}

// @req CB-78746
static UDS_ErrorCode startRoutineHeating_histogram(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength >= 25u);
        *responseIndex += 25u;
        const uint8_t cscAddress = *option - 1u;
        if(cscAddress >= BMS_CONFIG_NUMBER_OF_SLAVES)
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            uint16_t size                          = 0;
            const uint32_t* heatingHistogramBuffer = (const uint32_t*)heatingCurrentHistogram_getHistogram(cscAddress, &size);
            if((size > HEATING_CURRENT_HISTOGRAM_COUNTER_SIZE)
               || (((size * sizeof(uint32_t)) + optionLength) > 25u))
            {
                errorCode = UDS_ERR_CODE_RESP_TOO_LONG;
            }
            else
            {
                response = bufferMethods_copyValueToBuffer_u8(*option, response);
                for(uint16_t index = 0u; index < size; index++)
                {
                    response = bufferMethods_copyValueToBufferBigEndian_u32(heatingHistogramBuffer[index], response);
                }
            }
        }
    }
    return errorCode;
}

static UDS_ErrorCode startRoutineHeating_histogram_downscaled(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        errorCode = UDS_ERR_CODE_SERVICE_NOT_SUPPORTED;
    }
    return errorCode;
}

// @req CB-89472
static UDS_ErrorCode startRoutineI_T_histogram(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength >= 25u);
        *responseIndex += 25u;
        const uint8_t cscAddress = *option - 1u;
        if(cscAddress >= BMS_CONFIG_NUMBER_OF_SLAVES)
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            uint16_t size                          = 0;
            const uint32_t* heatingHistogramBuffer = (const uint32_t*)downscaledCurrentViolationHistogram_getHistogram(cscAddress, &size);
            if((size > HEATING_CURRENT_HISTOGRAM_COUNTER_SIZE)
               || (((size * sizeof(uint32_t)) + optionLength) > 25u))
            {
                errorCode = UDS_ERR_CODE_RESP_TOO_LONG;
            }
            else
            {
                response = bufferMethods_copyValueToBuffer_u8(*option, response);
                for(uint16_t index = 0u; index < size; index++)
                {
                    response = bufferMethods_copyValueToBufferBigEndian_u32(heatingHistogramBuffer[index], response);
                }
            }
        }
    }
    return errorCode;
}

static UDS_ErrorCode startRoutineCycle_counter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        response[0] = option[0];  // module index
        *responseIndex += 1u;
        errorCode = UDS_ERR_CODE_SERVICE_NOT_SUPPORTED;
    }
    return errorCode;
}

static UDS_ErrorCode startRoutineEnergy_counter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        response[0] = option[0];  // module index
        *responseIndex += 1u;
        errorCode = UDS_ERR_CODE_SERVICE_NOT_SUPPORTED;
    }
    return errorCode;
}

// @req CB-79127
static UDS_ErrorCode startRoutineDeep_discharge_flag(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if((optionLength != 1u) || (responseLength < 2u))
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    if(UDS_ERR_CODE_OK == errorCode)
    {
        if((*option == 0u) || (*option > BMS_CONFIG_NUMBER_OF_SLAVES))
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
    }
    if(errorCode == UDS_ERR_CODE_OK)
    {
        response[0] = *option;
        response[1] = (cscNvm_getDeepDischargeFlag(*option) == true) ? 5u : 3u;
        *responseIndex += 2u;
    }
    return errorCode;
}
// @req CB-79128
static UDS_ErrorCode startRoutineCell_voltages(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = ((optionLength != 1u) || (responseLength <= 31u)) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength > 31u);
        *responseIndex += 31u;
        const uint8_t cscAddress = *option - 1u;
        if(cscAddress >= BMS_CONFIG_NUMBER_OF_SLAVES)
        {
            logging_info("routine requested %d\n", cscAddress);
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            response[0] = option[0];  // module index
            for(uint8_t i = 0u; i < CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL; i++)
            {
                bufferMethods_copyValueToBufferBigEndian_u16(cellVoltageMeasurement_getValue(cscAddress, i), &response[(i * 2u) + 1u]);
            }
            bufferMethods_copyValueToBufferBigEndian_u16(moduleVoltageMeasurement_getValue(cscAddress), &response[29]);
        }
    }
    return errorCode;
}
// @req CB-79129
static UDS_ErrorCode startRoutineTemperatures(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = ((optionLength != 1u) || (responseLength <= 17u)) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;
    if(errorCode == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength > 17u);
        *responseIndex += 17u;
        const uint8_t cscAddress = *option - 1u;
        if(cscAddress >= BMS_CONFIG_NUMBER_OF_SLAVES)
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            response = bufferMethods_copyValueToBuffer_u8((uint8_t)(*option), response);

#if BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS > 0
            const int16_t* terminalTemperatures = terminalTemperatureMeasurement_getTerminalTemperatures(cscAddress);
            response                            = bufferMethods_copyValueToBufferBigEndian_s16(terminalTemperatures[0], response);
#else
            response = bufferMethods_copyValueToBufferBigEndian_s16(0x7FFF, response);
#endif

            for(uint8_t temperatureSensor = 0u; temperatureSensor < BMS_CONFIG_NUMBER_OF_TEMPERATURE_SENSORS; temperatureSensor++)
            {
                response = bufferMethods_copyValueToBufferBigEndian_s16(cellTemperatureMeasurement_getValue(cscAddress, temperatureSensor), response);
            }
#if BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS > 1
            response = bufferMethods_copyValueToBufferBigEndian_s16(terminalTemperatures[1], response);
#else
            response = bufferMethods_copyValueToBufferBigEndian_s16(0x7FFF, response);
#endif
            for(uint8_t temperatureNotConnected = 0u; temperatureNotConnected < (AFE_MC33771_MAX_NUMBER_OF_TEMP_SENSORS - BMS_CONFIG_NUMBER_OF_TEMPERATURE_SENSORS - BMS_CONFIG_NUMBER_OF_BALANCING_TEMPERATURE_SENSORS - BMS_CONFIG_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS); temperatureNotConnected++)
            {
                response = bufferMethods_copyValueToBufferBigEndian_s16(0x7FFF, response);
            }
            bufferMethods_copyValueToBufferBigEndian_s16(afeTemperatureMeasurement_getValue(cscAddress), response);
        }
    }
    return errorCode;
}

static UDS_ErrorCode startRoutineBalancing_status(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        DEBUG_ASSERT(responseLength > 15u);
        *responseIndex += 15u;
        const uint8_t cscAddress        = *option - 1u;
        uint16_t balancingStatusBitmask = subMasterBalancing_getCellBalancingStatusValue(cscAddress);
        response[0]                     = option[0];  // module index
        for(uint8_t i = 0u; i < AFE_MAX_NUMBER_OF_CELLS; i++)
        {
            response[i + 1u] = (uint8_t)((balancingStatusBitmask >> i) & 0x01u);
        }
    }
    return errorCode;
}

static UDS_ErrorCode startRoutineHeating_current(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if((optionLength != 1u) || (responseLength < 5u))
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if((*option > BMS_CONFIG_NUMBER_OF_SLAVES) || (*option == 0u))
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    else
    {
        uint16_t size;
        const int32_t* heatingCurrentBuffer = heatingCurrentMeasurement_getCurrents(&size);

        uint8_t index = *option - 1u;

        response = bufferMethods_copyValueToBuffer_u8((uint8_t)(*option), response);
        bufferMethods_copyValueToBufferBigEndian_s32(heatingCurrentBuffer[index], response);
        *responseIndex += 5u;
    }
    return errorCode;
}

static UDS_ErrorCode startRoutineRead_csc_pcb_identification(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if((optionLength != 1u) || (responseLength < 7u))
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }

    if(UDS_ERR_CODE_OK == errorCode)
    {
        if((*option > BMS_CONFIG_NUMBER_OF_SLAVES) || (*option == 0u))
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
    }

    if(errorCode == UDS_ERR_CODE_OK)
    {
        response[0] = *option;

        uint16_t cscPcbHardwareVersion = cscNvm_getCscPcbHardwareVersion(*option);
        response[1]                    = ((cscPcbHardwareVersion >> 8u) & 0xFFu);
        response[2]                    = (cscPcbHardwareVersion & 0xFFu);

        cscNvm_getCSCPcbKbsSerialNumber(&response[3], *option);
        *responseIndex += 9u;
    }

    return errorCode;
}

static UDS_ErrorCode startRoutineRead_csc_parameter_bandende(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if((optionLength != 1u) || (responseLength < (4u + CSC_NVM_CSC_PCB_KBS_SERIAL_NUMBER_LENGTH)))
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if((*option > BMS_CONFIG_NUMBER_OF_SLAVES) || (*option == 0u))
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    else
    {
        response = bufferMethods_copyValueToBuffer_u8((uint8_t)(*option), response);
        response = bufferMethods_copyValueToBufferBigEndian_u16(cscNvm_getModuleNominalVoltage(*option), response);
        cscNvm_getCSCPcbKbsSerialNumber(&response[3], *option);
        response += CSC_NVM_CSC_PCB_KBS_SERIAL_NUMBER_LENGTH;
        bufferMethods_copyValueToBuffer_u8(cscNvm_getEolTestResult(*option), response);
        *responseIndex += (4u + CSC_NVM_CSC_PCB_KBS_SERIAL_NUMBER_LENGTH);
    }
    return errorCode;
}

static UDS_ErrorCode startRoutine_lib_heating_manual_control_activate(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if((optionLength != 1u) || (responseLength < 1u))
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if((*option > BMS_CONFIG_NUMBER_OF_SLAVES) || (*option == 0u))
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    else
    {
        uint8_t csc = *option - 1u;
        for(uint8_t gpio = 0; gpio < AFE_MC33771_MAX_NUMBER_OF_TEMP_SENSORS; gpio++)
        {
            if(((AFE_CONNECTED_GPIO_OUTPUTS >> gpio) & 1u) == 1u)
            {
                afeComProcedure_setRequiredGpioState(csc, gpio, IO_HIGH_STATE);
            }
        }

        bufferMethods_copyValueToBuffer_u8((uint8_t)(*option), response);
        *responseIndex += 1u;
    }
    return errorCode;
}

static UDS_ErrorCode startRoutine_lib_heating_manual_control_deactivate(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if((optionLength != 1u) || (responseLength < 1u))
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if((*option > BMS_CONFIG_NUMBER_OF_SLAVES) || (*option == 0u))
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    else
    {
        uint8_t csc = *option - 1u;
        for(uint8_t gpio = 0; gpio < AFE_MC33771_MAX_NUMBER_OF_TEMP_SENSORS; gpio++)
        {
            if(((AFE_CONNECTED_GPIO_OUTPUTS >> gpio) & 1u) == 1u)
            {
                afeComProcedure_setRequiredGpioState(csc, gpio, IO_LOW_STATE);
            }
        }

        bufferMethods_copyValueToBuffer_u8((uint8_t)(*option), response);
        *responseIndex += 1u;
    }
    return errorCode;
}

static UDS_ErrorCode startRoutineWrite_csc_pcb_identification(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if(optionLength != 7u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }

    if(errorCode == UDS_ERR_CODE_OK)
    {
        const uint8_t cscAddress = option[0];
        if(cscAddress == 0xFFu)
        {
            uint16_t cscPcbHardwareVersion = (option[1] << 8u) + option[2];
            for(uint8_t csc = 1; csc <= BMS_CONFIG_NUMBER_OF_SLAVES; csc++)
            {
                cscNvm_setCscPcbHardwareVersion(cscPcbHardwareVersion, csc);
                cscNvm_setCSCPcbKbsSerialNumber(&option[3], CSC_NVM_CSC_PCB_KBS_SERIAL_NUMBER_LENGTH, csc);
            }
        }
        else if((cscAddress > 0u) && (cscAddress <= BMS_CONFIG_NUMBER_OF_SLAVES))
        {
            uint16_t cscPcbHardwareVersion = (option[1] << 8u) + option[2];
            cscNvm_setCscPcbHardwareVersion(cscPcbHardwareVersion, cscAddress);
            cscNvm_setCSCPcbKbsSerialNumber(&option[3], CSC_NVM_CSC_PCB_KBS_SERIAL_NUMBER_LENGTH, cscAddress);
        }
        else
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
    }

    return errorCode;
}

static UDS_ErrorCode startRoutineWrite_csc_parameter_bandende(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if((optionLength != 1u) || (responseLength < 1u))
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if((*option > BMS_CONFIG_NUMBER_OF_SLAVES) || (*option == 0u))
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    else
    {
        uint8_t cscAddress = bufferMethods_getValueFromBufferBigEndian_u8(&option[0]);
        bool writeSuccess  = cscNvm_setModuleNominalVoltage(bufferMethods_getValueFromBufferBigEndian_u16(&option[1]), cscAddress);
        writeSuccess       = cscNvm_setCSCPcbKbsSerialNumber(&option[3], CSC_NVM_CSC_PCB_KBS_SERIAL_NUMBER_LENGTH, cscAddress);
        writeSuccess       = cscNvm_setEolTestResult(bufferMethods_getValueFromBufferBigEndian_u8(&option[(3u + CSC_NVM_CSC_PCB_KBS_SERIAL_NUMBER_LENGTH)]), cscAddress);
        if(writeSuccess == false)
        {
            errorCode = UDS_ERR_CODE_GENERAL_PROGRAMM_ERR;
        }
        else
        {
            response[0] = *option;
            *responseIndex += 1u;
        }
    }
    return errorCode;
}

static UDS_ErrorCode startRoutineWrite_module_aging(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u);
    UDS_ErrorCode errorCode = (optionLength != 1u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        response[0] = option[0];  // module index
        *responseIndex += 1u;
        errorCode = UDS_ERR_CODE_SERVICE_NOT_SUPPORTED;
    }
    return errorCode;
}

static UDS_ErrorCode udsRoutineSlaveRoutineResetModuleHistogramData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    uint8_t moduleNumber    = *option;
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if(optionLength != 1u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if(moduleNumber == 0u)
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    else if((moduleNumber <= BMS_CONFIG_NUMBER_OF_SLAVES) || (moduleNumber == 255u))
    {
        response[0] = *option;
        *responseIndex += 1u;
    }
    else
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    return errorCode;
}

static UDS_ErrorCode udsRoutineSlaveRoutineResetEventData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    uint8_t moduleNumber    = *option;
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if(optionLength != 1u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if(moduleNumber == 0u)
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    else if((moduleNumber <= BMS_CONFIG_NUMBER_OF_SLAVES) || (moduleNumber == 255u))
    {

        response[0] = *option;
        *responseIndex += 1u;
    }
    else
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    return errorCode;
}

static UDS_ErrorCode startRoutineResetCycle_counter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    uint8_t moduleNumber    = *option;
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if(optionLength != 1u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if(moduleNumber == 0u)
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    else if((moduleNumber <= BMS_CONFIG_NUMBER_OF_SLAVES) || (moduleNumber == 255u))
    {

        response[0] = *option;
        *responseIndex += 1u;
    }
    else
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    return errorCode;
}

static UDS_ErrorCode udsRoutineCscRoutineResetEnergyData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    uint8_t moduleNumber    = *option;
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if(optionLength != 1u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if(moduleNumber == 0u)
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    else if((moduleNumber <= BMS_CONFIG_NUMBER_OF_SLAVES) || (moduleNumber == 255u))
    {

        response[0] = *option;
        *responseIndex += 1u;
    }
    else
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    return errorCode;
}

// @req CB-79166
static UDS_ErrorCode startRoutineResetDeepDischarge(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    DEBUG_ASSERT(optionLength == 1u)

    const uint8_t cscAddress = *option;

    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if(optionLength != 1u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if(cscAddress == 0xFFu)
    {
        response[0] = option[0];  // module index
        *responseIndex += 1u;
        for(uint8_t i = 1; i <= BMS_CONFIG_NUMBER_OF_SLAVES; i++)
        {
            cscNvm_setDeepDischargeFlag(false, i);
        }
    }
    else if((cscAddress > 0u) && (cscAddress <= BMS_CONFIG_NUMBER_OF_SLAVES))
    {
        response[0] = option[0];  // module index
        *responseIndex += 1u;

        cscNvm_setDeepDischargeFlag(false, cscAddress);
    }
    else
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    return errorCode;
}

static UDS_ErrorCode udsRoutineSlaveRoutineResetComplete(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    uint8_t moduleNumber    = *option;
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;

    if(optionLength != 1u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else if(moduleNumber == 0u)
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    else if((moduleNumber <= BMS_CONFIG_NUMBER_OF_SLAVES) || (moduleNumber == 255u))
    {

        response[0] = *option;
        *responseIndex += 1u;
    }
    else
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    return errorCode;
}

// @req CB-74631
// @req CB-74632
// @req CB-74633
// @req CB-74635
// @req CB-74637
// @req CB-74638
// @req CB-74641
// @req CB-75303
// @req CB-75304
// @req CB-75305
// @req CB-75306
// @req CB-75307
// @req CB-75334
// @req CB-75335
static UDS_ErrorCode uds_routineControl_CheckProgrammingPreconditions(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode status = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(status == UDS_ERR_CODE_OK)
    {
        if(systemMasterInfoReceive_areAllSafetyRelaysOpen() == true)
        {
            preconditionsChecked = true;
        }
        else
        {
            status    = UDS_ERR_CODE_COND_NOT_CORRECT;
            *response = BATTERY_MAIN_CONTACTOR_CLOSED;
            *responseIndex += 1u;
        }
    }

    return status;
}

// @req CB-73817 CB-73826 CB-73848 CB-73859 CB-73885 CB-73907 CB-74187
static UDS_ErrorCode uds_routineControl_EraseUserMemoryDTCs(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode status = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(status == UDS_ERR_CODE_OK)
    {
        *response = CORRECT_RESULT;
    }
    else
    {
        *response = INCORRECT_RESULT;
    }
    *responseIndex += 1u;

    return status;
}

static UDS_ErrorCode uds_routineControl_ResetToDefaultSettings(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode status = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(status == UDS_ERR_CODE_OK)
    {
        *response = CORRECT_RESULT;
    }
    else
    {
        *response = INCORRECT_RESULT;
    }
    *responseIndex += 1u;

    return status;
}

static UDS_ErrorCode uds_routineControl_ResetToFactorySettings(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode status = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(status == UDS_ERR_CODE_OK)
    {
        *response = CORRECT_RESULT;
    }
    else
    {
        *response = INCORRECT_RESULT;
    }
    *responseIndex += 1u;

    return status;
}


static UDS_ErrorCode startRoutineICDreset(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = ((optionLength != 1u) || (option == NULL)) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if((errorCode == UDS_ERR_CODE_OK) && ((*option < 1u) || (*option > 2u)))
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    if(errorCode == UDS_ERR_CODE_OK)
    {
        icdaSensor_startResetRoutine(*option);
    }

    // TODO response

    return errorCode;
}

// @req CB-88856
static UDS_ErrorCode startRoutineICDClearStatus(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        icdaSensor_requestMessageWithoutOption(ICDA_MUX_ID_REQUEST_CLEAR_STATUS_BITS);
    }

    // TODO response

    return errorCode;
}

// @req CB-88854
static UDS_ErrorCode startRoutineICDClearEventCounter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        icdaSensor_requestMessageWithoutOption(ICDA_MUX_ID_REQUEST_CLEAR_EVENT_COUNTER);
    }

    // TODO response

    return errorCode;
}

// @req CB-88852
static UDS_ErrorCode startRoutineICDGetEventCounter(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = ((optionLength != 2u) || (option == NULL) || (responseLength <= 6u)) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    // Measurements status
    if((errorCode == UDS_ERR_CODE_OK) && ((option[0] < 1u) || (option[0] > 10u)))
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    // System status
    if((errorCode == UDS_ERR_CODE_OK) && (icdaSensor_validateSystemStatusOption(option[1]) == false))
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    if(errorCode == UDS_ERR_CODE_OK)
    {
        *responseIndex += 6u;
        ICDASensor_eventCounter icdEventCounter = icdaSensor_requestEventCounter(option[0], option[1]);

        if(icdEventCounter.dataReceived == false)
        {
            errorCode = UDS_ERR_CODE_RESP_PENDING;
        }
        else
        {
            response[0] = icdEventCounter.measurementEventCounter;
            response[1] = icdEventCounter.systemEventCounter;
            bufferMethods_copyValueToBufferBigEndian_u16(icdEventCounter.eventCounterValueMeasurement, &response[2]);
            bufferMethods_copyValueToBufferBigEndian_u16(icdEventCounter.eventCoutnerValueSystem, &response[4]);
        }
    }

    return errorCode;
}

#if defined(BMS_CONFIG_TASK_PERFORMACE_MEASUREMENT)
static UDS_ErrorCode startRoutineAfeTaskSubmoduleTimings(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = ((optionLength != 1u) || (option == NULL) || (responseLength <= 12u)) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if((errorCode == UDS_ERR_CODE_OK) && (option[0] >= AFE_SUBROUTINE_SIZE))
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    if(errorCode == UDS_ERR_CODE_OK)
    {
        *responseIndex += 12u;
        TaskPerformanceMeasurement_SubroutineDiagnosisInfo afeSubmoduleTimings = *afeTask_getSubmoduleTimings((AfeCheckSubroutines)option[0]);
        bufferMethods_copyValueToBufferBigEndian_u32(afeSubmoduleTimings.subroutineMinMeasuredTime, &response[0]);
        bufferMethods_copyValueToBufferBigEndian_u32(afeSubmoduleTimings.subroutineMaxMeasuredTime, &response[4]);
        bufferMethods_copyValueToBufferBigEndian_u32(afeSubmoduleTimings.subroutineAvgMeasuredTime, &response[8]);
    }
    return errorCode;
}

static UDS_ErrorCode startRoutineAfeTaskSubmoduleOSTimings(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = ((optionLength != 1u) || (option == NULL) || (responseLength <= 6u)) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if((errorCode == UDS_ERR_CODE_OK) && (option[0] >= AFE_SUBROUTINE_SIZE))
    {
        errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
    if(errorCode == UDS_ERR_CODE_OK)
    {
        *responseIndex += 6u;
        uint16_t timeValue = afeCheck_getSubmoduleOSTimings((AfeCheckSmIdentifier)option[0], MIN_MEASURED_TIME);
        bufferMethods_copyValueToBufferBigEndian_u16(timeValue, &response[0]);
        timeValue = afeCheck_getSubmoduleOSTimings((AfeCheckSmIdentifier)option[0], MAX_MEASURED_TIME);
        bufferMethods_copyValueToBufferBigEndian_u16(timeValue, &response[2]);
        timeValue = afeCheck_getSubmoduleOSTimings((AfeCheckSmIdentifier)option[0], LAST_MEASURED_TIME);
        bufferMethods_copyValueToBufferBigEndian_u16(timeValue, &response[4]);
    }
    return errorCode;
}
#endif

#if defined(HIL_CONFIGURATION) || defined(SIL_DEBUG)
static UDS_ErrorCode startRoutineResetWriteOnceData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        vehicleManufacturerData_resetVinAvailabilityWrittenAlready();
    }

    return errorCode;
}

static UDS_ErrorCode startRoutineResetIcdaAfeSynchronizationData(const uint8_t* option, uint16_t optionLength, uint8_t* response, uint16_t responseLength, uint16_t* responseIndex)
{
    UDS_ErrorCode errorCode = (optionLength != 0u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        synchronizedMeasurements_resetSyncMeasurementsValues();
    }
    return errorCode;
}
#endif

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

bool uds_routineControl_getPreconditionsChecked(void)
{
    return preconditionsChecked;
}

const UDS_RoutineControlEntry routineControlTable_common[] = {

};

const uint16_t UDS_ROUTINE_CONTROL_COMMON_TABLE_SIZE = sizeof(routineControlTable_common) / sizeof(UDS_RoutineControlEntry);

// clang-format off
const UDS_RoutineControlEntry routineControlTable_project[] = {
/*    ID ------------------------------------------------------- Start Function----------------------------------- STOP ------------------------------- RES - Security Level ------------------------------------------------------- Session ---------------- Session length -------------- */
    { UDS_ROUTINE_ERASE_USER_MEMORY_DTCS,                        uds_routineControl_EraseUserMemoryDTCs,            NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_RESET_TO_DEFAULT_SETTINGS,                     uds_routineControl_ResetToDefaultSettings,         NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_CHECK_PROGRAMMING_PRECONDITIONS,               uds_routineControl_CheckProgrammingPreconditions,  NULL,                                NULL, 0,                                                                     uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_RESET_TO_FACTORY_SETTINGS,                     uds_routineControl_ResetToFactorySettings,         NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_ERASE_EEPROM,                                  udsRoutineControlEraseEepromStart,                 NULL,                                NULL, BIT(UDS_SECURITY_LEVEL_INTERNAL),                                      NULL,                    NULL                          },
    { UDS_ROUTINE_CLEAR_TASK_PERFORMANCE_DATA_NVM,               udsRoutineControlClearTaskPerformanceNvmData,      NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_RESET_BATTERY_HISTOGRAMS,               udsRoutineMasterRoutineResetBatteryHistogramData,  NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_RESET_MODULE_HISTOGRAMS,                udsRoutineMasterRoutineResetModuleHistogramData,   NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_RESET_TIMER_DATA,               udsRoutineMasterRoutineResetTimerData,             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_RESET_EVENT_DATA,               udsRoutineMasterRoutineResetEventData,             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_RESET_COUNTER_DATA,             dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_RESET_CYCLE_DATA,               dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_RESET_ENERGY_DATA,              udsRoutineMasterRoutineResetEnergyCounter,         NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_RESET_ERROR_COUNTER,            dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_RESET_COMPLETE,                 dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_RESET_IRREVERSIBLE_ERROR,       dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_RESET_CONTACTOR_HISTOGRAMS,             udsRoutineMasterRoutineResetContactorHistograms,   NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_CAPACITY_MEASUREMENT,           dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_POWERPATH_CONNECTION_ANALYSIS,  dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_INITIATE_DATA_RECOVERY_BATTERY, dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_UPDATE_RECOVERY_DATA,           dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_SOC_REFERENCE,                  dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_LIB_TURN_ON_KION,                              dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_LIB_TURN_OFF_KION,                             dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_START_CPS_OUT_CONTROL,                  udsRoutineMasterRoutineStartCPSoutControl,         NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_START_CPS_POWER_DOWN,                   udsRoutineMasterRoutineStartCPSPowerDown,          NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_ROUTINE_REST_SOH,                       dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_MASTER_SET_TO_DEFAULT,                         dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_SLAVE_RESET_HISTOGRAMS,                        udsRoutineSlaveRoutineResetModuleHistogramData,    NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_SLAVE_ROUTINE_RESET_EVENT_DATA,                udsRoutineSlaveRoutineResetEventData,              NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_SLAVE_ROUTINE_RESET_CYCLE_DATA,                startRoutineResetCycle_counter,                    NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_SLAVE_ROUTINE_RESET_ENERGY_DATA,               udsRoutineCscRoutineResetEnergyData,               NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_SLAVE_ROUTINE_RESET_DEEP_DISCHARGE_FLAG,       startRoutineResetDeepDischarge,                    NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_SLAVE_ROUTINE_RESET_COMPLETE,                  udsRoutineSlaveRoutineResetComplete,               NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_CYCLE_COUNTER,                                 startRoutineCycle_counter,                         NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_ENERGY_COUNTER,                                startRoutineEnergy_counter,                        NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_DEEP_DISCHARGE_FLAG,                           startRoutineDeep_discharge_flag,                   NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_CELL_VOLTAGES,                                 startRoutineCell_voltages,                         NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_TEMPERATURES,                                  startRoutineTemperatures,                          NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_BALANCING_STATUS,                              startRoutineBalancing_status,                      NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_HEATING_CURRENT,                               startRoutineHeating_current,                       NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_READ_CSC_PCB_IDENTIFICATION,                   startRoutineRead_csc_pcb_identification,           NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_READ_CSC_PARAMETER_BANDENDE,                   startRoutineRead_csc_parameter_bandende,           NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_WRITE_CSC_PCB_IDENTIFICATION,                  startRoutineWrite_csc_pcb_identification,          NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_WRITE_CSC_PARAMETER_BANDENDE,                  startRoutineWrite_csc_parameter_bandende,          NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_WRITE_MODULE_AGING,                            startRoutineWrite_module_aging,                    NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_HEATING_FOIL,                                  dummy_routine_control,                             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_LIB_HEATING_MANUAL_CONTROL_ACTIVATE,           startRoutine_lib_heating_manual_control_activate,  NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_LIB_HEATING_MANUAL_CONTROL_DEACTIVATE,         startRoutine_lib_heating_manual_control_deactivate,NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_U_CELL_HISTOGRAM_OP,                           startRoutineU_cell_histogram_op,                   NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_U_CELL_HISTOGRAM_ST,                           startRoutineU_cell_histogram_st,                   NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_U_LOW_VIOLATION_HISTOGRAM,                     startRoutineU_low_violation_histogram,             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_U_HIGH_VIOLATION_HISTOGRAM,                    startRoutineU_high_violation_histogram,            NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_T_HISTOGRAM_OP,                                startRoutineT_histogram_op,                        NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_T_HISTOGRAM_ST,                                startRoutineT_histogram_st,                        NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_U_T_MODULE_HISTOGRAM_DOWNSCALED,               startRoutineU_t_module_histogram_downscaled,       NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_HEATING_HISTOGRAM,                             startRoutineHeating_histogram,                     NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_HEATING_HISTOGRAM_DOWNSCALED,                  startRoutineHeating_histogram_downscaled,          NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_I_T_HISTOGRAM,                                 startRoutineI_T_histogram,                         NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    // ICDA routines
    { UDS_ROUTINE_ICD_RESET,                                     startRoutineICDreset,                              NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_ICD_CLEAR_STATUS,                              startRoutineICDClearStatus,                        NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_ICD_CLEAR_EVENT_COUNTER,                       startRoutineICDClearEventCounter,                  NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_ICD_GET_EVENT_COUNTER,                         startRoutineICDGetEventCounter,                    NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
#if defined(BMS_CONFIG_TASK_PERFORMACE_MEASUREMENT)
    { UDS_ROUTINE_AFE_TASK_SUBROUTINE_TIMINGS,                   startRoutineAfeTaskSubmoduleTimings,               NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    { UDS_ROUTINE_AFE_TASK_SUBROUTINE_OS_TIMINGS,                startRoutineAfeTaskSubmoduleOSTimings,             NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
#endif
#if defined(HIL_CONFIGURATION) || defined(SIL_DEBUG)
    {UDS_ROUTINE_RESET_WRITE_ONCE_DATA,                         startRoutineResetWriteOnceData,                     NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
    {UDS_ROUTINE_RESET_ICDA_AFE_SYNCHRONIZATION_DATA,           startRoutineResetIcdaAfeSynchronizationData,        NULL,                                NULL, (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2)), uds_extendedSessionList, &UDS_EXTENDEDSESSIONLIST_SIZE },
#endif
};
// clang-format on
const uint16_t UDS_ROUTINE_CONTROL_PROJECT_TABLE_SIZE = sizeof(routineControlTable_project) / sizeof(UDS_RoutineControlEntry);
