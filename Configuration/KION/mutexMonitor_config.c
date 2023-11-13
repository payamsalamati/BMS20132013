/**
 * @file mutexMonitor_config.c
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

#include "kionCAN.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

void mutexMonitor_mutexPendFailedHook(MutexAnalysisData pendingMutexAnalysis, uint8_t mutexPendingSource, uint8_t mutexRequestingSource, OSIf_Error error)
{
#if defined(SW_RESET_ANALYSIS_CAN_DATA)
    kionCAN_sendMutexPendFailedSignal(pendingMutexAnalysis, mutexPendingSource, mutexRequestingSource, error);
#endif
}

void mutexMonitor_mutexPostFailedHook(uint8_t mutexPostSource, OSIf_Error error)
{
#if defined(SW_RESET_ANALYSIS_CAN_DATA)
    kionCAN_sendMutexPostFailedSignal(mutexPostSource, error);
#endif
}
