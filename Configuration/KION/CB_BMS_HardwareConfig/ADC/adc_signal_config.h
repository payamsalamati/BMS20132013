/**
 * @file adc_signal_config.h
 * @copyright Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */

#pragma once

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include <stdint.h>

#include "adcIf.h"

//***************************************************************************/
//************************** PUBLIC TYPEDEFS ********************************/
//***************************************************************************/

typedef struct
{
    const ADC_SignalConfig* ADC_LSS_COC_K1_Measure;
    const ADC_SignalConfig* ADC_LSS_COC_K2_Measure;
    const ADC_SignalConfig* ADC_LSS_COC_K3_Measure;
    const ADC_SignalConfig* ADC_Current_S1Ch1_Intern;
    const ADC_SignalConfig* ADC_Current_S1Ch2_Intern;
    const ADC_SignalConfig* ADC_Current_S2Ch1_Intern;
    const ADC_SignalConfig* ADC_Current_S2Ch2_Intern;
    const ADC_SignalConfig* ADC_Vp_K1_Measure;
    const ADC_SignalConfig* ADC_Vp_K2_Measure;
    const ADC_SignalConfig* ADC_Vp_K3_Measure;
    const ADC_SignalConfig* ADC_Terminal_30;
    const ADC_SignalConfig* ADC_5V_Measure;
    const ADC_SignalConfig* ADC_3V3_Measure;
    const ADC_SignalConfig* ADC_Temp_Sense;
    const ADC_SignalConfig* ADC_VSense_Mux;
    const ADC_SignalConfig* ADC_AUXm_K1_Sensor;
    const ADC_SignalConfig* ADC_AUXm_K2_Sensor;
    const ADC_SignalConfig* ADC_AUXm_K3_Sensor;
    const ADC_SignalConfig* ADC_HV_Measure_1;
    const ADC_SignalConfig* ADC_HV_Measure_2;
    const ADC_SignalConfig* ADC_HV_Measure_3;
} ADC_Signals;

//***************************************************************************/
//************************** PUBLIC VARIABLE DEFINITIONS ********************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DECLARATIONS *******************/
//***************************************************************************/
