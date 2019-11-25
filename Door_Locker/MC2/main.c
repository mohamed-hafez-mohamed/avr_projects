/*
 * door_locker.c
 *
 * Created: 10/26/2019 02:47:29 PM
 * Author : Mohamed Hafez
 */ 

#include <util/delay.h>
#include "GPIO.h"
#include "external_eeprom.h"
#define F_CPU 8000000UL

int main(void)
{
	sys_init();
    while (1) 
    {
		handle_received();
	}
}

