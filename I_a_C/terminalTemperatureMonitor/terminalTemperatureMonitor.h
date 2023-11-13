/**
 * @file terminalTemperatureMonitor.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef struct
{
    int32_t terminalTemperaturePlusThreshold1;
    int32_t terminalTemperaturePlusThreshold2;
    int32_t terminalTemperatureNegativeThreshold1;
    int32_t terminalTemperatureNegativeThreshold2;
} TerminalTemperatureMonitorConfig;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void terminalTemperatureMonitor_mainFunction(void);
