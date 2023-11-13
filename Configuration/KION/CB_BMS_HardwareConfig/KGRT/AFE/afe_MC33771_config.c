/**
 * @file     afe_MC33771_config.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 */

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "afe_MC33771.h"
#include "afe_MC33771_config.h"

#include AFE_INCLUDE_HEADER

#include "bms_config.h"
#include "spiIf.h"
#include "task_cfg.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/
const SPI_DataFormatConfig afe_MC33771_X_spiDataFormatConfig_transmit = {
    .spi_Format_Delay              = 0,
    .spi_Format_Parity_Polarity    = SPI_PARITY_EVEN,
    .spi_Format_Parity_Control     = 0,  // 0 = enabled
    .spi_Format_Wait_Enable        = 0,
    .spi_Format_Shift_Direction    = SPI_SHIFT_DIR_MSB,
    .spi_Format_Half_Duplex_Enable = DISABLED,
    .spi_Format_CS_Delay_Control   = 0,  // 0 = enabled
    .spi_Format_Clock_Polarity     = SPI_CLOCK_POL_ACTIVE_HIGH,
    .spi_Format_Clock_Phase        = DISABLED,           // SPI data format x clock delay
    .spi_Format_Baudrate           = 2000000,            // Prescaler will be calculated with this value
    .spi_Format_Data_Length        = (uint8_t)SPI_8_BIT  // SPI data format x data-word length.
};

const SPI_DataFormatConfig afe_MC33771_X_spiDataFormatConfig_receive = {
    .spi_Format_Delay              = 0,
    .spi_Format_Parity_Polarity    = SPI_PARITY_EVEN,
    .spi_Format_Parity_Control     = 0,  // 0 = enabled
    .spi_Format_Wait_Enable        = 0,
    .spi_Format_Shift_Direction    = SPI_SHIFT_DIR_MSB,
    .spi_Format_Half_Duplex_Enable = DISABLED,
    .spi_Format_CS_Delay_Control   = 0,  // 0 = enabled
    .spi_Format_Clock_Polarity     = SPI_CLOCK_POL_ACTIVE_HIGH,
    .spi_Format_Clock_Phase        = DISABLED,           // SPI data format x clock delay
    .spi_Format_Baudrate           = 2000000,            // Prescaler will be calculated with this value
    .spi_Format_Data_Length        = (uint8_t)SPI_8_BIT  // SPI data format x data-word length.
};

MEM_AFE SPI_MIBSPI_TransferGroupConfig afe_MC33771_X_mibspi_receiveTransferGroupConfig = {
    .spi_Mibspi_Transfergroup_Oneshot_Control        = ENABLED,
    .spi_Mibspi_Transfergroup_Pointer_Reset          = ENABLED,
    .spi_Mibspi_Transfergroup_Trigger_Event_Control  = SPI_TRIGGER_EVENT_ALWAYS,
    .spi_Mibspi_Transfergroup_Trigger_Source_Control = SPI_TRIGGER_SOURCE_DISABLED,
    .spi_Mibspi_Transfergroup_Buffer_Length          = AFE_SPI_LENGTH,
    .spi_Mibspi_Transfergroup_Buffer_Mode            = SPI_BUFFER_MODE_ALWAYS,
    .spi_Mibspi_Transfergroup_CS_Hold_All            = ENABLED,
    .spi_Mibspi_Transfergroup_CS_Hold_Last           = DISABLED,
    .spi_Mibspi_Transfergroup_Lock_Transmission      = DISABLED,
    .spi_Mibspi_Transfergroup_Data_Format_Select     = SPI_DATA_FORMAT_0,
    .spi_Mibspi_Transfergroup_CS_Select              = AFE_MC33771_RX_CHIP_SELECT_BITMASK,
    .spi_Mibspi_Transfergroup_Delay_Control          = DISABLED
};

const SPI_MIBSPI_TransferGroupConfig afe_MC33771_X_mibspi_transmitTransferGroupConfig = {
    .spi_Mibspi_Transfergroup_Number                 = SPI_TransferGroup_0,
    .spi_Mibspi_Transfergroup_Oneshot_Control        = ENABLED,
    .spi_Mibspi_Transfergroup_Pointer_Reset          = DISABLED,
    .spi_Mibspi_Transfergroup_Trigger_Event_Control  = SPI_TRIGGER_EVENT_ALWAYS,
    .spi_Mibspi_Transfergroup_Trigger_Source_Control = SPI_TRIGGER_SOURCE_DISABLED,
    .spi_Mibspi_Transfergroup_Buffer_Length          = AFE_SPI_LENGTH,
    .spi_Mibspi_Transfergroup_Buffer_Mode            = SPI_BUFFER_MODE_ALWAYS,
    .spi_Mibspi_Transfergroup_CS_Hold_All            = ENABLED,
    .spi_Mibspi_Transfergroup_CS_Hold_Last           = DISABLED,
    .spi_Mibspi_Transfergroup_Lock_Transmission      = DISABLED,
    .spi_Mibspi_Transfergroup_Data_Format_Select     = SPI_DATA_FORMAT_0,
    .spi_Mibspi_Transfergroup_CS_Select              = AFE_MC33771_TX_CHIP_SELECT_BITMASK,
    .spi_Mibspi_Transfergroup_Delay_Control          = DISABLED
};


MEM_AFE SPI_CommInterfaceConfig afe_MC33771_X_CommInterface_RX[] = {
    { (uint8_t)SPI_PORT_5, (uint8_t)AFE_MC33771_RX_CHIP_SELECT_BITMASK, SPI_DATA_FORMAT_0, AFE_SPI_LENGTH },
};

const uint8_t afe_MC33771_X_CommInterface_RX_SIZE = sizeof(afe_MC33771_X_CommInterface_RX) / sizeof(SPI_CommInterfaceConfig);

const SPI_CommInterfaceConfig afe_MC33771_X_CommInterface_TX[] = {
    { (uint8_t)SPI_PORT_3, (uint8_t)AFE_MC33771_TX_CHIP_SELECT_BITMASK, SPI_DATA_FORMAT_0, AFE_SPI_LENGTH },
};

const uint8_t afe_MC33771_X_CommInterface_TX_SIZE = sizeof(afe_MC33771_X_CommInterface_TX) / sizeof(SPI_CommInterfaceConfig);


const AFE_DeviceConfig afe_MC33771_X_deviceConfig = {
    .nAuxInputs        = 8,
    .nCells            = 14,
    .interfaceConfigRx = afe_MC33771_X_CommInterface_RX,
    .interfaceConfigTx = afe_MC33771_X_CommInterface_TX,
};


const AFE_DeviceConfig* const afe_MC33771_deviceConfig = {
    &afe_MC33771_X_deviceConfig,
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
