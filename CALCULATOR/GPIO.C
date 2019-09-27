/*
 * GPIO.c
 *
 * Created: 8/26/2019 09:51:13 ص
 *  Author: Mohamed Hafez
 */ 

#include "GPIO.h"

//PORTS' FUNCTIONS
void port_dirc(port_t port,portDirc_t dirc)                                                  //SEPCIFY PORT DIRECTION
{
	ACCESS_REG_8BIT((port + DIRC_OFFEST)) = dirc;
}

uint8 port_read(port_t port)                                                                 //READ FROM PORT
{
	return ACCESS_REG_8BIT((port + INTPUT_OFFEST));
}

void port_write(port_t port ,uint8 val)                                                       //WRITE TO PORT
{
	ACCESS_REG_8BIT((port + OUTPUT_OFFEST)) = val;
}


void pin_dirc(uint8 pin,pinDirc_t dirc)                                           //SEPCIFY PIN DIRECTION
{
	port_t port;
	if(pin <= END_PORTA)
	{
		port = A;
	}
	else if(pin >= START_PORTB && pin <= END_PORTB)
	{
		pin -= CNFG_PINS_PORTB;
		port = B;
	}
	else if(pin >= START_PORTC && pin <= END_PORTC)
	{
		pin -= CNFG_PINS_PORTC;
		port = C;
	}
	else
	{
		pin -= CNFG_PINS_PORTD;
		port = D;
	}
	switch(dirc)
	{
		case PIN_INPUT :
		CLEAR_BIT((port + DIRC_OFFEST),pin);
		break;
		case PIN_OUTPUT :
		SET_BIT((port + DIRC_OFFEST),pin);
		break;
	}
}

void pins_dirc(uint8 pin_start, uint8 pin_end, uint8 dirc)                             //SEPCIFY PINS DIRECTION
{
	port_t port;
	if(pin_start <= END_PORTA)
	{
		port = A;
	}
	else if(pin_start >= START_PORTB && pin_start <= END_PORTB)
	{
		pin_start -= CNFG_PINS_PORTB;
		pin_end   -= CNFG_PINS_PORTB;
		port = B;
	}
	else if(pin_start >= START_PORTC && pin_start < END_PORTC)
	{
		pin_start -= CNFG_PINS_PORTC;
		pin_end   -= CNFG_PINS_PORTC;
		port = C;
	}
	else
	{
		pin_start -= CNFG_PINS_PORTD;
		pin_end   -= CNFG_PINS_PORTD;
		port = D;
	}
	uint8 i;
	switch(dirc)
	{
		case PIN_INPUT :
		for(i = pin_start;i <= pin_end;i++)
		{
			CLEAR_BIT((port + DIRC_OFFEST),i);
		}
		break;
		case PIN_OUTPUT :
		for(i = pin_start;i <= pin_end;i++)
		{
			SET_BIT((port + DIRC_OFFEST),i);
		}
		
		break;
	}
}

bool_t pin_read(uint8 pin)                                                             //READ FROM PIN
{
	port_t port;
	if(pin <= END_PORTA)
	{
		port = A;
	}
	else if(pin >= START_PORTB && pin <= END_PORTB)
	{
		pin -= CNFG_PINS_PORTB;
		port = B;
	}
	else if(pin >= START_PORTC && pin <= END_PORTC)
	{
		pin -= CNFG_PINS_PORTC;
		port = C;
	}
	else
	{
		pin -= CNFG_PINS_PORTD;
		port = D;
	}
	return (IS_BIT_SET((port + INTPUT_OFFEST),pin));
}

void pin_write(uint8 pin,logic_status_t logic)                                        //WRITE TO PIN
{
	port_t port;
	if(pin <= END_PORTA)
	{
		port = A;
	}
	else if(pin >= START_PORTB && pin <= END_PORTB)
	{
		pin -= CNFG_PINS_PORTB;
		port = B;
	}
	else if(pin >= START_PORTC && pin <= END_PORTC)
	{
		pin -= CNFG_PINS_PORTC;
		port = C;
	}
	else
	{
		pin -= CNFG_PINS_PORTD;
		port = D;
	}
	switch(logic)
	{
		case HIGH_LEVEL :
		SET_BIT((port + OUTPUT_OFFEST),pin);
		break;
		case LOW_LEVEL :
		CLEAR_BIT((port + OUTPUT_OFFEST),pin);
		break;
	}
}

void set_pins(uint8 pin_start, uint8 pin_end)
{
	port_t port;
	if(pin_start <= END_PORTA)
	{
		port = A;
	}
	else if(pin_start >= START_PORTB && pin_start <= END_PORTB)
	{
		pin_start -= CNFG_PINS_PORTB;
		pin_end   -= CNFG_PINS_PORTB;
		port = B;
	}
	else if(pin_start >= START_PORTC && pin_start < END_PORTC)
	{
		pin_start -= CNFG_PINS_PORTC;
		pin_end   -= CNFG_PINS_PORTC;
		port = C;
	}
	else
	{
		pin_start -= CNFG_PINS_PORTD;
		pin_end   -= CNFG_PINS_PORTD;
		port = D;
	}
	uint8 i;
	for(i = pin_start;i <= pin_end;i++)
	{
		SET_BIT((port + OUTPUT_OFFEST),i);
	}
}

void clear_pins(uint8 pin_start, uint8 pin_end)
{
	port_t port;
	if(pin_start <= END_PORTA)
	{
		port = A;
	}
	else if(pin_start >= START_PORTB && pin_start <= END_PORTB)
	{
		pin_start -= CNFG_PINS_PORTB;
		pin_end   -= CNFG_PINS_PORTB;
		port = B;
	}
	else if(pin_start >= START_PORTC && pin_start < END_PORTC)
	{
		pin_start -= CNFG_PINS_PORTC;
		pin_end   -= CNFG_PINS_PORTC;
		port = C;
	}
	else
	{
		pin_start -= CNFG_PINS_PORTD;
		pin_end   -= CNFG_PINS_PORTD;
		port = D;
	}
	uint8 i;
	for(i = pin_start;i <= pin_end;i++)
	{
		CLEAR_BIT((port + OUTPUT_OFFEST),i);
	}
}

void uart_cnfg(void)
{
	pin_dirc(D0,PIN_INPUT);
	pin_dirc(D1,PIN_OUTPUT);
}

void spi_cnfg_master(void)
{
	
	pin_dirc(B4,PIN_OUTPUT);       //SS
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
