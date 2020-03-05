/*
 * ICS.c
 *
 * Created: 9/26/2019 04:36:07 ?
 * Author : Mohamed Hafez
 */ 

#include "I2C.h"
#include <avr/delay.h>
uint8 d;
int main(void)
{
	i2c_init(0b0000100);
	pin_dirc(B0,PIN_OUTPUT);
    while (1) 
    {
		i2c_listen();
		if(i2c_getStatus() == I2C_ST_SLA_R_ACK)
		{
			i2c_write('t');
		}
    }
}