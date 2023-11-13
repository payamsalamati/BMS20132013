/**
 * @file canData.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "canData.h"

#include "task_cfg.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    KION_TIME_t lastTimeData;
    KION_TIMESTAMP_t lastTimestampData;
    KION_LIB_PDO_RX1_t lastLibPdoRx1Data;
    KION_LIB_PDO_RX4_t lastLibPdoRx4Data;
    int32_t lastLibPdoRx4_truckOperatingHoursCharging;
    int32_t lastLibPdoRx4_truckOperatingHoursDriving;
    KION_LIB_EMERGENCY_t lastLibEmergencyData;
    KION_LIB_HEARTBEAT_t lastLibHeartbeatData;
    KION_LIB_PDO_TX1_t lastLibPdoTx1Data;
    KION_LIB_PDO_TX2_t lastLibPdoTx2Data;
    KION_LIB_PDO_TX3_t lastLibPdoTx3Data;
    KION_LIB_PDO_TX4_t lastLibPdoTx4Data;
    KION_LIB_PDO_TX5_t lastLibPdoTx5Data;
    KION_LIB_PDO_TX6_t lastLibPdoTx6Data;
    KION_LIB_PDO_TX7_t lastLibPdoTx7Data;
    KION_LIB_PDO_TX8_t lastLibPdoTx8Data;
    KION_HEARTBTBMS_t lastHeartbtBmsData;
    LINDE_LIIOCHARGER_PDO1_t lastLindePdoRx1Data;
    LINDE_TRACTION_PDO4_t lastLindeTractionPdoRx4Data;
    LINDE_TIMESTAMP_t lastLindeTimestampData;
    bool libPdoRx1DataReceived;
    bool libPdoRx4DataReceived;
} CAN_DATA;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_CAN static CAN_DATA canData;

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void canData_storeLastTimeData(KION_TIME_t lastValue)
{
    canData.lastTimeData = lastValue;
}

void canData_storeLastTimestampData(KION_TIMESTAMP_t lastValue)
{
    canData.lastTimestampData = lastValue;
}

void canData_storeLastLibPdoRx1Data(KION_LIB_PDO_RX1_t lastValue)
{
    canData.lastLibPdoRx1Data = lastValue;
}

void canData_storeLastLibPdoRx4Data(KION_LIB_PDO_RX4_t lastValue)
{
    // @req CB-75128
    canData.lastLibPdoRx4Data = lastValue;
    if(canData.lastLibPdoRx4Data.truck_operating_hours_mode == 0x1)
    {
        canData.lastLibPdoRx4_truckOperatingHoursDriving = canData.lastLibPdoRx4Data.truck_operating_hours;
    }
    else if(canData.lastLibPdoRx4Data.truck_operating_hours_mode == 0x8)
    {
        canData.lastLibPdoRx4_truckOperatingHoursCharging = canData.lastLibPdoRx4Data.truck_operating_hours;
    }
    else
    {
    }
}

void canData_storeLastLibEmergencyData(KION_LIB_EMERGENCY_t lastValue)
{
    canData.lastLibEmergencyData = lastValue;
}

void canData_storeLastLibHeartbeatData(KION_LIB_HEARTBEAT_t lastValue)
{
    canData.lastLibHeartbeatData = lastValue;
}

void canData_storeLastLibPdoTx1Data(KION_LIB_PDO_TX1_t lastValue)
{
    canData.lastLibPdoTx1Data = lastValue;
}

void canData_storeLastLibPdoTx2Data(KION_LIB_PDO_TX2_t lastValue)
{
    canData.lastLibPdoTx2Data = lastValue;
}

void canData_storeLastLibPdoTx3Data(KION_LIB_PDO_TX3_t lastValue)
{
    canData.lastLibPdoTx3Data = lastValue;
}

void canData_storeLastLibPdoTx4Data(KION_LIB_PDO_TX4_t lastValue)
{
    canData.lastLibPdoTx4Data = lastValue;
}

void canData_storeLastLibPdoTx5Data(KION_LIB_PDO_TX5_t lastValue)
{
    canData.lastLibPdoTx5Data = lastValue;
}

void canData_storeLastLibPdoTx6Data(KION_LIB_PDO_TX6_t lastValue)
{
    canData.lastLibPdoTx6Data = lastValue;
}

void canData_storeLastLibPdoTx7Data(KION_LIB_PDO_TX7_t lastValue)
{
    canData.lastLibPdoTx7Data = lastValue;
}

void canData_storeLastLibPdoTx8Data(KION_LIB_PDO_TX8_t lastValue)
{
    canData.lastLibPdoTx8Data = lastValue;
}

void canData_storeLastHeartbtBmsData(KION_HEARTBTBMS_t lastValue)
{
    canData.lastHeartbtBmsData = lastValue;
}

void canData_storeLastLindePdoRx1Data(LINDE_LIIOCHARGER_PDO1_t lastValue)
{
    canData.lastLindePdoRx1Data = lastValue;
}

void canData_storeLastLindeTractionPdoRx4Data(LINDE_TRACTION_PDO4_t lastValue)
{
    canData.lastLindeTractionPdoRx4Data = lastValue;
}

void canData_storeLastLindeTimestampData(LINDE_TIMESTAMP_t lastValue)
{
    canData.lastLindeTimestampData = lastValue;
}


uint32_t canData_getLastCanOpenTimeOfDay_ms(void)
{
    return canData.lastTimeData.canopen_time_of_day_ms;
}

uint16_t canData_getLastCanOpenTimeOfDay_Days(void)
{
    return canData.lastTimeData.canopen_time_of_day_days;
}

uint32_t canData_getLastDateTime(void)
{
    return canData.lastTimestampData.DateTime;
}

uint32_t canData_getLastLibChargingPower(void)
{
    return canData.lastLibPdoRx1Data.lib_charging_power;
}

uint32_t canData_getLastLibChargingVoltage(void)
{
    return canData.lastLibPdoRx1Data.lib_charging_voltage;
}

uint16_t canData_getLastLibChargingCurrent(void)
{
    return canData.lastLibPdoRx1Data.lib_charging_current;
}

uint16_t canData_getLastLibPowerConsumptionAverage(void)
{
    return canData.lastLibPdoRx4Data.lib_power_consumption_average;
}

uint32_t canData_getLastTruckOperatingHours(void)
{
    return canData.lastLibPdoRx4Data.truck_operating_hours;
}

uint8_t canData_getLastTruckOperatingHoursMode(void)
{
    return canData.lastLibPdoRx4Data.truck_operating_hours_mode;
}

uint16_t canData_getLastEmergencyCodeLib(void)
{
    return canData.lastLibEmergencyData.emergency_error_code_lib;
}

uint8_t canData_getLastEmergencyRegisterObjectLib(void)
{
    return canData.lastLibEmergencyData.error_register_object_lib;
}

uint32_t canData_getLastUdsDtcLib(void)
{
    return canData.lastLibEmergencyData.uds_dtc_lib;
}

uint8_t canData_getLastKionCanopenStateLib(void)
{
    return canData.lastLibHeartbeatData.canopen_state_lib;
}

uint8_t canData_getLastLibShockWarning(void)
{
    return canData.lastLibPdoTx1Data.lib_shock_warning;
}

uint8_t canData_getLastLibServiceRequired(void)
{
    return canData.lastLibPdoTx1Data.lib_service_required;
}

uint8_t canData_getLastLibInitComplete(void)
{
    return canData.lastLibPdoTx1Data.lib_init_complete;
}

uint8_t canData_getLastLibCurrentLimited(void)
{
    return canData.lastLibPdoTx1Data.lib_current_limited;
}

uint8_t canData_getLastLibTemperatureTooLow(void)
{
    return canData.lastLibPdoTx1Data.lib_temperature_too_low;
}

uint8_t canData_getLastLibReady(void)
{
    return canData.lastLibPdoTx1Data.lib_ready;
}

uint8_t canData_getLastLibEmergencyOperation(void)
{
    return canData.lastLibPdoTx1Data.lib_emergency_operation;
}

uint8_t canData_getLastLibTemperatureTooHigh(void)
{
    return canData.lastLibPdoTx1Data.lib_temperature_too_high;
}

uint8_t canData_getLastLibError(void)
{
    return canData.lastLibPdoTx1Data.lib_error;
}

uint8_t canData_getLastLibInDrivingMode(void)
{
    return canData.lastLibPdoTx1Data.lib_in_driving_mode;
}

uint8_t canData_getLastLibFatalError(void)
{
    return canData.lastLibPdoTx1Data.lib_fatal_error;
}

uint8_t canData_getLastLibInChargingMode(void)
{
    return canData.lastLibPdoTx1Data.lib_in_charging_mode;
}

uint8_t canData_getLastLibCpsOutputActive(void)
{
    return canData.lastLibPdoTx1Data.lib_cps_output_active;
}

uint8_t canData_getLastLibCpsOutputDeactivationInhibit(void)
{
    return canData.lastLibPdoTx1Data.lib_cps_output_deactivation_inhibit;
}

uint32_t canData_getLastLibCurrent(void)
{
    return canData.lastLibPdoTx1Data.lib_current;
}

uint32_t canData_getLastLibVoltageInFrontOfContactor(void)
{
    return canData.lastLibPdoTx2Data.lib_voltage_in_front_of_contacto;
}

uint32_t canData_getLastLibVoltageAfterContactor(void)
{
    return canData.lastLibPdoTx2Data.lib_voltage_after_contactor;
}

uint32_t canData_getLastLibPower(void)
{
    return canData.lastLibPdoTx2Data.lib_power;
}

uint8_t canData_getLastLibStateOfHealth(void)
{
    return canData.lastLibPdoTx2Data.lib_state_of_health;
}

uint32_t canData_getLastLibMaxDischargingPower2s(void)
{
    return canData.lastLibPdoTx3Data.lib_max_discharging_power_2s;
}

uint32_t canData_getLastLibMaxDischargingPower100s(void)
{
    return canData.lastLibPdoTx3Data.lib_max_discharging_power_100s;
}

uint8_t canData_getLastLibSocWithSoh(void)
{
    return canData.lastLibPdoTx3Data.lib_soc_with_soh;
}

uint32_t canData_getLastLibMinDischargingVoltage(void)
{
    return canData.lastLibPdoTx3Data.lib_min_discharging_voltage;
}

uint32_t canData_getLastLibChargingPower2s(void)
{
    return canData.lastLibPdoTx4Data.lib_max_charging_power_2s;
}

uint8_t canData_getLastLibSocWithoutSoh(void)
{
    return canData.lastLibPdoTx4Data.lib_soc_without_soh;
}

uint32_t canData_getLastLibMaxChargingVoltage(void)
{
    return canData.lastLibPdoTx4Data.lib_max_charging_voltage;
}

uint32_t canData_getLastLibMaxChargingPower100s(void)
{
    return canData.lastLibPdoTx4Data.lib_max_charging_power_100s;
}

uint32_t canData_getLastLibMaxDischargingCurrent2s(void)
{
    return canData.lastLibPdoTx5Data.lib_max_discharging_current_2s;
}

uint32_t canData_getLastLibMaxDischargingCurrent100s(void)
{
    return canData.lastLibPdoTx5Data.lib_max_discharging_current_100s;
}

uint32_t canData_getLastLibMaxChargingCurrent2s(void)
{
    return canData.lastLibPdoTx6Data.lib_max_charging_current_2s;
}

uint32_t canData_getLastLibMaxChargingCurrent100s(void)
{
    return canData.lastLibPdoTx6Data.lib_max_charging_current_100s;
}

uint16_t canData_getLastLibSocWithoutSohFine(void)
{
    return canData.lastLibPdoTx6Data.lib_soc_without_soh_fine;
}

int8_t canData_getLastLibMinTemperature(void)
{
    return canData.lastLibPdoTx6Data.lib_min_temperature;
}

int8_t canData_getLastLibMaxTemperature(void)
{
    return canData.lastLibPdoTx6Data.lib_max_temperature;
}

uint8_t canData_getLastLibPowerpathOk(void)
{
    return canData.lastLibPdoTx7Data.lib_powerpath_ok;
}


uint8_t canData_getLastBmsBatStat(void)
{
    return canData.lastHeartbtBmsData.stateBms;
}

bool canData_getLibPdoRx1DataReceived(void)
{
    return canData.libPdoRx1DataReceived;
}

void canData_setLibPdoRx1DataReceived(void)
{
    canData.libPdoRx1DataReceived = true;
}

bool canData_getLibPdoRx4DataReceived(void)
{
    return canData.libPdoRx4DataReceived;
}

void canData_setLibPdoRx4DataReceived(bool newValue)
{
    canData.libPdoRx4DataReceived = true;
}
