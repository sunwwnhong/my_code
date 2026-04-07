/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 ? All right Reserved                                   */
/*											2018 ~													*/
/****************************************************************************************************/
/*文件名:Pr02_PosCurveGenerator.c                                                                   */
/*创建时间: 2018.06.30                                                                              */
/*版本说明: V1.0                                                                                    */
/*功能描述:位置曲线生成器                                                                           */
/****************************************************************************************************/
#include "Main.h"


LONG EGearDen;
LLONG ACCDECCoeffQ15;



/****************************************************************************************************/
/*																									*/
/*		位置速度信息的计算处理  																	*/
/*  Attention: 加速和减速的时间均是基于 [0,3000] rpm来计算                    						*/
/*																									*/
/****************************************************************************************************/
void PosVelocityCoeffCount( void )
{
    LONG KX = 0;
    UCHAR AbsPosType;                           //绝对值位置起点选择
    LLONG PosDeltTemp;                          //电机位置偏移量
    LLONG MotFbkPos = 0;                        //电机反馈单圈位置（用户单位）
    LLONG OrgPosOffset_temp;                    //绝对值零点的脉冲数（用户单位）
    
    PrSpeed_AccDec_CoefCount();                 //计算加减速基值
    /*----------------------------------------------------------------------------------------------*/
    /* 最大速度计算                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
    PosCurvP.ProfRefSpdQ15 = ((LLONG)EGearDen<<12) * Pr_DICtrgV.PrSpd  / (600000);
    /*----------------------------------------------------------------------------------------------*/
    /* 位置控制加减速基值计算                                                                       */
    /*----------------------------------------------------------------------------------------------*/
    PosCurvP.AccBaseQ15 = (ACCDECCoeffQ15>>3) / Pr_DICtrgV.PrAccTime; 
    if(PosCurvP.AccBaseQ15 <= 1)
        PosCurvP.AccBaseQ15 = 1;
    /*----------------------------------------------------------------------------------------------*/
    PosCurvP.DecBaseQ15 = (ACCDECCoeffQ15>>3) / Pr_DICtrgV.PrDecTime;    
    if(PosCurvP.DecBaseQ15 <= 1)
    {
        PosCurvP.DecBaseQ15 = 1;
    }
    /*----------------------------------------------------------------------------------------------*/
    /*  目标位置量( 增量脉冲量,绝对脉冲量计算处理 )                                                 */
    /*----------------------------------------------------------------------------------------------*/
    if( Pr_DICtrgV.PosOption  == 0x01 )       /* 绝对式位置                               */
    {
        AbsPosType = (Prm.PrModeSet >> 12) & 0x0F;
        if( !AbsPosType )                     //原点回归的零点作为绝对位置起点
        {
            /*--------------------------------------------------------------------------------------*/
            /*------断使能后，电机位置可能变化，用CoutRrst.UnPfbkCntr2来计算实际位置----------------*/
            /*--------------------------------------------------------------------------------------*/
            PosDeltTemp = (LLONG)CoutRrst.UnPfbkCntr2 - Pr_DICtrgV.PosCmdSum ;

            if(PosCurvV.Pos1TarReach)
            {
                Pr_DICtrgV.PosCmdSum +=(Pr_DICtrgV.PosFbkDelt) ;
            }
            /*    断使能后，再次运行位置指令                                                        */
            else
            {
                Pr_DICtrgV.PosCmdSum +=(PosDeltTemp - Pr_DICtrgV.PosFbkDelt) ;
            }


            Pr_DICtrgV.PosCmdSum +=(PosDeltTemp - Pr_DICtrgV.PosFbkDelt) ; 
			
			
            if(!Kprm.f.FencUse)
                KX = Pr_DICtrgV.PrPos - Pr_DICtrgV.PosCmdSum;
            else
                KX = Pr_DICtrgV.PrPos - CoutRrst.UnFenseCnt2;
				

            PosCurvP.TargetPos      = KX;
            PosCurvV.PosSumIn       += (KX - PosCurvV.PosRemain);
            PosCurvV.PosRemain      = KX;
        }
        else                                //Pn296/Pn297设置的绝对零点作为绝对位置起点
        {           
            MotFbkPos = (LLONG)RoutV.ABSEncSValue * EGearDen/MencP.PulseNo;
            OrgPosOffset_temp = (LLONG)((SHORT)Prm.orgMpos-RoutV.ABSEncMValue) * EGearDen;
            OrgPosOffset_temp+= (LLONG)(( ((ULONG)Prm.orgSposH) << 16 ) + Prm.orgSposL ) * EGearDen / MencP.PulseNo;
            OrgPosOffset_temp-=  MotFbkPos;
                        
            KX = Pr_DICtrgV.PrPos + OrgPosOffset_temp;
            
            PosCurvP.TargetPos      = KX;
            PosCurvV.PosSumIn      += ( KX - PosCurvV.PosRemain );
            PosCurvV.PosRemain      = KX;
        }
    }
    /*----------------------------------------------------------------------------------------------*/
    else if( Pr_DICtrgV.PosOption == 0x00 )  /* 增量式位置                               */
    {
        PosCurvP.TargetPos     = Pr_DICtrgV.PrPos;
        PosCurvV.PosRemain    += PosCurvP.TargetPos;
        PosCurvV.PosSumIn     += PosCurvP.TargetPos;
    }
    /*----------------------------------------------------------------------------------------------*/
    else if( Pr_DICtrgV.PosOption  == 0x02)  /* 相对式位置                               */
    {
        PosCurvP.TargetPos     = Pr_DICtrgV.PrPos;
        PosCurvV.PosSumIn      = PosCurvV.PosSumOut + Pr_DICtrgV.PrPos;
          
        PosCurvV.PosRemain     = Pr_DICtrgV.PrPos;
    }
    /*----------------------------------------------------------------------------------------------*/
    else                                                /* CAP 命令 ( 捕获 )                        */
    {
        //待完善
        KX = 0;
        PosCurvP.TargetPos      = KX;
        PosCurvV.PosRemain     += KX;
        PosCurvV.PosSumIn      += KX; 
    }
    /*----------------------------------------------------------------------------------------------*/
    PosCurvV.TargetReach    = 0;                        /* 目标位置到达标志位清零                   */
}

/****************************************************************************************************/
/*																									*/
/*		速度和加减速系数的计算处理  																*/
/*  Attention: 加速和减速的时间均是基于 [0,3000] rpm来计算                    						*/
/*		MencP.PulseNo:一圈的脉冲数（编码器单位）         	        								*/
/****************************************************************************************************/
ULONG EncoderNum,EncoderDen;         //电子齿轮比
//LLONG PrModeSpdMax;
void PrSpeed_AccDec_CoefCount(void)
{
    LLONG EncoderNum_CMD;               //编码器线数（转一圈所需脉冲数)
    
    
    EncoderNum = ((ULONG)Prm.ratb2h << 16) + Prm.ratb2l;
    EncoderDen = ((ULONG)Prm.rata2h << 16) + Prm.rata2l;
    
    if(!EncoderNum)
    {
        EncoderNum_CMD = EncoderDen;
    }
    else
    {
        EncoderNum_CMD = (LLONG)MencP.PulseNo * EncoderDen / EncoderNum;
    }
    /*-----------------------------------------------------------------------------------------*/
    /*                  3000rpm × EncoderNum_CMD × 125 us                                      */
    /* ACCDECCoeff = ---------------------------------------  (以3000rpm为基准)                */
    /*                    60 × 1000 × 1000  (min -->us)                                        */
    /*-----------------------------------------------------------------------------------------*/
    EGearDen = (LONG) EncoderNum_CMD;
    ACCDECCoeffQ15 =( EncoderNum_CMD << 15 ) / 160; 
//    PrModeSpdMax = (LLONG)(EGearDen<<12)/10;
}
