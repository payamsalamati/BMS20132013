/**
 *
 * @file kioninterCAN_receive.c
 * @created on Mon Nov 16 10:15:18 CET 2020
 * @brief This module write data from the CAN messages into the
             structs, corresponding to the message ID
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 * - kioninterCPS_BMS_UDS_RESP ()
 * - kioninterCH_CPS_WakeUp ()
 * - kioninterCPS_VEHICLE_UDS_RESP ()
 * - kioninterCPS_BMS_Emergency ()
 * - kioninterCPS_Heartbeat ()
 * - kioninterCPS_BMS_SDO_RESP ()
 * - kioninterCPS_BMS_PDO_TX2 ()
 * - kioninterCPS_BMS_PDO_TX3 ()
 * - kioninterCPS_BMS_PDO_TX1 ()
 * - kioninterICDA_BMS_Result ()
 * - kioninterICDA_BMS_Response ()
 */

//******************* INCLUDES ********************************//
#include "kioninterCAN.h"
#include "kioninterCAN_sendReceive.h"
#include "osIf.h"
#include "dem.h"
#include "debug.h"

#if defined(SYNC_AFE_AND_ICDA_MEASUREMENTS)
#include "synchronizedMeasurements.h"
#endif

/* ---------------------------------  VARIABLE DEFINITIONS  -------------------------------- */
/**
 * @var highestID
 * @brief this variable saves the highest received sending ID
 * Initialization of the highest ID
 */
//MEM_CAN uint8_t highestID = 0;

// Array of last rolling counters per Message
MEM_CAN static uint8_t ctRollLastValue[4];
// Array of flags if last received rolling counter was wrong
MEM_CAN static bool ctRollLastValueError[4];
// Position of message-specific last rolling counter (and flag) in array
#define ctRollPosID0x282 0
#define ctRollPosID0x382 1
#define ctRollPosID0x182 2
#define ctRollPosID0x502 3
// Array of flags if last received crc was wrong
MEM_CAN static bool crcLastValueError[3];
#define crcPosID0x282 0
#define crcPosID0x382 1
#define crcPosID0x182 2

/* ---------------------------------  FUNCTION DEFINITIONS  -------------------------------- */

#define SIGN_EXTEND(x, bitsize) ((x ^ (1 << (bitsize - 1))) - (1 << (bitsize - 1)))
void kioninterCAN_receive(CANMessage* msg)
{

    uint8_t array[MAX_MESSAGE_DLC] = { 0 };

    switch(msg->id)
    {
        case 0x6E6:
        {
            KIONINTER_CPS_BMS_UDS_RESP_t data = { 0 };
            data.CPS_UDSData                  = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.CPS_UDSData |= ((uint64_t)msg->data[1]) << 8u;
            data.CPS_UDSData |= ((uint64_t)msg->data[2]) << 16u;
            data.CPS_UDSData |= ((uint64_t)msg->data[3]) << 24u;
            data.CPS_UDSData |= ((uint64_t)msg->data[4]) << 32u;
            data.CPS_UDSData |= ((uint64_t)msg->data[5]) << 40u;
            data.CPS_UDSData |= ((uint64_t)msg->data[6]) << 48u;
            data.CPS_UDSData |= (uint64_t)(msg->data[7] & 0b11111111) << 56u;


            kioninterCAN_followUpCPS_BMS_UDS_RESP(&data, msg);
        }
        break;
        case 0x1FFFFFFF:
        {
            KIONINTER_CH_CPS_WAKEUP_t data = { 0 };
            data.CH_Data                   = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.CH_Data |= ((uint64_t)msg->data[1]) << 8u;
            data.CH_Data |= ((uint64_t)msg->data[2]) << 16u;
            data.CH_Data |= ((uint64_t)msg->data[3]) << 24u;
            data.CH_Data |= ((uint64_t)msg->data[4]) << 32u;
            data.CH_Data |= ((uint64_t)msg->data[5]) << 40u;
            data.CH_Data |= ((uint64_t)msg->data[6]) << 48u;
            data.CH_Data |= (uint64_t)(msg->data[7] & 0b11111111) << 56u;

            kioninterCAN_followUpCH_CPS_WakeUp(&data, msg);
        }
        break;
        case 0x6DF:
        {
            kioninterCAN_followUpCPS_VEHICLE_UDS_RESP(msg);
        }
        break;
        case 0x82:
        {
            KIONINTER_CPS_BMS_EMERGENCY_t data = { 0 };
            data.CPS_EMCY_ErrorCode            = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.CPS_EMCY_ErrorCode |= (uint64_t)(msg->data[1] & 0b11111111) << 8u;

            data.CPS_EMCY_ErrorRegister = (uint8_t)(((uint64_t)msg->data[2]) >> 0) & 0b11111111u;
            data.CPS_UDS_DTC            = (uint8_t)((uint32_t)msg->data[3]) >> 0u;
            data.CPS_UDS_DTC |= ((uint32_t)msg->data[4]) << 8u;
            data.CPS_UDS_DTC |= ((uint32_t)msg->data[5]) << 16u;

            if(data.CPS_EMCY_ErrorCode == 4096u)
            {
                dem_reportFaultFromApp((DEM_FaultCode)data.CPS_UDS_DTC);
            }
            else if(data.CPS_EMCY_ErrorCode == 0u)
            {
                dem_clearFaultFromApp((DEM_FaultCode)data.CPS_UDS_DTC);
            }
            else
            {
                //do nothing
            }

            kioninterCAN_followUpCPS_BMS_Emergency(&data, msg);
        }
        break;
        case 0x702:
        {
            KIONINTER_CPS_HEARTBEAT_t data = { 0 };
            data.CPS_HBState               = (uint8_t)(((uint64_t)msg->data[0]) >> 0) & 0b11111111u;

            kioninterCAN_followUpCPS_Heartbeat(&data, msg);
        }
        break;
        case 0x582:
        {
            KIONINTER_CPS_BMS_SDO_RESP_t data = { 0 };
            data.CPS_SDO_RX_Data              = (uint8_t)(((uint64_t)msg->data[0]) >> 0) & 0b11111111u;

            kioninterCAN_followUpCPS_BMS_SDO_RESP(&data, msg);
        }
        break;
        case 0x282:
        {
            KIONINTER_CPS_BMS_PDO_TX2_t data = { 0 };
            data.CPS_CPSout_I                = (uint8_t)((uint64_t)msg->data[0]) >> 0u;
            data.CPS_CPSout_I |= (uint64_t)(msg->data[1] & 0b11111111) << 8u;

            data.CPS_Temp1CPSout = (uint8_t)((msg->data[2]) >> 0) & 0b11111111u;
            data.CPS_Temp1CPSout += -40.0;
            data.CPS_Temp2CPSout = (uint8_t)((msg->data[3]) >> 0) & 0b11111111u;
            data.CPS_Temp2CPSout += -40.0;

            data.CPS_TX2_Counter  = (uint8_t)(((uint64_t)msg->data[5]) >> 4) & 0b1111u;
            data.CPS_TX2_Checksum = (uint8_t)((uint64_t)msg->data[6]) >> 0u;
            data.CPS_TX2_Checksum |= (uint64_t)(msg->data[7] & 0b11111111) << 8u;


            if(data.CPS_TX2_Counter != (ctRollLastValue[ctRollPosID0x282] + 1) % 16)
            {
                ctRollLastValue[ctRollPosID0x282] = data.CPS_TX2_Counter;
                dem_reportFaultFromApp(DTC_CAN_CT_ROLL_INCORRECT);
                ctRollLastValueError[ctRollPosID0x282] = true;
                break;
            }
            else
            {
                ctRollLastValue[ctRollPosID0x282] = data.CPS_TX2_Counter;
                if(ctRollLastValueError[ctRollPosID0x282] == true)
                {
                    dem_clearFaultFromApp(DTC_CAN_CT_ROLL_INCORRECT);
                    ctRollLastValueError[ctRollPosID0x282] = false;
                }
            }

            help_data2CRC_KION(msg->id, msg->data, array, MESSAGE_DLC_6);
            if(data.CPS_TX2_Checksum != crc16_calculation_KION(array, MESSAGE_DLC_6 + 2u))
            {
                dem_reportFaultFromApp(DTC_CAN_CRC_INCORRECT);
                crcLastValueError[crcPosID0x282] = true;
                break;
            }
            else if(crcLastValueError[crcPosID0x282] == true)
            {
                dem_clearFaultFromApp(DTC_CAN_CRC_INCORRECT);
                crcLastValueError[crcPosID0x282] = false;
            }
            else
            {
                // crc ok
            }
            kioninterCAN_followUpCPS_BMS_PDO_TX2(&data, msg);
        }
        break;
        case 0x382:
        {
            KIONINTER_CPS_BMS_PDO_TX3_t data = { 0 };
            data.CPS_VoltageInput            = (uint8_t)((uint16_t)msg->data[0]) << 0u;
            data.CPS_VoltageInput |= (uint16_t)(msg->data[1]) << 8u;

            data.CPS_VoltageInput *= 0.025;

            data.CPS_CPSoutVoltage = (uint8_t)((uint16_t)msg->data[2]) << 0u;
            data.CPS_CPSoutVoltage |= (uint16_t)(msg->data[3]) << 8u;

            data.CPS_CPSoutVoltage *= 0.025;

            data.CPS_TX3_Counter  = (uint8_t)(((uint64_t)msg->data[5]) >> 4) & 0b1111u;
            data.CPS_TX3_Checksum = (uint8_t)((uint64_t)msg->data[6]) >> 0u;
            data.CPS_TX3_Checksum |= (uint64_t)(msg->data[7] & 0b11111111) << 8u;


            if(data.CPS_TX3_Counter != (ctRollLastValue[ctRollPosID0x382] + 1) % 16)
            {
                ctRollLastValue[ctRollPosID0x382] = data.CPS_TX3_Counter;
                dem_reportFaultFromApp(DTC_CAN_CT_ROLL_INCORRECT);
                ctRollLastValueError[ctRollPosID0x382] = true;
                break;
            }
            else
            {
                ctRollLastValue[ctRollPosID0x382] = data.CPS_TX3_Counter;
                if(ctRollLastValueError[ctRollPosID0x382] == true)
                {
                    dem_clearFaultFromApp(DTC_CAN_CT_ROLL_INCORRECT);
                    ctRollLastValueError[ctRollPosID0x382] = false;
                }
            }

            help_data2CRC_KION(msg->id, msg->data, array, MESSAGE_DLC_6);
            if(data.CPS_TX3_Checksum != crc16_calculation_KION(array, MESSAGE_DLC_6 + 2u))
            {
                dem_reportFaultFromApp(DTC_CAN_CRC_INCORRECT);
                crcLastValueError[crcPosID0x382] = true;
                break;
            }
            else if(crcLastValueError[crcPosID0x382] == true)
            {
                dem_clearFaultFromApp(DTC_CAN_CRC_INCORRECT);
                crcLastValueError[crcPosID0x382] = false;
            }
            else
            {
                // crc ok
            }
            kioninterCAN_followUpCPS_BMS_PDO_TX3(&data, msg);
        }
        break;
        case 0x182:
        {
            KIONINTER_CPS_BMS_PDO_TX1_t data = { 0 };
            data.CPS_CPSoutBoost             = (uint8_t)(((uint64_t)msg->data[1]) >> 4) & 0b11u;
            data.CPS_CPSout                  = (uint8_t)(((uint64_t)msg->data[1]) >> 6) & 0b11u;
            data.CPS_StartupAfterPowerdown   = (uint8_t)(((uint64_t)msg->data[2]) >> 4) & 0b1u;
            data.CPS_Emergency               = (uint8_t)(((uint64_t)msg->data[2]) >> 5) & 0b1u;
            data.CPS_CPSoutLimitation        = (uint8_t)(((uint64_t)msg->data[2]) >> 7) & 0b1u;
            data.CPS_Error                   = (uint8_t)((uint64_t)msg->data[3]) >> 0u;
            data.CPS_Error |= (uint64_t)(msg->data[4] & 0b11111111) << 8u;

            data.CPS_TX1_Counter  = (uint8_t)(((uint64_t)msg->data[5]) >> 4) & 0b1111u;
            data.CPS_TX1_Checksum = (uint8_t)((uint64_t)msg->data[6]) >> 0u;
            data.CPS_TX1_Checksum |= (uint64_t)(msg->data[7] & 0b11111111) << 8u;


            if(data.CPS_TX1_Counter != (ctRollLastValue[ctRollPosID0x182] + 1) % 16)
            {
                ctRollLastValue[ctRollPosID0x182] = data.CPS_TX1_Counter;
                dem_reportFaultFromApp(DTC_CAN_CT_ROLL_INCORRECT);
                ctRollLastValueError[ctRollPosID0x182] = true;
                break;
            }
            else
            {
                ctRollLastValue[ctRollPosID0x182] = data.CPS_TX1_Counter;
                if(ctRollLastValueError[ctRollPosID0x182] == true)
                {
                    dem_clearFaultFromApp(DTC_CAN_CT_ROLL_INCORRECT);
                    ctRollLastValueError[ctRollPosID0x182] = false;
                }
            }

            help_data2CRC_KION(msg->id, msg->data, array, MESSAGE_DLC_6);
            if(data.CPS_TX1_Checksum != crc16_calculation_KION(array, MESSAGE_DLC_6 + 2u))
            {
                dem_reportFaultFromApp(DTC_CAN_CRC_INCORRECT);
                crcLastValueError[crcPosID0x182] = true;
                break;
            }
            else if(crcLastValueError[crcPosID0x182] == true)
            {
                dem_clearFaultFromApp(DTC_CAN_CRC_INCORRECT);
                crcLastValueError[crcPosID0x182] = false;
            }
            else
            {
                // crc ok
            }
            kioninterCAN_followUpCPS_BMS_PDO_TX1(&data, msg);
        }
        break;
        case 0x502:
        {
            kioninterCAN_followUpICDA_BMS_Result(msg, false);
        }
        break;
#if defined(SYNC_AFE_AND_ICDA_MEASUREMENTS)
        case SYNC_ICDA_RESULT_MSG_ID:
        {
            kioninterCAN_followUpICDA_BMS_Result(msg, true);
        }
#endif
        break;
        default:
            break;
    }
}
