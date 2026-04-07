/*
 * Pr03_PosSpeed.h
 *
 *  Created on: 2018年11月29日
 *      Author: zhuxc
 */

#ifndef Pr03_PosSpeed_H
#define Pr03_PosSpeed_H
/*--------------------------------------------------------------------------------------------------*/
/*		PR模式——位置速度模式变量结构体																*/
/*--------------------------------------------------------------------------------------------------*/
typedef struct
{
    /*----------------------------------------------------------------------------------------------*/
    LONG   ProfRefSpdQ15;               /* 目标速度                                                 */
    LONG   AccBaseQ15;                  /* 加速基值                                                 */
    LONG   DecBaseQ15;                  /* 减速基值                                                 */
}PR_POSSPEED;

extern PR_POSSPEED PrPosSpdP;
extern void PrPosSpdCoeffCount( void );
extern LONG PrPosSpeedDeal( LONG PosSpd_Q15 );
#endif
