/**
 * @file kbsIntegration.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */

#pragma once

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>
#include <stdbool.h>

#include "nvm.h"
#include "dem.h"

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

void kbsIntegration_mainFunction_10ms(void);
void kbsIntegration_mainFunction_100ms(void);
void kbsIntegration_mainFunction_1000ms(void);
void kbsIntegration_init(void);

NVM_Result kbsIntegration_nvmReadCallback(const uint8_t* mirror, uint16_t length);
/**
 * @brief function to write NVM data from RAM into CSCNVM and BMS NVM
 * @details This function is called every 60 minutes by kbsIntegration_mainFunction and during shutdown.
 *          If this function is called during shutdown it reads values from Algorithms with the function KBSInterface_terminate and writes them in CSC and BMS NVM.
 *          If this function is called by the cyclic call in the main function, it should read values from the Algorithms with the function KBSInterface_update_NVM and write the in the CSC and BMS NVM.
 */
NVM_Result kbsIntegration_nvmWriteCallback(uint8_t* mirror, uint16_t length);

bool kbsIntegration_setSocEOC(uint16_t value);
bool kbsIntegration_setSocDOD(uint16_t value);
bool kbsIntegration_setDiagDerating(uint8_t value);

int32_t kbsIntegration_getDeratingChargeLimit(void);
int32_t kbsIntegration_getDeratingDischargeLimit(void);

int32_t kbsIntegration_getDeratingChargeLimitContinous(void);
int32_t kbsIntegration_getDeratingDischargeLimitContinous(void);

uint16_t kbsIntegration_getSocWithSOH_Internal(void);
uint16_t kbsIntegration_getSocWithoutSOH_Internal(void);


uint32_t kbsIntegration_getMaxChargingPowerContinous(void);
uint32_t kbsIntegration_getMaxDischargingPowerContinous(void);

uint32_t kbsIntegration_getMaxChargingPowerPulse(void);
uint32_t kbsIntegration_getMaxDischargingPowerPulse(void);

uint8_t kbsIntegration_getCurrentLimited(void);

bool kbsIntegration_isMonitorDtc(DEM_FaultCode fault);
const uint8_t* kbsIntegration_getIndividualSnapshotOfFault(uint32_t* size, DEM_FaultCode fault);
