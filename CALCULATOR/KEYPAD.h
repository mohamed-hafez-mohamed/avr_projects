/*
 * KEYPAD.h
 *
 * Created: 9/2/2019 10:30:24 م
 *  Author: MAOHAMED HAFEZ
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "keypad_pcnfg.h"
#include "GPIO.h"

#define START_ROW  0
#define END_ROW    3
#define START_COL  0
#define END_COL    3
//Keypad Information
typedef struct
{
	uint8 keypadRow[ROWS];    //keypad ROW array
	uint8 keypadCol[COLUMS]; //keypad COL array
}keypadcnfg_t;

// to initialize the key pad pass the pin config and the function to receive the key pressed
void keypad_init(keypadcnfg_t* ptrkeypad,void (*ptr_fu)(uint8 ));

// this function called at the infinity loop to check any pressed
void keypad_mainFun(keypadcnfg_t* ptrkeypad);



#endif /* KEYPAD_H_ */