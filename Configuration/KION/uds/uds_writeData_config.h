/**
 * @file uds_writeData_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


#pragma once


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "config_enable.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

typedef enum
{
    UDS_DATA_ID_OCV_Map                                         = 0x2000,
    UDS_DATA_ID_Ri_ch_Map                                       = 0x2001,
    UDS_DATA_ID_Ri_dch_Map                                      = 0x2002,
    UDS_DATA_ID_Capacity_Table                                  = 0x2003,
    UDS_DATA_ID_I_ch_cont_Map                                   = 0x2004,
    UDS_DATA_ID_I_ch_peak_Map                                   = 0x2005,
    UDS_DATA_ID_I_dch_cont_Map                                  = 0x2006,
    UDS_DATA_ID_I_dch_peak_Map                                  = 0x2007,
    UDS_DATA_ID_I_ch_cont_safety_Map                            = 0x2008,
    UDS_DATA_ID_I_ch_peak_safety_Map                            = 0x2009,
    UDS_DATA_ID_I_dch_cont_safety_Map                           = 0x200A,
    UDS_DATA_ID_I_dch_peak_safety_Map                           = 0x200B,
    UDS_DATA_ID_Aging_Map                                       = 0x200C,
    UDS_DATA_ID_HeatingFoil_Map                                 = 0x200D,
    UDS_DATA_ID_ntc_1_fusi                                      = 0x200E,
    UDS_DATA_ID_ntc_2_slave_PCB                                 = 0x200F,
    UDS_DATA_ID_LEM_DHAB_Sensor_Data                            = 0x2010,
    UDS_DATA_ID_I_ch_cont_Map_T_bins                            = 0x2020,
    UDS_DATA_ID_I_ch_peak_Map_T_bins                            = 0x2021,
    UDS_DATA_ID_I_dch_cont_Map_T_bins                           = 0x2022,
    UDS_DATA_ID_I_dch_peak_Map_T_bins                           = 0x2023,
    UDS_DATA_ID_I_ch_dsg_Map_SOC_bins                           = 0x2024,
    UDS_DATA_ID_I_ch_cont_safety_Map_T_bins                     = 0x2025,
    UDS_DATA_ID_I_ch_peak_safety_Map_T_bins                     = 0x2026,
    UDS_DATA_ID_I_dch_cont_safety_Map_T_bins                    = 0x2027,
    UDS_DATA_ID_I_dch_peak_safety_Map_T_bins                    = 0x2028,
    UDS_DATA_ID_I_ch_dsg_safety_Map_OCV_bins                    = 0x2029,
    UDS_DATA_ID_OCV_Ri_Map_T_Bins                               = 0x202A,
    UDS_DATA_ID_OCV_Ri_Map_SOC_Bins                             = 0x202B,
    UDS_DATA_ID_Capacity_Table_T_Bins                           = 0x202C,
    UDS_DATA_ID_Aging_Map_T_Bins                                = 0x202D,
    UDS_DATA_ID_HeatingFoil_Map_T_Bins                          = 0x202E,
    UDS_DATA_ID_U_Cell_Histogram_Bins                           = 0x2550,
    UDS_DATA_ID_U_Violation_Histogram_Bins                      = 0x2551,
    UDS_DATA_ID_U_T_Bat_Histogram_T_Bins                        = 0x2552,
    UDS_DATA_ID_U_T_Bat_Histogram_U_Bins                        = 0x2553,
    UDS_DATA_ID_T_Histogram_Bins                                = 0x2554,
    UDS_DATA_ID_I_Histogram_Bins                                = 0x2555,
    UDS_DATA_ID_I_Violation_Histogram_s_Bins                    = 0x2557,
    UDS_DATA_ID_PCB_Histogram_Bins                              = 0x2558,
    UDS_DATA_ID_BMS_Heating_Histogram_Bins                      = 0x2559,
    UDS_DATA_ID_BMS_Current_Violation_Log_Bins                  = 0x255B,
    UDS_DATA_ID_Security_Access_Test                            = 0x4014,
    UDS_DATA_ID_Battery_Configuration                           = 0x4200,
    UDS_DATA_ID_Cell_Configuration                              = 0x4201,
    UDS_DATA_ID_NTC_Setting_Configuration                       = 0x4202,
    UDS_DATA_ID_CAN_Configuration                               = 0x4203,
    UDS_DATA_ID_Contactor_Configuration                         = 0x4204,  // @req CB-10059
    UDS_DATA_ID_CPS_Configuration                               = 0x4206,
    UDS_DATA_ID_Heating_Controller_Configuration                = 0x4207,
    UDS_DATA_ID_Communication_Protocol_Configuration            = 0x4208,
    UDS_DATA_ID_Authentification_Configuration                  = 0x4209,
    UDS_DATA_ID_Components_Power_Consumption                    = 0x420A,
    UDS_DATA_ID_CPS_Settings_Configuration                      = 0x420C,
    UDS_DATA_ID_Pushbutton_Configuration                        = 0x420D,
    UDS_DATA_ID_Timeout_Shutdown_Configuration                  = 0x4220,
    UDS_DATA_ID_Timeout_OpenContactors_Configuration            = 0x4221,
    UDS_DATA_ID_PeriodicWakeUp_Configuration                    = 0x4222,
    UDS_DATA_ID_Emergency_Configuration                         = 0x4223,
    UDS_DATA_ID_Error_Configuration                             = 0x4224,
    UDS_DATA_ID_Shutdown_Configuration                          = 0x4225,
    UDS_DATA_ID_CPSout_Configuration                            = 0x4226,
    UDS_DATA_ID_Precharge_Configuration                         = 0x4227,
    UDS_DATA_ID_Periodic_Wakeup_Configuration                   = 0x4228,
    UDS_DATA_ID_S2_Precharge_Configuration                      = 0x422C,  // @req CB-92395
    UDS_DATA_ID_derating_param_limit_max_charge_current_100s    = 0x492F,
    UDS_DATA_ID_derating_param_limit_max_charge_discurrent_100s = 0x4930,
    UDS_DATA_ID_derating_param_limit_max_charge_current_2s      = 0x4931,
    UDS_DATA_ID_derating_param_limit_max_charge_discurrent_2s   = 0x4932,
    UDS_DATA_ID_derating_param_max_charge_voltage_offset        = 0x4933,
    UDS_DATA_ID_derating_param_drop_difference_discharge        = 0x4934,
    UDS_DATA_ID_derating_param_drop_difference_charge           = 0x4935,
    UDS_DATA_ID_derating_param_min_voltage_hysteresis           = 0x4936,
    UDS_DATA_ID_derating_param_max_voltage_hysteresis           = 0x4937,
    UDS_DATA_ID_derating_param_threshold_relative_linear        = 0x4938,
    UDS_DATA_ID_derating_param_threshold_linear_constant        = 0x4939,
    UDS_DATA_ID_derating_param_max_rate_relative                = 0x493A,
    UDS_DATA_ID_derating_param_max_rate_linear                  = 0x493B,
    UDS_DATA_ID_derating_param_diag_derating                    = 0x493C,
    UDS_DATA_ID_derating_param_discharge_voltage                = 0x493D,
    UDS_DATA_ID_derating_param_charge_voltage                   = 0x493E,
    UDS_DATA_ID_derating_param_regeneration_voltage             = 0x494F,
    UDS_DATA_ID_soc_param_max_current_ocv                       = 0x4968,
    UDS_DATA_ID_soc_param_min_ref_ocv                           = 0x4969,
    UDS_DATA_ID_soc_param_rest_time_ocv                         = 0x496A,
    UDS_DATA_ID_soc_param_min_voltage_ref_plausibility          = 0x496B,
    UDS_DATA_ID_soc_param_max_soc_rate                          = 0x496C,
    UDS_DATA_ID_soc_param_full_charge_soc_hysteresis            = 0x496D,
    UDS_DATA_ID_soc_param_full_charge_voltage_hysteresis        = 0x496E,
    UDS_DATA_ID_soc_param_full_charge_current_hysteresis        = 0x496F,
    UDS_DATA_ID_soc_param_cutoff_charge_current                 = 0x4970,
    UDS_DATA_ID_soc_param_cutoff_discharge_current              = 0x4971,
    UDS_DATA_ID_soc_param_depth_of_discharge                    = 0x4972,
    UDS_DATA_ID_soc_param_end_of_charge                         = 0x4973,
    UDS_DATA_ID_soc_param_discharge_soc_hysteresis              = 0x4974,
    UDS_DATA_ID_soc_param_discharge_voltage_hysteresis          = 0x4975,
    UDS_DATA_ID_ttf_learn_output_i_O                            = 0x49A0,
    UDS_DATA_ID_ttf_learn_output_i_cutoff                       = 0x49A1,
    UDS_DATA_ID_ttf_learn_output_tcv                            = 0x49A2,
    UDS_DATA_ID_ttf_learn_output_soc_cc_cv                      = 0x49A3,
    UDS_DATA_ID_soh_param_soh_end_of_life                       = 0x49C8,
    UDS_DATA_ID_soh_param_cycles_end_of_life                    = 0x49C9,
    UDS_DATA_ID_soh_param_dod_cycle_counter                     = 0x49CA,
    UDS_DATA_ID_soh_param_eoc_cycle_counter                     = 0x49CB,
    UDS_DATA_ID_soh_param_calendar_age_end_of_life              = 0x49CC,
    UDS_DATA_ID_soh_param_soh_calendar_end_of_life              = 0x49CD,
    UDS_DATA_ID_ttf_learn_param_time_wws                        = 0x49A7,
    UDS_DATA_ID_ttf_learn_param_soc_cutoff                      = 0x49A8,
    UDS_DATA_ID_ttf_learn_param_lambda_cc_cv                    = 0x49A9,
    UDS_DATA_ID_ttf_learn_param_lambda_cv_end                   = 0x49AA,
    UDS_DATA_ID_ttf_learn_param_i_error                         = 0x49AB,
    UDS_DATA_ID_battery_powerpath_connection_analysis_settings  = 0x5010,
    UDS_DATA_ID_lib_battery_capacity_measurement_settings       = 0x5015,
    UDS_DATA_ID_lib_charge_current_manual_override              = 0x501A,
    UDS_DATA_ID_lib_charge_current_manual_control               = 0x501B,
    UDS_DATA_ID_lib_heating_manual_override                     = 0x5020,
    UDS_DATA_ID_lib_heating_manual_control                      = 0x5021,
    UDS_DATA_ID_Invocations                                     = 0x5022,
    UDS_DATA_ID_balancing_param_stop_diff                       = 0x5023,
    UDS_DATA_ID_balancing_param_start_diff                      = 0x5024,
    UDS_DATA_ID_LIB_Manufacturer                                = 0x4100,
    UDS_DATA_ID_LIB_Manufacturing_Date                          = 0x4101,
    UDS_DATA_ID_LIB_Device_Name                                 = 0x4102,
    UDS_DATA_ID_LIB_Tray_Variant                                = 0x4103,
    UDS_DATA_ID_LIB_Cell_Type                                   = 0x4104,
    UDS_DATA_ID_LIB_KION_Hardware_Number                        = 0x4105,
    UDS_DATA_ID_LIB_KION_Part_Number                            = 0x4106,
    UDS_DATA_ID_LIB_KION_ZSB_Number                             = 0x4107,
    UDS_DATA_ID_LIB_KION_Order_Number                           = 0x4108,
    UDS_DATA_ID_LIB_KION_Customer_Order_Number                  = 0x4109,
    UDS_DATA_ID_LIB_KION_Sequence_Number                        = 0x410A,
    UDS_DATA_ID_LIB_KBS_BPN                                     = 0x410B,
    UDS_DATA_ID_LIB_KBS_Serial_Number                           = 0x410C,
    UDS_DATA_ID_LIB_KBS_Part_Number                             = 0x410D,
    UDS_DATA_ID_LIB_Parameter_Version                           = 0x410E,
    UDS_DATA_ID_LIB_EOL_Test_Result                             = 0x410F,
    UDS_DATA_ID_LIB_Nameplate                                   = 0x4110,
    UDS_DATA_ID_LIB_Master_PCB_Identification                   = 0x4112,
    UDS_DATA_ID_LIB_Master_PCB_EOL_Test_Result                  = 0x4113,
    UDS_DATA_ID_LIB_CPS_PCB_Identification                      = 0x4114,
    UDS_DATA_ID_LIB_CPS_PCB_EOL_Test_Result                     = 0x4115,
    UDS_DATA_ID_BMS_Diagnostic_Variant_ID                       = 0xF100,
    UDS_DATA_ID_BMS_Brand_ID                                    = 0xF101,
    UDS_DATA_ID_BMS_ECU_Hardware_Version_Number                 = 0xF111,
    UDS_DATA_ID_BMS_VIN_Availability                            = 0xF121,
    UDS_DATA_ID_BMS_ECU_Manfufacturing_Date                     = 0xF18B,
    UDS_DATA_ID_BMS_ECU_Serial_Number                           = 0xF18C,
    UDS_DATA_ID_BMS_Vehicle_Identification_Number               = 0xF190,
    UDS_DATA_ID_BMS_Vehicle_Manufacturer_ECU_Hardware_Number    = 0xF191,
    UDS_DATA_ID_BMS_System_Name_or_Engine_Type                  = 0xF197,
    UDS_DATA_ID_repair_shop_code_or_tester_serial_number        = 0xF198,
    UDS_DATA_ID_BMS_ECU_Installation_Date                       = 0xF19D,
    UDS_DATA_ID_lib_average_power_consumption                   = 0x4303,
    UDS_DATA_ID_lib_time_till_end_of_shift                      = 0x4304,
    UDS_DATA_ID_lib_available_charging_power                    = 0x4305,
    UDS_DATA_ID_lib_charging_time_end_of_shift_soc_buffer       = 0x4308,
    UDS_DATA_ID_lib_battery_powerpath_connection_analysis_start = 0x4309,
    UDS_DATA_ID_lib_battery_capacity_measurement_start          = 0x4311,
    UDS_DATA_ID_cps_monitor_cps_out_error_limit                 = 0x4E80,

    // CB BMS
    UDS_DATA_ID_PARAM_Current_Sensor_Config  = 0x4205,
    UDS_DATA_ID_PARAM_Peak_CH_Current_TH2    = 0x4E1B,
    UDS_DATA_ID_PARAM_Peak_DCH_Current_TH2   = 0x4E1F,
    UDS_DATA_ID_PARAM_Current_Interpretation = 0x420E,
} UDS_Data_ID_Kion;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
