/*
 * Mot17_MakeMonitorData.h
 *
 *  Created on: 2018年06月13日
 *      Author: zhuxc
 */
#ifndef Mot17_MakeMonitorData_H
#define Mot17_MakeMonitorData_H
  
  
  
typedef	struct									 
{
    LONG	Kcurload;       //有效扭矩(电流)运算增益
    LONG	Kcurloadcycle;  //有效转矩（电流）计算增益 Un142
} CIOXP;
 
typedef	struct
{
    struct {
    UINT	LastAlmStatus	:1;     //上次报警状态
    UINT	Sample00		:1;
    UINT	Sample01		:1;
    } b;
    LONG    IsqrSum;                        //用于监控电流负载计算
    LONG    IsqrSum1;                       //用于监控电流负载计算
    LONG    UnIsqrSum;                      //平方电流积分值： Σ（（I*I）>>14）
    LONG    UnIsqrSumMax;                   //最大电流积分平方值 （Un145）
    LONG    Pfbk64Sum;                      //用于监控电机转速计算
    LONG    Pcmd64Sum;                      //用于监视器的命令脉冲率计算
    LONG    MotSpd64Sum;                    //用于监控电机转速计算
    LONG    FencSpd64Sum;                   //用于负载端转速计算

    LONG    FensePul;
    LONG    FensePulLst;
    LONG    FensePulSum;
    LONG    FenseSumCnt;

    USHORT  IsqrSumCnt;                     //用于监控电流负载计算
    USHORT  IsqrSumCnt1;                    //用于监控电流负载计算
    USHORT  Pfbk64SumCnt;                   //用于监控电机转速计算
    USHORT  AlmLatchSeqPtr;                 //监控报警时的锁存序列指针
    USHORT  MtrgStatus;
    USHORT  MtrgFlg;
    ALMLTMON    AlmLtMon;
} CIOXV;

extern CIOXP	CioxP;
extern CIOXV	CioxV;							 
 
extern void	LpxMakeMonitorData( void );
extern void	IprmcalCurrentLoadGain( void );
 #endif

/*--------------------------------------------------------------------------------------------------*/
/*                                          End of The File                                         */
/*--------------------------------------------------------------------------------------------------*/
