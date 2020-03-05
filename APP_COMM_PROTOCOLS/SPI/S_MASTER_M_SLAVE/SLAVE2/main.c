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
SPI_SLAVE_MODE,
SAMPLE_RAISING_EDGE,
SPI_FOSC_DIV4
};

uint8 x;
int main(void)
{
	spi_cnfg_Slave();
    spi_init(&myspi);
    while (1) 
    {
	   x = spi_receive();
    }
}