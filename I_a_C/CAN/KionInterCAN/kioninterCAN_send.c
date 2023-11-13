/**
 *
 * @file kioninterCAN_send.c
 * @created on Mon Nov 16 10:15:18 CET 2020
 * @brief This module write data from the structs to the CAN messages and calls can_send
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - kioninterBMS_CPS_UDS_REQ: --
 * - kioninterBMS_CPS_PDO_TX3: --
 * - kioninterBMS_CPS_PDO_TX2: --
 * - kioninterBMS_Heartbeat: --
 * - kioninterBMS_TimeStamp: --
 * - kioninterBMS_CPS_SDO_REQ: --
 * - kioninterBMS_ModuleCotrol: --
 * - kioninterBMS_CPS_PDO_TX1: --
 * - kioninterBMS_ICDA_Request: --
 */

//******************* INCLUDES ********************************//
#include "kioninterCAN.h"
#include "kioninterCAN_config.h"
#include "osIf.h"
#include "types.h"
#include "debug.h"
#include "canIf.h"
#include "stateFunctions.h"
#include "timestamp.h"

typedef void (*KionInterCanSendFunction)(void);
typedef bool (*KionInterCanSendFunctionRequirement)(void);
typedef struct
{
    KionInterCanSendFunction sendFunction;
    KionInterCanSendFunctionRequirement requirementFunction;
    uint16_t timeOffset;
} KionInterCanPdoConfig;

MEM_CAN static uint8_t BMS_CPS_PDO_TX3RollingCounter    = 0;
MEM_CAN static uint8_t BMS_CPS_PDO_TX2RollingCounter    = 0;
MEM_CAN static uint8_t BMS_CPS_PDO_TX1RollingCounter    = 0;
MEM_CAN static uint8_t interCAN_TrySendHeartBeatCounter = 0;

MEM_CAN static uint16_t intervalCounter100ms = 0;

static bool cpsPdoRequirements(void);
static bool cpsTimestampRequirements(void);

/* ---------------------------------  FUNCTION DEFINITIONS  -------------------------------- */

static bool cpsPdoRequirements(void)
{
    return (stmFct_getCpsCommunicationEnable() == true) && (kioninterCAN_getMissingAckErrorCounter() < KIONINTERCAN_MAX_MISSING_ACK_ERROR_COUNT);
}

static bool cpsTimestampRequirements(void)
{
    return (stmFct_getCpsCommunicationEnable() == true) && (timestamp_isTimestampInitialized() == true) && (kioninterCAN_getMissingAckErrorCounter() < KIONINTERCAN_MAX_MISSING_ACK_ERROR_COUNT);
}

uint8_t kionInterCAN_getTrySendHeartBeatCounter(void)
{
    return interCAN_TrySendHeartBeatCounter;
}
uint8_t kioninterCAN_getBMS_CPS_PDO_TX1RollingCounter(void)
{
    return BMS_CPS_PDO_TX1RollingCounter;
}
/**
 * @brief send function for CAN message
 */
void kioninterCAN_sendBMS_CPS_UDS_REQ(const CANMessage* msg)
{
    CAN_STATUS statusCAN = canIf_send(kioninterCANTransmitBMS_CPS_UDS_REQHandler, MESSAGE_DLC_8, msg->data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(KIONINTERCAN_NODE);
}

/**
 * @brief send function for CAN message
 */
void kioninterCAN_sendBMS_CPS_PDO_TX3(void)
{
    KIONINTER_BMS_CPS_PDO_TX3_t kioninter_bms_cps_pdo_tx3 = { 0 };
    kioninterCAN_prepareBMS_CPS_PDO_TX3(&kioninter_bms_cps_pdo_tx3);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx3.BMS_INFO_RemainingCapacity <= UMAXVAL_24BIT);
    data[0] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx3.BMS_INFO_RemainingCapacity) << 0u);
    data[1] = (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx3.BMS_INFO_RemainingCapacity) >> 8u);
    data[2] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx3.BMS_INFO_RemainingCapacity) >> 16u);

    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx3.BMS_INFO_TimeToWakeUp <= UMAXVAL_16BIT);
    data[3] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx3.BMS_INFO_TimeToWakeUp) << 0u);
    data[4] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx3.BMS_INFO_TimeToWakeUp) >> 8u);

    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx3.BMS_INFO_DeepDisPossible <= UMAXVAL_1BIT);
    data[5] |= ((uint64_t)kioninter_bms_cps_pdo_tx3.BMS_INFO_DeepDisPossible) << 0u;

    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx3.BMS_INFO_DeepDisImminent <= UMAXVAL_1BIT);
    data[5] |= ((uint64_t)kioninter_bms_cps_pdo_tx3.BMS_INFO_DeepDisImminent) << 1u;


    BMS_CPS_PDO_TX3RollingCounter++;
    BMS_CPS_PDO_TX3RollingCounter %= 16;
    kioninter_bms_cps_pdo_tx3.BMS_RX3_Counter = BMS_CPS_PDO_TX3RollingCounter;
    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx3.BMS_RX3_Counter <= UMAXVAL_4BIT);
    data[5] |= ((uint64_t)kioninter_bms_cps_pdo_tx3.BMS_RX3_Counter) << 4u;

    uint8_t array[MAX_MESSAGE_DLC] = { 0 };
    help_data2CRC_KION(KIONINTER_CAN_RX_BMS_CPS_PDO_TX3, data, array, MESSAGE_DLC_6);
    kioninter_bms_cps_pdo_tx3.BMS_RX3_Checksum = crc16_calculation_KION(array, MESSAGE_DLC_6 + 2u);
    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx3.BMS_RX3_Checksum <= UMAXVAL_16BIT);
    data[6] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx3.BMS_RX3_Checksum) << 0u);
    data[7] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx3.BMS_RX3_Checksum) >> 8u);

    // TODO Implement Middle CRC calculation	// Having the CRC not at the beginning or end is not implemented yet...

    CAN_STATUS statusCAN = canIf_send(kioninterCANTransmitBMS_CPS_PDO_TX3Handler, MESSAGE_DLC_8, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(KIONINTERCAN_NODE);
}

/**
 * @brief send function for CAN message
 */
void kioninterCAN_sendBMS_CPS_PDO_TX2(void)
{
    KIONINTER_BMS_CPS_PDO_TX2_t kioninter_bms_cps_pdo_tx2 = { 0 };
    kioninterCAN_prepareBMS_CPS_PDO_TX2(&kioninter_bms_cps_pdo_tx2);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx2.BMS_REQ_CPSout_I <= UMAXVAL_16BIT);
    data[0] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx2.BMS_REQ_CPSout_I) << 0u);
    data[1] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx2.BMS_REQ_CPSout_I) >> 8u);

    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx2.BMS_REQ_CPSoutBoost_I <= UMAXVAL_16BIT);
    data[2] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx2.BMS_REQ_CPSoutBoost_I) << 0u);
    data[3] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx2.BMS_REQ_CPSoutBoost_I) >> 8u);


    BMS_CPS_PDO_TX2RollingCounter++;
    BMS_CPS_PDO_TX2RollingCounter %= 16;
    kioninter_bms_cps_pdo_tx2.BMS_RX2_Counter = BMS_CPS_PDO_TX2RollingCounter;
    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx2.BMS_RX2_Counter <= UMAXVAL_4BIT);
    data[5] |= ((uint64_t)kioninter_bms_cps_pdo_tx2.BMS_RX2_Counter) << 4u;

    uint8_t array[MAX_MESSAGE_DLC] = { 0 };
    help_data2CRC_KION(KIONINTER_CAN_RX_BMS_CPS_PDO_TX2, data, array, MESSAGE_DLC_6);
    kioninter_bms_cps_pdo_tx2.BMS_RX2_Checksum = crc16_calculation_KION(array, MESSAGE_DLC_6 + 2u);
    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx2.BMS_RX2_Checksum <= UMAXVAL_16BIT);
    data[6] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx2.BMS_RX2_Checksum) << 0u);
    data[7] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx2.BMS_RX2_Checksum) >> 8u);

    // TODO Implement Middle CRC calculation	// Having the CRC not at the beginning or end is not implemented yet...

    CAN_STATUS statusCAN = canIf_send(kioninterCANTransmitBMS_CPS_PDO_TX2Handler, MESSAGE_DLC_8, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(KIONINTERCAN_NODE);
}

/**
 * @brief send function for CAN message
 */
void kioninterCAN_sendBMS_Heartbeat(void)
{
    KIONINTER_BMS_HEARTBEAT_t kioninter_bms_heartbeat = { 0 };
    kioninterCAN_prepareBMS_Heartbeat(&kioninter_bms_heartbeat);

    uint8_t data[MESSAGE_DLC_1] = { 0 };

    DEBUG_ASSERT(kioninter_bms_heartbeat.BMS_HBState <= UMAXVAL_8BIT);
    data[0] |= ((uint64_t)kioninter_bms_heartbeat.BMS_HBState) << 0u;


    CAN_STATUS statusCAN = canIf_send(kioninterCANTransmitBMS_HeartbeatHandler, MESSAGE_DLC_1, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(KIONINTERCAN_NODE);
}

/**
 * @brief send function for CAN message
 */
void kioninterCAN_sendBMS_TimeStamp(void)
{
    KIONINTER_BMS_TIMESTAMP_t kioninter_bms_timestamp = { 0 };
    kioninterCAN_prepareBMS_TimeStamp(&kioninter_bms_timestamp);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(kioninter_bms_timestamp.BMS_CANopen_Ms <= UMAXVAL_32BIT);
    data[0] |= (uint8_t)(((uint64_t)kioninter_bms_timestamp.BMS_CANopen_Ms) << 0u);
    data[1] = (uint8_t)(((uint64_t)kioninter_bms_timestamp.BMS_CANopen_Ms) >> 8u);
    data[2] = (uint8_t)(((uint64_t)kioninter_bms_timestamp.BMS_CANopen_Ms) >> 16u);
    data[3] |= (uint8_t)(((uint64_t)kioninter_bms_timestamp.BMS_CANopen_Ms) >> 24u);

    DEBUG_ASSERT(kioninter_bms_timestamp.BMS_CANopen_Days <= UMAXVAL_16BIT);
    data[4] |= (uint8_t)(((uint64_t)kioninter_bms_timestamp.BMS_CANopen_Days) << 0u);
    data[5] |= (uint8_t)(((uint64_t)kioninter_bms_timestamp.BMS_CANopen_Days) >> 8u);


    CAN_STATUS statusCAN = canIf_send(kioninterCANTransmitBMS_TimeStampHandler, MESSAGE_DLC_8, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(KIONINTERCAN_NODE);
}

/**
 * @brief send function for CAN message
 */
void kioninterCAN_sendBMS_CPS_SDO_REQ(void)
{
    KIONINTER_BMS_CPS_SDO_REQ_t kioninter_bms_cps_sdo_req = { 0 };
    kioninterCAN_prepareBMS_CPS_SDO_REQ(&kioninter_bms_cps_sdo_req);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(kioninter_bms_cps_sdo_req.BMS_SDO_TX_Data <= UMAXVAL_64BIT);
    data[0] |= (uint8_t)(((uint64_t)kioninter_bms_cps_sdo_req.BMS_SDO_TX_Data) << 0u);
    data[1] = (uint8_t)(((uint64_t)kioninter_bms_cps_sdo_req.BMS_SDO_TX_Data) >> 8u);
    data[2] = (uint8_t)(((uint64_t)kioninter_bms_cps_sdo_req.BMS_SDO_TX_Data) >> 16u);
    data[3] = (uint8_t)(((uint64_t)kioninter_bms_cps_sdo_req.BMS_SDO_TX_Data) >> 24u);
    data[4] = (uint8_t)(((uint64_t)kioninter_bms_cps_sdo_req.BMS_SDO_TX_Data) >> 32u);
    data[5] = (uint8_t)(((uint64_t)kioninter_bms_cps_sdo_req.BMS_SDO_TX_Data) >> 40u);
    data[6] = (uint8_t)(((uint64_t)kioninter_bms_cps_sdo_req.BMS_SDO_TX_Data) >> 48u);
    data[7] |= (uint8_t)(((uint64_t)kioninter_bms_cps_sdo_req.BMS_SDO_TX_Data) >> 56u);


    CAN_STATUS statusCAN = canIf_send(kioninterCANTransmitBMS_CPS_SDO_REQHandler, MESSAGE_DLC_8, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(KIONINTERCAN_NODE);
}

/**
 * @brief send function for CAN message
 */
void kioninterCAN_sendBMS_ModuleCotrol(void)
{
    KIONINTER_BMS_MODULECOTROL_t kioninter_bms_modulecotrol = { 0 };
    kioninterCAN_prepareBMS_ModuleCotrol(&kioninter_bms_modulecotrol);

    uint8_t data[MESSAGE_DLC_2] = { 0 };

    DEBUG_ASSERT(kioninter_bms_modulecotrol.BMS_ServiceID <= UMAXVAL_8BIT);
    data[0] |= ((uint64_t)kioninter_bms_modulecotrol.BMS_ServiceID) << 0u;

    DEBUG_ASSERT(kioninter_bms_modulecotrol.BMS_NodeID <= UMAXVAL_8BIT);
    data[1] |= ((uint64_t)kioninter_bms_modulecotrol.BMS_NodeID) << 0u;


    CAN_STATUS statusCAN = canIf_send(kioninterCANTransmitBMS_ModuleCotrolHandler, MESSAGE_DLC_2, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(KIONINTERCAN_NODE);
}

/**
 * @brief send function for CAN message
 */
void kioninterCAN_sendBMS_CPS_PDO_TX1(void)
{
    KIONINTER_BMS_CPS_PDO_TX1_t kioninter_bms_cps_pdo_tx1 = { 0 };
    kioninterCAN_prepareBMS_CPS_PDO_TX1(&kioninter_bms_cps_pdo_tx1);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx1.BMS_REQ_PowerDown <= UMAXVAL_1BIT);
    data[0] |= ((uint64_t)kioninter_bms_cps_pdo_tx1.BMS_REQ_PowerDown) << 5u;

    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx1.BMS_REQ_CPSout <= UMAXVAL_1BIT);
    data[0] |= ((uint64_t)kioninter_bms_cps_pdo_tx1.BMS_REQ_CPSout) << 7u;

    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx1.BMS_INFO_BMSstate <= UMAXVAL_8BIT);
    data[1] |= ((uint64_t)kioninter_bms_cps_pdo_tx1.BMS_INFO_BMSstate) << 0u;

    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx1.BMS_REQ_Min_V <= UMAXVAL_16BIT);
    data[3] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx1.BMS_REQ_Min_V) << 0u);
    data[4] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx1.BMS_REQ_Min_V) >> 8u);


    BMS_CPS_PDO_TX1RollingCounter++;
    BMS_CPS_PDO_TX1RollingCounter %= 16;
    kioninter_bms_cps_pdo_tx1.BMS_RX1_Counter = BMS_CPS_PDO_TX1RollingCounter;
    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx1.BMS_RX1_Counter <= UMAXVAL_4BIT);
    data[5] |= ((uint64_t)kioninter_bms_cps_pdo_tx1.BMS_RX1_Counter) << 4u;

    uint8_t array[MAX_MESSAGE_DLC] = { 0 };
    help_data2CRC_KION(KIONINTER_CAN_RX_BMS_CPS_PDO_TX1, data, array, MESSAGE_DLC_6);
    kioninter_bms_cps_pdo_tx1.BMS_RX1_Checksum = crc16_calculation_KION(array, MESSAGE_DLC_6 + 2u);
    DEBUG_ASSERT(kioninter_bms_cps_pdo_tx1.BMS_RX1_Checksum <= UMAXVAL_16BIT);
    data[6] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx1.BMS_RX1_Checksum) << 0u);
    data[7] |= (uint8_t)(((uint64_t)kioninter_bms_cps_pdo_tx1.BMS_RX1_Checksum) >> 8u);

    // TODO Implement Middle CRC calculation	// Having the CRC not at the beginning or end is not implemented yet...

    CAN_STATUS statusCAN = canIf_send(kioninterCANTransmitBMS_CPS_PDO_TX1Handler, MESSAGE_DLC_8, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(KIONINTERCAN_NODE);
}

/**
 * @brief send function for CAN message
 */
void kioninterCAN_sendBMS_ICDA_Request(const uint8_t* data)
{
    CAN_STATUS statusCAN = canIf_send(kioninterCANTransmitBMS_ICDA_RequestHandler, MESSAGE_DLC_8, data);

    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(KIONINTERCAN_NODE);
}

void kioninterCANSendInterleaved(void)
{
    const KionInterCanPdoConfig kionInterCanConfig[] = {
        { kioninterCAN_sendBMS_CPS_PDO_TX1, cpsPdoRequirements, 0 },
        { kioninterCAN_sendBMS_CPS_PDO_TX2, cpsPdoRequirements, 20 },
        { kioninterCAN_sendBMS_CPS_PDO_TX3, cpsPdoRequirements, 40 },
        { kioninterCAN_sendBMS_TimeStamp, cpsTimestampRequirements, 60 },
    };

    for(uint8_t i = 0; i < (sizeof(kionInterCanConfig) / sizeof(KionInterCanPdoConfig)); i++)
    {
        if((intervalCounter100ms == kionInterCanConfig[i].timeOffset)
           && ((kionInterCanConfig[i].requirementFunction != NULL) && (kionInterCanConfig[i].requirementFunction() == true))
           && (kionInterCanConfig[i].sendFunction != NULL))
        {
            kionInterCanConfig[i].sendFunction();
        }
    }

    intervalCounter100ms += 10u;
    intervalCounter100ms %= 100u;
}


void kioninterCANSend40(void)
{
    if((stmFct_getCpsCommunicationEnable() == true) && (kioninterCAN_getMissingAckErrorCounter() < KIONINTERCAN_MAX_MISSING_ACK_ERROR_COUNT))
    {
        kioninterCAN_sendBMS_Heartbeat();
        interCAN_TrySendHeartBeatCounter++;
    }
}

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
/**
 * @brief send function for CAN message
 * If send Id equals to receive Id -> broadcast (all participants will receive the message)
 * @param receiveId uC Id of the receiving uC.
 */
void kioninterCAN_sendStrPM_SyM_Val1(void)
{
    KIONSTRPM_SYM_VAL1_t kioninter_strpm_sym_val1_t = { 0 };
    kioninterCAN_prepareStrPM_SyM_Val1(&kioninter_strpm_sym_val1_t);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    uint8_t StrPM_SyM_Val1StateTemp = kioninter_strpm_sym_val1_t.StrPM_SyM_Val1State;
    DEBUG_ASSERT(StrPM_SyM_Val1StateTemp <= UMAXVAL_8BIT);
    data[1] |= StrPM_SyM_Val1StateTemp;

    uint8_t StrPM_SyM_Val1MastertypTemp = kioninter_strpm_sym_val1_t.StrPM_SyM_Val1Mastertyp;
    DEBUG_ASSERT(StrPM_SyM_Val1MastertypTemp <= UMAXVAL_2BIT);
    data[2] |= StrPM_SyM_Val1MastertypTemp;

    uint8_t StrPM_SyM_Val1SWVersionTemp = kioninter_strpm_sym_val1_t.StrPM_SyM_Val1SWVersion;
    DEBUG_ASSERT(StrPM_SyM_Val1SWVersionTemp <= UMAXVAL_8BIT);
    data[2] |= (StrPM_SyM_Val1SWVersionTemp << 2) & UINT8_MAX;
    data[3] |= (StrPM_SyM_Val1SWVersionTemp >> 6) & UINT8_MAX;

    uint8_t StrPM_SyM_Val1HWVersionTemp = kioninter_strpm_sym_val1_t.StrPM_SyM_Val1HWVersion;
    DEBUG_ASSERT(StrPM_SyM_Val1HWVersionTemp <= UMAXVAL_8BIT);
    data[3] |= (StrPM_SyM_Val1HWVersionTemp << 2) & UINT8_MAX;
    data[4] |= (StrPM_SyM_Val1HWVersionTemp >> 6) & UINT8_MAX;

    uint8_t StrPM_SyM_Val1HviTemp = kioninter_strpm_sym_val1_t.StrPM_SyM_Val1Hvi;
    DEBUG_ASSERT(StrPM_SyM_Val1HviTemp <= UMAXVAL_1BIT);
    data[4] |= (StrPM_SyM_Val1HviTemp << 2) & UINT8_MAX;

    uint8_t StrPM_SyM_Val1ErrorRequestTemp = kioninter_strpm_sym_val1_t.StrPM_SyM_Val1ErrorRequest;
    DEBUG_ASSERT(StrPM_SyM_Val1ErrorRequestTemp <= UMAXVAL_1BIT);
    data[4] |= (StrPM_SyM_Val1ErrorRequestTemp << 3) & UINT8_MAX;

    // uint8_t StrPM_SyM_Val1ShutOffRequest = kioninter_strpm_sym_val1_t.StrPM_SyM_Val1ShutOffRequest;
    // DEBUG_ASSERT(StrPM_SyM_Val1ShutOffRequest <= UMAXVAL_1BIT);
    // data[4] |= (StrPM_SyM_Val1ShutOffRequest << 4) & UINT8_MAX;

    uint8_t StrPM_SyM_Val1T2Reac = kioninter_strpm_sym_val1_t.StrPM_SyM_Val1T2Reac;
    DEBUG_ASSERT(StrPM_SyM_Val1T2Reac <= UMAXVAL_4BIT);
    data[5] |= (StrPM_SyM_Val1T2Reac << 4) & UINT8_MAX;

    uint8_t StrPM_SyM_Val1HighSev = kioninter_strpm_sym_val1_t.StrPM_SyM_Val1HighSev;
    DEBUG_ASSERT(StrPM_SyM_Val1HighSev <= UMAXVAL_4BIT);
    data[5] |= (StrPM_SyM_Val1HighSev)&UINT8_MAX;


    uint8_t StrPM_SyM_Val1CtRollTemp = kioninter_strpm_sym_val1_t.StrPM_SyM_Val1CtRoll;
    data[6] |= StrPM_SyM_Val1CtRollTemp;

    uint8_t array[MAX_MESSAGE_DLC_INTERCAN] = { 0 }; /**< used for crc calculation in accordance with Autosar E2E profile A1 */

    help_data2CRC_SAE8(INTER_CAN_RX_STRPM_SYM_VAL1, data, array, MESSAGE_DLC_8);

    data[7] = crc8_calculation(array, MESSAGE_DLC_8 + 1u);

    canIf_send(kioninterCANTransmitStrPM_SyM_Val1Handler, MESSAGE_DLC_8, data);
}
#endif

void kioninterCANSend10(void)
{
#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
    if(kioninterCAN_getMissingAckErrorCounter() < KIONINTERCAN_MAX_MISSING_ACK_ERROR_COUNT)
    {
        kioninterCAN_sendStrPM_SyM_Val1();
    }
#endif

    kioninterCANSendInterleaved();
}
