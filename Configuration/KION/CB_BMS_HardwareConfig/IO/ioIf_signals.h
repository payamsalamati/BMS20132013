/**
 * @file     ioIf_signals.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

#pragma once

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "ioIf.h"
#include "hwVersionIf.h"
#include "io_signals_config.h"
//***************************************************************************/
//************************** PUBLIC TYPEDEFS ********************************/
//***************************************************************************/

//***************************************************************************/
//************************** PUBLIC VARIABLE DEFINITIONS ********************/
//***************************************************************************/

//***************************************************************************/
//************************** PUBLIC FUNCTION DECLARATIONS *******************/
//***************************************************************************/
IO_Status io_setEeprom_nHoldEnable(IO_VAL_t state);
IO_Status io_setEeprom_nWriteProtect(IO_VAL_t state);
IO_Status io_setICDCurrentSensorSupplyEnable(IO_VAL_t state);
IO_Status io_set13VBatEnable(IO_VAL_t state);
IO_Status io_setLatchEnable(IO_VAL_t state);
IO_Status io_setBcmEnable(IO_VAL_t state);
IO_Status io_setBcmPrechargeControl(IO_VAL_t state);
IO_Status io_setBcmWakeUp(IO_VAL_t state);
IO_Status io_setDssWakeUp(IO_VAL_t state);
IO_Status io_setCpsEnableWakeUp(IO_VAL_t state);
IO_Status io_setCan1WakeUp(IO_VAL_t state);
IO_Status io_setSlaveEnable(IO_VAL_t state);
IO_Status io_setLED1(IO_VAL_t state);
IO_Status io_setLED2(IO_VAL_t state);
IO_Status io_setLED3(IO_VAL_t state);
IO_Status io_setExt_Output_1(IO_VAL_t state);
IO_Status io_setExt_Output_2(IO_VAL_t state);
IO_Status io_setExt_Output_3(IO_VAL_t state);
IO_Status io_setExt_Output_4(IO_VAL_t state);
IO_Status io_setContactorFaultline1(IO_VAL_t state);
IO_Status io_setContactorFaultline2(IO_VAL_t state);
IO_Status io_setContactorFaultline3(IO_VAL_t state);
IO_Status io_setContactorReset1(IO_VAL_t state);
IO_Status io_setContactorReset2(IO_VAL_t state);
IO_Status io_setContactorReset3(IO_VAL_t state);
IO_Status io_setSPI_AFE_Wakeup(IO_VAL_t state);
IO_Status io_setContactorControl1(IO_VAL_t state);
IO_Status io_setContactorControl2(IO_VAL_t state);
IO_Status io_setContactorControl3(IO_VAL_t state);
//***************************************************************************/
//************************** INPUTS  ****************************************/
//***************************************************************************/
IO_Status io_getHighsideSwitchStatus1(IO_VAL_t* state);
IO_Status io_getHighsideSwitchStatus2(IO_VAL_t* state);
IO_Status io_getHighsideSwitchStatus3(IO_VAL_t* state);
IO_Status io_getContactorAlarm1(IO_VAL_t* state);
IO_Status io_getContactorAlarm2(IO_VAL_t* state);
IO_Status io_getContactorAlarm3(IO_VAL_t* state);
IO_Status io_getExt_Input_1(IO_VAL_t* state);
IO_Status io_getExt_Input_2(IO_VAL_t* state);
IO_Status io_getExt_Input_3(IO_VAL_t* state);
IO_Status io_getExt_Input_4(IO_VAL_t* state);
IO_Status io_getBCM_nReady(IO_VAL_t* state);
IO_Status io_getCpsSensWakeUp(IO_VAL_t* state);
IO_Status io_getButtonSensWakeUp(IO_VAL_t* state);
IO_Status io_getSBC_Fault(IO_VAL_t* state);
IO_Status io_getIsoOk(IO_VAL_t* state);
IO_Status io_getSlaveInterrupt(IO_VAL_t* state);
IO_Status io_getRelayAux_1(IO_VAL_t* state);
IO_Status io_getRelayAux_2(IO_VAL_t* state);
IO_Status io_getRelayAux_3(IO_VAL_t* state);

//***************************************************************************/
//********************** IO Status of Outputs *******************************/
//***************************************************************************/
IO_Status io_getStatusEeprom_nHoldEnable(IO_VAL_t* state);
IO_Status io_getStatusEeprom_nWriteProtect(IO_VAL_t* state);
IO_Status io_getStatusICDCurrentSensorSupplyEnable(IO_VAL_t* state);
IO_Status io_getStatus13VBatEnable(IO_VAL_t* state);
IO_Status io_geStatustLatchEnable(IO_VAL_t* state);
IO_Status io_getStatusBcmEnable(IO_VAL_t* state);
IO_Status io_getStatusBcmPrechargeControl(IO_VAL_t* state);
IO_Status io_getStatusBcmWakeUp(IO_VAL_t* state);
IO_Status io_getStatusDssWakeUp(IO_VAL_t* state);
IO_Status io_getStatusCpsEnableWakeUp(IO_VAL_t* state);
IO_Status io_getStatusCan1WakeUp(IO_VAL_t* state);
IO_Status io_getStatusSlaveEnable(IO_VAL_t* state);
IO_Status io_getStatusLED1(IO_VAL_t* state);
IO_Status io_getStatusLED2(IO_VAL_t* state);
IO_Status io_getStatusLED3(IO_VAL_t* state);
IO_Status io_getStatusExt_Output_1(IO_VAL_t* state);
IO_Status io_getStatusExt_Output_2(IO_VAL_t* state);
IO_Status io_getStatusExt_Output_3(IO_VAL_t* state);
IO_Status io_getStatusExt_Output_4(IO_VAL_t* state);
IO_Status io_getStatusContactorFaultline1(IO_VAL_t* state);
IO_Status io_getStatusContactorFaultline2(IO_VAL_t* state);
IO_Status io_getStatusContactorFaultline3(IO_VAL_t* state);
IO_Status io_getStatusContactorReset1(IO_VAL_t* state);
IO_Status io_getStatusContactorReset2(IO_VAL_t* state);
IO_Status io_getStatusContactorReset3(IO_VAL_t* state);
IO_Status io_getStatusSPI_AFE_Wakeup(IO_VAL_t* state);
IO_Status io_getStatusContactorControl1(IO_VAL_t* state);
IO_Status io_getStatusContactorControl2(IO_VAL_t* state);
IO_Status io_getStatusContactorControl3(IO_VAL_t* state);
