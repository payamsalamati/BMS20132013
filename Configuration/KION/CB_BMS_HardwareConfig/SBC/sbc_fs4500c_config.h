/*
 * @file    sbc_fs4500c.h
 *
 * @copyright (c) Futavis GmbH, Aachen 2017 - alle Rechte vorbehalten
 * @brief   Configurations of the NXP FS4500C system basis chip
 */

#pragma once

//***************************************************************************/
//************************** INCLUDES ***************************************/
//***************************************************************************/

#include "sbc.h"
#include "sbc_fs4500c_private.h"

//***************************************************************************/
//************************** PUBLIC TYPEDEFS ********************************/
//***************************************************************************/
typedef enum
{
    SBC_DEVICE_FS4500C = 0,
} SBC_Device;

#define FS4500C_nDEVICES 1U


//************************** HARDWARECONFIG*****************************************//
#define SBC_FS4500C_HW_CONFIG_LDT CONFIG_ENABLED
#define SBC_FS4500C_HW_CONFIG_LIN CONFIG_DISABLED

#define SBC_FS4500C_HW_CONFIG_LS_DETECT_V_PRE SBC_FS4500C_BUCK_BOOST

//************************** Watchdog Error Msk*****************************************//
#define SBC_FS4500C_WATCHDOG_ERROR_MSK (SBC_FS4500C_WATCHDOG_ANSWER_BAD_DATA_MSK                  \
                                        | SBC_FS4500C_WATCHDOG_ANSWER_BAD_TIMING_MSK              \
                                        | SBC_FS4500C_WATCHDOG_ANSWER_INTERNAL_HARDWARE_ERROR_MSK \
                                        | SBC_FS4500C_WATCHDOG_ANSWER_INTERNAL_SOFTWARE_ERROR_MSK)


//************************** MAIN MACHINE REGISTERS ********************************//

// INIT_VREG_CONFIG
#define SBC_FS4500C_INIT_VREG_CONFIG_ICCA_LIM     SBC_FS4500C_ENABLE   // I_cca limited to internal MOSFET
#define SBC_FS4500C_INIT_VREG_CONFIG_TCCA_LIM_OFF SBC_FS4500C_DISABLE  // current limit duration before VCCA is switched off(Disable = 10ms, Enable = 50ms)
#define SBC_FS4500C_INIT_VREG_CONFIG_IPFF_DIS     SBC_FS4500C_DISABLE  // input power feed forward (IPFF) function of VPRE
#define SBC_FS4500C_INIT_VREG_CONFIG_VCAN_OV_MON  SBC_FS4500C_DISABLE  // CAN_5V overvoltage monitoring
#define SBC_FS4500C_INIT_VREG_CONFIG_TAUX_LIM_OFF SBC_FS4500C_DISABLE  // current limit duration before VAUX is switched off(Disable = 10ms, Enable = 50ms)
#define SBC_FS4500C_INIT_VREG_CONFIG_VAUX_TRK_EN  SBC_FS4500C_DISABLE  // VAUX regulator as a tracker of VCCA
#define SBC_FS4500C_INIT_VREG_CONFIG              (SBC_FS4500C_INIT_VREG_CONFIG_ICCA_LIM << SBC_FS4500C_INIT_VREG_ICCA_LIM_POS \
                                      | SBC_FS4500C_INIT_VREG_CONFIG_TCCA_LIM_OFF << SBC_FS4500C_INIT_VREG_TCCA_LIM_OFF_POS    \
                                      | SBC_FS4500C_INIT_VREG_CONFIG_IPFF_DIS << SBC_FS4500C_INIT_VREG_IPFF_DIS_POS            \
                                      | SBC_FS4500C_INIT_VREG_CONFIG_VCAN_OV_MON << SBC_FS4500C_INIT_VREG_VCAN_OV_MON_POS      \
                                      | SBC_FS4500C_INIT_VREG_CONFIG_TAUX_LIM_OFF << SBC_FS4500C_INIT_VREG_TAUX_LIM_OFF_POS    \
                                      | SBC_FS4500C_INIT_VREG_CONFIG_VAUX_TRK_EN << SBC_FS4500C_INIT_VREG_VAUX_TRK_EN_POS)

// INIT_WU1_CONFIG
#define SBC_FS4500C_INIT_WU1_CONFIG_IO0 SBC_FS4500C_WAKE_UP_RISING_EDGE  // IO_0 wake-up configuration
#define SBC_FS4500C_INIT_WU1_CONFIG_IO2 SBC_FS4500C_WAKE_UP_NO_WU        // IO_2 wake-up configuration
#define SBC_FS4500C_INIT_WU1_CONFIG_IO3 SBC_FS4500C_WAKE_UP_RISING_EDGE  // IO_3 wake-up configurations
#define SBC_FS4500C_INIT_WU1_CONFIG_IO4 SBC_FS4500C_WAKE_UP_RISING_EDGE  // IO_4 wake-up configuration
#define SBC_FS4500C_INIT_WU1_CONFIG     (SBC_FS4500C_INIT_WU1_CONFIG_IO0 << SBC_FS4500C_INIT_WU1_IO_0_POS \
                                     | SBC_FS4500C_INIT_WU1_CONFIG_IO2 << SBC_FS4500C_INIT_WU1_IO_2_POS   \
                                     | SBC_FS4500C_INIT_WU1_CONFIG_IO3 << SBC_FS4500C_INIT_WU1_IO_3_POS   \
                                     | SBC_FS4500C_INIT_WU1_CONFIG_IO4 << SBC_FS4500C_INIT_WU1_IO_4_POS)

// INIT_WU2_CONFIG
#define SBC_FS4500C_INIT_WU2_CONFIG_WU_IO5        SBC_FS4500C_WAKE_UP_NO_WU  // IO_5 wake-up configuration
#define SBC_FS4500C_INIT_WU2_CONFIG_CAN_DIS_CFG   SBC_FS4500C_DISABLE        // CAN behavior when FS1B is asserted low(Disable = RX only mode, Enable = CAN sleep mode)
#define SBC_FS4500C_INIT_WU2_CONFIG_CAN_WU_TO     SBC_FS4500C_DISABLE        // CAN wake-up timeout(Disable = 120us, Enable = 2.8ms)
#define SBC_FS4500C_INIT_WU2_CONFIG_LIN_J2602_DIS SBC_FS4500C_DISABLE        // Compliant with J2602 standard
#define SBC_FS4500C_INIT_WU2_CONFIG_LIN_SR        0b00u                      // Configure the LIN slew rate: 20 kbits/s
#define SBC_FS4500C_INIT_WU2_CONFIG               (SBC_FS4500C_INIT_WU2_CONFIG_WU_IO5 << SBC_FS4500C_INIT_WU2_IO_5_POS     \
                                     | SBC_FS4500C_INIT_WU2_CONFIG_CAN_DIS_CFG << SBC_FS4500C_INIT_WU2_CAN_DIS_CFG_POS     \
                                     | SBC_FS4500C_INIT_WU2_CONFIG_CAN_WU_TO << SBC_FS4500C_INIT_WU2_CAN_WU_TO_POS         \
                                     | SBC_FS4500C_INIT_WU2_CONFIG_LIN_J2602_DIS << SBC_FS4500C_INIT_WU2_LIN_J2602_DIS_POS \
                                     | SBC_FS4500C_INIT_WU2_CONFIG_LIN_SR << SBC_FS4500C_INIT_WU2_LIN_SR_POS)

// INIT_INT_CONFIG
#define SBC_FS4500C_INIT_INT_CONFIG_DURATION SBC_FS4500C_DISABLE  // duration of the interrupt pulse(Disable = 100us, Enable = 25us)
#define SBC_FS4500C_INIT_INT_CONFIG_LIN      SBC_FS4500C_DISABLE  // Inhibit the interrupt for LIN error bits
#define SBC_FS4500C_INIT_INT_CONFIG_ALL      SBC_FS4500C_DISABLE  // Inhibit ALL the interrupt
#define SBC_FS4500C_INIT_INT_CONFIG_VSNS     SBC_FS4500C_DISABLE  // Inhibit the interrupt for VSNS_UV
#define SBC_FS4500C_INIT_INT_CONFIG_VPRE     SBC_FS4500C_DISABLE  // Inhibit the interrupt for VPRE status event
#define SBC_FS4500C_INIT_INT_CONFIG_VCORE    SBC_FS4500C_DISABLE  // Inhibit the interrupt for VCORE status event
#define SBC_FS4500C_INIT_INT_CONFIG_VOTHER   SBC_FS4500C_DISABLE  // Inhibit the interrupt for VCCA/VAUX and VCAN status event
#define SBC_FS4500C_INIT_INT_CONFIG_CAN      SBC_FS4500C_DISABLE  // Inhibit the interrupt for CAN error bits
#define SBC_FS4500C_INIT_INT_CONFIG          (SBC_FS4500C_INIT_INT_CONFIG_DURATION << SBC_FS4500C_INIT_INT_DURATION_POS \
                                     | SBC_FS4500C_INIT_INT_CONFIG_LIN << SBC_FS4500C_INIT_INT_LIN_POS                  \
                                     | SBC_FS4500C_INIT_INT_CONFIG_ALL << SBC_FS4500C_INIT_INT_ALL_POS                  \
                                     | SBC_FS4500C_INIT_INT_CONFIG_VSNS << SBC_FS4500C_INIT_INT_VSNS_POS                \
                                     | SBC_FS4500C_INIT_INT_CONFIG_VPRE << SBC_FS4500C_INIT_INT_VPRE_POS                \
                                     | SBC_FS4500C_INIT_INT_CONFIG_VCORE << SBC_FS4500C_INIT_INT_VCORE_POS              \
                                     | SBC_FS4500C_INIT_INT_CONFIG_VOTHER << SBC_FS4500C_INIT_INT_VOTHER_POS            \
                                     | SBC_FS4500C_INIT_INT_CONFIG_CAN << SBC_FS4500C_INIT_INT_CAN_POS)

// INIT_INH_INT_CONFIG
#define SBC_FS4500C_INIT_INH_INT_CONFIG_IO_0 SBC_FS4500C_DISABLE  // Inhibit the interrupt pulse for IO_0
#define SBC_FS4500C_INIT_INH_INT_CONFIG_IO_2 SBC_FS4500C_DISABLE  // Inhibit the interrupt pulse for IO_2
#define SBC_FS4500C_INIT_INH_INT_CONFIG_IO_3 SBC_FS4500C_DISABLE  // Inhibit the interrupt pulse for IO_3
#define SBC_FS4500C_INIT_INH_INT_CONFIG_IO_4 SBC_FS4500C_DISABLE  // Inhibit the interrupt pulse for IO_4
#define SBC_FS4500C_INIT_INH_INT_CONFIG_IO_5 SBC_FS4500C_DISABLE  // Inhibit the interrupt pulse for IO_5
#define SBC_FS4500C_INIT_INH_INT_CONFIG      (SBC_FS4500C_INIT_INH_INT_CONFIG_IO_0 << SBC_FS4500C_INIT_INT_INH_IO_0_POS \
                                         | SBC_FS4500C_INIT_INH_INT_CONFIG_IO_2 << SBC_FS4500C_INIT_INT_INH_IO_2_POS    \
                                         | SBC_FS4500C_INIT_INH_INT_CONFIG_IO_3 << SBC_FS4500C_INIT_INT_INH_IO_3_POS    \
                                         | SBC_FS4500C_INIT_INH_INT_CONFIG_IO_4 << SBC_FS4500C_INIT_INT_INH_IO_4_POS    \
                                         | SBC_FS4500C_INIT_INH_INT_CONFIG_IO_5 << SBC_FS4500C_INIT_INT_INH_IO_5_POS)

// LONG_DURATION_TIMER_CONFIG
#define SBC_FS4500C_LONG_DURATION_TIMER_CONFIG_FCNT       SBC_FS4500C_LONG_DURATION_TIMER_FCNT4
#define SBC_FS4500C_LONG_DURATION_TIMER_CONFIG_REG_SE     SBC_FS4500C_DISABLE  // Counter register selection(Disable = Read programmed wake-up register, Enable = Read real time counter into wake-up register)
#define SBC_FS4500C_LONG_DURATION_TIMER_CONFIG_LDT_MODE   SBC_FS4500C_ENABLE   // Operating mode selection(Disable = Calibration mode, Enable = Normal mode)
#define SBC_FS4500C_LONG_DURATION_TIMER_CONFIG_LDT_ENABLE SBC_FS4500C_DISABLE  // LDT counter control
#define SBC_FS4500C_LONG_DURATION_TIMER_CONFIG            (SBC_FS4500C_LONG_DURATION_TIMER_CONFIG_FCNT << SBC_FS4500C_LDT_FUNCTION_POS \
                                                | SBC_FS4500C_LONG_DURATION_TIMER_CONFIG_REG_SE << SBC_FS4500C_LDT_REG_SE_POS          \
                                                | SBC_FS4500C_LONG_DURATION_TIMER_CONFIG_LDT_MODE << SBC_FS4500C_LDT_MODE_POS          \
                                                | SBC_FS4500C_LONG_DURATION_TIMER_CONFIG_LDT_ENABLE << SBC_FS4500C_LDT_ENABLE_POS)


// MODE_CONFIG
#define SBC_FS4500C_MODE_CONFIG_VKAM_EN       SBC_FS4500C_DISABLE  // VKAM control
#define SBC_FS4500C_MODE_CONFIG_LPOFF_AUTO_WU SBC_FS4500C_DISABLE  // Configure the device in LPOFF_AUTO_WU(Disable = no action, Enable = Go to LPOFF mode and wake-up automatically after 1.0 ms)
#define SBC_FS4500C_MODE_CONFIG_GO_LPOFF      SBC_FS4500C_DISABLE  // Configure the device in LPOFF-SLEEP(Disable = no action, Enable = Go to LPOFF mode and wait for wake-up event)
#define SBC_FS4500C_MODE_CONFIG_INT_REQ       SBC_FS4500C_DISABLE  // Request for an INT pulse
#define SBC_FS4500C_MODE_CONFIG               (SBC_FS4500C_MODE_CONFIG_VKAM_EN << SBC_FS4500C_MODE_VKAM_EN_POS \
                                 | SBC_FS4500C_MODE_CONFIG_LPOFF_AUTO_WU << SBC_FS4500C_MODE_LPOFF_AUTO_WU_POS \
                                 | SBC_FS4500C_MODE_CONFIG_GO_LPOFF << SBC_FS4500C_MODE_GO_LPOFF_POS           \
                                 | SBC_FS4500C_MODE_CONFIG_INT_REQ << SBC_FS4500C_MODE_INT_REQ_POS)

#define SBC_FS4500C_MODE_SLEEP_CONFIG_VKAM_EN       SBC_FS4500C_DISABLE  // VKAM control
#define SBC_FS4500C_MODE_SLEEP_CONFIG_LPOFF_AUTO_WU SBC_FS4500C_DISABLE  // Configure the device in LPOFF_AUTO_WU(Disable = no action, Enable = Go to LPOFF mode and wake-up automatically after 1.0 ms)
#define SBC_FS4500C_MODE_SLEEP_CONFIG_GO_LPOFF      SBC_FS4500C_ENABLE   // Configure the device in LPOFF-SLEEP(Disable = no action, Enable = Go to LPOFF mode and wait for wake-up event)
#define SBC_FS4500C_MODE_SLEEP_CONFIG_INT_REQ       SBC_FS4500C_DISABLE  // Request for an INT pulse
#define SBC_FS4500C_MODE_SLEEP_CONFIG               (SBC_FS4500C_MODE_SLEEP_CONFIG_VKAM_EN << SBC_FS4500C_MODE_VKAM_EN_POS \
                                       | SBC_FS4500C_MODE_SLEEP_CONFIG_LPOFF_AUTO_WU << SBC_FS4500C_MODE_LPOFF_AUTO_WU_POS \
                                       | SBC_FS4500C_MODE_SLEEP_CONFIG_GO_LPOFF << SBC_FS4500C_MODE_GO_LPOFF_POS           \
                                       | SBC_FS4500C_MODE_SLEEP_CONFIG_INT_REQ << SBC_FS4500C_MODE_INT_REQ_POS)

// REG_MODE_CONFIG
#define SBC_FS4500C_REG_MODE_CONFIG_VCORE_EN SBC_FS4500C_ENABLE  // VCORE control
#define SBC_FS4500C_REG_MODE_CONFIG_VCCA_EN  SBC_FS4500C_ENABLE  // VCCA control
#define SBC_FS4500C_REG_MODE_CONFIG_VAUX_EN  SBC_FS4500C_ENABLE  // VAUX control
#define SBC_FS4500C_REG_MODE_CONFIG_VCAN_EN  SBC_FS4500C_ENABLE  // VCAN control
#define SBC_FS4500C_REG_MODE_CONFIG          (SBC_FS4500C_REG_MODE_CONFIG_VCORE_EN << SBC_FS4500C_REG_MODE_WRITE_VCORE_EN_POS \
                                     | SBC_FS4500C_REG_MODE_CONFIG_VCCA_EN << SBC_FS4500C_REG_MODE_WRITE_VCCA_EN_POS          \
                                     | SBC_FS4500C_REG_MODE_CONFIG_VAUX_EN << SBC_FS4500C_REG_MODE_WRITE_VAUX_EN_POS          \
                                     | SBC_FS4500C_REG_MODE_CONFIG_VCAN_EN << SBC_FS4500C_REG_MODE_WRITE_VCAN_EN_POS)

// IO_OUT_AUX_CONFIG
#define SBC_FS4500C_IO_OUT_AMUX_CONFIG_IO_OUT_4_EN SBC_FS4500C_DISABLE  // output gate driver capability for IO_4(Disable = High-impedance (IO_4 configured as input), Enable = Enabled (IO_4 configured as output gate driver))
#define SBC_FS4500C_IO_OUT_AMUX_CONFIG_IO_OUT_4    SBC_FS4500C_DISABLE  // IO_4 output gate driver state
#define SBC_FS4500C_IO_OUT_AMUX_CONFIG_AMUX        0b000                // Select AMUX output, default = 0b000
#define SBC_FS4500C_IO_OUT_AMUX_CONFIG             (SBC_FS4500C_IO_OUT_AMUX_CONFIG_IO_OUT_4_EN << SBC_FS4500C_IO_OUT_AMUX_IO_4_EN_POS \
                                        | SBC_FS4500C_IO_OUT_AMUX_CONFIG_IO_OUT_4 << SBC_FS4500C_IO_OUT_AMUX_IO_4_POS                 \
                                        | SBC_FS4500C_IO_OUT_AMUX_CONFIG_AMUX << SBC_FS4500C_IO_OUT_AMUX_AMUX_POS)


// CAN_LIN_MODE_CONFIG
#define SBC_FS4500C_CAN_LIN_MODE_CONFIG_CAN_MODE     SBC_FS4500C_CAN_LIN_MODE_NORMAL_OP
#define SBC_FS4500C_CAN_LIN_MODE_CONFIG_CAN_AUTO_DIS SBC_FS4500C_ENABLE  //  no Automatic CAN mode disable
#define SBC_FS4500C_CAN_LIN_MODE_CONFIG_LIN_MODE     SBC_FS4500C_CAN_LIN_MODE_SLEEP_NO_WU
#define SBC_FS4500C_CAN_LIN_MODE_CONFIG_LIN_AUTO_DIS SBC_FS4500C_DISABLE  //  no Automatic LIN mode disable
#define SBC_FS4500C_CAN_LIN_MODE_CONFIG              (SBC_FS4500C_CAN_LIN_MODE_CONFIG_CAN_MODE << SBC_FS4500C_CAN_LIN_MODE_CAN_MODE_POS \
                                         | SBC_FS4500C_CAN_LIN_MODE_CONFIG_CAN_AUTO_DIS << SBC_FS4500C_CAN_LIN_MODE_CAN_AUTO_DIS_POS    \
                                         | SBC_FS4500C_CAN_LIN_MODE_CONFIG_LIN_MODE << SBC_FS4500C_CAN_LIN_MODE_LIN_MODE_POS            \
                                         | SBC_FS4500C_CAN_LIN_MODE_CONFIG_LIN_AUTO_DIS << SBC_FS4500C_CAN_LIN_MODE_LIN_AUTO_DIS_POS)


#define SBC_FS4500C_CAN_LIN_MODE_SLEEP_CONFIG_CAN_MODE     SBC_FS4500C_CAN_LIN_MODE_SLEEP_NO_WU
#define SBC_FS4500C_CAN_LIN_MODE_SLEEP_CONFIG_CAN_AUTO_DIS SBC_FS4500C_ENABLE  //
#define SBC_FS4500C_CAN_LIN_MODE_SLEEP_CONFIG_LIN_MODE     SBC_FS4500C_CAN_LIN_MODE_SLEEP_NO_WU
#define SBC_FS4500C_CAN_LIN_MODE_SLEEP_CONFIG_LIN_AUTO_DIS SBC_FS4500C_DISABLE  //  no Automatic LIN mode disable
#define SBC_FS4500C_CAN_LIN_MODE_SLEEP_CONFIG              (SBC_FS4500C_CAN_LIN_MODE_SLEEP_CONFIG_CAN_MODE << SBC_FS4500C_CAN_LIN_MODE_CAN_MODE_POS \
                                               | SBC_FS4500C_CAN_LIN_MODE_SLEEP_CONFIG_CAN_AUTO_DIS << SBC_FS4500C_CAN_LIN_MODE_CAN_AUTO_DIS_POS    \
                                               | SBC_FS4500C_CAN_LIN_MODE_SLEEP_CONFIG_LIN_MODE << SBC_FS4500C_CAN_LIN_MODE_LIN_MODE_POS            \
                                               | SBC_FS4500C_CAN_LIN_MODE_SLEEP_CONFIG_LIN_AUTO_DIS << SBC_FS4500C_CAN_LIN_MODE_LIN_AUTO_DIS_POS)

//************************** FAIL-SAFE REGISTERS ************************************//
#define SBC_FS4500C_INIT_FS1B_TIMING_CONFIG       0b01100101  // default (37ms time range)
#define SBC_FS4500C_INIT_SUPERVISOR_CONFIG        0b00001100  // default (normal undervoltage detection threshold, FS1B timing factor = 1x)
#define SBC_FS4500C_INIT_FAULT_CONFIG             0b00001100  // FS1B has no impact on CAN
#define SBC_FS4500C_INIT_FSSM_CONFIG              0b00001100  // FFCU monitoring disabled, RSTB low duration = 10ms
#define SBC_FS4500C_INIT_SF_IMPACT_CONFIG         0b00011000  // default (FS1B t_delay mode, RSTB assert at WD_CNT_ERR max value)
#define SBC_FS4500C_INIT_WD_CNT_CONFIG            0b00001100  // default (maximum counter values = 6)
#define SBC_FS4500C_INIT_VCORE_OVUV_IMPACT_CONFIG 0b11100111  // default (VCORE overvoltage impacts RSTB & FS0B, VCORE undervoltage impacts FS0B)
#define SBC_FS4500C_INIT_VCCA_OVUV_IMPACT_CONFIG  0b11100111  // default (VCCA overvoltage impacts RSTB & FS0B, VCCA undervoltage impacts FS0B)
#define SBC_FS4500C_INIT_VAUX_OVUV_IMPACT_CONFIG  0b11100111  // default (VAUX overvoltage impacts RSTB & FS0B, VAUX undervoltage impacts FS0B)
