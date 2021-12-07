/*
 * main.c
 *
 *  Created on: Oct 21, 2021
 *      Author: Mustafa
 */


#include "lcd.h"
#include "ultrasonic.h"


void main(void)
{


	/*Initializing the LCD*/
	LCD_init();

	/*Writing it on LCD for one time in the program only*/
	LCD_displayStringRowColumn(0, 0, "Distance=     CM");

	uint16 distance_value = 0;
	while(1)
	{
		/*Iinitializing Ultrasonic that initializes ICU to detect rising edge*/
		Ultrasonic_init();

		/*Reading distance to display it*/
		distance_value = Ultrasonic_readDistance();

		/*Displaying value on LCD after converting it into string*/
		LCD_moveCursor(0, 10);
		LCD_intgerToString(distance_value);
		/*Condition to clear number from lcd when decrementing */
		if(distance_value < 10)
		{
			LCD_displayStringRowColumn( 0 , 11 , "  ");/*clearing 2nd & 3rd numbers*/
		}
		else if(distance_value < 100)
		{
			LCD_displayStringRowColumn( 0 , 12 , " ");/*clear 3rd number from lcd when decrementing*/
		}

	}
}
