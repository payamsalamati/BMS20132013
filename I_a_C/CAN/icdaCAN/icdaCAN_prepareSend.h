/**
 *
 * @file icdaCAN_prepareSend.h
 * @modulenumber 0x0D
 *
 * @author Generated File with DPCParser NO_TAG? Commit 12345678
 * @created on Fri Feb 11 15:37:19 CET 2022
 * @brief This module write data from the data interface into the
             CAN messages
 * @copyright Futavis GmbH, Aachen 2022 - alle Rechte vorbehalten
 * @details Generated from file "icda.sym"
 * @par Global variables
 * @par changes
 * - first creation Fri Feb 11 15:37:19 CET 2022
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//
#include "stdint.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
/**
 * @brief prepare the BMS_ICDA_Request CAN message
 * @details
 * @par Global variables
 */
void icdaCAN_prepareBMS_ICDA_Request(ICDA_BMS_ICDA_REQUEST_t* icda_bms_icda_request);
