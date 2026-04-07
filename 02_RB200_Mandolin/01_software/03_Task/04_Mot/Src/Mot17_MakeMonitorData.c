/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot17_MakeMonitorData.c
* Version            : V0.1
* Date               : 2024
* Description        : 监控数据制作
***********************************************************************************************/
#include "Main.h"
 
CIOXP	CioxP;		//ScanC变量用于I/O处理
CIOXV	CioxV;		//ScanC变量用于I/O处理
 
ULONG	CpiUmoncalMotorLoad( LONG IsqrSum );
 
  
  
/**********************************************************************************************/
/* Function_Name: LpxMakeMonitorData         */
/* Description  : 监控数据生成
                  调用：ScanC
                  输入：
                  输出：   */
/**********************************************************************************************/
void	LpxMakeMonitorData( void )
{
LONG	lwk;
SHORT   swk;
  
  
    //Un000,Un007
    CioxV.Pfbk64Sum += CinK.dMotPos;
    CioxV.Pcmd64Sum += CinK.dPcmdCnt;
    CioxV.MotSpd64Sum += CinK.MotSpd;
    //CioxV.FencSpd64Sum += CinK.FencSpd;
    if( ++CioxV.Pfbk64SumCnt >= SVCDEF_UNSPD_SCMEANNUM )	//64ms平均处理
    {
        CoutV.UnPfbk64ms = CioxV.Pfbk64Sum;			    //电机速度          [pulse/64ms]
        CoutV.UnPcmd64ms = CioxV.Pcmd64Sum;				//位置指令速度        [pulse/64ms]
        CioxV.Pfbk64Sum  = 0;
        CioxV.Pcmd64Sum  = 0;
        CioxV.Pfbk64SumCnt = 0;
        CoutV.UnMotSpd   = ((CioxV.MotSpd64Sum >> 4)+1)>>1;
        //CoutV.UnFencSpd   = ((CioxV.FencSpd64Sum >> 4)+1)>>1;
        CioxV.MotSpd64Sum = 0;
    }
    if( Kprm.f.FencUse )
    {
        if ( CioxV.FenseSumCnt  >= 50)
        {
            CoutV.UnFpos100ms = CioxV.FensePulSum;
            CioxV.FensePulSum = 0;
            CioxV.FensePulLst = CoutRrst.UnFenseCnt2;
            CioxV.FenseSumCnt = 0;
            CoutV.UnFencrpm100ms = CoutV.UnFpos100ms * 10 * 600 / FencV.FencPulseNo;
        }
        else
        {
            if ( CioxV.FenseSumCnt == 0)
            {
                CioxV.FensePulLst = CoutRrst.UnFenseCnt2;
                CioxV.FenseSumCnt ++;
            }
            else
            {
                CioxV.FensePul = CoutRrst.UnFenseCnt2  ;
                CioxV.FensePulSum += CioxV.FensePul - CioxV.FensePulLst;
                CioxV.FensePulLst = CoutRrst.UnFenseCnt2;
                CioxV.FenseSumCnt ++;
            }
        }
    }

    switch( BoutV.CtrlMode.b.cm )
    {
         case CTRLMODE_POS:             //位置控制模式
             CoutV.f.Sv.Vrefon  = FALSE;
             CoutV.f.Sv.Trefon  = FALSE;
             CoutV.f.Sv.Prefon  = (CinK.dPcmdCnt != 0)? TRUE : FALSE;
             CoutV.f.Sv.PerrClr = (BinV.f.PerClrSignal)? TRUE : FALSE;
             break;
         case CTRLMODE_SPD:             //速度控制模式
         case CTRLMODE_JOG:             //点动控制模式
             if( (CoutV.f.Sv.BaseEnable) && (MlibAbs32(BinV.SpdRef) > Gprm.TgonSpdLevel) )
             {
                CoutV.f.Sv.Vrefon = TRUE;
             }
             else
             {
                CoutV.f.Sv.Vrefon = FALSE;
             }
             CoutV.f.Sv.Prefon  = FALSE;
             CoutV.f.Sv.PerrClr = FALSE;
             break;
         case CTRLMODE_TRQ:              //转矩控制模式
             if( (CoutV.f.Sv.BaseEnable) && (MlibAbs32(AoutV.TrqRefi) > Iprm.TrefonLevel) )
             {
                CoutV.f.Sv.Trefon = TRUE;
             }
             else
             {
                CoutV.f.Sv.Trefon = FALSE;
             }
             CoutV.f.Sv.Vrefon  = FALSE;
             CoutV.f.Sv.Prefon  = FALSE;
             CoutV.f.Sv.PerrClr = FALSE;
             break;
         default:
             CoutV.f.Sv.Vrefon  = FALSE;
             CoutV.f.Sv.Trefon  = FALSE;
             CoutV.f.Sv.Prefon  = FALSE;
             CoutV.f.Sv.PerrClr = FALSE;
             break;
    }

    /* Un016~Un017 : 负载端速度   @20251216 yjp */
    CoutV.UnSpeedFbk = ((LONG)(CoutV.UnMotSpd * 100 / MIT.GR));  // 负载端速度反馈 @20251216 yjp
    CoutV.UnSpeedRef = ((LONG)(BoutV.UnSpdRef * 100 / MIT.GR));  // 负载端速度指令 @20251216 yjp

    /* Un142 : 瞬时负载率(电流有效值指令) */
    lwk = ((LONG)CinK.IdRefMon * CinK.IdRefMon) + ((LONG)CinK.IqRefMon * CinK.IqRefMon);
#if 0
    CoutV.UnCrntRef = MlibSqrtu32( lwk );
#else
    CoutV.UnCrntRef = __sqrt( (float)lwk );
#endif

    /* 0x6077 实际转矩值 */
//    swk   = KpiMonCurrentCal(CoutV.UnCrntRef);
//    u16TorqActVal = swk;
//    if( AinK.IqRef >= 0 )
//    {
//        u16TorqActVal = swk;
//    }
//    else
//    {
//        u16TorqActVal = -swk;
//    }
//     ODDatArr[ OD_6077 ].all = u16TorqActVal;
//    swk= KpiMonCurrentCal(AinK.IqFbMon) / 100;
//    u16TorqActVal = swk;
//    ODDatArr[ OD_6077 ].all = u16TorqActVal;

     /* Un018~Un019 : 负载端转矩  @20251216 yjp */

     CoutV.UnTorqueRef = (LONG)(Iprm.fkmontrq1 * (float)CinK.TrqRefMon * Prm.rattrq * 0.001 * MIT.GR * (float)Prm.Pn544);
     CoutV.UnTorqueFbk = (LONG)((float)KpiMonCurrentCal (AinK.IqFbMon) * Prm.rattrq * 0.00001 * MIT.GR * (float)Prm.Pn544);

    /* Un80D 最大累積負荷率 [%]   */
    CioxV.IsqrSum += CoutV.UnCrntRef;
    if( ++CioxV.IsqrSumCnt >= KPI_SCANC_MS( Prm.monitortime ) )
    {
        CoutV.UnIsqrSum  = CpiUmoncalMotorLoad( CioxV.IsqrSum ) ;
        if( CoutV.UnIsqrSum > CoutV.UnIsqrSumMax )
        {
            CoutV.UnIsqrSumMax = CoutV.UnIsqrSum;
        }
        CioxV.IsqrSum       = 0;
        CioxV.IsqrSumCnt    = 0;
    }


    CoutV.UnMotSpdx = CinK.MotSpd;
    CoutV.UnTrqRef  = CinK.TrqRefMon;
    CioxV.MtrgStatus = ( CioxV.MtrgStatus << 1 ) & 0x03;

    /* Un145 : 累计负载率(动作监视) [%]  */
    if( CinV.f.Sv.TMonTrg == 1 )
    {
        CioxV.MtrgStatus |= 0x01;
        CioxV.MtrgStatus &= 0x03;
    }
    if( CioxV.MtrgStatus == 0x01 )
    {
        CioxV.MtrgFlg = 1;
        CioxV.IsqrSum1 = 0;
        CioxV.IsqrSumCnt1 = 0;
    }
    if( CioxV.MtrgFlg == 1 )
    {
        CioxV.IsqrSum1 += CoutV.UnCrntRef;
        if( ++CioxV.IsqrSumCnt1 >= KPI_SCANC_MS( Prm.monitortime ) )
        {
            CoutV.UnIsqrSum1  = CpiUmoncalMotorLoad( CioxV.IsqrSum1 ) ;
            CioxV.IsqrSum1       = 0;
            CioxV.IsqrSumCnt1    = 0;
            CioxV.MtrgFlg        = 0;
        }
    }
    return;
}
 
  
  
  
  
  
/**********************************************************************************************/
/* Function_Name: IprmcalCurrentLoadGain         */
/* Description  : 负载率
                  调用：main函数调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void	IprmcalCurrentLoadGain( void )
{
LONG	kx,sx;
#if 0
    kx = MlibSqrtu32( 16384 * KPI_SCANC_MS( 10000 ) );
    kx = MlibScalKxgain( 1,  (128 * 128),    kx,    &sx,  0 );
    kx = MlibPcalKxgain( kx, Bprm.PerMaxTrq, 15000, &sx, 24 );
#else
    /*                            128 * PerMaxTrq               128 * 128 * PerMaxTrq               */
    /*      CioxP.Kcurload = -------------------------- = -----------------------------------       */
    /*                         15000 * √SCANC_MS(10000)    15000 * √(16384*SCANC_MS(10000))         */
    kx = Prm.monitortime;
    kx = MlibScalKxgain( 20,  1,    kx,    &sx,  0 );
    kx = MlibPcalKxgain( kx, Bprm.PerMaxTrq, 15000, &sx, 24 );
#endif
    CioxP.Kcurload = kx;
    return;
}
 
  
/**********************************************************************************************/
/* Function_Name: CpiUmoncalMotorLoad         */
/* Description  : 有效转矩（电流）
                  调用：本地
                  输入：
                  输出：   */
/**********************************************************************************************/
ULONG	CpiUmoncalMotorLoad( LONG IsqrSum )
{
LONG	x;
    x = IsqrSum;
    /* 有效转矩（电流）计算公式：CurLoad = Sqrt( Σ((Id^2 + Iq^2)>>14) ) * Kcurload */
    return( MlibMulgain( x, CioxP.Kcurload ) );
 }
