

/**
 * @file periodicWakeUp.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  This module calculates new values for the next sleep time interval.
 *  The counter of the periodic wake up intervals is stored in nvm.
 *
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
    uint32_t maxNumberOfFastWakeUps;
    int8_t temperatureThreshold;
    uint32_t shortInterval;
    uint32_t middleInterval;
    uint32_t longInterval;
} PeriodicWakeUpConfig;


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void periodicWakeUp_init(void);

/**
 * @brief Increment periodic wake up counter and calculate next sleep time interval.
 * @details
 * ## Requirements:
 * **Requirement**  |**Description**
 * :---------------:|:--------------
 * **PwuM_00001**   |The counter will be incremented by 1 and next sleep time will be calculated
 *
 */
void periodicWakeUp_incrementWakeUpCounter(void);

/**
 * @brief Reset periodic wake up counter and calculate next sleep time interval.
 * @details
 * ## Requirements:
 * **Requirement**  |**Description**
 * :---------------:|:--------------
 * **PwuM_00002**   |The counter will be setted to 0 and next sleep time will be calculated
 *
 */
void periodicWakeUp_resetWakeUpCounter(void);

/**
 * @brief get function for next sleep time in sec.
 *
 * @return uint32_t next sleep time
 */
uint32_t periodicWakeUp_getTimeToWakeUp(void);

/**
 * @brief Check nvm data and store wake up counter.
 * @details
 * ## Requirements:
 * **Requirement**  |**Description**
 * :---------------:|:--------------
 * **PwuM_00003**   |If the crc in nvm is incorrect, the wake up counter will be setted to "0" and next sleep time will be calculated
 * **PwuM_00004**   |If the crc in nvm is correct, the nvm and the local wake up counter will be added and next sleep time will be calculated
 *
 * @param mirror nvm memory
 * @param length length of nvm memory
 *
 */
void periodicWakeUp_checkNvm(const uint8_t* mirror, uint16_t length);

/**
 * @brief Copy data in nvm memory.
 * @details
 * ## Requirements:
 * **Requirement**  |**Description**
 * :---------------:|:--------------
 * **PwuM_00005**   |Copy module data in nvm memory
 *
 * @param mirror nvm memory
 * @param length length of nvm memory
 *
 */
void periodicWakeUp_copyNvmForWrite(uint8_t* mirror, uint16_t length);


/**
 * @brief get function for the periodic wake up counter
 *
 * @return uint16_t periodic wake up counter
 */
uint16_t periodicWakeUp_getWakeUpCounter(void);

/**
 * @brief get function for the configured maximum limit of fast wakeUps
 *
 * @return uint32_t configured maximum number of fast wake-ups
 */
uint32_t periodicWakeUp_getMaxNumberOfFastWakeUps(void);

/**
 * @brief get function for the configured temperature threshold in °C
 *
 * @return int8_t configured temperature threshold
 */
int8_t periodicWakeUp_getTemperatureThreshold(void);

/**
 * @brief get function for the configured short interval
 *
 * @return uint32_t configured short interval
 */
uint32_t periodicWakeUp_getShortInterval(void);

/**
 * @brief get function for the configured middle interval
 *
 * @return uint32_t configured middle interval
 */
uint32_t periodicWakeUp_getMiddleInterval(void);

/**
 * @brief get function for the configured long interval
 *
 * @return uint32_t configured long interval
 */
uint32_t periodicWakeUp_getLongInterval(void);

/**
 * @brief set function for the configured maximum limit of fast wakeUps
 */
void periodicWakeUp_setMaxNumberOfFastWakeUps(uint32_t newValue);

/**
 * @brief set function for the configured temperature threshold in °C
 */
void periodicWakeUp_setTemperatureThreshold(int8_t newValue);

/**
 * @brief set function for the configured short interval
 */
void periodicWakeUp_setShortInterval(uint32_t newValue);

/**
 * @brief set function for the configured middle interval
 */
void periodicWakeUp_setMiddleInterval(uint32_t newValue);

/**
 * @brief set function for the configured long interval
 */
void periodicWakeUp_setLongInterval(uint32_t newValue);
