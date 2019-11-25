/*
 * TIMER0.h
 *
 * Created: 9/10/2019 02:19:21 م
 *  Author: mah_h
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "timer_cnfg.h"

#define CLEAR_REGISTER         0x00
#define SET                    1

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

typedef enum            //Timer/Counter0 over flow Interrupt Enable
{
	TOIE0_enable,
	TOIE0_disable
}TOVFIE0;

typedef enum            //Timer/Counter0 Output Compare Match Interrupt Enable
{
	OCIE0_enable,
	OCIE0_disable
}OCMIE0;

typedef struct 
{
	clk_selectType Timer0_clkSelect;
	WAVE_FORM_GEN  Timer0_mode;
	TOVFIE0        Timer0_TOIE;
	OCMIE0         Timer0_OCIE;
}timer0_cnfg;

void timer0_init(timer0_cnfg* ptrtimer0);
#endif /* TIMER0_H_ */