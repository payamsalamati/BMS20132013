/*
 * stateMachineTask_config_KION.h
 *
 *  Created on: 07.11.2019
 *      Author: Kostiantyn
 */

#pragma once

#include "config_enable.h"


/**@def StateMachineEnter(X)
 * @brief
 * @details
 *
 * (Fix value)
 */
#define StateMachineEnter(X) kionStateMachine_enter(X)

/**@def StateMachineHandleType
 * @brief
 * @details
 *
 * (Fix value)
 */
#define StateMachineHandleType KionStateMachine

/**@def StateMachineInit(X)
 * @brief
 * @details
 *
 * (Fix value)
 */
#define StateMachineInit(X) kionStateMachine_init(X)

/**@def StateMachineRunCycle(X)
 * @brief
 * @details
 *
 * (Fix value)
 */
#define StateMachineRunCycle(X) kionStateMachine_runCycle(X)

/**@def SOFTWARE_VERSION_STATUS
 * @brief // PP = Project number
 * @details
 *
 * (Fix value)
 */
#define SOFTWARE_VERSION_STATUS 0xAA

#define STATE_MACHINE_HEADER "KionStateMachine.h"

#define STATE_MACHINE_HEADER_ERROR "ErrorStm.h"

#define ErrorStateMachineHandleType ErrorStm

#define STATE_MACHINE_CAN_OPEN CONFIG_ENABLED
