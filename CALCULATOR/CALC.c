/*
 * CALC.c
 *
 * Created: 9/7/2019 08:52:36 م
 *  Author: MAOHAMED HAFEZ
 */ 

#include "CALC.h"
#define ARRAY_INDEX  15
lcdcnfg_t mylcd       = {{D4,D5,D6,D7},C0,C1};
keypadcnfg_t mykeypad = {{A0,A1,A2,A3},{A4,A5,A6,A7}};

uint8 buffer[ARRAY_INDEX];
uint8 buffer_op1[7];
uint8 buffer_op2[7];
uint8 buffer_index = 0;
uint8 operand1, operand2, result, operato;

void calc_init(void)
{
	lcd_init(&mylcd);
	keypad_init(&mykeypad,print_num);
}


void print_num(uint8 chr)
{
	if(chr == '=')
	{
		lcd_chr(&mylcd, chr);
		buffer[buffer_index] = chr;
		buffer_index++;
		parse_buffer(&buffer);
	}
	else
	{
		lcd_chr(&mylcd, chr);
		buffer[buffer_index] = chr;
		buffer_index++;
	}
}

void parse_buffer(uint8* buffer)
{
	uint8 count;
	uint8 count_op1 = 0,count_op2 = 0, count_aux = 0;
	for(count = 0;count <= (buffer_index - 1);count++)
	{
		if(buffer[count] == '+'
		|| buffer[count] == '-'
		|| buffer[count] == '*'
		|| buffer[count] == '/')
		{
			operato = buffer[count];
			count_aux = count;
			count_aux = count_aux + 1;
			for(count_op1 = 0;count_op1 < (count_aux - 1);count_op1++)
			{
				buffer_op1[count_op1] = buffer[count_op1];
			}
			operand1 = atoi(&buffer_op1);
		}
		if(buffer[count] == '=')
		{
			for(count_aux;count_aux < (buffer_index - 1);count_aux++)
			{
				buffer_op2[count_op2] = buffer[count_aux];
				count_op2++;
			}
			operand2 = atoi(&buffer_op2);
			break;
		}
	}
	execute_operation(operato);
}

void execute_operation(uint8 operato)
{
	switch(operato)
	{
		case '+' :
		result = operand1 + operand2;
		break;
		case '-' :
		result = operand1 - operand2;
		break;
		case '*' :
		result = operand1 * operand2;
		break;
		case '/' :
		result = operand1 / operand2;
		break;
	}
	print_result(result);
}

void print_result(uint8 res)
{
	lcd_setCursor(&mylcd,1,0);
	lcd_num(&mylcd,res);
}