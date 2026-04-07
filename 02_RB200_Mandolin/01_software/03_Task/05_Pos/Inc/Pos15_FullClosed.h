/*
 * Pos15_FullClosed.h
 *
 *  Created on: 2018年11月23日
 *      Author: zhuxc
 */
#ifndef Pos15_FullClosed_H
#define Pos15_FullClosed_H


typedef  struct
{
    LONG    MotPulseNo;
} FENCP;

typedef  struct
{
    ULONG  RxPos[2];        //光学尺脉冲值高位  RxPos[0]为当前值，RxPos[1]为上周期的值
    LONG   FencPos;         //32bit全闭环位置累计计数
    LONG   FencAbsPos;      //全闭环编码器绝对位置
    LONG   FencAbsPosPul;     //全闭环编码器绝对位置(转换为电机编码器单位)
	LONG   FencMPos;
	SHORT  FencReadCnt;
    
	SHORT  FirstReadFlag;
	LONG   FencPulseNo;
	SHORT  FencPulseBit;
    LONG   FencSpd;         //全闭环编码器速度

    UCHAR  FenseTrigStatus; //全闭环补偿有效状态
    UCHAR  FenseTrigEn;     //全闭环补偿有效标志
} FENCV;


#define FULL_CLOSED_METHOD_MIXERROR     0       // TODO 全闭环混合误差滤波方案

extern FENCV FencV;
extern FENCP FencP;
extern LONG LpxReadFencPosition( void );
extern void IprmcalFullClosedEnc( void );
extern void KpxInitFullClosedEncoder( void );
extern LONG FensecmdMoveAvergeFilter( LONG pcmdin );
extern void KpxInitFullClosedMaFilter( void );

extern void Delta_FencPosFil_Cal(void);

extern void LpxCheckSemiFullPerrOverFlow( void );
extern LONG FenseMixMaFilter( LONG pcmdin );
extern LONG FullClosedMethod2( void );
#endif
