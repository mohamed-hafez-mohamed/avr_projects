/*
 * SPI_S.c
 *
 * Created: 9/18/2019 10:51:42 ?
 * Author : mah_h
 */ 

#include "SPI.h"
#include <avr/delay.h>
spi_cnfg myspi = {
SPI_INTERRUPT_DISABLE, 
SPI_MSB_FIRST,
SPI_MASTER_MODE,
SAMPLE_RAISING_EDGE,
SPI_FOSC_DIV4
};

int main(void)
{
	spi_cnfg_master();
    spi_init(&myspi);
    while (1) 
    {
		pin_write(B3,LOW_LEVEL);
		pin_write(B4,HIGH_LEVEL);
		spi_transmit(8);
		/*uint8 count;
		for(count = 0;count < 5;count++)
		{
			spi_transmit(data[count]);
			_delay_ms(10);
		}*/
    }
}