/**
 * @file afe_multibuffer_config.h
 * @copyright (c) Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
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


//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

// DISABLED: "normal" SPI usage without interrupt
// ENABLED: Multibuffer usage with interrupt receive (queue)   Multibuffer with TMS570 receive interrupt = SPI PORT 5, transmit port = SPI PORT 4
#define AFE_MULTIBUFFER_USAGE CONFIG_ENABLED

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
