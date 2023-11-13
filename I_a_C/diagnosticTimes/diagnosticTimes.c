/**
 * @file diagnosticTimes.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdbool.h>
#include "diagnosticTimes.h"
#include "task_cfg.h"
#include "nvm.h"
#include "osIf.h"
#include "debug.h"
#include "stateFunctions.h"
#include "subMasterBalancing.h"
#if defined(UNIT_TEST)
#include "test_diagnosticTimer.h"
#else
#include "cell_module.h"
#endif

#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
#include "alternativeMemFunctions.h"
#endif

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_APPLICATION DiagnosticTimesNvm diagnosticTimesNvm = {
    .diagnosticTotalOperatingTimeIns  = 0u,
    .diagnosticDriveOperatingTimeIns  = 0u,
    .diagnosticChargeOperatingTimeIns = 0u,
    .diagnosticPeriodicWakeUpTimeIns  = 0u,
    .diagnosticTotalBalancingTimeIns  = 0u,
};

MEM_APPLICATION uint8_t diagnosticTimes_counter = 0u;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void diagnosticTimes_checkNvm(const uint8_t* mirror, uint16_t length)
{
    if((nvm_getErrorStatus(NVM_DIAGNOSTIC_TIMES_BLOCK_ID) == NVM_REQ_OK) && (sizeof(DiagnosticTimesNvm) == length))
    {
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
        alternativeMemFunctions_memcpy((uint8_t*)&diagnosticTimesNvm, mirror, sizeof(DiagnosticTimesNvm));
#else
        memcpy((uint8_t*)&diagnosticTimesNvm, mirror, sizeof(DiagnosticTimesNvm));
#endif
    }
}

void diagnosticTimes_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
    alternativeMemFunctions_memcpy(mirror, (uint8_t*)&diagnosticTimesNvm, sizeof(DiagnosticTimesNvm));
#else
    memcpy(mirror, (uint8_t*)&diagnosticTimesNvm, sizeof(DiagnosticTimesNvm));
#endif
}

// wird alle 100ms in limitCheckTask aufgerufen
void diagnosticTimes_mainFunction(void)
{
    diagnosticTimes_counter++;
    if((diagnosticTimes_counter % 10u) == 0u)
    {
        diagnosticTimes_counter = 0u;
        // @req CB-78495
        diagnosticTimesNvm.diagnosticTotalOperatingTimeIns++;
        STMStates state = stmFct_getBatteryStateGlobal();

        bool balancingActive = false;

        if(state == State_Drive_Mode_Active)
        {
            // @req CB-78496
            diagnosticTimesNvm.diagnosticDriveOperatingTimeIns++;
        }
        else if(state == State_Charge_Mode_Active)
        {
            // @req CB-78497
            diagnosticTimesNvm.diagnosticChargeOperatingTimeIns++;
        }
        else if((state == State_PeriodicWakeUp_Routines)
                || (state == State_PeriodicWakeUp_Balancing)
                || (state == State_PeriodicWakeUp_Relaxing)
                || (state == State_PeriodicWakeUp_Update_Recovery_Data))
        {
            // @req CB-78498
            diagnosticTimesNvm.diagnosticPeriodicWakeUpTimeIns++;
        }
        else
        {
            // do nothing
        }
        for(uint16_t i = 0; i < BMS_CONFIG_NUMBER_OF_SLAVES; i++)
        {
            if(subMasterBalancing_getCellBalancingStatusValue(i) != 0u)
            {
                balancingActive = true;
            }
        }
        if(balancingActive == true)
        {
            // @req CB-78499
            diagnosticTimesNvm.diagnosticTotalBalancingTimeIns++;
        }
    }
}

uint32_t diagnosticTimes_getDiagnosticTotalOperatingTimeIns(void)
{
    return diagnosticTimesNvm.diagnosticTotalOperatingTimeIns;
}

uint32_t diagnosticTimes_getDiagnosticDriveOperatingTimeIns(void)
{
    return diagnosticTimesNvm.diagnosticDriveOperatingTimeIns;
}

uint32_t diagnosticTimes_getDiagnosticChargeOperatingTimeIns(void)
{
    return diagnosticTimesNvm.diagnosticChargeOperatingTimeIns;
}

uint32_t diagnosticTimes_getDiagnosticPeriodicWakeUpTimeIns(void)
{
    return diagnosticTimesNvm.diagnosticPeriodicWakeUpTimeIns;
}

uint32_t diagnosticTimes_getDiagnosticTotalBalancingTimeIns(void)
{
    return diagnosticTimesNvm.diagnosticTotalBalancingTimeIns;
}

void diagnosticTimes_clearAll(void)
{
    diagnosticTimesNvm.diagnosticTotalOperatingTimeIns  = 0u;
    diagnosticTimesNvm.diagnosticDriveOperatingTimeIns  = 0u;
    diagnosticTimesNvm.diagnosticChargeOperatingTimeIns = 0u;
    diagnosticTimesNvm.diagnosticPeriodicWakeUpTimeIns  = 0u;
    diagnosticTimesNvm.diagnosticTotalBalancingTimeIns  = 0u;
    diagnosticTimes_counter                             = 0u;
}
