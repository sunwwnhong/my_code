/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Seq03_OverTravelSequence.c
* Version            : V0.1
* Date               : 2024
* Description        : 超程时序
***********************************************************************************************/
#include "Main.h"
 
 #define ACTMOD_WAIT_STATE	0	 
#define ACTMOD_DSTP_STATE	1	 
#define ACTMOD_ZCLR_STATE	2	 
#define ACTMOD_ZTIM_STATE	3	 
#define ACTMOD_ZWAT_STATE	4	 
#define ACTMOD_BSTP_STATE	5	 
#define ACTMOD_BTIM_STATE	6	 
#define ACTMOD_BWAT_STATE	7	 
 
  
  
  
  
  
#define	OTDBOP_NONE		0x00		 
#define	OTDBOP_DEF		0x01		 
#define	OTDBOP_FREE		0x02

/**********************************************************************************************/
/* Function_Name: LpxOverTravelSequence                                                       */
/* Description  : OT时序判定
                  调用：ScanC*/
/**********************************************************************************************/
void	LpxOverTravelSequence( void )
{
LONG	lwk,TRef;
CTRLMD	CtrlMode;
UCHAR	DetOTEnable;
LONG 	servoOnComp;                 
  
#if ( CCSW_NETID != NETID_NONE )
USHORT	CtrlMode2Lst;
    CtrlMode2Lst = SvSeqV.CtrlMode2;
    SvSeqV.CtrlMode2 = BinV.f.Ctrl.ModSel;
#endif
     CtrlMode.dw = BoutV.CtrlMode.dw;
  
  
 	if( TblExeV.TblZmd.b.zm == CTRLMODE_ZCLMP )
	{
		DetOTEnable = FALSE;                                     
	}
	else
	{
		DetOTEnable = TRUE;                                      
	}
  
  
	if( DetOTEnable == TRUE )
	{
		switch( CtrlMode.b.cm )
		{
             case CTRLMODE_SPD:                               
                 lwk = BoutV.SpdRefi;
                CoutV.f.Sv.Ot = (((lwk>=0) && CinV.f.Sv.Pot) || ((lwk<=0) && CinV.f.Sv.Not))? TRUE : FALSE;
            break;
             case CTRLMODE_POS:                               
                 lwk = PosMngV.PosErrA.per32s;                
                if( lwk == 0 )
                {
                    CoutV.f.Sv.Ot = (CinV.f.Sv.Pot || CinV.f.Sv.Not)? TRUE : FALSE;
                }
                 else
                {
                    CoutV.f.Sv.Ot = ((((lwk>0) || (AoutV.dPosRefi>=0)) && CinV.f.Sv.Pot) ||
								    ((( lwk<0) || (AoutV.dPosRefi<=0)) && CinV.f.Sv.Not)) ? TRUE : FALSE;
                }
 			break;
             case CTRLMODE_TRQ:                               
                 lwk = AoutV.TrqRefi;
                  
                 if( ((lwk>=0) && CinV.f.Sv.Pot) || ((lwk<=0) && CinV.f.Sv.Not) )
                {
                    SvSeqV.OtOffCnt = 0;
                    if( SvSeqV.OtOnCnt >= KPI_SCANC_MS( 20 ) )
                    {
                        CoutV.f.Sv.Ot = TRUE;
                    }
                    else
                    {
                        SvSeqV.OtOnCnt++;                      
                    }
                }
                else
                {
                    SvSeqV.OtOnCnt = 0;
                    if( SvSeqV.OtOffCnt >= KPI_SCANC_MS( 20 ) )
                    {
                        CoutV.f.Sv.Ot = FALSE;
                    }
                    else
                    {
                        SvSeqV.OtOffCnt++;
                    }
                }
			break;
 		default:                                             
 			CoutV.f.Sv.Ot = FALSE;
			break;
		}
	}
	else	 
	{
		CoutV.f.Sv.Ot = FALSE;
	}
  

    switch( SvSeqV.OtStep )
    {
         /*超程判定初始化 */
         case 0:                                              
             CoutV.f.Sv.OtBeReq = TRUE;
            CoutV.f.Sv.OtTrqLimit = FALSE;                                     
            SvSeqV.f.OtZeroStop = FALSE;                     
            SvSeqV.f.OtZeroClamp = FALSE;                    
            SvSeqV.OtDbopReq = OTDBOP_NONE;                  
            SvSeqV.OtWait = 0;
            SvSeqV.OtStep = 1;
            break;
         case 1:
             /*超程时，报WRN_POT/WRN_NOT故障,并根据控制模式，执行不同超程操作 */
             if( CoutV.f.Sv.Ot == TRUE )					     
            {
                servoOnComp = (!CoutV.f.Sv.BBSvcRefClrReq && MencV.f.PhaseReady )? TRUE : FALSE;
                  
                  
                  
                if( servoOnComp && Iprm.f.OtStopWarn )
                {   
                      
                     if( CinV.f.Sv.Pot == TRUE )
                    {
                        KPI_WARNINGSET( WRN_POT );		     
                    }
                    else if( CinV.f.Sv.Not == TRUE )
                    {
                        KPI_WARNINGSET( WRN_NOT );		                             
                    }
                    else
                    {
                        ;
                    }
                     SvSeqV.OtWarngWaitCnt = 0;
                }
                  
                /*转矩控制时，与Pn004相同的停机方式执行*/
                if( CtrlMode.b.cm == CTRLMODE_TRQ )          
                {
                    TRef = AoutV.TrqRefi;                            //  转矩指令输出
                    if( ((TRef>=0) && CinV.f.Sv.Pot) || ((TRef<=0) && CinV.f.Sv.Not) )
                    {                        
                       // CoutV.f.Sv.OtBeReq = FALSE;	             // 影响驱动器使能
                        SvSeqV.OtDbopReq = OTDBOP_DEF;
                        SvSeqV.OtStep = 2;	
                        break;
                    }
                }
                  
                  
                switch( Iprm.OtStopMode	)				     
                {
                     case OTSTOPMODE_DEFAULT:		        //  与Pn004相同的停机方式执行
                        CoutV.f.Sv.OtBeReq = FALSE;
                        SvSeqV.OtDbopReq = OTDBOP_DEF;
                        SvSeqV.OtStep = 2;
                        break;
                     case OTSTOPMODE_ZSTOPZC:			     
                        CoutV.f.Sv.OtTrqLimit = TRUE;
                        SvSeqV.f.OtZeroStop = TRUE;
                        SvSeqV.OtDbopReq = OTDBOP_NONE;
                        SvSeqV.OtStep = 3;
                        break;
                     case OTSTOPMODE_ZSTOPFR:			     
                        CoutV.f.Sv.OtTrqLimit = TRUE;
                        SvSeqV.f.OtZeroStop = TRUE;
                        SvSeqV.OtDbopReq = OTDBOP_NONE;
                        SvSeqV.OtStep = 5;
                        break;
                     default:
                            break;
                }
			}
            /*未超程，超过1000ms清除警告*/
			else
			{
				if( SvSeqV.OtWarngWaitCnt > KPI_SCANC_MS( 1000 ) )
				{
                      
                     KPI_WARNINGCLR( WRN_POT );		         
                    KPI_WARNINGCLR( WRN_NOT );		         
 				}
				else
				{
					SvSeqV.OtWarngWaitCnt++;
				}
			}
			break;
 		case 2:                      
 			if( CoutV.f.Sv.Ot == FALSE )						 
			{
				if( ++SvSeqV.OtWait >= KPI_SCANC_MS( 20 ) )		 
				{
					CoutV.f.Sv.OtBeReq = TRUE;					 
					SvSeqV.OtDbopReq = OTDBOP_NONE;				 
					SvSeqV.OtWait = 0;
					SvSeqV.OtStep = 1;
				}
			}
#if ( CCSW_NETID != NETID_NONE )
			else if((( SvSeqV.CtrlMode2 == POS_CTRL_MODE ) || ( SvSeqV.CtrlMode2 == SPD_CTRL_MODE ))
				&& ( CtrlMode2Lst == NO_CTRL_MODE ) 
				&& ( Iprm.OtStopMode == OTSTOPMODE_ZSTOPZC ))
			{													 
				CoutV.f.Sv.OtBeReq = TRUE;						 
				CoutV.f.Sv.OtTrqLimit = TRUE;
				SvSeqV.f.OtZeroStop = TRUE;
				SvSeqV.OtDbopReq = OTDBOP_NONE;
				SvSeqV.OtStep = 3;
			}
#endif
			else
			{
				SvSeqV.OtWait = 0;
			}
			break;
		/*零速最大转矩停机，停止完成后进入锁机状态*/
 		case 3:                                              
 			if( CoutV.f.Sv.Ot == FALSE )					 
			{
				CoutV.f.Sv.OtTrqLimit   = FALSE;			 
				SvSeqV.f.OtZeroStop     = FALSE;
				SvSeqV.OtStep           = 1;
			}
			else if( CoutV.f.Sv.MotStop )					 
			{
				SvSeqV.f.OtZeroStop     = FALSE;			 
				SvSeqV.f.OtZeroClamp    = TRUE;				 
				SvSeqV.OtStep           = 4;
			}
			break;
 		case 4:                                              
 			if( CoutV.f.Sv.Ot == FALSE )					 
			{
				CoutV.f.Sv.OtTrqLimit   = FALSE;			 
				SvSeqV.f.OtZeroClamp    = FALSE;			 
				SvSeqV.OtStep           = 1;				 
			}
			break;
		/*零速最大转矩停机，停止完成后进入自由停机状态状态*/
 		case 5:  
 			if( CoutV.f.Sv.Ot == FALSE )					 
			{
				CoutV.f.Sv.OtTrqLimit = FALSE;				 
				SvSeqV.f.OtZeroStop = FALSE;
				SvSeqV.OtStep = 1;
			}
 			else if( CoutV.f.Sv.MotStop )					 
			{
				CoutV.f.Sv.OtBeReq = FALSE;					 
				CoutV.f.Sv.OtTrqLimit = FALSE;
				SvSeqV.f.OtZeroStop = FALSE;
				SvSeqV.OtDbopReq = OTDBOP_FREE;				 
				SvSeqV.OtStep = 6;
			}
			break;
		/*自由停机状态*/
 		case 6:  
 			if( CoutV.f.Sv.Ot == FALSE )					 
			{
				if( ++SvSeqV.OtWait >= KPI_SCANC_MS( 20 ) )	 
				{											 
					CoutV.f.Sv.OtBeReq = TRUE;				 
					SvSeqV.OtDbopReq = OTDBOP_NONE;			 
					SvSeqV.OtWait = 0;						 
					SvSeqV.OtStep = 1;						 
				}
			}
 			else
			{
				SvSeqV.OtWait = 0;
			}
			break;
 		default:  
 			 
			break;
		}
 		CoutK.f.Ot = (CoutV.f.Sv.Ot)? TRUE : FALSE;
		return;
}

/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/
