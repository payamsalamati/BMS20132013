/**
 *
 * @file kionCAN_followUpReceive.c
 * @created on Tue Feb 16 14:15:58 CET 2021
 * @brief This module write data from the CAN messages into the
             structs, corresponding to the message ID
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - kiontime: -time stamp (TIME)-
 * - kionobc_heartbeat: -heartbeat (NMT error control), node 0x51 (OBC)-
 * - kionmodule_control: -network management (NMT)-
 * - kionlib_sdo_rx: -SDO Rx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC-
 * - kionlib_pdo_rx4: -PDO 4 (Rx), node 0x27 (LIB with KION protocol)-
 * - kionlib_pdo_rx1: -PDO 1 (Rx), node 0x27 (LIB with KION protocol)-
 * - kionkmc_heartbeat: -heartbeat (NMT error control), node 0x01 (KMC)-
 * - kionexc_heartbeat: -heartbeat (NMT error control), node 0x4A (EXC)-
 * - kionTimeStamp: -Linde proprietary timestamp message (for LIB with Linde SAFT protocol)-
 * - kionSYNC: -CANopen SYNC message (for LIB with Linde BMZ protocol)-
 * - kionHeartbtLiionCharger: -Network Management, Error Control,  liion battery charger Heartbeat-
 * - kionDiagReqBms: --
 * - kionBmsSDOrx: -CAN Open: Service data object (SDO) send by KWPC-
 */

//******************* INCLUDES ********************************//
#include "kionCAN.h"

#include "canId_config.h"

#include "semaphores.h"
#include "sdo.h"
#include "nmt.h"
#include "isotp.h"
#include "isotp_config.h"
#include "stateFunctions.h"
#include "canopen_config.h"
#include "canOpenWatchdog.h"
#include "uds.h"
#include "cps.h"
#if CAN_INTERNAL_ID == INTERCAN_ID
#include CAN_INTERNAL_HEADER
#endif
#include "canData.h"
#include "timestamp.h"

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//

//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific receive functions !!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!! Please add the needed functions for your project !!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
void kionCAN_followUpdtu_uds(const KION_DTU_UDS_t* data, const CANMessage* msg)
{
}

void kionCAN_followUptime(const KION_TIME_t* data, const CANMessage* msg)
{
    // @req CB-75131
    // @req CB-75132
    timestamp_updateUnixTimeFromCANopenTimestamp(data->canopen_time_of_day_ms, data->canopen_time_of_day_days);
    canData_storeLastTimeData(*data);
}

void kionCAN_followUpobc_heartbeat(const KION_OBC_HEARTBEAT_t* data, const CANMessage* msg)
{
    stmFct_resetCanTimeoutTimer();
}

void kionCAN_followUpmodule_control(const KION_MODULE_CONTROL_t* data, const CANMessage* msg)
{
    nmt_receive(&canOpenConfigKion, msg);
}

void kionCAN_followUplib_sdo_rx(const KION_LIB_SDO_RX_t* data, const CANMessage* msg)
{
    sdo_receive(&canOpenConfigKion, msg);
}

void kionCAN_followUplib_pdo_rx4(const KION_LIB_PDO_RX4_t* data, const CANMessage* msg)
{
    canData_storeLastLibPdoRx4Data(*data);
    canData_setLibPdoRx4DataReceived(true);
}

void kionCAN_followUplib_pdo_rx1(const KION_LIB_PDO_RX1_t* data, const CANMessage* msg)
{
    canData_storeLastLibPdoRx1Data(*data);
    canData_setLibPdoRx1DataReceived();
}

void kionCAN_followUpKmc_heartbeat(const KION_KMC_HEARTBEAT_t* data, const CANMessage* msg)
{
    stmFct_resetCanTimeoutTimer();
}

void kionCAN_followUpexc_heartbeat(const KION_EXC_HEARTBEAT_t* data, const CANMessage* msg)
{
    stmFct_resetCanTimeoutTimer();
}

void kionCAN_followUpTimeStamp(const KION_TIMESTAMP_t* data, const CANMessage* msg)
{
    canData_storeLastTimestampData(*data);
}

void kionCAN_followUpSYNC(const KION_SYNC_t* data, const CANMessage* msg)
{
}

void kionCAN_followUpHeartbtLiionCharger(const KION_HEARTBTLIIONCHARGER_t* data, const CANMessage* msg)
{
    stmFct_resetCanTimeoutTimer();
}
