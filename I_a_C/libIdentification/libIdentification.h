

/**
 * @file libIdentification.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief short description
 * @details
 *  <b>Beschreibung</b>
 *
 * Detaillierte Beschreibung des Moduls
 *
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>

#if defined(UNIT_TEST)
#include "test/bms_config.h"
#else
#include "module_config.h"
#endif

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define LIB_IDENTIFICATION_MANUFACTURER_NAME_STRING_LENGTH            16U
#define LIB_IDENTIFICATION_DEVICE_NAME_STRING_LENGTH                  16U
#define LIB_IDENTIFICATION_TRAY_VARIANT_STRING_LENGTH                 16U
#define LIB_IDENTIFICATION_CELL_TYPE_NAME_STRING_LENGTH               16U
#define LIB_IDENTIFICATION_KION_HW_NUMBER_STRING_LENGTH               11U
#define LIB_IDENTIFICATION_KION_PART_NUMBER_STRING_LENGTH             16U
#define LIB_IDENTIFICATION_KION_ZSB_NUMBER_STRING_LENGTH              11U
#define LIB_IDENTIFICATION_KION_ORDER_NUMBER_STRING_LENGTH            16U
#define LIB_IDENTIFICATION_KION_CUSTOMER_ORDER_NUMBER_STRING_LENGTH   16U
#define LIB_IDENTIFICATION_KION_SEQUENCE_NUMBER_STRING_LENGTH         16U
#define LIB_IDENTIFICATION_KION_BPN_STRING_LENGTH                     16U
#define LIB_IDENTIFICATION_KION_SERIAL_NUMBER_STRING_LENGTH           16U
#define LIB_IDENTIFICATION_KION_PART_NUMBER_STRING_LENGTH             16U
#define LIB_IDENTIFICATION_MASTER_PCB_MANUFACTURER_STRING_LENGTH      9U
#define LIB_IDENTIFICATION_MASTER_PCB_DEVICE_NAME_STRING_LENGTH       16U
#define LIB_IDENTIFICATION_MASTER_PCB_KBS_SERIAL_NUMBER_STRING_LENGTH 16U
#define LIB_IDENTIFICATION_MASTER_PCB_KBS_PART_NUMBER_STRING_LENGTH   16U
#define LIB_IDENTIFICATION_CPS_PCB_MANUFACTURER_STRING_LENGTH         9U
#define LIB_IDENTIFICATION_CPS_PCB_DEVICE_NAME_STRING_LENGTH          16U
#define LIB_IDENTIFICATION_CPS_PCB_KBS_SERIAL_NUMBER_STRING_LENGTH    16U
#define LIB_IDENTIFICATION_CPS_PCB_KBS_PART_NUMBER_STRING_LENGTH      16U
#define LIB_IDENTIFICATION_MODULE_SERIAL_NUMBER_STRING_LENGTH         16U
#define LIB_IDENTIFICATION_MODULE_PCB_SERIAL_NUMBER_STRING_LENGTH     16U
#define LIB_IDENTIFICATION_NUMBERS_OF_VINS_TO_STORE                   128U
#define LIB_IDENTIFICATION_VIN_STRING_LENGTH                          12U

typedef struct
{
    char libManufacturerName[LIB_IDENTIFICATION_MANUFACTURER_NAME_STRING_LENGTH];
    uint32_t libManufacturingDate;
    char libDeviceName[LIB_IDENTIFICATION_DEVICE_NAME_STRING_LENGTH];
    char libTrayVariant[LIB_IDENTIFICATION_TRAY_VARIANT_STRING_LENGTH];
    char libCellTypeName[LIB_IDENTIFICATION_CELL_TYPE_NAME_STRING_LENGTH];
    char libKionHardwareNumber[LIB_IDENTIFICATION_KION_HW_NUMBER_STRING_LENGTH];
    char libKionPartNumber[LIB_IDENTIFICATION_KION_PART_NUMBER_STRING_LENGTH];
    char libKionZsbNumber[LIB_IDENTIFICATION_KION_ZSB_NUMBER_STRING_LENGTH];
    char libKionOrderNumber[LIB_IDENTIFICATION_KION_ORDER_NUMBER_STRING_LENGTH];
    char libKionCustomerOrderNumber[LIB_IDENTIFICATION_KION_CUSTOMER_ORDER_NUMBER_STRING_LENGTH];
    char libKionSequenceNumber[LIB_IDENTIFICATION_KION_SEQUENCE_NUMBER_STRING_LENGTH];
    char libKbsBpn[LIB_IDENTIFICATION_KION_BPN_STRING_LENGTH];
    char libKbsSerialNumber[LIB_IDENTIFICATION_KION_SERIAL_NUMBER_STRING_LENGTH];
    char libKbsPartNumber[LIB_IDENTIFICATION_KION_PART_NUMBER_STRING_LENGTH];
    uint32_t libParameterVersion;
    uint8_t libEolTestResult;
    uint8_t reserve0[37];
    char masterPcbManufacturer[LIB_IDENTIFICATION_MASTER_PCB_MANUFACTURER_STRING_LENGTH];
    uint32_t masterPcbManufacturingDate;
    char masterPcbDeviceName[LIB_IDENTIFICATION_MASTER_PCB_DEVICE_NAME_STRING_LENGTH];
    char masterPcbKbsSerialNumber[LIB_IDENTIFICATION_MASTER_PCB_KBS_SERIAL_NUMBER_STRING_LENGTH];
    char masterPcbKbsPartNumber[LIB_IDENTIFICATION_MASTER_PCB_KBS_PART_NUMBER_STRING_LENGTH];
    uint8_t masterPcbEolTestResult;
    char cpsPcbManufacturer[LIB_IDENTIFICATION_CPS_PCB_MANUFACTURER_STRING_LENGTH];
    uint32_t cpsPcbManufacturingDate;
    char cpsPcbDeviceName[LIB_IDENTIFICATION_CPS_PCB_DEVICE_NAME_STRING_LENGTH];
    char cpsPcbKbsSerialNumber[LIB_IDENTIFICATION_CPS_PCB_KBS_SERIAL_NUMBER_STRING_LENGTH];
    char cpsPcbKbsPartNumber[LIB_IDENTIFICATION_CPS_PCB_KBS_PART_NUMBER_STRING_LENGTH];
    uint8_t cpsPcbEolTestResult;
    char listOfConnectedModuleSerialNumbers[BMS_CONFIG_MAX_NUMBER_OF_SLAVES][LIB_IDENTIFICATION_MODULE_SERIAL_NUMBER_STRING_LENGTH];
    char listOfConnectedModulePcbSerialNumbers[BMS_CONFIG_MAX_NUMBER_OF_SLAVES][LIB_IDENTIFICATION_MODULE_PCB_SERIAL_NUMBER_STRING_LENGTH];
    char listOfConnectedVins[LIB_IDENTIFICATION_NUMBERS_OF_VINS_TO_STORE][LIB_IDENTIFICATION_VIN_STRING_LENGTH];
    uint8_t ringBufferVinsIndex;
    uint8_t reserve1[88];
    uint32_t dummy_reserve_for_crc;
} LibIdentificationNvmData;

typedef struct
{
    uint32_t libNameplateNominalVoltage;
    uint16_t libNameplateNumberOfParallelConnectedCells;
    uint16_t libNameplateNumberOfSerialConnectedCells;
    uint32_t libNameplateMaxChargeCurrent;
    uint32_t libNameplateMaxDischargeCurrent;
    uint32_t libNameplateMaxChargeVoltage;
    uint32_t libNameplateMaxDischargeVoltage;
    uint16_t libNameplateCapacity;
    uint16_t libNameplateCapacityEquivalentLab;
    uint32_t libNameplateEnergyContent;
    uint16_t libNameplateWeight;
} LibIdentificationParameterData;

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

const char* libIdentification_getLibManufacturerName(uint8_t* maxStringLength);
void libIdentification_setLibManufacturerName(const char* newString);

uint32_t libIdentification_getLibManufacturingDate(void);
void libIdentification_setLibManufacturingDate(uint32_t newValue);

const char* libIdentification_getLibDeviceName(uint8_t* maxStringLength);
void libIdentification_setLibDeviceName(const char* newString);

const char* libIdentification_getLibTrayVariant(uint8_t* maxStringLength);
void libIdentification_setLibTrayVariant(const char* newString);

const char* libIdentification_getLibCellTypeName(uint8_t* maxStringLength);
void libIdentification_setLibCellTypeName(const char* newString);

const char* libIdentification_getLibKionHardwareNumber(uint8_t* maxStringLength);
void libIdentification_setLibKionHardwareNumber(const char* newString);

const char* libIdentification_getLibKionPartNumber(uint8_t* maxStringLength);
void libIdentification_setLibKionPartNumber(const char* newString);

const char* libIdentification_getLibKionZsbNumber(uint8_t* maxStringLength);
void libIdentification_setLibKionZsbNumber(const char* newString);

const char* libIdentification_getLibKionOrderNumber(uint8_t* maxStringLength);
void libIdentification_setLibKionOrderNumber(const char* newString);

const char* libIdentification_getLibKionCustomerOrderNumber(uint8_t* maxStringLength);
void libIdentification_setLibKionCustomerOrderNumber(const char* newString);

const char* libIdentification_getLibKionSequenceNumber(uint8_t* maxStringLength);
void libIdentification_setLibKionSequenceNumber(const char* newString);

const char* libIdentification_getLibKbsBpn(uint8_t* maxStringLength);
void libIdentification_setLibKbsBpn(const char* newString);

const char* libIdentification_getLibKbsSerialNumber(uint8_t* maxStringLength);
void libIdentification_setLibKbsSerialNumber(const char* newString);

const char* libIdentification_getLibKbsPartNumber(uint8_t* maxStringLength);
void libIdentification_setLibKbsPartNumber(const char* newString);

uint32_t libIdentification_getLibParameterVersion(void);
void libIdentification_setLibParameterVersion(uint32_t newValue);

uint8_t libIdentification_getLibEolTestResult(void);
void libIdentification_setLibEolTestResult(uint8_t newValue);

uint32_t libIdentification_getLibNameplateNominalVoltage(void);
void libIdentification_setLibNameplateNominalVoltage(uint32_t newValue);

uint16_t libIdentification_getLibNameplateNumberOfParallelConnectedCells(void);
void libIdentification_setLibNameplateNumberOfParallelConnectedCells(uint16_t newValue);

uint16_t libIdentification_getLibNameplateNumberOfSerialConnectedCells(void);
void libIdentification_setLibNameplateNumberOfSerialConnectedCells(uint16_t newValue);

uint32_t libIdentification_getLibNameplateMaxChargeCurrent(void);
void libIdentification_setLibNameplateMaxChargeCurrent(uint32_t newValue);

uint32_t libIdentification_getLibNameplateMaxDischargeCurrent(void);
void libIdentification_setLibNameplateMaxDischargeCurrent(uint32_t newValue);

uint32_t libIdentification_getLibNameplateMaxChargeVoltage(void);
void libIdentification_setLibNameplateMaxChargeVoltage(uint32_t newValue);

uint32_t libIdentification_getLibNameplateMaxDischargeVoltage(void);
void libIdentification_setLibNameplateMaxDischargeVoltage(uint32_t newValue);

uint16_t libIdentification_getLibNameplateCapacity(void);
void libIdentification_setLibNameplateCapacity(uint16_t newValue);

uint16_t libIdentification_getLibNameplateCapacityEquivalentLab(void);
void libIdentification_setLibNameplateCapacityEquivalentLab(uint16_t newValue);

uint32_t libIdentification_getLibNameplateEnergyContent(void);
void libIdentification_setLibNameplateEnergyContent(uint32_t newValue);

uint16_t libIdentification_getLibNameplateWeight(void);
void libIdentification_setLibNameplateWeight(uint16_t newValue);

const char* libIdentification_getMasterPcbManufacturer(uint8_t* maxStringLength);
void libIdentification_setMasterPcbManufacturer(const char* newString);

uint32_t libIdentification_getMasterPcbManufacturingDate(void);
void libIdentification_setMasterPcbManufacturingDate(uint32_t newValue);

const char* libIdentification_getMasterPcbDeviceName(uint8_t* maxStringLength);
void libIdentification_setMasterPcbDeviceName(const char* newString);

const char* libIdentification_getMasterPcbKbsSerialNumber(uint8_t* maxStringLength);
void libIdentification_setMasterPcbKbsSerialNumber(const char* newString);

const char* libIdentification_getMasterPcbKbsPartNumber(uint8_t* maxStringLength);
void libIdentification_setMasterPcbKbsPartNumber(const char* newString);

uint8_t libIdentification_getMasterPcbEolTestResult(void);
void libIdentification_setMasterPcbEolTestResult(uint8_t newValue);

const char* libIdentification_getCpsPcbManufacturer(uint8_t* maxStringLength);
void libIdentification_setCpsPcbManufacturer(const char* newString);

uint32_t libIdentification_getCpsPcbManufacturingDate(void);
void libIdentification_setCpsPcbManufacturingDate(uint32_t newValue);

const char* libIdentification_getCpsPcbDeviceName(uint8_t* maxStringLength);
void libIdentification_setCpsPcbDeviceName(const char* newString);

const char* libIdentification_getCpsPcbKbsSerialNumber(uint8_t* maxStringLength);
void libIdentification_setCpsPcbKbsSerialNumber(const char* newString);

const char* libIdentification_getCpsPcbKbsPartNumber(uint8_t* maxStringLength);
void libIdentification_setCpsPcbKbsPartNumber(const char* newString);

uint8_t libIdentification_getCpsPcbEolTestResult(void);
void libIdentification_setCpsPcbEolTestResult(uint8_t newValue);

const char* libIdentification_getListOfConnectedModuleSerialNumbers(uint8_t cscNumber, uint8_t* maxStringLength);
void libIdentification_setListOfConnectedModuleSerialNumbers(uint8_t cscNumber, const char* newString);

const char* libIdentification_getListOfConnectedModulePcbSerialNumbers(uint8_t cscNumber, uint8_t* maxStringLength);
void libIdentification_setListOfConnectedModulePcbSerialNumbers(uint8_t cscNumber, const char* newString);

const char* libIdentification_getVehicleIdentificationNumber(uint8_t index, uint8_t* maxStringLength);
void libIdentification_insertToRingVehicleIdentificationNumber(const char* newString);
