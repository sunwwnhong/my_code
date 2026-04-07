/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Pos08_PosFF.c
* Version            : V0.1
* Date               : 2023
* Description        : 前馈控制
***********************************************************************************************/
  

  
#include "Main.h"
 

/**********************************************************************************************/
/* Function_Name: PcaldPosRefFFGain                                                  */
/* Description  :位置前馈增益参数计算
           输入：Kpx：位置增益系数
                 CycleUs：前馈计算执行周期
                 FFgain：前馈增益 （%）
           输出：PosCtrl.P.KdPff                                                              */

/**********************************************************************************************/
void PcaldPosRefFFGain( void )
{
#if (FLOAT_USE == 1)
    float fkx;
    fkx = Hprm.fKpx * 1000000.0f / (float)Iprm.SvCycleUs;
    PosCtrl.P.fKdPff = fkx * (float)Prm.ffgn * 0.01f;
#else
	LONG kx;
	LONG sx;
	kx = MlibScalKskxkx( Hprm.Kpx, 1000000, Iprm.SvCycleUs, &sx, 0 );
	PosCtrl.P.KdPff = MlibPcalKxgain( kx, Prm.ffgn, 100, &sx, 24 );
#endif
	return;
}
  
  
/**********************************************************************************************/
/* Function_Name: PcaldPosRefFFFilter                                                  */
/* Description  :位置前馈增益滤波参数计算
           输入：Kpx：位置增益系数
                 CycleUs：前馈计算执行周期
                 FFgain：前馈增益 （%）
           输出：PosCtrl.P.KdPffFil                                                             */

/**********************************************************************************************/
void PcaldPosRefFFFilter( void )
{
#if (FLOAT_USE == 1)
    PosCtrl.P.fKdPffFil = FlibPcalKf1gain( Prm.fffil * 10, Iprm.SvCycleUs, 0 );
#else
    PosCtrl.P.KdPffFil = MlibPcalKf1gain( Prm.fffil * 10, Iprm.SvCycleUs, 0 );
#endif
    return;
}
  
  
/**********************************************************************************************/
/* Function_Name: dPosRefFeedForward                                                      */
/* Description  :速度前馈量计算（非MFC控制下有效）
           输入：dPosRef：位置增量输入
                 SpdFFOut: 速度前馈原指令
           输出：SpdFFOut：速度前馈量输出                                                     */
/**********************************************************************************************/
void dPosRefFeedForward( LONG  dPosRef )
{
#if (FLOAT_USE == 1)
    float fSpdFFx;

    /* 速度前馈值计算与限制 */
    fSpdFFx              = (float)dPosRef * PosCtrl.P.fKdPff;
    if( fSpdFFx > 16777216.0f )
    {
        fSpdFFx = 16777216.0f;
    }
    else if( fSpdFFx < -16777216.0f)
    {
        fSpdFFx = -16777216.0f;
    }

    /* 速度前馈值滤波 */
    PosCtrl.V.fdPFfFilo  = FlibLpfilter1( fSpdFFx, PosCtrl.P.fKdPffFil, PosCtrl.V.fdPFfFilo );
    BoutV.SpdFFCx      += (LONG)PosCtrl.V.fdPFfFilo;
    //BoutV.SpdFFCx = PosCtrl.V.fdPFfFilo;
#else
	LONG SpdFFx;
	SpdFFx				= MlibMulgain( dPosRef, PosCtrl.P.KdPff );
	PosCtrl.V.dPFfFilo  = MlibLpfilter1( SpdFFx, PosCtrl.P.KdPffFil, PosCtrl.V.dPFfFilo );
	BoutV.SpdFFCx	   += PosCtrl.V.dPFfFilo;
#endif
	return;
}
 
/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/
