/**
 *
 * @file  baseCAN.h
 * @brief
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 */

#ifndef BASECAN_H
#define BASECAN_H

//******************* INCLUDES ********************************//

#include "canIf_types.h"
#include "dem.h"

//******************* FUNCTION PROTOTYPES *********************//

void baseCAN_receiveInterrupt(CANMessageObject msgObj);
void baseCAN_transmitISRHandler(CANMessageObject msgObj);
void baseCAN_alertInterrupt(CAN_STATUS status);

void baseCAN_init(void);
void baseCAN_send10ms(void);
void baseCAN_send20ms(void);
void baseCAN_send40ms(void);
void baseCAN_send100ms(void);
void baseCAN_send1000ms(void);
void baseCAN_receive(const CANMessage* msg);

#endif
