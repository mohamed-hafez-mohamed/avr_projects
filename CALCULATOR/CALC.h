/*
 * CALC.h
 *
 * Created: 9/7/2019 08:51:52 م
 *  Author: MAOHAMED HAFEZ
 */ 


#ifndef CALC_H_
#define CALC_H_

#include "LCD.h"
#include "KEYPAD.h"

void calc_init(void);

void print_num(uint8 chr);

void parse_buffer(uint8 buffer[]);

void execute_operation(uint8 operator);

void print_result(uint8 res);

#endif /* CALC_H_ */