/**
 *
 * @file kionCAN_receive.c
 * @created on Tue Feb 16 14:15:58 CET 2021
 * @brief This module write data from the CAN messages into the
             structs, corresponding to the message ID
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - kiondtu_uds (UDS requests from DTU)
 * - kiontime (time stamp (TIME))
 * - kionobc_heartbeat (heartbeat (NMT error control), node 0x51 (OBC))
 * - kionmodule_control (network management (NMT))
 * - kionlib_sdo_rx (SDO Rx, node 0x27 (LIB with KION protocol), SDO clients: KMC, OBC, EXC)
 * - kionlib_pdo_rx4 (PDO 4 (Rx), node 0x27 (LIB with KION protocol))
 * - kionlib_pdo_rx1 (PDO 1 (Rx), node 0x27 (LIB with KION protocol))
 * - kionkmc_heartbeat (heartbeat (NMT error control), node 0x01 (KMC))
 * - kionexc_heartbeat (heartbeat (NMT error control), node 0x4A (EXC))
 * - kionTimeStamp (Linde proprietary timestamp message (for LIB with Linde SAFT protocol))
 * - kionSYNC (CANopen SYNC message (for LIB with Linde BMZ protocol))
 * - kionHeartbtLiionCharger (Network Management, Error Control,  liion battery charger Heartbeat)
 * - kionDiagReqBms ()
 * - kionBmsSDOrx (CAN Open: Service data object (SDO) send by KWPC)
 */

//******************* INCLUDES ********************************//
#include "kionCAN.h"
#include "kionCAN_sendReceive.h"
#include "osIf.h"
#include "dem.h"

#include "stateFunctions.h"
#include "xcpIf.h"

/* ---------------------------------  VARIABLE DEFINITIONS  -------------------------------- */
/**
 * @var highestID
 * @brief this variable saves the highest received sending ID
 * Initialization of the highest ID
 */
//MEM_CAN uint8_t highestID = 0;


/* ---------------------------------  FUNCTION DEFINITIONS  -------------------------------- */

#define SIGN_EXTEND(x, bitsize) ((x ^ (1u << (bitsize - 1u))) - (1u << (bitsize - 1u)))
void kionCAN_receive(const CANMessage* msg)
{

    stmFct_setComOnCan(true);

    switch(msg->id)
    {
        // @req CB-75002
        case 0x680:
        {
            KION_DTU_UDS_t data  = { 0 };
            data.isotp_n_ta      = (uint8_t)(((uint64_t)msg->data[0]) >> 0) & 0b11111111u;
            data.isotp_fs        = (uint8_t)(((uint64_t)msg->data[1]) >> 0) & 0b1111u;
            data.isotp_bs        = (uint8_t)(((uint64_t)msg->data[2]) >> 0) & 0b11111111u;
            data.isotp_stmin     = (uint8_t)(((uint64_t)msg->data[3]) >> 0) & 0b11111111u;
            data.isotp_n_data_fc = (uint8_t)(((uint64_t)msg->data[4]) << 0) & 0b11111111u;
            data.isotp_n_data_fc <<= 8;
            data.isotp_n_data_fc |= (uint8_t)msg->data[5];
            data.isotp_n_data_fc <<= 8;
            data.isotp_n_data_fc |= (uint8_t)msg->data[6];
            data.isotp_n_data_fc <<= 8;
            data.isotp_n_data_fc |= ((uint64_t)msg->data[7] >> 0) & 0b11111111u;


            kionCAN_followUpdtu_uds(&data, msg);
        }
        break;
        // @req CB-74998
        case 0x100:
        {
            KION_TIME_t data            = { 0 };
            data.canopen_time_of_day_ms = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.canopen_time_of_day_ms |= ((uint64_t)msg->data[1]) << 8u;
            data.canopen_time_of_day_ms |= ((uint64_t)msg->data[2]) << 16u;
            data.canopen_time_of_day_ms |= (uint64_t)(msg->data[3] & 0b1111) << 24u;

            data.canopen_time_of_day_days = (uint8_t)((uint64_t)msg->data[4]) >> 0u;
            data.canopen_time_of_day_days |= (uint64_t)(msg->data[5] & 0b11111111) << 8u;


            kionCAN_followUptime(&data, msg);
        }
        break;
        case 0x751:
        {
            KION_OBC_HEARTBEAT_t data = { 0 };
            data.canopen_state_obc    = (uint8_t)(((uint64_t)msg->data[0]) >> 1) & 0b1111111u;

            kionCAN_followUpobc_heartbeat(&data, msg);
        }
        break;
        // @req CB-74997
        case 0x0:
        {
            KION_MODULE_CONTROL_t data         = { 0 };
            data.canopen_nmt_command_specifier = (uint8_t)(((uint64_t)msg->data[0]) >> 0) & 0b11111111u;
            data.canopen_node_id               = (uint8_t)(((uint64_t)msg->data[1]) >> 0) & 0b11111111u;

            kionCAN_followUpmodule_control(&data, msg);
        }
        break;
        // @req CB-75001
        case 0x627:
        {
            KION_LIB_SDO_RX_t data             = { 0 };
            data.canopen_sdo_size_indicator    = (uint8_t)(((uint64_t)msg->data[0]) >> 0) & 0b1u;
            data.canopen_sdo_transfer_type     = (uint8_t)(((uint64_t)msg->data[0]) >> 1) & 0b1u;
            data.canopen_sdo_number_of_bytes_2 = (uint8_t)(((uint64_t)msg->data[0]) >> 2) & 0b11u;
            data.canopen_sdo_download_index    = (uint8_t)((uint64_t)msg->data[1]) >> 0u;
            data.canopen_sdo_download_index |= (uint64_t)(msg->data[2] & 0b11111111) << 8u;

            data.canopen_sdo_download_subindex = (uint8_t)(((uint64_t)msg->data[3]) >> 0) & 0b11111111u;
            data.canopen_sdo_data              = (uint8_t)((uint64_t)msg->data[4]) >> 0u;
            data.canopen_sdo_data |= ((uint64_t)msg->data[5]) << 8u;
            data.canopen_sdo_data |= ((uint64_t)msg->data[6]) << 16u;
            data.canopen_sdo_data |= (uint64_t)(msg->data[7] & 0b11111111) << 24u;

            kionCAN_followUplib_sdo_rx(&data, msg);
        }
        break;
        // @req CB-75000 CB-91890
        case 0x527:
        {
            KION_LIB_PDO_RX4_t data = { 0 };

            // @req CB-75014
            // @req CB-75127
            data.truck_operating_hours = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.truck_operating_hours |= ((uint64_t)msg->data[1]) << 8u;
            data.truck_operating_hours |= ((uint64_t)msg->data[2]) << 16u;
            data.truck_operating_hours |= (uint64_t)(msg->data[3] & 0b11111111) << 24u;
            data.truck_operating_hours += -36000.0;

            // @req CB-75015
            data.truck_operating_hours_mode = (uint8_t)(((uint64_t)msg->data[4]) >> 0) & 0b1111u;

            // @req CB-75016
            data.lib_power_consumption_average = (uint8_t)((uint64_t)msg->data[4]) >> 4u;
            data.lib_power_consumption_average |= (uint64_t)(msg->data[5] & 0b11111111) << 4u;
            data.lib_power_consumption_average *= 0.05;
            data.lib_power_consumption_average += -102.3;


            kionCAN_followUplib_pdo_rx4(&data, msg);
        }
        break;
            // @req CB-74999
        case 0x227:
        {
            KION_LIB_PDO_RX1_t data = { 0 };
            // @req CB-75010
            data.lib_charging_current = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.lib_charging_current |= (uint64_t)(msg->data[1] & 0b11111111) << 8u;

            data.lib_charging_current *= 0.01;

            // @req CB-75011
            data.lib_charging_voltage = (uint8_t)((uint64_t)msg->data[2]) >> 0u;
            data.lib_charging_voltage |= ((uint64_t)msg->data[3]) << 8u;
            data.lib_charging_voltage |= (uint64_t)(msg->data[4] & 0b11) << 16u;

            data.lib_charging_voltage *= 0.01;

            // @req CB-75012
            data.lib_charging_power = (uint8_t)((uint64_t)msg->data[4]) >> 2u;
            data.lib_charging_power |= ((uint64_t)msg->data[5]) << 6u;
            data.lib_charging_power |= (uint64_t)(msg->data[6] & 0b11111) << 14u;


            kionCAN_followUplib_pdo_rx1(&data, msg);
        }
        break;
        // @req CB CB-75003
        case 0x701:
        {
            KION_KMC_HEARTBEAT_t data = { 0 };
            data.canopen_state_kmc    = (uint8_t)(((uint64_t)msg->data[0]) >> 1) & 0b1111111u;

            kionCAN_followUpKmc_heartbeat(&data, msg);
        }
        break;
        case 0x74A:
        {
            KION_EXC_HEARTBEAT_t data = { 0 };
            data.canopen_state_exc    = (uint8_t)(((uint64_t)msg->data[0]) >> 0) & 0b1111111u;

            kionCAN_followUpexc_heartbeat(&data, msg);
        }
        break;
        case 0xFF:
        {
            KION_TIMESTAMP_t data = { 0 };
            data.DateTime         = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.DateTime |= ((uint64_t)msg->data[1]) << 8u;
            data.DateTime |= ((uint64_t)msg->data[2]) << 16u;
            data.DateTime |= (uint64_t)(msg->data[3] & 0b11111111) << 24u;


            kionCAN_followUpTimeStamp(&data, msg);
        }
        break;
        case 0x80:
        {
            KION_SYNC_t data = { 0 };

            kionCAN_followUpSYNC(&data, msg);
        }
        break;
        case 0x705:
        {
            KION_HEARTBTLIIONCHARGER_t data = { 0 };
            data.stateLiionCharger          = (uint8_t)(((uint64_t)msg->data[0]) >> 0) & 0b1111111u;

            kionCAN_followUpHeartbtLiionCharger(&data, msg);
        }
        break;
        case 0x78D:
        {
            KION_DIAGREQBMS_t data = { 0 };
            data.BmsRqPCI          = (uint8_t)(((uint64_t)msg->data[0]) >> 0) & 0b11111111u;
            data.BmsRqData         = (uint8_t)((uint64_t)msg->data[1]) >> 0u;
            data.BmsRqData |= ((uint64_t)msg->data[2]) << 8u;
            data.BmsRqData |= ((uint64_t)msg->data[3]) << 16u;
            data.BmsRqData |= ((uint64_t)msg->data[4]) << 24u;
            data.BmsRqData |= ((uint64_t)msg->data[5]) << 32u;
            data.BmsRqData |= ((uint64_t)msg->data[6]) << 40u;
            data.BmsRqData |= (uint64_t)(msg->data[7] & 0b11111111) << 48u;


            kionCAN_followUpDiagReqBms(&data, msg);
        }
        break;
        // @req CB-18850
        case 0x1CFF27FD:
        {
            xcpIf_receive(msg);
        }
        break;
        default:
            break;
    }
}
