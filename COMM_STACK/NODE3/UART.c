/*
 * UART.c
 *
 * Created: 9/16/2019 04:17:24 ?
 *  Author: Mohamed Hafez
 */ 

#include "UART.h"

#define WAIT_TO_TRANSMIT  !IS_BIT_SET((UARTBASE + UCSRA_OFFSET),UDRE)
#define WAIT_TO_RECEIVE   !IS_BIT_SET((UARTBASE + UCSRA_OFFSET),RXC)
#define DATA              ACCESS_REG_8BIT((UARTBASE + USART_OFFSET))

static uint8 (*pfunc_TX)(void);
static void  (*pfunc_RX)(uint8 rx_value);
static uint8 (*pfunc_UD)(void);

void  uart_init(UART_cnfg* ptr_uart)
{
	ACCESS_REG_16BIT((UARTBASE + UBRRL_OFFSET)) = ((ptr_uart)->baudrate);            // baud rate setting
	ACCESS_REG_8BIT((UARTBASE + UCSRC_OFFSET)) |= (SET << URSEL);
	switch((ptr_uart)->databits)
	{
		//configuration for different transmitted and received bits(5,6,7,8,9)
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
	
	ACCESS_REG_8BIT((UARTBASE + UCSRC_OFFSET)) |= (((ptr_uart)->parity)    << UPM0);//no parity 
	ACCESS_REG_8BIT((UARTBASE + UCSRC_OFFSET)) |= (((ptr_uart)->stopbits)  << USBS);//1stop , 
	ACCESS_REG_8BIT((UARTBASE + UCSRC_OFFSET)) |= (((ptr_uart)->operation) << UMSEL); //configuration operation (sync or async)
	ACCESS_REG_8BIT((UARTBASE + UCSRC_OFFSET)) |= (((ptr_uart)->colck)     << UCPOL);
	switch((ptr_uart)->state)
	{
		case RECEIVE :
		   ACCESS_REG_8BIT((UARTBASE + UCSRB_OFFSET)) |= (SET << RXEN); // wake up uart for recieve
		break;
		case TRANSMIT:
		   ACCESS_REG_8BIT((UARTBASE + UCSRB_OFFSET)) |= (SET << TXEN); // wake up uart transmit
		break;
		case TRANCIVER :
		   ACCESS_REG_8BIT((UARTBASE + UCSRB_OFFSET)) |= (SET << RXEN); // wake up uart for recieve
		   ACCESS_REG_8BIT((UARTBASE + UCSRB_OFFSET)) |= (SET << TXEN); // wake up uart transmit
		break;
	}
}

void  uart_transmit(uint8 data,uint8 databits)
{
	while (WAIT_TO_TRANSMIT); // checking if there's still data in Buffer
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
	while (WAIT_TO_RECEIVE); // checking is that recieve completed
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

void int_tx(uint8 databits, uint8 (*pfunc_tx)( void))
{
	SET_BIT((UARTBASE + UCSRB_OFFSET),TXCIE);
	pfunc_TX = pfunc_tx;
}

uint8 int_rx(uint8 databits, void (*pfunc_rx)(uint8 rx_value))
{
	SET_BIT((UARTBASE + UCSRB_OFFSET),RXCIE);
	pfunc_RX = pfunc_rx;
}

void int_ud(uint8 databits, uint8 (*pfunc_ud)(void))
{
	SET_BIT((UARTBASE + UCSRB_OFFSET),UDRIE);
	pfunc_UD = pfunc_ud;
}

ISR(USART_TXC_vect)
{
	sei();
	WRITE_REG_8BIT((UARTBASE + USART_OFFSET),(*pfunc_TX)());
}

ISR(USART_RXC_vect)
{
	sei();
	(*pfunc_RX)(DATA);
}

ISR(USART_UDRE_vect)
{
	sei();
	//uint8 data = (*pfunc_UD)()
	WRITE_REG_8BIT((UARTBASE + USART_OFFSET),(*pfunc_UD)());
	CLEAR_BIT((UARTBASE + UCSRB_OFFSET),UDRIE);
	
}