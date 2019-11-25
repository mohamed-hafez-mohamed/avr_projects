/*
 * door_system.h
 *
 * Created: 10/28/2019 11:05:14 ص
 *  Author: Mohamed Hafez
 */ 


#ifndef DOOR_SYSTEM_H_
#define DOOR_SYSTEM_H_

#include "UART.h"
#include "PWM.h"
#include "avr/delay.h"

void sys_init(void);        //function to initialize devices

void handle_received(void); //receive messages from another micro and make decessions

void open_door(void);       //turn on door

#endif /* DOOR_SYSTEM_H_ */