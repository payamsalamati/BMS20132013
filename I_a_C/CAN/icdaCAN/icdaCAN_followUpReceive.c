/**
 *
 * @file icdaCAN_followUpReceive.c
 * @created on Wed Feb 19 10:47:50 CET 2020
 * @brief This module write data from the CAN messages into the
             structs, corresponding to the message ID
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables

 * - kioninterICDA_BMS_Result: --
 * - kioninterICDA_BMS_Response: --
 */

//******************* INCLUDES ********************************//

#include "icdaCAN.h"

#include "canId_config.h"
#include "icdaSensor.h"
#include "cps.h"
#include "stateFunctions.h"
#include "cpsMonitor.h"

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//

//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific receive functions !!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!! Please add the needed functions for your project !!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//


void icdaCAN_followUpICDA_BMS_Result(const CANMessage* msg)
{
    // @req CB-15640
    icdaSensor_processCANresult(msg, false);
}

void icdaCAN_followUpICDA_BMS_Response(const CANMessage* msg)
{
    icdaSensor_processCANresponse(msg);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific send functions END!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
