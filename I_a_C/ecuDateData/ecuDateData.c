/**
 * @file ecuDateData.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *   Interfaces to other modules:
 *   -
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "ecuDateData.h"
#include "ecuDateData_config.h"
#include "task_cfg.h"
#include "nvm.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

MEM_APPLICATION EcuDateNvmData ecuDateNvm = {
    .ecuInstallationDateYear  = ECU_DATE_DATA_DEFAULT_INSTALLATION_DATE_YEAR,
    .ecuInstallationDateMonth = ECU_DATE_DATA_DEFAULT_INSTALLATION_DATE_MONTH,
    .ecuInstallationDateDay   = ECU_DATE_DATA_DEFAULT_INSTALLATION_DATE_DAY,
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS ********************//
//***************************************************************************//

uint8_t ecuDateData_getEcuInstallationDateYear(void)
{
    return ecuDateNvm.ecuInstallationDateYear;
}

uint8_t ecuDateData_getEcuInstallationDateMonth(void)
{
    return ecuDateNvm.ecuInstallationDateMonth;
}

uint8_t ecuDateData_getEcuInstallationDateDay(void)
{
    return ecuDateNvm.ecuInstallationDateDay;
}

void ecuDateData_setEcuInstallationDateYear(uint8_t newValue)
{
    ecuDateNvm.ecuInstallationDateYear = newValue;
}

void ecuDateData_setEcuInstallationDateMonth(uint8_t newValue)
{
    ecuDateNvm.ecuInstallationDateMonth = newValue;
}

void ecuDateData_setEcuInstallationDateDay(uint8_t newValue)
{
    ecuDateNvm.ecuInstallationDateDay = newValue;
}

#if defined(UNIT_TEST)
void ecuDateData_clearAll()
{
    ecuDateNvm.ecuInstallationDateYear  = 0;
    ecuDateNvm.ecuInstallationDateMonth = 0;
    ecuDateNvm.ecuInstallationDateDay   = 0;
}
#endif

uint8_t ecuDateData_getWriteBlockOnceIndicator(void)
{
    return ecuDateNvm.writeBlockOnce;
}
