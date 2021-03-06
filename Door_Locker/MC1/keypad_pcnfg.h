﻿/*
 * keypad_pcnfg.h
 *
 * Created: 9/2/2019 10:29:28 م
 *  Author: MAOHAMED HAFEZ
 */ 


#ifndef KEYPAD_PCNFG_H_
#define KEYPAD_PCNFG_H_

/*
* user should change the numbers of rows and colmus
* confg the buttons in it's poisition
* min values for row and colum 2 * 2
* max values for row and colum 4 * 4
* it can be easily add more rows and colums
*/

#define ROWS	    4
#define COLUMS	    4

#define COLUMS_POS	4

// the dirctives use to change the .c code to adjust to selected key pad
// don't touch it
#if ROWS >= 3
#define _ROW_3
#endif

#if ROWS >= 4
#define _ROW_4
#endif

#if COLUMS >= 3
#define _COLUM_3
#endif

#if COLUMS >= 4
#define _COLUM_4
#endif

// row 1
#define P_0_0 ('7') //colum 0
#define P_0_1 ('8') //colum 1
#define P_0_2 ('9') //colum 2
#define P_0_3 ('/') //colum 3

// row 2
#define P_1_0 '4' //colum 0
#define P_1_1 '5' //colum 1
#define P_1_2 '6' //colum 2
#define P_1_3 '*' //colum 3

// row 3
#ifdef _ROW_3
#define P_2_0 '1' //colum 0
#define P_2_1 '2' //colum 1
#define P_2_2 '3' //colum 2
#define P_2_3 '-' //colum 3
#endif // _ROW_3_

// row 4
#ifdef _ROW_4
#define P_3_0 '*' //colum 0
#define P_3_1 '0' //colum 1
#define P_3_2 '=' //colum 2
#define P_3_3 '+' //colum 3
#endif // _ROW_4_



#endif /* KEYPAD_PCNFG_H_ */