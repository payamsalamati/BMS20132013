/**
 * @file     sdo_readTable_KION.c
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

#include <string.h>
#include "sdo.h"

#include "stateFunctions.h"
#include "moduleVoltageMeasurement.h"
#include "stateFunctions.h"
#include "protocolSelection.h"
#include "module_config.h"
#include "csc_config.h"
#include "libIdentification.h"
#include "highVoltageMeasurement.h"
#include "dem.h"
#include "dem_config.h"
#include "softwareversion.h"
#include "softwareversionKion.h"
#include "uds_readTable_KION.h"
#include "debug.h"
#include "sdoData.h"
#include "emcy.h"
#include "ecuIdentification.h"
#include "cellVoltageMeasurement.h"
#include "energyCounter.h"
#include "bufferMethods.h"
#include "diagnosticTimes.h"
#include "energyCounter.h"
#include "vehicleManufacturerData.h"
#include "identification.h"
#include "cps.h"
#include "canOpenStmFct.h"
#include "stringCurrentMeasurement.h"
#include "lindeCAN.h"
#include "kbsIntegration.h"
#include "protocolInterface.h"

static const uint8_t* getLibManufacturer(uint16_t* size);
static const uint8_t* getBatterySerialNumber(uint16_t* size);
static uint32_t getEnergyContent(void);
static uint8_t getKionNominalVoltageAndSwitchToKionProtocol(void);
static uint8_t getNumberOfSlaves(void);
static uint8_t getParallelModules(void);
static uint8_t getSerialModules(void);
static uint8_t getParallelCellsInModule(void);
static uint8_t getSerialCellsInModule(void);
static const uint8_t* getKionZsbNumber(uint16_t* size);
static const uint8_t* getTrayVariant(uint16_t* size);
static uint16_t getDictionaryVersion(void);
static uint32_t getDeviceType(void);
static uint8_t getGenericError(void);
static const uint8_t* getLibIdentificationDeviceName(uint16_t* size);
static const uint8_t* getManufacturerHardwareVersionByString(uint16_t* size);
static const uint8_t* getManufacturerSoftwareVersionByString(uint16_t* size);
static void readVehicleManufacturerSparePartNumber(uint8_t* buffer, uint16_t size);
static void readVehicleManufacturerEcuHardwareNumber(uint8_t* buffer, uint16_t size);
static void readApplicationSoftwareIdentification(uint8_t* buffer, uint16_t size);
static uint8_t getMaxSupportedSubIndexByApplicationSoftwareIdentification(void);
static void getManufacturerSoftwareVersionApplication(uint8_t* buffer, uint16_t size);
static void getManufacturerSoftwareVersionData(uint8_t* buffer, uint16_t size);
static uint8_t getMaxSupportedSubIndexByManufacturerSoftwareVersion(void);
static const uint8_t* getEcuManufacturingDate(uint16_t* size);
static const uint8_t* getVehicleIdentificationNumber(uint16_t* size);
static const uint8_t* getEcuSerialNumber(uint16_t* size);
static uint32_t getCobIdEmcy(void);
static uint16_t getProducerHeartbeatTime(void);
static uint8_t getKeySwitchStatus(void);
static uint8_t getMaxSupportedSubIndexForIdentity(void);
static uint32_t getVendorID(void);
static uint8_t getDiagnosticSession(uint8_t* buffer, uint16_t length);
static uint32_t getColoumbCounterChargePositiveCurrent(void);
static uint32_t getColoumbCounterDischargePositiveCurrent(void);
static uint32_t getColoumbCounterDischarge(void);
static uint8_t getLindeTruckNominalVoltage(void);
static uint8_t getLindeChargerNominalVoltage(void);
static uint8_t getBatteryState(void);
static uint16_t getBatteryVoltage(void);
static uint16_t getMaxChargeCurrent2Linde(void);
static uint16_t getMaxDischargeCurrent2Linde(void);
static uint16_t getMaxChargeCurrent100Linde(void);
static uint16_t getMaxDischargeCurrent100Linde(void);
static uint16_t getMaxDischargePower2Linde(void);
static uint16_t getMaxChargePower2Linde(void);

/**@req WHBMS-3883*/
#define DICTIONARY_VERSION (uint16_t)0x00CA /*Dummy Value*/

#define MAX_ARRAY_LENGTH (uint16_t)16

/**@req WHBMS-3786*/
#define SDO_READ_DEVICE_TYPE (uint32_t)0


/**@req WHBMS-18700*/
#define SDO_VENDOR_ID                (uint32_t)0x12345678 /*Dummy Value: To be defined*/
#define SDO_KION_PROGRAMMING_SESSION 0x02u


// *************************************************************************************************** /
// ************************* SDO Tables ************************************************************** /
// *************************************************************************************************** /

const SDOReadTableEntry sdoReadTableCommon[] = {
    // Index     Subindex  Function     Return Type           Function Type          Param1      Param2
    { 0x4A01, 0x01, (void*)highVoltageMeasurement_getMasterHvVoltagesValue, SDOReturnType_UINT32, SDOFunctionType_Array1D, 2, 0 },
    { 0x4A01, 0x02, (void*)highVoltageMeasurement_getMasterHvVoltagesValue, SDOReturnType_UINT32, SDOFunctionType_Array1D, 1, 0 },
    { 0x4A01, 0x03, (void*)highVoltageMeasurement_getMasterHvVoltagesValue, SDOReturnType_UINT32, SDOFunctionType_Array1D, 0, 0 },
    { 0x1014, 0x00, (void*)getCobIdEmcy, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },                                             // @req CB-72992
    { 0x1017, 0x00, (void*)getProducerHeartbeatTime, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },                                 // @req CB-73016
    { 0x2013, 0x00, (void*)readVehicleManufacturerEcuHardwareNumber, SDOReturnType_Buffer, SDOFunctionType_Var, MAX_ARRAY_LENGTH, 0 },  // @req CB-73096
    { 0x2014, 0x00, (void*)readVehicleManufacturerSparePartNumber, SDOReturnType_Buffer, SDOFunctionType_Var, MAX_ARRAY_LENGTH, 0 },    // @req CB-73106
    { 0x2015, 0x00, (void*)getEcuSerialNumber, SDOReturnType_Pointer, SDOFunctionType_Var, 0, 0 },                                      // @req CB-73115
    { 0x2016, 0x00, (void*)getEcuManufacturingDate, SDOReturnType_Pointer, SDOFunctionType_Var, 0, 0 },                                 // @req CB-73123
    { 0x2017, 0x00, (void*)getVehicleIdentificationNumber, SDOReturnType_Pointer, SDOFunctionType_Var, 0, 0 },                          // @req CB-73131 CB-89688
    { 0x2252, 0x01, (void*)getDiagnosticSession, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },                                      /**@req WHBMS-14746*/
    { 0x2260, 0x01, (void*)diagnosticTimes_getDiagnosticTotalOperatingTimeIns, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },       /**@req WHBMS-14707*/
    { 0x3007, 0x01, (void*)getNumberOfSlaves, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },
    { 0x3007, 0x02, (void*)getParallelModules, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },
    { 0x3007, 0x03, (void*)getSerialModules, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },
    { 0x3007, 0x04, (void*)getParallelCellsInModule, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },
    { 0x3007, 0x05, (void*)getSerialCellsInModule, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },
    { 0x3006, 0x01, (void*)libIdentification_getLibManufacturingDate, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },
    { 0x2246, 0x01, (void*)getTrayVariant, SDOReturnType_Pointer, SDOFunctionType_Var, 0, 0 },
    { 0x3003, 0x01, (void*)getKionZsbNumber, SDOReturnType_Pointer, SDOFunctionType_Var, 0, 0 },
    { 0x3008, 0x01, (void*)libIdentification_getLibNameplateNominalVoltage, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },
    { 0x3008, 0x02, (void*)libIdentification_getLibNameplateNumberOfParallelConnectedCells, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },
    { 0x3008, 0x03, (void*)libIdentification_getLibNameplateNumberOfSerialConnectedCells, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },
    { 0x3008, 0x04, (void*)libIdentification_getLibNameplateMaxChargeCurrent, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },
    { 0x3008, 0x05, (void*)libIdentification_getLibNameplateMaxDischargeCurrent, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },
    { 0x3008, 0x06, (void*)libIdentification_getLibNameplateMaxChargeVoltage, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },
    { 0x3008, 0x07, (void*)libIdentification_getLibNameplateMaxDischargeVoltage, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },
    { 0x3008, 0x08, (void*)libIdentification_getLibNameplateCapacity, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },
    { 0x3008, 0x09, (void*)libIdentification_getLibNameplateCapacityEquivalentLab, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },
    { 0x3008, 0x0A, (void*)libIdentification_getLibNameplateEnergyContent, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },
    { 0x3008, 0x0B, (void*)libIdentification_getLibNameplateWeight, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },
    { 0x1008, 0x00, (void*)getLibIdentificationDeviceName, SDOReturnType_Pointer, SDOFunctionType_Var, 0, 0 },          // @req CB-72959
    { 0x1009, 0x00, (void*)getManufacturerHardwareVersionByString, SDOReturnType_Pointer, SDOFunctionType_Var, 0, 0 },  // @req CB-72968
    // https://polarion.futavis.de/polarion/#/project/WHBMS_BMS_1v0/workitem?id=WHBMS-39661
    { 0x4A02, 0x01, (void*)cellVoltageMeasurement_getMinValue, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },
    // https://polarion.futavis.de/polarion/#/project/WHBMS_BMS_1v0/workitem?id=WHBMS-39662
    { 0x4A02, 0x04, (void*)cellVoltageMeasurement_getMaxValue, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },
    // https://polarion.futavis.de/polarion/#/project/WHBMS_BMS_1v0/workitem?id=WHBMS-39664
    { 0x4A04, 0x01, (void*)getColoumbCounterChargePositiveCurrent, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },
    // https://polarion.futavis.de/polarion/#/project/WHBMS_BMS_1v0/workitem?id=WHBMS-40202
    { 0x4A04, 0x02, (void*)getColoumbCounterDischarge, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },
    // https://polarion.futavis.de/polarion/#/project/WHBMS_BMS_1v0/workitem?id=WHBMS-39665
    { 0x4A04, 0x03, (void*)getColoumbCounterDischargePositiveCurrent, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },
};
const uint16_t SDO_READ_TABLE_COMMON_SIZE = sizeof(sdoReadTableCommon) / sizeof(SDOReadTableEntry);

const SDOReadTableEntry sdoReadTableKion[] = {
    // Index     Subindex  Function     Return Type           Function Type          Param1      Param2
    { 0x1000, 0x00, (void*)getDeviceType, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },                            // @req CB-72927
    { 0x1001, 0x00, (void*)getGenericError, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },                           // @req CB-72934
    { 0x100A, 0x00, (void*)getManufacturerSoftwareVersionByString, SDOReturnType_Pointer, SDOFunctionType_Var, 0, 0 },  // @req CB-72979
    { 0x1018, 0x00, (void*)getMaxSupportedSubIndexForIdentity, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },        // @req CB-73025
    { 0x1018, 0x01, (void*)getVendorID, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },                              /**@req WHBMS-18700*/
    /*--------------------------------------------*/
    { 0x2000, 0x02, (void*)ecuIdentification_getBrandId, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },  // @req CB-73033 CB-73031 CB-73034 CB-73035 CB-73037 CB-73039
    { 0x2000, 0x03, (void*)cps_getCpsOutDeactivationInhibitStatus, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },
    { 0x2000, 0x04, (void*)getDictionaryVersion, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },                                       // @req CB-73043
    { 0x2002, 0x01, (void*)getLibManufacturer, SDOReturnType_Pointer, SDOFunctionType_Var, 0, 0 },                                        // @req CB-75135 CB-74774
    { 0x2010, 0x00, (void*)ecuIdentification_getEcuHardwareVersionNumber, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },              // @req CB-73064 CB-73063 CB-73065 CB-73066 CB-73069
    { 0x2011, 0x00, (void*)getMaxSupportedSubIndexByManufacturerSoftwareVersion, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },        // @req CB-73073
    { 0x2011, 0x01, (void*)getManufacturerSoftwareVersionApplication, SDOReturnType_Buffer, SDOFunctionType_Var, 9, 0 },                  // @req CB-73074
    { 0x2011, 0x02, (void*)getManufacturerSoftwareVersionData, SDOReturnType_Buffer, SDOFunctionType_Var, 9, 0 },                         // @req CB-73074
    { 0x2012, 0x00, (void*)getMaxSupportedSubIndexByApplicationSoftwareIdentification, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },  // @req CB-73084
    { 0x2012, 0x01, (void*)readApplicationSoftwareIdentification, SDOReturnType_Buffer, SDOFunctionType_Var, MAX_ARRAY_LENGTH, 0 },       // @req CB-73085
    { 0x2018, 0x00, (void*)getKeySwitchStatus, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },                                          // @req CB-73142

    { 0x2241, 0x01, (void*)getBatterySerialNumber, SDOReturnType_Pointer, SDOFunctionType_Var, 0, 0 },  // @req CB-75139 CB-74817
    { 0x2243, 0x01, (void*)getEnergyContent, SDOReturnType_UINT32, SDOFunctionType_Var, 0, 0 },         // @req CB-75141 CB-74825
    // @req CB-8473
    { 0x2270, 0x01, (void*)getKionNominalVoltageAndSwitchToKionProtocol, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },  // @req CB-75142 CB-74847
};
const uint16_t SDO_READ_TABLE_KION_SIZE = sizeof(sdoReadTableKion) / sizeof(SDOReadTableEntry);

const SDOReadTableEntry sdoReadTableLindeTruck[] = {
    // Index     Subindex  Function     Return Type           Function Type          Param1      Param2
    { 0x2210, 0x01, (void*)getBatteryState, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },  //@req CB-91771
    { 0x2220, 0x01, (void*)cellVoltageMeasurement_getAverageValue, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },
    { 0x2221, 0x01, (void*)getBatteryVoltage, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },                        //@req CB-91771
    { 0x2222, 0x01, (void*)stringCurrentMeasurement_getValue, SDOReturnType_INT32, SDOFunctionType_Var, 0, 0 },         //@req CB-91772
    { 0x2230, 0x01, (void*)getMaxChargeCurrent2Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },                //@req CB-91774
    { 0x2230, 0x02, (void*)getMaxDischargeCurrent2Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },             //@req CB-91777
    { 0x2231, 0x01, (void*)getMaxChargeCurrent100Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },              //@req CB-91778
    { 0x2231, 0x02, (void*)getMaxDischargeCurrent100Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },           //@req CB-91779
    { 0x2232, 0x01, (void*)getMaxDischargePower2Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },               //@req CB-91776
    { 0x2232, 0x02, (void*)getMaxChargePower2Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },                  //@req CB-91781
    { 0x2234, 0x01, (void*)kbsIntegration_getSocWithSOH_Internal, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },     //@req CB-91785
    { 0x2234, 0x02, (void*)kbsIntegration_getSocWithoutSOH_Internal, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },  //@req CB-91786
    { 0x2270, 0x01, (void*)getLindeTruckNominalVoltage, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },
};
const uint16_t SDO_READ_TABLE_LINDE_TRUCK_SIZE = sizeof(sdoReadTableLindeTruck) / sizeof(SDOReadTableEntry);

const SDOReadTableEntry sdoReadTableLindeCharger[] = {
    // Index     Subindex  Function     Return Type           Function Type          Param1      Param2
    { 0x2210, 0x01, (void*)getBatteryState, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },  //@req CB-91771
    { 0x2220, 0x01, (void*)cellVoltageMeasurement_getAverageValue, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },
    { 0x2221, 0x01, (void*)getBatteryVoltage, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },                        //@req CB-91771
    { 0x2222, 0x01, (void*)stringCurrentMeasurement_getValue, SDOReturnType_INT32, SDOFunctionType_Var, 0, 0 },         //@req CB-91772
    { 0x2230, 0x01, (void*)getMaxChargeCurrent2Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },                //@req CB-91774
    { 0x2230, 0x02, (void*)getMaxDischargeCurrent2Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },             //@req CB-91777
    { 0x2231, 0x01, (void*)getMaxChargeCurrent100Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },              //@req CB-91778
    { 0x2231, 0x02, (void*)getMaxDischargeCurrent100Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },           //@req CB-91779
    { 0x2232, 0x01, (void*)getMaxDischargePower2Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },               //@req CB-91776
    { 0x2232, 0x02, (void*)getMaxChargePower2Linde, SDOReturnType_UINT16, SDOFunctionType_Var, 0, 0 },                  //@req CB-91781
    { 0x2234, 0x01, (void*)kbsIntegration_getSocWithSOH_Internal, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },     //@req CB-91785
    { 0x2234, 0x02, (void*)kbsIntegration_getSocWithoutSOH_Internal, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },  //@req CB-91786
    { 0x2280, 0x01, (void*)getLindeChargerNominalVoltage, SDOReturnType_UINT8, SDOFunctionType_Var, 0, 0 },             // @req CB-89645
};
const uint16_t SDO_READ_TABLE_LINDE_CHARGER_SIZE = sizeof(sdoReadTableLindeCharger) / sizeof(SDOReadTableEntry);

// @req CB-74775 CB-74776 CB-74777
static const uint8_t* getLibManufacturer(uint16_t* size)
{
    uint8_t stringLength  = 0;
    const uint8_t* retVal = (const uint8_t*)libIdentification_getLibManufacturerName(&stringLength);
    *size                 = stringLength;
    return retVal;
}

// @req CB-74818 CB-74819 CB-74820 CB-74822
static const uint8_t* getBatterySerialNumber(uint16_t* size)
{
    uint8_t stringLength  = 0;
    const uint8_t* retVal = (const uint8_t*)libIdentification_getLibKbsSerialNumber(&stringLength);
    *size                 = stringLength;
    return retVal;
}

// @req CB-74826 CB-74827 CB-74828
static uint32_t getEnergyContent(void)
{
    return (uint32_t)libIdentification_getLibNameplateCapacity();
}

// @req CB-74848 CB-74849 CB-74850 CB-74851 CB-74852 CB-74853
static uint8_t getKionNominalVoltageAndSwitchToKionProtocol(void)
{
    protocolSelection_setBrand(Protocol_KION);
    return protocolInterface_getNominalVoltageConfig();
}

static uint8_t getNumberOfSlaves(void)
{
    return BMS_CONFIG_NUMBER_OF_SLAVES;
}

static uint8_t getParallelModules(void)
{
    return CELL_MODULE_CONFIG_STRING_NO_OF_MODULES_PARALLEL;
}

static uint8_t getSerialModules(void)
{
    return CELL_MODULE_CONFIG_STRING_NO_OF_MODULES_SERIAL;
}

static uint8_t getParallelCellsInModule(void)
{
    return CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_PARALLEL;
}

static uint8_t getSerialCellsInModule(void)
{
    return CELL_MODULE_CONFIG_MODULE_NO_OF_CELLS_SERIAL;
}

static const uint8_t* getKionZsbNumber(uint16_t* size)
{
    uint8_t stringLength  = 0;
    const uint8_t* retVal = (const uint8_t*)libIdentification_getLibKionZsbNumber(&stringLength);
    *size                 = stringLength;
    return retVal;
}

static const uint8_t* getTrayVariant(uint16_t* size)
{
    uint8_t stringLength  = 0;
    const uint8_t* retVal = (const uint8_t*)libIdentification_getLibTrayVariant(&stringLength);
    *size                 = stringLength;
    return retVal;
}

// @req CB-73042
// @req CB-73044
// @req CB-73047
// @req CB-73048
// @req CB-73049
static uint16_t getDictionaryVersion(void)
{
    return DICTIONARY_VERSION;
}


// @req CB-72925
// @req CB-72928
// @req CB-72929
// @req CB-72930
static uint32_t getDeviceType(void)
{
    return SDO_READ_DEVICE_TYPE;
}


// @req CB-72932
// @req CB-72935
// @req CB-72936
// @req CB-72937
// @req CB-72939
// @req CB-72940
static uint8_t getGenericError(void)
{
    /* The optional Bits 1 - 7 of the error_register are not supported, and
       are set all the 0.
    */
    return (dem_getSeverityLevelOfSystem() != DEM_SEVERITY_INACTIVE);
}

// @req CB-72956
// @req CB-72960
// @req CB-72961
// @req CB-72962
// @req CB-72964
static const uint8_t* getLibIdentificationDeviceName(uint16_t* size)
{
    uint8_t stringLength;
    const uint8_t* retPtr = (const uint8_t*)ecuIdentification_getSystemNameOrEngineType(&stringLength);
    *size                 = stringLength;
    return retPtr;
}


// @req CB-72966
// @req CB-72969
// @req CB-72970
// @req CB-72971
// @req CB-72972
// @req CB-72973
static const uint8_t* getManufacturerHardwareVersionByString(uint16_t* size)
{
    return (const uint8_t*)ecuIdentification_getEcuHardwareVersionNumberByString(size);
}


// @req CB-72977
// @req CB-72980
// @req CB-72981
// @req CB-72982
// @req CB-72983
// @req CB-72988
static const uint8_t* getManufacturerSoftwareVersionByString(uint16_t* size)
{
    return (const uint8_t*)softwareversionKion_getVersionByString(size);
}

// @req CB-73102
// @req CB-73105
// @req CB-73107
// @req CB-73108
// @req CB-73109
// @req CB-73110
static void readVehicleManufacturerSparePartNumber(uint8_t* buffer, uint16_t size)
{
    DEBUG_ASSERT(size == MAX_ARRAY_LENGTH);
    getVehicleManufacturerSparePartNumber(buffer, MAX_ARRAY_LENGTH);
}

// @req CB-73091
// @req CB-73095
// @req CB-73098
// @req CB-73099
// @req CB-73100
static void readVehicleManufacturerEcuHardwareNumber(uint8_t* buffer, uint16_t size)
{
    DEBUG_ASSERT(size == MAX_ARRAY_LENGTH);
    getVehicleManufacturerEcuHardwareNumber(buffer, MAX_ARRAY_LENGTH);
}

// @req CB-73081
// @req CB-73083
// @req CB-73086
// @req CB-73087
// @req CB-73088
// @req CB-73089
static void readApplicationSoftwareIdentification(uint8_t* buffer, uint16_t size)
{
    DEBUG_ASSERT(size == MAX_ARRAY_LENGTH);
    const uint8_t numberOfLogicalBlocks = 2;
    const char* identification          = identification_getApplicationSoftwareIdentification();
    const uint8_t typeLength            = 15;  // Identification is 15 byte string

    buffer[0] = numberOfLogicalBlocks;
    memcpy((buffer + 1u), &identification[0], (typeLength * sizeof(char)));
}

static uint8_t getMaxSupportedSubIndexByApplicationSoftwareIdentification(void)
{
    /* The maximum supported subindex depends on the amount of individual
       application softwares which are available on the CAN node.
       The default maximum supported subindex is 1
    */
    return 1;
}

// @req CB-73072
// @req CB-73075
// @req CB-73076
// @req CB-73077
// @req CB-73078
static void getManufacturerSoftwareVersionApplication(uint8_t* buffer, uint16_t size)
{
    DEBUG_ASSERT(size == 9u);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(softwareversion_getMajor(), buffer);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(softwareversion_getMinor(), buffer);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(softwareversion_getPatch(), buffer);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(softwareversionKion_getVariant(), buffer);
    bufferMethods_copyValueToBuffer_u8(softwareversionKion_getReleaseStatus(), buffer);
}

static void getManufacturerSoftwareVersionData(uint8_t* buffer, uint16_t size)
{
    DEBUG_ASSERT(size == 9u);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(softwareversionKion_getGenerationParameter(), buffer);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(softwareversionKion_getVersionParameter(), buffer);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(softwareversionKion_getBugfixParameter(), buffer);
    buffer = bufferMethods_copyValueToBufferLittleEndian_u16(softwareversionKion_getVariantParameter(), buffer);
    bufferMethods_copyValueToBuffer_u8(softwareversionKion_getReleaseStatusParameter(), buffer);
}

static uint8_t getMaxSupportedSubIndexByManufacturerSoftwareVersion(void)
{
    /* The default maximum supported subindex is 2 (1. Application + 2. Data) */
    return 0x02u;
}

// @req CB-73121
// @req CB-73122
// @req CB-73124
// @req CB-73125
// @req CB-73126
static const uint8_t* getEcuManufacturingDate(uint16_t* size)
{
    uint8_t dateLength    = 0;
    const uint8_t* retVal = (const uint8_t*)ecuIdentification_getEcuManufacturingDate(&dateLength);
    *size                 = dateLength;
    return retVal;
}

// @req CB-73128
// @req CB-73130
// @req CB-73133
// @req CB-73135
// @req CB-73136
// @req CB-73137
static const uint8_t* getVehicleIdentificationNumber(uint16_t* size)
{
    uint8_t stringLength  = 0;
    const uint8_t* retVal = (const uint8_t*)vehicleManufacturerData_getVehicleIdentificationNumber(&stringLength);
    *size                 = stringLength;
    return retVal;
}

// @req CB-73112
// @req CB-73114
// @req CB-73116
// @req CB-73117
// @req CB-73118
// @req CB-73119
static const uint8_t* getEcuSerialNumber(uint16_t* size)
{
    uint8_t stringLength  = 0;
    const uint8_t* retVal = (const uint8_t*)ecuIdentification_getEcuSerialNumber(&stringLength);
    *size                 = stringLength;
    return retVal;
}

// @req CB-72990
// @req CB-72993
// @req CB-72996
// @req CB-72997
static uint32_t getCobIdEmcy(void)
{
    return emcy_getEmcyCobID();
}

// @req CB-73014
// @req CB-73017
// @req CB-73018
// @req CB-73020
static uint16_t getProducerHeartbeatTime(void)
{
    return 0x028u;
}

// @req CB-73140
// @req CB-73143
// @req CB-73145
// @req CB-73148
// @req CB-73149
// @req CB-73150
static uint8_t getKeySwitchStatus(void)
{
    return sdoData_getKeySwitchStatus();
}


// @req CB-73028
static uint8_t getMaxSupportedSubIndexForIdentity(void)
{
    /* The default maximum supported subindex is 1 */
    return 1;
}

// @req CB-73023
// @req CB-73026
// @req CB-73027
static uint32_t getVendorID(void)
{
    return SDO_VENDOR_ID;
}

/**@req WHBMS-17574*/
static uint8_t getDiagnosticSession(uint8_t* buffer, uint16_t length)
{
    return SDO_KION_PROGRAMMING_SESSION;
}

static uint32_t getColoumbCounterChargePositiveCurrent(void)
{
    const ENERGY_COUNTER_NVM* tmpData = energyCounter_getCoulombCounterData();
    // calculate mWs in 0.001 kWh
    return (uint32_t)(tmpData->diagnosticCoulombCountPositiveCharge / 3600u / 1000u);
}

static uint32_t getColoumbCounterDischargePositiveCurrent(void)
{
    const ENERGY_COUNTER_NVM* tmpData = energyCounter_getCoulombCounterData();
    // calculate mWs in 0.001 kWh
    return (uint32_t)(tmpData->diagnosticCoulombCountPositiveDischarge / 3600u / 1000u);
}

static uint32_t getColoumbCounterDischarge(void)
{
    const ENERGY_COUNTER_NVM* tmpData = energyCounter_getCoulombCounterData();
    // calculate mWs in 0.001 kWh
    return (uint32_t)(tmpData->diagnosticCoulombCountNegativeDischarge / 3600u / 1000u);
}

static uint8_t getLindeTruckNominalVoltage(void)
{
    return protocolInterface_getNominalVoltageConfig();
}

static uint8_t getLindeChargerNominalVoltage(void)
{
    if(canOpenStm_getCanOpenState(&canOpenConfigLinde) == canOpen_State_PreOperational)
    {
        protocolInterface_setConnectedDevice(CHARGER);
        protocolSelection_setBrand(Protocol_LINDE);
    }
    return protocolInterface_getNominalVoltageConfig();
}

static uint8_t getBatteryState(void)
{
    return 0;  //todo
}

static uint16_t getBatteryVoltage(void)
{
    return (highVoltageMeasurement_getMasterHvVoltagesValue(0) * LINDE_LIIOBMS_BATTERYVOLTAGE_FACTOR) - LINDE_LIIOBMS_BATTERYVOLTAGE_OFFSET;
}

static uint16_t getMaxDischargeCurrent2Linde(void)
{
    return (kbsIntegration_getDeratingDischargeLimit() * LINDE_LIIOBMS_MAXDISCHARGECURRENT2_FACTOR) - LINDE_LIIOBMS_MAXDISCHARGECURRENT2_OFFSET;
}

static uint16_t getMaxChargeCurrent2Linde(void)
{
    return (kbsIntegration_getDeratingChargeLimit() * LINDE_LIIOBMS_MAXCHARGECURRENT2_FACTOR) - LINDE_LIIOBMS_MAXCHARGECURRENT2_OFFSET;
}

static uint16_t getMaxDischargeCurrent100Linde(void)
{
    return (kbsIntegration_getDeratingDischargeLimitContinous() * LINDE_LIIOBMS_MAXDISCHARGECURRENT100_FACTOR) - LINDE_LIIOBMS_MAXDISCHARGECURRENT100_OFFSET;
}

static uint16_t getMaxChargeCurrent100Linde(void)
{
    return (kbsIntegration_getDeratingChargeLimitContinous() * LINDE_LIIOBMS_MAXCHARGECURRENT100_FACTOR) - LINDE_LIIOBMS_MAXCHARGECURRENT100_OFFSET;
}

static uint16_t getMaxDischargePower2Linde(void)
{
    return (kbsIntegration_getMaxDischargingPowerPulse() * LINDE_LIIOBMS_MAXDISCHARGEPOWER2_FACTOR) - LINDE_LIIOBMS_MAXDISCHARGEPOWER2_OFFSET;
}

static uint16_t getMaxChargePower2Linde(void)
{
    return (kbsIntegration_getMaxDischargingPowerPulse() * LINDE_LIIOBMS_MAXDISCHARGEPOWER2_FACTOR) - LINDE_LIIOBMS_MAXDISCHARGEPOWER2_OFFSET;
}
