/*
 * SPI.c
 *
 * Created: 9/17/2019 10:33:23 ?
 *  Author: Mohamed Hafez
 */ 

#include "SPI.h"
#include "avr/interrupt.h"

#define DATA       READ_REG_8BIT((SPIBASE +SPDR_OFFSET))
static void(*ptr_func)(uint8); // the passed data in call_back work only for receiving


void spi_init(spi_cnfg* ptr)
{
	ACCESS_REG_8BIT((SPIBASE+SPCR_OFFSET))
	|=  (1 << SPE)
	|   (ptr->Interrupt     << SPIE) 
	|   (ptr->DataOrder     << DORD)
	|   (ptr->ModeSelect    << MSTR)  
	|   (ptr->TypeSelect    << CPHA) 
	|   (ptr->ClockSelect   << SPR0);
}

uint8 spi_exchangeData(uint8 data)
{  // check if slave it will be stucked here
	WRITE_REG_8BIT((SPIBASE+SPDR_OFFSET),data);
	while (IS_BIT_CLEAR((SPIBASE+SPSR_OFFSET),SPIF));
	return READ_REG_8BIT((SPIBASE + SPDR_OFFSET));
}

uint8 spi_receive()
{
	while (IS_BIT_CLEAR((SPIBASE+SPSR_OFFSET),SPIF));
	return READ_REG_8BIT((SPIBASE + SPDR_OFFSET));
}

void spi_transmit(uint8 data)
{
	WRITE_REG_8BIT((SPIBASE + SPDR_OFFSET),data);
	while (IS_BIT_CLEAR((SPIBASE+SPSR_OFFSET),SPIF));
}

void  spi_int(void(*ptr_Fun)(uint8))
{
	ptr_func = ptr_Fun;
	SET_BIT((SPIBASE + SPCR_OFFSET),SPIE);
}

ISR(SPI_STC_vect)
{ 
	(*ptr_func)(DATA);
}
