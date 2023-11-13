/**
 * @file currentSensorIf_config.c
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

#include "currentSensorIf.h"
#include "task_cfg.h"
#include <stddef.h>
#include "icdaSensor_config.h"
#include "icdaSensor.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

#define CURRENTSENSORIF_CONFIG_LEM          3u
#define CURRENTSENSORIF_CONFIG_ICDA         5u
#define CURRENTSENSORIF_CONFIG_PARALLEL_LEM 8u
#define CURRENTSENSORIF_CONFIG_SERIAL_LEM   13u

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

extern const CurrentSensorIf icdaCurrentFunction;

// @req CB-10029
MEM_SEC_PARAMETER uint8_t currentSensorConfiguration = CURRENTSENSORIF_CONFIG_ICDA;

MEM_SEC_PARAMETER CurrentSensorContext safetyCurrentSensorCfgSystemTable[] = {
    { &icdaCurrentFunction, 1, CURRENT_SENSOR_TYPE_STRING, true, 0 },
    { 0, 1, CURRENT_SENSOR_TYPE_NO_TYPE, false, 0 },
};
const uint16_t CURRENT_SENSOR_CONFIG_SYSTEMMASTER_TABLE_SIZE = (sizeof(safetyCurrentSensorCfgSystemTable) / sizeof(CurrentSensorContext));

const CurrentSensorContextTable masterCurrentSensorCfgsTable[] = {
    { &safetyCurrentSensorCfgSystemTable[0], (sizeof(safetyCurrentSensorCfgSystemTable) / sizeof(CurrentSensorContext)), 0 },
};

#if !defined(UNIT_TEST)
MEM_SEC_PARAMETER CurrentSensorContext currentSensorConfigSubmaster[] = {};
#else
const CurrentSensorContext currentSensorConfigSubmaster[] = {};
#endif

const uint16_t CURRENT_SENSOR_CONFIG_SUBMASTER_TABLE_SIZE = (sizeof(currentSensorConfigSubmaster) / sizeof(CurrentSensorContext));


const int32_t CURRENT_SENSOR_CALIBRATION_OFFSET_ERROR_LIMIT = 0;


bool currentSensorIf_setCurrentSensorConfig(uint8_t newConfig)
{
    bool retVal = true;
    switch(newConfig)
    {
        case CURRENTSENSORIF_CONFIG_LEM:
            retVal = false;
            break;
        case CURRENTSENSORIF_CONFIG_ICDA:
            icdaSensor_setCurrentSensorConfig(ICDA_CURRENT_SENSOR_ACTIVATED);
            break;
        case CURRENTSENSORIF_CONFIG_PARALLEL_LEM:
            retVal = false;
            break;
        case CURRENTSENSORIF_CONFIG_SERIAL_LEM:
            retVal = false;
            break;
        default:
            retVal = false;
            break;
    }
    return retVal;
}

uint8_t currentSensorIf_getCurrentSensorConfig(void)
{
    uint8_t retVal = 0;
    if(safetyCurrentSensorCfgSystemTable[0].sensorIfFunctions == &icdaCurrentFunction)
    {
        retVal = CURRENTSENSORIF_CONFIG_ICDA;
    }
    return retVal;
}

CurrentSensorContext* currentSensorIf_getSafetyCurrentSensorContext(uint8_t safetyCurrentSensorIndex)
{
    CurrentSensorContext* retVal = NULL;
    if((safetyCurrentSensorIndex <= (uint8_t)(sizeof(safetyCurrentSensorCfgSystemTable) / sizeof(CurrentSensorContext))) && (safetyCurrentSensorIndex > 0u))
    {
        retVal = &safetyCurrentSensorCfgSystemTable[safetyCurrentSensorIndex];
    }
    return retVal;
}

int8_t currentSensorIf_getCurrentDirection(uint8_t safetyCurrentSensorIndex)
{
    int8_t retVal                   = 0;
    const CurrentSensorContext* ptr = currentSensorIf_getSafetyCurrentSensorContext(safetyCurrentSensorIndex);
    if(ptr != NULL)
    {
        retVal = ptr->currentDirection;
    }
    return retVal;
}
