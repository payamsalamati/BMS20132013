/**
 * @file energyCounter.c
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief Unittest for energyCounter module
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <string.h>
#include <math.h>

#include "energyCounter.h"
#include "batteryCurrentMeasurement.h"
#include "task_cfg.h"
#include "nvm.h"
#include "nvm_config_id.h"
#include "debug.h"
#include "stateFunctions.h"
#include "moduleVoltageMeasurement.h"

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

/**
 * @var coulombCountsData
 * @brief Diagnostic Coulomb Count Data, data in mWs
 */
MEM_ENERGY_COUNTER static ENERGY_COUNTER_NVM coulombCountsData = {
    .diagnosticCoulombCountPositiveCharge    = 0ULL,
    .diagnosticCoulombCountPositiveDischarge = 0ULL,
    .diagnosticCoulombCountNegativeDischarge = 0ULL
};


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS ********************//
//***************************************************************************//

static void energyCounter_integrationStep(STMStates BatteryState);

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//


void energyCounter_mainFunction(void)
{
    energyCounter_integrationStep(stmFct_getBatteryStateGlobal());
}


static void energyCounter_integrationStep(STMStates BatteryState)
{

    bool direction = (batteryCurrentMeasurement_getValue() >= 0) ? true : false;

    uint64_t energy = ((float)moduleVoltageMeasurement_getAverage() * (float)abs(batteryCurrentMeasurement_getValue()) / 1000.0 * 0.1) + 0.5;

    switch(BatteryState)
    {
        case State_Drive_Mode_Active:

            if(direction == true)
            {
                coulombCountsData.diagnosticCoulombCountPositiveDischarge += energy;
            }
            else
            {
                coulombCountsData.diagnosticCoulombCountNegativeDischarge += energy;
            }
            break;

        case State_Charge_Mode_Active:

            if(direction == true)
            {
                coulombCountsData.diagnosticCoulombCountPositiveCharge += energy;
            }
            else
            {
                /* DO-NOTHING */
            }
            break;

        default:
            /* DO-NOTHING */
            break;
    }
}


const ENERGY_COUNTER_NVM* energyCounter_getCoulombCounterData(void)
{
    return (const ENERGY_COUNTER_NVM*)&coulombCountsData;
}


void energyCounter_checkNvm(const uint8_t* mirror, uint16_t length)
{
    DEBUG_ASSERT(sizeof(ENERGY_COUNTER_NVM) == length);

    if(NVM_REQ_OK == nvm_getErrorStatus((NVM_ENERGY_COUNTER_BLOCK_ID)))
    {
        ENERGY_COUNTER_NVM tmpData;
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
        alternativeMemFunctions_memcpy(&tmpData, mirror, sizeof(ENERGY_COUNTER_NVM));
#else
        memcpy(&tmpData, mirror, sizeof(ENERGY_COUNTER_NVM));
#endif
        coulombCountsData.diagnosticCoulombCountPositiveCharge += tmpData.diagnosticCoulombCountPositiveCharge;
        coulombCountsData.diagnosticCoulombCountPositiveDischarge += tmpData.diagnosticCoulombCountPositiveDischarge;
        coulombCountsData.diagnosticCoulombCountNegativeDischarge += tmpData.diagnosticCoulombCountNegativeDischarge;
    }
}


void energyCounter_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
    alternativeMemFunctions_memcpy(mirror, (uint8_t*)&coulombCountsData, sizeof(coulombCountsData));
#else
    memcpy(mirror, (uint8_t*)&coulombCountsData, sizeof(coulombCountsData));
#endif
}


void energyCounter_resetDiagnosticCoulombCount(void)
{
    coulombCountsData.diagnosticCoulombCountPositiveCharge    = 0ULL;
    coulombCountsData.diagnosticCoulombCountPositiveDischarge = 0ULL;
    coulombCountsData.diagnosticCoulombCountNegativeDischarge = 0ULL;
}
