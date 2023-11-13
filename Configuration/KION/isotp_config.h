/**
 * @file     isotp_DEFAULT.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 */

#pragma once


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "config_enable.h"
#include "isotp.h"
//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

/**
 * @brief length of receive buffer for isotp messages
 * this determines the maximum size of a message that can be received
 */
#define ISOTP_BROADCAST_REMOTE_ADDRESS 0xFE

/**
 * @def ISOTP_TIMER_INTERVAL
 * @brief interval in which isotp_timer() must be called by the application given in ms
 */
#define ISOTP_TIMER_INTERVAL 10


#define CAN_ISOTP_DEFAULT_FRAME_TXTIME 10  // minimum Time needed between two can messsages for CF
#define CAN_ISOTP_DEFAULT_RECV_STMIN   0x01
#define CAN_ISOTP_DEFAULT_RECV_WFTMAX  0

/**@def ISOTP_INTER_CAN
 * @brief enable uds for inter CAN
 * @details
 *
 * (Fix value)
 */
#define ISOTP_INTER_CAN CONFIG_DISABLED

//***************************************************************************//
//************************** SOCKETS ****************************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
