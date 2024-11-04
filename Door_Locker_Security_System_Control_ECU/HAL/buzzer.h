/***************************************************************************************************************
 * buzzer.h
 * Author: Muhammed Ayman
 * Module: Buzzer
 **************************************************************************************************************/

#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_

/*******************************************************************************
 *                                Configurations                               *
 *******************************************************************************/

#define BUZZER_PORT_CONNECTION			PORTC_ID
#define BUZZER_PIN_CONNECION			PIN7_ID

/*******************************************************************************
 *                      	Functions Prototypes                               *
 *******************************************************************************/

/*
 * Initializes the buzzer pin direction and turn off the buzzer.
 */
void Buzzer_init(void);

/*
 * Activates the buzzer.
 */
void Buzzer_on(void);

/*
 * Deactivates the buzzer.
 */
void Buzzer_off(void);

#endif /* HAL_BUZZER_H_ */
