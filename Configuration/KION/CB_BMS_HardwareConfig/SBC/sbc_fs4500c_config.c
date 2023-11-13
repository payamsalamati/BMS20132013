/**
 * @file     sbc_FS4500c_config_default.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "FS4500c/sbc_fs4500c.h"
#include "config_enable.h"
#include "spiIf.h"
#include "ioIf.h"
//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/
const SBCType* const sbcTypes[] = {
    &sbc_FS4500C
};

const uint8_t SBC_TYPES_LENGTH = sizeof(sbcTypes) / sizeof(SBCType*);

const SPI_DataFormatConfig SBC_FS4500C_spiDataFormatConfig = {
    .spi_Format_Delay              = 0,
    .spi_Format_Parity_Polarity    = SPI_PARITY_EVEN,
    .spi_Format_Parity_Control     = 0,  // 0 = enabled
    .spi_Format_Wait_Enable        = 0,
    .spi_Format_Shift_Direction    = SPI_SHIFT_DIR_MSB,
    .spi_Format_Half_Duplex_Enable = DISABLED,
    .spi_Format_CS_Delay_Control   = 0,  // 0 = enabled
    .spi_Format_Clock_Polarity     = SPI_CLOCK_POL_ACTIVE_HIGH,
    .spi_Format_Clock_Phase        = DISABLED,            // SPI data format x clock delay
    .spi_Format_Baudrate           = 8000000,             // NOTE: Specification CLK = 8MHz
    .spi_Format_Data_Length        = (uint8_t)SPI_16_BIT  // SPI data format x data-word length.
};

const SPI_CommInterfaceConfig SBC_FS4500C_INTERFACE_CONFIG[] = {
    { (uint8_t)SPI_PORT_1, (uint8_t)SPI_CHIP_SELECT_1, SPI_DATA_FORMAT_1, 1 },
};

const uint8_t SBC_FS4500C_INTERFACECONFIG_LENGTH = sizeof(SBC_FS4500C_INTERFACE_CONFIG) / sizeof(SPI_CommInterfaceConfig);

/**
 * @brief
 */
const SBC_FS4500_Config SBC_FS4500C_DeviceConfig = {
    .config = {
        .nDevices      = 1,
        .nAnalogInputs = 5,
        .nGPIOs        = 6,
        .nCan          = 1,
    },
    .interfaceConfig = SBC_FS4500C_INTERFACE_CONFIG,
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
