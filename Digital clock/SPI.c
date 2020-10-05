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
	if(ptr->ModeSelect == SPI_MASTER_MODE)
	{
		spi_cnfg_master();
	}
	else
	{
		spi_cnfg_Slave();
	}
	ACCESS_REG_8BIT((SPIBASE+SPCR_OFFSET))
	|=  (1 << SPE)
	|   (ptr->Interrupt     << SPIE)
	|   (ptr->DataOrder     << DORD)
	|   (ptr->ModeSelect    << MSTR)
	|   (ptr->TypeSelect    << CPHA)
	|   (ptr->ClockSelect   << SPR0);
}

uint8 spi_exchangeData(uint8 data)
{  
	pin_write(SPI_SLAVE_1, LOW_LEVEL);
	// check if slave it will be stucked here
	WRITE_REG_8BIT((SPIBASE+SPDR_OFFSET),data);
	while (IS_BIT_CLEAR((SPIBASE+SPSR_OFFSET),SPIF));
	pin_write(SPI_SLAVE_1, HIGH_LEVEL);
	return READ_REG_8BIT((SPIBASE + SPDR_OFFSET));
}

uint8 spi_receive()
{
	pin_write(SPI_SLAVE_1, LOW_LEVEL);
	while (IS_BIT_CLEAR((SPIBASE+SPSR_OFFSET),SPIF));
	pin_write(SPI_SLAVE_1, HIGH_LEVEL);
	return READ_REG_8BIT((SPIBASE + SPDR_OFFSET));
}

void spi_transmit(uint8 data)
{
	pin_write(SPI_SLAVE_1, LOW_LEVEL);
	WRITE_REG_8BIT((SPIBASE + SPDR_OFFSET),data);
	while (IS_BIT_CLEAR((SPIBASE+SPSR_OFFSET),SPIF));
	pin_write(SPI_SLAVE_1, HIGH_LEVEL);
}

void  spi_int(void(*ptr_Fun)(uint8))
{
	ptr_func = ptr_Fun;
	SET_BIT((SPIBASE + SPCR_OFFSET),SPIE);
}

ISR(SPI_STC_vect)
{ 
	sei();
	(*ptr_func)(DATA);
}

void spi_cnfg_master(void)
{
	pin_dirc(SPI_SLAVE_1,PIN_OUTPUT);       //to select slave
	pin_dirc(B5,PIN_OUTPUT);       //MOSi
	pin_dirc(B6,PIN_INPUT);	       //MISO
	pin_dirc(B7,PIN_OUTPUT);	   //SCK
}

void spi_cnfg_Slave(void)
{
	pin_dirc(B4,PIN_INPUT);       //SS
	pin_dirc(B5,PIN_INPUT);       //MOSi
	pin_dirc(B6,PIN_OUTPUT);	  //MISO
	pin_dirc(B7,PIN_INPUT);       //sck
}