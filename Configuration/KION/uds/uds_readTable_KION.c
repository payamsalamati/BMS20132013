/**
 * @file     uds_readTable_KION.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief Sourcefile for uds_readTable_KION,generated via Variants
 * @details
 * UDS Read table  for KION,generated via Variants
Contains the automitacally generated UDS Read Entries for the configured variables of the dataInterface
 * -
 *
 *
 */

// *************************************************************************************************** /
// ************************* Includes **************************************************************** /
// *************************************************************************************************** /

#include "debug.h"
#include "fut_math.h"

#include "uds_readData/uds_readData.h"
#include "uds_config.h"
#include "uds.h"

#include "systemMasterData.h"
#include "stateFunctions.h"
#include "safety.h"

#include "measurements.h"
#include "measurements_config.h"

#include "measurements_getOnBoardTemperature.h"
#include "highVoltageMeasurement.h"
#include "auxRelayMeasurement.h"
#include "measurements_config.h"
#include "supplyVoltageMeasurement.h"
#include "stringVoltageMeasurement.h"


#include "task_cfg.h"
#include "afe_MC33771_config.h"
#include "bms.h"
#include "bms_config.h"
#include "module_config.h"
#include "idAllocation.h"
#include "uds_readData.h"
#include "csc_config.h"
#include "adcCurrentSensorIf.h"
#include "can_config.h"
#include "stateFunctions.h"
#include "stm_config.h"
#include "masterType.h"
#include "diagnosticsCommunication.h"
#include "voltageHistogram.h"
#include "voltageViolationHistogram.h"
#include "temperatureHistogram.h"
#include "moduleVoltageTemperatureHistogram.h"
#include "batteryCurrentTemperatureHistogram.h"
#include "warrantyData.h"
#include "taskPerformanceMeasurement.h"
#include "cellVoltageMeasurement.h"
#include "cellTemperatureMeasurement.h"
#include "afeTemperatureMeasurement.h"
#include "taskPerformanceMeasurement.h"
#include "stackUsageMonitor.h"
#include "taskAliveMonitor.h"
#include "protocolSelection.h"
#include "cps_config.h"
#include "periodicWakeUp.h"
#include "linearInterpolation.h"
#include "masterCurrentMeasurement.h"
#include "currentViolationHistogram.h"
#include "libIdentification.h"
#include "componentsPowerConsumption.h"
#include "hwVersionIf.h"
#include "moduleVoltageMeasurement.h"
#include "canData.h"
#include "softwareversion.h"
#include "vehicleManufacturerData.h"
#include "ecuDateData.h"
#include "systemMasterInfoReceive.h"
#include "safetyAfeValueMeasurement.h"
#include "batteryCurrentMeasurement.h"
#include "batteryContactorHistogram.h"
#include "masterPcbTemperatureHistogram.h"
#include "socTemperatureHistogram.h"
#include "histogramBins_config.h"
#include "voltageContactorHistogram.h"
#include "protocolInterface.h"

#include "fingerprint.h"
#include "shareData.h"
#include "eepromIf.h"
#include "memory_config.h"
#include "uds_diagnosticSessionControl.h"
#include "softwareversion_bootloader_config.h"
#include "identification.h"
#include "ecuIdentification.h"

#include "afeComProcedure.h"
#include "afe_MC33771_config.h"

#include "uds_readTable_KION.h"
#include "afe_MC33771.h"

#include AFE_INCLUDE_HEADER

#include "energyCounter.h"
#include "subMasterBalancing.h"

#include "softwareversionKion.h"
#include "bufferMethods.h"
#include "kioninterCAN_config.h"
#include "timestamp.h"
#include "diagnosticTimes.h"
#include "demUDS.h"
#include "demUDS_config.h"
#include "icdaSensor.h"
#include "eventData.h"
#include "heatingCurrentHistogram.h"
#include "currentViolationLogHistogram.h"
#include "debug.h"
#include "fut_math.h"
#include "testerSerialNumber.h"
#include "stmPrecharge.h"
#include "terminalTemperatureMeasurement.h"

#if defined(SYNC_AFE_AND_ICDA_MEASUREMENTS)
#include "synchronizedMeasurements.h"
#endif
#include "heatingCurrentMeasurement.h"

extern uint8_t
currentSensorIf_getCurrentSensorConfig(void);
extern int8_t currentSensorIf_getCurrentDirection(uint8_t safetyCurrentSensorIndex);

// *************************************************************************************************** /
// ************************* PRIVATE TYPEDEFS ******************************************************** /
// *************************************************************************************************** /

typedef enum
{
    NOT_CONNECTED = 0,
    FUSI          = 3,
    NON_FUSI      = 5,
    INVALID       = UINT8_MAX,
} DidEnumNTC;

typedef enum
{
    ContactorOpenClosed_Open      = 0x00,
    ContactorOpenClosed_Closed    = 0x01,
    ContactorOpenClosed_Undefined = 0xff,
} ContactorOpenClosed;

typedef enum
{
    ContactorConntected_NotConnected    = 0x00,
    ContactorConntected_ConnectedFusi   = 0x03,
    ContactorConnected_ConnectedNonFusi = 0x05,
} ContactorConntected;

#define DIAGNOSTIC_VERSION                  0x0001u
#define ECU_VARIANT_ID                      0x0035u
#define UDS_READ_TABLE_AUX_CONTACTOR_OPEN   3u
#define UDS_READ_TABLE_AUX_CONTACTOR_CLOSED 5u
#define READ_TABLE_KION_PROGRAMMING_SESSION 2u
#define CURRENT_SENSOR_CONFIG_PARALLEL_LEM  8u

// *************************************************************************************************** /
// ************************* EXTERN VARIABLE DEFINITIONS ********************************************* /
// *************************************************************************************************** /

extern MEM_SEC_PARAMETER uint8_t securityAccessTest;
MEM_SEC_PARAMETER uint8_t libChargingPreventionExcBassi = 3;

// *************************************************************************************************** /
// ************************* PRIVATE FUNCTIONS DECLARATION ******************************************* /
// *************************************************************************************************** /

static uint8_t uds_readTable_assignEnumValueFromBaudrate(uint32_t baudrate);
static uint8_t dummy_u8(void);
static uint16_t dummy_u16(void);
static uint32_t dummy_u32(void);
static uint64_t dummy_u64(void);
static int16_t dummy_s16(void);
static int32_t dummy_s32(void);
static void dummy_buffer(uint8_t* buffer, uint16_t length);
static uint8_t getContactorState(uint16_t contactorNumber);
static uint8_t getAuxContactorState(uint16_t contactorNumber);

// *************************************************************************************************** /
// ************************* Cell_&_Sensor_Map_Data ************************************************** /
// *************************************************************************************************** /

static void readAdcCurrentSensorConfig(uint8_t* buffer, uint16_t length);

// *************************************************************************************************** /
// ************************* Histogram_Data ********************************************************** /
// *************************************************************************************************** /

static void readHistogramCellVoltagesBins(uint8_t* buffer, uint16_t length);
static void readHistogramVoltageViolationBins(uint8_t* buffer, uint16_t length);
static void readHistogramTemperatureHistogramBins(uint8_t* buffer, uint16_t length);
static void readHistogramCurrentTemperatureBins(uint8_t* buffer, uint16_t length);
static void readHistogramHeatingCurrentBins(uint8_t* buffer, uint16_t length);
static void readHistogramCurrentViolationLogBins(uint8_t* buffer, uint16_t length);
static void readCurrentViolationHistogram_Cont(uint8_t* buffer, uint16_t length);
static void readSocTemperatureHistogram(uint8_t* buffer, uint16_t length);
static void readHistogramCurrentViolationLog(uint8_t* buffer, uint16_t length);
static void readMasterPcbTemperatureHistogram(uint8_t* buffer, uint16_t length);
static void readBatteryContactorHistogram(uint8_t* buffer, uint16_t length);
static void readCurrentViolationHistogram_Pulse(uint8_t* buffer, uint16_t length);
static void readHistogramCurrentViolationBins(uint8_t* buffer, uint16_t length);
static void readHistogramMasterPcbTemperatureBins(uint8_t* buffer, uint16_t length);
static void readHistogramVoltageTemperatureVoltageBins(uint8_t* buffer, uint16_t length);
static void readUTBatHistogramTBins(uint8_t* buffer, uint16_t length);
static void readHistogramVoltageTemperature(uint8_t* buffer, uint16_t length);
static void readCurrentTemperatureHistogram_Charge(uint8_t* buffer, uint16_t length);
static void readCurrentTemperatureHistogram_Drive(uint8_t* buffer, uint16_t length);
static void readHistogramSocBins(uint8_t* buffer, uint16_t length);
static void readHistogramVoltageContactor(uint8_t* buffer, uint16_t length);
static void readHistogramVoltageContactorBins(uint8_t* buffer, uint16_t length);

// *************************************************************************************************** /
// ************************* Diagnostic_Data ********************************************************* /
// *************************************************************************************************** /

static void readLibTemperatureData(uint8_t* buffer, uint16_t length);
static void readLibVoltageData(uint8_t* buffer, uint16_t length);
static uint16_t readLibCellBalancingCounter(void);
static void readLibVoltageMeasurements(uint8_t* buffer, uint16_t length);
static void readLibCurrentMeasurements(uint8_t* buffer, uint16_t length);
static void readListOfLastVins(uint8_t* buffer, uint16_t length);
static void readIndividualSnapshotData(uint8_t* buffer, uint16_t length);
static void readLibTotalTime(uint8_t* buffer, uint16_t length);
static void getContactorStates(uint8_t* buffer, uint16_t length);
static uint8_t getDiagnosticSession(uint8_t* buffer, uint16_t length);
static void readIcdaDiagInfoData(uint8_t* buffer, uint16_t length);
static void readIcdaIdentificationData(uint8_t* buffer, uint16_t length);
static void readAfeCommunicationErrorCounter(uint8_t* buffer, uint16_t length);
static void readIcdaAfeMeasurementTimeDifference(uint8_t* buffer, uint16_t length);

// *************************************************************************************************** /
// ************************* Master_Configuration **************************************************** /
// *************************************************************************************************** /

static void readBatteryConfig(uint8_t* buffer, uint16_t length);
static void readCellConfig(uint8_t* buffer, uint16_t length);
static void readCanBaudrate(uint8_t* buffer, uint16_t length);
static void readContactorConfiguration(uint8_t* buffer, uint16_t length);
static uint16_t readBrandId(void);
static void readComponentsPowerConsumption(uint8_t* buffer, uint16_t length);
static void readNtcConfig(uint8_t* buffer, uint16_t length);
static void readCpsSetting(uint8_t* buffer, uint16_t length);
static void readSafetyCurrentSensorDirections(uint8_t* buffer, uint16_t length);
static void readPeriodicWakeupConfig(uint8_t* buffer, uint16_t length);
static void readS2PrechargeConfiguration(uint8_t* buffer, uint16_t length);  // @req CB-92395

// *************************************************************************************************** /
// ********************************** Module_Data **************************************************** /
// *************************************************************************************************** /

// *************************************************************************************************** /
// ********************************** Algorithm_Data ************************************************* /
// *************************************************************************************************** /

// *************************************************************************************************** /
// ********************************** LIB_Identification ********************************************* /
// *************************************************************************************************** /

// *************************************************************************************************** /
// *************************************** KION_CAN_Data ********************************************* /
// *************************************************************************************************** /

static void readCanOpenTimeOfDay(uint8_t* buffer, uint16_t length);
static void readKionTruckOperatingHours(uint8_t* buffer, uint16_t length);
static void readEmergencyLib(uint8_t* buffer, uint16_t length);
static uint8_t readCanSignalBmsReqCPSout(void);
static uint8_t readCanSignalBmsReqPowerDown(void);
static uint8_t readCanSignalBmsInfoBMSState(void);
static uint32_t readCanSignalBmsReqCPSoutI(void);
static uint32_t readCanSignalBmsReqCPSoutBoostI(void);
static uint16_t readCanSignalBmsInfoTimeToWakeUp(void);
static uint8_t readCanSignalDeepDisPossible(void);
static uint8_t readCanSignalDeepDisImminent(void);
static uint32_t readCanSignalBmsCANopenMs(void);
static uint16_t readCanSignalBmsCANopenDays(void);


// *************************************************************************************************** /
// ******************************************* KION_Data ********************************************* /
// *************************************************************************************************** /

static void readStandardSnapshotData(uint8_t* buffer, uint16_t length);
static void readEcuManufacturingDate(uint8_t* buffer, uint16_t length);
static void readEcuSerialNumber(uint8_t* buffer, uint16_t length);
static void getVehicleIdentificationNumber(uint8_t* buffer, uint16_t length);

//***************************************************************************//
//************************** BOOTLOADER *************************************//
//***************************************************************************//

//************************** FINGERPRINT ************************************//
static void getFingerprint(uint8_t* buffer, uint8_t blockNumber);
static void getFingerprintMultiBlock(uint8_t* buffer, const uint8_t* blockNumber);
static void getHISFingerprint(uint8_t* buffer, uint16_t length);
static void getBootSoftwareFingerprint(uint8_t* buffer, uint16_t length);
static void getLogicalBlockTableFingerprint(uint8_t* buffer, uint16_t length);
static void getApplicationSoftwareFingerprint(uint8_t* buffer, uint16_t length);

//************************** COUNTER & LIMIT ********************************//
static void getCounter(uint8_t* buffer, uint8_t blockNumber);
static void getLimit(uint8_t* buffer, uint8_t blockNumber);
static void getLogicalBlockTableCounter(uint8_t* buffer, uint16_t length);
static void getLogicalBlockTableLimit(uint8_t* buffer, uint16_t length);
static void getApplicationSoftwareCounter(uint8_t* buffer, uint16_t length);
static void getApplicationSoftwareLimit(uint8_t* buffer, uint16_t length);

//************************** IDENTIFICATION *********************************//
static void getIdentification(uint8_t* buffer, const char* identification);
static void getIdentificationBackup(uint8_t* buffer, uint8_t startAddress);
static void getIdentificationWithoutBlocks(uint8_t* buffer, char* identification);
static void getBootSoftwareIdentification(uint8_t* buffer, uint16_t length);
static void getLogicalBlockTableIdentification(uint8_t* buffer, uint16_t length);
static void getBootSoftwareIdentificationBackup(uint8_t* buffer, uint16_t length);
static void getLogicalBlockTableIdentificationBackup(uint8_t* buffer, uint16_t length);
static void getApplicationSoftwareIdentificationBackup(uint8_t* buffer, uint16_t length);
static void getSystemNameOrEngineType(uint8_t* buffer, uint16_t length);
static void getTesterSerialNumber(uint8_t* buffer, uint16_t length);
static void getEcuInstallationDate(uint8_t* buffer, uint16_t length);
static void getDiagnosticVariantId(uint8_t* buffer, uint16_t length);
static uint16_t getBrandId(void);
static uint16_t getVehicleManufacturerECUSoftwareNumber(void);
static uint8_t isECUGateway(void);
static void getSoftwareVersionNumber(uint8_t* buffer, uint16_t length, uint16_t variant);
static void getProgrammingDate(uint8_t* buffer, uint16_t length);

static uint8_t getSecurityAccessTest(void);
static uint8_t getLibChargingPreventionExcBassi(void);

// *************************************************************************************************** /
// ************************* PRIVATE FUNCTIONS DEFINITIONS ******************************************* /
// *************************************************************************************************** /

static uint8_t uds_readTable_assignEnumValueFromBaudrate(uint32_t baudrate)
{
    uint8_t returnVal;
    switch(baudrate)
    {
        case 500u * 1000u:
            returnVal = 0u;
            break;
        case 1000u * 1000u:
            returnVal = 3u;
            break;
        default:
            returnVal = UINT8_MAX;
            break;
    }
    return returnVal;
}

static uint8_t dummy_u8(void)
{
    return (uint8_t)1u;
}

static uint16_t dummy_u16(void)
{
    return (uint16_t)1u;
}

static uint32_t dummy_u32(void)
{
    return (uint32_t)1u;
}

static uint64_t dummy_u64(void)
{
    return (uint64_t)1u;
}

static int16_t dummy_s16(void)
{
    return (int16_t)1u;
}

static int32_t dummy_s32(void)
{
    return (int32_t)1u;
}

static void dummy_buffer(uint8_t* buffer, uint16_t length)
{
    for(uint16_t i = 0; i < length; i++)
    {
        buffer[i] = 0x00u;
    }
}

static uint8_t getContactorState(uint16_t contactorNumber)
{
    uint8_t returnValue = ContactorOpenClosed_Undefined;
    if(contactorNumber < BMS_CONFIG_NUMBER_OF_RELAIS)
    {
        returnValue = (systemMasterInfoReceive_isRelayClosed(idAllocation_getMasterId(), contactorNumber) == true) ? ContactorOpenClosed_Closed : ContactorOpenClosed_Open;
    }
    return returnValue;
}

static uint8_t getAuxContactorState(uint16_t contactorNumber)
{
    uint8_t returnValue = ContactorOpenClosed_Undefined;
    if(contactorNumber < BMS_CONFIG_NUMBER_OF_RELAIS)
    {
        IO_VAL_t value          = auxRelayMeasurement_getValue(contactorNumber);
        const RelayTable* table = relayTable_getTableForThisMaster();
        bool state              = ((table[contactorNumber].aux == RELAYAUX_NOPEN) && (value == IO_HIGH_STATE))
                     || ((table[contactorNumber].aux == RELAYAUX_NCLOSED) && (value == IO_LOW_STATE));
        returnValue = (state == true) ? UDS_READ_TABLE_AUX_CONTACTOR_CLOSED : UDS_READ_TABLE_AUX_CONTACTOR_OPEN;
    }
    return returnValue;
}


// *************************************************************************************************** /
// ************************* Cell_&_Sensor_Map_Data ************************************************** /
// *************************************************************************************************** /


static void readAdcCurrentSensorConfig(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 38u);
    // not supported
}


// *************************************************************************************************** /
// ************************* Histogram_Data ********************************************************** /
// *************************************************************************************************** /

// @req CB-78695
static void readHistogramCellVoltagesBins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 44u);
    uint16_t size              = 0;
    const int32_t* histoBuffer = voltageHistogram_getHistogramLimits(&size);
    DEBUG_ASSERT((size * sizeof(int32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_s32(histoBuffer[i], buffer);
    }
}

static void readHistogramVoltageViolationBins(uint8_t* buffer, uint16_t length)
{
    uint8_t offset                               = 0;
    uint16_t size                                = 0;
    const uint16_t* systemVoltageViolationLimits = voltageViolationHistogram_getSystemVoltageViolationLimits(&size);
    DEBUG_ASSERT((offset + (size * sizeof(uint16_t))) <= length);
    memcpy(&buffer[offset], systemVoltageViolationLimits, size * sizeof(uint16_t));
    offset += (size * sizeof(uint16_t));

    const int16_t* systemTemperatureLimits = voltageViolationHistogram_getSystemTemperatureLimits(&size);
    DEBUG_ASSERT((offset + (size * sizeof(int16_t))) <= length);
    memcpy(&buffer[offset], systemTemperatureLimits, size * sizeof(int16_t));
    offset += (size * sizeof(int16_t));

    const uint16_t* systemVoltageErrorValuesDischarge = voltageViolationHistogram_getSystemVoltageErrorValuesDischarge(&size);
    DEBUG_ASSERT((offset + (size * sizeof(uint16_t))) <= length);
    memcpy(&buffer[offset], systemVoltageErrorValuesDischarge, size * sizeof(uint16_t));
    offset += (size * sizeof(uint16_t));

    const uint16_t* systemVoltageErrorValuesCharge = voltageViolationHistogram_getSystemVoltageErrorValuesCharge(&size);
    DEBUG_ASSERT((offset + (size * sizeof(uint16_t))) <= length);
    memcpy(&buffer[offset], systemVoltageErrorValuesCharge, size * sizeof(uint16_t));
}

static void readHistogramCurrentViolationBins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 7u);
    CurrentViolationConditionParameters parameters = currentViolationHistogram_getConditionParameters();
    buffer                                         = bufferMethods_copyValueToBuffer_u8(parameters.t_regen_limit, buffer);
    buffer                                         = bufferMethods_copyValueToBuffer_u8(parameters.t_dch_limit, buffer);
    buffer                                         = bufferMethods_copyValueToBufferBigEndian_u16(parameters.t_ch_rms_limit, buffer);
    buffer                                         = bufferMethods_copyValueToBufferBigEndian_u16(parameters.t_dch_rms_limit, buffer);
    bufferMethods_copyValueToBuffer_u8(parameters.c_violation, buffer);
}

static void readHistogramMasterPcbTemperatureBins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 18u);
    uint16_t size              = 0;
    const int16_t* histoBuffer = masterPcbTemperatureHistogram_getHistogramBins(&size);
    DEBUG_ASSERT((size * sizeof(int16_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_s16(histoBuffer[i], buffer);
    }
}

static void readMasterPcbTemperatureHistogram(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 40u);
    uint16_t size               = 0;
    const uint32_t* histoBuffer = (const uint32_t*)masterPcbTemperatureHistogram_getHistogram(&size);
    DEBUG_ASSERT((size * sizeof(uint32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_u32(histoBuffer[i], buffer);
    }
}

static void readHistogramVoltageContactorBins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 20u);
    uint16_t size              = 0;
    const int32_t* histoBuffer = voltageContactorHistogram_getHistogramBins(&size);
    DEBUG_ASSERT((size * sizeof(int32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_s32(histoBuffer[i], buffer);
    }
}


// @req CB-78699
static void readHistogramTemperatureHistogramBins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 32u);
    uint16_t size              = 0;
    const int32_t* histoBuffer = temperatureHistogram_getHistogramLimitsOperation(&size);
    DEBUG_ASSERT((size * sizeof(int32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_s32(histoBuffer[i], buffer);
    }
}

// @req CB-78700
static void readHistogramCurrentTemperatureBins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 92u);
    uint16_t size              = 0;
    const int32_t* histoBuffer = batteryCurrentTemperatureHistogram_getHistogramLimits(&size);
    DEBUG_ASSERT((size * sizeof(int32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_s32(histoBuffer[i] / 1000, buffer);
    }
}

// @req CB-78703
static void readHistogramHeatingCurrentBins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 12u);
    uint16_t size                      = 0u;
    const int32_t* histogramBinsBuffer = heatingCurrentHistogram_getHistogramLimits(&size);
    for(uint16_t binIndex = 0u; binIndex < size; binIndex++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_u16(histogramBinsBuffer[binIndex], buffer);
    }
}

// @req CB-89471
static void readHistogramCurrentViolationLogBins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 8u);
    uint8_t limitsLength  = 0u;
    int32_t* limitsBuffer = currentViolationLogHistogram_getHistogramLimits(&limitsLength);
    DEBUG_ASSERT((limitsLength * sizeof(int32_t) == length));
    for(uint8_t index = 0u; index < limitsLength; index++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_s32(limitsBuffer[index], buffer);
    }
}

static void readHistogramVoltageTemperatureVoltageBins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 28u);
    uint16_t size              = 0;
    const int32_t* histoBuffer = moduleVoltageTemperatureHistogram_getVoltageLimits(&size);
    DEBUG_ASSERT((size * sizeof(int32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_s32(histoBuffer[i], buffer);
    }
}

static void readHistogramVoltageTemperature(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 224u);
    uint16_t size               = 0;
    const uint32_t* histoBuffer = (const uint32_t*)moduleVoltageTemperatureHistogram_getHistogram(&size);
    DEBUG_ASSERT((size * sizeof(uint32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_u32(histoBuffer[i], buffer);
    }
}

// @req CB-78658
static void readCurrentTemperatureHistogram_Drive(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 768u);
    uint16_t size               = 0;
    const uint32_t* histoBuffer = (const uint32_t*)batteryCurrentTemperatureHistogram_getDischargeHistogram(&size);
    DEBUG_ASSERT((size * sizeof(uint32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_u32(histoBuffer[i], buffer);
    }
}

static void readBatteryContactorHistogram(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 192u);
    uint16_t size               = 0;
    const uint32_t* histoBuffer = (const uint32_t*)batteryContactorHistogram_getHistogram(&size);
    DEBUG_ASSERT(size * sizeof(uint32_t) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_u32(histoBuffer[i], buffer);
    }
}


// @req CB-78664
static void readCurrentTemperatureHistogram_Charge(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 768u);
    uint16_t size               = 0;
    const uint32_t* histoBuffer = (const uint32_t*)batteryCurrentTemperatureHistogram_getChargeHistogram(&size);
    DEBUG_ASSERT((size * sizeof(uint32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_u32(histoBuffer[i], buffer);
    }
}

static void readCurrentViolationHistogram_Cont(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 72u);
    uint16_t size               = 0;
    const uint32_t* histoBuffer = (const uint32_t*)currentViolationHistogram_getContViolationHistogram(&size);
    DEBUG_ASSERT((size * sizeof(uint32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_u32(histoBuffer[i], buffer);
    }
}

static void readUTBatHistogramTBins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 28u);
    uint16_t size = BATTERY_TEMPERATURE_LIMITS_SIZE;
    extern int32_t batteryTemperatureLimits[];
    DEBUG_ASSERT(length == (size * sizeof(int32_t)));
    for(uint16_t i = 0u; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_s32(batteryTemperatureLimits[i], buffer);
    }
}

static void readHistogramSocBins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 24u);
    uint16_t size = SOC_HISTOGRAM_LIMITS_SIZE;
    extern int32_t socHistogramLimits[];
    DEBUG_ASSERT(length == (size * sizeof(int32_t)));
    for(uint16_t i = 0u; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_s32(socHistogramLimits[i], buffer);
    }
}
static void readSocTemperatureHistogram(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 224u);
    uint16_t size               = 0;
    const uint32_t* histoBuffer = (const uint32_t*)socTemperatureHistogram_getHistogram(&size);
    DEBUG_ASSERT((size * sizeof(uint32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_u32(histoBuffer[i], buffer);
    }
}

// @req CB-89470
static void readHistogramCurrentViolationLog(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 40u);
    uint16_t numberOfRings                            = 0u;
    CurrentViolationLogHistogramRing* histogramBuffer = currentViolationLogHistogram_getHistogram(&numberOfRings);
    DEBUG_ASSERT(numberOfRings == CURRENT_VIOLATION_LOG_HISTOGRAM_NUMBER_OF_RINGS);
    DEBUG_ASSERT(((numberOfRings * CURRENT_VIOLATION_LOG_HISTOGRAM_VALUES_IN_RING) * sizeof(uint32_t)) == length);
    for(uint16_t ringIndex = 0u; ringIndex < numberOfRings; ringIndex++)
    {
        for(uint16_t eventIndex = 0u; eventIndex < CURRENT_VIOLATION_LOG_HISTOGRAM_VALUES_IN_RING; eventIndex++)
        {
            buffer = bufferMethods_copyValueToBufferBigEndian_u32(histogramBuffer[ringIndex].ringValues[eventIndex].value, buffer);
        }
    }
}

static void readHistogramVoltageContactor(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 80u);
    uint16_t size               = 0;
    const uint32_t* histoBuffer = (const uint32_t*)voltageContactorHistogram_getHistogram(&size);
    logging_info("%i, %i\n", size, length);
    DEBUG_ASSERT(size * sizeof(uint32_t) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_u32(histoBuffer[i], buffer);
    }
}

static void readCurrentViolationHistogram_Pulse(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 72u);
    uint16_t size               = 0;
    const uint32_t* histoBuffer = (const uint32_t*)currentViolationHistogram_getPulseViolationHistogram(&size);
    DEBUG_ASSERT((size * sizeof(uint32_t)) == length);
    for(uint16_t i = 0; i < size; i++)
    {
        buffer = bufferMethods_copyValueToBufferBigEndian_u32(histoBuffer[i], buffer);
    }
}

// *************************************************************************************************** /
// ************************* Diagnostic_Data ********************************************************* /
// *************************************************************************************************** /

// @req CB-78494
static void readLibTotalTime(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 20u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(diagnosticTimes_getDiagnosticTotalOperatingTimeIns(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(diagnosticTimes_getDiagnosticDriveOperatingTimeIns(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(diagnosticTimes_getDiagnosticChargeOperatingTimeIns(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(diagnosticTimes_getDiagnosticPeriodicWakeUpTimeIns(), buffer);
    bufferMethods_copyValueToBufferBigEndian_u32(diagnosticTimes_getDiagnosticTotalBalancingTimeIns(), buffer);
}

// @req CB-89025
static void readLibEventData(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 38u);
    buffer = bufferMethods_copyValueToBufferBigEndian_s32(eventData_getHighestPositiveCurrentDriveModeMaster(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_s32(eventData_getHighestNegativeCurrentDriveModeMaster(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_s32(eventData_getHighestPositiveCurrentChargeModeMaster(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(eventData_getHighestBatteryVoltageMaster(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(eventData_getLowestBatteryVoltageMaster(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(eventData_getHighestCellVoltageMaster(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(eventData_getLowestCellVoltageMaster(), buffer);
    buffer = bufferMethods_copyValueToBuffer_s8(eventData_getHighestFuSiTemperatureMaster(), buffer);
    buffer = bufferMethods_copyValueToBuffer_s8(eventData_getLowestFuSiTemperatureMaster(), buffer);
    bufferMethods_copyValueToBufferBigEndian_u16(eventData_getHighestImbalanceCellVoltageMaster(), buffer);
}

static uint16_t readLibCellBalancingCounter(void)
{
    uint16_t retVal = 0;
    for(uint8_t i = 0; i < BMS_CONFIG_NUMBER_OF_SLAVES; i++)
    {
        uint16_t balancingStatusBitmask = subMasterBalancing_getCellBalancingStatusValue(i);
        for(uint8_t j = 0; j < AFE_MAX_NUMBER_OF_CELLS; j++)
        {
            if(((balancingStatusBitmask >> j) & 0x01u) == true)
            {
                retVal++;
            }
        }
    }
    return retVal;
}

// @req CB-92898
static void readLibTemperatureData(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 22u);

    int16_t moduleFuSiTemperatureSensorMinimum        = cellTemperatureMeasurement_getMinValue();                           // @req WHBMS-15502
    uint8_t FuSiSensorModuleWithTemperatureMinimum    = cellTemperatureMeasurement_getTemperatureSensorAddressOfMin();      // @req WHBMS-15503
    uint8_t FuSiSensorNumberWithTemperatureMinimum    = cellTemperatureMeasurement_getMinNumber();                          // @req WHBMS-15505
    int16_t moduleFuSiTemperatureSensorMaximum        = cellTemperatureMeasurement_getMaxValue();                           // @req WHBMS-15506
    uint8_t FuSiSensorModuleWithTemperatureMaximum    = cellTemperatureMeasurement_getTemperatureSensorAddressOfMax();      // @req WHBMS-15525
    uint8_t FuSiSensorNumberWithTemperatureMaximum    = cellTemperatureMeasurement_getMaxNumber();                          // @req WHBMS-15526
    int16_t moduleNonFuSiTemperatureSensorMinimum     = terminalTemperatureMeasurement_getMinValue();                       // @req WHBMS-15527
    uint8_t nonFuSiSensorModuleWithTemperatureMinimum = terminalTemperatureMeasurement_getTemperatureSensorAddressOfMin();  // @req WHBMS-15528
    uint8_t nonFuSiSensorNumberWithTemperatureMinimum = terminalTemperatureMeasurement_getMinNumber();                      // @req WHBMS-15529
    int16_t moduleNonFuSiTemperatureSensorMaximum     = terminalTemperatureMeasurement_getMaxValue();                       // @req WHBMS-15530
    uint8_t nonFuSiSensorModuleWithTemperatureMaximum = terminalTemperatureMeasurement_getTemperatureSensorAddressOfMax();  // @req WHBMS-15531
    uint8_t nonFuSiSensorNumberWithTemperatureMaximum = terminalTemperatureMeasurement_getMaxNumber();                      // @req WHBMS-15532
    int16_t masterPcbTemperatureSensor                = measurements_getOnBoardTemperature_getTSensorOnMaster();            // @req WHBMS-15538
    int16_t moduleFuSiTemperatureSensorAverage        = cellTemperatureMeasurement_getAverageValue();                       // @req WHBMS-15540
    int16_t moduleNonFuSiTemperatureSensorAverage     = terminalTemperatureMeasurement_getAverageValue();                   // @req WHBMS-15545

    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBufferBigEndian_s16(moduleFuSiTemperatureSensorMinimum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBuffer_u8(FuSiSensorModuleWithTemperatureMinimum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBuffer_u8(FuSiSensorNumberWithTemperatureMinimum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBufferBigEndian_s16(moduleFuSiTemperatureSensorMaximum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBuffer_u8(FuSiSensorModuleWithTemperatureMaximum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBuffer_u8(FuSiSensorNumberWithTemperatureMaximum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBufferBigEndian_s16(moduleNonFuSiTemperatureSensorMinimum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBuffer_u8(nonFuSiSensorModuleWithTemperatureMinimum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBuffer_u8(nonFuSiSensorNumberWithTemperatureMinimum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBufferBigEndian_s16(moduleNonFuSiTemperatureSensorMaximum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBuffer_u8(nonFuSiSensorModuleWithTemperatureMaximum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBuffer_u8(nonFuSiSensorNumberWithTemperatureMaximum, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBufferBigEndian_s16(masterPcbTemperatureSensor, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    buffer = bufferMethods_copyValueToBufferBigEndian_s16(moduleFuSiTemperatureSensorAverage, buffer);
    // cppcheck-suppress misra-c2012-17.8; A function parameter should not be modified
    bufferMethods_copyValueToBufferBigEndian_s16(moduleNonFuSiTemperatureSensorAverage, buffer);
}

static void readLibVoltageData(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 20u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(cellVoltageMeasurement_getMinValue(), buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(cellVoltageMeasurement_getCSCAddressOfMin(), buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(cellVoltageMeasurement_getMinNumber(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(cellVoltageMeasurement_getMaxValue(), buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(cellVoltageMeasurement_getCSCAddressOfMax(), buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(cellVoltageMeasurement_getMaxNumber(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(cellVoltageMeasurement_getMaxCellVoltageDrift(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(moduleVoltageMeasurement_getMin(), buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(moduleVoltageMeasurement_getMinNumber(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(moduleVoltageMeasurement_getMax(), buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(moduleVoltageMeasurement_getMaxNumber(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(moduleVoltageMeasurement_getMaxModuleVoltageDrift(), buffer);
    bufferMethods_copyValueToBufferBigEndian_u16(cellVoltageMeasurement_getAverageValue(), buffer);
}

static void readLibVoltageMeasurements(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 12u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(highVoltageMeasurement_getMasterHvVoltagesValue(2), buffer);  // @req CB-78590
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(highVoltageMeasurement_getMasterHvVoltagesValue(1), buffer);  // @req CB-78591
    bufferMethods_copyValueToBufferBigEndian_u32(highVoltageMeasurement_getMasterHvVoltagesValue(0), buffer);           // @req CB-78593
}

static void readLibCurrentMeasurements(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 8u);
    uint16_t size               = 0u;
    int32_t* heaterCurrentArray = (int32_t*)heatingCurrentMeasurement_getCurrents(&size);                    // @req CB-78586
    int32_t current             = batteryCurrentMeasurement_getValue() - sum_s32(heaterCurrentArray, size);  //@req CB-78585
    buffer                      = bufferMethods_copyValueToBufferBigEndian_u32(current, buffer);
    bufferMethods_copyValueToBufferBigEndian_u32(batteryCurrentMeasurement_getValue(), buffer);
}

static void readListOfLastVins(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 1536u);
    DEBUG_ASSERT((sizeof(char) * LIB_IDENTIFICATION_NUMBERS_OF_VINS_TO_STORE * LIB_IDENTIFICATION_VIN_STRING_LENGTH) == 1536u);
    uint16_t offset = 0;
    for(uint8_t i = 0; i < LIB_IDENTIFICATION_NUMBERS_OF_VINS_TO_STORE; i++)
    {
        DEBUG_ASSERT(offset <= (length - LIB_IDENTIFICATION_VIN_STRING_LENGTH));
        uint8_t stringLength;
        const char* stringPointer = libIdentification_getVehicleIdentificationNumber(i, &stringLength);
        DEBUG_ASSERT(stringLength == LIB_IDENTIFICATION_VIN_STRING_LENGTH);
        memcpy(&buffer[offset], stringPointer, stringLength * sizeof(char));
        offset += (stringLength * sizeof(char));
    }
}

static void readIndividualSnapshotData(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    DTCSnapshot snapshot;
    demUDS_getLastLoadedSnapshot(&snapshot);
    memcpy(&buffer[0], &snapshot.data[DEM_UDS_STANDARD_SNAPSHOT_SIZE], DEM_UDS_INDIVIDUAL_SNAPSHOT_SIZE);
}

static void getContactorStates(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 6u);
    buffer = bufferMethods_copyValueToBuffer_u8(getContactorState(0u), buffer);     // @req CB-78601
    buffer = bufferMethods_copyValueToBuffer_u8(getContactorState(1u), buffer);     // @req CB-78602
    buffer = bufferMethods_copyValueToBuffer_u8(getContactorState(2u), buffer);     // @req CB-78603
    buffer = bufferMethods_copyValueToBuffer_u8(getAuxContactorState(0u), buffer);  // @req CB-78605
    buffer = bufferMethods_copyValueToBuffer_u8(getAuxContactorState(1u), buffer);  // @req CB-78606
    bufferMethods_copyValueToBuffer_u8(getAuxContactorState(2u), buffer);           // @req CB-78604
}
static uint8_t getDiagnosticSession(uint8_t* buffer, uint16_t length)
{
    return READ_TABLE_KION_PROGRAMMING_SESSION;
}

// @req CB-93244 CB-93245
static void readIcdaDiagInfoData(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    icdaSensor_requestNewDiagnosticData();

    ICDASensor_Diagnostic_Information diagInfo = icdaSensor_getDiagnosticInformation();                                                                           // @req CB-10282
    buffer                                     = bufferMethods_copyValueToBufferBigEndian_u32(diagInfo.PARAM_ICD_Status_Bits, buffer);                            // @req CB-10258
    buffer                                     = bufferMethods_copyValueToBufferBigEndian_s16((uint32_t)diagInfo.PARAM_ICD_Temperature.temperatureChip, buffer);  // @req CB-10257
    buffer                                     = bufferMethods_copyValueToBufferBigEndian_s16((uint32_t)diagInfo.PARAM_ICD_Temperature.temperatureExt, buffer);   // @req CB-10257
    bufferMethods_copyValueToBufferBigEndian_u32(diagInfo.PARAM_ICD_Lifetime, buffer);                                                                            // @req CB-10261
}


static void readIcdaIdentificationData(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 38u);
    ICDASensor_Identification icdaIdData = icdaSensor_getIcdaSensorIdentification();  // @req CB-10250
    for(uint8_t deviceIdIndex = 0; deviceIdIndex < ICDA_DEVICE_ID_LENGTH; deviceIdIndex++)
    {
        buffer = bufferMethods_copyValueToBuffer_u8(icdaIdData.PARAM_ICD_DeviceID[deviceIdIndex], buffer);  // @req CB-10249
    }

    buffer = bufferMethods_copyValueToBufferBigEndian_u24(icdaIdData.PARAM_ICD_SerialNumber, buffer);  // @req CB-10253
    bufferMethods_copyValueToBufferBigEndian_u24(icdaIdData.PARAM_ICD_FWVersion, buffer);              // @req CB-10252
}

static void readAfeCommunicationErrorCounter(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 28u);

    buffer = bufferMethods_copyValueToBufferBigEndian_u32(afe_MC33771_X_getFrameErrorCounter(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(afe_MC33771_X_getRegAddressErrorCounter(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(afe_MC33771_X_getCscAddressErrorCounter(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(afe_MC33771_X_getRequestTypeErrorCounter(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(afe_MC33771_X_getCrcErrorCounter(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(afe_MC33771_X_getMsgCounterErrorCounter(), buffer);
    bufferMethods_copyValueToBufferBigEndian_u32(afe_MC33771_X_getCorrectFrameCounter(), buffer);
}

static void readIcdaAfeMeasurementTimeDifference(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 20u);

    const SyncMeasurementsHelper* measurementRates = synchronizedMeasurements_getAfeAndIcdaMeasurementSynchronizationVariable();

    buffer = bufferMethods_copyValueToBufferBigEndian_u16(measurementRates->numberOfMeasurements, buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(measurementRates->numberOfTimeDifferenceViolations, buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(measurementRates->minTimeDifference, buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(measurementRates->maxTimeDifference, buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(measurementRates->avgTimeDifference, buffer);
    bufferMethods_copyValueToBufferBigEndian_u32(measurementRates->lastTimeDifference, buffer);
}

// *************************************************************************************************** /
// ************************* Master_Configuration **************************************************** /
// *************************************************************************************************** /

static void readBatteryConfig(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 5u);

    buffer = bufferMethods_copyValueToBuffer_u8(BMS_CONFIG_NUMBER_OF_SLAVES, buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(CELL_MODULE_CONFIG_STRING_NO_OF_MODULES_PARALLEL, buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(CELL_MODULE_CONFIG_STRING_NO_OF_MODULES_SERIAL, buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_PARALLEL, buffer);
    bufferMethods_copyValueToBuffer_u8(CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL, buffer);
}

static void readCellConfig(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 6u);

    buffer = bufferMethods_copyValueToBufferBigEndian_u16(CELL_MODULE_CONFIG_CELL_NOMINAL_VOLTAGE, buffer);
    // 3600 -> unit conversion mAs to mAh
    bufferMethods_copyValueToBufferBigEndian_u32(CELL_MODULE_CONFIG_CELL_NOMINAL_CAPACITY / 3600, buffer);
}

static void readCanBaudrate(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 2u);

    buffer[0] = uds_readTable_assignEnumValueFromBaudrate(CAN_NODE1_BAUDRATE);
    buffer[1] = uds_readTable_assignEnumValueFromBaudrate(CAN_NODE2_BAUDRATE);
}

// @req CB-79078
static void readContactorConfiguration(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 9u);
    uint16_t relayTableSize = relayTable_getSizeForThisMaster();
    DEBUG_ASSERT((relayTableSize * 2u) < length);
    const RelayTable* relayTable = relayTable_getTableForThisMaster();
    for(uint16_t index = 0u; index < relayTableSize; index++)
    {
        if(relayTable[index].relayType == RELAYPOSTYPE_NOT_CONNECTED)
        {
            buffer = bufferMethods_copyValueToBuffer_u8(ContactorConntected_NotConnected, buffer);
            buffer = bufferMethods_copyValueToBuffer_u8(relayTable[index].aux, buffer);
        }
        else
        {
            if(relayTable[index].safetyRelay == true)
            {
                buffer = bufferMethods_copyValueToBuffer_u8(ContactorConntected_ConnectedFusi, buffer);
                buffer = bufferMethods_copyValueToBuffer_u8(relayTable[index].aux, buffer);
            }
            else
            {
                buffer = bufferMethods_copyValueToBuffer_u8(ContactorConnected_ConnectedNonFusi, buffer);
                buffer = bufferMethods_copyValueToBuffer_u8(relayTable[index].aux, buffer);
            }
        }
    }
    for(uint16_t index2 = (relayTableSize * 2u); index2 < 8u; index2++)
    {
        buffer = bufferMethods_copyValueToBuffer_u8(0u, buffer);
    }
    bufferMethods_copyValueToBuffer_u8(stmFct_getPreferenceDirection(), buffer);
}

static uint16_t readBrandId(void)
{
    uint16_t brand    = UINT16_MAX;
    uint16_t tmpBrand = PROTOCOL_SELECTION_CONFIG_BRAND_ID_DETECTION;
    if(tmpBrand == Protocol_KION)
    {
        brand = 3u;
    }
    else if(tmpBrand == Protocol_AUTOMATIC)
    {
        brand = 0u;
    }
    else
    {
        brand = UINT16_MAX;
    }
    return brand;
}

static void readComponentsPowerConsumption(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 6u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(componentsPowerConsumption_getAverageOfMaster(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(componentsPowerConsumption_getAverageOfCsc(), buffer);
    bufferMethods_copyValueToBufferBigEndian_u16(componentsPowerConsumption_getAverageOfCps(), buffer);
}

static void readNtcConfig(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 5u);

    for(uint8_t i = 0; i < length; i++)
    {
        uint8_t result         = UINT8_MAX;
        bool isFusiRelevant    = ((uint8_t)1 << (i + 1u)) & AFE_CONNECTED_TEMPSENS;
        bool isNotFusiRelevant = ((uint8_t)1 << (i + 1u)) & AFE_CONNECTED_APP_TEMPSENS;
        if(isFusiRelevant)
        {
            result = FUSI;
        }
        else if(isNotFusiRelevant)
        {
            result = NON_FUSI;
        }
        else
        {
            result = NOT_CONNECTED;
        }
        buffer[i] = result;
    }
}

static void readCpsSetting(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 12u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(CPS_OUT_LIMIT, buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(CPS_OUT_LIMIT_BOOST, buffer);
    bufferMethods_copyValueToBufferBigEndian_u32(CPS_IMPUT_VOLTAGE_LIMIT, buffer);
}

static uint8_t readStmPushbuttonConfig(void)
{
    uint8_t retVal = 0u;
    if(STM_CONFIG_PUSHBUTTON == true)
    {
        retVal = 3u;
    }
    return retVal;
}

static void readStmTimeoutShutdownConfig(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 6u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(STM_CONFIG_TIMEOUT_INIT, buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(STM_CONFIG_TIMEOUT_WAITINGMODE, buffer);
    bufferMethods_copyValueToBufferBigEndian_u16(STM_CONFIG_TIMEOUT_DIAGMODE, buffer);
}

static void readStmTimeoutOpenContactorsConfig(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 4u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(STM_CONFIG_TIMEOUT_OPEN_CONTACTORS, buffer);
    // 1000 -> convert mA to output unit [A]
    bufferMethods_copyValueToBufferBigEndian_u16((uint16_t)(STM_CONFIG_SHUTDOWN_MAX_CURRENT / 1000), buffer);
}

static void readStmPwuConfig(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 12u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(STM_CONFIG_PWU_MAX_BALANCING_TIME, buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(STM_CONFIG_PWU_MAX_RELAXINGG_TIME, buffer);
    bufferMethods_copyValueToBufferBigEndian_u32(STM_CONFIG_PWU_TIMEOUT_RECOVERY_ROUTINE, buffer);
}

static uint16_t readStmEmergencyTimerConfig(void)
{
    return (uint16_t)STM_CONFIG_EMERGENCY_CAT3_TIMER;
}

static void readStmErrorConfig(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 4u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(STM_CONFIG_ERROR_TIMEOUT_CAN, buffer);
    bufferMethods_copyValueToBufferBigEndian_u16(STM_CONFIG_ERROR_TIMEOUT_OPEN_CONTACTORS, buffer);
}

static uint8_t readStmNumberOfPdoCountsConfig(void)
{
    return (uint8_t)STM_CONFIG_NUMBER_OF_PDO_COUNTS;
}

static void readStmCpsOutConfig(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 6u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(STM_CONFIG_CPSOUT_DELAY_ENABLE, buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(STM_CONFIG_CPSOUT_DELAY_DISABLE_DRIVE, buffer);
    bufferMethods_copyValueToBufferBigEndian_u32(STM_CONFIG_CPSOUT_DELAY_DISABLE_EMERGENCY, buffer);
}


static void readDiagnosticEnergyCountData(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 12u);

    const ENERGY_COUNTER_NVM* tmpData = energyCounter_getCoulombCounterData();
    // calculate mWs in Wh
    uint32_t tmp1 = (uint32_t)(tmpData->diagnosticCoulombCountPositiveCharge / 3600u / 1000u);
    uint32_t tmp2 = (uint32_t)(tmpData->diagnosticCoulombCountNegativeDischarge / 3600u / 1000u);
    uint32_t tmp3 = (uint32_t)(tmpData->diagnosticCoulombCountPositiveDischarge / 3600u / 1000u);

    buffer = bufferMethods_copyValueToBufferBigEndian_u32(tmp1, buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(tmp2, buffer);
    bufferMethods_copyValueToBufferBigEndian_u32(tmp3, buffer);
}

static void readSafetyCurrentSensorDirections(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 2u);
    uint8_t tmp1 = (currentSensorIf_getCurrentDirection(0u) >= 0) ? 0u : 3u;
    uint8_t tmp2 = (currentSensorIf_getCurrentDirection(1u) >= 0) ? 0u : 3u;

    buffer = bufferMethods_copyValueToBuffer_u8(tmp1, buffer);
    bufferMethods_copyValueToBuffer_u8(tmp2, buffer);
}

static void readPeriodicWakeupConfig(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 17u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(periodicWakeUp_getMaxNumberOfFastWakeUps(), buffer);
    buffer = bufferMethods_copyValueToBuffer_u8((uint8_t)periodicWakeUp_getTemperatureThreshold(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(periodicWakeUp_getShortInterval(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(periodicWakeUp_getMiddleInterval(), buffer);
    bufferMethods_copyValueToBufferBigEndian_u32(periodicWakeUp_getLongInterval(), buffer);
}

// @req CB-92395
static void readS2PrechargeConfiguration(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 6u);
    buffer = bufferMethods_copyValueToBuffer_u8((uint8_t)stmPrecharge_getS2PrechargeMethod(), buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(stmPrecharge_getS2VoltageBasedPrechargeCondition(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(stmPrecharge_getS2VoltageBasedPrechargeTimeout(), buffer);
    bufferMethods_copyValueToBufferBigEndian_u16(stmPrecharge_getS2TimeBasedPrechargeTime(), buffer);
}

// *************************************************************************************************** /
// ********************************** Module_Data **************************************************** /
// *************************************************************************************************** /

// *************************************************************************************************** /
// ********************************** Algorithm_Data ************************************************* /
// *************************************************************************************************** /


// *************************************************************************************************** /
// ********************************** LIB_Identification ********************************************* /
// *************************************************************************************************** /

static void readLibIdentificationManufacturerName(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibManufacturerName(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationDeviceName(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibDeviceName(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationTrayVariant(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibTrayVariant(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationCellTypeName(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibCellTypeName(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationKionHardwareNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 11u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibKionHardwareNumber(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationKionPartNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibKionPartNumber(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationKionZsbNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 11u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibKionZsbNumber(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationKionOrderNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibKionOrderNumber(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationKionCustomerOrderNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibKionCustomerOrderNumber(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationKionSequenceNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibKionSequenceNumber(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationKbsBpn(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibKbsBpn(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationKbsSerialNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibKbsSerialNumber(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationKbsPartNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = libIdentification_getLibKbsPartNumber(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void readLibIdentificationNameplate(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 34u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(libIdentification_getLibNameplateNominalVoltage(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(libIdentification_getLibNameplateNumberOfParallelConnectedCells(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(libIdentification_getLibNameplateNumberOfSerialConnectedCells(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(libIdentification_getLibNameplateMaxChargeCurrent(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(libIdentification_getLibNameplateMaxDischargeCurrent(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(libIdentification_getLibNameplateMaxChargeVoltage(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(libIdentification_getLibNameplateMaxDischargeVoltage(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(libIdentification_getLibNameplateCapacity(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(libIdentification_getLibNameplateCapacityEquivalentLab(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(libIdentification_getLibNameplateEnergyContent(), buffer);
    bufferMethods_copyValueToBufferBigEndian_u16(libIdentification_getLibNameplateWeight(), buffer);
}

static void readLibIdentificationMasterPcb(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 61u);
    uint8_t maxLength;
    const char* pointer = libIdentification_getMasterPcbManufacturer(&maxLength);
    memcpy(buffer, pointer, maxLength * sizeof(char));
    buffer  = bufferMethods_copyValueToBufferBigEndian_u32(libIdentification_getMasterPcbManufacturingDate(), &buffer[maxLength]);
    pointer = libIdentification_getMasterPcbDeviceName(&maxLength);
    memcpy(buffer, pointer, maxLength * sizeof(char));
    buffer  = &buffer[maxLength];
    pointer = libIdentification_getMasterPcbKbsSerialNumber(&maxLength);
    memcpy(buffer, pointer, maxLength * sizeof(char));
    buffer  = &buffer[maxLength];
    pointer = libIdentification_getMasterPcbKbsPartNumber(&maxLength);
    memcpy(buffer, pointer, maxLength * sizeof(char));
}

static void readLibIdentificationCpsPcb(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 61u);
    uint8_t maxLength;
    const char* pointer = libIdentification_getCpsPcbManufacturer(&maxLength);
    memcpy(buffer, pointer, maxLength * sizeof(char));
    buffer  = bufferMethods_copyValueToBufferBigEndian_u32(libIdentification_getCpsPcbManufacturingDate(), &buffer[maxLength]);
    pointer = libIdentification_getCpsPcbDeviceName(&maxLength);
    memcpy(buffer, pointer, maxLength * sizeof(char));
    buffer  = &buffer[maxLength];
    pointer = libIdentification_getCpsPcbKbsSerialNumber(&maxLength);
    memcpy(buffer, pointer, maxLength * sizeof(char));
    buffer  = &buffer[maxLength];
    pointer = libIdentification_getCpsPcbKbsPartNumber(&maxLength);
    memcpy(buffer, pointer, maxLength * sizeof(char));
}

static void readListOfConnectedModuleSerialNumbers(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 512u);
    for(uint8_t i = 0; i < BMS_CONFIG_MAX_NUMBER_OF_SLAVES; i++)
    {
        uint8_t maxLength;
        const char* pointer = libIdentification_getListOfConnectedModuleSerialNumbers(i, &maxLength);
        memcpy(buffer, pointer, maxLength * sizeof(char));
        buffer = &buffer[maxLength];
    }
}

static void readListOfConnectedModulePcbSerialNumbers(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 512u);
    for(uint8_t i = 0; i < BMS_CONFIG_MAX_NUMBER_OF_SLAVES; i++)
    {
        uint8_t maxLength;
        const char* pointer = libIdentification_getListOfConnectedModulePcbSerialNumbers(i, &maxLength);
        memcpy(buffer, pointer, maxLength * sizeof(char));
        buffer = &buffer[maxLength];
    }
}

// *************************************************************************************************** /
// *************************************** KION_CAN_Data ********************************************* /
// *************************************************************************************************** /

static void readCanOpenTimeOfDay(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 6u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(timestamp_getCANopenMilliSeconds(), buffer);
    bufferMethods_copyValueToBufferBigEndian_u16(timestamp_getCANopenDays(), buffer);
}

static void readKionTruckOperatingHours(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 5u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u32(canData_getLastTruckOperatingHours(), buffer);
    bufferMethods_copyValueToBuffer_u8(canData_getLastTruckOperatingHoursMode(), buffer);
}

static void readEmergencyLib(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 7u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(canData_getLastEmergencyCodeLib(), buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(canData_getLastEmergencyRegisterObjectLib(), buffer);
    bufferMethods_copyValueToBufferBigEndian_u32(canData_getLastUdsDtcLib(), buffer);
}

static uint8_t readCanSignalBmsReqCPSout(void)
{
    return (uint8_t)cps_getCpsOutReq();
}

static uint8_t readCanSignalBmsReqPowerDown(void)
{
    return (uint8_t)cps_getCpsPowerDown();
}

static uint8_t readCanSignalBmsInfoBMSState(void)
{
    return (uint8_t)cps_getCpsInfoBmsState();
}

static uint32_t readCanSignalBmsReqCPSoutI(void)
{
    return (CPS_OUT_LIMIT * KIONINTER_BMS_REQ_CPSOUT_I_FACTOR) - KIONINTER_BMS_REQ_CPSOUT_I_OFFSET;
}

static uint32_t readCanSignalBmsReqCPSoutBoostI(void)
{
    return (CPS_OUT_LIMIT_BOOST * KIONINTER_BMS_REQ_CPSOUTBOOST_I_FACTOR) - KIONINTER_BMS_REQ_CPSOUTBOOST_I_OFFSET;
}

static uint16_t readCanSignalBmsInfoTimeToWakeUp(void)
{
    return (uint16_t)(periodicWakeUp_getTimeToWakeUp() & 0xffffu);
}

static uint8_t readCanSignalDeepDisPossible(void)
{
    return (uint8_t)dem_isFaultActive(DTC_CELL_UNDER_VOLTAGE_ERROR, false);
}

static uint8_t readCanSignalDeepDisImminent(void)
{
    return (uint8_t)dem_isFaultActive(DTC_DEEP_DISCHARGE, false);
}

static uint32_t readCanSignalBmsCANopenMs(void)
{
    return timestamp_getCANopenMilliSeconds();
}

static uint16_t readCanSignalBmsCANopenDays(void)
{
    return timestamp_getCANopenDays();
}

// *************************************************************************************************** /
// ******************************************* KION_Data ********************************************* /
// *************************************************************************************************** /

// @req CB-74360 CB-74361
void readManufacturerSoftwareVersion(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 19u);
    buffer = bufferMethods_copyValueToBuffer_u8(2u, buffer);

    // Application
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversion_getMajor(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversion_getMinor(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversion_getPatch(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversionKion_getVariant(), buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(softwareversionKion_getReleaseStatus(), buffer);

    // Data
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversionKion_getGenerationParameter(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversionKion_getVersionParameter(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversionKion_getBugfixParameter(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversionKion_getVariantParameter(), buffer);
    bufferMethods_copyValueToBuffer_u8(softwareversionKion_getReleaseStatusParameter(), buffer);
}

// @req CB-94109
void readAlgorithmSoftwareVersion(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 9u);

    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversionKion_getAlgorithmGenerationParameter(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversionKion_getAlgorithmVersionParameter(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversionKion_getAlgorithmBugfixParameter(), buffer);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(softwareversionKion_getAlgorithmVariantParameter(), buffer);
    bufferMethods_copyValueToBuffer_u8(softwareversionKion_getAlgorithmReleaseStatusParameter(), buffer);
}


static void readStandardSnapshotData(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 12u);
    DTCSnapshot snapshot;
    demUDS_getLastLoadedSnapshot(&snapshot);
    memcpy(&buffer[0], &snapshot.data, DEM_UDS_STANDARD_SNAPSHOT_SIZE);
}

static void readEcuManufacturingDate(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 3u);
    uint8_t dateLength;
    const uint8_t* datePointer = (const uint8_t*)ecuIdentification_getEcuManufacturingDate(&dateLength);
    DEBUG_ASSERT(length == dateLength);
    memcpy(buffer, datePointer, dateLength * sizeof(uint8_t));
}

static void readEcuSerialNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t retLength;
    const uint8_t* data = (const uint8_t*)ecuIdentification_getEcuSerialNumber(&retLength);
    DEBUG_ASSERT(length == retLength);
    memcpy(buffer, data, retLength * sizeof(uint8_t));
}

static void getVehicleIdentificationNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t retLength;
    const uint8_t* data = (const uint8_t*)vehicleManufacturerData_getVehicleIdentificationNumber(&retLength);
    DEBUG_ASSERT(length == retLength);
    memcpy(buffer, data, retLength * sizeof(uint8_t));
}

//***************************************************************************//
//************************** BOOTLOADER *************************************//
//***************************************************************************//

//************************** FINGERPRINT ************************************//

static void getFingerprint(uint8_t* buffer, uint8_t blockNumber)
{
    const uint8_t numberOfLogicalBlocks = 1;
    buffer[0]                           = numberOfLogicalBlocks;
    memcpy((buffer + 1u), &shareData->logicalBlock[blockNumber].fingerprint, sizeof(Fingerprint));
    buffer[(1u + sizeof(Fingerprint))] = shareData->logicalBlock[blockNumber].programmingState;
}

static void getFingerprintMultiBlock(uint8_t* buffer, const uint8_t* blockNumber)
{
    const uint8_t numberOfLogicalBlocks = 2;
    buffer[0]                           = numberOfLogicalBlocks;

    const uint8_t typeLength = 47;  // Fingerprint is 47 bytes
    for(uint8_t i = 0; i < numberOfLogicalBlocks; i++)
    {
        memcpy((buffer + 1u + i + (i * typeLength)), &shareData->logicalBlock[blockNumber[i]].fingerprint, sizeof(Fingerprint));
        buffer[(1u + i + ((i + 1u) * typeLength))] = shareData->logicalBlock[blockNumber[i]].programmingState;
    }
}

static void getHISFingerprint(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 96u);
    const uint8_t blockNumber[2] = { LOGICAL_BLOCK_BOOTLOADER, LOGICAL_BLOCK_APPLICATION };
    getFingerprintMultiBlock(buffer, blockNumber);
}

static void getBootSoftwareFingerprint(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 49u);
    getFingerprint(buffer, LOGICAL_BLOCK_BOOTLOADER);
}

static void getLogicalBlockTableFingerprint(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 49u);
    getFingerprint(buffer, LOGICAL_BLOCK_LOGICAL_BLOCK_TABLE);
}

static void getApplicationSoftwareFingerprint(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 97u);
    const uint8_t blockNumber[2] = { LOGICAL_BLOCK_APPLICATION, LOGICAL_BLOCK_DATA };
    getFingerprintMultiBlock(buffer, blockNumber);
}

//************************** COUNTER & LIMIT ********************************//

// @req CB-74388
// @req CB-74390
// @req CB-74391
// @req CB-74392
// @req CB-74394
static void getCounter(uint8_t* buffer, uint8_t blockNumber)
{
    uint8_t numberOfLogicalBlocks = 1;

    buffer[0] = numberOfLogicalBlocks;

    uint8_t length   = 2;  // Counter and Limit is uint16_t -> 2 x uint8_t
    uint16_t counter = shareData->logicalBlock[blockNumber].programmingCounter;

    for(uint8_t i = 0; i < numberOfLogicalBlocks; i++)
    {
        buffer[((i * length) + 1u)] = (counter >> 8u);
        buffer[((i * length) + 2u)] = counter;
    }
}

// @req CB-74389
// @req CB-74390
// @req CB-74391
// @req CB-74392
// @req CB-74394
static void getLimit(uint8_t* buffer, uint8_t blockNumber)
{
    uint8_t numberOfLogicalBlocks = 1;

    buffer[0] = numberOfLogicalBlocks;

    uint8_t length = 2;  // Counter and Limit is uint16_t -> 2 x uint8_t
    uint16_t limit = shareData->logicalBlock[blockNumber].programmingLimit;

    for(uint8_t i = 0; i < numberOfLogicalBlocks; i++)
    {
        buffer[((i * length) + 1u)] = (limit >> 8u);
        buffer[((i * length) + 2u)] = limit;
    }
}

static void getLogicalBlockTableCounter(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 3u);
    getCounter(buffer, LOGICAL_BLOCK_LOGICAL_BLOCK_TABLE);
}

static void getLogicalBlockTableLimit(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 3u);
    getLimit(buffer, LOGICAL_BLOCK_LOGICAL_BLOCK_TABLE);
}

static void getApplicationSoftwareCounter(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 5u);
    const uint8_t numberOfLogicalBlocks = 2;
    buffer[0]                           = numberOfLogicalBlocks;

    const uint16_t counter[2] = { shareData->logicalBlock[LOGICAL_BLOCK_APPLICATION].programmingCounter, shareData->logicalBlock[LOGICAL_BLOCK_DATA].programmingCounter };
    const uint8_t typeLength  = 2;  // Counter is uint16_t -> 2 x uint8_t
    for(uint8_t i = 0; i < numberOfLogicalBlocks; i++)
    {
        buffer[((i * typeLength) + 1u)] = (counter[i] >> 8u);
        buffer[((i * typeLength) + 2u)] = counter[i];
    }
}

static void getApplicationSoftwareLimit(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 5u);
    const uint8_t numberOfLogicalBlocks = 2;
    buffer[0]                           = numberOfLogicalBlocks;

    const uint16_t limit[2]  = { shareData->logicalBlock[LOGICAL_BLOCK_APPLICATION].programmingLimit, shareData->logicalBlock[LOGICAL_BLOCK_DATA].programmingLimit };
    const uint8_t typeLength = 2;  // Limit is uint16_t -> 2 x uint8_t
    for(uint8_t i = 0; i < numberOfLogicalBlocks; i++)
    {
        buffer[((i * typeLength) + 1u)] = (limit[i] >> 8u);
        buffer[((i * typeLength) + 2u)] = limit[i];
    }
}

//************************** IDENTIFICATION *********************************//

static void getIdentification(uint8_t* buffer, const char* identification)
{
    const uint8_t numberOfLogicalBlocks = 1;
    buffer[0]                           = numberOfLogicalBlocks;

    const uint8_t typeLength = 15;  // Identification is 15 byte string
    memcpy((buffer + 1u), identification, (typeLength * sizeof(char)));
    buffer[(1u + typeLength)] = 0u;
}

static void getIdentificationBackup(uint8_t* buffer, uint8_t startAddress)
{
    const uint8_t numberOfLogicalBlocks = 1;
    buffer[0]                           = numberOfLogicalBlocks;

    const uint8_t typeLength = 15;  // Identification is 15 byte string
    if(eepromIf_read(0u, startAddress, (buffer + 1u), typeLength) != EEPROM_SUCCESS)
    {
        memset((buffer + 1u), 0x00u, (typeLength * sizeof(uint8_t)));
    }
    buffer[(1u + typeLength)] = 0u;
}

static void getIdentificationWithoutBlocks(uint8_t* buffer, char* identification)
{
    const uint8_t typeLength = 15;  // Identification is 15 byte string
    memcpy(buffer, identification, (typeLength * sizeof(char)));
    buffer[typeLength] = 0u;
}

static void getBootSoftwareIdentification(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 17u);
    getIdentification(buffer, (char*)shareData->bootloaderIdentification);
}

// @req CB-74392
// @req CB-74394
static void getLogicalBlockTableIdentification(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 17u);
    getIdentification(buffer, (char*)shareData->bootloaderIdentification);
}

void getApplicationSoftwareIdentification(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 33u);
    const uint8_t numberOfLogicalBlocks = 2;
    buffer[0]                           = numberOfLogicalBlocks;

    const char* identification[2] = { identification_getApplicationSoftwareIdentification(), identification_getApplicationDataIdentification() };
    const uint8_t typeLength      = 15;  // Identification is 15 byte string
    for(uint8_t i = 0; i < numberOfLogicalBlocks; i++)
    {
        memcpy((buffer + 1u + i + (i * typeLength)), identification[i], (typeLength * sizeof(char)));
        buffer[(1u + i + ((i + 1u) * typeLength))] = 0u;
    }
}

static void getBootSoftwareIdentificationBackup(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 17u);
    getIdentificationBackup(buffer, EXT_FLASH_ADDR_BOOTLOADER_IDENTIFICATION_BACKUP_START);
}

static void getLogicalBlockTableIdentificationBackup(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 17u);
    getIdentificationBackup(buffer, EXT_FLASH_ADDR_BOOTLOADER_IDENTIFICATION_BACKUP_START);
}

// @req CB-74392
// @req CB-74394
static void getApplicationSoftwareIdentificationBackup(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 33u);
    const uint8_t numberOfLogicalBlocks = 2;
    buffer[0]                           = numberOfLogicalBlocks;

    uint8_t startAddress[2]  = { EXT_FLASH_ADDR_APPLICATION_SOFTWARE_IDENTIFICATION_BACKUP_START, EXT_FLASH_ADDR_APPLICATION_DATA_IDENTIFICATION_BACKUP_START };
    const uint8_t typeLength = 15;  // Identification is 15 byte string
    for(uint8_t i = 0; i < numberOfLogicalBlocks; i++)
    {
        if(eepromIf_read(0u, startAddress[i], (buffer + 1u + i + (i * typeLength)), typeLength) != EEPROM_SUCCESS)
        {
            memset((buffer + 1u + i + (i * typeLength)), 0x00u, (typeLength * sizeof(uint8_t)));
        }
        buffer[(1u + i + ((i + 1u) * typeLength))] = 0u;
    }
}

void getVehicleManufacturerSparePartNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    getIdentificationWithoutBlocks(buffer, VEHICLE_MANUFACTURER_SPARE_PART_NUMBER);
}

void getVehicleManufacturerEcuHardwareNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = ecuIdentification_getVehicleManufacturerEcuHardwareNumber(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void getSystemNameOrEngineType(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    uint8_t stringLength;
    const char* stringPointer = ecuIdentification_getSystemNameOrEngineType(&stringLength);
    DEBUG_ASSERT(length == stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

// @req CB-91826
static void getTesterSerialNumber(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 44u);
    const char* stringPointer = testerSerialNumber_getTesterSerialNumber();
    uint8_t stringLength      = strlen(stringPointer);
    DEBUG_ASSERT(length >= stringLength);
    memcpy(buffer, stringPointer, stringLength * sizeof(char));
}

static void getEcuInstallationDate(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 3u);
    buffer = bufferMethods_copyValueToBuffer_u8(ecuDateData_getEcuInstallationDateYear(), buffer);
    buffer = bufferMethods_copyValueToBuffer_u8(ecuDateData_getEcuInstallationDateMonth(), buffer);
    bufferMethods_copyValueToBuffer_u8(ecuDateData_getEcuInstallationDateDay(), buffer);
}

// @req CB-74460
// @req CB-74461
// @req CB-74462
// @req CB-74464
// @req CB-74465
// @req CB-74466
// @req CB-74467
static void getDiagnosticVariantId(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 4u);
    buffer = bufferMethods_copyValueToBufferBigEndian_u16(DIAGNOSTIC_VERSION, buffer);
    bufferMethods_copyValueToBufferBigEndian_u16(ECU_VARIANT_ID, buffer);
}

// @req CB-74472
// @req CB-74473
// @req CB-74474
// @req CB-74475
// @req CB-74476
static uint16_t getBrandId(void)
{
    return ecuIdentification_getBrandId();
}

// @req CB-74376
// @req CB-74377
// @req CB-78909
// @req CB-78910
// @req CB-78913
static uint16_t getVehicleManufacturerECUSoftwareNumber(void)
{
    return 0x0100u;  // communicating with application software
}

static uint8_t isECUGateway(void)
{
    return 0x00u;  // ECU has no gateway function
}

static void getSoftwareVersionNumber(uint8_t* buffer, uint16_t length, uint16_t variant)
{
    uint8_t numberOfLogicalBlocks = 1;

    DEBUG_ASSERT((numberOfLogicalBlocks + (numberOfLogicalBlocks * 9u)) == length);

    uint16_t generation  = softwareversion_getMajor_extern();
    uint16_t version     = softwareversion_getMinor_extern();
    uint16_t bugfix      = softwareversion_getPatch_extern();
    uint8_t releaseState = 0x01;

    buffer[0] = numberOfLogicalBlocks;
    for(uint8_t j = 0; j < numberOfLogicalBlocks; j += 9u)
    {
        buffer[(j + 1u)] = (generation >> 8u);
        buffer[(j + 2u)] = generation;
        buffer[(j + 3u)] = (version >> 8u);
        buffer[(j + 4u)] = version;
        buffer[(j + 5u)] = (bugfix >> 8u);
        buffer[(j + 6u)] = bugfix;
        buffer[(j + 7u)] = (variant >> 8u);
        buffer[(j + 8u)] = variant;
        buffer[(j + 9u)] = releaseState;
    }
}

static void getProgrammingDate(uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 3u);
    Fingerprint fingerprint = shareData->logicalBlock[LOGICAL_BLOCK_APPLICATION].fingerprint;
    buffer[0]               = fingerprint.date.year;
    buffer[1]               = fingerprint.date.month;
    buffer[2]               = fingerprint.date.day;
}

static uint8_t getSecurityAccessTest(void)
{
    return securityAccessTest;
}

static uint8_t getLibChargingPreventionExcBassi(void)
{
    return libChargingPreventionExcBassi;
}

// *************************************************************************************************** /
// ************************* UDS Tables ************************************************************** /
// *************************************************************************************************** /

static const DCFunction table_hb_0x20[] = {
    /* {ID, Function Pointer, Return Type, Function Type, P1, P2,securityBitmask} */
    { 13, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 108, 0, 0b0 },
    { 14, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 610, 0, 0b0 },
    { 15, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 610, 0, 0b0 },
    { 16, (void*)readAdcCurrentSensorConfig, DCReturnType_Buffer, DCFunctionType_Var, 38, 0, 0b0 },
    { 46, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 108, 0, 0b0 },
};

static const DCFunction table_hb_0x25[] = {
    /* {ID, Function Pointer, Return Type, Function Type, P1, P2,securityBitmask} */
    { 0, (void*)readHistogramVoltageTemperature, DCReturnType_Buffer, DCFunctionType_Var, 224, 0, 0b0 },
    { 1, (void*)readCurrentTemperatureHistogram_Drive, DCReturnType_Buffer, DCFunctionType_Var, 768, 0, 0b0 },   // @req CB-78658
    { 2, (void*)readCurrentTemperatureHistogram_Charge, DCReturnType_Buffer, DCFunctionType_Var, 768, 0, 0b0 },  // @req CB-78664
    { 3, (void*)readCurrentViolationHistogram_Pulse, DCReturnType_Buffer, DCFunctionType_Var, 72, 0, 0b0 },      // @req CB-78670
    { 4, (void*)readCurrentViolationHistogram_Cont, DCReturnType_Buffer, DCFunctionType_Var, 72, 0, 0b0 },       // @req CB-78680
    { 5, (void*)readBatteryContactorHistogram, DCReturnType_Buffer, DCFunctionType_Var, 192, 0, 0b0 },
    { 6, (void*)readMasterPcbTemperatureHistogram, DCReturnType_Buffer, DCFunctionType_Var, 40, 0, 0b0 },
    { 7, (void*)readSocTemperatureHistogram, DCReturnType_Buffer, DCFunctionType_Var, 224, 0, 0b0 },
    { 8, (void*)readHistogramCurrentViolationLog, DCReturnType_Buffer, DCFunctionType_Var, 40, 0, 0b0 },  // @req CB-89470
    { 9, (void*)readHistogramVoltageContactor, DCReturnType_Buffer, DCFunctionType_Var, 80, 0, 0b0 },     // @req CB-91617
    { 80, (void*)readHistogramCellVoltagesBins, DCReturnType_Buffer, DCFunctionType_Var, 44, 0, 0b0 },    // @req CB-78695
    { 81, (void*)readHistogramVoltageViolationBins, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 82, (void*)readUTBatHistogramTBins, DCReturnType_Buffer, DCFunctionType_Var, 28, 0, 0b0 },  //@req CB-78697
    { 83, (void*)readHistogramVoltageTemperatureVoltageBins, DCReturnType_Buffer, DCFunctionType_Var, 28, 0, 0b0 },
    { 84, (void*)readHistogramTemperatureHistogramBins, DCReturnType_Buffer, DCFunctionType_Var, 32, 0, 0b0 },
    { 85, (void*)readHistogramCurrentTemperatureBins, DCReturnType_Buffer, DCFunctionType_Var, 92, 0, 0b0 },    //@req CB-78700
    { 87, (void*)readHistogramCurrentViolationBins, DCReturnType_Buffer, DCFunctionType_Var, 7, 0, 0b0 },       // @req CB-78701
    { 88, (void*)readHistogramMasterPcbTemperatureBins, DCReturnType_Buffer, DCFunctionType_Var, 18, 0, 0b0 },  // @req CB-78702
    { 89, (void*)readHistogramHeatingCurrentBins, DCReturnType_Buffer, DCFunctionType_Var, 12, 0, 0b0 },        // @req CB-78703
    { 90, (void*)readHistogramSocBins, DCReturnType_Buffer, DCFunctionType_Var, 24, 0, 0b0 },
    { 91, (void*)readHistogramCurrentViolationLogBins, DCReturnType_Buffer, DCFunctionType_Var, 8, 0, 0b0 },  // @req CB-89471
    { 92, (void*)readHistogramVoltageContactorBins, DCReturnType_Buffer, DCFunctionType_Var, 20, 0, 0b0 },    // @req CB-91616
};


static const DCFunction table_hb_0x40[] = {
    /* {ID, Function Pointer, Return Type, Function Type, P1, P2,securityBitmask} */
    { 0, (void*)readLibTotalTime, DCReturnType_Buffer, DCFunctionType_Var, 20, 0, 0b0 },
    { 1, (void*)readLibEventData, DCReturnType_Buffer, DCFunctionType_Var, 38, 0, 0b0 },
    { 2, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 12, 0, 0b0 },
    { 3, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 4, (void*)readDiagnosticEnergyCountData, DCReturnType_Buffer, DCFunctionType_Var, 12, 0, 0b0 },
    { 5, (void*)readLibTemperatureData, DCReturnType_Buffer, DCFunctionType_Var, 22, 0, 0b0 },  // @req CB-92898
    { 6, (void*)readLibVoltageData, DCReturnType_Buffer, DCFunctionType_Var, 20, 0, 0b0 },
    { 7, (void*)readLibCellBalancingCounter, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 8, (void*)periodicWakeUp_getWakeUpCounter, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 9, (void*)getContactorStates, DCReturnType_Buffer, DCFunctionType_Var, 6, 0, 0b0 },  // https://polarion.futavis.de/polarion/#/project/CB_BMS/workitem?id=CB-78600
    { 10, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 10, 0, 0b0 },
    { 11, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 8, 0, 0b0 },
    // @req CB-78589
    { 12, (void*)readLibVoltageMeasurements, DCReturnType_Buffer, DCFunctionType_Var, 12, 0, 0b0 },
    // @req CB-78614
    { 13, (void*)stmFct_getBatteryStateGlobal, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    // @req CB-78582
    { 14, (void*)readLibCurrentMeasurements, DCReturnType_Buffer, DCFunctionType_Var, 8, 0, 0b0 },
    { 15, (void*)afeIf_getNumberOfCsc, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 16, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    // @req CB-78621
    { 17, (void*)stmFct_getWakeUpType, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 18, (void*)hwVersion_getVersion, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 19, (void*)readListOfLastVins, DCReturnType_Buffer, DCFunctionType_Var, 1536, 0, 0b0 },
    { 20, (void*)getSecurityAccessTest, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 21, (void*)getLibChargingPreventionExcBassi, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 22, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 12, 0, 0b0 },
    // @req CB-19032
    // @req CB-10259
    { 24, (void*)readIcdaDiagInfoData, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    // @req CB-19034
    { 25, (void*)readIcdaIdentificationData, DCReturnType_Buffer, DCFunctionType_Var, 38, 0, 0b0 },
    { 32, (void*)readIndividualSnapshotData, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 33, (void*)readAfeCommunicationErrorCounter, DCReturnType_Buffer, DCFunctionType_Var, 28, 0, 0b0 },
    { 34, (void*)readIcdaAfeMeasurementTimeDifference, DCReturnType_Buffer, DCFunctionType_Var, 20, 0, 0b0 },  // @req cB-91528
};


static const DCFunction table_hb_0x42[] = {
    /* {ID, Function Pointer, Return Type, Function Type, P1, P2,securityBitmask} */
    { 0, (void*)readBatteryConfig, DCReturnType_Buffer, DCFunctionType_Var, 5, 0, 0b0 },
    { 1, (void*)readCellConfig, DCReturnType_Buffer, DCFunctionType_Var, 6, 0, 0b0 },
    { 2, (void*)readNtcConfig, DCReturnType_Buffer, DCFunctionType_Var, 5, 0, 0b0 },
    { 3, (void*)readCanBaudrate, DCReturnType_Buffer, DCFunctionType_Var, 2, 0, 0b0 },
    { 4, (void*)readContactorConfiguration, DCReturnType_Buffer, DCFunctionType_Var, 9, 0, 0b0 },  // @req CB-79078
    { 5, (void*)currentSensorIf_getCurrentSensorConfig, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 6, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 8, (void*)readBrandId, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 9, (void*)protocolInterface_getNominalVoltageConfig, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 10, (void*)readComponentsPowerConsumption, DCReturnType_Buffer, DCFunctionType_Var, 6, 0, 0b0 },
    { 12, (void*)readCpsSetting, DCReturnType_Buffer, DCFunctionType_Var, 12, 0, 0b0 },
    { 13, (void*)readStmPushbuttonConfig, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 14, (void*)readSafetyCurrentSensorDirections, DCReturnType_Buffer, DCFunctionType_Var, 2, 0, 0b0 },
    { 32, (void*)readStmTimeoutShutdownConfig, DCReturnType_Buffer, DCFunctionType_Var, 6, 0, 0b0 },
    { 33, (void*)readStmTimeoutOpenContactorsConfig, DCReturnType_Buffer, DCFunctionType_Var, 4, 0, 0b0 },
    { 34, (void*)readStmPwuConfig, DCReturnType_Buffer, DCFunctionType_Var, 12, 0, 0b0 },
    { 35, (void*)readStmEmergencyTimerConfig, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 36, (void*)readStmErrorConfig, DCReturnType_Buffer, DCFunctionType_Var, 4, 0, 0b0 },
    { 37, (void*)readStmNumberOfPdoCountsConfig, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 38, (void*)readStmCpsOutConfig, DCReturnType_Buffer, DCFunctionType_Var, 6, 0, 0b0 },
    { 40, (void*)readPeriodicWakeupConfig, DCReturnType_Buffer, DCFunctionType_Var, 17, 0, 0b0 },
    { 42, (void*)icdaSensor_getIcdConfiguration, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },  // @req CB-19033
    { 44, (void*)readS2PrechargeConfiguration, DCReturnType_Buffer, DCFunctionType_Var, 6, 0, 0b0 },    // @req CB-92395
};

static const DCFunction table_hb_0x49[] = {
    /* {ID, Function Pointer, Return Type, Function Type, P1, P2,securityBitmask} */
    { 3, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 19, (void*)dummy_s32, DCReturnType_INT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 20, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 21, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 43, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 44, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 45, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 46, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 124, (void*)dummy_u64, DCReturnType_UINT64, DCFunctionType_Var, 8, 0, 0b0 },
    { 125, (void*)dummy_u64, DCReturnType_UINT64, DCFunctionType_Var, 8, 0, 0b0 },
    { 126, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 224, 0, 0b0 },
    { 127, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 224, 0, 0b0 },
    { 137, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 138, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 141, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 142, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 143, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 144, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 146, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 112, 0, 0b0 },
    { 147, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 148, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 149, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 150, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 160, (void*)dummy_s16, DCReturnType_INT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 161, (void*)dummy_s16, DCReturnType_INT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 162, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 163, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 164, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 165, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 20, 0, 0b0 },
    { 166, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 20, 0, 0b0 },
    { 167, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 168, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 169, (void*)dummy_s16, DCReturnType_INT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 170, (void*)dummy_s16, DCReturnType_INT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 171, (void*)dummy_s16, DCReturnType_INT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 172, (void*)dummy_s16, DCReturnType_INT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 173, (void*)dummy_s16, DCReturnType_INT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 174, (void*)dummy_s16, DCReturnType_INT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 175, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 176, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 177, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 178, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 179, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 180, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 181, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 182, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 183, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 184, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 192, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 193, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 194, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    // { 195, (void*)dummy_f32, DCReturnType_Float32, DCFunctionType_Var, 4, 0, 0b0 },
    // { 196, (void*)dummy_f32, DCReturnType_Float32, DCFunctionType_Var, 4, 0, 0b0 },
    { 197, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 198, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 199, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 240, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    // { 242, (void*)dummy_f32, DCReturnType_Float32, DCFunctionType_Var, 4, 0, 0b0 },
    // { 243, (void*)dummy_f32, DCReturnType_Float32, DCFunctionType_Var, 4, 0, 0b0 },
    { 244, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 245, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 246, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 247, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 248, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 249, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 250, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 251, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 252, (void*)dummy_u32, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
};

static const DCFunction table_hb_0x50[] = {
    /* {ID, Function Pointer, Return Type, Function Type, P1, P2,securityBitmask} */
    { 16, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 4, 0, 0b0 },
    { 21, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 5, 0, 0b0 },
    { 26, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 27, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 3, 0, 0b0 },
    { 32, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 34, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 35, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 36, (void*)dummy_u16, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
};

static const DCFunction table_hb_0x41[] = {
    /* {ID, Function Pointer, Return Type, Function Type, P1, P2,securityBitmask} */
    { 0, (void*)readLibIdentificationManufacturerName, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 1, (void*)libIdentification_getLibManufacturingDate, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 2, (void*)readLibIdentificationDeviceName, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 3, (void*)readLibIdentificationTrayVariant, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 4, (void*)readLibIdentificationCellTypeName, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 5, (void*)readLibIdentificationKionHardwareNumber, DCReturnType_Buffer, DCFunctionType_Var, 11, 0, 0b0 },
    { 6, (void*)readLibIdentificationKionPartNumber, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 7, (void*)readLibIdentificationKionZsbNumber, DCReturnType_Buffer, DCFunctionType_Var, 11, 0, 0b0 },
    { 8, (void*)readLibIdentificationKionOrderNumber, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 9, (void*)readLibIdentificationKionCustomerOrderNumber, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 10, (void*)readLibIdentificationKionSequenceNumber, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 11, (void*)readLibIdentificationKbsBpn, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 12, (void*)readLibIdentificationKbsSerialNumber, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 13, (void*)readLibIdentificationKbsPartNumber, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },
    { 14, (void*)libIdentification_getLibParameterVersion, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 15, (void*)libIdentification_getLibEolTestResult, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 16, (void*)readLibIdentificationNameplate, DCReturnType_Buffer, DCFunctionType_Var, 34, 0, 0b0 },
    { 18, (void*)readLibIdentificationMasterPcb, DCReturnType_Buffer, DCFunctionType_Var, 61, 0, 0b0 },
    { 19, (void*)libIdentification_getMasterPcbEolTestResult, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 20, (void*)readLibIdentificationCpsPcb, DCReturnType_Buffer, DCFunctionType_Var, 61, 0, 0b0 },
    { 21, (void*)libIdentification_getCpsPcbEolTestResult, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 22, (void*)readListOfConnectedModuleSerialNumbers, DCReturnType_Buffer, DCFunctionType_Var, 512, 0, 0b0 },
    { 23, (void*)readListOfConnectedModulePcbSerialNumbers, DCReturnType_Buffer, DCFunctionType_Var, 512, 0, 0b0 },
};


static const DCFunction table_hb_0x44[] = {
    /* {ID, Function Pointer, Return Type, Function Type, P1, P2,securityBitmask} */
    { 0, (void*)readCanOpenTimeOfDay, DCReturnType_Buffer, DCFunctionType_Var, 6, 0, 0b0 },  // https://polarion.futavis.de/polarion/#/project/WHBMS_BMS_1v0/workitem?id=WHBMS-14748
    { 1, (void*)canData_getLastDateTime, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 2, (void*)canData_getLastLibChargingPower, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 3, (void*)canData_getLastLibChargingVoltage, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 4, (void*)canData_getLastLibChargingCurrent, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 5, (void*)canData_getLastLibPowerConsumptionAverage, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, 0b0 },
    { 6, (void*)readKionTruckOperatingHours, DCReturnType_Buffer, DCFunctionType_Var, 5, 0, 0b0 },
    { 7, (void*)readEmergencyLib, DCReturnType_Buffer, DCFunctionType_Var, 7, 0, 0b0 },
    { 8, (void*)canData_getLastKionCanopenStateLib, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 9, (void*)canData_getLastLibShockWarning, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 10, (void*)canData_getLastLibServiceRequired, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 11, (void*)canData_getLastLibInitComplete, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 12, (void*)canData_getLastLibCurrentLimited, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 14, (void*)canData_getLastLibTemperatureTooLow, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 15, (void*)canData_getLastLibReady, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 16, (void*)canData_getLastLibEmergencyOperation, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 17, (void*)canData_getLastLibTemperatureTooHigh, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 18, (void*)canData_getLastLibError, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 19, (void*)canData_getLastLibInDrivingMode, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 20, (void*)canData_getLastLibFatalError, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 21, (void*)canData_getLastLibInChargingMode, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 23, (void*)canData_getLastLibCurrent, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 24, (void*)canData_getLastLibVoltageInFrontOfContactor, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 25, (void*)canData_getLastLibVoltageAfterContactor, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 26, (void*)canData_getLastLibPower, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 27, (void*)canData_getLastLibStateOfHealth, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 28, (void*)canData_getLastLibMaxDischargingPower2s, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 29, (void*)canData_getLastLibMaxDischargingPower100s, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 30, (void*)canData_getLastLibSocWithSoh, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 31, (void*)canData_getLastLibMinDischargingVoltage, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 32, (void*)canData_getLastLibChargingPower2s, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 33, (void*)canData_getLastLibSocWithoutSoh, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 34, (void*)canData_getLastLibMaxChargingVoltage, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 35, (void*)canData_getLastLibMaxChargingPower100s, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 36, (void*)canData_getLastLibMaxDischargingCurrent2s, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 37, (void*)canData_getLastLibMaxDischargingCurrent100s, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 38, (void*)canData_getLastLibMaxChargingCurrent2s, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 39, (void*)canData_getLastLibMaxChargingCurrent100s, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, 0b0 },
    { 40, (void*)canData_getLastLibPowerpathOk, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    // https://polarion.futavis.de/polarion/#/project/WHBMS_BMS_1v0/workitem?id=WHBMS-14704
    { 64, (void*)getDiagnosticSession, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
    { 64, (void*)dummy_u8, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, 0b0 },
};


// __attribute__((section(".software_id"))) char softwareIdentification[15];
// __attribute__((section(".data_id"))) char dataIdentification[15];
// // extern __attribute__((section(".flash_id"))) volatile char abcdefgh[15];

// void setIdentification(void)
// {
//     for(uint8_t i = 0; i < 15; i++)
//     {
//         if(i != 8u)
//         {
//             softwareIdentification[i] = (uint8_t)IDENTIFICATION[i] - 48u;
//             dataIdentification[i] = (uint8_t)IDENTIFICATION[i] - 48u;
//         }
//         else
//         {
//             softwareIdentification[i] = (uint8_t)IDENTIFICATION[i];
//             dataIdentification[i] = (uint8_t)IDENTIFICATION[i];
//         }
//     }
// }

static const DCFunction table_hb_0x81[] = {
    /* {ID, Function Pointer, Return Type, Function Type, P1, P2,securityBitmask} */
    { 0x00, (void*)readCanSignalBmsReqCPSout, DCReturnType_UINT8, DCFunctionType_Var, 1, 0 },
    { 0x02, (void*)readCanSignalBmsReqPowerDown, DCReturnType_UINT8, DCFunctionType_Var, 1, 0 },
    { 0x04, (void*)readCanSignalBmsReqCPSoutI, DCReturnType_UINT32, DCFunctionType_Var, 4, 0 },
    { 0x05, (void*)readCanSignalBmsReqCPSoutBoostI, DCReturnType_UINT32, DCFunctionType_Var, 4, 0 },
    { 0x06, (void*)readCanSignalBmsInfoBMSState, DCReturnType_UINT8, DCFunctionType_Var, 1, 0 },
    { 0x08, (void*)readCanSignalBmsInfoTimeToWakeUp, DCReturnType_UINT16, DCFunctionType_Var, 2, 0 },
    { 0x09, (void*)readCanSignalDeepDisPossible, DCReturnType_UINT8, DCFunctionType_Var, 1, 0 },
    { 0x0A, (void*)readCanSignalDeepDisImminent, DCReturnType_UINT8, DCFunctionType_Var, 1, 0 },
    { 0x14, (void*)readCanSignalBmsCANopenMs, DCReturnType_UINT32, DCFunctionType_Var, 4, 0 },
    { 0x15, (void*)readCanSignalBmsCANopenDays, DCReturnType_UINT16, DCFunctionType_Var, 2, 0 },
};

// @req CB-75226
// @req CB-75227
static const DCFunction table_hb_0xF1[] = {
    /* {ID, Function Pointer, Return Type, Function Type, P1, P2,securityBitmask} */

    /* manufacturer-specific DIDs: */
    { 0x00, (void*)getDiagnosticVariantId, DCReturnType_Buffer, DCFunctionType_Var, 4, 0, true },
    // https://polarion.futavis.de/polarion/#/project/WHBMS_BMS_1v0/workitem?id=WHBMS-14544
    { 0x01, (void*)getBrandId, DCReturnType_UINT16, DCFunctionType_Var, 2, 0, true },
    { 0x02, (void*)diagnosticTimes_getDiagnosticTotalOperatingTimeIns, DCReturnType_UINT32, DCFunctionType_Var, 4, 0, true },                 // Component Operating Hours
    { 0x03, (void*)getLogicalBlockTableIdentification, DCReturnType_Buffer, DCFunctionType_Var, 17, 0 },                                      // Logical Block Table Identification
    { 0x04, (void*)getLogicalBlockTableFingerprint, DCReturnType_Buffer, DCFunctionType_Var, 49, 0 },                                         // Logical Block Table Fingerprint
    { 0x05, (void*)getBootSoftwareIdentificationBackup, DCReturnType_Buffer, DCFunctionType_Var, 17, 0 },                                     // Boot Software Identification Backup
    { 0x06, (void*)getApplicationSoftwareIdentificationBackup, DCReturnType_Buffer, DCFunctionType_Var, 33, 0 },                              // Application Software Identification Backup + Application Data Identification Backup
    { 0x08, (void*)getLogicalBlockTableIdentificationBackup, DCReturnType_Buffer, DCFunctionType_Var, 17, 0 },                                // Logical Block Table Identification Backup
    { 0x09, (void*)getSoftwareVersionNumber, DCReturnType_Buffer, DCFunctionType_Array1D, 10, 0x0300 },                                       // Boot Software Version Number
    { 0x0A, (void*)getSoftwareVersionNumber, DCReturnType_Buffer, DCFunctionType_Array1D, 10, 0x0301 },                                       // Logical Block Table Version Number
    { 0x0B, (void*)getApplicationSoftwareCounter, DCReturnType_Buffer, DCFunctionType_Var, 5, 0 },                                            // Application Software Programming Counter + Application Data Programming Counter
    { 0x0D, (void*)getLogicalBlockTableCounter, DCReturnType_Buffer, DCFunctionType_Var, 3, 0 },                                              // Logical Block Table Programming Counter
    { 0x0E, (void*)getApplicationSoftwareLimit, DCReturnType_Buffer, DCFunctionType_Var, 5, 0 },                                              // Application Software Programming Limit + Application Data Programming Limit
    { 0x10, (void*)getLogicalBlockTableLimit, DCReturnType_Buffer, DCFunctionType_Var, 3, 0 },                                                // Logical Block Table Programming Limit
    { 0x11, (void*)ecuIdentification_getEcuHardwareVersionNumber, DCReturnType_UINT16, DCFunctionType_Var, 0, 0, true },                      // ECU Hardware Version Number
    { 0x20, (void*)readStandardSnapshotData, DCReturnType_Buffer, DCFunctionType_Var, 12, 0, 0b0 },                                           // Standard Snapshot Data
    { 0x21, (void*)vehicleManufacturerData_getVehicleIdentificationNumberAvailability, DCReturnType_UINT8, DCFunctionType_Var, 1, 0, true },  // Vehicle Identification Number Availability
    { 0x22, (void*)dummy_buffer, DCReturnType_Buffer, DCFunctionType_Var, 6, 0, 0b0 },                                                        // Response Extension List
    { 0x23, (void*)isECUGateway, DCReturnType_UINT8, DCFunctionType_Var, 0, 0, true },                                                        // ECU is Gateway
    { 0x5B, (void*)getHISFingerprint, DCReturnType_Buffer, DCFunctionType_Var, 96, 0 },                                                       // HIS Fingerprint (read)

    /* ISO 14229-1 DIDs */
    { 0x80, (void*)getBootSoftwareIdentification, DCReturnType_Buffer, DCFunctionType_Var, 17, 0 },                 // Boot Software Identification
    { 0x81, (void*)getApplicationSoftwareIdentification, DCReturnType_Buffer, DCFunctionType_Var, 33, 0 },          // Application Software Identification + Application Data Identification
    { 0x83, (void*)getBootSoftwareFingerprint, DCReturnType_Buffer, DCFunctionType_Var, 49, 0 },                    // Boot Software Fingerprint
    { 0x84, (void*)getApplicationSoftwareFingerprint, DCReturnType_Buffer, DCFunctionType_Var, 97, 0 },             // Application Software Fingerprint + Application Data Fingerprint
    { 0x86, (void*)uds_diagnosticSessionControl_getSession, DCReturnType_INT8, DCFunctionType_Var, 0, 0, true },    // Active Diagnostic Session
    { 0x87, (void*)getVehicleManufacturerSparePartNumber, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },    // Vehicle Manufacturer Spare Part Number
    { 0x88, (void*)getVehicleManufacturerECUSoftwareNumber, DCReturnType_UINT16, DCFunctionType_Var, 0, 0, true },  // Vehicle Manufacturer ECU Software Number
    { 0x89, (void*)readManufacturerSoftwareVersion, DCReturnType_Buffer, DCFunctionType_Var, 19, 0 },               // Vehicle Manufacturer ECU Software Version Number
    { 0x8A, (void*)readAlgorithmSoftwareVersion, DCReturnType_Buffer, DCFunctionType_Var, 9, 0 },                   // KBS Algorithm Software Version Number
    { 0x8B, (void*)readEcuManufacturingDate, DCReturnType_Buffer, DCFunctionType_Var, 3, 0, 0b0 },                  // ECU Manufacturing Date
    { 0x8C, (void*)readEcuSerialNumber, DCReturnType_Buffer, DCFunctionType_Var, 16, 0, 0b0 },                      // ECU Serial Number
    { 0x90, (void*)getVehicleIdentificationNumber, DCReturnType_Buffer, DCFunctionType_Var, 16, 0 },                // Vehicle Identification Number
    { 0x91, (void*)getVehicleManufacturerEcuHardwareNumber, DCReturnType_Buffer, DCFunctionType_Var, 16, 0 },       // Vehicle Manufacturer ECU Hardware Number
    { 0x97, (void*)getSystemNameOrEngineType, DCReturnType_Buffer, DCFunctionType_Var, 16, 0 },                     // System Name or Engine Type
    { 0x98, (void*)getTesterSerialNumber, DCReturnType_Buffer, DCFunctionType_Var, 44, 0, 0b0 },                    // Repair Shop Code or Tester Serial Number
    { 0x99, (void*)getProgrammingDate, DCReturnType_Buffer, DCFunctionType_Var, 3, 0, 0b0 },                        // Programming Date
    { 0x9D, (void*)getEcuInstallationDate, DCReturnType_Buffer, DCFunctionType_Var, 3, 0, 0b0 },                    // ECU Installation Date
};

static const DCFunction table_hb_0xFF[] = {
    /* {ID, Function Pointer, Return Type, Function Type, P1, P2,securityBitmask} */
    { 0x00, (void*)uds_getUDSVersion, DCReturnType_UINT32, DCFunctionType_Var, 0, 0, true }
};


const UDSFunctionTable udsFunctionTables[] = {
    { 32, sizeof(table_hb_0x20) / sizeof(DCFunction), table_hb_0x20 },
    { 37, sizeof(table_hb_0x25) / sizeof(DCFunction), table_hb_0x25 },
    { 64, sizeof(table_hb_0x40) / sizeof(DCFunction), table_hb_0x40 },
    { 65, sizeof(table_hb_0x41) / sizeof(DCFunction), table_hb_0x41 },
    { 66, sizeof(table_hb_0x42) / sizeof(DCFunction), table_hb_0x42 },
    { 68, sizeof(table_hb_0x44) / sizeof(DCFunction), table_hb_0x44 },
    { 73, sizeof(table_hb_0x49) / sizeof(DCFunction), table_hb_0x49 },
    { 80, sizeof(table_hb_0x50) / sizeof(DCFunction), table_hb_0x50 },
    { 129, sizeof(table_hb_0x81) / sizeof(DCFunction), table_hb_0x81 },
    { 241, sizeof(table_hb_0xF1) / sizeof(DCFunction), table_hb_0xF1 },
    { 255, sizeof(table_hb_0xFF) / sizeof(DCFunction), table_hb_0xFF },
};

const uint8_t uds_read_highByteCount = sizeof(udsFunctionTables) / sizeof(UDSFunctionTable);
