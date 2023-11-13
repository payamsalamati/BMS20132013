/**
 * @file demUDS_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


#pragma once
//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

typedef struct DTCExtendedKion
{
    uint32_t firstOccurrence;
    uint32_t lastOccurenceTime;
    uint32_t totalOccurences;
} DTCExtendedKion;

typedef struct DEMIndividualSnapshot
{
    uint8_t sm;
    uint8_t cscAddress;
    uint8_t padding[14];
} DEMIndividualSnapshot;

typedef struct DTCStandardSnapshotKion
{
    uint32_t truckOperatingTime;
    uint32_t totalOperatingTime;
    uint32_t timestamp;
} DTCStandardSnapshotKion;

typedef struct DTCSnapshotKion
{
    DTCStandardSnapshotKion standardSnapshot;
    DEMIndividualSnapshot individualSnapshot;
} DTCSnapshotKion;

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define DEM_UDS_SNAPSHOT_SIZE            28u
#define DEM_UDS_STANDARD_SNAPSHOT_SIZE   12u
#define DEM_UDS_INDIVIDUAL_SNAPSHOT_SIZE 16u
#define DEM_UDS_EXTENDED_SIZE            12u

#define DEM_UDS_SEMAPHORE_TIMEOUT 50u
#define DEM_UDS_QUEUE_LENGTH      10u

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
