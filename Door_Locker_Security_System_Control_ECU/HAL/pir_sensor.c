/***************************************************************************************************************
 * pir_sensor.c
 * Author: Muhammed Ayman
 * Module: PIR Sensor
 **************************************************************************************************************/

#include "pir_sensor.h"
#include <avr/io.h>
#include "../MCAL/gpio.h"

/*******************************************************************************
 *                      	Functions Definitions                              *
 *******************************************************************************/

/*
 *  Function to initialize the PIR driver.
 *  Set up pin direction as input pin.
 */
void PIR_init(void)
{
	GPIO_setupPinDirection(PIR_PORT_CONNECTION, PIN_CONNECTION, PIN_INPUT);
}

/*
 *  Function to return PIR State.
 */
uint8 PIR_getState(void)
{
	return GPIO_readPin(PIR_PORT_CONNECTION, PIN_CONNECTION);
}
