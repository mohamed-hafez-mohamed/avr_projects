/*******************************************************************************
* Title                 :   DWATCH 
* Filename              :   DWATCH_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   26/09/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  26/09/20   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file DWATCH_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/	

#include "common.h"
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <stdlib.h>
#include "DWATCH_interface.h"
#include "DWATCH_config.h"
#include "DWATCH_private.h"
#include "TIMER0.h"
#include "TFT_interface.h"

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
static uint8  Static_uint8Time[]     = "  :  :  ";
static uint8  Static_uint8Calender[] = "  /  /20  "; 
static uint8  Static_uint8Second = 40;
static uint8  Static_uint8Minute = 59;
static uint8  Static_uint8Hour   = 23;
static uint8  Static_uint8Day    = 1;
static uint8  Static_uint8Date   = 26;
static uint8  Static_uint8Month  = 9;
static uint16 Static_uint16Year  = 20;

timer0_cnfg mytimer = {EXT_CLK_FALLING, CTC, Toggle_on_com};
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void ADWATCH_voidCalCulateTime(void * Copy_VP)
{
   Static_uint8Second++;
   if(Static_uint8Second == 60)
   {
      Static_uint8Second = 0;
      Static_uint8Minute++;
   }
   if(Static_uint8Minute == 60)
   {
      Static_uint8Minute = 0;
      Static_uint8Hour++;
   }
   if(Static_uint8Hour == 24)
   {
      Static_uint8Hour = 0;
      Static_uint8Date++;
      Static_uint8Day++;
   }
   if(Static_uint8Day == 8)
   {
      Static_uint8Day = 1;
   }
   if(Static_uint8Date == 31)
   {
      Static_uint8Date = 1;
      Static_uint8Month++;
   }
   if(Static_uint8Month == 13)
   {
      Static_uint16Year++;
   }
   Static_uint8Time[7]     = Static_uint8Second % 10 + 48;
   Static_uint8Time[6]     = Static_uint8Second / 10 + 48;
   Static_uint8Time[4]     = Static_uint8Minute % 10 + 48;
   Static_uint8Time[3]     = Static_uint8Minute / 10 + 48;
   Static_uint8Time[1]     = Static_uint8Hour   % 10 + 48;
   Static_uint8Time[0]     = Static_uint8Hour   / 10 + 48;
   Static_uint8Calender[9] = Static_uint16Year  % 10 + 48;
   Static_uint8Calender[8] = Static_uint16Year  / 10 + 48;
   Static_uint8Calender[4] = Static_uint8Month  % 10 + 48;
   Static_uint8Calender[3] = Static_uint8Month  / 10 + 48;
   Static_uint8Calender[1] = Static_uint8Date   % 10 + 48;
   Static_uint8Calender[0] = Static_uint8Date   / 10 + 48;
}
void ADWATCH_voidDisplayDay(void)
{
   switch(Static_uint8Day)
   {
      case 1:  HTFT_uint8DrawText(35, 10, " SATURDAY  ", TFT_CYAN_COLOR, TFT_BLACK_COLOR, 1); break;
      case 2:  HTFT_uint8DrawText(35, 10, " SUNDAY  "  , TFT_CYAN_COLOR, TFT_BLACK_COLOR, 1); break;
      case 3:  HTFT_uint8DrawText(35, 10, " MONDAY  "  , TFT_CYAN_COLOR, TFT_BLACK_COLOR, 1); break;
      case 4:  HTFT_uint8DrawText(35, 10, " TUESDAY "  , TFT_CYAN_COLOR, TFT_BLACK_COLOR, 1); break;
      case 5:  HTFT_uint8DrawText(35, 10, "WEDNESDAY"  , TFT_CYAN_COLOR, TFT_BLACK_COLOR, 1); break;
      case 6:  HTFT_uint8DrawText(35, 10, "THURSDAY "  , TFT_CYAN_COLOR, TFT_BLACK_COLOR, 1); break;
      default: HTFT_uint8DrawText(35, 10, "FRIDAY "    , TFT_CYAN_COLOR, TFT_BLACK_COLOR, 1); break;
   }
}

void ADWATCH_voidDisplay(void)
{
   HTFT_uint8DrawText(35, 27, Static_uint8Calender, TFT_YELLOW_COLOR, TFT_BLACK_COLOR, 1);
   HTFT_uint8DrawText(35, 50, Static_uint8Time,     TFT_GREEN_COLOR,  TFT_BLACK_COLOR, 1);
}

ISR(TIMER0_COMP_vect)
{
	sei();
	ADWATCH_voidCalCulateTime(NULL);
}



/*************** END OF FUNCTIONS ***************************************************************************/
