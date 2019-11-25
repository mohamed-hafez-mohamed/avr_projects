/*
 * GUI_CHECK.h
 *
 * Created: 10/26/2019 07:34:57 PM
 *  Author: Mohamed Hafez
 */ 


#ifndef GUI_CHECK_H_
#define GUI_CHECK_H_

#include "LCD.h"
#include "KEYPAD.h"
#include "UART.h"
#include "GPIO.h"

#define DEFAULT_PASSCODE 12345

void  sys_init(void);              // initialization function to initialize all devices

void  door_system(uint8 chr);      //the fundamental function which passed to main keypad function

void  gui_write_passcode(void);    //function used to write message to user on lcd

void  choose_mode(void);          //function used to write message to user on lcd

void  gui_write_new_Passcode(void);  //function used to write message to user on lcd

void  gui_wrong_passcode(void);     //function used to write message to user on lcd

void  receive_code(void);           //function used to receive code from another micro

uint8  check_code(void);            //function to check the written code

void  send_newCode(uint8* buffer);  //function used to send new code to another micro

void  send_messg(uint8 messg);      //function to send message to another micro




#endif /* GUI_CHECK_H_ */