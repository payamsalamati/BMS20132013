/**
 * @file canData.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "kionCAN_sendReceive.h"
#include "lindeCAN_sendReceive.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void canData_storeLastTimeData(KION_TIME_t lastValue);
void canData_storeLastTimestampData(KION_TIMESTAMP_t lastValue);
void canData_storeLastLibPdoRx1Data(KION_LIB_PDO_RX1_t lastValue);
void canData_storeLastLibPdoRx4Data(KION_LIB_PDO_RX4_t lastValue);
void canData_storeLastLibEmergencyData(KION_LIB_EMERGENCY_t lastValue);
void canData_storeLastLibHeartbeatData(KION_LIB_HEARTBEAT_t lastValue);
void canData_storeLastLibPdoTx1Data(KION_LIB_PDO_TX1_t lastValue);
void canData_storeLastLibPdoTx2Data(KION_LIB_PDO_TX2_t lastValue);
void canData_storeLastLibPdoTx3Data(KION_LIB_PDO_TX3_t lastValue);
void canData_storeLastLibPdoTx4Data(KION_LIB_PDO_TX4_t lastValue);
void canData_storeLastLibPdoTx5Data(KION_LIB_PDO_TX5_t lastValue);
void canData_storeLastLibPdoTx6Data(KION_LIB_PDO_TX6_t lastValue);
void canData_storeLastLibPdoTx7Data(KION_LIB_PDO_TX7_t lastValue);
void canData_storeLastLibPdoTx8Data(KION_LIB_PDO_TX8_t lastValue);
void canData_storeLastHeartbtBmsData(KION_HEARTBTBMS_t lastValue);

void canData_storeLastLindePdoRx1Data(LINDE_LIIOCHARGER_PDO1_t lastValue);
void canData_storeLastLindeTractionPdoRx4Data(LINDE_TRACTION_PDO4_t lastValue);
void canData_storeLastLindeTimestampData(LINDE_TIMESTAMP_t lastValue);

uint32_t canData_getLastCanOpenTimeOfDay_ms(void);
uint16_t canData_getLastCanOpenTimeOfDay_Days(void);
uint32_t canData_getLastDateTime(void);
uint32_t canData_getLastLibChargingPower(void);
uint32_t canData_getLastLibChargingVoltage(void);
uint16_t canData_getLastLibChargingCurrent(void);
uint16_t canData_getLastLibPowerConsumptionAverage(void);
uint32_t canData_getLastTruckOperatingHours(void);
uint8_t canData_getLastTruckOperatingHoursMode(void);
uint16_t canData_getLastEmergencyCodeLib(void);
uint8_t canData_getLastEmergencyRegisterObjectLib(void);
uint32_t canData_getLastUdsDtcLib(void);
uint8_t canData_getLastKionCanopenStateLib(void);
uint8_t canData_getLastLibShockWarning(void);
uint8_t canData_getLastLibServiceRequired(void);
uint8_t canData_getLastLibInitComplete(void);
uint8_t canData_getLastLibCurrentLimited(void);
uint8_t canData_getLastLibTemperatureTooLow(void);
uint8_t canData_getLastLibReady(void);
uint8_t canData_getLastLibEmergencyOperation(void);
uint8_t canData_getLastLibTemperatureTooHigh(void);
uint8_t canData_getLastLibError(void);
uint8_t canData_getLastLibInDrivingMode(void);
uint8_t canData_getLastLibFatalError(void);
uint8_t canData_getLastLibInChargingMode(void);
uint8_t canData_getLastLibCpsOutputActive(void);
uint8_t canData_getLastLibCpsOutputDeactivationInhibit(void);
uint32_t canData_getLastLibCurrent(void);
uint32_t canData_getLastLibVoltageInFrontOfContactor(void);
uint32_t canData_getLastLibVoltageAfterContactor(void);
uint32_t canData_getLastLibPower(void);
uint8_t canData_getLastLibStateOfHealth(void);
uint32_t canData_getLastLibMaxDischargingPower2s(void);
uint32_t canData_getLastLibMaxDischargingPower100s(void);
uint8_t canData_getLastLibSocWithSoh(void);
uint32_t canData_getLastLibMinDischargingVoltage(void);
uint32_t canData_getLastLibChargingPower2s(void);
uint8_t canData_getLastLibSocWithoutSoh(void);
uint32_t canData_getLastLibMaxChargingVoltage(void);
uint32_t canData_getLastLibMaxChargingPower100s(void);
uint32_t canData_getLastLibMaxDischargingCurrent2s(void);
uint32_t canData_getLastLibMaxDischargingCurrent100s(void);
uint32_t canData_getLastLibMaxChargingCurrent2s(void);
uint32_t canData_getLastLibMaxChargingCurrent100s(void);
uint8_t canData_getLastLibPowerpathOk(void);
uint16_t canData_getLastLibSocWithoutSohFine(void);
int8_t canData_getLastLibMinTemperature(void);
int8_t canData_getLastLibMaxTemperature(void);
uint8_t canData_getLastLibPowerpathOk(void);
int64_t canData_getLastLibCurrentUnfiltered(void);
uint64_t canData_getLastLibVoltageInFrontOfContactorUnfiltered(void);
uint64_t canData_getLastLibVoltageAfterContactorUnfiltered(void);
int32_t canData_getLastBmsBatCurr(void);
uint16_t canData_getLastBmsBatVolt(void);
uint16_t canData_getLastBmsMaxDirCurr(void);
uint16_t canData_getLastBmsMaxCharCurr(void);
uint16_t canData_getLastBmsNormCharCur(void);
uint16_t canData_getLastBmsPowForChar(void);
uint16_t canData_getLastBmsPowForDis(void);
uint16_t canData_getLastBmsCharVoltHigh(void);
uint16_t canData_getLastBmsDisVoltMin(void);
uint8_t canData_getLastBmsSocWithSoh(void);
uint8_t canData_getLastBmsSocWoutSoh(void);
uint8_t canData_getLastBmsSoh(void);
uint8_t canData_getLastBmsBatStat(void);
uint8_t canData_getLastFaultBatteryCode1(void);
uint8_t canData_getLastFaultBatteryCode2(void);
uint8_t canData_getLastFaultBatteryCode3(void);
uint8_t canData_getLastFaultBatteryCode4(void);
uint8_t canData_getLastFaultBatteryCode5(void);
bool canData_getLibPdoRx1DataReceived(void);
void canData_setLibPdoRx1DataReceived(void);
bool canData_getLibPdoRx4DataReceived(void);
void canData_setLibPdoRx4DataReceived(bool newValue);
