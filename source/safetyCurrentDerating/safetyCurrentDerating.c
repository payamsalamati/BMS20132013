/**
 * @file currentDerating.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "safetyCurrentDerating.h"
#include "safetyCurrentDerating_config.h"

#include "linearInterpolation.h"
#include "cellVoltageMeasurement.h"
#include "cellTemperatureMeasurement.h"
#include "errorDetection.h"
#include "currentSensorIf.h"
#include "fut_math.h"
#include "batteryCurrentMeasurement.h"

#include "task_cfg.h"
#if !defined(UNIT_TEST)
#include "csc_config.h"
#include "module_config.h"
#include "bms_config.h"
#include "monitoring_config.h"
#else
#include "safetyCurrentDerating/test/test_safetyCurrentDerating.h"
#endif
#include "debug.h"
#include "dem_config.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

typedef struct
{
    int32_t dischargeCont;
    int32_t dischargePeak;
    int32_t chargeCont;
    int32_t chargePeak;
} SafetyCurrentDerating;

typedef struct
{
    ErrorType type;
    const CharacteristicDiagram* table;
    const uint32_t* detectionTime;
    uint16_t voltage;
    int32_t* limit;
    Error* error;
    DTC dtc;
} SafetyCurrentDeratingEntry;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//

static int32_t calculateLimit(const SafetyCurrentDeratingEntry* entry, int16_t minTemperature, int16_t maxTemperature);
static void checkLimit(SafetyCurrentDeratingEntry* entry, int32_t current, int32_t limit, Error* error);
static uint32_t getSensorFactor(void);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

extern const CharacteristicDiagram currentDerating_characteristicDiagramI_ch_cont_safety;
MEM_SEC_PARAMETER uint32_t CURRENT_DERATING_CHG_MAX_CONT_SAFETY_TIME = CURRENT_DERATING_CHG_MAX_CONT_SAFETY_TIME_DEFAULT;
MEM_SEC_PARAMETER uint32_t CURRENT_DERATING_CHG_MAX_CONT_WARN_TIME   = CURRENT_DERATING_CHG_MAX_CONT_WARN_TIME_DEFAULT;

extern const CharacteristicDiagram currentDerating_characteristicDiagramI_ch_peak_safety;
MEM_SEC_PARAMETER uint32_t CURRENT_DERATING_CHG_MAX_PEAK_SAFETY_TIME = CURRENT_DERATING_CHG_MAX_PEAK_SAFETY_TIME_DEFAULT;
MEM_SEC_PARAMETER uint32_t CURRENT_DERATING_CHG_MAX_PEAK_WARN_TIME   = CURRENT_DERATING_CHG_MAX_PEAK_WARN_TIME_DEFAULT;

extern const CharacteristicDiagram currentDerating_characteristicDiagramI_dch_cont_safety;
MEM_SEC_PARAMETER uint32_t CURRENT_DERATING_DSG_MAX_CONT_SAFETY_TIME = CURRENT_DERATING_DSG_MAX_CONT_SAFETY_TIME_DEFAULT;
MEM_SEC_PARAMETER uint32_t CURRENT_DERATING_DSG_MAX_CONT_WARN_TIME   = CURRENT_DERATING_DSG_MAX_CONT_WARN_TIME_DEFAULT;

extern const CharacteristicDiagram currentDerating_characteristicDiagramI_dch_peak_safety;
MEM_SEC_PARAMETER uint32_t CURRENT_DERATING_DSG_MAX_PEAK_SAFETY_TIME = CURRENT_DERATING_DSG_MAX_PEAK_SAFETY_TIME_DEFAULT;
MEM_SEC_PARAMETER uint32_t CURRENT_DERATING_DSG_MAX_PEAK_WARN_TIME   = CURRENT_DERATING_DSG_MAX_PEAK_WARN_TIME_DEFAULT;

MEM_SAFETY static Error safetyCurrentDeratingError[8u][BMS_CONFIG_MAX_NUMBER_OF_CURRENT_SENSORS] = { 0 };

MEM_SAFETY static SafetyCurrentDerating safetyCurrentDerating = { 0 };

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


static int32_t calculateLimit(const SafetyCurrentDeratingEntry* entry, int16_t minTemperature, int16_t maxTemperature)
{
    int32_t minTemp = linearInterpolation_interpolateCharacteristicDiagram(entry->voltage, minTemperature, entry->table);
    int32_t maxTemp = linearInterpolation_interpolateCharacteristicDiagram(entry->voltage, maxTemperature, entry->table);
    return min2_abs(minTemp, maxTemp);
}

static void checkLimit(SafetyCurrentDeratingEntry* entry, int32_t current, int32_t limit, Error* error)
{
    // @req CB-15655 CB-15660
    const uint32_t zero      = 0;
    const ErrorConfig config = {
        .type           = entry->type,
        .detectionValue = &limit,
        .detectionTime  = entry->detectionTime,
        .releaseValue   = &limit,
        .releaseTime    = &zero,
    };
    error->faultCode = entry->dtc;
    error->config    = &config;
    errorDetection(error, current, MONITORING_CYCLE_TIME);
}

static uint32_t getSensorFactor(void)
{
    return CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_PARALLEL * CELL_MODULE_CONFIG_STRING_NO_OF_MODULES_PARALLEL;
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

// @req CB-75603
void safetyCurrentDerating_mainFunction(void)
{

    uint16_t minVoltage = cellVoltageMeasurement_getMinValue();
    uint16_t maxVoltage = cellVoltageMeasurement_getMaxValue();

    int16_t minTemperature = cellTemperatureMeasurement_getMinValue();
    int16_t maxTemperature = cellTemperatureMeasurement_getMaxValue();


    // clang-format off
     // Polarion Requirement BMS-5938
    // @req CB-77022 CB-77023 CB-77024 CB-77025 CB-77026 CB-77027 CB-77028 CB-77029 CB-75602
    SafetyCurrentDeratingEntry table[] = {
        { ErrorType_Max, &currentDerating_characteristicDiagramI_ch_cont_safety, &CURRENT_DERATING_CHG_MAX_CONT_SAFETY_TIME, maxVoltage, 
            &safetyCurrentDerating.chargeCont, &safetyCurrentDeratingError[0][0], DTC_CURRENT_CONT_CHARGE_THRESHOLD_2},

        { ErrorType_Max, &currentDerating_characteristicDiagramI_ch_cont_safety, &CURRENT_DERATING_CHG_MAX_CONT_WARN_TIME, maxVoltage, 
            &safetyCurrentDerating.chargeCont, &safetyCurrentDeratingError[1][0], DTC_CURRENT_CONT_CHARGE_THRESHOLD_1},

        { ErrorType_Max, &currentDerating_characteristicDiagramI_ch_peak_safety, &CURRENT_DERATING_CHG_MAX_PEAK_SAFETY_TIME, maxVoltage, 
            &safetyCurrentDerating.chargePeak, &safetyCurrentDeratingError[2][0], DTC_CURRENT_PEAK_CHARGE_THRESHOLD_2},

        { ErrorType_Max, &currentDerating_characteristicDiagramI_ch_peak_safety, &CURRENT_DERATING_CHG_MAX_PEAK_WARN_TIME, maxVoltage, 
            &safetyCurrentDerating.chargePeak, &safetyCurrentDeratingError[3][0], DTC_CURRENT_PEAK_CHARGE_THRESHOLD_1},

        { ErrorType_Min, &currentDerating_characteristicDiagramI_dch_cont_safety, &CURRENT_DERATING_DSG_MAX_CONT_SAFETY_TIME, minVoltage, 
            &safetyCurrentDerating.dischargeCont, &safetyCurrentDeratingError[4][0], DTC_CURRENT_CONT_DISCHARGE_THRESHOLD_2},

        { ErrorType_Min, &currentDerating_characteristicDiagramI_dch_cont_safety, &CURRENT_DERATING_DSG_MAX_CONT_WARN_TIME, minVoltage, 
            &safetyCurrentDerating.dischargeCont, &safetyCurrentDeratingError[5][0], DTC_CURRENT_CONT_DISCHARGE_THRESHOLD_1},

        { ErrorType_Min, &currentDerating_characteristicDiagramI_dch_peak_safety, &CURRENT_DERATING_DSG_MAX_PEAK_SAFETY_TIME, minVoltage, 
            &safetyCurrentDerating.dischargePeak, &safetyCurrentDeratingError[6][0], DTC_CURRENT_PEAK_DISCHARGE_THRESHOLD_2},

        { ErrorType_Min, &currentDerating_characteristicDiagramI_dch_peak_safety, &CURRENT_DERATING_DSG_MAX_PEAK_WARN_TIME, minVoltage, 
            &safetyCurrentDerating.dischargePeak, &safetyCurrentDeratingError[7][0], DTC_CURRENT_PEAK_DISCHARGE_THRESHOLD_1},
    };
    // clang-format on

    for(uint8_t i = 0; i < sizeof(table) / sizeof(SafetyCurrentDeratingEntry); i++)
    {
        SafetyCurrentDeratingEntry* entry = &table[i];
        *(entry->limit)                   = calculateLimit(entry, minTemperature, maxTemperature);
        // table contains the last allowed values
        // errorDetection module checks for equality
        // increase/decrease by one, so that for edge cases the correct value will be checked
        if(entry->type == ErrorType_Max)
        {
            *(entry->limit) += 1;
        }
        else
        {
            *(entry->limit) -= 1;
        }
        // @req CB-15654
        int32_t current   = batteryCurrentMeasurement_getValue();
        uint32_t factor   = getSensorFactor();
        int32_t tempLimit = *(entry->limit) * factor;
        checkLimit(entry, current, tempLimit, &entry->error[0u]);
    }
}


#if defined(UNIT_TEST)
void safetyCurrentDerating_reset(void)
{
    memset(&safetyCurrentDerating, 0, sizeof(SafetyCurrentDerating));
    memset(safetyCurrentDeratingError, 0, sizeof(safetyCurrentDeratingError));
}
#endif
