/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Drv_ACR04_OverTrq.c
* Version            : V0.1
* Date               : 2024
* Description        : 转矩模式速度限制转矩计算
***********************************************************************************************/

#include "Main.h"
 
#define  	SPDLMTSW	   0x40000					 
#define  	INTDECVAL	   ( 2 * SPDLMTSW )  		 
 #define  	OVERTRQLMT	   19573419  				 
 
  
/**********************************************************************************************/
/* Function_Name: OverTorqueCalculation       */
/* Description  : 转矩模式速度限制转矩计算
                  SCANB调用：转矩模式，速度限制情况下，剩余转矩计算
                  输入：转速限制值，转速反馈值
                  输出：剩余转矩   */
/**********************************************************************************************/
LONG OverTorqueCalculation( LONG SpdLmt, LONG SpdFbk )
{
LONG	SpdLimitx;
LONG	nerp;
LONG	neri;
LONG	nerpi;
LONG	lwrk;
LONG	overtorque;
LONG	Status;
LONG    TargetSpd;
LONG    TRef;
    /*** EtherCat指令源时，速度限制处理 ***/
    if( Kprm.f.EtherCATNet == 1 )
    {
        if( !BinV.f.BaseEnable  || ((u16ControlWord & 0x0008) == 0x0000))
        {
            TargetSpd = 0;
        }
        else
        {
            /*非停机状态下，按照0x607F进行限制处理*/
            TargetSpd = u32MaxProfileVel;

            /*不同减速停机处理下的速度限制处理*/
            EcontSMachine.HaltStatus = ( EcontSMachine.HaltStatus << 1 ) & 0x03;


            if( ( u16ControlWord & 0x0104 ) == 0x0104 )
            {
                EcontSMachine.HaltStatus |= 0x01;
            }

            if( EcontSMachine.HaltStatus == 1 )
            {
                  
                if( s16HaltOptioncode == 1 )
                {
                    EcontSMachine.DecBase_Q15 = EcontSMachine.DecSBase6084_Q15;
                }
                else if( s16HaltOptioncode == 2 )
                {
                    EcontSMachine.DecBase_Q15 = EcontSMachine.DecSBase6085_Q15;
                }
                else
                {
                    EcontSMachine.DecBase_Q15 = ( (INT64)TargetSpd ) << 15;
                    if( EcontSMachine.DecBase_Q15 < 0 )
                    {
                        EcontSMachine.DecBase_Q15 = -EcontSMachine.DecBase_Q15;
                    }
                }
                EcontSMachine.SpdOutQ15 = ( (INT64)TargetSpd ) << 15;
            }
            else
            {;}


            EcontSMachine.FastStatus = ( EcontSMachine.FastStatus << 1 ) & 0x03;
            if( ( u16ControlWord & 0x0004 ) == 0x0000 )
            {
                EcontSMachine.FastStatus |= 0x01;
            }

            if( EcontSMachine.FastStatus == 0x01 )
                {
                      
                     if( s16QuickShutdownOpt == 0 )
                    {
                         if((CiA402StatusMachine == 1) && (QuickStop_flag == 1))
                         {
                             EtherCAT_ControlStatus = 2;    //解决012快速停机CIA402状态机未进入case6,直接断使能
                         }
                         else if(CiA402StatusMachine == 0)
                         {
                             EtherCAT_ControlStatus = 2;
                         }
                    }
                    else if( s16QuickShutdownOpt == 1 )
                    {
                        EcontSMachine.DecBase_Q15 = EcontSMachine.DecSBase6084_Q15;
                    }
                    else if( s16QuickShutdownOpt == 2 )
                    {
                        EcontSMachine.DecBase_Q15 = EcontSMachine.DecSBase6085_Q15;
                    }
                    else
                    {
                        EcontSMachine.DecBase_Q15 = ( (INT64)TargetSpd ) << 15;
                        if( EcontSMachine.DecBase_Q15 < 0 )
                        {
                            EcontSMachine.DecBase_Q15 = -EcontSMachine.DecBase_Q15;
                        }
                    }
                     EcontSMachine.SpdOutQ15 = ( (INT64)TargetSpd ) << 15;
                }
                else if( EcontSMachine.FastStatus == 0x03 )
                {
                    if( EcontSMachine.SpdOutQ15 == 0 )
                    {
                        if((CiA402StatusMachine == 1) && (QuickStop_flag == 1))
                        {
                            EtherCAT_ControlStatus = 2;    //解决012快速停机CIA402状态机未进入case6,直接断使能
                        }
                        else if(CiA402StatusMachine == 0)
                        {
                            EtherCAT_ControlStatus = 1;
                        }
                    }
                }
                else
               {;}
                 if( EcontSMachine.FastStatus == 0x03 || EcontSMachine.HaltStatus == 0x03 )
                {
                     if( EcontSMachine.SpdOutQ15 == 0 )
                    {
                        ;
                    }
                    else if( EcontSMachine.SpdOutQ15 > 0 )                    
                    {
                          
                         EcontSMachine.SpdOutQ15 -=  EcontSMachine.DecBase_Q15;
                        if( EcontSMachine.SpdOutQ15 > 0 )
                        {
                            ;
                        }
                        else
                        {
                            EcontSMachine.SpdOutQ15 = 0;
                        }
                    }
                     else                                                       
                    {
                          
                         EcontSMachine.SpdOutQ15 +=  EcontSMachine.DecBase_Q15;
                        if( EcontSMachine.SpdOutQ15 < 0 )
                        {
                            ;
                        }
                        else
                        {
                            EcontSMachine.SpdOutQ15 = 0;
                        }
                    }
                     TargetSpd = EcontSMachine.SpdOutQ15 >> 15;
                }
            }
              
              
            TargetSpd = (LONG)(( INT64 )TargetSpd * Iprm.Egear.b / Iprm.Egear.a);
             TargetSpd = (LONG)(( INT64 )TargetSpd * 600 * PositionFactor.aEntries[0] / 
                              (( INT64 )MencP.PulseNo * PositionFactor.aEntries[1]));
            SpdLimitx = TargetSpd;
    }
    /*** CANopen指令源时，速度限制处理 ***/
    else if( Kprm.f.CanOpenNet == 1 )
    {
        SpdLimitx = CanSpdV.CanMaxSpd;
    }
    /*** 标准机型时，速度限制处理 ***/
    else
    {
        //转矩控制时，速度限制源选择Pn400.Y
        switch( Iprm.VrefSpdLmtSEL )
        {
             case 0:
                SpdLimitx = 0;
                break;
             case 1:
                SpdLimitx = 0;
                break;
             case 2:     // Pn415 : 转矩控制模式时内部速度限制
                SpdLimitx = Prm.ntqspdlimt1 * 10;
                break;
             case 3:
                if( CinV.f.Sv.TSLimit == 0 )    // 转矩速度限制源选择
                    SpdLimitx = Prm.ntqspdlimt1 * 10;
                else
                    SpdLimitx = Prm.ntqspdlimt2 * 10;   // Pn416 : 转矩控制模式时内部速度限制
                break;
             case 4:            // 转矩方向确定速度限制源：0时，Pn415；1时，Pn416。
                if( CinV.f.Sv.TDIR == 0 )
                    SpdLimitx = Prm.ntqspdlimt1 * 10;
                else
                    SpdLimitx = Prm.ntqspdlimt2 * 10;
                break;
             default:
                SpdLimitx = 0;
                break;
         }
    }

    /*转矩模式速度限制转矩计算*/
    //-------------------------- 转矩模式限位后无法反转问题  @20240807  ------------------------
    if(CoutV.f.Sv.Ot == TRUE)
    {
        TRef = AoutV.TrqRefi;
        //限位后，速度限制在限位方向强制为0
        if( ((TRef>=0) && CinV.f.Sv.Pot) || ((TRef<=0) && CinV.f.Sv.Not) )
        {
            SpdLimitx = 0;
        }
    }

    // 转换速度输入到速度标幺值，并限幅处理
    SpdLimitx = MlibAbs32( SpdLimitx );
    TrqCtrl.V.SpdLimit = KpiSpeedLevelCal( SpdLimitx, 0 );

    /*** 限速PI控制误差信号计算 ***/
    if ( SpdFbk > 0 )
    {
        nerp = SpdFbk - TrqCtrl.V.SpdLimit; // 限速值，本身没有方向，这里方向取反馈速度相同方向。
    }
    else if ( SpdFbk < 0 )
    {
        nerp = SpdFbk + TrqCtrl.V.SpdLimit;
    }
    else                // 限速值，速度为零是，方向取转矩指令相同方向。
    {
        nerp = ( AoutV.TrqRefi >= 0 )?	-TrqCtrl.V.SpdLimit : TrqCtrl.V.SpdLimit;
    }

    /*** 限速PI控制运算 ***/
    lwrk = MlibMulgain29( nerp, TrqCtrl.P.OverTrqLoopGain[0] );
    neri = MlibIntegral( nerp, TrqCtrl.P.OverTrqIntegGain[0], TrqCtrl.V.OverTrqIntegBuf );
    nerpi = lwrk + neri;
    //伺服未使能，清零积分项和PI输出，及相关标志
    if( !BinV.f.BaseEnable )
    {
        nerpi = 0;
        TrqCtrl.V.OverTrqIntegBuf[ 0 ] = 0;
        TrqCtrl.V.OverTrqIntegBuf[ 1 ] = 0;
        Status = FALSE;
    }
    /***采用异或运算来判定是否符号相同，符号相同则最高符号位为0为正值，
            符号不同则最高符号位为1为负值。 ***/
    else if ( (((SpdFbk ^ nerpi) < 0 ) && (AoutV.TrqRefi >= 0)) || \
        ((((SpdFbk - 1) ^ nerpi) < 0 ) && (AoutV.TrqRefi < 0)) )
    {


        if( TrqCtrl.V.SpdLimit <= SPDLMTSW )  // SPDLMTSW = 0x40000,Q24,则=1/64*超速值。代表速度较小时。
        {
            /*** 积分项加一个相反的2倍速差，若符号不变，说明积分项足够大，肯定是在限速状态
                        之所以这里进入方向相反判断，是因为比例项较大的原因。此种情况继续保持限速。
                        因为若不限速的话，积分项不会累积的，每次都会清零。
                        低速下，比例项和积分项可能差距很小，这里增加这个积分阈值判断，确保状态不频繁改变 ***/
            if ( neri >= 0 )
            {
                lwrk = -INTDECVAL;
                if( TrqCtrl.V.SpdLimit < 0x100 )lwrk = 0;   // 限速足够低，比如0速，可以按照0来处理。
                neri = MlibIntegral( lwrk, TrqCtrl.P.OverTrqIntegGain[0], TrqCtrl.V.OverTrqIntegBuf );

                Status = ( neri >= 0 ) ? TRUE : FALSE;
            }
            else
            {
                lwrk = INTDECVAL;
                if( TrqCtrl.V.SpdLimit < 0x100 )lwrk = 0;
                neri = MlibIntegral( lwrk, TrqCtrl.P.OverTrqIntegGain[0], TrqCtrl.V.OverTrqIntegBuf );

                Status = ( neri < 0  ) ? TRUE : FALSE;
            }
        }
        // 速度较大时，速度反馈和PI输出方向反向，说明没有达到限制值。
        else
        {
            Status = FALSE;
        }
    }
    // 速度反馈和PI输出方向相同，说明实际速度已经达到限制值。
    else
    {
        Status = TRUE;
    }
    // 达到限制值，则对应标志赋值1
    if ( Status )
    {
         BoutV.f.Ctrl.SpdClamp = TRUE;
    }
    // 未到限制值，则清零PI和积分项，及对应标志。
    else
    {
        TrqCtrl.V.OverTrqIntegBuf[ 1 ] = 0;
        TrqCtrl.V.OverTrqIntegBuf[ 0 ] = 0;
        nerpi = 0;
        BoutV.f.Ctrl.SpdClamp = FALSE;
    }

#if 1
    overtorque = MlibLimitul( nerpi, OVERTRQLMT, -OVERTRQLMT );
#else
        overtorque = nerpi;
#endif
          
		return overtorque;
 }
 
  
  
 void PcalSpeedLimitGain( USHORT  Loophz, UCHAR	GselNo )
{
	USHORT SpdLimGain;
	LONG   SpdLimIntegGain;
 	 
 	 
 
	if( Loophz < 100 )
	{
		SpdLimGain		= 100;
		SpdLimIntegGain = 32000;
	}
	else if( Loophz < 200 )
    {
        SpdLimGain		= Loophz;
        SpdLimIntegGain = 3200000.0f / (float)Loophz;
    }
    else
    {
        SpdLimGain		= Loophz;
        SpdLimIntegGain = 16000;
    }
      
	TrqCtrl.P.OverTrqLoopGain[ GselNo ]	= MlibScalKskxkx( Hprm.Kvx, ( 100  + Prm.jrate ) * SpdLimGain, 1000, NULL, 24 );
      
      
     TrqCtrl.P.OverTrqIntegGain[GselNo] = MlibScalKskxkx( TrqCtrl.P.OverTrqLoopGain[GselNo], Iprm.SvCycleUs, SpdLimIntegGain, NULL, 24 ); 
	return;
}
