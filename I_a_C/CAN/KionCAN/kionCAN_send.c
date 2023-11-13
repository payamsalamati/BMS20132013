/**
 *
 * @file kionCAN_send.c
 * @created on Tue Feb 16 14:15:58 CET 2021
 * @brief This module write data from the structs to the CAN messages and calls can_send
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - kionADC_Values0: --
 * - kionADC_Values1: --
 * - kionADC_Values2: --
 * - kionADC_Values3: --
 * - kiondebugDTC: --
 * - kionlib_uds: -UDS responses from LIB with KION protocol-
 * - kionlib_sdo_tx: -SDO Tx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC-
 * - kionlib_pdo_tx7: -PDO 7 (Tx), node 0x77 (LIB with KION protocol)-
 * - kionlib_pdo_tx6: -PDO 6 (Tx), node 0x77 (LIB with KION protocol)-
 * - kionlib_pdo_tx5: -PDO 5 (Tx), node 0x77 (LIB with KION protocol)-
 * - kionlib_pdo_tx4: -PDO 4 (Tx), node 0x27 (LIB with KION protocol)-
 * - kionlib_pdo_tx3: -PDO 3 (Tx), node 0x27 (LIB with KION protocol)-
 * - kionlib_pdo_tx2: -PDO 2 (Tx), node 0x27 (LIB with KION protocol)-
 * - kionlib_pdo_tx1: -PDO 1 (Tx), node 0x27 (LIB with KION protocol)-
 * - kionlib_heartbeat: -heartbeat (NMT error control), node 0x27 (LIB with KION protocol)-
 * - kionlib_emergency: -emergency (EMCY), node 0x27 (LIB with KION protocol)-
 * - kioncps_uds: -UDS responses from CPS in LIB with KION protocol-
 * - kionHeartbtBms: -Network Management, Error Control, Battery management system Heartbeat-
 * - kionDiagRespBms: --
 * - kionBmsSDOtx: -CAN Open: Data for Service data object (SDO) send by BMS-
 * - kiondebugValues1: --
 */

//******************* INCLUDES ********************************//
#include "emcy.h"
#include "kionCAN.h"
#include "osIf.h"
#include "types.h"
#include "debug.h"
#include "stateFunctions.h"
#include "canOpenStmFct.h"
#include "canopen_config.h"
#include "crcFut.h"
#include "protocolSelection.h"
#include "sbc_fs4500c.h"
#include "kioninterCAN.h"
#include "canProtocol.h"


typedef void (*KionCanSendFunction)(void);
typedef bool (*KionCanSendFunctionRequirement)(void);

typedef struct
{
    KionCanSendFunction sendFunction;
    KionCanSendFunctionRequirement requirementFunction;
    uint16_t timeOffset;
} KionCanPdoConfig;

MEM_CAN static uint8_t lib_pdo_tx7_message_counter = 0;

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
MEM_SEC_PARAMETER bool sendDebugValues = true;
#else
MEM_SEC_PARAMETER bool sendDebugValues = false;
#endif

MEM_CAN static uint16_t intervalCounter100ms = 0;

static bool kionPdoRequirements(void);

/* ---------------------------------  FUNCTION DEFINITIONS  -------------------------------- */

static bool kionPdoRequirements(void)
{
    return (canOpenStm_getCanOpenState(&canOpenConfigKion) == canOpen_State_Operational) && (missingAckErrorCntExternal < EXTERNALCAN_MAX_MISSING_ACK_ERROR_COUNT);
}

uint8_t kionCAN_getLib_pdo_tx7_message_counter(void)
{
    return lib_pdo_tx7_message_counter;
}

void kionCAN_resetLib_pdo_tx7_message_counter(void)
{
    lib_pdo_tx7_message_counter = 0xFu;  //set to max value. Next value is "0"
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_uds(const CANMessage* msg)
{
    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_udsHandler, MESSAGE_DLC_8, msg->data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_sdo_tx(const CANMessage* msg)
{
    KION_LIB_SDO_TX_t kion_lib_sdo_tx = { 0 };
    kionCAN_preparelib_sdo_tx(&kion_lib_sdo_tx);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    for(uint8_t i = 0; i < MESSAGE_DLC_8; i++)
    {
        data[i] = msg->data[i];
    }

    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_sdo_txHandler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_pdo_tx8(void)
{
    KION_LIB_PDO_TX8_t kion_lib_pdo_tx8 = { 0 };
    kionCAN_preparelib_pdo_tx8(&kion_lib_pdo_tx8);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(kion_lib_pdo_tx8.lib_current_unfiltered <= UMAXVAL_19BIT);
    data[0] = (uint8_t)(((uint64_t)kion_lib_pdo_tx8.lib_current_unfiltered) << 0u);
    data[1] = (uint8_t)(((uint64_t)kion_lib_pdo_tx8.lib_current_unfiltered) >> 8u);
    data[2] = (uint8_t)(((uint64_t)kion_lib_pdo_tx8.lib_current_unfiltered) >> 16u);

    DEBUG_ASSERT(kion_lib_pdo_tx8.lib_voltage_in_front_of_contactor_unfiltered <= UMAXVAL_18BIT);
    data[2] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx8.lib_voltage_in_front_of_contactor_unfiltered) << 3u);
    data[3] = (uint8_t)(((uint64_t)kion_lib_pdo_tx8.lib_voltage_in_front_of_contactor_unfiltered) >> 5u);
    data[4] = (uint8_t)(((uint64_t)kion_lib_pdo_tx8.lib_voltage_in_front_of_contactor_unfiltered) >> 13u);

    DEBUG_ASSERT(kion_lib_pdo_tx8.lib_voltage_after_contactor_unfiltered <= UMAXVAL_18BIT);
    data[4] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx8.lib_voltage_after_contactor_unfiltered) << 5u);
    data[5] = (uint8_t)(((uint64_t)kion_lib_pdo_tx8.lib_voltage_after_contactor_unfiltered) >> 3u);
    data[6] = (uint8_t)(((uint64_t)kion_lib_pdo_tx8.lib_voltage_after_contactor_unfiltered) >> 11u);

    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_pdo_tx8Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_pdo_tx7(void)
{
    KION_LIB_PDO_TX7_t kion_lib_pdo_tx7 = { 0 };
    kionCAN_preparelib_pdo_tx7(&kion_lib_pdo_tx7);

    uint8_t data[MESSAGE_DLC_8] = { 0 };
    // @req CB-74983
    DEBUG_ASSERT(kion_lib_pdo_tx7.lib_powerpath_ok <= UMAXVAL_2BIT);
    data[0] |= ((uint64_t)kion_lib_pdo_tx7.lib_powerpath_ok) << 0u;

    // @req CB-75121
    lib_pdo_tx7_message_counter++;
    lib_pdo_tx7_message_counter %= 16;
    kion_lib_pdo_tx7.lib_pdo_tx7_message_counter = lib_pdo_tx7_message_counter;

    // @req CB-74984
    DEBUG_ASSERT(kion_lib_pdo_tx7.lib_pdo_tx7_message_counter <= UMAXVAL_4BIT);
    data[5] |= ((uint64_t)kion_lib_pdo_tx7.lib_pdo_tx7_message_counter) << 4u;

    // @req CB-75122
    uint8_t array[MAX_MESSAGE_DLC] = { 0 };
    help_data2CRC_KION(KION_CAN_RX_LIB_PDO_TX7, data, array, MESSAGE_DLC_6);
    kion_lib_pdo_tx7.lib_pdo_tx7_checksum = crc16_calculation_KION(array, MESSAGE_DLC_6 + 2u);
    // @req CB-74985
    DEBUG_ASSERT(kion_lib_pdo_tx7.lib_pdo_tx7_checksum <= UMAXVAL_16BIT);
    data[6] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx7.lib_pdo_tx7_checksum) << 0u);
    data[7] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx7.lib_pdo_tx7_checksum) >> 8u);

    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_pdo_tx7Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_pdo_tx6(void)
{
    KION_LIB_PDO_TX6_t kion_lib_pdo_tx6 = { 0 };
    kionCAN_preparelib_pdo_tx6(&kion_lib_pdo_tx6);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    // @req CB-74974
    DEBUG_ASSERT(kion_lib_pdo_tx6.lib_max_charging_current_2s <= UMAXVAL_18BIT);
    data[0] = (uint8_t)(((uint64_t)kion_lib_pdo_tx6.lib_max_charging_current_2s) << 0u);
    data[1] = (uint8_t)(((uint64_t)kion_lib_pdo_tx6.lib_max_charging_current_2s) >> 8u);
    data[2] = (uint8_t)(((uint64_t)kion_lib_pdo_tx6.lib_max_charging_current_2s) >> 16u);

    // @req CB-74975
    DEBUG_ASSERT(kion_lib_pdo_tx6.lib_max_charging_current_100s <= UMAXVAL_18BIT);
    data[2] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx6.lib_max_charging_current_100s) << 2u);
    data[3] = (uint8_t)(((uint64_t)kion_lib_pdo_tx6.lib_max_charging_current_100s) >> 6u);
    data[4] = (uint8_t)(((uint64_t)kion_lib_pdo_tx6.lib_max_charging_current_100s) >> 14u);

    // @req CB-74978
    DEBUG_ASSERT(kion_lib_pdo_tx6.lib_soc_without_soh_fine <= UMAXVAL_10BIT);
    data[4] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx6.lib_soc_without_soh_fine) << 6u);
    data[5] = (uint8_t)(((uint64_t)kion_lib_pdo_tx6.lib_soc_without_soh_fine) >> 2u);

    // @req CB-74980
    DEBUG_ASSERT(kion_lib_pdo_tx6.lib_min_temperature <= UMAXVAL_8BIT);
    data[6] = (uint8_t)(((uint64_t)kion_lib_pdo_tx6.lib_min_temperature) << 0u);

    // @req CB-74981
    DEBUG_ASSERT(kion_lib_pdo_tx6.lib_max_temperature <= UMAXVAL_8BIT);
    data[7] = (uint8_t)(((uint64_t)kion_lib_pdo_tx6.lib_max_temperature) << 0u);

    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_pdo_tx6Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_pdo_tx5(void)
{
    KION_LIB_PDO_TX5_t kion_lib_pdo_tx5 = { 0 };
    kionCAN_preparelib_pdo_tx5(&kion_lib_pdo_tx5);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    // @req CB-74969
    // DEBUG_ASSERT(kion_lib_pdo_tx5.lib_max_discharging_current_2s <= UMAXVAL_18BIT);  //out commented, due to error in kbs algorithm
    data[0] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx5.lib_max_discharging_current_2s) << 0u);
    data[1] = (uint8_t)(((uint64_t)kion_lib_pdo_tx5.lib_max_discharging_current_2s) >> 8u);
    data[2] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx5.lib_max_discharging_current_2s) >> 16u);

    // @req CB-74971
    DEBUG_ASSERT(kion_lib_pdo_tx5.lib_max_discharging_current_100s <= UMAXVAL_18BIT);
    data[2] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx5.lib_max_discharging_current_100s) << 2u);
    data[3] = (uint8_t)(((uint64_t)kion_lib_pdo_tx5.lib_max_discharging_current_100s) >> 6u);
    data[4] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx5.lib_max_discharging_current_100s) >> 14u);


    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_pdo_tx5Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_pdo_tx4(void)
{
    KION_LIB_PDO_TX4_t kion_lib_pdo_tx4 = { 0 };
    kionCAN_preparelib_pdo_tx4(&kion_lib_pdo_tx4);

    uint8_t data[MESSAGE_DLC_8] = { 0 };
    // @req CB-74964
    DEBUG_ASSERT(kion_lib_pdo_tx4.lib_max_charging_voltage <= UMAXVAL_18BIT);
    data[0] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx4.lib_max_charging_voltage) << 0u);
    data[1] = (uint8_t)(((uint64_t)kion_lib_pdo_tx4.lib_max_charging_voltage) >> 8u);
    data[2] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx4.lib_max_charging_voltage) >> 16u);

    // @req CB-74965
    //DEBUG_ASSERT(kion_lib_pdo_tx4.lib_max_charging_power_2s <= UMAXVAL_19BIT);
    data[2] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx4.lib_max_charging_power_2s) << 2u);
    data[3] = (uint8_t)(((uint64_t)kion_lib_pdo_tx4.lib_max_charging_power_2s) >> 6u);
    data[4] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx4.lib_max_charging_power_2s) >> 14u);

    // @req CB-74966
    DEBUG_ASSERT(kion_lib_pdo_tx4.lib_max_charging_power_100s <= UMAXVAL_19BIT);
    data[4] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx4.lib_max_charging_power_100s) << 5u);
    data[5] = (uint8_t)(((uint64_t)kion_lib_pdo_tx4.lib_max_charging_power_100s) >> 3u);
    data[6] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx4.lib_max_charging_power_100s) >> 11u);

    // @req CB-74967
    DEBUG_ASSERT(kion_lib_pdo_tx4.lib_soc_without_soh <= UMAXVAL_8BIT);
    data[7] |= ((uint64_t)kion_lib_pdo_tx4.lib_soc_without_soh) << 0u;


    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_pdo_tx4Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_pdo_tx3(void)
{
    KION_LIB_PDO_TX3_t kion_lib_pdo_tx3 = { 0 };
    kionCAN_preparelib_pdo_tx3(&kion_lib_pdo_tx3);

    uint8_t data[MESSAGE_DLC_8] = { 0 };
    // @req CB-74959
    DEBUG_ASSERT(kion_lib_pdo_tx3.lib_min_discharging_voltage <= UMAXVAL_18BIT);
    data[0] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx3.lib_min_discharging_voltage) << 0u);
    data[1] = (uint8_t)(((uint64_t)kion_lib_pdo_tx3.lib_min_discharging_voltage) >> 8u);
    data[2] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx3.lib_min_discharging_voltage) >> 16u);

    // @req CB-74960
    //DEBUG_ASSERT(kion_lib_pdo_tx3.lib_max_discharging_power_2s <= UMAXVAL_19BIT);
    data[2] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx3.lib_max_discharging_power_2s) << 2u);
    data[3] = (uint8_t)(((uint64_t)kion_lib_pdo_tx3.lib_max_discharging_power_2s) >> 6u);
    data[4] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx3.lib_max_discharging_power_2s) >> 14u);

    // @req CB-74961
    // DEBUG_ASSERT(kion_lib_pdo_tx3.lib_max_discharging_power_100s <= UMAXVAL_19BIT);
    data[4] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx3.lib_max_discharging_power_100s) << 5u);
    data[5] = (uint8_t)(((uint64_t)kion_lib_pdo_tx3.lib_max_discharging_power_100s) >> 3u);
    data[6] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx3.lib_max_discharging_power_100s) >> 11u);

    // @req CB-74962
    DEBUG_ASSERT(kion_lib_pdo_tx3.lib_soc_with_soh <= UMAXVAL_8BIT);
    data[7] |= ((uint64_t)kion_lib_pdo_tx3.lib_soc_with_soh) << 0u;


    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_pdo_tx3Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_pdo_tx2(void)
{
    KION_LIB_PDO_TX2_t kion_lib_pdo_tx2 = { 0 };
    kionCAN_preparelib_pdo_tx2(&kion_lib_pdo_tx2);

    uint8_t data[MESSAGE_DLC_8] = { 0 };
    // @req CB-74954
    DEBUG_ASSERT(kion_lib_pdo_tx2.lib_voltage_in_front_of_contacto <= UMAXVAL_18BIT);
    data[0] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx2.lib_voltage_in_front_of_contacto) << 0u);
    data[1] = (uint8_t)(((uint64_t)kion_lib_pdo_tx2.lib_voltage_in_front_of_contacto) >> 8u);
    data[2] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx2.lib_voltage_in_front_of_contacto) >> 16u);

    // @req CB-74955
    DEBUG_ASSERT(kion_lib_pdo_tx2.lib_voltage_after_contactor <= UMAXVAL_18BIT);
    data[2] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx2.lib_voltage_after_contactor) << 2u);
    data[3] = (uint8_t)(((uint64_t)kion_lib_pdo_tx2.lib_voltage_after_contactor) >> 6u);
    data[4] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx2.lib_voltage_after_contactor) >> 14u);

    // @req CB-74956
    DEBUG_ASSERT(kion_lib_pdo_tx2.lib_power <= UMAXVAL_20BIT);
    data[4] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx2.lib_power) << 4u);
    data[5] = (uint8_t)(((uint64_t)kion_lib_pdo_tx2.lib_power) >> 4u);
    data[6] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx2.lib_power) >> 12u);

    // @req CB-74957
    DEBUG_ASSERT(kion_lib_pdo_tx2.lib_state_of_health <= UMAXVAL_8BIT);
    data[7] |= ((uint64_t)kion_lib_pdo_tx2.lib_state_of_health) << 0u;


    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_pdo_tx2Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_pdo_tx1(void)
{
    KION_LIB_PDO_TX1_t kion_lib_pdo_tx1 = { 0 };
    kionCAN_preparelib_pdo_tx1(&kion_lib_pdo_tx1);

    uint8_t data[MESSAGE_DLC_8] = { 0 };
    // @req CB-74938
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_init_complete <= UMAXVAL_2BIT);
    data[0] |= ((uint64_t)kion_lib_pdo_tx1.lib_init_complete) << 0u;

    // @req CB-74939
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_ready <= UMAXVAL_2BIT);
    data[0] |= ((uint64_t)kion_lib_pdo_tx1.lib_ready) << 2u;

    // @req CB-74940
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_in_driving_mode <= UMAXVAL_2BIT);
    data[0] |= ((uint64_t)kion_lib_pdo_tx1.lib_in_driving_mode) << 4u;

    // @req CB-74941
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_in_charging_mode <= UMAXVAL_2BIT);
    data[0] |= ((uint64_t)kion_lib_pdo_tx1.lib_in_charging_mode) << 6u;

    // @req CB-74942
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_error <= UMAXVAL_2BIT);
    data[1] |= ((uint64_t)kion_lib_pdo_tx1.lib_error) << 0u;

    // @req CB-74943
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_current_limited <= UMAXVAL_2BIT);
    data[1] |= ((uint64_t)kion_lib_pdo_tx1.lib_current_limited) << 2u;

    // @req CB-74944
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_emergency_operation <= UMAXVAL_2BIT);
    data[1] |= ((uint64_t)kion_lib_pdo_tx1.lib_emergency_operation) << 4u;

    // @req CB-74945
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_shock_warning <= UMAXVAL_2BIT);
    data[1] |= ((uint64_t)kion_lib_pdo_tx1.lib_shock_warning) << 6u;

    // @req CB-74946
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_fatal_error <= UMAXVAL_2BIT);
    data[2] |= ((uint64_t)kion_lib_pdo_tx1.lib_fatal_error) << 0u;

    // @req CB-74947
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_temperature_too_low <= UMAXVAL_2BIT);
    data[2] |= ((uint64_t)kion_lib_pdo_tx1.lib_temperature_too_low) << 2u;

    // @req CB-74948
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_temperature_too_high <= UMAXVAL_2BIT);
    data[2] |= ((uint64_t)kion_lib_pdo_tx1.lib_temperature_too_high) << 4u;

    // @req CB-74949
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_service_required <= UMAXVAL_2BIT);
    data[2] |= ((uint64_t)kion_lib_pdo_tx1.lib_service_required) << 6u;

    // @req CB-89128
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_cps_output_active <= UMAXVAL_2BIT);
    data[3] |= ((uint64_t)kion_lib_pdo_tx1.lib_cps_output_active) << 0u;

    // @req CB-89129
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_cps_output_deactivation_inhibit <= UMAXVAL_2BIT);
    data[3] |= ((uint64_t)kion_lib_pdo_tx1.lib_cps_output_deactivation_inhibit) << 2u;

    data[3] |= 240u;

    // @req CB-74952
    DEBUG_ASSERT(kion_lib_pdo_tx1.lib_current <= UMAXVAL_19BIT);
    data[4] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx1.lib_current) << 0u);
    data[5] = (uint8_t)(((uint64_t)kion_lib_pdo_tx1.lib_current) >> 8u);
    data[6] |= (uint8_t)(((uint64_t)kion_lib_pdo_tx1.lib_current) >> 16u);


    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_pdo_tx1Handler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_heartbeat(void)
{
    KION_LIB_HEARTBEAT_t kion_lib_heartbeat = { 0 };
    kionCAN_preparelib_heartbeat(&kion_lib_heartbeat);

    uint8_t data[MESSAGE_DLC_1] = { 0 };

    DEBUG_ASSERT(kion_lib_heartbeat.canopen_state_lib <= UMAXVAL_7BIT);
    data[0] |= ((uint64_t)kion_lib_heartbeat.canopen_state_lib) << 0u;


    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_heartbeatHandler, MESSAGE_DLC_1, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
        canOpenStm_setHeartbeatSent(&canOpenConfigKion);
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendLib_emergency(const uint8_t* emcyData)
{
    CAN_STATUS statusCAN = canIf_send(kionCANTransmitlib_emergencyHandler, MESSAGE_DLC_8, emcyData);
    if(statusCAN == CAN_SUCCESS)
    {  // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendCps_uds(const CANMessage* msg)
{
    CAN_STATUS statusCAN = canIf_send(kionCANTransmitcps_udsHandler, MESSAGE_DLC_8, msg->data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendDiagRespBms(void)
{
    KION_DIAGRESPBMS_t kion_diagrespbms = { 0 };
    kionCAN_prepareDiagRespBms(&kion_diagrespbms);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(kion_diagrespbms.BmsRsPCI <= UMAXVAL_8BIT);
    data[0] |= ((uint64_t)kion_diagrespbms.BmsRsPCI) << 0u;

    DEBUG_ASSERT(kion_diagrespbms.BmsRsData <= UMAXVAL_56BIT);
    data[1] |= (uint8_t)(((uint64_t)kion_diagrespbms.BmsRsData) << 0u);
    data[2] = (uint8_t)(((uint64_t)kion_diagrespbms.BmsRsData) >> 8u);
    data[3] = (uint8_t)(((uint64_t)kion_diagrespbms.BmsRsData) >> 16u);
    data[4] = (uint8_t)(((uint64_t)kion_diagrespbms.BmsRsData) >> 24u);
    data[5] = (uint8_t)(((uint64_t)kion_diagrespbms.BmsRsData) >> 32u);
    data[6] = (uint8_t)(((uint64_t)kion_diagrespbms.BmsRsData) >> 40u);
    data[7] |= (uint8_t)(((uint64_t)kion_diagrespbms.BmsRsData) >> 48u);


    CAN_STATUS statusCAN = canIf_send(kionCANTransmitDiagRespBmsHandler, MESSAGE_DLC_8, data);
    if(statusCAN != CAN_SUCCESS)
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

/**
 * @brief send function for CAN message
 */
void kionCAN_sendDebugDTC(DTC dtc, DEM_Severity severity)
{
    uint8_t data[MESSAGE_DLC_8] = { 0 };

    data[0] = (dtc >> 0u) & 0xff;
    data[1] = (dtc >> 8u) & 0xff;
    data[2] = (dtc >> 16u) & 0xff;
    data[3] = (dtc >> 24u) & 0xff;

    data[4] = severity & 0xff;

    CAN_STATUS statusCAN = canIf_send(kionCANTransmitdebugDTCHandler, MESSAGE_DLC_5, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}


#if defined(SW_RESET_ANALYSIS_CAN_DATA)
void kionCAN_sendTaskCurrentTimes(void)
{
    KION_CURRENTTASKTIMES_t kion_currentTasktimes;
    kionCAN_prepareTaskCurrentTimes(&kion_currentTasktimes);
    uint8_t data[MESSAGE_DLC_8] = { 0 };

    data[0] = kion_currentTasktimes.currentSafetyTaskTime;
    data[1] = ((kion_currentTasktimes.currentSafetyTaskTime >> 8) & 0x03);

    data[1] |= (kion_currentTasktimes.currentAfeTaskTime << 2);
    data[2] = (kion_currentTasktimes.currentAfeTaskTime >> 6) & 0x0F;

    data[2] |= (kion_currentTasktimes.currentNVMTaskTime << 4);
    data[3] = (kion_currentTasktimes.currentNVMTaskTime >> 4) & 0x3F;

    data[3] |= (kion_currentTasktimes.currentLimitCheckTaskTime << 6);
    data[4] = (kion_currentTasktimes.currentLimitCheckTaskTime >> 2);

    data[5] |= (kion_currentTasktimes.currentCanSendTaskTime);
    data[6] |= ((kion_currentTasktimes.currentCanSendTaskTime >> 8) & 0x03);

    data[6] |= (kion_currentTasktimes.currentCanReceiveTaskTime << 2);
    data[7] = (kion_currentTasktimes.currentCanReceiveTaskTime >> 6) & 0x0F;

    CAN_STATUS statusCAN = canIf_send(kionCANTransmitdebugTaskCurrentTimeHandler, MESSAGE_DLC_8, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

void kionCAN_sendTaskMaxTimes(void)
{
    KION_MAXTASKTIMES_t kion_maxTasktimes;
    kionCAN_prepareTaskMaxTimes(&kion_maxTasktimes);
    uint8_t data[MESSAGE_DLC_8] = { 0 };

    data[0] = kion_maxTasktimes.maxSafetyTaskTime;
    data[1] = ((kion_maxTasktimes.maxSafetyTaskTime >> 8) & 0x03);

    data[1] |= (kion_maxTasktimes.maxAfeTaskTime << 2);
    data[2] = (kion_maxTasktimes.maxAfeTaskTime >> 6) & 0x0F;

    data[2] |= (kion_maxTasktimes.maxNVMTaskTime << 4);
    data[3] = (kion_maxTasktimes.maxNVMTaskTime >> 4) & 0x3F;

    data[3] |= (kion_maxTasktimes.maxLimitCheckTaskTime << 6);
    data[4] = (kion_maxTasktimes.maxLimitCheckTaskTime >> 2);

    data[5] |= (kion_maxTasktimes.maxCanSendTaskTime);
    data[6] |= ((kion_maxTasktimes.maxCanSendTaskTime >> 8) & 0x03);

    data[6] |= (kion_maxTasktimes.maxCanReceiveTaskTime << 2);
    data[7] = (kion_maxTasktimes.maxCanReceiveTaskTime >> 6) & 0x0F;

    CAN_STATUS statusCAN = canIf_send(kionCANTransmitdebugTaskMaxTimeHandler, MESSAGE_DLC_8, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

void kionCAN_sendSBCStatus(uint8_t watchdogRefreshState, uint8_t idCounter)
{
    KION_SBCSTATUS_t kion_sbcStatus;
    kionCAN_prepareSBCStatus(&kion_sbcStatus);
    uint8_t data[MESSAGE_DLC_3] = { 0 };

    data[0] = (uint8_t)watchdogRefreshState;
    data[1] = (uint8_t)kion_sbcStatus.wdCounter;
    data[2] = (uint8_t)idCounter;

    CAN_STATUS statusCAN = canIf_send(kionCANTransmitdebugSBCStatusHandler, MESSAGE_DLC_3, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

void kionCAN_sendMutexPendFailedSignal(MutexAnalysisData pendingMutexAnalysis, uint8_t mutexPendingSource, uint8_t mutexRequestingSource, OSIf_Error error)
{
    uint8_t data[MESSAGE_DLC_8] = { 0 };

    uint32_t mutexPendingDuration = osIf_getTimeDifference(pendingMutexAnalysis.mutexPendingStartingTime);
    int16_t osError               = (int16_t)error;

    data[0] = (uint8_t)mutexPendingSource;
    data[1] |= (uint8_t)mutexRequestingSource;
    data[2] |= (uint8_t)mutexPendingDuration;
    data[3] |= (uint8_t)(mutexPendingDuration >> 8);
    data[4] |= (uint8_t)(mutexPendingDuration >> 16);
    data[5] |= (uint8_t)(mutexPendingDuration >> 24);
    data[6] |= (int8_t)(osError);
    data[7] |= (int8_t)(osError >> 8);

    CAN_STATUS statusCAN = canIf_send(kionCANTransmitMutexPendFailedHandler, MESSAGE_DLC_8, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}

void kionCAN_sendMutexPostFailedSignal(uint8_t mutexPostSource, OSIf_Error error)
{
    uint8_t data[MESSAGE_DLC_3] = { 0 };

    int16_t osError = (int16_t)error;

    data[0] = (uint8_t)mutexPostSource;
    data[1] |= (int8_t)(osError);
    data[2] |= (int8_t)(osError >> 8);

    CAN_STATUS statusCAN = canIf_send(kionCANTransmitMutexPostFailedHandler, MESSAGE_DLC_3, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}
#endif


void kionCAN_sendDebugValues1(void)
{
    KION_DEBUGVALUES1_t kion_debugvalues1 = { 0 };
    kionCAN_preparedebugValues1(&kion_debugvalues1);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(kion_debugvalues1.CellVoltageMax <= UMAXVAL_16BIT);
    data[0] |= (uint8_t)(((uint64_t)kion_debugvalues1.CellVoltageMax) << 0u);
    data[1] |= (uint8_t)(((uint64_t)kion_debugvalues1.CellVoltageMax) >> 8u);

    DEBUG_ASSERT(kion_debugvalues1.CellVoltageMin <= UMAXVAL_16BIT);
    data[2] |= (uint8_t)(((uint64_t)kion_debugvalues1.CellVoltageMin) << 0u);
    data[3] |= (uint8_t)(((uint64_t)kion_debugvalues1.CellVoltageMin) >> 8u);

    DEBUG_ASSERT((kion_debugvalues1.CellTemperatureMax >= INT8_MIN) && (kion_debugvalues1.CellTemperatureMax <= INT8_MAX));
    data[4] |= ((uint64_t)kion_debugvalues1.CellTemperatureMax) << 0u;

    DEBUG_ASSERT((kion_debugvalues1.CellTemperatureMin >= INT8_MIN) && (kion_debugvalues1.CellTemperatureMin <= INT8_MAX));
    data[5] |= ((uint64_t)kion_debugvalues1.CellTemperatureMin) << 0u;

    DEBUG_ASSERT(kion_debugvalues1.RelaySupplyMin <= UMAXVAL_16BIT);
    data[6] |= (uint8_t)(((uint64_t)kion_debugvalues1.RelaySupplyMin) << 0u);
    data[7] |= (uint8_t)(((uint64_t)kion_debugvalues1.RelaySupplyMin) >> 8u);


    CAN_STATUS statusCAN = canIf_send(kionCANTransmitdebugValues1Handler, MESSAGE_DLC_8, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_1);
}


/**
 * @brief send function for CAN message
 */
void kionCANSend1000(void)
{
#if defined(STMFCT_BLOCKCOMCAN1)
    if(stmFct_getBlockComCan1() == false)
    {
#endif
#if defined(STMFCT_BLOCKCOMCAN1)
    }
#endif
}

void kionCANSend40(void)
{
    kionCANSendHeartbeat();
}

void kionCANSend100(void)
{
}

void kionCANSendInterleaved(void)
{
    // 100 ms
#if defined(STMFCT_BLOCKCOMCAN1)
    if(stmFct_getBlockComCan1() == false)
    {
#endif
        const KionCanPdoConfig kionCanConfig100[] = {
            { kionCAN_sendLib_pdo_tx1, kionPdoRequirements, 0 },
            { kionCAN_sendLib_pdo_tx2, kionPdoRequirements, 10 },
            { kionCAN_sendLib_pdo_tx3, kionPdoRequirements, 20 },
            { kionCAN_sendLib_pdo_tx4, kionPdoRequirements, 30 },
            { kionCAN_sendLib_pdo_tx5, kionPdoRequirements, 40 },
            { kionCAN_sendLib_pdo_tx6, kionPdoRequirements, 50 },
            { kionCAN_sendLib_pdo_tx7, kionPdoRequirements, 60 },
        };

        for(uint8_t i = 0; i < (sizeof(kionCanConfig100) / sizeof(KionCanPdoConfig)); i++)
        {
            if((intervalCounter100ms == kionCanConfig100[i].timeOffset)
               && ((kionCanConfig100[i].requirementFunction != NULL) && (kionCanConfig100[i].requirementFunction() == true))
               && (kionCanConfig100[i].sendFunction != NULL))
            {
                kionCanConfig100[i].sendFunction();
            }
        }

#if defined(STMFCT_BLOCKCOMCAN1)
    }
#endif

    intervalCounter100ms += 10u;
    intervalCounter100ms %= 100u;
}

void kionCANSend10(void)
{
#if defined(STMFCT_BLOCKCOMCAN1)
    if(stmFct_getBlockComCan1() == false)
    {
#endif
        if((canOpenStm_getCanOpenState(&canOpenConfigKion) == canOpen_State_Operational) && (missingAckErrorCntExternal < EXTERNALCAN_MAX_MISSING_ACK_ERROR_COUNT))
        {
            kionCAN_sendLib_pdo_tx8();
        }
#if defined(STMFCT_BLOCKCOMCAN1)
    }
#endif

    kionCANSendDebug10();
    kionCANSendInterleaved();
}


void kionCANSendDebug10(void)
{
#if defined(STMFCT_BLOCKCOMCAN1)
    if(stmFct_getBlockComCan1() == false)
    {
#if defined(SW_RESET_ANALYSIS_CAN_DATA)
        // kionCAN_sendTaskCurrentTimes();
        // kionCAN_sendTaskMaxTimes();
#endif
    }
#endif
    if((sendDebugValues == true) && (missingAckErrorCntExternal < EXTERNALCAN_MAX_MISSING_ACK_ERROR_COUNT))
    {
        kionCAN_sendDebugValues1();
    }
}

void kionCANSendHeartbeat(void)
{

#if defined(STMFCT_BLOCKCOMCAN1)
    if(stmFct_getBlockComCan1() == false)
    {
#endif
        if((canOpenStm_getCanOpenState(&canOpenConfigKion) != canOpen_State_Stopped) && (missingAckErrorCntExternal < EXTERNALCAN_MAX_MISSING_ACK_ERROR_COUNT))
        {
            // @req CB-72650
            kionCAN_sendLib_heartbeat();
        }
#if defined(STMFCT_BLOCKCOMCAN1)
    }
#endif
}

void kionCAN_processEmcyMsg(void)
{
    if(missingAckErrorCntExternal < EXTERNALCAN_MAX_MISSING_ACK_ERROR_COUNT)
    {
        emcy_doJob();
    }
}
