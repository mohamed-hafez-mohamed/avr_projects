/*
 * PWM.c
 *
 * Created: 9/18/2019 02:38:33 ?
 *  Author: mah_h
 */ 

#include "PWM.h"

//timer0
void pwm0_init(void)
{
	pin_dirc(B3,PIN_OUTPUT);
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))     |= (SET << WGM00);
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))     |= (SET << WGM01);
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))     |= (SET << COM01);
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))     |= (3   << CS00);
	ACCESS_REG_8BIT((TIMER0BASE + TIMER0_OFFSET))      = 0x00;
}

//timer1
void pwm1_init(void)
{
	pin_dirc(D4,PIN_OUTPUT);
	pin_dirc(D5,PIN_OUTPUT);
	ACCESS_REG_8BIT((TIMER1BASE + CONTROL1A_OFFSET))   |= (SET << WGM10);
	ACCESS_REG_8BIT((TIMER1BASE + CONTROL1A_OFFSET))   |= (2   << COM1B0);
	ACCESS_REG_8BIT((TIMER1BASE + CONTROL1A_OFFSET))   |= (2   << COM1A0);
	ACCESS_REG_8BIT((TIMER1BASE + CONTROL1B_OFFSET))   |= (3   << CS10);
	ACCESS_REG_8BIT((TIMER1BASE + CONTROL1B_OFFSET))   |= (1   << WGM12);
	ACCESS_REG_8BIT((TIMER0BASE + TIMER1L_OFFSET))      = 0x00;
	ACCESS_REG_8BIT((TIMER0BASE + TIMER1H_OFFSET))      = 0x00;
}

//timer2	
void pwm2_init(void)
{
	pin_dirc(D7,PIN_OUTPUT);
	ACCESS_REG_8BIT((TIMER2BASE + CONTROL2_OFFSET))   |= (4   << CS20);
	ACCESS_REG_8BIT((TIMER2BASE + CONTROL2_OFFSET))   |= (SET << WGM21);
	ACCESS_REG_8BIT((TIMER2BASE + CONTROL2_OFFSET))   |= (SET << WGM20);
	ACCESS_REG_8BIT((TIMER2BASE + CONTROL2_OFFSET))   |= (2   << COM20);
	ACCESS_REG_8BIT((TIMER0BASE + TIMER2_OFFSET))      = 0x00;
}
	
void pwm_stop(uint8 pin)
{
	switch(pin)
	{
		case B3:
		{
			ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET)) &= ~(SET << COM01);	//disconnect oco
			break;
		}
		case D4:
		{
			ACCESS_REG_8BIT((TIMER1BASE + CONTROL1A_OFFSET)) &= ~(SET << COM1A0); // disconnect oc1b
			break;
		}
		case D5:
		{
			ACCESS_REG_8BIT((TIMER1BASE + CONTROL1A_OFFSET)) &= ~(SET << COM1B0); // disconnect oc1a
			break;
		}
		case D7:
		{
			ACCESS_REG_8BIT((TIMER2BASE + CONTROL2_OFFSET)) &= ~(SET << COM20); // disconnect oc2
			break;
		}
	}
}

void pwm_write(uint8 pin,uint8 val)
{
	if (val == 0)
	{
		pwm_stop(pin);
		pin_write(pin, LOW_LEVEL);
	}
	else if (val == 255)
	{
		pwm_stop(pin);
		pin_write(pin, HIGH_LEVEL);
	}
	else
	{
	   switch(pin)
	   {
	      case B3:
	         ACCESS_REG_8BIT((TIMER0BASE + OUTPUTCOM0_OFFSET)) = val;
	      break;
	      case D4:
	         ACCESS_REG_8BIT((TIMER0BASE + OUTPUTCOM1BL_OFFSET)) = val;
	      break;
	      case D5:
	         ACCESS_REG_8BIT((TIMER0BASE + OUTPUTCOM1AL_OFFSET)) = val;/*
 * PWM.c
 *
 * Created: 9/18/2019 02:38:33 ?
 *  Author: mah_h
 */ 

#include "PWM.h"

//timer0
void pwm0_init(void)
{
	pin_dirc(B3,PIN_OUTPUT);
	ACCESS_REG_8BIT((TIMER0BASE + TIMER0_OFFSET))        = 0x00;
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))     |= (2   << CS00 );
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))     |= (SET << WGM00);
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))     |= (SET << WGM01);
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))     |= (2   << COM00);
}

//timer1
void pwm1_init(void)
{
	pin_dirc(D4,PIN_OUTPUT);
	pin_dirc(D5,PIN_OUTPUT);
	ACCESS_REG_8BIT((TIMER1BASE + CONTROL1A_OFFSET))   |= (SET << WGM10);
	ACCESS_REG_8BIT((TIMER1BASE + CONTROL1A_OFFSET))   |= (2   << COM1B0);
	ACCESS_REG_8BIT((TIMER1BASE + CONTROL1A_OFFSET))   |= (2   << COM1A0);
	ACCESS_REG_8BIT((TIMER1BASE + CONTROL1B_OFFSET))   |= (3   << CS10);
	ACCESS_REG_8BIT((TIMER1BASE + CONTROL1B_OFFSET))   |= (1   << WGM12);
	ACCESS_REG_8BIT((TIMER0BASE + TIMER1L_OFFSET))      = 0x00;
	ACCESS_REG_8BIT((TIMER0BASE + TIMER1H_OFFSET))      = 0x00;
}

//timer2	
void pwm2_init(void)
{
	pin_dirc(D7,PIN_OUTPUT);
	ACCESS_REG_8BIT((TIMER2BASE + CONTROL2_OFFSET))   |= (4   << CS20);
	ACCESS_REG_8BIT((TIMER2BASE + CONTROL2_OFFSET))   |= (SET << WGM21);
	ACCESS_REG_8BIT((TIMER2BASE + CONTROL2_OFFSET))   |= (SET << WGM20);
	ACCESS_REG_8BIT((TIMER2BASE + CONTROL2_OFFSET))   |= (2   << COM20);
	ACCESS_REG_8BIT((TIMER0BASE + TIMER2_OFFSET))      = 0x00;
}
	
void pwm_stop(uint8 pin)
{
	switch(pin)
	{
		case B3:
		{
			ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET)) &= ~(SET << COM01);	//disconnect oco
			break;
		}
		case D4:
		{
			ACCESS_REG_8BIT((TIMER1BASE + CONTROL1A_OFFSET)) &= ~(SET << COM1A0); // disconnect oc1b
			break;
		}
		case D5:
		{
			ACCESS_REG_8BIT((TIMER1BASE + CONTROL1A_OFFSET)) &= ~(SET << COM1B0); // disconnect oc1a
			break;
		}
		case D7:
		{
			ACCESS_REG_8BIT((TIMER2BASE + CONTROL2_OFFSET)) &= ~(SET << COM20); // disconnect oc2
			break;
		}
	}
}

void pwm_write(uint8 pin,uint8 val)
{
	if (val == 0)
	{
		pwm_stop(pin);
		pin_write(pin, LOW_LEVEL);
	}
	else if (val == 255)
	{
		pwm_stop(pin);
		pin_write(pin, HIGH_LEVEL);
	}
	else
	{
	   switch(pin)
	   {
	      case B3:
	         ACCESS_REG_8BIT((TIMER0BASE + OUTPUTCOM0_OFFSET))   = val;
	      break;
	      case D4:
	         ACCESS_REG_8BIT((TIMER0BASE + OUTPUTCOM1BL_OFFSET)) = val;
	      break;
	      case D5:
	         ACCESS_REG_8BIT((TIMER0BASE + OUTPUTCOM1AL_OFFSET)) = val;
	      break;
	      case D7:
	         ACCESS_REG_8BIT((TIMER0BASE + OUTPUTCOM2_OFFSET))   = val;
	      break;
	   }
	}
}
	      break;
	      case D7:
	         ACCESS_REG_8BIT((TIMER0BASE + OUTPUTCOM2_OFFSET)) = val;
	      break;
	   }
	}
}
