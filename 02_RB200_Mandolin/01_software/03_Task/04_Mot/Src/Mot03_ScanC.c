/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot03_ScanC.c
* Version            : V0.1
* Date               : 2024
* Description        : ScanC处理
***********************************************************************************************/

#include "Main.h"
 
  
/**********************************************************************************************/
/* Function_Name: CpiScanCInitMain        */
/* Description  : ScanC初始化
                  调用：main函数*/
/**********************************************************************************************/
void CpiScanCInitMain( void )
{
    /* 伺服驱动器初始默认的工作模式( 模式A ) */
   	CoutV.CtrlMcmd.dw = Iprm.CtrlModeA;
}
 
  
  
/**********************************************************************************************/
/* Function_Name: CpxOutputMain        */
/* Description  : ScanC输出输入接口处理
                  调用：SCANC*/
/**********************************************************************************************/
void CpxOutputMain( void )
{
    /* 基本封锁时位置偏差/控制指令清除要求（OT时不清除）*/
    if( CoutV.f.Sv.BkBeReq == FALSE )
    {
        CoutV.f.Sv.BBSvcRefClrReq = TRUE;
    }
    else if( CoutV.f.Sv.BaseEnable || (!CoutV.f.Sv.OtBeReq) )
    {
        CoutV.f.Sv.BBSvcRefClrReq = FALSE;
    }
  
    /* 监控数据处理 */
    LpxMakeMonitorData( );

    /* 报警监视处理部分相关数据处理 */
    LpxAlmLatchMonitorSeuqence( );

    /* 残留振动（位置环低频振动）频度检测处理 */
    LpxRemVibrationMon( );
    return;
}
 
  
/**********************************************************************************************/
/* Function_Name: CpxInputMain        */
/* Description  : ScanC输入接口处理（控制使能、控制模式、端子状态）
                  调用：SCANC*/
/**********************************************************************************************/
void CpxInputMain( void )
{
    /* ScanC 中开关量输入信号更新 */
    ScanCinputAptIf();

    /*速度切换与加速度切换接口处理*/
    CoutV.ModeSwAcc = CinK.MotSpd - CoutV.ModeSwSpd;
    CoutV.ModeSwSpd = CinK.MotSpd;
  
    /*电机停止状态判定*/
    LpxCheckMotorStop( );

    /*CANopen和EtherCAT电机运行状态与转速到达判定*/
    if( Kprm.f.EtherCATNet == 1 )
    {
        LpxEtherCatCheckMotorRun( );				         
        LpxEtherCatCheckMotorVcmp( );                        
    }
    else if( Kprm.f.CanOpenNet == 1 )
    {
        LpxCanOpenCheckMotorRun( );
        LpxCanOpenCheckMotorVcmp( );
    }
    else
    {
        LpxCheckMotorRun( );						         
        LpxCheckMotorVcmp( );                                
    }
    LpxCheckMotorLowVel();
    LpxVelOver();

    MIT_Fedback_Mon();

    /*自举状态判定*/
    CinK.f.PumpOnComp = KioV.f.PumpOnComp;
}
  
/**********************************************************************************************/
/* Function_Name: KpxScanCInput        */
/* Description  : ScanC输入处理
                  调用：ScanC                                              */
/**********************************************************************************************/
void KpxScanCInput( void )
{
LONG	lwk0;
    /* 计算电机速度 [2^24/OvrSpd] */
    if( MencV.f.EncDataNG )					//Encoder Data NG
    {
        CinK.MotSpd = 0;			        //电机速度
        CinK.AbsMotSpd = 0;					//电机速度绝对值
//        CinK.FencSpd = 0;
    }
    else
    {
        if(KioV.MotSpdCntC > 0)             //Encoder Data OK
        {
            CinK.MotSpd = (float)KioV.MotSpdSumC / (float)KioV.MotSpdCntC;
        }
//        if(KioV.FencSpdCntC > 0)             //Encoder Data OK
//        {
//            CinK.FencSpd = (float)KioV.FencSpdSumC / (float)KioV.FencSpdCntC;
//        }
        CinK.AbsMotSpd = MlibABS( CinK.MotSpd );		//电机速度
    }
  
    CinK.f.PumpOnComp = KioV.f.PumpOnComp;		//控制状态通知（完成/未完成）

    /* 电流给定 */
    CinK.IdRefMon = AinK.IdRefMon;		        //d轴电流指令监视[15000/Imax]
    CinK.IqRefMon = AinK.IqRefMon;				//q轴电流指令监视[15000/Imax]

    /* 电流反馈 */
    CinK.IdFbMon = AinK.IdFbMon;				//d轴电流反馈监视  [15000/Imax]
    CinK.IqFbMon = AinK.IqFbMon;				//q轴电流反馈监视  [15000/Imax]

    /* 转矩指令 [2^24/Imax] */
    if( Iprm.f.RvsDir )
    {
        CinK.TrqRefMon = -BinK.TrqRefMon;		//扭矩指令[2^24/MaxTrq]
    }
    else
    {
        CinK.TrqRefMon = BinK.TrqRefMon;
    }
    CinK.AbsTrqRefMon = MlibABS( CinK.TrqRefMon );	//扭矩指令绝对值[2^24/MaxTrq]      [2^24/MaxTrq]

    /* 电机脉冲增量 */
    lwk0 = KioV.MotPosC - CinK.MotPos;
    CinK.MotPos  = KioV.MotPosC;
    CinK.dMotPos = lwk0;

    /* 脉冲频率计算(转速) */
    lwk0 = KioV.PcmdCntrC - CinK.PcmdCntr;
    CinK.PcmdCntr = KioV.PcmdCntrC;
    CinK.dPcmdCnt = lwk0;

    /* 再生制动动作时间计数处理 */
    lwk0 = KioV.RegOnCount[0];
    CinK.dRegOnCount = lwk0 - KioV.RegOnCount[1];
    KioV.RegOnCount[1] = (SHORT)lwk0;

    /* 控制主回路母线电压 */
    CinK.DcVolt   = BinK.DcVolt;

    CoutK.f.AlmRst = (CinV.f.Seq.AlmReset)? TRUE : FALSE;
}
  
  
  
LONG	BpiGetCoinOffTime( void )
{
#if(FLOAT_USE == 1)
    float wk;
    wk = BoutV.UnCoinOffTimer * fKPI_SBCYCLEMS;
#else
    LONG    scantime = KPI_SBCYCLEUS;
    LONG    wk;
    wk = BoutV.UnCoinOffTimer  * scantime / 100;
#endif
    return wk;
}
  
/**********************************************************************************************/
/* Function_Name: CpiScanCMain        */
/* Description  : ScanC主处理
                  调用：ScanC              */
/**********************************************************************************************/
void CpiScanCMain( void )
{
    /* 输入处理 */
    CpxInputMain( );	    //ScanC主处理输入处理
    /* 故障检测 */
    CpxCheckAlarm();
    /* 监测伺服振动 */
    CpxCheckSvVib();
    /* 故障,警告管理 */
    KpiAlarmManager();
    /* CANopen紧急报文处理 */
	EMCY_Clear();
	/* 伺服状态管理 */
	CpxServoSequence();
	/* 程序JOG序列处理 */
    CpxPrgJogPosSequence();
    /* 离线惯量辨识 */
    CpxJatOfflineCalc();
    /* 高级调整 */
    CpxAdvancedAutoTuning( CoutV.f.Sv.VibDetFlg, BpiGetCoinOffTime( ) );
    /* 电角度由标幺值转deg */
    MotorPhaseCnt_Deg();
    /* 轴2软件升级处理与故障复位处理 */
	//ACR_MotBP( );
	//MotB_OC_Reset( );
	/* ScanC主处理输出函数 */
    CpxOutputMain( );
	BrakePWM_Control( );



}
  
/**********************************************************************************************/
/* Function_Name: IntScanC        */
/* Description  : ScanC中断服务函数
               调用：ScanC*/
/**********************************************************************************************/
void IntScanC( void )
{
    /* SCANC输入函数 */
    KpxScanCInput( );
      
    /* SCANC主程序处理 */
 	CpiScanCMain( );

 	/* 用户程序处理：原点回归 */
    UserD_TaskC( );
    /* 双轴CAN断线处理*/
    MuxAxis485_LineOff();

    /* 上电时间计数，用于编码器上电处理*/
	if(KnlV.MainTimer < 0xFFFF0000)
	{
		KnlV.MainTimer += KPI_SCCYCLEMS;
	}
	/* 输出信号处理 */
    LpxCoutputAptIf( );
    /*运行时间戳记录 */
 #if 0
    if( CoutK.f.PowerOn )                                    
#endif
    {
        if( ++KnlV.TmStampCntx >= KPI_SCANC_MS( 100 ) )
        {
            KnlV.TmStampCntx = 0;
            if( KnlV.TmStamp < 0xFFFFFFFF )                    
            {
                ++KnlV.TmStamp;
            }
              
             ++KnlV.TmStampSaveCnt;
             /* 每隔1小时保存一次运行时间 */
            if( KnlV.TmStampSaveCnt > (36000UL * 2) )
            {
                KnlV.TmStampSaveCnt = 0;
                TmStampSaveEn();       //准备EEP存储时间变量
            }
        }
    }        
    KnlV.ScanCcnt++;
}
 
