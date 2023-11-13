/**
 * @file     adc_TMS570LS_config.c
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

#include "TMS570/adc_TMS570LS.h"
#include "adc_TMS570LS_config.h"
//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/

/**
 * @brief
 */
const ADC_DeviceConfig ADC_TMS570LS_DeviceConfig = {
    .nDevices   = 1,
    .nPorts     = ADC_TMS570LS_nPORTS,
    .nChannels  = ADC_TMS570LS_nChannels,
    .refVoltage = 3300.0,
    .maxVal     = 4096,
    .resolution = ADC_TMS570LS_RESOLUTION,
};

const ADC_TMS570LS_GroupConfig ADC_TMS570LS_Port1_EventGroup = {
    .triggerType            = HARDWARE_TRIGGER,  // EventGroup shall always be hardware triggered
    .triggerEdge            = HIGH_TO_LOW_EDGE,
    .triggerSource          = 0u,
    .fifoSize               = 1u,
    .storeChannelId         = false,
    .continuouslyConversion = false,
    .overwriteUnreadResults = true,
    .acquisitionTime        = 1,
};

const ADC_TMS570LS_GroupConfig ADC_TMS570LS_Port1_Group1 = {
    .triggerType            = SOFTWARE_TRIGGER,
    .triggerEdge            = HIGH_TO_LOW_EDGE,
    .triggerSource          = 0u,
    .fifoSize               = 16u,
    .storeChannelId         = false,
    .continuouslyConversion = false,
    .overwriteUnreadResults = false,
    .acquisitionTime        = 4,
};

const ADC_TMS570LS_GroupConfig ADC_TMS570LS_Port1_Group2 = {
    .triggerType            = HARDWARE_TRIGGER,
    .triggerEdge            = HIGH_TO_LOW_EDGE,
    .triggerSource          = 0u,
    .fifoSize               = 1u,
    .storeChannelId         = false,
    .continuouslyConversion = false,
    .overwriteUnreadResults = true,
    .acquisitionTime        = 1,
};

const ADC_TMS570LS_GroupConfig ADC_TMS570LS_Port2_EventGroup = {
    .triggerType            = HARDWARE_TRIGGER,  // EventGroup shall always be hardware triggered
    .triggerEdge            = HIGH_TO_LOW_EDGE,
    .triggerSource          = 0u,
    .fifoSize               = 1u,
    .storeChannelId         = false,
    .continuouslyConversion = false,
    .overwriteUnreadResults = true,
    .acquisitionTime        = 1,
};

const ADC_TMS570LS_GroupConfig ADC_TMS570LS_Port2_Group1 = {
    .triggerType            = SOFTWARE_TRIGGER,
    .triggerEdge            = HIGH_TO_LOW_EDGE,
    .triggerSource          = 0u,
    .fifoSize               = 16u,
    .storeChannelId         = false,
    .continuouslyConversion = false,
    .overwriteUnreadResults = false,
    .acquisitionTime        = 1,
};

const ADC_TMS570LS_GroupConfig ADC_TMS570LS_Port2_Group2 = {
    .triggerType            = SOFTWARE_TRIGGER,
    .triggerEdge            = HIGH_TO_LOW_EDGE,
    .triggerSource          = 0u,
    .fifoSize               = 1u,
    .storeChannelId         = false,
    .continuouslyConversion = false,
    .overwriteUnreadResults = false,
    .acquisitionTime        = 1,
};

const ADC_TMS570LS_GroupConfig* const ADC_TMS570_Ports[ADC_TMS570LS_nPORTS][ADC_TMS570LS_nGroups] = {
    { &ADC_TMS570LS_Port1_EventGroup,
      &ADC_TMS570LS_Port1_Group1,
      &ADC_TMS570LS_Port1_Group2 },
    { &ADC_TMS570LS_Port2_EventGroup,
      &ADC_TMS570LS_Port2_Group1,
      &ADC_TMS570LS_Port2_Group2 }
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
