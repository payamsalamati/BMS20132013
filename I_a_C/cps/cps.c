/**
 * @file cpsData.c
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

#include "cps.h"
#include "cps_config.h"

#include "task_cfg.h"
#include "kionCAN.h"
#include "kioninterCAN.h"
#include "nvm.h"
#include "debug.h"
#include "osIf.h"
#include "isotp_config.h"
#include "ioIf_signals.h"
#include "stateFunctions.h"
#if defined(UNIT_TEST)
#include "test_cps.h"
#else
#include "stm_config.h"
#endif

#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
#include "alternativeMemFunctions.h"
#endif

#include "dem.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    /* initiate a CPS power down (deep-discharge protection) on next regular shutdown */
    bool reqBmsPowerDownRegularShutdown;
    /* initiate a CPS power down (deep-discharge protection) */
    bool reqBmsPowerDown;
    /* control state of heating */
    bool reqBmsHeating;
    /* BMS indicates that it is ready to sleep / for regular power down. */
    CPS_INFO_t infoBmsState;
    /* requested heating current in mA*/
    uint16_t reqBmsHeatingCurrent;
    /* time wake up signal has to be high in ms */
    uint32_t activationTime;
    /* deep discharge is possible */
    bool deepDsgPossible;
    /* deep discharge is imminent */
    bool deepDsgImminent;
    /* cps out status received from cps */
    bool cpsOutStatus;
    /* cps out deactivation inhibit status negativ egde recognized */
    bool cpsOutDeactivationInhibitStatusNegativEdge;
    /* cps out deactivation inhibit status negativ egde timer */
    uint32_t cpsOutDeactivationInhibitStatusNegativEdgeTimer;
} CpsData;

typedef struct
{
    bool cpsOutBmsReq;
    /* cps out deactivation inhibit status */
    bool cpsOutDeactivationInhibitStatus;
    uint8_t reserve[58];
} CpsDataNvm;

#define CPS_NVM_INIT_MAX_DELAY 20
#define CPS_WAKE_UP_TIME_IN_ms 2000

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static bool cpsOutDeactivationInhibitStatusConditionsFullfilled(void);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_NVM CpsDataNvm cpsDataNVM = {
    .cpsOutBmsReq                    = false,  // @req CB-90327
    .cpsOutDeactivationInhibitStatus = false,  // @req CB-89872
};

MEM_CAN static CpsData cpsData = {
    .reqBmsPowerDownRegularShutdown                  = false,
    .reqBmsPowerDown                                 = false,                         // @req CB-91558
    .infoBmsState                                    = CPS_INFO_BMS_STATE_UNDEFINED,  // @req CB-91559
    .reqBmsHeating                                   = false,
    .reqBmsHeatingCurrent                            = 4000,
    .activationTime                                  = 0,
    .deepDsgPossible                                 = false,
    .deepDsgImminent                                 = false,
    .cpsOutStatus                                    = false,
    .cpsOutDeactivationInhibitStatusNegativEdge      = false,
    .cpsOutDeactivationInhibitStatusNegativEdgeTimer = 0,
};

MEM_SEC_PARAMETER CpsConfig cpsConfig = {
    .cpsOutLimit              = CPS_OUT_LIMIT_DEFAULT,
    .cpsOutLimitBoost         = CPS_OUT_LIMIT_BOOST_DEFAULT,
    .cpsInputVoltageLimit     = CPS_IMPUT_VOLTAGE_LIMIT_DEFAULT,
    .cpsInfoRemainingCapacity = CPS_INFO_REMAINING_CAPACITY_DEFAULT,
};

MEM_CAN CpsPdoTx1Data cpsPdoTx1Data;
MEM_CAN CpsPdoTx2Data cpsPdoTx2Data;
MEM_CAN CpsPdoTx3Data cpsPdoTx3Data;
MEM_CAN CpsEmergency cpsEmergency;

MEM_SAFETY OSIf_Event cpsInitSem;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static bool cpsOutDeactivationInhibitStatusConditionsFullfilled(void)
{
    bool conditionsFullfilled = true;
    if((cpsData.reqBmsPowerDownRegularShutdown == true) || (dem_getSeverityLevelOfFault(DTC_CPS_GENERAL_POWERPATH_OT, true) >= DEM_SEVERITY_CONFIRMED))
    {
        conditionsFullfilled = false;
    }
    return conditionsFullfilled;
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

void cps_tunnelCpsVehicleUdsResponse(const CANMessage* msg)
{
    kionCAN_sendCps_uds(msg);
}

void cps_tunnelCpsVehicleUdsRequest(const CANMessage* msg)
{
    if((msg->data[0] == CPS_VEHICLE_EXTENDED_ADDRESS_RX) || (msg->data[0] == ISOTP_BROADCAST_REMOTE_ADDRESS))
    {
        kioninterCAN_sendBMS_CPS_UDS_REQ(msg);
        stmFct_resetCanTimeoutTimer();
    }
}

void cps_initCpsPdoSignals(void)
{
    nvm_readBlock(NVM_CPS_DATA_BLOCK_ID, NULL);
    cpsData.reqBmsPowerDown = false;
    cpsData.infoBmsState    = CPS_INFO_BMS_STATE_OPERATIONAL;

    cpsInitSem = osIf_semaphoreCreate(0);
    DEBUG_ASSERT(cpsInitSem.type != OSIF_EVENT_ERROR);
}

void cps_setCpsOutStatus(bool newSetting)
{
    cpsData.cpsOutStatus = newSetting;
}

bool cps_getCpsOutStatus(void)
{
    return cpsData.cpsOutStatus;
}

bool cps_getCpsOutReq(void)
{
    bool cpsOutDeactivationInhibit = cps_getCpsOutDeactivationInhibitStatus();
    if(cpsData.cpsOutDeactivationInhibitStatusNegativEdge == true)
    {
        uint32_t timeDifference                            = osIf_getTimeDifference(cpsData.cpsOutDeactivationInhibitStatusNegativEdgeTimer);
        cpsData.cpsOutDeactivationInhibitStatusNegativEdge = (timeDifference > STM_CONFIG_CPSOUT_DELAY_DISABLE_DRIVE) ? false : cpsData.cpsOutDeactivationInhibitStatusNegativEdge;
        cpsOutDeactivationInhibit                          = (timeDifference > STM_CONFIG_CPSOUT_DELAY_DISABLE_DRIVE) ? false : true;
    }
    // the system reads 8 bits directly from NVM on startup.
    // in case the NVM has an error or on the first start the value could be > 1, therefore only use the last bit
    return (cps_getCpsOutBmsReq() == true) || (cpsOutDeactivationInhibit == true);
}

void cps_setCpsOutBmsReq(bool newSetting)
{
    cpsDataNVM.cpsOutBmsReq = newSetting;
}

bool cps_getCpsOutBmsReq(void)
{
    // the system reads 8 bits directly from NVM on startup.
    // in case the NVM has an error or on the first start the value could be > 1, therefore only use the last bit
    return cpsDataNVM.cpsOutBmsReq & 1u;
}

void cps_setCpsOutDeactivationInhibitStatus(bool newSetting)
{
    if(cpsOutDeactivationInhibitStatusConditionsFullfilled())
    {
        if((newSetting == false) && (cpsDataNVM.cpsOutDeactivationInhibitStatus == true))
        {
            cpsData.cpsOutDeactivationInhibitStatusNegativEdge      = true;
            cpsData.cpsOutDeactivationInhibitStatusNegativEdgeTimer = osIf_getOStime();
        }
        else
        {
            cpsData.cpsOutDeactivationInhibitStatusNegativEdge = false;
        }
        cpsDataNVM.cpsOutDeactivationInhibitStatus = newSetting;
    }
    else
    {
        cpsDataNVM.cpsOutDeactivationInhibitStatus = false;
    }
}

bool cps_getCpsOutDeactivationInhibitStatus(void)
{
    // the system reads 8 bits directly from NVM on startup.
    // in case the NVM has an error or on the first start the value could be > 1, therefore only use the last bit
    return cpsDataNVM.cpsOutDeactivationInhibitStatus & 1u;
}

void cps_setCpsPowerDownRegularShutdown(void)
{
    cpsData.reqBmsPowerDownRegularShutdown = true;
    cps_setCpsOutDeactivationInhibitStatus(false);
}

bool cps_getCpsPowerDownRegularShutdown(void)
{
    return cpsData.reqBmsPowerDownRegularShutdown;
}

void cps_setCpsPowerDown(bool newSetting)
{
    cpsData.reqBmsPowerDown = newSetting;
}

bool cps_getCpsPowerDown(void)
{
    return cpsData.reqBmsPowerDown;
}

void cps_setCpsInfoBmsState(CPS_INFO_t newSetting)
{
    cpsData.infoBmsState = newSetting;
}

CPS_INFO_t cps_getCpsInfoBmsState(void)
{
    return cpsData.infoBmsState;
}

void cps_setCpsHeatingEnable(bool newSetting)
{
    cpsData.reqBmsHeating = newSetting;
}

bool cps_getCpsHeatingEnable(void)
{
    return cpsData.reqBmsHeating;
}

void cps_setCpsHeatingCurrent(uint16_t newSetting)
{
    cpsData.reqBmsHeatingCurrent = newSetting;
}

uint16_t cps_getCpsHeatingCurrent(void)
{
    return cpsData.reqBmsHeatingCurrent;
}

void cps_checkNvm(const uint8_t* mirror, uint16_t length)
{
    DEBUG_ASSERT(sizeof(CpsDataNvm) == length);
    if(nvm_getErrorStatus(NVM_CPS_DATA_BLOCK_ID) != NVM_REQ_OK)
    {
        cpsDataNVM.cpsOutBmsReq                    = true;
        cpsDataNVM.cpsOutDeactivationInhibitStatus = false;
    }
    else
    {
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
        alternativeMemFunctions_memcpy((uint8_t*)&cpsDataNVM, mirror, sizeof(CpsDataNvm));
#else
        memcpy((uint8_t*)&cpsDataNVM, mirror, sizeof(CpsDataNvm));
#endif
        // @req CB-19013
        if(stmFct_getWakeUpType() != WakeUpSource_AfterReset)
        {
            cpsDataNVM.cpsOutDeactivationInhibitStatus = false;
        }
    }
    osIf_semaphoreGive(cpsInitSem);
}

void cps_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
    alternativeMemFunctions_memcpy(mirror, (uint8_t*)&cpsDataNVM, sizeof(CpsDataNvm));
#else
    memcpy(mirror, (uint8_t*)&cpsDataNVM, sizeof(CpsDataNvm));
#endif
}

void cps_waitForNvm(void)
{
    osIf_semaphoreTake(cpsInitSem, CPS_NVM_INIT_MAX_DELAY);
}

void cps_setPdoTx1(const KIONINTER_CPS_BMS_PDO_TX1_t* data)
{
    cpsPdoTx1Data.cpsError                   = data->CPS_Error;
    cpsPdoTx1Data.cpsBoostCurrentStatus      = data->CPS_CPSoutBoost;
    cpsPdoTx1Data.cpsCurrentLimitationStatus = data->CPS_CPSoutLimitation;
    cpsPdoTx1Data.cpsEmergency               = data->CPS_Emergency;
    cpsPdoTx1Data.cpsStartupAfterPowerDown   = data->CPS_StartupAfterPowerdown;
}

void cps_setPdoTx2(const KIONINTER_CPS_BMS_PDO_TX2_t* data)
{
    cpsPdoTx2Data.cpsOutI     = data->CPS_CPSout_I;
    cpsPdoTx2Data.cpsOutTemp1 = data->CPS_Temp1CPSout;
    cpsPdoTx2Data.cpsOutTemp2 = data->CPS_Temp2CPSout;
}

void cps_setPdoTx3(const KIONINTER_CPS_BMS_PDO_TX3_t* data)
{
    cpsPdoTx3Data.cpsVoltageInput  = data->CPS_VoltageInput;
    cpsPdoTx3Data.cpsVoltageOutput = data->CPS_CPSoutVoltage;
}

void cps_setCpsEmergency(const KIONINTER_CPS_BMS_EMERGENCY_t* data)
{
    cpsEmergency.cpsDTC           = data->CPS_UDS_DTC;
    cpsEmergency.cpsErrorCode     = data->CPS_EMCY_ErrorCode;
    cpsEmergency.cpsErrorRegister = data->CPS_EMCY_ErrorRegister;
}

uint16_t cps_getCpsOutI(void)
{
    return cpsPdoTx2Data.cpsOutI;
}

//@req CB-77818
void cps_enableWakeUp(void)
{
    if(cpsData.activationTime == 0u)
    {
        io_setCpsEnableWakeUp(IO_HIGH_STATE);
        cpsData.activationTime = osIf_getOStime();
    }
    else if((osIf_getOStime() - cpsData.activationTime) >= CPS_WAKE_UP_TIME_IN_ms)
    {
        io_setCpsEnableWakeUp(IO_LOW_STATE);
    }
    else
    {
    }
}

bool cps_isDeepDischargeImminent(void)
{
    cpsData.deepDsgImminent = dem_isFaultActive(DTC_DEEP_DISCHARGE, false);
    ;
    return cpsData.deepDsgImminent;
}

bool cps_isDeepDischargePossible(void)
{
    cpsData.deepDsgPossible = dem_isFaultActive(DTC_CELL_UNDER_VOLTAGE_ERROR, false);
    return cpsData.deepDsgPossible;
}
