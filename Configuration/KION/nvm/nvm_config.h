/**
 * @file     nvm_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 *
 */

#pragma once

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

// Autosar Config

#include "nvm_config_id.h"
#include "config_enable.h"

/** @brief
 * preprocessor switch to enable some API calls which are related to
 * NVM API configuration classes
 */
#define NVM_API_CONFIG_CLASS 3u  // Available classes: 1, 2, 3


/**
 * @brief configuration ID regarding the NV memory layout. This configuration ID
 * shall be published as e.g. a SW-C shall have the possibility to write it to NV memory
 */
#define NVM_COMPILED_CONFIG_ID 0

/**
 * @brief Defines the number of least significant bits which shall be used to address
 * a certain dataset of a NVRAM block within the interface to the memory hardware
 * abstraction.
 * 0..8: Number of bits which are used for dataset or redundant block addressing
 * 0: No dataset or redundant NVRAM blocks are configured at all, no selection
 * bits required.
 * 1: In case of redundant NVRAM blocks are configured, but no dataset NVRAM blocks
 */
#define NVM_DATASET_SELECTION_BITS 6

/**
 * @brief Preprocessor switch to enable job prioritization handling
 * True: Job prioritization handling enabled
 * False: Job prioritization handling disabled
 */
#define NVM_JOB_PRIORITIZATION CONFIG_DISABLED


/**
 * @brief Preprocessor switch to enable/disable the polling mode in the NVRAM Manager
 * and at the same time disable/enable the callback functions usable by lower layers
 * True: Polling mode enabled, callback function usage disabled
 * False: Polling mode disabled, callback function usage enabled
 */
#define NVM_POLLING_MODE CONFIG_DISABLED

/**
 * @brief Preprocessor switch to enable the API NVM_setRamBlockStatus
 * True: API NVM_setRamBlockStatus enabled
 * False: API NVM_setRamBlockStatus disabled
 */
#define NVM_SET_RAM_BLOCK_STATUS_API CONFIG_DISABLED

/**
 * @brief Defines the number of queue entries for the standard job queue
 */
#define NVM_SIZE_STANDARD_JOB_QUEUE 5


// Futavis config

/**
 * @def NVM_MAX_BLOCK_LENGTH
 * @brief maximum size of the block length for all NVM Blocks
 */
#define NVM_MAX_BLOCK_LENGTH 40004

#define NVM_MAX_NUMBER_OF_BLOCKS 189

#define NVM_CRC_SIZE 4

#define NVM_USE_BLOCK_WRITE_PROTECTION CONFIG_ENABLED

#define NVM_USE_CALC_RAM_BLOCK_CRC CONFIG_DISABLED

#define NVM_USE_CRC_COMP_MECHANISM CONFIG_DISABLED

#define NVM_USE_RESISTANT_TO_CHANGED_SW CONFIG_DISABLED

#define NVM_READ_ALL_BLOCKS_PER_LOOP 15

#define NVM_WRITE_ALL_BLOCKS_PER_LOOP 15

void nvm_config_checkSize(void);
