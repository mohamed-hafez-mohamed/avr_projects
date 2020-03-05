/*
 * ICS.c
 *
 * Created: 9/26/2019 04:36:07 ?
 * Author : Mohamed Hafez
 */ 

#include "I2C.h"
#include "UART.h"
#include <avr/delay.h>

UART_cnfg myuart =
{
	baudrate_2400,
	_8BIT,
	DISABLED_PARITY,
	_1STOPBIT,
	TRANCIVER,
	Asynchronous_Operation,
	RISINGTX,
};

volatile uint8 num_byte, count1, count2;
volatile uint8 flag_transmission1;
volatile uint8 data1[255];

void store_print(uint8 received)
{
	data1[count1] = received;
	count1++;
}
int main(void)
{
    i2c_init(0b0000001);
	uart_init(&myuart);
	sei();
    while (1) 
    {
		int_rx(&store_print);
		if(data1[count1 - 1] == '+' && flag_transmission1 == 0)
		{
			num_byte = count1 - 1;
			flag_transmission1 = 1;
		}
		if(flag_transmission1 == 1)
		{
			i2c_start();
			i2c_writeAddress(0b0000010, I2C_TX);
			i2c_write(num_byte);
			i2c_stop();
			flag_transmission1 = 2;
		}
		if(flag_transmission1 == 2)
		{
			i2c_start();
			i2c_writeAddress(0b0000010, I2C_TX);
			for(count2 = 0;count2 < num_byte;count2++)
			{
				i2c_write(data1[count2]);
				_delay_ms(1);
			}
			i2c_stop();
			flag_transmission1 = 3;
		}
    }
}