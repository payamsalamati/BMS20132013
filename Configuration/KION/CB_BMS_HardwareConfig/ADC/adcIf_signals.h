/**
 * @file adcIf_signals.h
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

#include <stdint.h>
#include "adcIf.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

ADC_STATUS_t adc_getLssCoc_K1(int32_t* voltage);
ADC_STATUS_t adc_getLssCoc_K2(int32_t* voltage);
ADC_STATUS_t adc_getLssCoc_K3(int32_t* voltage);
ADC_STATUS_t adc_getLssCoc_Kx(int32_t* voltage, uint8_t contactorIndex);
ADC_STATUS_t adc_getCurrent1_Ch1(int32_t* voltage);
ADC_STATUS_t adc_getCurrent1_Ch2(int32_t* voltage);
ADC_STATUS_t adc_getCurrent2_Ch1(int32_t* voltage);
ADC_STATUS_t adc_getCurrent2_Ch2(int32_t* voltage);
ADC_STATUS_t adc_getContactorSupply1(int32_t* voltage);
ADC_STATUS_t adc_getContactorSupply2(int32_t* voltage);
ADC_STATUS_t adc_getContactorSupply3(int32_t* voltage);
ADC_STATUS_t adc_getBoardVoltageKl30(int32_t* voltage);
ADC_STATUS_t adc_getBoardVoltage5V(int32_t* voltage);
ADC_STATUS_t adc_getBoardVoltage3V3(int32_t* voltage);
ADC_STATUS_t adc_getTempSenseVoltage(int32_t* voltage);
ADC_STATUS_t adc_getSbcMuxVoltage(int32_t* voltage);
ADC_STATUS_t adc_getHvVoltage1(int32_t* voltage);
ADC_STATUS_t adc_getHvVoltage2(int32_t* voltage);
ADC_STATUS_t adc_getHvVoltage3(int32_t* voltage);
ADC_STATUS_t adc_getHardwareVersionVoltage(int32_t* voltage);
uint32_t adc_getConnectedChannels_ofAdcGroup(ADC_PortConfig port, ADC_GROUP_t group);
