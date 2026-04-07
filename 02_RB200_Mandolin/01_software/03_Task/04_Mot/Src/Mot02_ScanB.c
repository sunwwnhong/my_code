/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot01_ScanB.c
* Version            : V0.1
* Date               : 2024
* Description        : ScanB处理
***********************************************************************************************/

#include "Main.h"
void LpxMakeCoinOffTime( void );
void LpxSettlingTimeCalc( void );
 
  
/**********************************************************************************************/
/* Function_Name: BpiScanBInitMain        */
/* Description  : ScanB初始化
                  调用：main函数*/
/**********************************************************************************************/
void BpiScanBInitMain( void )
{
    /*  初始化伺服增益切换 */
    BpxInitServoGainChange();
      
    /*  初始化位置管理  */
    BpxInitSvcPositionManager();
      
    /*  初始化A型振动抑制  */
    BpxInitResVibControl();
      
    /*  初始化位置稳定化控制  */
    BpxInitPosStbCtrl();
      
    /*  初始化振动检测 */
    BpxInitVibrationDetect();
      
    /*  初始化摩擦补偿 */
#if( DIDOVS != 0 )
		BpxInitDisturbObserver( );
#endif
	/* 齿隙补偿 */
 #if ( SVFSEL_BLSH_COMMON_PROC )
    BpxInitBlshCompensate( );
#endif
    /* 免调整初始化 */
 #if( TUNINGLESS_CTRL != 0 )
	BpxInitTuningLess( );
#endif
}
 

#define	DELAY_ALM_TO_COIN	KPI_SCANB_MS( 10 )
/**********************************************************************************************/
/* Function_Name: LpxBinputAptIf        */
/* Description  : ScanB端子信号输入处理
                  调用：SCANB*/
/**********************************************************************************************/
void	LpxBinputAptIf( void )
{
HWSIN	Inx;
  
    /* 序列信号输入 */
    KPI_SIN_START( Inx );
    BinV.f.Ctrl.EnbPCtrl    = KPI_SIN_PCON( Inx );
    BinV.f.Sv.Inhibit       = KPI_SIN_INHIBIT( Inx );
    BinV.f.Sv.GainSel0      = KPI_SIN_GAINSEL0( Inx );
    BinV.f.Sv.TlimitSel     = KPI_SIN_TlimitSel( Inx );
    BinV.f.Sv.Psel          = KPI_SIN_PSEL( Inx );
    BoutV.f.Sv.PselA        = ( Iprm.PGAINSet == 0x00 ) ? 0 :BinV.f.Sv.Psel;
    BinV.f.Sv.PerClrSignal  = KPI_SIN_CLR( Inx );
    BinV.f.Sv.ORGEn         = KPI_SIN_ORGEN( Inx );
    BinV.f.Sv.ORGS          = KPI_SIN_ORGS( Inx );

    /* 增益切换用增益号 */
    BinV.GselNum = BinV.f.Sv.GainSel0;
    /* 位置偏差清除电平信号 */
    PosClrDeal();
}
 
  
/**********************************************************************************************/
/* Function_Name: BpxInputMain        */
/* Description  : ScanB输入接口处理（控制使能、控制模式、端子状态）
                  调用：SCANB*/
/**********************************************************************************************/
void	BpxInputMain( void )
{
    BinV.fl = BinV.f;

    BinV.f.BaseEnable = ( CoutV.f.Sv.BaseEnable )? TRUE : FALSE;
    LpxServoControlMode( );
    LpxBinputAptIf( );
}
  
/**********************************************************************************************/
/* Function_Name: BpxOutputMain        */
/* Description  : ScanB输出输入接口处理
                  调用：SCANB*/
/**********************************************************************************************/
void	BpxOutputMain( void )
{
  
    /* 整定时间测量处理 */
    if( KnlV.ScanBcnt & 0x08 )
    {
        LpxSettlingTimeCalc( );
    }
    /* 位置整定时间 --> Un105 */
    LpxMakeSettlingTime( );

    /* 最大过冲-->Un106 */
    LpxMakeMaxOverShoot( );

    /* 定位振荡持续时间计算-->Un10B */
    LpxMakeCoinOffTime( );

    /* 上次位置指令增量值保存 */
    PosMngV.LastdPcmda = PosMngV.dPcmda;

    /* SCANB->SCANC速度与位置量传递 */
    KioV.MotSpdSumB += BinK.MotSpd; //ScanB 电机速度累加
    KioV.MotSpdCntB++;

    /* Data Copy for ScanC */
    if( KPX_CHK_SCANC_START( KnxV.ScanCstrtCnt ) )		//每16个ScanB启动一次ScanC
    {
        KioV.MotPosC      = BinK.MotPos;			    //SCANC用电机位置数据更新
        KioV.PcmdCntrC    = BoutK.PcmdRingCntr;			//SCANC用位置指令计数器更新
        KioV.MotSpdSumC   = KioV.MotSpdSumB;
        KioV.MotSpdCntC   = KioV.MotSpdCntB;
        KioV.MotSpdSumB   = 0;
        KioV.MotSpdCntB   = 0;
    }

    /* 监视器输出变量 */
    if( BoutV.CtrlMode.b.cm == CTRLMODE_SPD || BoutV.CtrlMode.b.cm == CTRLMODE_JOG)
        BoutV.UnSpdRef    = BinV.SpdRef;
    else
        BoutV.UnSpdRef    = AoutV.SpdRefi;

    if( Kprm.f.EtherCATNet == 1 )
    {
#if(FLOAT_USE == 1)
        s32VelDemandVal = Iprm.fKmonspd1 * (float)BoutV.UnSpdRef;
#else
        s32VelDemandVal     = KpiMonSpeedCal( BoutV.UnSpdRef ) ;
#endif
#if(FLOAT_USE == 1)
        s16TorqDemandVal = Iprm.fkmontrq1 * (float)CinK.TrqRefMon;
#else
        s16TorqDemandVal    = KpiMonTorqueCal1( CinK.TrqRefMon );
#endif
    }
    else if( Kprm.f.CanOpenNet == 1 )
    {
#if(FLOAT_USE == 1)
        ODDatArr[ OD_606B ].all = Iprm.fKmonspd1 * (float)BoutV.UnSpdRef;
#else
        ODDatArr[ OD_606B ].all = KpiMonSpeedCal1( BoutV.UnSpdRef );
#endif
#if(FLOAT_USE == 1)
        ODDatArr[ OD_6074 ].all = Iprm.fkmontrq1 * (float)CinK.TrqRefMon;
#else
        ODDatArr[ OD_6074 ].all = KpiMonTorqueCal1( CinK.TrqRefMon);
#endif
    }
    else
    {
    }
    BoutV.AmonSpdRef  = BoutV.SpdRefo + BoutV.SpdFFCx;

    //转矩给定值获取
    if( Iprm.f.RvsDir == 0)
    {
        BoutV.AmonTrqRef  = BinK.TrqRefMon;
    }
    else
    {
        BoutV.AmonTrqRef  = -BinK.TrqRefMon;
    }
    if( ((Prm.syssw2 & 0x0008) == 0x0008) && (BoutV.CtrlMode.b.cm == CTRLMODE_TRQ) )
    {
        BoutV.AmonTrqRef = AoutV.TrqRefi;

    }
    BoutV.AmonIdRef   = BinK.IdRefMon;
    BoutV.AmonPosErra = PosMngV.PosErrA.per32s;
    BoutV.AmonPosErrx = PosMngV.PosErr;
    BoutV.TrcCtrlTrqRef = TrqFil.V.FilOut + AoutV.TrqFFCx - BoutV.AmonDisTrq;

    //干扰输入前扭矩指令
    switch( TrqFil.V.TrqInputPos )
    {
        case 0x01:
            BoutV.TrcCompTrqRef = AoutV.TrqRefi;
            break;
        case 0x02:
            BoutV.TrcCompTrqRef = TrqFil.V.FilOut;      //低通滤波器之后
            break;
        case 0x03:
            BoutV.TrcCompTrqRef = BinK.TrqRefFilMon;    //转矩指令过滤后
            break;
        case 0x00:
        default :
            BoutV.TrcCompTrqRef = 0;
            break;
    }
}
  
/**********************************************************************************************/
/* Function_Name: BpxScanBMain        */
/* Description  : ScanB主处理函数
                  调用：ScanB
                  输入：
                  输出：*/
/**********************************************************************************************/
void BpxScanBMain( void )
{
    /*ScanB输入接口处理（控制使能、控制模式、端子状态）*/
    BpxInputMain( );
    /* 增益切换 */
    BpxServoGainChange( );
    /* Table 运行 */
    BpxTableDriveExecute( );

    /* 控制模式的选择( 来自设置模式还是Table表 ) */
    if( (TblExeV.TblCmd == TBLCMD_NOCMD) || (BoutV.CtrlMode.b.zm != CTRLMODE_ZNONE) )
    {
        BoutV.ZctrlMode.b.zm    = BoutV.CtrlMode.b.zm;
        BoutV.ZctrlMode.b.zmchg = BoutV.CtrlModeChg.b.zm;
    }
    else
    {
        BoutV.ZctrlMode.b.zm    = TblExeV.TblZmd.b.zm;
        BoutV.ZctrlMode.b.zmchg = TblExeV.TblZmd.b.zmchg;
    }

    /* 伺服三环指令控制处理部分 */
    BpxYecServoControl( );  //伺服控制模块输入计算
    /* 伺服离线惯量辨识 */
    BpxJatOfflineCalc( );

    /* 转矩限制处理 */
    BpxTorqueLimitControl( );
    /* 控制响应指标与输出监控变量计算、电流限制 */
    BpxOutputMain( );

    /* 数据采集：用于Fn功能和示波器功能 */
    BpxSvcDtraceExecute( );
    BpxDataTraceExecute( );

    /* CanOpen 协议处理 */
    if( Kprm.f.CanOpenNet )
    {
        Can_Deal();         //CAN接收报文处理
        ComLedStatu( );     //CAN状态LED灯处理
    }
 }
  
/**********************************************************************************************/
/* Function_Name: IntScanB2        */
/* Description  : ScanB2处理函数
               调用：ScanB*/
/**********************************************************************************************/
  
void IntScanB2(void )
{
    KnlV.f.ScanB250us ^= 0x01;      //ScanB 250us Cycle Flag

    /* 每隔250us处理一次 */
    if(KnlV.f.ScanB250us)
    {
        ReadDIStatus();              //输入端子信号读取(键值,SI1-SI9)
        LpxDetectDcVolt();           //电压检测&电压故障保护
        //LpxRegeneControl();          //再生制动
    }
    else
    {
#if (FLOAT_USE == 1)
        FLpxWFPrmCalc();            //弱磁
#else
        LpxWFPrmCalc( );
#endif
    }
}
 
  
/**********************************************************************************************/
/* Function_Name: IntScanB        */
/* Description  : ScanB中断服务函数
                  调用：ScanA条件触发，125us周期*/
/**********************************************************************************************/
void IntScanB( void )
{
          
    /* ScanB输入函数 */
    KpxInputScanB( ); //BINK输入参数获取：位置指令、位置与速度反馈、电流给定
                      //控制指令、DI信号、模式获取

    /* SCANB伺服主控制模块 */
    BpxScanBMain( );        //SCANB主函数

    /* 特殊功能处理部 */
    UserD_TaskB( );         //原点回归处理 输出AinK.ORGDelta

    /* 自举 */
    LpxChargePumpControl(  );

    TlObs_Main();

    /* USB通讯信息管理 */
    DpxUsbifMsgManager( );
    /* DO端口输出 */
    LpxBoutputAptIf( );
    YOutPutToFPGA( );

    /* TPDO 数据发送处理 */
    if( Kprm.f.CanOpenNet )
    {
        TPDO_DataSendDeal();
    }

    KnlV.ScanBcnt++;
    KPI_DI( );
    KnxV.ScanCstrtCnt++;    //ScanC 中断请求计数
}
 
  
  
  
/**********************************************************************************************/
/* Function_Name: LpxSettlingTimeCalc                                                         */
/* Description  : 定位整定时间计算：记录位置指令完成后只到位置持续在完成范围的时间（125us单位）
                输出：BoutV.OutSettlingTime 整定时间                                              */
/**********************************************************************************************/
void	LpxSettlingTimeCalc( void )
{
    /* 运行过程中停止整定时间计算 */
 	if( PosMngV.dPcmda != 0 )			//正在动作
	{
		if( BioxV.settlingtime.cmsub_in_d == 0 )	 //输入位置指令的最初扫描
		{
			BioxV.settlingtime.OutCnt = BioxV.settlingtime.cnt_buf; //将保持的整定时间代入输出用变量
 		}
 		 
		/* 动作中清除变量 */
		BioxV.settlingtime.f.calcFlg		= FALSE;     //关闭运算中标志
		BioxV.settlingtime.f.coin_signal_d	= FALSE;     //上次COIN信号OFF
		BioxV.settlingtime.cnt			    = 0;		 //清除计数器
	}
	else if( BioxV.settlingtime.cmsub_in_d != 0 )	//位置指令发送完成开始计算整定时间
	{		
		BioxV.settlingtime.f.calcFlg = TRUE;		     
	}
 	 
 	/* 整定时间计算：从指令发送完成开始计时，位置在Coin范围内锁存计数值作为整定时间，
 	        只到计数值达到65535，将最终的锁存值作为整定时间      */
	if( BioxV.settlingtime.f.calcFlg )
	{
	    //整定时间计算运算
 		if( BioxV.settlingtime.cnt == 65535 )
		{
			BioxV.settlingtime.OutCnt = BioxV.settlingtime.cnt_buf;
		}
 		 
 		/* 仅在定位完成信号为ON时缓冲整定时间 */
		if( ( BoutV.f.Ctrl.Coin == TRUE ) && ( BioxV.settlingtime.f.coin_signal_d == FALSE ) )
		{
			BioxV.settlingtime.cnt_buf = BioxV.settlingtime.cnt;
		}
 		 
		/* 使计数器递增（其中65535为极限） */
		if( BioxV.settlingtime.cnt != 65535 )
		{
			BioxV.settlingtime.cnt++;
		}
	}
 	 
	/* 保留上次值 */
	BioxV.settlingtime.cmsub_in_d       = PosMngV.dPcmda;		        //保持差分位置指令
	BioxV.settlingtime.f.coin_signal_d  = BoutV.f.Ctrl.Coin;	        //保持COIN信号
	BoutV.OutSettlingTime               = BioxV.settlingtime.OutCnt;
 	return;
 }
  
  
/**********************************************************************************************/
/* Function_Name: BpiRsetCoinOffTime                                                         */
/* Description  : 定位振荡时间清除（Fn201无指令输入型智能调整用）
            调用：Fn高级整定*/
/**********************************************************************************************/
void BpiRsetCoinOffTime( void )
{
#if(FLOAT_USE == 1)
    BoutV.UnCoinOffTimer = 0.0f;
#else
	BoutV.UnCoinOffTimer = 0;
#endif
	BioxV.CoinLatch = FALSE;
	BoutV.f.CoinLatch = FALSE;
	return;
}
  
  
/**********************************************************************************************/
/* Function_Name: LpxMakeCoinOffTime                                                         */
/* Description  : 定位振荡持续时间计算
                  记录位置指令发完后，实际位置从定位位置范围又到定位完成范围外的振动时间（125us）
            输出：BoutV.UnCoinOffTimer 整定时间                                              */
/**********************************************************************************************/
void	LpxMakeCoinOffTime( void )
{
    //位置控制到达后，触发Coin时间计数
    if( (BoutV.CtrlMode.b.cm == CTRLMODE_POS) && (PosMngV.dPcmda == 0) )
    {
        if( BoutV.f.Ctrl.Coin )
        {
            BioxV.CoinLatch = TRUE;
            BoutV.f.CoinLatch = TRUE;
        }
    }
    else
    {
        BioxV.CoinLatch = FALSE;
        BoutV.f.CoinLatch = FALSE;
    }
    //振动次数记录
    if( (BioxV.CoinLatch) && (!BoutV.f.Ctrl.Coin) )
    {
#if(FLOAT_USE == 1)
        if(BoutV.UnCoinOffTimer < 16777216.0f)
        {
            BoutV.UnCoinOffTimer += 1.0f;
        }
#else
        if(BoutV.UnCoinOffTimer < 0x1000000)
        {
            BoutV.UnCoinOffTimer++;
        }
#endif
    }

    //非位置控制模式，定位振荡时间清除
    if( BoutV.CtrlMode.b.cm != CTRLMODE_POS)
    {
        BpiRsetCoinOffTime( );
    }
    return;
}
 
