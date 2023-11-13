/**
 *
 * @file icdaCAN_sendReceive.h
 * @modulenumber 0x0D
 * @author Generated File with DPCParser NO_TAG? Commit 12345678
 * @created on Fri Feb 11 15:37:19 CET 2022
 * @brief This module write the date from the CAN messages into
             structs which correspond with the ID of the message
 * @copyright Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
 * @details Generated from file "icda.sym"
 * @par Global variables
 * - slaveID (R)
 * @par changes
 * - first creation Fri Feb 11 15:37:19 CET 2022
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include <stdint.h>
#include "icdaCAN.h"
#include "crcFut.h"
//#include "sdo.h"


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//
/** ID for */
#define ICDA_CAN_ID_BMS_ICDA_REQUEST 0x500u

/** ID for */
#define ICDA_CAN_ID_ICDA_BMS_RESULT 0x502u

/** ID for */
#define ICDA_CAN_ID_ICDA_BMS_RESPONSE 0x501u

#define ICDA_CAN_ID_UDS 0x10Au

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

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


/* ---------------------------------  STRUCTS  -------------------------------- */

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
} ICDA_BMS_ICDA_REQUEST_t;

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
} ICDA_ICDA_BMS_RESULT_t;
