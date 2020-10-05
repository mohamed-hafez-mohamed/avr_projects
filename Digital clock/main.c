/*
 * TFT.c
 *
 * Created: 9/27/2020 3:55:13 PM
 * Author : Mohamed_Hafez
 */ 

#define F_CPU 20000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "GPIO.h"
#include "TIMER0.h"
#include "SPI.h"
#include "TFT_interface.h"
#include "DWATCH_interface.h"

spi_cnfg myspi = {
	SPI_INTERRUPT_DISABLE,
	SPI_MSB_FIRST,
	SPI_MASTER_MODE,
	SAMPLE_RAISING_EDGE,
	SPI_FOSC_DIV4
};

extern mytimer;
int main(void)
{
	sei();
	pin_dirc(PINA0, PIN_OUTPUT);
	pin_dirc(PINA2, PIN_OUTPUT);
	timer0_init(&mytimer);
	spi_init(&myspi);
	HTFT_voidInit();
	HTFT_uint8FillColour(TFT_BLACK_COLOR);
	 HTFT_uint8DrawRectangle(0,130,0,160,TFT_BLUE_COLOR);
	 HTFT_uint8DrawFastHLine(0,130,20,TFT_BLUE_COLOR);
	 HTFT_uint8DrawFastHLine(0,130,40,TFT_BLUE_COLOR);
	 HTFT_uint8DrawFastHLine(0,130,60,TFT_RED_COLOR);
	oc_int(OCIE0_enable);
	
	while(1)
	{
		ADWATCH_voidDisplayDay();
		ADWATCH_voidDisplay();
		/*HTFT_uint8DrawChar(20,30,'A',TFT_YELLOW_COLOR,TFT_BLACK_COLOR,1);
		HTFT_uint8DrawRectangle(10,40,10,40,TFT_GREEN_COLOR);*/
	}
}

