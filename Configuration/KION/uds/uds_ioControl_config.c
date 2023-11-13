/**
 * @file     uds_ioControl_config.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * <b>Dependencies</b>
 *  - which other modules are needed by this module and why
 *
 * <b>Description</b>
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//


#include "uds_ioControl/uds_ioControl.h"
#include "uds_protected.h"


//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

//static void relay0(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response);
//static void relay1(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response);
//static void gpio0(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response);
//static void gpio1(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response);
//static void gpio2(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response);
//static void gpio3(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response);

//static void idOut(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response);
//static void codingOut(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response);
//static void powerHold(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response);

//***************************************************************************//
//************************** VARIABLE DECLARATIONS **************************//
//***************************************************************************//

const UDSIOControlTableEntry udsIOControlTable[] = {
    //	{0x0000u, relay0, 		1, BIT(UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT), BIT(UDS_SECURITY_LEVEL_INTERNAL)},
    //	{0x0001u, relay1, 		1, BIT(UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT), BIT(UDS_SECURITY_LEVEL_INTERNAL)},
    //	{0x0002u, gpio0, 		1, BIT(UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT), BIT(UDS_SECURITY_LEVEL_INTERNAL)},
    //	{0x0003u, gpio1, 		1, BIT(UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT), BIT(UDS_SECURITY_LEVEL_INTERNAL)},
    //	{0x0004u, gpio2, 		1, BIT(UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT), BIT(UDS_SECURITY_LEVEL_INTERNAL)},
    //	{0x0005u, gpio3, 		1, BIT(UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT), BIT(UDS_SECURITY_LEVEL_INTERNAL)},
    //	{0x0006u, idOut, 		1, BIT(UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT), BIT(UDS_SECURITY_LEVEL_INTERNAL)},
    //	{0x0007u, codingOut, 	1, BIT(UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT), BIT(UDS_SECURITY_LEVEL_INTERNAL)},
    //	{0x0008u, powerHold, 	1, BIT(UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT), BIT(UDS_SECURITY_LEVEL_INTERNAL)},

};
const uint16_t UDS_IO_CONTROL_TABLE_SIZE = sizeof(udsIOControlTable) / sizeof(UDSIOControlTableEntry);

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

//static void relay0(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response)
//{
//	switch(param)
//	{
//	case UDS_IO_CONTROL_PARAMETER_RETURN_CONTROL_TO_ECU:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_RESET_TO_DEFAULT:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_FREEZE_CURRENT_STATE:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT:
//		ioIf_setRelai(0, (IO_VAL_t)controlState[0]);
//		response[0] = controlState[0];
//		break;
//	default:
//		break;
//	}
//}
//
//static void relay1(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response)
//{
//	switch(param)
//	{
//	case UDS_IO_CONTROL_PARAMETER_RETURN_CONTROL_TO_ECU:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_RESET_TO_DEFAULT:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_FREEZE_CURRENT_STATE:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT:
//		ioIf_setRelai(1, (IO_VAL_t)controlState[0]);
//		response[0] = controlState[0];
//		break;
//	default:
//		break;
//	}
//}
//
//static void gpio0(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response)
//{
//	switch(param)
//	{
//	case UDS_IO_CONTROL_PARAMETER_RETURN_CONTROL_TO_ECU:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_RESET_TO_DEFAULT:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_FREEZE_CURRENT_STATE:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT:
//	    io_setExt_Output_1((IO_VAL_t)controlState[0]);
//		response[0] = controlState[0];
//		break;
//	default:
//		break;
//	}
//}
//
//static void gpio1(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response)
//{
//	switch(param)
//	{
//	case UDS_IO_CONTROL_PARAMETER_RETURN_CONTROL_TO_ECU:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_RESET_TO_DEFAULT:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_FREEZE_CURRENT_STATE:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT:
//	    io_setExt_Output_2((IO_VAL_t)controlState[0]);
//		response[0] = controlState[0];
//		break;
//	default:
//		break;
//	}
//}
//
//static void gpio2(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response)
//{
//	switch(param)
//	{
//	case UDS_IO_CONTROL_PARAMETER_RETURN_CONTROL_TO_ECU:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_RESET_TO_DEFAULT:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_FREEZE_CURRENT_STATE:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT:
//	    io_setExt_Output_3((IO_VAL_t)controlState[0]);
//		response[0] = controlState[0];
//		break;
//	default:
//		break;
//	}
//}
//
//static void gpio3(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response)
//{
//	switch(param)
//	{
//	case UDS_IO_CONTROL_PARAMETER_RETURN_CONTROL_TO_ECU:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_RESET_TO_DEFAULT:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_FREEZE_CURRENT_STATE:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT:
//	    io_setExt_Output_4((IO_VAL_t)controlState[0]);
//		response[0] = controlState[0];
//		break;
//	default:
//		break;
//	}
//}
//
//static void idOut(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response)
//{
//	switch(param)
//	{
//	case UDS_IO_CONTROL_PARAMETER_RETURN_CONTROL_TO_ECU:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_RESET_TO_DEFAULT:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_FREEZE_CURRENT_STATE:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT:
//		io_setIdOut((IO_VAL_t)controlState[0]);
//		response[0] = controlState[0];
//		break;
//	default:
//		break;
//	}
//}
//
//static void codingOut(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response)
//{
//	switch(param)
//	{
//	case UDS_IO_CONTROL_PARAMETER_RETURN_CONTROL_TO_ECU:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_RESET_TO_DEFAULT:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_FREEZE_CURRENT_STATE:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT:
//		io_setCodingOut((IO_VAL_t)controlState[0]);
//		response[0] = controlState[0];
//		break;
//	default:
//		break;
//	}
//}
//
//static void powerHold(UDS_IOControl_Parameter param, const uint8_t* controlState, uint8_t* response)
//{
//	switch(param)
//	{
//	case UDS_IO_CONTROL_PARAMETER_RETURN_CONTROL_TO_ECU:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_RESET_TO_DEFAULT:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_FREEZE_CURRENT_STATE:
//		break;
//	case UDS_IO_CONTROL_PARAMETER_SHORT_TERM_ADJUSTMENT:
//		io_setPowerHold((IO_VAL_t)controlState[0]);
//		response[0] = controlState[0];
//		break;
//	default:
//		break;
//	}
//}
