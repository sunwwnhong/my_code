/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Pos01_PosCmd.c
* Version            : V0.1
* Date               : 2023
* Description        : 位置控制指令给定
***********************************************************************************************/

#include "Main.h"
 
  
/**********************************************************************************************/
/* Function_Name: KpxInputScanB                                                          */
/* Description  : SCANB输入变量处理                                                         */
/**********************************************************************************************/
void KpxInputScanB( void )
{
LONG	lwk0;												 
LONG	lwk1;
LONG	MotSpd;												 
          
    /* 位置指令给定获取 */
    PosCmdSource( );

    /* 输出的脉冲格式为 单位采集时间(125us)内的变化量 */
    if( BinV.f.Sv.OrgPulseEn )
    {
        /* 在现有的脉冲基础上对脉冲进行给定,其它情况下关闭处理*/
        BinK.dPcmdHwCntr += AinK.ORGDelta;
        AinK.ORGDelta = 0;
    }

    /* 脉冲指令汇合点 */      
    BinK.dPcmdInputHwCntr = BinK.dPcmdHwCntr; 
  
    /* 计算电机位置和速度 */
    lwk0 = AinK.MotPos - KioV.MotPosB;                  //位置增量
    KioV.MotPosB = AinK.MotPos;                         //更新电机位置
    BinK.MotPos += lwk0;                                //更新电机位置
    BinK.dMotPos = lwk0;                                //更新电机位置增量

    /* 电机反馈脉冲数累加处理 */
    if( MencP.FirstFlag == 1 )
    {
        lwk1 = lwk0;
        CoutRrst.UnPfbkCntr  += lwk1;                       //编码器单位
    #if(FLOAT_USE == 1)
        lwk0 = flibEgearRvscnv( lwk1, &Iprm.Egear, &BinK.RemCntr2 ) ;
    #else
        lwk0 = MlibEgearRvscnv( lwk1, &Iprm.Egear, &BinK.RemCntr2 ) ;
    #endif
        CoutRrst.UnPfbkCntr2 += lwk0;                       //用户单位
    }
    else
    {
        CoutRrst.UnPfbkCntr = 0;
        CoutRrst.UnPfbkCntr2 = 0;
    }

    if( MencP.FirstFlag  && Kprm.f.FencUse)
    {
        AinK.dMotPosUnit =  lwk0;
       // AinK.MixUserErr += lwk0;                            /* 混合偏差[用户单位] -- 方式2补偿用    */
        CoutV.UnFposUserError += lwk0;
        lwk0 = MlibEgearRvscnv( lwk1, &Iprm.sfgear, &BinK.RemCntr3 ) ;

        AinK.dMotPosBUnit = lwk0;

        CoutRrst.UnPfbkCntr3 += lwk0;                       /* 光学尺单位                           */
    //        CoutRrst.UnPfbkCntr4 += lwk0;                       /* 混合偏差清除     【光学尺单位】      */
        AinK.MixFbkErr += lwk0;                             /* 混合偏差[光学尺单位] -- Er.d03用     */
       // CoutV.UnFposError += lwk0;                          /* 混合偏差[光学尺单位] --监控用        */
        /*--------------------------------------------------------------------------------------------------*/
        /*      Input Full Closed Encoder Position                                                          */
        /*--------------------------------------------------------------------------------------------------*/
        lwk0 = AinK.FencPosUnit - BinK.FencPosUnit;
        BinK.FencPosUnit = AinK.FencPosUnit;
        AinK.MixFbkErr -= lwk0;                             /* 混合偏差 [光学尺单位]  --Er.d03用    */
        /*------------------------------------------------------------------------------------------*/
        lwk0 = AinK.FencPos - KioV.FencPosB;                /* Cal. Delta Position[编码器单位]       */
        KioV.FencPosB = AinK.FencPos;                       /* Update Motor Position                */
        BinK.FencPos += lwk0;                               /* Update Fencoder Position             */
        BinK.dFencPos = lwk0;                               /* Update Delta Fencoder Position       */

        //AinK.MixPulAErr = AinK.MixPulAErr + BinK.dMotPos - lwk0;

        CoutV.UnFposError = CoutV.UnFposError + AinK.dMotPosBUnit - AinK.dFencPosUnit;    /* 混合偏差监控用[光学尺单位]           */
        AinK.dFencPosUnit = 0;
    }
    else
    {
        CoutV.UnFposError = 0;
        CoutRrst.UnPfbkCntr3 = 0;
        AinK.MixFbkErr = 0;
    }
    /*------------------------------------------------------------------------------------------*/

    if( !BinV.f.BaseEnable )
    {
        BinK.RemCntr5 = 0;
    }
//        lwk0 = MlibPcmdEgear( lwk0, &Iprm.sfgear, &BinK.RemCntr5 ) ;  /* 光学尺转编码器           */
    lwk0 = MlibEgearRvscnv( lwk0, &Iprm.Egear, &BinK.RemCntr5 ) ;   /* 编码器转用户             */

    AinK.MixUserErr = AinK.MixUserErr + AinK.dMotPosUnit - lwk0;                            /* 混合偏差 [用户单位] -- 方式2 补偿用  */
    CoutV.UnFposUserError -= lwk0;                      /* 混合偏差 [用户单位] --监控用         */

//    BinK.FencSpd  = AinK.FencSpd;                              //Motor Speed for ScanB [2^24/OvrSpd]



    if( Kprm.f.FencUse == 0 )
    {
        AinK.MixUserErr = 0;
    }

	MotSpd = AoutV.MotSpd_a;                            //平均速度  [2^24/OvrSpd]
    BinK.MotSpd  = MotSpd;                              //Motor Speed for ScanB [2^24/OvrSpd]
    BinK.AbsMotSpd = (MotSpd >= 0)? MotSpd : -MotSpd;   //Absolute Motor Speed [2^24/OvrSpd]
  
    /* 电机基准方向改变 */
    if( Iprm.f.RvsDir )
    {
        MotSpd  = - MotSpd;
    }

#if(FLOAT_USE == 1)
    AinK.Pcmpd = (SHORT)( (float)MotSpd * KioP.fKpcmpd );       //相位补偿（延迟）
#else
    AinK.Pcmpd = (SHORT)MlibMulgainNolim( MotSpd, KioP.Kpcmpd );
#endif

    /* From ScanA to ScanB */
    BinK.IqRefMon  = AinK.IqRefMon;			//Q轴电流指令监视[15000/Imax]
#if(FLOAT_USE == 1)
    BinK.TrqRefMon = 1118.481067f * BinK.IqRefMon;  //Q轴电流指令监视[15000/Imax]
#else
    BinK.TrqRefMon = MlibMulhigh32( ((LONG)BinK.IqRefMon << 16), 73300775 );
#endif
    BinK.IdRefMon = AinK.IdRefMon;			        //D轴电流指令监视[15000/Imax]
#if(FLOAT_USE == 1)
    BinK.TrqRefFilMon = 1118.481067f * AinK.IdRefMon;
#else
    BinK.TrqRefFilMon = MlibMulhigh32( ((LONG)AinK.IdRefMon << 16), 73300775 );
#endif
    BinK.TrqRefo_a = AoutV.TrqRefo_a;			    //转矩指令指令平均値
#if(FLOAT_USE == 1)
    BinK.TrqRefMon_a = 1118.481067f * AinK.IqRefMon_a;
#else
    BinK.TrqRefMon_a = MlibMulhigh32( ((LONG)AinK.IqRefMon_a << 16), 73300775 );
#endif
}
 
 
/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/
