/**
 *
 * @file icdaCAN_send.c
 * @modulenumber ICDA_NB
 * @author Generated File with DPCParser NO_TAG? Commit 12345678
 * @created on Fri Feb 11 15:37:19 CET 2022
 * @brief This module write data from the structs to the CAN messages and calls can_send
 * @copyright Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
 * @details Generated from file "icda.sym"
 * @par Global variables
 * - icdaBMS_ICDA_Request: --
 * @par changes
 * - first creation Fri Feb 11 15:37:19 CET 2022
 */

//******************* INCLUDES ********************************//
#include "icdaCAN.h"
#include "stdio.h"
#include "osIf.h"
#include "types.h"
#include "debug.h"


/* ---------------------------------  FUNCTION DEFINITIONS  -------------------------------- */
/**
 * @brief send function for CAN message
 * @req CB-91635
 */
void icdaCAN_sendBMS_ICDA_Request()
{
    ICDA_BMS_ICDA_REQUEST_t icda_bms_icda_request = { 0 };
    icdaCAN_prepareBMS_ICDA_Request(&icda_bms_icda_request);

    uint8_t data[MESSAGE_DLC_8] = { 0 };

    DEBUG_ASSERT(icda_bms_icda_request.MUX <= UMAXVAL_8BIT);
    data[0] |= ((uint64_t)icda_bms_icda_request.MUX) << 0u;

    DEBUG_ASSERT(icda_bms_icda_request.P0 <= UMAXVAL_8BIT);
    data[1] |= ((uint64_t)icda_bms_icda_request.P0) << 0u;

    DEBUG_ASSERT(icda_bms_icda_request.P1 <= UMAXVAL_8BIT);
    data[2] |= ((uint64_t)icda_bms_icda_request.P1) << 0u;

    DEBUG_ASSERT(icda_bms_icda_request.P2 <= UMAXVAL_8BIT);
    data[3] |= ((uint64_t)icda_bms_icda_request.P2) << 0u;

    DEBUG_ASSERT(icda_bms_icda_request.P3 <= UMAXVAL_8BIT);
    data[4] |= ((uint64_t)icda_bms_icda_request.P3) << 0u;

    DEBUG_ASSERT(icda_bms_icda_request.P4 <= UMAXVAL_8BIT);
    data[5] |= ((uint64_t)icda_bms_icda_request.P4) << 0u;

    DEBUG_ASSERT(icda_bms_icda_request.P5 <= UMAXVAL_8BIT);
    data[6] |= ((uint64_t)icda_bms_icda_request.P5) << 0u;

    DEBUG_ASSERT(icda_bms_icda_request.P6 <= UMAXVAL_8BIT);
    data[7] |= ((uint64_t)icda_bms_icda_request.P6) << 0u;

    CAN_STATUS statusCAN = canIf_send(icdaCANTransmitBMS_ICDA_RequestHandler, MESSAGE_DLC_8, data);
    if(statusCAN == CAN_SUCCESS)
    {
        // all is well!
    }
    else
    {  // CAN error
        dem_reportFaultFromApp(DTC_CAN_SEND_DRIVER_ERROR);
    }
    canIf_waitForTxBusReadyStatus(CAN_NODE_0);
}
