/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot10_ServoControl.c
* Version            : V0.1
* Date               : 2024
* Description        : 伺服控制主程序
***********************************************************************************************/

#include "Main.h"
 
void InitSpdCtrlModeVar( void );
 
  
  
 
void	LpxPosSpdFeedbackCal( void );			         
void	BpxSpeedFeedbackSel( void );
  
  
/**********************************************************************************************/
/* Function_Name: ApxYecServoControl                                                       */
/* Description  : 伺服控制处理 每隔 62.5 运行一次
                  SCANA调用                                  */
/**********************************************************************************************/


//#ifdef RunRAM
//#pragma CODE_SECTION(ApxYecServoControl, ".TI.ramfunc");
//#endif
void ApxYecServoControl( void )
{
LONG TorqCmd;
    /* 扩展控制输出变量 */
    AoutV.SpdFFCx = BoutV.SpdFFCx;              // 扩展控制：速度FF补偿(位置前馈)
    AoutV.SpdFBCx = BoutV.SpdFBCx;              // 扩展控制：速度FB补偿
    //增加60B2在位置模式下的转矩前馈功能 2025.08.30 @syhu
    AoutV.TrqFFCx = BoutV.TrqFFCx + BoutV.TrqFFCOffSet;  // 扩展控制：转矩FF补偿
    AoutV.TrqFBCx = BoutV.TrqFBCx;              // 扩展控制：转矩FB补偿
  
    /*  电机位置＆速度FB计算 */
    LpxPosSpdFeedbackCal( );
  
    /* 伺服扩展控制 */
	if( Iprm.f.TuningLess)
	{
#if( TUNINGLESS_CTRL != 0 )
	    //免调整控制 --> AoutV.SpdFbki, AoutV.TrqFBCx
 		ApxTuningLessCtrl( AoutV.SpdFbki, AoutV.TrqRefi,AinK.TrqRefoLimit );
#endif
	}
	else
	{
	    //扰动观测器
 	    ApxDisturbObserver( AoutV.SpdObsFbki, AinK.TrqRefoLimit );       
 	}
  
	/*  不同的控制模式进行相应的处理 */
	switch( BoutV.CtrlMode.b.cm )
	{
	    case CTRLMODE_POS_MIT:
	        AoutV.TrqRefo = APL_MITCtr_ScanA();
	        break;

	    /* 位置控制模式   */
 		case CTRLMODE_POS:
			LpxSvPositionManager( );        //SCANA指令位置增量更新

			// 伺服位置管理＆位置指令作成
			AoutV.SpdRefp = BasePositionControl(	             
								AoutV.dPosRefi,			         
								AoutV.dPosFbki,			         
								BoutV.f.PerClrCmd,		         
								0,		                         
								0  );	                         
              
			/* 位置环PI调节器输出值限幅 */
			AoutV.SpdRefi = SvonSpeedLimit( AoutV.SpdRefp );
			/* 速度环PI调节器*/
 			AoutV.TrqRefs = BaseSpeedControl(       // 速度制御演算
                                AoutV.SpdRefi,          // 速度指令
                                AoutV.SpdObsFbki,       // 速度ＦＢ
                                AoutV.SpdFFCx,          // 速度ＦＦ补偿值//    位置稳定控制
                                AoutV.SpdFBCx,          // 速度ＦＢ补偿值
                                AinK.dMotPos );         // 位置FB增量值（钳位）
 		    /* 速度环PI调节器输出值 */
 			AoutV.TrqRefi = AoutV.TrqRefs + AoutV.TLObs;
              
 			/* 速度环PI调节器输出值滤波 */
			AoutV.TrqRefo = BaseTorqueFilter( AoutV.TrqRefi, AoutV.TrqFBCx, AoutV.TrqFFCx);
 			break;
 	  	 
 		/* 速度控制模式   */
		case CTRLMODE_SPD:
		    /* 速度环PI调节器  */
 			AoutV.TrqRefs = BaseSpeedControl(       // 速度制御演算
                                BoutV.SpdRefi,          // 速度指令
                                AoutV.SpdObsFbki,       // 速度ＦＢ
                                BoutV.SpdComp,          // 速度ＦＦ补偿值//    位置稳定控制
                                AoutV.SpdFBCx,          // 速度ＦＢ补偿值
                                AinK.dMotPos );         // 位置FB增量值（钳位）

 			/* 速度环PI调节器输出值  */
 			AoutV.TrqRefi = AoutV.TrqRefs + AoutV.TLObs;

 			/* 速度环PI调节器输出值滤波 */
			AoutV.TrqRefo = BaseTorqueFilter( AoutV.TrqRefi, AoutV.TrqFBCx, AoutV.TrqFFCx );
			break;

		/* 转矩控制模式   */
 		case CTRLMODE_TRQ:
			LpxInitTrqCtrlModeVar( );		 // 初次进入转矩模式，电流控制参数初始化
			LpxTorqueControl( );			 // 转模式下转矩指令生成
			break;
		/* 点动控制模式   */
 		case CTRLMODE_JOG:
            AoutV.TrqRefs = BaseSpeedControl(
                                BoutV.SpdRefi,
                                AoutV.SpdObsFbki,
                                0,
                                AoutV.SpdFBCx,
                                AinK.dMotPos ); //速度控制模块
            AoutV.TrqRefi = AoutV.TrqRefs;
            AoutV.TrqRefo = BaseTorqueFilter( AoutV.TrqRefi, AoutV.TrqFBCx, 0 );
        break;
 	  	 
        /* 原点搜索模式   */
		case CTRLMODE_ZSRCH:
 			break;
 	  	 
 		/* 电机零点相位搜索模式   */
        case CTRLMODE_ZPHASE:
            /*  判断零相位辨识是否有开启 */
            if( StateM_Var.f.PhaseStudy )
            {
                  
				/* 零相位寻找过程中,需要对电流指令逐渐平滑处理 */
                ZeroPhaseDeal( );
                TorqCmd = 10 * ZeroPhaseV.PhaseCurOut;
            }
            else
            {
                TorqCmd = 0;
                ZeroPhaseV.FirstFlag = 0;
                ZeroPhaseV.Step = 0;
            }
            /*  将转矩指令0.01% 转换成 2^24处理  */
            TorqCmd = KpiTorqueLevelCal( TorqCmd, 0 );
              
            /* 电流限幅后赋值给参考指令源 */
            AoutV.TrqRefo = MlibLimitul( TorqCmd, 0x01000000, -0x01000000 );
            break;
         /* IF/VF控制模式 */
         case CTRLMODE_VF:
            SysBitDef1.f.VFEn = 1;
            /* 角度&电压生成 */
            SoftStartVfRef( );
            AoutV.TrqRefo = VfCtrl.IFCurOut;
        break;
          
 		default:
 			break;
 	}
	/*  摩擦补偿 */
    FrictionCompDeal( );    //输出AoutV.TrqComp
    /*  脉动补偿 */
    BoutV.TrqRefBeforeComp = AoutV.TrqRefo;	    // 补偿前扭矩        [2^24/MaxTrq]
    AoutV.TrqRefoComp = AoutV.TrqRefo + AoutV.TrqComp + ApxVelRippleComp( MencV.MotPhase);
    /*  电流指令输出 */
    KaiOutputTrqRef( AoutV.TrqRefoComp, 0, AoutV.DisTrqRef3 );	    // TrqRefo --> AinK.IqRef
  
    /*  平均转矩指令更新(For ScanB) */
    AoutV.TrqRefo_a = ( AoutV.TrqRefo + AoutV.TrqRefo_l ) >> 1;
    AoutV.TrqRefo_l = AoutV.TrqRefo;

 }
 
  
/**********************************************************************************************/
/* Function_Name: BpxYecServoControl                                                     */
/* Description  : 伺服控制处理主要部分
                  SCANB调用                                  */
/**********************************************************************************************/
void BpxYecServoControl( void )
{
    /* 扩展控制输出变量清除零 */
    BoutV.SpdFFCx = 0;                                      //  扩展控制：速度FF补偿
    BoutV.SpdFBCx = 0;                                      //  扩展控制：速度FB补偿
    BoutV.TrqFFCx = 0;                                      //  扩展控制：转矩FF补偿
    BoutV.TrqFBCx = 0;                                      //  扩展控制：转矩FB补偿

    /*  通用控制运算处理(速度反馈选择)    */
    BoutV.SpdFbki = BinK.MotSpd;
    BoutV.SpdObsFbki = AoutV.SpdObsFbki_a;
  
  
    /*  位置指令管理
        通过ScanA处理伺服基本控制。
        这里更新的位置指令通过ScanA插值后，成为伺服基本控制的输入。
        位置指令的更新必须在125us的前半部分62.5us以内进行 */
	BpxSvcPosCommandManager( );  	        // 伺服控制位置指令管理(dPosRefi,etc)

    PosRefRenewal( );			            //位置指令更新处理
  
    /*  伺服扩展控制  */
    BpxVibrationDetect( );                  // 振动监测
    BpxMFVibSup( );                         // A型抑振控制处理


  
    /*  基于控制模式的分支  */
 	switch( BoutV.CtrlMode.b.cm )
	{
 	    // 位置控制模式
 		case CTRLMODE_POS:										 
 			InitPosCtrlModeVar( );			  // 位置控制模式切换初次变量初始化
			if( BoutV.f.MFCModel == 0 )
			{													 
				dPosRefFeedForward( BoutV.dPosRefi );			 
			}

 			 
			/*  模拟量输入速度前馈和转矩前馈（暂无效） */
			
			if( ( TblExeV.TblCmd == TBLCMD_NOCMD ) && ( ( BoutV.f.MFCModel == 0 ) || ( Gprm.f.MFCFF == TRUE ) ) )
			{
				BoutV.SpdRfFilo = 0;
				BoutV.SpdFFCx += BoutV.SpdRfFilo;		// 速度ＦＦ指令加算
				BoutV.TrqFFCx += BinV.TrqFFC;			// 转矩ＦＦ指令加算
			}
 			Gprm.f.TuningLessVComp = TRUE;		//位置控制时,免调整中相位超前补偿始终有效
 			break;
 		/* 速度控制模式 */
		case CTRLMODE_SPD:										 
            InitSpdCtrlModeVar( );			        // 其它模式切换至速度模式变量初始化
 			if( TblExeV.TblCmd != TBLCMD_NOCMD )    //辅助功能运行模式
			{
				BinV.SpdRef  	= TblExeV.SpdRef;	//辅助功能运行速度指令
				BoutV.SpdRefi	= BinV.SpdRef;
				BoutV.SpdRfFilo = 0;
			}
 			else                                    //速度指令源选择
            {
 			    /* 速度指令源选择 */
                if( Kprm.f.EtherCATNet == 1 )
                {
                    BinV.SpdRef = EtherCatSpdSource( ); // EtherCAT速度指令源
                }
                else                                                 
                {
                  	BinV.SpdRef = KpiInputSpdRef( );    // 标准脉冲型和CANopen速度指令源
                }
                /*  低通滤波 */
                BoutV.SpdRfFilo = MlibLpfilter1( BinV.SpdRef, SpdCtrl.P.KVrfFil, BoutV.SpdRfFilo );
                /* 速度指令输出 */
                BoutV.SpdRefi = BoutV.SpdRfFilo;
                /*  减速停机 */
                if( CinV.f.Seq.ServoOffDecM == TRUE)
                {
                    BoutV.SpdRefi = BaseLinDecStopSpdRef(BoutV.SpdLdstpRefo);
                    BoutV.SpdLdstpRefo = BoutV.SpdRefi;
                }
			}
 			//转矩ＦＦ指令计算//无意义
			if( TblExeV.TblCmd == TBLCMD_NOCMD )				 
			{
				BoutV.TrqFFCx += BinV.TrqFFC;
			}
			// 免调整中相位超前补偿设定//无意义
			Gprm.f.TuningLessVComp = Iprm.f.TuningLessVComp;	 
 			 
			break;
		/* 转矩控制模式 (零速停止／零速钳位进行速度控制)     */
		case CTRLMODE_TRQ:				         
			BoutV.SpdRfFilo = MlibLpfilter1( BinV.SpdLmt, SpdCtrl.P.KVrfFil, BoutV.SpdRfFilo );
			BoutV.OverTrq   = OverTorqueCalculation( BoutV.SpdRfFilo, BinK.MotSpd );
			Gprm.f.TuningLess = FALSE;
			break;
		/* JOG运行模式 */
		case CTRLMODE_JOG:										 
 			BinV.SpdRef  		   = RoutV.JogSpeed;
			BoutV.SpdRefi		   = BinV.SpdRef;
 			Gprm.f.TuningLess	   = Iprm.f.TuningLess;  		// 恢复免调整功能开关
			Gprm.f.TuningLessVComp = FALSE;  					// JOG时免调整中相位前进补偿始终无效
			break;
		/* 原点搜索模式   */
		case CTRLMODE_ZSRCH:									 
 			 
			Gprm.f.TuningLess	   = Iprm.f.TuningLess;  		// 恢复免调整功能开关
			Gprm.f.TuningLessVComp = FALSE;  		            // 原点搜索模式时免调整中相位前进补偿始终无效
			break;
          
		default:
 			break;
	}
  
 	/*  当不为位置模式或零速停止进行位置控制变量初始化 */
	if( ( BoutV.CtrlMode.b.cm != CTRLMODE_POS ) || 
        ( BoutV.ZctrlMode.b.zm == CTRLMODE_ZSTOP ) ||
        ( BoutV.ZctrlMode.b.zm == CTRLMODE_DSTOP ))
	{
        InitBasePositionControl( );  		// 位置控制变量初期化
	}
	return;
 }    
 
  
/**********************************************************************************************/
/* Function_Name: LpxPosSpdFeedbackCal                                                      */
/* Description  : 电机位置＆速度处理
                  ApxYecServoControl调用                                  */
/**********************************************************************************************/
void	LpxPosSpdFeedbackCal( void )
{
LONG skx;
float fkx;
/*--------------------------------------------------------------------------------------------------*/
/*      位置ＦＢ更新(使用电机侧编码器或者全闭环光学尺进行反馈脉冲处理)                                */
/*--------------------------------------------------------------------------------------------------*/
/*  Edit By Zhuxc @ 2019.02.15  全闭环功能有效后,可以通过内部强制位置反馈信号源为光学尺或者通过外部 */
/*                              DI 端子来选择位置反馈信号源                                         */
/*--------------------------------------------------------------------------------------------------*/
    if( Kprm.f.FencUse && (Prm.fcplsel2 & 0x000F) == 0x0000)
    {
        if( Iprm.f.FencSource )
        {
            /*--------------------------------------------------------------------------------------*/
            /* 强制使用全闭环光学尺信号当做脉冲反馈参数位置环运算                                   */
            /*--------------------------------------------------------------------------------------*/
            AoutV.dPosFbki = (Prm.FenseSel & 0x0001)? AinK.dFencPos : AinK.dMotPos;
            Kprm.f.FencUseFlag = (Prm.FenseSel & 0x0001)? 1 : 0;
        }
        else
        {
            /*--------------------------------------------------------------------------------------*/
            /* 通过外部DI端子来切换位置反馈源的选择(L:电机编码器; H:全闭环光学尺)                   */
            /*--------------------------------------------------------------------------------------*/
            AoutV.dPosFbki = (CinV.f.Sv.FencS)? AinK.dFencPos : AinK.dMotPos;
            Kprm.f.FencUseFlag = (CinV.f.Sv.FencS)? 1 : 0;
        }
    }
    else
    {
        AoutV.dPosFbki = AinK.dMotPos;
        if( Kprm.f.FencUse == 0 )
            Kprm.f.FencUseFlag = 0;
    }
	/* 速度ＦＢ更新   */
	/*  相位补偿速度观测器前速度生成 */
    AoutV.SpdFbki = AinK.MotSpd;             
    /*  相位补偿速度观测器   */
    if( Iprm.f.EhVobs == TRUE)       // 速度观测器开启
    {
        AoutV.SpdObsFbki = ApxEhSpeedObserver( AoutV.SpdFbki, AoutV.TrqRefi );
    }
    else                            // 速度观测器关闭
    {
        AoutV.SpdObsFbki = AoutV.SpdFbki;    // FB速度
    }
      
    /*  平均速度更新(For ScanB)   */
    AoutV.MotSpd_a = ( AinK.MotSpd + AoutV.MotSpd_l ) >> 1;				    // 电机反馈速度平均值
    AoutV.MotSpd_l = AinK.MotSpd;

    AoutV.SpdObsFbki_a = ( AoutV.SpdObsFbki + AoutV.SpdObsFbki_l ) >> 1;    // 观测速度平均值
    AoutV.SpdObsFbki_l = AoutV.SpdObsFbki;

    /*  EtherCat 机型，OBJ606C计算 */
    if( Kprm.f.EtherCATNet == 1 )
    {
        if( ( Prm.EtherCATConfig & 0x0010 ) == 0x0010 )
        {
#if(FLOAT_USE == 1)
            s32VelActualVal = Iprm.fKmonspd * (float)AoutV.MotSpd_a;
#else
            s32VelActualVal = KpiMonSpeedCal( AoutV.MotSpd_a );                 
#endif
        }
        else
        {
#if(FLOAT_USE == 1)
            fkx = Iprm.fKmonspd1 * (float)AoutV.MotSpd_a;
            fkx = fkx * MencP.PulseNoDiv600;
            fkx = fkx * Iprm.Ethfgear.adivb;
            fkx = fkx * Iprm.Egear.adivb;
#else
            skx = KpiMonSpeedCal1( AoutV.MotSpd_a );                            
            DataTmp = (INT64)skx * MencP.PulseNo / 600;
            DataTmp = (INT64)DataTmp * PositionFactor.aEntries[1] / PositionFactor.aEntries[0];
            DataTmp = (INT64)DataTmp * Iprm.Egear.a / Iprm.Egear.b;
#endif
            s32VelActualVal = ( s32VelActualVal * 15 + (LONG)fkx ) >> 4;
        }
    }
    /* CanOpen 机型，OBJ606C计算 */
    else if( Kprm.f.CanOpenNet == 1)
    {
        skx = (AoutV.MotSpd_c + AoutV.MotSpd_a ) >> 1;
        AoutV.MotSpd_c = AoutV.MotSpd_a;
 #if(FLOAT_USE == 1)
            skx = Iprm.fKmonspd * (float)skx;            
#else
            skx = KpiMonSpeedCal( skx );                 
#endif
        if( ( Prm.Mode & 0xF000 ) == 0x1000 )
        {
            ODDatArr[ OD_606C ].sall = skx;
        }
        else
        {
            fkx = (float)skx * MencP.PulseNoDiv60;
            fkx = fkx * Iprm.Egear.adivb;
            skx = fkx * Iprm.CANgear.adivb;
            ODDatArr[ OD_606C ].sall = ( ODDatArr[ OD_606C ].sall * 15 + (LONG)skx ) >> 4;
        }
    }
    else
    {
        ;
    }
    return;
}
 
  
  
/**********************************************************************************************/
/* Function_Name: InitSpdCtrlModeVar                                                      */
/* Description  : 速度控制模式切换初次变量初始化
                  BpxYecServoControl调用                                  */
/**********************************************************************************************/
void InitSpdCtrlModeVar( void )
{
    switch( BPI_GET_BASE_CTRLMODELST() )	// 上个周期基本控制模式
	{
        /* 位置控制模式 */
 		case CTRLMODE_POS:										 
 			BoutV.SpdRfFilo = BoutV.SpdFbki;		// 速度指令滤波输出 = 速度ＦＢ
 			BoutV.SpdRefo	= BoutV.SpdFbki;		// 速度指令软起动输出 = 速度ＦＢ
            RpiANotchDisableReqSet( ); 	            // 自动陷波器无效
 			break;
 		/* 转矩控制模式 */
 		case CTRLMODE_TRQ:										 
 			BoutV.SpdRfFilo = BoutV.SpdFbki;		// 速度指令滤波输出 = 速度ＦＢ
 			BoutV.SpdRefo	= BoutV.SpdFbki;		// 速度指令软起动输出 = 速度ＦＢ

 			if( Gprm.f.Dobs )                       // 扰动观测器有效
			{													 
 				TrqFil.V.TrqFilClrCmd = TRUE;		// 转矩指令滤波积分初始化
			}													 
 			if( RoutV.f.TunLessCtrlOffSts == FALSE )    // 免调整强制无效
			{
				Gprm.f.TuningLess = Iprm.f.TuningLess;  // 免调整强制无效
			}													 
 																 
 			SpdCtrl.V.SpdRefFilClrCmd = TRUE;	        // 速度指令相位超前补偿滤波器初始化
 																 
			SpdCtrl.V.SpdFFFilClrCmd  = TRUE;			// 速度FF相位超前补偿滤波器初始化
 																 
			RpiANotchDisableReqSet( );                  // 自动陷波分析强制无效
			break;
	}
	return;
}
