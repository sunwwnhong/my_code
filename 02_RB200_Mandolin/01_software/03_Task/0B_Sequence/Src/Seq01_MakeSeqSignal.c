/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Seq01_MakeSeqSignal.c
* Version            : V0.1
* Date               : 2024
* Description        : 伺服使能状态判定
***********************************************************************************************/
#include "Main.h"
 
 enum	KNLMODE	{
		KPI_KMD_NORMAL		  = 0x00,
		KPI_KMD_ADJREFAD		,
		KPI_KMD_ADJCURAD		,
		KPI_KMD_SOFTRESET		,
		KPI_KMD_PARAMRESET		,
};
  
/**********************************************************************************************/
/* Function_Name: LpxMakeSequenceSignal                                                      */
/* Description  : 伺服使能状态判定
               调用：ScanC
               输入：CoutK.f.PowerOn                    电压模块输出
                     CoutV.f.Sv.AlmReady             无故障
                     CinK.f.EncReady                 位置信息处理
                     RoutV.f.RndReady                循环运行标志，主循环置位
                     CoutV.f.Sv.HwbbState            硬件基级封锁（暂时未用）
                     CurrentSample.CurFlg.f.ZeroOk   电流采集完成标识
               输出：CoutV.f.Sv.SvonReq常规模式下伺服使能请求（作为抱闸逻辑的输入条件）
                     CinV.f.Sv.PoleDetect 常规模式下磁极搜索请求
                     CoutV.f.Sv.SvonRef（伺服ON无效判定用）*/
/**********************************************************************************************/

 void	LpxMakeSequenceSignal( void )
{
     /*伺服上电、无故障、编码器准备好、主循环置位、电流采样校准完成、
       基级未封锁条件、磁极搜索已完成条件下，伺服ready状态置位          */
     if( CoutK.f.PowerOn && \
        CoutV.f.Sv.AlmReady && \
        RoutV.f.RndReady && \
        CurrentSample.CurFlg.f.ZeroOk)
    {
        CoutV.f.Sv.SvReadyPhaseIgnore   = TRUE;
        CoutV.f.Seq.ServoReady          = (MencV.f.PhaseReady)? TRUE : FALSE;   //PhaseReady:电机相位已知
    }
     else
    {
        CoutV.f.Sv.SvReadyPhaseIgnore   = FALSE;                         
        CoutV.f.Seq.ServoReady          = FALSE;                         
    }
  
  
    if( KnlV.KnlMode == KPI_KMD_NORMAL )
    {
          
         if( CoutK.f.RndSvControl == TRUE )     //辅助功能伺服控制使能有效（部分Fn功能开启)
        {
              
            if ( MencV.f.PhaseReady )            //电机相位已知
            {
                //辅助功能伺服使能请求
                CoutV.f.Sv.SvonReq = (RoutV.f.SvonReq == TRUE)? TRUE : FALSE;
            }
             else
            {
                //辅助功能磁极搜索请求
                CoutV.f.Sv.SvonReq = (RoutV.f.PdetReq == TRUE)? TRUE : FALSE;
            }
              
              
            if( MencV.f.PhaseReady )
            {
                CoutV.f.Sv.SvonRef = (RoutV.f.SvonReq)? TRUE : FALSE;
            }
             else
            {
                CoutV.f.Sv.SvonRef = (RoutV.f.SvonReq || RoutV.f.PdetReq)? TRUE : FALSE;
            }
         }
          
         else
        {
            if ( MencV.f.PhaseReady )
            {
                  
                 CoutV.f.Sv.SvonReq = (CinV.f.Seq.ServoOn == TRUE)? TRUE : FALSE;
            }
            else
            {
                  
                 CoutV.f.Sv.SvonReq = (CinV.f.Sv.PoleDetect == TRUE)? TRUE : FALSE;
            }
              
              
              
             if( MencV.f.PhaseReady )
            {
                CoutV.f.Sv.SvonRef = (CinV.f.Seq.ServoOn)? TRUE : FALSE;
            }
            else
            {
                CoutV.f.Sv.SvonRef = (CinV.f.Seq.ServoOn || CinV.f.Sv.PoleDetect)? TRUE : FALSE;
            }
         }
    }
     else
    {
        CoutV.f.Sv.SvonReq = FALSE;
        CoutV.f.Sv.SvonRef = FALSE;
    }
      
      
    CoutK.f.SvonReq = ( CoutV.f.Sv.SvonReq )? TRUE : FALSE;
  
  
    SvSeqV.AlmStopMode = SvSeqV.OperateAlmStopMode;

    /*  转矩控制、Gr.2停机方式参考Pn004设定为1时、全闭环位置偏差过大、
        硬件基波封锁、相位信息未获取时按照Pn004设定的停机方式执行    */
    if(SvSeqV.AlmStopMode == STOPMODE_ZEROSTOP)
    {
        if((BoutV.CtrlMode.b.cm  == CTRLMODE_TRQ)        ||		 
           (Iprm.f.G2AlmStopMode == TRUE)                ||		 
           (CoutV.f.Sv.HwbbState == TRUE)                ||		 
           (!MencV.f.PhaseReady) )							     
        {
            SvSeqV.AlmStopMode = Iprm.StopMode;				     
        }
    }
  
     if( SvSeqV.AlmStopMode == STOPMODE_ZEROSTOP )
    {
          
         if( CoutV.f.Sv.MotStop )     //转速状态
        {                                                   
            SvSeqV.f.AlmZstopFinish = TRUE;
        }
          
         SvSeqV.f.AlmZeroStop = (SvSeqV.f.AlmZstopFinish == FALSE)? TRUE : FALSE;
    }
     else
    {
        SvSeqV.f.AlmZeroStop    = FALSE;    //零速停机标志
        SvSeqV.f.AlmZstopFinish = FALSE;    //零速停机完成标识
    }
     return;
}
  
  
 /**********************************************************************************************/
 /* Function_Name: CpiGetRoundServoControl                                                    */
 /* Description  :
                   调用：辅助功能
                   输出：*/
 /**********************************************************************************************/
  
 LONG	CpiGetRoundServoControl( LONG NormalOpeDrv )
{
LONG    rc;
     KPI_DI( );
      
     if( CoutV.f.Sv.SvonRef == FALSE )
    {
          
         if( NormalOpeDrv == TRUE )
        {
            CoutV.NormalOpeDrive = TRUE;                     
        }
        else
        {
            CoutV.NormalOpeDrive = FALSE;                    
        }
        CoutK.f.RndSvControl = TRUE;
        rc = TRUE;
    }
    else
    {
        rc = FALSE;
    }
     KPI_EI( );
    return( rc );
 }
  
  
/**********************************************************************************************/
/* Function_Name: CpiFreeRoundServoControl                                                   */
/* Description  :
               调用：辅助功能
               输出：*/
/**********************************************************************************************/
void	CpiFreeRoundServoControl( void )
{
    CoutK.f.RndSvControl = FALSE;
    return;
}
  
/**********************************************************************************************/
/* Function_Name: LpxCheckSvonCmdInvalid                                                      */           
/* Description  : 外部使能无效标志位
				  调用：ScanC
				  输出：     */
/**********************************************************************************************/
void LpxCheckSvonCmdInvalid( void )
{
  
  
    if( ( CoutK.f.RndSvControl == TRUE ) && ( CoutV.NormalOpeDrive == TRUE ) )
    {
        ChkAlmV.f.OperatorDrive = TRUE;  						 
    }
  
 	else
        if( ( ChkAlmV.f.OperatorDrive == TRUE ) && ( CinV.f.Seq.ServoOn == TRUE ) )
		{
			KPI_ALARMSET  ( ALM_SVONCMD );						 
		}
  
     if(ChkAlmV.f.OperatorDrive && !CoutK.f.RndSvControl)
    {
        ChkAlmV.f.OperatorDrive = FALSE;
    }
 	return;
 }
