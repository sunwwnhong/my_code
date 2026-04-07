/*
 * Pos03_PcmdFilter.h
 *
 *  Created on: 2018年06月20日
 *      Author: zhuxc
 */
#ifndef Pos03_PcmdFilter_H
#define Pos03_PcmdFilter_H
  
  
/*--------------------------------------------------------------------------------------------------*/
/*      移动平均滤波器参数变量定义                                                       */
/*--------------------------------------------------------------------------------------------------*/
typedef struct  {                                   /* 移动平均滤波器参数变量定义        */
    struct  {                                   /* 移动平均滤波器用参数                           */
    LONG    PmafNum[2];                         /* 移动平均次数=移动平局时间/控制周期           */
    UCHAR   ImafSft[2];                         /* 插值移动平均次数(2^Sft)                      */
    UCHAR   SpareByte[2];                       /* 予備                                           */
    } P;
/*----------------------------------------------------------------------------------------------*/
    struct  {                                   /* 移动平均数据滤波用变量                      */
    LONG    pcmdinx;                            /* 长时间插值移动平均滤波器插值周期内的累加值    */
    LONG    pcmdiny;                            /* 长时间插值移动平均滤波器演算用              */
    LONG    index;                              /* 插值移动平均滤波器index                       */
    LONG    Filo;                               /* 滤波器输出                                    */
    PMAFV   Pmafvar;                            /* 移动平均滤波器运算变量结构                    */
    PIMFV   Pimfvar;                            /* 插值移动平均滤波器运算变量结构              */
    } V;
} MAFIL;

extern void	BpxInitPcmdFilter( void );
extern LONG	BpxPcmdFilter( LONG pcmdin );
extern void	PcalPcmdExpFilter( USHORT PrmTime, LONG Flag );
extern void	PcalPcmdMoveAvergeFilter( USHORT PrmTime, LONG Flag );
extern void	BpiStopPcmdFilter( void );
extern void	BpiRunPcmdFilter( void );
extern void	PcalPcmdAvffFilter( void );
extern void	PcalPcmdAvffFilterSel( void );
extern LONG	BpxPcmdAvffFilter( LONG dPcmd );
extern void	PcalPcmdExpFilBias( void );

extern LONG PcmdMoveAvergeFilter( LONG pcmdin );
#endif
