/*
 * dataInterface_validate_config_KION.h
 *
 *  Created on: 06.11.2019
 *      Author: Kostiantyn
 */

#pragma once


/**@def SOC_VALID_COUNTER
 * @brief how often a value needs to be receive to be seen as valid
 * @details
 *
 * (Fix value)
 */
#define SOC_VALID_COUNTER 5

/**@def SOC_VALID_MAX
 * @brief Maximal SOC Value
 * @details
 *
 * (Fix value)
 */
#define SOC_VALID_MAX 100

/**@def BALANCING_TEMPERATURE_VALID_MAX
 * @brief
 * @details
 *
 * (Fix value)
 */
#define BALANCING_TEMPERATURE_VALID_MAX 300

/**@def BALANCING_TEMPERATURE_VALID_MIN
 * @brief
 * @details
 *
 * (Fix value)
 */
#define BALANCING_TEMPERATURE_VALID_MIN -40

/**@def ISOLATION_MAX_VALUE
 * @brief TODO Description
 * @details
 *
 * (Fix value)
 * @unit: kOhm
 */
#define ISOLATION_MAX_VALUE 500000

/**@def ISOLATION_MIN_VALUE
 * @brief TODO Description
 * @details
 *
 * (Fix value)
 * @unit: kOhm
 */
#define ISOLATION_MIN_VALUE 300

/**@def NUMBER_OF_ISO_MONITORS
 * @brief TODO Description
 * @details
 *
 * (Fix value)
 */
#define NUMBER_OF_ISO_MONITORS 1
