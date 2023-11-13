/**
 *
 * @file kionCAN_prepareSend.c
 *
 * @created on Tue Feb 16 14:15:58 CET 2021
 * @brief This module write data from the CAN messages into the
             structs, corresponding to the message ID
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - kionADC_Values0 -  -
 * - kionADC_Values1 -  -
 * - kionADC_Values2 -  -
 * - kionADC_Values3 -  -
 * - kiondebugDTC -  -
 * - kionlib_uds - UDS responses from LIB with KION protocol -
 * - kionlib_sdo_tx - SDO Tx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC -
 * - kionlib_pdo_tx7 - PDO 7 (Tx), node 0x77 (LIB with KION protocol) -
 * - kionlib_pdo_tx6 - PDO 6 (Tx), node 0x77 (LIB with KION protocol) -
 * - kionlib_pdo_tx5 - PDO 5 (Tx), node 0x77 (LIB with KION protocol) -
 * - kionlib_pdo_tx4 - PDO 4 (Tx), node 0x27 (LIB with KION protocol) -
 * - kionlib_pdo_tx3 - PDO 3 (Tx), node 0x27 (LIB with KION protocol) -
 * - kionlib_pdo_tx2 - PDO 2 (Tx), node 0x27 (LIB with KION protocol) -
 * - kionlib_pdo_tx1 - PDO 1 (Tx), node 0x27 (LIB with KION protocol) -
 * - kionlib_heartbeat - heartbeat (NMT error control), node 0x27 (LIB with KION protocol) -
 * - kionlib_emergency - emergency (EMCY), node 0x27 (LIB with KION protocol) -
 * - kionHeartbtBms - Network Management, Error Control, Battery management system Heartbeat -
 * - kionDiagRespBms -  -
 * - kionBmsSDOtx - CAN Open: Data for Service data object (SDO) send by BMS -
 * - kiondebugValues1 -  -
 */

//******************* INCLUDES ********************************//
#include "kionCAN.h"

#include "systemMasterData.h"
#include "highVoltageMeasurement.h"

#include "module_config.h"

#include "afeTask.h"
#include "canOpenStmFct.h"
#include "canopen_config.h"
#include "systemMasterData.h"
#include "csc_config.h"
#include "moduleVoltageMeasurement.h"
#include "task_cfg.h"
#include "idAllocation.h"
#include "stateFunctions.h"
#include "stringCurrentMeasurement.h"
#include "safetyRelayInterface.h"
#include "auxRelayMeasurement.h"
#include "canData.h"
#include "voltageMonitor_config.h"
#include "fut_math.h"
#include "kbsIntegration.h"
#include "types.h"
#include "cellVoltageMeasurement.h"
#include "cellTemperatureMeasurement.h"
#include "supplyVoltageMeasurement.h"
#include "math.h"
#include "serviceRequirement.h"
#include "cps.h"
#include "highVoltageMeasurement.h"

#if defined(SW_RESET_ANALYSIS_CAN_DATA)
#include "taskAliveMonitor.h"
#include "sbc_fs4500c.h"
#endif

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//

#define BMS_SOC_WITH_SOH_DEFAULT         100u    // 100 %
#define BMS_MAX_DIR_CURR_DEFAULT         300000  // 300000mA
#define INITIAL_VALUE_OF_STATE_OF_HEALTH 0xFF

//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific receive functions !!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!! Please add the needed functions for your project !!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

void kionCAN_preparelib_uds(KION_LIB_UDS_t* kion_lib_uds)
{

    //kion_lib_uds->isotp_n_ta = dataInterface_getXXX();
    //kion_lib_uds->isotp_bs = dataInterface_getXXX();
    //kion_lib_uds->isotp_fs = dataInterface_getXXX();
    //kion_lib_uds->isotp_n_data_fc = dataInterface_getXXX();
    //kion_lib_uds->isotp_stmin = dataInterface_getXXX();
}

void kionCAN_preparelib_sdo_tx(KION_LIB_SDO_TX_t* kion_lib_sdo_tx)
{

    //kion_lib_sdo_tx->canopen_sdo_abort_code = dataInterface_getXXX();
    //kion_lib_sdo_tx->canopen_sdo_abort_index = dataInterface_getXXX();
    //kion_lib_sdo_tx->canopen_sdo_abort_subindex = dataInterface_getXXX();
}

void kionCAN_preparelib_pdo_tx8(KION_LIB_PDO_TX8_t* kion_lib_pdo_tx8)
{
    const DEM_FaultCode dtcList[] = {
        DTC_ICD_COM_FAULT,
        DTC_ICD_SENSOR_MEASUREMENT_FAULT,
        DTC_ICD_SENSOR_SYSTEM_FAULT,
        DTC_ICD_CONFIGURATION_INVALID,
        DTC_ICD_RESULT_RC_FAULT,
        DTC_ICD_SENSOR_PERSISTENT_FAULT
    };
    uint16_t dtcListSize                                           = (sizeof(dtcList) / sizeof(DEM_FaultCode));
    kion_lib_pdo_tx8->lib_current_unfiltered                       = (dem_isFaultInListActive(&dtcList[0], dtcListSize, false) == false) ? ((stringCurrentMeasurement_getValue() * KION_LIB_CURRENT_FACTOR) - KION_LIB_CURRENT_OFFSET) : 0x7FFFE;
    kion_lib_pdo_tx8->lib_voltage_in_front_of_contactor_unfiltered = (highVoltageMeasurement_getMasterHvVoltagesValueUnValidated(2) / 1000.0 * KION_LIB_VOLTAGE_IN_FRONT_OF_CONTACTO_FACTOR) - KION_LIB_VOLTAGE_IN_FRONT_OF_CONTACTO_OFFSET;
    kion_lib_pdo_tx8->lib_voltage_after_contactor_unfiltered       = (highVoltageMeasurement_getMasterHvVoltagesValueUnValidated(0) / 1000.0 * KION_LIB_VOLTAGE_AFTER_CONTACTOR_FACTOR) - KION_LIB_VOLTAGE_AFTER_CONTACTOR_OFFSET;

    canData_storeLastLibPdoTx8Data(*kion_lib_pdo_tx8);
}

void kionCAN_preparelib_pdo_tx7(KION_LIB_PDO_TX7_t* kion_lib_pdo_tx7)
{
    // @req CB-75120 CB-15669
    kion_lib_pdo_tx7->lib_powerpath_ok = (dem_getSeverityLevelOfFault(DTC_CONTACTOR_DIAG_ERROR, true) < DEM_SEVERITY_CONFIRMED);
    canData_storeLastLibPdoTx7Data(*kion_lib_pdo_tx7);
}

void kionCAN_preparelib_pdo_tx6(KION_LIB_PDO_TX6_t* kion_lib_pdo_tx6)
{
    // @req CB-75118
    // @req CB-18805
    kion_lib_pdo_tx6->lib_max_charging_current_2s = kbsIntegration_getDeratingChargeLimit() / 10;
    // @req CB-75119
    // @req CB-18806
    kion_lib_pdo_tx6->lib_max_charging_current_100s = kbsIntegration_getDeratingChargeLimitContinous() / 10;
    // @req CB-18800
    kion_lib_pdo_tx6->lib_soc_without_soh_fine = kbsIntegration_getSocWithoutSOH_Internal();  // INT121
    kion_lib_pdo_tx6->lib_min_temperature      = (systemMasterData_getBatteryTemperatureMin() * KION_LIB_TEMPERATURE_MIN_FACTOR) - KION_LIB_TEMPERATURE_MIN_OFFSET;
    kion_lib_pdo_tx6->lib_max_temperature      = (systemMasterData_getBatteryTemperatureMax() * KION_LIB_TEMPERATURE_MAX_FACTOR) - KION_LIB_TEMPERATURE_MAX_OFFSET;

    canData_storeLastLibPdoTx6Data(*kion_lib_pdo_tx6);
}

void kionCAN_preparelib_pdo_tx5(KION_LIB_PDO_TX5_t* kion_lib_pdo_tx5)
{
    // @req CB-75116
    // @req CB-18807
    kion_lib_pdo_tx5->lib_max_discharging_current_2s = kbsIntegration_getDeratingDischargeLimit() / 10;
    // @req CB-75117
    // @req CB-18808
    kion_lib_pdo_tx5->lib_max_discharging_current_100s = kbsIntegration_getDeratingDischargeLimitContinous() / 10;
    canData_storeLastLibPdoTx5Data(*kion_lib_pdo_tx5);
}

void kionCAN_preparelib_pdo_tx4(KION_LIB_PDO_TX4_t* kion_lib_pdo_tx4)
{
    // @req CB-75113
    // @req CB-18801
    kion_lib_pdo_tx4->lib_max_charging_power_100s = kbsIntegration_getMaxChargingPowerContinous() & UMAXVAL_19BIT;  // INT123
    // @req CB-75112
    // @req CB-18803
    kion_lib_pdo_tx4->lib_max_charging_power_2s = kbsIntegration_getMaxChargingPowerPulse() & UMAXVAL_19BIT;  // INT125

    // @req CB-75114
    // @req CB-18800
    // @req CB-91447
    kion_lib_pdo_tx4->lib_soc_without_soh = (uint16_t)(roundf(((float)kbsIntegration_getSocWithoutSOH_Internal() * KION_LIB_SOC_WITHOUT_SOH_FACTOR))) - (uint16_t)KION_LIB_SOC_WITHOUT_SOH_OFFSET;  // INT121
    // @req CB-75111
    kion_lib_pdo_tx4->lib_max_charging_voltage = (((CELL_VOLTAGE_MAX_ERR_DETECT_VAL * CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL * CELL_MODULE_CONFIG_STRING_NO_OF_MODULES_SERIAL) / 1000.0) * KION_LIB_MAX_CHARGING_VOLTAGE_FACTOR) - KION_LIB_MAX_CHARGING_VOLTAGE_OFFSET;

    canData_storeLastLibPdoTx4Data(*kion_lib_pdo_tx4);
}

void kionCAN_preparelib_pdo_tx3(KION_LIB_PDO_TX3_t* kion_lib_pdo_tx3)
{
    // @req CB-75106
    // @req CB-18804
    kion_lib_pdo_tx3->lib_max_discharging_power_2s = kbsIntegration_getMaxDischargingPowerPulse() & UMAXVAL_19BIT;  // INT126
    // @req CB-75107
    // @req CB-18802
    kion_lib_pdo_tx3->lib_max_discharging_power_100s = kbsIntegration_getMaxDischargingPowerContinous() & UMAXVAL_19BIT;  // INT124
    // @req CB-75105
    kion_lib_pdo_tx3->lib_min_discharging_voltage = (((CELL_VOLTAGE_MIN_ERR_DETECT_VAL * CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL * CELL_MODULE_CONFIG_STRING_NO_OF_MODULES_SERIAL) / 1000.0) * KION_LIB_MIN_DISCHARGING_VOLTAGE_FACTOR) - KION_LIB_MIN_DISCHARGING_VOLTAGE_OFFSET;
    // @req CB-75108
    // @req CB-18799
    // @req CB-91441
    kion_lib_pdo_tx3->lib_soc_with_soh = (uint16_t)(roundf((float)kbsIntegration_getSocWithSOH_Internal() * KION_LIB_SOC_WITH_SOH_FACTOR)) - (uint16_t)KION_LIB_SOC_WITH_SOH_OFFSET;  // INT119
    canData_storeLastLibPdoTx3Data(*kion_lib_pdo_tx3);
}

void kionCAN_preparelib_pdo_tx2(KION_LIB_PDO_TX2_t* kion_lib_pdo_tx2)
{

    // @req CB-75103
    kion_lib_pdo_tx2->lib_power = ((int32_t)((int64_t)highVoltageMeasurement_getMasterHvVoltagesValue(0) * (int64_t)stringCurrentMeasurement_getValue() / (int64_t)1000 / (int64_t)1000) * KION_LIB_POWER_FACTOR) - KION_LIB_POWER_OFFSET;
    // @req CB-75102
    kion_lib_pdo_tx2->lib_voltage_after_contactor = (highVoltageMeasurement_getMasterHvVoltagesValue(2) / 1000.0 * KION_LIB_VOLTAGE_AFTER_CONTACTOR_FACTOR) - KION_LIB_VOLTAGE_AFTER_CONTACTOR_OFFSET;
    // @req CB-74957
    // @req CB-75104
    kion_lib_pdo_tx2->lib_state_of_health = INITIAL_VALUE_OF_STATE_OF_HEALTH;
    // @req CB-75101
    kion_lib_pdo_tx2->lib_voltage_in_front_of_contacto = (highVoltageMeasurement_getMasterHvVoltagesValue(0) / 1000.0 * KION_LIB_VOLTAGE_IN_FRONT_OF_CONTACTO_FACTOR) - KION_LIB_VOLTAGE_IN_FRONT_OF_CONTACTO_OFFSET;
    canData_storeLastLibPdoTx2Data(*kion_lib_pdo_tx2);
}

void kionCAN_preparelib_pdo_tx1(KION_LIB_PDO_TX1_t* kion_lib_pdo_tx1)
{

    kion_lib_pdo_tx1->lib_cps_output_active               = cps_getCpsOutStatus();
    kion_lib_pdo_tx1->lib_cps_output_deactivation_inhibit = cps_getCpsOutDeactivationInhibitStatus();
    // @req CB-75090
    kion_lib_pdo_tx1->lib_in_charging_mode = stmFct_getLibCharge();
    // @req CB-75088
    kion_lib_pdo_tx1->lib_ready = stmFct_getLibReady() && (dem_getSeverityLevelOfSystem() < DEM_SEVERITY_CONFIRMED);
    // @req CB-75087
    kion_lib_pdo_tx1->lib_init_complete = afeTask_isAfeTaskRunning();
    // @req CB-75091 CB-15720
    kion_lib_pdo_tx1->lib_error = dem_getSeverityLevelOfSystem() == DEM_SEVERITY_CONFIRMED;
    // @req CB-75092 - outdated
    // @req CB-18798
    kion_lib_pdo_tx1->lib_current_limited = kbsIntegration_getCurrentLimited();  // INT131
    // @req CB-75089
    kion_lib_pdo_tx1->lib_in_driving_mode = stmFct_getLibDrive();
    // @req CB-75093
    kion_lib_pdo_tx1->lib_emergency_operation = stmFct_getEmergency() && (dem_getSeverityLevelOfSystem() < DEM_SEVERITY_CONFIRMED);
    // @req CB-75096
    kion_lib_pdo_tx1->lib_temperature_too_high = dem_isFaultActive(DTC_CELL_HIGH_TEMPERATURE_ERROR, false);
    // @req CB-75097
    kion_lib_pdo_tx1->lib_temperature_too_low = dem_isFaultActive(DTC_CELL_LOW_TEMPERATURE_ERROR, false);

    kion_lib_pdo_tx1->lib_shock_warning = 0x03;  // not Applicable Draft
    // @req CB-75095
    // @req CB-90051
    kion_lib_pdo_tx1->lib_fatal_error = dem_getSeverityLevelOfSystem() >= DEM_SEVERITY_SAFE_STATE;
    // @req CB-75098
    kion_lib_pdo_tx1->lib_service_required = serviceRequirement_getServiceRequired();
    // @req CB-75100
    kion_lib_pdo_tx1->lib_current = (stringCurrentMeasurement_getValue() * KION_LIB_CURRENT_FACTOR) - KION_LIB_CURRENT_OFFSET;
    canData_storeLastLibPdoTx1Data(*kion_lib_pdo_tx1);
}

void kionCAN_preparelib_heartbeat(KION_LIB_HEARTBEAT_t* kion_lib_heartbeat)
{
    // @req CB-72658
    kion_lib_heartbeat->canopen_state_lib = canOpenStm_getCanOpenState(&canOpenConfigKion);
    canData_storeLastLibHeartbeatData(*kion_lib_heartbeat);
}

void kionCAN_preparelib_emergency(KION_LIB_EMERGENCY_t* kion_lib_emergency)
{

    //kion_lib_emergency->error_register_object_lib = dataInterface_getXXX();
    //kion_lib_emergency->uds_dtc_lib = dataInterface_getXXX();
    //kion_lib_emergency->emergency_error_code_lib = dataInterface_getXXX();
    canData_storeLastLibEmergencyData(*kion_lib_emergency);
}

void kionCAN_prepareHeartbtBms(KION_HEARTBTBMS_t* kion_heartbtbms)
{

    canData_storeLastHeartbtBmsData(*kion_heartbtbms);
}

void kionCAN_prepareDiagRespBms(KION_DIAGRESPBMS_t* kion_diagrespbms)
{

    //kion_diagrespbms->BmsRsData = dataInterface_getXXX();
    //kion_diagrespbms->BmsRsPCI = dataInterface_getXXX();
}

void kionCAN_prepareBmsSDOtx(KION_BMSSDOTX_t* kion_bmssdotx)
{

    //kion_bmssdotx->BmsSDOtxData = dataInterface_getXXX();
}

#if defined(SW_RESET_ANALYSIS_CAN_DATA)
void kionCAN_prepareTaskMaxTimes(KION_MAXTASKTIMES_t* kion_maxTasktimes)
{
    kion_maxTasktimes->maxSafetyTaskTime     = taskAliveMonitor_getMaxCycleTimeSinceLastStartup(TASK_SAFETY_PRIO) / 10;
    kion_maxTasktimes->maxAfeTaskTime        = taskAliveMonitor_getMaxCycleTimeSinceLastStartup(TASK_AFE_PRIO) / 10;
    kion_maxTasktimes->maxNVMTaskTime        = taskAliveMonitor_getMaxCycleTimeSinceLastStartup(TASK_NVM_PRIO) / 10;
    kion_maxTasktimes->maxLimitCheckTaskTime = taskAliveMonitor_getMaxCycleTimeSinceLastStartup(TASK_LIMITCHECK10_PRIO) / 10;
    kion_maxTasktimes->maxCanSendTaskTime    = taskAliveMonitor_getMaxCycleTimeSinceLastStartup(TASK_CANSEND_PRIO) / 10;
    kion_maxTasktimes->maxCanReceiveTaskTime = taskAliveMonitor_getMaxCycleTimeSinceLastStartup(TASK_CANRECEIVE_PRIO) / 10;
}

void kionCAN_prepareTaskCurrentTimes(KION_CURRENTTASKTIMES_t* kion_currentTasktimes)
{
    kion_currentTasktimes->currentSafetyTaskTime     = taskAliveMonitor_getCurrentTaskTimeSinceLastCall(TASK_SAFETY_PRIO) / 10;
    kion_currentTasktimes->currentAfeTaskTime        = taskAliveMonitor_getCurrentTaskTimeSinceLastCall(TASK_AFE_PRIO) / 10;
    kion_currentTasktimes->currentNVMTaskTime        = taskAliveMonitor_getCurrentTaskTimeSinceLastCall(TASK_NVM_PRIO) / 10;
    kion_currentTasktimes->currentLimitCheckTaskTime = taskAliveMonitor_getCurrentTaskTimeSinceLastCall(TASK_LIMITCHECK10_PRIO) / 10;
    kion_currentTasktimes->currentCanSendTaskTime    = taskAliveMonitor_getCurrentTaskTimeSinceLastCall(TASK_CANSEND_PRIO) / 10;
    kion_currentTasktimes->currentCanReceiveTaskTime = taskAliveMonitor_getCurrentTaskTimeSinceLastCall(TASK_CANRECEIVE_PRIO) / 10;
}

void kionCAN_prepareSBCStatus(KION_SBCSTATUS_t* kion_sbcStatus)
{
    SBC_FS4500C_Status* status = sbc_FS4500C_getStatus();
    kion_sbcStatus->wdCounter  = status->watchdog.wdCounter;
}
#endif

void kionCAN_preparedebugValues1(KION_DEBUGVALUES1_t* kion_debugvalues1)
{

    kion_debugvalues1->CellVoltageMax     = cellVoltageMeasurement_getMaxValue();
    kion_debugvalues1->CellVoltageMin     = cellVoltageMeasurement_getMinValue();
    kion_debugvalues1->CellTemperatureMax = cellTemperatureMeasurement_getMaxValue();
    kion_debugvalues1->CellTemperatureMin = cellTemperatureMeasurement_getMinValue();
    kion_debugvalues1->RelaySupplyMin     = (uint16_t)supplyVoltageMeasurement_getRelaySupplyMin();
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific send functions END!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
