/*
 * system_door.c
 *
 * Created: 10/28/2019 11:06:08 ص
 *  Author: Mohamed Hafez
 */ 

#include "door_system.h"

#define ARRAY_INDEX  5                                //size of passcode array
#define SPEED        255                             //motor speed
#define FRIST_ADDRESS_EEPROM 0x0000
uint8 received_messg;                               //variable used to store the received letter
uint8 received_code;                                //variable used to store the received code from eeprom
uint8 buffer2[ARRAY_INDEX];                         //array to store received code from eeprom
uint8 buffer_index2 = 0;                            //array index

void sys_init(void)                                 //function to initialize devices
{
	uart_baudrate(baudrate_2400);
	uart_setframe(_8BIT,DISABLED,_1STOPBIT);
	uart_init(TRANSMIT,Asynchronous_Operation,RISINGTX);
	uart_init(RECEIVE,Asynchronous_Operation,RISINGTX);
	uart_cnfg();
	pwm0_init();
	EEPROM_init();
	pin_dirc(D4,PIN_OUTPUT);
	pin_dirc(D5,PIN_OUTPUT);
	pin_dirc(B0,PIN_OUTPUT);
}

void open_door(void)                                //turn on door
{
	pin_write(B0,HIGH_LEVEL);
	pin_write(D4,HIGH_LEVEL);                      
	pin_write(D5,LOW_LEVEL);
	pwm_write(B3,SPEED);
	_delay_ms(1500);
	pin_write(B0,LOW_LEVEL);
	pin_write(D4,LOW_LEVEL);
	pin_write(D5,HIGH_LEVEL);
	pwm_write(B3,255);
	_delay_ms(1500);
	pin_write(D4,LOW_LEVEL);
	pin_write(D5,LOW_LEVEL);
	pwm_write(B3,0);
}

void handle_received(void)
{
	uint8 count;
	received_messg = uart_receive(_8BIT);          //receive a message from another micro and make decessions
	if(received_messg == 'o')                      //if received message is 'o' 
	{
		open_door();
	}
	 if(received_messg == 't')                     //transmit passcode stored in eeprom to another micro
	 {
		 uint8 count;
		 for(count = 0;count < ARRAY_INDEX;count++)
		 {
			 EEPROM_readByte((FRIST_ADDRESS_EEPROM + count),&received_code); //read paascode from eeprom
			 _delay_ms(10);
			 buffer2[count] = received_code;                                //storing code in buffer
			 uart_transmit(buffer2[count],_8BIT);
		 }
	 }
	 
	 if(received_messg == 'r')
	 {
		 uint8 count;
		 for(count = 0;count < ARRAY_INDEX;count++)
		 {
			 buffer2[count] = uart_receive(_8BIT);
			 EEPROM_writeByte((FRIST_ADDRESS_EEPROM + count),buffer2[count]); //sending passcode to another micro
			 _delay_ms(10);
		 }
	 }
}