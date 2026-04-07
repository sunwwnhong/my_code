/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                   */
/*											2017 ~													*/
/****************************************************************************************************/
/*																									*/
/*																									*/
/*		Can07_SpdCmd.c : canopen速度指令处理            											*/
/*																									*/
/*																									*/
/****************************************************************************************************/
#include "Main.h"

CANOPENSPD CanSpdV; 
CANOPENINTERMODE CanIntMod;

/****************************************************************************************************/
/*                                                                                                  */
/*                                  Canopen 速度指令源                                              */
/*                                                                                                  */
/****************************************************************************************************/
LONG CanOpenSpdSource( void )
{
    SHORT Spd = 0;
    LLONG   TargetSpd = 0;
    LLONG   TargetSpd_Q15;
    LLONG    SpdCmdValue;
    if( ( Prm.Mode & 0xF000 ) == 0x1000 )
    {
        Spd = ( SHORT )ODDatArr[Target_Velocity_RPM].word.LowWord;
        SpdCmdValue = (LLONG)Spd * MencP.PulseNo / 60;
    }
    else
    {
        SpdCmdValue = (LLONG)ODDatArr[Target_Velocity_RPM].sall;
    }

	
    /*----------------------------------------------------------------------------------------------*/
    if( ODDatArr[Operation_Mode].all == 3 )                                     /* 轮廓速度模式     */
    {
        /*------------------------------------------------------------------------------------------*/
        /* 加减速度限制处理                                                                         */
        /*------------------------------------------------------------------------------------------*/
        LONG  SpdAcc,SpdDec;
        if( ODDatArr[Profile_Acceleration].all >= ODDatArr[ Max_Acceleration ].all )
        {
            SpdAcc = ODDatArr[ Max_Acceleration ].all;
        }
        else
        {
            SpdAcc = ODDatArr[Profile_Acceleration].all;
        }

        if( ODDatArr[Profile_Deceleration].all >= ODDatArr[ Max_Deceleration ].all )
        {
            SpdDec = ODDatArr[ Max_Deceleration ].all;
        }
        else
        {
            SpdDec = ODDatArr[Profile_Deceleration].all;
        }
        /*------------------------------------------------------------------------------------------*/
        /*  加速时基计算                         【0x6083】                                         */
        /*------------------------------------------------------------------------------------------*/
        if( ( Prm.Mode & 0xF000 ) == 0x1000 )
        {
            if( ODDatArr[Profile_Acceleration].all == 0)
            {
                ODDatArr[Profile_Acceleration].all = 1;
            }
            CanSpdV.AccBasic_Q15 = (ULLONG) MencP.PulseNo * 50 / ( ODDatArr[Profile_Acceleration].all);
            CanSpdV.AccBasic_Q15 = CanSpdV.AccBasic_Q15 >> 3;
        }
        else
        {
            CanSpdV.AccBasic_Q15 = (ULLONG)SpdAcc * 512 / 125;        
        }
        /*------------------------------------------------------------------------------------------*/
        if( CanSpdV.AccBasic_Q15 <= 1)
        {
            CanSpdV.AccBasic_Q15 = 1;
        }

        /*------------------------------------------------------------------------------------------*/
        /*  减速时基计算                         【0x6084】                                         */
        /*------------------------------------------------------------------------------------------*/
        if( ( Prm.Mode & 0xF000 ) == 0x1000 )
        {
            if( ODDatArr[Profile_Deceleration].all == 0)
            {
                ODDatArr[Profile_Deceleration].all = 1;
            }
            CanSpdV.DecBasic_Q15 = (ULLONG) MencP.PulseNo * 50 / ( ODDatArr[Profile_Deceleration].all );
            CanSpdV.DecBasic_Q15 =CanSpdV.DecBasic_Q15 >> 3;
        }
        else
        {
          
          
            CanSpdV.DecBasic_Q15 = (ULLONG)SpdDec * 512 / 125;        
        }
        /*------------------------------------------------------------------------------------------*/
        
        if(CanSpdV.DecBasic_Q15<= 1)
        {
            CanSpdV.DecBasic_Q15 = 1;
        }
        /*------------------------------------------------------------------------------------------*/
        /*  目标速度                             【0x60FF】                                         */
        /*------------------------------------------------------------------------------------------*/
        if( ( Prm.Mode & 0xF000 ) == 0x1000 )
        {
            TargetSpd_Q15 = (LLONG)SpdCmdValue;
        }
        else
        {
          
            TargetSpd_Q15 = (LLONG)SpdCmdValue << 15;
        }
		
		CanSpdV.TargetSpd_Q15 = TargetSpd_Q15;   
        /*------------------------------------------------------------------------------------------*/
        /* 暂停 & 快速停机 功能检测                                                                 */
        /*------------------------------------------------------------------------------------------*/
        ContSMachine.HaltStatus = ( ContSMachine.HaltStatus << 1 ) & 0x03;
    
        /*------------------------------------------------------------------------------------------*/
        /* 暂停状态检测                                                                             */
        /*------------------------------------------------------------------------------------------*/
        if( ( ODDatArr[Control_Word].all & 0x0100 ) == 0x0100 )
        {
            ContSMachine.HaltStatus |= 0x01;
        }
        
        /*------------------------------------------------------------------------------------------*/
        if( ContSMachine.HaltStatus == 1 )
        {
            /*--------------------------------------------------------------------------------------*/
            /* 减速度选择                                                                           */
            /*--------------------------------------------------------------------------------------*/
            if( ODDatArr[ Halt_option_code ].word.LowWord == 1 )
            {
                ContSMachine.DecBase_Q15 = ContSMachine.DecSBase6084_Q15;
            }
            else if( ODDatArr[ Halt_option_code ].word.LowWord == 2 )
            {
                ContSMachine.DecBase_Q15 = ContSMachine.DecSBase6085_Q15;
            }
            else
            {
                ContSMachine.DecBase_Q15 = CanSpdV.SpdCmd;
            }            
        }
        else if( ContSMachine.HaltStatus == 3 )
        {
            TargetSpd_Q15 = 0;
            CanSpdV.AccBasic_Q15 = ContSMachine.DecBase_Q15;
            CanSpdV.DecBasic_Q15 = ContSMachine.DecBase_Q15;
        }
        else
        {;}
        
        /*------------------------------------------------------------------------------------------*/
        /* 快速停机检测                                                                             */
        /*------------------------------------------------------------------------------------------*/
        ContSMachine.FastStatus = ( ContSMachine.FastStatus << 1 ) & 0x03;
        if( ( ODDatArr[Control_Word].all & 0x0004 ) == 0x0000 )
        {
            ContSMachine.FastStatus |= 0x01;
        }
        
        /*------------------------------------------------------------------------------------------*/
        if( ContSMachine.FastStatus == 0x01 )                   /* 第一次进入                       */
        {
            /*--------------------------------------------------------------------------------------*/
            /* 减速度选择                                                                           */
            /*--------------------------------------------------------------------------------------*/
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
            else if( ODDatArr[ Quick_stop_option_code ].word.LowWord == 1 || \
                      ODDatArr[ Quick_stop_option_code ].word.LowWord == 5)
            {
                ContSMachine.DecBase_Q15 = ContSMachine.DecSBase6084_Q15;
            }
            else if( ODDatArr[ Quick_stop_option_code ].word.LowWord == 2 || \
                      ODDatArr[ Quick_stop_option_code ].word.LowWord == 6)
            {
                ContSMachine.DecBase_Q15 = ContSMachine.DecSBase6085_Q15;
            }
            else
            {
                ContSMachine.DecBase_Q15 = CanSpdV.SpdCmd;
            }
        }
        else if( ContSMachine.FastStatus == 0x03 )
        {
            TargetSpd_Q15 = 0;
            CanSpdV.AccBasic_Q15 = ContSMachine.DecBase_Q15;
            CanSpdV.DecBasic_Q15 = ContSMachine.DecBase_Q15;
            if( CanSpdV.SpdCmd == 0 )
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
                        CanOpen_ControlStatus = 1;
                    }
                }
            }
        }
        else
        {;}
        /*------------------------------------------------------------------------------------------*/
        if( CanSpdV.SpdCmd >= 0 )                                   /* 目标速度 大于0               */
        {
            if( CanSpdV.SpdCmd <= TargetSpd_Q15 )
            {
                /*----------------------------------------------------------------------------------*/
                /*  加速                                                                            */
                /*----------------------------------------------------------------------------------*/
                CanSpdV.SpdCmd +=  CanSpdV.AccBasic_Q15;
                if( CanSpdV.SpdCmd >= TargetSpd_Q15)
                {
                    CanSpdV.SpdCmd      = TargetSpd_Q15;
                }
            }
            else
            {
                /*----------------------------------------------------------------------------------*/
                /*  减速                                                                            */
                /*----------------------------------------------------------------------------------*/
                CanSpdV.SpdCmd -=  CanSpdV.DecBasic_Q15;
                if( CanSpdV.SpdCmd < TargetSpd_Q15)
                {
                    CanSpdV.SpdCmd      = TargetSpd_Q15;
                }
                if( CanSpdV.DecBasic_Q15 == 0 )
                {
                    CanSpdV.SpdCmd = 0; //ReDesign @20230918
                }
            }
        }
        /*------------------------------------------------------------------------------------------*/
        else                                                        /* 目标速度 小于0               */
        {
            if( CanSpdV.SpdCmd <= TargetSpd_Q15 )
            {
                /*----------------------------------------------------------------------------------*/
                /*  减速                                                                            */
                /*----------------------------------------------------------------------------------*/
                CanSpdV.SpdCmd +=  CanSpdV.DecBasic_Q15;
                if( CanSpdV.SpdCmd >= TargetSpd_Q15)
                {
                    CanSpdV.SpdCmd      = TargetSpd_Q15;
                }
                if( CanSpdV.DecBasic_Q15 == 0 )
                {
                    CanSpdV.SpdCmd = 0; //ReDesign @20230918
                }
            }
            else
            {
                /*----------------------------------------------------------------------------------*/
                /*  加速                                                                            */
                /*----------------------------------------------------------------------------------*/
                CanSpdV.SpdCmd -=  CanSpdV.AccBasic_Q15;
                if( CanSpdV.SpdCmd < TargetSpd_Q15)
                {
                    CanSpdV.SpdCmd      = TargetSpd_Q15;
                }
            }        
        }
        /*------------------------------------------------------------------------------------------*/
        /*      伺服在OFF时 清零相关变量                                                            */
        /*------------------------------------------------------------------------------------------*/
        if( !BinV.f.BaseEnable )
        {
            CanSpdV.SpdCmd  = 0;
        }
        if( ( Prm.Mode & 0xF000 ) == 0x1000 )
        {
            TargetSpd = CanSpdV.SpdCmd;
        }
        else
        {
            TargetSpd = CanSpdV.SpdCmd >> 15;
        }
    }  
    else                                                        /* 其它模式                        */
    {
        TargetSpd = 0;
        CanSpdV.SpdCmd = 0;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 将Canopen 速度指令 PP/s 转换成0.1rpm                                                         */
    /*----------------------------------------------------------------------------------------------*/
    if( ( Prm.Mode & 0xF000 ) == 0x1000 )
    {
        TargetSpd   = ( INT64 )TargetSpd * 600 / MencP.PulseNo ;
    }
    else
    {
        TargetSpd   = ( INT64 )TargetSpd * 600 * Iprm.Egear.b / Iprm.Egear.a;
        
        TargetSpd   = ( INT64 )TargetSpd * ODDatArr[Position_Factor_Numer].sall /\
                (( INT64 )MencP.PulseNo * ODDatArr[Position_Factor_Divisor].sall);
    }
    /*----------------------------------------------------------------------------------------------*/
    /*  Canopen 速度指令极性                                                                        */
    /*----------------------------------------------------------------------------------------------*/
    if( ODDatArr[Polarity].all & 0x40)
    {
        TargetSpd = -TargetSpd;
    }

//    /*----------------------------------------------------------------------------------------------*/
//    /*  将速度指令转换成系统速度指令标幺值                                                          */
//    /*----------------------------------------------------------------------------------------------*/
//    TargetSpd = KpiSpeedLevelCal( TargetSpd, 0 );    
    /*----------------------------------------------------------------------------------------------*/
    /*  CANopen  机型时,同时还受到CANopen 对象字典 【0x607F】限制                                   */
    /*----------------------------------------------------------------------------------------------*/ 
    TargetSpd = MlibLimitul(TargetSpd,  CanSpdV.CanMaxSpd,    -CanSpdV.CanMaxSpd);

    return TargetSpd;
}

/****************************************************************************************************/
/*                                                                                                  */
/*     函数：InterPosMode插补位置模式                                                               */
/*     功能：插补位置模式根据插补周期更新位置指令值                                                 */
/*                                                                                                  */
/****************************************************************************************************/
LONG InterPosMode(void)
{
    LONG PosDelta = 0;                                                       //插补位置增量
    
    /*----------------------------------------------------------------------------------------------*/
    /* t0时刻PDO数据传输S0，t1时刻PDO数据传输S1；则t1时期更新插补位置为S0，插补周期为（t1-t0）      */
    /* t2时刻PDO数据传输S2，则t1时期更新插补位置为S1，插补周期为（t2-t1）                           */
    /* 同步接收的时候已经处理过一次 2021.2.26                                                       */
    /*----------------------------------------------------------------------------------------------*/
    if(PDO_Var.SYNCUpFlag1 == 1)                                            //判断同步报文更新 接收插补位置值
    { 
        PDO_Var.SYNCUpFlag1 = 0;                                            //同步接收标志清零
        if((ODDatArr[Status_Word].word.LowWord&0x006F) == 0x0027)           //判断当前运行状态机是否在运行状态
        {
            /*-------------------判断控制字bit4是否为1  为1的情况下开启插补模式----------------------*/
            if(ODDatArr[Control_Word].word.LowWord&0x0010)
            {
                CanIntMod.InterPosNew = (LONG)ODDatArr[Position_CMD_Lowword].all;
                CanOpenSyncTimeus = InterPeriod*125;                        //125us单位转换成us单位
                PcalPcmdMoveAvergeFilter( Prm.mafil,1 );
                  
                PosDelta = CanIntMod.InterPosNew - CanIntMod.IntorPosOld;   //插补位置指令增量计算 
                CanIntMod.IntorPosOld = CanIntMod.InterPosNew;
            }
            else
            {
                PosDelta = 0;                                               //bit4清零情况下  插补位置给0              
            }
        }
        else
        {
            PosDelta = 0;                                                   //非运行状态下位置增量清零
            CanIntMod.InterPeriodFlag = 0;
            CanIntMod.PDOPeriodFlag = 0;
            CanIntMod.InterPeriodCnt = 0;
            CanIntMod.PDOPeriodCnt = 0;
        }
    }

    /*------------------------------------------------------------------------------------------*/
    /* 位置指令取反                                                                             */
    /*------------------------------------------------------------------------------------------*/
    if( ODDatArr[Polarity].all & 0x80)
        PosDelta = -PosDelta;
    /*------------------------------------------------------------------------------------------*/
    return PosDelta;
}
