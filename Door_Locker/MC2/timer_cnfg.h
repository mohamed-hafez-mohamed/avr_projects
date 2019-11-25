/*
 * timer_cnfg.h
 *
 * Created: 9/18/2019 02:33:06 م
 *  Author: mah_h
 */ 


#ifndef TIMER_CNFG_H_
#define TIMER_CNFG_H_

#define SET                      1
//REGISTERS' ADREESES
///TIMER0
#define TIMER0BASE               0x52
#define TIMER0_OFFSET            0x00
#define CONTROL0_OFFSET          0x01
#define FLAG_OFFSET              0x06
#define MASK_OFFSET              0x07
#define OUTPUTCOM0_OFFSET        0x09
//TIMER1
#define TIMER1BASE               0x46
#define INPUTCAP1L_OFFSET        0x00
#define INPUTCAP1H_OFFSET        0x01
#define OUTPUTCOM1BL_OFFSET      0x02
#define OUTPUTCOM1BH_OFFSET      0x03
#define OUTPUTCOM1AL_OFFSET      0x04
#define OUTPUTCOM1AH_OFFSET      0x05
#define TIMER1L_OFFSET           0x06
#define TIMER1H_OFFSET           0x07
#define CONTROL1B_OFFSET         0x08
#define CONTROL1A_OFFSET         0x09
//timer2
#define TIMER2BASE               0x43
#define OUTPUTCOM2_OFFSET         0x00
#define TIMER2_OFFSET            0x01
#define CONTROL2_OFFSET          0x02
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
//TIMER1 BITS NAMES
#define WGM10  0
#define COM1B0 4
#define COM1A0 6
#define CS10   0
#define WGM12  3
//TIMER2 BITS NAMES
#define CS20   0
#define WGM21  3
#define WGM20  6
#define COM20  4
#endif /* TIMER_CNFG_H_ */