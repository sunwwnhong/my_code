/*
 * APP26_MotorBrake.h
 *
 *  Created on: 2020Äê6ÔÂ23ÈÕ
 *      Author: zhuxc
 */

#ifndef APP26_MotorBrake_H
#define APP26_MotorBrake_H

typedef struct
{
   USHORT Step;
   USHORT Period;
   USHORT Periodcnt_24V;
   USHORT Periodcnt_12V;
   USHORT HoldTimeCnt;
}BRAKE_DEF;


extern BRAKE_DEF Brake_V;
extern void MotorBK_Init(void);
extern void MotorBK_On(void);
extern void MotorBK_Off(void);


#endif

