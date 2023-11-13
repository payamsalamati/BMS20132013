/**
 * @file highVoltageMonitor.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Checks the high voltage against the error limits.
 * @details
 *   Interfaces to other modules:
 *   - measurements
 *   - highVoltageMeasurement
 *   - idAllocation
 *   - subMasterInfoSend
 *   - errorDetection
 *   - dem
 *  <b>Global variables</b>
 *  MEM_SEC_PARAMETER HvVoltageMonitorConfig hvVoltageMonitorConfigParameter (required for post build configuration)
 *  For a more detailed description refer to the mainFunciton documentation.
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
    int32_t hvVoltageDifferenceMaxDetectVal;
    int32_t hvVoltageDifferenceMaxReleaseVal;
} HvVoltageMonitorConfig;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

/**
 * @brief Main function of the module.
 * @details This function checks the high voltage against the error limits.
 *          Only when the minus and the plus or precharge relay are closed, the voltage can be measured. Only in that case the error can be detected.
 *          Otherwise, when the relays are open, the error detection should reset.
 * ##Requirements:
 * **Requirement**    |**Description**
 * :-----------------:|:-----------------
 * **HVM_00010**      |The function shall get the master ID by calling the function idAllocation_getMasterId.
 * **HVM_00011**      |The function shall get the master voltage value by calling the function
 *      ^             |submasterVoltageMeasurement_getValue.
 * **HVM_00012**      |The function shall get the master hv voltage value by calling the function
 *      ^             |highVoltageMeasurement_getMasterHvVoltagesValue with the configuration variable HVVoltageVehicle.
 * **HVM_00013**      |If the function subMasterInfoSend_getRelay with the configuration variable RELAI_MINUS is true
 *      ^             |and subMasterInfoSend_getRelay with either the configuration variable RELAI_PLUS or RELAI_PRECHARGE is true,
 *      ^             |call the function errorDetection with the configuration hvVoltageVehicleError, the absolute value of the difference between
 *      ^             |the master voltage value and the master hv voltage value, and the configuration variable MONITORING_CYCLE_TIME.
 */
void highVoltageMonitor_mainFunction(void);
