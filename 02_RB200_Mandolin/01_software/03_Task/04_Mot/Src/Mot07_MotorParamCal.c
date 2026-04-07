/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot07_MotorParamCal.c
* Version            : V0.1
* Date               : 2024
* Description        : 电机相关变量处理
***********************************************************************************************/

  
  
#include "Main.h"
  
  
BPRMDAT	Bprm;
  
  
/**********************************************************************************************/
/* Function_Name: BprmCommonMotorParamCal*/
/* Description  : 电机基础参数计算
                  main函数调用*/
/**********************************************************************************************/
void	BprmCommonMotorParamCal( void )
{
ULONG	Imax;
  
    /*  指数的计算 : 10^exp  */
    Bprm.ExpTrq  = KpxBprmExpCal( Prm.exp_trat_jmot & 0x00FF );         //  额定转矩指数
    Bprm.ExpJmot = KpxBprmExpCal( (Prm.exp_trat_jmot >> 8) );           //  惯量指数
    Bprm.ExpMotW = KpxBprmExpCal( Prm.exp_motw_spd & 0x00FF   );        //  功率指数
    Bprm.ExpSpd  = KpxBprmExpCal( Prm.exp_motw_spd >> 8  );             //  额定输出指数
#if (FLOAT_USE == 1)
    Bprm.fExpTrq  = FlibExpCal( Prm.exp_trat_jmot & 0x00FF );
    Bprm.fExpJmot = FlibExpCal( Prm.exp_trat_jmot >> 8 );
    Bprm.fExpMotW = FlibExpCal( Prm.exp_motw_spd & 0x00FF);
    Bprm.fExpSpd  = FlibExpCal( Prm.exp_motw_spd >> 8  );
#endif

    /*  最大扭矩[%]的计算 : Min{驱动器最大电流, 电机最大电流}   */
    if( Prm.imax <= Prm.imaxs )
    {
        Imax = Prm.imax;                // 电机的最大瞬时电流 < 驱动器的最大瞬时电流
        Bprm.PerMaxIee = Prm.imax;      // 则以电机的最大电流为基准
    }
    else
    {
        Imax = Prm.imaxs;               // 电机的最大瞬时电流 > 驱动器的最大瞬时电流
        Bprm.PerMaxIee = Prm.imaxs;     // 则以驱动器的最大电流为基准
    }
    
    /* 电机额定电流峰值[0.1A]  */
    /* Bprm.PerMaxTrq是转化系数，不是单纯的标幺基准 */
    Bprm.PerMaxTrq = (((Imax * 200)/Prm.irat) + 1) >> 1;
    Bprm.fPerMaxTrq = (float)Imax * 100.0f / (float)Prm.irat;

    /*  OS（超速）阀值计算[0.01%]2^24]的计算  */
    Bprm.MaxVel = (Prm.vrat_max.b.h ) + Prm.MaxspdTun;

/*---------------------------------------------------------------------------------------------*/
/*        1.过速点的值比最大转速大于一定的幅值,过速点的速度标幺为2^24                          */
/*        2.根据过速点的值可以反向推导出最大速度值.                                            */
/*        3.根据最大转速和额定转速的值,可以推导出额定转速值.                                   */
/*        执行上述做法的好处是,速度值可以有效的覆盖造2^24范围内,有效提高精度.                  */
/*---------------------------------------------------------------------------------------------*/

    Bprm.PerOvrSpd = (Prm.ratmt2_os.b.h) * (Prm.oslv_pol.b.l & 0x00FF);             //  过速点的幅值,0.01%
    Bprm.NorOvrSpd = 0x01000000;
    Bprm.NorMaxSpd = MlibScalKxgain( Bprm.NorOvrSpd, 10000, (Bprm.PerOvrSpd+10000), NULL, -24 );
    Bprm.NorRatSpd = MlibScalKxgain( Bprm.NorMaxSpd, (Prm.vrat_max.b.l & 0x00FF), Bprm.MaxVel, NULL, -24 );
    Bprm.NorRatSpd1 = MlibScalKxgain( Bprm.NorRatSpd, 15000, Bprm.MaxVel, NULL, -24 );

    /*  最大电流计算 : Imax [0.1A]    */
    Bprm.MaxCur = MlibScalKxgain( Imax,  1,  10, NULL, -1 );
#if (FLOAT_USE == 1 )
    Bprm.fMaxCur = (float)Imax / 10.0f;
#endif
    /*  电机容量计算 : motw [W]   */
    Bprm.MotW = MlibScalKskxkx( Bprm.ExpMotW, Prm.motw, 1, NULL, -1 );

    /*  电机定子电阻计算 : motr [0.001ohm]  */
    Bprm.MotR = MlibScalKxgain( Prm.motr,  1, 1000, NULL, -1 );
#if ( FLOAT_USE == 1 )
    Bprm.fMotR = (float)Prm.motr / 1000.0f;
#endif
    /*  电感计算 : motl [0.01mH]        for SPM Motor   */
    Bprm.MotLd  = MlibScalKxgain( Prm.motl,  1, 100000, NULL, -1 );
    Bprm.MotLq  = MlibScalKxgain( Prm.motl,  1, 100000, NULL, -1 );
    Bprm.MotLdb = MlibScalKxgain( Prm.motl,  1, 100000, NULL, -1 );
#if ( FLOAT_USE == 1 )
    Bprm.fMotLd = (float)Prm.motl / 100000.0f;
    Bprm.fMotLq = (float)Prm.motl / 100000.0f;
#endif
    /*  驱动器/电机容量比和最大电流比计算   */
    Bprm.AmpMotWatRatio  = MlibScalKxkxks( ((ULONG)Prm.ampw <<16 ), 1, Bprm.MotW, NULL, -24 );
    Bprm.AmpMotImaxRatio = ((ULONG)Prm.imaxs<<16) / Prm.imax;
    return;
}
 
  
/**********************************************************************************************/
/* Function_Name: BprmRotaryMotorParamCal*/
/* Description  : 旋转式电动机基本参数计算*/

/**********************************************************************************************/
void BprmRotaryMotorParamCal( void )
{
LONG kx,
	 sx;
#if (FLOAT_USE == 1)
    float   fw;
#endif
    /*  电机脉冲数的计算[pulse / rev]   */
    Bprm.MotPulse = MencP.PulseNo;
#if(FLOAT_USE == 1)
    Bprm.fMotPulse = (float)MencP.PulseNo;
#endif
  
    /*  电机脉冲转换系数的计算[rad / pulse]        */
	kx			  = MlibScalKxgain( C2PAIE7, 1, Bprm.MotPulse, &sx, 0 );
	Bprm.Kmotpls  = MlibPcalKxgain( kx, 1, C10POW7, &sx, -1 );
 #if(FLOAT_USE == 1)
	fw = (float)C2PAIE7 / Bprm.fMotPulse;
	Bprm.fKmotpls = fw / (float)C10POW7;
#endif
/*--------------------------------------------------------------------------------------------------*/
/*      モータパルス変換係数[鐨?pulse]の計算                                                      */
/*     Calculation of the motor pulse conversion coefficient [rad / pulse]                          */
/*--------------------------------------------------------------------------------------------------*/
//  if( Kprm.f.FencUse )
    {
        kx = MlibScalKxgain( C2PAIE7, 1, FencP.MotPulseNo, &sx, 0 );
        Bprm.KmotplsFC = MlibPcalKxgain( kx, 1, C10POW7, &sx, -1 );
    }
#if(FLOAT_USE == 1)
   fw = (float)C2PAIE7 / (float)FencP.MotPulseNo;
   Bprm.fKmotplsFC = fw / (float)C10POW7;
#endif


	if( Kprm.f.FencUse )
    {
        Bprm.FbPulse = FencP.MotPulseNo;                        /*     Full-Closed Control          */
#if(FLOAT_USE == 1)
        Bprm.fFbPulse = (float)FencP.MotPulseNo;
#endif
    }
    else
    {
        Bprm.FbPulse = Bprm.MotPulse;
#if(FLOAT_USE == 1)
        Bprm.fFbPulse = Bprm.fMotPulse;
#endif                                                          /*     Semi-Closed Control          */
    }


  
    /*  XFB脉冲数[pulse/rev]、[pulse/鐨则ch]的计算[pulse / spitch]   */
    Bprm.XfbPulse1 = Bprm.FbPulse;							     
    Bprm.XfbPulse2 = Bprm.FbPulse;							     
    /*  FB脉冲变换系数的计算[rad / pulse]    */
 	kx				  = MlibScalKxgain( C2PAIE7, 1, Bprm.FbPulse, &sx, 0 );
	Bprm.Kfbpls  	  = MlibPcalKxgain( kx, 1, C10POW7, &sx, -1 );
#if(FLOAT_USE == 1)
    fw = (float)C2PAIE7 / Bprm.fFbPulse;
    Bprm.fKfbpls = fw / (float)C10POW7;
#endif

/*  电角度转换系数 : MotorPosition[rad] --> ElectricAngle[rad] */
/*------------------------------------------------------------------------------------------*/
/*      Keangle = PoleNo / 2                                        PoleNo : [-]            */
/*------------------------------------------------------------------------------------------*/
	Bprm.Keangle	  = MlibScalKxgain( (Prm.oslv_pol.b.h), 1, 2, NULL, -1 );
 #if(FLOAT_USE == 1)
	Bprm.fKeangle      = 0.5f * (Prm.oslv_pol.b.h);
#endif

/*  额定速度的计算 */
/*------------------------------------------------------------------------------------------*/
/*                                                                                          */
/*                 2*PAI * RATVEL * 100                             RATVEL    : [100r/min]  */
/*      RatSpd = ------------------------                                                   */
/*                         60                                                               */
/*------------------------------------------------------------------------------------------*/
 	kx                = MlibScalKxgain( (Prm.vrat_max.b.l & 0x00FF), C2PAIE7, 6000000, &sx, 0 );
	Bprm.RatSpd  	  = MlibPcalKxkskx( kx, Bprm.ExpSpd, 1, &sx, -1 );
 #if(FLOAT_USE == 1)
    fw = (float)(Prm.vrat_max.b.l & 0x00FF) * (float)C2PAIE7 / 6000000.0f;
    Bprm.fRatSpd = fw * Bprm.fExpSpd;
#endif

/*  最大速度[rad/s]的计算  */
/*------------------------------------------------------------------------------------------*/
/*                                                                                          */
/*                 2*PAI * MAXVEL * 100 * (10000+PerOvrSpd)         MAXVEL    : [100r/min]  */
/*      OvrSpd = --------------------------------------------       PerOvrSpd : [0.01%]     */
/*                             60 * 10000                                                   */
/*                                                                                          */
/*------------------------------------------------------------------------------------------*/
 	kx = MlibScalKxgain( Bprm.MaxVel, C2PAIE7, C10POW7, &sx, 0 );
	kx = MlibPcalKxgain( kx, ( Bprm.PerOvrSpd + 10000 ), 6000, &sx, 0 );
	Bprm.OvrSpd  	  = MlibPcalKxkskx( kx, Bprm.ExpSpd, 1, &sx, -1 );
 #if(FLOAT_USE == 1)
    fw = (float)Bprm.MaxVel * (float)C2PAIE7 / (float)C10POW7;
    fw = fw * (float)(Bprm.PerOvrSpd + 10000) / 6000.0F;
    Bprm.fOvrSpd = fw * Bprm.fExpSpd;
#endif

/*  最大扭矩[Nm]的计算 */
/*------------------------------------------------------------------------------------------*/
/*                                                                                          */
/*                 RATTRQ * MAXTRQ                                  RATTRQ : [0.01Nm]       */
/*      MaxTrq = -------------------                                MAXTRQ : [%]            */
/*                    100 * 100                                                             */
/*      Prm.rattrq : 额定转矩 0.01 Nm                                                       */
/*------------------------------------------------------------------------------------------*/
	kx = MlibScalKxgain( Prm.rattrq, Bprm.PerMaxTrq, 10000, &sx, 0 );
	Bprm.MaxTrq  	  = MlibPcalKxkskx( kx, Bprm.ExpTrq, 1, &sx, -1 );
#if (FLOAT_USE == 1)
    fw = (float)Prm.rattrq * (float)Bprm.PerMaxTrq / 10000.0F;
    Bprm.fMaxTrq = fw * Bprm.fExpTrq;
#endif
  
/*   电机惯量[kg*m^2]的計算    */
/*------------------------------------------------------------------------------------------*/
/*                                                                                          */
/*                JMOT                                              JMOT : [10^-6 kgm^2]    */
/*      Jmot = ------------                                                                 */
/*               1000000                                                                    */
/*                                                                                          */
/*------------------------------------------------------------------------------------------*/
 	Bprm.Jmot = MlibScalKskxkx( Bprm.ExpJmot, Prm.jmot, 1000000UL, NULL, -1 );
 #if (FLOAT_USE == 1)
    Bprm.fJmot = Bprm.fExpJmot * (float)Prm.jmot / 1000000.0F;
#endif

/* 反电势常数[Vrms/rad/s]的计算 */
/*------------------------------------------------------------------------------------------*/
/*                                                                                          */
/*                   60  * EMFCMP                               EMFCMP : [0.1mVrms/r/min]   */
/*      MotEmf = -------------------                                                        */
/*                 2*PAI * 10000                                                            */
/*                                                                                          */
/*------------------------------------------------------------------------------------------*/
 	Bprm.MotEmf  	  = MlibScalKxgain( Prm.emfcmp, 60000, C2PAIE7, NULL, -1 );
 #if (FLOAT_USE == 1)
    Bprm.fMotEmf = (float)Prm.emfcmp * 60000.0F / (float)C2PAIE7;
#endif

/*  过脉冲速度计算  [pulse/sec]    */
/*------------------------------------------------------------------------------------------*/
/*                                                                                          */
/*                  OvrSpd [rad/sec]                                                        */
/*      OvrPspd = ----------------------                                                    */
/*                  Kfbpls [rad/pulse]                                                      */
/*                                                                                          */
/*------------------------------------------------------------------------------------------*/
	Bprm.OvrPspd = MlibScalKxksks( 1, Bprm.OvrSpd, Bprm.Kfbpls, NULL, -1 );
	Bprm.MaxPspd = MlibScalKskxkx( Bprm.OvrPspd, Bprm.NorMaxSpd, Bprm.NorOvrSpd, NULL, -1 );
 #if (FLOAT_USE == 1)
    Bprm.fOvrPspd = Bprm.fOvrSpd / Bprm.fKfbpls;
    Bprm.fMaxPspd = Bprm.fOvrPspd * (float)Bprm.NorMaxSpd / (float)Bprm.NorOvrSpd;
#endif

/*  归一化速度计算系数 : r/min --> NormalizedSpeed   */
/*------------------------------------------------------------------------------------------*/
/*                                                                                          */
/*                  (2*PAI) * 2^24                                                          */
/*      Knorspd = ------------------------                          OvrSpd : [rad/s]        */
/*                    60 * OvrSpd                                                           */
/*                                                                                          */
/*------------------------------------------------------------------------------------------*/
    Bprm.Knorspd	  = MlibScalKxkxks( 1756906, 1, Bprm.OvrSpd, NULL, -1 );
 #if (FLOAT_USE == 1)
    Bprm.fKnorspd = 1756906.0F /Bprm.fOvrSpd;
#endif

/*  归一化速度计算系数 : r/min --> NormalizedSpeed   */
/*------------------------------------------------------------------------------------------*/
/*                                                                                          */
/*                      MAXVEL * 100 * (10000+PerOvrSpd)            MAXVEL    : [100r/min]  */
/*      NorspdConv = --------------------------------------------   PerOvrSpd : [0.01%]     */
/*                                      10000                                               */
/*                                                                                          */
/*  Use the Iprm.Kmonspd = 1 / Bprm.Knorspd NormalizedSpeed -> to perform and Un001 display */
/*  r/min conversion to fall digit, to create a new conversion gain so as not to fall digit */
/*-------------------------------------------------------------------------------------------*/
	kx = MlibScalKxgain( Bprm.MaxVel, ( Bprm.PerOvrSpd + 10000 ), 100, &sx, 0 );
	Bprm.NorspdConv   = MlibPcalKxkskx( kx, Bprm.ExpSpd, 0x1000000, &sx, -1 );
 #if (FLOAT_USE == 1)
    fw = (float)Bprm.MaxVel * (float)(Bprm.PerOvrSpd + 10000) / 100.0F;
    Bprm.fNorspdConv = ( fw * Bprm.fExpSpd ) / (float)0x1000000;
#endif

/*      速度換算系数 : 0.1r/min --> pulse/ms  */
/*------------------------------------------------------------------------------------------*/
/*                     Bprm.XfbPulse1                                                       */
/*      KMotSpdConv = ----------------      Bprm.XfbPulse1 : [pulse/rev]                    */
/*                     60 * 1000 * 10                                                       */
/*------------------------------------------------------------------------------------------*/
 	Bprm.KMotSpdConv = MlibScalKxgain( Bprm.XfbPulse1, 1, 60UL * 10000, NULL, -1 );

#if (FLOAT_USE == 1)
    Bprm.fKMotSpdConv = (float)Bprm.XfbPulse1 / 60.0F / 10000.0F;
#endif
    /*--------------------------------------------------------------------------------------------------*/
    /*      速度換算係数 : pulse/ScanA --> 2^24/OvrSpd                                <V158>              */
    /*--------------------------------------------------------------------------------------------------*/
    /*                      Bprm.KmotplsFC              10^9        Ts              :[ns]               */
    /*      KConvLoadSpd = ---------------- * 2^24 * -----------    Bprm.KmotplsFC  :[rad/pulse]        */
    /*                       Bprm.OvrSpd              Ts(ScanA)     Bprm.OvrSpd     :[rad/s]            */
    /*--------------------------------------------------------------------------------------------------*/
    kx = MlibScalKskxkx( Bprm.KmotplsFC, 1000000, KPI_SACYCLENS, &sx, 0 );
    kx                = MlibPcalKxgain( kx, 1000, 1, &sx, 0 );
    Bprm.KConvLoadSpd = MlibPcalKxkxks( kx, Bprm.NorOvrSpd, Bprm.OvrSpd, &sx, 24 );
#if (FLOAT_USE == 1)
    fw = (float)Bprm.fKmotplsFC * (float)1000000000 / (float)KPI_SACYCLENS;
    Bprm.fKConvLoadSpd = fw * (float)Bprm.NorOvrSpd  / (float)Bprm.fOvrSpd;
    //Bprm.fKConvLoadSpd = fw * (float)C10POW7 * 60.0f / (float)C2PAIE7;
#endif

 	return;
 }
  
  
