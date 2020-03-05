/*
 * PWM.h
 *
 * Created: 9/18/2019 02:38:14 ?
 *  Author: mah_h
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "GPIO.h"
#include "timer_cnfg.h"
void pwm0_init(void);

void pwm1_init(void);

void pwm2_init(void);

void pwm_write(uint8 pin,uint8 value);

void pwm_stop(uint8 pin);


#endif /* PWM_H_ */