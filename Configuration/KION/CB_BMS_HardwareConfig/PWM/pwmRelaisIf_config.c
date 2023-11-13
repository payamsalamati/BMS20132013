/**
 * @file     pwmRelaisIf_config.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * This configuration is measured values from a GV352RPB to a WHBMS 3V11 master.
 * The dependence of the duty cycle on the module voltage was shown.
 *
 */

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "pwmRelaisIf.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/

//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/

/**
 * @brief Set configuration of pwm duty cycle for  hold phase and pickup phase
 * according to stack voltage for GV352RPB (measured values)
 *
 * duty Cycle values in %
 * start value = 11 V
 * final value = 35 V
 */
const PWMDutyCycleParameters GV352_ModuleVoltageControlTable[] = {
    { 24, 99 },  // 11V
    { 22, 99 },  // 12V
    { 20, 97 },  // 13V
    { 19, 86 },  // 14V
    { 17, 82 },  // 15V
};
const uint8_t GV352_TABLE_SIZE = (sizeof(GV352_ModuleVoltageControlTable) / sizeof(PWMDutyCycleParameters));

const PWMRelayControlConfig pwmControl_VoltageControlConfig = {
    .minVoltage          = 11,   // V
    .maxVoltage          = 15,   // V
    .pickupPhaseDuration = 100,  // ms
    .dutyCycleTable      = GV352_ModuleVoltageControlTable,
    .tableSize           = &GV352_TABLE_SIZE,
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
