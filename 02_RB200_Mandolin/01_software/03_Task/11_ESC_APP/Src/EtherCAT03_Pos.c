/****************************************************************************************************/
/*                                                                                                  */
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                   */
/*                                          2017 ~                                                  */
/****************************************************************************************************/
/*                                                                                                  */
/*                                                                                                  */
/*      EtherCAT16_Pos.c : 位置处理部分                                                               */
/*                                                                                                  */
/*                                                                                                  */
/****************************************************************************************************/
#include "Main.h"

ETHERCAT_CONTROL EcontSMachine;
ETHERCAT_POS EthPosV;
UCHAR AbsPosRecord = 0;

LLONG s32SynchSum = 0;
ULONG u32SynchNum = 0;
LONG s32SynchPos = 0;



/****************************************************************************************************/
/*Description  :暂停功能减速基值更新                                                                */
/*  位置轮廓模式                                                                                    */
/*  周期同步位置模式                                                                                */
/*  回零模式                                                                                        */
/****************************************************************************************************/
LONG EProfile_Dec_6084 = 0;
LONG EQuickStop_Dec_6085 = 0;
LONG EHomE_Acc_609A = 0;
void EtherCatHaltParameter_Update( void )
{
    /*----------------------------------------------------------------------------------------------*/
    if( EProfile_Dec_6084 != u32ProfileDec )
    {
        EProfile_Dec_6084 = u32ProfileDec;
        EcontSMachine.DecBase6084_Q15    = (float)EProfile_Dec_6084 / 1953.125f;     // 1953.125 = 8 / 15625
        if( EcontSMachine.DecBase6084_Q15 == 0 )
        {
            EcontSMachine.DecBase6084_Q15 = 1;
        }
        EcontSMachine.DecSBase6084_Q15   = (float)EProfile_Dec_6084 / 0.244140625f;  // 512 / 125;
    }
    /*----------------------------------------------------------------------------------------------*/
    if( EQuickStop_Dec_6085 != u32QuickStopDec )
    {
        EQuickStop_Dec_6085 = u32QuickStopDec;
        EcontSMachine.DecBase6085_Q15    = (float)EQuickStop_Dec_6085 / 1953.125f;
        if( EcontSMachine.DecBase6085_Q15 == 0 )
        {
            EcontSMachine.DecBase6085_Q15 = 1;
        }
        EcontSMachine.DecSBase6085_Q15   = (float)EQuickStop_Dec_6085 / 0.244140625f;
    }
    /*----------------------------------------------------------------------------------------------*/
    if( EHomE_Acc_609A != u32HomingAcc )
    {
        EHomE_Acc_609A = u32HomingAcc;
        EcontSMachine.DecBase609A_Q15 = (float)EHomE_Acc_609A / 0.244140625f;
        if( EcontSMachine.DecBase609A_Q15 == 0 )
        {
            EcontSMachine.DecBase609A_Q15 = 1;
        }
    }
}

/****************************************************************************************************/
/*                                                                                                  */
/*  暂停、快速停机功能,根据当前的速度进行减速处理                                                               */
/*                                                                                                  */
/****************************************************************************************************/
LONG Halt_Fast_StopMode( LONG PosDelta )
{
LONG PosCmdOut = 0;
LONG skx = 0;
INT64 DataTmp;
    /*----------------------------------------------------------------------------------------------*/
    /* 暂停 & 快速停机 功能检测                                                                          */
    /*----------------------------------------------------------------------------------------------*/
    EcontSMachine.HaltStatus = ( EcontSMachine.HaltStatus << 1 ) & 0x03;
    
    /*----------------------------------------------------------------------------------------------*/
    /* 暂停状态检测                                                                                    */
    /*----------------------------------------------------------------------------------------------*/
    if( ( u16ControlWord & 0x0104 ) == 0x0104 )
    {
        EcontSMachine.HaltStatus |= 0x01;
    }
    
    /*----------------------------------------------------------------------------------------------*/
    if( EcontSMachine.HaltStatus != 0x03 )
    {
        HaltEndFlag = 0;
    }
      
    /*----------------------------------------------------------------------------------------------*/
    if( EcontSMachine.HaltStatus == 0x01 )                      /* 第一次进入                       */
    {
        /*------------------------------------------------------------------------------------------*/
        if( s8ModeofOPDis == 6 )                                /* 回零                             */
        {
            OrgStr = OrgStrDefault;                             /* 原点回归复位                     */
            OrgControlBit.bit.OrgDone = 1;
        }
        /*------------------------------------------------------------------------------------------*/
        else if( s8ModeofOPDis == 1 )                           /* 轮廓位置模式                     */
        {
            PosCurGenerator_Clear();                            /* 轮廓位置复位                     */
        }
        /*------------------------------------------------------------------------------------------*/
        skx = KpiMonSpeedCal1( AoutV.MotSpd_a );               // 1rpm
        DataTmp = (double)skx * MencP.PulseNo / 600.0f;
        DataTmp = (double)DataTmp * (float)PositionFactor.aEntries[1] / (float)PositionFactor.aEntries[0];
        DataTmp = (double)DataTmp * Iprm.Egear.adivb;          //Iprm.Egear.a / Iprm.Egear.b;
        
        EcontSMachine.SpdOutQ15 = ((INT64)s32SynchPos) << 15;

        /*------------------------------------------------------------------------------------------*/
        /* 减速度选择                                                                               */
        /*------------------------------------------------------------------------------------------*/
        if( s16HaltOptioncode == 1 )
        {
            if( s8ModeofOPDis == 6 )
            {
                EcontSMachine.DecBase_Q15 = EcontSMachine.DecBase609A_Q15;
            }
            else
            {
                EcontSMachine.DecBase_Q15 = EcontSMachine.DecBase6084_Q15;
            }
        }
        /*------------------------------------------------------------------------------------------*/
        else if( s16HaltOptioncode == 2 )
        {
            EcontSMachine.DecBase_Q15 = EcontSMachine.DecBase6085_Q15;
        }
        else
        {
            EcontSMachine.DecBase_Q15 = EcontSMachine.SpdOutQ15;            /* 立即减速             */
            if( EcontSMachine.DecBase_Q15 < 0 )
            {
                EcontSMachine.DecBase_Q15 = -EcontSMachine.DecBase_Q15;
            }
        }
        /*------------------------------------------------------------------------------------------*/
    }
    else if( EcontSMachine.HaltStatus == 0x03 )                         /* 已经进入                 */
    {
        /*------------------------------------------------------------------------------------------*/
        /* 减速处理                                                                                 */
        /*------------------------------------------------------------------------------------------*/
        if( EcontSMachine.SpdOutQ15 == 0LL )                            /* 减速完成,速度 == 0       */
        {
            PosCmdOut = 0;
            HaltEndFlag = 1;
        }
        /*------------------------------------------------------------------------------------------*/
        else if( EcontSMachine.SpdOutQ15 > 0 )                         /* 速度大于零               */
        {
            EcontSMachine.SpdOutQ15 -= EcontSMachine.DecBase_Q15;
            if( EcontSMachine.SpdOutQ15 > 0 )
            {
                PosCmdOut = EcontSMachine.SpdOutQ15 >> 15;
            }
            else
            {
                PosCmdOut = 0;
                EcontSMachine.SpdOutQ15 = 0;
            }
        }
        /*------------------------------------------------------------------------------------------*/
        else                                                            /* 速度小于零               */
        {
            EcontSMachine.SpdOutQ15 += EcontSMachine.DecBase_Q15;
            if( EcontSMachine.SpdOutQ15 < 0 )
            {
                PosCmdOut = EcontSMachine.SpdOutQ15 >> 15;
            }
            else
            {
                PosCmdOut = 0;
                EcontSMachine.SpdOutQ15 = 0;
            }    
        }
    }
    else if( EcontSMachine.HaltStatus == 0x02 )
    {
        u16StatusWord &= 0xEFFF;                    // 内部轮廓位置模式,暂停时恢复
        EthPosV.AbsPosCmd = s32PosActVal;
    }
    else
    {;}
    
    /*----------------------------------------------------------------------------------------------*/
    /* 快速停机检测                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
    EcontSMachine.FastStatus = ( EcontSMachine.FastStatus << 1 ) & 0x03;
    if( ( u16ControlWord & 0x0004 ) == 0x0000 )
    {
        EcontSMachine.FastStatus |= 0x01;
    }
    
    /*----------------------------------------------------------------------------------------------*/
    if( EcontSMachine.FastStatus == 0x01 )                       /* 第一次进入                      */
    {
        /*------------------------------------------------------------------------------------------*/
        if( s8ModeofOPDis == 6 )                                 /* 回零模式                        */
        {
            OrgStr = OrgStrDefault;                              /* 原点回归复位                    */
            OrgControlBit.bit.OrgDone = 1;
        }
        /*------------------------------------------------------------------------------------------*/
        else if( s8ModeofOPDis == 1 )                            /* 轮廓位置模式                    */
        {
            PosCurGenerator_Clear();                             /* 轮廓位置复位                    */
        }
        /*------------------------------------------------------------------------------------------*/
        //EcontSMachine.SpdOutQ15 = ((INT64)s32SynchPos) << 15;
        skx = KpiMonSpeedCal1( AoutV.MotSpd_a );               // 1rpm    20230101
        DataTmp = (double)skx * (float)MencP.PulseNo / 600.0f;
        DataTmp = (double)DataTmp * (float)PositionFactor.aEntries[1] / (float)PositionFactor.aEntries[0];
        DataTmp = (double)DataTmp * Iprm.Egear.adivb;   //   Iprm.Egear.a / Iprm.Egear.b;
        
        
        EcontSMachine.SpdOutQ15 = ((INT64)s32SynchPos) << 15;
        
        /*------------------------------------------------------------------------------------------*/
        /* 减速度选择                                                                               */
        /*------------------------------------------------------------------------------------------*/
        if( s16QuickShutdownOpt == 0 )
        {
            /*--------------------------------------------------------------------------------------*/
            /* 模式 0:自由滑行                                                                      */
            /*--------------------------------------------------------------------------------------*/
            if((CiA402StatusMachine == 1) && (QuickStop_flag == 1))
            {
                EtherCAT_ControlStatus = 2;    //解决012快速停机CIA402状态机未进入case6,直接断使能
            }
            else if(CiA402StatusMachine == 0)
            {
                EtherCAT_ControlStatus = 2;
            }
        }
        else if( s16QuickShutdownOpt == 1 || s16QuickShutdownOpt == 5)
        {
            if( s8ModeofOPDis == 6 )
            {
                EcontSMachine.DecBase_Q15 = EcontSMachine.DecBase609A_Q15;
            }
            else
            {
                EcontSMachine.DecBase_Q15 = EcontSMachine.DecBase6084_Q15;
            }
        }
        else if( s16QuickShutdownOpt == 2 || s16QuickShutdownOpt == 6)
        {
            EcontSMachine.DecBase_Q15 = EcontSMachine.DecBase6085_Q15;
        }
        else
        {
            EcontSMachine.DecBase_Q15 = EcontSMachine.SpdOutQ15;
            if( EcontSMachine.DecBase_Q15 < 0 )
            {
                EcontSMachine.DecBase_Q15 = -EcontSMachine.DecBase_Q15;
            }
        }
    }
    else if( EcontSMachine.FastStatus == 0x03 )                         /* 已经进入                 */
    {
        /*------------------------------------------------------------------------------------------*/
        /* 减速处理                                                                                 */
        /*------------------------------------------------------------------------------------------*/
        if( EcontSMachine.SpdOutQ15 == 0 )                               /* 减速完成,速度 == 0      */
        {
            PosCmdOut = 0;
            if(s16QuickShutdownOpt == 1 || s16QuickShutdownOpt == 2)
            {
                if((CiA402StatusMachine == 1) && (QuickStop_flag == 1))
                {
                    EtherCAT_ControlStatus = 2;    //解决012快速停机CIA402状态机未进入case6,直接断使能
                }
                else if(CiA402StatusMachine == 0)
                {
                    EtherCAT_ControlStatus = 2;
                }
            }
        }
        else if( EcontSMachine.SpdOutQ15 > 0 )                           /* 速度大于零              */
        {
            EcontSMachine.SpdOutQ15 -= EcontSMachine.DecBase_Q15;
            if( EcontSMachine.SpdOutQ15 > 0 )
            {
                
                PosCmdOut = EcontSMachine.SpdOutQ15 >> 15;
            }
            else
            {
                PosCmdOut = 0;
                EcontSMachine.SpdOutQ15 = 0;
            }
        }
        else                                                            /* 速度小于零               */
        {
            EcontSMachine.SpdOutQ15 += EcontSMachine.DecBase_Q15;
            if( EcontSMachine.SpdOutQ15 < 0 )
            {
                
                PosCmdOut = EcontSMachine.SpdOutQ15 >> 15;
            }
            else
            {
                PosCmdOut = 0;
                EcontSMachine.SpdOutQ15 = 0;
            }        
        }
    }
    
    else if( EcontSMachine.FastStatus == 0x02 )
    {
       // CanPosV.s32TargetPosOld = ODDatArr[Targe_Position_MM].all;      /*  更新旧值                */
        EthPosV.AbsPosCmd = s32PosActVal;   
    }
    
    /*----------------------------------------------------------------------------------------------*/
    if( EcontSMachine.FastStatus == 0x03 || EcontSMachine.HaltStatus == 0x03 )
    {
        return ( PosCmdOut );
    }
    else
    {
        return PosDelta;
    }
}

/****************************************************************************************************/
/*Function_Name:EtherCAT_PosCmdDeal                                                                 */
/*Description  :位置指令源处理                                                                      */
/*  位置轮廓模式                                                                                    */
/*  周期同步位置模式                                                                                */
/*  回零模式                                                                                        */
/****************************************************************************************************/
LONG EtherCAT_PosCmd( void )
{
LONG PosDelta = 0;
LONG PosTmp = 0;
LONG KX = 0;
    /*----------------------------------------------------------------------------------------------*/
    /* 伺服 Off 时相关数据清零                                                                      */
    /*----------------------------------------------------------------------------------------------*/
    if( ( BinV.f.BaseEnable == 0 ) || ((u16ControlWord & 0x0008) == 0x0000))
    {
        EthPosV.PPStep = 0;
        u16StatusWord &= 0xEFFF;                                    /* 可以接收新的位置指令         */
        PosCurGenerator_Clear( );
/*--------------------------------------------------------------------------------------------------*/
#if 1
        EthPosV.s32TargetPosOld = s32TargetPos;                     /* 更新旧值                     */
#else
        EthPosV.s32TargetPosOld = s32PosActVal;
#endif
/*--------------------------------------------------------------------------------------------------*/
        EthPosV.AbsPosCmd = s32PosActVal;
        EthPosV.s32PositionOffsetFlag   = 0;

        EthPosV.OB6040Bit4Status2 = 0;

        return 0;
    }
    
    if( s8ModeofOPDis != 8 )
    {
        EthPosV.s32PositionOffsetFlag   = 0;
    }

    EthPosV.Mode18Sel = EthPosV.Mode18Sel << 1;
    EthPosV.Mode18Sel &= 0x0003;
    if( s8ModeofOPDis == 1 )
    {
        EthPosV.Mode18Sel |= 0x0001;
        EthPosV.Mode18Sel &= 0x0003;
    }
    if( EthPosV.Mode18Sel == 1 )
    {
        EthPosV.AbsPosCmd = s32PosActVal;
    }

    EthPosV.OB6040Bit4Status2 = EthPosV.OB6040Bit4Status2 << 1;
    EthPosV.OB6040Bit4Status2 &= 0x03;
    if( ( u16ControlWord & 0x0010 )  == 0x0010)
    {
       EthPosV.OB6040Bit4Status2 |= 0x01;
    }

    /*----------------------------------------------------------------------------------------------*/
    /* 位置轮廓模式                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
    if(s8ModeofOPDis == 1)
    {
        /*------------------------------------------------------------------------------------------*/
        EthPosV.s32TargetPosOld = s32TargetPos;

        /*------------------------------------------------------------------------------------------*/
        switch( EthPosV.PPStep )
        {
            /*--------------------------------------------------------------------------------------*/
            case 0:                                                /* 控制字6040的Bit4为上升沿检测  */
                    /*------------------------------------------------------------------------------*/
                    /* 只有在控制字 Bit4 为                                                         */
                    /*------------------------------------------------------------------------------*/
                    if( (u16ControlWord & 0x0010) == 0x0000 )
                    {
                        u16StatusWord &= 0xEFFF;                   /* 可以接收新的位置指令          */
                    }
                    /*------------------------------------------------------------------------------*/
                    /* 绝对位置指令立即执行                                                         */
                    /*------------------------------------------------------------------------------*/
                    if(CAN_EXFUNC0_2_EN)
                    {
                        u16StatusWord &= 0xEFFF;                   /* 可以接收新的位置指令          */
                    }
                    /*------------------------------------------------------------------------------*/
                    /* 非立即更新模式                                                               */
                    /*------------------------------------------------------------------------------*/
                    //解决立即更新时，快速停机、暂停停机不按减速度停机问题
                    if( ( (u16ControlWord & 0x0020 )== 0x0000) && ((u16ControlWord & 0x0004) == 0x0004)\
                        &&( u16ControlWord & 0x0104 ) != 0x0104 )      /* Bit5:0 非立即更新            */
                    {
                        if( EthPosV.OB6040Bit4Status2 == 0x01 )      /* 控制字6040的Bit4为上升沿     */
                        {
                            EthPosV.PPStep = 1;
                        }
                    }
                    /*------------------------------------------------------------------------------*/
                    /* 立即更新模式   对象字典【607A】                                              */
                    /*------------------------------------------------------------------------------*/
                    else                                            /* Bit5:1 立即更新              */
                    {
                        /*--------------------------------------------------------------------------*/
                        /* 绝对位置立即更新                                                         */
                        if(CAN_EXFUNC0_2_EN &&(EthPosV.OB6040Bit4Status == 0x03))
                        {
                            if(( EthPosV.s32TargetPos607AOld != s32TargetPos)||(EthPosV.s32TargetVel6081Old != u32ProfileVel))
                            {
                                /*------------------------------------------------------------------*/
                                if( u8Polarity & 0x80 )                /* 位置指令极性              */
                                {
                                    PosTmp = -s32TargetPos;
                                }
                                else
                                {
                                    PosTmp = s32TargetPos;
                                }
                                /*------------------------------------------------------------------*/
                                if( u16ControlWord & 0x0040 )          /* 相对位置                  */
                                {
                                    PosCurvP.TargetPos = PosTmp;
                                    EthPosV.AbsPosCmd += PosTmp;
                                }
                                else                                   /* 绝对位置                  */
                                {
                                    PosCurvP.TargetPos = PosTmp - EthPosV.AbsPosCmd;
                                    EthPosV.AbsPosCmd = PosTmp;
                                }
                                PosCurvV.PosBlock = 0;
                                /*------------------------------------------------------------------*/
                                EthercatPosParameterUpdate();          /* 相关参数更新              */   
                            }
                        }
                        /*--------------------------------------------------------------------------*/
                        else if( EthPosV.OB6040Bit4Status == 0x01 && (u16StatusWord & 0x1000) == 0x0000)
                        {
                            u16StatusWord |= 0x1000;               /* 置位状态字 Bit12 为1          */
                            /*----------------------------------------------------------------------*/
                            if( u8Polarity & 0x80 )                /* 位置指令极性                  */
                            {
                                PosTmp = -s32TargetPos;
                            }
                            else
                            {
                                PosTmp = s32TargetPos;
                            }
                            /*----------------------------------------------------------------------*/
                            if( u16ControlWord & 0x0040 )          /* 相对位置                      */
                            {
                                PosCurvP.TargetPos = PosTmp;
                                EthPosV.AbsPosCmd += PosTmp;
                            }
                            else                                   /* 绝对位置                      */
                            {
                                PosCurvP.TargetPos = PosTmp - EthPosV.AbsPosCmd;
                                EthPosV.AbsPosCmd = PosTmp;
                            }
                            
                            PosCurvV.PosBlock = 0;
                            /*----------------------------------------------------------------------*/
                            EthercatPosParameterUpdate();          /* 相关参数更新                  */                        
                        }
                        /*--------------------------------------------------------------------------*/
                        if( EthPosV.OB6040Bit4Status == 0x02 )
                        {
                            u16StatusWord &= 0xEFFF;               /* 可以接收新的位置指令          */
                        }
                        /*--------------------------------------------------------------------------*/
                        EthPosV.s32TargetPos607AOld = s32TargetPos;
                        EthPosV.s32TargetVel6081Old = u32ProfileVel;
                        PosCurveGenerator_Deal( );
                        
                        PosDelta = PosCurvV.PosCmdOut;
                        EthPosV.PPStep = 0;
                    }
                    break;
            /*--------------------------------------------------------------------------------------*/
            case 1:
                    /*------------------------------------------------------------------------------*/
                    /* u16ControlWord Bit5 :    0 非立即更新                                        */
                    /* StatusWord     Bit12:    0 上一指令发送完成,可以更新                         */
                    /*------------------------------------------------------------------------------*/
                    if((( u16ControlWord & 0x0020 ) == 0x0000) && (( u16StatusWord & 0x1000) == 0x0000 ))
                    {
                        /*--------------------------------------------------------------------------*/
                        /* 非立即更新模式 (置位相应标志位,当前位置执行中)                           */
                        /*--------------------------------------------------------------------------*/
                        u16StatusWord |= 0x1000;                   /* 置位状态字 Bit12 为1          */         
                        /*--------------------------------------------------------------------------*/
                        /* 相关信息更新                                                             */
                        /*--------------------------------------------------------------------------*/
                        /*                       位置指令计算更新                                   */
                        /*--------------------------------------------------------------------------*/
                        if( u8Polarity & 0x80 )                    /* 位置指令极性                  */
                        {
                            PosTmp = -s32TargetPos;
                        }
                        else
                        {
                            PosTmp = s32TargetPos;
                        }
                        /*--------------------------------------------------------------------------*/                        
                        if( u16ControlWord & 0x0040 )              /* 相对位置                      */
                        {
                            PosCurvP.TargetPos = PosTmp;
                            EthPosV.AbsPosCmd += PosTmp;
                        }
                        else                                       /* 绝对位置                      */
                        {
                            PosCurvP.TargetPos = PosTmp - EthPosV.AbsPosCmd;
                            EthPosV.AbsPosCmd = PosTmp;
                        }
                        
                        EthercatPosParameterUpdate();              /* 相关参数更新                  */
                        
                        EthPosV.PPStep = 2;                        /* 进入下一步                    */
                    }
                break;
            /*--------------------------------------------------------------------------------------*/
            case 2:
                if( PosCurvV.TargetReach )
                {
                    /*------------------------------------------------------------------------------*/
                    /* 位置曲线生成结束                                                             */
                    /*------------------------------------------------------------------------------*/
                    EthPosV.PPStep = 0;
                }
                else
                {
                    PosCurveGenerator_Deal( );
                    PosDelta = PosCurvV.PosCmdOut;
                }
                break;
            /*--------------------------------------------------------------------------------------*/
            default:
                break;
        }
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 回零模式                                                                                     */
    /*----------------------------------------------------------------------------------------------*/
    else if( s8ModeofOPDis == 6 )
    {
        /*------------------------------------------------------------------------------------------*/
        /* 原点回归时,读取外部的相关信号                                                            */
        /*------------------------------------------------------------------------------------------*/
        DISignReach = BinV.f.Sv.ORGS;                           /* 原点信号                         */
        
        /*------------------------------------------------------------------------------------------*/
        /* 待定                                                                                     */
        /*------------------------------------------------------------------------------------------*/
        PosLimit = CinV.f.Sv.PotIn;                             /* 正限位信号输入                   */
        NegLimit = CinV.f.Sv.NotIn;                             /* 反向限位信号输入                 */
        
        /*------------------------------------------------------------------------------------------*/
        /* 原点信号沿触发状态判断                                                                   */
        /*------------------------------------------------------------------------------------------*/
        if(DISignReach == 1 && DISignOld == 0)
        {
            OrgPrCtlBit.OrgSignUp = 1;
            OrgPrCtlBit.OrgSignDown = 0;
//            u16StatusWord |= 0x8000;                            //找到参考点，bit15置1
        }
        else if(DISignReach == 0 && DISignOld == 1)
        {
            OrgPrCtlBit.OrgSignUp = 0;
            OrgPrCtlBit.OrgSignDown = 1;
//            u16StatusWord |= 0x8000;                            //找到参考点，bit15置1
        }
        else
        {
            OrgPrCtlBit.OrgSignUp = 0;
            OrgPrCtlBit.OrgSignDown = 0;
        }
        /*------------------------------------------------------------------------------------------*/
        /* 正限位触发信号判断                                                                       */
        /*------------------------------------------------------------------------------------------*/
        if(PosLimit == 1 && PosLimitOld == 0)
        {
            OrgPrCtlBit.PosLimUp = 1;
            OrgPrCtlBit.PosLimDown = 0;

        }
        else if(PosLimit == 0 && PosLimitOld == 1)
        {
            OrgPrCtlBit.PosLimUp = 0;
            OrgPrCtlBit.PosLimDown = 1;
            if(s8HomingMethod == 18)
            {
                u16StatusWord |= 0x8000;                        //找到参考点，bit15置1
            }
        }
        else
        {
            OrgPrCtlBit.PosLimUp = 0;
            OrgPrCtlBit.PosLimDown = 0;
        }
        /*------------------------------------------------------------------------------------------*/
        /* 负限位触发信号判断                                                                       */
        /*------------------------------------------------------------------------------------------*/
        if(NegLimit == 1 && NegLimitOld == 0)
        {
            OrgPrCtlBit.NegLimUp = 1;
            OrgPrCtlBit.NegLimDown = 0;

        }
        else if(NegLimit == 0 && NegLimitOld == 1)
        {
            OrgPrCtlBit.NegLimUp = 0;
            OrgPrCtlBit.NegLimDown = 1;
            if(s8HomingMethod == 17)
            {
                u16StatusWord |= 0x8000;                        //找到参考点，bit15置1
            }
        }
        else
        {
            OrgPrCtlBit.NegLimUp = 0;
            OrgPrCtlBit.NegLimDown = 0;
        }
        
        /*------------------------------------------------------------------------------------------*/
        /* 前一拍输入信号更新                                                                       */
        /*------------------------------------------------------------------------------------------*/
        NegLimitOld = NegLimit;
        PosLimitOld = PosLimit;
        DISignOld   = DISignReach;

        
        /*------------------------------------------------------------------------------------------*/
        /* 开始进行原点回归功能的相关变量初始化处理                                                 */
        /*------------------------------------------------------------------------------------------*/
        if( EthPosV.OB6040Bit4Status == 0x01 )
        {
            /*--------------------------------------------------------------------------------------*/
            /* 上升沿     (加减速,最大速度等更新处理)                                               */
            /*--------------------------------------------------------------------------------------*/
            OrigSearch_ParamUpdate( );
            OrgControlBit.bit.OrgOkFlag = 0;
            u16StatusWord &= 0x7FFF;                            //未找到参考点，bit15清0
        }
        else if( EthPosV.OB6040Bit4Status == 0x03 )
        {
            /*--------------------------------------------------------------------------------------*/
            /* 高电平    ( 原点搜索执行处理 )                                                       */
            /*--------------------------------------------------------------------------------------*/          
            PosDelta = OrigSearch_Deal( );
            
            if( OrgStr.OrgStep == ORG_FAIL )
            {
                /*----------------------------------------------------------------------------------*/
                /* 原点回归完成失败                                                                 */
                /*----------------------------------------------------------------------------------*/
                ;
            }
        }
        else if( EthPosV.OB6040Bit4Status == 0x02 )
        {
            /*--------------------------------------------------------------------------------------*/
            /* 下降沿                                                                               */
            /*--------------------------------------------------------------------------------------*/
            ;
        }
        
        EthPosV.s32TargetPosOld = s32TargetPos;                 /* 计算上一次的偏差值               */
        EthPosV.AbsPosCmd       = s32PosActVal;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 周期同步位置模式                                                                             */
    /*----------------------------------------------------------------------------------------------*/
    else if( s8ModeofOPDis == 8 )
    {
        /*------------------------------------------------------------------------------------------*/
        EthPosV.PPStep = 0;
        /*------------------------------------------------------------------------------------------*/
        /* 脉冲指令变化值计算处理   对象字典【0x607A】 + 【0x60B0】                                 */
        /*------------------------------------------------------------------------------------------*/

        if( EthPosV.s32PositionOffsetFlag == 0 )
        {
            EthPosV.s32PositionOffsetFlag = 1;
            /*上电使能运行，首次计算根据当前位置与给定位置的增量执行位置增量控制给定*/
            PosDelta = s32TargetPos - EthPosV.AbsPosCmd;
            PosDelta += s32PositionOffset;
            EthPosV.s32PositionOffsetOld = s32PositionOffset;


        }
        else
        {
            /* 后续运算按照位置增量给定作为位置控制 */
            PosDelta = s32TargetPos - EthPosV.s32TargetPosOld;
//            PosDelta += s32PositionOffset;
//            EthPosV.s32PositionOffsetOld = s32PositionOffset;

        }
        if( EthPosV.s32PositionOffsetOld != s32PositionOffset )
        {
            /*--------------------------------------------------------------------------------------*/
            /* 位置偏置是绝对位置的偏置                                                             */
            /*--------------------------------------------------------------------------------------*/
            PosDelta += (s32PositionOffset - EthPosV.s32PositionOffsetOld );
            EthPosV.s32PositionOffsetOld = s32PositionOffset;
        }
        /*------------------------------------------------------------------------------------------*/
        /* 位置指令取反                                                                             */
        /*------------------------------------------------------------------------------------------*/
        if( u8Polarity & 0x80)
            PosDelta = -PosDelta;
        /*------------------------------------------------------------------------------------------*/
        EthPosV.s32TargetPosOld = s32TargetPos;                 /* 计算上一次的偏差值               */
        BoutV.TrqFFCOffSet = KpiTorqueLevelCal( ((LONG)s16TorqueOffset * 10), 0 );
    }
    else
    {
        /*------------------------------------------------------------------------------------------*/
        /* 非位置模式,位置指令的值需要做更新处理,否则第一次切入时存在异常                           */
        /*------------------------------------------------------------------------------------------*/
        EthPosV.s32TargetPosOld = s32TargetPos;
    }
    
    /*----------------------------------------------------------------------------------------------*/
    /* 暂停 & 快速停机                                                                              */
    /*----------------------------------------------------------------------------------------------*/
    u32SynchNum ++;
    s32SynchSum += PosDelta;
    if( u32SynchNum >= u32SynchCnt )
    {
        u32SynchNum = 0;
        s32SynchPos = (double)s32SynchSum / (float)u32SynchCnt;
        s32SynchSum = 0;
    }
    
    /*----------------------------------------------------------------------------------------------*/
    if(s8ModeofOPDis == 1 || s8ModeofOPDis == 6 || s8ModeofOPDis == 8)
    {
        PosDelta = Halt_Fast_StopMode(PosDelta);
    }
    else
    {
    
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 位置指令电子齿轮比处理                                                                             */
    /*----------------------------------------------------------------------------------------------*/
    s32PosDemandValPUU += PosDelta;                             /* 对象字典 【0x6062】                 */

#if(FLOAT_USE == 1)
    KX = FlibPcmdEgear( PosDelta, &Iprm.Ethfgear, &EthPosV.PosCmdRemain );
#else
    KX = MlibPcmdEgear( PosDelta, &Iprm.Ethfgear, &EthPosV.PosCmdRemain );
#endif


    s32PosDemandVal += KX;                                      /* 对象字典 【0x60FC】                 */

    return KX;
}


/****************************************************************************************************/
/*                                                                                                  */
/*                              EtherCAT 位置指令信息处理                                           */
/*                                                                                                  */
/****************************************************************************************************/
void EtherCATPosDeal( void )
{
    /*----------------------------------------------------------------------------------------------*/
    /* 在其他工作模式下,位置模式变量清零                                                            */
    /*----------------------------------------------------------------------------------------------*/
    EthPosV.s32TargetPosOld = s32TargetPos;
    EthPosV.AbsPosCmd = s32PosActVal;
    EthPosV.PPStep = 0;
}

/****************************************************************************************************/
/*                                                                                                  */
/*                                          探针功能                                                */
/*                                                                                                  */
/****************************************************************************************************/
typedef union   {
        struct  {
        /*------------------------------------------------------------------------------------------*/
        UINT    Latch1PosTrEn       :1;     /*  0:Latch1 上升沿锁存使能                             */
        UINT    Latch1NegTrEn       :1;     /*  1:Latch1 下降沿锁存使能                             */
        UINT    Latch2PosTrEn       :1;     /*  2:Latch2 上升沿锁存使能                             */
        UINT    Latch2NegTrEn       :1;     /*  3:Latch2 下降沿锁存使能                             */

        UINT    Latch1Source        :1;     /*  4:Latch1 信号源                                     */
        UINT    Latch1TrigMode      :1;     /*  5:Latch1 触发模式                                   */
        UINT    Latch2PosFlag       :1;     /*  8:Latch2 上升沿锁存标志                             */
        UINT    Latch2NegFlag       :1;     /*  9:Latch2 下降沿锁存标志                             */
        UINT    Latch2Source        :1;     /*  12:Latch2 信号源                                    */
        UINT    Latch2TrigMode      :1;     /*  13:Latch2 触发模式                                  */
        UINT    Reserved2           :2;     /*  14-15:                                              */
        } f;
        /*------------------------------------------------------------------------------------------*/
        USHORT  W[2];
}LATCHCONTROL;
LATCHCONTROL LatchControlV;

typedef union   {
        struct  {
        /*------------------------------------------------------------------------------------------*/
        UINT    Latch1EnFlag        :1;     /*  0:Latch1 使能状态                                   */
        UINT    Latch1PosEn         :1;     /*  1:Latch1 上升沿锁存使能                             */
        UINT    Latch1NegEn         :1;     /*  2:Latch1 下降沿锁存使能                             */
        UINT    Latch1Cnt           :4;     /*  3:Latch1 锁存计数                                   */
        UINT    Latch1Level         :1;     /*  7:Latch1 高低状态                                   */
        UINT    Latch2EnFlag        :1;     /*  8:Latch2 使能状态                                   */
        UINT    Latch2PosEn         :1;     /*  9:Latch2 上升沿锁存使能                             */
        UINT    Latch2NegEn         :1;     /*  10:Latch2 下降沿锁存使能                            */
        UINT    Latch2Cnt           :4;     /*  3:Latch2 锁存计数                                   */
        UINT    Latch2Level         :1;     /*  15:Latch2 高低状态                                  */
        } f;
        /*------------------------------------------------------------------------------------------*/
        USHORT  W;
}TROBESTATUS;
TROBESTATUS TrobeStatus;

/*--------------------------------------------------------------------------------------------------*/
typedef union   {
        struct  {
        /*------------------------------------------------------------------------------------------*/
        UINT    Latch1PKick         :4;     /*  03-00:Latch1 上升沿锁存标志                         */
        UINT    Latch1NKick         :4;     /*  07-04:Latch1 下降沿锁存标志                         */
        UINT    Latch2PKick         :4;     /*  11-08:Latch2 上升沿锁存标志                         */
        UINT    Latch2NKick         :4;     /*  15-12:Latch2 下降沿锁存标志                         */
        } f;
        /*------------------------------------------------------------------------------------------*/
        USHORT  W;
}LATCHKICK;


typedef struct
{
    UCHAR Latch1Status;                     /* Latch0 状态值                                        */
    UCHAR Latch2Status;                     /* Latch1 状态值                                        */
    UCHAR Latch1PEnStatus;
    UCHAR Latch1NEnStatus;
    UCHAR Latch2PEnStatus;
    UCHAR Latch2NEnStatus;    
    UCHAR Latch1Step;
    UCHAR Latch2Step;
    LATCHKICK Kick;
    UCHAR X3P_Status;
    UCHAR X4P_Ststus;
    /*----------------------------------------------------------------------------------------------*/
    LONG  ENCSValue;                        /* 编码器单圈值                                         */
    UCHAR ZFlag;                            /* 沿标志                                               */
    UCHAR Reserved;                         /* 预留                                                 */
    /*----------------------------------------------------------------------------------------------*/
}POSLATCHSTRUCT;
POSLATCHSTRUCT PosLatchV;
LATCHKICK LatchKick;
typedef struct
{
    UINT TouchProbe_60B8;                     /* 60B8探针功能                                       */
    UINT TouchProbe_60B9;                     /* 60B9探针状态                                       */
    LONG TouchProbe_60BA;                     /* 60BA探针1上升沿反馈位置                            */
    LONG TouchProbe_60BB;                     /* 60BB探针1下降沿反馈位置                            */
    LONG TouchProbe_60BC;                     /* 60BC探针2上升沿反馈位置                            */
    LONG TouchProbe_60BD;                     /* 60BD探针2下降沿反馈位置                            */
    LONG ActualPos_6064;                      /* 6064电机实际位置                                   */
    ULONG TouchProbe_6091_00;                 /* 6091_01电子齿轮比                                  */
    ULONG TouchProbe_6091_01;                 /* 6091_02电子齿轮比                                  */
}TOUCHREGTEMP;
TOUCHREGTEMP ThregTemp;
/****************************************************************************************************/
/*                                                                                                  */
/*                                     EtherCAT 探针变量初始化                                      */
/*                                                                                                  */
/****************************************************************************************************/
void PosLatch_Init( void )
{
    LatchControlV.W[0] = 0;
    LatchControlV.W[1] = 0;
    LatchKick.W = 0;
}


/****************************************************************************************************/
/*                                                                                                  */
/*                                          EtherCAT 探针功能                                         */
/*                                                                                                  */
/****************************************************************************************************/
void EtherCATPosLatch( void )
{

LONG lxk;
    /*----------------------------------------------------------------------------------------------*/
    if( Kprm.f.EtherCATNet == 0 && Kprm.f.CanOpenNet == 0)       /* 非EtherCAt机型则退出             */
        return;
    if(Kprm.f.EtherCATNet == 1)
    {
        ThregTemp.TouchProbe_60B8 = u16TouchProbeFun;
        ThregTemp.TouchProbe_60B9 = u16TouchProbeSts;
        ThregTemp.ActualPos_6064 = s32PosActVal;
        ThregTemp.TouchProbe_6091_00 = PositionFactor.aEntries[0];
        ThregTemp.TouchProbe_6091_01 = PositionFactor.aEntries[1];

    }
    else if(Kprm.f.CanOpenNet == 1)
    {
        ThregTemp.TouchProbe_60B8 = ODDatArr[  TouchProbe_Fun ].all;
        ThregTemp.TouchProbe_60B9 = ODDatArr[  TouchProbe_Sts ].all;
        ThregTemp.ActualPos_6064  = ODDatArr[ Position_Actual_Value_MM ].all;
        ThregTemp.TouchProbe_6091_00 = ODDatArr[  Position_Factor_Numer ].all;
        ThregTemp.TouchProbe_6091_01 = ODDatArr[  Position_Factor_Divisor ].all;
    }
    /*----------------------------------------------------------------------------------------------*/
    /*  探针——1 控制状态          对象字典 【0x60B8】                                               */
    /*----------------------------------------------------------------------------------------------*/
    PosLatchV.Latch1Status = PosLatchV.Latch1Status << 1;
    PosLatchV.Latch1Status &= 0x03;
    if(( ThregTemp.TouchProbe_60B8 & 0x0001 ) == 0x0001)
    {
        PosLatchV.Latch1Status |= 0x01;
        PosLatchV.Latch1Status &= 0x03;
    }
    /*----------------------------------------------------------------------------------------------*/
    PosLatchV.Latch2Status = PosLatchV.Latch2Status << 1;
    PosLatchV.Latch2Status &= 0x03;
    if(( ThregTemp.TouchProbe_60B8 & 0x0100 ) == 0x0100)
    {
        PosLatchV.Latch2Status |= 0x01;
        PosLatchV.Latch2Status &= 0x03;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 读取Latch1 和 Latch2 信号源状态                                                              */
    /*----------------------------------------------------------------------------------------------*/
    PosLatchV.X3P_Status = PosLatchV.X3P_Status << 1;
    PosLatchV.X3P_Status &= 0x0003;
    if( X3_Status == 1 )
    {
        PosLatchV.X3P_Status |= 0x0001;
        PosLatchV.X3P_Status &= 0x0003;
    }

    PosLatchV.X4P_Ststus = PosLatchV.X4P_Ststus << 1;
    PosLatchV.X4P_Ststus &= 0x0003;
    if( X4_Status == 1 )
    {
        PosLatchV.X4P_Ststus |= 0x0001;
        PosLatchV.X4P_Ststus &= 0x0003;
    }

    if( PosLatchV.X3P_Status == 2 )
    {
        LatchKick.f.Latch1PKick ++;
    }
    else if( PosLatchV.X3P_Status == 1)
    {
        LatchKick.f.Latch1NKick ++;
    }
    else
    {;}

    if( PosLatchV.X4P_Ststus == 2 )
    {
        LatchKick.f.Latch2PKick ++;
    }
    else if( PosLatchV.X4P_Ststus == 1)
    {
        LatchKick.f.Latch2NKick ++;
    }
    else
    {;}


    /*----------------------------------------------------------------------------------------------*/
    /* 编码器Z信号源                                                                                */
    /*----------------------------------------------------------------------------------------------*/
    lxk = (LONG)RoutV.ABSEncSValue - PosLatchV.ENCSValue;
    
    if( lxk > (MencP.PulseNo >> 2) )
    {
        lxk = MencP.PulseNo - RoutV.ABSEncSValue;
        PosLatchV.ZFlag = 1;
    }
    else if( lxk < -(MencP.PulseNo >> 2))
    {
        lxk = RoutV.ABSEncSValue;
        lxk = -lxk;
        PosLatchV.ZFlag = 1;
    }
    else
    {
        PosLatchV.ZFlag = 0;
    }
    
    if( PosLatchV.ZFlag == 1 )
    {
         /*-----------------------------------------------------------------------------------------*/
         /* 与 Pn204/Pn206 相关联                                                                   */
         /*-----------------------------------------------------------------------------------------*/
        //lxk = (LONG)((double)lxk * Iprm.Egear.fa / Iprm.Egear.fb);
        /*------------------------------------------------------------------------------------------*/
        /* 与 6091 相关联                                                                           */
        /*------------------------------------------------------------------------------------------*/
        //lxk  = (LONG)((double)lxk * (float)PositionFactor.aEntries[1]  / (float)PositionFactor.aEntries[0]);


        lxk = lxk * Iprm.Egear.adivb * Iprm.Ethfgear.adivb;     //20230101

    }
    
    PosLatchV.ENCSValue = RoutV.ABSEncSValue;
    /*----------------------------------------------------------------------------------------------*/
    if( ThregTemp.TouchProbe_60B8 & 0x002 )
    {
        LatchControlV.f.Latch1TrigMode = 1;                         /* 连续触发                     */
    }
    else
    {
        LatchControlV.f.Latch1TrigMode = 0;                         /* 单次触发                     */

    }
    /*----------------------------------------------------------------------------------------------*/
    if( (ThregTemp.TouchProbe_60B8 & 0x0004) == 0x0004 )           /* 触发源选择                    */
    {
        LatchControlV.f.Latch1Source = 1;                          /* Z 信号                        */
    }
    else
    {
        LatchControlV.f.Latch1Source = 0;                          /* X 信号                        */
    }
    /*----------------------------------------------------------------------------------------------*/
    if( PosLatchV.Latch1Status == 0x01 )                            /* Bit0 的上升沿到达            */
    {
        /*------------------------------------------------------------------------------------------*/
        TrobeStatus.f.Latch1EnFlag = 1;                             /* Latch1 使能                  */
        TrobeStatus.f.Latch1PosEn = 0;                              /* 上升沿触发锁存               */
        TrobeStatus.f.Latch1NegEn = 0;                              /* 下降沿触发锁存               */
        PosLatchV.Latch1PEnStatus = 0;
    }
    else if( PosLatchV.Latch1Status == 0x00 )
    {
        PosLatchV.Latch1NEnStatus      = 0;
        LatchControlV.f.Latch1NegTrEn  = 0;    
        PosLatchV.Latch1PEnStatus      = 0;
        LatchControlV.f.Latch1PosTrEn  = 0;  
        TrobeStatus.f.Latch1EnFlag     = 0;
    }
    else if( PosLatchV.Latch1Status == 0x03 )
    {
        PosLatchV.Latch1PEnStatus = PosLatchV.Latch1PEnStatus << 1;
        PosLatchV.Latch1PEnStatus &= 0x03;
        if( ThregTemp.TouchProbe_60B8 & 0x0010 )
        {
            PosLatchV.Latch1PEnStatus |= 0x01;
            PosLatchV.Latch1PEnStatus &= 0x03;
        }
        /*------------------------------------------------------------------------------------------*/
        if( PosLatchV.Latch1PEnStatus == 0x01 )
        {
            LatchControlV.f.Latch1PosTrEn = 1;                      /* 上升沿开启                   */
        }
        else if( PosLatchV.Latch1PEnStatus == 0x00 )
        {
            LatchControlV.f.Latch1PosTrEn = 0;
        }
        /*------------------------------------------------------------------------------------------*/
        if( LatchControlV.f.Latch1PosTrEn == 1 )
        {
          
            /*----------------------------------------------------------------------------------*/
            /*                              Latch1 上升沿信号锁存                               */
            /*----------------------------------------------------------------------------------*/
            if( LatchControlV.f.Latch1Source == 0 )
            {
                if( PosLatchV.Kick.f.Latch1NKick != LatchKick.f.Latch1NKick )
                {
                    ThregTemp.TouchProbe_60BA = ThregTemp.ActualPos_6064;    /* 对象 【0x60BA】     */
                    TrobeStatus.f.Latch1PosEn = 1;                      /* 上升沿触发锁存           */
                    TrobeStatus.f.Latch1Cnt ++;
                    /*--------------------------------------------------------------------------*/
                    if( LatchControlV.f.Latch1TrigMode )
                    {
                        LatchControlV.f.Latch1PosTrEn = 1;          /* 连续触发                 */
                    }
                    else
                    {
                        LatchControlV.f.Latch1PosTrEn = 0;          /* 单次触发                 */
                    }
                }
            }
            else
            {        
                if( PosLatchV.ZFlag == 1)
                {
                    ThregTemp.TouchProbe_60BA = ThregTemp.ActualPos_6064 + lxk;  /* 对象 【0x60BA】 */
                    TrobeStatus.f.Latch1PosEn = 1;                      /* 上升沿触发锁存           */
                    TrobeStatus.f.Latch1Cnt ++;
                    /*--------------------------------------------------------------------------*/
                    if( LatchControlV.f.Latch1TrigMode )
                    {
                        LatchControlV.f.Latch1PosTrEn = 1;          /* 连续触发                 */
                    }
                    else
                    {
                        LatchControlV.f.Latch1PosTrEn = 0;          /* 单次触发                 */
                    }
                }                
            }
        }
        /*------------------------------------------------------------------------------------------*/
        PosLatchV.Latch1NEnStatus = PosLatchV.Latch1NEnStatus << 1;
        PosLatchV.Latch1NEnStatus &= 0x03;
        if( ThregTemp.TouchProbe_60B8 & 0x0020 )
        {
            PosLatchV.Latch1NEnStatus |= 0x01;
            PosLatchV.Latch1NEnStatus &= 0x03;
        }
        /*------------------------------------------------------------------------------------------*/
        if( PosLatchV.Latch1NEnStatus == 0x01 )
        {
            LatchControlV.f.Latch1NegTrEn = 1;              /* 上升沿开启                   */
        }
        else if( PosLatchV.Latch1NEnStatus == 0x00 )
        {
            LatchControlV.f.Latch1NegTrEn = 0;
        }
        /*----------------------------------------------------------------------------------*/
        if( LatchControlV.f.Latch1NegTrEn == 1 )
        {
            /*----------------------------------------------------------------------------------*/
            /*                              Latch1 下降沿信号锁存                               */
            /*----------------------------------------------------------------------------------*/
            if( LatchControlV.f.Latch1Source == 0 )
            {
                if( PosLatchV.Kick.f.Latch1PKick != LatchKick.f.Latch1PKick )
                {
                    ThregTemp.TouchProbe_60BB = ThregTemp.ActualPos_6064;  /* 对象 【0x60BB】       */
                    TrobeStatus.f.Latch1NegEn = 1;                      /* 下降沿触发锁存           */
                    TrobeStatus.f.Latch1Cnt ++;
                    /*--------------------------------------------------------------------------*/
                    if( LatchControlV.f.Latch1TrigMode )
                    {
                        LatchControlV.f.Latch1NegTrEn = 1;          /* 连续触发                 */
                        PosLatchV.Kick.f.Latch1NKick = LatchKick.f.Latch1NKick;
                    }
                    else
                    {
                        LatchControlV.f.Latch1NegTrEn = 0;          /* 单次触发                 */
                    }                      
                }
            }
            else
            {
                if( PosLatchV.ZFlag == 1 )
                {
                    ThregTemp.TouchProbe_60BB = ThregTemp.ActualPos_6064 + lxk;  /* 对象 【0x60BB】 */
                    TrobeStatus.f.Latch1NegEn = 1;                  /* 下降沿触发锁存               */
                    TrobeStatus.f.Latch1Cnt ++;
                    /*------------------------------------------------------------------------------*/
                    if( LatchControlV.f.Latch1TrigMode )
                    {
                        LatchControlV.f.Latch1NegTrEn = 1;          /* 连续触发                     */
                    }
                    else
                    {
                        LatchControlV.f.Latch1NegTrEn = 0;          /* 单次触发                     */
                    }                      
                }                
            }
                /*----------------------------------------------------------------------------------*/
        }
    }
    else
    {
        TrobeStatus.f.Latch1EnFlag = 0;                             /* Latch1 未使能                */
        TrobeStatus.f.Latch1PosEn = 0;                              /* 上升沿触发锁存               */
        TrobeStatus.f.Latch1NegEn = 0;                              /* 下降沿触发锁存               */
    }
    
    /*----------------------------------------------------------------------------------------------*/
    /*  探针 2 的处理步骤                                                                           */
    /*----------------------------------------------------------------------------------------------*/    
    if( ThregTemp.TouchProbe_60B8 & 0x0200 )
    {
        LatchControlV.f.Latch2TrigMode = 1;                         /* 连续触发                     */
    }
    else
    {
        LatchControlV.f.Latch2TrigMode = 0;                         /* 单次触发                     */
    }
    /*----------------------------------------------------------------------------------------------*/
    if( ThregTemp.TouchProbe_60B8 & 0x0400 )                        /* 触发源选择                   */
    {
        LatchControlV.f.Latch2Source = 1;                           /* Z信号                        */
    }
    else
    {
        LatchControlV.f.Latch2Source = 0;                           /* X信号                        */
    }
    /*----------------------------------------------------------------------------------------------*/
    if(PosLatchV.Latch2Status == 0x01)
    {
        TrobeStatus.f.Latch2EnFlag = 1;                             /* Latch1 未使能                */
        TrobeStatus.f.Latch2PosEn = 0;                              /* 上升沿触发锁存               */
        TrobeStatus.f.Latch2NegEn = 0;                              /* 下降沿触发锁存               */
    }
    else if( PosLatchV.Latch2Status == 0x00 )
    {
        PosLatchV.Latch2PEnStatus     = 0;
        LatchControlV.f.Latch2PosTrEn = 0;
        PosLatchV.Latch2NEnStatus     = 0;
        LatchControlV.f.Latch2NegTrEn = 0;
        TrobeStatus.f.Latch2EnFlag    = 0;
        TrobeStatus.f.Latch2PosEn     = 0;
        TrobeStatus.f.Latch2NegEn     = 0;
    }
    else if( PosLatchV.Latch2Status == 0x03 )                       /* Bit0 的上升沿到达            */
    {
        PosLatchV.Latch2PEnStatus = PosLatchV.Latch2PEnStatus << 1;
        PosLatchV.Latch2PEnStatus &= 0x03;
        if( ThregTemp.TouchProbe_60B8 & 0x1000 )
        {
            PosLatchV.Latch2PEnStatus |= 0x01;
            PosLatchV.Latch2PEnStatus &= 0x03;
        }
        /*------------------------------------------------------------------------------------------*/
        if( PosLatchV.Latch2PEnStatus == 0x01 )
        {
            LatchControlV.f.Latch2PosTrEn = 1;                      /* 上升沿开启                   */
        }
        else if( PosLatchV.Latch2PEnStatus == 0x00 )
        {
            LatchControlV.f.Latch2PosTrEn = 0;
        }
        /*------------------------------------------------------------------------------------------*/
        if( LatchControlV.f.Latch2PosTrEn == 1 )
        {      
            /*--------------------------------------------------------------------------------------*/
            /*                              Latch2 上升沿信号锁存                                   */
            /*--------------------------------------------------------------------------------------*/
            if( LatchControlV.f.Latch2Source == 0 )
            {
                if( PosLatchV.Kick.f.Latch2NKick != LatchKick.f.Latch2NKick )
                {
                    ThregTemp.TouchProbe_60BC = ThregTemp.ActualPos_6064;  /* 对象 【0x60BA】       */
                    TrobeStatus.f.Latch2PosEn = 1;                      /* 上升沿触发锁存           */
                    TrobeStatus.f.Latch2Cnt ++;
                    /*--------------------------------------------------------------------------*/
                    if( LatchControlV.f.Latch2TrigMode )
                    {
                        LatchControlV.f.Latch2PosTrEn = 1;          /* 连续触发                 */
                    }
                    else
                    {
                        LatchControlV.f.Latch2PosTrEn = 0;          /* 单次触发                 */
                    }
                }
            }
            else
            {
                if( PosLatchV.ZFlag == 1 )
                {
                    ThregTemp.TouchProbe_60BC = ThregTemp.ActualPos_6064 + lxk; /* 对象 【0x60BA】  */
                    TrobeStatus.f.Latch2PosEn = 1;                      /* 上升沿触发锁存           */
                    TrobeStatus.f.Latch2Cnt ++;
                    /*--------------------------------------------------------------------------*/
                    if( LatchControlV.f.Latch2TrigMode )
                    {
                        LatchControlV.f.Latch2PosTrEn = 1;          /* 连续触发                 */
                    }
                    else
                    {
                        LatchControlV.f.Latch2PosTrEn = 0;          /* 单次触发                 */
                    }
                }                
            }
        }
        else
        {
            ;
        }

        PosLatchV.Latch2NEnStatus = PosLatchV.Latch2NEnStatus << 1;
        PosLatchV.Latch2NEnStatus &= 0x03;
        if( ThregTemp.TouchProbe_60B8 & 0x2000 )
        {
            PosLatchV.Latch2NEnStatus |= 0x01;
            PosLatchV.Latch2NEnStatus &= 0x03;
        }
        /*------------------------------------------------------------------------------------------*/
        if( PosLatchV.Latch2NEnStatus == 0x01 )
        {
            LatchControlV.f.Latch2NegTrEn = 1;                      /* 上升沿开启                   */
        }
        else if( PosLatchV.Latch2NEnStatus == 0x01 )
        {
            LatchControlV.f.Latch2NegTrEn = 0;
        }
        
        if( LatchControlV.f.Latch2NegTrEn == 1 )
        {
            /*----------------------------------------------------------------------------------*/
            /*                              Latch1 下降沿信号锁存                               */
            /*----------------------------------------------------------------------------------*/
            if( LatchControlV.f.Latch2Source == 0 )
            {
                if( PosLatchV.Kick.f.Latch2PKick != LatchKick.f.Latch2PKick )
                {
                    ThregTemp.TouchProbe_60BD = ThregTemp.ActualPos_6064;  /* 对象 【0x60BB】       */
                    TrobeStatus.f.Latch2NegEn = 1;                      /* 下降沿触发锁存           */
                    TrobeStatus.f.Latch2Cnt ++;
                    /*--------------------------------------------------------------------------*/
                    if( LatchControlV.f.Latch2TrigMode )
                    {
                        LatchControlV.f.Latch2NegTrEn = 1;          /* 连续触发                 */
                    }
                    else
                    {
                        LatchControlV.f.Latch2NegTrEn = 0;          /* 单次触发                 */
                    }
                }
            }
            else
            {
                if( PosLatchV.ZFlag == 1 )
                {
                    ThregTemp.TouchProbe_60BD = ThregTemp.ActualPos_6064 + lxk;   /* 对象 【0x60BB】*/
                    TrobeStatus.f.Latch2NegEn = 1;                      /* 下降沿触发锁存           */
                    TrobeStatus.f.Latch2Cnt ++;
                    /*--------------------------------------------------------------------------*/
                    if( LatchControlV.f.Latch2TrigMode )
                    {
                        LatchControlV.f.Latch2NegTrEn = 1;          /* 连续触发                 */
                    }
                    else
                    {
                        LatchControlV.f.Latch2NegTrEn = 0;          /* 单次触发                 */
                    }
                }                
            }
        }
    }

    /*----------------------------------------------------------------------------------------------*/
    PosLatchV.Kick.f.Latch1PKick = LatchKick.f.Latch1PKick;
    PosLatchV.Kick.f.Latch1NKick = LatchKick.f.Latch1NKick;
    PosLatchV.Kick.f.Latch2PKick = LatchKick.f.Latch2PKick;
    PosLatchV.Kick.f.Latch2NKick = LatchKick.f.Latch2NKick;
    /*----------------------------------------------------------------------------------------------*/
    TrobeStatus.f.Latch1Level = X3_Status;      //20221230
    TrobeStatus.f.Latch2Level = X4_Status;      //20221230
    /*----------------------------------------------------------------------------------------------*/
    PosLatchV.Kick.W = LatchKick.W;

    if(Kprm.f.EtherCATNet == 1)
    {
        u16TouchProbeSts = TrobeStatus.W;
        s32TouchProbePos1PVal = ThregTemp.TouchProbe_60BA;
        s32TouchProbePos1NVal = ThregTemp.TouchProbe_60BB;
        s32TouchProbePos2PVal = ThregTemp.TouchProbe_60BC;
        s32TouchProbePos2NVal = ThregTemp.TouchProbe_60BD;
    }
    else if(Kprm.f.CanOpenNet == 1)
    {
        ODDatArr[  TouchProbe_Sts ].all = TrobeStatus.W;               // 60B9
        ODDatArr[  TouchProbePos1_PVal ].all = ThregTemp.TouchProbe_60BA;
        ODDatArr[  TouchProbePos1_NVal ].all = ThregTemp.TouchProbe_60BB;
        ODDatArr[  TouchProbePos2_PVal ].all = ThregTemp.TouchProbe_60BC;
        ODDatArr[  TouchProbePos2_NVal ].all = ThregTemp.TouchProbe_60BD;
    }
    PosLatchV.ZFlag = 0;
}
