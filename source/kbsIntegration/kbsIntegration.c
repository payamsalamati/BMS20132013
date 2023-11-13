/**
 * @file kbsIntegration.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "kbsIntegration.h"

#include "KBSInterface.h"
#include "task_cfg.h"
#include "uds.h"
#include "uds_protected.h"
#include "uds_config.h"
#include "sdo.h"

#include "libIdentification.h"
#include "debug.h"
#include "cellVoltageMeasurement.h"
#include "batteryCurrentMeasurement.h"
#include "cellTemperatureMeasurement.h"
#if BMS_CONFIG_MAX_NUMBER_OF_BALANCING_TEMPERATURE_SENSORS > 0
#include "balancingTemperatureMeasurement.h"
#endif
#include "highVoltageMeasurement.h"
#include "icdaSensor.h"
#include "safetyAfeValueMeasurement.h"

#include "dem.h"
#include "afeComProcedure.h"
#include "xcpIf.h"
#include "canData.h"
#include "measurements_getOnBoardTemperature.h"
#include "diagnosticTimes.h"
#include "timestamp.h"
#include "systemMasterBalancing.h"
#include "subMasterBalancing.h"
#include "shutdownTimeMeasurement.h"
#include "cscNvm_config.h"
#include "stateFunctions.h"
#include "nvm.h"
#include "cps.h"
#include "cscNvm.h"
#include "mutexMonitor.h"
#include "spiIf_config.h"

#if !defined(UNIT_TEST)
#include "module_config.h"
#include "csc_config.h"
#include "KionStateMachine.h"
#include "afe_MC33771_common_config.h"
#else
#include "test_kbsIntegration_config.h"
#endif

#include "synchronizedMeasurements.h"
#include "afeComProcedure.h"
#include "terminalTemperatureMeasurement.h"
#include "protocolInterface.h"
#include "heatingCurrentMeasurement.h"
//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct KBSIntegration
{
    uint32_t timestamp10;
    uint32_t timestamp100;
    uint32_t timestamp1000;
    uint16_t counter1000;
    bool kbsMutexInitialized;
} KBSIntegration;

typedef struct KBSIntegrationParameter
{
    uint16_t socDOD;
    uint16_t socEOC;
    uint8_t diagDerating;
    uint16_t heatingStatusCurrentThresholdInmA;
} KBSIntegrationParameter;

#define CURRENTDERATING_DEFAULT_DIAG_DERATING 100u
#define SOC_DEFAULT_DEPTH_OF_DISCHARGE        900u
#define SOC_DEFAULT_END_OF_CHARGE             950u


#define KBS_INTERFACE_UDS_ID_START  0x8200
#define KBS_INTERFACE_UDS_ID_END    0xA5FF
#define KBS_INTERFACE_UDS_ID_START2 0xFD00
#define KBS_INTERFACE_UDS_ID_END2   0xFEFF

#define KBS_INTERFACE_UDS_ROUTINE_ID_START  0x1000
#define KBS_INTERFACE_UDS_ROUTINE_ID_END    0x9FFF
#define KBS_INTERFACE_UDS_ROUTINE_ID_START2 0xFD00
#define KBS_INTERFACE_UDS_ROUTINE_ID_END2   0xFEFF

#define KBS_INTERFACE_SDO_START 0x4450
#define KBS_INTERFACE_SDO_END   0x5FFF
#define KBS_INTERFACE_SDO_2     0x4209

// @req CB-94251
#define KBS_INTEGRATION_DEFAULT_HEATING_STATUS_CURRENT_THRESHOLD_IN_mA 500u

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static void kbsIntegrationFillInput(void);
static ENUM_STATE_BMS getKBSBMSState(void);
STATIC uint8_t getDeratingFactor(void);

static void kbsIntegrationUdsRoutineControl(const uint8_t* buf, uint16_t length, bool functionalAddressing);
static void kbsIntegrationEventMonitorCheck(void);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

#if !defined(SIL_DEBUG)
MEM_APPLICATION KBSInput kbsInput;
MEM_APPLICATION KBSOutput kbsOutput;
#else
__attribute__((section("A2L"))) volatile KBSInput kbsInput;
__attribute__((section("A2L"))) volatile KBSOutput kbsOutput;
#endif

MEM_APPLICATION KBSIntegration kbsIntegration = { 0 };

// @req CB-91894
MEM_APPLICATION uint8_t kbsIntegrationCscNvmCache[(BMS_CONFIG_MAX_NUMBER_OF_SLAVES * CSC_NVM_KBS_CSC_NVM_DATA_LENGTH)] = { 0 };

// @req CB-91981 CB-91980 CB-91979 CB-91984 CB-91982 CB-91983
MEM_APPLICATION eventMonitor kbsMonitor      = { 0 };
const uint16_t numberMonitorEntries          = (sizeof(kbsMonitor) / sizeof(diagnosticEvent));
const DEM_FaultCode diagnosticEventDtcList[] = {
    DTC_KBS_INTERFACE_MONITOR_1,
    DTC_KBS_INTERFACE_MONITOR_2,
    DTC_KBS_INTERFACE_MONITOR_3,
    DTC_KBS_INTERFACE_MONITOR_4,
    DTC_KBS_INTERFACE_MONITOR_5,
    DTC_KBS_INTERFACE_MONITOR_6,
    DTC_KBS_INTERFACE_MONITOR_7,
    DTC_KBS_INTERFACE_MONITOR_8,
    DTC_KBS_INTERFACE_MONITOR_9,
    DTC_KBS_INTERFACE_MONITOR_10,
    DTC_KBS_INTERFACE_MONITOR_11,
    DTC_KBS_INTERFACE_MONITOR_12,
    DTC_KBS_INTERFACE_MONITOR_13,
    DTC_KBS_INTERFACE_MONITOR_14,
    DTC_KBS_INTERFACE_MONITOR_15,
    DTC_KBS_INTERFACE_MONITOR_16,
    DTC_KBS_INTERFACE_MONITOR_17,
    DTC_KBS_INTERFACE_MONITOR_18,
    DTC_KBS_INTERFACE_MONITOR_19,
    DTC_KBS_INTERFACE_MONITOR_20,
    DTC_KBS_INTERFACE_MONITOR_21,
    DTC_KBS_INTERFACE_MONITOR_22,
};
const uint16_t diagnosticEventDtcListSize = (sizeof(diagnosticEventDtcList) / sizeof(DEM_FaultCode));

MEM_SEC_PARAMETER KBSIntegrationParameter kbsIntegrationParameter = {
    .socDOD                            = SOC_DEFAULT_DEPTH_OF_DISCHARGE,
    .socEOC                            = SOC_DEFAULT_END_OF_CHARGE,
    .diagDerating                      = CURRENTDERATING_DEFAULT_DIAG_DERATING,
    .heatingStatusCurrentThresholdInmA = KBS_INTEGRATION_DEFAULT_HEATING_STATUS_CURRENT_THRESHOLD_IN_mA  // @req CB-94251
};

extern KionStateMachine SM_handle;

// makes sure that main functions are not called while NVM is written or read
MEM_SHAREDATA OSIf_Event kbsIntegrationMutex;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static ENUM_STATE_BMS getKBSBMSState(void)
{
    KionStateMachineStates state = SM_handle.stateConfVector[0];
    ENUM_STATE_BMS translation   = ENUM_STATE_BMS_INVALID;

    if(((state == kionStateMachine_CBBMS_STM_Init))
       || (state == kionStateMachine_CBBMS_STM_Authentication_Listen_to_CAN))
    {
        translation = ENUM_STATE_BMS_IDLE;
    }
    else if((state == kionStateMachine_CBBMS_STM_Protocol_Handling_Protocol_Running_Running_Ready_Settings)
            || (state == kionStateMachine_CBBMS_STM_Protocol_Handling_Protocol_Running_Running_Ready_Idle))
    {
        translation = ENUM_STATE_BMS_READY;
    }
    else if((kionStateMachine_CBBMS_STM_Periodic_Wake_Up_Periodic_Wake_Up_Periodic_Wake_Up <= state)
            && (state <= kionStateMachine_CBBMS_STM_Periodic_Wake_Up_Periodic_Wake_Up_CPS_Power_Down))
    {
        translation = ENUM_STATE_BMS_PERIODIC_WAKEUP;
    }
    else if(state == kionStateMachine_CBBMS_STM_Protocol_Handling_Protocol_Running_Running_Drive_Mode_Active_)
    {
        translation = ENUM_STATE_BMS_DRIVE;
    }
    else if(state == kionStateMachine_CBBMS_STM_Protocol_Handling_Protocol_Running_Running_Charge_Mode_Active)
    {
        translation = ENUM_STATE_BMS_CHARGE;
    }

    DEM_Severity severity = dem_getSeverityLevelOfSystem();
    if(severity == DEM_SEVERITY_EMERGENCY_CONFIRMED)
    {
        translation = ENUM_STATE_BMS_EMERGENCY;
    }
    else if(severity == DEM_SEVERITY_SAFE_STATE)
    {
        translation = ENUM_STATE_BMS_ERROR_REVERSIBLE;
    }
    else if(severity == DEM_SEVERITY_PERMANENT)
    {
        translation = ENUM_STATE_BMS_FATAL_ERROR_IRREVERSIBLE;
    }
    else
    {
        // do nothing
    }


    return translation;
}

STATIC uint8_t getDeratingFactor(void)
{
    uint8_t factor        = 100;
    DEM_Severity severity = dem_getSeverityLevelOfSystem();
    // @req CB-93294
    if(severity == DEM_SEVERITY_PENDING)
    {
        uint8_t size            = 0;
        const DEM_Fault* faults = dem_getFaultInfo(&size);
        for(uint8_t i = 0; i < size; i++)
        {
            if(faults[i].activeSeverity == DEM_SEVERITY_EMERGENCY_CONFIRMED)
            {
                factor = 50;
                break;
            }
        }
    }

    if((severity == DEM_SEVERITY_EMERGENCY_CONFIRMED) || (severity == DEM_SEVERITY_CONFIRMED))
    {
        factor = 50;
    }
    else if(severity >= DEM_SEVERITY_SAFE_STATE)
    {
        factor = 0;
    }
    else
    {
        // do nothing
    }
    return factor;
}

static void kbsIntegrationFillInput(void)
{
    uint16_t size                  = 0;
    const int32_t* heatingCurrents = heatingCurrentMeasurement_getCurrents(&size);

    // @req CB-19057 CB-92018 CB-91507
    for(uint16_t module = 0; module < MODULES_PER_BATTERY; module++)
    {
        // @req CB-18780 CB-89762
        kbsInput.heatingCurrent_Module[module] = (module < BMS_CONFIG_NUMBER_OF_SLAVES) ? heatingCurrents[module] : INT32_MAX;

        // @req CB-18779 CB-19057 CB-89130 CB-89763 CB-91805 CB-91795
        for(uint16_t cell = 0; cell < CELLS_PER_MODULE; cell++)
        {
            kbsInput.voltage_Cell[(module * CELLS_PER_MODULE) + cell] = cellVoltageMeasurement_getMaskedValue(module, cell);
            // @req CB-91253 CB-91244 CB-91234
            kbsInput.get_balancing_Cell[(module * CELLS_PER_MODULE) + cell] = (ENUM_GET_SET)((subMasterBalancing_getCellBalancingStatusValueMasked(module) >> cell) & 1);
        }

        // @req CB-18778 CB-19057 CB-89130 CB-89764 CB-91807 CB-91415 CB-92019
        for(uint16_t tempSensor = 0u; tempSensor < TEMPERATURE_SENSORS_PER_MODULE; tempSensor++)
        {
            if(tempSensor == 0u)
            {
                kbsInput.temperature_Sensor[(module * TEMPERATURE_SENSORS_PER_MODULE)] = terminalTemperatureMeasurement_getMaskedValue(module, TERMINAL_TEMP_SENSOR_1);
            }
            else if(tempSensor == (BMS_CONFIG_NUMBER_OF_TEMPERATURE_SENSORS + 1u))
            {
                kbsInput.temperature_Sensor[(module * TEMPERATURE_SENSORS_PER_MODULE) + tempSensor] = terminalTemperatureMeasurement_getMaskedValue(module, TERMINAL_TEMP_SENSOR_2);
            }
            else
            {
                kbsInput.temperature_Sensor[(module * TEMPERATURE_SENSORS_PER_MODULE) + tempSensor] = cellTemperatureMeasurement_getMaskedValue(module, (tempSensor - 1u));
            }
        }

        // @req CB-18777 CB-92006 CB-92007
        if((afeComProcedure_getCurrentGpioStates(module) == AFE_CONNECTED_GPIO_OUTPUTS)
           && (abs(kbsInput.heatingCurrent_Module[module]) > kbsIntegrationParameter.heatingStatusCurrentThresholdInmA))
        {
            kbsInput.get_heating_Module[module] = ENUM_GET_SET_ON;
        }
        else
        {
            kbsInput.get_heating_Module[module] = ENUM_GET_SET_OFF;
        }
    }

    // @req CB-18772
    kbsInput.state_BMS = getKBSBMSState();

    // @req CB-18773 CB-92004 CB-92005
    kbsInput.get_balancing_Battery = (ENUM_GET_SET)systemMasterBalancing_getMasterBalancing();

    // @req CB-18774 CB-92001 CB-92013 CB-92003 CB-92012
    kbsInput.state_Charger = (ENUM_CONNECTION)(protocolInterface_getConnectedDevice() == CHARGER);  // can sdo charge signal

    // @req CB-18775 CB-92002 CB-92014 CB-92003 CB-92012
    kbsInput.state_Truck = (ENUM_CONNECTION)(protocolInterface_getConnectedDevice() == TRUCK);  // can sdo charge signal

    // @req CB-18776
    kbsInput.get_enable_BCM = ENUM_GET_SET_OFF;  // not available

    // @req CB-18781 CB-89130 CB-91987
    kbsInput.current_Battery = synchronizedMeasurements_getSyncCurrentValue();

    // @req CB-18785 CB-89130
    kbsInput.AhCounter_CurrentSensor = icdaSensor_getAhCounter();

    // @req CB-18782
    kbsInput.current_CPS = cps_getCpsOutI() * 10u;  // convert from [10mA] to [1mA]

    // @req CB-18783 CB-91988
    kbsInput.voltageBeforeContactors = highVoltageMeasurement_getMaskedMasterHvVoltagesValue(0);

    // @req CB-91800
    kbsInput.voltageBetweenContactors = highVoltageMeasurement_getMaskedMasterHvVoltagesValue(1);

    // @req CB-18784 CB-91989
    kbsInput.voltageAfterContactors = highVoltageMeasurement_getMaskedMasterHvVoltagesValue(2);

    // @req CB-91998
    kbsInput.selfDischargeTime = shutdownTimeMeasurement_getRelativeTimeInSeconds();

    // @req CB-18787
    kbsInput.get_PWM_BCM = UINT16_MAX;  // not available

    // @req CB-18788
    kbsInput.factorPowerReduction = getDeratingFactor();  // 100%                                                   // ?

    // @req CB-91237 CB-91801
    kbsInput.chargingPower = (canData_getLibPdoRx1DataReceived() == true) ? canData_getLastLibChargingPower() : UINT32_MAX;

    // @req CB-91768 CB-92000
    kbsInput.chargingVoltage = (canData_getLibPdoRx1DataReceived() == true) ? canData_getLastLibChargingVoltage() : UINT32_MAX;

    // @req CB-91239 CB-91802
    kbsInput.chargingCurrent = (canData_getLibPdoRx1DataReceived() == true) ? canData_getLastLibChargingCurrent() : UINT32_MAX;

    // @req CB-91797
    kbsInput.avgPowerConsumption_Vehicle = (canData_getLibPdoRx4DataReceived() == true) ? canData_getLastLibPowerConsumptionAverage() : UINT32_MAX;

    // @req CB-91803
    kbsInput.workTime_Truck = (canData_getLibPdoRx4DataReceived() == true) ? canData_getLastTruckOperatingHours() : UINT32_MAX;

    // @req CB-91799
    kbsInput.temperature_MasterPCB = measurements_getOnBoardTemperature_getTSensorOnMaster();

    // @req CB-91804
    kbsInput.workTime_Component = diagnosticTimes_getDiagnosticTotalOperatingTimeIns();

    // @req CB-91806
    kbsInput.dateTime = timestamp_getUnixTime();
}

static bool isInRange(uint32_t start, uint32_t end, uint32_t value)
{
    return (value >= start) && (value <= end);
}

// @req CB-18767
static void kbsIntegrationUdsRoutineControl(const uint8_t* buf, uint16_t length, bool functionalAddressing)
{
    UDS_ErrorCode error    = UDS_ERR_CODE_OK;
    uint16_t id            = (((uint16_t)buf[2] << 8u) | buf[3]);
    uint16_t responseIndex = 0;

    if((!isInRange(KBS_INTERFACE_UDS_ROUTINE_ID_START, KBS_INTERFACE_UDS_ROUTINE_ID_END, id))
       && (!isInRange(KBS_INTERFACE_UDS_ROUTINE_ID_START2, KBS_INTERFACE_UDS_ROUTINE_ID_END2, id)))
    {
        error = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    if(UDS_ERR_CODE_OK == error)
    {
        // TODO error code muss als pointer verwendet werden und muss nach dem aufruf ausgewertet werden
        KBSInterface_UDS_routineControl((ENUM_ROUTINE_CONTROL_TYPE)buf[UDS_LEV_POS], id, &buf[4u], (length - 4u), UDS_RESPONSE_BUFFER_LENGTH - 4u, &uds_responseBuffer[4], &responseIndex, &error);
    }

    if(error == UDS_ERR_CODE_OK)
    {
        if(functionalAddressing == false)
        {
            uds_responseBuffer[0] = buf[UDS_SID_POS] + UDS_RESPONSE_POSITIVE_OFFSET;
            uds_responseBuffer[1] = buf[UDS_LEV_POS];
            uds_responseBuffer[2] = buf[2];
            uds_responseBuffer[3] = buf[3];
            uds_send(uds_responseBuffer, responseIndex + 4);
        }
    }
    else
    {
        uds_errorResponse(buf, length, error);
    }
}

// checks if DTCs inside of kbsMonitor have been set
// @req CB-91986
static void kbsIntegrationEventMonitorCheck(void)
{
    DEBUG_ASSERT(diagnosticEventDtcListSize == numberMonitorEntries);
    const diagnosticEvent* diagnosticEventsPtr = (const diagnosticEvent*)&kbsMonitor.diagnosticEvent_1;
    for(uint16_t index = 0u; index < numberMonitorEntries; index++)
    {
        if(diagnosticEventsPtr[index].status_diagnosticEvent == ENUM_DIAGNOSTIC_EVENT_FAILED)
        {
            dem_reportFaultFromApp(diagnosticEventDtcList[index]);
        }
        else
        {
            dem_clearFaultFromApp(diagnosticEventDtcList[index]);
        }
    }
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

bool kbsIntegration_isMonitorDtc(DEM_FaultCode fault)
{
    return isInRange(diagnosticEventDtcList[0], diagnosticEventDtcList[(diagnosticEventDtcListSize - 1u)], fault);
}

const uint8_t* kbsIntegration_getIndividualSnapshotOfFault(uint32_t* size, DEM_FaultCode fault)
{
    const uint8_t* retVal                = NULL;
    diagnosticEvent* diagnosticEventsPtr = (diagnosticEvent*)&kbsMonitor.diagnosticEvent_1;
    bool indexFound                      = false;
    uint16_t index                       = 0u;
    for(; (index < numberMonitorEntries) && (indexFound == false); index++)
    {
        if(diagnosticEventDtcList[index] == fault)
        {
            indexFound = true;
            break;
        }
    }
    if(indexFound == true)
    {
        *size  = diagnosticEventsPtr[index].size_individualSnapshot;
        retVal = diagnosticEventsPtr[index].data_individualSnapshot;
    }
    return retVal;
}


// @req CB-18768 CB-91303
void kbsIntegration_mainFunction_10ms(void)
{
    if(kbsIntegration.kbsMutexInitialized == false)
    {
        return;
    }
    if(osIf_mutexPend(kbsIntegrationMutex, 10) == pdPASS)
    {
        kbsIntegrationFillInput();

        // @req CB-18792 CB-91809
        kbsInput.durationLastCall_10ms = osIf_getTimeDifference(kbsIntegration.timestamp10);
        KBSInterface_main_10ms(&kbsInput, &kbsOutput, &kbsMonitor);
        kbsIntegration.timestamp10 = osIf_getOStime();
        xcpIf_event(10);


        kbsIntegrationEventMonitorCheck();

        // @req CB-18797 CB-19057 CB-91383
        for(uint16_t module = 0; module < BMS_CONFIG_NUMBER_OF_SLAVES; module++)
        {
            IO_VAL_t heating = (kbsOutput.set_heating_Module[module] == ENUM_GET_SET_ON)
                                   ? IO_HIGH_STATE
                                   : IO_LOW_STATE;
            afeComProcedure_setRequiredGpioState(module, 0, heating);
            afeComProcedure_setRequiredGpioState(module, 6, heating);
        }

        for(uint16_t kbsModule = 0; kbsModule < MODULES_PER_BATTERY; kbsModule++)
        {
            for(uint8_t cell = 0; cell < CELLS_PER_MODULE; cell++)
            {
                subMasterBalancing_setCellBalancingStatusValueByCell(kbsOutput.set_balancing_Cell[kbsModule * CELLS_PER_MODULE + cell], kbsModule, cell);
            }
        }
        osIf_mutexPost(kbsIntegrationMutex);
    }
}

void kbsIntegration_mainFunction_100ms(void)
{
    if(kbsIntegration.kbsMutexInitialized == false)
    {
        return;
    }
    if(osIf_mutexPend(kbsIntegrationMutex, 10) == pdPASS)
    {
        // @req CB-91812
        kbsInput.durationLastCall_100ms = osIf_getTimeDifference(kbsIntegration.timestamp100);
        kbsIntegration.timestamp100     = osIf_getOStime();
        KBSInterface_main_100ms(&kbsInput, &kbsOutput, &kbsMonitor);
        xcpIf_event(11);
        osIf_mutexPost(kbsIntegrationMutex);
    }
}

void kbsIntegration_mainFunction_1000ms(void)
{
    if(kbsIntegration.kbsMutexInitialized == false)
    {
        return;
    }
    if(osIf_mutexPend(kbsIntegrationMutex, 10) == pdPASS)
    {
        // @req CB-91811
        kbsInput.durationLastCall_1000ms = osIf_getTimeDifference(kbsIntegration.timestamp1000);
        KBSInterface_main_1000ms(&kbsInput, &kbsOutput, &kbsMonitor);
        kbsIntegration.timestamp1000 = osIf_getOStime();
        xcpIf_event(12);
        kbsIntegration.counter1000++;

        // @req CB-91891
        if((kbsIntegration.counter1000 % (3600)) == 0u)  // every 60min
        {
            kbsIntegration.counter1000 = 0u;
            nvm_writeBlock(NVM_KBS_INTERFACE_BLOCK_ID, NULL);
        }
        osIf_mutexPost(kbsIntegrationMutex);
    }
}

NVM_Result kbsIntegration_nvmReadCallback(const uint8_t* mirror, uint16_t length)
{
    if(kbsIntegration.kbsMutexInitialized == false)
    {
        kbsIntegrationMutex                = osIf_mutexCreate();
        kbsIntegration.kbsMutexInitialized = true;
    }
    if(osIf_mutexPend(kbsIntegrationMutex, 10) == pdPASS)
    {
        // @req CB-92023 CB-92053
        KBSInterface_initialize_ASW();
        // @req CB-18766
        // @req CB-18769 linking here because nvm config is generated
        KBSInterface_initialize_NVM_BMS(mirror, length);
        for(uint8_t cscAddress = 0u; cscAddress < BMS_CONFIG_NUMBER_OF_SLAVES; cscAddress++)
        {
            cscNvm_getKbsCscNvmData(&kbsIntegrationCscNvmCache[(cscAddress * CSC_NVM_KBS_CSC_NVM_DATA_LENGTH)], (cscAddress + 1u));
        }
        KBSInterface_initialize_NVM_CSC(&kbsIntegrationCscNvmCache[0], (BMS_CONFIG_NUMBER_OF_SLAVES * CSC_NVM_KBS_CSC_NVM_DATA_LENGTH));
        osIf_mutexPost(kbsIntegrationMutex);
    }
    return NVM_OK;
}

NVM_Result kbsIntegration_nvmWriteCallback(uint8_t* mirror, uint16_t length)
{
    if(osIf_mutexPend(kbsIntegrationMutex, 10) == pdPASS)
    {
        STMStates currentState = stmFct_getBatteryStateGlobal();
        if(currentState != State_Shutdown_Procedure)
        {
            // @req CB-91891
            KBSInterface_update_NVM(length, (BMS_CONFIG_MAX_NUMBER_OF_SLAVES * CSC_NVM_KBS_CSC_NVM_DATA_LENGTH), mirror, &kbsIntegrationCscNvmCache[0]);
        }
        else
        {
            // @req CB-18770
            KBSInterface_terminate(length, (BMS_CONFIG_MAX_NUMBER_OF_SLAVES * CSC_NVM_KBS_CSC_NVM_DATA_LENGTH), mirror, &kbsIntegrationCscNvmCache[0]);
        }
        for(uint8_t cscAddress = 0u; cscAddress < BMS_CONFIG_NUMBER_OF_SLAVES; cscAddress++)
        {
            cscNvm_setKbsCscNvmData(&kbsIntegrationCscNvmCache[(cscAddress * CSC_NVM_KBS_CSC_NVM_DATA_LENGTH)], CSC_NVM_KBS_CSC_NVM_DATA_LENGTH, (cscAddress + 1u));
        }
        cscNvm_startWriteAll();
        osIf_mutexPost(kbsIntegrationMutex);
    }
    return NVM_OK;
}


void uds_hook(const uint8_t* buf, uint16_t length, bool functionalAddressing)
{
    switch((UDS_SID)buf[UDS_SID_POS])
    {

        case UDS_SID_ROUTINE_CONTROL:
        {
            kbsIntegrationUdsRoutineControl(buf, length, functionalAddressing);
        }
        default:
            break;
    }
}

// @req CB-18762
void uds_readHook(uint16_t id, uint16_t* responseIndex, uint8_t* responseBuffer)
{
    UDS_ErrorCode error = UDS_ERR_CODE_OK;

    if((!isInRange(KBS_INTERFACE_UDS_ID_START, KBS_INTERFACE_UDS_ID_END, id))
       && (!isInRange(KBS_INTERFACE_UDS_ID_START2, KBS_INTERFACE_UDS_ID_END2, id)))
    {
        error = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    if(UDS_ERR_CODE_OK == error)
    {
        responseBuffer[0u]    = id >> 8u;
        responseBuffer[1u]    = id & 0xff;
        uint16_t responseSize = 0;

        KBSInterface_UDS_readData(id, UDS_RESPONSE_BUFFER_LENGTH - *responseIndex - 2u, &responseBuffer[2u], &responseSize, &error);
        if(UDS_ERR_CODE_OK == error)
        {
            *responseIndex += responseSize + 2u;
        }
    }
}

#if defined(UDS_WRITE_HOOK)
// @req CB-91892
void uds_writeHook(uint16_t id, const uint8_t* requestBuffer, const uint16_t* requestBufferSize, uint8_t* responseCode)
{
    *responseCode = UDS_ERR_CODE_OK;

    if((!isInRange(KBS_INTERFACE_UDS_ID_START, KBS_INTERFACE_UDS_ID_END, id))
       && (!isInRange(KBS_INTERFACE_UDS_ID_START2, KBS_INTERFACE_UDS_ID_END2, id)))
    {
        *responseCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }

    if(UDS_ERR_CODE_OK == *responseCode)
    {

        KBSInterface_UDS_writeData(id, requestBuffer, requestBufferSize, responseCode);
    }
}

bool uds_writeHookConditionCheck(uint16_t index)
{
    bool retVal = true;
    if((!isInRange(KBS_INTERFACE_UDS_ID_START, KBS_INTERFACE_UDS_ID_END, index))
       && (!isInRange(KBS_INTERFACE_UDS_ID_START2, KBS_INTERFACE_UDS_ID_END2, index)))
    {
        retVal = false;
    }
    return retVal;
}
#endif

#if defined(SDO_UPLOAD_HOOK)
// @req CB-18761
SDOErrorCode sdo_uploadHook(uint16_t index, uint8_t subindex, uint8_t* buffer, uint32_t maxBufferSize, uint32_t* responseSize)
{
    SDOErrorCode abortCode = SDO_ERR_CODE_OK;
    if((!isInRange(KBS_INTERFACE_SDO_START, KBS_INTERFACE_SDO_END, index))
       && (KBS_INTERFACE_SDO_2 != index))
    {
        abortCode = SDO_ERR_CODE_OBJECT_UNKNOWN;
    }

    if(abortCode == SDO_ERR_CODE_OK)
    {
        uint16_t size = 0;
        KBSInterface_CANopen_readData(index, subindex, maxBufferSize, buffer, &size, (uint32_t*)&abortCode);
        *responseSize = size;
    }
    return abortCode;
}
#endif

#if defined(SDO_DOWNLOAD_HOOK)
// @req CB-91893
void sdo_downloadHook(uint16_t index, uint8_t subIndex, const uint8_t* requestBuffer, const uint16_t* requestBufferSize, uint32_t* abortCode)
{
    *abortCode = SDO_ERR_CODE_OK;
    if(sdo_downloadHookConditionCheck(index) == false)
    {
        *abortCode = SDO_ERR_CODE_OBJECT_UNKNOWN;
    }

    if(*abortCode == SDO_ERR_CODE_OK)
    {
        KBSInterface_CANopen_writeData(index, subIndex, requestBuffer, requestBufferSize, abortCode);
    }
}

bool sdo_downloadHookConditionCheck(uint16_t index)
{
    bool retVal = true;
    if((!isInRange(KBS_INTERFACE_SDO_START, KBS_INTERFACE_SDO_END, index))
       && (KBS_INTERFACE_SDO_2 != index))
    {
        retVal = false;
    }
    return retVal;
}
#endif


bool kbsIntegration_setSocDOD(uint16_t newValue)
{
    kbsIntegrationParameter.socDOD = newValue;
    return true;
}

bool kbsIntegration_setSocEOC(uint16_t newValue)
{
    kbsIntegrationParameter.socEOC = newValue;
    return true;
}

bool kbsIntegration_setDiagDerating(uint8_t newValue)
{
    kbsIntegrationParameter.diagDerating = newValue;
    return true;
}

int32_t kbsIntegration_getDeratingChargeLimit(void)
{
    return kbsOutput.maxChargeCurrent_Pulse;
}

int32_t kbsIntegration_getDeratingDischargeLimit(void)
{
    return kbsOutput.maxDischargeCurrent_Pulse;
}

int32_t kbsIntegration_getDeratingChargeLimitContinous(void)
{
    return kbsOutput.maxChargeCurrent_Continuous;
}
int32_t kbsIntegration_getDeratingDischargeLimitContinous(void)
{
    return kbsOutput.maxDischargeCurrent_Continuous;
}

uint16_t kbsIntegration_getSocWithSOH_Internal(void)
{
    return kbsOutput.SOCwithSOH;
}

uint16_t kbsIntegration_getSocWithoutSOH_Internal(void)
{
    return kbsOutput.SOCwithoutSOH;
}

uint32_t kbsIntegration_getMaxChargingPowerContinous(void)
{
    return kbsOutput.maxChargePower_Continuous;
}

uint32_t kbsIntegration_getMaxDischargingPowerContinous(void)
{
    return kbsOutput.maxDischargePower_Continuous;
}

uint32_t kbsIntegration_getMaxChargingPowerPulse(void)
{
    return kbsOutput.maxChargePower_Pulse;
}
uint32_t kbsIntegration_getMaxDischargingPowerPulse(void)
{
    return kbsOutput.maxDischargePower_Pulse;
}

uint8_t kbsIntegration_getCurrentLimited(void)
{
    return (uint8_t)kbsOutput.currentLimited;
}
