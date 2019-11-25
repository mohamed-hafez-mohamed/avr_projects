/*
 * KEYPAD.c
 *
 * Created: 9/2/2019 10:32:55 م
 *  Author: MAOHAMED HAFEZ
 */ 

#include "KEYPAD.h"

static void (*ptr_callBackFun)(uint8);

void keypad_init(keypadcnfg_t* ptrkeypad,void (*ptr_fu)(uint8 ))
{
	pins_dirc(ptrkeypad->keypadRow[START_ROW],ptrkeypad->keypadRow[END_ROW ],PIN_INPUT);
	pins_dirc(ptrkeypad->keypadCol[START_COL],ptrkeypad->keypadCol[END_COL],PIN_OUTPUT);
	set_pins(ptrkeypad->keypadRow[START_ROW],ptrkeypad->keypadRow[END_ROW ]);
	set_pins(ptrkeypad->keypadCol[START_COL],ptrkeypad->keypadCol[END_COL]);
	ptr_callBackFun = ptr_fu;
}

 static uint8 keypad_getKey(keypadcnfg_t* ptrkeypad)
{
	uint8 count_row, count_col;
	for(count_col = START_COL;count_col < COLUMS;count_col++)
	{
		set_pins(ptrkeypad->keypadCol[START_COL],ptrkeypad->keypadCol[END_COL]);
		pin_write(ptrkeypad->keypadCol[count_col], LOW_LEVEL);
		for(count_row = START_ROW;count_row < ROWS;count_row++)
		{
			if(!(pin_read(ptrkeypad->keypadRow[count_row])))
			{
				while(!(pin_read(ptrkeypad->keypadRow[count_row])));
				switch(count_row)
				{
					case 0 :
					   if(count_col == 0)      return P_0_0;
					   else if(count_col == 1) return P_0_1;
					#ifdef _ROW_3
					   else if(count_col == 2) return P_0_2;
					#endif
					#ifdef _ROW_4
					   else if(count_col == 3) return P_0_3;
					#endif
					   break;
					case 1 :
					   if(count_col == 0)      return P_1_0;
					   else if(count_col == 1) return P_1_1;
					#ifdef _ROW_3
					   else if(count_col == 2) return P_1_2;
					#endif
					#ifdef _ROW_4
					   else if(count_col == 3) return P_1_3;
					#endif
					   break;
					case 2 :
					   if(count_col == 0)      return P_2_0;
					   else if(count_col == 1) return P_2_1;
					#ifdef _ROW_3
					   else if(count_col == 2) return P_2_2;
					#endif
					#ifdef _ROW_4
					   else if(count_col == 3) return P_2_3;
					#endif
					   break;
					case 3 :
					   if(count_col == 0)      return P_3_0;
					   else if(count_col == 1) return P_3_1;
					#ifdef _ROW_3
					   else if(count_col == 2) return P_3_2;
					#endif
					#ifdef _ROW_4
					   else if(count_col == 3) return P_3_3;
					#endif
					   break;
				}
			}
		}
	}
}

void keypad_mainFun(keypadcnfg_t* ptrkeypad)
{
	volatile uint8 count_row;
	set_pins(ptrkeypad->keypadRow[START_ROW],ptrkeypad->keypadRow[END_ROW ]);
	clear_pins(ptrkeypad->keypadCol[START_COL],ptrkeypad->keypadCol[END_COL]);
	for(count_row = START_ROW;count_row < ROWS;count_row++)
	{
		if(!(pin_read(ptrkeypad->keypadRow[count_row])))
		{
			(*ptr_callBackFun)(keypad_getKey(ptrkeypad));
			return keypad_getKey(ptrkeypad);
		}
	}
}