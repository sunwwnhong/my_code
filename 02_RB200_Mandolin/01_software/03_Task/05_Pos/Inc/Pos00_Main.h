/*
 * Pos00_Main.h
 *
 *  Created on: 2018年1月31日
 *      Author: zhuxc
 */
#include "MlibSvc.h"
#include "Mot05_VarDef.h"
#ifndef Pos00_Main_H
#define Pos00_Main_H
#include "Pos01_PosCmd.h"
#include "Pos16_PosCmdMange.h"
#include "Pos02_PosStatus.h"
#include "Pos03_PcmdFilter.h"
#include "Pos04_Gear.h"
#include "Pos05_MFC.h"
#include "Pos06_PosPICoeff.h"
#include "Pos07_PosClr.h"
#include "Pos08_PosFF.h"
#include "Pos09_RemVibration.h"
#include "Pos11_PrgJog.h"
#include "Pos12_PErrClr.h"
#include "Pos13_PosPerfMonit.h"
#include "Pos15_FullClosed.h"
#include "Pos17_BacklashComp.h"
#include "Pos18_MIT.h"
 
  
 
typedef	struct	{
    PERRA   PosErrA;            //ScanA获取的位置误差（Unit）
    LONG    dPcmdEgear;         //位置给定增量（电子齿轮后）
    LONG    dPcmdEgrem;         //电子齿轮比单位转换余数
    LONG    dPcmda;             //位置给定增量(Unit)
    LONG    PosErr;             //位置误差（pul）
    LONG	Per64[2];
    LONG	LastdPcmda;
    USHORT  PossErrCnt0;        //位置偏差过大计数器0
    USHORT  PossErrCnt1;        //位置偏差过大计数器1
    UCHAR   SOnStatus;          //伺服使能电平状态
    UCHAR   EgearDisable;       //电子齿轮比使能状态
    UCHAR	OTStatus;		    //超程限位状态
} POSMNGV;
  
typedef	struct	{
    struct	{
    LONG	Kpi;	            //位置控制积分增益
    LONG	Kpd;			    //位置控制微分增益（暂未用）
    LONG	VelBias;		    //位置输出偏置（暂未用）
    LONG	BiasAddLevel;
#if (FLOAT_USE == 1)
    float   fKdPff;             //位置指令前馈增益
    float   fKdPffFil;          //位置指令前馈滤波增益系数
#else
    LONG    KdPff;
    LONG    KdPffFil;
#endif
    } P;
    struct {
        LONG    SpdRef;                 //位置控制模块输出
        LONG    PerIvar64[2];           //位置量积分累计值
        LONG    PacOut;                 //位置控制比例输出
        LONG    IacOut;                 //位置控制积分输出
        LONG    DacOut;                 //位置控制微分输出
        LONG    LastPacOut;             //位置控制比例输出（上一周期）
#if (FLOAT_USE == 1)
        float   fdPFfFilo;              //位置指令前馈滤波值
#else
    LONG    dPFfFilo;
#endif
    } V;
} POSCTRL;
extern POSMNGV PosMngV;   //位置控制管理结构体变量
extern POSCTRL PosCtrl;   //位置控制器结构体变量
 
extern LONG BasePositionControl( LONG , LONG , LONG , LONG ,LONG );
extern void InitPosCtrlModeVar( void );
extern void InitBasePositionControl( void );
 
#endif
