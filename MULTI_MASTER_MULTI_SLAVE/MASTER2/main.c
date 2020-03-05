/*
 * ICS.c
 *
 * Created: 9/26/2019 04:36:07 ?
 * Author : Mohamed Hafez
 */ 

#include "I2C.h"
#include <avr/delay.h>

uint8 y;
int main(void)
{
    i2c_init(0b0000010);
	pin_dirc(B0,PIN_INPUT);
	pin_dirc(B3,PIN_OUTPUT);
    while (1) 
    {
		if(pin_read(B0) == 1)
		{
			i2c_start();
			i2c_writeAddress(0b0000100, I2C_RX);
			if(i2c_getStatus() == I2C_MR_SLA_R_ACK)
			{
				y = i2c_readWithNAck();
			}
			i2c_stop();
		}
		if(y == 't')
		{
			pin_write(B3,HIGH_LEVEL);
		}
    }
}