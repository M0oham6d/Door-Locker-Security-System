/***************************************************************************************************************
 * buzzer.c
 * Author: Muhammed Ayman
 * Module: Buzzer
 **************************************************************************************************************/

#include "buzzer.h"
#include "../MCAL/gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Initializes the buzzer pin direction and turn off the buzzer.
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_CONNECTION, BUZZER_PIN_CONNECION, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_CONNECTION, BUZZER_PIN_CONNECION, LOGIC_LOW);
}

/*
 * Activates the buzzer.
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_CONNECTION, BUZZER_PIN_CONNECION, LOGIC_HIGH);
}

/*
 * Deactivates the buzzer.
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_CONNECTION, BUZZER_PIN_CONNECION, LOGIC_LOW);
}
