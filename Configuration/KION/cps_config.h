/**
 * @file cps_config.h
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

#include "cps.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

extern CpsConfig cpsConfig;

#define CPS_OUT_LIMIT_DEFAULT 7000u
#define CPS_OUT_LIMIT         cpsConfig.cpsOutLimit

#define CPS_OUT_LIMIT_BOOST_DEFAULT 15000
#define CPS_OUT_LIMIT_BOOST         cpsConfig.cpsOutLimitBoost

#define CPS_IMPUT_VOLTAGE_LIMIT_DEFAULT 20000
#define CPS_IMPUT_VOLTAGE_LIMIT         cpsConfig.cpsInputVoltageLimit

#define CPS_INFO_REMAINING_CAPACITY_DEFAULT 0xFFFFFF  // @req CB-91563
#define CPS_INFO_REMAINING_CAPACITY         cpsConfig.cpsInfoRemainingCapacity
