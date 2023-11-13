/**
 * @file     sdo_writeTable_KION.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief UDS Read table  for uds_readTable_SIL,generated via Variants
 * @details
 * Contains the automitacally generated UDS Read Entries for the configured variables of the dataInterface
 * -
 *
 *
 */

// *************************************************************************************************** /
// ************************* Includes **************************************************************** /
// *************************************************************************************************** /


#include <stdbool.h>

#include "sdo.h"

#include "emcy.h"
#include "stateFunctions.h"
#include "module_config.h"
#include "csc_config.h"
#include "protocolSelection.h"
#include "protocolInterface.h"
#include "libIdentification.h"
#include "sdoData.h"
#include "cps.h"
#include "canOpenStmFct.h"

#if CELL_MODULE_CONFIG_DEFAULT_MODULE_NO_OF_CELLS_SERIAL != 7
// cppcheck-suppress preprocessorErrorDirective; The configuration check should not generate an error in cppcheck
//TODO: Anpassung an CB BMS mit 14 Zellen
// #error Nominal module voltage dont match (24 V, 48 V and 80 V are possible in kion protocol)
#endif

static SDOErrorCode writeKionBatteryTurnOn(const uint8_t* data, uint32_t length);
static SDOErrorCode writeKionBatteryTurnOff(const uint8_t* data, uint32_t length);
static SDOErrorCode writeCpsOutDeactivationInhibit(const uint8_t* data, uint32_t length);
static SDOErrorCode writeLindeTruckBatteryTurnOn(const uint8_t* data, uint32_t length);
static SDOErrorCode writeLindeChargerBatteryTurnOn(const uint8_t* data, uint32_t length);
static SDOErrorCode writeLindeBatteryTurnOff(const uint8_t* data, uint32_t length);
static SDOErrorCode writeKionNominalVoltage(const uint8_t* data, uint32_t length);
static SDOErrorCode writeVehicleIdentificationNumber(const uint8_t* data, uint32_t length);
static SDOErrorCode writeEmcyCobId(const uint8_t* data, uint32_t length);
static SDOErrorCode writeKeySwitchStatus(const uint8_t* data, uint32_t length);
static SDOErrorCode writeKionPowerDown(const uint8_t* data, uint32_t length);
static SDOErrorCode writeLindeTruckNominalVoltage(const uint8_t* data, uint32_t length);


// *************************************************************************************************** /
// ************************* SDO Tables ************************************************************** /
// *************************************************************************************************** /

const SDOWriteTableEntry sdoWriteTableCommon[] = {
    // Index     Subindex  Length    Function
};
const uint16_t SDO_WRITE_TABLE_COMMON_SIZE = sizeof(sdoWriteTableCommon) / sizeof(SDOWriteTableEntry);

const SDOWriteTableEntry sdoWriteTableKion[] = {
    // Index     Subindex  Length    Function
    { 0x1014, 0x00, 4, writeEmcyCobId },           // @req CB-72992
    { 0x2200, 0x01, 1, writeKionBatteryTurnOn },   // @req CB-75137 CB-74801
    { 0x2200, 0x02, 1, writeKionBatteryTurnOff },  // @req CB-75138 CB-74809
    { 0x2200, 0x03, 1, writeCpsOutDeactivationInhibit },
    { 0x2200, 0x04, 1, writeKionPowerDown },  // @ req CB-89866
    { 0x2270, 0x01, 1, writeKionNominalVoltage },
    { 0x2271, 0x01, 12, writeVehicleIdentificationNumber },  // @req CB-75143 CB-74856
    { 0x2018, 0x00, 1, writeKeySwitchStatus },               // @req CB-73142
};
const uint16_t SDO_WRITE_TABLE_KION_SIZE = sizeof(sdoWriteTableKion) / sizeof(SDOWriteTableEntry);

const SDOWriteTableEntry sdoWriteTableLindeTruck[] = {
    // Index     Subindex  Length    Function
    { 0x2270, 0x01, 1, writeLindeTruckNominalVoltage },  // @req CB-89643
    { 0x2200, 0x01, 1, writeLindeTruckBatteryTurnOn },   //@req CB-89833
    { 0x2200, 0x02, 1, writeLindeBatteryTurnOff },       //@req CB-89836
};
const uint16_t SDO_WRITE_TABLE_LINDE_TRUCK_SIZE = sizeof(sdoWriteTableLindeTruck) / sizeof(SDOWriteTableEntry);

const SDOWriteTableEntry sdoWriteTableLindeCharger[] = {
    // Index     Subindex  Length    Function
    { 0x2200, 0x01, 1, writeLindeChargerBatteryTurnOn },  //@req CB-89833
    { 0x2200, 0x02, 1, writeLindeBatteryTurnOff },        //@req CB-89836
};
const uint16_t SDO_WRITE_TABLE_LINDE_CHARGER_SIZE = sizeof(sdoWriteTableLindeCharger) / sizeof(SDOWriteTableEntry);


// @req CB-72996
static SDOErrorCode writeEmcyCobId(const uint8_t* data, uint32_t length)
{
    SDOErrorCode retVal = SDO_ERR_CODE_OK;
    if((protocolSelection_getBrand() == Protocol_KION) && (data[0] == (0x80u + CANOPEN_NODE_ID_KION))
       && (data[1] == 0x00u) && (data[2] == 0x00u))
    {
        switch(data[3])
        {
            case 0x00:
                emcy_enable(true);
                break;
            case 0x80:
                emcy_enable(false);
                break;
            default:
                retVal = SDO_ERR_CODE_VALUE;
                break;
        }
    }
    else
    {
        retVal = SDO_ERR_CODE_VALUE;
    }
    return retVal;
}

// @req CB-74802 CB-74803 CB-74804 CB-74805
static SDOErrorCode writeKionBatteryTurnOn(const uint8_t* data, uint32_t length)
{
    SDOErrorCode retVal = SDO_ERR_CODE_OK;
    if(protocolSelection_getBrand() == Protocol_KION)
    {
        switch(*data)
        {
            case 0x01:
                protocolInterface_setCloseContactorsDriveMode(true);
                break;
            case 0x02:
                protocolInterface_setCloseContactorsChargeMode(true);
                break;
            default:
                retVal = SDO_ERR_CODE_VALUE;  //invalid Data
                break;
        }
    }
    else
    {
        retVal = SDO_ERR_CODE_OBJECT_ACCESS_RESTRICTED;
    }
    return retVal;
}

static SDOErrorCode writeLindeTruckBatteryTurnOn(const uint8_t* data, uint32_t length)
{
    SDOErrorCode retVal = SDO_ERR_CODE_OK;
    if(protocolSelection_getBrand() == Protocol_LINDE)
    {
        if(*data == 0x01 && protocolInterface_getConnectedDevice() == TRUCK)
        {
            protocolInterface_setCloseContactorsDriveMode(true);
        }
        else
        {
            retVal = SDO_ERR_CODE_VALUE;  //invalid Data
        }
    }
    else
    {
        retVal = SDO_ERR_CODE_OBJECT_ACCESS_RESTRICTED;
    }
    return retVal;
}

static SDOErrorCode writeLindeChargerBatteryTurnOn(const uint8_t* data, uint32_t length)
{
    SDOErrorCode retVal = SDO_ERR_CODE_OK;
    if(protocolSelection_getBrand() == Protocol_LINDE)
    {
        if(*data == 0x02 && protocolInterface_getConnectedDevice() == CHARGER)
        {
            protocolInterface_setCloseContactorsDriveMode(true);
        }
        else
        {
            retVal = SDO_ERR_CODE_VALUE;  //invalid Data
        }
    }
    else
    {
        retVal = SDO_ERR_CODE_OBJECT_ACCESS_RESTRICTED;
    }
    return retVal;
}

// @req CB-74810 CB-74811 CB-74812 CB-74813 CB-74814
static SDOErrorCode writeKionBatteryTurnOff(const uint8_t* data, uint32_t length)
{
    SDOErrorCode retVal = SDO_ERR_CODE_OK;
    if(protocolSelection_getBrand() == Protocol_KION)
    {
        switch(*data)
        {
            case 0x01:
                protocolInterface_setOpenContactors(true);
                break;
            default:
                retVal = SDO_ERR_CODE_VALUE;  //invalid Data
                break;
        }
    }
    else
    {
        retVal = SDO_ERR_CODE_OBJECT_ACCESS_RESTRICTED;
    }
    return retVal;
}

// @req CB-90328 CB-90329
static SDOErrorCode writeCpsOutDeactivationInhibit(const uint8_t* data, uint32_t length)
{
    SDOErrorCode retVal = SDO_ERR_CODE_OK;
    if(protocolSelection_getBrand() == Protocol_KION)
    {
        switch(*data)
        {
            case 0x00:
                cps_setCpsOutDeactivationInhibitStatus(false);
                break;
            case 0x01:
                cps_setCpsOutDeactivationInhibitStatus(true);
                break;
            default:
                retVal = SDO_ERR_CODE_VALUE;  //invalid Data
                break;
        }
    }
    else
    {
        retVal = SDO_ERR_CODE_OBJECT_ACCESS_RESTRICTED;
    }
    return retVal;
}


static SDOErrorCode writeLindeBatteryTurnOff(const uint8_t* data, uint32_t length)
{
    SDOErrorCode retVal = SDO_ERR_CODE_OK;
    if(protocolSelection_getBrand() == Protocol_LINDE)
    {
        switch(*data)
        {
            case 0x01:
                protocolInterface_setOpenContactors(true);
                break;
            default:
                retVal = SDO_ERR_CODE_VALUE;  //invalid Data
                break;
        }
    }
    else
    {
        retVal = SDO_ERR_CODE_OBJECT_ACCESS_RESTRICTED;
    }
    return retVal;
}

static SDOErrorCode writeKionNominalVoltage(const uint8_t* data, uint32_t length)
{
    SDOErrorCode retVal = SDO_ERR_CODE_VALUE;
    if(*data == protocolInterface_getNominalVoltageConfig())
    {
        protocolSelection_setBrand(Protocol_KION);
        retVal = SDO_ERR_CODE_OK;
    }
    return retVal;
}

// @req CB-74857 CB-74858 CB-74859 CB-74860
static SDOErrorCode writeVehicleIdentificationNumber(const uint8_t* data, uint32_t length)
{
    const char* pointer;
    pointer = (const char*)data;
    libIdentification_insertToRingVehicleIdentificationNumber(pointer);
    return SDO_ERR_CODE_OK;
}

// @req CB-73145
// @req CB-73151
static SDOErrorCode writeKeySwitchStatus(const uint8_t* data, uint32_t length)
{
    return (sdoData_setKeySwitchStatus(*data) == true) ? SDO_ERR_CODE_OK : SDO_ERR_CODE_VALUE;
}

static SDOErrorCode writeKionPowerDown(const uint8_t* data, uint32_t length)
{
    SDOErrorCode retVal = SDO_ERR_CODE_OK;

    switch(*data)
    {
        case 0x01:
            cps_setCpsPowerDownRegularShutdown();
            break;
        default:
            retVal = SDO_ERR_CODE_VALUE;
            break;
    }

    return retVal;
}

static SDOErrorCode writeLindeTruckNominalVoltage(const uint8_t* data, uint32_t length)
{
    SDOErrorCode retVal = SDO_ERR_CODE_VALUE;
    if(*data == protocolInterface_getNominalVoltageConfig())
    {
        protocolInterface_setConnectedDevice(TRUCK);
        protocolSelection_setBrand(Protocol_LINDE);
        retVal = SDO_ERR_CODE_OK;
    }
    return retVal;
}
