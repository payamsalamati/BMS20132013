/**
 * @file memory_config.h
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief Contains EEPROM Addresses
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

// Start address of Bootloader block in NVM is 0x0008
#define EXT_FLASH_ADDR_ECU_RESET_START  0x0008u
#define EXT_FLASH_ADDR_ECU_RESET_LENGTH 1u

#define EXT_FLASH_ADDR_STAY_IN_BOOT_START  (EXT_FLASH_ADDR_ECU_RESET_START + EXT_FLASH_ADDR_ECU_RESET_LENGTH)
#define EXT_FLASH_ADDR_STAY_IN_BOOT_LENGTH 1u

#define EXT_FLASH_ADDR_BOOTLOADER_IDENTIFICATION_BACKUP_START  (EXT_FLASH_ADDR_STAY_IN_BOOT_START + EXT_FLASH_ADDR_STAY_IN_BOOT_LENGTH)
#define EXT_FLASH_ADDR_BOOTLOADER_IDENTIFICATION_BACKUP_LENGTH 15u

#define EXT_FLASH_ADDR_APPLICATION_SOFTWARE_IDENTIFICATION_BACKUP_START  (EXT_FLASH_ADDR_BOOTLOADER_IDENTIFICATION_BACKUP_START + EXT_FLASH_ADDR_BOOTLOADER_IDENTIFICATION_BACKUP_LENGTH)
#define EXT_FLASH_ADDR_APPLICATION_SOFTWARE_IDENTIFICATION_BACKUP_LENGTH 15u

#define EXT_FLASH_ADDR_APPLICATION_DATA_IDENTIFICATION_BACKUP_START  (EXT_FLASH_ADDR_APPLICATION_SOFTWARE_IDENTIFICATION_BACKUP_START + EXT_FLASH_ADDR_APPLICATION_SOFTWARE_IDENTIFICATION_BACKUP_LENGTH)
#define EXT_FLASH_ADDR_APPLICATION_DATA_IDENTIFICATION_BACKUP_LENGTH 15u


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
