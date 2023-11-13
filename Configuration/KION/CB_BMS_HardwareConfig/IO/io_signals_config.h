/**
 * @file     io_signals_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 *	 -
 */

#pragma once

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "ioIf.h"
#include "hwVersionIf.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/
typedef struct
{
    /************ OUTPUTS ************/
    const IO_SignalConfig* IO_SIGNALS_EEPROM_HoldEnable;
    const IO_SignalConfig* IO_SIGNALS_EEPROM_WriteProtect;
    const IO_SignalConfig* IO_SIGNALS_VSUP_ICD_Enable;
    const IO_SignalConfig* IO_SIGNALS_13V_BAT_Enable;
    const IO_SignalConfig* IO_SIGNALS_LATCH_Enable;
    const IO_SignalConfig* IO_SIGNALS_BCM_Enable;
    const IO_SignalConfig* IO_SIGNALS_BCM_PRECHARGE_CONTROL;
    const IO_SignalConfig* IO_SIGNALS_BCM_WAKE_UP;
    const IO_SignalConfig* IO_SIGNALS_DSS_WU;
    const IO_SignalConfig* IO_SIGNALS_CPS_Enable_WU;
    const IO_SignalConfig* IO_SIGNALS_CAN1_WU;
    const IO_SignalConfig* IO_SIGNALS_Slave_Enable;
    const IO_SignalConfig* IO_SIGNALS_LED_1;
    const IO_SignalConfig* IO_SIGNALS_LED_2;
    const IO_SignalConfig* IO_SIGNALS_LED_3;
    const IO_SignalConfig* IO_SIGNALS_Ext_Output_1;
    const IO_SignalConfig* IO_SIGNALS_Ext_Output_2;
    const IO_SignalConfig* IO_SIGNALS_Ext_Output_3;
    const IO_SignalConfig* IO_SIGNALS_Ext_Output_4;
    const IO_SignalConfig* IO_SIGNALS_HSS_K1_Enable;
    const IO_SignalConfig* IO_SIGNALS_HSS_K2_Enable;
    const IO_SignalConfig* IO_SIGNALS_HSS_K3_Enable;
    const IO_SignalConfig* IO_SIGNALS_LSS_COC_K1_Reset;
    const IO_SignalConfig* IO_SIGNALS_LSS_COC_K2_Reset;
    const IO_SignalConfig* IO_SIGNALS_LSS_COC_K3_Reset;
    const IO_SignalConfig* IO_SIGNALS_AFE_Wakeup;

    /************ INPUTS ************/
    const IO_SignalConfig* IO_SIGNALS_HSS_K1_Status;
    const IO_SignalConfig* IO_SIGNALS_HSS_K2_Status;
    const IO_SignalConfig* IO_SIGNALS_HSS_K3_Status;
    const IO_SignalConfig* IO_SIGNALS_LSS_COC_K1_Alert;
    const IO_SignalConfig* IO_SIGNALS_LSS_COC_K2_Alert;
    const IO_SignalConfig* IO_SIGNALS_LSS_COC_K3_Alert;
    const IO_SignalConfig* IO_SIGNALS_Ext_Input_1;
    const IO_SignalConfig* IO_SIGNALS_Ext_Input_2;
    const IO_SignalConfig* IO_SIGNALS_Ext_Input_3;
    const IO_SignalConfig* IO_SIGNALS_Ext_Input_4;
    const IO_SignalConfig* IO_SIGNALS_BCM_nREADY;
    const IO_SignalConfig* IO_SIGNALS_CPS_SENS_WU;
    const IO_SignalConfig* IO_SIGNALS_BUTTON_SENS_WU;
    const IO_SignalConfig* IO_SIGNALS_SBC_Fault;
    const IO_SignalConfig* IO_SIGNALS_ISO_OK;
    const IO_SignalConfig* IO_SIGNALS_Slave_Interrupt;
} IO_Signals;
//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DEFINITIONS *******************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DEFINITIONS ********************/
//***************************************************************************/
const IO_Signals* io_getIoHardwareConfig(HWVERSION_STATUS hwVersion);
uint8_t io_getIoSignalListSize(HWVERSION_STATUS hwVersion);
