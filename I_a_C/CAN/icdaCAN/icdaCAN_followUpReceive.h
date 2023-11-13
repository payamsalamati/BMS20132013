/**
 *
 * @file icdaCAN_followUpReceive.h
 * @created on  Mon Nov 16 10:15:18 CET 2020
 * @brief This module provides an interface to the data interface and other functions
             for the received CAN messages
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @details
 * @par Global variables
 */

#pragma once

//******************* INCLUDES ********************************//
#include <stdint.h>

/**
 * @brief interface function for ICDA_BMS_Result CAN message
 * @details
 * @param data Message data
 * @param msg CAN frame data (id, dlc, etc.)
 * @par Global variables
 */
void icdaCAN_followUpICDA_BMS_Result(const CANMessage* msg);
/**
 * @brief interface function for ICDA_BMS_Response CAN message
 * @details
 * @param data Message data
 * @param msg CAN frame data (id, dlc, etc.)
 * @par Global variables
 */
void icdaCAN_followUpICDA_BMS_Response(const CANMessage* msg);
