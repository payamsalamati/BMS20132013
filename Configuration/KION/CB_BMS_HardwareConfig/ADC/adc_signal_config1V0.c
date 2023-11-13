/**
 * @file adc_signal_config1V0.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>
#include "adcCurrentSensorIf.h"
#include "adcIf.h"
#include "adc_signal_config.h"
#include "debug.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

/**--------------- LSS COC K1 Measure ---------------------------*/
static const ADC_SignalConfig ADC_LSS_COC_K1_Measure_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 0.0,
    .divider_R2 = 1.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 6,
};

/**--------------- LSS COC K2 Measure ---------------------------*/
static const ADC_SignalConfig ADC_LSS_COC_K2_Measure_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 0.0,
    .divider_R2 = 1.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 13,
};

/**--------------- LSS COC K3 Measure ---------------------------*/
static const ADC_SignalConfig ADC_LSS_COC_K3_Measure_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 0.0,
    .divider_R2 = 1.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 3,
};

/**--------------- Channel 1 Sensor 1 Measure ---------------------------*/
static const ADC_SignalConfig ADC_Current_V1Ch1_Intern_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 5110.0,
    .divider_R2 = 10000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 9,
};

/**--------------- Channel 1 Sensor 2 Measure ---------------------------*/
static const ADC_SignalConfig ADC_Current_V1Ch2_Intern_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 5110.0,
    .divider_R2 = 10000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 2,
};

/**--------------- Channel 2 Sensor 1 Measure ---------------------------*/
static const ADC_SignalConfig ADC_Current_V2Ch1_Intern_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 5110.0,
    .divider_R2 = 10000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 0,
};

/**--------------- Channel 2 Sensor 2 Measure ---------------------------*/
static const ADC_SignalConfig ADC_Current_V2Ch2_Intern_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 5110.0,
    .divider_R2 = 10000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 1,
};

/**--------------- V+ K1 Measure ---------------------------*/
static const ADC_SignalConfig ADC_Vp_K1_Measure_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 660000.0,
    .divider_R2 = 66000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 22,
};

/**--------------- V+ K2 Measure ---------------------------*/
static const ADC_SignalConfig ADC_Vp_K2_Measure_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 660000.0,
    .divider_R2 = 66000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 14,
};

/**--------------- V+ K3 Measure ---------------------------*/
static const ADC_SignalConfig ADC_Vp_K3_Measure_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 660000.0,
    .divider_R2 = 66000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 5,
};

/**--------------- 13V Measure ---------------------------*/
static const ADC_SignalConfig ADC_Terminal_30_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 660000.0,
    .divider_R2 = 66000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 8,
};

/**--------------- 5V Measure ---------------------------*/
static const ADC_SignalConfig ADC_5V_Measure_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 10000.0,
    .divider_R2 = 10000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 18,
};

/**--------------- 3V3 Measure ---------------------------*/
static const ADC_SignalConfig ADC_3V3_Measure_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 10000.0,
    .divider_R2 = 100000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 15,
};

/**--------------- Temp Main Measure ---------------------------*/
static const ADC_SignalConfig ADC_Temp_Sense_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 0.0,
    .divider_R2 = 1.0,
    .offset     = 500,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 7,
};

/**--------------- SBC MUX out Measure ---------------------------*/
static const ADC_SignalConfig ADC_VSense_Mux_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 0.0,
    .divider_R2 = 1.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 17,
};

/**--------------- AUX- K1 Sensor ---------------------------*/
static const ADC_SignalConfig ADC_AUXm_K1_Sensor_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 8200.0,
    .divider_R2 = 15000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 10,
};

/**--------------- AUX- K2 Sensor ---------------------------*/
static const ADC_SignalConfig ADC_AUXm_K2_Sensor_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 8200.0,
    .divider_R2 = 15000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 4,
};

/**--------------- AUX- K3 Sensor ---------------------------*/
static const ADC_SignalConfig ADC_AUXm_K3_Sensor_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_TMS570LS,
    .divider_R1 = 8200.0,
    .divider_R2 = 15000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .port       = ADC_PORTA,
    .group      = ADC_GROUP1,
    .channel    = 11,
};

/**--------------- HV Measure 1 ---------------------------*/
static const ADC_SignalConfig ADC_HV_Measure_1_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_ADS1118,
    .divider_R1 = 360000.0,
    .divider_R2 = 12400.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .channel    = 0,
};

/**--------------- HV Measure 2 ---------------------------*/
static const ADC_SignalConfig ADC_HV_Measure_2_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_ADS1118,
    .divider_R1 = 360000.0,
    .divider_R2 = 12400.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .channel    = 1,
};

/**--------------- HV Measure 3 ---------------------------*/
static const ADC_SignalConfig ADC_HV_Measure_3_Signal = {
    .deviceType = (uint8_t)ADC_DEVICE_ADS1118,
    .divider_R1 = 1120000.0,
    .divider_R2 = 36000.0,
    .offset     = 0,
    .unit       = PHYSICAL_UNIT_mV,
    .deviceNr   = 0,
    .channel    = 2,
};


const ADC_Signals adc_signals_HW1V0 = {
    .ADC_LSS_COC_K1_Measure   = &ADC_LSS_COC_K1_Measure_Signal,
    .ADC_LSS_COC_K2_Measure   = &ADC_LSS_COC_K2_Measure_Signal,
    .ADC_LSS_COC_K3_Measure   = &ADC_LSS_COC_K3_Measure_Signal,
    .ADC_Current_S1Ch1_Intern = &ADC_Current_V1Ch1_Intern_Signal,
    .ADC_Current_S1Ch2_Intern = &ADC_Current_V1Ch2_Intern_Signal,
    .ADC_Current_S2Ch1_Intern = &ADC_Current_V2Ch1_Intern_Signal,
    .ADC_Current_S2Ch2_Intern = &ADC_Current_V2Ch2_Intern_Signal,
    .ADC_Vp_K1_Measure        = &ADC_Vp_K1_Measure_Signal,
    .ADC_Vp_K2_Measure        = &ADC_Vp_K2_Measure_Signal,
    .ADC_Vp_K3_Measure        = &ADC_Vp_K3_Measure_Signal,
    .ADC_Terminal_30          = &ADC_Terminal_30_Signal,
    .ADC_5V_Measure           = &ADC_5V_Measure_Signal,
    .ADC_3V3_Measure          = &ADC_3V3_Measure_Signal,
    .ADC_Temp_Sense           = &ADC_Temp_Sense_Signal,
    .ADC_VSense_Mux           = &ADC_VSense_Mux_Signal,
    .ADC_AUXm_K1_Sensor       = &ADC_AUXm_K1_Sensor_Signal,
    .ADC_AUXm_K2_Sensor       = &ADC_AUXm_K2_Sensor_Signal,
    .ADC_AUXm_K3_Sensor       = &ADC_AUXm_K3_Sensor_Signal,
    .ADC_HV_Measure_1         = &ADC_HV_Measure_1_Signal,
    .ADC_HV_Measure_2         = &ADC_HV_Measure_2_Signal,
    .ADC_HV_Measure_3         = &ADC_HV_Measure_3_Signal,
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
