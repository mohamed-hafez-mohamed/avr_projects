/*
 * ADC.h
 *
 * Created: 9/3/2019 09:23:43 ?
 *  Author: mah_h
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/interrupt.h>
#include "GPIO.h"

#define CLEAR_REGISTER 0x00
#define CLEAR_MUX_BITS 0x1F
//REGISTERS' ADRESSES
#define ADCBASE        0x24
#define LOW_OFFSET     0x00
#define HIGH_OFFSET    0x01
#define CSRA_OFFSET    0x02
#define MUX_OFFSET     0x03
#define SFIOR_OFFSET   0x2C
//BITS NAMES
#define MUX0  0
#define REFS0 6
#define ADPS0 0
#define ADIE  3
#define ADIF  4
#define ADATE 5
#define ADSC  6
#define ADEN  7
#define ADTS0 5

typedef enum
{
	AREF_OFF      = 0,
	AVCC          = 1,
	INTERNAL_VREF = 3,
}vref_selectType;

typedef enum
{
	FREE_RUNNING_MODE    = 0,
	ANALOG_COMPARTOR     = 1,
	EXTERNAL_INITERRUPT0 = 2,
	COMPARE_MATCH_TIMER0 = 3,
	OVERFLOW_TIMER0      = 4,
	COMPARE_MATCH_TIMER1 = 5,
	OVERFLOW_TIMER1      = 6,
}mode_selectType;

typedef enum
{
	CLK_ADC_DIV_2   = 0,
	CLK_ADC_DIV_4   = 2,
	CLK_ADC_DIV_8   = 3,
	CLK_ADC_DIV_16  = 4,
	CLK_ADC_DIV_32  = 5,
	CLK_ADC_DIV_64  = 6,
	CLK_ADC_DIV_128 = 7,
}clk_select;

typedef enum
{
	CHANNEL0,
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
	CHANNEL5,
	CHANNEL6,
	CHANNEL7,
}channel_selectType;

typedef enum            //ADC Interrupt Enable
{
	ADC_DISABLE,
	ADC_ENABLE
}INT_cnfg;

typedef struct
{
	vref_selectType    vref;
	clk_select     clk;
	mode_selectType    mode;
}ADC_cnfg;

void   adc_init(ADC_cnfg* ptrADC);

uint16 adc_read(channel_selectType channel);

void   adc_int(INT_cnfg adcint, channel_selectType channel, void (*ptr_func)(uint16 val));

#endif /* ADC_H_ */