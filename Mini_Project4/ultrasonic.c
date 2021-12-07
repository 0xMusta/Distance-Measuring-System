/*
 * ultrasonic.c
 *
 *  Created on: Oct 19, 2021
 *      Author: Mustafa
 */


#include "icu.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include  "gpio.h"
#include <util/delay.h> /* For the delay functions */
#include "avr/io.h" /* To use the IO Ports Registers */
#include "ultrasonic.h"


uint8 g_edgeCount = 0;//variable to count number of edges falling or rising
uint32 g_timeHigh = 0;//variable to count the time for which the echo is high


void Ultrasonic_init(void)
{
	/*
	 * The ICU  configured with frequency F_CPU/8 and to detect the raising
	 * edge as the first edge
	 *  F_CPU/8  */
	/*
	 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
	 * of TCCR1B Register should be (0, 1, 0)
	 */
	/*Raising edge*/
	/*
	 * Bit 6 - ICES1 in TCCR1B Register should be 1 for Raising edge
	 */
	/*configure ICU to use F/8 and detect rising edge*/
	Icu_ConfigType Config_Icu = {F_CPU_8,RISING};

	/*Calling ICU init with configuration pointer to struct*/
	Icu_init(&Config_Icu);

	/*Setup the ICU call back function*/
	Icu_setCallBack(Ultrasonic_edgeProcessing);

	/* Setup the direction for the trigger pin as output pin */

	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
}

void Ultrasonic_Trigger(void)
{

	/*
	 * The Timing diagram is shown below. You only need to supply a short 10uS
	 * pulse to the trigger input to start the ranging, and then the module will send out
	 * an 8 cycle burst of ultrasound at 40 kHz and raise its echo
	 */

	/*
	 * Transmit trigger pulse of at least 10 us to the HC-SR04 Trig Pin
	 */
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);

	_delay_us(10);

	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);

}


uint16 Ultrasonic_readDistance(void)
{

	/*Sending the trigger pulse*/
	Ultrasonic_Trigger();

	/*Waiting for edge processing*/
	/*Then calculating and returning the distance using timer value*/
	/*Ultrasonic sensor  Formula: uS / 58 = centimeters or uS / 148 =inch; or: the
	 * range = high level time * velocity (340M/S) / 2*/
	uint16 distance = (g_timeHigh / 58) ;
	return distance;
}



void Ultrasonic_edgeProcessing(void)
{


	/*Detecting falling edge for the end of the pulse width */

	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/*Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		Icu_DeInit(); /* Disable ICU Driver */
		g_edgeCount = 0; /*Restart edge count*/
		Icu_setEdgeDetectionType(RISING);
	}

}


