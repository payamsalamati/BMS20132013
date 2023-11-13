
/**
 *******************************************************************************
 **
 **  Project Name                : FeLiX
 **  Software Version            : 4.2303.0
 **  Model Name                  : FeLiX
 **  File Type                   : Header
 **  Author                      : juldie1
 **  Date                        : Fri Apr 28 16:47:08 2023
 **
 **  Copyright                   : (c) KION Battery Systems GmbH, Karlstein am Main 2022 -  All right reserved
 **
 **  Short Description           : Model for FeLiX
 **
 **  Detailed Description        :
 **
 **
 **  Modification History        :

 *******************************************************************************
 **/

#include <stdint.h>

#define MEM_SEC_PARAMETER_KBS __attribute__((section(".kbs_param")))

#define CELLS_PER_MODULE               15
#define MODULES_PER_BATTERY            8
#define STRINGS_PER_BATTERY            8
#define TEMPERATURE_SENSORS_PER_MODULE 8

/*  Includes */
#ifndef RTW_HEADER_KBSInterface_h_
#define RTW_HEADER_KBSInterface_h_

/*  Defines */

/*  Data Types */
typedef uint8_t ENUM_DIAGNOSTIC_EVENT;

/* enum ENUM_DIAGNOSTIC_EVENT */
#define ENUM_DIAGNOSTIC_EVENT_PASSED ((ENUM_DIAGNOSTIC_EVENT)0U) /* Default value */
#define ENUM_DIAGNOSTIC_EVENT_FAILED ((ENUM_DIAGNOSTIC_EVENT)1U)

typedef uint8_t ENUM_GET_SET;

/* enum ENUM_GET_SET */
#define ENUM_GET_SET_OFF ((ENUM_GET_SET)0U) /* Default value */
#define ENUM_GET_SET_ON  ((ENUM_GET_SET)1U)

typedef uint8_t ENUM_STATE_BMS;

/* enum ENUM_STATE_BMS */
#define ENUM_STATE_BMS_INVALID                                 ((ENUM_STATE_BMS)0U) /* Default value */
#define ENUM_STATE_BMS_IDLE                                    ((ENUM_STATE_BMS)1U)
#define ENUM_STATE_BMS_SELF_TEST                               ((ENUM_STATE_BMS)2U)
#define ENUM_STATE_BMS_BCM_TEST                                ((ENUM_STATE_BMS)3U)
#define ENUM_STATE_BMS_READY                                   ((ENUM_STATE_BMS)4U)
#define ENUM_STATE_BMS_PERIODIC_WAKEUP                         ((ENUM_STATE_BMS)5U)
#define ENUM_STATE_BMS_BALANCING                               ((ENUM_STATE_BMS)6U)
#define ENUM_STATE_BMS_DIAGNOSIS                               ((ENUM_STATE_BMS)10U)
#define ENUM_STATE_BMS_STANDALONE_DIAGNOSTIC_SERVICE_OPERATION ((ENUM_STATE_BMS)14U)
#define ENUM_STATE_BMS_DRIVE                                   ((ENUM_STATE_BMS)16U)
#define ENUM_STATE_BMS_FATAL_ERROR_IRREVERSIBLE                ((ENUM_STATE_BMS)24U)
#define ENUM_STATE_BMS_CHARGE                                  ((ENUM_STATE_BMS)32U)
#define ENUM_STATE_BMS_EMERGENCY                               ((ENUM_STATE_BMS)72U)
#define ENUM_STATE_BMS_ERROR_REVERSIBLE                        ((ENUM_STATE_BMS)136U)

typedef uint8_t ENUM_CONNECTION;

/* enum ENUM_CONNECTION */
#define ENUM_CONNECTION_NOT_CONNECTED ((ENUM_CONNECTION)0U) /* Default value */
#define ENUM_CONNECTION_CONNECTED     ((ENUM_CONNECTION)1U)

typedef uint8_t ENUM_OPERATINGMODE_FAN;

/* enum ENUM_OPERATINGMODE_FAN */
#define ENUM_OPERATINGMODE_FAN_OFF        ((ENUM_OPERATINGMODE_FAN)0U) /* Default value */
#define ENUM_OPERATINGMODE_FAN_CONTINUOUS ((ENUM_OPERATINGMODE_FAN)1U)
#define ENUM_OPERATINGMODE_FAN_CONTROLLED ((ENUM_OPERATINGMODE_FAN)2U)

typedef uint8_t ENUM_STATE_BALANCING;

/* enum ENUM_STATE_BALANCING */
#define ENUM_STATE_BALANCING_INACTIVE ((ENUM_STATE_BALANCING)0U) /* Default value */
#define ENUM_STATE_BALANCING_ACTIVE   ((ENUM_STATE_BALANCING)1U)

typedef uint8_t ENUM_CURRENTLIMITED;

/* enum ENUM_CURRENTLIMITED */
#define ENUM_CURRENTLIMITED_OFF                  ((ENUM_CURRENTLIMITED)0U) /* Default value */
#define ENUM_CURRENTLIMITED_ON                   ((ENUM_CURRENTLIMITED)1U)
#define ENUM_CURRENTLIMITED_SIGNAL_ERROR         ((ENUM_CURRENTLIMITED)2U)
#define ENUM_CURRENTLIMITED_SIGNAL_NOT_AVAILABLE ((ENUM_CURRENTLIMITED)3U)

typedef struct
{
    uint16_t identifier_diagnosticEvent;
    ENUM_DIAGNOSTIC_EVENT status_diagnosticEvent;
    const uint8_t* data_individualSnapshot;
    uint32_t size_individualSnapshot;
} diagnosticEvent;

typedef uint8_t ENUM_ROUTINE_CONTROL_TYPE;

/* enum ENUM_ROUTINE_CONTROL_TYPE */
#define ENUM_ROUTINE_CONTROL_TYPE_START_ROUTINE   ((ENUM_ROUTINE_CONTROL_TYPE)1U) /* Default value */
#define ENUM_ROUTINE_CONTROL_TYPE_STOP_ROUTINE    ((ENUM_ROUTINE_CONTROL_TYPE)2U)
#define ENUM_ROUTINE_CONTROL_TYPE_REQUEST_RESULTS ((ENUM_ROUTINE_CONTROL_TYPE)3U)

typedef struct
{
    ENUM_GET_SET get_balancing_Cell[(CELLS_PER_MODULE * MODULES_PER_BATTERY)];
    ENUM_GET_SET get_heating_Module[MODULES_PER_BATTERY];
    ENUM_GET_SET get_balancing_Battery;
    ENUM_GET_SET get_enable_BCM;
    ENUM_STATE_BMS state_BMS;
    ENUM_CONNECTION state_Charger;
    ENUM_CONNECTION state_Truck;
    ENUM_OPERATINGMODE_FAN operatingMode_Fan;
    int16_t temperature_Sensor[(TEMPERATURE_SENSORS_PER_MODULE * MODULES_PER_BATTERY)];
    uint16_t voltage_Cell[(CELLS_PER_MODULE * MODULES_PER_BATTERY)];
    int32_t heatingCurrent_Module[MODULES_PER_BATTERY];
    int16_t temperature_MasterPCB;
    int32_t current_Battery;
    uint16_t current_CPS;
    uint32_t voltageBeforeContactors;
    uint32_t voltageAfterContactors;
    uint32_t voltageBetweenContactors;
    int32_t AhCounter_CurrentSensor;
    uint32_t selfDischargeTime;
    uint8_t factorPowerReduction;
    uint16_t get_PWM_BCM;
    uint16_t get_speed_Fan;
    uint32_t chargingCurrent;
    uint32_t chargingVoltage;
    uint32_t chargingPower;
    uint32_t avgPowerConsumption_Vehicle;
    uint32_t workTime_Truck;
    uint32_t workTime_Component;
    uint32_t dateTime;
    uint32_t durationLastCall_10ms;
    uint32_t durationLastCall_100ms;
    uint32_t durationLastCall_1000ms;
} KBSInput;

typedef struct
{
    ENUM_GET_SET set_balancing_Cell[(CELLS_PER_MODULE * MODULES_PER_BATTERY)];
    ENUM_GET_SET set_heating_Module[MODULES_PER_BATTERY];
    ENUM_GET_SET set_enable_BCM;
    ENUM_STATE_BALANCING state_balancing_Battery;
    ENUM_CURRENTLIMITED currentLimited;
    uint16_t SOCwithSOH;
    uint16_t SOCwithoutSOH;
    uint32_t maxChargePower_Continuous;
    uint32_t maxChargePower_Pulse;
    uint32_t maxDischargePower_Continuous;
    uint32_t maxDischargePower_Pulse;
    uint32_t maxChargeCurrent_Continuous;
    uint32_t maxChargeCurrent_Pulse;
    uint32_t maxDischargeCurrent_Continuous;
    uint32_t maxDischargeCurrent_Pulse;
    uint16_t SOH_Capacity;
    uint16_t SOH_Performance;
    uint32_t remainingCapacity_Actual;
    uint16_t set_speed_Fan;
} KBSOutput;

typedef struct
{
    diagnosticEvent diagnosticEvent_1;
    diagnosticEvent diagnosticEvent_2;
    diagnosticEvent diagnosticEvent_3;
    diagnosticEvent diagnosticEvent_4;
    diagnosticEvent diagnosticEvent_5;
    diagnosticEvent diagnosticEvent_6;
    diagnosticEvent diagnosticEvent_7;
    diagnosticEvent diagnosticEvent_8;
    diagnosticEvent diagnosticEvent_9;
    diagnosticEvent diagnosticEvent_10;
    diagnosticEvent diagnosticEvent_11;
    diagnosticEvent diagnosticEvent_12;
    diagnosticEvent diagnosticEvent_13;
    diagnosticEvent diagnosticEvent_14;
    diagnosticEvent diagnosticEvent_15;
    diagnosticEvent diagnosticEvent_16;
    diagnosticEvent diagnosticEvent_17;
    diagnosticEvent diagnosticEvent_18;
    diagnosticEvent diagnosticEvent_19;
    diagnosticEvent diagnosticEvent_20;
    diagnosticEvent diagnosticEvent_21;
    diagnosticEvent diagnosticEvent_22;
} eventMonitor;

/**************************** GLOBAL DATA *************************************/
/*  Definitions */

/************************** EXTERNAL DATA DECLARATIONS *************************/

/*************************** FUNCTIONS ****************************************/

void KBSInterface_CANopen_readData(uint16_t index, uint8_t subIndex, uint16_t maxBufferSize, uint8_t* responseBuffer, uint16_t* responseBufferSize, uint32_t* abortCode);

void KBSInterface_CANopen_writeData(uint16_t index, uint8_t subIndex, const uint8_t* requestBuffer, const uint16_t* requestBufferSize, uint32_t* abortCode);

void KBSInterface_UDS_readData(uint16_t id, uint16_t maxBufferSize, uint8_t* responseBuffer, uint16_t* responseBufferSize, uint8_t* responseCode);

void KBSInterface_UDS_routineControl(ENUM_ROUTINE_CONTROL_TYPE type,
                                     uint16_t id,
                                     const uint8_t* option,
                                     uint8_t optionSize,
                                     uint16_t maxBufferSize,
                                     uint8_t* responseBuffer,
                                     uint16_t* responseBufferSize,
                                     uint8_t* responseCode);

void KBSInterface_UDS_writeData(uint16_t id, const uint8_t* requestBuffer, const uint16_t* requestBufferSize, uint8_t* responseCode);

void KBSInterface_initialize_NVM_BMS(const uint8_t* in_NVM_BMS, uint32_t size_NVM_BMS);

void KBSInterface_initialize_NVM_CSC(const uint8_t* in_NVM_CSC, uint32_t size_NVM_CSC);

void KBSInterface_main_1000ms(const KBSInput* input, KBSOutput* output, eventMonitor* monitor);

void KBSInterface_main_100ms(const KBSInput* input, KBSOutput* output, eventMonitor* monitor);

void KBSInterface_main_10ms(const KBSInput* input, KBSOutput* output, eventMonitor* monitor);

void KBSInterface_terminate(uint32_t size_NVM_BMS, uint32_t size_NVM_CS, uint8_t* out_NVM_BMS, uint8_t* out_NVM_CSC);

void KBSInterface_update_NVM(uint32_t size_NVM_BMS, uint32_t size_NVM_CSC, uint8_t* out_NVM_BMS, uint8_t* out_NVM_CSC);

void KBSInterface_terminate_ASW(void);

void KBSInterface_initialize_ASW(void);

#endif /* RTW_HEADER_KBSInterface_h_ */
