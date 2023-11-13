/**
 * @file voltageViolationHistogram_config.h
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */

#ifndef __VOLTAGEVIOLATIONHISTOGRAM_CONFIG_H__
#define __VOLTAGEVIOLATIONHISTOGRAM_CONFIG_H__
//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

//***************************************************************************//
//************************** PUBLIC TYPEDEFS ********************************//
//***************************************************************************//

//***************************************************************************//
//************************** PUBLIC VARIABLE DEFINITIONS ********************//
//***************************************************************************//
/**
 * @brief operating limit for voltage violation histogram [mV]
 *
 */
#define VOLTAGE_VIOLATION_HISTOGRAM_VOLTAGE_MAX 4150

/**
 * @brief operating limit for voltage violation histogram [mV]
 *
 */
#define VOLTAGE_VIOLATION_HISTOGRAM_VOLTAGE_MIN 2500

#define VOLTAGE_VIOLATION_HISTOGRAM_LOW_POSITION  0
#define VOLTAGE_VIOLATION_HISTOGRAM_HIGH_POSITION 1

#define VOLTAGE_VIOLATION_HISTOGRAM_NUMBER_OF_LOW_RING_VALUES  10
#define VOLTAGE_VIOLATION_HISTOGRAM_NUMBER_OF_HIGH_RING_VALUES 15

#define VOLTAGE_VIOLATION_HISTOGRAM_NUMBER_OF_HISTOGRAMS_PER_MODULE 2

#define VOLTAGE_VIOLATION_HISTOGRAM_COUNTER_SIZE 2


//***************************************************************************//
//************************** PUBLIC FUNCTION DECLARATIONS *******************//
//***************************************************************************//

#endif  // __VOLTAGEVIOLATIONHISTOGRAM_CONFIG_H__*/
