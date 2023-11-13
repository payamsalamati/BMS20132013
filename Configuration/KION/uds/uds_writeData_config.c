/**
 * @file     uds_writeData_config.c
 * @copyright (c) Futavis GmbH, Aachen 2019 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 * Detaillierte Beschreibung des Moduls
 *
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "uds.h"
#include "uds_config.h"
#include "uds_writeData_config.h"
#include "uds_diagnosticSessionControl_config.h"
#include "uds_protected.h"
#include "uds_writeData/uds_writeData.h"
#include <stddef.h>

#include "debug.h"
#include "linearInterpolation.h"

#include "bms.h"
#include "cell_module.h"
#include "stateFunctions.h"
#include "cps.h"
#include "protocolSelection.h"
#include "kionProtocol.h"
#include "voltageHistogram.h"
#include "voltageViolationHistogram.h"
#include "temperatureHistogram.h"
#include "batteryCurrentTemperatureHistogram.h"
#include "currentViolationHistogram.h"
#include "componentsPowerConsumption.h"
#include "cps_config.h"
#include "libIdentification.h"
#include "vehicleManufacturerData.h"
#include "ecuDateData.h"
#include "afeComProcedure.h"
#include "afe_MC33771_private.h"
#include "afe_MC33771_config.h"
#include "ecuIdentification.h"
#include "cpsMonitor.h"
#include "bufferMethods.h"
#include "periodicWakeUp.h"
#include "task_cfg.h"
#include "kbsIntegration.h"
#include "types.h"
#include "heatingCurrentHistogram.h"
#include "currentViolationLogHistogram.h"
#include "batteryContactorHistogram.h"
#include "socTemperatureHistogram.h"
#include "testerSerialNumber.h"
#include "stmPrecharge.h"
#include "nvm.h"

extern bool currentSensorIf_setCurrentSensorConfig(uint8_t newConfig);

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

/* Cell_&_Sensor_Map_Data */
extern MEM_SEC_PARAMETER uint8_t securityAccessTest;

// *************************************************************************************************** /
// ************************* PRIVATE FUNCTIONS DECLARATION ******************************************* /
// *************************************************************************************************** /

/* LIB_Identification */
static UDS_ErrorCode writeLIB_Manufacturer(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_Manufacturing_Date(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_Device_Name(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_Tray_Variant(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_Cell_Type(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_KION_Hardware_Number(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_KION_Part_Number(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_KION_ZSB_Number(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_KION_Order_Number(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_KION_Customer_Order_Number(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_KION_Sequence_Number(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_KBS_BPN(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_KBS_Serial_Number(const uint8_t* buffer, uint16_t length);  // @req CB-91765
static UDS_ErrorCode writeLIB_KBS_Part_Number(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_Parameter_Version(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_EOL_Test_Result(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_Nameplate(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_Master_PCB_Identification(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_Master_PCB_EOL_Test_Result(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_CPS_PCB_Identification(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeLIB_CPS_PCB_EOL_Test_Result(const uint8_t* buffer, uint16_t length);

static UDS_ErrorCode writeBMS_Brand_ID(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_ECU_Hardware_Version_Number(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_Vehicle_Manufacturer_ECU_Hardware_Number(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_System_Name_or_Engine_Type(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_VIN_Availability(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_ECU_Installation_Date(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_Vehicle_Identification_Number(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_Contactor_Configuration(const uint8_t* buffer, uint16_t length);
#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
static UDS_ErrorCode writeBMS_Heating_Current_Histogram_Bins(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_Current_Violation_Log_Histogram_Bins(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_S2_Precharge_configuration(const uint8_t* buffer, uint16_t length);  // @req CB-92395
static UDS_ErrorCode writeBMS_Voltage_Cell_Histogram_Bins(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_Temperature_Histogram_Bins(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_Current_Histogram_Bins(const uint8_t* buffer, uint16_t length);
static UDS_ErrorCode writeBMS_Current_Violation_Histogram_Bins(const uint8_t* buffer, uint16_t length);
#endif
static bool conditioncheck_vehicle_identification_number(uint16_t id);
static bool conditioncheck_vehicle_identification_number_availability(uint16_t id);
static UDS_ErrorCode write_repair_shop_code_or_tester_serial_number(const uint8_t* buffer, uint16_t length);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

const UDSWriteDataFunctionTableEntry uds_writeDataTable[] = {
    { UDS_DATA_ID_LIB_Manufacturer, 16, writeLIB_Manufacturer, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_Manufacturing_Date, 4, writeLIB_Manufacturing_Date, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_Device_Name, 16, writeLIB_Device_Name, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_Tray_Variant, 16, writeLIB_Tray_Variant, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_Cell_Type, 16, writeLIB_Cell_Type, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_KION_Hardware_Number, 11, writeLIB_KION_Hardware_Number, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_KION_Part_Number, 16, writeLIB_KION_Part_Number, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_KION_ZSB_Number, 11, writeLIB_KION_ZSB_Number, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_KION_Order_Number, 16, writeLIB_KION_Order_Number, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_KION_Customer_Order_Number, 16, writeLIB_KION_Customer_Order_Number, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_KION_Sequence_Number, 16, writeLIB_KION_Sequence_Number, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_KBS_BPN, 16, writeLIB_KBS_BPN, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_KBS_Serial_Number, 16, writeLIB_KBS_Serial_Number, NULL, 0, NULL, NULL },  // @req CB-91765
    { UDS_DATA_ID_LIB_KBS_Part_Number, 16, writeLIB_KBS_Part_Number, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_Parameter_Version, 4, writeLIB_Parameter_Version, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_EOL_Test_Result, 1, writeLIB_EOL_Test_Result, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_Nameplate, 34, writeLIB_Nameplate, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_Master_PCB_Identification, 61, writeLIB_Master_PCB_Identification, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_Master_PCB_EOL_Test_Result, 1, writeLIB_Master_PCB_EOL_Test_Result, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_CPS_PCB_Identification, 61, writeLIB_CPS_PCB_Identification, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_LIB_CPS_PCB_EOL_Test_Result, 1, writeLIB_CPS_PCB_EOL_Test_Result, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_BMS_Brand_ID, 2, writeBMS_Brand_ID, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_BMS_ECU_Hardware_Version_Number, 2, writeBMS_ECU_Hardware_Version_Number, NULL, 0, NULL, NULL },

    { UDS_DATA_ID_BMS_Vehicle_Manufacturer_ECU_Hardware_Number, 16, writeBMS_Vehicle_Manufacturer_ECU_Hardware_Number, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_BMS_System_Name_or_Engine_Type, 16, writeBMS_System_Name_or_Engine_Type, NULL, 0, NULL, NULL },

    { UDS_DATA_ID_BMS_VIN_Availability, 1, writeBMS_VIN_Availability, conditioncheck_vehicle_identification_number_availability, BIT(UDS_SECURITY_ACCESS_LEVEL_2), uds_devSessionList, &UDS_DEVSESSIONLIST_SIZE },                // @req CB-74438 CB-74439
    { UDS_DATA_ID_BMS_Vehicle_Identification_Number, 16, writeBMS_Vehicle_Identification_Number, conditioncheck_vehicle_identification_number, BIT(UDS_SECURITY_ACCESS_LEVEL_2), uds_devSessionList, &UDS_DEVSESSIONLIST_SIZE },  // @req CB-74431 CB-74432
    { UDS_DATA_ID_BMS_ECU_Installation_Date, 3, writeBMS_ECU_Installation_Date, NULL, 0, NULL, NULL },
    { UDS_DATA_ID_Contactor_Configuration, 9, writeBMS_Contactor_Configuration, NULL, 0, NULL, NULL },  // @req CB-79078
#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
    { UDS_DATA_ID_BMS_Heating_Histogram_Bins, 12, writeBMS_Heating_Current_Histogram_Bins, NULL, 0, NULL, NULL },           // @req CB-78703
    { UDS_DATA_ID_BMS_Current_Violation_Log_Bins, 8, writeBMS_Current_Violation_Log_Histogram_Bins, NULL, 0, NULL, NULL },  // @req CB-89471
    { UDS_DATA_ID_S2_Precharge_Configuration, 6, writeBMS_S2_Precharge_configuration, NULL, 0, NULL, NULL },                // @req CB-79078
    { UDS_DATA_ID_U_Cell_Histogram_Bins, 44, writeBMS_Voltage_Cell_Histogram_Bins, NULL, 0, NULL, NULL },                   // @req CB-78695
    { UDS_DATA_ID_T_Histogram_Bins, 32, writeBMS_Temperature_Histogram_Bins, NULL, 0, NULL, NULL },                         // @req CB-78699
    { UDS_DATA_ID_I_Histogram_Bins, 92, writeBMS_Current_Histogram_Bins, NULL, 0, NULL, NULL },                             // @req CB-78700
    { UDS_DATA_ID_I_Violation_Histogram_s_Bins, 7, writeBMS_Current_Violation_Histogram_Bins, NULL, 0, NULL, NULL },
#endif
    { UDS_DATA_ID_repair_shop_code_or_tester_serial_number, 44, write_repair_shop_code_or_tester_serial_number, NULL, 0, NULL, NULL },
};
const uint16_t UDS_WRITE_TABLE_SIZE = (sizeof(uds_writeDataTable) / sizeof(UDSWriteDataFunctionTableEntry));

const UDSWriteDataFunctionTableEntry uds_writeDataTableTest[] = {

};
const uint16_t UDS_WRITE_TABLE_TEST_SIZE = (sizeof(uds_writeDataTableTest) / sizeof(UDSWriteDataFunctionTableEntry));

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


/* LIB_Identification */
static UDS_ErrorCode writeLIB_Manufacturer(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    libIdentification_setLibManufacturerName((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_Manufacturing_Date(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 4u);
    libIdentification_setLibManufacturingDate(bufferMethods_getValueFromBufferBigEndian_u32(&buffer[0]));
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_Device_Name(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    libIdentification_setLibDeviceName((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_Tray_Variant(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    libIdentification_setLibTrayVariant((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_Cell_Type(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    libIdentification_setLibCellTypeName((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_KION_Hardware_Number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 11u);
    libIdentification_setLibKionHardwareNumber((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_KION_Part_Number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    libIdentification_setLibKionPartNumber((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_KION_ZSB_Number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 11u);
    libIdentification_setLibKionZsbNumber((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_KION_Order_Number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    libIdentification_setLibKionOrderNumber((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_KION_Customer_Order_Number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    libIdentification_setLibKionCustomerOrderNumber((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_KION_Sequence_Number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    libIdentification_setLibKionSequenceNumber((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_KBS_BPN(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    libIdentification_setLibKbsBpn((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

// @req CB-91765
static UDS_ErrorCode writeLIB_KBS_Serial_Number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    libIdentification_setLibKbsSerialNumber((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_KBS_Part_Number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    libIdentification_setLibKbsPartNumber((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_Parameter_Version(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 4u);
    libIdentification_setLibParameterVersion(bufferMethods_getValueFromBufferBigEndian_u32(&buffer[0]));
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_EOL_Test_Result(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 1u);
    libIdentification_setLibEolTestResult(buffer[0]);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_Nameplate(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 34u);
    libIdentification_setLibNameplateNominalVoltage(bufferMethods_getValueFromBufferBigEndian_u32(&buffer[0]));
    libIdentification_setLibNameplateNumberOfParallelConnectedCells(bufferMethods_getValueFromBufferBigEndian_u16(&buffer[4]));
    libIdentification_setLibNameplateNumberOfSerialConnectedCells(bufferMethods_getValueFromBufferBigEndian_u16(&buffer[6]));
    libIdentification_setLibNameplateMaxChargeCurrent(bufferMethods_getValueFromBufferBigEndian_u32(&buffer[8]));
    libIdentification_setLibNameplateMaxDischargeCurrent(bufferMethods_getValueFromBufferBigEndian_u32(&buffer[12]));
    libIdentification_setLibNameplateMaxChargeVoltage(bufferMethods_getValueFromBufferBigEndian_u32(&buffer[16]));
    libIdentification_setLibNameplateMaxDischargeVoltage(bufferMethods_getValueFromBufferBigEndian_u32(&buffer[20]));
    libIdentification_setLibNameplateCapacity(bufferMethods_getValueFromBufferBigEndian_u16(&buffer[24]));
    libIdentification_setLibNameplateCapacityEquivalentLab(bufferMethods_getValueFromBufferBigEndian_u16(&buffer[26]));
    libIdentification_setLibNameplateEnergyContent(bufferMethods_getValueFromBufferBigEndian_u32(&buffer[28]));
    libIdentification_setLibNameplateWeight(bufferMethods_getValueFromBufferBigEndian_u16(&buffer[32]));
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_Master_PCB_Identification(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 61u);
    libIdentification_setMasterPcbManufacturer((const char*)&buffer[0]);
    libIdentification_setMasterPcbManufacturingDate(bufferMethods_getValueFromBufferBigEndian_u32(&buffer[9]));
    libIdentification_setMasterPcbDeviceName((const char*)&buffer[13]);
    libIdentification_setMasterPcbKbsSerialNumber((const char*)&buffer[29]);
    libIdentification_setMasterPcbKbsPartNumber((const char*)&buffer[45]);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_Master_PCB_EOL_Test_Result(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 1u);
    libIdentification_setMasterPcbEolTestResult(buffer[0]);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_CPS_PCB_Identification(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 61u);
    libIdentification_setCpsPcbManufacturer((const char*)&buffer[0]);
    libIdentification_setCpsPcbManufacturingDate(bufferMethods_getValueFromBufferBigEndian_u32(&buffer[9]));
    libIdentification_setCpsPcbDeviceName((const char*)&buffer[13]);
    libIdentification_setCpsPcbKbsSerialNumber((const char*)&buffer[29]);
    libIdentification_setCpsPcbKbsPartNumber((const char*)&buffer[45]);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeLIB_CPS_PCB_EOL_Test_Result(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 1u);
    libIdentification_setCpsPcbEolTestResult(buffer[0]);
    return UDS_ERR_CODE_OK;
}

// @req CB-74473
// @req CB-74474
// @req CB-74475
// @req CB-74476
static UDS_ErrorCode writeBMS_Brand_ID(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 2u);
    ecuIdentification_setBrandId(bufferMethods_getValueFromBufferBigEndian_u16(&buffer[0]));
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeBMS_ECU_Hardware_Version_Number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 2u);
    ecuIdentification_setEcuHardwareVersionNumber(bufferMethods_getValueFromBufferBigEndian_u16(&buffer[0]));
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeBMS_Vehicle_Manufacturer_ECU_Hardware_Number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    ecuIdentification_setVehicleManufacturerEcuHardwareNumber((const char*)&buffer[0]);
    return UDS_ERR_CODE_OK;
}

static UDS_ErrorCode writeBMS_System_Name_or_Engine_Type(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    ecuIdentification_setSystemNameOrEngineType((const char*)&buffer[0]);
    return UDS_ERR_CODE_OK;
}


static UDS_ErrorCode writeBMS_VIN_Availability(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 1u);
    bool retVal               = vehicleManufacturerData_setVehicleIdentificationNumberAvailability(buffer[0]);
    UDS_ErrorCode returnValue = UDS_ERR_CODE_OK;
    if(retVal == false)
    {
        returnValue = UDS_ERR_CODE_GENERAL_PROGRAMM_ERR;
    }
    return returnValue;
}

static UDS_ErrorCode writeBMS_ECU_Installation_Date(const uint8_t* buffer, uint16_t length)
{
    UDS_ErrorCode returnValue = UDS_ERR_CODE_OK;
    if((length == 3u) && (ecuDateData_getWriteBlockOnceIndicator() == 0u))
    {
        ecuDateData_setEcuInstallationDateYear(bufferMethods_getValueFromBufferBigEndian_u8(&buffer[0]));
        ecuDateData_setEcuInstallationDateMonth(bufferMethods_getValueFromBufferBigEndian_u8(&buffer[1]));
        ecuDateData_setEcuInstallationDateDay(bufferMethods_getValueFromBufferBigEndian_u8(&buffer[2]));
        nvm_writeBlock(NVM_ECU_DATE_DATA_BLOCK_ID, NULL);
    }
    else
    {
        // https://polarion.futavis.de/polarion/#/project/WHBMS_BMS_1v0/workitem?id=WHBMS-5080
        returnValue = UDS_ERR_CODE_COND_NOT_CORRECT;
    }
    return returnValue;
}

// @req CB-74430
// @req CB-74434
static UDS_ErrorCode writeBMS_Vehicle_Identification_Number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 16u);
    vehicleManufacturerData_setVehicleIdentificationNumber((const char*)buffer);
    return UDS_ERR_CODE_OK;
}

#if defined(SIL_DEBUG) || defined(HIL_CONFIGURATION)
// @req CB-78703
static UDS_ErrorCode writeBMS_Heating_Current_Histogram_Bins(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 12u);
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;
    bool writeSuccess       = true;
    if(length != 12u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else
    {
        uint16_t numberOfBinValues = 0u;
        heatingCurrentHistogram_getHistogramLimits(&numberOfBinValues);
        for(uint16_t index = 0u; index < numberOfBinValues; index++)
        {
            writeSuccess = (writeSuccess == true) ? heatingCurrentHistogram_setHistogramLimits((int32_t)bufferMethods_getValueFromBufferBigEndian_u16(&buffer[index * 2u]), index) : false;
        }
    }
    if(writeSuccess == false)
    {
        errorCode = UDS_ERR_CODE_GENERAL_PROGRAMM_ERR;
    }
    return errorCode;
}

// @req CB-89471
static UDS_ErrorCode writeBMS_Current_Violation_Log_Histogram_Bins(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 8u);
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;
    bool writeSuccess       = true;
    if(length != 8u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else
    {
        uint8_t numberOfBinValues = 0u;
        currentViolationLogHistogram_getHistogramLimits(&numberOfBinValues);
        for(uint8_t index = 0u; index < numberOfBinValues; index++)
        {
            writeSuccess = (writeSuccess == true) ? currentViolationLogHistogram_setHistogramLimits(bufferMethods_getValueFromBufferBigEndian_s32(&buffer[index * 4u]), index) : false;
        }
    }
    if(writeSuccess == false)
    {
        errorCode = UDS_ERR_CODE_GENERAL_PROGRAMM_ERR;
    }
    return errorCode;
}

// @req CB-78695
static UDS_ErrorCode writeBMS_Voltage_Cell_Histogram_Bins(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 44u);
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;
    bool writeSuccess       = true;
    if(length != 44u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else
    {
        uint16_t numberOfBinValues = 0u;
        voltageHistogram_getHistogramLimits(&numberOfBinValues);
        for(uint16_t index = 0u; index < numberOfBinValues; index++)
        {
            writeSuccess = (writeSuccess == true) ? voltageHistogram_setHistogramLimits((int32_t)bufferMethods_getValueFromBufferBigEndian_s32(&buffer[index * 4u]), index) : false;
        }
    }
    if(writeSuccess == false)
    {
        errorCode = UDS_ERR_CODE_GENERAL_PROGRAMM_ERR;
    }
    return errorCode;
}

// @req CB-78699
static UDS_ErrorCode writeBMS_Temperature_Histogram_Bins(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 32u);
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;
    bool writeSuccess       = true;
    if(length != 32u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else
    {
        uint16_t numberOfBinValues = 0u;
        temperatureHistogram_getHistogramLimitsOperation(&numberOfBinValues);
        for(uint16_t index = 0u; index < numberOfBinValues; index++)
        {
            writeSuccess = (writeSuccess == true) ? temperatureHistogram_setHistogramLimits((int32_t)bufferMethods_getValueFromBufferBigEndian_s32(&buffer[index * 4u]), index) : false;
        }
    }
    if(writeSuccess == false)
    {
        errorCode = UDS_ERR_CODE_GENERAL_PROGRAMM_ERR;
    }
    return errorCode;
}

// @req CB-78700
static UDS_ErrorCode writeBMS_Current_Histogram_Bins(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 92u);
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;
    bool writeSuccess       = true;
    if(length != 92u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else
    {
        // batteryCurrentTemperatureHistogram
        uint16_t numberOfBinValues = 0u;
        batteryCurrentTemperatureHistogram_getHistogramLimits(&numberOfBinValues);
        for(uint16_t index = 0u; index < numberOfBinValues; index++)
        {
            writeSuccess = (writeSuccess == true) ? batteryCurrentTemperatureHistogram_setHistogramLimits((int32_t)bufferMethods_getValueFromBufferBigEndian_s32(&buffer[index * 4u]) * 1000, index) : false;
        }
    }
    if(writeSuccess == false)
    {
        errorCode = UDS_ERR_CODE_GENERAL_PROGRAMM_ERR;
    }
    return errorCode;
}

static UDS_ErrorCode writeBMS_Current_Violation_Histogram_Bins(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 7u);
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;
    if(length != 7u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else
    {
        bool writeSuccess = true;
        CurrentViolationConditionParameters parameters;

        parameters.t_regen_limit   = bufferMethods_getValueFromBufferBigEndian_u8(&buffer[0]);
        parameters.t_dch_limit     = bufferMethods_getValueFromBufferBigEndian_u8(&buffer[1]);
        parameters.t_ch_rms_limit  = bufferMethods_getValueFromBufferBigEndian_u16(&buffer[2]);
        parameters.t_dch_rms_limit = bufferMethods_getValueFromBufferBigEndian_u16(&buffer[4]);
        parameters.c_violation     = bufferMethods_getValueFromBufferBigEndian_u8(&buffer[6]);
        writeSuccess               = currentViolationHistogram_setConditionParameters(parameters);
        if(writeSuccess == false)
        {
            errorCode = UDS_ERR_CODE_GENERAL_PROGRAMM_ERR;
        }
    }
    return errorCode;
}

// @req CB-92395
static UDS_ErrorCode writeBMS_S2_Precharge_configuration(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 6u);
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;
    bool writeSuccess       = true;
    if(length != 6u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else
    {
        writeSuccess = stmPrecharge_setS2PrechargeMethod(bufferMethods_getValueFromBufferBigEndian_u8(&buffer[0]));
        writeSuccess = (writeSuccess == true) ? stmPrecharge_setS2VoltageBasedPrechargeCondition(bufferMethods_getValueFromBufferBigEndian_u8(&buffer[1])) : false;
        writeSuccess = (writeSuccess == true) ? stmPrecharge_setS2VoltageBasedPrechargeTimeout(bufferMethods_getValueFromBufferBigEndian_u16(&buffer[2])) : false;
        writeSuccess = (writeSuccess == true) ? stmPrecharge_setS2TimeBasedPrechargeTime(bufferMethods_getValueFromBufferBigEndian_u16(&buffer[4])) : false;
    }
    if(writeSuccess == false)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    return errorCode;
}
#endif

// @req CB-79078
static UDS_ErrorCode writeBMS_Contactor_Configuration(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length == 9u);
    UDS_ErrorCode errorCode = UDS_ERR_CODE_OK;
    bool writeSuccess       = true;
    if(length != 9u)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    else
    {
        /** TODO: configuring of contactor and aux is not possible
         *  only last byte to configure the contactor preference direction is written here
         */
        writeSuccess = stmConfig_setContactorPreferenceDirection(bufferMethods_getValueFromBufferBigEndian_u8(&buffer[8]));
    }

    if(writeSuccess == false)
    {
        errorCode = UDS_ERR_CODE_INCORRECT_MSG_FORMAT;
    }
    return errorCode;
}


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

static bool conditioncheck_vehicle_identification_number(uint16_t id)
{
    return !vehicleManufacturerData_getVinWrittenAlready();
}

static bool conditioncheck_vehicle_identification_number_availability(uint16_t id)
{
    return !vehicleManufacturerData_getVinAvailabilityWrittenAlready();
}

static UDS_ErrorCode write_repair_shop_code_or_tester_serial_number(const uint8_t* buffer, uint16_t length)
{
    DEBUG_ASSERT(length <= 44u);
    UDS_ErrorCode errorCode = (length > 44u) ? UDS_ERR_CODE_INCORRECT_MSG_FORMAT : UDS_ERR_CODE_OK;

    if(errorCode == UDS_ERR_CODE_OK)
    {
        if(strlen((const char*)buffer) <= 44u)
        {
            testerSerialNumber_setTesterSerialNumber((const char*)buffer);
        }
        else
        {
            errorCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
        }
    }
    return errorCode;
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
