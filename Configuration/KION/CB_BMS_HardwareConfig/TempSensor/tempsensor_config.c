/**
 * @file     tempsensor_config.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 */

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "tempsensor.h"
#include "tempsensor_config.h"
#include "batteryModule_config.h"
#include "task_cfg.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/

/**
 * @brief defines the used temperature sensors in the system
 * @detail sensor configurations of sensors who aren't calculated with a table
 * must not include in this table
 */
const TempSensorTableConfig* const tempSensors[] = {
    &tempSensor_externalSensor,
    &tempSensor_balancingSensor,
#if defined(APPLICATION_TEMPSENSOR_USAGE) && APPLICATION_TEMPSENSOR_USAGE == ENABLED
    &tempSensor_applicationSensor,
#endif
};

const uint8_t tempSensorConfigLength = sizeof(tempSensors) / sizeof(TempSensorTableConfig*);

/**
 * @brief defines the serial resistors connected to temp sensors
 * @detail Needed to calculate a correct temperature value from the series connection
 */
MEM_SEC_PARAMETER uint32_t tempSensorSerialResistorValue[] = {
    EXTERNAL_TEMPSENSOR_SERIAL_RESISTOR_VALUE,   // external tempsensor serial resistor value
    BALANCING_TEMPSENSOR_SERIAL_RESISTOR_VALUE,  // balancing tempsensor serial resistor value
#if defined(APPLICATION_TEMPSENSOR_USAGE) && APPLICATION_TEMPSENSOR_USAGE == ENABLED
    APPLICATION_TEMPSENSOR_SERIAL_RESISTOR_VALUE  // application tempsensor serial resistor value
#endif
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
