/**
 * @file terminalTemperatureMeasurement.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "terminalTemperatureMeasurement.h"
#include "temperatureMeasurement_config.h"
#include "fut_math.h"
#include "task_cfg.h"
#include "validation.h"
#include "safetyAfeValueMeasurement.h"
#include "debug.h"
#include "afeCheck.h"
#include "dem.h"

#if defined(UNIT_TEST)
#include "cell_module.h"
#include "test/bms_config.h"
#else
#include "module_config.h"
#endif

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    int16_t values[BMS_CONFIG_MAX_NUMBER_OF_SLAVES][BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS];
    uint8_t validateCounter[BMS_CONFIG_MAX_NUMBER_OF_SLAVES][BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS];
    MaxMin_s16_2DArray maxMin;
    MaxMin_s16 maxMinCsc[BMS_CONFIG_MAX_NUMBER_OF_SLAVES];
    int16_t average;
} TerminalTemperatureMeasurement;

MEM_SEC_PARAMETER static TerminalTempenSorConfig terminalTempSensorConfig = {
    .minusTerminal = TERMINAL_TEMP_SENSOR_1,
    .plusTerminal  = TERMINAL_TEMP_SENSOR_2,
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static void copyTerminalTemperaturesFromSafetyLayer(void);
static void calculateMasterTerminalTemperatureMaxMin(void);
static void calculateMasterTerminalTemperatureAverage(void);
static void calculateMasterTerminalTemperatureMaxMinCSC(void);
#if BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS > 0u
static bool isSMTerminalTemperatureRelevant(uint8_t sm);
static void loadMaskedValues(void);
#endif

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

#define TERMINAL_TEMPERATURE_ERROR (INT16_MAX - 1)

MEM_MEASUREMENTS static TerminalTemperatureMeasurement terminalTemperatureMeasurement;
MEM_MEASUREMENTS int16_t maskedTerminalTemperatureValues[BMS_CONFIG_MAX_NUMBER_OF_SLAVES][BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS];
MEM_SEC_PARAMETER AfeCheckSmIdentifier terminalTemperatureRelevantSMList[] = {
    SM05,
    SM06,
    SM07,
    SM08,
    SM09,
    SM10,
    SM11,
    SM12,
    SM13,
    SM15,
    SM18,
    SM21,
    SM23,
    SM24,
    SM25,
    SM31,
    SM33
};
const uint16_t terminalTemperatureRelevantSMListSize = (sizeof(terminalTemperatureRelevantSMList) / sizeof(DEM_FaultCode));

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static void copyTerminalTemperaturesFromSafetyLayer(void)
{
#if BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS > 0u
    const ValidationStaticConfig_s32 validateTemperatureConfig = {
        .maxValue     = TEMPERATURE_MEASUREMENT_VALID_MAX,
        .minValue     = TEMPERATURE_MEASUREMENT_VALID_MIN,
        .counterLimit = TEMPERATURE_MEASUREMENT_VALID_COUNTER
    };

    for(uint8_t slave = 0; slave < BMS_CONFIG_NUMBER_OF_SLAVES; slave++)
    {
        for(uint8_t tempSensor = 0; tempSensor < BMS_CONFIG_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS; tempSensor++)
        {
            terminalTemperatureMeasurement.values[slave][tempSensor] = validation_staticBorders_s32(
                safetyAfeValueMeasurement_getApplicationTemperaturesValue(slave, tempSensor),
                &validateTemperatureConfig,
                &terminalTemperatureMeasurement.validateCounter[slave][tempSensor],
                terminalTemperatureMeasurement.values[slave][tempSensor]);
        }
    }
#endif
}

static void calculateMasterTerminalTemperatureMaxMin(void)
{
    terminalTemperatureMeasurement.maxMin = maxMin_s16_2DArray((int16_t*)terminalTemperatureMeasurement.values,
                                                               BMS_CONFIG_NUMBER_OF_SLAVES,
                                                               BMS_CONFIG_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS,
                                                               BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS);
}

static void calculateMasterTerminalTemperatureAverage(void)
{
    terminalTemperatureMeasurement.average = average_s16_2DArray((int16_t*)terminalTemperatureMeasurement.values,
                                                                 BMS_CONFIG_NUMBER_OF_SLAVES,
                                                                 BMS_CONFIG_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS,
                                                                 BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS);
}

static void calculateMasterTerminalTemperatureMaxMinCSC(void)
{
    for(uint16_t cscAddress = 1; cscAddress <= BMS_CONFIG_NUMBER_OF_SLAVES; cscAddress++)
    {
        int16_t* ptr                                                       = &terminalTemperatureMeasurement.values[cscAddress - (uint16_t)1][0];
        terminalTemperatureMeasurement.maxMinCsc[cscAddress - (uint16_t)1] = maxMin_s16(ptr, BMS_CONFIG_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS);
    }
}

#if BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS > 0u
static bool isSMTerminalTemperatureRelevant(uint8_t sm)
{
    bool retVal = false;
    for(uint16_t index = 0u; ((index < terminalTemperatureRelevantSMListSize) && (retVal == false)); index++)
    {
        retVal = (terminalTemperatureRelevantSMList[index] == sm);
    }
    return retVal;
}

static void loadMaskedValues(void)
{
    uint8_t demFaultListSize      = 0u;
    const DEM_Fault* demFaultList = dem_getFaultInfo(&demFaultListSize);
    memcpy(&maskedTerminalTemperatureValues[0][0], &terminalTemperatureMeasurement.values[0][0], (sizeof(int16_t) * BMS_CONFIG_MAX_NUMBER_OF_SLAVES * BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS));

    for(uint8_t index = 0u; ((index < demFaultListSize) && (index < DEM_FAULT_CODES_MAX)); index++)
    {
        DEM_FaultCode currentFaultCode = demFaultList[index].fault;
        if((currentFaultCode == DTC_AFE_INIT_ERROR)
           || (currentFaultCode == DTC_AFE_COMM_ERROR))
        {
            for(uint16_t row = 0u; row < BMS_CONFIG_MAX_NUMBER_OF_SLAVES; row++)
            {
                for(uint16_t column = 0u; column < BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS; column++)
                {
                    maskedTerminalTemperatureValues[row][column] = TERMINAL_TEMPERATURE_ERROR;
                }
            }
            break;
        }
        else if((DEM_FaultCode)(currentFaultCode & 0xffff0000) == DTC_AFE_CHECK_SM_ERROR_DETECTED)
        {
            uint8_t cscAddress = (uint8_t)((uint32_t)(currentFaultCode >> 10u) & (uint8_t)0x3f) - 1u;
            uint8_t faultSM    = (uint8_t)((uint32_t)(currentFaultCode >> 4u) & (uint8_t)0x3f);
            uint8_t cell       = (uint8_t)((uint8_t)(currentFaultCode & 0xf) - 1u);
            if(isSMTerminalTemperatureRelevant(faultSM) == true
               && (cscAddress < BMS_CONFIG_NUMBER_OF_SLAVES)
               && (cell < BMS_CONFIG_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS))
            {
                maskedTerminalTemperatureValues[cscAddress][cell] = TERMINAL_TEMPERATURE_ERROR;
            }
        }
        else
        {
            // do nothing
        }
    }
}
#endif

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void terminalTemperatureMeasurement_mainFunction(void)
{
    copyTerminalTemperaturesFromSafetyLayer();
    calculateMasterTerminalTemperatureMaxMin();
    calculateMasterTerminalTemperatureAverage();
    calculateMasterTerminalTemperatureMaxMinCSC();
#if BMS_CONFIG_MAX_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS > 0u
    loadMaskedValues();
#endif
}

int16_t terminalTemperatureMeasurement_getValue(uint16_t i, uint16_t j)
{
    DEBUG_API_CHECK(i < BMS_CONFIG_NUMBER_OF_SLAVES);
    DEBUG_API_CHECK(j < BMS_CONFIG_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS);
    return ((i < BMS_CONFIG_NUMBER_OF_SLAVES) && (j < BMS_CONFIG_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS)) ? terminalTemperatureMeasurement.values[i][j] : 0;
}

int16_t terminalTemperatureMeasurement_getMinValue(void)
{
    return terminalTemperatureMeasurement.maxMin.min;
}

int16_t terminalTemperatureMeasurement_getMaxValue(void)
{
    return terminalTemperatureMeasurement.maxMin.max;
}

uint8_t terminalTemperatureMeasurement_getTemperatureSensorAddressOfMax(void)
{
    return terminalTemperatureMeasurement.maxMin.maxIndex1;
}

uint8_t terminalTemperatureMeasurement_getTemperatureSensorAddressOfMin(void)
{
    return terminalTemperatureMeasurement.maxMin.minIndex1;
}

uint8_t terminalTemperatureMeasurement_getMaxNumber(void)
{
    return terminalTemperatureMeasurement.maxMin.maxIndex2;
}

uint8_t terminalTemperatureMeasurement_getMinNumber(void)
{
    return terminalTemperatureMeasurement.maxMin.minIndex2;
}

int16_t terminalTemperatureMeasurement_getAverageValue(void)
{
    return terminalTemperatureMeasurement.average;
}

int16_t terminalTemperatureMeasurement_getMaxValueCSC(uint16_t cscAddress)
{
    return terminalTemperatureMeasurement.maxMinCsc[cscAddress - (uint16_t)1].max;
}

int16_t terminalTemperatureMeasurement_getMinValueCSC(uint16_t cscAddress)
{
    return terminalTemperatureMeasurement.maxMinCsc[cscAddress - (uint16_t)1].min;
}

int16_t terminalTemperatureMeasurement_getPlusTerminalTemperature(uint16_t cscAddress)
{
    return terminalTemperatureMeasurement.values[cscAddress][terminalTempSensorConfig.plusTerminal];
}

int16_t terminalTemperatureMeasurement_getMinusTerminalTemperature(uint16_t cscAddress)
{
    return terminalTemperatureMeasurement.values[cscAddress][terminalTempSensorConfig.minusTerminal];
}

const int16_t* terminalTemperatureMeasurement_getTerminalTemperatures(uint16_t cscAddress)
{
    return &terminalTemperatureMeasurement.values[cscAddress][0];
}

void terminalTemperatureMeasurement_setMinusTerminal(TERMINAL_TEMP_SENSOR sensor)
{
    terminalTempSensorConfig.minusTerminal = sensor;
}

void terminalTemperatureMeasurement_setPlusTerminal(TERMINAL_TEMP_SENSOR sensor)
{
    terminalTempSensorConfig.plusTerminal = sensor;
}

TERMINAL_TEMP_SENSOR terminalTemperatureMeasurement_getMinusTerminal(void)
{
    return terminalTempSensorConfig.minusTerminal;
}

TERMINAL_TEMP_SENSOR terminalTemperatureMeasurement_getPlusTerminal(void)
{
    return terminalTempSensorConfig.plusTerminal;
}

int16_t terminalTemperatureMeasurement_getMaskedValue(uint16_t cscAddress, uint16_t sensor)
{
    int16_t retVal = INT16_MAX;
    if((cscAddress < BMS_CONFIG_NUMBER_OF_SLAVES) && (sensor < BMS_CONFIG_NUMBER_OF_APPLICATION_TEMPERATURE_SENSORS))
    {
        retVal = maskedTerminalTemperatureValues[cscAddress][sensor];
    }
    return retVal;
}
