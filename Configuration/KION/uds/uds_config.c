/**
 * @file     uds_config.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "uds.h"
#include "uds_config.h"
#include "uds_routineControl.h"
#include "uds_securityAccess.h"
#include "uds_readData.h"
#include "uds_diagnosticSessionControl.h"
#include "uds_diagnosticSessionControl_config.h"
#include "uds_communicationControl.h"
#include "uds_controlDtcSetting.h"
#include "uds_clearDiagnosticInformation.h"
#include "uds_ecuReset.h"
#include "uds_ioControl.h"
#include "uds_writeData.h"
#include "uds_dtc.h"
#include "task_cfg.h"
#include "KBSInterface.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

// @req CB-73521 CB-73578 CB-73601 CB-73602
// clang-format off
const UDS_Service udsServiceTable[] =
{
/*  SID ----------------------------------------- Function pointer --------------- Session ----------------- Session length ---------------- Security Level ---------------- */
    {UDS_SID_TESTER_PRESENT,                      uds_testerPresent,               NULL,                     NULL,                           0                               },
    {UDS_SID_DIAGNOSTIC_SESSION_CONTROL,          uds_diagnosticSessionControl,    NULL,                     NULL,                           0                               },
    {UDS_SID_SECURITY_ACCESS,                     uds_securityAccess,              uds_extendedSessionList,  &UDS_EXTENDEDSESSIONLIST_SIZE,  0                               },
    {UDS_SID_ECU_RESET,                           uds_ecuReset,                    uds_extendedSessionList,  &UDS_EXTENDEDSESSIONLIST_SIZE,  (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2))},
    {UDS_SID_CLEAR_DIAGNOSTIC_INFORMATION,        uds_clearDiagnosticInformation,  uds_extendedSessionList,  &UDS_EXTENDEDSESSIONLIST_SIZE,  (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2))},
    {UDS_SID_CONTROL_DTC_SETTING,                 uds_controlDtcSetting,           uds_extendedSessionList,  &UDS_EXTENDEDSESSIONLIST_SIZE,  (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2))},
    {UDS_SID_COMMUNICATION_CONTROL,               uds_communicationControl,        uds_extendedSessionList,  &UDS_EXTENDEDSESSIONLIST_SIZE,  (BIT(UDS_SECURITY_ACCESS_LEVEL_1) | BIT(UDS_SECURITY_ACCESS_LEVEL_2))},
    #if !defined(SIL_DEBUG)
    {UDS_SID_ROUTINE_CONTROL,                     uds_routineControl,              uds_extendedSessionList,  &UDS_EXTENDEDSESSIONLIST_SIZE,  0                               },
    #else
    {UDS_SID_ROUTINE_CONTROL,                     uds_routineControl,              NULL,                     NULL,                           0                               },
    #endif
    {UDS_SID_READ_DATA_BY_IDENTIFIER,             uds_readDataByIdentifier,        NULL,                     NULL,                           0                               },
    {UDS_SID_WRITE_DATA_BY_IDENTIFIER,            uds_writeDataByIdentifier,       NULL,                     NULL,                           0                               },
    {UDS_SID_INPUT_OUTPUT_CONTROL_BY_IDENTIFIER,  uds_ioControl,                   uds_extendedSessionList,  &UDS_EXTENDEDSESSIONLIST_SIZE,  0                               },
    {UDS_SID_READ_DTC_INFORMATION,				  uds_dtc,						   NULL, 				   	 NULL, 							 0		    				     }
};
// clang-format on
const uint32_t UDS_SERVICE_TABLE_SIZE = sizeof(udsServiceTable) / sizeof(UDS_Service);

extern CANMessageObject kionCANTransmitlib_udsHandler;

extern MEM_ISOTP isotp_sock socket_uds;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

uint8_t uds_canSend(const CANMessage* message)
{
#if ISOTP_INTER_CAN == CONFIG_ENABLED
    if((masterType_get() == MASTER_TYPE_SYSTEM) && send_on_customer_can)
    {
        canIf_send(UDS_SEND_CUSTOMER, message->dlc, message->data);
    }
    else
    {
        canIf_send(interCANTransmitStrPM_SyM_UDSHandler, message->dlc, message->data);
    }
#else
    canIf_send(UDS_SEND_CUSTOMER, message->dlc, message->data);
#endif

    return 0;
}
