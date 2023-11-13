/**
 * @file heatingCurrentMeasurement.c
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
#include "safetyAfeValueMeasurement.h"
#include "heatingCurrentMeasurement.h"
#include "bms.h"
#include "debug.h"
#include "task_cfg.h"
#if !defined(UNIT_TEST)
#include "afe_MC33771_common_config.h"
#else
#include "test_heatingCurrentMeasurement.h"
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


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//
MEM_SAFETYDATA static int32_t heatingCurrents[BMS_CONFIG_MAX_NUMBER_OF_SLAVES] = { 0 };

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

void heatingCurrentMeasurement_mainFunction(void)
{
    uint16_t iSenseCurrentsSize   = 0;
    const int32_t* iSenseCurrents = safetyAfeValueMeasurement_getAfeCurrents(&iSenseCurrentsSize);

    DEBUG_ASSERT_EQUALS(iSenseCurrentsSize, BMS_CONFIG_NUMBER_OF_SLAVES * AFE_NUMBER_OF_AFE_PER_CSC);

    for(uint8_t i = 0; i < BMS_CONFIG_NUMBER_OF_SLAVES; i++)
    {
        int32_t tempCurrent = 0;
        for(uint8_t j = 0; j < AFE_NUMBER_OF_AFE_PER_CSC; j++)
        {
            tempCurrent += iSenseCurrents[i * AFE_NUMBER_OF_AFE_PER_CSC + j];
        }
        heatingCurrents[i] = tempCurrent / AFE_NUMBER_OF_AFE_PER_CSC;
    }
}

const int32_t* heatingCurrentMeasurement_getCurrents(uint16_t* size)
{
    *size = BMS_CONFIG_NUMBER_OF_SLAVES;
    return (const int32_t*)heatingCurrents;
}

int32_t heatingCurrentMeasurement_getCurrentValue(uint8_t cscIndex)
{
    DEBUG_API_CHECK(cscIndex < BMS_CONFIG_NUMBER_OF_SLAVES)
    return (cscIndex < BMS_CONFIG_NUMBER_OF_SLAVES) ? heatingCurrents[cscIndex] : INT32_MAX;
}
