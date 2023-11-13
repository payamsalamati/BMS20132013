/**
 * @file demUDS_config.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Project specific implementations for demUDS
 * @details
 *  <b>Beschreibung</b>
 *
 *  This module implements project specific functions for demUDS
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "demUDS.h"
#include "demUDS_config.h"
#include "diagnosticTimes.h"
#include "canData.h"
#include "timestamp.h"
#include "task_cfg.h"
#include "kbsIntegration.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


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

void demUDS_saveSnapshotData(DEM_FaultCode externFault, DEM_FaultCode internFault, DTCSnapshot* snapshot)
{
    DTCSnapshotKion* snapshotKion                     = (DTCSnapshotKion*)snapshot;
    snapshotKion->standardSnapshot.truckOperatingTime = canData_getLastTruckOperatingHours();
    snapshotKion->standardSnapshot.totalOperatingTime = diagnosticTimes_getDiagnosticTotalOperatingTimeIns();
    snapshotKion->standardSnapshot.timestamp          = timestamp_getUnixTime();

    if(demUDS_isSaveSnapshotFault(externFault) == true)
    {
        // save individual snapshot of DTCs in KBS monitor
        uint32_t size                 = 0u;
        const uint8_t* snapshotToSave = kbsIntegration_getIndividualSnapshotOfFault(&size, externFault);
        if(size <= DEM_UDS_INDIVIDUAL_SNAPSHOT_SIZE)
        {
            memcpy(&(snapshot->data[DEM_UDS_STANDARD_SNAPSHOT_SIZE]), snapshotToSave, size);
            uint8_t numberUnwrittenValues = (DEM_UDS_INDIVIDUAL_SNAPSHOT_SIZE - size);
            memset(&(snapshot->data[DEM_UDS_STANDARD_SNAPSHOT_SIZE + size]), 0xAA, numberUnwrittenValues);  // fill rest with 0xAA padding
        }
    }
    else
    {
        if((externFault & 0xffffff00) == DTC_AFE_CHECK_SM_FAILED_EXTERNAL)
        {
            snapshotKion->individualSnapshot.sm         = (uint8_t)(internFault & 0x3fu);
            snapshotKion->individualSnapshot.cscAddress = (uint8_t)((internFault & 0xFC0u) >> 6u);
        }
        else if((externFault & 0xffffff00) == DTC_AFE_CHECK_SM_ERROR_DETECTED_EXTERNAL)
        {
            snapshotKion->individualSnapshot.sm         = (uint8_t)((internFault & 0x3f0u) >> 4u);
            snapshotKion->individualSnapshot.cscAddress = (uint8_t)((internFault & 0xfc00) >> 10u);
        }
        else
        {
            snapshotKion->individualSnapshot.sm         = 0xAAu;
            snapshotKion->individualSnapshot.cscAddress = 0xAAu;
        }
        for(uint8_t index = 0u; index < 14u; index++)
        {
            snapshotKion->individualSnapshot.padding[index] = 0xAAu;
        }
    }
}

void demUDS_saveExtendedData(DTCExtendedData* extendedDataBuffer, const DTCSnapshot* snapshot)
{
    DTCExtendedKion* extendedKion       = (DTCExtendedKion*)extendedDataBuffer;
    const DTCSnapshotKion* snapshotKion = (DTCSnapshotKion*)snapshot;
    extendedKion->lastOccurenceTime     = snapshotKion->standardSnapshot.timestamp;
    extendedKion->totalOccurences++;
}

uint16_t demUDS_getSnapshotDataIndividualDataidentifier(DEM_FaultCode fault)
{
    uint16_t dataIdentifier = 0x0000;
    if(((fault & 0xffffff00) == DTC_AFE_CHECK_SM_FAILED_EXTERNAL) || ((fault & 0xffffff00) == DTC_AFE_CHECK_SM_ERROR_DETECTED_EXTERNAL) || demUDS_isSaveSnapshotFault(fault))
    {
        dataIdentifier = 0x4020;
    }
    return dataIdentifier;
}

bool demUDS_isSaveSnapshotFault(DEM_FaultCode fault)
{
    return kbsIntegration_isMonitorDtc(fault);
}
