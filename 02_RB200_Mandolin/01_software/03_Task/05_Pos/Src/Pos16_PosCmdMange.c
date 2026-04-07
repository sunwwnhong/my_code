/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Pos16_PosCmdMange.c
* Version            : V0.1
* Date               : 2023
* Description        : 位置指令管理
***********************************************************************************************/
  

#include "Main.h"
void LpxInputPositionReference( void );
LONG LpxMultiplyInputPulse( void );
  
/**********************************************************************************************/
/* Function_Name: BpxSvcPosCommandManager                                                         */
/* Description  : 位置指令管理
          调用： SCANB                                               */
/**********************************************************************************************/
void	BpxSvcPosCommandManager( void )
{
    /* 位置反馈获取 */
    if( Kprm.f.FencUse == FALSE )
    {
        BoutV.dPosFbki = BinK.dMotPos;
    }
    else
    {
        BoutV.dPosFbki = BinK.dFencPos;
    }
    /* 位置指令信号处理完成复位 */
    BoutV.f.Sv.Den = TRUE;
    /* 位置指令信号获取（包含Table运行处理） */
    LpxInputPositionReference( );
    /*电子齿轮处理 dPosRef 位置指令（Unit）-> dPcmdEgear位置指令（pul）*/
    if( PosMngV.EgearDisable )
    {
        PosMngV.dPcmdEgear = PosMngV.dPcmda;
    }
    else
    {
    #if(FLOAT_USE == 1)
        PosMngV.dPcmdEgear = FlibPcmdEgear( PosMngV.dPcmda, &Iprm.Egear, &PosMngV.dPcmdEgrem );
    #else
        PosMngV.dPcmdEgear = MlibPcmdEgear( PosMngV.dPcmda, &Iprm.Egear, &PosMngV.dPcmdEgrem );
    #endif
    }
    /* 指令滤波处理 */
    BoutV.dPcmdFilo     = BpxPcmdFilter( PosMngV.dPcmdEgear );

    #if( VIBSUPPRESS_FIL != 0 )
    BoutV.dPcmdFilo = BpxPcmdAbvControl( BoutV.dPcmdFilo );
    #endif


    BoutV.AmondPosCmd = PosMngV.dPcmda;				               


    #if ( SVFSEL_BLSH_COMMON_PROC )
    if( Iprm.BacklashEn )
    {
    BpxCompensateBacklash( &BoutV.dPcmdFilo, &PosMngV.dPcmda );
    }
    #endif

    #if( VIBSUPPRESS_FIL2 != 0 )
    BoutV.dPcmdFilo = BpxPcmdAvffFilter( BoutV.dPcmdFilo );
    #endif
    #if( INPUTSHAPING_FIL != 0 )
    BoutV.dPcmdFilo = BpxPcmdInptShpFilter( BoutV.dPcmdFilo );
    #endif

    /* MFC 前馈补偿 */
    #if( MODELFOLLOW_CTRL != 0 )
    BoutV.dPosRefi = BpxMfcModelControl( BoutV.dPcmdFilo );          
    #else
    BoutV.dPosRefi = BoutV.dPcmdFilo;
    #endif

    /* 位置控制状态处理 */
    if( Kprm.f.EtherCATNet == 1 )                                    
    {
        BpxControlPositionSignal_EtherCat( );
    }
    else if( Kprm.f.CanOpenNet == 1 )
    {
        BpxControlPositionSignal_CanOpen( );                         
    }
    else
    {
        BpxControlPositionSignal( );                                 
    }

    return;
}
  
  
/**********************************************************************************************/
/* Function_Name: LpxInputPositionReference                                                         */
/* Description  : 位置指令获取
          调用： SCANB                                               */
/**********************************************************************************************/
void	LpxInputPositionReference( void )
{
LONG	lwk_dPcmdHwCntr;
  
    // Table 运转模式位置增量获取
    if( TblExeV.TblCmd != TBLCMD_NOCMD )
    {
        BoutK.f.PerClrEdge = FALSE;
        if( CoutV.f.Sv.BaseEnable )
        {
            PosMngV.dPcmda = TblExeV.dPosRef;
 #if	( CCSW_SFTID == SFTID_EXIST )
            PosMngV.dPcmda = (BoutV.ZctrlMode.b.zm == CTRLMODE_DSTOP ) ? 0 : PosMngV.dPcmda;
#endif
             BoutK.PcmdRingCntr += PosMngV.dPcmda;
            BoutV.f.PerClrCmd = FALSE;
        }
        else
        {
#if ( SVFSEL_BLSH_COMMON_PROC )
            BpxInvaildBlshCompensate( );
#endif
            BpxInitSvcPositionManager( );
            BoutV.f.PerClrCmd = TRUE;
        }
    }
    // PJOG 运转模式位置增量获取
    else if( BoutV.CtrlMode.us[0] == CTRLMODE_PJOG )
    {
        BoutK.f.PerClrEdge = FALSE;						     
        if( BoutV.CtrlModeLst.us[0] != CTRLMODE_PJOG )
        {                                                    
            PrgJogReset();								     
        }
         if( CoutV.f.Sv.BaseEnable )
        {
              
             PosMngV.dPcmda = MlibPcmdMaker( PJogV.Var.AbsPosCmd,
                                           0,
                                           PJogPcmk.P.maxspd,
                                           &PJogPcmk,
                                           PCMKMODE_POS );
             if( PJogPcmk.V.calendf == FALSE )
            {
                BoutV.f.Sv.Den = FALSE;
            }
             BoutK.PcmdRingCntr += PosMngV.dPcmda;		     
            BoutV.f.PerClrCmd = FALSE;					     
        }
        else
        {
            BpxInitSvcPositionManager( );				     
            BoutV.f.PerClrCmd = TRUE;					     
        }
    }
    //常规位置模式下位置增量获取
    else
    {
        //输入倍率处理
        lwk_dPcmdHwCntr     = LpxMultiplyInputPulse( );
         /*------------------------------------------------------------------------------------------*/
         /* 遇到限位后,脉冲接收禁止                                                                  */
         /*------------------------------------------------------------------------------------------*/
        if( Iprm.OtPErrorclr != 0 )
        {
            if( CinV.f.Sv.Pot == TRUE && lwk_dPcmdHwCntr >= 0)
            {
                lwk_dPcmdHwCntr = 0;
            }
            if( CinV.f.Sv.Not == TRUE && lwk_dPcmdHwCntr < 0)
            {
                lwk_dPcmdHwCntr = 0;
            }
        }
        /*------------------------------------------------------------------------------------------*/
        /* 判断位置偏差清除信号监测                                                                 */
        /*------------------------------------------------------------------------------------------*/
          
        BoutV.f.PerClrCmd = (  BinV.f.PerClrCmd ) ? TRUE : FALSE;
          
        /*------------------------------------------------------------------------------------------*/
        /* 位置偏差清除处理                                                                         */
        /*------------------------------------------------------------------------------------------*/
        if( BoutV.f.PerClrCmd || CoutV.CtrlMcmd.us[0] == CTRLMODE_SPD || CoutV.CtrlMcmd.us[0] == CTRLMODE_TRQ \
            || CoutV.CtrlMcmd.us[0] == CTRLMODE_JOG    )
        {
            BpxEdgeClrSvcPositionManager( );			     
            BoutV.AmondPosCmd =  lwk_dPcmdHwCntr;		     
            BoutK.f.PerClrEdge = FALSE;
        }
        /*------------------------------------------------------------------------------------------*/
        /*      脉冲禁止                                                                            */
        /*------------------------------------------------------------------------------------------*/
 		 
        PosMngV.dPcmda = ( BinV.f.Sv.Inhibit || ( BoutV.ZctrlMode.b.zm == CTRLMODE_DSTOP ) ) ?
						   0 : lwk_dPcmdHwCntr;
     }
    return;
}
 
/****************************************************************************************************/
/*                                                                                                  */
/*      位置偏差计算Ａ(指令単位)                                                                   */
/*                                                                                                  */
/****************************************************************************************************/

void	MlibPerrcala( LONG pcmda, LONG pfbka, EGEAR *egear, PERRA *perra )
{
LONG	perrx;				 /* 位置偏差計算作業用                                                   */
LONG	carry;				 /* Carry of (per64[0]+perrx)                                           */
  
/*--------------------------------------------------------------------------------------------------*/
/*      位置反馈計算(指令単位)                                                                        */
/*--------------------------------------------------------------------------------------------------*/
#if (FLOAT_USE == 1)                 
        LONG    wk1;
        LONG    wk2;
        perra->pfbkb = (LONG)((float)pfbka * egear->adivb);
         wk1 = (pfbka * egear->a);                        
        wk2 = (perra->pfbkb * egear->b);                 
        perra->pfbkrem = perra->pfbkrem + ((ULONG)wk1 - (ULONG)wk2);
#else
        LONG    wk1[2];              
        LONG    wk2[2];              
		MUL3232( egear->g1, pfbka, wk1 );
		MUL3232( egear->g2, pfbka, wk2 );
		perra->pfbkb = wk1[0] + (wk2[1]<<1) + ((ULONG)wk2[0]>>31);
		MUL3232( egear->a, pfbka, wk1 );
		MUL3232( egear->b, perra->pfbkb, wk2 );
		perra->pfbkrem = perra->pfbkrem + ((ULONG)wk1[0] - (ULONG)wk2[0]);
#endif
		if( perra->pfbkrem <  0                 ){ --(perra->pfbkb); perra->pfbkrem += egear->b;}
		if( perra->pfbkrem >= egear->b          ){ ++(perra->pfbkb); perra->pfbkrem -= egear->b;}
		if( perra->pfbkrem >= ((egear->b+1)>>1) ){ ++(perra->pfbkb); perra->pfbkrem -= egear->b;}
/*--------------------------------------------------------------------------------------------------*/
/*      位置偏差計算(指令単位)                                                                        */
/*--------------------------------------------------------------------------------------------------*/
		perrx = pcmda - perra->pfbkb;
		carry = (((ULONG)(perra->per64[0]+perrx)) < ((ULONG)(perra->per64[0])));
		perra->per64[0] = perra->per64[0] + (perrx);
		perra->per64[1] = perra->per64[1] + (perrx>>31) + carry;
		perrx = (perra->per64[1]<<2) + (((ULONG)perra->per64[0])>>30);
		if( perrx > 0       ) perra->per32s =  0x3FFFFFFF;
		else if( perrx < -1 ) perra->per32s = -0x40000000;
		else                  perra->per32s =  perra->per64[0];
		perra->per32a = (perra->per32s>=0)? perra->per32s : -perra->per32s;
/*--------------------------------------------------------------------------------------------------*/
/*      位置偏差切り上げ計算(指令単位)                                                                */
/*--------------------------------------------------------------------------------------------------*/
		perra->per32sx = perra->per32s;
		if( (perra->pfbkrem < 0)&&( perra->per32s >= 0) ) perra->per32sx += 1;
		if( (perra->pfbkrem > 0)&&( perra->per32s <= 0) ) perra->per32sx -= 1;
		perra->per32ax = (perra->per32sx>=0)? perra->per32sx : -perra->per32sx;
/*--------------------------------------------------------------------------------------------------*/
/*      位置偏差监视值计算(指令単位,切り上げ／ゼロ)                                                 */
/*--------------------------------------------------------------------------------------------------*/
		perra->per32mx = (perra->per32s==0)? 0 : perra->per32sx;
 		return;
 }
 
  
  
/**********************************************************************************************/
/* Function_Name: LpxSvPositionManager                                                         */
/* Description  : SCANA位置指令管理
          调用： SCANA                                               */
/**********************************************************************************************/
void	LpxSvPositionManager( void )
{
/*--------------------------------------------------------------------------------------------------*/
/*  位置指令更新(125us更新一次指令,62.5us对位置指令的处理)                                          */
/*  即:位置指令每隔125us采集一次,将此采集到的位置指令进行细分到2个62.5us周期内进行处理              */
/*--------------------------------------------------------------------------------------------------*/

    if( AoutV.RefRenewalCnt != BoutV.RefRenewalCnt )     //位置指令刷新
    {
        AoutV.dPosRefi = BoutV.CompdPosRefi >> 1;		     
        AoutV.dPcmda   = BoutV.CompdPcmda   >> 1;
        if( AoutV.RefRenewalChkCnt == 0 )
        {
            AoutV.dPosRefi += AoutV.NextdPosRefi;		     
            AoutV.dPcmda   += AoutV.NextdPcmda;
        }
        AoutV.NextdPosRefi = BoutV.CompdPosRefi - (BoutV.CompdPosRefi >> 1);
        AoutV.NextdPcmda   = BoutV.CompdPcmda   - (BoutV.CompdPcmda   >> 1);
        AoutV.RefRenewalChkCnt = 0;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 第二次(第二个62.5us)进入判断标志                                                             */
    /*----------------------------------------------------------------------------------------------*/
    else
    {
        if( AoutV.RefRenewalChkCnt == 0 )				     
        {
            AoutV.dPosRefi = AoutV.NextdPosRefi;		     
            AoutV.dPcmda   = AoutV.NextdPcmda;
        }
        else											     
        {
            AoutV.dPosRefi = 0;                              
            AoutV.dPcmda   = 0;
        }
        AoutV.RefRenewalChkCnt++;                            
    }
    AoutV.RefRenewalCnt = BoutV.RefRenewalCnt;
  
    /* 位置误差计算 */
    //功能安全判定位置误差过大导致的减速停机时，不进行位置误差计算
    if (BoutV.ZctrlMode.b.zm == CTRLMODE_DSTOP)
    {
        return;                                                  
    }
    //误差未清除状态下，执行位置误差（脉冲单位与用户单位）计算
    if( !BoutV.f.PerClrCmd )
    {
        //用户单位
        if( PosMngV.EgearDisable )
        {
            MlibPerrcala( AoutV.dPcmda, AoutV.dPosFbki, &Iprm.Egear0, &PosMngV.PosErrA );
        }
        //脉冲单位
        else
        {
            MlibPerrcala( AoutV.dPcmda, AoutV.dPosFbki, &Iprm.Egear, &PosMngV.PosErrA );
        }
    }
      
    // CANopen 和 EtherCAT 位置误差计算 OBJ60F4
    if( PositionFactor.aEntries[0] != 0 )
    {
#if (FLOAT_USE == 1)
        s32FollowErrActVal = (float)PosMngV.PosErrA.per32s * Iprm.Ethfgear.adivb;
#else
        s32FollowErrActVal =(INT64)PosMngV.PosErrA.per32s * PositionFactor.aEntries[1] / PositionFactor.aEntries[0];
#endif
    }
    else
    {
        s32FollowErrActVal = PosMngV.PosErrA.per32s;                 
    }
    ODDatArr[ OD_60F4 ].all = (ULONG)PosMngV.PosErrA.per32s;
    return;
}
  
  
  
  
/**********************************************************************************************/
/* Function_Name: PosRefRenewal                                                           */
/* Description  : SCANB指令位置增量累加更新
            输入：PosEgearRef
                  PosRef     当前周期SCANB的位置增量
            输出：BoutV.CompdPosRefi  SCANB的位置增量累加(pul)
                  BoutV.CompdPcmda    SCANB的位置增量累加(Unit)                                */
/**********************************************************************************************/
void PosRefRenewal( void )
{
	if( BoutV.CtrlMode.b.cm == CTRLMODE_POS )
	{
	    //在SCANA中连续检测到多个SCANB,对SCANB中的位置量进行累加处理
		if( AoutV.RefRenewalCnt != BoutV.RefRenewalCnt )	 
		{
			BoutV.CompdPosRefi += BoutV.dPosRefi;
			BoutV.CompdPcmda   += PosMngV.dPcmda;
		}
		else												 
		{
			BoutV.CompdPosRefi = BoutV.dPosRefi;
			BoutV.CompdPcmda   = PosMngV.dPcmda;
		}
	}
 	else													 
	{
		BoutV.CompdPosRefi = 0;
		BoutV.CompdPcmda   = 0;
	}
 	BoutV.RefRenewalCnt++;									 
	return;
}
 
  
/**********************************************************************************************/
/* Function_Name: KpiPositionLevelCal                                                        */
/* Description  : 位置标幺处理
            速度环P/PI切换条件(位置偏差)
            [指令单位]Position [Command Unit] --> Position [Pulse]                           */
/**********************************************************************************************/
LONG KpiPositionLevelCal( LONG	Position )
{
	LONG x;
 	x = MlibMulgain30( Position, Iprm.Kposlvl );
	return ( x );
}
 
  
/**********************************************************************************************/
/* Function_Name: SvonSpeedLimit                                                       */
/* Description  : 伺服使能位置限定状态判定
              相关功能码：
                    Pn270  伺服ON时速度限制值rpm
               输出：伺服位置限制gPosCtrSts.bit.SvonSpdLmt                                    */
/**********************************************************************************************/
LONG SvonSpeedLimit( LONG  SpdRefi )
{
	LONG AbsSpdRefi;
	LONG SpdRefx = SpdRefi;

	//OT停机方式为OTSTOPMODE_ZSTOPZC最大转矩零速停机并锁轴，当OT释放执行位置限定
    if( Iprm.OtStopMode == OTSTOPMODE_ZSTOPZC )
    {
         if( BinV.fl.BaseEnable == TRUE )
        {
            BoutV.f.OTStatus = BoutV.f.OTStatus << 1;
            BoutV.f.OTStatus &= 0x03;
            if( CoutV.f.Sv.Ot == 1 )
            {
                BoutV.f.OTStatus |= 1;
            }
            if( BoutV.f.OTStatus == 2 ) 
            {
                BoutV.f.SvonSpdLmtFlag = TRUE;
            }
        }
        else
        {
            BoutV.f.OTStatus = 0;
        }
        /*伺服上电使能或OT释放时，开始判定是否进行速度限制*/
        if( ( BinV.f.BaseEnable && ( BinV.fl.BaseEnable == FALSE ) ) || BoutV.f.SvonSpdLmtFlag )
        {
            AbsSpdRefi = MlibABS( SpdRefi );
             if( AbsSpdRefi > Gprm.SvonSpdLmtLevel )  		     
            {													 
                BoutV.f.SvonSpdLmtFlag = TRUE;					 
                SpdRefx = ( SpdRefi >= 0 ) ? Gprm.SvonSpdLmtLevel:-Gprm.SvonSpdLmtLevel;
            }
            else
            {
                BoutV.f.SvonSpdLmtFlag = FALSE;  			     
            }
        }
        else
        {
            BoutV.f.SvonSpdLmtFlag = FALSE;  			         
        }   
    }
    else
    {
        /*伺服上电使能或OT释放时，开始判定是否进行速度限制*/
        if( ( BinV.f.BaseEnable && ( BinV.fl.BaseEnable == FALSE ) ) || BoutV.f.SvonSpdLmtFlag )
        {
            AbsSpdRefi = MlibABS( SpdRefi );
            if( AbsSpdRefi > Gprm.SvonSpdLmtLevel )
            {													 
                BoutV.f.SvonSpdLmtFlag = TRUE;					 
                SpdRefx = ( SpdRefi >= 0 ) ? Gprm.SvonSpdLmtLevel:-Gprm.SvonSpdLmtLevel;
            }
            else
            {
                BoutV.f.SvonSpdLmtFlag = FALSE;  			     
            }
        }
        else
        {
            BoutV.f.SvonSpdLmtFlag = FALSE;  			         
        }
    }
    /*A.9A2 : 伺服ON时速度限制 报警判定*/
    if( BoutV.f.SvonSpdLmtFlag )
    {
        KPI_WARNINGSET( WRN_SERVOONE );                          
    }
    else
    {
        KPI_WARNINGCLR( WRN_SERVOONE );                          
    }
 	return ( SpdRefx ); 
}
  
  
/**********************************************************************************************/
/* Function_Name: LpxMultiplyInputPulse                                                              */
/* Description  :位置脉冲倍频与脉冲禁止处理，只针对常规位置给定源（非PJOG和TABLE运行模式）
           输入：
           输出：PosMngV.dPcmda 位置指令增量（Unit）                            */
/**********************************************************************************************/
LONG	LpxMultiplyInputPulse( void )
{
LONG	lwk_dPcmdHwCntr;									 
 		 
    /* 外部脉冲输入倍率：有效场合( 强制有效 ）*/
    if( Iprm.PGAINSet == 0x01 )
    {
        lwk_dPcmdHwCntr     = BinK.dPcmdHwCntr      * Prm.MulFrq;
        BoutK.PcmdRingCntr += BinK.dPcmdInputHwCntr * Prm.MulFrq;
    }
    /*  外部脉冲输入倍率：有效场合( 外部端子切换 ) */
    else if( Iprm.PGAINSet == 0x02 )
    {
        if( BinV.f.Sv.Psel == TRUE )
        {
            lwk_dPcmdHwCntr     = BinK.dPcmdHwCntr      * Prm.MulFrq;
            BoutK.PcmdRingCntr += BinK.dPcmdInputHwCntr * Prm.MulFrq;
        }
        else
        {
            lwk_dPcmdHwCntr     = BinK.dPcmdHwCntr;
            BoutK.PcmdRingCntr += BinK.dPcmdInputHwCntr;
        }
    }
    /*  外部脉冲输入倍率：无效场合*/
    else
    {
        lwk_dPcmdHwCntr     = (LONG)BinK.dPcmdHwCntr;
        BoutK.PcmdRingCntr += (LONG)BinK.dPcmdInputHwCntr;
    }
    return(lwk_dPcmdHwCntr);
}
 
  
/**********************************************************************************************/
/* Function_Name: BpxInitSvcPositionManager                                                           */
/* Description  : 位置参数参数相关初始化                                                      */
/**********************************************************************************************/
void	BpxInitSvcPositionManager( void )
{
    BoutV.AmondPosCmd  = 0;
    MlibResetLONGMemory( &PosMngV, (sizeof(PosMngV)) /2 );
    BoutV.dPosRefi = 0;
    BoutV.CompdPosRefi = 0;
    BoutV.CompdPcmda = 0;
    if( BoutV.CtrlMode.b.cm == CTRLMODE_POS )
    {
        BoutV.f.Ctrl.Coin = TRUE;
        BoutV.f.Sv.Near = TRUE;
    }
    else
    {
        BoutV.f.Ctrl.Coin = FALSE;
        BoutV.f.Sv.Near = FALSE;
    }

    BpxInitPcmdFilter( );
#if( MODELFOLLOW_CTRL != 0 )
    BpxInitMfcModelControl( );
#endif
    return;
}
 
  
/**********************************************************************************************/
/* Function_Name: BpiEnableEgear                                                          */
/* Description  : 打开电子齿轮（TABLE运行模式用）                                             */
/**********************************************************************************************/
void	BpiEnableEgear( void )
{
    PosMngV.EgearDisable = FALSE;
    return;
}
  
  
/**********************************************************************************************/
/* Function_Name: BpiDisableEgear                                                         */
/* Description  : 关闭电子齿轮（TABLE运行模式用）                                             */
/**********************************************************************************************/
void	BpiDisableEgear( void )
{
    PosMngV.EgearDisable = TRUE;
    return;
}
 
 
