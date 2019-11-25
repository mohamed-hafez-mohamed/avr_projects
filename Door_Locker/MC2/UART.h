/*
 * UART.h
 *
 * Created: 9/16/2019 04:17:51 م
 *  Author: mah_h
 */ 


#ifndef UART_H_
#define UART_H_

#include "GPIO.h"

#define SET          1
#define UARTBASE     0x29
#define UBRRL_OFFSET 0x00
#define UCSRB_OFFSET 0x01
#define UCSRA_OFFSET 0x02
#define USART_OFFSET 0x03
#define UCSRC_OFFSET 0x17
#define UBRRH_OFFSET 0x17

#define UCSZ0 1
#define UCSZ1 2
#define UCSZ2 2
#define UPM0  4
#define UPM1  5
#define USBS  3
#define UMSEL 6
#define UCPOL 0
#define RXEN  4
#define TXEN  3
#define UDRE  5
#define RXC   7
#define URSEL 7

typedef enum
{
	RECEIVE,
	TRANSMIT,
}uartstate_cnfg;

typedef enum
{
	baudrate_2400  = 25,
	baudrate_4800  = 12,
	baudrate_9600  = 6,
}uartbaudrate_cnfg;

typedef enum
{
	_5BIT = 0,
	_6BIT = 1,
	_7BIT = 2,
	_8BIT = 3,
	_9BIT = 7,
}uartdata_bits;

typedef enum
{
	DISABLED = 0,
	EVEN     = 2,
	ODD      = 3,
}uartparity_cnfg;

typedef enum
{
	_1STOPBIT = 0,
	_2STOPBIT = 1,
}uartstopbit_cnfg;

typedef enum
{
	Asynchronous_Operation = 0,
	Synchronous_Operation  = 1,
}uartoperation_cnfg;

typedef enum
{
	RISINGTX  = 0,
	FALLINGTX = 1,
}uartclock_cnfg;

void  uart_baudrate(uartbaudrate_cnfg);

void  uart_setframe(uartdata_bits,uartparity_cnfg,uartstopbit_cnfg);

void  uart_init(uartstate_cnfg,uartoperation_cnfg,uartclock_cnfg);

void  uart_transmit(uint8 data,uint8 databits);

uint8 uart_receive(uint8 databits);

#endif /* UART_H_ */