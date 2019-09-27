/*
 * CALCULATOR.c
 *
 * Created: 9/7/2019 08:41:24 م
 * Author : MAOHAMED HAFEZ
 */ 

#include "CALC.h"

extern lcdcnfg_t mylcd;
extern keypadcnfg_t mykeypad;
	
int main(void)
{
	calc_init();
    while (1) 
    {
		keypad_mainFun(&mykeypad);
    }
}

