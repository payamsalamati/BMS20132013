/*
 * udsDiagnosticSessionControl_XLFLEED.h
 *
 *  Created on: 27.05.2019
 *      Author: Valentin Niemann
 */

#pragma once


#include "uds.h"
#include "stateFunctions.h"


#define UDS_SESSION_TIMEOUT 5000u

#define UDS_SESSION_DEV 0x40u

extern const uint8_t uds_devSessionList[];
extern const uint8_t UDS_DEVSESSIONLIST_SIZE;

extern const uint8_t uds_extendedSessionList[];
extern const uint8_t UDS_EXTENDEDSESSIONLIST_SIZE;

#define UDS_TESTERPRESENT_STMRESET() stmFct_resetCanTimeoutTimer()
