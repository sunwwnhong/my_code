/*
 * Pos05_MFC.h
 *
 *  Created on: 2018年 08月30日
 *      Author: zhuxc
 */
#ifndef Pos05_MFC_H
#define Pos05_MFC_H
#define MODELFOLLOW_CTRL 1
 
/*--------------------------------------------------------------------------------------------------*/
/*      MFC参数与变量定义                                                                      */
/*--------------------------------------------------------------------------------------------------*/
typedef	struct	{
    LONG    Fsft;                               /* DTR高阶滤波器分辨率位移量                    */
    LONG    InvFsft;                            /* DTR高阶滤波器分辨率位移量导数                 */
    LONG    Kf1[2];                             /* 2阶滤波器增益1                             */
    LONG    Kf2;                                /* 2阶滤波器增益2(1阶微分滤波器用)              */
    LONG    Kf3;                                /* 2阶滤波器增益3(1阶微分滤波器用)               */
    LONG    Kj1;                                /* 机械增益系数1                              */
    LONG    Kj2;                                /* 机械增益系数2                              */
    LONG    Kj2_sft;                            /* 机械增益系数2(分解能UP用???なし)         */
    LONG    Kj3;                                /* 机械增益系数3                                */
    LONG    Kvff;                               /* 速度前馈增益                                 */
    LONG    Ktff1;                              /* 转矩前馈增益1(正转)                          */
    LONG    Ktff2;                              /* 转矩前馈增益2(反转)                          */
    LONG    Cfric;                              /* 库仑摩擦力补偿转矩                            */
    LONG    Kfcf;                               /* 库仑摩擦力补偿滤波器增益                     */
    USHORT  Fccflag;                            /* 二惯量系统下的全闭环控制标识                   */
    USHORT  PSFccflag;                          /* 二惯量系统下的速度反馈来源于负载编码器      */
    UCHAR   MFCModel;                           /* 机械模型, Pn240.10=01时,ONE_MASS, Pn240.10=11或21时,ONE_BASE    */
    UCHAR   MFC_type;                           /* MFC控制类型选择Pn248.X, 0:SGDX_TYPE(只有需要与以往产品兼容时), 1:SGDV_TYPE(默认) */
} MFCP;
typedef	struct	{								     
    MFCP    P[3];                               /* MFC控制参数组,P[0]为实际执行的控制参数，
                                                     P[1]是第1模型增益参数，P[2]是第2模型增益参数*/
    MFCP    Pexe;                               /* MFC实际执行的控制参数                        */
    /*----------------------------------------------------------------------------------------------*/
    struct {                                    /* MFC控制模块变量                              */
    LONG    execnt;                             /* MFC执行周期计数（用于二惯量模型时序处理）    */
    LONG    MfcPosErr;                          /* 模型位置偏差(计算用)  [pulse]                 */
    LONG    PosErr;                             /* 模型位置偏差(监控用)  [pulse]                 */
    LONG    Per64[2];                           /* 模型位置偏差(计算用)  [pulse]                 */
    LONG    Vref;                               /* 模型速度指令               [2^24/OvrSpd]       */
    LONG    Pfbk;                               /* 模型位置反馈               [pulse/Scan]        */
    /*----------------------------------------------------------------------------------------------*/
    LONG    Fwk1[2];                            /* 2阶滤波器计算用                             */
    LONG    Fwk2[2];                            /* 2阶滤波器计算用                             */
    LONG    Fwk3[2];                            /* 2阶滤波器计算用                             */
    LONG    Fwk4[2];                            /* 2阶滤波器计算用                             */
    LONG    Filo;                               /* 一阶差分二次滤波器后位置指令               */
    LONG    FCmdF;                              /* 二阶滤波器后位置指令               */
    LONG    dFilwk;                             /* 用于一阶微分二阶滤波器计算                    */
    LONG    Fwkrem1;                            /* 用于一阶微分二阶滤波器计算                    */
    LONG    Fwkrem2;                            /* 用于一阶微分二阶滤波器计算                    */
    /*----------------------------------------------------------------------------------------------*/
    LONG    PCmdsub;                            /* 位置指令输入                                   */
    LONG    FCmd[3];                            /* 高次滤波后位置指令                            */
    LONG    dFCmd[2];                           /* 高次滤波后位置指令１阶微分值                   */
    LONG    d2FCmd[2];                          /* 高次滤波后位置指令2阶微分值                   */
    LONG    d3FCmd;                             /* 高次滤波后位置指令3 阶微分値                  */
    LONG    wkrem1;                             /* 位置指令演算用                              */
    LONG    wkrem2;                             /* 位置指令演算用                              */
    LONG    PosSum[2];                          /* 位置指令累计值                              */
    LONG    TrqRef;                             /* 模型转矩指令                                   */
    LONG    Ktffcmdx;                           /* 转矩FF增益                                   */
    LONG    FricCmpTrq;                         /* 库仑摩擦力补偿转矩                            */
    LONG    FCmdFilo[3];                        /* 高阶滤波器后位置命令（分辨率UP计算）          */
    /*----------------------------------------------------------------------------------------------*/
    LONG    PffCmd;                             /* 位置校正指令                             */
    LONG    VffCmd;                             /* 速度前馈增量                               */
    LONG    TffCmd;                             /* 转矩前馈增量                               */
    } V;
} MFCTRL;

extern MFCTRL		Mfc;
extern void BpxInitMfcModelControl( void );
extern void	BpiStopMfcCtrl( void );
extern void	BpiRunMfcCtrl( void );
extern SHORT BpiGetMfcParamEnableSts( void );
extern void	PcalMfcModelControl(USHORT,USHORT,USHORT,USHORT,USHORT,USHORT,USHORT,USHORT,LONG);
extern void	PcalMfcModelControlSel( void );
extern void IprmcalMfcTypeSel( void );
extern LONG	BpxMfcModelControl( LONG dPcmd );
#endif
 
 
/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/
