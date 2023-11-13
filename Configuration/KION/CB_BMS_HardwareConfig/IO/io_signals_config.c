/**
 * @file     io_signals_config.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 *	 -
 */

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/
#include "ioIf.h"
#include "io_signals_config.h"
#include "ioIf_config.h"

//***************************************************************************/
//************************** PRIVATE TYPEDEFS *******************************/
//***************************************************************************/


//***************************************************************************/
//************************** PRIVATE VARIABLE DECLARATIONS ******************/
//***************************************************************************/

/**--------------------------- Signal Configurations ------------------------------------------*/
/**---------------------- Digital Outputs -----------------------------------------*/

/**--------------- EEPROM Hold Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_EEPROM_HoldEnable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 26,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- EEPROM Write Protect ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_EEPROM_WriteProtect = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 19,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- VSUP ICD Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_VSUP_ICD_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 14,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- 10V BAT Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_13V_BAT_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 22,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- LATCH Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_LATCH_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOA,
    .pin        = 4,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- BCM 3V3 Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_BCM_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 1,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- BCM 2V3 PRECHRG ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_BCM_PRECHARGE_CONTROL = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 2,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};


/**--------------- BCM 3V3 Wakeup ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_BCM_WakeUp = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 6,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- BCM not Ready ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_BCM_nReady = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 15,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};


/**--------------- DSS Wakeup ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_DSS_WU = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOA,
    .pin        = 7,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- CPS Enable Wakeup ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_CPS_Enable_WU = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 5,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- CAN1 Wakeup ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_CAN1_WU = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET2,
    .pin        = 9,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- NXP CSC Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_NXP_CSC_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_SPI5,
    .pin        = 1,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- LED 1 ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_LED_1 = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOA,
    .pin        = 1,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};


/**--------------- LED 2 ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_LED_2 = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOA,
    .pin        = 2,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};


/**--------------- LED 3 ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_LED_3 = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 29,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- GPIO1 Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_GPIO1_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 3,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- GPIO2 Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_GPIO2_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_SPI5,
    .pin        = 17,  //SPIPCx-Register, pin17 -> SPISIMO[1]
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- GPIO3 Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_GPIO3_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 7,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- GPIO4 Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_GPIO4_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 31,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- HSS K1 Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_HSS_K1_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOB,
    .pin        = 4,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- HSS K2 Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_HSS_K2_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOB,
    .pin        = 7,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- HSS K3 Enable ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_HSS_K3_Enable = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOA,
    .pin        = 3,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- LSS COC K1 Reset ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_LSS_COC_K1_Reset = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 23,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- LSS COC K2 Reset ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_LSS_COC_K2_Reset = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 8,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- LSS COC K3 Reset ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_LSS_COC_K3_Reset = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 20,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- AFE Wakeup ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_AFE_WU = {
    .direction  = IO_OUTPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_SPI3,
    .pin        = 1,  //CS1
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**---------------------- Digital Inputs -----------------------------------------*/

/**--------------- HSS K1 Status ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_HSS_K1_Status = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 27,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- HSS K2 Status ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_HSS_K2_Status = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOA,
    .pin        = 0,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- HSS K3 Status ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_HSS_K3_Status = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 16,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- LSS COC K1 Alert ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_LSS_COC_K1_Alert = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 13,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- LSS COC K2 Alert ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_LSS_COC_K2_Alert = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 24,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- LSS COC K3 Alert ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_LSS_COC_K3_Alert = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOA,
    .pin        = 6,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- GPIO1 SENS ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_GPIO1_SENS = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOB,
    .pin        = 6,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- GPIO2 SENS ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_GPIO2_SENS = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 0,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- GPIO3 SENS ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_GPIO3_SENS = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOB,
    .pin        = 0,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- GPIO4 SENS ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_GPIO4_SENS = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 28,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- CPS SENS Wakeup ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_CPS_SENS_WU = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_GIOB,
    .pin        = 3,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- Button SENS Wakeup ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_BUTTON_SENS_WU = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 10,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- SBC Fault ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_SBC_FAULT = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_HET1,
    .pin        = 17,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- ISO OK ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_ISO_OK = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_NON_INVERTED_LOGIC,
    .port       = (uint8_t)IO_SPI5,
    .pin        = 2,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**--------------- NXP CSC Interrupt ---------------------------
 * @brief
 */
static const IO_SignalConfig IO_NXP_CSC_INT = {
    .direction  = IO_INPUT_DIRECTION,
    .logic      = IO_INVERTED_LOGIC,
    .port       = (uint8_t)IO_SPI3,
    .pin        = 5,
    .deviceNr   = 0,
    .deviceType = (uint8_t)IO_DEVICE_TMS570LS,
};

/**------------ Hardware specific io channels --------------------------*/

const IO_Signals IO_SIGNAL_CONFIG_HW_1V0 = {
    /************ OUTPUTS ************/
    .IO_SIGNALS_EEPROM_HoldEnable     = &IO_EEPROM_HoldEnable,
    .IO_SIGNALS_EEPROM_WriteProtect   = &IO_EEPROM_WriteProtect,
    .IO_SIGNALS_VSUP_ICD_Enable       = &IO_VSUP_ICD_Enable,
    .IO_SIGNALS_13V_BAT_Enable        = &IO_13V_BAT_Enable,
    .IO_SIGNALS_LATCH_Enable          = &IO_LATCH_Enable,
    .IO_SIGNALS_BCM_Enable            = &IO_BCM_Enable,
    .IO_SIGNALS_BCM_PRECHARGE_CONTROL = &IO_BCM_PRECHARGE_CONTROL,
    .IO_SIGNALS_BCM_WAKE_UP           = &IO_BCM_WakeUp,
    .IO_SIGNALS_DSS_WU                = &IO_DSS_WU,
    .IO_SIGNALS_CPS_Enable_WU         = &IO_CPS_Enable_WU,
    .IO_SIGNALS_CAN1_WU               = &IO_CAN1_WU,
    .IO_SIGNALS_Slave_Enable          = &IO_NXP_CSC_Enable,
    .IO_SIGNALS_LED_1                 = &IO_LED_1,
    .IO_SIGNALS_LED_2                 = &IO_LED_2,
    .IO_SIGNALS_LED_3                 = &IO_LED_3,
    .IO_SIGNALS_Ext_Output_1          = &IO_GPIO1_Enable,
    .IO_SIGNALS_Ext_Output_2          = &IO_GPIO2_Enable,
    .IO_SIGNALS_Ext_Output_3          = &IO_GPIO3_Enable,
    .IO_SIGNALS_Ext_Output_4          = &IO_GPIO4_Enable,
    .IO_SIGNALS_HSS_K1_Enable         = &IO_HSS_K1_Enable,
    .IO_SIGNALS_HSS_K2_Enable         = &IO_HSS_K2_Enable,
    .IO_SIGNALS_HSS_K3_Enable         = &IO_HSS_K3_Enable,
    .IO_SIGNALS_LSS_COC_K1_Reset      = &IO_LSS_COC_K1_Reset,
    .IO_SIGNALS_LSS_COC_K2_Reset      = &IO_LSS_COC_K2_Reset,
    .IO_SIGNALS_LSS_COC_K3_Reset      = &IO_LSS_COC_K3_Reset,
    .IO_SIGNALS_AFE_Wakeup            = &IO_AFE_WU,

    /************ INPUTS ************/
    .IO_SIGNALS_HSS_K1_Status    = &IO_HSS_K1_Status,
    .IO_SIGNALS_HSS_K2_Status    = &IO_HSS_K2_Status,
    .IO_SIGNALS_HSS_K3_Status    = &IO_HSS_K3_Status,
    .IO_SIGNALS_LSS_COC_K1_Alert = &IO_LSS_COC_K1_Alert,
    .IO_SIGNALS_LSS_COC_K2_Alert = &IO_LSS_COC_K2_Alert,
    .IO_SIGNALS_LSS_COC_K3_Alert = &IO_LSS_COC_K3_Alert,
    .IO_SIGNALS_Ext_Input_1      = &IO_GPIO1_SENS,
    .IO_SIGNALS_Ext_Input_2      = &IO_GPIO2_SENS,
    .IO_SIGNALS_Ext_Input_3      = &IO_GPIO3_SENS,
    .IO_SIGNALS_Ext_Input_4      = &IO_GPIO4_SENS,
    .IO_SIGNALS_BCM_nREADY       = &IO_BCM_nReady,
    .IO_SIGNALS_CPS_SENS_WU      = &IO_CPS_SENS_WU,
    .IO_SIGNALS_BUTTON_SENS_WU   = &IO_BUTTON_SENS_WU,
    .IO_SIGNALS_SBC_Fault        = &IO_SBC_FAULT,
    .IO_SIGNALS_ISO_OK           = &IO_ISO_OK,
    .IO_SIGNALS_Slave_Interrupt  = &IO_NXP_CSC_INT,
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
const IO_Signals* io_getIoHardwareConfig(HWVERSION_STATUS hwVersion)
{
    const IO_Signals* pointer;
    switch(hwVersion)
    {
        case(HWVERSION1v0):
            pointer = &IO_SIGNAL_CONFIG_HW_1V0;
            break;
        default:
            pointer = &IO_SIGNAL_CONFIG_HW_1V0;
            break;
    }
    return pointer;
}
