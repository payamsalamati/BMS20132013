/**
 * @file logicalBlock_config.h
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief Configuration for Logical Blocks
 * @details
 *
 *  A logical block represents one or more continuous memory address spaces.
 *  The use of different storage media (internal flash, external flash, EEPROM)
 *  is allowed for different logical blocks.
 *  A logical block is the smallest erasable and validatable memory unit.
 *  A logical block may consist of one or more segments. There may be gaps
 *  between the segments.
 *
 *  The logical block table is a data block located in the application software
 *  of a server describing all logical blocks. The logical block table itself is
 *  a logical block. Its purpose is to allow the logical block layout of the
 *  application to be changed if necessary.
 *
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

#define LOGICAL_BLOCK_BOOTLOADER          0x00u
#define LOGICAL_BLOCK_LOGICAL_BLOCK_TABLE 0x01u
#define LOGICAL_BLOCK_APPLICATION         0x02u
#define LOGICAL_BLOCK_DATA                0x03u

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
