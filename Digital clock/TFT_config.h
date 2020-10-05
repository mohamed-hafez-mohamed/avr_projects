/****************************************************************************
* Title                 :   TFT   
* Filename              :   TFT_config.h
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
/** @file  TFT_TFT_config.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef TFT_CONFIG_H_
#define TFT_CONFIG_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
//Color Mode
#define TFT_RGB_4_4_4     0X03
#define TFT_RGB_5_6_5     0X05
#define TFT_RGB_6_6_6     0X06
//TFT LCD SIZE 
#define TFT_WIDTH         132
#define TFT_HEIGHT        162
/******************************************************************************
* Configuration Constants
*******************************************************************************/

//TFT PINS
#define TFT_A0_PIN        PINA0
#define TFT_RST_PIN       PINA1
#define TFT_SLAVE_PIN     PINA2
//Choose the mode
/**
 * TFT_RGB_4_4_4     
 * TFT_RGB_5_6_5     
 * TFT_RGB_6_6_6     
 * */
#define TFT_COLOR_MODE    TFT_RGB_5_6_5

#define TFT_WIDTH_SIZE    (TFT_WIDTH - 1)
#define TFT_HEIGHT_SIZE   (TFT_HEIGHT - 1)


#endif /*File_H_*/

/*** End of File **************************************************************/
