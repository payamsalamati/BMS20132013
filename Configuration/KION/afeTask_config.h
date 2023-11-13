/**
 * @file     afeTask_config_default.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - all rights reserved
 * @brief    Configuration for afe Task
 * @details
 *	 Interfaces to other modules:
 */

#pragma once


//***************************************************************************/
//*************************** DEFINES ***************************************/
//***************************************************************************/

#define AFETASK_MAIN_FUNCTION_CYCLE_TIME 200U
#define AFETASK_SAFETY_COMM_ERROR_TIME   3000U  //time after AFE communication error is set in ms
#define AFETASK_COMM_ERROR_TIME          2000U  //time after AFE communication error is set in ms
#define AFETASK_SAFETY_MAX_TRY_AFE_COMM  (uint8_t)(AFETASK_SAFETY_COMM_ERROR_TIME / AFETASK_MAIN_FUNCTION_CYCLE_TIME)
#define AFETASK_MAX_TRY_AFE_COMM         (uint8_t)(AFETASK_COMM_ERROR_TIME / AFETASK_MAIN_FUNCTION_CYCLE_TIME)
