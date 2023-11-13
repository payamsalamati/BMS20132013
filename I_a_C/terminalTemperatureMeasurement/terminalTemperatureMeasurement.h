/**
 * @file terminalTemperatureMeasurement.h
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

typedef enum
{
    TERMINAL_TEMP_SENSOR_1 = 0,
    TERMINAL_TEMP_SENSOR_2 = 1,
} TERMINAL_TEMP_SENSOR;

typedef struct
{
    TERMINAL_TEMP_SENSOR minusTerminal;
    TERMINAL_TEMP_SENSOR plusTerminal;
} TerminalTempenSorConfig;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
/**
 * @brief Main function of the module.
 * @details This function copies all terminal temperatures from the safety layer and calculates the maximum and average master terminal temperature.
 */
void terminalTemperatureMeasurement_mainFunction(void);

/**
 * @brief Getter for terminal temperatures array by indices.
 * @param slave index of slave
 * @param sensor index of sensor
 * @return int16_t terminalTemperatureMeasurement.values[i][j]
 * @details This function returns the temperatures by indices.
 */
int16_t terminalTemperatureMeasurement_getValue(uint16_t slave, uint16_t sensor);

/**
 * @brief Getter for terminalTemperatureMeasurement.maxMin.max.
 * @return int16_t terminalTemperatureMeasurement.maxMin.max
 * @details This function returns the terminalTemperatureMeasurement.maxMin.max.
 */
int16_t terminalTemperatureMeasurement_getMaxValue(void);

/**
 * @brief Getter for terminalTemperatureMeasurement.maxMin.min.
 * @return int16_t terminalTemperatureMeasurement.maxMin.min
 * @details This function returns the terminalTemperatureMeasurement.maxMin.min.
 */
int16_t terminalTemperatureMeasurement_getMinValue(void);

/**
 * @brief Getter for terminalTemperatureMeasurement.maxMinCsc[cscAddress].max.
 * @return int16_t terminalTemperatureMeasurement.maxMinCsc[cscAddress].max
 * @details This function returns the terminalTemperatureMeasurement.maxMinCsc[cscAddress].max.
 */
int16_t terminalTemperatureMeasurement_getMaxValueCSC(uint16_t cscAddress);

/**
 * @brief Getter for terminalTemperatureMeasurement.maxMinCsc[cscAddress].min.
 * @return int16_t terminalTemperatureMeasurement.maxMinCsc[cscAddress].min
 * @details This function returns the terminalTemperatureMeasurement.maxMinCsc[cscAddress].min.
 */
int16_t terminalTemperatureMeasurement_getMinValueCSC(uint16_t cscAddress);

/**
 * @brief Getter for terminalTemperatureMeasurement.average.
 * @param i index of master
 * @return int16_t terminalTemperatureMeasurement.average
 * @details This function returns the terminalTemperatureMeasurement.average.
 */
int16_t terminalTemperatureMeasurement_getAverageValue(void);

/**
 * @brief Getter for terminalTemperatureMeasurement.maxIndex1.
 * @return uint8_t terminalTemperatureMeasurement.maxIndex1
 */
uint8_t terminalTemperatureMeasurement_getTemperatureSensorAddressOfMax(void);

/**
 * @brief Getter for terminalTemperatureMeasurement.minIndex1.
 * @return uint8_t terminalTemperatureMeasurement.minIndex1
 */
uint8_t terminalTemperatureMeasurement_getTemperatureSensorAddressOfMin(void);

/**
 * @brief Getter for terminalTemperatureMeasurement.maxMin.maxIndex2.
 * @return uint8_t terminalTemperatureMeasurement.maxMin.maxIndex2
 */
uint8_t terminalTemperatureMeasurement_getMaxNumber(void);

/**
 * @brief Getter for terminalTemperatureMeasurement.maxMin.minIndex2.
 * @return uint8_t terminalTemperatureMeasurement.maxMin.minIndex2
 */
uint8_t terminalTemperatureMeasurement_getMinNumber(void);

/**
 * @brief Getter for terminalTemperatureMeasurement.maxMinCsc[cscAddress].max.
 * @return int16_t terminalemperatureMeasurement.maxMinCsc[cscAddress].max
 */
int16_t terminalTemperatureMeasurement_getMaxValueCSC(uint16_t cscAddress);

/**
 * @brief Getter for terminalTemperatureMeasurement.maxMinCsc[cscAddress].min.
 * @return int16_t terminalTemperatureMeasurement.maxMinCsc[cscAddress].min
 */
int16_t terminalTemperatureMeasurement_getMinValueCSC(uint16_t cscAddress);

/**
 * @brief Getter for temperature at the plus terminal for a given cscAddress
 * @return int16_t plus terminal temperature at cscAddress
 */
int16_t terminalTemperatureMeasurement_getPlusTerminalTemperature(uint16_t cscAddress);

/**
 * @brief Getter for temperature at the minus terminal for a given cscAddress
 * @return int16_t minus terminal temperature at cscAddress
 */
int16_t terminalTemperatureMeasurement_getMinusTerminalTemperature(uint16_t cscAddress);

/**
 * @brief Getter for temperatures for a given cscAddress
 * @return const int16_t*
 */
const int16_t* terminalTemperatureMeasurement_getTerminalTemperatures(uint16_t cscAddress);

/**
 * @brief Setter for which sensor is configured to be the minus terminal
 */
void terminalTemperatureMeasurement_setMinusTerminal(TERMINAL_TEMP_SENSOR sensor);

/**
 * @brief Setter for which sensor is configured to be the plus terminal
 */
void terminalTemperatureMeasurement_setPlusTerminal(TERMINAL_TEMP_SENSOR sensor);

/**
 * @brief Getter for sensor at minus terminal
 * @return TERMINAL_TEMP_SENSOR minus terminal sensor
 */
TERMINAL_TEMP_SENSOR terminalTemperatureMeasurement_getMinusTerminal(void);

/**
 * @brief Getter for sensor at plus terminal
 * @return TERMINAL_TEMP_SENSOR plus terminal sensor
 */
TERMINAL_TEMP_SENSOR terminalTemperatureMeasurement_getPlusTerminal(void);

/**
 * @brief Getter for masked temperature at given cscAddress and sensor
 * @return maskedTerminalTemperatureValues[cscAddress][sensor]
 */
int16_t terminalTemperatureMeasurement_getMaskedValue(uint16_t cscAddress, uint16_t sensor);
