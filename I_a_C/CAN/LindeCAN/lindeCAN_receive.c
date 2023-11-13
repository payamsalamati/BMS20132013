/**
 *
 * @file lindeCAN_receive.c
 * @modulenumber 0x0D
 * @author Generated File with DPCParser release-1.3.4 Commit 1347995
 * @created on Thu Mar 30 17:16:56 CEST 2023
 * @brief This module write data from the CAN messages into the
             structs, corresponding to the message ID
 * @copyright Futavis GmbH, Aachen 2023 - alle Rechte vorbehalten
 * @details Generated from file "lindeCAN.sym"
 * @par Global variables
 * - lindemodule_control (network management (NMT))
 * - lindeTraction_SDOreq_LiIoBMS (SDO Rx, node 0x0D (LIB with Linde BMZ protocol))
 * - lindeTraction_PDO4 (PDO 4 (Tx), node 0x01 (KMC) (for LIB with Linde BMZ protocol))
 * - lindeTimeStamp (Linde proprietary timestamp message (for LIB with Linde BMZ protocol))
 * - lindeSYNC (CANopen SYNC message (for LIB with Linde BMZ protocol))
 * - lindeLiIoCharger_SDOreq_LiIoBMS (SDO Rx, node 0x5D (LIB with Linde BMZ protocol), SDO clients: OBC, EXC)
 * - lindeLiIoCharger_PDO1 (PDO 1 (Tx), node 0x5D (OBC, EXC))
 * @par changes
 * - first creation Thu Mar 30 17:16:56 CEST 2023
 */

//******************* INCLUDES ********************************//
#include "lindeCAN.h"
#include "lindeCAN_sendReceive.h"
#include "osIf.h"
#include "dem.h"

/* ---------------------------------  VARIABLE DEFINITIONS  -------------------------------- */
/**
 * @var highestID
 * @brief this variable saves the highest received sending ID
 * Initialization of the highest ID
 */
//MEM_CAN uint8_t highestID = 0;


/* ---------------------------------  FUNCTION DEFINITIONS  -------------------------------- */

#define SIGN_EXTEND(x, bitsize) ((x ^ (1 << (bitsize - 1))) - (1 << (bitsize - 1)))

void lindeCAN_receive(const CANMessage* msg)
{
    switch(msg->id)
    {
        case LINDE_CAN_ID_MODULE_CONTROL:
        {
            LINDE_MODULE_CONTROL_t data = { 0 };

            data.canopen_nmt_command_specifier = (uint8_t)(((uint64_t)msg->data[0]) >> 0) & 0b11111111u;
            data.canopen_node_id               = (uint8_t)(((uint64_t)msg->data[1]) >> 0) & 0b11111111u;

            lindeCAN_followUpmodule_control(&data, msg);
        }
        break;
        case LINDE_CAN_ID_TRACTION_SDOREQ_LIIOBMS:
        {
            LINDE_TRACTION_SDOREQ_LIIOBMS_t data = { 0 };

            data.Traction_SDOreq_LiIoBMS_Data = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.Traction_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[1]) << 8u;
            data.Traction_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[2]) << 16u;
            data.Traction_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[3]) << 24u;
            data.Traction_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[4]) << 32u;
            data.Traction_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[5]) << 40u;
            data.Traction_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[6]) << 48u;
            data.Traction_SDOreq_LiIoBMS_Data |= (uint64_t)(msg->data[7] & 0b11111111) << 56u;


            lindeCAN_followUpTraction_SDOreq_LiIoBMS(&data, msg);
        }
        break;
        case LINDE_CAN_ID_TRACTION_PDO4:
        {
            LINDE_TRACTION_PDO4_t data = { 0 };

            data.TruckWorkTime = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.TruckWorkTime |= ((uint64_t)msg->data[1]) << 8u;
            data.TruckWorkTime |= ((uint64_t)msg->data[2]) << 16u;
            data.TruckWorkTime |= (uint64_t)(msg->data[3] & 0b11111111) << 24u;


            lindeCAN_followUpTraction_PDO4(&data, msg);
        }
        break;
        case LINDE_CAN_ID_TIMESTAMP:
        {
            LINDE_TIMESTAMP_t data = { 0 };

            data.DateTime = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.DateTime |= ((uint64_t)msg->data[1]) << 8u;
            data.DateTime |= ((uint64_t)msg->data[2]) << 16u;
            data.DateTime |= (uint64_t)(msg->data[3] & 0b11111111) << 24u;


            lindeCAN_followUpTimeStamp(&data, msg);
        }
        break;
        case LINDE_CAN_ID_SYNC:
        {
            LINDE_SYNC_t data = { 0 };


            lindeCAN_followUpSYNC(&data, msg);
        }
        break;
        case LINDE_CAN_ID_LIIOCHARGER_SDOREQ_LIIOBMS:
        {
            LINDE_LIIOCHARGER_SDOREQ_LIIOBMS_t data = { 0 };

            data.LiIoCharger_SDOreq_LiIoBMS_Data = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.LiIoCharger_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[1]) << 8u;
            data.LiIoCharger_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[2]) << 16u;
            data.LiIoCharger_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[3]) << 24u;
            data.LiIoCharger_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[4]) << 32u;
            data.LiIoCharger_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[5]) << 40u;
            data.LiIoCharger_SDOreq_LiIoBMS_Data |= ((uint64_t)msg->data[6]) << 48u;
            data.LiIoCharger_SDOreq_LiIoBMS_Data |= (uint64_t)(msg->data[7] & 0b11111111) << 56u;


            lindeCAN_followUpLiIoCharger_SDOreq_LiIoBMS(&data, msg);
        }
        break;
        case LINDE_CAN_ID_LIIOCHARGER_PDO1:
        {
            LINDE_LIIOCHARGER_PDO1_t data = { 0 };

            data.LiIoCharger_ChargingCurrent = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.LiIoCharger_ChargingCurrent |= (uint64_t)(msg->data[1] & 0b11111111) << 8u;

            data.LiIoCharger_ChargingCurrent *= 0.025;

            data.LiIoCharger_ChargingVoltage = (uint8_t)((uint64_t)msg->data[2]) >> 0u;
            data.LiIoCharger_ChargingVoltage |= (uint64_t)(msg->data[3] & 0b11111111) << 8u;

            data.LiIoCharger_ChargingVoltage *= 0.025;

            data.LiIoCharger_WorkingHours = (uint8_t)((uint64_t)msg->data[4]) >> 0u;
            data.LiIoCharger_WorkingHours |= ((uint64_t)msg->data[5]) << 8u;
            data.LiIoCharger_WorkingHours |= ((uint64_t)msg->data[6]) << 16u;
            data.LiIoCharger_WorkingHours |= (uint64_t)(msg->data[7] & 0b11111111) << 24u;


            lindeCAN_followUpLiIoCharger_PDO1(&data, msg);
        }
        break;
        default:
            break;
    }
}
