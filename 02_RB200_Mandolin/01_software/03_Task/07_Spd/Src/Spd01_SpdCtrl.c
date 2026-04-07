/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Drv_ASR01_Ctrl.c
* Version            : V0.1
* Date               : 2024
* Description        : 速度环控制处理
***********************************************************************************************/

#include "Main.h"
 
#ifdef	TST_ENCLESS
void	KpiMencLessSpdCtrl( SPDCTRL *pSpdCtrl );
#else
#define KpiMencLessSpdCtrl( x ) { ;}
#endif
void ModeSwitch( LONG  Spdref, LONG  SpdFFC );
 
 
  
/**********************************************************************************************/
/* Function_Name: InitBaseSpeedControl                                               */
/* Description  : 速度控制变量初始化
                  SCNA调用                */
/**********************************************************************************************/
void	InitBaseSpeedControl( void )
{
    MlibResetLONGMemory( &SpdCtrl.V, sizeof( SpdCtrl.V ) / 2 );
	return;
}
 
  
  
  
  
LONG BaseLinDecStopSpdRef( LONG SpdRefo )
{
	if( SpdRefo > 0 )
	{
		SpdRefo = SpdRefo - SpdCtrl.P.SpdOffDec;
		if( SpdRefo < 0 )
		{
			SpdRefo = 0;
		}
	}
	else if( SpdRefo < 0 )
	{
		SpdRefo = SpdRefo + SpdCtrl.P.SpdOffDec;
		if( SpdRefo > 0 )
		{
			SpdRefo = 0;
		}
	}
	else
	{
		SpdRefo = 0;
	}
 	return( SpdRefo );
}
 
  
/**********************************************************************************************/
/* Function_Name: PcalBaseSoftOffDec                                              */
/* Description  : 伺服Off时减速时间预处理                                                */
/**********************************************************************************************/
void PcalBaseSoftOffDec( void )
{
	LONG kx,
		 sx;
	if( Prm.offdec == 0 )
	{
		kx = 0x01000000;
	}
	else
	{
		kx = MlibScalKxgain( 10000UL, 0x01000000, ( Bprm.PerOvrSpd + 10000UL ), &sx, 0 );
		kx = MlibPcalKxgain( kx, KPI_SBCYCLEUS, ( 1000UL * Prm.offdec ), &sx, -24 );
	}
    SpdCtrl.P.SpdOffDec = kx;
	return;
}
  
  
/**********************************************************************************************/
/* Function_Name: BaseSpeedControl                                                          */
/* Description  : 速度环PI运算
                  SCANA调用
                  输入：SpdRefx——速度给定, SpdFbk——速度反馈, SpdFBC——速度反馈补偿, SpdFFC——速度前馈补偿
                  输出：SpdCtrl.V.TrqRef——转矩指令                                  */
/**********************************************************************************************/

//#ifdef RunRAM
//#pragma CODE_SECTION(BaseSpeedControl, ".TI.ramfunc");
//#endif

LONG BaseSpeedControl( LONG  SpdRef, LONG  SpdFbk,       
					   LONG  SpdFFC, LONG  SpdFBC,       
					   LONG  dPosFbk )                   
{
	LONG SpdRefx;
	LONG SpdErrP;
	LONG SpdErrI;
	LONG TrqRef0;
    LONG kx;
  
    /* 滑行时再ON处理 */
 	if( CoutV.f.Sv.BBSvcRefClrReq )  	    //   基极封锁时位置偏差/控制指令清除要求
	{													 
 	    // 完善在自由滑行时,电机没有完全停止下来时,驱动器此时再ON,速度指令瞬间拉低为0,造成较大的冲击
 		if( ( BPI_GET_BASE_CTRLMODE( ) == CTRLMODE_SPD ) || ( BPI_GET_BASE_CTRLMODE( ) == CTRLMODE_JOG ) )
		{
			BoutV.SpdRefo = BinK.MotSpd;
			SoftSpd_Update( BinK.MotSpd );
		}
		else
		{
			BoutV.SpdRefo = 0;
			SoftSpd_Update( 0 );
		}
	}
	else    /* 软启动平滑处理 */
    {
	    if( BoutV.ZctrlMode.b.zm == CTRLMODE_ZCLMP )
	    {
	        BoutV.SpdRefo = 0;
	        SoftSpd_Update( 0 );
	    }
	    else if( ( BPI_GET_BASE_CTRLMODE( ) == CTRLMODE_SPD ) || ( BPI_GET_BASE_CTRLMODE( ) == CTRLMODE_JOG ) )
		{
              
 		    if( CinV.f.Seq.ServoOffDecM == TRUE)
		    {
		        BoutV.SpdRefo = SpdRef;     // 位置控制时,不需要软启动
		    }
		    else
		    {
		        BoutV.SpdRefo = BaseSoftStartSpdRef( SpdRef, BoutV.SpdRefo );   //加减速处理
		    }
		}
		else
		{
              
 			BoutV.SpdRefo = SpdRef;
			SoftSpd_Update( SpdRef );
		}
    }   
 	/* 速度指令 = 速度指令参考值 + 速度前馈值( 位置前馈 ) */
 	BoutV.SpdRefSum = MlibSatAdd32( BoutV.SpdRefo, SpdFFC );
  
 	/* 初始化处理 */
	if( BinV.f.BaseEnable == FALSE )    //伺服驱动器没有使能
	{
		InitBaseSpeedControl( );		//速度控制变量初始化
        ZxCtrl.V.PosError = 0;                           
        SpdCtrl.V.SFSpdOld = SpdRef;                     
        SpdCtrl.V.FfFilo = 0;
        SpdCtrl.V.FfFilo = 0;
        BoutV.SpdReffinal = 0;
          
        SoftStart_Init( );
 
        return ( 0 );
	}
	// 在转矩控制模式,且非零速控制模式时,退出
 	else
    {
		if(( BPI_GET_BASE_CTRLMODE( ) == CTRLMODE_TRQ ) && ( BoutV.ZctrlMode.b.zm == CTRLMODE_ZNONE ))
		{
 			InitBaseSpeedControl( );	//速度控制变量初始化
			return ( 0 );
		}
    }
  
	/* 零速停机, 零速箝位, 减速停机处理 */
	if( BoutV.ZctrlMode.b.zm == CTRLMODE_ZSTOP )	//零速停止
	{
		SpdRefx  	  = 0;			//速度指令为0
		SpdFFC		  = 0;
		AoutV.TrqFFCx = 0;
	}
	/* 减速停机 */
    else if( BoutV.ZctrlMode.b.zm == CTRLMODE_DSTOP )
    {
		SpdRefx = BoutV.SpdLdstpRefo;
    }
	/* 零速箝位 */
 	else if( BoutV.ZctrlMode.b.zm == CTRLMODE_ZCLMP )        
    {
        SpdRefx  	  = ZeroPositionControl( dPosFbk );  	 //零钳位控制运算
        SpdFFC		  = 0;
        AoutV.TrqFFCx = 0;
    }
	/* 内部减速处理 */
    else
    {
        SpdRefx = BoutV.SpdRefo;
    }
    if( BoutV.f.SvonSpdLmtFlag )
    {
        SpdFFC = 0;                      
    }					
 
    /*  免调整生效时，速度指令相位超前补偿运算*/
 	if( Iprm.f.TuningLess )
	{															 
		SpdRefx = LpxSpdRefPhaseComp( SpdRefx );   // 速度指令超前处理
		SpdFFC	= LpxSpdFFPhaseComp( SpdFFC );     // 速度前馈超前处理
	}

 	//速度指令监控用
    if( CinV.f.Seq.ServoOn == 1 )
    {
        BoutV.SpdReffinal = SpdRefx;
    }
    else
    {
        BoutV.SpdReffinal = 0;
    }
    /* 模式切换(P控制/PI控制)计算 */
 	ModeSwitch( SpdRefx, SpdFFC );								 
  
 	/* 速度控制计算 */

 	// 速度给定前馈量叠加
	if( ( BoutV.ZctrlMode.b.zm != CTRLMODE_ZSTOP ) && ( BoutV.ZctrlMode.b.zm != CTRLMODE_ZCLMP ) )
	{
		BoutV.SpdRefSum = MlibSatAdd32( SpdRefx, SpdFFC );
	}
      
	// 判断速度偏差是否与转矩指令方向相同,不同则积分器开启
	if( ( ( SpdRefx - SpdFbk >= 0 ) && ( SpdCtrl.V.TrqRef < 0 ) )
	 || ( ( SpdRefx - SpdFbk <  0 ) && ( SpdCtrl.V.TrqRef > 0 ) ) )
	{
		BoutV.f.neri_calc_on = TRUE;		//速度偏差和扭矩指令的方向不同
	}
	else
	{
		BoutV.f.neri_calc_on = FALSE;		//速度偏差和扭矩指令的符号相同
	}
      
	/* P控制 */
    // BinV.f.Ctrl.EnbPCtrl ——> 端子切换至P控制
    // BoutV.f.ModeSWFlag   ——>0:PI控制;1:P控制
    // Iprm.f.IPSpdContro   ——>0:PI控制;1:I-P控制
 	if( BinV.f.Ctrl.EnbPCtrl || ( BoutV.f.ModeSWFlag && ( !Iprm.f.IPSpdControl ) ) )								
	{
		BoutV.f.PConActFlag = TRUE;        //P控制有效标志位
		SpdCtrl.V.SpdFbFilo = MlibLpfilter1( SpdFbk + SpdFBC, SpdCtrl.P.KVfbFil, SpdCtrl.V.SpdFbFilo );
		SpdErrP  		    = SpdRefx - SpdCtrl.V.SpdFbFilo + SpdFFC;   //速度误差
		SpdCtrl.V.PacOut    = MlibMulgain( SpdErrP, GselGains[ 0 ].Kv );    //速度环比例增益
 		if( !Iprm.f.SpdIctrlKeep )			//速度控制积分不保持的场合
		{												 
			SpdCtrl.V.IacOut = MlibLpfilter1( 0, SpdCtrl.P.KVintegFil, SpdCtrl.V.IacOut );
			SpdCtrl.V.Ivar64[ 1 ] = SpdCtrl.V.IacOut << 1;
			SpdCtrl.V.Ivar64[ 0 ] = 0;          //带时间常数积分清除 Integration clear
		}
	}
 	/* PI或IP控制 */
	else
 	{
		BoutV.f.PConActFlag = FALSE;      // PI控制有效
		SpdCtrl.V.SpdFbFilo	= MlibLpfilter1( SpdFbk + SpdFBC, SpdCtrl.P.KVfbFil, SpdCtrl.V.SpdFbFilo );
          
		/* 比例运算 */
        // Iprm.f.IPSpdContro = 0,P-I控制: SpdCtrl.P.PI = 1;
        // Iprm.f.IPSpdContro = 1,I-P控制: SpdCtrl.P.PI = (100 - PnE44.l)/100
		SpdErrP = MlibMulgainNolim( SpdRefx, SpdCtrl.P.PI ) - SpdCtrl.V.SpdFbFilo + SpdFFC;
		SpdCtrl.V.PacOut = MlibMulgain( SpdErrP, GselGains[ 0 ].Kv );      //速度环比例增益

		/* 积分运算 */
		SpdErrI  		 = SpdRefx - SpdCtrl.V.SpdFbFilo + SpdFFC;           
		if( ( !BoutV.f.Ctrl.TrqClamp ) || ( BoutV.f.neri_calc_on == TRUE ) )
		{
			SpdCtrl.V.IacOut = MlibIntegral( SpdErrI, GselGains[ 0 ].Kvi, SpdCtrl.V.Ivar64 );
		}
	}
  
 	/* 速度控制输出(比例+积分) */
	TrqRef0  		 = SpdCtrl.V.PacOut + SpdCtrl.V.IacOut;
	SpdCtrl.V.TrqRef = MlibMulgain29( TrqRef0, GselGains[ 0 ].Kv2 );

	/* 速度前馈处理    注:只针对速度和位置模式有效 */
    if( ( BPI_GET_BASE_CTRLMODE( ) == CTRLMODE_SPD ) || ( BPI_GET_BASE_CTRLMODE( ) == CTRLMODE_POS ))
    {
        if( Iprm.f.TuningLess == FALSE)        //免调整开启后无效
        {
            kx = SpdRef - SpdCtrl.V.SFSpdOld;
            kx = MlibMulgain( kx, GselGains[ 0 ].SFCoeff);
              
            /* 一阶低通滤波 */
            SpdCtrl.V.FfFilo  = MlibLpfilter1( kx, SpdCtrl.P.KdPffFil, SpdCtrl.V.FfFilo );
            SpdCtrl.V.TrqRef += SpdCtrl.V.FfFilo;
            /*  速度前馈监控用 */
 #if(FLOAT_USE == 1)
            SpdCtrl.V.TrqFedFor = (LONG)(0.0008940696716f * SpdCtrl.V.FfFilo);
#else
            SpdCtrl.V.TrqFedFor = MlibMulhigh32( SpdCtrl.V.FfFilo,  3840000 );
#endif
        }
        else
        {
            SpdCtrl.V.FfFilo = 0;
        }
    }
    else
    {
        SpdCtrl.V.FfFilo = 0;
    }
    SpdCtrl.V.SFSpdOld = SpdRef;        //更新,便于下一次使用
	return ( SpdCtrl.V.TrqRef );
}
 
  
/**********************************************************************************************/
/* Function_Name: ModeSwitch                                               */
/* Description  : 模式切换(P控制/PI控制)计算
                  SCANA调用                                                */
/**********************************************************************************************/
#define     MSWTorque         0x00                      // 以内部转矩指令为条件。设定值:Pn10C
#define     MSWSpdRef         0x01                      // 以速度指令为条件。设定值:Pn10D
#define     MSWAccMot         0x02                      // 以加速度指令为条件。设定值:Pn10E
#define     MSWPosErr         0x03                      // 以位置偏差脉冲为条件。设定值:Pn10F
#define     MSWNotUse         0x04                      // 无模式开关功能

void ModeSwitch( LONG  Spdref, LONG  SpdFFC )			 
{
	switch( Gprm.MSW )  //Pn130.X : 速度环P/PI控制开关选择
	{   
 		case MSWTorque:  		// 以内部转矩指令为条件
			BoutV.f.ModeSWFlag = ( MlibABS(AoutV.TrqRefo) >= Gprm.MSWTrqLevel ) ? TRUE : FALSE;
			break;
 		case MSWSpdRef:  	    // 以速度指令为条件
			BoutV.f.ModeSWFlag
			= ( MlibABS( Spdref + SpdFFC ) >= Gprm.MSWSpdLevel )? TRUE:FALSE;
			break;
 		case MSWAccMot:  	    // 以加速度指令为条件
			BoutV.f.ModeSWFlag
			= ( MlibABS( CoutV.ModeSwAcc ) >= Gprm.MSWAccLevel )? TRUE:FALSE;
			break;
 		case MSWPosErr:  	    // 以位置偏差脉冲为条件
			BoutV.f.ModeSWFlag = ( MlibABS( PosMngV.PosErr ) >= Gprm.MSWErrLevel )? TRUE:FALSE;
			break;
 		case MSWNotUse:  						 
		default:                // 无模式开关功能
			BoutV.f.ModeSWFlag = FALSE;
			break;
	}
}
 
 
