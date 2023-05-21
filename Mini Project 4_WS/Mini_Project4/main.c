#include "icu.h"
#include "lcd.h"
#include "Ultrasonic.h"
#include <avr/io.h>

uint16 distance_measure = 0;

int main (void)
{
	LCD_init();
	SREG |= (1<<7);
	Ultrasonic_init();

	while (1)
	{
			distance_measure = Ultrasonic_readDistance();
			LCD_displayStringRowColumn(0, 1, "Distance = ");
			if (distance_measure < 100)
			{
				LCD_moveCursor(0, 12);
				LCD_intgerToString(distance_measure);
				LCD_moveCursor(0,14);
				LCD_displayCharacter(' ');
			}
			else
			{
				LCD_moveCursor(0, 12);
				LCD_intgerToString(distance_measure);
			}
		}

	return 0;
}
