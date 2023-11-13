/**
 * @file batteryModule_config.h
 * @copyright Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "tempsensor.h"
#include "config_enable.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//
#if defined(KGRT)
#define APPLICATION_TEMPSENSOR_USAGE CONFIG_ENABLED

extern const TempSensorTableConfig TempSensor_TA4_TEK_170330_850;
extern const TempSensorTableConfig TempSensor_NCU18XH103J6SRB;

#define tempSensor_externalSensor  TempSensor_TA4_TEK_170330_850
#define tempSensor_balancingSensor TempSensor_NCU18XH103J6SRB
#if defined(APPLICATION_TEMPSENSOR_USAGE) && APPLICATION_TEMPSENSOR_USAGE == CONFIG_ENABLED
#define tempSensor_applicationSensor TempSensor_NCU18XH103J6SRB  //if enabled, the corresponding sensor configuration must be inserted here
#endif


#else
#define APPLICATION_TEMPSENSOR_USAGE CONFIG_ENABLED
extern const TempSensorTableConfig TempSensor_NCP18XH103F03RB;

#define tempSensor_externalSensor  TempSensor_NCP18XH103F03RB
#define tempSensor_balancingSensor TempSensor_NCP18XH103F03RB
#if defined(APPLICATION_TEMPSENSOR_USAGE) && APPLICATION_TEMPSENSOR_USAGE == CONFIG_ENABLED
#define tempSensor_applicationSensor TempSensor_NCP18XH103F03RB  // if enabled, the corresponding sensor configuration must be inserted here
#endif
#endif

#define EXTERNAL_TEMPSENSOR_SERIAL_RESISTOR_VALUE    6800u
#define BALANCING_TEMPSENSOR_SERIAL_RESISTOR_VALUE   6800u
#define APPLICATION_TEMPSENSOR_SERIAL_RESISTOR_VALUE 6800u
