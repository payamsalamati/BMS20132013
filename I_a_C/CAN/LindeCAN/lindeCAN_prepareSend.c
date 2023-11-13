/**
 *
 * @file lindeCAN_prepareSend.c
 * @modulenumber 0x0D
 *
 * @author Generated File with DPCParser release-1.3.4 Commit 1347995
 * @created on Thu Mar 30 17:16:56 CEST 2023
 * @brief This module write data from the CAN messages into the
             structs, corresponding to the message ID
 * @copyright Futavis GmbH, Aachen 2023 - alle Rechte vorbehalten
 * @details Generated from file "lindeCAN.sym"
 * @par Global variables
 * - lindeLiIoBMS_SDOresp_Traction - SDO Tx, node 0x0D (LIB with Linde BMZ protocol), SDO client: KMC -
 * - lindeLiIoBMS_SDOresp_LiIoCharger - SDO Tx, node 0x5D (LIB with Linde BMZ protocol), SDO client: OBC, EXC -
 * - lindeLiIoBMS_PDO5 - PDO5 (Tx), node 0x01 (LIB with Linde BMZ prototol) -
 * - lindeLiIoBMS_PDO4 - PDO4 (Tx), node 0x0D (LIB with Linde BMZ prototol) -
 * - lindeLiIoBMS_PDO3 - PDO3 (Tx), node 0x0D (LIB with Linde BMZ prototol) -
 * - lindeLiIoBMS_PDO2 - PDO2 (Tx), node 0x0D (LIB with Linde BMZ prototol) -
 * - lindeLiIoBMS_PDO1 - PDO1 (Tx), node 0x0D (LIB with Linde BMZ protocol) -
 * - lindeLiIoBMS_Heartbeat - heartbeat (NMT error control), node 0x0D (LIB with Linde BMZ protocol) -
 * @par changes
 * - first creation Thu Mar 30 17:16:56 CEST 2023
 */

//******************* INCLUDES ********************************//
#include "lindeCAN.h"

#include "canOpenStmFct.h"
#include "canopen_config.h"
#include "canData.h"
#include "stringCurrentMeasurement.h"
#include "logging.h"
#include "kbsIntegration.h"
#include "highVoltageMeasurement.h"
#include "libIdentification.h"
#include "protocolInterface.h"
#include "lindeProtocol.h"
#include "stateFunctions.h"
#include "voltageMonitor_config.h"

//**************************PUBLIC VARIABLE DEFINITIONS ******************************//

//************************** PUBLIC FUNCTION DEFINITIONS *****************************************//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific receive functions !!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!! Please add the needed functions for your project !!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

void lindeCAN_prepareLiIoBMS_SDOresp_Traction(LINDE_LIIOBMS_SDORESP_TRACTION_t* linde_liiobms_sdoresp_traction)
{

    //	linde_liiobms_sdoresp_traction->LiIoBMS_SDOresp_Traction_Data = dataInterface_getXXX();
}

void lindeCAN_prepareLiIoBMS_SDOresp_LiIoCharger(LINDE_LIIOBMS_SDORESP_LIIOCHARGER_t* linde_liiobms_sdoresp_liiocharger)
{

    //	linde_liiobms_sdoresp_liiocharger->LiIoBMS_SDOresp_LiIoCharger_Data = dataInterface_getXXX();
}

void lindeCAN_prepareLiIoBMS_PDO5(LINDE_LIIOBMS_PDO5_t* linde_liiobms_pdo5)
{
    // @req CB-91654
    linde_liiobms_pdo5->LiIoBMS_MaxDischargePower2 = (kbsIntegration_getMaxDischargingPowerPulse() * LINDE_LIIOBMS_MAXDISCHARGEPOWER2_FACTOR) - LINDE_LIIOBMS_MAXDISCHARGEPOWER2_OFFSET;
    linde_liiobms_pdo5->LiIoBMS_MaxChargePower2    = (kbsIntegration_getMaxChargingPowerPulse() * LINDE_LIIOBMS_MAXCHARGEPOWER2_FACTOR) - LINDE_LIIOBMS_MAXCHARGEPOWER2_OFFSET;
    //	linde_liiobms_pdo5->LiIoBMS_OutputVoltage = (dataInterface_getXXX() * LINDE_LIIOBMS_OUTPUTVOLTAGE_FACTOR) - LINDE_LIIOBMS_OUTPUTVOLTAGE_OFFSET;
}

void lindeCAN_prepareLiIoBMS_PDO4(LINDE_LIIOBMS_PDO4_t* linde_liiobms_pdo4)
{
    // @req CB-91653
    linde_liiobms_pdo4->LiIoBMS_SOCwithSOH          = kbsIntegration_getSocWithSOH_Internal();
    linde_liiobms_pdo4->LiIoBMS_SOCwithoutSOH       = kbsIntegration_getSocWithoutSOH_Internal();
    linde_liiobms_pdo4->LiIoBMS_MaxChargeVoltage    = (((CELL_VOLTAGE_MAX_ERR_DETECT_VAL * CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL * CELL_MODULE_CONFIG_STRING_NO_OF_MODULES_SERIAL) / 1000.0) * LINDE_LIIOBMS_MAXCHARGEVOLTAGE_FACTOR) - LINDE_LIIOBMS_MAXCHARGEVOLTAGE_OFFSET;
    linde_liiobms_pdo4->LiIoBMS_MinDischargeVoltage = (((CELL_VOLTAGE_MIN_ERR_DETECT_VAL * CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL * CELL_MODULE_CONFIG_STRING_NO_OF_MODULES_SERIAL) / 1000.0) * LINDE_LIIOBMS_MINDISCHARGEVOLTAGE_FACTOR) - LINDE_LIIOBMS_MINDISCHARGEVOLTAGE_OFFSET;
}

void lindeCAN_prepareLiIoBMS_PDO3(LINDE_LIIOBMS_PDO3_t* linde_liiobms_pdo3)
{

    //	linde_liiobms_pdo3->LiIoBMS_DTC4 = dataInterface_getXXX();
    //	linde_liiobms_pdo3->LiIoBMS_DTC1 = dataInterface_getXXX();
    //	linde_liiobms_pdo3->LiIoBMS_DTC3 = dataInterface_getXXX();
    //	linde_liiobms_pdo3->LiIoBMS_DTC2 = dataInterface_getXXX();
}

void lindeCAN_prepareLiIoBMS_PDO2(LINDE_LIIOBMS_PDO2_t* linde_liiobms_pdo2)
{
    // @req CB-91651
    linde_liiobms_pdo2->LiIoBMS_MaxChargeCurrent2      = (kbsIntegration_getDeratingChargeLimit() * LINDE_LIIOBMS_MAXCHARGECURRENT2_FACTOR) - LINDE_LIIOBMS_MAXCHARGECURRENT2_OFFSET;
    linde_liiobms_pdo2->LiIoBMS_MaxDischargeCurrent2   = (kbsIntegration_getDeratingDischargeLimit() * LINDE_LIIOBMS_MAXDISCHARGECURRENT2_FACTOR) - LINDE_LIIOBMS_MAXDISCHARGECURRENT2_OFFSET;
    linde_liiobms_pdo2->LiIoBMS_MaxDischargeCurrent100 = (kbsIntegration_getDeratingDischargeLimitContinous() * LINDE_LIIOBMS_MAXDISCHARGECURRENT100_FACTOR) - LINDE_LIIOBMS_MAXDISCHARGECURRENT100_OFFSET;
    linde_liiobms_pdo2->LiIoBMS_MaxChargeCurrent100    = (kbsIntegration_getDeratingChargeLimitContinous() * LINDE_LIIOBMS_MAXCHARGECURRENT100_FACTOR) - LINDE_LIIOBMS_MAXCHARGECURRENT100_OFFSET;
}

void lindeCAN_prepareLiIoBMS_PDO1(LINDE_LIIOBMS_PDO1_t* linde_liiobms_pdo1)
{
    // @req CB-91650
    //linde_liiobms_pdo1->LiIoBMS_SOH            = dataInterface_getXXX();
    linde_liiobms_pdo1->LiIoBMS_BatteryCurrent = (stringCurrentMeasurement_getValue() * LINDE_LIIOBMS_BATTERYCURRENT_FACTOR) - LINDE_LIIOBMS_BATTERYCURRENT_OFFSET;
    // TODO: globalState enum
    // For now we use stm to check if ready/driving/charging
    if(stmFct_getLibReady() == true)
    {
        linde_liiobms_pdo1->LiIoBMS_BatteryState = LIIOBMS_READY;
    }
    else if(stmFct_getDriveEnabled() == true)
    {
        linde_liiobms_pdo1->LiIoBMS_BatteryState = LIIOBMS_DRIVE;
    }
    else if(stmFct_getChargeEnabled() == true)
    {
        linde_liiobms_pdo1->LiIoBMS_BatteryState = LIIOBMS_CHARGE;
    }
    else
    {
        linde_liiobms_pdo1->LiIoBMS_BatteryState = LIIOBMS_ERROR;
    }
    linde_liiobms_pdo1->LiIoBMS_BatteryVoltage = (highVoltageMeasurement_getMasterHvVoltagesValue(0) * LINDE_LIIOBMS_BATTERYVOLTAGE_FACTOR) - LINDE_LIIOBMS_BATTERYVOLTAGE_OFFSET;
}

void lindeCAN_prepareLiIoBMS_Heartbeat(LINDE_LIIOBMS_HEARTBEAT_t* linde_liiobms_heartbeat)
{
    // @req CB-91647
    if(protocolInterface_getConnectedDevice() == CHARGER)
    {
        linde_liiobms_heartbeat->LiIoBMS_State = canOpenStm_getCanOpenState(&canOpenConfigLindeCharger);
    }
    else
    {
        linde_liiobms_heartbeat->LiIoBMS_State = canOpenStm_getCanOpenState(&canOpenConfigLinde);
    }
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!! Project specific send functions END!!!!!!!!!!!!!!!!!!!//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
