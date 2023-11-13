
/**
 * @file     dem_config.h
 * @copyright � Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @author   Oliver Blasius
 * @date     04.02.2019
 * @version  1.0
 * @brief    Short description
 * @details
 *  <b>Eindeutige Modulnummer</b>

 *  <b>Beschreibung</b>

 *  Detaillierte Beschreibung des Moduls
 *  <b>Globale Variablen</b>
 *
 *   <b>Schnittstellen zu anderen Modulen</b>

 *   <b>Eingabedaten</b>

 *   <b>Ausgabedaten</b>
 *
 *
 *  <b>�nderungen</b>
 *  - Ersterstellung Oliver Blasius, 04.02.2019
 */

#pragma once


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#if !defined(UNIT_TEST)
#include "batteryModule_config.h"
#endif

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define DEM_ENABLED  1
#define DEM_DISABLED 0

/**
 * @brief activate or deactivate internal DTCs
 */
// #define INTERNAL_USE

/**
 * @def DEM_MAIN_FUNCTION_CYCLE_TIME
 * @brief configure the cycle time of the module in ms
 */
#define DEM_MAIN_FUNCTION_CYCLE_TIME 10U

#if DEM_MAIN_FUNCTION_CYCLE_TIME % 10 != 0
#error invalid DEM Config
#endif


#if defined(UNIT_TEST)

#define DEM_MAX_FREEZE_FRAME_SIZE  40U
#define DEM_MAX_EXTENDED_DATA_SIZE 40U

#define DEM_MAX_NUMBER_OF_FREEZE_FRAME_RAM 5U
#define DEM_MAX_NUMBER_OF_FREEZE_FRAME_NVM 5U

#if DEM_MAX_NUMBER_OF_FREEZE_FRAME_RAM < DEM_MAX_NUMBER_OF_FREEZE_FRAME_NVM
#error "number of freeze frames in ram must be equal to number of freeze frames in nvm"
#endif

#define DEM_MAX_NUMBER_OF_EXTENDED_DATA_RAM 10U
#define DEM_MAX_NUMBER_OF_EXTENDED_DATA_NVM 50U

#define DEM_FAULT_MEMORY_ADDRESS 0x00
#define DEM_FAULT_MEMORY_SIZE    sizeof(DEM_FaultMemory)


// Length of the OS Queue, only needed when DEM_OS Enabled
#define DEM_QUEUE_LENGTH 10U

// this determines how many faults the module is able to handle at the same time
#define DEM_FAULT_CODES_MAX 100U

#else

#define DEM_MAX_FREEZE_FRAME_SIZE  40U
#define DEM_MAX_EXTENDED_DATA_SIZE 40U

#define DEM_MAX_NUMBER_OF_FREEZE_FRAME_RAM 50U
#define DEM_MAX_NUMBER_OF_FREEZE_FRAME_NVM 50U

#if DEM_MAX_NUMBER_OF_FREEZE_FRAME_RAM < DEM_MAX_NUMBER_OF_FREEZE_FRAME_NVM
#error "number of freeze frames in ram must be equal to number of freeze frames in nvm"
#endif

#define DEM_MAX_NUMBER_OF_EXTENDED_DATA_RAM 10U
#define DEM_MAX_NUMBER_OF_EXTENDED_DATA_NVM 50U

#define DEM_FAULT_MEMORY_ADDRESS 0x00
#define DEM_FAULT_MEMORY_SIZE    sizeof(DEM_FaultMemory)


// Length of the OS Queue, only needed when DEM_OS Enabled
#define DEM_QUEUE_LENGTH         80U

// this determines how many faults the module is able to handle at the same time
#define DEM_FAULT_CODES_MAX      100U

#endif

#define DTC_ONBOARD_TEMP_SENSOR 8  // Muss Kion kommuniziert werden


#define DTC_CONTACTOR_HISTOGRAM_LIMIT_WARNING 0  // kann nicht ausgelöst werden
#define DTC_CONTACTOR_HISTOGRAM_LIMIT_ALERT   0  // kann nicht ausgelöst werden
#define DTC_CONTACTOR_HISTOGRAM_LIMIT_ERROR   0  // kann nicht ausgelöst werden
#define DTC_CURRENT_SENSOR_BATTERY_IMBALANCE  0  // kann nicht ausgelöst werden

#define DEM_NVM_CONFIG CONFIG_ENABLED

typedef enum
{
    DTC_OS_MUTEX_PEND_FAULT                            = 0x1a0000,
    DTC_OS_MUTEX_POST_FAULT                            = 0x1b0000,
    DTC_CONTACTOR_DIAG_ERROR                           = 0x360000,
    DTC_PRECHARGE_TIMEOUT                              = 0xef0000,
    DTC_HW_VERSION_MISMATCH                            = 0x410000,
    DTC_TASK_TIMING_MALFUNCTIONING                     = 0x600000,
    DTC_TASK_MPU_TRIGGERED                             = 0x610000,
    DTC_CAN_SEND_DRIVER_ERROR                          = 0x970000,
    DTC_CAN_QUEUE_FULL                                 = 0x980000,
    DTC_CONTACTOR_DRIVER_ERROR                         = 0xc50000,
    DTC_AFE_CHECK_SM_FAILED                            = 0xd60000,
    DTC_AFE_CHECK_SM_ERROR_DETECTED                    = 0xd70000,
    DTC_AFE_CHECK_HIL_APROVED_SM_ERROR_DETECTED        = 0xd80000,
    DTC_BALANCING_OVER_TEMPERATURE_ALERT               = 0xea0000,
    DTC_AUX_RELAY_DRIVER_ERROR                         = 0xfc0000,
    DTC_NVM_ERROR                                      = 0xb00000,
    DTC_VOLTAGE_DRIVER_ERROR                           = 0xce0000,
    DTC_SBC_WATCHDOG_ERROR                             = 0xc10000,
    DTC_SBC_DIAGNOSIS_ERROR                            = 0xc00000,
    DTC_ICD_COM_FAULT                                  = 0x380096,
    DTC_ICD_SENSOR_MEASUREMENT_FAULT                   = 0x380098,
    DTC_ICD_SENSOR_SYSTEM_FAULT                        = 0x380099,
    DTC_ICD_CONFIGURATION_INVALID                      = 0x380095,
    DTC_ICD_RESULT_RC_FAULT                            = 0x380093,
    DTC_ICD_SENSOR_PERSISTENT_FAULT                    = 0x380097,
    DTC_CELL_OVER_VOLTAGE_WARNING                      = 0x380050,
    DTC_CELL_OVER_VOLTAGE_ALERT                        = 0x380051,
    DTC_CELL_OVER_VOLTAGE_ERROR                        = 0x380052,
    DTC_CELL_UNDER_VOLTAGE_WARNING                     = 0x380053,
    DTC_CELL_UNDER_VOLTAGE_ALERT                       = 0x380054,
    DTC_CELL_UNDER_VOLTAGE_ERROR                       = 0x380055,
    DTC_DEEP_DISCHARGE                                 = 0x380058,
    DTC_DEEP_DISCHARGE_CELL_DAMAGE_ERROR               = 0x380059,
    DTC_CELL_VOLTAGE_IMBALANCE_WARNING                 = 0x380165,
    DTC_CELL_VOLTAGE_IMBALANCE_ERROR                   = 0x380166,
    DTC_CELL_HIGH_TEMPERATURE_WARNING                  = 0x380060,
    DTC_CELL_HIGH_TEMPERATURE_ALERT                    = 0x380061,
    DTC_CELL_HIGH_TEMPERATURE_ERROR                    = 0x380062,
    DTC_CELL_LOW_TEMPERATURE_WARNING                   = 0x380063,
    DTC_CELL_LOW_TEMPERATURE_ALERT                     = 0x380064,
    DTC_CELL_LOW_TEMPERATURE_ERROR                     = 0x380065,
    DTC_CURRENT_PEAK_CHARGE_THRESHOLD_1                = 0x380080,
    DTC_CURRENT_PEAK_CHARGE_THRESHOLD_2                = 0x380081,
    DTC_CURRENT_CONT_CHARGE_THRESHOLD_1                = 0x380082,
    DTC_CURRENT_CONT_CHARGE_THRESHOLD_2                = 0x380083,
    DTC_CURRENT_PEAK_DISCHARGE_THRESHOLD_1             = 0x380084,
    DTC_CURRENT_PEAK_DISCHARGE_THRESHOLD_2             = 0x380085,
    DTC_CURRENT_CONT_DISCHARGE_THRESHOLD_1             = 0x380086,
    DTC_CURRENT_CONT_DISCHARGE_THRESHOLD_2             = 0x380087,
    DTC_CURRENT_SENSOR_STRING_IMBALANCE                = 0x380089,
    DTC_CONTACTOR_SUPPLY_VOLTAGE_LOW                   = 0x380177,
    DTC_CONTACTOR_SUPPLY_VOLTAGE_HIGH                  = 0x380178,
    DTC_SYSTEM_VOLTAGE_MONITOR_ERROR                   = 0x380163,
    DTC_BMS_CONFIGURATION_BATTERY_MODULE_COUNT_ERROR   = 0x380167,
    DTC_BMS_ONBOARD_TEMP_SENSOR_OVER_TEMPERATURE       = 0x380182,
    DTC_BMS_ONBOARD_TEMP_SENSOR_DRIVER_ERROR           = 0x380181,
    DTC_BMS_SUPPLY_LOW_VOLTAGE_FAULT                   = 0x380183,
    DTC_BMS_SUPPLY_OVER_VOLTAGE_FAULT                  = 0x380184,
    DTC_BATTERY_CONNECTION_ANALYSIS_THRESHOLD_1        = 0x380185,
    DTC_BATTERY_CONNECTION_ANALYSIS_THRESHOLD_2        = 0x380186,
    DTC_HEATING_CURRENTS_DEVIATION_TOO_HIGH            = 0x380189,
    DTC_HEATING_SHORT_CIRCUIT                          = 0x380187,
    DTC_HEATING_NOT_CONNECTED                          = 0x380188,
    DTC_CAN0_CT_ROLL_INCORRECT                         = 0x380144,
    DTC_CAN0_CRC_INCORRECT                             = 0x380145,
    DTC_BMS_CPSOUT_STATUS_NOT_CORRECT                  = 0x380140,
    DTC_BMS_CPSOUT_OVERLOAD                            = 0x380141,
    DTC_BMS_CPS_DATA_RECOVERY_UPLOAD_FAILED            = 0x380142,
    DTC_BMS_CPS_DATA_RECOVERY_DOWNLOAD_FAILED          = 0x380143,
    DTC_FAN_WARNING                                    = 0x380110,
    DTC_FAN_FAULT                                      = 0x380111,
    DTC_BCM_PRE_CHARGE_TIMEOUT                         = 0x380025,
    DTC_BCM_ERROR                                      = 0x380026,
    DTC_BCM_TEST                                       = 0x380027,
    DTC_BCM_PWM_PLAUSIBILITY                           = 0x380028,
    DTC_ICD_MISSING_RESPONSE                           = 0x380094,
    DTC_BMS_SUPPLY_VOLTAGE_DRIVER_ERROR                = 0x380172,
    DTC_CONTACTOR_SUPPLY_VOLTAGE_DRIVER_ERROR          = 0x380173,
    DTC_ONBOARD_TEMP_SENSOR_DRIVER_ERROR               = 0x380179,
    DTC_AFE_INIT_ERROR                                 = 0x380190,
    DTC_AFE_COMM_ERROR                                 = 0x380158,
    DTC_AFE_CHECK_FTTI_TIMEOUT                         = 0x383300,
    DTC_RESET_REG_INTERN_CONFIG                        = 0x380195,
    DTC_RESET_REG_EXTERN_CONFIG                        = 0x380196,
    DTC_CONTACTOR_DIAG_ERROR_EXTERNAL                  = 0x380020,
    DTC_PRECHARGE_TIMEOUT_EXTERNAL                     = 0x380168,
    DTC_HW_VERSION_MISMATCH_EXTERNAL                   = 0x380199,
    DTC_TASK_TIMING_MALFUNCTIONING_EXTERNAL            = 0x380191,
    DTC_TASK_MPU_TRIGGERED_EXTERNAL                    = 0x380192,
    DTC_CAN_SEND_DRIVER_ERROR_EXTERNAL                 = 0x380155,
    DTC_CAN_QUEUE_FULL_EXTERNAL                        = 0x380156,
    DTC_CONTACTOR_DRIVER_ERROR_EXTERNAL                = 0x380174,
    DTC_AFE_CHECK_SM_FAILED_EXTERNAL                   = 0x383100,
    DTC_AFE_CHECK_SM_ERROR_DETECTED_EXTERNAL           = 0x383200,
    DTC_BALANCING_OVER_TEMPERATURE_ALERT_EXTERNAL      = 0x380124,
    DTC_AUX_RELAY_DRIVER_ERROR_EXTERNAL                = 0x380180,
    DTC_NVM_ERROR_EXTERNAL                             = 0x380197,
    DTC_VOLTAGE_DRIVER_ERROR_EXTERNAL                  = 0x380198,
    DTC_SBC_WATCHDOG_ERROR_EXTERNAL                    = 0x380193,
    DTC_SBC_DIAGNOSIS_ERROR_EXTERNAL                   = 0x380194,
    DTC_AFE_CHECK_DURING_SHUTDOWN                      = 0xd52000,
    DTC_NVM_FAULT                                      = 0xeb9000,
    DTC_DEM_QUEUE_FULL                                 = 0x990000,
    DTC_KBS_INTERFACE_MONITOR_1                        = 0x380240,
    DTC_KBS_INTERFACE_MONITOR_2                        = 0x380241,
    DTC_KBS_INTERFACE_MONITOR_3                        = 0x380242,
    DTC_KBS_INTERFACE_MONITOR_4                        = 0x380243,
    DTC_KBS_INTERFACE_MONITOR_5                        = 0x380244,
    DTC_KBS_INTERFACE_MONITOR_6                        = 0x380245,
    DTC_KBS_INTERFACE_MONITOR_7                        = 0x380246,
    DTC_KBS_INTERFACE_MONITOR_8                        = 0x380247,
    DTC_KBS_INTERFACE_MONITOR_9                        = 0x380248,
    DTC_KBS_INTERFACE_MONITOR_10                       = 0x380249,
    DTC_KBS_INTERFACE_MONITOR_11                       = 0x380250,
    DTC_KBS_INTERFACE_MONITOR_12                       = 0x380251,
    DTC_KBS_INTERFACE_MONITOR_13                       = 0x380252,
    DTC_KBS_INTERFACE_MONITOR_14                       = 0x380253,
    DTC_KBS_INTERFACE_MONITOR_15                       = 0x380254,
    DTC_KBS_INTERFACE_MONITOR_16                       = 0x380255,
    DTC_KBS_INTERFACE_MONITOR_17                       = 0x380256,
    DTC_KBS_INTERFACE_MONITOR_18                       = 0x380257,
    DTC_KBS_INTERFACE_MONITOR_19                       = 0x380258,
    DTC_KBS_INTERFACE_MONITOR_20                       = 0x380259,
    DTC_KBS_INTERFACE_MONITOR_21                       = 0x380260,
    DTC_KBS_INTERFACE_MONITOR_22                       = 0x380261,
    DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1     = 0x380068,
    DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2     = 0x380069,
    DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1 = 0x380071,
    DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2 = 0x380072,
    DTC_CPS_GENERAL_POWERPATH_OT                       = 0x381050,
    DTC_NON_SYSTEM_MASTER_ERROR                        = 0x9d0000,
} DTC;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
