/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Seq02_MechaBrakeSequence.c
* Version            : V0.1
* Date               : 2024
* Description        : 机械抱闸时序
***********************************************************************************************/
#include "Main.h"
 
  
  
  
  
  
  
/**********************************************************************************************/
/* Function_Name: LpxMechaBrakeSequence                                                      */
/* Description  : 根据抱闸时序，执行抱闸动作
                  调用：ScanC
                  输出：根据抱闸时序，执行抱闸动作*/
/**********************************************************************************************/
 void LpxMechaBrakeSequence( void )
{
CTRLMD	CtrlMode;
     CtrlMode.dw = BoutV.CtrlMode.dw;


     switch( SvSeqV.BkStep )
    {
         /* SETP 0:初始化抱闸状态，完成切换至1 */
         case 0:      
             SvSeqV.f.Brake      = TRUE;					       
            SvSeqV.f.BkZeroStop = FALSE;					   
            CinV.f.Seq.ServoOffDecM = 0;
            SvSeqV.BkWait       = 0;
            SvSeqV.BkStep       = 1;
            break;
        /* STEP1:等待伺服使能请求，有请求后，开始抱闸请求 */
        case 1:      
         if( CoutV.f.Sv.SvonReq && CoutV.f.Sv.SvReadyPhaseIgnore )
        {
            CoutV.f.Sv.BkBeReq = TRUE;
            /* 检测MOS管状态是否打开，打开后，等待抱闸延时后，松开抱闸，跳转STEP2 */
             if(Kprm.f.MotorLessTestMode == FALSE)		     
            {
                if( StateM_Var.f.PwmEn )            	     
                {
                     SvSeqV.BkWait += KPI_SCCYCLEMS;
                    if( SvSeqV.BkWait > Prm.brkOnDly )
                    {
                        SvSeqV.f.Brake = FALSE;				 
                        SvSeqV.BkWait = 0;
                        SvSeqV.BkStep = 2;
                    }
                }
                else
                {
                    SvSeqV.BkWait = 0;
                }
            }
             /* 伺服使能后，20ms后，松开抱闸，跳转至STEP2 */
             else                                             
            {
                if( CoutV.f.Sv.BaseEnable == TRUE)		     
                {
                    SvSeqV.BkWait += KPI_SCCYCLEMS;
                    if( SvSeqV.BkWait > 20 )                 
                    {
                        SvSeqV.f.Brake = FALSE;				 
                        SvSeqV.BkWait = 0;
                        SvSeqV.BkStep = 2;
                    }
                }
                else
                {
                    SvSeqV.BkWait = 0;
                }
            }
         }
        else
        {
            CoutV.f.Sv.BkBeReq      = FALSE;			     
            SvSeqV.BkWait           = 0;
            CinV.f.Seq.ServoOffDecM = 0;
        }
        break;
          
		case 2:
		    /* 在伺服使能请求下和故障零速请求时，维持STEP2 */
 			if( CoutV.f.Sv.SvonReq && CoutV.f.Sv.SvReadyPhaseIgnore ) 
			{
				;											 
			}
 			else if( SvSeqV.f.AlmZeroStop )					 
			{
				;											 
			}
 			/* 检测到外部断电后，开启抱闸，跳转至STEP4 */
             else if( CoutV.f.Seq.PowerOffflg == 1 )         
            {
				SvSeqV.f.Brake = TRUE;						 
				SvSeqV.BkStep = 4;
                SvSeqV.BkWait = 0;
            }
              
 			/*速度高于抱闸阈值时，不接受抱闸请求，跳转至STEP3*/
			else if( CinK.AbsMotSpd >= Gprm.BkonSpdLevel )	 
			{												 
				CoutV.f.Sv.BkBeReq = FALSE;					 
				SvSeqV.BkStep = 3;							 
			}
              
 			/*低于抱闸阈值时，非零速停机/伺服OFF抱闸延时时间到/基级封锁，跳转至STEP1,开启抱闸*/
			else if( ( SvSeqV.AlmStopMode > STOPMODE_ZEROSTOP ) ||
					 ( Gprm.BkonDelayTime == 0 ) || 
					 ( CoutV.f.Sv.HwbbState ) )
			{												 
				CoutV.f.Sv.BkBeReq = FALSE;					 
				SvSeqV.f.Brake = TRUE;						 
 				SvSeqV.BkStep = 1;							 
			}
              
              
			else											 
			{												 
				SvSeqV.f.Brake = TRUE;						 
 				if( CtrlMode.b.cm == CTRLMODE_TRQ )			 
					SvSeqV.f.BkZeroStop = FALSE;			 
				else
					SvSeqV.f.BkZeroStop = TRUE;				 
 				SvSeqV.BkStep = 4;
			}
 			break;
 		/* 等待转速低于抱闸阈值，或持续时间到，开启抱闸，跳转至STEP1 */
 		case 3:	 
                  
			SvSeqV.BkWait += KPI_SCCYCLEMS;
			if( (SvSeqV.BkWait >= Gprm.BkonWaitTime) || (CinK.AbsMotSpd <= Gprm.BkonSpdLevel) )
			{												 
				SvSeqV.f.Brake = TRUE;						 
				SvSeqV.BkWait = 0;							 
				SvSeqV.BkStep = 1;							 
			}
			break;
        /*  伺服OFF抱闸延时时间到，跳转至STEP1，关闭抱闸请求 */
        /* 外部断电后，需要清除PowerOffflg标志位 */
 		case 4:  
 			SvSeqV.BkWait += KPI_SCCYCLEMS;
            if( CoutV.f.Seq.PowerOffflg == 1 )
            {
                if(SvSeqV.BkWait >= Gprm.BkonDelayTime)
                {
                    CoutV.f.Sv.BkBeReq = FALSE;				 
                    SvSeqV.f.BkZeroStop = FALSE;			 
                    SvSeqV.BkWait = 0;						 
                    SvSeqV.BkStep = 1;						 
                    CoutV.f.Seq.PowerOffflg = 0;
                }
            }
            else
            {        
                if( (SvSeqV.BkWait >= Gprm.BkonDelayTime) || (SvSeqV.AlmStopMode > STOPMODE_ZEROSTOP) || 
                    (CoutV.f.Sv.HwbbState) )
                {											 
                    CoutV.f.Sv.BkBeReq = FALSE;				 
                    SvSeqV.f.BkZeroStop = FALSE;			 
                    SvSeqV.BkWait = 0;						 
                    SvSeqV.BkStep = 1;						 
                }
            }
			break;
 		default:  
 			 
			break;
		}
  
  
  
  
  
#if 0
		if( SvSeqV.f.Brake == FALSE) || (CinV.f.Seq.BrkRelease == TRUE) )
#else
        if( Iprm.f.BKsel == 0 )
        {
            if( (SvSeqV.f.Brake == FALSE)  )
    #endif
            {
                if(Kprm.f.MotorLessTestMode == FALSE)
                    CoutV.f.Seq.BrkReleasing = FALSE;
                else
                    CoutV.f.Seq.BrkReleasing = TRUE;
            }
            else
            {
                CoutV.f.Seq.BrkReleasing = TRUE ;
            }
        }
        else
        {
            if( 1 == CinV.f.Sv.BKSel)
            {
                CoutV.f.Seq.BrkReleasing = FALSE;
            }
            else
            {
                if( CoutV.f.Sv.BaseEnable == FALSE )
                    CoutV.f.Seq.BrkReleasing = TRUE;
                else
                    CoutV.f.Seq.BrkReleasing = FALSE;
            }
        }
		return;
 }
