/*
 * slave2.c
 *
 * Created: 2/15/2020 10:53:04 PM
 * Author : mah_h
 */ 

#include "SPI.h"
#include "UART.h"
#include <avr/delay.h>

spi_cnfg myspi = {
	SPI_INTERRUPT_DISABLE,
	SPI_MSB_FIRST,
	SPI_SLAVE_MODE,
	SAMPLE_RAISING_EDGE,
	SPI_FOSC_DIV4
};

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

uint8 num_bytes, count5, count6, flag_transmission3;
int main(void)
{
	uart_init(&myuart);
    spi_init(&myspi);
	num_bytes = spi_receive();
	uint8* ptr = (uint8*)malloc(num_bytes);
	flag_transmission3 = 1;
    while (1) 
    {
		if(flag_transmission3 == 1)
		{
			while(count5 < num_bytes)
			{
				ptr[count5] = spi_receive();
				count5++;
			}
			flag_transmission3 = 2;
		}
		
		if(flag_transmission3 == 2)
		{
			for(count6 = 0;count6 < num_bytes;count6++)
			{
				uart_transmit(ptr[count6], _8BIT);
			}
			flag_transmission3 = 3;
			free(ptr);
		}
    }
}

