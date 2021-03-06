/*
 * CoOperativeScheduler.c
 *
 * Created: 8/30/2020 4:24:01 PM
 * Author : Mohamed_Hafez
 */ 

#include <stdlib.h>
#include <util/delay.h>
#include "common.h"
#include "platform_PCfg.h"
#include "GPIO.h"
#include "SCHEDULER_interface.h"


extern Queue_t ReadyQueue;
static uint8 Global_u8LedStatus;

void led_tog(void)
{
	if(Global_u8LedStatus == 0)
	{
		pin_write(A0, HIGH_LEVEL);
		Global_u8LedStatus = 1;
	}
	else

	{
		pin_write(A0, LOW_LEVEL);
		Global_u8LedStatus = 0;
	}
}

uint16 main(void)
{
	pin_dirc(A0, PIN_OUTPUT);
	SCHEDULER_voidInitScheduler(&ReadyQueue);
	SCHEDULER_uint16CreateTask(&led_tog,0,1000,0,NULL);
	SCHEDULER_voidStartScheduler();
	while (1)
	{
		SCHEDULER_voidDispatchTasks(&ReadyQueue);
	}
}


