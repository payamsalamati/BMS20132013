/**
 * @file canWakeupIf_config.c
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

#include "canWakeupIf.h"
#include "can_TJA1145.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

#define CAN_WAKE_UP_USED_DEVICE (uint8_t)0

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

const CANWakeUpType* const canWakeUpTypes[] = {
    &canWakeUp_TJA1145,
};
const uint8_t CAN_WAKEUP_TYPES_LENGTH = sizeof(canWakeUpTypes) / sizeof(CANWakeUpType*);

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//


CAN_STATUS canWakeUpIf_init(void)
{
    return canWakeUpTypes[CAN_WAKE_UP_USED_DEVICE]->init();
}

CAN_STATUS canWakeUpIf_setWakeUpMessage(CANMessageObjectConfig* config, uint32_t baudrate, bool dataMask, uint8_t dlc, const uint8_t* dataMaskData)
{
    return canWakeUpTypes[CAN_WAKE_UP_USED_DEVICE]->setWakeUpMessage(config, baudrate, dataMask, dlc, dataMaskData);
}

CAN_STATUS canWakeUpIf_getWakeUpMessage(CANMessageObjectConfig* config, uint32_t* baudrate, bool* dataMask, uint8_t* dlc, uint8_t* dataMaskData)
{
    return canWakeUpTypes[CAN_WAKE_UP_USED_DEVICE]->getWakeUpMessage(config, baudrate, dataMask, dlc, dataMaskData);
}

CAN_STATUS canWakeUpIf_setPowerMode(CANWakeUp_Mode newMode)
{
    return canWakeUpTypes[CAN_WAKE_UP_USED_DEVICE]->setPowerMode(newMode);
}

CAN_STATUS canWakeUpIf_getPowerMode(CANWakeUp_Mode* mode)
{
    return canWakeUpTypes[CAN_WAKE_UP_USED_DEVICE]->getPowerMode(mode);
}

CAN_STATUS canWakeUpIf_getDiagnostic(CANWakeUp_DiagnosisRegister* diagnosis)
{
    return canWakeUpTypes[CAN_WAKE_UP_USED_DEVICE]->getDiagnostic(diagnosis);
}

CAN_STATUS canWakeUpIf_getIdentificationNr(uint8_t* number)
{
    return canWakeUpTypes[CAN_WAKE_UP_USED_DEVICE]->getIdentificationNumber(number);
}
