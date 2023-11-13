/**
 * @file     can_TJA1145_config_default.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 */

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "can_TJA1145.h"
#include "config_enable.h"
#include "spiIf.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/

const SPI_DataFormatConfig can_TJA1145_spiDataFormatConfig = {
    .spi_Format_Delay              = 0,
    .spi_Format_Parity_Polarity    = SPI_PARITY_EVEN,
    .spi_Format_Parity_Control     = 0,  // 0 = enabled
    .spi_Format_Wait_Enable        = 0,
    .spi_Format_Shift_Direction    = SPI_SHIFT_DIR_MSB,
    .spi_Format_Half_Duplex_Enable = DISABLED,
    .spi_Format_CS_Delay_Control   = 0,  // 0 = enabled
    .spi_Format_Clock_Polarity     = SPI_CLOCK_POL_ACTIVE_HIGH,
    .spi_Format_Clock_Phase        = DISABLED,  // SPI data format x clock delay
    .spi_Format_Baudrate           = 1000000,   // Prescaler will be calculated with this value
    .spi_Format_Data_Length        = SPI_8_BIT  // SPI data format x data-word length.
};

const SPI_CommInterfaceConfig can_TJA1145_InterfaceConfig[] = {
    { (uint8_t)SPI_PORT_1, (uint8_t)SPI_CHIP_SELECT_0, SPI_DATA_FORMAT_0, 0 }
};

const CAN_TJA1145_DeviceConfig can_TJA1145_DeviceConfig = {
    .config = {
        .nDevices        = 1,
        .nNodes          = 1,
        .nMessageObjects = 1,
    },
    .interfaceConfig = can_TJA1145_InterfaceConfig,
};

//***************************************************************************/
//************************** PRIVATE FUNCTION DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DEFINITIONS *******************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DEFINITIONS * ******************/
//***************************************************************************/
