

/**
 * @file protocolSelection.c
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

#include "protocolSelection.h"
#include <stddef.h>

#include "osIf.h"
#include "nvm.h"
#include "task_cfg.h"
#include "debug.h"
#include "stateFunctions.h"
#include "protocolSelection_config.h"

#if defined(UNIT_TEST)
#include "test_protocolSelection.h"
#endif

#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
#include "alternativeMemFunctions.h"
#endif

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    Protocol actual;
    bool authentificationComplete;
} ProtocolSelectionData;

typedef struct
{
    Protocol last;
    uint8_t reserve[7];
} ProtocolSelectionNVM;

#define PROTOCOL_SELECTION_NVM_INIT_MAX_DELAY 200

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_NVM ProtocolSelectionNVM protocolSelectionNVM = {
    .last = Protocol_ERROR,
};

MEM_NVM bool protocolSelectionIsNvmRead = false;

MEM_SHAREDATA ProtocolSelectionData protocolSelectionData = {
    .actual                   = Protocol_ERROR,
    .authentificationComplete = false,
};

MEM_SEC_PARAMETER ProtocolSelectionConfig protocolSelectionConfigParameter = {
    .brandIdConfig = Protocol_AUTOMATIC,
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

void protocolSelection_checkNvm(const uint8_t* mirror, uint16_t length)
{
    DEBUG_ASSERT(sizeof(ProtocolSelectionNVM) == length);
    if(nvm_getErrorStatus(NVM_PROTOCOL_SELECTION_DATA_BLOCK_ID) == NVM_REQ_OK)
    {
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
        alternativeMemFunctions_memcpy((uint8_t*)&protocolSelectionNVM, mirror, sizeof(ProtocolSelectionNVM));
#else
        memcpy((uint8_t*)&protocolSelectionNVM, mirror, sizeof(ProtocolSelectionNVM));
#endif
    }
    protocolSelectionIsNvmRead = true;
}

void protocolSelection_copyNvmForWrite(uint8_t* mirror, uint16_t length)
{
#if defined(USE_ALTERNATIVE_MEM_FUNCTIONS)
    alternativeMemFunctions_memcpy(mirror, (uint8_t*)&protocolSelectionNVM, sizeof(ProtocolSelectionNVM));
#else
    memcpy(mirror, (uint8_t*)&protocolSelectionNVM, sizeof(ProtocolSelectionNVM));
#endif
}

bool protocolSelection_isNvmRead(void)
{
    return protocolSelectionIsNvmRead;
}

void protocolSelection_init(void)
{
    nvm_readBlock(NVM_PROTOCOL_SELECTION_DATA_BLOCK_ID, NULL);
    if(protocolSelectionConfigParameter.brandIdConfig != Protocol_AUTOMATIC)
    {
        protocolSelectionData.actual                   = protocolSelectionConfigParameter.brandIdConfig;
        protocolSelectionData.authentificationComplete = true;
        protocolSelectionNVM.last                      = protocolSelectionConfigParameter.brandIdConfig;
    }
}

void protocolSelection_setBrand(Protocol newSetting)
{
    if(protocolSelectionConfigParameter.brandIdConfig == Protocol_AUTOMATIC && protocolSelectionData.authentificationComplete == false)
    {
        protocolSelectionData.actual                   = newSetting;
        protocolSelectionData.authentificationComplete = true;
        protocolSelectionNVM.last                      = newSetting;
        protocolSelection_authentificationCompleteHook(newSetting);
    }
}

Protocol protocolSelection_getLastBrand(void)
{
    Protocol retVal = protocolSelectionNVM.last;
    if(retVal != Protocol_KION)
    {
        retVal = Protocol_KION;  //set default Brand
    }
    return retVal;
}

Protocol protocolSelection_getBrand(void)
{
    return protocolSelectionData.actual;
}

bool protocolSelection_getAuthentificationComplete(void)
{
    return protocolSelectionData.authentificationComplete;
}

void protocolSelection_resetBrand(void)
{
    protocolSelectionData.actual                   = (protocolSelectionConfigParameter.brandIdConfig != Protocol_AUTOMATIC) ? protocolSelectionConfigParameter.brandIdConfig : Protocol_ERROR;
    protocolSelectionData.authentificationComplete = (protocolSelectionConfigParameter.brandIdConfig != Protocol_AUTOMATIC) ? true : false;
}

bool protocolSelection_setBrandIdConfig(uint16_t newValue)
{
    bool retVal = true;
    switch(newValue)
    {
        case 0u:
            protocolSelectionConfigParameter.brandIdConfig = Protocol_AUTOMATIC;
            break;
        case 3u:
            protocolSelectionConfigParameter.brandIdConfig = Protocol_KION;
            break;
        default:
            retVal = false;
            break;
    }
    return retVal;
}

#if defined(UNIT_TEST)
void protocolSelection_resetAll()
{
    protocolSelectionNVM.last                      = Protocol_ERROR;
    protocolSelectionData.actual                   = Protocol_ERROR;
    protocolSelectionData.authentificationComplete = false;
    protocolSelectionConfigParameter.brandIdConfig = Protocol_AUTOMATIC;
}
#endif
