/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                   */
/*											2017 ~													*/
/****************************************************************************************************/
/*																									*/
/*																									*/
/*		Can08_TorqCmd.c : canopen转矩指令处理            											*/
/*																									*/
/*																									*/
/****************************************************************************************************/
#include "Main.h"

CANOPENTORQ CanTorq;
/****************************************************************************************************/
/*Function_Name:KpiEtherCatInputTrqRef                                                         		*/
/*Description  :EtherCat 给定转矩指令                                                               */
/****************************************************************************************************/
//LONG CanOpenTorCmd = 0;
//LONG CanOpenTargetTorq = 0;
//INT64 CanOpenTorqRatio = 0;
LONG KpiCanOpenInputTrqRef(void)
{
    LONG TorqCmd;
    LONG TargetTorq;
    LONG Ratio = 0;
    if( ODDatArr[Operation_Mode].all == 4 )                                     /* 轮廓转矩模式                 */
    {
        /*------------------------------------------------------------------------------------------*/
        /* 伺服在未使能时,轮廓转矩指令清零                                                          */
        /*------------------------------------------------------------------------------------------*/
        if( BinV.f.BaseEnable )
        {
            /*--------------------------------------------------------------------------------------*/
            /*  伺服使能                ( 以一定斜率加减速 )                                        */
            /*--------------------------------------------------------------------------------------*/
            if( ODDatArr[Torque_Slope_MS].all == 0 )               /* 对转矩斜率进行限定            */
			{
                ODDatArr[Torque_Slope_MS].all = 1;
			}
            /*--------------------------------------------------------------------------------------*/
            /* 转矩指令标幺为 Q15格式                                                               */
            /*--------------------------------------------------------------------------------------*/
            TargetTorq = (SHORT)ODDatArr[Target_Torque].all;
            if( TargetTorq> 5000 ) 
			{
                CanTorq.TargetTorqQ15 = 163840000;
			}
            else if( TargetTorq < -5000 ) 
			{
                CanTorq.TargetTorqQ15 = -163840000;
			}
            else 
			{
                CanTorq.TargetTorqQ15 = TargetTorq<<15;
			}
            /*--------------------------------------------------------------------------------------*/
            /* 斜率系数,转矩计算是在62.5us循环里面运行                                              */
            /* 6087h单位：0.1%/s                                                                    */
            /*--------------------------------------------------------------------------------------*/
            Ratio = ((LONG)ODDatArr[Torque_Slope_MS].all << 8 ) / 125;
            CanTorq.TorqReachFlg    = 0;
            
            
            /*--------------------------------------------------------------------------------------*/
            /* 暂停 & 快速停机 功能检测                                                             */
            /*--------------------------------------------------------------------------------------*/
            ContSMachine.HaltStatus = ( ContSMachine.HaltStatus << 1 ) & 0x03;
        
            /*--------------------------------------------------------------------------------------*/
            /* 暂停状态检测                                                                         */
            /*--------------------------------------------------------------------------------------*/
            if( ( ODDatArr[Control_Word].all & 0x0100 ) == 0x0100 )
            {
                ContSMachine.HaltStatus |= 0x01;
            }
            
            /*--------------------------------------------------------------------------------------*/
            if( ContSMachine.HaltStatus == 3 )
            {
                CanTorq.TargetTorqQ15 = 0;
                if(ODDatArr[ Halt_option_code ].word.LowWord == 3)
                {
                    Ratio = CanTorq.TorCmdQ15;                          //解决转矩模式暂停停机3急停转矩停机20250525
                }
            }
            
            /*--------------------------------------------------------------------------------------*/
            /* 快速停机检测                                                                         */
            /*--------------------------------------------------------------------------------------*/
            ContSMachine.FastStatus = ( ContSMachine.FastStatus << 1 ) & 0x03;
            if( ( ODDatArr[Control_Word].all & 0x0004 ) == 0x0000 )
            {
                ContSMachine.FastStatus |= 0x01;
            }
            if( ContSMachine.FastStatus == 0x01 )               /* 第一次进入                       */
            {
                if( ODDatArr[ Quick_stop_option_code ].word.LowWord == 0 )
                {
                /*----------------------------------------------------------------------------------*/
                /* 模式 0:自由滑行                                                                  */
                /*----------------------------------------------------------------------------------*/
                    if(CiA402StatusMachine == 0)
                    {
                        CanOpen_ControlStatus = 2;
                    }
                }
            }
            else if( ContSMachine.FastStatus == 3 )
            {
                CanTorq.TargetTorqQ15 = 0;
                if( CanTorq.TorCmdQ15 == 0 )
                {
                    if(ODDatArr[ Quick_stop_option_code ].word.LowWord == 1 || \
                    ODDatArr[ Quick_stop_option_code ].word.LowWord == 2 )
                    {
                        if((CiA402StatusMachine == 1) && (QuickStop_flag == 1))
                        {
                            CanOpen_ControlStatus = 2;    //解决012快速停机CIA402状态机未进入case6,直接断使能
                        }
                        else if(CiA402StatusMachine == 0)
                        {
                            CanOpen_ControlStatus = 2;
                        }
                    }
                }
            }
            /*--------------------------------------------------------------------------------------*/
            if( CanTorq.TorCmdQ15  <=  CanTorq.TargetTorqQ15 )
            {
                CanTorq.TorCmdQ15  += Ratio;
                if( CanTorq.TorCmdQ15 >  CanTorq.TargetTorqQ15 )
                {
                    CanTorq.TorCmdQ15   = CanTorq.TargetTorqQ15;
                    CanTorq.TorqReachFlg= 1;
                }
            }
            else
            {
                CanTorq.TorCmdQ15 -= Ratio;
                if( CanTorq.TorCmdQ15 <  CanTorq.TargetTorqQ15 ) 
                {
                    CanTorq.TorCmdQ15   = CanTorq.TargetTorqQ15;
                    CanTorq.TorqReachFlg= 1;
                }
            }            
            
            /*--------------------------------------------------------------------------------------*/
            /* 输出转矩处理                                                                         */
            /*--------------------------------------------------------------------------------------*/
            TorqCmd = CanTorq.TorCmdQ15 >> 15 ;
        }
        else
        {
            CanTorq.TorCmdQ15   = 0;
            TorqCmd             = 0;
            CanTorq.TorqReachFlg= 0;
        }
    }
    else
    {
        TorqCmd                 = 0;
        CanTorq.TorqReachFlg    = 0;
        CanTorq.TorCmdQ15       = 0;
    }

    /*----------------------------------------------------------------------------------------------*/
    /* 改变转矩方向       对象字典【0x607E】                                                        */
    /*----------------------------------------------------------------------------------------------*/
    if( (ODDatArr[Polarity].all & 0x20) == 0x20 )
        TorqCmd = -TorqCmd;
    /*----------------------------------------------------------------------------------------------*/
    return TorqCmd;
}
