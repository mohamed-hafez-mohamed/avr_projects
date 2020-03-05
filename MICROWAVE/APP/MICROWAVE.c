/*
 * MICROWAVE.c
 *
 * Created: 2/19/2020 10:41:04 AM
 *  Author: mah_h
 */ 

#include "MICROWAVE.h"


lcdcnfg_t mylcd       = {{D0,D1,D2,D3},D4,D5};         //lcd pins
keypadcnfg_t mykeypad = {{C0,C1,C2,C3},{C4,C5,C6,C7}}; //keypad pins
timer0_cnfg mytimer = {EXT_CLK_FALLING, CTC, Toggle_on_com};
ADC_cnfg myadc  ={AVCC, CLK_ADC_DIV_128, FREE_RUNNING_MODE};

uint8 buffer_index;                                                   //buffer index
uint8 buffer[ARRAY_INDEX];                                           //buffer to store entered time
volatile uint8 entered_time, time_second, time_minute, temperature; //this variables to store the entered time,sec,min,temp
volatile uint8 flag_finishoccure_once, flag_temperatue_once, flag_writeagain_CM, flag_heating;

//initialization funcation
void MOD_Init(void)
{
	//determine the pins' directions'
	pin_dirc(START_BUTTON,  PIN_INPUT);
	pin_dirc(WEIGHT_SENSOR, PIN_INPUT);
	pin_dirc(DOOR_SENSOR,   PIN_INPUT);
	pin_dirc(CANCEL_BUTTON, PIN_INPUT);
	pin_dirc(HEATER,        PIN_OUTPUT);
	pin_dirc(IN1,           PIN_OUTPUT);
	pin_dirc(IN2,           PIN_OUTPUT);
	pin_dirc(RELAY,         PIN_OUTPUT);
	pin_dirc(BUZZER,        PIN_OUTPUT);
	//some functions executed only once after turning on system
	timer0_init(&mytimer);
	lcd_init(&mylcd);
	keypad_init(&mykeypad,&MOD_GetEnteredTime);
	adc_init(&myadc);
	MOD_PrintWelcome();
	MOD_PrintMsgTemp();
	MOD_PrintCurrentTime();
	MOD_PrintUserMessage();
	sei();                              //to enable global interrupt 
}

//welcome message
void MOD_PrintWelcome(void)
{
	lcd_setCursor(&mylcd,1,4);
	lcd_str(&mylcd,"WELCOME");
	_delay_ms(1000);
	lcd_clear(&mylcd);
}

//function used to print message to user on lcd to tell him enter time
void MOD_PrintUserMessage(void)                        
{
	lcd_setCursor(&mylcd,0,12);
	lcd_chr(&mylcd,'M');
	lcd_setCursor(&mylcd,0,0);
	lcd_str(&mylcd,"set time:");
	lcd_setCursor(&mylcd,0,9);
}

//function used to print current time to user on lcd
void MOD_PrintCurrentTime(void)                        
{
	lcd_setCursor(&mylcd,1,0);
	lcd_str(&mylcd,"cur time:");
	lcd_setCursor(&mylcd,1,11);
	lcd_chr(&mylcd,':');
	lcd_setCursor(&mylcd,1,12);
	lcd_num(&mylcd,0);
	lcd_setCursor(&mylcd,1,13);
	lcd_num(&mylcd,0);
	lcd_setCursor(&mylcd,1,9);
	lcd_num(&mylcd,0);
	lcd_setCursor(&mylcd,1,10);
	lcd_num(&mylcd,0);
}

//function used to print current temperature to user on lcd
void MOD_PrintMsgTemp(void)
{
	lcd_setCursor(&mylcd,2,0);
	lcd_str(&mylcd,"temperature:");
	lcd_setCursor(&mylcd,2,15);
	lcd_chr(&mylcd,'C');
	lcd_setCursor(&mylcd,2,13);
	lcd_num(&mylcd,temperature);
}

//function used to print message after finishing heating
void MOD_TimeFinish(void)                        
{
	uint8 i;
	lcd_setCursor(&mylcd,1,12);
	lcd_num(&mylcd,0);
	lcd_setCursor(&mylcd,1,13);
	lcd_num(&mylcd,0);
	lcd_setCursor(&mylcd,1,9);
	lcd_num(&mylcd,0);
	lcd_setCursor(&mylcd,1,10);
	lcd_num(&mylcd,0);
	lcd_setCursor(&mylcd,3,0);
	//to clear raw3
	for(i = 12; i<= 15;i++)
	{
		lcd_setCursor(&mylcd,3,i);
		lcd_chr(&mylcd,'\0');
	}
	lcd_setCursor(&mylcd,3,0);
	lcd_str(&mylcd,"Delicious Meal");
}

//function print cancel message
void MOD_Cancel(void)
{
	flag_heating = 0;
	lcd_setCursor(&mylcd,3,0);
	lcd_str(&mylcd,"Heating Canceled");
	
}

//function used to calculate the entered time by user
void MOD_GetEnteredTime(uint8 chr)
{
	if(chr != '=' || flag_writeagain_CM == 0)
	{
		lcd_chr(&mylcd,chr);
		buffer[buffer_index] = chr - ASCII_TO_INTEGER;
		buffer_index++;
		flag_writeagain_CM = 1;
	}
	else if(chr == '=')
	{
		entered_time = buffer[0] * 10 + buffer[1] * 1;
	}
}

//function return sensor's status
uint8 MOD_GetSensorValue(void)
{
	if(pin_read(START_BUTTON) && pin_read(WEIGHT_SENSOR) && pin_read(DOOR_SENSOR))
	{
		return 1;
	}
}

//function used to update minute and print it
void MOD_TimeUpdateMinute(void)                       
{
	if(time_second == MINUTE)
	{
		time_minute++;
		if(time_minute <= 9)
		{
			lcd_setCursor(&mylcd,1,10);
			lcd_num(&mylcd,time_minute);
		}
		else
		{
			lcd_setCursor(&mylcd,1,9);
			lcd_num(&mylcd,time_minute);
		}
		time_second = 0;
		lcd_setCursor(&mylcd,1,12);
		lcd_num(&mylcd,0);
		lcd_setCursor(&mylcd,1,13);
		lcd_num(&mylcd,0);
	}
}

//function used to open microwave(fan,lamp,heater)
void MOD_OpenMicrowave(void)
{
	oc_int(OCIE0_enable);
	MOD_OpenFan();
	pin_write(HEATER,HIGH_LEVEL);
	pin_write(RELAY, HIGH_LEVEL);
	pin_write(BUZZER, LOW_LEVEL);
}

//function used to close microwave(fan,lamp,heater) and open buzeer for alert
void MOD_CloseMicrowave(void)
{
	oc_int(OCIE0_disable);
	MOD_CloseFan();
	pin_write(HEATER, LOW_LEVEL);
	pin_write(RELAY,  LOW_LEVEL);
	pin_write(BUZZER,HIGH_LEVEL);
	_delay_ms(200);
	pin_write(BUZZER,LOW_LEVEL);
}

//this th mother function that executed if conditions achieved
void MOD_ManageSystem(void)
{
    adc_int(ADC_ENABLE,CHANNEL0, &MOD_PrintTemperature);
	if(time_minute == entered_time && flag_finishoccure_once == 0)
	{
		MOD_TimeFinish();
		MOD_CloseMicrowave();
		flag_finishoccure_once = 1;
	}
	else if(time_minute != entered_time)
	{
		MOD_TimeUpdateMinute();
		MOD_OpenMicrowave();
		if(flag_heating == 0)
		{
			uint8 i;
			for(i = 7; i<= 15;i++)
			{
				lcd_setCursor(&mylcd,3,i);
				lcd_chr(&mylcd,'\0');
			}
			lcd_setCursor(&mylcd,3,0);
			lcd_str(&mylcd,"HEATING");
			 flag_heating = 1;
		}
	}
}

//clear time and print cancel message
void MOD_ClearTime(void)
{
	flag_writeagain_CM    = 0;
	time_second           = 0;
	time_minute           = 0;
	entered_time          = 0;
	buffer_index          = 0;
	lcd_setCursor(&mylcd,0,9);
	lcd_chr(&mylcd,'\0');
	lcd_setCursor(&mylcd,0,10);
	lcd_chr(&mylcd,'\0');
	lcd_setCursor(&mylcd,0,9);
	lcd_setCursor(&mylcd,3,0);
	lcd_str(&mylcd,"Time Canceled");
	lcd_setCursor(&mylcd,0,9);
}

//turn on fan
void MOD_OpenFan(void)                                
{
	pin_write(IN1,HIGH_LEVEL);
	pin_write(IN2,LOW_LEVEL);
	pwm_write(OC0,SPEED);
}

//turn off fan
void MOD_CloseFan(void)
{
	pin_write(IN1,LOW_LEVEL);
	pin_write(IN2,LOW_LEVEL);
	pwm_write(OC0,0);
}

//print temperature
void MOD_PrintTemperature(uint16 adc_volt)
{
	temperature = adc_volt * (VREF * MVOLTTOVOLT / MAX_LEVEL_NUM);
	if(flag_temperatue_once == temperature)
	{
		//no code executed if the temperature doesn't change
	}
	else
	{
		lcd_setCursor(&mylcd,2,13);
		lcd_num(&mylcd,temperature);
		lcd_setCursor(&mylcd,2,15);
		lcd_chr(&mylcd,'C');
		flag_temperatue_once = temperature; //this statement used to reprint temp if it changed
	}
}

ISR(TIMER0_COMP_vect)
{
	sei();
	time_second++;
	if(time_second <= 9)
	{
		lcd_setCursor(&mylcd,1,13);
		lcd_num(&mylcd,time_second);
	}
	else
	{
		lcd_setCursor(&mylcd,1,12);
		lcd_num(&mylcd,time_second);
	}
}