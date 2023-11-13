/**
 * @file     spi_TMS570LS_config.h
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 *
 */

#pragma once


//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/


//***************************************************************************/
//************************** PUBLIC TYPEDEFS ********************************/
//***************************************************************************/

/**
 * @brief true = The chip select signal is held active at the end of a transfer until a control field with new data and
 * control information is loaded into SPIDAT1, false = chip select is deactivated at end of transfer */
#define SPI_TMS570LS_CHIP_SELECT_HOLD_CONFIG 0b1u

/**
 * @brief true = after transaction WDELAY will be loaded,
 * false = no delay at the and of transfer */
#define SPI_TMS570LS_DELAY_COUNTER_ENABLE 0b1u

#define SPI_TMS570LS_DATALENGTH_ERROR_MAX_NUMBER_OF_BUFFER_ENTRIES_DELETE 0x40u

//********************************************************************************************************************************//
//********************************************************************************************************************************//
//********************************************************************************************************************************//

/** @name Register definition
 * @brief  The structure of the registers is identical for PC0 to PC8 and looks as follows:
 *
 * Bit 0-7        -->     Chip select pins 0-7
 * Bit 8          -->     Enable pin
 * Bit 9          -->     Clock pin
 * Bit 10         -->     SIMO[0] pin
 * Bit 11         -->     SOMI[0] pin
 * Bit 12 - 15    -->     reserved
 * Bit 16 - 23    -->     SIMO[x] pins
 * Bit 24 - 31    -->     SOMI[x] pins
 */

/**
 * @defgroup PC0 register
 * @brief PC0 register = functional pin configuration.
 *
 * 1: define pin as SPI Function
 * 0: define pin as GIO
 * @{
 */
#define SPI_TMS570LS_CHANNEL_1_PC0_CS_CONFIG       0x3Fu
#define SPI_TMS570LS_CHANNEL_1_PC0_ENA_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_1_PC0_CLK_CONFIG      0b1u
#define SPI_TMS570LS_CHANNEL_1_PC0_SIMO_CONFIG     0b1u
#define SPI_TMS570LS_CHANNEL_1_PC0_SOMI_CONFIG     0b1u
#define SPI_TMS570LS_CHANNEL_1_PC0_SIMO_ALL_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_1_PC0_SOMI_ALL_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_1_PC0_REGISTER        ((SPI_TMS570LS_CHANNEL_1_PC0_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_1_PC0_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_1_PC0_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC0_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC0_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC0_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC0_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_3_PC0_CS_CONFIG   0x1Eu
#define SPI_TMS570LS_CHANNEL_3_PC0_ENA_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_3_PC0_CLK_CONFIG  0b1u
#define SPI_TMS570LS_CHANNEL_3_PC0_SIMO_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_3_PC0_SOMI_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_3_PC0_REGISTER    ((SPI_TMS570LS_CHANNEL_3_PC0_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_3_PC0_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_3_PC0_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC0_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC0_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_4_PC0_CS_CONFIG   0b1u
#define SPI_TMS570LS_CHANNEL_4_PC0_ENA_CONFIG  0b1u
#define SPI_TMS570LS_CHANNEL_4_PC0_CLK_CONFIG  0b1u
#define SPI_TMS570LS_CHANNEL_4_PC0_SIMO_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_4_PC0_SOMI_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_4_PC0_REGISTER    ((SPI_TMS570LS_CHANNEL_4_PC0_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_4_PC0_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_4_PC0_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC0_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC0_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_5_PC0_CS_CONFIG       0b1000u
#define SPI_TMS570LS_CHANNEL_5_PC0_ENA_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_5_PC0_CLK_CONFIG      0b1u
#define SPI_TMS570LS_CHANNEL_5_PC0_SIMO_CONFIG     0b1u
#define SPI_TMS570LS_CHANNEL_5_PC0_SOMI_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_5_PC0_SIMO_ALL_CONFIG 0x1u
#define SPI_TMS570LS_CHANNEL_5_PC0_SOMI_ALL_CONFIG 0x0u
#define SPI_TMS570LS_CHANNEL_5_PC0_REGISTER        ((SPI_TMS570LS_CHANNEL_5_PC0_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_5_PC0_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_5_PC0_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC0_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC0_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC0_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC0_CS_CONFIG))


/**
 * @defgroup PC1_register
 * @brief PC1 register = Input Output Configuration
 *
 * 1: Output
 * 0: Input
 * @{
 */
#define SPI_TMS570LS_CHANNEL_1_PC1_CS_CONFIG       0x3Fu
#define SPI_TMS570LS_CHANNEL_1_PC1_ENA_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_1_PC1_CLK_CONFIG      0b1u
#define SPI_TMS570LS_CHANNEL_1_PC1_SIMO_CONFIG     0b1u
#define SPI_TMS570LS_CHANNEL_1_PC1_SOMI_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_1_PC1_SIMO_ALL_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_1_PC1_SOMI_ALL_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_1_PC1_REGISTER        ((SPI_TMS570LS_CHANNEL_1_PC1_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_1_PC1_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_1_PC1_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC1_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC1_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC1_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC1_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_3_PC1_CS_CONFIG   0x1Eu
#define SPI_TMS570LS_CHANNEL_3_PC1_ENA_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_3_PC1_CLK_CONFIG  0b1u
#define SPI_TMS570LS_CHANNEL_3_PC1_SIMO_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_3_PC1_SOMI_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_3_PC1_REGISTER    ((SPI_TMS570LS_CHANNEL_3_PC1_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_3_PC1_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_3_PC1_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC1_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC1_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_4_PC1_CS_CONFIG   0b1u
#define SPI_TMS570LS_CHANNEL_4_PC1_ENA_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_4_PC1_CLK_CONFIG  0b1u
#define SPI_TMS570LS_CHANNEL_4_PC1_SIMO_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_4_PC1_SOMI_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_4_PC1_REGISTER    ((SPI_TMS570LS_CHANNEL_4_PC1_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_4_PC1_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_4_PC1_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC1_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC1_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_5_PC1_CS_CONFIG       0b0011u
#define SPI_TMS570LS_CHANNEL_5_PC1_ENA_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_5_PC1_CLK_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_5_PC1_SIMO_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_5_PC1_SOMI_CONFIG     0b1u
#define SPI_TMS570LS_CHANNEL_5_PC1_SIMO_ALL_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_5_PC1_SOMI_ALL_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_5_PC1_REGISTER        ((SPI_TMS570LS_CHANNEL_5_PC1_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_5_PC1_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_5_PC1_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC1_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC1_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC1_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC1_CS_CONFIG))
/** @} */

/**
 * @brief PC3 register = Predefined output state
 *
 * 1: Pin State = High
 * 0: Pin State = Low
 * @{
 */
#define SPI_TMS570LS_CHANNEL_1_PC3_CS_CONFIG       0x3Fu
#define SPI_TMS570LS_CHANNEL_1_PC3_ENA_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_1_PC3_CLK_CONFIG      0b1u
#define SPI_TMS570LS_CHANNEL_1_PC3_SIMO_CONFIG     0b1u
#define SPI_TMS570LS_CHANNEL_1_PC3_SOMI_CONFIG     0b1u
#define SPI_TMS570LS_CHANNEL_1_PC3_SIMO_ALL_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_1_PC3_SOMI_ALL_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_1_PC3_REGISTER        ((SPI_TMS570LS_CHANNEL_1_PC3_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_1_PC3_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_1_PC3_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC3_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC3_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC3_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC3_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_3_PC3_CS_CONFIG   0x3Fu
#define SPI_TMS570LS_CHANNEL_3_PC3_ENA_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_3_PC3_CLK_CONFIG  0b1u
#define SPI_TMS570LS_CHANNEL_3_PC3_SIMO_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_3_PC3_SOMI_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_3_PC3_REGISTER    ((SPI_TMS570LS_CHANNEL_3_PC3_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_3_PC3_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_3_PC3_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC3_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC3_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_4_PC3_CS_CONFIG   0b1u
#define SPI_TMS570LS_CHANNEL_4_PC3_ENA_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_4_PC3_CLK_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_4_PC3_SIMO_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_4_PC3_SOMI_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_4_PC3_REGISTER    ((SPI_TMS570LS_CHANNEL_4_PC3_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_4_PC3_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_4_PC3_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC3_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC3_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_5_PC3_CS_CONFIG       0xFu
#define SPI_TMS570LS_CHANNEL_5_PC3_ENA_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_5_PC3_CLK_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_5_PC3_SIMO_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_5_PC3_SOMI_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_5_PC3_SIMO_ALL_CONFIG 0x0u
#define SPI_TMS570LS_CHANNEL_5_PC3_SOMI_ALL_CONFIG 0b111u
#define SPI_TMS570LS_CHANNEL_5_PC3_REGISTER        ((SPI_TMS570LS_CHANNEL_5_PC3_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_5_PC3_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_5_PC3_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC3_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC3_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC3_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC3_CS_CONFIG))


/**
 * @brief PC6 register = Open Drain Enable
 *
 * 1: Output value is in high-impedance state
 * 0: Output value is logic Low
 * @{
 */
#define SPI_TMS570LS_CHANNEL_1_PC6_CS_CONFIG       0x00u
#define SPI_TMS570LS_CHANNEL_1_PC6_ENA_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_1_PC6_CLK_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_1_PC6_SIMO_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_1_PC6_SOMI_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_1_PC6_SIMO_ALL_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_1_PC6_SOMI_ALL_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_1_PC6_REGISTER        ((SPI_TMS570LS_CHANNEL_1_PC6_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_1_PC6_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_1_PC6_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC6_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC6_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC6_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC6_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_3_PC6_CS_CONFIG   0x00u
#define SPI_TMS570LS_CHANNEL_3_PC6_ENA_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_3_PC6_CLK_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_3_PC6_SIMO_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_3_PC6_SOMI_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_3_PC6_REGISTER    ((SPI_TMS570LS_CHANNEL_3_PC6_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_3_PC6_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_3_PC6_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC6_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC6_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_4_PC6_CS_CONFIG   0b0u
#define SPI_TMS570LS_CHANNEL_4_PC6_ENA_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_4_PC6_CLK_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_4_PC6_SIMO_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_4_PC6_SOMI_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_4_PC6_REGISTER    ((SPI_TMS570LS_CHANNEL_4_PC6_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_4_PC6_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_4_PC6_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC6_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC6_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_5_PC6_CS_CONFIG       0x0u
#define SPI_TMS570LS_CHANNEL_5_PC6_ENA_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_5_PC6_CLK_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_5_PC6_SIMO_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_5_PC6_SOMI_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_5_PC6_SIMO_ALL_CONFIG 0x0u
#define SPI_TMS570LS_CHANNEL_5_PC6_SOMI_ALL_CONFIG 0x0u
#define SPI_TMS570LS_CHANNEL_5_PC6_REGISTER        ((SPI_TMS570LS_CHANNEL_5_PC6_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_5_PC6_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_5_PC6_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC6_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC6_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC6_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC6_CS_CONFIG))


/**
 * @brief PC7 register = Enable/disable Pull Up / Pull Down configuration
 *
 * 1: Pull Control disabled
 * 0: Pull Control enabled
 * @{
 */
#define SPI_TMS570LS_CHANNEL_1_PC7_CS_CONFIG       0x00u
#define SPI_TMS570LS_CHANNEL_1_PC7_ENA_CONFIG      0b1u
#define SPI_TMS570LS_CHANNEL_1_PC7_CLK_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_1_PC7_SIMO_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_1_PC7_SOMI_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_1_PC7_SIMO_ALL_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_1_PC7_SOMI_ALL_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_1_PC7_REGISTER        ((SPI_TMS570LS_CHANNEL_1_PC7_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_1_PC7_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_1_PC7_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC7_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC7_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC7_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC7_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_3_PC7_CS_CONFIG   0x00u
#define SPI_TMS570LS_CHANNEL_3_PC7_ENA_CONFIG  0b1u
#define SPI_TMS570LS_CHANNEL_3_PC7_CLK_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_3_PC7_SIMO_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_3_PC7_SOMI_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_3_PC7_REGISTER    ((SPI_TMS570LS_CHANNEL_3_PC7_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_3_PC7_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_3_PC7_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC7_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC7_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_4_PC7_CS_CONFIG   0b0u
#define SPI_TMS570LS_CHANNEL_4_PC7_ENA_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_4_PC7_CLK_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_4_PC7_SIMO_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_4_PC7_SOMI_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_4_PC7_REGISTER    ((SPI_TMS570LS_CHANNEL_4_PC7_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_4_PC7_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_4_PC7_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC7_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC7_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_5_PC7_CS_CONFIG       0x0u
#define SPI_TMS570LS_CHANNEL_5_PC7_ENA_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_5_PC7_CLK_CONFIG      0b0u
#define SPI_TMS570LS_CHANNEL_5_PC7_SIMO_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_5_PC7_SOMI_CONFIG     0b0u
#define SPI_TMS570LS_CHANNEL_5_PC7_SIMO_ALL_CONFIG 0x0u
#define SPI_TMS570LS_CHANNEL_5_PC7_SOMI_ALL_CONFIG 0x0u
#define SPI_TMS570LS_CHANNEL_5_PC7_REGISTER        ((SPI_TMS570LS_CHANNEL_5_PC7_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_5_PC7_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_5_PC7_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC7_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC7_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC7_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC7_CS_CONFIG))


/**
 * @brief PC8 register = If PC7 enabled, choose between Pull Up / Pull Down
 *
 * 1: Pull Up on pin
 * 0: Pull down on pin
 * @{
 */
#define SPI_TMS570LS_CHANNEL_1_PC8_CS_CONFIG       0x3Fu
#define SPI_TMS570LS_CHANNEL_1_PC8_ENA_CONFIG      0b1u
#define SPI_TMS570LS_CHANNEL_1_PC8_CLK_CONFIG      0b1u
#define SPI_TMS570LS_CHANNEL_1_PC8_SIMO_CONFIG     0b1u
#define SPI_TMS570LS_CHANNEL_1_PC8_SOMI_CONFIG     0b1u
#define SPI_TMS570LS_CHANNEL_1_PC8_SIMO_ALL_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_1_PC8_SOMI_ALL_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_1_PC8_REGISTER        ((SPI_TMS570LS_CHANNEL_1_PC8_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_1_PC8_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_1_PC8_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC8_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_1_PC8_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC8_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_1_PC8_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_3_PC8_CS_CONFIG   0x3Fu
#define SPI_TMS570LS_CHANNEL_3_PC8_ENA_CONFIG  0b1u
#define SPI_TMS570LS_CHANNEL_3_PC8_CLK_CONFIG  0b1u
#define SPI_TMS570LS_CHANNEL_3_PC8_SIMO_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_3_PC8_SOMI_CONFIG 0b1u
#define SPI_TMS570LS_CHANNEL_3_PC8_REGISTER    ((SPI_TMS570LS_CHANNEL_3_PC8_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_3_PC8_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_3_PC8_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC8_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_3_PC8_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_4_PC8_CS_CONFIG   0b1u
#define SPI_TMS570LS_CHANNEL_4_PC8_ENA_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_4_PC8_CLK_CONFIG  0b0u
#define SPI_TMS570LS_CHANNEL_4_PC8_SIMO_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_4_PC8_SOMI_CONFIG 0b0u
#define SPI_TMS570LS_CHANNEL_4_PC8_REGISTER    ((SPI_TMS570LS_CHANNEL_4_PC8_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS) \
                                             | (SPI_TMS570LS_CHANNEL_4_PC8_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)  \
                                             | (SPI_TMS570LS_CHANNEL_4_PC8_CLK_CONFIG << SPI_TMS570LS_CLK_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC8_ENA_CONFIG << SPI_TMS570LS_ENA_POS)    \
                                             | (SPI_TMS570LS_CHANNEL_4_PC8_CS_CONFIG))

#define SPI_TMS570LS_CHANNEL_5_PC8_CS_CONFIG       0xFu
#define SPI_TMS570LS_CHANNEL_5_PC8_ENA_CONFIG      0b1u
#define SPI_TMS570LS_CHANNEL_5_PC8_CLK_CONFIG      0b1u
#define SPI_TMS570LS_CHANNEL_5_PC8_SIMO_CONFIG     0b1u
#define SPI_TMS570LS_CHANNEL_5_PC8_SOMI_CONFIG     0b1u
#define SPI_TMS570LS_CHANNEL_5_PC8_SIMO_ALL_CONFIG 0xFu
#define SPI_TMS570LS_CHANNEL_5_PC8_SOMI_ALL_CONFIG 0xFu
#define SPI_TMS570LS_CHANNEL_5_PC8_REGISTER        ((SPI_TMS570LS_CHANNEL_5_PC8_SOMI_ALL_CONFIG << SPI_TMS570LS_SOMI_ALL_DATALINES_POS) \
                                             | (SPI_TMS570LS_CHANNEL_5_PC8_SIMO_ALL_CONFIG << SPI_TMS570LS_SIMO_ALL_DATALINES_POS)      \
                                             | (SPI_TMS570LS_CHANNEL_5_PC8_SOMI_CONFIG << SPI_TMS570LS_SOMI_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC8_SIMO_CONFIG << SPI_TMS570LS_SIMO_POS)                        \
                                             | (SPI_TMS570LS_CHANNEL_5_PC8_CLK_CONFIG << SPI_TMS570LS_CLK_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC8_ENA_CONFIG << SPI_TMS570LS_ENA_POS)                          \
                                             | (SPI_TMS570LS_CHANNEL_5_PC8_CS_CONFIG))

#define SPI_TMS570LS_FMT_0_WAITENA_CONFIG 0b0u
#define SPI_TMS570LS_FMT_1_WAITENA_CONFIG 0b0u
#define SPI_TMS570LS_FMT_2_WAITENA_CONFIG 0b0u
#define SPI_TMS570LS_FMT_3_WAITENA_CONFIG 0b0u

//***************************************************************************/
//************************** PUBLIC VARIABLE DEFINITIONS ********************/
//***************************************************************************/

extern const SPI_ChannelConfig* const spi_TMS570LS_ChannelConfig[];
extern const SPI_DeviceConfig SPI_TMS570LS_DeviceConfig;

//***************************************************************************/
//************************** PUBLIC FUNCTION DECLARATIONS *******************/
//***************************************************************************/
