/*************** (C) COPYRIGHT 2025  Veichi Technology Co., Ltd*********************************
* File Name          : MIT.c
* Version            : V0.1
* Date               : 2025
* Description        : 机器狗MIT控制
***********************************************************************************************/
 #include "Main.h"


MITSTRUCT MIT;

/**********************************************************************************************/
/* Function_Name: MIT_CurrentLevelCal                                                          */
/* Description  : 计算电流的标幺值
                  SCANA调用
                  速度值得計算 :
                  标幺值 = I * [2^24/Imax]

                  输入：实际速度
                  输出：标幺速度                                                */
/**********************************************************************************************/
LONG MIT_CurrentLevelCal( float  I )
{
    LONG x,imax;

    imax = MlibMIN((SHORT)Prm.imaxs ,(SHORT)Prm.imax);
    x = 0x1000000 /imax * I ; //

    return ( x );
}
/****************************************************************************************************/
/*                                                                                                  */
/*     初始化(相关变量清零)                                                                     */
/*                                                                                                  */
/****************************************************************************************************/
void MIT_Init(void)
{
    MlibResetSHORTMemory((void *)&MIT, sizeof(MIT)); /* 相关数据清零处理                      */

    if(MIT_402_EN)
    {
        if(Kprm.f.EtherCATNet == 1)
        {
            MIT.GR = (float)u16MITMode.aEntries[EMIT_Red_Num] / (float)u16MITMode.aEntries[EMIT_Red_Den];
        }
        else if(Kprm.f.CanOpenNet == 1)
        {
            MIT.GR = (float)ODDatArr[  EMIT_Red_Num ].all / (float)ODDatArr[  MIT_Red_Den ].all;
        }
        else if(Kprm.f.StandardType == 1)
        {
            MIT.GR = (float)Prm.MIT_RateA / (float)Prm.MIT_RateB;
        }
    }
    else
    {
        MIT.GR = (float)Prm.MIT_RateA / (float)Prm.MIT_RateB;
    }
    MIT.Kt = (float)Prm.rattrq * 0.1f/ (float)Prm.irat;

    if(MIT_402_EN)
    {
        if(Kprm.f.EtherCATNet == 1)
        {
            MIT.PosFilt = (KPI_SACYCLEUS /( (float)u16MITMode.aEntries[EMIT_PosO_FTC] * 10.0f + KPI_SACYCLEUS ));
            MIT.TrefFilt = (KPI_SACYCLEUS /( (float)u16MITMode.aEntries[EMIT_TorqueO_FTC] * 10.0f + KPI_SACYCLEUS ));
        }
        else if(Kprm.f.CanOpenNet == 1)
        {
            MIT.PosFilt = (KPI_SACYCLEUS /( (float)ODDatArr[  MIT_PosO_FTC ].sall * 10.0f + KPI_SACYCLEUS ));
            MIT.TrefFilt = (KPI_SACYCLEUS /( (float)ODDatArr[  MIT_TorqueO_FTC ].sall * 10.0f + KPI_SACYCLEUS ));
        }
        else if(Kprm.f.StandardType == 1)
        {
            MIT.PosFilt = (KPI_SACYCLEUS /( (float)Prm.MIT_PosFil * 10.0f + KPI_SACYCLEUS ));
            MIT.TrefFilt = (KPI_SACYCLEUS /( (float)Prm.MIT_Tref * 10.0f + KPI_SACYCLEUS ));
        }
    }
    else
    {
        MIT.PosFilt = (KPI_SACYCLEUS /( (float)Prm.MIT_PosFil * 10.0f + KPI_SACYCLEUS ));
        MIT.TrefFilt = (KPI_SACYCLEUS /( (float)Prm.MIT_Tref * 10.0f + KPI_SACYCLEUS ));
    }

}


void MIT_Para_Update( void )
{
    if((Prm.b_prm400 & 0x000F)!= 7)
    {
        if(MIT_402_EN)
        {
            if(Kprm.f.EtherCATNet == 1)
            {
                MIT.TorqCmd  = (SHORT) u16MITMode.aEntries[EMIT_TorqueFF];
                u16MITMode.aEntries[EMIT_TorqueFF_Un] = MIT.TorqCmd;
            }
            else if(Kprm.f.CanOpenNet == 1)
            {
                MIT.TorqCmd  = (SHORT) ODDatArr[  MIT_TorqueFF ].all;
                ODDatArr[  MIT_TorqueFF_Un ].all = MIT.TorqCmd;
            }
            else if(Kprm.f.StandardType == 1)
            {
                MIT.TorqCmd  = (SHORT) Prm.MIT_Trq;
            }
        }
        else
        {
            MIT.TorqCmd  = (SHORT) Prm.MIT_Trq;
        }

    }
    else
    {
        MIT.AngleCmdSin = InnerInputCal(&CurSig);
        MIT.TorqCmd  = (SHORT) MIT.AngleCmdSin;
    }

    if(MIT_402_EN)
    {
        if(Kprm.f.EtherCATNet == 1)
        {
            MIT.AngleCmd = (SHORT) u16MITMode.aEntries[ EMIT_Given_Angle ] ;
            MIT.VelCmd   = (SHORT) u16MITMode.aEntries[ EMIT_GivenAngVel ];
            MIT.KpValCmd = u16MITMode.aEntries[ EMIT_Kp_Set ];
            MIT.KdValCmd = u16MITMode.aEntries[ EMIT_Kd_Set ];
			
			u16MITMode.aEntries[ EMIT_Given_Angle_Un ] = MIT.AngleCmd;
			u16MITMode.aEntries[ EMIT_GivenAngVel_Un ] = MIT.VelCmd;
			u16MITMode.aEntries[ EMIT_Kp_Un ] = MIT.KpValCmd;
			u16MITMode.aEntries[ EMIT_Kd_Un ] = MIT.KdValCmd;

            MIT.PosFilt = (KPI_SACYCLEUS /( (float)u16MITMode.aEntries[EMIT_PosO_FTC] * 10.0f + KPI_SACYCLEUS ));
            MIT.TrefFilt = (KPI_SACYCLEUS /( (float)u16MITMode.aEntries[EMIT_TorqueO_FTC] * 10.0f + KPI_SACYCLEUS ));
        }
        else if(Kprm.f.CanOpenNet == 1)
        {
            MIT.AngleCmd = (SHORT) ODDatArr[ MIT_TorqueFF ].sall ;
            MIT.VelCmd   = (SHORT) ODDatArr[ MIT_Given_Angle ].sall;
            MIT.KpValCmd = ODDatArr[ MIT_GivenAngVel ].all;
            MIT.KdValCmd = ODDatArr[ MIT_PosO_FTC ].all;
			
			ODDatArr[ MIT_Given_Angle_Un ].sall = MIT.AngleCmd;
			ODDatArr[ MIT_GivenAngVel_Un ].sall = MIT.VelCmd;
			ODDatArr[ MIT_Kp_Un ].all = MIT.KpValCmd;
			ODDatArr[ MIT_Kd_Un ].all = MIT.KdValCmd;

            MIT.PosFilt = (KPI_SACYCLEUS /( (float)ODDatArr[  MIT_PosO_FTC ].sall * 10.0f + KPI_SACYCLEUS ));
            MIT.TrefFilt = (KPI_SACYCLEUS /( (float)ODDatArr[  MIT_TorqueO_FTC ].sall * 10.0f + KPI_SACYCLEUS ));
        }
        else if(Kprm.f.StandardType == 1)
        {
            MIT.AngleCmd = (SHORT) Prm.MIT_Sitam ;
            MIT.VelCmd   = (SHORT) Prm.MIT_WmRef;
            MIT.KpValCmd = Prm.MIT_Kp;
            MIT.KdValCmd = Prm.MIT_Kd;
        }
    }
    else
    {
        MIT.AngleCmd = (SHORT) Prm.MIT_Sitam ;
        MIT.VelCmd   = (SHORT) Prm.MIT_WmRef;
        MIT.KpValCmd = Prm.MIT_Kp;
        MIT.KdValCmd = Prm.MIT_Kd;
    }
}





/**********************************************************************************************/
/* Function_Name: APL_MITCtr_ScanA                                                         */
/* Description  : 运动控制模式
                  SCANA调用
                  输入：
                  输出：iq转矩指令                                                  */
/**********************************************************************************************/

LONG APL_MITCtr_ScanA( void )
{
    float pi = 3.1415926;
    float MIT_Kp;//位置环增益
    float MIT_Kd;//速度环增益
    float TrqTn;//上位机给定转矩
    float MIT_Wn;//上位机给定转矩

    double TrqPos;

    MIT_Para_Update();
    if( BinV.f.BaseEnable )           // 伺服使能 RinV.f.BaseEnable
    {
        //位置指令滤波
        MIT.AngleCmdFil = ((1 - MIT.PosFilt) * MIT.AngleCmdFil + MIT.PosFilt * MIT.AngleCmd);//LPF

        /*MIT位置转矩计算*/
        MIT_Kp = (float)MIT.KpValCmd / 100;         //给增益先去小数
        MIT.PosCtrNm =  MIT_Kp * ( (float)MIT.AngleCmdFil * 10.0f  - MIT.MRPulseLSitam ) / 100;  //位置环 100为了去掉Prm.MIT_Sitam的小数点
        //转换为0.1A
        MIT.PosCtrAout =  MIT.PosCtrNm  / (MIT.Kt * MIT.GR) ;//负载端误差*负载端Kt=iq;负载端转矩常数Temp / GR * Kt *GR * 10(电流小数点);
        TrqPos =  MIT_CurrentLevelCal( MIT.PosCtrAout );//真实值转标幺值，Q24
        /*转矩限幅根据需要修改*/
        MIT.TrqSitam = MlibLimitul( TrqPos, 0x1000000, -0x1000000 );// 限幅输出0x1000000是最大电流 0x800000(8388608) 5566985(0x58FD8F)是额定电流

        /*MIT速度转矩计算*/
        //rpm->0.01rad/s(负载)
        MIT.VelFed1   = (float) KpiMonSpeedCal( AoutV.SpdObsFbki ) * pi * 10.0f/ (MIT.GR * 3.0f);
        MIT_Kd = (float)MIT.KdValCmd / 100;//给增益先去小数点

        //0.1Nm->0.1A
        MIT_Wn = MIT_Kd * ( MIT.VelCmd  - MIT.VelFed1 ) * 0.1f / (MIT.GR * MIT.Kt );
        MIT.TrqWm = MIT_CurrentLevelCal(MIT_Wn);//速度环标幺值

        /*MIT前馈速度转矩计算*/
        /* 计算给定转矩TN 0.1Nm*/
        TrqTn = (float) MIT.TorqCmd * 0.1f / (MIT.GR * MIT.Kt) ; //相对额定转矩百分比计算转矩电流
        MIT.TrqTn = MIT_CurrentLevelCal(TrqTn);//电流标幺

        /*MIT输出电流计算*/
        MIT.TrqMIT = MIT.TrqWm + MIT.TrqSitam;
        MIT.TrqRefitl = (float)MIT.TrqMIT + MIT.TrqTn;

        /*转矩指令滤波*/
        MIT.TrqRefo = ((1 - MIT.TrefFilt) *MIT.TrqRefo + MIT.TrefFilt * MIT.TrqRefitl);//LPF
    }
    else
    {
        MIT.TrqRefo = 0;
    }

    /*观测*/

    AoutV.TrqRefi = MIT.TrqRefo;
    AoutV.TrqRefi = MlibLimitul( AoutV.TrqRefi, 0x1000000, -0x1000000 );// 限幅输出0x1000000是300%额定转矩 0x800000是100%转矩 转矩限幅后面再修改
    return (AoutV.TrqRefi);

}


const SHORT MIT_Effcient[42] = { 100, 100 ,100, 100, 100, 100, 100 ,100, 100, 100,
                                 100, 100 ,100, 100, 100, 100, 100 ,100, 100, 100,
                                 100, 100 ,100, 100, 100, 100, 100 ,100, 100, 100,
                                 100, 100 ,100, 100, 100, 100, 100 ,100, 100, 100,
                                 100, 100 };

void MIT_Efficiency_Cal(LONG  TrqRefi)
{
    USHORT Num,Res;

    MIT.TrqNm = Prm.rattrq *  Prm.maxtrq  *  TrqRefi / 0x1000000;

    Num = ( MIT.TrqNm + Prm.rattrq *  Prm.maxtrq ) / 1000;
    Res = ( MIT.TrqNm + Prm.rattrq *  Prm.maxtrq ) % 1000;


    MIT.Effcient = MIT_Effcient[Num] +  (LONG)Res * (MIT_Effcient[Num + 1] - MIT_Effcient[Num]) / 1000;
}


void MIT_Fedback_Mon (void)
{
    float pi = 3.1415926;

    /***************************************** Type5报文反馈 ***********************************************/
    /* 转矩系数反馈 */
    if (Prm.KtSetEn)
    {
        MIT.Kt = Prm.KtSet / MIT.GR;
    }
    else
    {
        MIT.Kt = (float)Prm.rattrq * 0.1f/ (float)Prm.irat;
    }

    /* 位置反馈监控 */
    if( Kprm.f.FencUse == FALSE )
    {
        MIT.MRPulseLSitam = 2 * pi * ( ((double)CoutRrst.UnPfbkCntr) / (double)MencP.PulseNo ) * 1000 / MIT.GR;
    }
    else
    {
        if(Kprm.f.FencUseFlag == TRUE)
        {
            MIT.MRPulseLSitam = 2000.0f * pi * ( ((double)FencV.FencPos) / (double)FencV.FencPulseNo ) ;
        }
        else
        {
            MIT.MRPulseLSitam = 2 * pi * ( ((double)CoutRrst.UnPfbkCntr) / (double)MencP.PulseNo ) * 1000 / MIT.GR;
        }
    }
    //0.001rad->°
    MIT.AngleFeb = MIT.MRPulseLSitam * 0.1f ;


    /* 速度位置反馈监控 */
    // 标幺值 -> rpm -> 0.01rad/s
    MIT.VelFeb   = (float) KpiMonSpeedCal( BinK.MotSpd ) * pi * 10.0f / (MIT.GR * 3.0f);

    /* 转矩反馈监控 */
    //15000*100 ->0.01%->0.1Nm
    MIT.TorqFeb  = MIT.GR *  Iprm.fkmontrq2 * (float)AinK.IqFbMon * (float)Prm.rattrq / 1000000.0f;

    if(MIT_402_EN)
    {
        if(Kprm.f.EtherCATNet == 1)
        {
            u16MITMode.aEntries[ EMIT_Given_Angle_Un ] = MIT.AngleFeb;
            u16MITMode.aEntries[ EMIT_Given_Angle_Un ] = MIT.VelFeb;
            u16MITMode.aEntries[ EMIT_Given_Angle_Un ] = MIT.TorqFeb;
        }
        else if(Kprm.f.CanOpenNet == 1)
        {
            ODDatArr[ MIT_Given_Angle_Un ].sall = MIT.AngleFeb;
            ODDatArr[ MIT_Given_Angle_Un ].sall = MIT.VelFeb;
            ODDatArr[ MIT_Given_Angle_Un ].sall = MIT.TorqFeb;
        }
    }


}











