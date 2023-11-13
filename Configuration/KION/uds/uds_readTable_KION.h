/**
 * @file uds_routineControl_config.h
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief Configuration for uds routine control.
 */

#pragma once

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include <stdint.h>

//***************************************************************************/
//************************** PUBLIC TYPEDEFS ********************************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC VARIABLE DEFINITIONS ********************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DECLARATIONS *******************/
//***************************************************************************/

void getVehicleManufacturerSparePartNumber(uint8_t* buffer, uint16_t length);
void getVehicleManufacturerEcuHardwareNumber(uint8_t* buffer, uint16_t length);
void getApplicationSoftwareIdentification(uint8_t* buffer, uint16_t length);
void readManufacturerSoftwareVersion(uint8_t* buffer, uint16_t length);
