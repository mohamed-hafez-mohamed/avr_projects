/*
 * ADC.c
 *
 * Created: 9/3/2019 09:23:59 ?
 *  Author: mah_h
 */ 

//#include <avr/interrupt.h>
#include "ADC.h"
#include <avr/interrupt.h>

#define  ADC_BUSY   IS_BIT_CLEAR((ADCBASE + CSRA_OFFSET),ADIF)
#define  V_IN	    ACCESS_REG_16BIT((ADCBASE + LOW_OFFSET))

static void (*ptr_callBackFun)(uint16);

void adc_init(ADC_cnfg* ptrADC)
{
	ACCESS_REG_8BIT((ADCBASE + CSRA_OFFSET))  = CLEAR_REGISTER;              //clear ADCSRA REG
	ACCESS_REG_8BIT((ADCBASE + MUX_OFFSET))   = CLEAR_REGISTER;              //clear ADCMUX REG
	ACCESS_REG_8BIT((ADCBASE + MUX_OFFSET))   |= ((ptrADC->vref)    << REFS0);  //V REFERENCE (REFS0,REFS1) (bit6,bit7) in ADMUX REG
	ACCESS_REG_8BIT((ADCBASE + CSRA_OFFSET))  |= ((ptrADC->clk)     << ADPS0);  //clock conversion (ADPS0,ADPS1,ADPS2) in ADCSRA REG
	SET_BIT((ADCBASE + CSRA_OFFSET),ADEN);                                   //SET EN BIT IN ACSRA REG
	ACCESS_REG_8BIT((ADCBASE + SFIOR_OFFSET)) |= ((ptrADC->mode)    << ADTS0);  //mode (ADTS0,ADTS1,ADTS2)(bit 5,6,7) in SFIOR   REG
	if((ptrADC->mode) != FREE_RUNNING_MODE)
	{
		SET_BIT((ADCBASE + CSRA_OFFSET),ADATE);                              //set trigger mode (ADATE BIT5)in ADCSRA REG
	}
}

uint16 adc_read(channel_selectType channel)
{
	ACCESS_REG_8BIT((ADCBASE + MUX_OFFSET))   |= ((channel) << MUX0);
	SET_BIT((ADCBASE + CSRA_OFFSET),ADSC);                              //start conversion (ADSC BIT 6) at ACSRA REG
	while((ADC_BUSY)); 
	(*ptr_callBackFun)(V_IN);                                                 // check (ADC Interrupt Flag BIT 4) in ACSRA REG
	return V_IN;
}

void adc_int(INT_cnfg adcint, channel_selectType channel, void (*ptr_func)(uint16 val))
{
	ACCESS_REG_8BIT((ADCBASE + CSRA_OFFSET))  |= ((adcint)  << ADIE);
	ACCESS_REG_8BIT((ADCBASE + MUX_OFFSET))   |= ((channel) << MUX0);
	SET_BIT((ADCBASE + CSRA_OFFSET),ADSC);                                     // start conversion for one shoot
	ptr_callBackFun = ptr_func;							       
}

ISR(ADC_vect)
{
	sei();
	(*ptr_callBackFun)(V_IN);
}