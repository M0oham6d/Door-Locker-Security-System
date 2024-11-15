/***************************************************************************************************************
 * Door_Locker_Security_System_HMI_ECU.c
 * Author: Muhammed Ayman
 * Module: APPLICATION
 **************************************************************************************************************/

#include "Door_Locker_Security_System_HMI_ECU.h"
#include <util/delay.h>
#include <avr/io.h>
#include "../HAL/keypad.h"
#include "../HAL/lcd.h"
#include "../MCAL/uart.h"
#include "../MCAL/timer.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Entered passwords from user in the beginning. */
uint8 g_key[PASSWORD_SIZE], g_key_confirm[PASSWORD_SIZE];
/* The entered password to unlock the door. */
uint8 g_key_again[PASSWORD_SIZE];
/* Counter used if user enter password wrong. */
uint8 g_incorrectPass1 = 1;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Function to take 1 password from user.
 */
void takePassFromUser(uint8 * a_ptr)
{
	uint8 counter = 0;

	/* Take the password from user. */
	while(counter < PASSWORD_SIZE)
	{
		_delay_ms(KEYPAD_DELAY);						/* Delay for waiting for the next number. */

		/* To make sure that these buttons do not entered as password. */
		if('=' != KEYPAD_getPressedKey() && '-' != KEYPAD_getPressedKey() && '+' != KEYPAD_getPressedKey())
		{
			a_ptr[counter] = KEYPAD_getPressedKey();	/* Storing the password. */
			LCD_displayCharacter('*');					/* To secure the password. */
			counter++;
		}
	}
	/* Wait for user to enter '=' */
	while('=' != KEYPAD_getPressedKey());
}

/*
 * Function to create the password at the beginning.
 */
void creatingPassword(void)
{
	uint8 wrongPass_flag;

	do{
		/*
		 * User will add the password.
		 * Password will be stored.
		 */
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "PLZ Enter Pass:");
		LCD_moveCursor(1, 0);

		takePassFromUser(g_key);

		/*
		 * Confirming the password for more security.
		 * Password will be stored.
		 */
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "PLZ Re-Enter The");
		LCD_displayStringRowColumn(1, 0, "Same Pass:");

		takePassFromUser(g_key_confirm);

		/* Send 2 passwords to MC2. */
		UART_sendByte(I_AM_READY);
		while(I_AM_READY != UART_receiveByte());
		UART_sendArray(g_key, PASSWORD_SIZE);
		UART_sendArray(g_key_confirm, PASSWORD_SIZE);

		/* Wait for signal from MC2 to know the password is correct or not. */
		while(I_AM_READY != UART_receiveByte());
		UART_sendByte(I_AM_READY);
		wrongPass_flag = UART_receiveByte();

		/* If the password is wrong, display a message and get the password again. */
		if(wrongPass_flag)
		{
			/* Print message for user if the 2 passwords are not identical. */
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 3, "Try Again.");
			_delay_ms(MESSAGE_DELAY);
		}
	}while(wrongPass_flag);
}

/*
 * Function to check if the password is match with the one in EEPROM.
 * If they do not match for 3 times, alarm will be on.
 * Else, continue the program.
 */
void checkPassAndAlarm(void)
{
	uint8 wrongPass_flag;

	do{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "PLZ Enter Old");
		LCD_displayStringRowColumn(1, 0, "Pass:");

		/* Take the password from user. */
		takePassFromUser(g_key_again);

		/* Send the password to MC2. */
		UART_sendByte(I_AM_READY);
		while(I_AM_READY != UART_receiveByte());
		UART_sendArray(g_key_again, PASSWORD_SIZE);

		/* Wait for signal from MC2 to know the password is correct or not. */
		while(I_AM_READY != UART_receiveByte());
		UART_sendByte(I_AM_READY);
		wrongPass_flag = UART_receiveByte();

		/* If the password is wrong for 3 times, alarm will be on and return to home screen.
		 * Else, user will enter the password again.
		 */
		if(wrongPass_flag)
		{
			if(3 == g_incorrectPass1)
			{
				/* Print message for user. */
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 2, "System Locked");
				LCD_displayStringRowColumn(1, 1, "Wait For 1 Min");
				/* Wait for 1 minute (59 seconds). */
				for (int i = 0; i < 59; i++) {
					_delay_ms(1000);
				}

				return;
			}
			else
			{
				g_incorrectPass1++;

				/* Print message for user if the 2 passwords are not identical. */
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 3, "Try Again.");
				_delay_ms(MESSAGE_DELAY);
			}
		}
	}while(wrongPass_flag);
	/* Reset the counter if the password is correct. */
	g_incorrectPass1 = 1;
}

/*
 * Function to delay for 15s.
 */
void delay_15s(void)
{
	Timer_ConfigType timer_configrations1 = {0, 65535, TIMER1_ID, F_CPU_1024, COMPARE_MODE};
	Timer_init(&timer_configrations1);
	while(!(TIFR & (1<<OCF1A)));
	TIFR |= (1<<OCF1A);
	Timer_ConfigType timer_configrations2 = {0, 51621, TIMER1_ID, F_CPU_1024, COMPARE_MODE};
	Timer_init(&timer_configrations2);
	while(!(TIFR & (1<<OCF1A)));
	TIFR |= (1<<OCF1A);

	/* De-initialize timer1. */
	Timer_deInit(TIMER1_ID);
}

/*
 * The main function.
 */
int main(void)
{
	/* Initialize LCD. */
	LCD_init();

	/* Initialize UART with configurations. */
	UART_ConfigType uart_configrations = {9600, UART_Parity_ODD, UART_STOP_1_BIT, MODE_EIGHT_BIT};
	UART_init(&uart_configrations);

	/* System INTRO. */
	LCD_displayStringRowColumn(0, 6, "Hello");
	_delay_ms(MESSAGE_DELAY);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 1, "Welcome To our");
	LCD_displayStringRowColumn(1, 5, "System");
	_delay_ms(MESSAGE_DELAY);

	/* Create the password at the beginning. */
	creatingPassword();

	/* Print message for user. */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Password Created");
	LCD_displayStringRowColumn(1, 2, "Successfully");
	_delay_ms(MESSAGE_DELAY);

	while(1)
	{
		/* Clear the screen. */
		LCD_clearScreen();

		/* Home screen. */
		LCD_displayStringRowColumn(0, 0, "+ : Open Door");
		LCD_displayStringRowColumn(1, 0, "- : Change Pass");

		/* ٍSend the entered button to MC2. */
		UART_sendByte(I_AM_READY);
		while(I_AM_READY != UART_receiveByte());
		UART_sendByte(KEYPAD_getPressedKey());

		switch (KEYPAD_getPressedKey())
		{
		/* Opening door. */
		case '+':
			/*Function to check if the password is match with the one in EEPROM.*/
			/* If they do not match for 3 times, alarm will be on.*/
			/* Else, continue the program.*/
			checkPassAndAlarm();

			/* To go to home screen if the password was wrong 3 times. */
			if(3 == g_incorrectPass1)
			{
				g_incorrectPass1 = 1;
				break;
			}

			/* Print message for user. */
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 1, "Door Unlocking");
			LCD_displayStringRowColumn(1, 4, "PLZ Wait");

			/* Wait 15s until door is opened. */
			delay_15s();

			/* Receive PIR status. */
			while(I_AM_READY != UART_receiveByte());
			UART_sendByte(I_AM_READY);
			if(UART_receiveByte())
			{
				/* Print message for user. */
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 1, "Wait For People");
				LCD_displayStringRowColumn(1, 4, "To Enter");
			}

			/* Wait until people get in. */
			while(UART_receiveByte());

			/* Print message for user. */
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 2, "Door Locking");

			/* Wait until door is closed. */
			delay_15s();

			break;

		/* Changing the password. */
		case '-':
			/*Function to check if the password is match with the one in EEPROM.*/
			/* If they do not match for 3 times, alarm will be on.*/
			/* Else, continue the program.*/
			checkPassAndAlarm();

			/* To go to home screen if the password was wrong 3 times. */
			if(3 == g_incorrectPass1)
			{
				g_incorrectPass1 = 1;
				break;
			}

			/* Create the new password. */
			creatingPassword();

			/* Print message for user. */
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Password Changed");
			LCD_displayStringRowColumn(1, 2, "Successfully");
			_delay_ms(MESSAGE_DELAY);

			break;

		default:
			/* Print message for user. */
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 3, "Try Again.");
			_delay_ms(MESSAGE_DELAY);
		}
	}
	return 0;
}
