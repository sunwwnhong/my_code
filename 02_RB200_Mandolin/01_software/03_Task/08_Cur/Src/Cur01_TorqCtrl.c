/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Cur01_TorqCtrl.c
* Version            : V0.1
* Date               : 2024
* Description        : 电流环控制主程序
***********************************************************************************************/

#include "Main.h"
 
  
/**********************************************************************************************/
/* Function_Name: LpxInitTrqCtrlModeVar         */
/* Description  : 电流控制参数初始化
                  输入：
                  输出：    */
/**********************************************************************************************/
void	LpxInitTrqCtrlModeVar( void )
{
	if(BoutV.CtrlModeLst.b.cm != CTRLMODE_TRQ)				 
	{
 	  	 
 	  	 
 #if(FLOAT_USE == 1)
	    TrqFil.V.FilOut = 1118.481067f * AinK.IqRefMon;
#else
        TrqFil.V.FilOut = MlibMulhigh32( (((LONG)AinK.IqRefMon) << 16), 73300775 );
#endif
 		AoutV.TrqRefi = TrqFil.V.FilOut;					 
		AoutV.DisTrqRef3 = 0;								 
		BoutV.SpdRefo = 0;									 
	}
	return;
}
  
  
/**********************************************************************************************/
/* Function_Name: LpxTorqueControl         */
/* Description  : 转矩控制主程序
                  SCANA调用：转矩模式下转矩指令生产，并进行一阶和二阶滤波输出
                  输入：
                  输出： AoutV.TrqRefo 转矩指令输出   */
/**********************************************************************************************/
void LpxTorqueControl( void )
{
LONG	TrqRefx;
LONG	TRef;
LONG    TRefLimit;
  
    /**** TBLCMD存在指令时 ****/
    if( TblExeV.TblCmd != TBLCMD_NOCMD )
    {
        /**** 存在零控制情况下，对各零控制情况进行控制 ****/
        if( BoutV.ZctrlMode.b.zm != CTRLMODE_ZNONE )
        {
            AoutV.TrqRefi = BaseSpeedControl(
                            0,
                            AinK.MotSpd,
                            0,
                            0,
                            AinK.dMotPos );
            TrqRefx = AoutV.TrqRefi;
        }
        // 无零速控制情况下，伺服未使能
        else if( BinV.f.BaseEnable == FALSE )
        {
            AoutV.TrqRefo   = 0;	    // 转矩输出复位
            TrqFil.V.FilOut = 0;        // 转矩滤波器输出复位
            /*** 滤波器复位 ***/
            TrqFil.V.LpFil2[0] = 0;
            TrqFil.V.LpFil2[1] = 0;
            TrqFil.V.LpFil2[2] = 0;
            TrqFil.V.LpFil2[3] = 0;
            return;
        }
        // 无零速控制情况下，伺服使能
        else
        {
            AoutV.TrqRefi = TblExeV.TrqRef;
            TrqRefx = AoutV.TrqRefi;    // 直接使用对应指令
        }
    }
    // TBLCMD无命令情况，正常转矩模式下
    else
    {
        // 从各个指令源获取转矩指令
        if( Kprm.f.EtherCATNet == 1 )
        {
            TRef = KpiEtherCatInputTrqRef( );
        }
        else
        {
            TRef = KpiInputTrqRef( );
        }

        // 一阶滤波运算执行
        AoutV.TrqRefi = MlibLpfilter1( TRef, TrqFil.A.Ktrflpf, AoutV.TrqRefi );
        AoutV.TrqRefiTemp = AoutV.TrqRefi;

        /**** 转矩控制限制优先时Pn430.Y为1时,对转矩指令限制 ****/
        if( ( Prm.trqcmddirtype1 & 0x0010 ) == 0x0010 )
        {
            TrqRefx = AoutV.TrqRefi - BoutV.OverTrq;
              
            TRefLimit = MlibABS( AoutV.TrqRefi );
            if( TrqRefx >= 0 )
            {
                if( TrqRefx >= TRefLimit )
                {
                    TrqRefx = TRefLimit;
                }
                 else if( TrqRefx < 0 )
                {
                    TrqRefx = 0;
                }
            }
            else
            {
                if( TrqRefx < -TRefLimit )
                {
                    TrqRefx = -TRefLimit;
                }
                 else if( TrqRefx > 0 )
                {
                    TrqRefx = 0;
                }
            }
        }
        else
        {

            TrqRefx = AoutV.TrqRefi - BoutV.OverTrq;
        }

        /**** 无效控制模式，直接返回 ****/
        if( BoutV.ZctrlMode.b.zm != CTRLMODE_ZNONE )
        {
            return;
        }
        /**** 非使能状态下复位处理 ****/
        else if( BinV.f.BaseEnable == FALSE )
        {
            AoutV.TrqRefo = 0;
            if ( CoutV.f.Sv.BBSvcRefClrReq )
            {
                  
                TrqCtrl.V.OverTrqIntegBuf[ 1 ] = AoutV.TrqRefi << 1;
                TrqCtrl.V.OverTrqIntegBuf[ 0 ] = 0;
                AoutV.TrqRefi = 0;
            }
            TrqFil.V.FilOut = 0;
            TrqFil.V.LpFil2[0] = 0;
            TrqFil.V.LpFil2[1] = 0;
            TrqFil.V.LpFil2[2] = 0;
            TrqFil.V.LpFil2[3] = 0;
            return;
        }
    }

    /**** 滤波未开启时处理 ****/
    if( TrqFil.V.TrqFilDisable )
    {
        AoutV.TrqRefo   = MlibLimitul( TrqRefx, 0x01000000, -0x01000000 );
        TrqFil.V.FilOut = TrqRefx;
        TrqFil.V.LpFil2[0] = 0;
        TrqFil.V.LpFil2[1] = 0;
        TrqFil.V.LpFil2[2] = 0;
        TrqFil.V.LpFil2[3] = 0;
        return;
    }

    /**** 一阶转矩滤波处理与限制 ****/
    if(TrqFil.V.TrqFilClrCmd == TRUE)
    {
        TrqFil.V.TrqFilClrCmd = FALSE;
    }

    TrqFil.V.FilOut = MlibLpfilter1( TrqRefx, TrqFil.A.Klpf, TrqFil.V.FilOut );


    TrqRefx = MlibLimitul( TrqFil.V.FilOut, 0x01000000, -0x01000000 );

    /**** 二阶转矩滤波处理与限制 ****/
    if( Gprm.f.LpassFil2 == FALSE )
    {
        TrqFil.V.LpFil2[0] = 0;
        TrqFil.V.LpFil2[1] = 0;
        TrqFil.V.LpFil2[2] = 0;
        TrqFil.V.LpFil2[3] = 0;
    }
    else
    {
        TrqRefx = MlibLowPassfilter2(TrqRefx, TrqFil.P.Klpf2, TrqFil.V.LpFil2 );
    }
    AoutV.TrqRefo = MlibLimitul( TrqRefx, 0x01000000, -0x01000000 );
    return;
}
volatile USHORT AngleTest = 0;
volatile ULONG EncErrCnt = 0;
  
/**********************************************************************************************/
/* Function_Name: KpiOutputCurRef         */
/* Description  : 电流指令给定处理
                  输入：
                  输出：    */
/**********************************************************************************************/

#ifdef RunRAM
#pragma CODE_SECTION(KpiOutputCurRef, ".TI.ramfunc");
#endif

void KpiOutputCurRef(void)
{
float fkx;
LONG KX = 0;
LONG Spd = 0;

    /*磁极辨识时，矢量角与转速获取*/
     if(StateM_Var.f.PhaseStudy)
    {
        fkx = (float)ZeroPhaseV.Angle * 6.283185307f / 4096.0f;
        Acr_V.SinVal = __sin( fkx );
        Acr_V.CosVal = __cos( fkx );
        Acr_V.MotWm = 0.0f;
    }
    /*编码器错误时，矢量角与转速获取*/
    else if( StateM_Var.f.EncError )
    {
        fkx = 0.0f;
        Acr_V.SinVal = __sin( fkx );
        Acr_V.CosVal = __cos( fkx );
        Acr_V.MotWm = 0.0f;
        AinK.IqRef = (LONG)((float)Gprm.EstopTrqLmt * 8.940696716e-4);
        EncErrCnt ++;
        if( EncErrCnt > 48000 )
        {
            StateM_Var.f.EncError = 0;
        }
    }
    /*正常运行下，矢量角与转速获取*/
    else                                                         
    {
        EncErrCnt = 0;
        /*IF模式下，矢量角与转速获取*/
        if( BPI_GET_BASE_CTRLMODE() == CTRLMODE_VF )
        {
            fkx = VfCtrl.V.MotPhase;
            Acr_V.MotWm = 0.0f;
        }
        /*非IF模式模式下，矢量角与转速获取*/
        else
        {
            //fkx = (ULONG)(AinK.Pcmpd + MencV.MotPhase);
            fkx = MencV.MotPhase + (ULONG)AinK.Pcmpd;
            if( fkx >=4096 )
            {
                fkx -= 4096;
            }
            AinK.Monitor1 = ((LONG)AinK.Pcmpd * 360)>>12;
        }
        fkx = fkx * 6.283185307f / 4096.0f;
        Acr_V.SinVal = __sin( fkx );
        Acr_V.CosVal = __cos( fkx );
          
        //2^24->15000rad/s
        fkx = (float)AinK.MotSpd * 0.00089406967163f;
        //Acr_V.MotWm = fkx;///   modify by shuangbo  Iprm.f.RvsDir ? -fkx : fkx;
        Acr_V.MotWm = Iprm.f.RvsDir ? -fkx : fkx;
        Acr_V.UqCmd = (float)Prm.VfSetVolt * 8.192f;
    }

    //电流环辅助控制参数传递至CLA模块，用于死区补偿开关、VF控制开关、电压补偿开关
    Acr_V.VFtest = Prm.syssw2;
      
    if( ((Prm.syssw2 & 0x0008) == 0x0008) &&
            ((BoutV.CtrlMode.b.cm == CTRLMODE_TRQ) || (BoutV.CtrlMode.b.cm == CTRLMODE_POS_MIT)))
    {
        AinK.IdRef = AinK.IqRef ;
        AinK.IqRef = 0 ;
    }
    else
    {
        /*陷波滤波处理*/
        AinK.IqRef = NotchDeal( AinK.IqRef );
        /*弱磁控制处理*/
        AinK.IdRef = LpxWFIdCalc( );
    }
      
    /*转矩限制处理*/
    if( AinK.IqRef > BoutK.PosTrqLmt_15000 )                     
    {
        AinK.IqRef = BoutK.PosTrqLmt_15000;
        BoutV.f.Ctrl.TrqClamp = TRUE;
    }
    else if( AinK.IqRef < BoutK.NegTrqLmt_15000 )                
    {
        AinK.IqRef = BoutK.NegTrqLmt_15000;
        BoutV.f.Ctrl.TrqClamp = TRUE;
    }
    else                                                         
    {
        BoutV.f.Ctrl.TrqClamp = FALSE;
    }
#if 1
    /*转矩到达判定处理*/
    if( Gprm.TrqObjReach1 != 0 || Gprm.TrqObjReach2 != 0)
    {
        if( CinV.f.Seq.ServoOffDecM == TRUE)
        {
            AinK.TorqReachCnt = 0;
            BoutV.f.Ctrl.TorqReach = 0;
        }
        else
        {
            KX = AinK.IqRef >= 0 ? AinK.IqRef : -AinK.IqRef;             
            UCHAR Flag = 0;
             Spd = KpiMonSpeedCal( BoutV.UnSpdRef );
             if( ( KX > Gprm.TrqObjReach1 && Spd >= 0 ) || ( KX > Gprm.TrqObjReach2 && Spd <= 0 ))
            {
                Flag = 1;
            }
            if( BoutV.f.Ctrl.TorqReach  ^ Flag )                         
            {
                AinK.TorqReachCnt ++;
            }
            else
            {
                AinK.TorqReachCnt = 0;
            }
            if( AinK.TorqReachCnt > ( (ULONG)Prm.torqcmdtimewindow * 16UL) )
            {
                BoutV.f.Ctrl.TorqReach = Flag;
            }
             if( !BinV.f.BaseEnable )
            {
                AinK.TorqReachCnt = 0;
                BoutV.f.Ctrl.TorqReach = FALSE;
            }
             if( BoutV.f.Ctrl.TorqReach == 1 && CAN_EXFUNC0_11_EN )
            {
                KPI_ALARMSET( ALM_TREACH );
            }
        }
    }
#endif
      
    /*转矩到达判定处理*/
#if ( FPGAUse == 1 )
    ASIC_WR(MREG_Addr0F,(USHORT)AinK.IdRef);
#else
    /*dq轴电流给定传递至CLA电流控制输入*/
    Acr_V.Id_Cmd = (float)AinK.IdRef;
#endif
      
      
#if ( FPGAUse == 1 )
    if(  StateM_Var.f.PhaseStudy == 1 )
    {
        ASIC_WR(MREG_Addr10,AinK.IqRef);                         
    }
    else
    {
        if( Iprm.f.RvsDir )
        {
            ASIC_WR(MREG_Addr10,-AinK.IqRef);                         
        }
        else
        {
            ASIC_WR(MREG_Addr10,AinK.IqRef);                         
        }
    }
#else
    if(  StateM_Var.f.PhaseStudy == 1 )
    {
        Acr_V.Iq_Cmd = (float)AinK.IqRef;
    }
    else
    {
        Acr_V.Iq_Cmd = Iprm.f.RvsDir ? -AinK.IqRef : AinK.IqRef;
    }
#endif
  
    /*dq轴、UVW三相电流、电流有效值监控参数获取*/
    AinK.IqRefMon = Acr_V.Iq_Cmd;
      
    AinK.IdRefMon = AinK.IdRef;
    AinK.IqRefMon1 = (LONG)AinK.IqRef * 100 ;
    AinK.IdRefMon1 = (LONG)AinK.IdRef * 100;
      
 
         
    if( CoutV.f.Sv.BaseEnable )                               
    {
#ifdef CPU1
        if(Iprm.f.RvsDir == FALSE)
        {
            AinK.IqFbMon = AMotVar[0].IqFbk * 100;
            AinK.IdFbMon = AMotVar[0].IdFbk * 100;
        }
        else
        {
            AinK.IqFbMon = -AMotVar[0].IqFbk * 100;
            AinK.IdFbMon = -AMotVar[0].IdFbk * 100;
        }
#endif
 #if 0
        Iee = (long long)AinK.CurrentU * AinK.CurrentU + \
              (long long)AinK.CurrentV * AinK.CurrentV + \
              (long long)AinK.CurrentW * AinK.CurrentW;
        Iee = ( Iee * 10923 ) >> 14;                             
         AinK.CurrentTmp =  (AinK.CurrentTmp * 31 + MlibSqrtu32((ULONG)Iee) + 16 ) >> 5;  
#else
#ifdef CPU1
        fkx = AMotVar[0].Iu * AMotVar[0].Iu + AMotVar[0].Iv * AMotVar[0].Iv + AMotVar[0].Iw * AMotVar[0].Iw;
          
#if 1
        AinK.CurrentU = AMotVar[0].Iu;
        AinK.CurrentV = AMotVar[0].Iv;
        AinK.CurrentW = AMotVar[0].Iw;

#else
        AinK.CurrentU = A1ToC1V.Monitor2;
        AinK.CurrentV = A1ToC1V.Monitor3;
        AinK.CurrentW = A1ToC1V.Monitor4;
#endif
 #endif
        fkx *= 0.6666666667f;
        fkx = __sqrt(fkx);
        AinK.IeeMonitor = AinK.IeeMonitor * 0.96875f + fkx * 0.03125f;
#endif
    }
    else
    {
        AinK.IqFbMon        = 0;
        AinK.IdFbMon        = 0;
        AinK.CurrentTmp     = 0;
        AinK.IeeMonitor     = 0;
        AinK.CurrentU = AMotVar[0].Iu;
        AinK.CurrentV = AMotVar[0].Iv;
        AinK.CurrentW = AMotVar[0].Iw;
    }
      
    /*虚拟电机控制开启处理*/
    if( Kprm.f.MotorLessTestMode == TRUE )
    {
        ApxMotorLessTestModeMechaModel(AinK.IqRefMon);
    }  
}
 
  
 /****************************************************************************************************/
 /*                               The End of the file                                                */
 /****************************************************************************************************/
