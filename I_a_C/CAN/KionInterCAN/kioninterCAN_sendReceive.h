/**
 *
 * @file kioninterCAN_sendReceive.h
 * @created on Mon Nov 16 10:15:18 CET 2020
 * @brief This module write the date from the CAN messages into
             structs which correspond with the ID of the message
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - slaveID (R)
 */
#pragma once

//******************* INCLUDES ********************************//
#include <stdint.h>
#include "kioninterCAN.h"
#include "crcFut.h"
//#include "sdo.h"

//******************* DEFINES ********************************//
/** ID for */
#define KIONINTER_CAN_RX_BMS_CPS_UDS_REQ 0x680u
/** ID for */
#define KIONINTER_CAN_RX_BMS_CPS_PDO_TX3 0x381u
/** ID for */
#define KIONINTER_CAN_RX_BMS_CPS_PDO_TX2 0x281u
/** ID for */
#define KIONINTER_CAN_RX_BMS_HEARTBEAT 0x701u
/** ID for */
#define KIONINTER_CAN_RX_BMS_TIMESTAMP 0x100u
/** ID for */
#define KIONINTER_CAN_RX_BMS_CPS_SDO_REQ 0x602u
/** ID for */
#define KIONINTER_CAN_RX_BMS_MODULECOTROL 0x0u
/** ID for */
#define KIONINTER_CAN_RX_BMS_CPS_PDO_TX1 0x181u
/** ID for */
#define KIONINTER_CAN_RX_BMS_ICDA_REQUEST 0x500u
/** ID for */
#define KIONINTER_CAN_RX_CPS_BMS_UDS_RESP 0x6e6u
/** ID for */
#define KIONINTER_CAN_RX_CH_CPS_WAKEUP 0x1fffffffu
/** ID for */
#define KIONINTER_CAN_RX_CPS_VEHICLE_UDS_RESP 0x6dfu
/** ID for */
#define KIONINTER_CAN_RX_CPS_BMS_EMERGENCY 0x82u
/** ID for */
#define KIONINTER_CAN_RX_CPS_HEARTBEAT 0x702u
/** ID for */
#define KIONINTER_CAN_RX_CPS_BMS_SDO_RESP 0x582u
/** ID for */
#define KIONINTER_CAN_RX_CPS_BMS_PDO_TX2 0x282u
/** ID for */
#define KIONINTER_CAN_RX_CPS_BMS_PDO_TX3 0x382u
/** ID for */
#define KIONINTER_CAN_RX_CPS_BMS_PDO_TX1 0x182u
/** ID for */
#define KIONINTER_CAN_RX_ICDA_BMS_RESULT 0x502u
/** ID for */
#define KIONINTER_CAN_RX_ICDA_BMS_RESPONSE 0x501u

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
 * @brief Struct for BMS_CPS_UDS_REQ
 */
typedef struct
{
    uint8_t messageCounter;
    /*  Voltage input of CPS (from Battery). */
    uint64_t BMS_UDSData;
} KIONINTER_BMS_CPS_UDS_REQ_t;

/**
 * @brief Struct for BMS_CPS_PDO_TX3
 */
typedef struct
{
    uint8_t messageCounter;
    /*  remaining capacity of battery */
    uint32_t BMS_INFO_RemainingCapacity;
    /*  time to the next BMS wakeup */
    uint16_t BMS_INFO_TimeToWakeUp;
    /*  time to the next BMS wakeup */
    uint8_t BMS_INFO_DeepDisPossible;
    /*  time to the next BMS wakeup */
    uint8_t BMS_INFO_DeepDisImminent;
    uint8_t BMS_RX3_Counter;
    uint16_t BMS_RX3_Checksum;
} KIONINTER_BMS_CPS_PDO_TX3_t;

/**
 * @brief Struct for BMS_CPS_PDO_TX2
 */
typedef struct
{
    uint8_t messageCounter;
    /*  requested CPS out current (vehicle supply) */
    uint32_t BMS_REQ_CPSout_I;
    /*  requested CPS out boost current (vehicle supply) */
    uint32_t BMS_REQ_CPSoutBoost_I;
    uint8_t BMS_RX2_Counter;
    uint16_t BMS_RX2_Checksum;
} KIONINTER_BMS_CPS_PDO_TX2_t;

/**
 * @brief Struct for BMS_Heartbeat
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t BMS_HBState;
} KIONINTER_BMS_HEARTBEAT_t;

/**
 * @brief Struct for BMS_TimeStamp
 */
typedef struct
{
    uint8_t messageCounter;
    uint32_t BMS_CANopen_Ms;
    uint16_t BMS_CANopen_Days;
} KIONINTER_BMS_TIMESTAMP_t;

/**
 * @brief Struct for BMS_CPS_SDO_REQ
 */
typedef struct
{
    uint8_t messageCounter;
    uint64_t BMS_SDO_TX_Data;
} KIONINTER_BMS_CPS_SDO_REQ_t;

/**
 * @brief Struct for BMS_ModuleCotrol
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t BMS_ServiceID;
    uint8_t BMS_NodeID;
} KIONINTER_BMS_MODULECOTROL_t;

/**
 * @brief Struct for BMS_CPS_PDO_TX1
 */
typedef struct
{
    uint8_t messageCounter;
    /*   initiate a CPS power down (deep-discharge protection) */
    uint8_t BMS_REQ_PowerDown;
    /*  control CPS out (vehicle supply) */
    uint8_t BMS_REQ_CPSout;
    /*  BMS indicates that it is ready to sleep / for regular power down. */
    uint8_t BMS_INFO_BMSstate;
    /*  requested heating current */
    uint32_t BMS_REQ_Min_V;
    uint8_t BMS_RX1_Counter;
    uint16_t BMS_RX1_Checksum;
} KIONINTER_BMS_CPS_PDO_TX1_t;

/**
 * @brief Struct for BMS_ICDA_Request
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t MUX;
    uint8_t P0;
    uint8_t P1;
    uint8_t P2;
    uint8_t P3;
    uint8_t P4;
    uint8_t P5;
    uint8_t P6;
} KIONINTER_BMS_ICDA_REQUEST_t;

/**
 * @brief Struct for CPS_BMS_UDS_RESP
 */
typedef struct
{
    uint8_t messageCounter;
    /*  Voltage input of CPS (from Battery). */
    uint64_t CPS_UDSData;
} KIONINTER_CPS_BMS_UDS_RESP_t;

/**
 * @brief Struct for CH_CPS_WakeUp
 */
typedef struct
{
    uint8_t messageCounter;
    int64_t CH_Data;
} KIONINTER_CH_CPS_WAKEUP_t;

/**
 * @brief Struct for CPS_VEHICLE_UDS_RESP
 */
typedef struct
{
    uint8_t messageCounter;
    /*  Voltage input of CPS (from Battery). */
    uint64_t CPS_UDSData;
} KIONINTER_CPS_VEHICLE_UDS_RESP_t;

/**
 * @brief Struct for CPS_BMS_Emergency
 */
typedef struct
{
    uint8_t messageCounter;
    uint16_t CPS_EMCY_ErrorCode;
    uint8_t CPS_EMCY_ErrorRegister;
    uint32_t CPS_UDS_DTC;
} KIONINTER_CPS_BMS_EMERGENCY_t;

/**
 * @brief Struct for CPS_Heartbeat
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t CPS_HBState;
} KIONINTER_CPS_HEARTBEAT_t;

/**
 * @brief Struct for CPS_BMS_SDO_RESP
 */
typedef struct
{
    uint8_t messageCounter;
    int8_t CPS_SDO_RX_Data;
} KIONINTER_CPS_BMS_SDO_RESP_t;

/**
 * @brief Struct for CPS_BMS_PDO_TX2
 */
typedef struct
{
    uint8_t messageCounter;
    /*  current consumption of vehicle */
    uint32_t CPS_CPSout_I;
    /*  temperature of CPS power path */
    uint8_t CPS_Temp1CPSout;
    /*  temperature of CPS power path */
    uint8_t CPS_Temp2CPSout;
    uint8_t CPS_TX2_Counter;
    uint16_t CPS_TX2_Checksum;
} KIONINTER_CPS_BMS_PDO_TX2_t;

/**
 * @brief Struct for CPS_BMS_PDO_TX3
 */
typedef struct
{
    uint8_t messageCounter;
    /*  voltage input of CPS (Battery) */
    uint16_t CPS_VoltageInput;
    /*  voltage output of CPS out (vehicle supply) */
    uint16_t CPS_CPSoutVoltage;
    uint8_t CPS_TX3_Counter;
    uint16_t CPS_TX3_Checksum;
} KIONINTER_CPS_BMS_PDO_TX3_t;

/**
 * @brief Struct for CPS_BMS_PDO_TX1
 */
typedef struct
{
    uint8_t messageCounter;
    /*  state of CPS out boost (vehicle supply) */
    uint8_t CPS_CPSoutBoost;
    /*  state of CPS out boost (vehicle supply) */
    uint8_t CPS_CPSout;
    /*  CPS emergency wakeup */
    uint8_t CPS_StartupAfterPowerdown;
    /*  CPS emergency wakeup */
    uint8_t CPS_Emergency;
    /*  state of current limitation for CPS out (vehicle supply) */
    uint8_t CPS_CPSoutLimitation;
    uint16_t CPS_Error;
    uint8_t CPS_TX1_Counter;
    uint16_t CPS_TX1_Checksum;
} KIONINTER_CPS_BMS_PDO_TX1_t;

/**
 * @brief Struct for ICDA_BMS_Result
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t Status;
    uint8_t MessageCounter;
    int32_t Result_I;
    uint16_t Result_Ubat;
} ICDA_BMS_Result_t;

/**
 * @brief Struct for ICDA_BMS_Response
 */
typedef struct
{
    uint8_t messageCounter;
    uint8_t MUX_ID;
    uint8_t P0;
    uint8_t P1;
    uint8_t P2;
    uint8_t P3;
    uint8_t P4;
    uint8_t P5;
    uint8_t P6;
} KIONINTER_ICDA_BMS_RESPONSE_t;

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
#define MAX_MESSAGE_DLC_INTERCAN 9u
/** ID for Values from Pack and String Master*/
#define INTER_CAN_RX_STRPM_SYM_VAL1 0x300u
typedef struct
{
    uint8_t messageCounter;
    /* ErrorMessage */
    uint8_t StrPM_SyM_Val1ErrorMessage;
    /* State of sending Master */
    uint8_t StrPM_SyM_Val1State;
    /* Mastertyp (System, Pack or String Master) */
    uint8_t StrPM_SyM_Val1Mastertyp;
    /* Software version */
    uint8_t StrPM_SyM_Val1SWVersion;
    /* hardware version */
    uint8_t StrPM_SyM_Val1HWVersion;
    /* Hv interlock status, 0 = active, 1 = error, no connection */
    uint8_t StrPM_SyM_Val1Hvi;
    /*Highest Severity*/
    uint8_t StrPM_SyM_Val1HighSev;
    /*time to reaction of highest severity*/
    uint8_t StrPM_SyM_Val1T2Reac;
    /*Signals a request to perform error shutdown*/
    uint8_t StrPM_SyM_Val1ErrorRequest;
    /* Rolling Counter (Specification, see Documentation of Rolling Counter) */
    uint8_t StrPM_SyM_Val1CtRoll;
    /* Checksum (Specification, see Documentation of Checksum) */
    uint8_t StrPM_SyM_Val1Crc;
} KIONSTRPM_SYM_VAL1_t;
#endif
