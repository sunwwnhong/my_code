/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                   */
/*											2017 ~													*/
/****************************************************************************************************/
/*																									*/
/*																									*/
/*		User21_AlmLatchMonitor.c : 当前故障时相关数据记录处理    									*/
/*																									*/
/*																									*/
/****************************************************************************************************/
#include "Main.h"



/****************************************************************************************************/
/*																									*/
/*		警报监视器数据处理       																	*/
/*																									*/
/****************************************************************************************************/
void	LpxMakeAlmMonitorData( void )
{
/*--------------------------------------------------------------------------------------------------*/
/*		0x801 : 报警代码 [-]																	    */
/*--------------------------------------------------------------------------------------------------*/
        CioxV.AlmLtMon.AlmCode = Alm.AlmWrnCode;
/*--------------------------------------------------------------------------------------------------*/
/*		0x802 : 报警时间戳 [-]																	    */
/*--------------------------------------------------------------------------------------------------*/
        CioxV.AlmLtMon.TmStamp = KnlV.TmStamp;
		return;
}

/****************************************************************************************************/
/*																									*/
/*		警报锁存器用监控数据制作        															*/
/*																									*/
/****************************************************************************************************/
#define	MONSETBIT( sig, bit )	((sig)? (1UL<<bit) : 0x0000)
/*--------------------------------------------------------------------------------------------------*/
void	LpxMakeAlmLatchMonitorData( void )
{
LONG	val;	/* <V194> */
/*--------------------------------------------------------------------------------------------------*/
/*		0x802 : 电机转速                        													*/
/*--------------------------------------------------------------------------------------------------*/
      val = KpiMonSpeedCal( CoutV.UnMotSpdx );
      CioxV.AlmLtMon.MotSpd = (SHORT)MlibLimitul(val, 0x00007FFF, 0xFFFF8000) ;
        
/*--------------------------------------------------------------------------------------------------*/
/*		0x803 : 速度指令 [min-1, mm/s]																*/
/*--------------------------------------------------------------------------------------------------*/
      val = KpiMonSpeedCal( BoutV.UnSpdRef );
      CioxV.AlmLtMon.SpdRef = (SHORT)MlibLimitul(val, 0x00007FFF, 0xFFFF8000) ;
        
/*--------------------------------------------------------------------------------------------------*/
/*		0x804 : 内部转矩指令 [%]																    */
/*--------------------------------------------------------------------------------------------------*/
#if(FLOAT_USE == 1)
    CioxV.AlmLtMon.TrqRef =(float)CoutV.UnTrqRef * Iprm.fKmontrq;
#else
    CioxV.AlmLtMon.TrqRef = (SHORT)KpiMonTorqueCal( CoutV.UnTrqRef );
#endif

/*--------------------------------------------------------------------------------------------------*/
/*		0x805 : 输入指令脉冲速度                													        */
/*--------------------------------------------------------------------------------------------------*/
#if(FLOAT_USE == 1)
    val = (float)CinK.dPcmdCnt * Iprm.fKmonpcmdspd2ms;
#else
    val = MlibMulgain( CinK.dPcmdCnt, Iprm.Kmonpcmdspd2ms );
#endif
    CioxV.AlmLtMon.PcmdSpd = (SHORT)MlibLimitul(val, 0x00007FFF, 0xFFFF8000) ;

/*--------------------------------------------------------------------------------------------------*/
/*		0x806 : 位置偏差量 [pulse]													                    */
/*--------------------------------------------------------------------------------------------------*/
    CioxV.AlmLtMon.PosErr = PosMngV.PosErrA.per32s;

/*--------------------------------------------------------------------------------------------------*/
/*		0x810 : 内部信号监视器 [-]																	    */
/*--------------------------------------------------------------------------------------------------*/
		CioxV.AlmLtMon.InterSignal = (	MONSETBIT( CoutV.f.Seq.MainPowerOn,		0	) |
									//	MONSETBIT( MencV.f.EncReady,			1	) |
										MONSETBIT( CinK.f.EncReady,				1	) |
									//	MONSETBIT( CoutV.f.Sv.SvonReq,			2	) |
										MONSETBIT( CoutK.f.DbBeReq,				2	) |
										MONSETBIT( CoutV.f.Sv.DbOn,				3	) |
										MONSETBIT( Iprm.f.RvsDir,				4	) |
										MONSETBIT( BoutV.f.ModeSWFlag,			5	) |
										MONSETBIT( CoutV.f.Sv.Vrefon,			6	) |
										MONSETBIT( CoutV.f.Sv.Trefon,			7	) |
										MONSETBIT( CoutV.f.Sv.Prefon,			8	) |
										MONSETBIT( CoutV.f.Sv.PrefSign,			9	) |
										MONSETBIT( CoutV.f.Sv.PerrClr,			10	) |
										MONSETBIT( BoutV.f.BiasONFlag,			11	) |
										MONSETBIT( CoutK.f.Acon,				12	) |
//待完善										MONSETBIT( KPI_MON_HWSOUT_RELAYON,		13	) |
//待完善										MONSETBIT( KPI_MON_HWSOUT_REGENON,		14	) |
										MONSETBIT( CoutV.f.Sv.RegeAlmSignal,	15	) |
										MONSETBIT( CoutV.f.Sv.BaseEnable,		16	) |
										MONSETBIT( 0,							17	) |
#if		CCSW_MENCID == MENCID_SERIAL
//待完善										((MencV.RxAlmCode.w & 0x0040) <<		13	) |
#elif	CCSW_MENCID == MENCID_ANALOG
										((MencV.RxAlmCode.w & 0x0001) <<		19	) |
#endif
										MONSETBIT( BoutV.f.InertiaTuning,		20	) |
										MONSETBIT( (CoutV.f.Sv.BaseEnable & !MencV.f.PhaseReady),	21	) |
										MONSETBIT( MencV.f.PhaseReady,			22	) );

/*--------------------------------------------------------------------------------------------------*/
/*		0x814 : 内部入力信号モニタ [-]																*/
/*--------------------------------------------------------------------------------------------------*/
//待完善		KPX_READ_PCMD_STATUS( lwk );
		CioxV.AlmLtMon.InSignal = (	MONSETBIT( CinV.f.Seq.ServoOn,			0	) |
									MONSETBIT( BinV.f.Ctrl.EnbPCtrl,		1	) |
									MONSETBIT( CinV.f.Sv.Pot,				2	) |
									MONSETBIT( CinV.f.Sv.Not,				3	) |
									MONSETBIT( CinV.f.Seq.AlmReset,			4	) |
									MONSETBIT( BinV.f.Sv.TlimitSel,			5	) |
//									MONSETBIT( BinV.f.Sv.Ncl,				6	) |	
									MONSETBIT( CinV.f.Sv.ABSEn,				7	) |
									MONSETBIT( CinV.f.Sv.SpdD,				8	) |
									MONSETBIT( CinV.f.Sv.SpdA,				9	) |
									MONSETBIT( CinV.f.Sv.SpdB,				10	) |
									MONSETBIT( CinV.f.Sv.Csel,				11	) |
									MONSETBIT( CinV.f.Sv.Zclamp,			12	) |
									MONSETBIT( BinV.f.Sv.Inhibit,			13	) |
									MONSETBIT( BinV.f.Sv.GainSel0,			14	) |
									MONSETBIT( BinV.f.Sv.GainSel1,			15	) |
									MONSETBIT( CinV.f.Sv.PoleDetect,		16	) |
									MONSETBIT( 0,							17	) |
									MONSETBIT( BinV.f.Sv.DecSignal,			18	) |
									((BoutV.ExtInState & 0x7) <<			19	) |
//待完善									MONSETBIT( KPX_CHECK_PCMD_CADAT( lwk ),	24	) |
// 待完善									MONSETBIT( KPX_CHECK_PCMD_CBDAT( lwk ),	25	) |
									MONSETBIT( BinV.f.PerClrSignal,			26	) |
									MONSETBIT( BinV.f.Sv.Psel,				27	) );

/*--------------------------------------------------------------------------------------------------*/
/*		0x818 : 内部出力信号モニタ [-]																*/
/*--------------------------------------------------------------------------------------------------*/
		CioxV.AlmLtMon.OutSignal = (	MONSETBIT( Alm.f.AlmFlag,				0	) |
										MONSETBIT( BoutV.f.Ctrl.Coin,			1	) |
										MONSETBIT( CoutV.f.Ctrl.ReachSpd,		2	) |
										MONSETBIT( CoutV.f.Ctrl.MotorMoving,	3	) |
										MONSETBIT( CoutV.f.Seq.ServoReady,		4	) |
										MONSETBIT( BoutV.f.Ctrl.TrqClamp,		5	) |
										MONSETBIT( BoutV.f.Ctrl.SpdClamp,		6	) |
										MONSETBIT( CoutV.f.Seq.BrkReleasing,	7	) |
										MONSETBIT( Alm.f.WrnFlag,				8	) |
										MONSETBIT( BoutV.f.Sv.Near,				9	) |
										MONSETBIT( BoutV.f.Sv.PgCphase,			10	) |
										MONSETBIT( BoutV.f.Sv.PselA,			22	) );

/*--------------------------------------------------------------------------------------------------*/
/*		0x820 : 主回路母線電圧 [V]																	*/
/*--------------------------------------------------------------------------------------------------*/
		CioxV.AlmLtMon.DcVoltage = BinK.UnDcVolt;			        /* <V135>	*/
/*--------------------------------------------------------------------------------------------------*/
/*		0x821 : 電流検出値 [0.01A]																		*/
/*--------------------------------------------------------------------------------------------------*/
		CioxV.AlmLtMon.IFBMon = KpiMonCurrentCal1( CoutV.UnCrntLatch);
/*--------------------------------------------------------------------------------------------------*/
/*		0x822 : 累積負荷率 [%(周期2ms)]																*/
/*--------------------------------------------------------------------------------------------------*/
		CioxV.AlmLtMon.MotLoad = (USHORT)KpiMonCurrentCal( CoutV.UnCrntRef );

/*--------------------------------------------------------------------------------------------------*/
/*		0x823 : 回生負荷率 [10%(周期2ms)]															*/
/*--------------------------------------------------------------------------------------------------*/
		CioxV.AlmLtMon.RgPower = CoutV.UnRgPower;

/*--------------------------------------------------------------------------------------------------*/
/*		0x824 : ＤＢ抵抗消費電力 [%(周期2ms)]														*/
/*--------------------------------------------------------------------------------------------------*/
		CioxV.AlmLtMon.DbPower = CoutV.UnDbPower;

/*--------------------------------------------------------------------------------------------------*/
/*		0x825 : 最大累積負荷率 [%]																	*/
/*--------------------------------------------------------------------------------------------------*/
//		CioxV.AlmLtMon.MaxMotLoad10s = (USHORT)KpiMonCurrentCal( CoutV.UnIsqrSumMax );
		CioxV.AlmLtMon.MaxMotLoad10s = (USHORT)CoutV.UnIsqrSumMax ;

/*--------------------------------------------------------------------------------------------------*/
/*		0x826 : 慣性モーメント比/重量比 [%]															*/
/*--------------------------------------------------------------------------------------------------*/
		CioxV.AlmLtMon.JLRatio = CoutV.EstimatJrat;		/* 制御で使用している慣性比を保存			*/

/*--------------------------------------------------------------------------------------------------*/
/*		0x830 : シリアルエンコーダ通信異常回数 [-]													*/
/*--------------------------------------------------------------------------------------------------*/
		CioxV.AlmLtMon.EncComErrCnt = MencV.ComErrCnt;
		return;
}




/****************************************************************************************************/
/*																									*/
/*		报警信息锁存处理部分              															*/
/*																									*/
/****************************************************************************************************/
void	LpxAlmLatchMonitorSeuqence( void )
{

/*--------------------------------------------------------------------------------------------------*/
/*		主回路电压在较低时,不进行故障的更新处理                                    					*/
/*--------------------------------------------------------------------------------------------------*/
#if 0
  if ( CinK.DcVolt < (Iprm.UvLevel - 20 ) )
    {
        CioxV.AlmLatchSeqPtr = 0;
    }
    else
#endif
    {
        switch ( CioxV.AlmLatchSeqPtr )
        {
            /*--------------------------------------------------------------------------------------*/
            case 0:
                /*----------------------------------------------------------------------------------*/
                /*		アラーョ殑検出の場合、データ更新											*/
                /*----------------------------------------------------------------------------------*/
                if ( Alm.f.AlmFlag == FALSE )
                {
                    LpxMakeAlmLatchMonitorData( );
                }
                /*----------------------------------------------------------------------------------*/
                /*		前回アラームなし＆今回アラーム検崇殑、EEPROM書込み待ち行列への登録			*/
                /*----------------------------------------------------------------------------------*/
                else if ( CioxV.b.LastAlmStatus == FALSE )
                {
                    LpxMakeAlmMonitorData( );
                    KriAddEepromQueue( Param_ALMMON, (USHORT *)&CioxV.AlmLtMon, EEPQUEID_ALARMMON );
                    CioxV.AlmLatchSeqPtr = 1;
                }
                break;
            /*--------------------------------------------------------------------------------------*/
            case 1:
                /*----------------------------------------------------------------------------------*/
                /*		EEPROM書込み処理に移行したら、シ鐨劚ンスクリア＆レジスタへのモニタコピー	*/
                /*----------------------------------------------------------------------------------*/
                if ( KriChkEepromQueue( EEPQUEID_ALARMMON ) > 0 )
                {
                    CioxV.AlmLatchSeqPtr = 0;
                    MlibCopyWordMemory( (USHORT *)&CioxV.AlmLtMon, (USHORT *)&CoutV.AlmLtMon, sizeof( ALMLTMON ));
                }
                
                break;
            /*--------------------------------------------------------------------------------------*/
            default :
                break;
        }
    }
/*--------------------------------------------------------------------------------------------------*/
/*		アラーム状態保存																			*/
/*--------------------------------------------------------------------------------------------------*/
    
    CioxV.b.LastAlmStatus = (Alm.f.AlmFlag == TRUE)? TRUE : FALSE;

    return;
}
