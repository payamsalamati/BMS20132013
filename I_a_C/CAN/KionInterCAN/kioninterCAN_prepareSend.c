/**
 *
 * @file kioninterCAN_prepareSend.c
 *
 * @created on Mon Nov 16 10:15:18 CET 2020
 * @brief This module write data from the CAN messages into the
             structs, corresponding to the message ID
 * @copyright Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - kioninterBMS_CPS_UDS_REQ -  -
 * - kioninterBMS_CPS_PDO_TX3 -  -
 * - kioninterBMS_CPS_PDO_TX2 -  -
 * - kioninterBMS_Heartbeat -  -
 * - kioninterBMS_TimeStamp -  -
 * - kioninterBMS_CPS_SDO_REQ -  -
 * - kioninterBMS_ModuleCotrol -  -
 * - kioninterBMS_CPS_PDO_TX1 -  -
 * - kioninterBMS_ICDA_Request -  -
 */

//******************* INCLUDES ********************************//
#include "kioninterCAN.h"

#include "stateFunctions.h"
#include "safety.h"
#include "measurements.h"
#include "measurements_config.h"
#include "softwareversion.h"

#include "highVoltageMeasurement.h"
#include "systemMasterData.h"
#include "auxRelayMeasurement.h"
#include "idAllocation.h"


#include "currentSensorIf.h"
#include "cps.h"
#include "cps_config.h"
#include "ioFunctions.h"
#include "periodicWakeUp.h"
#include "cpsMonitor.h"
#include "timestamp.h"
#include "types.h"

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
#include "safetyDataIf.h"
#endif
#include "debug.h"

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//

//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific receive functions !!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!! Please add the needed functions for your project !!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

void kioninterCAN_prepareBMS_CPS_PDO_TX3(KIONINTER_BMS_CPS_PDO_TX3_t* kioninter_bms_cps_pdo_tx3)
{

    kioninter_bms_cps_pdo_tx3->BMS_INFO_DeepDisImminent   = cps_isDeepDischargeImminent();
    kioninter_bms_cps_pdo_tx3->BMS_INFO_DeepDisPossible   = cps_isDeepDischargePossible();
    kioninter_bms_cps_pdo_tx3->BMS_INFO_TimeToWakeUp      = (uint16_t)(periodicWakeUp_getTimeToWakeUp() & 0xffffu);
    kioninter_bms_cps_pdo_tx3->BMS_INFO_RemainingCapacity = CPS_INFO_REMAINING_CAPACITY;
}

void kioninterCAN_prepareBMS_CPS_PDO_TX2(KIONINTER_BMS_CPS_PDO_TX2_t* kioninter_bms_cps_pdo_tx2)
{

    kioninter_bms_cps_pdo_tx2->BMS_REQ_CPSoutBoost_I = (CPS_OUT_LIMIT_BOOST * KIONINTER_BMS_REQ_CPSOUTBOOST_I_FACTOR) - KIONINTER_BMS_REQ_CPSOUTBOOST_I_OFFSET;
    kioninter_bms_cps_pdo_tx2->BMS_REQ_CPSout_I      = (CPS_OUT_LIMIT * KIONINTER_BMS_REQ_CPSOUT_I_FACTOR) - KIONINTER_BMS_REQ_CPSOUT_I_OFFSET;
}

void kioninterCAN_prepareBMS_Heartbeat(KIONINTER_BMS_HEARTBEAT_t* kioninter_bms_heartbeat)
{

    kioninter_bms_heartbeat->BMS_HBState = 0x05;
}

void kioninterCAN_prepareBMS_TimeStamp(KIONINTER_BMS_TIMESTAMP_t* kioninter_bms_timestamp)
{

    kioninter_bms_timestamp->BMS_CANopen_Days = timestamp_getCANopenDays();
    kioninter_bms_timestamp->BMS_CANopen_Ms   = timestamp_getCANopenMilliSeconds();
}

void kioninterCAN_prepareBMS_CPS_SDO_REQ(KIONINTER_BMS_CPS_SDO_REQ_t* kioninter_bms_cps_sdo_req)
{

    //kioninter_bms_cps_sdo_req->BMS_SDO_TX_Data = dataInterface_getXXX();
}

void kioninterCAN_prepareBMS_ModuleCotrol(KIONINTER_BMS_MODULECOTROL_t* kioninter_bms_modulecotrol)
{

    //kioninter_bms_modulecotrol->BMS_ServiceID = dataInterface_getXXX();
    //kioninter_bms_modulecotrol->BMS_NodeID = dataInterface_getXXX();
}

// @req CB-77845 CB-90326
void kioninterCAN_prepareBMS_CPS_PDO_TX1(KIONINTER_BMS_CPS_PDO_TX1_t* kioninter_bms_cps_pdo_tx1)
{

    kioninter_bms_cps_pdo_tx1->BMS_REQ_Min_V     = (CPS_IMPUT_VOLTAGE_LIMIT * KIONINTER_BMS_REQ_MIN_V_FACTOR) - KIONINTER_BMS_REQ_MIN_V_OFFSET;
    kioninter_bms_cps_pdo_tx1->BMS_INFO_BMSstate = cps_getCpsInfoBmsState();
    kioninter_bms_cps_pdo_tx1->BMS_REQ_PowerDown = cps_getCpsPowerDown();
    kioninter_bms_cps_pdo_tx1->BMS_REQ_CPSout    = cps_getCpsOutReq();

    cpsMonitor_setBMS_REQ_CPSout((uint8_t)kioninter_bms_cps_pdo_tx1->BMS_REQ_CPSout);
}

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
void kioninterCAN_prepareStrPM_SyM_Val1(KIONSTRPM_SYM_VAL1_t* kioninter_strpm_sym_val1_t)
{
    kioninter_strpm_sym_val1_t->StrPM_SyM_Val1Mastertyp    = masterType_get();
    kioninter_strpm_sym_val1_t->StrPM_SyM_Val1ErrorMessage = (uint8_t)(((bool)dem_isErrorActive()) || safetyDataIf_getError());
    kioninter_strpm_sym_val1_t->StrPM_SyM_Val1SWVersion    = (uint8_t)softwareversion_getCommit();
    kioninter_strpm_sym_val1_t->StrPM_SyM_Val1HWVersion    = hwVersion_getVersion();
    // kioninter_strpm_sym_val1_t->StrPM_SyM_Val1Hvi          = hvInterlock_getMasterHvInterlockValue(idAllocation_getMasterId());
    kioninter_strpm_sym_val1_t->StrPM_SyM_Val1Hvi     = 0;
    kioninter_strpm_sym_val1_t->StrPM_SyM_Val1HighSev = dem_getSeverityLevelOfSystem();
    uint16_t strPM_SyM_Val1T2ReacGreaterThenMax       = (uint16_t)(dem_getRemainingSystemReactionTime() / 1000u);


    if(strPM_SyM_Val1T2ReacGreaterThenMax > UMAXVAL_4BIT)
    {
        kioninter_strpm_sym_val1_t->StrPM_SyM_Val1T2Reac = UMAXVAL_4BIT;
    }
    else
    {
        kioninter_strpm_sym_val1_t->StrPM_SyM_Val1T2Reac = strPM_SyM_Val1T2ReacGreaterThenMax;
    }
    if(kioninter_strpm_sym_val1_t->StrPM_SyM_Val1HighSev == DEM_SEVERITY_CONFIRMED)
    {
        kioninter_strpm_sym_val1_t->StrPM_SyM_Val1ErrorRequest = 1u;
    }
    else
    {
        kioninter_strpm_sym_val1_t->StrPM_SyM_Val1ErrorRequest = 0u;
    }
    if(masterType_get() == MASTER_TYPE_SYSTEM)
    {
        kioninter_strpm_sym_val1_t->StrPM_SyM_Val1State = stmFct_getBatteryStateGlobal();
    }
    else
    {
        kioninter_strpm_sym_val1_t->StrPM_SyM_Val1State = State_last_state;
    }
}
#endif
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific send functions END!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
