/*
 * UART.c
 *
 * Created: 9/16/2019 04:17:24 م
 *  Author: mah_h
 */ 

#include "UART.h"

void  uart_baudrate(uartbaudrate_cnfg baudrate)
{
	ACCESS_REG_8BIT((UARTBASE + UBRRL_OFFSET)) = baudrate;
}

void  uart_setframe(uartdata_bits databits,uartparity_cnfg parity,uartstopbit_cnfg stopbits)
{
	ACCESS_REG_8BIT((UARTBASE + UCSRC_OFFSET)) |= (SET << URSEL);
	switch(databits)
	{
		case _5BIT :
		   CLEAR_BIT((UARTBASE + UCSRC_OFFSET),UCSZ0);
		   CLEAR_BIT((UARTBASE + UCSRC_OFFSET),UCSZ1);
		   CLEAR_BIT((UARTBASE + UCSRB_OFFSET),UCSZ2);
		break;
		case _6BIT :
		   SET_BIT((UARTBASE + UCSRC_OFFSET),UCSZ0);
		   CLEAR_BIT((UARTBASE + UCSRC_OFFSET),UCSZ1);
		   CLEAR_BIT((UARTBASE + UCSRB_OFFSET),UCSZ2);
		break;
		case _7BIT :
		   CLEAR_BIT((UARTBASE + UCSRC_OFFSET),UCSZ0);
		   SET_BIT((UARTBASE + UCSRC_OFFSET),UCSZ1);
		   CLEAR_BIT((UARTBASE + UCSRB_OFFSET),UCSZ2);
		break;
		case _8BIT :
		   SET_BIT((UARTBASE + UCSRC_OFFSET),UCSZ0);
		   SET_BIT((UARTBASE + UCSRC_OFFSET),UCSZ1);
		   CLEAR_BIT((UARTBASE + UCSRB_OFFSET),UCSZ2);
		break;
		case _9BIT :
		   SET_BIT((UARTBASE + UCSRC_OFFSET),UCSZ0);
		   SET_BIT((UARTBASE + UCSRC_OFFSET),UCSZ1);
		   SET_BIT((UARTBASE + UCSRB_OFFSET),UCSZ2);
		break;
	}
	
	ACCESS_REG_8BIT((UARTBASE + UCSRC_OFFSET)) |= (parity   << UPM0);
	ACCESS_REG_8BIT((UARTBASE + UCSRC_OFFSET)) |= (stopbits << USBS);
}

void  uart_init(uartstate_cnfg state,uartoperation_cnfg operation,uartclock_cnfg colck)
{
	ACCESS_REG_8BIT((UARTBASE + UCSRC_OFFSET)) |= (operation << UMSEL);
	ACCESS_REG_8BIT((UARTBASE + UCSRC_OFFSET)) |= (colck     << UCPOL);
	switch(state)
	{
		case RECEIVE :
		   ACCESS_REG_8BIT((UARTBASE + UCSRB_OFFSET)) |= (SET << RXEN);
		break;
		case TRANSMIT:
		   ACCESS_REG_8BIT((UARTBASE + UCSRB_OFFSET)) |= (SET << TXEN);
		break;
	}
}

void  uart_transmit(uint8 data,uint8 databits)
{
	while (!(ACCESS_REG_8BIT((UARTBASE + UCSRA_OFFSET)) & (1 << UDRE)));
	switch(databits)
	{
		case _5BIT :
		case _6BIT :
		case _7BIT :
		case _8BIT : 
		   WRITE_REG_8BIT((UARTBASE + USART_OFFSET),data);
		break;
		case _9BIT :
		   
		break;
	}
}

uint8 uart_receive(uint8 databits)
{
	while (!(ACCESS_REG_8BIT((UARTBASE + UCSRA_OFFSET)) & (1 << RXC)));
	switch(databits)
	{
		case _5BIT :
		case _6BIT :
		case _7BIT :
		case _8BIT :
		  return READ_REG_8BIT((UARTBASE + USART_OFFSET));
		break;
		case _9BIT :
		
		break;
	}
}