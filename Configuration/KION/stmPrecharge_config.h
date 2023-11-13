/**
 * @file stmPrecharge_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
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

#include "stmPrecharge.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

extern StmPrechargeConfig stmPrechargeConfig;

// @req CB-92394
#define STM_PRECHARGE_CONFIG_DEFAULT_S2_PRECHARGE_METHOD PrechargeTimeBased
#define STM_PRECHARGE_CONFIG_S2_PRECHARGE_METHOD         stmPrechargeConfig.s2Precharge_Method

// @req CB-92396
#define STM_PRECHARGE_CONFIG_S2_PRECHARGE_VOLTAGE_BASED_MAX_RATIO     200u
#define STM_PRECHARGE_CONFIG_S2_PRECHARGE_VOLTAGE_BASED_MIN_RATIO     0u
#define STM_PRECHARGE_CONFIG_DEFAULT_S2_PRECHARGE_VOLTAGE_BASED_RATIO 190u
#define STM_PRECHARGE_CONFIG_S2_PRECHARGE_VOLTAGE_BASED_RATIO         stmPrechargeConfig.s2VoltageBasedPrechargeCondition

// @req CB-92397
#define STM_PRECHARGE_CONFIG_S2_PRECHARGE_VOLTAGE_BASED_MAX_TIMEOUT     UINT16_MAX
#define STM_PRECHARGE_CONFIG_S2_PRECHARGE_VOLTAGE_BASED_MIN_TIMEOUT     0u
#define STM_PRECHARGE_CONFIG_DEFAULT_S2_PRECHARGE_VOLTAGE_BASED_TIMEOUT 10000u
#define STM_PRECHARGE_CONFIG_S2_PRECHARGE_VOLTAGE_BASED_TIMEOUT         stmPrechargeConfig.s2VoltageBasedPrechargeTimeout

// @req CB-92398
#define STM_PRECHARGE_CONFIG_S2_PRECHARGE_TIME_BASED_MAX_TIME     UINT16_MAX
#define STM_PRECHARGE_CONFIG_S2_PRECHARGE_TIME_BASED_MIN_TIME     0u
#define STM_PRECHARGE_CONFIG_DEFAULT_S2_PRECHARGE_TIME_BASED_TIME 100u
#define STM_PRECHARGE_CONFIG_S2_PRECHARGE_TIME_BASED_TIME         stmPrechargeConfig.s2TimeBasedPrechargeTime

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
