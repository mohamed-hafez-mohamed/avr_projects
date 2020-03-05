/*
 * MICROWAVE.h
 *
 * Created: 2/19/2020 10:40:42 AM
 *  Author: mah_h
 */ 


#ifndef MICROWAVE_H_
#define MICROWAVE_H_


#include "GPIO.h"
#include "TIMER0.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "ADC.h"
#include "PWM.h" 
#include <avr/interrupt.h>
#include <avr/delay.h>
#define ARRAY_INDEX       2                            //size of passcode array
#define ASCII_TO_INTEGER  48                           //it's value used to convert ascii to int
#define VREF              5.0
#define MAX_LEVEL_NUM     1023.0
#define MVOLTTOVOLT       100                             //used in the temperatue eq to convert milli volt to volt
#define SPEED             255                             //motor speed
#define MINUTE            60
#define HEATER            A7
#define IN1               B1
#define IN2               B2
#define OC0               B3
#define START_BUTTON      B4
#define WEIGHT_SENSOR     B5
#define DOOR_SENSOR       B6
#define CANCEL_BUTTON     B7
#define RELAY             D6
#define BUZZER            D7

void MOD_Init(void);

void MOD_PrintWelcome(void);

void MOD_PrintUserMessage(void);

void MOD_PrintCurrentTime(void);

void MOD_GetEnteredTime(uint8 chr);

uint8 MOD_GetSensorValue(void);

void MOD_TimeUpdateMinute(void);

void MOD_OpenFan(void);

void MOD_CloseFan(void);

void MOD_OpenMicrowave(void);

void MOD_CloseMicrowave(void);

void MOD_Cancel(void);

void MOD_ManageSystem(void);

void MOD_ClearTime(void);

void MOD_TimeFinish(void);

void MOD_PrintMsgTemp(void);

void MOD_PrintTemperature(uint16 adc_volt);


#endif /* MICROWAVE_H_ */