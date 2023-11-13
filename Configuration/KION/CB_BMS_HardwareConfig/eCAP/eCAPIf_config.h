/**
 * @file eCAPIf_config.h
 * @copyright Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief This module contains the signals for eCAP
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
#include "eCAP_TMS570LS.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//
extern const uint8_t ECAP_SIGNAL_CONFIG_LENGTH;
extern const ECAPSignalConfig* ecapSignals[];


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

uint32_t eCapIf_getSpeedFanFrequency(void);

uint8_t eCapIf_getBCMnRDyDutyCycle(void);
