/**
 * @file canopen_config.c
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

#include <stddef.h>
#include <stdint.h>
#include "canopen_config.h"
#include "task_cfg.h"
#include "signalWatchdog.h"
#include "task_cfg.h"
#include "sdo.h"
#include "kionCAN.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_CAN CanOpenNodeStm canOpenNodeHandlerKion;
MEM_CAN CanOpenNodeStm canOpenNodeHandlerLinde;
MEM_CAN CanOpenNodeStm canOpenNodeHandlerLindeCharger;

extern bool canOpenStm_checkNodeBevorStartKion(void);
extern bool canOpenStm_checkNodeBevorStartLinde(void);

// cppcheck-suppress misra-c2012-8.11 ; size is given by SDO_READ_TABLE_SIZE
extern const SDOWriteTableEntry sdoWriteTableKion[];
extern const uint16_t SDO_WRITE_TABLE_KION_SIZE;

// cppcheck-suppress misra-c2012-8.11 ; size is given by SDO_READ_TABLE_SIZE
extern const SDOReadTableEntry sdoReadTableKion[];
extern const uint16_t SDO_READ_TABLE_KION_SIZE;

const CanOpenMessage canOpenMessageConfigKion[] = {
    //  Id          minCycletime    maxCycletime    cycleTimeBuffer
};

const CANopen canOpenConfigKion = {
    .nodeId             = CANOPEN_NODE_ID_KION,
    .stateMachineHandle = &canOpenNodeHandlerKion,
    .messageTable       = canOpenMessageConfigKion,
    .messageTableSize   = sizeof(canOpenMessageConfigKion) / sizeof(CanOpenMessage),
    // @req CB-74754
    .ckeckNodeBeforeStart   = canOpenStm_checkNodeBevorStartKion,
    .callbackAfterStartNode = kionCAN_resetLib_pdo_tx7_message_counter,
    .sdoNodeWriteTable      = sdoWriteTableKion,
    .sdoNodeWriteTableSize  = &SDO_WRITE_TABLE_KION_SIZE,
    .sdoNodeReadTable       = sdoReadTableKion,
    .sdoNodeReadTableSize   = &SDO_READ_TABLE_KION_SIZE,
};

// cppcheck-suppress misra-c2012-8.11 ; size is given by SDO_READ_TABLE_SIZE
extern const SDOWriteTableEntry sdoWriteTableLindeTruck[];
extern const uint16_t SDO_WRITE_TABLE_LINDE_TRUCK_SIZE;

// cppcheck-suppress misra-c2012-8.11 ; size is given by SDO_READ_TABLE_SIZE
extern const SDOReadTableEntry sdoReadTableLindeTruck[];
extern const uint16_t SDO_READ_TABLE_LINDE_TRUCK_SIZE;

const CanOpenMessage canOpenMessageConfigLinde[] = {
    //  Id          minCycletime    maxCycletime    cycleTimeBuffer
};

const CANopen canOpenConfigLinde = {
    .nodeId                = CANOPEN_NODE_ID_LINDE,
    .stateMachineHandle    = &canOpenNodeHandlerLinde,
    .messageTable          = canOpenMessageConfigLinde,
    .messageTableSize      = sizeof(canOpenMessageConfigLinde) / sizeof(CanOpenMessage),
    .ckeckNodeBeforeStart  = canOpenStm_checkNodeBevorStartLinde,
    .sdoNodeWriteTable     = sdoWriteTableLindeTruck,
    .sdoNodeWriteTableSize = &SDO_WRITE_TABLE_LINDE_TRUCK_SIZE,
    .sdoNodeReadTable      = sdoReadTableLindeTruck,
    .sdoNodeReadTableSize  = &SDO_READ_TABLE_LINDE_TRUCK_SIZE,
};

// cppcheck-suppress misra-c2012-8.11 ; size is given by SDO_READ_TABLE_SIZE
extern const SDOWriteTableEntry sdoWriteTableLindeCharger[];
extern const uint16_t SDO_WRITE_TABLE_LINDE_CHARGER_SIZE;

// cppcheck-suppress misra-c2012-8.11 ; size is given by SDO_READ_TABLE_SIZE
extern const SDOReadTableEntry sdoReadTableLindeCharger[];
extern const uint16_t SDO_READ_TABLE_LINDE_CHARGER_SIZE;

const CANopen canOpenConfigLindeCharger = {
    .nodeId                = CANOPEN_NODE_ID_LINDE_CHARGER,
    .stateMachineHandle    = &canOpenNodeHandlerLindeCharger,
    .messageTable          = canOpenMessageConfigLinde,
    .messageTableSize      = sizeof(canOpenMessageConfigLinde) / sizeof(CanOpenMessage),
    .ckeckNodeBeforeStart  = canOpenStm_checkNodeBevorStartLinde,
    .sdoNodeWriteTable     = sdoWriteTableLindeCharger,
    .sdoNodeWriteTableSize = &SDO_WRITE_TABLE_LINDE_CHARGER_SIZE,
    .sdoNodeReadTable      = sdoReadTableLindeCharger,
    .sdoNodeReadTableSize  = &SDO_READ_TABLE_LINDE_CHARGER_SIZE,
};

const CANopen* const canOpenConfigs[] = {
    &canOpenConfigKion,
    &canOpenConfigLinde,
    &canOpenConfigLindeCharger
};
const uint8_t CAN_OPEN_CONFIG_SIZE = sizeof(canOpenConfigs) / sizeof(CANopen*);

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
