/**
 * @file cpsData.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


#pragma once
//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdbool.h>
#include <stdint.h>
#include "nvm_config_id.h"

#include "canIf_types.h"
#include "kioninterCAN.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef enum
{
    CPS_INFO_BMS_STATE_UNDEFINED   = 0x00u,
    CPS_INFO_BMS_STATE_SHUTDOWN    = 0x01u,
    CPS_INFO_BMS_STATE_OPERATIONAL = 0x04u,
} CPS_INFO_t;

typedef struct
{
    uint32_t cpsOutLimit;
    uint32_t cpsOutLimitBoost;
    uint32_t cpsInputVoltageLimit;
    uint32_t cpsInfoRemainingCapacity;
} CpsConfig;

typedef struct
{
    uint8_t cpsError;
    uint8_t cpsBoostCurrentStatus;
    uint8_t cpsCurrentLimitationStatus;
    uint8_t cpsEmergency;
    uint8_t cpsStartupAfterPowerDown;
} CpsPdoTx1Data;

typedef struct
{
    uint16_t cpsOutI;
    int8_t cpsOutTemp1;
    int8_t cpsOutTemp2;
} CpsPdoTx2Data;

typedef struct
{
    uint16_t cpsVoltageInput;
    uint16_t cpsVoltageOutput;
} CpsPdoTx3Data;

typedef struct
{
    uint16_t cpsErrorCode;
    uint8_t cpsErrorRegister;
    uint32_t cpsDTC;
} CpsEmergency;

#define CPS_VEHICLE_EXTENDED_ADDRESS_RX 0x5Fu

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

/**
 * @fn cps_tunnelCpsVehicleUdsResponse
 * @brief tunnels cps uds response fron interCAN to customCAN
 * @param
 * @return
 */
void cps_tunnelCpsVehicleUdsResponse(const CANMessage* msg);

/**
 * @fn cps_tunnelCpsVehicleUdsRequest
 * @brief tunnels cps uds request fron customCAN to interCAN
 * @param
 * @return
 */
void cps_tunnelCpsVehicleUdsRequest(const CANMessage* msg);

/**
 * @fn cps_initCPS
 * @brief sets the init settings for cps
 * @param global variables
 * @return
 */
void cps_initCpsPdoSignals(void);

/**
 * @fn cps_setCpsOutStatus
 * @brief setter for cps out status flag
 * @param newSetting New state for cps out status flag
 * @return
 */
void cps_setCpsOutStatus(bool newSetting);

/**
 * @fn cps_getCpsOutStatus
 * @brief getter for cps out status flag
 * @param global variables
 * @return actual state of cps out status flag
 */
bool cps_getCpsOutStatus(void);

/**
 * @fn cps_getCpsOutReq
 * @brief getter for cps truck out flag
 * @param global variables
 * @return actual state of cps truck out flag
 */
bool cps_getCpsOutReq(void);

/**
 * @fn cps_setCpsOutBmsReq
 * @brief setter for cps truck out flag
 * @param newSetting New state for cps truck out flag
 * @return
 */
void cps_setCpsOutBmsReq(bool newSetting);

/**
 * @fn cps_getCpsOutBmsReq
 * @brief getter for cps truck out flag
 * @param global variables
 * @return actual state of cps truck out flag
 */
bool cps_getCpsOutBmsReq(void);

/**
 * @fn cps_setCpsOutDeactivationInhibitStatus
 * @brief setter for cps out deactivation inhibit flag
 * @param newSetting New state for cps truck out flag
 * @return
 */
void cps_setCpsOutDeactivationInhibitStatus(bool newSetting);

/**
 * @fn cps_getCpsOutDeactivationInhibitStatus
 * @brief getter for cps out deactivation inhibit flag
 * @param global variables
 * @return actual state of cps out deactivation inhibit flag
 */
bool cps_getCpsOutDeactivationInhibitStatus(void);

/**
 * @fn cps_setCpsPowerDownRegularShutdown
 * @brief setter for cps power down on regular shutdown flag
 * @return
 */
void cps_setCpsPowerDownRegularShutdown(void);

/**
 * @fn cps_getCpsPowerDownRegularShutdown
 * @brief getter for cps power down on regular shutdown flag
 * @param global variables
 * @return actual state of cps truck out flag (regular shutdown only)
 */
bool cps_getCpsPowerDownRegularShutdown(void);

/**
 * @fn cps_setCpsPowerDown
 * @brief setter for cps power down flag
 * @param newSetting New state for cps truck out flag
 * @return
 */
void cps_setCpsPowerDown(bool newSetting);

/**
 * @fn cps_getCpsPowerDown
 * @brief getter for cps power down flag
 * @param global variables
 * @return actual state of cps truck out flag
 */
bool cps_getCpsPowerDown(void);

/**
 * @fn cps_setCpsInfoBmsState
 * @brief setter for cps info bms state
 * @param newSetting New state bms state
 * @return
 */
void cps_setCpsInfoBmsState(CPS_INFO_t newSetting);

/**
 * @fn cps_getCpsInfoBmsState
 * @brief getter for cps info bms state
 * @param global variables
 * @return actual state of bms state
 */
CPS_INFO_t cps_getCpsInfoBmsState(void);

/**
 * @fn cps_setCpsHeatingEnable
 * @brief setter for cps heating enable
 * @param newSetting New state of cps heating enable
 * @return
 */
void cps_setCpsHeatingEnable(bool newSetting);

/**
 * @fn cps_getCpsHeatingEnable
 * @brief getter for cps heating enable
 * @param global variables
 * @return actual state of cps heating state
 */
bool cps_getCpsHeatingEnable(void);

/**
 * @fn cps_setCpsHeatingCurrent
 * @brief setter for cps heating current
 * @param newSetting New value of cps heating current
 * @return
 */
void cps_setCpsHeatingCurrent(uint16_t newSetting);

/**
 * @fn cps_getCpsHeatingCurrent
 * @brief getter for cps heating current
 * @param global variables
 * @return actual value of cps heating current
 */
uint16_t cps_getCpsHeatingCurrent(void);

void cps_checkNvm(const uint8_t* mirror, uint16_t length);

void cps_copyNvmForWrite(uint8_t* mirror, uint16_t length);

void cps_waitForNvm(void);

/**
 * @brief Save received CPS CAN Message 0x182u data to module variable
 * */
void cps_setPdoTx1(const KIONINTER_CPS_BMS_PDO_TX1_t* data);

/**
 * @brief Save received CPS CAN Message 0x282u data to module variable
 * */
void cps_setPdoTx2(const KIONINTER_CPS_BMS_PDO_TX2_t* data);

/**
 * @brief Save received CPS CAN Message 0x382u data to module variable
 * */
void cps_setPdoTx3(const KIONINTER_CPS_BMS_PDO_TX3_t* data);

/**
 * @brief Save received CPS CAN Message 0x82u data to module variable
 * */
void cps_setCpsEmergency(const KIONINTER_CPS_BMS_EMERGENCY_t* data);

/**
 * @brief return last received CPS OUT temperature
 * @return cpsOutCurrent
 * */
uint16_t cps_getCpsOutI(void);

/**
 * @brief The function shall set cps wake up signal for two seconds to high state
 *
 */
void cps_enableWakeUp(void);

/**
 * @brief return status of deep discharge imminent flag
 * @return deep discharge imminent
 * */
bool cps_isDeepDischargeImminent(void);

/**
 * @brief return status of deep discharge possible flag
 * @return deep discharge possible
 * */
bool cps_isDeepDischargePossible(void);
