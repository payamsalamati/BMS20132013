/**
 * @file ioIf_signals.c
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

#include "hwversion_config.h"
#include "ioIf.h"
#include "ioIf_signals.h"

#include "pwmRelaisIf_config.h"
#include "pwmRelaisIf.h"

#include "adcIf.h"
#include "adc_signal_config.h"
//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/
#if USE_FIX_HARDWARE_CONFIGURATION == CONFIG_ENABLED

#if(USED_HARDWARE_VERSION == HARDWAREVERSION_1v0) || (USED_HARDWARE_VERSION == HARDWAREVERSION_1v3) || (USED_HARDWARE_VERSION == HARDWAREVERSION_1v4) || (USED_HARDWARE_VERSION == HARDWAREVERSION_1v5)

extern const IO_Signals IO_SIGNAL_CONFIG_HW_1V0;
const IO_Signals* const ioSignals               = &IO_SIGNAL_CONFIG_HW_1V0;
const IO_SignalConfig* const ioSignalConfigList = (const IO_SignalConfig*)&IO_SIGNAL_CONFIG_HW_1V0;
const uint16_t ioSignalConfigListSize           = sizeof(IO_SIGNAL_CONFIG_HW_1V0) / sizeof(IO_SignalConfig*);

extern const ADC_Signals* adcSignals;
#else

#error no valid hardware configuration for IO signal configuration

#endif
#else
const IO_Signals* ioSignals;
const IO_SignalConfig* const* ioSignalConfigList;

#endif
//***************************************************************************/
//************************** PRIVATE FUNCTION DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DEFINITIONS *******************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DEFINITIONS * ******************/
//***************************************************************************/


//***************************************************************************/
//************************** OUTPUTS ****************************************/
//***************************************************************************/
IO_Status io_setEeprom_nHoldEnable(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_EEPROM_HoldEnable, state);
}

IO_Status io_setEeprom_nWriteProtect(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_EEPROM_WriteProtect, state);
}

IO_Status io_setICDCurrentSensorSupplyEnable(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_VSUP_ICD_Enable, state);
}

IO_Status io_setContactorControl1(IO_VAL_t state)
{
#if defined(PWM_RELAIS_CONTROL_GLOBAL) && PWM_RELAIS_CONTROL_GLOBAL == CONFIG_ENABLED
    return (pwmRelaisIf_setRelaisStatus(0u, state) == PWM_STATUS_SUCCESS) ? IO_SUCCESS : IO_INVALID_LOGIC;
#else
    return IO_FAILURE;
#endif
}

IO_Status io_setContactorControl2(IO_VAL_t state)
{
#if defined(PWM_RELAIS_CONTROL_GLOBAL) && PWM_RELAIS_CONTROL_GLOBAL == CONFIG_ENABLED
    return (pwmRelaisIf_setRelaisStatus(1u, state) == PWM_STATUS_SUCCESS) ? IO_SUCCESS : IO_INVALID_LOGIC;
#else
    return IO_FAILURE;
#endif
}

IO_Status io_setContactorControl3(IO_VAL_t state)
{
#if defined(PWM_RELAIS_CONTROL_GLOBAL) && PWM_RELAIS_CONTROL_GLOBAL == CONFIG_ENABLED
    return (pwmRelaisIf_setRelaisStatus(2u, state) == PWM_STATUS_SUCCESS) ? IO_SUCCESS : IO_INVALID_LOGIC;
#else
    return IO_FAILURE;
#endif
}

IO_Status io_set13VBatEnable(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_13V_BAT_Enable, state);
}

IO_Status io_setLatchEnable(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_LATCH_Enable, state);
}

IO_Status io_setBcmEnable(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_BCM_Enable, state);
}

IO_Status io_setBcmPrechargeControl(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_BCM_PRECHARGE_CONTROL, state);
}

IO_Status io_setBcmWakeUp(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_BCM_WAKE_UP, state);
}

IO_Status io_setDssWakeUp(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_DSS_WU, state);
}

IO_Status io_setCpsEnableWakeUp(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_CPS_Enable_WU, state);
}

IO_Status io_setCan1WakeUp(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_CAN1_WU, state);
}

IO_Status io_setSlaveEnable(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_Slave_Enable, state);
}

IO_Status io_setLED1(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_LED_1, state);
}

IO_Status io_setLED2(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_LED_2, state);
}

IO_Status io_setLED3(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_LED_3, state);
}

IO_Status io_setExt_Output_1(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_Ext_Output_1, state);
}

IO_Status io_setExt_Output_2(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_Ext_Output_2, state);
}

IO_Status io_setExt_Output_3(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_Ext_Output_3, state);
}

IO_Status io_setExt_Output_4(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_Ext_Output_4, state);
}

IO_Status io_setContactorFaultline1(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_HSS_K1_Enable, state);
}

IO_Status io_setContactorFaultline2(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_HSS_K2_Enable, state);
}

IO_Status io_setContactorFaultline3(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_HSS_K3_Enable, state);
}

IO_Status io_setContactorReset1(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_LSS_COC_K1_Reset, state);
}

IO_Status io_setContactorReset2(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_LSS_COC_K2_Reset, state);
}

IO_Status io_setContactorReset3(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_LSS_COC_K3_Reset, state);
}

IO_Status io_setSPI_AFE_Wakeup(IO_VAL_t state)
{
    return ioIf_setPinState(ioSignals->IO_SIGNALS_AFE_Wakeup, state);
}

//***************************************************************************/
//************************** INPUTS  ****************************************/
//***************************************************************************/
IO_Status io_getHighsideSwitchStatus1(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_HSS_K1_Status, state);
}

IO_Status io_getHighsideSwitchStatus2(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_HSS_K2_Status, state);
}

IO_Status io_getHighsideSwitchStatus3(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_HSS_K3_Status, state);
}

IO_Status io_getContactorAlarm1(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_LSS_COC_K1_Alert, state);
}

IO_Status io_getContactorAlarm2(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_LSS_COC_K2_Alert, state);
}

IO_Status io_getContactorAlarm3(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_LSS_COC_K3_Alert, state);
}

IO_Status io_getExt_Input_1(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_Ext_Input_1, state);
}

IO_Status io_getExt_Input_2(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_Ext_Input_2, state);
}

IO_Status io_getExt_Input_3(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_Ext_Input_3, state);
}

IO_Status io_getExt_Input_4(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_Ext_Input_4, state);
}

IO_Status io_getBCM_nReady(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_BCM_nREADY, state);
}

IO_Status io_getCpsSensWakeUp(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_CPS_SENS_WU, state);
}

IO_Status io_getButtonSensWakeUp(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_BUTTON_SENS_WU, state);
}

IO_Status io_getSBC_Fault(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_SBC_Fault, state);
}

IO_Status io_getIsoOk(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_ISO_OK, state);
}

IO_Status io_getSlaveInterrupt(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_Slave_Interrupt, state);
}

IO_Status io_getRelayAux_1(IO_VAL_t* state)
{
    return adcIf_getAnalogIoState(adcSignals->ADC_AUXm_K1_Sensor, IO_NON_INVERTED_LOGIC, state);
}

IO_Status io_getRelayAux_2(IO_VAL_t* state)
{
    return adcIf_getAnalogIoState(adcSignals->ADC_AUXm_K2_Sensor, IO_NON_INVERTED_LOGIC, state);
}

IO_Status io_getRelayAux_3(IO_VAL_t* state)
{
    return adcIf_getAnalogIoState(adcSignals->ADC_AUXm_K3_Sensor, IO_NON_INVERTED_LOGIC, state);
}

//***************************************************************************/
//**********************IO STATUS_OF_OUTPUT     *****************************/
//***************************************************************************/

IO_Status io_getStatusEeprom_nHoldEnable(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_EEPROM_HoldEnable, state);
}
IO_Status io_getStatusEeprom_nWriteProtect(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_EEPROM_WriteProtect, state);
}
IO_Status io_getStatusICDCurrentSensorSupplyEnable(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_VSUP_ICD_Enable, state);
}
IO_Status io_getStatus13VBatEnable(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_13V_BAT_Enable, state);
}
IO_Status io_geStatustLatchEnable(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_LATCH_Enable, state);
}
IO_Status io_getStatusBcmEnable(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_BCM_Enable, state);
}
IO_Status io_getStatusBcmPrechargeControl(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_BCM_PRECHARGE_CONTROL, state);
}
IO_Status io_getStatusBcmWakeUp(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_BCM_WAKE_UP, state);
}
IO_Status io_getStatusDssWakeUp(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_DSS_WU, state);
}
IO_Status io_getStatusCpsEnableWakeUp(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_CPS_Enable_WU, state);
}
IO_Status io_getStatusCan1WakeUp(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_CAN1_WU, state);
}
IO_Status io_getStatusSlaveEnable(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_Slave_Enable, state);
}
IO_Status io_getStatusLED1(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_LED_1, state);
}
IO_Status io_getStatusLED2(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_LED_2, state);
}
IO_Status io_getStatusLED3(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_LED_3, state);
}
IO_Status io_getStatusExt_Output_1(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_Ext_Output_1, state);
}
IO_Status io_getStatusExt_Output_2(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_Ext_Output_2, state);
}
IO_Status io_getStatusExt_Output_3(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_Ext_Output_3, state);
}
IO_Status io_getStatusExt_Output_4(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_Ext_Output_4, state);
}
IO_Status io_getStatusContactorFaultline1(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_HSS_K1_Enable, state);
}
IO_Status io_getStatusContactorFaultline2(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_HSS_K2_Enable, state);
}
IO_Status io_getStatusContactorFaultline3(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_HSS_K3_Enable, state);
}
IO_Status io_getStatusContactorReset1(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_LSS_COC_K1_Reset, state);
}
IO_Status io_getStatusContactorReset2(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_LSS_COC_K2_Reset, state);
}
IO_Status io_getStatusContactorReset3(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_LSS_COC_K3_Reset, state);
}
IO_Status io_getStatusSPI_AFE_Wakeup(IO_VAL_t* state)
{
    return ioIf_getPinState(ioSignals->IO_SIGNALS_AFE_Wakeup, state);
}
IO_Status io_getStatusContactorControl1(IO_VAL_t* state)
{
    *state = pwmRelaisIf_getRelaisStatus(0) ? IO_HIGH_STATE : IO_LOW_STATE;
    return IO_SUCCESS;
}
IO_Status io_getStatusContactorControl2(IO_VAL_t* state)
{
    *state = pwmRelaisIf_getRelaisStatus(1) ? IO_HIGH_STATE : IO_LOW_STATE;
    return IO_SUCCESS;
}
IO_Status io_getStatusContactorControl3(IO_VAL_t* state)
{
    *state = pwmRelaisIf_getRelaisStatus(2) ? IO_HIGH_STATE : IO_LOW_STATE;
    return IO_SUCCESS;
}
