/***************************************************************************************************************
 * pwm.h
 * Author: Muhammed Ayman
 * Module: PWM
 **************************************************************************************************************/

#ifndef MCAL_PWM_H_
#define MCAL_PWM_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                      	Functions Prototypes                               *
 *******************************************************************************/

/*
 * Function to initialize Timer0 with Fast PWM mode.
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* MCAL_PWM_H_ */
