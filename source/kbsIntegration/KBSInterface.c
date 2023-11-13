/**
 * @file KBSInterface.c
 * @copyright (c) Futavis GmbH, Aachen 2022 - all rights reserved
 * @brief Interface between KBS algorithms and Futavis code. Functions are called by Futavis and implemented by KBS.
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "KBSInterface.h"

#include "osIf.h"
#include "uds_protected.h"
#include "sdo.h"
#include "task_cfg.h"
#include <string.h>

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

#define NVM_SIZE               1000u
#define KBS_SDO_TEST_DATA_SIZE 20
#define KBS_UDS_TEST_DATA_SIZE 20

uint8_t kbs_data[NVM_SIZE];
volatile MEM_SEC_PARAMETER_KBS uint8_t kbs_parameter[NVM_SIZE];
uint8_t kbs_nvm_data_bms[NVM_SIZE]                = { 0 };
uint8_t kbs_nvm_data_csc[NVM_SIZE]                = { 0 };
uint8_t kbs_sdo_test_data[KBS_SDO_TEST_DATA_SIZE] = { 0 };
uint8_t kbs_uds_test_data[KBS_UDS_TEST_DATA_SIZE] = { 0 };
uint16_t mismatch                                 = 0;

eventMonitor test_monitor                    = { 0 };
const uint8_t individualSnapshotTestData[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

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
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

void KBSInterface_initialize_ASW(void)
{
}

void KBSInterface_initialize_NVM_BMS(const uint8_t* in_NVM_BMS, uint32_t size_NVM_BMS)
{
    memcpy(kbs_nvm_data_bms, in_NVM_BMS, NVM_SIZE);
}

void KBSInterface_initialize_NVM_CSC(const uint8_t* in_NVM_CSC, uint32_t size_NVM_CSC)
{
    memcpy(kbs_nvm_data_csc, in_NVM_CSC, NVM_SIZE);
}

void KBSInterface_update_NVM(uint32_t size_NVM_BMS, uint32_t size_NVM_CSC, uint8_t* out_NVM_BMS, uint8_t* out_NVM_CSC)
{
    memcpy(out_NVM_BMS, &kbs_nvm_data_bms[0], size_NVM_BMS);
    memcpy(out_NVM_CSC, &kbs_nvm_data_csc[0], size_NVM_CSC);
}

void KBSInterface_main_10ms(const KBSInput* input, KBSOutput* output, eventMonitor* monitor)
{
    kbs_data[0] = kbs_parameter[0];
    for(uint16_t i = 0; i < NVM_SIZE; i++)
    {
        kbs_data[i] = i + 1;
    }
}

void KBSInterface_main_100ms(const KBSInput* input, KBSOutput* output, eventMonitor* monitor)
{
    output->SOCwithSOH                     = 498;
    output->SOCwithoutSOH                  = 598;
    output->maxChargePower_Continuous      = 1200;
    output->maxDischargePower_Continuous   = 1300;
    output->maxChargePower_Pulse           = 1400;
    output->maxDischargePower_Pulse        = 1500;
    output->maxChargeCurrent_Pulse         = 1600;
    output->maxChargeCurrent_Continuous    = 1700;
    output->maxDischargeCurrent_Pulse      = 1800;
    output->maxDischargeCurrent_Continuous = 2000;
    output->currentLimited                 = ENUM_CURRENTLIMITED_SIGNAL_ERROR;

    memcpy(monitor, &test_monitor, sizeof(eventMonitor));

    for(uint16_t i = 0; i < NVM_SIZE; i++)
    {
        kbs_data[i] = (i + 1) * 10u;
    }
}

void KBSInterface_main_1000ms(const KBSInput* input, KBSOutput* output, eventMonitor* monitor)
{
    for(uint16_t i = 0; i < NVM_SIZE; i++)
    {
        kbs_data[i] = (i + 1) * 100u;
    }
}

void KBSInterface_terminate(uint32_t size_NVM_BMS, uint32_t size_NVM_CSC, uint8_t* out_NVM_BMS, uint8_t* out_NVM_CSC)
{
    memcpy(out_NVM_BMS, &kbs_nvm_data_bms[0], size_NVM_BMS);
    memcpy(out_NVM_CSC, &kbs_nvm_data_csc[0], size_NVM_CSC);
}

void KBSInterface_UDS_routineControl(ENUM_ROUTINE_CONTROL_TYPE type, uint16_t id, const uint8_t* option, uint8_t optionSize, uint16_t maxBufferSize, uint8_t* responseBuffer, uint16_t* responseBufferSize, uint8_t* responseCode)
{
    *responseCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    if((id == 0x1001)
       || (id == 0xfded))
    {
        if(type == ENUM_ROUTINE_CONTROL_TYPE_START_ROUTINE)
        {
            responseBuffer[0]   = 0xab;
            responseBuffer[1]   = 0xcd;
            *responseBufferSize = 2;
            *responseCode       = UDS_ERR_CODE_OK;
        }
        else if(type == ENUM_ROUTINE_CONTROL_TYPE_STOP_ROUTINE)
        {
            *responseCode = UDS_ERR_CODE_SUB_FUNCTION_NOT_SUPPORTED;
        }
        else if(type == ENUM_ROUTINE_CONTROL_TYPE_REQUEST_RESULTS)
        {
        }
        else
        {
        }
    }
}

void KBSInterface_UDS_readData(uint16_t id, uint16_t maxBufferSize, uint8_t* responseBuffer, uint16_t* responseBufferSize, uint8_t* responseCode)
{
    if((id == 0x820e)
       || (id == 0xFD0e))
    {
        responseBuffer[0]   = 0x01;
        responseBuffer[1]   = 0x02;
        *responseBufferSize = 2;
        *responseCode       = UDS_ERR_CODE_OK;
    }
    else if(id == 0x8555)
    {
        memcpy(responseBuffer, &kbs_uds_test_data[0], KBS_UDS_TEST_DATA_SIZE);
        *responseBufferSize = KBS_UDS_TEST_DATA_SIZE;
        *responseCode       = SDO_ERR_CODE_OK;
    }
    else if(id == 0x8888)  // to test bms and csc write functions
    {
        // only first 300 bytes are sent back to save time
        memcpy(&responseBuffer[0], &kbs_nvm_data_bms[0], 300);
        memcpy(&responseBuffer[300], &kbs_nvm_data_csc[0], 300);
        *responseBufferSize = 600;
        *responseCode       = UDS_ERR_CODE_OK;
    }
    else
    {
        *responseCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
}

void KBSInterface_UDS_writeData(uint16_t id, const uint8_t* requestBuffer, const uint16_t* requestBufferSize, uint8_t* responseCode)
{
    if(id == 0x8555)
    {
        memcpy(&kbs_uds_test_data[0], requestBuffer, requestBufferSize[0]);
        *responseCode = UDS_ERR_CODE_OK;
    }
    else if(id == 0x8666)  // to set a diagnostic event inside of test_monitor
    {
        uint8_t eventMonitorID                                        = (requestBuffer[0] - 1u);
        diagnosticEvent* diagnosticEventPtr                           = &test_monitor.diagnosticEvent_1;
        diagnosticEventPtr[eventMonitorID].identifier_diagnosticEvent = 12u;
        diagnosticEventPtr[eventMonitorID].status_diagnosticEvent     = ENUM_DIAGNOSTIC_EVENT_FAILED;
        diagnosticEventPtr[eventMonitorID].data_individualSnapshot    = &individualSnapshotTestData[0];
        diagnosticEventPtr[eventMonitorID].size_individualSnapshot    = 16u;
    }
    else if(id == 0x8777)  // to clear all diagnostic events inside of test_monitor
    {
        memset(&test_monitor, 0, sizeof(eventMonitor));
    }
    else if(id == 0x8888)  // to test bms and csc write functions
    {
        // set only first 300 bytes to test values because all of the data would take too long
        memset(&kbs_nvm_data_bms[0], 0xde, 300);
        memset(&kbs_nvm_data_csc[0], 0xbe, 300);
    }
    else
    {
        *responseCode = UDS_ERR_CODE_REQUEST_OUT_OF_RANGE;
    }
}

void KBSInterface_CANopen_readData(uint16_t index, uint8_t subIndex, uint16_t maxBufferSize, uint8_t* responseBuffer, uint16_t* responseBufferSize, uint32_t* abortCode)
{
    if(((index == 0x4801) && (subIndex == 0x01))      // for tests of SDO reads in range (KBS_INTERFACE_SDO_START - KBS_INTERFACE_SDO_END)
       || ((index == 0x4209) && (subIndex == 0x01)))  // for tests of SDO reads in KBS_INTERFACE_SDO_2
    {
        memcpy(responseBuffer, &kbs_sdo_test_data[0], 4);
        *responseBufferSize = 4;
        *abortCode          = 0;
    }
    else if((index == 0x4802) && (subIndex == 0x02))  // for SDO read testcase with > 4 byte data
    {
        memcpy(responseBuffer, &kbs_sdo_test_data[0], KBS_SDO_TEST_DATA_SIZE);
        *responseBufferSize = KBS_SDO_TEST_DATA_SIZE;
        *abortCode          = SDO_ERR_CODE_OK;
    }
    else
    {
        *abortCode = SDO_ERR_CODE_OBJECT_UNKNOWN;
    }
}

void KBSInterface_CANopen_writeData(uint16_t index, uint8_t subIndex, const uint8_t* requestBuffer, const uint16_t* requestBufferSize, uint32_t* abortCode)
{
    if(((index == 0x4801) && (subIndex == 0x01))      // for tests of SDO reads in range (KBS_INTERFACE_SDO_START - KBS_INTERFACE_SDO_END)
       || ((index == 0x4209) && (subIndex == 0x01))   // for tests of SDO reads in KBS_INTERFACE_SDO_2
       || ((index == 0x4802) && (subIndex == 0x02)))  // for SDO read testcase with > 4 byte data
    {
        memcpy(&kbs_sdo_test_data[0], requestBuffer, requestBufferSize[0]);
        *abortCode = SDO_ERR_CODE_OK;
    }
    else
    {
        *abortCode = SDO_ERR_CODE_OBJECT_UNKNOWN;
    }
}
