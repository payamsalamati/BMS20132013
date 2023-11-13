/**
 * @file initializationTask_config.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
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

#include "cps.h"
#include "protocolSelection.h"

#include "KBSInterface.h"
#include "identification.h"
#include "libIdentification.h"
#include "ecuIdentification.h"
#include "ioIf_signals.h"
#include "icdaSensor.h"
#include "periodicWakeUp.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

#define KBS_PARAM_ADDRESS        (&PARAMFLASH_Start + IDENTIFICATION_LENGTH)
#define KBS_PARAM_ADDRESS_LENGTH (sizeof(KBSInput) + sizeof(KBSOutput))

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

extern uint32_t PARAMFLASH_Start;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

void initializationTask_projectDepententInitHook(void)
{
    cps_enableWakeUp();
    cps_initCpsPdoSignals();
    protocolSelection_init();
    periodicWakeUp_init();
}
