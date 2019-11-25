/*
 * LCD.h
 *
 * Created: 9/2/2019 10:24:52 م
 *  Author: MAOHAMED HAFEZ
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "lcd_pcnfg.h"
#include "GPIO.h"

#define COL16 16
#define COL32 32
#ifdef _4BIT_MODE
#define DATA_PINS 4
#endif
#ifdef _8BIT_MODE
#define DATA_PINS 8
#endif

typedef struct
{
	uint8 data_pins[DATA_PINS];
	uint8 EN;
	uint8 RS;
}lcdcnfg_t;

#define CLEAR_SCREEN                                0x01
#define LCD_4BIT_MODE                               0x02
#define LCD_ENTRY_DEC   							0x04
#define LCD_ENTRY_DEC_SHIFT   						0x05
#define ENTRY_MODE                                  0x06
#define LCD_ENTRY_INC_SHIFT   						0x07
#define DISPLAY_OFF                                 0x08
#define CURSOR_OFF                                  0x0C
#define LCD_DISP_ON_BLINK   						0x0D
#define CURSOR_ON                                   0x0E
#define CURSOR_BLINK                                0x0F
#define LCD_MOVE_CURSOR_LEFT 	  					0x10
#define LCD_MOVE_CURSOR_RIGHT   					0x14
#define LCD_MOVE_DISP_LEFT   						0x18
#define LCD_MOVE_DISP_RIGHT       					0x1C
#define LCD_4BIT_MODE_2_LINE                        0x28
#define LCD_8BIT_MODE_2_LINE                        0x38
#define LCD_BEGIN_AT_FIRST_RAW						0x80
#define LCD_BEGIN_AT_SECOND_RAW						0xC0
#define LCD_BEGIN_AT_THIRD_RAW						0x90
#define LCD_BEGIN_AT_FOURTH_RAW						0xD0

void lcd_init(const lcdcnfg_t* ptrlcdcnfg);

void lcd_cmd(const lcdcnfg_t* ptrlcdcnfg, uint8 cmd);

void lcd_setCursor(const lcdcnfg_t* ptrlcdcnfg, uint8 row, uint8 col);

void lcd_clear(const lcdcnfg_t* ptrlcdcnfg);

void lcd_displayOff(const lcdcnfg_t* ptrlcdcnfg);

void lcd_chr(const lcdcnfg_t* ptrlcdcnfg, uint8 chr);

void lcd_str(const lcdcnfg_t* ptrlcdcnfg, uint8* str);

void lcd_num(const lcdcnfg_t* ptrlcdcnfg, uint32 num);

void lcd_fnum(const lcdcnfg_t* ptrlcdcnfg, float fnum);



#endif /* LCD_H_ */