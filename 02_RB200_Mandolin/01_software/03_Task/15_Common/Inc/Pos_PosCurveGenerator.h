/*
 * Pos_PosCurveGenerator.h
 *
 *  Created on: 2018年07月02日
 *      Author: zhuxc
 */


#include "EtherCAT_Main.h"

#ifndef Pos_PosCurveGenerator_H
#define Pos_PosCurveGenerator_H

typedef struct
{
    INT64 PosSumIn;                         /* 输入脉冲和                                           */
    INT64 PosSumOut;                        /* 输入脉冲和                                           */
    INT64 PosRemain;                        /* 位置指令余量                                         */
    INT64 ProfRefMaxSpdQ15;                 /* 定位最大速度 Q15                                     */
    INT64  PosRefSpd;                        /* 参考目标速度                                         */
    INT64 TurningPosABS;                    /* 减速位置点                                           */
    INT64 SpdOutQ15;                        /* 输出: 输出速度值                                     */
    INT64 SpdOutABSQ15;                     /* 速度输出绝对值                                       */
    INT64 PosCmdABS;                        /* 速度输出值                                           */
    INT64 PosCmdRemABS;                     /* 速度命令余数                                         */
    INT64 PosCmdOut;                        /* 位置命令输出                                         */
    INT64 InsertPosABS;                     /* 减速时位置计算                                       */
    INT64 PosSpdCmd;                         /* 位置输出对应速度值                                   */
    UCHAR PosCase;                          /* 位置区间判断                                         */
    UCHAR PosBlock;                         /* 位置块                                               */
    UCHAR TargetReach;                      /* 位置到达                                             */
    UCHAR Pos1TarReach;
}POSCURVEGENERATOR_V;
typedef struct
{
    LLONG  TargetPos;                       /* 输入：目标位置值                                     */
    LLONG  ProfRefSpdQ15;                   /* 输出：最大定位速度 Q15                               */
    LLONG  AccBaseQ15;                      /* 输出：加速基值 Q15                                   */
    LLONG  DecBaseQ15;                      /* 输出：减速基值 Q15                                   */
}POSCURVEGENERATOR_P;


extern POSCURVEGENERATOR_P PosCurvP;
extern POSCURVEGENERATOR_V PosCurvV;


extern void EthercatPosParameterUpdate( void );
extern void PosCurveGenerator_Deal( void );
extern void PosCurGenerator_Clear( void );
#endif
