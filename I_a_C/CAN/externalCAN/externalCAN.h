/**
 * @file     externalCAN.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * <b>Dependencies</b>
 *  - which other modules are needed by this module and why
 *
 * <b>Description</b>
 *
 */


#pragma once


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>
#include "kionCAN.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

extern CANNodeConfig externalCanConfig;


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//
#define EXTERNALCAN_NODE CAN_NODE_2

#define CAN_EXTERNAL_CONFIG_STRUCT    externalCanConfig
#define CAN_EXTERNAL_CONFIG()         externalCAN_setMessageBoxesBeforeProtocol()
#define CAN_EXTERNAL_RECEIVE(x)       externalCAN_receiveMessage(x)
#define CAN_EXTERNAL_CONFIG_SEND()    externalCAN_setTransmitMessageBoxesBeforeProtocol()
#define CAN_EXTERNAL_SEND_1000()      externalCAN_send_1000()
#define CAN_EXTERNAL_SEND_100()       externalCAN_send_100()
#define CAN_EXTERNAL_SEND_40()        externalCAN_send_40()
#define CAN_EXTERNAL_SEND_20()        externalCAN_send_20()
#define CAN_EXTERNAL_SEND_10()        externalCAN_send_10()
#define CAN_EXTERNAL_SEND_EMCY_MSG(x) externalCAN_send_emcy_msg(x)
#define CAN_EXTERNAL_SWRESET()        externalCAN_reset()

#define EXTERNALCAN_MAX_MISSING_ACK_ERROR_COUNT 3u

//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void externalCAN_receiveMessage(CANMessage* msg);
void externalCAN_setMessageBoxesBeforeProtocol(void);
void externalCAN_setMessageBoxesKion(void);
void externalCAN_setMessageBoxesLinde(void);
void externalCAN_setTransmitMessageBoxesBeforeProtocol(void);
void externalCAN_setTransmitMessageBoxesKion(void);
void externalCAN_setTransmitMessageBoxesLinde(void);
void externalCAN_send_1000(void);
void externalCAN_send_100(void);
void externalCAN_send_40(void);
void externalCAN_send_20(void);
void externalCAN_send_10(void);
void externalCAN_send_emcy_msg(uint8_t* emcyData);
void externalCAN_reset(void);
void externalCAN_receiveInterrupt(CANMessageObject msgObj);
void externalCAN_transmitISRHandler(CANMessageObject msgObj);
void externalCAN_alertInterrupt(CAN_STATUS status);
uint16_t externalCAN_getMissingAckErrorCounterExternal(void);
