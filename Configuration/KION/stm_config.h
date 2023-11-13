/**
 * @file stm_config.h
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

#include "stateFunctions.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

extern StmConfig stmConfigParameter;

/**
 * @brief timeout for init state
 */
#define STM_CONFIG_MAX_TIMEOUT_INIT     10000u
#define STM_CONFIG_MIN_TIMEOUT_INIT     0u
#define STM_CONFIG_DEFAULT_TIMEOUT_INIT 5000u
#define STM_CONFIG_TIMEOUT_INIT         stmConfigParameter.timeoutInit

/**
 * @brief timeout for waiting mode
 */
#define STM_CONFIG_MAX_TIMEOUT_WAITINGMODE 43200000u
#define STM_CONFIG_MIN_TIMEOUT_WAITINGMODE 0u
#if defined(EMV_TEST)
#define STM_CONFIG_DEFAULT_TIMEOUT_WAITINGMODE STM_CONFIG_MAX_TIMEOUT_WAITINGMODE
#else
#define STM_CONFIG_DEFAULT_TIMEOUT_WAITINGMODE 10000u
#endif
#define STM_CONFIG_TIMEOUT_WAITINGMODE stmConfigParameter.timeoutWaiting

/**
 * @brief timeout for diag mode
 */
#define STM_CONFIG_MAX_TIMEOUT_DIAGMODE     43200000u
#define STM_CONFIG_MIN_TIMEOUT_DIAGMODE     0u
#define STM_CONFIG_DEFAULT_TIMEOUT_DIAGMODE 10000u
#define STM_CONFIG_TIMEOUT_DIAGMODE         stmConfigParameter.timeoutDiagMode

/**
 * @brief max current for open contactors
 */
#define STM_CONFIG_MAX_SHUTDOWN_MAX_CURRENT     500000u
#define STM_CONFIG_MIN_SHUTDOWN_MAX_CURRENT     0u
#define STM_CONFIG_DEFAULT_SHUTDOWN_MAX_CURRENT 50000u
#define STM_CONFIG_SHUTDOWN_MAX_CURRENT         stmConfigParameter.shutdownMaxCurrent

/**
 * @brief max can timeout to open contactors
 */
#define STM_CONFIG_MAX_TIMEOUT_OPEN_CONTACTORS     60000u
#define STM_CONFIG_MIN_TIMEOUT_OPEN_CONTACTORS     0u
#define STM_CONFIG_DEFAULT_TIMEOUT_OPEN_CONTACTORS 1000u
#define STM_CONFIG_TIMEOUT_OPEN_CONTACTORS         stmConfigParameter.timeoutOpenContactors

/**
 * @brief max balancing time in periodc wake up
 */
#define STM_CONFIG_MAX_PWU_MAX_BALANCING_TIME     60000000u
#define STM_CONFIG_MIN_PWU_MAX_BALANCING_TIME     0u
#define STM_CONFIG_DEFAULT_PWU_MAX_BALANCING_TIME 1800000u
#define STM_CONFIG_PWU_MAX_BALANCING_TIME         stmConfigParameter.pwuMaxBalTime

/**
 * @brief max cell relaxing time in periodc wake up
 */
#define STM_CONFIG_MAX_PWU_MAX_RELAXINGG_TIME     60000000u
#define STM_CONFIG_MIN_PWU_MAX_RELAXINGG_TIME     0u
#define STM_CONFIG_DEFAULT_PWU_MAX_RELAXINGG_TIME 300000u
#define STM_CONFIG_PWU_MAX_RELAXINGG_TIME         stmConfigParameter.pwuMaxRelaxTime

/**
 * @brief max time for recovery routine
 */
#define STM_CONFIG_MAX_PWU_TIMEOUT_RECOVERY_ROUTINE     60000000u
#define STM_CONFIG_MIN_PWU_TIMEOUT_RECOVERY_ROUTINE     0u
#define STM_CONFIG_DEFAULT_PWU_TIMEOUT_RECOVERY_ROUTINE 2400000u
#define STM_CONFIG_PWU_TIMEOUT_RECOVERY_ROUTINE         stmConfigParameter.pwuTimeoutRecovery

/**
 * @brief timer for CAT3 DTC in emergency state
 */
#define STM_CONFIG_MAX_EMERGENCY_CAT3_TIMER     60000u
#define STM_CONFIG_MIN_EMERGENCY_CAT3_TIMER     0u
#define STM_CONFIG_DEFAULT_EMERGENCY_CAT3_TIMER 5000u
#define STM_CONFIG_EMERGENCY_CAT3_TIMER         stmConfigParameter.emergencyCat3Timer

/**
 * @brief required (min) number of pdo counts cps required to set signals
 */
#define STM_CONFIG_MAX_NUMBER_OF_PDO_COUNTS     255u
#define STM_CONFIG_MIN_NUMBER_OF_PDO_COUNTS     0u
#define STM_CONFIG_DEFAULT_NUMBER_OF_PDO_COUNTS 3u
#define STM_CONFIG_NUMBER_OF_PDO_COUNTS         stmConfigParameter.numberOfPDOCounts

/**
 * @brief required delay for CPSout enable
 */
#define STM_CONFIG_MAX_CPSOUT_DELAY_ENABLE     10000u
#define STM_CONFIG_MIN_CPSOUT_DELAY_ENABLE     0u
#define STM_CONFIG_DEFAULT_CPSOUT_DELAY_ENABLE 100u
#define STM_CONFIG_CPSOUT_DELAY_ENABLE         stmConfigParameter.cpsoutDelayEnable

/**
 * @brief required delay for CPSout disable in drive mode
 */
#define STM_CONFIG_MAX_CPSOUT_DELAY_DISABLE_DRIVE 10000u
#define STM_CONFIG_MIN_CPSOUT_DELAY_DISABLE_DRIVE 0u
#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
#define STM_CONFIG_DEFAULT_CPSOUT_DELAY_DISABLE_DRIVE 500u
#else
#define STM_CONFIG_DEFAULT_CPSOUT_DELAY_DISABLE_DRIVE 100u
#endif
#define STM_CONFIG_CPSOUT_DELAY_DISABLE_DRIVE stmConfigParameter.cpsoutDelayDisableDrive

/**
 * @brief required delay for CPSout disable in emergency mode
 */
#define STM_CONFIG_MAX_CPSOUT_DELAY_DISABLE_EMERGENCY     10000u
#define STM_CONFIG_MIN_CPSOUT_DELAY_DISABLE_EMERGENCY     0u
#define STM_CONFIG_DEFAULT_CPSOUT_DELAY_DISABLE_EMERGENCY 500u
#define STM_CONFIG_CPSOUT_DELAY_DISABLE_EMERGENCY         stmConfigParameter.cpsoutDelayDisableEmergency

/**
 * @brief required delay for CPSout disable in error mode
 */
#define STM_CONFIG_CPSOUT_DELAY_DISABLE_ERROR 600

/**
 * @brief timeout for open contactors routine in error mode in ms
 */
#define STM_CONFIG_MAX_ERROR_TIMEOUT_OPEN_CONTACTORS     60000u
#define STM_CONFIG_MIN_ERROR_TIMEOUT_OPEN_CONTACTORS     0u
#define STM_CONFIG_DEFAULT_ERROR_TIMEOUT_OPEN_CONTACTORS 5000u
#define STM_CONFIG_ERROR_TIMEOUT_OPEN_CONTACTORS         stmConfigParameter.errorTimeoutOpenContactors

/**
 * @brief can timeout in error mode in ms
 */
#define STM_CONFIG_MAX_ERROR_TIMEOUT_CAN 60000u
#define STM_CONFIG_MIN_ERROR_TIMEOUT_CAN 0u
#if defined(SIL_DEBUG)
#define STM_CONFIG_DEFAULT_ERROR_TIMEOUT_CAN 1500u
#else
#define STM_CONFIG_DEFAULT_ERROR_TIMEOUT_CAN 190u
#endif
#define STM_CONFIG_ERROR_TIMEOUT_CAN stmConfigParameter.errorTimeoutCAN

/**
 * @brief timeout for close contactors routine
 */
#define STM_CONFIG_TIMEOUT_CLOSE_CONTACTORS 1000

/**
 * @brief Cycle time of statemachine
 */
#define STM_CONFIG_CYCLE_TIME 10

/**
 * @brief timer for hw initialization
 */
#define STM_CONFIG_WAIT_FOR_HW_INIT 5000

#define STM_CONFIG_CPS_SHUTDOWN_TIMEOUT  100u
#define STM_CONFIG_ICDA_SHUTDOWN_TIMEOUT 10u

/**
 * @brief pushbutten is built in
 */
#define STM_CONFIG_DEFAULT_PUSHBUTTON false
#define STM_CONFIG_PUSHBUTTON         stmConfigParameter.pushButtonConfig

/**
 * @brief Contactor Preference Direction Configuration
 */
#define STM_CONFIG_DEFAULT_CONTACTOR_PREFERENCE_DIRECTION S1_ChargeDirection
#define STM_CONFIG_CONTACTOR_PREFERENCE_DIRECTION         stmConfigParameter.contactorPreferenceDirection


#define STM_CPSOUT_VARIANT_OFF 0u
#define STM_CPSOUT_VARIANT_ON  1u

#define STM_CONFIG_DEFAULT_CPSOUT_VARIANT STM_CPSOUT_VARIANT_ON

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
