/**
 * @file ioFunctions_config.c
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

#include "ioFunctions.h"
#include <stdint.h>
#include "task_cfg.h"
#include "sbcIf.h"
#include "ioIf_signals.h"
//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//
MEM_IO IOState extOut1;

const IOConfig outputDataConfigTable[] = {
    { Ext_Output_1, &extOut1, NULL, io_setExt_Output_1 },
};
const uint8_t OUTPUTDATACONFIGTABLE_SIZE = sizeof(outputDataConfigTable) / sizeof(IOConfig);


MEM_IO IOState butEn;

const IOConfig inputDataConfigTable[] = {
    { BUTTON_ENABLE, &butEn, sbcIf_getButton_Enable, NULL },
};
const uint8_t INPUTDATACONFIGTABLE_SIZE = sizeof(inputDataConfigTable) / sizeof(IOConfig);


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
