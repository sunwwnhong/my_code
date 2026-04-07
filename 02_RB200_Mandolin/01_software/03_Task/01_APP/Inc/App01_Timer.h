/*
 * App01_Timer.h
 *
 *  Created on: 2022年7月11日
 *      Author: zhuxc
 */

#ifndef App01_Timer_H
#define App01_Timer_H


#define KNLFSEL_MEASURE_SCANA_EXETIME   1       //SCANA执行时间测算开启
#define KNLFSEL_MEASURE_SCANB_EXETIME   1       //SCANB执行时间测算开启
#define KNLFSEL_MEASURE_SCANC_EXETIME   1       //SCANC执行时间测算开启
#define KNLFSEL_MEASURE_SCANR_EXETIME   1       //SCANR执行时间测算开启
#define KNLFSEL_MEASURE_SCANE_EXETIME   1       //SCANE执行时间测算开启

//-------------------------------------------------------------------------------------------------
#define CPU_FRTMREG                 (HWREG(CPUTIMER1_BASE + CPUTIMER_O_TIM))
#define KPX_RST_STRTIMEX(st)        { st = CPU_FRTMREG;}                    // 当前计时器值的获取
#define KPX_GET_CURTIMEX(ct,st)     { ct = (ULONG)(st - CPU_FRTMREG);}      // 计算运行执行时间
#define KPX_UPD_MAXTIMEX(mt,ct)     { if( ct > mt ){ mt = ct;} }            // 最大运算时间的获取
#define KPX_GET_EXETIMEX(mt,ct,st)  { KPX_GET_CURTIMEX( ct, st ); KPX_UPD_MAXTIMEX( mt, ct );}

//-------------------------------------------------------------------------------------------------
//  ScanA 运行时间测算处理
//-------------------------------------------------------------------------------------------------
#if KNLFSEL_MEASURE_SCANA_EXETIME == 0
#define KPX_RST_SCANA_STRTIME( st ) { ;}
#define KPX_GET_SCANA_EXETIME( st ) { ;}
#else
#define KPX_RST_SCANA_STRTIME( st ) { KPX_RST_STRTIMEX( st );}
#define KPX_GET_SCANA_EXETIME( st ) { KPX_GET_EXETIMEX( KnlV.MaxExeTimeA, KnlV.CurExeTimeA, st );}
#endif
//-------------------------------------------------------------------------------------------------
//  ScanB 运行时间测算处理
//-------------------------------------------------------------------------------------------------
#if     KNLFSEL_MEASURE_SCANB_EXETIME == 0
#define KPX_RST_SCANB_STRTIME( st ) { ;}
#define KPX_GET_SCANB_EXETIME( st ) { ;}
#else
#define KPX_RST_SCANB_STRTIME( st ) { KPX_RST_STRTIMEX( st );}
#define KPX_GET_SCANB_EXETIME( st ) { KPX_GET_EXETIMEX( KnlV.MaxExeTimeB, KnlV.CurExeTimeB, st );}
#endif
//-------------------------------------------------------------------------------------------------
//  ScanC 运行时间测算处理
//-------------------------------------------------------------------------------------------------
#if     KNLFSEL_MEASURE_SCANC_EXETIME == 0
#define KPX_RST_SCANC_STRTIME( st ) { ;}
#define KPX_GET_SCANC_EXETIME( st ) { ;}
#else
#define KPX_RST_SCANC_STRTIME( st ) { KPX_RST_STRTIMEX( st );}
#define KPX_GET_SCANC_EXETIME( st ) { KPX_GET_EXETIMEX( KnlV.MaxExeTimeC, KnlV.CurExeTimeC, st );}
#endif
//-------------------------------------------------------------------------------------------------
//  ScanN 运行时间测算处理
//-------------------------------------------------------------------------------------------------
#if     KNLFSEL_MEASURE_SCANR_EXETIME == 0
#define KPX_RST_SCANN_STRTIME( st ) { ;}
#define KPX_GET_SCANN_EXETIME( st ) { ;}
#else
#define KPX_RST_SCANR_STRTIME( st ) { KPX_RST_STRTIMEX( st );}
#define KPX_GET_SCANR_EXETIME( st ) { KPX_GET_EXETIMEX( KnlV.MaxExeTimeR, KnlV.CurExeTimeR, st );}
#endif

//-------------------------------------------------------------------------------------------------
//  ScanE 运行时间测算处理
//-------------------------------------------------------------------------------------------------
#if     KNLFSEL_MEASURE_SCANE_EXETIME == 0
#define KPX_RST_SCANE_STRTIME( st ) { ;}
#define KPX_GET_SCANE_EXETIME( st ) { ;}
#else
#define KPX_RST_SCANE_STRTIME( st ) { KPX_RST_STRTIMEX( st );}
#define KPX_GET_SCANE_EXETIME( st ) { KPX_GET_EXETIMEX( KnlV.MaxExeTimeE, KnlV.CurExeTimeE, st );}
#endif

//-------------------------------------------------------------------------------------------------
extern void InitCpu1_Timer( void );


#endif

