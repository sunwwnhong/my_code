/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Seq10_ControlMode.c
* Version            : V0.1
* Date               : 2024
* Description        : 控制模式
***********************************************************************************************/
#include "Main.h"
 
/**********************************************************************************************/
/* Function_Name: LpxCselControlMode                                                    */
/* Description  : 控制模式判断
                  调用：*/
/**********************************************************************************************/
 USHORT	LpxCselControlMode( void )
{
USHORT	CtrlMode;
    {
          
          
        BoutV.CSELStatus = ( BoutV.CSELStatus << 1 ) & 0x03;
        if( CinV.f.Sv.CTrig == 1 )
        {
            BoutV.CSELStatus |= 0x01;
        }
          
          
        if( Iprm.CtrlMode == 6 )
        {
            if( BoutV.CSELStatus == 0x01 )
            {
                 if( CinV.f.Sv.Csel == 0 )
                {
                    if( CinV.f.Sv.Csel2 == 0 )
                    {
                        Iprm.CtrlModeInit = Iprm.CtrlModeA;
                    }
                    else
                    {
                        Iprm.CtrlModeInit = Iprm.CtrlModeB;
                    }
                }
                 else
                {
                    if( CinV.f.Sv.Csel2 == 0 )
                    {
                        Iprm.CtrlModeInit = Iprm.CtrlModeC;
                    } 
                }
             }
             CtrlMode = Iprm.CtrlModeInit;
        }
        else
        {
            if( CinV.f.Sv.Csel )	                             
            {
                CtrlMode = Iprm.CtrlModeB;				         
            }
             else
            {
                CtrlMode = Iprm.CtrlModeA;					     
            }
         }
    }
      
      
    if( CinV.f.Sv.JOGFlag )
    {
        CtrlMode = CTRLMODE_JOG;
         if( ((CinV.f.Sv.JOGP == TRUE)  && (CinV.f.Sv.JOGN == TRUE  )) ||
            ((CinV.f.Sv.JOGP == FALSE) && (CinV.f.Sv.JOGN == FALSE )))
        {
            RoutV.JogSpeed = 0;
        }
         else if( CinV.f.Sv.JOGP == TRUE )
        {
            RoutV.JogSpeed =  KpiSpeedLevelCal( (LONG)Prm.jogspd * 10, 0 );	     
        }
         else
        {
            RoutV.JogSpeed = -KpiSpeedLevelCal( (LONG)Prm.jogspd * 10, 0 );	     
        }
    }
      
      
    if( CinV.f.Sv.EmcyStop )
    {
        CtrlMode = CTRLMODE_JOG;
        RoutV.JogSpeed = 0;
    }
      
      
    if( CinV.f.Seq.ServoOffDecM )
    {
        CtrlMode = CTRLMODE_SPD;    
    }
     return( CtrlMode );
}
  
  
/**********************************************************************************************/
/* Function_Name: LpxServoControlMode                                                       */
/* Description  : 控制模式管理
               调用：ScanB*/
/**********************************************************************************************/
void LpxServoControlMode( void )
{
CTRLMD	CtrlMode;
    CtrlMode.dw = CoutV.CtrlMcmd.dw;				             
    if( CoutV.CtrlMcmd.us[0] == CTRLMODE_NOCMD )                 
    {
        CtrlMode.us[0] = BinV.NetCtrlMcmd;			             
    }
     BoutV.CtrlModeLst.dw = BoutV.CtrlMode.dw;					 
    BoutV.CtrlModeChg.dw = CtrlMode.dw ^ BoutV.CtrlMode.dw;		 
    BoutV.CtrlMode.dw = CtrlMode.dw;							 
}
  
  
  
  
/**********************************************************************************************/
/* Function_Name: LpxControlModeManager                                                     */
/* Description  : 控制模式时序
                  SCANC调用
                  输入：
                  输出：控制模式-CoutV.CtrlMcmd.dw                                       */
/**********************************************************************************************/
void	LpxControlModeManager( void )
{
CTRLMD	CtrlMcmd;
  
    /* 根据机型和控制模式确定基本控制模式 */
    if( CoutK.f.RndSvControl )					         
    {
        CtrlMcmd.us[0] = RoutV.CtrlMcmd;			     
    }
 	else if( Kprm.f.EtherCATNet == TRUE )				 
    {
          
         if( CinV.f.Sv.EmcyStop )
        {
            if(CAN_EXFUNC0_12_EN)
            {
                CtrlMcmd.us[0] = EtherCAT_ControlMode;        //急停按钮与快速停机相关联
            }
            else
            {
                CtrlMcmd.us[0] = CTRLMODE_JOG;                // 急停按钮立即零速 
                RoutV.JogSpeed = 0;
            }
        }   
          
         else if( CinV.f.Seq.ServoOffDecM )
        {
            CtrlMcmd.us[0] = CTRLMODE_SPD;    
        }
        else if( ( Prm.b_prm0_0 & 0x000F ) == 0x0007 )
        {
            CtrlMcmd.us[0] = CTRLMODE_VF;
        }
        else if( Prm.Testpassword == 3322 )   
        {
            CtrlMcmd.us[0] = CTRLMODE_VF;
        }
          
         else
        {
            CtrlMcmd.us[0] = EtherCAT_ControlMode;
        }
    }
     else if( Kprm.f.CanOpenNet == TRUE )
    {
          
         if( CinV.f.Sv.EmcyStop )
        {
            if(CAN_EXFUNC0_12_EN)
            {
                CtrlMcmd.us[0] = CanOpen_ControlMode;          //急停按钮与快速停机相关联
            }
            else
            {
                CtrlMcmd.us[0] = CTRLMODE_JOG;                // 急停按钮立即零速 
                RoutV.JogSpeed = 0;
            }
            
        }   
        else if( CinV.f.Seq.ServoOffDecM )
        {
            CtrlMcmd.us[0] = CTRLMODE_SPD;    
        }
          
         else if( CinV.f.Sv.JOGFlag && CAN_EXFUNC0_7_DIS)
        {
            CtrlMcmd.us[0] = CTRLMODE_JOG;
             if( ((CinV.f.Sv.JOGP == TRUE)  && (CinV.f.Sv.JOGN == TRUE  )) ||
                ((CinV.f.Sv.JOGP == FALSE) && (CinV.f.Sv.JOGN == FALSE )))
            {
                RoutV.JogSpeed = 0;
            }
             else if( CinV.f.Sv.JOGP == TRUE )
            {
                RoutV.JogSpeed =  KpiSpeedLevelCal( (LONG)Prm.jogspd * 10, 0 );      
            }
             else
            {
                RoutV.JogSpeed = -KpiSpeedLevelCal( (LONG)Prm.jogspd * 10, 0 );      
            }
        }
          
         else
        {
            CtrlMcmd.us[0] = CanOpen_ControlMode;
        }
    }
 	else                                                     
    {
        CtrlMcmd.us[0] = LpxCselControlMode( );
    }
     
    /* 根据停机模式CoutV.StopMode确认零控制模式 */
     if( CoutV.StopMode == STOPMODE_ZEROSTOP )
    {
        CtrlMcmd.b.zm = CTRLMODE_ZSTOP;				     
    }
 	else if( CoutV.StopMode == STOPMODE_LDECSTOP )		 
	{
		CtrlMcmd.b.zm = CTRLMODE_DSTOP;				     
	}
     else if( SvSeqV.f.OtZeroClamp )					     
    {
        CtrlMcmd.b.zm = CTRLMODE_ZCLMP;				     
    }
     else if( SvSeqV.f.ZcZeroClamp )					     
    {
        CtrlMcmd.b.zm = CTRLMODE_ZCLMP;				     
    }
    else if( (Brake_V.Step != 3) && (CoutV.f.Seq.BrkReleasing == 0) )
     {
         CtrlMcmd.b.zm = CTRLMODE_ZCLMP;
     }
     else											     
    {
        CtrlMcmd.b.zm = CTRLMODE_ZNONE;				     
    }


     /* 获取OT发生标志 */
     CtrlMcmd.b.ot = (CoutV.f.Sv.Ot == TRUE)? TRUE : FALSE;
  
     CoutV.CtrlMcmd.dw = CtrlMcmd.dw;				     
     return;
}
