#include "Ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include "util/delay.h"

const Icu_ConfigType Config_Ptr = { F_CPU_8,RISING };

uint16 distance = 0 ;
uint16 g_timeHigh = 0 ;
uint8  g_edgeCount = 0 ;

void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if( g_edgeCount == 1)
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
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
		g_edgeCount = 0;
	}
}

void Ultrasonic_init(void)
{
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	Icu_init(& Config_Ptr);
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
}

void Ultrasonic_Trigger(void)
{
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	distance = ( g_timeHigh  / 58.8);
	return distance;
}
