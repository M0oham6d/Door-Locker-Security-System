/***************************************************************************************************************
 * uart.c
 * Author: Muhammed Ayman
 * Module: UART
 **************************************************************************************************************/

#include "uart.h"
#include <avr/io.h>
#include "../Common_Macros/common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr)
{
    uint16 ubrr_value = 0;

    /* U2X = 1 for double transmission speed */
    UCSRA = (1<<U2X);

    /************************** UCSRB Description **************************
     * RXCIE = 0 Disable USART RX Complete Interrupt Enable
     * TXCIE = 0 Disable USART TX Complete Interrupt Enable
     * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
     * RXEN  = 1 Receiver Enable
     * RXEN  = 1 Transmitter Enable
     * UCSZ2 = 0 For 5-bit, 6-bit, 7-bit, 8-bit data mode
     * RXB8 & TXB8 not used for 8-bit data mode
     ***********************************************************************/
    UCSRB = (1<<RXEN) | (1<<TXEN);

    /************************** UCSRC Description **************************
     * URSEL   = 1 The URSEL must be one when writing the UCSRC
     * UMSEL   = 0 Asynchronous Operation
     * UPM1:0  = 00 Disable parity bit, 10  Even Parity, 11  Odd Parity
     * USBS    = 0 One stop bit, 1 Two stop bit
     * UCSZ1:0 = 11 For 8-bit data mode
     * UCPOL   = 0 Used with the Synchronous operation only
     ***********************************************************************/
    UCSRC = (1<<URSEL) | ((Config_Ptr->bit_data)<<UCSZ0) |
            ((Config_Ptr->Parity_Configurations)<<UPM0) |
            ((Config_Ptr->StopBit_Configurations)<<USBS);

    /* Calculate the UBRR register value */
    ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baudRate * 8UL))) - 1);

    /* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH */
    UBRRH = ubrr_value>>8;
    UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
    /*
     * UDRE flag is set when the TX buffer (UDR) is empty and ready for
     * transmitting a new byte so wait until this flag is set to one
     */
    while(BIT_IS_CLEAR(UCSRA,UDRE)){}

    /*
     * Put the required data in the UDR register and it also clear the UDRE flag as
     * the UDR register is not empty now
     */
    UDR = data;
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void)
{
    /* RXC flag is set when the UART receive data so wait until this flag is set to one */
    while(BIT_IS_CLEAR(UCSRA,RXC)){}

    /*
     * Read the received data from the RX buffer (UDR)
     * The RXC flag will be cleared after read the data
     */
    return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
    uint8 i = 0;

    /* Send the whole string */
    while(Str[i] != '\0')
    {
        UART_sendByte(Str[i]);
        i++;
    }
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
    uint8 i = 0;

    /* Receive the first byte */
    Str[i] = UART_receiveByte();

    /* Receive the whole string until the '#' */
    while(Str[i] != '#')
    {
        i++;
        Str[i] = UART_receiveByte();
    }

    /* After receiving the whole string plus the '#', replace the '#' with '\0' */
    Str[i] = '\0';
}

/*
 * Description :
 * Send the required array through UART to the other UART device.
 */
void UART_sendArray(const uint8 *a_ptr, uint8 size)
{
    uint8 i;

    /* Send the whole array */
	for(i = 0; i < size; i++)
    {
        UART_sendByte(a_ptr[i]);
    }
    UART_sendByte('#');
}

/*
 * Description :
 * Receive the required array until the '#' symbol through UART from the other UART device.
 */
void UART_receiveArray(uint8 *a_ptr)
{
    uint8 i = 0;

    /* Receive the first byte */
	a_ptr[i] = UART_receiveByte();

    /* Receive the whole string until the '#' */
	while(a_ptr[i] != '#')
	{
		i++;
		a_ptr[i] = UART_receiveByte();
	}
}
