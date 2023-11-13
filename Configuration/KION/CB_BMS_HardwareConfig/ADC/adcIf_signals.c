/**
 * @file adcIf_signals.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "adcIf.h"
#include "adc_signal_config.h"
#include "debug.h"
#include "hwversion_config.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/

#if defined(USE_FIX_HARDWARE_CONFIGURATION) && USE_FIX_HARDWARE_CONFIGURATION == CONFIG_ENABLED

#if(USED_HARDWARE_VERSION == HARDWAREVERSION_1v0)
extern const ADC_Signals adc_signals_HW1V0;
const ADC_Signals* const adcSignals                = &adc_signals_HW1V0;
const ADC_SignalConfig* const* adcSignalConfigList = (const ADC_SignalConfig* const*)&adc_signals_HW1V0;
const uint16_t adcSignalConfigListSize             = sizeof(adc_signals_HW1V0) / sizeof(ADC_SignalConfig*);
#elif(USED_HARDWARE_VERSION == HARDWAREVERSION_1v3) || (USED_HARDWARE_VERSION == HARDWAREVERSION_1v4) || (USED_HARDWARE_VERSION == HARDWAREVERSION_1v5)
extern const ADC_Signals adc_signals_HW1V3;
const ADC_Signals* const adcSignals                = &adc_signals_HW1V3;
const ADC_SignalConfig* const* adcSignalConfigList = (const ADC_SignalConfig* const*)&adc_signals_HW1V3;
const uint16_t adcSignalConfigListSize             = sizeof(adc_signals_HW1V3) / sizeof(ADC_SignalConfig*);
#else

#error no valid hardware configuration for ADC signal configuration

#endif
#else
const ADC_Signals* adcSignals;
const ADC_SignalConfig* const* adcSignalConfigList;

#endif

//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/

/**--------------- HW Version ---------------------------*/

const ADC_SignalConfig ADC_HW_Version = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 0.0,
    .divider_R2 = 1.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .channel    = 16,
    .group      = ADC_GROUP1,
};

//***************************************************************************/
//************************** PRIVATE FUNCTION DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DEFINITIONS *******************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DEFINITIONS * ******************/
//***************************************************************************/

ADC_STATUS_t adc_getLssCoc_K1(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_LSS_COC_K1_Measure, voltage);
}

ADC_STATUS_t adc_getLssCoc_K2(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_LSS_COC_K2_Measure, voltage);
}

ADC_STATUS_t adc_getLssCoc_K3(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_LSS_COC_K3_Measure, voltage);
}

ADC_STATUS_t adc_getLssCoc_Kx(int32_t* voltage, uint8_t contactorIndex)
{
    switch(contactorIndex)
    {
        case 0:
            return adcIf_getVoltage(adcSignals->ADC_LSS_COC_K1_Measure, voltage);
        case 1:
            return adcIf_getVoltage(adcSignals->ADC_LSS_COC_K2_Measure, voltage);
        case 2:
            return adcIf_getVoltage(adcSignals->ADC_LSS_COC_K3_Measure, voltage);
        default:
            return ADC_INVALID_PORT;
    }
}

ADC_STATUS_t adc_getCurrent1_Ch1(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_Current_S1Ch1_Intern, voltage);
}

ADC_STATUS_t adc_getCurrent1_Ch2(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_Current_S1Ch2_Intern, voltage);
}

ADC_STATUS_t adc_getCurrent2_Ch1(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_Current_S2Ch1_Intern, voltage);
}

ADC_STATUS_t adc_getCurrent2_Ch2(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_Current_S2Ch2_Intern, voltage);
}

ADC_STATUS_t adc_getContactorSupply1(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_Vp_K1_Measure, voltage);
}

ADC_STATUS_t adc_getContactorSupply2(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_Vp_K2_Measure, voltage);
}

ADC_STATUS_t adc_getContactorSupply3(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_Vp_K3_Measure, voltage);
}

ADC_STATUS_t adc_getBoardVoltageKl30(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_Terminal_30, voltage);
}

ADC_STATUS_t adc_getBoardVoltage5V(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_5V_Measure, voltage);
}

ADC_STATUS_t adc_getBoardVoltage3V3(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_3V3_Measure, voltage);
}

ADC_STATUS_t adc_getTempSenseVoltage(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_Temp_Sense, voltage);
}

ADC_STATUS_t adc_getSbcMuxVoltage(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_VSense_Mux, voltage);
}

ADC_STATUS_t adc_getHvVoltage1(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_HV_Measure_1, voltage);
}

ADC_STATUS_t adc_getHvVoltage2(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_HV_Measure_2, voltage);
}

ADC_STATUS_t adc_getHvVoltage3(int32_t* voltage)
{
    return adcIf_getVoltage(adcSignals->ADC_HV_Measure_3, voltage);
}

ADC_STATUS_t adc_getHardwareVersionVoltage(int32_t* voltage)
{
    return adcIf_getVoltage(&ADC_HW_Version, voltage);
}

uint32_t adc_getConnectedChannels_ofAdcGroup(ADC_PortConfig port, ADC_GROUP_t group)
{
    uint32_t bitMask = 0u;
    for(uint8_t i = 0u; i < adcSignalConfigListSize; i++)
    {
        if(adcSignalConfigList[i]->deviceType == ADC_DEVICE_TMS570LS)
        {
            if(adcSignalConfigList[i]->port == port && adcSignalConfigList[i]->group == group)
            {
                bitMask |= (uint32_t)(1u << adcSignalConfigList[i]->channel);
            }
        }
    }
    return bitMask;
}
