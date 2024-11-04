/***************************************************************************************************************
 * timer.h
 * Author: Muhammed Ayman
 * Module: Timer
 **************************************************************************************************************/

#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	TIMER0_ID, TIMER1_ID, TIMER2_ID
}Timer_ID_Type;

typedef enum
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
	,F_CPU_8_TIMER2 = 2, F_CPU_32_TIMER2, F_CPU_64_TIMER2, F_CPU_128_TIMER2, F_CPU_256_TIMER2, F_CPU_1024_TIMER2
}Timer_ClockType;

typedef enum
{
	NORMAL_MODE, COMPARE_MODE
}Timer_ModeType;

typedef struct
{
	uint16 timer_InitialValue;
	uint16 timer_compare_MatchValue; 		/*it will be used in compare mode only*/
	Timer_ID_Type timer_ID;
	Timer_ClockType timer_clock;
	Timer_ModeType timer_mode;
}Timer_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function to initialize the Timer driver.
 */
void Timer_init(const Timer_ConfigType * Config_Ptr);

/*
 * Function to disable the Timer via Timer_ID.
 */
void Timer_deInit(Timer_ID_Type timer_type);

/*
 * Function to get the Timer Value.
 */
uint16 Timer_getTimerValue(Timer_ID_Type timer_type);

/*
 * Function to set the Call Back function address to the required Timer.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID);

#endif /* MCAL_TIMER_H_ */
