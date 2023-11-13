/**
 * @file canProtocol_config.c
 * @copyright (c) Futavis GmbH, Aachen 2023 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "canProtocol_config.h"
#include "canProtocol.h"
#include "lindeCAN.h"
#include "kionCAN.h"
#include "baseCAN.h"

//**********************PUBLIC VARIABLE DEFINITIONS **************************//

MEM_CAN uint16_t missingAckErrorCntExternal = 0;
MEM_CAN uint16_t missingAckErrorCntInternal = 0;

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_CAN uint8_t canProtocol = (uint8_t)CAN_PROTOCOL_BASE;

CANProtocol baseCAN = {
    .init            = baseCAN_init,
    .send10ms        = baseCAN_send10ms,
    .send20ms        = baseCAN_send20ms,
    .send40ms        = baseCAN_send40ms,
    .send100ms       = baseCAN_send100ms,
    .send1000ms      = baseCAN_send1000ms,
    .send5000ms      = NULL,
    .sendUDS         = kionCAN_sendLib_uds,
    .sendEmcy        = NULL,
    .receive         = baseCAN_receive,
    .udsHandler      = &kionCANTransmitlib_udsHandler,
    .udsFixedHandler = NULL,
    .xcpHandler      = &xcpCanTransmitHandler
};

const CANProtocol lindeCAN = {
    .init            = lindeCAN_init,
    .send10ms        = lindeCANSend10,
    .send20ms        = NULL,
    .send40ms        = lindeCANSend40,
    .send100ms       = NULL,
    .send1000ms      = NULL,
    .send5000ms      = NULL,
    .sendUDS         = kionCAN_sendLib_uds,
    .sendEmcy        = NULL,
    .receive         = lindeCAN_receive,
    .udsHandler      = &kionCANTransmitlib_udsHandler,
    .udsFixedHandler = NULL,
    .xcpHandler      = &xcpCanTransmitHandler
};
const CANProtocol kionCAN = {
    .init            = kionCAN_init,
    .send10ms        = kionCANSend10,
    .send20ms        = NULL,
    .send40ms        = kionCANSend40,
    .send100ms       = kionCANSend100,
    .send1000ms      = kionCANSend1000,
    .send5000ms      = NULL,
    .sendUDS         = kionCAN_sendLib_uds,
    .sendEmcy        = kionCAN_sendLib_emergency,
    .receive         = kionCAN_receive,
    .udsHandler      = &kionCANTransmitlib_udsHandler,
    .udsFixedHandler = NULL,
    .xcpHandler      = &xcpCanTransmitHandler
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

const CANProtocol* canProtocol_choose(uint8_t val)
{
    switch(val)
    {
        case CAN_PROTOCOL_BASE:
            return &baseCAN;
        case CAN_PROTOCOL_LINDE:
            return &lindeCAN;
        case CAN_PROTOCOL_KION:
            return &kionCAN;
        default:
            break;
    }
    return NULL;
}

void canProtocol_switch(uint8_t val)
{
    canProtocol = val;
}
