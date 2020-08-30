/*
 * GPIO.h
 *
 * Created: 8/26/2019 09:50:07 ?
 *  Author: Mohamed Hafez
 */ 


#ifndef GPIO_H_
#define GPIO_H_


#include "common.h"
#include "platform_PCfg.h"

//ENUM FOR PORTS' NAMES
typedef enum
{
	A = Base_A,
	B = Base_B,
	C = Base_C,
	D = Base_D,
}port_t;

//ENUM FOR PINS' NAMES
typedef enum
{
	A0  ,
	A1	,
	A2	,
	A3	,
	A4	,
	A5	,
	A6	,
	A7	,

	B0  ,
	B1  ,
	B2	,
	B3	,
	B4	,
	B5	,
	B6	,
	B7	,

	C0	,
	C1	,
	C2	,
	C3	,
	C4	,
	C5	,
	C6	,
	C7	,

	D0	,
	D1	,
	D2	,
	D3	,
	D4	,
	D5	,
	D6	,
	D7	,
}pin_t;

//ENUM FOR PORTS' DIRECION
typedef enum
{
	PORT_INPUT  = 0x00,
	PORT_OUTPUT = 0xff,
}portDirc_t;

//ENUM FOR PORTS' DIRECION
typedef enum
{
	PIN_INPUT,
	PIN_OUTPUT,
}pinDirc_t;

////ENUM FOR PINS' LOGIC STATE
typedef enum
{
	LOW_LEVEL,
	HIGH_LEVEL,
}logic_status_t;

//STRUCTURE FOR BITFIELD
typedef struct
{
	volatile uint16 b0 : 1;
	volatile uint16 b1 : 1;
	volatile uint16 b2 : 1;
	volatile uint16 b3 : 1;
	volatile uint16 b4 : 1;
	volatile uint16 b5 : 1;
	volatile uint16 b6 : 1;
	volatile uint16 b7 : 1;
}bit_t;

//PORTS' FUNCTIONS
void   port_dirc(port_t port,portDirc_t dirc);                                           //SEPCIFY PORT DIRECTION

uint16  port_read(port_t port);                                                           //READ FROM PORT

void   port_write(port_t port ,uint16 val);                                               //WRITE TO PORT

//PINS' FUNCTIONS
void   pin_dirc(uint16 pin,pinDirc_t dirc);                                   //SEPCIFY PIN DIRECTION

void   pins_dirc(uint16 pin_start, uint16 pin_end, uint16 dirc);               //SEPCIFY PINS DIRECTION

bool_t pin_read(uint16 pin);                                                  //READ FROM PIN

void   pin_write(uint16 pin,logic_status_t logic);                           //WRITE TO PIN

void set_pins(uint16 pin_start, uint16 pin_end);                               //SET GROUP OD PINS

void clear_pins(uint16 pin_start, uint16 pin_end);                             //CLEAR GROUP OD PINS

void uart_cnfg(void);

void spi_cnfg_master(void);

void spi_cnfg_Slave(void);
#endif /* GPIO_H_ */