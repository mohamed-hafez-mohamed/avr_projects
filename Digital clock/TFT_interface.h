/****************************************************************************
* Title                 :   TFT   
* Filename              :   TFT_interface.h
* Author                :   Mohamed Hafez
* Origin Date           :   21/9/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None
*
*****************************************************************************/
/****************************************************************************
* Doxygen C Template 
*
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description 
*  21/9/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  TFT_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef TFT_INTERFACE_H_
#define TFT_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
// Color definitions
#define TFT_BLACK_COLOR     0x0000
#define TFT_BLUE_COLOR      0x001F
#define TFT_RED_COLOR       0xF800
#define TFT_GREEN_COLOR     0x07E0
#define TFT_CYAN_COLOR      0x07FF
#define TFT_MAGENTA_COLOR   0xF81F
#define TFT_YELLOW_COLOR    0xFFE0
#define TFT_WHITE_COLOR     0xFFFF
/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

void HTFT_voidInit(void);

void HTFT_voidDisplayImage(const uint16 * Copy_uint16Image);

uint8 HTFT_uint8DrawPixel(uint16 Copy_uint16Width, uint16 Copy_uint16Height, uint16  Copy_uint16Color);
uint8 HTFT_uint8FillRectangle(uint16 Copy_uint16Width1, uint16 Copy_uint16Width2, uint16 Copy_uint16Height1, uint16 Copy_uint16Height2, uint16  Copy_uint16Color);
uint8 HTFT_uint8FillColour(uint16  Copy_uint16Color);
uint8 HTFT_uint8DrawFastVLine(uint16 Copy_uint16Width1, uint16 Copy_uint16Height1, uint16 Copy_uint16Height2, uint16  Copy_uint16Color);
uint8 HTFT_uint8DrawFastHLine(uint16 Copy_uint16Width1, uint16 Copy_uint16Width2,  uint16 Copy_uint16Height1, uint16  Copy_uint16Color);
uint8 HTFT_uint8DrawCircle(sint16 Copy_sint16Width, sint16 Copy_sint16Height, sint16 Copy_sint16Radius,uint16 Copy_uint16Color);
uint8 HTFT_uint8DrawRectangle(uint16 Copy_uint16Width1, uint16 Copy_uint16Width2, uint16 Copy_uint16Height1, uint16 Copy_uint16Height2, uint16  Copy_uint16Color);
uint8 HTFT_uint8FillRect(uint16 Copy_uint16Width1, uint16 Copy_uint16Width2, uint16 Copy_uint16Height1, uint16 Copy_uint16Height2, uint16  Copy_uint16Color);

uint8 HTFT_uint8DrawChar(uint8 Copy_uint8Width, uint8 Copy_uint8Height, uint8 Copy_uint8Char,uint16 Copy_uint16Color, uint16 Copy_uint16Bg, uint16 Copy_uint16Size);
uint8 HTFT_uint8DrawText(uint8 Copy_uint8Width, uint8 Copy_uint8Height, uint8 * Copy_uint8Text,uint16 Copy_uint16Color, uint16 Copy_uint16Bg, uint16 Copy_uint16Size);
#endif /*File_H_*/

/*** End of File **************************************************************/
