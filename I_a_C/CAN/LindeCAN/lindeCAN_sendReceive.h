/**
 *
 * @file lindeCAN_sendReceive.h
 * @modulenumber 0x0D
 * @author Generated File with DPCParser release-1.3.4 Commit 1347995
 * @created on Thu Mar 30 17:16:56 CEST 2023
 * @brief This module write the date from the CAN messages into
             structs which correspond with the ID of the message
 * @copyright Futavis GmbH, Aachen 2023 - alle Rechte vorbehalten
 * @details Generated from file "lindeCAN.sym"
 * @par Global variables
 * - slaveID (R)
 * @par changes
 * - first creation Thu Mar 30 17:16:56 CEST 2023
 */
#ifndef INTERFACELAYER_LINDECAN_SENDRECEIVE_H_
#define INTERFACELAYER_LINDECAN_SENDRECEIVE_H_

//******************* INCLUDES ********************************//
#include <stdint.h>
#include <stdbool.h>
//#include "sdo.h"

//******************* DEFINES ********************************//
/** ID for SDO Tx, node 0x0D (LIB with Linde BMZ protocol), SDO client: KMC*/
#define LINDE_CAN_ID_LIIOBMS_SDORESP_TRACTION 0x58du

/** ID for SDO Tx, node 0x5D (LIB with Linde BMZ protocol), SDO client: OBC, EXC*/
#define LINDE_CAN_ID_LIIOBMS_SDORESP_LIIOCHARGER 0x5ddu

/** ID for PDO5 (Tx), node 0x01 (LIB with Linde BMZ prototol)*/
#define LINDE_CAN_ID_LIIOBMS_PDO5 0x301u

/** ID for PDO4 (Tx), node 0x0D (LIB with Linde BMZ prototol)*/
#define LINDE_CAN_ID_LIIOBMS_PDO4 0x48du

/** ID for PDO3 (Tx), node 0x0D (LIB with Linde BMZ prototol)*/
#define LINDE_CAN_ID_LIIOBMS_PDO3 0x38du

/** ID for PDO2 (Tx), node 0x0D (LIB with Linde BMZ prototol)*/
#define LINDE_CAN_ID_LIIOBMS_PDO2 0x28du

/** ID for PDO1 (Tx), node 0x0D (LIB with Linde BMZ protocol)*/
#define LINDE_CAN_ID_LIIOBMS_PDO1 0x18du

/** ID for heartbeat (NMT error control), node 0x0D (LIB with Linde BMZ protocol)*/
#define LINDE_CAN_ID_LIIOBMS_HEARTBEAT 0x70du

/** ID for network management (NMT)*/
#define LINDE_CAN_ID_MODULE_CONTROL 0x0u

/** ID for SDO Rx, node 0x0D (LIB with Linde BMZ protocol)*/
#define LINDE_CAN_ID_TRACTION_SDOREQ_LIIOBMS 0x60du

/** ID for PDO 4 (Tx), node 0x01 (KMC) (for LIB with Linde BMZ protocol)*/
#define LINDE_CAN_ID_TRACTION_PDO4 0x481u

/** ID for Linde proprietary timestamp message (for LIB with Linde BMZ protocol)*/
#define LINDE_CAN_ID_TIMESTAMP 0xffu

/** ID for CANopen SYNC message (for LIB with Linde BMZ protocol)*/
#define LINDE_CAN_ID_SYNC 0x80u

/** ID for SDO Rx, node 0x5D (LIB with Linde BMZ protocol), SDO clients: OBC, EXC*/
#define LINDE_CAN_ID_LIIOCHARGER_SDOREQ_LIIOBMS 0x65du

/** ID for PDO 1 (Tx), node 0x5D (OBC, EXC)*/
#define LINDE_CAN_ID_LIIOCHARGER_PDO1 0x485u


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

/* ----------------------------------  ENUMS  --------------------------------- */


/* ---------------------------------  STRUCTS  -------------------------------- */

/**
 * @brief Struct for LiIoBMS_SDOresp_Traction
 */
typedef struct
{
    uint8_t messageCounter;
    uint64_t LiIoBMS_SDOresp_Traction_Data;
} LINDE_LIIOBMS_SDORESP_TRACTION_t;

/**
 * @brief Struct for LiIoBMS_SDOresp_LiIoCharger
 */
typedef struct
{
    uint8_t messageCounter;
    uint64_t LiIoBMS_SDOresp_LiIoCharger_Data;
} LINDE_LIIOBMS_SDORESP_LIIOCHARGER_t;

/**
 * @brief Struct for LiIoBMS_PDO5
 */
typedef struct
{
    uint8_t messageCounter;
    uint64_t LiIoBMS_OutputVoltage;
    uint32_t LiIoBMS_MaxDischargePower2;
    uint32_t LiIoBMS_MaxChargePower2;
} LINDE_LIIOBMS_PDO5_t;

/**
 * @brief Struct for LiIoBMS_PDO4
 */
typedef struct
{
    uint8_t messageCounter;
    uint64_t LiIoBMS_MinDischargeVoltage;
    uint64_t LiIoBMS_MaxChargeVoltage;
    uint8_t LiIoBMS_SOCwithoutSOH;
    uint8_t LiIoBMS_SOCwithSOH;
} LINDE_LIIOBMS_PDO4_t;

/**
 * @brief Struct for LiIoBMS_PDO3
 */
typedef struct
{
    uint8_t messageCounter;
    uint16_t LiIoBMS_DTC1;
    uint16_t LiIoBMS_DTC2;
    uint16_t LiIoBMS_DTC3;
    uint16_t LiIoBMS_DTC4;
} LINDE_LIIOBMS_PDO3_t;

/**
 * @brief Struct for LiIoBMS_PDO2
 */
typedef struct
{
    uint8_t messageCounter;
    uint32_t LiIoBMS_MaxChargeCurrent2;
    uint32_t LiIoBMS_MaxDischargeCurrent2;
    uint32_t LiIoBMS_MaxChargeCurrent100;
    uint32_t LiIoBMS_MaxDischargeCurrent100;
} LINDE_LIIOBMS_PDO2_t;

/**
 * @brief Struct for LiIoBMS_PDO1
 */
typedef struct
{
    uint8_t messageCounter;
    /*  positive values = charging, negative values = discharging */
    int64_t LiIoBMS_BatteryCurrent;
    uint64_t LiIoBMS_BatteryVoltage;
    uint8_t LiIoBMS_BatteryState;
    uint8_t LiIoBMS_SOH;
} LINDE_LIIOBMS_PDO1_t;

/**
 * @brief Struct for LiIoBMS_Heartbeat
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t LiIoBMS_State;
} LINDE_LIIOBMS_HEARTBEAT_t;

/**
 * @brief Struct for module_control
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t canopen_nmt_command_specifier;
    uint8_t canopen_node_id;
} LINDE_MODULE_CONTROL_t;

/**
 * @brief Struct for Traction_SDOreq_LiIoBMS
 */
typedef struct
{
    uint8_t messageCounter;
    uint64_t Traction_SDOreq_LiIoBMS_Data;
} LINDE_TRACTION_SDOREQ_LIIOBMS_t;

/**
 * @brief Struct for Traction_PDO4
 */
typedef struct
{
    uint8_t messageCounter;
    uint32_t TruckWorkTime;
} LINDE_TRACTION_PDO4_t;

/**
 * @brief Struct for TimeStamp
 */
typedef struct
{
    uint8_t messageCounter;
    uint32_t DateTime;
} LINDE_TIMESTAMP_t;

/**
 * @brief Struct for SYNC
 */
typedef struct
{
    uint8_t messageCounter;
} LINDE_SYNC_t;

/**
 * @brief Struct for LiIoCharger_SDOreq_LiIoBMS
 */
typedef struct
{
    uint8_t messageCounter;
    uint64_t LiIoCharger_SDOreq_LiIoBMS_Data;
} LINDE_LIIOCHARGER_SDOREQ_LIIOBMS_t;

/**
 * @brief Struct for LiIoCharger_PDO1
 */
typedef struct
{
    uint8_t messageCounter;
    uint32_t LiIoCharger_ChargingCurrent;
    uint32_t LiIoCharger_ChargingVoltage;
    uint32_t LiIoCharger_WorkingHours;
} LINDE_LIIOCHARGER_PDO1_t;

typedef enum
{
    LIIOBMS_READY  = 0x1,
    LIIOBMS_DRIVE  = 0x2,
    LIIOBMS_CHARGE = 0x3,
    LIIOBMS_ERROR  = 0x4,
} LINDE_LIIOBMS_BATTERY_STATE;


#endif /* INTERFACELAYER_LINDECAN_SENDRECEIVE_H_ */
