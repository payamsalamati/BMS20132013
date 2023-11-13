
/**
 * @file     dem_config.c
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>
#include "dem.h"
#include "emcy.h"
#include "kionCAN.h"
#include "stateFunctions.h"
#include "osIf.h"
#include "task_cfg.h"
#include "safety.h"
#include "batteryModule_config.h"
#include "cps.h"
#include "canProtocol.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_SEC_PARAMETER static DEM_SeverityTransition severityTransitionTable[] = {
    /*	 Fault -------------Bitmask  --------- Category ------------------- Level -------------------- Transition times -- */
    { DTC_CONTACTOR_DIAG_ERROR, 0xffff0000, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_A, { 2000, 0 } },       // @req CB-88942
    { DTC_PRECHARGE_TIMEOUT, 0xffffff00, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },           // @req CB-77042
    { DTC_HW_VERSION_MISMATCH, 0xffffff00, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_C, { 0, 0 } },          // @req CB-77082
    { DTC_TASK_TIMING_MALFUNCTIONING, 0xffffff00, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },  // @req CB-77080
    { DTC_TASK_MPU_TRIGGERED, 0xffffff00, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },          // @req CB-77081
    { DTC_CAN_SEND_DRIVER_ERROR, 0xffffff00, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },       // @req CB-77088
    { DTC_CAN_QUEUE_FULL, 0xffffff00, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },              // @req CB-77083
    { DTC_CONTACTOR_DRIVER_ERROR, 0xffffff00, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },      // @req CB-77094
    { DTC_AFE_CHECK_SM_FAILED, 0xffff0000, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },         // @req CB-77101
    { DTC_AFE_CHECK_HIL_APROVED_SM_ERROR_DETECTED, 0xffff0000, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },
    { DTC_BALANCING_OVER_TEMPERATURE_ALERT, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },          // @req CB-77085
    { DTC_AUX_RELAY_DRIVER_ERROR, 0xffffff00, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                    // @req CB-77097
    { DTC_NVM_ERROR, 0xffffff00, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                                 // @req CB-77084
    { DTC_VOLTAGE_DRIVER_ERROR, 0xffffff00, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_A, { 1000, 5000 } },                  // @req CB-77089
    { DTC_SBC_WATCHDOG_ERROR, 0xffffff00, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                        // @req CB-77107
    { DTC_SBC_DIAGNOSIS_ERROR, 0xffffff00, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                       // @req CB-77108
    { DTC_ICD_COM_FAULT, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 5000, 5000 } },                        // @req CB-19036
    { DTC_ICD_SENSOR_MEASUREMENT_FAULT, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 3000, 0 } },             // @req CB-19037
    { DTC_ICD_SENSOR_SYSTEM_FAULT, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 3000, 0 } },                  // @req CB-19038
    { DTC_ICD_CONFIGURATION_INVALID, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 0, 5000 } },               // @req CB-19039
    { DTC_ICD_RESULT_RC_FAULT, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 3000, 0 } },                      // @req CB-19443
    { DTC_ICD_SENSOR_PERSISTENT_FAULT, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 0, 5000 } },             // @req CB-19444
    { DTC_CELL_OVER_VOLTAGE_WARNING, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 1000, 0 } },                // @req CB-76996
    { DTC_CELL_OVER_VOLTAGE_ALERT, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 3000, 5000 } },              // @req CB-76997
    { DTC_CELL_OVER_VOLTAGE_ERROR, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_C, { 0, 0 } },                       // @req CB-76998
    { DTC_AFE_CHECK_SM_ERROR_DETECTED, 0xffff0000, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 4500, 5000 } },          // @req CB-77102
    { DTC_AFE_CHECK_FTTI_TIMEOUT, 0xffffff00, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 1000, 5000 } },               // @req CB-77103
    { DTC_CELL_UNDER_VOLTAGE_WARNING, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 15000, 0 } },              // @req CB-76999
    { DTC_CELL_UNDER_VOLTAGE_ALERT, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 15000, 5000 } },            // @req CB-77000
    { DTC_CELL_UNDER_VOLTAGE_ERROR, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_C, { 15000, 5000 } },             // @req CB-77002
    { DTC_DEEP_DISCHARGE, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                               // @req CB-77004
    { DTC_DEEP_DISCHARGE_CELL_DAMAGE_ERROR, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_QM, { 0, 0 } },             // @req CB-77005
    { DTC_CELL_VOLTAGE_IMBALANCE_WARNING, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },            // @req CB-77007
    { DTC_CELL_VOLTAGE_IMBALANCE_ERROR, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 20000, 0 } },          // @req CB-77008
    { DTC_CELL_HIGH_TEMPERATURE_WARNING, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 1000, 0 } },            // @req CB-77010
    { DTC_CELL_HIGH_TEMPERATURE_ALERT, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 1000, 5000 } },          // @req CB-77011
    { DTC_CELL_HIGH_TEMPERATURE_ERROR, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_C, { 0, 0 } },                   // @req CB-77012
    { DTC_CELL_LOW_TEMPERATURE_WARNING, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 1000, 0 } },             // @req CB-77013
    { DTC_CELL_LOW_TEMPERATURE_ALERT, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 3000, 5000 } },           // @req CB-77014
    { DTC_CELL_LOW_TEMPERATURE_ERROR, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_C, { 0, 0 } },                    // @req CB-77015
    { DTC_CURRENT_PEAK_CHARGE_THRESHOLD_1, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 5000, 0 } },          // @req CB-77022
    { DTC_CURRENT_PEAK_CHARGE_THRESHOLD_2, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 10000, 5000 } },     // @req CB-77023
    { DTC_CURRENT_CONT_CHARGE_THRESHOLD_1, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 30000, 0 } },         // @req CB-77024
    { DTC_CURRENT_CONT_CHARGE_THRESHOLD_2, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 60000, 5000 } },     // @req CB-77025
    { DTC_CURRENT_PEAK_DISCHARGE_THRESHOLD_1, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 10000, 0 } },      // @req CB-77026
    { DTC_CURRENT_PEAK_DISCHARGE_THRESHOLD_2, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 10000, 5000 } },  // @req CB-77027
    { DTC_CURRENT_CONT_DISCHARGE_THRESHOLD_1, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 30000, 0 } },      // @req CB-77028
    { DTC_CURRENT_CONT_DISCHARGE_THRESHOLD_2, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 30000, 5000 } },  // @req CB-77029
    { DTC_CURRENT_SENSOR_STRING_IMBALANCE, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_A, { 3000, 5000 } },      // @req CB-77033
    { DTC_CONTACTOR_SUPPLY_VOLTAGE_LOW, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_A, { 0, 0 } },                  // @req CB-77038
    { DTC_CONTACTOR_SUPPLY_VOLTAGE_HIGH, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },             // @req CB-77039
    { DTC_SYSTEM_VOLTAGE_MONITOR_ERROR, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },              // @req CB-77044
#if defined(HIL_CONFIGURATION)
    { DTC_BMS_CONFIGURATION_BATTERY_MODULE_COUNT_ERROR, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },  // @req CB-77046
#else
    { DTC_BMS_CONFIGURATION_BATTERY_MODULE_COUNT_ERROR, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_QM, { 0, 0 } },  // @req CB-77046
#endif
    { DTC_BMS_ONBOARD_TEMP_SENSOR_OVER_TEMPERATURE, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },        // @req CB-77048
    { DTC_BMS_ONBOARD_TEMP_SENSOR_DRIVER_ERROR, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },            // @req CB-77049
    { DTC_BMS_SUPPLY_LOW_VOLTAGE_FAULT, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 5000, 1000 } },              // @req CB-77050
    { DTC_BMS_SUPPLY_OVER_VOLTAGE_FAULT, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 5000, 1000 } },             // @req CB-77051
    { DTC_BATTERY_CONNECTION_ANALYSIS_THRESHOLD_1, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },         // @req CB-77053
    { DTC_BATTERY_CONNECTION_ANALYSIS_THRESHOLD_2, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 10000, 1000 } },  // @req CB-77054
    { DTC_HEATING_CURRENTS_DEVIATION_TOO_HIGH, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 20000, 5000 } },      // @req CB-77056
    { DTC_HEATING_SHORT_CIRCUIT, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-77057
    { DTC_HEATING_NOT_CONNECTED, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-77058
    { DTC_CAN0_CT_ROLL_INCORRECT, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                          // @req CB-77063
    { DTC_CAN0_CRC_INCORRECT, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                              // @req CB-77064
    { DTC_BMS_CPSOUT_STATUS_NOT_CORRECT, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                   // @req CB-77066
    { DTC_BMS_CPSOUT_OVERLOAD, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                             // @req CB-77067
    { DTC_BMS_CPS_DATA_RECOVERY_UPLOAD_FAILED, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },             // @req CB-77068
    { DTC_BMS_CPS_DATA_RECOVERY_DOWNLOAD_FAILED, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },           // @req CB-77069
    { DTC_FAN_WARNING, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                                     // @req CB-88864
    { DTC_FAN_FAULT, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                                       // @req CB-88865
    { DTC_BCM_PRE_CHARGE_TIMEOUT, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                          // @req CB-88870
    { DTC_BCM_ERROR, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 1000, 0 } },                                    // @req CB-88871
    { DTC_BCM_TEST, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                                        // @req CB-88872
    { DTC_BCM_PWM_PLAUSIBILITY, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 5000, 0 } },                         // @req CB-88873
    { DTC_ICD_MISSING_RESPONSE, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                            // @req CB-88943
    { DTC_BMS_SUPPLY_VOLTAGE_DRIVER_ERROR, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                 // @req CB-77091
    { DTC_CONTACTOR_SUPPLY_VOLTAGE_DRIVER_ERROR, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_A, { 1000, 5000 } },      // @req CB-77092
    { DTC_ONBOARD_TEMP_SENSOR_DRIVER_ERROR, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                // @req CB-77096
    { DTC_AFE_INIT_ERROR, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                                     // @req CB-77099
    { DTC_AFE_COMM_ERROR, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 3000, 5000 } },                             // @req CB-77100
    { DTC_RESET_REG_INTERN_CONFIG, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-77105
    { DTC_RESET_REG_EXTERN_CONFIG, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-77106
    { DTC_OS_MUTEX_PEND_FAULT, 0xff000000, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                             // @req CB-92844
    { DTC_OS_MUTEX_POST_FAULT, 0xff000000, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                             // @req CB-92845
    { DTC_KBS_INTERFACE_MONITOR_1, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_2, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_3, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_4, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_5, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_6, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_7, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_8, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_9, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_10, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                          // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_11, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_12, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_13, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_14, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_15, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_16, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_17, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_18, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_19, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_20, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_21, 0xffffffff, DEM_CATEGORY_PREWARNING, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                         // @req CB-91986
    { DTC_KBS_INTERFACE_MONITOR_22, 0xffffffff, DEM_CATEGORY_SHUTDOWN, DEM_SAFETY_LEVEL_QM, { 0, 0 } },                           // @req CB-91986
#if defined(APPLICATION_TEMPSENSOR_USAGE) && (APPLICATION_TEMPSENSOR_USAGE == CONFIG_ENABLED)
    { DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },       // @req CB-93945 CB-93961 CB-93962 CB-93963
    { DTC_PLUS_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 1000, 0 } },      // @req CB-93944 CB-93957 CB-93965 CB-93966
    { DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_1, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },   // @req CB-93943 CB-93954 CB-93955 CB-93960
    { DTC_NEGATIVE_TERMINAL_OVER_TEMPERATURE_THRESHOLD_2, 0xffffffff, DEM_CATEGORY_EMERGENCY, DEM_SAFETY_LEVEL_QM, { 1000, 0 } },  // @req CB-93946 CB-93958 CB-93969 CB-93970
#endif
    { DTC_CPS_GENERAL_POWERPATH_OT, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } },  // @req CB-76972
};

const DEM_Cfg demCfgInternal = {
    .severityTransitionTable     = severityTransitionTable,
    .severityTransitionTableSize = sizeof(severityTransitionTable) / sizeof(DEM_SeverityTransition),
};

const DTCMap dtcMap[] = {
    { .internalDTC  = (DTC)DTC_CONTACTOR_DIAG_ERROR,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_CONTACTOR_DIAG_ERROR_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_PRECHARGE_TIMEOUT,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_PRECHARGE_TIMEOUT_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_HW_VERSION_MISMATCH,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_HW_VERSION_MISMATCH_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_TASK_TIMING_MALFUNCTIONING,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_TASK_TIMING_MALFUNCTIONING_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_TASK_MPU_TRIGGERED,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_TASK_MPU_TRIGGERED_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_CAN_SEND_DRIVER_ERROR,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_CAN_SEND_DRIVER_ERROR_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_CAN_QUEUE_FULL,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_CAN_QUEUE_FULL_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_CONTACTOR_DRIVER_ERROR,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_CONTACTOR_DRIVER_ERROR_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_AFE_CHECK_SM_FAILED,
      .leftBitmask  = 0xfc00,
      .externalDTC  = (DTC)DTC_AFE_CHECK_SM_FAILED_EXTERNAL,
      .rightBitmask = 0x3f },
    { .internalDTC  = (DTC)DTC_AFE_CHECK_SM_ERROR_DETECTED,
      .leftBitmask  = 0xfc00,
      .externalDTC  = (DTC)DTC_AFE_CHECK_SM_ERROR_DETECTED_EXTERNAL,
      .rightBitmask = 0x3f },
    { .internalDTC  = (DTC)DTC_BALANCING_OVER_TEMPERATURE_ALERT,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_BALANCING_OVER_TEMPERATURE_ALERT_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_AUX_RELAY_DRIVER_ERROR,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_AUX_RELAY_DRIVER_ERROR_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_NVM_ERROR,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_NVM_ERROR_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_VOLTAGE_DRIVER_ERROR,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_VOLTAGE_DRIVER_ERROR_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_SBC_WATCHDOG_ERROR,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_SBC_WATCHDOG_ERROR_EXTERNAL,
      .rightBitmask = 0 },
    { .internalDTC  = (DTC)DTC_SBC_DIAGNOSIS_ERROR,
      .leftBitmask  = 0,
      .externalDTC  = (DTC)DTC_SBC_DIAGNOSIS_ERROR_EXTERNAL,
      .rightBitmask = 0 },
};

const uint32_t dtcMapSize = sizeof(dtcMap) / sizeof(DTCMap);


const DEM_SeverityTransition demDefaultTransition
    = { 0xffffffff, 0xffffffff, DEM_CATEGORY_INFORMATION, DEM_SAFETY_LEVEL_QM, { 0, 0 } };

MEM_SAFETY OSIf_Event sendDebugDtcMutex;

MEM_SEC_PARAMETER bool disableWarningEmcyMsg = false;

extern bool sendDebugValues;

void dem_reportFaultHook(DEM_FaultCode fault, bool isInternalDTC)
{
    if((isInternalDTC == false)
       && ((disableWarningEmcyMsg == false) || ((disableWarningEmcyMsg == true) && (dem_getSeverityLevelOfFault(fault, true) > DEM_SEVERITY_INFORMATION))))
    {
        emcy_reportFault(fault);
    }
}

void dem_clearFaultHook(DEM_FaultCode fault, bool isInternalDTC, uint8_t numberOfActiveFaults)
{
    if(isInternalDTC == false && ((disableWarningEmcyMsg == false) || ((disableWarningEmcyMsg == true) && (dem_getSeverityLevelOfFault(fault, true) > DEM_SEVERITY_INFORMATION))))
    {
        emcy_clearFault(fault, numberOfActiveFaults);
    }
}

void dem_initHook(void)
{
    emcy_initialize();

    sendDebugDtcMutex = osIf_mutexCreate();

    if(sendDebugDtcMutex.handle == NULL)
    {
        safety_criticalException();
    }
}

void dem_emergencyHook(void)
{
    stmFct_setEmergency();
}

void dem_severityChangedHook(DEM_FaultCode fault, DEM_Severity severity)
{
    if((sendDebugValues == true) && (missingAckErrorCntExternal < EXTERNALCAN_MAX_MISSING_ACK_ERROR_COUNT))
    {
        osIf_mutexPend(sendDebugDtcMutex, 5u);
        kionCAN_sendDebugDTC((DTC)fault, severity);
        osIf_mutexPost(sendDebugDtcMutex);
    }
    if(((severity == DEM_SEVERITY_CONFIRMED) || (severity == DEM_SEVERITY_EMERGENCY_CONFIRMED)) && (dem_getSeverityLevelOfSystem() <= DEM_SEVERITY_CONFIRMED))
    {
        dem_emergencyHook();
    }
    if((fault == DTC_CPS_GENERAL_POWERPATH_OT) && (severity == DEM_SEVERITY_INFORMATION))
    {
        cps_setCpsOutDeactivationInhibitStatus(false);
    }
}
