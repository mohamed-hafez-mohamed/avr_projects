/*
 * TIMER0.h
 *
 * Created: 9/10/2019 02:19:21 ?
 *  Author: mah_h
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/interrupt.h>
#include "timer_cnfg.h"

typedef enum
{
	NO_CLK_SRC,          //Timer Disable
	NO_PRESCALING,
	PRESCALING_CLK8,
	PRESCALING_CLK64,
	PRESCALING_CLK256,
	PRESCALING_CLK1024,
	EXT_CLK_FALLING,
	EXT_CLK_RISING
}clk_selectType;

typedef enum    
{
	Normal,
	PWM_phase_correct,
	CTC,
	Fast_PWM
}WAVE_FORM_GEN;

typedef enum
{
	Normal_port,   //Normal port operation, OC0 disconnected
	Toggle_on_com, //Toggle OC0 on compare match or reserved with other modes
	Clear_on_com,  //Clear OC0 on compare match or (non-inverting mode) with other modes
	Set_on_com     //set OC0 on compare match or (inverting mode) with other modes
}COMPARE_MATCH_OUTPUT;

typedef enum            //Timer/Counter0 over flow Interrupt Enable
{
	TOIE0_disable,
	TOIE0_enable
}TOVFIE0;

typedef enum            //Timer/Counter0 Output Compare Match Interrupt Enable
{
	OCIE0_disable,
	OCIE0_enable
}OCMIE0;

typedef struct 
{
	clk_selectType        Timer0_clkSelect;
	WAVE_FORM_GEN         Timer0_mode;
	COMPARE_MATCH_OUTPUT  Timer0_COM;
}timer0_cnfg;

void timer0_init(timer0_cnfg* ptrtimer0);

uint8 ocr0(uint8 mode, uint8 value);

uint8 tcnt0(uint8 mode, uint8 value);

void ov_int(TOVFIE0 Timer0_TOIE, void(*ptr_ISR)(void));

void oc_int(OCMIE0 Timer0_OCIE);

//void(*ptr_ISR)(void)
#endif /* TIMER0_H_ */