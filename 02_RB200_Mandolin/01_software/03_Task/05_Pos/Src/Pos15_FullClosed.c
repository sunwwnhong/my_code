/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Pos15_FullClosed.c
* Version            : V0.1
* Date               : 2023
* Description        : 全闭环位置控制

    全闭环补偿功能/滤波控制(Fenc)适用于全闭环控制，可消除由电机与负载之间柔性振荡或打滑导致的全闭环编码器与
电机编码器之间的混合误差。

***********************************************************************************************/


#include "Main.h"
#include "Pos15_FullClosed.h"
#include "App16_SPI.h"

FENCP FencP;            //全闭环控制参数
FENCV FencV;            //全闭环控制变量
MAFIL FenseMaFil;       //全闭环混合误差滤波参数
LONG FensePmafbuf[ 256 ];   //全闭环滑动平均滤波缓存



void MixErrorClear( void );
void FullClosedMoveAvergeFilter( USHORT PrmTime );

/**********************************************************************************************/
/* Function_Name: IprmcalFullClosedEnc                                                             */
/* Description  : 全闭环电子齿轮比计算
        输出：   Iprm.sfgear  全闭环编码器电子齿轮比系数
        相关功能码：  Pn023~ Pn026 : 全闭环编码器电子齿轮比分子/分母                          */
/**********************************************************************************************/
void IprmcalFullClosedEnc( void )
{
ULONG	Rata;
ULONG	Ratb;
    Rata = ULONGOF( Prm.fcplsml, Prm.fcplsmh );                         
    Ratb = ULONGOF( Prm.fcplsnl, Prm.fcplsnh );                         
    MlibPcalKegear( Rata, Ratb, &Iprm.sfgear );
    if( Iprm.sfgear.a == 0 )
    {
        KpiSetParamError( &pndef_fcplsml );
    }
    else if( Iprm.sfgear.b == 0 )
    {
        KpiSetParamError( &pndef_fcplsnl );
    }
    return;
}

/**********************************************************************************************/
/* Function_Name: KpxInitFullClosedEncoder                                                  */
/* Description  : 全闭环控制参数初始化                                                            */
/*********************************************************************************************/

void	KpxInitFullClosedEncoder( void )
{
    if( Kprm.f.FencUse == FALSE )
    {
        return;				                                
    }
    MlibResetLONGMemory( &FencP, sizeof(FencP)/2 );
    MlibResetLONGMemory( &FencV, sizeof(FencV)/2 );

    FencV.FencPulseBit = 19;
    FencV.FencPulseNo = ( 1UL << FencV.FencPulseBit );         // 负载端位数强制为19位
    FencP.MotPulseNo = FencV.FencPulseNo;

    MlibResetLONGMemory( &FenseMaFil, sizeof(FenseMaFil)/2 );
    KpxInitFullClosedMaFilter();


    return;
}



void    KpxInitFullClosedMaFilter( void )
{
    FullClosedMoveAvergeFilter( (USHORT) Prm.FensFiltTime );     //TODO:全闭环混合滤波系数初始化
    FenseMaFil.P.ImafSft[0] = FenseMaFil.P.ImafSft[1];      //TODO
    FenseMaFil.P.PmafNum[0] = FenseMaFil.P.PmafNum[1];      //TODO
}
/**********************************************************************************************/
/* Function_Name: LpxReadFencPosition                                                        */
/* Description  :全闭环编码器 : 位置信息读取
           输入：FencDir:编码器方向
                 SpdCoef：速度单位转换系数
           输出：dFencPos：全闭环位置增量
                 FencV.FencSpd  全闭环速度                                                    */
/**********************************************************************************************/
LONG	LpxReadFencPosition( void )
{
LONG	dFencPos;
LONG    FencPosTmp;

    if(FencV.FirstReadFlag == 0)
    {
        FencV.FencReadCnt ++;
        FencV.RxPos[1]   = FencV.RxPos[0];
        FencV.RxPos[0]   = CTek5900_Pos;

        if (FencV.FencReadCnt >= Prm.EncDelay)
        {
            FencV.FirstReadFlag = 1;
            if( MotorPhaseV.ZeroPhaseDir )
            {
                FencPosTmp = FencV.FencPulseNo - FencV.RxPos[0] - 1;
            }
            else
            {
                FencPosTmp = FencV.RxPos[0];
            }
            if ( Iprm.f.RvsDir == 0)
            {
                FencV.FencAbsPos  = FencPosTmp;
                if( FencV.FencAbsPos >= (FencV.FencPulseNo >> 1) )
                {
                    FencV.FencMPos    = -1;
                }
                else
                {
                    FencV.FencMPos    = 0;
                }
            }
            else
            {
                FencV.FencAbsPos  = FencV.FencPulseNo - FencPosTmp - 1;
                if( FencV.FencAbsPos >= (FencV.FencPulseNo >> 1) )
                {
                    FencV.FencMPos    = -1;
                }
                else
                {
                    FencV.FencMPos    = 0;
                }
            }
        }
        return 0;
    }
    else
    {
        FencV.RxPos[1]   = FencV.RxPos[0];
        FencV.RxPos[0]   = CTek5900_Pos;
    }

    dFencPos = (SHORT)(FencV.RxPos[0] - FencV.RxPos[1]);        
    if(Iprm.f.FencDir)
        dFencPos = -dFencPos;
#if 0
    FencSpd = MlibMulgain( dFencPos, Bprm.KConvLoadSpd );
    FencV.FencSpd = LpxTimeBasesFencSpdCalc( dFencPos, FencSpd, FencV.f.SpdCmpEnable );
#else
    //FencV.FencSpd = MlibMulgain( dFencPos, Bprm.KConvLoadSpd );
    //FencV.FencSpd = (float)dFencPos * Bprm.fKConvLoadSpd ;
#endif
    if( MotorPhaseV.ZeroPhaseDir )
    {
        FencPosTmp = FencV.FencPulseNo - FencV.RxPos[0] - 1;
    }
    else
    {
        FencPosTmp = FencV.RxPos[0];
    }
    if ( Iprm.f.RvsDir == 0)
    {
        FencV.FencAbsPos  = FencPosTmp;
        if( FencV.FencAbsPos >= (FencV.FencPulseNo >> 1) )
        {
            FencV.FencMPos    = -1;
        }
        else
        {
            FencV.FencMPos    = 0;
        }
    }
    else
    {
        FencV.FencAbsPos  = FencV.FencPulseNo - FencPosTmp - 1;
        if( FencV.FencAbsPos >= (FencV.FencPulseNo >> 1) )
        {
            FencV.FencMPos    = -1;
        }
        else
        {
            FencV.FencMPos    = 0;
        }
    }
    FencV.FencPos  = FencV.FencMPos * FencV.FencPulseNo  + FencV.FencAbsPos;
    return( dFencPos );
}

/**********************************************************************************************/
/* Function_Name: LpxCheckSemiFullPerrOverFlow                                                */
/* Description  : 全闭环混合位置偏差过大
      相关功能码：Pn029：全闭环混合偏差过大阈值设定
           输入： AinK.MixFbkErr全闭环误差
                  Gprm.fpgclcLevel：Pn029
           输出： Er.D03故障                                                                */
/**********************************************************************************************/
void LpxCheckSemiFullPerrOverFlow( void )
{
	if( Kprm.f.FencUse )
	{
#if 1
        if( !BinV.f.BaseEnable || !Kprm.f.FencUse )
#else
        if( !BinV.f.BaseEnable )
#endif
        {
            AinK.MixFbkErr  = 0;                                    
            AinK.MixUserErr = 0;
            AinK.dMixPulAErr = 0;
        }
        MixErrorClear( );       //混合误差清除条件判定

        //全闭环混合误差超出故障范围，持续20ms，报故障
        if( Gprm.fpgoverLevel != 0 )
        {
            if(( MlibAbs32( AinK.MixFbkErr )) > Gprm.fpgoverLevel )
            {
                if( ChkAlmV.FSOFAlmCnt >= KPI_SCANC_MS( 20 ) )  
                {
                    KPI_ALARMSET  ( ALM_FSOF );  		        
                }
                else
                {
                    ChkAlmV.FSOFAlmCnt++;                       
                }
            }
            else
            {
                ChkAlmV.FSOFAlmCnt = 0;                         
            }
        }
	}
    else
    {
        AinK.MixFbkErr = 0;
    }
}

/**********************************************************************************************/
/* Function_Name: MixErrorClear                                                */
/* Description  : 混合误差清除条件判定（Pn021.Y）                                                              */
/**********************************************************************************************/
void MixErrorClear( void )
{
    if( !Kprm.f.FencUse )
    {
        AinK.MixFbkErr = 0;
        return;
    }
//    switch( Prm.fcplsel2 & 0x00F0 )
//    {
//        case 0x0000:            /*混合误差不清除*/
//            break;
//        case 0x0010:            /*位置误差超过Pn262清除*/
//            if( PosMngV.PosErrA.per32a <= Gprm.CoinLevel )
//            {
//                AinK.MixFbkErr = 0;
//            }
//            break;
//        case 0x0020:            /*混合位置误差超过Pn029清除*/
//            if( ( MlibAbs32( AinK.MixFbkErr ) ) > Gprm.fpgclcLevel )
//            {
//                AinK.MixFbkErr = 0;
//            }
//            break;
//        default:
//            break;
//    }
}

/**********************************************************************************************/
/* Function_Name: FullClosedMoveAvergeFilter                                                */
/* Description  : 全闭环位置平滑滤波参数计算                                                         */
/**********************************************************************************************/
void FullClosedMoveAvergeFilter( USHORT PrmTime )
{
LONG	i,x;
LONG	MaTimeUs = 100UL * PrmTime;
    //实际调用滑动平均为SCANA, 256调整为128
    if( MaTimeUs <= ((LONG)128 * Iprm.SvCycleUs ) )
    {
        FenseMaFil.P.ImafSft[1] = 0;
        FenseMaFil.P.PmafNum[1] = MaTimeUs / Iprm.SvCycleUs / 2UL;
        if( FenseMaFil.P.PmafNum[1] < 1 )
        {
            FenseMaFil.P.PmafNum[1] = 1;
        }
    }
    else
    {
        x = (LONG)128 * Iprm.SvCycleUs;
        for( i=1; i < 5; i++ )
        {
            if( (x << i) >= MaTimeUs ){ break;}
        }
        FenseMaFil.P.ImafSft[1] = (UCHAR)i;
        FenseMaFil.P.PmafNum[1] = (2UL * MaTimeUs) / (Iprm.SvCycleUs << i );
        if( FenseMaFil.P.PmafNum[1] > 256 )
        {
            FenseMaFil.P.PmafNum[1] = 256;
        }
    }
    return;
}

/**********************************************************************************************/
/* Function_Name: FenseMixMaFilter                                                */
/* Description  : 全闭环位置误差平滑滤波（暂未用）                                                             */
/**********************************************************************************************/
LONG	FenseMixMaFilter( LONG pcmdin )
{
LONG	pcmdfilo;
    FenseMaFil.V.pcmdinx += pcmdin;
    if( ++FenseMaFil.V.index >= (1 << FenseMaFil.P.ImafSft[0]) )
    {
        FenseMaFil.V.pcmdiny = MlibPcmdMafil(
                            FenseMaFil.V.pcmdinx,
                            FenseMaFil.P.PmafNum[0],
                            &FenseMaFil.V.Pmafvar,
                            &FensePmafbuf[0]			);
        FenseMaFil.V.index   = 0;
        FenseMaFil.V.pcmdinx = 0;
    }
    pcmdfilo = MlibPcmdImafil(
                FenseMaFil.V.pcmdiny,
                FenseMaFil.P.ImafSft[0],
                FenseMaFil.V.index,
                &FenseMaFil.V.Pimfvar	);
    return( pcmdfilo );
}

//TODO
/**********************************************************************************************/
/* Function_Name: FensecmdMoveAvergeFilter                                                    */
/* Description  : 全闭环滑动平均滤波处理
             输入：
             输出：                                         */
/**********************************************************************************************/
LONG FensecmdMoveAvergeFilter( LONG pcmdin )
{

    //短时间滑动平均滤波处理，通常平均移动滤波器
    if( FenseMaFil.P.ImafSft[0] == 0 )
    {
        FenseMaFil.V.Filo = MlibPcmdMafil(
                            pcmdin,
                            FenseMaFil.P.PmafNum[0],
                            &FenseMaFil.V.Pmafvar,
                            &FensePmafbuf[0]            );
    }
    else    //长时间滤波器:平均移动滤波器+插值移动平均滤波器
    {
        FenseMaFil.V.Filo = FenseMixMaFilter( pcmdin );
    }
    //滑动平均位置滤波完成判定
    if( (pcmdin | FenseMaFil.V.pcmdinx | FenseMaFil.V.Pmafvar.zcntx | FenseMaFil.V.Pimfvar.zcntx) == 0 )
    {
        FenseMaFil.P.PmafNum[0] = FenseMaFil.P.PmafNum[1];
        FenseMaFil.P.ImafSft[0] = FenseMaFil.P.ImafSft[1];
    }
//    else
//    {
//        BoutV.f.Sv.Den = FALSE;
//        FilMng.FilChgDisable = TRUE;
//    }
    return( FenseMaFil.V.Filo );
}


/**********************************************************************************************/
/* Function_Name: Delta_FencPosFil_Cal                                                           */
/* Description  : 全闭环负载编码器反馈滤波处理                                              */
/**********************************************************************************************/
void Delta_FencPosFil_Cal(void)
{
    static  USHORT Enable_Lst = 0;

    //使能开启时开始执行平滑滤波
    if( BinV.f.BaseEnable )
    {
        /* 方案1：负载增量反馈 = 混合误差滤波 + 电机位置反馈 */
        if ((Prm.FenseSel & 0x0000) == 0x0000)
        {
            AinK.dMixPulAErr =  AinK.dMotPos - AinK.dFencPosOri;
            AinK.dMixPulAErrFil = FensecmdMoveAvergeFilter ( AinK.dMixPulAErr );
            AinK.dFencPos = AinK.dMotPos - AinK.dMixPulAErrFil;
        }
        /* 方案2：负载增量反馈滤波 */
        else
        {
            AinK.dFencPos = FensecmdMoveAvergeFilter ( AinK.dFencPosOri );
        }

    }
    else
    {
        /* 关闭使能瞬间，滑动平均滤波相关变量清除 */
        if( (BinV.f.BaseEnable == 0) && Enable_Lst)
        {
            /* 方案1：负载增量反馈 = 混合误差滤波 + 电机位置反馈 */
            if ((Prm.FenseSel & 0x0000) == 0x0000)
            {
                AinK.dMixPulAErr = 0;
                MlibResetLONGMemory( &FenseMaFil.V, sizeof(FenseMaFil.V)/2 );
            }
            /* 方案2：负载增量反馈滤波 */
            else
                MlibResetLONGMemory( &FenseMaFil.V, sizeof(FenseMaFil.V)/2 );

            AinK.dFencPos = AinK.dFencPosOri;
        }
        else
        {
            AinK.dMixPulAErr = 0;
            AinK.dFencPos = AinK.dFencPosOri;
        }
    }
    Enable_Lst = BinV.f.BaseEnable;
}
