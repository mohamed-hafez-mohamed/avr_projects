/*
 * TIMER0.c
 *
 * Created: 9/10/2019 02:20:45 م
 *  Author: mah_h
 */ 

#include "GPIO.h"
#include "TIMER0.h"

void timer0_init(timer0_cnfg* ptrtimer0)
{
	ACCESS_REG_8BIT((TIMER0BASE + TIMER0_OFFSET))   = CLEAR_REGISTER;                 //clear TCNT0 REG
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))  = CLEAR_REGISTER;                 //clear TCCR0 REG
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET)) |= (ptrtimer0->Timer0_clkSelect << CS00);
	switch(ptrtimer0->Timer0_mode)
	{
		case Normal :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM00);
		break;
		case PWM_phase_correct :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |= (SET << WGM00);
		break;
		case CTC :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |= (SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM00);
		break;
		case Fast_PWM :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |= (SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |= (SET << WGM00);
		break;
	}
	switch(ptrtimer0->Timer0_TOIE)
	{
		case TOIE0_enable :
		   ACCESS_REG_8BIT((TIMER0BASE + MASK_OFFSET)) |=  (SET << TOIE0);
		break;
		case TOIE0_disable :
		   ACCESS_REG_8BIT((TIMER0BASE + MASK_OFFSET)) &= ~(SET << TOIE0);
		break;
	}
	switch(ptrtimer0->Timer0_OCIE)
	{
		case OCIE0_enable :
		   ACCESS_REG_8BIT((TIMER0BASE + MASK_OFFSET)) |=  (SET << OCIE0);
		break;
		case OCIE0_disable :
		   ACCESS_REG_8BIT((TIMER0BASE + MASK_OFFSET)) &= ~(SET << OCIE0);
		break;
	}
}