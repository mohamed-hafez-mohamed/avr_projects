/*
 * MICROWAVE.c
 *
 * Created: 2/19/2020 10:22:49 AM
 * Author : mah_h
 */ 

#include "MICROWAVE.h"

static uint8 flag_choose_cancelmode; //this flag used to make the cancel state executd only once
extern keypadcnfg_t mykeypad;
int main(void)
{
    MOD_Init();
    while (1) 
    {
		keypad_mainFun(&mykeypad);
		if(MOD_GetSensorValue())
		{
			//if weight sensor and door sensor and start button are pressed turn on the microwave
			MOD_ManageSystem();
		}
		if(pin_read(CANCEL_BUTTON))                            
		//if cancel button pressed, check the heater
		{
			if(pin_read(HEATER) || flag_choose_cancelmode == 1)
			{
				//if cancel button pressed &the heater work,close microwave
				MOD_Cancel();
				MOD_CloseMicrowave();
				flag_choose_cancelmode = 1;
			}
			else
			{
				MOD_ClearTime(); //clear time id heater doesn't work
			}
		}
    }
}

