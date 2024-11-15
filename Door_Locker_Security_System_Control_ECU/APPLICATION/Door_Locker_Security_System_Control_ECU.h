/***************************************************************************************************************
 * Door_Locker_Security_System_Control_ECU.h
 * Author: Muhammed Ayman
 * Module: APPLICATION
 **************************************************************************************************************/

#ifndef APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_CONTROL_ECU_H_
#define APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_CONTROL_ECU_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PASSWORD_SIZE			5
#define I_AM_READY				0x01
#define WRONG_PASS				1U
#define CORRECT_PASS			0U

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Function to receive 2 passwords and check them.
 * If they are identical, save the password to EEPROM.
 * Else, Receive the 2 passwords again.
 */
void receive2Password(uint8 * a_ptr1, uint8 * a_ptr2);

/*
 * Function to receive password and check it.
 * If the user entered password 3 times wrong, alarm will be on.
 * Else, user will enter the password again if it is wrong.
 * If the password is correct, the program will continue normally.
 */
void checkPassAndAlarm(void);

/*
 * Function to delay for 15s.
 */
void delay_15s(void);

#endif /* APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_CONTROL_ECU_H_ */
