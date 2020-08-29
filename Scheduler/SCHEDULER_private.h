/****************************************************************************
* Title                 :   DRIVER   
* Filename              :   DRIVER_private.h
* Author                :   Mohamed Hafez
* Origin Date           :   10/08/2020
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
*  04/01/15   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  DRIVER_private.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef DRIVER_PRIVATE_H_
#define DRIVER_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

//REGISTERS' ADREESES
///TIMER0
#define TIMER0BASE               0x52
#define TIMER0_OFFSET            0x00
#define CONTROL0_OFFSET          0x01
#define FLAG_OFFSET              0x06
#define MASK_OFFSET              0x07
#define OUTPUTCOM0_OFFSET        0x09

//TIMER0 BITS NAMES
#define CS00  0
#define COM00 4
#define COM01 5
#define WGM00 6
#define WGM01 3
#define TOIE0 0
#define OCIE0 1
#define TOV0  0
#define OCF0  1
#define OC0   B3
#define T0    B0

#endif
/*** End of File **************************************************************/
