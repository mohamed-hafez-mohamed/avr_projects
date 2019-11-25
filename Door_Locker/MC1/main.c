/*
 * door_locker.c
 *
 * Created: 10/26/2019 02:37:04 PM
 * Author : Mohamed Hafez
 */ 

#include "GUI_CHECK.h"

extern lcdcnfg_t mylcd;
extern keypadcnfg_t mykeypad;

int main(void)
{
    sys_init();                     //function to initialize system
	gui_write_passcode();           //showing the frist message to user
    while (1) 
    {
		keypad_mainFun(&mykeypad); //the keypad main function used to show the clicked key
    }
}

