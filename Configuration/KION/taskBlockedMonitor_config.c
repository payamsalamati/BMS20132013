/**
 * @file taskBlockedMonitor_config.c
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
#include "taskBlockedMonitor.h"
#include "task_cfg.h"
#include "dem.h"
#include "safetyDataIf.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//
/**
 * @brief this function will be called when this module kills a task as a
 * 		  reaction to a timeout
 * @details THIS FUNCTION MUST BE PROVIDED BY THE UPPER LAYER (APPLICATION)
 * an empty function will be used as default, overwrite this function if you
 * want an application specific reaction
 * @param[id] the id of the killed task
 * ##Requirements:
 * **Requirement**  |**Description**
 * :---------------:|:---------------
 * **TskM_00002**   |DTC *DTC_TASK_TIMING_MALFUNCTIONING* + ID-bitmask will be set
 *
 */
void taskBlockedMonitor_taskKilledNotification(uint8_t id);

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//

// @req CB-77080
void taskBlockedMonitor_taskKilledNotification(uint8_t id)
{
    dem_reportFault(DTC_TASK_TIMING_MALFUNCTIONING + id);
    safetyDataIf_setError();
}

//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//
