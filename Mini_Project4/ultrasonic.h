/*
 * ultrasonic.h
 *
 *  Created on: Oct 21, 2021
 *      Author: Mustafa
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description : Function to initialize the ultrasonic sensor driver
 * 	1. Set the required clock for ICU.
 * 	2. Set the required edge detection for ICU.
 * 	3. Enable the Input Capture Interrupt for ICU.
 * 	4. Initialize Timer1 Registers for ICU.
 * 	5. Set Callback Function for ICU.
 * 	6. Setup the direction for the trigger pin as output pin.
 */
void Ultrasonic_init(void);

/*
 * Description : Function to trigger the ultrasonic by pulse of least period of 10 us
 */
void Ultrasonic_Trigger(void);

/*
 * Description : Function to read the distance from ultrasonic
 */
uint16 Ultrasonic_readDistance(void);
/*
 * Description : Function to get the the value of the Timer from ICU.
 * IT's the Callback Function for ICU driver
 */
void Ultrasonic_edgeProcessing(void);




#endif /* ULTRASONIC_H_ */
