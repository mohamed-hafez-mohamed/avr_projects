/*
 * lcd.c
 *
 * Created: 8/31/2019 04:23:37 ?
 *  Author: Mohamed Hafez
 */ 

#include<stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "LCD.h"

#define  F_CPU 1000000UL

#define EN    ptrlcdcnfg->EN
#define RS    ptrlcdcnfg->RS

static void kick(const lcdcnfg_t* ptrlcdcnfg, uint8 chr)
{
	/*
	* assign data in the pins of the confg
	* make pulse to make lcd work
	*/
	uint8 i;
	for(i = 0;i < DATA_PINS;i++)
	{
		if(chr & (SET << i))
		{
			pin_write(ptrlcdcnfg->data_pins[i],HIGH_LEVEL);
		}
		else
		{
			pin_write(ptrlcdcnfg->data_pins[i],LOW_LEVEL);
		}
	}
	pin_write(EN,HIGH_LEVEL);
	_delay_ms(1);
	pin_write(EN,LOW_LEVEL);
}

void lcd_init(const lcdcnfg_t* ptrlcdcnfg)
{
	/*
	* set dirction output for data and control pins
	* config the lcd to start working
	*/
	uint8 i;
	for(i = 0;i < DATA_PINS;i++)
	{
		pin_dirc(ptrlcdcnfg->data_pins[i],PIN_OUTPUT);
	}
	
	pin_dirc(EN,PIN_OUTPUT);
	pin_dirc(RS,PIN_OUTPUT);
	#ifdef _4BIT_MODE
	lcd_cmd(ptrlcdcnfg,LCD_4BIT_MODE);        
	lcd_cmd(ptrlcdcnfg,LCD_4BIT_MODE_2_LINE);
	#endif
	
	#ifdef _8BIT_MODE
	lcd_cmd(ptrlcdcnfg,LCD_8BIT_MODE_2_LINE);
	#endif
	lcd_setCursor(ptrlcdcnfg,0,0);
	lcd_cmd(ptrlcdcnfg,ENTRY_MODE);
	lcd_cmd(ptrlcdcnfg,CURSOR_BLINK);
	lcd_cmd(ptrlcdcnfg,CLEAR_SCREEN);
}

void lcd_cmd(const lcdcnfg_t* ptrlcdcnfg, uint8 cmd)
{
	/*
	* select the register "command || data " in this case command
	* sent the command
	*/
	pin_write(RS,LOW_LEVEL);
	
	#ifdef _8BIT_MODE
	kick(ptrlcdcnfg, cmd);
	#endif
	
	#ifdef _4BIT_MODE
	kick(ptrlcdcnfg,cmd>>4);
	kick(ptrlcdcnfg,(cmd));
	#endif
	_delay_ms(2);
}

void lcd_setCursor(const lcdcnfg_t* ptrlcdcnfg, uint8 row, uint8 col)
{
	switch(row)
	{
		case 0 :
		lcd_cmd(ptrlcdcnfg,(unsigned) LCD_BEGIN_AT_FIRST_RAW   | col);
		break;
		case 1 :
		lcd_cmd(ptrlcdcnfg,(unsigned) LCD_BEGIN_AT_SECOND_RAW  | col);
		break;
		#ifdef LCD_16_4
		case 2 :
		lcd_cmd(ptrlcdcnfg,(unsigned) LCD_BEGIN_AT_THIRD_RAW  | col);
		break;
		case 3 :
		lcd_cmd(ptrlcdcnfg,(unsigned) LCD_BEGIN_AT_FOURTH_RAW | col);
		break;
		#endif
	}
}

void lcd_clear(const lcdcnfg_t* ptrlcdcnfg)
{
	lcd_cmd(ptrlcdcnfg,CLEAR_SCREEN);
}

void lcd_displayOff(const lcdcnfg_t* ptrlcdcnfg)
{
	lcd_cmd(ptrlcdcnfg,DISPLAY_OFF);
}

void lcd_chr(const lcdcnfg_t* ptrlcdcnfg, uint8 chr)
{
	pin_write(RS,HIGH_LEVEL);
	#ifdef _8BIT_MODE
	kick(ptrlcdcnfg,chr);
	#endif
	
	#ifdef _4BIT_MODE
	kick(ptrlcdcnfg,chr>>4);
	kick(ptrlcdcnfg,(chr));
	#endif
	_delay_ms(2);
}

void lcd_str(const lcdcnfg_t* ptrlcdcnfg, uint8 str[])
{
	uint8 count = 0;
	while(str[count] != '\0')
	{
		lcd_chr(ptrlcdcnfg,str[count]);
		count++;
		if (count == COL16) // go to the second line
		{
			lcd_setCursor(ptrlcdcnfg,1,0); //line 1 position zero
		}
		else if (count == COL32) // clear screen and show again
		{
			lcd_clear(ptrlcdcnfg);
			lcd_setCursor(ptrlcdcnfg,0,0); //line 0 position zero
			count = 0 ;
		}
	}
}

void lcd_num(const lcdcnfg_t* ptrlcdcnfg, uint8 num)
{
	uint8 *buffer[16];
	itoa(num, buffer, DECIMAL);
	lcd_str(ptrlcdcnfg,buffer);
}

void lcd_fnum(const lcdcnfg_t* ptrlcdcnfg, float fnum)
{
	uint8  *buffer[16];
	uint8  *tmpSign = (fnum < 0) ? "-" : "";                //Get sign
	float  tmpVal   = (fnum < 0) ? -fnum : fnum;            //store the sent number
	uint16 tmpInt1  = tmpVal;                               // Get the first integer part before the point
	float  tmpFrac  = tmpVal -  tmpInt1;                    // Get fraction .
	uint16 tmpInt2  = tmpFrac * NUMBER_AFTER_POINT;         // Turn into fraction into integer value
	// Print as parts
	sprintf (buffer, "%s%d.%2d", tmpSign, tmpInt1, tmpInt2);
	lcd_str(ptrlcdcnfg,buffer) ;
}