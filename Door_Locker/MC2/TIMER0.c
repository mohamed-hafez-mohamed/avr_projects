/*
 * TIMER0.c
 *
 * Created: 9/10/2019 02:20:45 ?
 *  Author: mah_h
 */ 

#include "GPIO.h"
#include "TIMER0.h"

static void (*pfunc_ovi)(void);
static void (*pfunc_oci)(void);

void timer0_init(timer0_cnfg* ptrtimer0)
{
	pin_dirc(T0,PIN_INPUT);
	ACCESS_REG_8BIT((TIMER0BASE + TIMER0_OFFSET))    = CLEAR_REGISTER;                 //clear TCNT0 REG
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))  = CLEAR_REGISTER;                 //clear TCCR0 REG
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET)) |= (ptrtimer0->Timer0_clkSelect << CS00);
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET)) |= (ptrtimer0->Timer0_COM       << COM00);
	ACCESS_REG_8BIT((TIMER0BASE + MASK_OFFSET))     |=  (ptrtimer0->Timer0_TOIE     << TOIE0);
	ACCESS_REG_8BIT((TIMER0BASE + MASK_OFFSET))     |=  (ptrtimer0->Timer0_OCIE     << OCIE0);
	switch(ptrtimer0->Timer0_mode)
	{
		case Normal :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM00);
		break;
		case PWM_phase_correct :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |=  (SET << WGM00);
		   pin_dirc(OC0,PIN_OUTPUT);
		break;
		case CTC :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |=  (SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM00);
		   pin_dirc(OC0,PIN_OUTPUT);
		break;
		case Fast_PWM :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |=  (SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |=  (SET << WGM00);
		   pin_dirc(OC0,PIN_OUTPUT);
		break;
	}
}

uint8 ocr0(uint8 mode, uint8 value)
{
	switch(mode)
	{
		case 'w' :
		   WRITE_REG_8BIT((TIMER0BASE + OUTPUTCOM0_OFFSET), value);
		break;
		case 'r' :
		   return ACCESS_REG_8BIT(TIMER0BASE + OUTPUTCOM0_OFFSET);
		break;
	}
}

uint8 tcnt0(uint8 mode, uint8 value)
{
	switch(mode)
	{
		case 'w' :
		   WRITE_REG_8BIT((TIMER0BASE + OUTPUTCOM0_OFFSET), value);
		break;
		case 'r' :
		   return ACCESS_REG_8BIT(TIMER0BASE + TIMER0_OFFSET);
		break;
	}
}

void ov_int(void (*ptr_ISR)(void))
{
	pfunc_ovi = ptr_ISR;
}

void oc_int(void (*ptr_ISR)(void))
{
	pfunc_oci = ptr_ISR;
}

ISR(TIMER0_OVF_vect)
{
	sei();
	(*pfunc_ovi)();
}

ISR(TIMER0_COMP_vect)
{
	sei();
	(*pfunc_oci)();
}
