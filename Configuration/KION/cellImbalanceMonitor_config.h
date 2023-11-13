/**
 * @file cellImbalanceMonitor_config.h
 * @copyright Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
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


//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//


/**@def CELL_IMBALANCE_ALERT_RELEASE_DIFF
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: ms
 */
#define CELL_IMBALANCE_ALERT_RELEASE_DIFF 200

/**@def CELL_IMBALANCE_ALERT_RELEASE_TIME
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: ms
 */
#define CELL_IMBALANCE_ALERT_RELEASE_TIME 60000

/**@def CELL_IMBALANCE_ERR_DETECT_DIFF
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
// https://polarion.futavis.de/polarion/#/project/WHBMS_BMS_1v0/workitem?id=WHBMS-19899
#define CELL_IMBALANCE_DEFAULT_ERR_DETECT_DIFF 250

/**@def CELL_IMBALANCE_ERR_DETECT_TIME
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: ms
 */
#define CELL_IMBALANCE_DEFAULT_ERR_DETECT_TIME 0

/**@def CELL_IMBALANCE_ERR_RELEASE_DIFF
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define CELL_IMBALANCE_DEFAULT_ERR_RELEASE_DIFF 250

/**@def CELL_IMBALANCE_ERR_RELEASE_TIME
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: ms
 */
#define CELL_IMBALANCE_DEFAULT_ERR_RELEASE_TIME 0

/**@def CELL_IMBALANCE_WARN_DETECT_DIFF
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
// https://polarion.futavis.de/polarion/#/project/WHBMS_BMS_1v0/workitem?id=WHBMS-19898
#define CELL_IMBALANCE_DEFAULT_WARN_DETECT_DIFF 50

/**@def CELL_IMBALANCE_PERM_ERR_DETECT_TIME
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: ms
 */
#define CELL_IMBALANCE_PERM_ERR_DETECT_TIME 0

/**@def CELl_IMBALANCE_WARN_DETECT_DIFF
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define CELL_IMBALANCE_DEFAULT_WARN_DETECT_DIFF 50

/**@def CELL_IMBALANCE_WARN_DETECT_TIME
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: ms
 */
#define CELL_IMBALANCE_DEFAULT_WARN_DETECT_TIME 0

/**@def CELL_IMBALANCE_WARN_RELEASE_DIFF
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: mV
 */
#define CELL_IMBALANCE_DEFAULT_WARN_RELEASE_DIFF 50

/**@def CELL_IMBALANCE_WARN_RELEASE_TIME
 * @brief
 * @details
 *
 * (Fix value)
 * @unit: ms
 */
#define CELL_IMBALANCE_DEFAULT_WARN_RELEASE_TIME 0

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//
