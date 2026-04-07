/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Spd08_SpdStatus.c
* Version            : V0.1
* Date               : 2024
* Description        : 速度状态判定
***********************************************************************************************/

  
  
  
  
#include "Main.h"
 
  
  
#define MOTSPD_TGMGN	12710

void    LpxEtherCatCheckVelCmpOver( void );

void	LpxCheckMotorRun( void )
{
    if( CinK.AbsMotSpd >= Gprm.TgonSpdLevel )
    {
        CoutV.f.Ctrl.MotorMoving = TRUE;
    }
    else
    {
        CoutV.f.Ctrl.MotorMoving = FALSE;
    }
    return;
}

void    LpxCheckMotorLowVel( void )
{
    LONG    val ;

    if( Prm.SpdSwitch == 0)         //速度指令增益切换
    {
        if( MlibABS(BoutV.SpdRefSum) <= Gprm.LowSpdLevel )
        {
            BoutV.f.Sv.LowVel = TRUE;
        }
        else
        {
            BoutV.f.Sv.LowVel = FALSE;
        }
    }
    else if( Prm.SpdSwitch == 1)        //速度反馈增益切换
    {
        if( MlibABS(CinK.AbsMotSpd) <= Gprm.LowSpdLevel )
        {
            BoutV.f.Sv.LowVel = TRUE;
        }
        else
        {
            BoutV.f.Sv.LowVel = FALSE;
        }
    }
    else                //位置指令速度增益切换
    {
        val = (float)CoutV.UnPcmd64ms * Iprm.fKmonpcmdspd;           //64ms 平均

        val =  MlibLimitul(val, 0x00007FFF, 0xFFFF8000) ;

        if( MlibABS(val) <= (SHORT)Prm.LowSpdLevel )
        {
            BoutV.f.Sv.LowVel = TRUE;
        }
        else
        {
            BoutV.f.Sv.LowVel = FALSE;
        }
    }
}
  
  
  
USHORT MotorMovingTime0 = 0;
USHORT MotorMovingTime1 = 0;
void LpxEtherCatCheckMotorRun( void )
{
     if( CoutV.f.Ctrl.MotorMoving )
    {
        MotorMovingTime0 = 0;
        if( CinK.AbsMotSpd < Gprm.EthTgonSpdLevel )
        {
            if( ++MotorMovingTime1 > u16VelthresdTime )
            {
                CoutV.f.Ctrl.MotorMoving = FALSE;
            }
        }
        else
        {
            MotorMovingTime1 = 0;
        }
    }
     else
    {
        MotorMovingTime1 = 0;
        if( CinK.AbsMotSpd > Gprm.EthTgonSpdLevel )
        {
            if( ++MotorMovingTime0 > u16VelthresdTime )
            {
                CoutV.f.Ctrl.MotorMoving = TRUE;
            }
        }
        else
        {
            MotorMovingTime0 = 0;
        }
    }
     return;
 }
  
  
  
void LpxCanOpenCheckMotorRun( void )
{
LONG CanOpenSpdLevel = KpiSpeedLevelCal( ODDatArr[ OD_606F ].all, 0 );
     if( CoutV.f.Ctrl.MotorMoving )
    {
        MotorMovingTime0 = 0;
        if( CinK.AbsMotSpd < CanOpenSpdLevel )
        {
            if( ++MotorMovingTime1 > ODDatArr[ OD_6070 ].all )
            {
                CoutV.f.Ctrl.MotorMoving = FALSE;
            }
        }
        else
        {
            MotorMovingTime1 = 0;
        }
    }
     else
    {
        MotorMovingTime1 = 0;
        if( CinK.AbsMotSpd > CanOpenSpdLevel )
        {
            if( ++MotorMovingTime0 > ODDatArr[ OD_6070 ].all )
            {
                CoutV.f.Ctrl.MotorMoving = TRUE;
            }
        }
        else
        {
            MotorMovingTime0 = 0;
        }
    }
    return;
 }
 
  
  
 #define MOTSPD_DBLVL	60000					     
 void	LpxCheckMotorStop( void )
{
 		if( CinK.AbsMotSpd < MOTSPD_DBLVL )
		{
			CoutV.f.Sv.MotStop = TRUE;				 /* 马达停止检测信号设定(ON)                      */
		}
		else
		{
			CoutV.f.Sv.MotStop = FALSE;				 /* 马达停止检测信号设定(OFF)                      */
		}
 		CoutK.f.MotStop = (CoutV.f.Sv.MotStop)? TRUE : FALSE;
 		return;
 }
 
  
  
 void LpxCheckMotorVcmp( void )
{
		if( (BoutV.CtrlMode.b.cm == CTRLMODE_SPD) || (BoutV.CtrlMode.b.cm == CTRLMODE_JOG) )
		{
			if( MlibAbs32( BinV.SpdRef - CinK.MotSpd ) <= Gprm.VcmpSpdLevel  &&  BinV.f.BaseEnable)
			{
				CoutV.f.Ctrl.ReachSpd = TRUE;            
			}
			else
			{
				CoutV.f.Ctrl.ReachSpd = FALSE;       
			}
		}
		else
		{
            CoutV.f.Ctrl.ReachSpd = FALSE;           
		}
 		return;
}
  
  
  
USHORT SpeedReachTime0 = 0;
USHORT SpeedReachTime1 = 0;
USHORT SpeedReachTime2 = 0;
USHORT SpeedReachTime3 = 0;
void	LpxEtherCatCheckMotorVcmp( void )
{
    if (!CiA402_SPEEDOVER_EN)
    {
        if( (BoutV.CtrlMode.b.cm == CTRLMODE_SPD) || (BoutV.CtrlMode.b.cm == CTRLMODE_JOG) )
        {

             if( BinV.f.BaseEnable )
            {
                if( CoutV.f.Ctrl.ReachSpd )
                {
                    SpeedReachTime0 = 0;
                    if( MlibAbs32( BinV.SpdRef - CinK.MotSpd ) > Gprm.EthVcmpSpdLevel )
                    {
                        SpeedReachTime1 += 1;
                        if( SpeedReachTime1 > u16VelWindowTime )
                            CoutV.f.Ctrl.ReachSpd = FALSE;
                    }
                    else
                    {
                        SpeedReachTime1 = 0;
                    }
                }
                else
                {
                    SpeedReachTime1 = 0;
                    if( MlibAbs32( BinV.SpdRef - CinK.MotSpd ) <= Gprm.EthVcmpSpdLevel )
                    {
                        SpeedReachTime0 += 1;
                        if( SpeedReachTime0 > u16VelWindowTime )
                            CoutV.f.Ctrl.ReachSpd = TRUE;
                    }
                    else
                    {
                        SpeedReachTime0 = 0;
                    }
                }
            }
            else
            {
                SpeedReachTime0 = 0;
                SpeedReachTime1 = 0;
                CoutV.f.Ctrl.ReachSpd = FALSE;
            }
        }
        else
        {
            CoutV.f.Ctrl.ReachSpd = FALSE;
            SpeedReachTime0 = 0;
            SpeedReachTime1 = 0;
        }
    }
    else
    {
        LpxEtherCatCheckVelCmpOver();
    }
}

void    LpxEtherCatCheckVelCmpOver( void )
{
    if((BoutV.CtrlMode.b.cm == CTRLMODE_POS) || (BoutV.CtrlMode.b.cm == CTRLMODE_SPD) || (BoutV.CtrlMode.b.cm == CTRLMODE_JOG) )
    {

        if( BinV.f.BaseEnable )
        {
            if( MlibAbs32( BoutV.UnSpdRef - CinK.MotSpd ) > Gprm.EthVcmpSpdLevel )
            {
                SpeedReachTime1 += 1;
                if( SpeedReachTime1 > u16VelWindowTime )
                {
                    KPI_ALARMSET( ALM_SPDERR );
                }
            }
            else
            {
                SpeedReachTime1 = 0;
            }

        }
        else
        {
            SpeedReachTime1 = 0;
        }
    }
    else
    {
        SpeedReachTime1 = 0;
    }

    if((BoutV.CtrlMode.b.cm == CTRLMODE_POS) || (BoutV.CtrlMode.b.cm == CTRLMODE_SPD) || (BoutV.CtrlMode.b.cm == CTRLMODE_JOG) )
    {
        if( BinV.f.BaseEnable )
        {

            if( MlibAbs32( BoutV.UnSpdRef - CinK.MotSpd ) > Gprm.EthVcmpSpdWrmLev )
            {
                SpeedReachTime2 += 1;
                if( SpeedReachTime2 > u16VelWindowTime )
                {
                    KPI_WARNINGSET( WRN_SPDERR_WARN );
                }
            }
            else
            {
                SpeedReachTime2 = 0;
            }

        }
        else
        {
            SpeedReachTime2 = 0;
        }
    }
}

USHORT SpeedOverTime = 0;
void    LpxVelOver( void )
{
    if( BinV.f.BaseEnable )
    {
        if( CinK.MotSpd > Bprm.NorOvrSpd )
        {
            SpeedOverTime ++;
            if(SpeedOverTime >= 10)
            {
                KPI_ALARMSET( ALM_SPDERR );
                SpeedOverTime = 0;
            }
        }
    }
    else
    {
        SpeedOverTime = 0;
    }
}

  
  
  
void LpxCanOpenCheckMotorVcmp( void )
{
 LONG CanOpenSpdLevel;
LONG CanOpenSpdDiff;
LONG CanOpenSpdRef;
    if( (BoutV.CtrlMode.b.cm == CTRLMODE_SPD) || (BoutV.CtrlMode.b.cm == CTRLMODE_JOG) )
    {
        CanOpenSpdLevel = KpiSpeedLevelCal( ODDatArr[ OD_606D ].all, 0 );
        CanOpenSpdRef = (LLONG)CanSpdV.ReaSpdRef * Iprm.Egear.b / Iprm.Egear.a;
        CanOpenSpdDiff  = MlibAbs32( CanOpenSpdRef - CinK.MotSpd );

         if( BinV.f.BaseEnable )
        {
            if( CoutV.f.Ctrl.ReachSpd )                              
            {
                SpeedReachTime0 = 0;
                if( CanOpenSpdDiff > CanOpenSpdLevel )
                {
                    SpeedReachTime1 += 1;
                    if( SpeedReachTime1 > ODDatArr[ OD_606E ].all )
                        CoutV.f.Ctrl.ReachSpd = FALSE;
                }
                else
                {
                    SpeedReachTime1 = 0;
                }
            }
            else                                                     
            {
                SpeedReachTime1 = 0;
                if( CanOpenSpdDiff <= CanOpenSpdLevel )
                {
                    SpeedReachTime0 += 1;
                    if( SpeedReachTime0 > ODDatArr[ OD_606E ].all )
                        CoutV.f.Ctrl.ReachSpd = TRUE;
                }
                else
                {
                    SpeedReachTime0 = 0;
                }
            }
        }
        else
        {
            CoutV.f.Ctrl.ReachSpd = FALSE;           
            SpeedReachTime0 = 0;
            SpeedReachTime1 = 0;
        }
    }
    else
    {
        CoutV.f.Ctrl.ReachSpd = FALSE;               
        SpeedReachTime0 = 0;
        SpeedReachTime1 = 0;
    }
    return;
}

/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/
