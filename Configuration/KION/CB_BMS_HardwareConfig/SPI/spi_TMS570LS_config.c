/**
 * @file     spi_TMS570LS_config_KION_HW2V6.c
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


#include "TMS570/spi_TMS570LS.h"
#include "config_enable.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/

/** SPI data formats are defined in own HW modules */
// SPI-Channel 1
extern const SPI_DataFormatConfig can_TJA1145_spiDataFormatConfig;
extern const SPI_DataFormatConfig SBC_FS4500C_spiDataFormatConfig;
extern const SPI_DataFormatConfig eeprom_M95xxx_spiDataFormatConfig;
extern const SPI_DataFormatConfig ADS1118_spiDataFormatConfig;

// SPI-Channel 3
extern const SPI_DataFormatConfig afe_MC33771_X_spiDataFormatConfig_transmit;

// SPI-Channel 5
extern const SPI_DataFormatConfig afe_MC33771_X_spiDataFormatConfig_receive;
extern const SPI_MIBSPI_TransferGroupConfig afe_MC33771_X_mibspi_receiveTransferGroupConfig;
extern const SPI_MIBSPI_TransferGroupConfig afe_MC33771_X_mibspi_transmitTransferGroupConfig;


//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/

/**
 * @brief General SPI TMS570LS hardware parameters.
 *
 * The maximum values should be specified here.
 */
const SPI_DeviceConfig SPI_TMS570LS_DeviceConfig = {
    .maxDataPerAction = SPI_MAX_DATA_LENGTH,
    .maxNumberOfData  = 16,
    .nDataFormats     = 4,
    .nInterfaces      = 4,
    .nChipSelects     = 6,
};

/**
 * @brief Default data format configuration
 *
 * Can be used as template or for unused data formats.
 * @see detailed SPI_DataFormatConfig description in spi_helpers.h
 */
const SPI_DataFormatConfig spiDataFormat_default = {
    .spi_Format_Delay              = 0,
    .spi_Format_Parity_Polarity    = SPI_PARITY_EVEN,
    .spi_Format_Parity_Control     = 0,  // 0 = enabled
    .spi_Format_Wait_Enable        = 0,
    .spi_Format_Shift_Direction    = SPI_SHIFT_DIR_MSB,
    .spi_Format_Half_Duplex_Enable = DISABLED,
    .spi_Format_CS_Delay_Control   = 0,  // 0 = enabled
    .spi_Format_Clock_Polarity     = SPI_CLOCK_POL_ACTIVE_HIGH,
    .spi_Format_Clock_Phase        = DISABLED,           // SPI data format x clock delay
    .spi_Format_Baudrate           = 1000000,            // Prescaler will be calculated with this value
    .spi_Format_Data_Length        = (uint8_t)SPI_8_BIT  // SPI data format x data-word length.
};

/**
 * @brief Default multibuffer transer group configuration
 *
 * Can be used as template or for unused transfer groups.
 * @see detailed SPI_MIBSPI_TransferGroupConfig description in spi_helpers.h
 */
const SPI_MIBSPI_TransferGroupConfig spi_mibspi_tranferGroup_default = {
    .spi_Mibspi_Transfergroup_Oneshot_Control        = ENABLED,
    .spi_Mibspi_Transfergroup_Pointer_Reset          = DISABLED,
    .spi_Mibspi_Transfergroup_Trigger_Event_Control  = SPI_TRIGGER_EVENT_ALWAYS,
    .spi_Mibspi_Transfergroup_Trigger_Source_Control = SPI_TRIGGER_SOURCE_DISABLED,
    .spi_Mibspi_Transfergroup_Buffer_Length          = 0,
};

/**
 * @brief Data format configurations for SPI Channel 1.
 *
 */
const SPI_DataFormatConfig* const SPI_Channel1_DataFormatTable[] = {
    &can_TJA1145_spiDataFormatConfig,
    &SBC_FS4500C_spiDataFormatConfig,
    &eeprom_M95xxx_spiDataFormatConfig,
    &ADS1118_spiDataFormatConfig,
};

const uint8_t SPI_CHANNEL_1_NUMBER_OF_DATA_FORMAT = sizeof(SPI_Channel1_DataFormatTable) / sizeof(SPI_DataFormatConfig*);


/**
 * @brief data format configurations for SPI Channel 3
 */
const SPI_DataFormatConfig* const SPI_Channel3_DataFormatTable[] = {
    &afe_MC33771_X_spiDataFormatConfig_transmit,
    &spiDataFormat_default,
    &spiDataFormat_default,
    &spiDataFormat_default,
};

const uint8_t SPI_CHANNEL_3_NUMBER_OF_DATA_FORMAT = sizeof(SPI_Channel3_DataFormatTable) / sizeof(SPI_DataFormatConfig*);

/**
 * @brief data format configurations for SPI Channel 5
 */
const SPI_DataFormatConfig* const SPI_Channel5_DataFormatTable[] = {
    &afe_MC33771_X_spiDataFormatConfig_receive,
    &spiDataFormat_default,
    &spiDataFormat_default,
    &spiDataFormat_default,
};

const uint8_t SPI_CHANNEL_5_NUMBER_OF_DATA_FORMAT = sizeof(SPI_Channel5_DataFormatTable) / sizeof(SPI_DataFormatConfig*);

const SPI_MIBSPI_TransferGroupConfig* const SPI_MIBSPI_Channel3_TransferGroupTable[] = {
    &afe_MC33771_X_mibspi_transmitTransferGroupConfig,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
};

const SPI_MIBSPI_TransferGroupConfig* const SPI_MIBSPI_Channel5_TransferGroupTable[] = {
    &afe_MC33771_X_mibspi_receiveTransferGroupConfig,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
    &spi_mibspi_tranferGroup_default,
};

const uint8_t SPI_MIBSPI_CHANNEL_5_NUMBER_OF_TRANSFER_GOUPS = sizeof(SPI_MIBSPI_Channel5_TransferGroupTable) / sizeof(SPI_MIBSPI_TransferGroupConfig*);

/**
 * @brief Hardware configurations for SPI channel 1.
 */
const SPI_ChannelConfig spi_TMS570LS_channel_1 = {
    .SPI_PortNumber              = (uint8_t)SPI_PORT_1,
    .SPI_MasterSlaveMode         = SPI_MASTER_MODE,
    .SPI_ClockInput              = SPI_CLOCK_SRC_INTERNAL,
    .SPI_CS_to_Transmit_Delay    = 2500,  // in ns
    .SPI_CS_after_Transmit_Delay = 100,   // in ns
    .SPI_EnablePin               = DISABLED,
    .SPI_TXInterrupt             = DISABLED,
    .SPI_RXInterrupt             = DISABLED,
    .DataFormat                  = SPI_Channel1_DataFormatTable,
    .SPI_MIBSPI_EnableMode       = DISABLED,
};

/**
 * @brief Hardware configurations for SPI channel 3.
 */
const SPI_ChannelConfig spi_TMS570LS_channel_3 = {
    .SPI_PortNumber              = (uint8_t)SPI_PORT_3,
    .SPI_MasterSlaveMode         = SPI_MASTER_MODE,
    .SPI_ClockInput              = SPI_CLOCK_SRC_INTERNAL,
    .SPI_CS_to_Transmit_Delay    = 1750,  // in ns
    .SPI_CS_after_Transmit_Delay = 700,   // in ns
    .SPI_EnablePin               = DISABLED,
    .SPI_TXInterrupt             = DISABLED,
    .SPI_RXInterrupt             = DISABLED,
    .DataFormat                  = SPI_Channel3_DataFormatTable,
    .SPI_MIBSPI_EnableMode       = ENABLED,

    // additional configurations because of SPI_MIBSPI_EnableMode = ENABLED
    .SPI_MIBSPI_DefaultCS       = 0xFF,
    .SPI_MIBSPI_EnableRamParity = DISABLED,
    .SPI_MIBSPI_TransferGroup   = SPI_MIBSPI_Channel3_TransferGroupTable,
    .SPI_MibspiReceiveOnlyPort  = false,
};

/**
 * @brief Hardware configurations for SPI channel 5.
 */
const SPI_ChannelConfig spi_TMS570LS_channel_5 = {
    .SPI_PortNumber              = (uint8_t)SPI_PORT_5,
    .SPI_MasterSlaveMode         = SPI_SLAVE_MODE,
    .SPI_ClockInput              = SPI_CLOCK_SRC_EXTERNAL,
    .SPI_CS_to_Transmit_Delay    = 0,  // in ns
    .SPI_CS_after_Transmit_Delay = 0,  // in ns
    .SPI_EnablePin               = DISABLED,
    .SPI_TXInterrupt             = DISABLED,
    .SPI_RXInterrupt             = ENABLED,
    .DataFormat                  = SPI_Channel5_DataFormatTable,
    .SPI_MIBSPI_EnableMode       = ENABLED,

    // additional configurations because of SPI_MIBSPI_EnableMode = ENABLED
    .SPI_MIBSPI_DefaultCS       = 0xFF,
    .SPI_MIBSPI_EnableRamParity = DISABLED,
    .SPI_MIBSPI_TransferGroup   = SPI_MIBSPI_Channel5_TransferGroupTable,
    .SPI_MibspiReceiveOnlyPort  = true,
};

const SPI_ChannelConfig* const spi_TMS570LS_ChannelConfig[] = {
    &spi_TMS570LS_channel_1,
    &spi_TMS570LS_channel_3,
    &spi_TMS570LS_channel_5
};

const uint8_t SPI_CHANNEL_CONFIG_LENGTH = sizeof(spi_TMS570LS_ChannelConfig) / sizeof(SPI_ChannelConfig*);

//***************************************************************************/
//************************** PRIVATE FUNCTION DECLARATIONS ******************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE FUNCTION DEFINITIONS *******************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC FUNCTION DEFINITIONS * ******************/
//***************************************************************************/
