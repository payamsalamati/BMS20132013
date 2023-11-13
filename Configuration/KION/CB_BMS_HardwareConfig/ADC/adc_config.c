/**
 * @file     adc_config.c
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

#include "adc_ADS1118.h"
#include "adc_TMS570LS.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/

// Has to be in same order as ADC_Device
const ADCType* const adcTypes[] = {
    &adc_TMS570LS,
    &adc_ADS1118,
};

const uint8_t ADC_TYPES_LENGTH = sizeof(adcTypes) / sizeof(ADCType*);

// Has to be in same order as ADC_Device
const ADC_DeviceConfig* const adcDeviceConfigs[] = {
    &ADC_TMS570LS_DeviceConfig,
    &ADC_ADS1118_DeviceConfig.config,
};

const uint8_t ADC_DEVICE_CONFIGS_LENGTH = sizeof(adcDeviceConfigs) / sizeof(ADC_DeviceConfig*);

//***************************************************************************/
//************************** PRIVATE FUNCTION DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DEFINITIONS *******************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DEFINITIONS * ******************/
//***************************************************************************/
