/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot01_ScanA.c
* Version            : V0.1
* Date               : 2024
* Description        : ScanA处理
***********************************************************************************************/
  
#include "Main.h"

AINK AinK;		    //ScanA输入变量
AOUTV AoutV;        //ScanA输出变量


void FildBusPosFbk( void );


void FencePosFbk( void );
  
/**********************************************************************************************/
/* Function_Name: ApiScanAMain         */
/* Description  : SCANA中断主函数
                  调用：SCANA_Task调用
                  输入：
                  输出：   */
/**********************************************************************************************/

//#ifdef RunRAM
//#pragma CODE_SECTION(ApiScanAMain, ".TI.ramfunc");
//#endif

void ApiScanAMain( void )
{
LONG	MotSpd;
LONG	lwk0;
          
    //从编码器模块中 获取编码器位置信息MencV.dMotPos/MencV.RcvPosX
    MencP.KpiReadMencPosition( );

    //速度计算与滤波处理
    RmxSencScanServiceA( );
    MotSpd = MencV.MotSpd;
    MotSpd = LpxSpdDetMaFilter( MotSpd );

    if ( Prm.fbfil == 0)
    {
        AinK.MotSpdFilt = MotSpd;

    }
    else
    {
        AinK.MotSpdFilt = MlibLpfilter1( MotSpd , SpdCtrl.P.KVfbFil, AinK.MotSpdFilt );
    }


    //SCANA电机位置、速度和加速度输入变量获取
    lwk0 = MencV.MotPos - KioV.MotPosA;
    KioV.MotPosA = MencV.MotPos;


    if(Iprm.f.RvsDir)
    {
        AinK.MotSpd  = -AinK.MotSpdFilt;		    //作为转速控制输入、免调整控制和速度观测器的输入
        AinK.MotPos -=  lwk0;           //作为SCANB和SCANC的位置运算接口传递
        AinK.dMotPos = -lwk0;           //作为CANopen和EtherCAT位置相关的对象字典输入接口和零速钳位控制接口
    }
    else
    {
        AinK.MotSpd  = AinK.MotSpdFilt;
        AinK.MotPos += lwk0;
        AinK.dMotPos = lwk0;
    }
    AinK.ABSMotSpd = MlibABS( AinK.MotSpd );
	
	FencePosFbk();

    /* 减速停机时速度参考 */
    if( CinV.f.Seq.ServoOffDecM == 0 )
    {
        BoutV.SpdLdstpRefo = AinK.MotSpd;
    }


    /* 转矩限制值获取 */
    if(AoutV.TrqRefo > BoutK.PosTrqLmt)
    {
        AinK.TrqRefoLimit = BoutK.PosTrqLmt;
    }
    else if(AoutV.TrqRefo < BoutK.NegTrqLmt)
    {
        AinK.TrqRefoLimit = BoutK.NegTrqLmt;
    }
    else
    {
        AinK.TrqRefoLimit = AoutV.TrqRefo;
    }

    //CANopen和EtherCAT位置反馈处理
    FildBusPosFbk( );

    //CANopen和EtherCAT探针功能处理,25mm没有DI接口，删除
    //EtherCATPosLatch( );

    //模拟量校准处理
    ADCChannel1And2Deal( );

	/*伺服控制：基础控制：三环控制（位置环路、速度环路（零速控制）、转矩给定处理）            */
    /*                    电流零点搜索控制、V/F控制                          */
    /*          高级控制：免调整、速度观测器、负载观测器、摩擦补偿                    */
    ApxYecServoControl( );

    if(Kprm.f.FencUse && !KTM5900_Load_En)
    {
        MT6709_PosRead_Cmd(SPIB_BASE);
    }


    //CAN 数据帧接收处理(SDO)部分
    if( Kprm.f.CanOpenNet )
    {
        CAN1_RXCheck( );
    }

    /* 电流给定CLA接口:电机相位角、电机补偿角、角速度、反电势、dq轴指令 */
    KpiOutputCurRef( );

    /* 串口数据接收与发送 */
    RS485MsgManager();

    STO_FaultOutOff();

    /* 触发SCANB中断 */
    KnlV.ScanAcnt++;
    if((KnlV.ScanAcnt & 0x0F)==0x02 )
    {
        /* 第1个125us任务调度 */
        KnlV.ScanAcnt = 0;
        IntScanB2();
    }
}
 
  
/**********************************************************************************************/
/* Function_Name: FildBusPosFbk         */
/* Description  : CANopen和EtherCAT位置反馈处理
                  调用：SCANA_Task调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void FildBusPosFbk( void )
{

    LONG    lwk1;
    INT64   DataTmp;
    LONG    tmp;
    LONG    tmp1;
    LLONG   PulseOffset;

    /* 负载端位置累加按照未滤波的原始值处理，而位置全闭环控制按照滤波值处理 */
    lwk1 = (Kprm.f.FencUse)? AinK.dFencPosOri : AinK.dMotPos;

    if( Kprm.f.EtherCATNet == 1 )
    {
       /* 多圈编码器当做增量式用时 */
//
//       if(Kprm.f.FencUseFlag)
//       {
           if( Iprm.f.MulTSingT == 0x1 )
           {
                /* 控制模式为回零模式时，执行回零操作时处理 */
                if( s8ModeofOP == 0x06 && EthPosV.OB6040Bit4Status == 0x03 )
                {
                    MencP.OrgSegStatus = ( MencP.OrgSegStatus << 1 ) & 0x03;
                    if( OrgControlBit.bit.OrgDone  == 1 )
                    {
                        MencP.OrgSegStatus |= 0x01;
                    }
                }
                /* Pn040.Y =2 时， 单圈绝对值编码器使用时 */
                if( Iprm.f.MulTSing == 0x01 )
                {
                    /* 编码器上电前初始位置获取 */
                    if( MencP.FirstFlag == 0 )
                    {

                    /* 回零状态时处理 */
                    if( MencP.OrgSegStatus == 0x01 )
                    {
                        tmp1 = (INT64)s32HomeOffset * PositionFactor.aEntries[0] / PositionFactor.aEntries[1];
                        tmp1 = (INT64)tmp1 * Iprm.Egear.b / Iprm.Egear.a;
                        s32PosActValInc = tmp1;
                    }
                    /* 非回零状态时处理 */
                    else
                    {
                        /* 0x6063计算 有负载端编码器，反馈负载端编码器的绝对位置（转化为电机编码器单位） */
                        if ( Kprm.f.FencUseFlag )
                        {
                            tmp1 = (INT64)FencV.FencAbsPos * Iprm.sfgear.b / Iprm.sfgear.a;
                            s32PosActValInc = tmp1;
                        }
                        /* 无有负载端编码器，反馈电机编码器绝对位置 */
                        else
                            s32PosActValInc = RoutV.ABSEncSValue;
                    }
                }
                else
                {
                    s32PosActValInc += lwk1;                     
                }
            }
            /*  Pn040.Y =1 时多圈编码器当做增量式使用 */
            else
            {
                /* 编码器上电前初始位置获取值为零点偏置值 */
                if( MencP.FirstFlag == 0 )
                {
                    lwk1            = 0;
                    tmp1 = (double)s32HomeOffset * PositionFactor.aEntries[0] / PositionFactor.aEntries[1];
                    tmp1 = (double)tmp1 * Iprm.Egear.b / Iprm.Egear.a;
                    s32PosActValInc = tmp1;                  //【6063】 编码器单位            
                }
                else
                {
                    s32PosActValInc += lwk1;                 
                }
            }
        }
        /* 正常使用绝对值编码器时 */
        else
        {
            /* Pn277 单圈溢出功能开启时，位置取值处理 */
            if( (Prm.revovDir & 0x0001) == 0x0001 )
            {
                DataTmp = MRevV.MRPulse;
                s32PosActValInc = (LONG)MRevV.MRPulse;     // 电机位置反馈
            }
            else
            {
                /* 回零状态获取 */
                MencP.OrgSegStatus = ( MencP.OrgSegStatus << 1 ) & 0x03;
                if( OrgControlBit.bit.OrgOkFlag  == 1 )
                {
                    MencP.OrgSegStatus |= 0x01;
                }

                /* 控制模式为回零模式时，执行回零操作时处理 */
                if( MencP.OrgSegStatus == 0x01 )
                {
                     /* 负载端编码器使用时，参考负载端当前位置作为零点参考点 */
                     if ( Kprm.f.FencUseFlag )
                     {
                         tmp = FencV.FencAbsPos;
                         tmp1 = (LONG)(((double)((float)s32HomeOffset)) * Iprm.Ethfgear.bdiva * Iprm.Egear.bdiva);
                         tmp -= tmp1;
                         Prm.orgSposL = (USHORT)(tmp & 0x0000FFFF);
                         Prm.orgSposH = (USHORT)((tmp >> 16) & 0xFFFF);
                         Prm.orgMpos = FencV.FencMPos;

                     }
                     /* 电机编码器使用时，参考电机负载端位置作为零点参考点 */
                     else
                     {
                        tmp = RoutV.ABSEncSValue;
                        tmp1 = (LONG)(((double)((float)s32HomeOffset)) * Iprm.Ethfgear.bdiva * Iprm.Egear.bdiva);
                        tmp -= tmp1;
                        Prm.orgSposL = (USHORT)(tmp & 0x0000FFFF);
                        Prm.orgSposH = (USHORT)((tmp >> 16) & 0xFFFF);
                        Prm.orgMpos = RoutV.ABSEncMValue;
                     }
                     EnccodeStep = 1;
                     /* 原点回归状完成，待态写入EEPROM */
					 if( CAN_EXFUNC1_0_EN )
                     {
                        Prm.orgstatus = 1;
                     }

                    }

                MencP.PulseInitValue = (LONG)(( ((ULONG)Prm.orgSposH) << 16 ) + Prm.orgSposL);
                if (Kprm.f.FencUseFlag)
                {
                    //20260309 @syhu 解决Pn002设定为预定方向相反6064增量方向异常问题
                    if (MencP.FirstFlag == 0)
                    {
                        DataTmp = (INT64)( FencV.FencMPos - (SHORT)Prm.orgMpos ) * FencV.FencPulseNo + \
                                        FencV.FencAbsPos - MencP.PulseInitValue;
                        DataTmp = DataTmp * Iprm.sfgear.b / Iprm.sfgear.a;
                        s32PosActValInc = (LONG)( DataTmp ) ;
                    }
                    else
                    {
                        s32PosActValInc += lwk1;
                    }
                }
                else
                {
                    DataTmp = (INT64)( RoutV.ABSEncMValue - (SHORT)Prm.orgMpos ) * MencP.PulseNo + \
                                     RoutV.ABSEncSValue - MencP.PulseInitValue;
                    s32PosActValInc = (LONG)( DataTmp ) ;

                }
            }
        }
        DataTmp       = (double)s32PosActValInc * Iprm.Egear.fa / Iprm.Egear.fb;
        s32PosActVal  = (double)DataTmp * PositionFactor.aEntries[1]  / PositionFactor.aEntries[0];
    }
    else if( Kprm.f.CanOpenNet == 1 )
    {
        /* CAN回原运行到原点偏置使能 */
        if(CAN_EXFUNC0_14_EN)
        {
            PulseOffset = 0;
        }
        else
        {
            PulseOffset = ODDatArr[Homing_Offset_MM].sall;
        }

        /* 原点回归完成获取 */
        BinK.ORGFinishFlg = ( BinK.ORGFinishFlg << 1 ) & 0x03;
        if( OrgControlBit.bit.OrgOkFlag == 1 )
        {
            BinK.ORGFinishFlg |= 0x01;
        }

        /* 多圈编码器当做增量式使用 */
        if( Iprm.f.MulTSingT == 0x1 )
        {
            /*原点回归完成后，参考当前原点偏置值设定0x6063*/
            if( BinK.ORGFinishFlg == 0x01 )
            {
                MencP.PulseOffset = (INT64)PulseOffset * \
                                    ODDatArr[Position_Factor_Numer].all /\
                                    ODDatArr[Position_Factor_Divisor].all;
                MencP.PulseOffset = (double)MencP.PulseOffset * Iprm.Egear.fb / Iprm.Egear.fa;
                ODDatArr[OD_6063].sall =  MencP.PulseOffset;
            }
            /* 其他状态下，正常累加增量值*/
            else
            {
                ODDatArr[OD_6063].sall += lwk1;
            }

                /* 6063 -> 6064 单位转换*/
                DataTmp = (double)ODDatArr[OD_6063].sall * Iprm.Egear.fa / Iprm.Egear.fb;

            ODDatArr[OD_6064].sall  = DataTmp * ODDatArr[Position_Factor_Divisor].all  /\
                                               ODDatArr[Position_Factor_Numer].all + \
                                              ODDatArr[Homing_Offset_MM].sall;
        }
        else    /* 多圈编码器正常使用 */
        {
            /*原点回归完成后，参考当前当前位置设定0x6063*/
            if( BinK.ORGFinishFlg == 0x01 )
            {
                if ( Kprm.f.FencUseFlag )
                {
                     tmp = FencV.FencAbsPos;
                     tmp1 = (LONG)(((double)((float)ODDatArr[Homing_Offset_MM].sall)) * Iprm.CANgear.bdiva * Iprm.Egear.bdiva);
                     tmp -= tmp1;
                     Prm.orgSposL = (USHORT)(tmp & 0x0000FFFF);
                     Prm.orgSposH = (USHORT)((tmp >> 16) & 0xFFFF);
                     Prm.orgMpos = FencV.FencMPos;
                }
                else
                {
                    tmp = RoutV.ABSEncSValue;
                    Prm.orgSposL = (USHORT)tmp;
                    Prm.orgSposH = (USHORT)(tmp >> 16);
                    Prm.orgMpos = RoutV.ABSEncMValue;
                }

                if( CAN_EXFUNC1_0_EN )
                {
                    Prm.orgstatus = 1;
                }

                MencP.PulseOffset = (double)ODDatArr[Homing_Offset_MM].sall * \
                                    ODDatArr[Position_Factor_Numer].all / \
                                    ODDatArr[Position_Factor_Divisor].all;
                MencP.PulseOffset = (double)MencP.PulseOffset * Iprm.Egear.fb / Iprm.Egear.fa;

                EnccodeStep = 1;
             }

             MencP.PulseInitValue = (LONG)(( ((ULONG)Prm.orgSposH) << 16 ) + Prm.orgSposL);

             if( Kprm.f.FencUseFlag )
             {
                    //20260309 @syhu 解决Pn002设定为预定方向相反6064增量方向异常问题
                     if (MencP.FirstFlag == 0)
                     {
                         DataTmp = (INT64)( FencV.FencMPos - (SHORT)Prm.orgMpos ) * FencV.FencPulseNo + \
                                         FencV.FencAbsPos - MencP.PulseInitValue;
                         DataTmp = DataTmp * Iprm.sfgear.b / Iprm.sfgear.a;
                         ODDatArr[OD_6063].sall = (LONG)( DataTmp ) ;
                     }
                     else
                     {
                         ODDatArr[OD_6063].sall += lwk1;
                     }

             }
             else
             {
                 DataTmp = (INT64)( RoutV.ABSEncMValue - (SHORT)Prm.orgMpos ) * MencP.PulseNo + \
                                  RoutV.ABSEncSValue - MencP.PulseInitValue;
                 ODDatArr[OD_6063].sall = (LONG)( DataTmp ) ;
             }
        }
        DataTmp       = (double)ODDatArr[OD_6063].sall * Iprm.Egear.fa / Iprm.Egear.fb;
        ODDatArr[OD_6064].sall  = (double)DataTmp * ODDatArr[Position_Factor_Divisor].all  /\
                ODDatArr[Position_Factor_Numer].all;
    }
    else
    {

    }
    // yjp @20251106 周期+1处理，解决伪多圈处理过程中全闭环的负载编码器值数据没有更新
    //20260309 +2处理 @syhu 解决6063上电原计数值+1无法有效获取6064初始值问题
    if( (MencP.PowerOnDelay < (Prm.EncDelay + 2))  )
    {
        MencP.PowerOnDelay ++;
        MencP.FirstFlag = 0;
    }
    else
    {
        MencP.FirstFlag = 1;
    }
}

void FencePosFbk()
{
    LONG    lwk0;

    /*------------------------------------------------------------------------------------------*/
    /*              全闭环功能( 进行优化处理,在没有开启的时候也进行脉冲累计计算 )               */
    /*------------------------------------------------------------------------------------------*/
    if( Kprm.f.FencUse )                                /* 全闭环功能开启                      */
    {


        lwk0 = Iprm.DirSign * LpxReadFencPosition( );   /* 读取完整编码器位置数据              */
        /* AinK.dFencPosUnit 为负载端位置增量（光栅尺单位），将在SCANB中计算混合偏差后清零*/
        AinK.dFencPosUnit += lwk0;
/*--------------------------------------------------------------------------------------------------*/
/*                                         全闭环测试( 低分辨率 )                                   */
/*--------------------------------------------------------------------------------------------------*/
        /*--------------------------------------------------------------------------------------*/
        /* 计算脉冲反馈值,便于监控功能Un00E 监控                                                */
        /*--------------------------------------------------------------------------------------*/
        CoutRrst.UnFenseCnt2 += lwk0;
        /*--------------------------------------------------------------------------------------*/
        /* Edit By Zhuxc @2019.02.15 将全闭环光学尺的单位转换成电机编码器的单位,便于实际的运算  */
        /*--------------------------------------------------------------------------------------*/
        AinK.FencPosUnit += lwk0;                       /* 全闭环光栅尺脉冲累加计数             */

        lwk0 = MlibPcmdEgear( lwk0, &Iprm.sfgear, &AinK.FencRemain );
        /*--------------------------------------------------------------------------------------*/
        AinK.dFencPosOri = lwk0;                           
        AinK.FencPos += lwk0;  							/* Update Fencoder Position             */
		CoutRrst.UnFenseCnt1 += lwk0;

        if( (Prm.FensFiltTime == 0) )
        {
            AinK.dFencPos = AinK.dFencPosOri;
        }
        else        //混合误差滤波获取全闭环反馈
        {
            Delta_FencPosFil_Cal();
        }
    }
}
