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

uint8 buffer[ARRAY_INDEX]; //buffer to store data entered from keypad
uint8 buffer_op1[7];       //buffer to store operand1 entered from keypad
uint8 buffer_op2[7];       //buffer to store operand2 entered from keypad
uint8 buffer_index = 0;
uint8 operand1, operand2, result, operato;

void calc_init(void)
{
	//initialize keypad and lcd
	lcd_init(&mylcd);
	keypad_init(&mykeypad,print_num);
}


uint8 print_num(uint8 chr)
{
	if(chr == '=')
	{
		lcd_chr(&mylcd, chr);       //print character entered from on lcd
		buffer[buffer_index] = chr; //store the character
		buffer_index++;
		parse_buffer(&buffer);      //funtuin used to parse the buffer to distingush data and separate it
	}
	else
	{
		lcd_chr(&mylcd, chr);       //print character entered from on lcd
		buffer[buffer_index] = chr; //store the character
		buffer_index++;
	}
}

void parse_buffer(uint8* buffer) //funtuin used to parse the buffer to distingush data and separate it
{
	uint8 count;
	uint8 count_op1 = 0,count_op2 = 0, count_aux = 0;
	//traverse buffer to extract the operator
	for(count = 0;count <= (buffer_index - 1);count++)
	{
		if(buffer[count] == '+'
		|| buffer[count] == '-'
		|| buffer[count] == '*'
		|| buffer[count] == '/')
		{
			operato   = buffer[count]; //store the operator in variable
			//calculate how many characters entered before operator
			count_aux = count;                             //auxalriy variable to calculate how many characters entered before operator
			count_aux = count_aux + 1;                     //store the value to use it late to calculate operand2
			for(count_op1 = 0;count_op1 < (count_aux - 1);count_op1++)
			{
				buffer_op1[count_op1] = buffer[count_op1];//store the characters in buffer
			}
			operand1 = atoi(&buffer_op1);                 //convert the characters to integer value
		}
		if(buffer[count] == '=')
		{
			//calculate the entered characters after operator and bbefore '='
			for(count_aux;count_aux < (buffer_index - 1);count_aux++)
			{
				buffer_op2[count_op2] = buffer[count_aux];//store the characters in buffer
				count_op2++;
			}
			operand2 = atoi(&buffer_op2);//convert the characters to integer value
			break;
		}
	}
	execute_operation(operato);
}

void execute_operation(uint8 operato) //calculate the result
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
	print_result(result);//print the result on lcd 
}

void print_result(uint8 res)
{
	lcd_setCursor(&mylcd,1,0);
	lcd_num(&mylcd,res);
}
