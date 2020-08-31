/*
 * TIMER0.c
 *
 * Created: 9/10/2019 02:20:45 ?
 *  Author: mah_h
 */ 

#include "GPIO.h"
#include "TIMER0.h"

static void (*pfunc_ovi)(void * );
static void (*pfunc_oci)(void * );
static void * CallBackOviParameter;
static void * CallBackOciParameter;
void timer0_init(timer0_cnfg* ptrtimer0)
{
	pin_dirc(T0,PIN_INPUT);
	ACCESS_REG_8BIT((TIMER0BASE + TIMER0_OFFSET))    = CLEAR_REGISTER;                 //clear TCNT0 REG
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))  = CLEAR_REGISTER;                 //clear TCCR0 REG
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET)) |= (ptrtimer0->Timer0_clkSelect << CS00);
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET)) |= (ptrtimer0->Timer0_COM       << COM00);
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

uint16 ocr0(uint16 mode, uint16 value)
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

uint16 tcnt0(uint16 mode, uint16 value)
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

void ov_int(TOVFIE0 Timer0_TOIEvoid, void (*ptr_ISR)(void *), void * parameter)
{
	ACCESS_REG_8BIT((TIMER0BASE + MASK_OFFSET)) |= (Timer0_TOIEvoid << TOIE0);
	pfunc_ovi = ptr_ISR;
	CallBackOviParameter = parameter;
}

void oc_int(OCMIE0 Timer0_OCIEvoid, void (*ptr_ISR)(void * ), void * parameter)
{
	ACCESS_REG_8BIT((TIMER0BASE + MASK_OFFSET)) |= (Timer0_OCIEvoid << OCIE0);
	pfunc_oci = ptr_ISR;
	CallBackOciParameter = parameter;
}

ISR(TIMER0_OVF_vect)
{
	sei();
	pfunc_ovi(CallBackOviParameter);
}

ISR(TIMER0_COMP_vect)
{
	sei();
	pfunc_oci(CallBackOciParameter);
}
