/*
 * ICS.c
 *
 * Created: 9/26/2019 04:36:07 ?
 * Author : Mohamed Hafez
 */ 

#include "I2C.h"
#include "SPI.h"
#include <avr/delay.h>
#include <stdlib.h>

spi_cnfg myspi = {
	SPI_INTERRUPT_DISABLE,
	SPI_MSB_FIRST,
	SPI_MASTER_MODE,
	SAMPLE_RAISING_EDGE,
	SPI_FOSC_DIV4
};

volatile uint8 count3, count4, bytes_number;
volatile uint8 flag_transmission2;
int main(void)
{
	i2c_init(0b0000010);
	spi_init(&myspi);
	i2c_listen();
	bytes_number = i2c_readWithNAck();
	uint8* ptr = (uint8*)malloc(bytes_number);
	flag_transmission2 = 1;
    while (1) 
    {
		if(flag_transmission2 == 1)
		{
			i2c_listen();
			uint8 i = i2c_read();
			while(count3 < bytes_number)
			{
				ptr[count3] = i2c_read();
				count3++;
			}
			flag_transmission2 = 2;
		}
		if(flag_transmission2 == 2)
		{
			spi_transmit(bytes_number);
			for(count4 = 0;count4 < bytes_number;count4++)
			{
				spi_transmit(ptr[count4]);
				_delay_ms(1);
			}
			flag_transmission2 = 3;
			free(ptr);
		}
    }
}