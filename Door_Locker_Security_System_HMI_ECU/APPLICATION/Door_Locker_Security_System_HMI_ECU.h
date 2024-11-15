/***************************************************************************************************************
 * Door_Locker_Security_System_HMI_ECU.h
 * Author: Muhammed Ayman
 * Module: APPLICATION
 **************************************************************************************************************/

#ifndef APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_HMI_ECU_H_
#define APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_HMI_ECU_H_

#include "../Standard_Types/standard_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define KEYPAD_DELAY			250
#define MESSAGE_DELAY			750
#define PASSWORD_SIZE			5
#define I_AM_READY				0x01

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Function to take 1 password from user.
 */
void takePassFromUser(uint8 * a_ptr);

/*
 * Function to create the password at the beginning.
 */
void creatingPassword(void);

/*
 * Function to check if the password is match with the one in EEPROM.
 * If they do not match for 3 times, alarm will be on.
 * Else, continue the program.
 */
void checkPassAndAlarm(void);

/*
 * Function to delay for 15s.
 */
void delay_15s(void);

#endif /* APPLICATION_DOOR_LOCKER_SECURITY_SYSTEM_HMI_ECU_H_ */
