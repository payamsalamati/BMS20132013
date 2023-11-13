/**
 * @file stmPrecharge.h
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
#include <stdbool.h>

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef enum
{
    PrechargeTimeBased    = 0,
    PrechargeVoltageBased = 3
} PrechargeMethod;

typedef struct
{
    // @req CB-10021
    // @req CB-10034
    // @req CB-92394
    PrechargeMethod s2Precharge_Method;
    // @req CB-10026
    // @req CB-92396
    uint8_t s2VoltageBasedPrechargeCondition;  // range [0%-100%]; Resolution [0.5%]
    // @req CB-10025
    // @req CB-92397
    uint16_t s2VoltageBasedPrechargeTimeout;  // 0ms – 65535ms. Resolution [1 ms]
    // @req CB-10050
    // @req CB-92398
    uint16_t s2TimeBasedPrechargeTime;  // 0ms – 65535ms. Resolution [1 ms]
} StmPrechargeConfig;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

/**
 * @fn stmPrecharge_isPrechargeVoltageS2Reached
 * @brief check if precharge voltage condition to close contactor S2 is reached
 * @param global variables
 * @return if precharge voltage condition of S2 is reached
 */
bool stmPrecharge_isPrechargeVoltageS2Reached(void);


bool stmPrecharge_setS2PrechargeMethod(uint8_t newValue);
bool stmPrecharge_setS2VoltageBasedPrechargeCondition(uint8_t newValue);
bool stmPrecharge_setS2VoltageBasedPrechargeTimeout(uint16_t newValue);
bool stmPrecharge_setS2TimeBasedPrechargeTime(uint16_t newValue);
bool stmPrecharge_setContactorPreferenceDirection(uint8_t newValue);

PrechargeMethod stmPrecharge_getS2PrechargeMethod(void);
uint8_t stmPrecharge_getS2VoltageBasedPrechargeCondition(void);
uint16_t stmPrecharge_getS2VoltageBasedPrechargeTimeout(void);
uint16_t stmPrecharge_getS2TimeBasedPrechargeTime(void);
uint8_t stmPrecharge_getContactorPreferenceDirection(void);
