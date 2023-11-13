/**
 *
 * @file icdaCAN_receive.c
 * @created on Mon Nov 16 10:15:18 CET 2020
 * @brief This module write data from the CAN messages into the
             structs, corresponding to the message ID
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - icdaCAN_followUpICDA_BMS_Result ()
 * - icdaCAN_followUpICDA_BMS_Response ()
 */

//******************* INCLUDES ********************************//
#include "icdaCAN.h"
#include "icdaCAN_sendReceive.h"
#include "osIf.h"
#include "dem.h"

/* ---------------------------------  VARIABLE DEFINITIONS  -------------------------------- */
/**
 * @var highestID
 * @brief this variable saves the highest received sending ID
 * Initialization of the highest ID
 */
//MEM_CAN uint8_t highestID = 0;

/* ---------------------------------  FUNCTION DEFINITIONS  -------------------------------- */

void icdaCAN_receive(CANMessage* msg)
{

    switch(msg->id)
    {
        case ICDA_CAN_ID_ICDA_BMS_RESULT:
        {
            icdaCAN_followUpICDA_BMS_Result(msg);
        }
        break;
        case ICDA_CAN_ID_ICDA_BMS_RESPONSE:  // @req CB-91629
        {
            icdaCAN_followUpICDA_BMS_Response(msg);
        }
        break;
        default:
            break;
    }
}
