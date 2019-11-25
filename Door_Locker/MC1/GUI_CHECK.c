/*
 * GUI_CHECK.c
 *
 * Created: 10/26/2019 07:35:26 PM
 *  Author: Mohamed Hafez
 */ 

#include "GUI_CHECK.h"
#include <avr/delay.h>
#include<stdio.h>
#include <stdlib.h>


#define ARRAY_INDEX       5                            //size of passcode array
#define ASCII_TO_INTEGER  48                           //it's value used to convert ascii to int  
lcdcnfg_t mylcd       = {{D4,D5,D6,D7},C0,C1};         //lcd pins
keypadcnfg_t mykeypad = {{A0,A1,A2,A3},{A4,A5,A6,A7}}; //keypad pins

uint8 character;	                                   //auxlariy variable
uint8 buffer[ARRAY_INDEX];                             //buffer to store entered passcode
uint8 buffer_received[ARRAY_INDEX];                    //buffer to store received passcode from another micro
uint8 buffer_newPass[ARRAY_INDEX];                     //buffer to store transmitted passcode to another micro
uint8 buffer_index = 0;                                //buffer index

void sys_init(void)                                    // initialization function to initialize all devices 
{
	lcd_init(&mylcd);
	keypad_init(&mykeypad,door_system);
	uart_baudrate(baudrate_2400);
	uart_setframe(_8BIT,DISABLED,_1STOPBIT);
	uart_init(TRANSMIT,Asynchronous_Operation,RISINGTX);
	uart_init(RECEIVE,Asynchronous_Operation,RISINGTX);
	uart_cnfg();
}

void gui_write_passcode(void)                        //function used to write message to user on lcd 
{
	lcd_clear(&mylcd);
	lcd_setCursor(&mylcd,0,0);
	lcd_str(&mylcd,"enter passcode");
	lcd_setCursor(&mylcd,1,0);
}

void choose_mode(void)                              //function used to write message to user on lcd
{
	lcd_clear(&mylcd);
	lcd_setCursor(&mylcd,0,0);
	lcd_str(&mylcd,"+:change passcod");
	lcd_setCursor(&mylcd,1,0);
	lcd_str(&mylcd,"-:open door");
}

void  gui_write_new_Passcode(void)                //function used to write message to user on lcd
{
	lcd_clear(&mylcd);
	lcd_setCursor(&mylcd,0,0);
	lcd_str(&mylcd,"write new pass");
	lcd_setCursor(&mylcd,1,0);
}

void  gui_wrong_passcode(void)                   //function used to write message to user on lcd
{
	lcd_clear(&mylcd);
	lcd_setCursor(&mylcd,0,0);
	lcd_str(&mylcd,"wrong code");
	_delay_ms(1000);
	lcd_clear(&mylcd);
	lcd_setCursor(&mylcd,0,0);
	lcd_str(&mylcd,"rewrite code");
	lcd_setCursor(&mylcd,1,0);
}
void receive_code(void)                         //function used to receive code from another micro
{ 
	send_messg('t');                            // sending letter 't' to another micro to make it sending the stored actual passcode
	uint8 count = 0;
	for(count = 0;count < ARRAY_INDEX;count++)  //for loop to store received passcode
	{
		buffer_received[count] = uart_receive(_8BIT);
	}
}

uint8  check_code(void)                           //function to check the written code 
{
	receive_code();
	int count;
	for(count = 0;count <= ARRAY_INDEX - 1;count++)
	{
		if(buffer[count] != buffer_received[count])
		{
			return 0;                           //return 1 if the received code and the written code are not equal
			break;
		}
		else if(buffer[count] == buffer_received[count] && count < ARRAY_INDEX - 1)
		{
			continue;
		}
		else if(buffer[count] == buffer_received[count] && count == ARRAY_INDEX - 1)
		{
			return 1;                          //return 1 if the received code and the written code are equal
			break;
		}
	}
}

void  send_messg(uint8 messg)                 //function to send message to another micro
{
	uart_transmit(messg,_8BIT);
}

void send_newCode(uint8* buffer)             //function used to send new code to another micro
{
	send_messg('r');                          //sending letter 'r' to make another micro receive new passcode
	uint8 count;
	for(count = 0;count < ARRAY_INDEX;count++)
	{
		uart_transmit(buffer_newPass[count],_8BIT);
	}
}


void door_system(uint8 chr)                 //the fundamental function which passed to main keypad function
{
	if(chr != '+' && chr != '-')           //writing letter on lcd except '+','-' and store written passcode
	{
		if(character == '+')              //'+' used to write new code
		{
			if(buffer_index != ARRAY_INDEX)//if number of written less than 5 number which is the number of passcode
			{
				lcd_chr(&mylcd,chr);
				buffer_newPass[buffer_index] = chr - ASCII_TO_INTEGER;//convert character(ascii) to int
				buffer_index++;
			}
			
			if(buffer_index == ARRAY_INDEX)//if written letter equal 5
			{
				buffer_index = 0;           //clear index to recount
				send_newCode(buffer_newPass);//sending new code
				lcd_clear(&mylcd);
				lcd_setCursor(&mylcd,0,0);
				lcd_str(&mylcd,"code changed");
			}
		}
		else
		{
			if(buffer_index != ARRAY_INDEX) //if letter written is '+' or '-' to make user chosing mode
			{
				lcd_chr(&mylcd,'*');        //writing star on lcd
				buffer[buffer_index] = chr - ASCII_TO_INTEGER;//convert character to int
				buffer_index++;
			}
			if(buffer_index == ARRAY_INDEX)
			{
				if(check_code() == 1)     //check code to make decision 
				{
					choose_mode();
				}
				else
				{
					gui_wrong_passcode();
					buffer_index = 0;       //to make user writing passcode again
				}
			}
		}
	}
	else
	{
		if(chr == '+' && check_code() == 1)
		{
			gui_write_new_Passcode();      //writing new code
			buffer_index = 0;
			character = chr;              //storing '+' character to use it 
		}
		else if(chr == '-' && check_code() == 1)
		{
			send_messg('o');             //sending letter 'o' to opem door
			lcd_clear(&mylcd);
			lcd_setCursor(&mylcd,0,0);
			lcd_str(&mylcd,"door open");
		}
	}
}
