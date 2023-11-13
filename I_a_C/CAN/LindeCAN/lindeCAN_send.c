/**
 *
 * @file lindeCAN_send.c
 * @modulenumber LINDE_NB
 * @author Generated File with DPCParser release-1.3.4 Commit 1347995
 * @created on Thu Mar 30 17:16:56 CEST 2023
 * @brief This module write data from the structs to the CAN messages and calls can_send
 * @copyright Futavis GmbH, Aachen 2023 - alle Rechte vorbehalten
 * @details Generated from file "lindeCAN.sym"
 * @par Global variables
 * - lindeLiIoBMS_SDOresp_Traction: -SDO Tx, node 0x0D (LIB with Linde BMZ protocol), SDO client: KMC-
 * - lindeLiIoBMS_SDOresp_LiIoCharger: -SDO Tx, node 0x5D (LIB with Linde BMZ protocol), SDO client: OBC, EXC-
 * - lindeLiIoBMS_PDO5: -PDO5 (Tx), node 0x01 (LIB with Linde BMZ prototol)-
 * - lindeLiIoBMS_PDO4: -PDO4 (Tx), node 0x0D (LIB with Linde BMZ prototol)-
 * - lindeLiIoBMS_PDO3: -PDO3 (Tx), node 0x0D (LIB with Linde BMZ prototol)-
 * - lindeLiIoBMS_PDO2: -PDO2 (Tx), node 0x0D (LIB with Linde BMZ prototol)-
 * - lindeLiIoBMS_PDO1: -PDO1 (Tx), node 0x0D (LIB with Linde BMZ protocol)-
 * - lindeLiIoBMS_Heartbeat: -heartbeat (NMT error control), node 0x0D (LIB with Linde BMZ protocol)-
 * @par changes
 * - first creation Thu Mar 30 17:16:56 CEST 2023
 */

//******************* INCLUDES ********************************//
#include "lindeCAN.h"
#include "stdio.h"
#include "osIf.h"
#include "types.h"
#include "debug.h"
#include "canOpenStmFct.h"
#include "canopen_config.h"
#include "canProtocol.h"

typedef void (*LindeCanSendFunction)(void);
typedef bool (*LindeCanSendFunctionRequirement)(void);

typedef struct
{
    LindeCanSendFunction sendFunction;
    LindeCanSendFunctionRequirement requirementFunction;
    uint16_t timeOffset;
} LindeCanPdoConfig;

MEM_CAN static uint16_t lindeIntervalCounter100ms = 0;

static bool lindePdoRequirements(void);
static void lindeCANSendInterleaved(void);

/* ---------------------------------  FUNCTION DEFINITIONS  -------------------------------- */

static bool lindePdoRequirements(void)
{
    return (canOpenStm_getCanOpenState(&canOpenConfigLinde) == canOpen_State_Operational) && (missingAckErrorCntExternal < 3u);
}

/**
 * @brief send function for CAN message
 */
void lindeCAN_sendLiIoBMS_SDOresp_Traction()
{
    LINDE_LIIOBMS_SDORESP_TRACTION_t linde_liiobms_sdoresp_traction = { 0 };
    lindeCAN_prepareLiIoBMS_SDOresp_Traction(&linde_liiobms_sdoresp_traction);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(linde_liiobms_sdoresp_traction.LiIoBMS_SDOresp_Traction_Data <= UMAXVAL_64BIT);
    data[0] |= (uint8_t)(((uint64_t)linde_liiobms_sdoresp_traction.LiIoBMS_SDOresp_Traction_Data) << 0u);
    data[1] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_traction.LiIoBMS_SDOresp_Traction_Data) >> 8u);
    data[2] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_traction.LiIoBMS_SDOresp_Traction_Data) >> 16u);
    data[3] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_traction.LiIoBMS_SDOresp_Traction_Data) >> 24u);
    data[4] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_traction.LiIoBMS_SDOresp_Traction_Data) >> 32u);
    data[5] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_traction.LiIoBMS_SDOresp_Traction_Data) >> 40u);
    data[6] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_traction.LiIoBMS_SDOresp_Traction_Data) >> 48u);
    data[7] |= (uint8_t)(((uint64_t)linde_liiobms_sdoresp_traction.LiIoBMS_SDOresp_Traction_Data) >> 56u);


    CAN_STATUS statusCAN = canIf_send(lindeCANTransmitLiIoBMS_SDOresp_TractionHandler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void lindeCAN_sendLiIoBMS_SDOresp_LiIoCharger()
{
    LINDE_LIIOBMS_SDORESP_LIIOCHARGER_t linde_liiobms_sdoresp_liiocharger = { 0 };
    lindeCAN_prepareLiIoBMS_SDOresp_LiIoCharger(&linde_liiobms_sdoresp_liiocharger);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(linde_liiobms_sdoresp_liiocharger.LiIoBMS_SDOresp_LiIoCharger_Data <= UMAXVAL_64BIT);
    data[0] |= (uint8_t)(((uint64_t)linde_liiobms_sdoresp_liiocharger.LiIoBMS_SDOresp_LiIoCharger_Data) << 0u);
    data[1] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_liiocharger.LiIoBMS_SDOresp_LiIoCharger_Data) >> 8u);
    data[2] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_liiocharger.LiIoBMS_SDOresp_LiIoCharger_Data) >> 16u);
    data[3] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_liiocharger.LiIoBMS_SDOresp_LiIoCharger_Data) >> 24u);
    data[4] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_liiocharger.LiIoBMS_SDOresp_LiIoCharger_Data) >> 32u);
    data[5] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_liiocharger.LiIoBMS_SDOresp_LiIoCharger_Data) >> 40u);
    data[6] = (uint8_t)(((uint64_t)linde_liiobms_sdoresp_liiocharger.LiIoBMS_SDOresp_LiIoCharger_Data) >> 48u);
    data[7] |= (uint8_t)(((uint64_t)linde_liiobms_sdoresp_liiocharger.LiIoBMS_SDOresp_LiIoCharger_Data) >> 56u);


    CAN_STATUS statusCAN = canIf_send(lindeCANTransmitLiIoBMS_SDOresp_LiIoChargerHandler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void lindeCAN_sendLiIoBMS_PDO5()
{
    LINDE_LIIOBMS_PDO5_t linde_liiobms_pdo5 = { 0 };
    lindeCAN_prepareLiIoBMS_PDO5(&linde_liiobms_pdo5);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(linde_liiobms_pdo5.LiIoBMS_OutputVoltage <= UMAXVAL_24BIT);
    data[0] |= (uint8_t)(((uint64_t)linde_liiobms_pdo5.LiIoBMS_OutputVoltage) << 0u);
    data[1] = (uint8_t)(((uint64_t)linde_liiobms_pdo5.LiIoBMS_OutputVoltage) >> 8u);
    data[2] |= (uint8_t)(((uint64_t)linde_liiobms_pdo5.LiIoBMS_OutputVoltage) >> 16u);

    DEBUG_ASSERT(linde_liiobms_pdo5.LiIoBMS_MaxDischargePower2 <= UMAXVAL_16BIT);
    data[3] |= (uint8_t)(((uint64_t)linde_liiobms_pdo5.LiIoBMS_MaxDischargePower2) << 0u);
    data[4] |= (uint8_t)(((uint64_t)linde_liiobms_pdo5.LiIoBMS_MaxDischargePower2) >> 8u);

    DEBUG_ASSERT(linde_liiobms_pdo5.LiIoBMS_MaxChargePower2 <= UMAXVAL_16BIT);
    data[5] |= (uint8_t)(((uint64_t)linde_liiobms_pdo5.LiIoBMS_MaxChargePower2) << 0u);
    data[6] |= (uint8_t)(((uint64_t)linde_liiobms_pdo5.LiIoBMS_MaxChargePower2) >> 8u);


    CAN_STATUS statusCAN = canIf_send(lindeCANTransmitLiIoBMS_PDO5Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void lindeCAN_sendLiIoBMS_PDO4()
{
    LINDE_LIIOBMS_PDO4_t linde_liiobms_pdo4 = { 0 };
    lindeCAN_prepareLiIoBMS_PDO4(&linde_liiobms_pdo4);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(linde_liiobms_pdo4.LiIoBMS_MinDischargeVoltage <= UMAXVAL_24BIT);
    data[0] |= (uint8_t)(((uint64_t)linde_liiobms_pdo4.LiIoBMS_MinDischargeVoltage) << 0u);
    data[1] = (uint8_t)(((uint64_t)linde_liiobms_pdo4.LiIoBMS_MinDischargeVoltage) >> 8u);
    data[2] |= (uint8_t)(((uint64_t)linde_liiobms_pdo4.LiIoBMS_MinDischargeVoltage) >> 16u);

    DEBUG_ASSERT(linde_liiobms_pdo4.LiIoBMS_MaxChargeVoltage <= UMAXVAL_24BIT);
    data[3] |= (uint8_t)(((uint64_t)linde_liiobms_pdo4.LiIoBMS_MaxChargeVoltage) << 0u);
    data[4] = (uint8_t)(((uint64_t)linde_liiobms_pdo4.LiIoBMS_MaxChargeVoltage) >> 8u);
    data[5] |= (uint8_t)(((uint64_t)linde_liiobms_pdo4.LiIoBMS_MaxChargeVoltage) >> 16u);

    DEBUG_ASSERT(linde_liiobms_pdo4.LiIoBMS_SOCwithoutSOH <= UMAXVAL_8BIT);
    data[6] |= ((uint64_t)linde_liiobms_pdo4.LiIoBMS_SOCwithoutSOH) << 0u;

    DEBUG_ASSERT(linde_liiobms_pdo4.LiIoBMS_SOCwithSOH <= UMAXVAL_8BIT);
    data[7] |= ((uint64_t)linde_liiobms_pdo4.LiIoBMS_SOCwithSOH) << 0u;


    CAN_STATUS statusCAN = canIf_send(lindeCANTransmitLiIoBMS_PDO4Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void lindeCAN_sendLiIoBMS_PDO3()
{
    LINDE_LIIOBMS_PDO3_t linde_liiobms_pdo3 = { 0 };
    lindeCAN_prepareLiIoBMS_PDO3(&linde_liiobms_pdo3);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(linde_liiobms_pdo3.LiIoBMS_DTC1 <= UMAXVAL_16BIT);
    data[0] |= (uint8_t)(((uint64_t)linde_liiobms_pdo3.LiIoBMS_DTC1) << 0u);
    data[1] |= (uint8_t)(((uint64_t)linde_liiobms_pdo3.LiIoBMS_DTC1) >> 8u);

    DEBUG_ASSERT(linde_liiobms_pdo3.LiIoBMS_DTC2 <= UMAXVAL_16BIT);
    data[2] |= (uint8_t)(((uint64_t)linde_liiobms_pdo3.LiIoBMS_DTC2) << 0u);
    data[3] |= (uint8_t)(((uint64_t)linde_liiobms_pdo3.LiIoBMS_DTC2) >> 8u);

    DEBUG_ASSERT(linde_liiobms_pdo3.LiIoBMS_DTC3 <= UMAXVAL_16BIT);
    data[4] |= (uint8_t)(((uint64_t)linde_liiobms_pdo3.LiIoBMS_DTC3) << 0u);
    data[5] |= (uint8_t)(((uint64_t)linde_liiobms_pdo3.LiIoBMS_DTC3) >> 8u);

    DEBUG_ASSERT(linde_liiobms_pdo3.LiIoBMS_DTC4 <= UMAXVAL_16BIT);
    data[6] |= (uint8_t)(((uint64_t)linde_liiobms_pdo3.LiIoBMS_DTC4) << 0u);
    data[7] |= (uint8_t)(((uint64_t)linde_liiobms_pdo3.LiIoBMS_DTC4) >> 8u);


    CAN_STATUS statusCAN = canIf_send(lindeCANTransmitLiIoBMS_PDO3Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void lindeCAN_sendLiIoBMS_PDO2()
{
    LINDE_LIIOBMS_PDO2_t linde_liiobms_pdo2 = { 0 };
    lindeCAN_prepareLiIoBMS_PDO2(&linde_liiobms_pdo2);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(linde_liiobms_pdo2.LiIoBMS_MaxChargeCurrent2 <= UMAXVAL_16BIT);
    data[0] |= (uint8_t)(((uint64_t)linde_liiobms_pdo2.LiIoBMS_MaxChargeCurrent2) << 0u);
    data[1] |= (uint8_t)(((uint64_t)linde_liiobms_pdo2.LiIoBMS_MaxChargeCurrent2) >> 8u);

    DEBUG_ASSERT(linde_liiobms_pdo2.LiIoBMS_MaxDischargeCurrent2 <= UMAXVAL_16BIT);
    data[2] |= (uint8_t)(((uint64_t)linde_liiobms_pdo2.LiIoBMS_MaxDischargeCurrent2) << 0u);
    data[3] |= (uint8_t)(((uint64_t)linde_liiobms_pdo2.LiIoBMS_MaxDischargeCurrent2) >> 8u);

    DEBUG_ASSERT(linde_liiobms_pdo2.LiIoBMS_MaxChargeCurrent100 <= UMAXVAL_16BIT);
    data[4] |= (uint8_t)(((uint64_t)linde_liiobms_pdo2.LiIoBMS_MaxChargeCurrent100) << 0u);
    data[5] |= (uint8_t)(((uint64_t)linde_liiobms_pdo2.LiIoBMS_MaxChargeCurrent100) >> 8u);

    DEBUG_ASSERT(linde_liiobms_pdo2.LiIoBMS_MaxDischargeCurrent100 <= UMAXVAL_16BIT);
    data[6] |= (uint8_t)(((uint64_t)linde_liiobms_pdo2.LiIoBMS_MaxDischargeCurrent100) << 0u);
    data[7] |= (uint8_t)(((uint64_t)linde_liiobms_pdo2.LiIoBMS_MaxDischargeCurrent100) >> 8u);


    CAN_STATUS statusCAN = canIf_send(lindeCANTransmitLiIoBMS_PDO2Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void lindeCAN_sendLiIoBMS_PDO1()
{
    LINDE_LIIOBMS_PDO1_t linde_liiobms_pdo1 = { 0 };
    lindeCAN_prepareLiIoBMS_PDO1(&linde_liiobms_pdo1);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(linde_liiobms_pdo1.LiIoBMS_BatteryCurrent <= UMAXVAL_24BIT);
    data[0] |= (uint8_t)(((uint64_t)linde_liiobms_pdo1.LiIoBMS_BatteryCurrent) << 0u);
    data[1] = (uint8_t)(((uint64_t)linde_liiobms_pdo1.LiIoBMS_BatteryCurrent) >> 8u);
    data[2] |= (uint8_t)(((uint64_t)linde_liiobms_pdo1.LiIoBMS_BatteryCurrent) >> 16u);

    DEBUG_ASSERT(linde_liiobms_pdo1.LiIoBMS_BatteryVoltage <= UMAXVAL_24BIT);
    data[3] |= (uint8_t)(((uint64_t)linde_liiobms_pdo1.LiIoBMS_BatteryVoltage) << 0u);
    data[4] = (uint8_t)(((uint64_t)linde_liiobms_pdo1.LiIoBMS_BatteryVoltage) >> 8u);
    data[5] |= (uint8_t)(((uint64_t)linde_liiobms_pdo1.LiIoBMS_BatteryVoltage) >> 16u);

    DEBUG_ASSERT(linde_liiobms_pdo1.LiIoBMS_BatteryState <= UMAXVAL_8BIT);
    data[6] |= ((uint64_t)linde_liiobms_pdo1.LiIoBMS_BatteryState) << 0u;

    DEBUG_ASSERT(linde_liiobms_pdo1.LiIoBMS_SOH <= UMAXVAL_8BIT);
    data[7] |= ((uint64_t)linde_liiobms_pdo1.LiIoBMS_SOH) << 0u;


    CAN_STATUS statusCAN = canIf_send(lindeCANTransmitLiIoBMS_PDO1Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void lindeCAN_sendLiIoBMS_Heartbeat()
{
    LINDE_LIIOBMS_HEARTBEAT_t linde_liiobms_heartbeat = { 0 };
    lindeCAN_prepareLiIoBMS_Heartbeat(&linde_liiobms_heartbeat);

    uint8_t data[MESSAGE_DLC_1] = { 0 };

    DEBUG_ASSERT(linde_liiobms_heartbeat.LiIoBMS_State <= UMAXVAL_7BIT);
    data[0] |= ((uint64_t)linde_liiobms_heartbeat.LiIoBMS_State) << 0u;


    CAN_STATUS statusCAN = canIf_send(lindeCANTransmitLiIoBMS_HeartbeatHandler, MESSAGE_DLC_1, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
        canOpenStm_setHeartbeatSent(&canOpenConfigLinde);
        canOpenStm_setHeartbeatSent(&canOpenConfigLindeCharger);
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

void lindeCANSend40(void)
{

#if defined(STMFCT_BLOCKCOMCAN1)
    if(stmFct_getBlockComCan1() == false)
    {
#endif
        if(((canOpenStm_getCanOpenState(&canOpenConfigLinde) != canOpen_State_Stopped) || (canOpenStm_getCanOpenState(&canOpenConfigLindeCharger) != canOpen_State_Stopped)) && (missingAckErrorCntExternal < 3u))
        {
            // @req CB-91647
            lindeCAN_sendLiIoBMS_Heartbeat();
        }
#if defined(STMFCT_BLOCKCOMCAN1)
    }
#endif
}

void lindeCANSend10(void)
{
    lindeCANSendInterleaved();
}

void lindeCANSendInterleaved(void)
{
    // 100 ms
#if defined(STMFCT_BLOCKCOMCAN1)
    if(stmFct_getBlockComCan1() == false)
    {
#endif
        const LindeCanPdoConfig lindeCanConfig100[] = {
            { lindeCAN_sendLiIoBMS_PDO1, lindePdoRequirements, 0 },
            { lindeCAN_sendLiIoBMS_PDO2, lindePdoRequirements, 10 },
            { lindeCAN_sendLiIoBMS_PDO4, lindePdoRequirements, 20 },
            { lindeCAN_sendLiIoBMS_PDO5, lindePdoRequirements, 30 },
        };

        for(uint8_t i = 0; i < (sizeof(lindeCanConfig100) / sizeof(LindeCanPdoConfig)); i++)
        {
            if((lindeIntervalCounter100ms == lindeCanConfig100[i].timeOffset)
               && ((lindeCanConfig100[i].requirementFunction != NULL) && (lindeCanConfig100[i].requirementFunction() == true))
               && (lindeCanConfig100[i].sendFunction != NULL))
            {
                lindeCanConfig100[i].sendFunction();
            }
        }

#if defined(STMFCT_BLOCKCOMCAN1)
    }
#endif

    lindeIntervalCounter100ms += 10u;
    lindeIntervalCounter100ms %= 100u;
}
