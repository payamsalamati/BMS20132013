/**
 * @file     measurements_getAfeValues_config_KION.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Configuration for measurements submodule getBatteryCurrent
 * @details
 *	 Interfaces to other modules:

 */

#pragma once


#include "adcIf_signals.h"

//***************************************************************************/
//**************************** DEFINES **************************************/
//***************************************************************************/

#define measurements_getAdcValuePP(X) adc_getPPVoltage(X)

#define measurements_getAdcValueTerminal30(X) adc_getBoardVoltageKl30(X)
