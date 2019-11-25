/*
 * platform_pcnfg.h
 *
 * Created: 9/2/2019 10:20:40 م
 *  Author: MAOHAMED HAFEZ
 */ 


#ifndef PLATFORM_PCNFG_H_
#define PLATFORM_PCNFG_H_

//make pins in range 0 :7
#define START_PORTA      0
#define END_PORTA        7
#define START_PORTB      8
#define END_PORTB        15
#define START_PORTC      16
#define END_PORTC        23
#define START_PORTD      24
#define END_PORTD        31
#define CNFG_PINS_PORTB  8
#define CNFG_PINS_PORTC  16
#define CNFG_PINS_PORTD  24
//REGISTERS' OPERATIONS
//INPUT&OUTPUT CONFIGURATION
#define INPUT_PIN  0
#define OUTPUT_PIN 1
//LOGIC STATE
#define HIGH	   1
#define LOW        0
//BASE ADDRESS FOR GPIO REGISTES
#define Base_A 0x39
#define Base_B 0x36
#define Base_C 0x33
#define Base_D 0x30
//INDEX VALUES FOR GPIO REGISTES
#define DIRC_OFFEST	   1
#define INTPUT_OFFEST  0
#define OUTPUT_OFFEST  2

//USING BITFIELD FOR OUTPUT
#define PORTA (*(bit_t*)(Base_A + OUTPUT_OFFEST))
#define PORTB (*(bit_t*)(Base_B + OUTPUT_OFFEST))
#define PORTC (*(bit_t*)(Base_C + OUTPUT_OFFEST))
#define PORTD (*(bit_t*)(Base_D + OUTPUT_OFFEST))


#endif /* PLATFORM_PCNFG_H_ */