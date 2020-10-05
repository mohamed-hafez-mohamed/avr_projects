/*******************************************************************************
* Title                 :   TFT 
* Filename              :   TFT_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   21/9/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  21/9/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file TFT_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include <util/delay.h>
#include <string.h>
#include "GPIO.h"
#include "SPI.h"
#include "TFT_interface.h"
#include "TFT_config.h"
#include "TFT_private.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static uint16 Static_uint16ColStart;
static uint16 Static_uint16RowStart;
static uint16 Static_uint16Wrap = 1;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void HTFT_voidWriteCommand(uint8 Copy_uint8Command)
{
   pin_write(TFT_A0_PIN, LOW_LEVEL);
   spi_exchangeData(Copy_uint8Command);
}

static void HTFT_voidWriteData(uint8 Copy_uint8Data)
{
   pin_write(TFT_A0_PIN, HIGH_LEVEL);
   spi_exchangeData(Copy_uint8Data);
}

static void HTFT_voidSetAddWindow(uint8 Copy_uint8Width1, uint8 Copy_uint8Width2, uint8 Copy_uint8Height1, uint8 Copy_uint8Height2)
{
	HTFT_voidWriteCommand(TFT_CASET_CMD);                         //Coloumn set address command
	HTFT_voidWriteData(0);                                        //Coloumn set address parameter MSB START
	HTFT_voidWriteData(Copy_uint8Width1);                            //Coloumn set address parameter LSB START
	HTFT_voidWriteData(0);                                        //Coloumn set address parameter MSB END
	HTFT_voidWriteData(Copy_uint8Width2 + Static_uint16ColStart);       //Coloumn set address parameter LSB END
	HTFT_voidWriteCommand(TFT_RASET_CMD);                         //Row set address command
	HTFT_voidWriteData(0);                                        //Row set address parameter MSB START
	HTFT_voidWriteData(Copy_uint8Height1);                           //Row set address parameter LSB START
	HTFT_voidWriteData(0);                                        //Row set address parameter MSB END
	HTFT_voidWriteData(Copy_uint8Height2 + Static_uint16RowStart);      //Row set address parameter LSB END

	HTFT_voidWriteCommand(TFT_RAMWR_CMD);                         //RAM Write
}

void HTFT_voidInit(void)
{
	//RESET PULSE
   pin_write(TFT_RST_PIN, HIGH_LEVEL);
   _delay_us(100);
   pin_write(TFT_RST_PIN, LOW_LEVEL);
   _delay_us(1);
   pin_write(TFT_RST_PIN, HIGH_LEVEL);
   _delay_us(100);
   pin_write(TFT_RST_PIN, LOW_LEVEL);
   _delay_us(100);
   pin_write(TFT_RST_PIN, HIGH_LEVEL);
   _delay_ms(120);
   //Commands
   HTFT_voidWriteCommand(TFT_SLPOUT_CMD);     //To Out from sleeping mode
   _delay_ms(150);
   HTFT_voidWriteCommand(TFT_COLMOD_CMD);     //Color Mode
   HTFT_voidWriteData(TFT_COLOR_MODE);        //Command Parameter              
   HTFT_voidWriteCommand(TFT_DISPON_CMD);     //TFT Display on
}

void HTFT_voidDisplayImage(const uint16 * Copy_uint16Image)
{
	HTFT_voidSetAddWindow(0, TFT_WIDTH_SIZE, 0, TFT_HEIGHT_SIZE);
	for(uint16 Local_uint16Counter = 0;Local_uint16Counter < (TFT_WIDTH * TFT_HEIGHT);Local_uint16Counter++)
	{
	    HTFT_voidWriteData(Copy_uint16Image[Local_uint16Counter] >> TFT_get_HIGH_BYTE);
		HTFT_voidWriteData(Copy_uint16Image[Local_uint16Counter] &  TFT_GET_LOW_BYTE);
	}
}
uint8 HTFT_uint8DrawPixel(uint16 Copy_uint16Width, uint16 Copy_uint16Height, uint16  Copy_uint16Color)
{
   if((Copy_uint16Width >= TFT_WIDTH) || (Copy_uint16Height >= TFT_HEIGHT))
	{
		return 1;
	}
	HTFT_voidSetAddWindow(Copy_uint16Width,Copy_uint16Width + 1,Copy_uint16Height,Copy_uint16Height + 1);
	HTFT_voidWriteData(Copy_uint16Color >> TFT_get_HIGH_BYTE);
	HTFT_voidWriteData(Copy_uint16Color &  TFT_GET_LOW_BYTE);
}

uint8 HTFT_uint8FillRectangle(uint16 Copy_uint16Width1, uint16 Copy_uint16Width2, uint16 Copy_uint16Height1, uint16 Copy_uint16Height2, uint16  Copy_uint16Color)
{
	uint16 Local_uint16HighByte;
	uint16 Local_uint16LowByte;
	if((Copy_uint16Width1 >= TFT_WIDTH) || (Copy_uint16Height1 >= TFT_HEIGHT))
	{
		return 1;
	}
   if((Copy_uint16Width1 + Copy_uint16Width2 - 1) >= TFT_WIDTH)  
	{
		Copy_uint16Width2 = TFT_WIDTH  - Copy_uint16Width1;
	}
   if((Copy_uint16Height1 + Copy_uint16Height2 - 1) >= TFT_HEIGHT) 
	{
		Copy_uint16Height2 = TFT_HEIGHT - Copy_uint16Height1;
	}
	uint16 Local_uint16Size = (Copy_uint16Width2 - Copy_uint16Width1 - 1) * (Copy_uint16Height2 * Copy_uint16Height1 - 1);
   HTFT_voidSetAddWindow(Copy_uint16Width1,Copy_uint16Width1+Copy_uint16Width2-1,Copy_uint16Height1,Copy_uint16Height1+Copy_uint16Height2-1);
   Local_uint16HighByte = Copy_uint16Color >> TFT_get_HIGH_BYTE;
	Local_uint16LowByte  = Copy_uint16Color &  TFT_GET_LOW_BYTE;
	for(uint16 Local_uint16Counter = 0;Local_uint16Counter < Local_uint16Size;Local_uint16Counter++)
	{
	   HTFT_voidWriteData(Local_uint16HighByte);
		HTFT_voidWriteData(Local_uint16LowByte);
	}
}

uint8 HTFT_uint8FillColour(uint16  Copy_uint16Color)
{
	return HTFT_uint8FillRectangle(0, TFT_WIDTH_SIZE, 0, TFT_HEIGHT_SIZE, Copy_uint16Color);
}

uint8 HTFT_uint8DrawFastVLine(uint16 Copy_uint16Width1, uint16 Copy_uint16Height1, uint16 Copy_uint16Height2, uint16  Copy_uint16Color)
{
	uint16 Local_uint16HighByte;
	uint16 Local_uint16LowByte;
	if((Copy_uint16Width1 >= TFT_WIDTH) || (Copy_uint16Height1 >= TFT_HEIGHT))
	{
		return 1;
	}
   if((Copy_uint16Height1 + Copy_uint16Height2 - 1) >= TFT_HEIGHT) 
	{
		Copy_uint16Height2 = TFT_HEIGHT - Copy_uint16Height1;
	}
	Local_uint16HighByte = Copy_uint16Color >> TFT_get_HIGH_BYTE;
	Local_uint16LowByte  = Copy_uint16Color &  TFT_GET_LOW_BYTE;
	HTFT_voidSetAddWindow(Copy_uint16Width1,Copy_uint16Width1,Copy_uint16Height1,Copy_uint16Height1+Copy_uint16Height2-1);
	while(Copy_uint16Height2--)
	{
		HTFT_voidWriteData(Local_uint16HighByte);
		HTFT_voidWriteData(Local_uint16LowByte);
	}
}

uint8 HTFT_uint8DrawFastHLine(uint16 Copy_uint16Width1, uint16 Copy_uint16Width2,  uint16 Copy_uint16Height1, uint16  Copy_uint16Color)
{
	uint16 Local_uint16HighByte;
	uint16 Local_uint16LowByte;
	if((Copy_uint16Width1 >= TFT_WIDTH) || (Copy_uint16Height1 >= TFT_HEIGHT))
	{
		return 1;
	}
   if((Copy_uint16Width1 + Copy_uint16Width2 - 1) >= TFT_HEIGHT) 
	{
		Copy_uint16Width2 = TFT_WIDTH - Copy_uint16Width1;
	}
	Local_uint16HighByte = Copy_uint16Color >> TFT_get_HIGH_BYTE;
	Local_uint16LowByte  = Copy_uint16Color &  TFT_GET_LOW_BYTE;
	HTFT_voidSetAddWindow(Copy_uint16Width1,Copy_uint16Width1+Copy_uint16Width2-1,Copy_uint16Height1,Copy_uint16Height1);
	while(Copy_uint16Width2--)
	{
		HTFT_voidWriteData(Local_uint16HighByte);
		HTFT_voidWriteData(Local_uint16LowByte);
	}
}

uint8 HTFT_uint8DrawRectangle(uint16 Copy_uint16Width1, uint16 Copy_uint16Width2, uint16 Copy_uint16Height1, uint16 Copy_uint16Height2, uint16  Copy_uint16Color)
{
	HTFT_uint8DrawFastHLine(Copy_uint16Width1, Copy_uint16Width2, Copy_uint16Height1, Copy_uint16Color);
	HTFT_uint8DrawFastHLine(Copy_uint16Width1, Copy_uint16Width2, Copy_uint16Height1+Copy_uint16Height2-1, Copy_uint16Color);
	HTFT_uint8DrawFastVLine(Copy_uint16Width1, Copy_uint16Height1, Copy_uint16Height2, Copy_uint16Color);
	HTFT_uint8DrawFastVLine(Copy_uint16Width1+Copy_uint16Width2-1, Copy_uint16Height1, Copy_uint16Height2, Copy_uint16Color);
}

uint8 HTFT_uint8FillRect(uint16 Copy_uint16Width1, uint16 Copy_uint16Width2, uint16 Copy_uint16Height1, uint16 Copy_uint16Height2, uint16  Copy_uint16Color)
{
	for (sint16 Local_sint16Counter = Copy_uint16Width1;Local_sint16Counter < Copy_uint16Width1 + Copy_uint16Width2;Local_sint16Counter++)
	{
		HTFT_uint8DrawFastVLine(Local_sint16Counter, Copy_uint16Height1, Copy_uint16Height2, Copy_uint16Color);
   }
}

uint8 HTFT_uint8DrawCircle(sint16 Copy_sint16Width, sint16 Copy_sint16Height, sint16 Copy_sint16Radius,uint16 Copy_uint16Color)
{
	sint16 Local_sint16F = 1 - Copy_sint16Radius;
	sint16 Local_sint16ddF_x = 1;
	sint16 Local_sint16ddF_y = -2 * Copy_sint16Radius;
	sint16 Local_sint16X = 0;
	sint16 Local_sint16Y = Copy_sint16Radius;
	HTFT_uint8DrawPixel(Copy_sint16Width, Copy_sint16Height + Copy_sint16Radius, Copy_uint16Color);
	HTFT_uint8DrawPixel(Copy_sint16Width, Copy_sint16Height - Copy_sint16Radius, Copy_uint16Color);
	HTFT_uint8DrawPixel(Copy_sint16Width + Copy_sint16Radius, Copy_sint16Height, Copy_uint16Color);
	HTFT_uint8DrawPixel(Copy_sint16Width - Copy_sint16Radius, Copy_sint16Height, Copy_uint16Color);
	while(Local_sint16X < Local_sint16Y)
	{
		if(Local_sint16F >= 0)
		{
			Local_sint16Y--;
			Local_sint16ddF_y += 2;
			Local_sint16F += Local_sint16ddF_y;
		}
		Local_sint16X++;
		Local_sint16ddF_x += 2;
      Local_sint16F += Local_sint16ddF_x;
		HTFT_uint8DrawPixel(Copy_sint16Width + Local_sint16X, Copy_sint16Height + Local_sint16Y, Copy_uint16Color);
		HTFT_uint8DrawPixel(Copy_sint16Width - Local_sint16X, Copy_sint16Height + Local_sint16Y, Copy_uint16Color);
		HTFT_uint8DrawPixel(Copy_sint16Width + Local_sint16X, Copy_sint16Height - Local_sint16Y, Copy_uint16Color);
		HTFT_uint8DrawPixel(Copy_sint16Width - Local_sint16X, Copy_sint16Height - Local_sint16Y, Copy_uint16Color);
		HTFT_uint8DrawPixel(Copy_sint16Width + Local_sint16Y, Copy_sint16Height + Local_sint16X, Copy_uint16Color);
		HTFT_uint8DrawPixel(Copy_sint16Width - Local_sint16Y, Copy_sint16Height + Local_sint16X, Copy_uint16Color);
		HTFT_uint8DrawPixel(Copy_sint16Width + Local_sint16Y, Copy_sint16Height - Local_sint16X, Copy_uint16Color);
		HTFT_uint8DrawPixel(Copy_sint16Width - Local_sint16Y, Copy_sint16Height - Local_sint16X, Copy_uint16Color);
	}
}

uint8 HTFT_uint8DrawChar(uint8 Copy_uint8Width, uint8 Copy_uint8Height, uint8 Copy_uint8Char,uint16 Copy_uint16Color, uint16 Copy_uint16Bg, uint16 Copy_uint16Size)
{
	if((Copy_uint8Width >= TFT_WIDTH) || (Copy_uint8Height >= TFT_HEIGHT))
	{
		return 1;
	}
	if(Copy_uint16Size < 1) Copy_uint16Size = 1;
	if((Copy_uint8Char < ' ') || (Copy_uint8Char > '~')) Copy_uint8Char = '?';
   for(uint8 Local_uint8Counter1 = 0; Local_uint8Counter1 < 5; Local_uint8Counter1++ )
	{
		uint8 Local_uint8Line;
		if(Copy_uint8Char < 'S') Local_uint8Line = Const_Font1[(Copy_uint8Char - 32)  * 5 + Local_uint8Counter1];
		else                  Local_uint8Line = Const_Font2[(Copy_uint8Char - 'S') * 5 + Local_uint8Counter1];
      for(uint8 Local_uint8Counter2 = 0;Local_uint8Counter2 < 7;Local_uint8Counter2++,Local_uint8Line>>= 1)
		{
			if(Local_uint8Line & 0X01)
			{
				if(Copy_uint16Size == 1)
				{
					HTFT_uint8DrawPixel(Copy_uint8Width + Local_uint8Counter1, Copy_uint8Height + Local_uint8Counter2, Copy_uint16Color);
				}
				else
				{
					HTFT_uint8FillRect(Copy_uint8Width+Local_uint8Counter1*Copy_uint16Size,Copy_uint8Height+Local_uint8Counter2*Copy_uint16Size,Copy_uint16Size,Copy_uint16Size,Copy_uint16Color);
				}
			}
			else if(Copy_uint16Bg != Copy_uint16Color)
			{
				if(Copy_uint16Size == 1)
				{
               HTFT_uint8DrawPixel(Copy_uint8Width + Local_uint8Counter1, Copy_uint8Height + Local_uint8Counter2, Copy_uint16Bg);
				}
				else
				{
					HTFT_uint8FillRect(Copy_uint8Width+Local_uint8Counter1*Copy_uint16Size,Copy_uint8Height+Local_uint8Counter2*Copy_uint16Size,Copy_uint16Size,Copy_uint16Size,Copy_uint16Bg);
				}
			}
		}
	}
}

uint8 HTFT_uint8DrawText(uint8 Copy_uint8Width, uint8 Copy_uint8Height, uint8 * Copy_uint8Text,uint16 Copy_uint16Color, uint16 Copy_uint16Bg, uint16 Copy_uint16Size)
{
	uint8  Local_uint8CursorX   = Copy_uint8Width;
	uint8  Local_uint8CursorY   = Copy_uint8Height;
	uint16 Local_uint16TextSize = strlen(Copy_uint8Text);
	for(uint16 Local_uint16Counter = 0;Local_uint16Counter < Local_uint16TextSize;Local_uint16Counter++)
	{
		if(Static_uint16Wrap && (Local_uint8CursorX + Copy_uint16Size * 5) > TFT_WIDTH)
		{
			Local_uint8CursorX = 0;
			Local_uint8CursorY = Local_uint8CursorY + Copy_uint16Size * 7 + 3;
			if(Local_uint8CursorY > TFT_HEIGHT) Local_uint8CursorY = TFT_HEIGHT;
         if(Copy_uint8Text[Local_uint16Counter] == 0x20) goto _Skip;
		}
		HTFT_uint8DrawChar(Local_uint8CursorX,Local_uint8CursorY,Copy_uint8Text[Local_uint16Counter],Copy_uint16Color,Copy_uint16Bg,Copy_uint16Size);
      Local_uint8CursorX = Local_uint8CursorX + Copy_uint16Size * 6;
      if(Local_uint8CursorX > TFT_WIDTH) Local_uint8CursorX = TFT_WIDTH;
      _Skip:;
	}
}


/*************** END OF FUNCTIONS ***************************************************************************/
