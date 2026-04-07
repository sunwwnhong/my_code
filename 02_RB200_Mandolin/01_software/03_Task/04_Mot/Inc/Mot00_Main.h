/*
 * Mot00_Main.h
 *
 *  Created on: 2017年2月28日
 *      Author: zhuxc
 */
#ifndef Mot00_Main_H
#define Mot00_Main_H
 
  
#include "Mot01_ScanA.h"
#include "Mot02_ScanB.h"
#include "Mot03_ScanC.h"
#include "Mot05_Round.h"
#include "Mot05_VarDef.h"
#include "Mot06_MotorParamTable.h"
#include "Mot07_MotorParamCal.h"
#include "Mot08_BaseParamCalc.h"
#include "Mot09_StateMachine.h"
#include "Mot10_ServoControl.h"
#include "Mot12_MoSenclf.h"
#include "Mot13_MoSpeedlf.h"
#include "Mot14_MRev.h"
#include "Mot15_Voltage.h"
#include "Mot16_Temperature.h"
#include "Mot17_MakeMonitorData.h"
#include "Mot21_VibCheck.h"
#include "Mot22_GainSel.h"
#include "Mot23_GainTable.h"
#include "Mot26_TurnLib.h"
#include "Mot27_SvcDataTrace.h"   
#include "Mot28_OnlineFFT.h"   
#include "Mot29_DtraceMngr.h"
#include "Mot30_DtraceExe.h"
#include "Mot31_TableExe.h"
#include "Mot32_JatOffLine.h"
#include "Mot33_AutoNotchSet.h"
#include "Mot34_TuningLess.h"
#include "Mot35_MotorRunOver.h"
#include "Mot36_MotorStall.h"
#include "Mot38_AI12Deal.h"
#include "Mot39_RegPowerProtect.h"
#include "Mot40_ALMDeal.h"
#include "Mot41_ServoStatus.h"
#include "Mot42_ABSReq.h"
#include "Mot43_DBBrakeProtect.h"
#include "Mot50_DIDO.h"
#include "Mot51_PanOper.h"
#include "Mot53_ParamMngr.h"
#include "Mot54_ParamEeprom.h"
#include "Mot55_ErrorDeal.h"
#include "Mot56_STO.h"
#include "Mot59_FactoryTest.h"
#include "Mot60_InformationCheck.h"
#include "Mot61_MotorLessTest.h"
#include "Mot62_DriveType.h"
#include "Mot63_MulAxis_485.h"
#include "Mot64_SerialNum.h"
  
#include "Seq00_Main.h"
#include "Seq01_MakeSeqSignal.h"
  
#include "Enc01_Encode.h"
#include "Enc02_EncAlarm.h"
#include "Enc04_EncEepDataSumCheck.h"
#include "Enc07_TamagawaEnc.h"
#include "Enc08_EncSoftLimit.h"
 
  
typedef	struct
{
    VULONG  ScanAcnt;               // ScanA中断执行计数器
    VULONG  ScanBcnt;               // ScanB中断执行计数器
    VULONG  ScanCcnt;               // ScanC中断执行计数器
    VULONG  ScanNcnt;               // ScanN中断执行计数器
    VULONG  ScanAMonCnt;            // ScanA中断时序检查计数器
    VULONG  Roundcnt;               // Round 执行计算器
    ULONG   CurExeTimeA;            // ScanA当前执行时间  [1/CPU_FRTMCNTUS us]
    ULONG   CurExeTimeB;            // ScanB当前执行时间  [1/CPU_FRTMCNTUS us]
    ULONG   CurExeTimeC;            // ScanC当前执行时间  [1/CPU_FRTMCNTUS us]
    ULONG   CurExeTimeR;            // ScanN当前执行时间  [1/CPU_FRTMCNTUS us]
    ULONG   CurExeTimeE;            // ScanE当前执行时间
    ULONG   MaxExeTimeA;            // ScanA最大执行时间
    ULONG   MaxExeTimeB;            // ScanB最大执行时间
    ULONG   MaxExeTimeC;            // ScanC最大执行时间
    ULONG   MaxExeTimeR;            // ScanN最大执行时间
    ULONG   MaxExeTimeE;
    struct {
        UINT	Pulse100ms		:1;      // 100ms 标志位
        UINT    ScanB250us      :1;      // 250us
        } f;
    USHORT  TmStampCntx;            // 时间戳计数器
    ULONG   TmStamp;                // 时间戳
    ULONG   TmStampSaveCnt;         // 时间戳保存计数
    ULONG   MainTimer;              // 主程序运行时间计时,用于绝对值编码器上电时电机欠压
    USHORT  KnlMode;                // 基带模式
    USHORT  ServoStatus;            // 伺服驱动器运行状态
    USHORT  EtherCatStatus;         // EtherCat运行状态
} KNLV;
  
  
  
/************************************相关变量初始化 ******************************************/
typedef  struct
{
    UCHAR  AdjPumponReq;                //  调整模式PUMPON请求
    UCHAR  ScanCstrtCnt;                //  ScanC 启动计数器,仅每个ScanB结尾++
    UCHAR  ScanCexeEndf;                //  ScanC 执行结束标志,ScanB启动ScanC时置0，ScanC结束置TRUE
    UCHAR  ScanAstopCnt;                //  ScanA 停止检查计数器
    ULONG  ScanAcntChkx;                //  ScanA 执行计数检查
    USHORT TmStampCntx;                 //  TimeStamp运算用计数器
#if CCSW_NETID == NETID_CMDPM
    USHORT LstStartTime;                //  CMSINT信号计时器捕捉上次值
#else
    USHORT Spare00;                     //   < Spare >
#endif
} KNXV;

extern KNXV	KnxV;
extern KNLV KnlV;
extern USHORT KpiRstShortTimer( USHORT *timer );
extern USHORT KpiGetShortTimer( USHORT *timer );
extern void Mot00_Main_Init(void);
#endif
