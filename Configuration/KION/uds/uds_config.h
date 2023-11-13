/**
 * @file     uds_DEFAULT.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

#pragma once


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>

#include "isotp.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define UDS_RESPONSE_BUFFER_LENGTH 2000u
#define UDS_RECEIVE_BUFFER_LENGTH  2000u

#define UDS_TIMER_INTERVAL 10u

/**@def ISOTP_SEND_CUSTOMER
 * @brief UDS handler for customer CAN
 * @details
 *
 * (Fix value)
 */
#define UDS_SEND_CUSTOMER kionCANTransmitlib_udsHandler

#define UDS_CAN_DEFAULT_RECV_BS        10
#define UDS_CAN_DEFAULT_EXT_ADDRESS_RX 0x27  // @req CB-75025
#define UDS_CAN_DEFAULT_EXT_ADDRESS_TX 0x00
#define UDS_CAN_DEFAULT_PAD_CONTENT    0xAAu /* prevent bit-stuffing */
#define UDS_CAN_ENDIANNESS             PROTOCOL_BIG_ENDIAN

#define UDS_CAN_DEFAULT_FLAGS (CAN_ISOTP_EXTEND_ADDR | CAN_ISOTP_TX_PADDING)

#define UDS_FACTOR_DERATING_THRESHOLD_REL_LIN   250u
#define UDS_FACTOR_DERATING_THRESHOLD_LIN_CONST 250u
#define UDS_FACTOR_DERATING_MAX_RATE_REL        0.1f
#define UDS_FACTOR_DERATING_MAX_RATE_LIN        250u

#define UDS_FACTOR_SOC_MIN_REF_OCV              100u
#define UDS_FACTOR_SOC_REST_TIME_OCV            1000u
#define UDS_FACTOR_SOC_FULLY_CHARGED_HYSTERESYS 100
#define UDS_FACTOR_SOC_DISCHARGED_HYSTERESYS    100u

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
