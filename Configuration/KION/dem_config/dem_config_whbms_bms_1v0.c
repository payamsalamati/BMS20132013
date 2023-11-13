
/**
 * @file     dem_config_whbms_bms_1v0.c
 * @copyright (c) Futavis GmbH, Aachen 2021 - alle Rechte vorbehalten
 * @brief    Short description
 * @details
 */

//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include <stdint.h>
#include "dem.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

static const DEM_SeverityTransition severityTransitionTable[] = {
    /*	 Fault -------------Bitmask  --------- Category ------------------- Level -------------------- Transition times -- */

};

const DEM_Cfg demCfgExternal = {
    .severityTransitionTable     = severityTransitionTable,
    .severityTransitionTableSize = sizeof(severityTransitionTable) / sizeof(DEM_SeverityTransition),
};
