/*
 * I2C.h
 *
 * Created: 9/26/2019 09:07:50 ?
 *  Author: Mohamed Hafez
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/interrupt.h>
#include "i2c_cnfig.h"
#include "GPIO.h"


typedef enum
{
	I2C_TX,
	I2C_RX
}i2c_status;

void  i2c_init(uint8 myaddress);

void i2c_listen();

void  i2c_stop(void);

void  i2c_write(uint8 data);

uint8 i2c_read(void);

uint8 i2c_readWithNAck(void);

uint8 i2c_getStatus(void);

void i2c_int(void (*p_func)(void));

#endif /* I2C_H_ */