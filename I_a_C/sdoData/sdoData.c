/**
 * @file sdoData.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "sdoData.h"
#include "task_cfg.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

#define KEY_SWITCH_STATUS_MIN     0x00u
#define KEY_SWITCH_STATUS_MAX     0x01u
#define KEY_SWITCH_STATUS_DEFAULT 0xFFu

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_APPLICATION SdoData sdoData = {
    .keySwitchStatus = KEY_SWITCH_STATUS_DEFAULT,  // @req CB-73147
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

uint8_t sdoData_getKeySwitchStatus(void)
{
    return sdoData.keySwitchStatus;
}
bool sdoData_setKeySwitchStatus(uint8_t newValue)
{
    bool retVal = false;
    if(((KEY_SWITCH_STATUS_MIN == 0u) || (newValue >= KEY_SWITCH_STATUS_MIN)) && (newValue <= KEY_SWITCH_STATUS_MAX))
    {
        sdoData.keySwitchStatus = newValue;
        retVal                  = true;
    }
    return retVal;
}
