/**
 * @file     adc_ADS1118_config.c
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

#include "ADS1118/adc_ADS1118.h"
#include "config_enable.h"
#include "spiIf.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/

const SPI_DataFormatConfig ADS1118_spiDataFormatConfig = {
    .spi_Format_Delay              = 0,
    .spi_Format_Parity_Polarity    = SPI_PARITY_EVEN,
    .spi_Format_Parity_Control     = 0,  // 0 = enabled
    .spi_Format_Wait_Enable        = 0,
    .spi_Format_Shift_Direction    = SPI_SHIFT_DIR_MSB,
    .spi_Format_Half_Duplex_Enable = DISABLED,
    .spi_Format_CS_Delay_Control   = 0,  // 0 = enabled
    .spi_Format_Clock_Polarity     = SPI_CLOCK_POL_ACTIVE_HIGH,
    .spi_Format_Clock_Phase        = DISABLED,   // SPI data format x clock delay
    .spi_Format_Baudrate           = 4000000,    // NOTE: Specification CLK = 4MHz
    .spi_Format_Data_Length        = SPI_16_BIT  // SPI data format x data-word length.
};

const SPI_CommInterfaceConfig ADC_ADS1118_InterfaceConfig[] = {
    { (uint8_t)SPI_PORT_1, (uint8_t)SPI_CHIP_SELECT_3, SPI_DATA_FORMAT_3, 1 },
};

const uint8_t ADC_ADS1118_INTERFACECONFIG_LENGTH = sizeof(ADC_ADS1118_InterfaceConfig) / sizeof(SPI_CommInterfaceConfig*);

/**
 * @brief
 */
const ADC_ADS1118_Config ADC_ADS1118_DeviceConfig = {
    .config = {
        .nDevices                 = ADC_ADS1118_nDEVICES,
        .nPorts                   = 1,
        .nChannels                = 4,
        .refVoltage               = 12288.0,  // 2 * 6144
        .maxVal                   = 26666,
        .negativeVoltageThreshold = 10,
        .resolution               = 16,
    },
    .interfaceConfig = ADC_ADS1118_InterfaceConfig,
};

//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DEFINITIONS *******************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DEFINITIONS * ******************/
//***************************************************************************/
