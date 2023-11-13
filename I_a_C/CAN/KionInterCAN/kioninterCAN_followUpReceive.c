/**
 *
 * @file kioninterCAN_followUpReceive.c
 * @created on Wed Feb 19 10:47:50 CET 2020
 * @brief This module write data from the CAN messages into the
             structs, corresponding to the message ID
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - kioninterCH_CPS_WakeUp: --
 * - kioninterCPS_VEHICLE_UDS_RESP: --
 * - kioninterCPS_BMS_Emergency: --
 * - kioninterCPS_Heartbeat: --
 * - kioninterCPS_BMS_SDO_RESP: --
 * - kioninterCPS_BMS_PDO_TX2: --
 * - kioninterCPS_BMS_PDO_TX3: --
 * - kioninterCPS_BMS_PDO_TX1: --
 * - kioninterICDA_BMS_Result: --
 * - kioninterICDA_BMS_Response: --
 */

//******************* INCLUDES ********************************//

#include "kioninterCAN.h"

#include "module_config.h"
#include "canId_config.h"
#include "icdaSensor.h"
#include "cps.h"
#include "stateFunctions.h"
#include "cpsMonitor.h"
#include "bms_config.h"

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//

//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific receive functions !!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!! Please add the needed functions for your project !!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
void kioninterCAN_followUpCPS_BMS_UDS_RESP(const KIONINTER_CPS_BMS_UDS_RESP_t* data, const CANMessage* msg)
{
}

void kioninterCAN_followUpCH_CPS_WakeUp(const KIONINTER_CH_CPS_WAKEUP_t* data, const CANMessage* msg)
{
}

void kioninterCAN_followUpCPS_VEHICLE_UDS_RESP(const CANMessage* msg)
{
    cps_tunnelCpsVehicleUdsResponse(msg);
}

void kioninterCAN_followUpCPS_BMS_Emergency(const KIONINTER_CPS_BMS_EMERGENCY_t* data, const CANMessage* msg)
{
    cps_setCpsEmergency(data);
}

void kioninterCAN_followUpCPS_Heartbeat(const KIONINTER_CPS_HEARTBEAT_t* data, const CANMessage* msg)
{
    stmFct_setCpsCommunicationEnable(true);
}

void kioninterCAN_followUpCPS_BMS_SDO_RESP(const KIONINTER_CPS_BMS_SDO_RESP_t* data, const CANMessage* msg)
{
}

void kioninterCAN_followUpCPS_BMS_PDO_TX2(const KIONINTER_CPS_BMS_PDO_TX2_t* data, const CANMessage* msg)
{
    cps_setPdoTx2(data);
}

void kioninterCAN_followUpCPS_BMS_PDO_TX3(const KIONINTER_CPS_BMS_PDO_TX3_t* data, const CANMessage* msg)
{
    cps_setPdoTx3(data);
}

// @req CB-89875
void kioninterCAN_followUpCPS_BMS_PDO_TX1(const KIONINTER_CPS_BMS_PDO_TX1_t* data, const CANMessage* msg)
{
    cps_setCpsOutStatus(data->CPS_CPSout);
    cpsMonitor_setCPSout(data->CPS_CPSout);
    cps_setPdoTx1(data);
}

void kioninterCAN_followUpICDA_BMS_Result(const CANMessage* msg, bool synchronizedValue)
{
    // @req CB-15622 CB-91587
#if defined(BMS_CONFIG_ICDA_SENSORS) && BMS_CONFIG_ICDA_SENSORS == CONFIG_ENABLED
    icdaSensor_processCANresult(msg, synchronizedValue);
#endif
}

void kioninterCAN_followUpICDA_BMS_Response(const CANMessage* msg)
{
    icdaSensor_processCANresponse(msg);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific send functions END!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
