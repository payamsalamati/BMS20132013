/**
 *
 * @file  baseCAN_config.c
 * @brief
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

//******************* INCLUDES ********************************//

#include "baseCAN.h"
#include "can_config.h"
#include "bms.h"

#include "kionCAN.h"
#include "lindeCAN.h"

//******************* DEFINE ***********************************//

#define BASECAN_NODE CAN_NODE_2

//************************** PUBLIC VARIABLE DEFINITIONS ******************************//

MEM_CAN CANNodeConfig baseCanConfig = {
    .canFrequency             = CAN_NODE2_FREQUENCY,
    .baudrate                 = 500,
    .samplePoint              = CAN_NODE2_SAMPLE_POINT,
    .synchronizationJumpWidth = CAN_NODE2_SYNCHRONIZATION_JUMP_WIDTH,
    .receiveISRHandler        = (CANInterruptHandler)baseCAN_receiveInterrupt,
    .transmitISRHandler       = (CANInterruptHandler)baseCAN_transmitISRHandler,
    .alertISRHandler          = (CANInterruptErrorHandler)baseCAN_alertInterrupt,
    .node                     = BASECAN_NODE
};

//************************** PUBLIC FUNCTION DEFINITIONS ******************************//

void baseCAN_init(void)
{
    kionCAN_configBeforeProtocolSelection();
    lindeCAN_configBeforeProtocolSelection();
    kionCAN_configSendBeforeProtocolSelection();
    lindeCAN_configSendBeforeProtocolSelection();
    canIf_configNode(&baseCanConfig);
}
