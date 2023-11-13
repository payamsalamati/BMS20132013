/**
 * @file     can_TMS570LS_config.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 */

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "TMS570/can_TMS570LS.h"
#include "can_config.h"
#include "debug.h"
//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/

#define CAN_TMS570LS_FREQUNECY 60000000  // Hz

//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/

const CAN_DeviceConfig can_TMS570LS_deviceConfig = {
    .nDevices        = 1,
    .nNodes          = CAN_TMS570LS_NUMBER_OF_NODES,
    .nMessageObjects = CAN_TMS570LS_NUMBER_OF_MESSAGE_OBJECTS,
};

const CANNodeConfig can_TMS570LS_Node1 = {
    .alertISRHandler          = NULL,
    .receiveISRHandler        = NULL,
    .transmitISRHandler       = NULL,
    .baudrate                 = 500,
    .canFrequency             = CAN_TMS570LS_FREQUNECY,
    .node                     = (CANNode)CAN_NODE_0,
    .samplePoint              = 75,
    .synchronizationJumpWidth = 2,
};

const CANNodeConfig can_TMS570LS_Node2 = {
    .alertISRHandler          = NULL,
    .receiveISRHandler        = NULL,
    .transmitISRHandler       = NULL,
    .baudrate                 = 500,
    .canFrequency             = CAN_TMS570LS_FREQUNECY,
    .node                     = (CANNode)CAN_NODE_1,
    .samplePoint              = 75,
    .synchronizationJumpWidth = 2,
};

const CANNodeConfig can_TMS570LS_Node3 = {
    .alertISRHandler          = NULL,
    .receiveISRHandler        = NULL,
    .transmitISRHandler       = NULL,
    .baudrate                 = 500,
    .canFrequency             = CAN_TMS570LS_FREQUNECY,
    .node                     = (CANNode)CAN_NODE_2,
    .samplePoint              = 75,
    .synchronizationJumpWidth = 2,
};

const CANNodeConfig* const can_TMS570LS_nodeConfigs[] = {
    &can_TMS570LS_Node1,
    &can_TMS570LS_Node2,
    &can_TMS570LS_Node3,
};

const uint8_t can_TMS570LS_numberOfNodes = sizeof(can_TMS570LS_nodeConfigs) / sizeof(CANNodeConfig*);

//***************************************************************************/
//************************** PRIVATE FUNCTION DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DEFINITIONS *******************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DEFINITIONS * ******************/
//***************************************************************************/
