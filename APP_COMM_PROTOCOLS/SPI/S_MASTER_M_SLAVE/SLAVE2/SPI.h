/*
 * SPI.h
 *
 * Created: 9/17/2019 10:33:00 ?
 *  Author: mah_h
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "spi_cnfg.h"
#include "GPIO.h"

typedef enum
{
	SPI_INTERRUPT_DISABLE,
	SPI_INTERRUPT_ENABLE
} Spi_InterruptType;

typedef enum
{
	SPI_MSB_FIRST,
	SPI_LSB_FIRST
} Spi_DataOrderType;

typedef enum
{
	SPI_SLAVE_MODE,
	SPI_MASTER_MODE
} Spi_ModeSelectType;

typedef enum
{
	SAMPLE_RAISING_EDGE,
	SETUP_RAISING_EDGE,
	SAMPLE_FALLING_EDGE,
	SETUP_FALLING_EDGE
} Spi_Type;

typedef enum
{
	SPI_FOSC_DIV4,
	SPI_FOSC_DIV16,
	SPI_FOSC_DIV64,
	SPI_FOSC_DIV128,
} Spi_ClockSelectType;

typedef struct
{
	Spi_InterruptType		Interrupt;
	Spi_DataOrderType		DataOrder;
	Spi_ModeSelectType		ModeSelect;
	Spi_Type                TypeSelect;
	Spi_ClockSelectType		ClockSelect;
} spi_cnfg;

void  spi_init(spi_cnfg* ptr);

uint8 spi_exchangeData(uint8 data);

uint8 spi_receive();

void  spi_transmit(uint8 data);

void  spi_int(void(*ptr_Fun)(uint8));






#endif /* SPI_H_ */