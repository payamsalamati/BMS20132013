/**
 * @file     afeIf_config.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include <stdlib.h>

#include "afeIf.h"

#include "MC33771/afe_MC33771.h"
#include "afe_MC33771_config.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/


#define AFE_USED_DEVICE 0

//***************************************************************************/
//************************** PUBLIC VARIABLE DECLARATIONS ******************/
//***************************************************************************/

const AFE_Type* const afeTypes[] = {
    &afe_MC33771,
};

const uint8_t AFE_TYPES_LENGTH = sizeof(afeTypes) / sizeof(AFE_Type*);


//***************************************************************************/
//************************** PRIVATE FUNCTION DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DEFINITIONS *******************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DEFINITIONS * ******************/
//***************************************************************************/


void afeIf_wakeup(void)
{
    afeTypes[AFE_USED_DEVICE]->powerMode->wakeup();
}

AFE_Status afeIf_init(void)
{
    return afeTypes[AFE_USED_DEVICE]->init->init();
}

AFE_Status afeIf_reinitOneCSC(uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->init->reinit(cscAddress);
}

AFE_Status afeIf_go2sleepBroadcast(void)
{
    return afeTypes[AFE_USED_DEVICE]->powerMode->go2sleepBroadcast();
}

void afeIf_sendNops(void)
{
    afeTypes[AFE_USED_DEVICE]->powerMode->sendNops();
}

AFE_Status afeIf_setAFEConfigs(uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->init->setConfigs(cscAddress);
}

AFE_Status afeIf_setAFEConfigsBroadcast()
{
    return afeTypes[AFE_USED_DEVICE]->init->setConfigsBroadcast();
}

AFE_Status afeIf_startNewConversion(uint8_t cscAddress, AFE_Averaging_Samples numSamples)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->startNewConversion(cscAddress, numSamples);
}

AFE_Status afeIf_startNewBroadcastConversion(AFE_Averaging_Samples numSamples)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->startNewBroadcastConversion(numSamples);
}

AFE_Status afeIf_getConversionState(AFE_ConversionState* state, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getConversionState(state, cscAddress);
}

AFE_Status afeIf_getCellVoltageN(AFE_CellTerminalNr cell, uint16_t* cellVoltage, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getCellVoltageN(cell, cellVoltage, cscAddress);
}

AFE_Status afeIf_getCellVoltagesAll(uint16_t* cellVoltage, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getCellVoltagesAll(cellVoltage, cscAddress);
}

AFE_Status afeIf_getCellVoltagesSorted(uint16_t* cellVoltages, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getCellVoltagesSorted(cellVoltages, cscAddress);
}

AFE_Status afeIf_getModuleVoltage(uint16_t* moduleVoltage, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getModuleVoltage(moduleVoltage, cscAddress);
}

AFE_Status afeIf_getTemperatureN(uint8_t sensorNumber, int16_t* temperature, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getTemperatureN(sensorNumber, temperature, cscAddress);
}

AFE_Status afeIf_getTemperaturesSorted(int16_t* temperatures, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getAllMeasurements(NULL, NULL, NULL, temperatures, NULL, NULL, NULL, cscAddress);
}

AFE_Status afeIf_getBalancingTemperaturesSorted(int16_t* balTemperatures, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getAllMeasurements(NULL, NULL, NULL, NULL, balTemperatures, NULL, NULL, cscAddress);
}

AFE_Status afeIf_getApplicationTemperaturesSorted(int16_t* appTemperatures, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getAllMeasurements(NULL, NULL, NULL, NULL, NULL, appTemperatures, NULL, cscAddress);
}

AFE_Status afeIf_getAFETemperature(int16_t* afeTemperature, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getAFETemperature(afeTemperature, cscAddress);
}

AFE_Status afeIf_getIsense(int32_t* afeCurrent, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getIsense(afeCurrent, cscAddress);
}

AFE_Status afeIf_getTemperaturesAll(int16_t* temperatures, int16_t* balTemperatures, int16_t* applicationTemperatures, int16_t* afeTemperature, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getTemperaturesAll(temperatures, balTemperatures, applicationTemperatures, afeTemperature, cscAddress);
}
AFE_Status afeIf_getAllMeasurements(int32_t* afeCurrents, uint16_t* cellVoltages, uint16_t* moduleVoltage, int16_t* temperatures, int16_t* balTemperatures, int16_t* applicationTemperatures, int16_t* afeTemperatures, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->measurements->getAllMeasurements(afeCurrents, cellVoltages, moduleVoltage, temperatures, balTemperatures, applicationTemperatures, afeTemperatures, cscAddress);
}

void afeIf_pauseBalancingBroadcast(AFE_Status* afeResults)
{
    afeTypes[AFE_USED_DEVICE]->balancing->pauseBalancingBroadcast(afeResults);
}
void afeIf_resumeBalancingBroadcast(AFE_Status* afeResults)
{
    afeTypes[AFE_USED_DEVICE]->balancing->resumeBalancingBroadcast(afeResults);
}
AFE_Status afeIf_setCellBalancing(uint16_t balStatusMask, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->balancing->setCellBalancingState(balStatusMask, cscAddress);
}
AFE_Status afeIf_getCellBalancing(uint16_t* balStatusMask, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->balancing->getCellBalancingState(balStatusMask, cscAddress);
}


void afeIf_controlBalancing(AFE_Status* results)
{
    if((afeTypes[AFE_USED_DEVICE] != NULL)
       && (afeTypes[AFE_USED_DEVICE]->balancing != NULL)
       && (afeTypes[AFE_USED_DEVICE]->balancing->balancingControl != NULL))
    {
        afeTypes[AFE_USED_DEVICE]->balancing->balancingControl(results);
    }
}
void afeIf_disableBalancing(AFE_Status* results)
{
    if((afeTypes[AFE_USED_DEVICE] != NULL)
       && (afeTypes[AFE_USED_DEVICE]->balancing != NULL)
       && (afeTypes[AFE_USED_DEVICE]->balancing->disableBalancing != NULL))
    {
        afeTypes[AFE_USED_DEVICE]->balancing->disableBalancing(results);
    }
}
void afeIf_setBalancingBitmask(uint8_t cscId, uint16_t newBitmask)
{
    if((afeTypes[AFE_USED_DEVICE] != NULL)
       && (afeTypes[AFE_USED_DEVICE]->balancing != NULL)
       && (afeTypes[AFE_USED_DEVICE]->balancing->setBalancingBitmask != NULL))
    {
        afeTypes[AFE_USED_DEVICE]->balancing->setBalancingBitmask(cscId, newBitmask);
    }
}
uint16_t afeIf_getCellBalancingBitmask(uint8_t cscId)
{
    uint16_t returnBitMask = 0xFFFF;
    if((afeTypes[AFE_USED_DEVICE] != NULL)
       && (afeTypes[AFE_USED_DEVICE]->balancing != NULL)
       && (afeTypes[AFE_USED_DEVICE]->balancing->getBalancingBitmask != NULL))
    {
        returnBitMask = afeTypes[AFE_USED_DEVICE]->balancing->getBalancingBitmask(cscId);
    }
    return returnBitMask;
}

AFE_Status afeIf_writeEEPROM(uint8_t eepromRegister, const uint8_t data, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->memoryAccess->writeEEPROM(eepromRegister, data, cscAddress);
}

AFE_Status afeIf_readEEPROM(uint8_t eepromRegister, uint8_t* regContent, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->memoryAccess->readEEPROM(eepromRegister, regContent, cscAddress);
}

void afeIf_readEEPROMBroadcast(AFE_Status* results, uint8_t eepromRegister, uint8_t* regContent)
{
    return afeTypes[AFE_USED_DEVICE]->memoryAccess->readEEPROMBroadcast(results, eepromRegister, regContent);
}

AFE_Status afeIf_setGPIOState(uint8_t cscAddress, uint8_t gpio, IO_VAL_t state)
{
    return afeTypes[AFE_USED_DEVICE]->gpioControl->setGpioState(cscAddress, gpio, state);
}
AFE_Status afeIf_getGPIOsState(uint8_t cscAddress, uint8_t* stateMatrix)
{
    return afeTypes[AFE_USED_DEVICE]->gpioControl->getAllGpiosStatus(cscAddress, stateMatrix);
}

void afeIf_SM01_OV_UV_Functional_Verification(AFE_Status* result, uint16_t* detected_OV_failure, uint16_t* detected_UV_failure)
{
    afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM01(result, detected_OV_failure, detected_UV_failure);
}

void afeIf_SM02_CTx_Open_Detect(AFE_Status* result, uint16_t* detectedOpenWireBitMask, uint16_t* detectedShortedSWxBitMask, uint16_t* detectedOpenSWxBitsMask)
{
    afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM02(result, detectedOpenWireBitMask, detectedShortedSWxBitMask, detectedOpenSWxBitsMask);
}

void afeIf_SM02_Alternative_CTx_Open_Detect(AFE_Status* result, uint16_t* detectedOpenWireBitMask)
{
    afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM02_alternative(result, detectedOpenWireBitMask);
}

AFE_Status afeIf_SM03_CellVoltage_Channel_Functional_Verification(uint16_t* incorrectVoltageChannel, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM03(incorrectVoltageChannel, cscAddress);
}

void afeIf_SM04_CTx_Cell_Terminal_Leakage_Monitor(AFE_Status* result, uint16_t* leakyCell, uint16_t* faultyConnector)
{
    afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM04(result, leakyCell, faultyConnector);
}

void afeIf_SM05_GPIOx_OT_UT_Functional_Verification(AFE_Status* result, uint8_t* detected_OTUT_failure)
{
    afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM05(result, detected_OTUT_failure);
}

AFE_Status afeIf_SM06_GPIOx_Open_Terminal_Diagnostics(uint16_t* detected_open_GPIO, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM06(detected_open_GPIO, cscAddress);
}

AFE_Status afeIf_SM07_ADC1_Functional_Verification(bool* adcFunctionalVerificationFailure, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM07(adcFunctionalVerificationFailure, cscAddress);
}

AFE_Status afeIf_SM18_Check_Of_Register_Content(uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM18(cscAddress);
}

AFE_Status afeIf_SM29a_UV_Internal_Detection(uint16_t* detectedUVFaults, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM29a(detectedUVFaults, cscAddress);
}

AFE_Status afeIf_SM29b_OV_Internal_Detection(uint16_t* detectedOVFaults, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM29b(detectedOVFaults, cscAddress);
}

AFE_Status afeIf_SM33_Temperatures_Plausibility_Check(uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM33(cscAddress);
}

void afeIf_SM34_OvUvDetectionInThePackController(AFE_Status* result, uint16_t* detectedOVUVFaults)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM34(result, detectedOVUVFaults);
}

AFE_Status afeIf_SM40_Cell_Balance_Open_Load_Detection(uint16_t* detectedOL, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM40(detectedOL, cscAddress);
}

AFE_Status afeIf_SM41_Cell_Balance_Short_Detection(uint16_t* detectedShort, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM41(detectedShort, cscAddress);
}

AFE_Status afeIf_SM44_Cell_Voltage_Plausibility_Check(uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM44(cscAddress);
}

AFE_Status afeIf_SM45_Vpwr_Compartion_To_Sum_Of_Cell_Voltages(uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->run_SM45(cscAddress);
}

AFE_Status afeIf_Read_Fault_Registers(AFE_FAULT1* fault1, AFE_FAULT2* fault2, AFE_FAULT3* fault3, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->readFaultRegisters(fault1, fault2, fault3, cscAddress);
}

AFE_Status afeIf_Reset_Register_Value(uint16_t registerAddress, uint16_t resetFlag, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->resetRegisterValue(registerAddress, resetFlag, cscAddress);
}

AFE_Status afeIf_OT_UT_Internal_Detection(uint16_t* detectedOTUTFaults, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosis->getOTUTValues(detectedOTUTFaults, cscAddress);
}

uint8_t afeIf_getNumberOfCsc(void)
{
    return afeTypes[AFE_USED_DEVICE]->init->getNumberOfInitialisedCSC();
}

AFE_Status afeIf_SM02_Broadcast_CTx_Open_Detect(void)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->run_SM02_broadcast();
}

AFE_Status afeIf_SM03_Broadcast_Cell_Voltage_Channel_Functional_Verification(void)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->run_SM03_broadcast();
}

void afeIf_SM04_Broadcast_CTx_Cell_Terminal_Leakage_Monitor(AFE_Status* result, uint16_t* leakyCell, uint16_t* faultyConnector)
{
    afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->run_SM04_broadcast(result, leakyCell, faultyConnector);
}

AFE_Status afeIf_SM05_Broadcast_GPIOx_OT_UT_Functional_Verification(void)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->run_SM05_broadcast();
}

AFE_Status afeIf_SM06_Broadcast_GPIOx_Open_Terminal_Diagnostics(void)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->run_SM06_broadcast();
}

AFE_Status afeIf_SM07_Broadcast_ADC1_Functional_Verification(void)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->run_SM07_broadcast();
}

AFE_Status afeIf_SM40_Broadcast_Cell_Balance_Open_Load_Detection(void)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->run_SM40_broadcast();
}

AFE_Status afeIf_Broadcast_Read_Fault_Registers(AFE_FAULT1* fault1, AFE_FAULT2* fault2, AFE_FAULT3* fault3, uint8_t cscAddress)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->readFaultRegisters_broadcast(fault1, fault2, fault3, cscAddress);
}

AFE_Status afeIf_SM18_Broadcast_Check_Of_Register_Content(void)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->run_SM18_broadcast();
}

AFE_Status afeIf_SM33_Broadcast_Temperatures_Plausibility_Check(void)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->run_SM33_broadcast();
}

AFE_Status afeIf_SM44_Broadcast_Cell_Voltage_Plausibility_Check(void)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->run_SM44_broadcast();
}

AFE_Status afeIf_SM45_Broadcast_Vpwr_Compartion_To_Sum_Of_Cell_Voltages(void)
{
    return afeTypes[AFE_USED_DEVICE]->diagnosisBroadcast->run_SM45_broadcast();
}
