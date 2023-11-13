/**
 *
 * @file kionCAN_sendReceive.h
 * @created on Tue Feb 16 14:15:58 CET 2021
 * @brief This module write the date from the CAN messages into
             structs which correspond with the ID of the message
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - slaveID (R)
 */

#pragma once

//******************* INCLUDES ********************************//
#include <stdint.h>
#include <stdbool.h>

//******************* DEFINES ********************************//
/** ID for */
#define KION_CAN_RX_DEBUGDTC 0x14u
/** ID for */
#define KION_CAN_RX_DEBUGVALUES1 0x15u
/** ID for */
#define KION_CAN_RX_DEBUGVALUES2 0x16u
/** ID for UDS responses from LIB with KION protocol*/
#define KION_CAN_RX_LIB_UDS 0x6a7u
/** ID for SDO Tx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC*/
#define KION_CAN_RX_LIB_SDO_TX 0x5a7u
/** ID for PDO 7 (Tx), node 0x77 (LIB with KION protocol)*/
#define KION_CAN_RX_LIB_PDO_TX7 0x3f7u
/** ID for PDO 6 (Tx), node 0x77 (LIB with KION protocol)*/
#define KION_CAN_RX_LIB_PDO_TX6 0x2f7u
/** ID for PDO 5 (Tx), node 0x77 (LIB with KION protocol)*/
#define KION_CAN_RX_LIB_PDO_TX5 0x1f7u
/** ID for PDO 4 (Tx), node 0x27 (LIB with KION protocol)*/
#define KION_CAN_RX_LIB_PDO_TX4 0x4a7u
/** ID for PDO 3 (Tx), node 0x27 (LIB with KION protocol)*/
#define KION_CAN_RX_LIB_PDO_TX3 0x3a7u
/** ID for PDO 2 (Tx), node 0x27 (LIB with KION protocol)*/
#define KION_CAN_RX_LIB_PDO_TX2 0x2a7u
/** ID for PDO 1 (Tx), node 0x27 (LIB with KION protocol)*/
#define KION_CAN_RX_LIB_PDO_TX1 0x1a7u
/** ID for heartbeat (NMT error control), node 0x27 (LIB with KION protocol)*/
#define KION_CAN_RX_LIB_HEARTBEAT 0x727u
/** ID for emergency (EMCY), node 0x27 (LIB with KION protocol)*/
#define KION_CAN_RX_LIB_EMERGENCY 0xa7u
/** ID for UDS responses from CPS in LIB with KION protocol*/
#define KION_CAN_RX_CPS_UDS 0x6dfu
/** ID for Network Management, Error Control, Battery management system Heartbeat*/
#define KION_CAN_RX_HEARTBTBMS 0x70du
/** ID for */
#define KION_CAN_RX_DIAGRESPBMS 0x79du
/** ID for CAN Open: Data for Service data object (SDO) send by BMS*/
#define KION_CAN_RX_BMSSDOTX 0x58du
/** ID for UDS requests from DTU*/
#define KION_CAN_RX_DTU_UDS 0x680u
/** ID for time stamp (TIME)*/
#define KION_CAN_RX_TIME 0x100u
/** ID for heartbeat (NMT error control), node 0x51 (OBC)*/
#define KION_CAN_RX_OBC_HEARTBEAT 0x751u
/** ID for network management (NMT)*/
#define KION_CAN_RX_MODULE_CONTROL 0x0u
/** ID for SDO Rx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC*/
#define KION_CAN_RX_LIB_SDO_RX 0x627u
/** ID for PDO 4 (Rx), node 0x27 (LIB with KION protocol)*/
#define KION_CAN_RX_LIB_PDO_RX4 0x527u
/** ID for PDO 1 (Rx), node 0x27 (LIB with KION protocol)*/
#define KION_CAN_RX_LIB_PDO_RX1 0x227u
/** ID for heartbeat (NMT error control), node 0x01 (KMC)*/
#define KION_CAN_RX_KWPC_HEARTBEAT 0x701u
/** ID for heartbeat (NMT error control), node 0x4A (EXC)*/
#define KION_CAN_RX_EXC_HEARTBEAT 0x74au
/** ID for Linde proprietary timestamp message (for LIB with Linde SAFT protocol)*/
#define KION_CAN_RX_TIMESTAMP 0xffu
/** ID for CANopen SYNC message (for LIB with Linde BMZ protocol)*/
#define KION_CAN_RX_SYNC 0x80u
/** ID for Network Management, Error Control,  liion battery charger Heartbeat*/
#define KION_CAN_RX_HEARTBTLIIONCHARGER 0x705u
/** ID for */
#define KION_CAN_RX_DIAGREQBMS 0x78du
/** ID for CAN Open: Service data object (SDO) send by KWPC*/
#define KION_CAN_RX_BMSSDORX 0x60du

//#define MESSAGE_DATA_LENGTH		8 /*Correct DLC should always be used*/

#define MAX_MESSAGE_DLC 11u  // Max DLC - 1 Byte Crc + 4 Byte extended MsgID (in case of MsgId in crc calculation)
#define MESSAGE_DLC_8   8u
#define MESSAGE_DLC_7   7u
#define MESSAGE_DLC_6   6u
#define MESSAGE_DLC_5   5u
#define MESSAGE_DLC_4   4u
#define MESSAGE_DLC_3   3u
#define MESSAGE_DLC_2   2u
#define MESSAGE_DLC_1   1u


/* ---------------------------------  STRUCTS  -------------------------------- */

/**
 * @brief Struct for ADC_Values0
 */
typedef struct
{
    uint8_t messageCounter;
    uint16_t ADC_3_3V;
    uint16_t ADC_5V;
    uint16_t ADC_Kl30;
    uint16_t Reserved;
} KION_ADC_Terminals_t;

/**
 * @brief Struct for ADC_Values1
 */
typedef struct
{
    uint8_t messageCounter;
    uint16_t ADC_SbcMux;
    uint16_t ADC_TempSens;
    uint16_t ADC_HWVersion;
    uint16_t Reserved;
} KION_ADC_VALUES1_t;

/**
 * @brief Struct for ADC_Values2
 */
typedef struct
{
    uint8_t messageCounter;
    uint16_t ADC_CurrentS1Ch1;
    uint16_t ADC_CurrentS1Ch2;
    uint16_t ADC_CurrentS2Ch1;
    uint16_t ADC_CurrentS2Ch2;
} KION_ADC_CurrentSensorValues_t;

typedef struct
{
    int32_t hvValue;
    uint32_t rawValue;
} KION_ADC_HV_VALUES_t;
/**
 * @brief Struct for debugDTC
 */
typedef struct
{
    uint8_t messageCounter;
    uint32_t DTC;
    uint8_t severity;
} KION_DEBUGDTC_t;

/**
 * @brief Struct for debugValues1
 */
typedef struct
{
    uint8_t messageCounter;
    uint16_t CellVoltageMax;
    uint16_t CellVoltageMin;
    int8_t CellTemperatureMax;
    int8_t CellTemperatureMin;
    uint16_t RelaySupplyMin;
} KION_DEBUGVALUES1_t;

/**
 * @brief Struct for debugValues2
 */
typedef struct
{
    uint8_t messageCounter;
    uint32_t Cell1;
    uint32_t Cell2;
    uint32_t Cell3;
    uint32_t Cell4;
    uint32_t Cell5;
    uint32_t Cell6;
    uint32_t Cell7;
    bool ComBreakActive;
} KION_DEBUGVALUES2_t;

typedef struct
{
    uint8_t messageCounter;
    uint32_t Cell8;
    uint32_t Cell9;
    uint32_t Cell10;
    uint32_t Cell11;
    uint32_t Cell12;
    uint32_t Cell13;
    uint32_t Cell14;
} KION_DEBUGVALUES3_t;

typedef struct
{
    uint8_t messageCounter;
    int32_t isenseValue;
    uint8_t gpioEna5VState;
    uint8_t gpioEnaHeaterState;
} KION_DEBUGVALUES4_t;


/**
 * @brief Struct for lib_uds
 */
typedef struct
{
    uint8_t messageCounter;
    /*  network target address (ISO-TP extended addressing) */
    uint8_t isotp_n_ta;
    /*  FlowControl FlowStatus (ISO-TP extended addressing) */
    uint8_t isotp_fs;
    /*  FlowControl BlockSize (ISO-TP extended addressing) */
    uint8_t isotp_bs;
    /*  FlowControl SeparationTime minimum (ISO-TP extended addressing) */
    uint8_t isotp_stmin;
    /*  FlowControl Data Field (ISO-TP extended addressing) */
    uint32_t isotp_n_data_fc;
} KION_LIB_UDS_t;

/**
 * @brief Struct for lib_sdo_tx
 */
typedef struct
{
    uint8_t messageCounter;
    uint16_t canopen_sdo_abort_index;
    uint8_t canopen_sdo_abort_subindex;
    uint32_t canopen_sdo_abort_code;
} KION_LIB_SDO_TX_t;

/**
 * @brief Struct for lib_pdo_tx8
 */
typedef struct
{
    uint8_t messageCounter;
    int64_t lib_current_unfiltered;
    uint64_t lib_voltage_in_front_of_contactor_unfiltered;
    uint64_t lib_voltage_after_contactor_unfiltered;
} KION_LIB_PDO_TX8_t;

/**
 * @brief Struct for lib_pdo_tx7
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t lib_powerpath_ok;
    uint8_t lib_pdo_tx7_message_counter;
    uint16_t lib_pdo_tx7_checksum;
} KION_LIB_PDO_TX7_t;

/**
 * @brief Struct for lib_pdo_tx6
 */
typedef struct
{
    uint8_t messageCounter;
    uint64_t lib_max_charging_current_2s;
    uint64_t lib_max_charging_current_100s;
    uint16_t lib_soc_without_soh_fine;
    int8_t lib_min_temperature;
    int8_t lib_max_temperature;
} KION_LIB_PDO_TX6_t;

/**
 * @brief Struct for lib_pdo_tx5
 */
typedef struct
{
    uint8_t messageCounter;
    uint64_t lib_max_discharging_current_2s;
    uint64_t lib_max_discharging_current_100s;
} KION_LIB_PDO_TX5_t;

/**
 * @brief Struct for lib_pdo_tx4
 */
typedef struct
{
    uint8_t messageCounter;
    uint64_t lib_max_charging_voltage;
    uint32_t lib_max_charging_power_2s;
    uint32_t lib_max_charging_power_100s;
    uint16_t lib_soc_without_soh;
} KION_LIB_PDO_TX4_t;

/**
 * @brief Struct for lib_pdo_tx3
 */
typedef struct
{
    uint8_t messageCounter;
    uint64_t lib_min_discharging_voltage;
    uint32_t lib_max_discharging_power_2s;
    uint32_t lib_max_discharging_power_100s;
    uint16_t lib_soc_with_soh;
} KION_LIB_PDO_TX3_t;

/**
 * @brief Struct for lib_pdo_tx2
 */
typedef struct
{
    uint8_t messageCounter;
    /*  voltage in front of battery contactor (as seen from battery), i.e. battery side of contactor */
    uint64_t lib_voltage_in_front_of_contacto;
    /*  voltage after battery contactor (as seen from battery), i.e. truck side of contactor */
    uint64_t lib_voltage_after_contactor;
    /*  positive values = charging, negative values = discharging */
    int32_t lib_power;
    uint16_t lib_state_of_health;
} KION_LIB_PDO_TX2_t;

/**
 * @brief Struct for lib_pdo_tx1
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t lib_init_complete;
    uint8_t lib_ready;
    uint8_t lib_in_driving_mode;
    uint8_t lib_in_charging_mode;
    uint8_t lib_error;
    uint8_t lib_current_limited;
    uint8_t lib_emergency_operation;
    uint8_t lib_shock_warning;
    uint8_t lib_fatal_error;
    uint8_t lib_temperature_too_low;
    uint8_t lib_temperature_too_high;
    uint8_t lib_service_required;
    uint8_t lib_cps_output_active;
    uint8_t lib_cps_output_deactivation_inhibit;
    /*  positive values = charging, negative values = discharging */
    int64_t lib_current;
} KION_LIB_PDO_TX1_t;

/**
 * @brief Struct for lib_heartbeat
 */
typedef struct
{
    uint8_t messageCounter;
    /*  CANopen node status of lithium-ion battery (KION protocol) */
    uint8_t canopen_state_lib;
} KION_LIB_HEARTBEAT_t;

/**
 * @brief Struct for lib_emergency
 */
typedef struct
{
    uint8_t messageCounter;
    uint16_t emergency_error_code_lib;
    uint8_t error_register_object_lib;
    uint32_t uds_dtc_lib;
} KION_LIB_EMERGENCY_t;

/**
 * @brief Struct for cps_uds
 */
typedef struct
{
    uint8_t messageCounter;
    /*  network target address (ISO-TP extended addressing) */
    uint8_t isotp_n_ta;
    /*  FlowControl FlowStatus (ISO-TP extended addressing) */
    uint8_t isotp_fs;
    /*  FlowControl BlockSize (ISO-TP extended addressing) */
    uint8_t isotp_bs;
    /*  FlowControl SeparationTime minimum (ISO-TP extended addressing) */
    uint8_t isotp_stmin;
    /*  FlowControl Data Field (ISO-TP extended addressing) */
    uint32_t isotp_n_data_fc;
} KION_CPS_UDS_t;

/**
 * @brief Struct for HeartbtBms
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t stateBms;
} KION_HEARTBTBMS_t;

/**
 * @brief Struct for DiagRespBms
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t BmsRsPCI;
    uint64_t BmsRsData;
} KION_DIAGRESPBMS_t;

/**
 * @brief Struct for BmsSDOtx
 */
typedef struct
{
    uint8_t messageCounter;
    /*  CAN Open: Data for Service data object (SDO) send by BMS */
    uint64_t BmsSDOtxData;
} KION_BMSSDOTX_t;

/**
 * @brief Struct for dtu_uds
 */
typedef struct
{
    uint8_t messageCounter;
    /*  network target address (ISO-TP extended addressing) */
    uint8_t isotp_n_ta;
    /*  FlowControl FlowStatus (ISO-TP extended addressing) */
    uint8_t isotp_fs;
    /*  FlowControl BlockSize (ISO-TP extended addressing) */
    uint8_t isotp_bs;
    /*  FlowControl SeparationTime minimum (ISO-TP extended addressing) */
    uint8_t isotp_stmin;
    /*  FlowControl Data Field (ISO-TP extended addressing) */
    uint32_t isotp_n_data_fc;
} KION_DTU_UDS_t;

/**
 * @brief Struct for time
 */
typedef struct
{
    uint8_t messageCounter;
    uint32_t canopen_time_of_day_ms;
    uint16_t canopen_time_of_day_days;
} KION_TIME_t;

/**
 * @brief Struct for obc_heartbeat
 */
typedef struct
{
    uint8_t messageCounter;
    /*  CANopen node status of on-board charger */
    uint8_t canopen_state_obc;
} KION_OBC_HEARTBEAT_t;

/**
 * @brief Struct for module_control
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t canopen_nmt_command_specifier;
    uint8_t canopen_node_id;
} KION_MODULE_CONTROL_t;

/**
 * @brief Struct for lib_sdo_rx
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t canopen_sdo_size_indicator;
    uint8_t canopen_sdo_transfer_type;
    uint8_t canopen_sdo_number_of_bytes_2;
    uint16_t canopen_sdo_download_index;
    uint8_t canopen_sdo_download_subindex;
    uint32_t canopen_sdo_data;
} KION_LIB_SDO_RX_t;

/**
 * @brief Struct for lib_pdo_rx4
 * @req CB-91890
 */
typedef struct
{
    uint8_t messageCounter;
    /*  main truck hour meter */
    int32_t truck_operating_hours;
    /*  main truck hour meter counting mode */
    uint8_t truck_operating_hours_mode;
    /*  for estimation of remaining charging time until end of shift */
    int32_t lib_power_consumption_average;
} KION_LIB_PDO_RX4_t;

/**
 * @brief Struct for lib_pdo_rx1
 * @req CB-91767
 */
typedef struct
{
    uint8_t messageCounter;
    /*  output current of charger */
    uint32_t lib_charging_current;
    /*  output voltage of charger */
    uint64_t lib_charging_voltage;
    /*  output power of charger */
    uint32_t lib_charging_power;
} KION_LIB_PDO_RX1_t;

/**
 * @brief Struct for kmc_heartbeat
 */
typedef struct
{
    uint8_t messageCounter;
    /*  CANopen node status of KION Motion Controller */
    uint8_t canopen_state_kmc;
} KION_KMC_HEARTBEAT_t;

/**
 * @brief Struct for exc_heartbeat
 */
typedef struct
{
    uint8_t messageCounter;
    /*  CANopen node status of the external battery charger */
    uint8_t canopen_state_exc;
} KION_EXC_HEARTBEAT_t;

/**
 * @brief Struct for TimeStamp
 */
typedef struct
{
    uint8_t messageCounter;
    uint32_t DateTime;
} KION_TIMESTAMP_t;

/**
 * @brief Struct for SYNC
 */
typedef struct
{
    uint8_t messageCounter;
} KION_SYNC_t;

/**
 * @brief Struct for HeartbtLiionCharger
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t stateLiionCharger;
} KION_HEARTBTLIIONCHARGER_t;

/**
 * @brief Struct for DiagReqBms
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t BmsRqPCI;
    uint64_t BmsRqData;
} KION_DIAGREQBMS_t;

/**
 * @brief Struct for BmsSDOrx
 */
typedef struct
{
    uint8_t messageCounter;
    /*  CAN Open: Data for Service data object (SDO) send by LAC */
    uint64_t BmsSDOrxData;
} KION_BMSSDORX_t;

#if defined(SW_RESET_ANALYSIS_CAN_DATA)
typedef struct
{
    uint16_t maxSafetyTaskTime;
    uint16_t maxAfeTaskTime;
    uint16_t maxNVMTaskTime;
    uint16_t maxLimitCheckTaskTime;
    uint16_t maxCanSendTaskTime;
    uint16_t maxCanReceiveTaskTime;
} KION_MAXTASKTIMES_t;

typedef struct
{
    uint16_t currentSafetyTaskTime;
    uint16_t currentAfeTaskTime;
    uint16_t currentNVMTaskTime;
    uint16_t currentLimitCheckTaskTime;
    uint16_t currentCanSendTaskTime;
    uint16_t currentCanReceiveTaskTime;
} KION_CURRENTTASKTIMES_t;

typedef struct
{
    uint8_t wdCounter;
} KION_SBCSTATUS_t;
#endif
