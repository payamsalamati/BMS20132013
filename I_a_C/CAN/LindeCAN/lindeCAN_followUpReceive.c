/**
 *
 * @file lindeCAN_followUpReceive.c
 * @modulenumber 0x0D
 * @author Generated File with DPCParser release-1.3.4 Commit 1347995
 * @created on Thu Mar 30 17:16:56 CEST 2023
 * @brief This module write data from the CAN messages into the
             structs, corresponding to the message ID
 * @copyright  Futavis GmbH, Aachen 2023 - alle Rechte vorbehalten
 * @details Generated from file "lindeCAN.sym"
 * @par Global variables
 * - lindemodule_control: -network management (NMT)-
 * - lindeTraction_SDOreq_LiIoBMS: -SDO Rx, node 0x0D (LIB with Linde BMZ protocol)-
 * - lindeTraction_PDO4: -PDO 4 (Tx), node 0x01 (KMC) (for LIB with Linde BMZ protocol)-
 * - lindeTimeStamp: -Linde proprietary timestamp message (for LIB with Linde BMZ protocol)-
 * - lindeSYNC: -CANopen SYNC message (for LIB with Linde BMZ protocol)-
 * - lindeLiIoCharger_SDOreq_LiIoBMS: -SDO Rx, node 0x5D (LIB with Linde BMZ protocol), SDO clients: OBC, EXC-
 * - lindeLiIoCharger_PDO1: -PDO 1 (Tx), node 0x5D (OBC, EXC)-
 * @par changes
 * - first creation Thu Mar 30 17:16:56 CEST 2023
 */

//******************* INCLUDES ********************************//
#include "lindeCAN.h"
#include "semaphores.h"
#include "nmt.h"
#include "canopen_config.h"
#include "sdo.h"
#include "protocolSelection.h"
#include "canOpenStmFct.h"
#include "canData.h"
#include "stateFunctions.h"
#include "logging.h"


//**************************PUBLIC VARIABLE DEFINITIONS ******************************//

//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific receive functions !!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!! Please add the needed functions for your project !!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
void lindeCAN_followUpmodule_control(const LINDE_MODULE_CONTROL_t* data, const CANMessage* msg)
{
    // @req CB-91633
    nmt_receive(&canOpenConfigLinde, msg);
}

void lindeCAN_followUpTraction_SDOreq_LiIoBMS(const LINDE_TRACTION_SDOREQ_LIIOBMS_t* data, const CANMessage* msg)
{
    // @req CB-91634
    sdo_receive(&canOpenConfigLinde, msg);
}

void lindeCAN_followUpTraction_PDO4(const LINDE_TRACTION_PDO4_t* data, const CANMessage* msg)
{
    // @req CB-91752
    canData_storeLastLindeTractionPdoRx4Data(*data);
}

void lindeCAN_followUpTimeStamp(const LINDE_TIMESTAMP_t* data, const CANMessage* msg)
{
    // @req CB-91757
    canData_storeLastLindeTimestampData(*data);
}

void lindeCAN_followUpSYNC(const LINDE_SYNC_t* data, const CANMessage* msg)
{
    // @req CB-91637
    stmFct_resetCanTimeoutTimer();
}

void lindeCAN_followUpLiIoCharger_SDOreq_LiIoBMS(const LINDE_LIIOCHARGER_SDOREQ_LIIOBMS_t* data, const CANMessage* msg)
{
    // @req CB-91636
    sdo_receive(&canOpenConfigLindeCharger, msg);
}

void lindeCAN_followUpLiIoCharger_PDO1(const LINDE_LIIOCHARGER_PDO1_t* data, const CANMessage* msg)
{
    // @req CB-91639
    canData_storeLastLindePdoRx1Data(*data);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific send functions END!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
