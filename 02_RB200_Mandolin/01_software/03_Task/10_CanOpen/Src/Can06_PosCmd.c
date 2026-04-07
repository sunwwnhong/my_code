/****************************************************************************************************/
/*                                                                                                  */
/*                           Copyright (C) ××× Electric Corporation                              */
/*                                  版权所有 · All right Reserved                                  */
/*                                          2019 ~                                                  */
/****************************************************************************************************/
/*                                                                                                  */
/*                                                                                                  */
/*      Can06_PosCmd.c : CanOpen  402协议-位置指令处理                                              */
/*                                                                                                  */
/*                                                                                                  */
/****************************************************************************************************/
#include "Main.h"
#include "CanOpen_OrigSearch.h"


ULONG CanOpenSyncTimeus = 0;
/*--------------------------------------------------------------------------------------------------*/
UCHAR CanOpen_ControlMode = 0;              /* 0:速度;1:位置;2:扭矩;7:力位混合控制                         */
/*--------------------------------------------------------------------------------------------------*/
CanOpen_POS CanPosV;

CanOpen_CONTROL ContSMachine;

CanOpen_POSJogOrg CanPOSJOGV;                          /* 手自动切换    @瑞博特20240311             */

typedef struct
{
    LLONG   PosRem;                             // 余数计算
    LLONG   PosRemSum;                          // 余数累加
    LLONG   PosInt;                             // 余数取整

}REMCALCULATE;
REMCALCULATE  Rem_Calc;
//--------------------------------------------------------------------------------------------------
//Function_Name: MlibCalc_RemAdd()
//Description: 余数累加处理
//Parameter: InPutDen为输入待处理数据
//           DiVRem为取余除数；
//           RemTm为计算取余的周期，一般为DiVRem的整数倍
//--------------------------------------------------------------------------------------------------
LLONG MlibCalc_RemAdd( LLONG InPutDen, LLONG DiVRem, LLONG RemTm)
{
    LLONG Datatemp = 0;
    LLONG Data_Int = 0;
    Rem_Calc.PosRem = InPutDen % DiVRem;
    Rem_Calc.PosRemSum = Rem_Calc.PosRemSum + Rem_Calc.PosRem;

    if(InPutDen >= 0)
    {
        if(Rem_Calc.PosRemSum >= RemTm)
        {
            Datatemp = Rem_Calc.PosRemSum /DiVRem;
            Rem_Calc.PosRemSum = Rem_Calc.PosRemSum % DiVRem;
        }
    }
    else
    {
        if(Rem_Calc.PosRemSum <= -RemTm)
        {
            Datatemp = Rem_Calc.PosRemSum / DiVRem;
            Rem_Calc.PosRemSum = Rem_Calc.PosRemSum % DiVRem;
        }
    }
    Data_Int = (InPutDen / DiVRem) + Datatemp;
    return (Data_Int);

}
/****************************************************************************************************/
/*Description  :暂停功能减速基值更新                                                                */
/*  位置轮廓模式                                                                                    */
/*  周期同步位置模式                                                                                */
/*  回零模式                                                                                        */
/****************************************************************************************************/
LONG Profile_Dec_6084 = 0;
LONG QuickStop_Dec_6085 = 0;
LONG HomE_Acc_609A = 0;
void HaltParameter_Update( void )
{
    /*----------------------------------------------------------------------------------------------*/
    if( Profile_Dec_6084 != ODDatArr[Profile_Deceleration].all )
    {
        Profile_Dec_6084 = ODDatArr[Profile_Deceleration].all;
        ContSMachine.DecBase6084_Q15    = (INT64)((double)Profile_Dec_6084 * 8.0f / 15625.0f);
        ContSMachine.DecSBase6084_Q15   = (INT64)((double)Profile_Dec_6084 * 512.0f / 125.0f);
    }
    /*----------------------------------------------------------------------------------------------*/
    if( QuickStop_Dec_6085 != ODDatArr[Quick_Stop_Deceleration].all )
    {
        QuickStop_Dec_6085 = ODDatArr[Quick_Stop_Deceleration].all;
        ContSMachine.DecBase6085_Q15    = (INT64)((double)QuickStop_Dec_6085 * 8.0f / 15625.0f);
        ContSMachine.DecSBase6085_Q15   = (INT64)((double)QuickStop_Dec_6085 * 512.0f / 125.0f);
    }
    /*----------------------------------------------------------------------------------------------*/
    if( HomE_Acc_609A != ODDatArr[Homing_Acceleration].all )
    {
        HomE_Acc_609A = ODDatArr[Homing_Acceleration].all;
        ContSMachine.DecBase609A_Q15 = (INT64)((double)HomE_Acc_609A * 8.0f / 15625.0f);
    }
}
/****************************************************************************************************/
/*Function_Name:CanOpen_PosCmdDeal                                                                 */
/*Description  :位置指令源处理                                                                      */
/*  位置轮廓模式                                                                                    */
/*  周期同步位置模式                                                                                */
/*  回零模式                                                                                        */
/****************************************************************************************************/
ULONG InterPeriod = 16;                     //插补位置周期
ULONG PulseTmp    = 0;
LONG  PosDeltaOld = 0;                      /* 开环位置切闭环位置防止速度抖动记录上一拍脉冲数20240228 */
LONG CanOpen_PosCmd( void )
{
    LONG PosDelta = 0;
    LONG PosTmp = 0;
    LONG PosActDelta = 0;                   /*   记录相对位置与绝对位置切换后一个周期内电机走过的脉冲数  */
    LONG KX;
    /*----------------------------------------------------------------------------------------------*/
    /* 伺服 Off 时相关数据清零                                                                      */
    /*----------------------------------------------------------------------------------------------*/
    if( !BinV.f.BaseEnable || (CinV.f.Sv.EmcyStop && CAN_EXFUNC0_12_DIS ))
    { 
        if(!BinV.f.BaseEnable)
        {
            CanPosV.PPStep = 0;
        }
        CanPOSJOGV.AutoJogStep = 0;
        //  解决断使能但一直为插补模式，电机位置改变，60C1=6064时电机飞车问题 @20240619
        CanIntMod.IntorPosOld = ODDatArr[Position_Actual_Value_MM].all;
        CanPosV.PosSpdCmd = 0;
        PosCurGenerator_Clear();
        CanPosV.s32TargetPosOld = ODDatArr[Targe_Position_MM].all ;   /*  更新旧值                  */
        CanPosV.AbsPosCmd = ODDatArr[Position_Actual_Value_MM].all;
        /*----------------------------------------------------------------------------------------------*/
        /* 解决紧急停机，电机运行不正常问题 @20240520                                                     */
        /*----------------------------------------------------------------------------------------------*/
        if(CinV.f.Sv.EmcyStop && CanPosV.PPStep != 0 && PosCurvV.TargetReach == 0)
        {
            CanPosV.PPStep = 1;
        }
        return 0;
    }
     /*-----------------------------------------------------------------------------------------------*/
     /* 手自动切换时对轮廓位置进行复位                 @瑞博特非标功能20240311                       */
     /*----------------------------------------------------------------------------------------------*/
     if(CAN_EXFUNC0_7_EN)
     {
         if(CanPOSJOGV.ManualAutoModOld !=  CinV.f.Sv.ManualAutoMod)
         {
             PosCurGenerator_Clear();
         }
     }
    /*---------------------------------------------------------------------------------------------*/
      /* 在开启模式切换功能并且断使能时，输出脉冲量为0   @瑞博特非标功能20240311                      */
      /*--------------------------------------------------------------------------- ------------------*/
      if((CinV.f.Sv.ManualAutoMod == 1) && CAN_EXFUNC0_7_EN)
      {
          /*------------------------------------------------------------------------------------------*/
          /* 在正向点动与反向点动同时生效时电机输出脉冲为0                                            */
          /*------------------------------------------------------------------------------------------*/
          if((CinV.f.Sv.JOGP == TRUE)  && (CinV.f.Sv.JOGN == TRUE  ))
          {
              PosDelta = 0;
              //CanPosV.PPStep = 0;
              CanPOSJOGV.AutoJogStep = 0;
          }
          /*------------------------------------------------------------------------------------------*/
          /* 手动模式下端子正向点动                                                                   */
          /*------------------------------------------------------------------------------------------*/
          else if( CinV.f.Sv.JOGP == TRUE )
          {
              AutoJOGSpd();
              //CanPosV.PPStep = 0;
              CanPOSJOGV.AutoJogStep = 0;
              if(CinV.f.Sv.Pot == 1)
              {
                  CanPOSJOGV.SpdCmd = 0;
              }
            PosDelta = MlibCalc_RemAdd(CanPOSJOGV.SpdCmd, 32768, 65536);
          }
          /*------------------------------------------------------------------------------------------*/
          /* 手动模式下端子负向点动                                                                   */
          /*------------------------------------------------------------------------------------------*/
          else if( CinV.f.Sv.JOGN == TRUE)
          {
              AutoJOGSpd();
              //CanPosV.PPStep = 0;
              CanPOSJOGV.AutoJogStep = 0;
              if(CinV.f.Sv.Not == 1)
              {
                  CanPOSJOGV.SpdCmd = 0;
              }
            PosDelta = MlibCalc_RemAdd(CanPOSJOGV.SpdCmd, 32768, 65536);
          }
          /*------------------------------------------------------------------------------------------*/
          /* 负向点动松开执行回原点（绝对位置0）,并且点动端子没有运行至限位     @20240311             */
          /*------------------------------------------------------------------------------------------*/
          else if((CinV.f.Sv.Pot == 0 || CinV.f.Sv.Not == 0) && (CAN_EXFUNC1_1_DIS))
          {
              switch(CanPOSJOGV.AutoJogStep)
              {
              case 0:
                  PosCurGenerator_Clear();
                  PosCurvV.SpdOutQ15 = CanPOSJOGV.SpdCmd;               /*  点动与回零的速度衔接      */
                  CanPosV.AbsPosCmd = ODDatArr[Position_Actual_Value_MM].all + \
                                      ODDatArr[Follow_Error_Actual_Value].all;
                  PosCurvP.TargetPos = - CanPosV.AbsPosCmd;
                  CanOpenPosJOGUpdate();
                  CanPOSJOGV.AutoJogStep = 1;
              break;
              case 1:
                  PosCurveGenerator_Deal( );
                  PosDelta = PosCurvV.PosCmdOut;
                  //    CanPosV.PPStep = 0;                       @20240313
              break;
              default:
              break;
              }
              CanPOSJOGV.SpdCmd = PosCurvV.SpdOutQ15;
          }
       CanPosV.PPStep = 0;
      /*----------------------------------------------------------------------------------------------*/
      /* 位置指令电子齿轮比处理                                                                       */
      /*----------------------------------------------------------------------------------------------*/
      ODDatArr[Position_Demand_Value_MM].all += PosDelta ;                 /* 对象字典 【0x6062】     */
      KX = MlibPcmdEgear( PosDelta, &Iprm.CANgear, &CanPosV.PosCmdRemain );
      ODDatArr[Postion_Demand_Value].all += KX;                            /* 对象字典 【0x60FC】     */
      CanPOSJOGV.ManualAutoModOld = CinV.f.Sv.ManualAutoMod;
      return KX;
      }


    /*----------------------------------------------------------------------------------------------*/
    if( ODDatArr[Operation_Mode_Display].all == 3 || ODDatArr[Operation_Mode_Display].all == 4 )
    {
        return PulseTmp;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 对象字典【0x6040】 Bit4 控制位的沿信号检测处理                                               */
    /*----------------------------------------------------------------------------------------------*/
    if(BinV.f.BaseEnable | CoutV.f.Sv.Ot)
    {
        CanPosV.OB6040Bit4Rising_edge = CanPosV.OB6040Bit4Rising_edge << 1;
        CanPosV.OB6040Bit4Rising_edge &= 0x03;
        if( ( ODDatArr[Control_Word].all & 0x0010 )  == 0x0010)
        {
            CanPosV.OB6040Bit4Rising_edge |= 0x01;
        }
    }
    else
    {
        CanPosV.OB6040Bit4Rising_edge = 0x00 ;
    }
     /*----------------------------------------------------------------------------------------------*/
    /* 暂停 & 快速停机 功能检测                                                                     */
    /*----------------------------------------------------------------------------------------------*/
    ContSMachine.HaltStatus = ( ContSMachine.HaltStatus << 1 ) & 0x03;
    
    /*----------------------------------------------------------------------------------------------*/
    /* 暂停状态检测                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
    if( ( ODDatArr[Control_Word].all & 0x0100 ) == 0x0100 )
    {
        ContSMachine.HaltStatus |= 0x01;
    }
      
    /*----------------------------------------------------------------------------------------------*/
    if( ContSMachine.HaltStatus == 0x01 )                       /* 第一次进入                       */
    {
        /*------------------------------------------------------------------------------------------*/
        if( ODDatArr[Operation_Mode_Display].all == 6 )
        {
            ContSMachine.SpdOutQ15 = OrgStr.OrgCmdOutQ15;
        }
        else if( ODDatArr[Operation_Mode_Display].all == 7 )
        {
            ContSMachine.SpdOutQ15 = ContSMachine.IntorPosTmpQ15;
        }
        else
        {
            ContSMachine.SpdOutQ15 = PosCurvV.SpdOutQ15;        /* 当前输出速度保存                 */
        }
        /*------------------------------------------------------------------------------------------*/
        PosCurGenerator_Clear();                                /* 轮廓位置复位                     */
        OrgStr = OrgStrDefault;                                 /* 原点回归复位                     */
        
        OrgControlBit.bit.OrgDone = 1;
        /*------------------------------------------------------------------------------------------*/
        /* 减速度选择                                                                               */
        /*------------------------------------------------------------------------------------------*/
        if( ODDatArr[ Halt_option_code ].word.LowWord == 1 )
        {
            if( ODDatArr[Operation_Mode_Display].all == 6 )
            {
                ContSMachine.DecBase_Q15 = ContSMachine.DecBase609A_Q15;
            }
            else
            {
                ContSMachine.DecBase_Q15 = ContSMachine.DecBase6084_Q15;
            }
        }
        else if( ODDatArr[ Halt_option_code ].word.LowWord == 2 )
        {
            ContSMachine.DecBase_Q15 = ContSMachine.DecBase6085_Q15;
        }
        else
        {
            ContSMachine.DecBase_Q15 = ContSMachine.SpdOutQ15;
        }
    }
    else if( ContSMachine.HaltStatus == 0x03 )                  /* 已经进入                         */
    {
        PDO_Var.SYNCUpFlag1 = 0;
        /*------------------------------------------------------------------------------------------*/
        /* 减速处理                                                                                 */
        /*------------------------------------------------------------------------------------------*/
        if( ContSMachine.SpdOutQ15 == 0 )                               /* 减速完成,速度 == 0       */
        {
            PosDelta = 0;
        }
        else if( ContSMachine.SpdOutQ15 > 0 )                           /* 速度大于零               */
        {
            if( ContSMachine.SpdOutQ15 >= ContSMachine.DecBase_Q15 )
            {
                ContSMachine.SpdOutQ15 -= ContSMachine.DecBase_Q15;
                PosDelta = ContSMachine.SpdOutQ15 >> 15;
            }
            else
            {
                PosDelta = ContSMachine.SpdOutQ15 >> 15;
                ContSMachine.SpdOutQ15 = 0;
            }
        }
        else                                                            /* 速度小于零               */
        {
            if( ContSMachine.SpdOutQ15 <= -ContSMachine.DecBase_Q15 )
            {
                ContSMachine.SpdOutQ15 += ContSMachine.DecBase_Q15;
                PosDelta = ContSMachine.SpdOutQ15 >> 15;
            }
            else
            {
                PosDelta = ContSMachine.SpdOutQ15 >> 15;
                ContSMachine.SpdOutQ15 = 0;
            }        
        }
    }
    else if( ContSMachine.HaltStatus == 0x02 )
    {
        CanPosV.s32TargetPosOld = ODDatArr[Targe_Position_MM].all;      /*  更新旧值                */
        CanPosV.AbsPosCmd = ODDatArr[Position_Actual_Value_MM].all;

    }
    
    /*----------------------------------------------------------------------------------------------*/
    /* 快速停机检测                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
    ContSMachine.FastStatus = ( ContSMachine.FastStatus << 1 ) & 0x03;
    if( ( ODDatArr[Control_Word].all & 0x0004 ) == 0x0000 )
    {
        ContSMachine.FastStatus |= 0x01;
    }
    
    /*----------------------------------------------------------------------------------------------*/
    if( ContSMachine.FastStatus == 0x01 )                       /* 第一次进入                       */
    {
        /*------------------------------------------------------------------------------------------*/
        if( ODDatArr[Operation_Mode_Display].all == 6 )
        {
            ContSMachine.SpdOutQ15 = OrgStr.OrgCmdOutQ15;
        }
        else if( ODDatArr[Operation_Mode_Display].all == 7 )
        {
            ContSMachine.SpdOutQ15 = ContSMachine.IntorPosTmpQ15;
        }
        else
        {
            ContSMachine.SpdOutQ15 = PosCurvV.SpdOutQ15;        /* 当前输出速度保存                 */
        }
        /*------------------------------------------------------------------------------------------*/
        PosCurGenerator_Clear();                                /* 轮廓位置复位                     */
        OrgStr = OrgStrDefault;                                 /* 原点回归复位                     */
        
        OrgControlBit.bit.OrgDone = 1;
        /*------------------------------------------------------------------------------------------*/
        /* 减速度选择                                                                               */
        /*------------------------------------------------------------------------------------------*/
        if( ODDatArr[ Quick_stop_option_code ].word.LowWord == 0 )
        {
            /*--------------------------------------------------------------------------------------*/
            /* 模式 0:自由滑行                                                                      */
            /*--------------------------------------------------------------------------------------*/
            if((CiA402StatusMachine == 1) && (QuickStop_flag == 1))
            {
                CanOpen_ControlStatus = 2;    //解决012快速停机CIA402状态机未进入case6,直接断使能
            }
            else if(CiA402StatusMachine == 0)
            {
                CanOpen_ControlStatus = 2;
            }
        }
        else if( ODDatArr[ Quick_stop_option_code ].word.LowWord == 1 || \
                  ODDatArr[ Quick_stop_option_code ].word.LowWord == 5)
        {
            if( ODDatArr[Operation_Mode_Display].all == 6 )
            {
                ContSMachine.DecBase_Q15 = ContSMachine.DecBase609A_Q15;
            }
            else
            {
                ContSMachine.DecBase_Q15 = ContSMachine.DecBase6084_Q15;
            }
        }
        else if( ODDatArr[ Quick_stop_option_code ].word.LowWord == 2 || \
                 ODDatArr[ Quick_stop_option_code ].word.LowWord == 6)
        {
            ContSMachine.DecBase_Q15 = ContSMachine.DecBase6085_Q15;
        }
        else
        {
            ContSMachine.DecBase_Q15 = ContSMachine.SpdOutQ15;
        }
    }
    else if( ContSMachine.FastStatus == 0x03 )                  /* 已经进入                         */
    {
        PDO_Var.SYNCUpFlag1 = 0;
        /*------------------------------------------------------------------------------------------*/
        /* 减速处理                                                                                 */
        /*------------------------------------------------------------------------------------------*/
        if( ContSMachine.SpdOutQ15 == 0 )                               /* 减速完成,速度 == 0       */
        {
            PosDelta = 0;
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
        else if( ContSMachine.SpdOutQ15 > 0 )                           /* 速度大于零               */
        {
            if( ContSMachine.SpdOutQ15 >= ContSMachine.DecBase_Q15 )
            {
                ContSMachine.SpdOutQ15 -= ContSMachine.DecBase_Q15;
                PosDelta = ContSMachine.SpdOutQ15 >> 15;
            }
            else
            {
                PosDelta = ContSMachine.SpdOutQ15 >> 15;
                ContSMachine.SpdOutQ15 = 0;
            }
        }
        else                                                            /* 速度小于零               */
        {
            if( ContSMachine.SpdOutQ15 <= -ContSMachine.DecBase_Q15 )
            {
                ContSMachine.SpdOutQ15 += ContSMachine.DecBase_Q15;
                PosDelta = ContSMachine.SpdOutQ15 >> 15;
            }
            else
            {
                PosDelta = ContSMachine.SpdOutQ15 >> 15;
                ContSMachine.SpdOutQ15 = 0;
            }        
        }
    }
    else if( ContSMachine.FastStatus == 0x02 )
    {
        CanPosV.s32TargetPosOld = ODDatArr[Targe_Position_MM].all;      /*  更新旧值                */
        CanPosV.AbsPosCmd = ODDatArr[Position_Actual_Value_MM].all;    
    }
    else
    {;}

    /*----------------------------------------------------------------------------------------------*/
    /* 轮廓位置模式                                                                                    */
    /*----------------------------------------------------------------------------------------------*/
    if(ODDatArr[Operation_Mode_Display].all == 1)
    {
    /*----------------------------------------------------------------------------------------------*/
    /* 在开启模式切换功能并且断使能时，输出脉冲量为0                                                */
    /*----------------------------------------------------------------------------------------------*/
        if((ODDatArr[Control_Word].all & 0x0008) != 0x0008 && CAN_EXFUNC0_4_EN)
        {
            PosDelta = 0;
        }
    /*----------------------------------------------------------------------------------------------*/
    /* 开环轮廓位置模式                                                                             */
    /*----------------------------------------------------------------------------------------------*/
        else if((ODDatArr[Control_Word].all & 0x0800) == 0x0800 && CAN_EXFUNC0_4_EN)
        {
            PosCurvP.TargetPos = 0;
            CanOpenPosParameterUpdate();                        /* 相关参数更新                     */
            if(CanPosV.PosSpdCmd >= 0)
            {
                if(CanPosV.PosSpdCmd < PosCurvP.ProfRefSpdQ15 )
                {
    /*----------------------------------------------------------------------------------------------*/
    /*              加速                                                                            */
    /*----------------------------------------------------------------------------------------------*/
                    CanPosV.PosSpdCmd += PosCurvP.AccBaseQ15;
                    if(CanPosV.PosSpdCmd >= PosCurvP.ProfRefSpdQ15 )
                    {
                        CanPosV.PosSpdCmd = PosCurvP.ProfRefSpdQ15;
                    }
                }
                else
                {
    /*----------------------------------------------------------------------------------------------*/
    /*              减速                                                                            */
    /*----------------------------------------------------------------------------------------------*/
                    CanPosV.PosSpdCmd -= PosCurvP.DecBaseQ15;
                    if(CanPosV.PosSpdCmd < PosCurvP.ProfRefSpdQ15 )
                    {
                        CanPosV.PosSpdCmd = PosCurvP.ProfRefSpdQ15;
                    }
                }
            }
            else
            {
                if(CanPosV.PosSpdCmd <= PosCurvP.ProfRefSpdQ15 )
                {
    /*----------------------------------------------------------------------------------------------*/
    /*              减速                                                                            */
    /*----------------------------------------------------------------------------------------------*/
                    CanPosV.PosSpdCmd += PosCurvP.DecBaseQ15;
                    if(CanPosV.PosSpdCmd >= PosCurvP.ProfRefSpdQ15 )
                    {
                        CanPosV.PosSpdCmd = PosCurvP.ProfRefSpdQ15;
                    }
                }
                else
                {
    /*----------------------------------------------------------------------------------------------*/
    /*              加速                                                                            */
    /*----------------------------------------------------------------------------------------------*/
                    CanPosV.PosSpdCmd -= PosCurvP.AccBaseQ15;
                    if(CanPosV.PosSpdCmd < PosCurvP.ProfRefSpdQ15 )
                    {
                        CanPosV.PosSpdCmd = PosCurvP.ProfRefSpdQ15;
                    }
                }
            }
    /*----------------------------------------------------------------------------------------------*/
    /* 开环轮廓位置所走的位置量计入位置模式，进行相关清零操作                                       */
    /*----------------------------------------------------------------------------------------------*/
            if((ODDatArr[Control_Word].all & 0x1800) == 0x0800)
            {
                CanPosV.s32TargetPosOld = ODDatArr[Targe_Position_MM].all;
                CanPosV.AbsPosCmd       = ODDatArr[Position_Actual_Value_MM].all;
                PosCurGenerator_Clear();                      /* 20220509  轮廓位置复位             */
            }
            CanPosV.PPStep = 0;
            PosDelta =  MlibCalc_RemAdd(CanPosV.PosSpdCmd, 32768, 65536);
            //PosDelta = CanPosV.PosSpdCmd >> 15;
            PosCurvV.SpdOutQ15 = CanPosV.PosSpdCmd;           /* 开环位置速度代入闭环位置速度       */
        }
        /*----------------------------------------------------------------------------------------------*/
        /* 闭环轮廓位置模式                                                                              */
        /*----------------------------------------------------------------------------------------------*/
        else
        {
        /*------------------------------------------------------------------------------------------*/
        /* 绝对位置更新用  ( 在驱动器使能OFF时更新一次后即可 )                                                 */
        /*------------------------------------------------------------------------------------------*/
        CanPosV.s32TargetPosOld = ODDatArr[Targe_Position_MM].all;
 
        /*------------------------------------------------------------------------------------------*/
        switch( CanPosV.PPStep )
        {
            //-------------------------------------------------------------------------------------
            case 0:                                                  
                //---------------------------------------------------------------------------------
                // 非立即更新模式
                //---------------------------------------------------------------------------------
                if( CAN_EXFUNC0_2_EN || CAN_EXFUNC0_3_EN )
                {
                    if( CanPosV.OB6040Bit4Status == 0x03 && (ODDatArr[Control_Word].all & 0x0040) == 0x0000)              /* 控制字6040的Bit4为高电平 */
                    {
                        CanPosV.PPStep = 1;
                    }
                }
                if( CanPosV.OB6040Bit4Status == 0x01 || CanPosV.OB6040Bit4Rising_edge == 0x01)              /* 控制字6040的Bit4为上升沿     */
                {
                    CanPosV.PPStep = 1;
                    CanPosV.UpdateTimeCnt=0;
                }

                /* 开环位置切闭环位置防止速度抖动20240228                                        */
                if(CAN_EXFUNC0_4_EN && (CanPosV.Ctrl_WordOld & 0x1800) == 0x0800)
                {
                    PosDelta = PosDeltaOld;
                }
                if( CAN_EXFUNC0_5_EN )
                {
                    /*----------------------------------------------------------------------------------*/
                    /* 记录当前的实际用户指令位置                                                       */
                    /*----------------------------------------------------------------------------------*/
                        CanPosV.PosActalueOld = ODDatArr[Position_Actual_Value_MM].all;

                }
                break;
            //-------------------------------------------------------------------------------------
            case 1:
                    //-----------------------------------------------------------------------------
                    // u16ControlWord Bit5 :    0 非立即更新
                    // StatusWord     Bit12:    0 上一指令发送完成,可以更新
                    //-----------------------------------------------------------------------------
                    // 相关信息更新
                    //-----------------------------------------------------------------------------
                       if(CAN_EXFUNC0_4_EN && (CanPosV.Ctrl_WordOld & 0x1800) == 0x0800)
                       {
                           CanPosV.AbsPosCmd = ODDatArr[Position_Actual_Value_MM].all + \
                                               ODDatArr[Follow_Error_Actual_Value].all + PosDeltaOld;
                           //CanPosV.AbsPosCmd = ODDatArr[Position_Actual_Value_MM].all + ODDatArr[Follow_Error_Actual_Value].all;
                       }
                       /*------------------------------------------------------------------------------*/
                       /* 手自动切换，当手动模式运行过程突然切换至自动模式，需要根据当前位置与当前位置偏差进行计算 */
                       /*------------------------------------------------------------------------------*/
                       if(CAN_EXFUNC0_7_EN && (CanPOSJOGV.ManualAutoModOld == 1))
                       {
                           CanPosV.AbsPosCmd = ODDatArr[Position_Actual_Value_MM].all + ODDatArr[Follow_Error_Actual_Value].all;
                       }

                       if( CAN_EXFUNC0_5_EN )
                       {
                           CanPosV.AbsPosCmd = ODDatArr[Position_Actual_Value_MM].all + ODDatArr[Follow_Error_Actual_Value].all;
                           PosCurvV.PosRemain = 0;
                           PosCurvV.PosSumIn  = 0;
                           PosCurvV.PosSumOut = 0;
                           PosCurvV.PosBlock  = 0;     /*  20231116 解决绝对切相对有时无法触发      */
                       }

                    //                       位置指令计算更新
                    //-----------------------------------------------------------------------------
                    if( (ODDatArr[Polarity].all & 0x80) == 0x0080 )        // 位置指令极性
                    {
                        PosTmp = -ODDatArr[Targe_Position_MM].sall;
                    }
                    else
                    {
                        PosTmp =  ODDatArr[Targe_Position_MM].sall;
                    }
                    //----------------------------------------------------------------------------
                    if( (ODDatArr[Control_Word].all & 0x0040) == 0x0040)  // 相对位置
                    {
                        if(CAN_EXFUNC0_5_EN)
                        {
                        /*--------------------------------------------------------------------------*/
                        /*     计算模式切换的瞬间电机走过的脉冲数                                   */
                        /*--------------------------------------------------------------------------*/
                            CanPosV.PosActalue = ODDatArr[Position_Actual_Value_MM].all;
                            PosActDelta = CanPosV.PosActalue - CanPosV.PosActalueOld;
                        /*--------------------------------------------------------------------------*/
                        /* 根据模式切换瞬间电机走过的脉冲数与当前的用户位置偏差计算出相对位置指令值 */
                        /*--------------------------------------------------------------------------*/
                            PosTmp = PosTmp - PosActDelta - ODDatArr[Follow_Error_Actual_Value].all;
                        }


                        PosCurvP.TargetPos = PosTmp;
                        CanPosV.AbsPosCmd += PosTmp;
                    }
                    else                                                  // 绝对位置
                    {
                        PosCurvP.TargetPos      = PosTmp - CanPosV.AbsPosCmd;
                        CanPosV.AbsPosCmd       = PosTmp;

                        CanPosV.AbsPosCmdOld    = ODDatArr[Targe_Position_MM].sall;
                        CanPosV.SpdCmdOld    = ODDatArr[Profile_Velocity_RPM].all;
                    }
                    //----------------------------------------------------------------------------
                    /* 开环位置切闭环位置防止速度抖动20240228                                        */
                    if(CAN_EXFUNC0_4_EN && (CanPosV.Ctrl_WordOld & 0x1800) == 0x0800)
                    {
                        PosDelta = PosDeltaOld;
                    }

                    PosCurvV.PosBlock  = 0;                               // 解决魔仓位置运行不到位问题@20240401
                    CanOpenPosParameterUpdate();                          // 相关参数更新
                    CanPOSJOGV.ManualAutoModOld = CinV.f.Sv.ManualAutoMod;
                    CanPosV.PPStep = 2;                                   // 进入下一步
                break;
            /*--------------------------------------------------------------------------------------*/
            case 2:
                if( PosCurvV.TargetReach )
                {
                    /*------------------------------------------------------------------------------*/
                    /* 位置曲线生成结束                                                                 */
                    /*------------------------------------------------------------------------------*/
                    CanPosV.PPStep = 0;
                }
                else
                {
                    PosCurveGenerator_Deal( );
                    PosDelta = PosCurvV.PosCmdOut;
                }
                //---------------------------------------------------------------------------------
              /*  if(CanPosV.UpdateTimeCnt<20)
                {
                    CanPosV.UpdateTimeCnt++;                            //控制字bit4更新周期为2ms
                }
                else
                {   
                    if( CanPosV.OB6040Bit4Status == 0x01 )         // 控制字6040的Bit4为上升沿
                    {
                        if( ( ODDatArr[Control_Word].all & 0x0020 )== 0x0020 ) // Bit5:0 立即更新
                        {
                            CanPosV.PPStep          = 1;
                        }
                    }
                    CanPosV.UpdateTimeCnt   = 0;
                }   */
                if( CanPosV.OB6040Bit4Rising_edge == 0x01 )     /* 控制字6040的Bit4为上升沿     */
                {
                    if( ( ODDatArr[Control_Word].all & 0x0020 )== 0x0020 ) /* Bit5:0 立即更新   */
                    {
                        CanPosV.PPStep          = 1;
                    }
                }
                    /*------------------------------------------------------------------------------*/
                    /* 检测【607A】 【6081】是否改动                                                */
                    /*------------------------------------------------------------------------------*/
                    if(CAN_EXFUNC0_2_EN && (ODDatArr[Control_Word].all & 0x0040) == 0x0000)
                    {
                        if(CanPosV.AbsPosCmdOld != ODDatArr[Targe_Position_MM].sall)
                        {
                            CanPosV.PPStep          = 1;
                        }
                    }
                    if(CAN_EXFUNC0_3_EN && (ODDatArr[Control_Word].all & 0x0040) == 0x0000)
                    {
                        if(CanPosV.SpdCmdOld != ODDatArr[Profile_Velocity_RPM].all)
                        {
                            CanPosV.PPStep          = 1;
                        }
                    }
                    if(CAN_EXFUNC0_5_EN)
                    {
                    /*----------------------------------------------------------------------------------*/
                    /* 记录当前的实际用户指令位置                                                         */
                    /*----------------------------------------------------------------------------------*/
                        CanPosV.PosActalueOld = ODDatArr[Position_Actual_Value_MM].all;
                    }
                break;
            /*--------------------------------------------------------------------------------------*/
            default:
                break;
            }
            CanPosV.PosSpdCmd = PosCurvV.SpdOutQ15;
            CanPOSJOGV.SpdCmd = PosCurvV.SpdOutQ15;         /* 手自动切换速度衔接       @瑞博特     */
            CanPOSJOGV.AutoJogStep = 0;
        }
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 回零模式                                                                                     */
    /*----------------------------------------------------------------------------------------------*/
    else if( ODDatArr[Operation_Mode_Display].all == 6 )
    {
        /*------------------------------------------------------------------------------------------*/
        /* 原点回归时,读取外部的相关信号                                                              */
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
//            ODDatArr[Status_Word].all |= 0x8000;                //找到参考点，bit15置1
        }
        else if(DISignReach == 0 && DISignOld == 1)
        {
            OrgPrCtlBit.OrgSignUp = 0;
            OrgPrCtlBit.OrgSignDown = 1;
//            ODDatArr[Status_Word].all |= 0x8000;                //找到参考点，bit15置1
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
        DISignOld = DISignReach;
        
        /*------------------------------------------------------------------------------------------*/
        /* 开始进行原点回归功能的相关变量初始化处理                                                 */
        /*------------------------------------------------------------------------------------------*/
        if( CanPosV.OB6040Bit4Status == 0x01 )
        {
            /*--------------------------------------------------------------------------------------*/
            /* 上升沿     (加减速,最大速度等更新处理)                                               */
            /*--------------------------------------------------------------------------------------*/
            Can_OrigSearch_ParamUpdate( );
            OrgControlBit.bit.OrgOkFlag = 0;
        }
        else if( CanPosV.OB6040Bit4Status == 0x03 )
        {
            /*--------------------------------------------------------------------------------------*/
            /* 高电平    ( 原点搜索执行处理 )                                                       */
            /*--------------------------------------------------------------------------------------*/          
            //---------------解决插补模式快速停机与减速停机不按减速度停机问题 @20250521 --------------------
            if((ContSMachine.FastStatus != 0x03) && (ContSMachine.HaltStatus != 0x03))
            {
                PosDelta = Can_OrigSearch_Deal( );
            }
        }
        else if( CanPosV.OB6040Bit4Status == 0x02 )
        {
            /*--------------------------------------------------------------------------------------*/
            /* 下降沿                                                                               */
            /*--------------------------------------------------------------------------------------*/
//            CinV.f.Sv.OTCheck = 0;                           /* 关闭屏蔽限位处理                   */
        }        
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 插补模式                                                                                     */
    /*----------------------------------------------------------------------------------------------*/
    else if( ODDatArr[Operation_Mode_Display].all == 7 )
    {
        if(PDO_Var.SYNCUpFlag1)
        {
            //根据插补时间单位计算插补周期值
            if(ODDatArr[Interpolation_Period_Index].byte.FirstByte == 0xFD) //60C2_2为-3插补周期单位为ms
            {
                InterPeriod = ODDatArr[Interpolation_Period_Unit].byte.FirstByte<<3;
            }
            else if(ODDatArr[Interpolation_Period_Index].byte.FirstByte == 0xFC)        //插补周期单位为0.1ms
            {
                InterPeriod = ((ULONG)ODDatArr[Interpolation_Period_Unit].byte.FirstByte<<3)/10;
            }
            else if(ODDatArr[Interpolation_Period_Index].byte.FirstByte == 0xFE)
            {
                InterPeriod = ((ULONG)ODDatArr[Interpolation_Period_Unit].byte.FirstByte<<3)*10; 
            }
            else
            {
                InterPeriod = 16 ;
            }
            if(InterPeriod < 8 )
            {
                InterPeriod = 8;                                                    //最小插补周期为1ms
            }
            else if(InterPeriod > 160)
            {
                InterPeriod = 160;                                                  //最大插补周期为20ms                                    
            }
        }
        //---------------解决插补模式快速停机与减速停机不按减速度停机问题 @20250521 --------------------
        if((ContSMachine.FastStatus != 0x03) && (ContSMachine.HaltStatus != 0x03))
        {
            PosDelta = InterPosMode();
        }
        ContSMachine.IntorPosTmpQ15 = (INT64)PosDelta << 15;
    }
    else
    {
        /*------------------------------------------------------------------------------------------*/
        /* 非插补模式,位置指令的值需要做更新处理,否则第一次切入时存在异常                           */
        /*------------------------------------------------------------------------------------------*/
        CanPosV.s32TargetPosOld = ODDatArr[Targe_Position_MM].all;
    }
    PosDeltaOld = PosDelta;
    /*----------------------------------------------------------------------------------------------*/
    /* 位置指令电子齿轮比处理                                                                       */
    /*----------------------------------------------------------------------------------------------*/
    ODDatArr[Position_Demand_Value_MM].all += PosDelta ;                 /* 对象字典 【0x6062】      */

#if(FLOAT_USE == 1)
    KX = FlibPcmdEgear( PosDelta, &Iprm.CANgear, &CanPosV.PosCmdRemain );
#else
    KX = MlibPcmdEgear( PosDelta, &Iprm.CANgear, &CanPosV.PosCmdRemain );
#endif
    ODDatArr[Postion_Demand_Value].all += KX;                          /* 对象字典 【0x60FC】       */

    PulseTmp = KX;
    return KX;
}


/****************************************************************************************************/
/*Function Name: AutoJOGZeroUpdate(void)                                                            */
/*Description  : 瑞博特自动回零（JOG点动相关参数计算）                                               */
/*Attention    :                                                                                    */
/****************************************************************************************************/
void AutoJOGSpd( void )
{
    SHORT Spd = 0;
    LLONG   TargetSpd_Q15;
    LLONG   SpdCmdValue;
    LLONG   SpdAcc,PrmAcc;
    LLONG   SpdDec,PrmDec;
    LLONG   CalcNum,CalcDen;
    Spd = ( SHORT )Prm.jogspd ;
    if( CinV.f.Sv.JOGN == TRUE )
    {
        Spd = -Spd;
    }
    CalcNum = MencP.PulseNo * Iprm.Egear.a * Iprm.CANgear.a;
    CalcDen = 60 * Iprm.Egear.b * Iprm.CANgear.b;
    SpdCmdValue = (LLONG)Spd * CalcNum / CalcDen;      /* pluse/s                                  */
    PrmAcc = (Prm.sfsacc<1) ? 1 : Prm.sfsacc;
    PrmDec = (Prm.sfsacc<1) ? 1 : Prm.sfsdec;
    //SpdCmdValue = SpdCmdValue * Iprm.Egear.a / Iprm.Egear.b;
    //SpdCmdValue = SpdCmdValue * Iprm.CANgear.a / Iprm.CANgear.b;
    SpdAcc = (INT64)3000.0f / PrmAcc * 1000;
    SpdDec = (INT64)3000.0f / PrmDec * 1000;           /* Pn310以3000rpm标幺，转换为单位rpm/s       */
    if( SpdAcc == 0)
    {
        SpdAcc = 1;
    }
    CanPOSJOGV.AccBasic_Q15 = (ULLONG) MencP.PulseNo * SpdAcc / 60;    /* pps/s                     */
    CanPOSJOGV.AccBasic_Q15 = CanPOSJOGV.AccBasic_Q15 * 8 / 15625;
    CanPOSJOGV.AccBasic_Q15 = CanPOSJOGV.AccBasic_Q15 * Iprm.Egear.a / Iprm.Egear.b;
    CanPOSJOGV.AccBasic_Q15 = CanPOSJOGV.AccBasic_Q15 * Iprm.CANgear.a / Iprm.CANgear.b;
    /*----------------------------------------------------------------------------------------------*/
    if( CanPOSJOGV.AccBasic_Q15 <= 1)
    {
        CanPOSJOGV.AccBasic_Q15 = 1;
    }
    if( SpdDec == 0)
    {
        SpdDec = 1;
    }
    CanPOSJOGV.DecBasic_Q15 = (ULLONG) MencP.PulseNo * SpdDec / 60;    /* pps/s                     */
    CanPOSJOGV.DecBasic_Q15 = CanPOSJOGV.DecBasic_Q15 * 8 / 15625;
    CanPOSJOGV.DecBasic_Q15 = CanPOSJOGV.DecBasic_Q15 * Iprm.Egear.a / Iprm.Egear.b;
    CanPOSJOGV.DecBasic_Q15 = CanPOSJOGV.DecBasic_Q15 * Iprm.CANgear.a / Iprm.CANgear.b;
    /*----------------------------------------------------------------------------------------------*/

    if(CanPOSJOGV.DecBasic_Q15<= 1)
    {
        CanPOSJOGV.DecBasic_Q15 = 1;
    }
    TargetSpd_Q15 = (LLONG)SpdCmdValue *  512 / 125;              /* Q15每125us                     */

    /*----------------------------------------------------------------------------------------------*/
    if( CanPOSJOGV.SpdCmd >= 0 )                                   /* 目标速度 大于0                */
    {
        if( CanPOSJOGV.SpdCmd <= TargetSpd_Q15 )
        {
            /*--------------------------------------------------------------------------------------*/
            /*  加速                                                                                */
            /*--------------------------------------------------------------------------------------*/
            CanPOSJOGV.SpdCmd +=  CanPOSJOGV.AccBasic_Q15;
            if( CanPOSJOGV.SpdCmd >= TargetSpd_Q15)
            {
                CanPOSJOGV.SpdCmd = TargetSpd_Q15;
            }
        }
        else
        {
            /*--------------------------------------------------------------------------------------*/
            /*  减速                                                                                */
            /*--------------------------------------------------------------------------------------*/
            CanPOSJOGV.SpdCmd -=  CanPOSJOGV.DecBasic_Q15;
            if( CanPOSJOGV.SpdCmd < TargetSpd_Q15)
            {
                CanPOSJOGV.SpdCmd = TargetSpd_Q15;
            }
        }
    }
        /*------------------------------------------------------------------------------------------*/
    else                                                         /* 目标速度 小于0                  */
    {
        if( CanPOSJOGV.SpdCmd <= TargetSpd_Q15 )
        {
            /*--------------------------------------------------------------------------------------*/
            /*  减速                                                                                */
            /*--------------------------------------------------------------------------------------*/
            CanPOSJOGV.SpdCmd +=  CanPOSJOGV.DecBasic_Q15;
            if( CanPOSJOGV.SpdCmd >= TargetSpd_Q15)
            {
                CanPOSJOGV.SpdCmd      = TargetSpd_Q15;
            }
        }
        else
        {
            /*--------------------------------------------------------------------------------------*/
            /*  加速                                                                                */
            /*--------------------------------------------------------------------------------------*/
            CanPOSJOGV.SpdCmd -=  CanPOSJOGV.AccBasic_Q15;
            if( CanPOSJOGV.SpdCmd < TargetSpd_Q15)
            {
                CanPOSJOGV.SpdCmd      = TargetSpd_Q15;
            }
        }
    }
}


/****************************************************************************************************/
/*Function Name: CanOpenPosJOGUpdate(void)                                                          */
/*Description  : 松开点动端子回零加减速计算                                                          */
/*Attention    :                                                                                    */
/****************************************************************************************************/
void CanOpenPosJOGUpdate( void )
{
    SHORT Spd = 0;
    LLONG   TargetSpd_Q15;
    LLONG   SpdCmdValue;
    LLONG   SpdAcc,PrmAcc;
    LLONG   SpdDec,PrmDec;
    LLONG   CalcNum,CalcDen;
    Spd = ( SHORT )Prm.jogspd ;
    if( CinV.f.Sv.JOGN == TRUE )
    {
        Spd = -Spd;
    }
    CalcNum = MencP.PulseNo * Iprm.Egear.a * Iprm.CANgear.a;
    CalcDen = 60 * Iprm.Egear.b * Iprm.CANgear.b;
    SpdCmdValue = (LLONG)Spd * CalcNum / CalcDen;                 /* pluse/s                        */
    TargetSpd_Q15 = (LLONG)SpdCmdValue *  512 / 125;              /* Q15每125us                     */

    PosCurvP.ProfRefSpdQ15 = (TargetSpd_Q15 > 0)? TargetSpd_Q15 : -TargetSpd_Q15;


    PrmAcc = (Prm.sfsacc<1) ? 1 : Prm.sfsacc;
    PrmDec = (Prm.sfsacc<1) ? 1 : Prm.sfsdec;
    SpdAcc = (INT64)3000.0f / PrmAcc * 1000;
    SpdDec = (INT64)3000.0f / PrmDec * 1000;                            /* rpm/s                    */
    SpdAcc = SpdAcc * MencP.PulseNo / 60;
    SpdDec = SpdDec * MencP.PulseNo / 60;
    /*----------------------------------------------------------------------------------------------*/
    /* 位置控制轮廓加速时间   对象字典:  【0x6083】                                                 */
    /*----------------------------------------------------------------------------------------------*/
    if( SpdAcc <= 1 )
    {
        SpdAcc=1;
    }
    PosCurvP.AccBaseQ15 = SpdAcc * 8 / 15625;
    PosCurvP.AccBaseQ15 =  PosCurvP.AccBaseQ15 * Iprm.Egear.a / Iprm.Egear.b;
    PosCurvP.AccBaseQ15 =  PosCurvP.AccBaseQ15 * Iprm.CANgear.a / Iprm.CANgear.b;
    if( PosCurvP.AccBaseQ15 <= 1 )
    {
        PosCurvP.AccBaseQ15 = 1;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 位置控制轮廓减速时间   对象字典:  【0x6084】                                                 */
    /*----------------------------------------------------------------------------------------------*/
    if( SpdDec <= 1 )
    {
        SpdDec = 1;
    }
    PosCurvP.DecBaseQ15 = SpdDec  * 8 / 15625;
    PosCurvP.DecBaseQ15 = PosCurvP.DecBaseQ15 * Iprm.Egear.a / Iprm.Egear.b;
    PosCurvP.DecBaseQ15 = PosCurvP.DecBaseQ15 * Iprm.CANgear.a / Iprm.CANgear.b;
    if( PosCurvP.DecBaseQ15 <= 1 )
    {
        PosCurvP.DecBaseQ15 = 1;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 目标位置赋值                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
        PosCurvV.PosRemain += PosCurvP.TargetPos;
        PosCurvV.PosSumIn  += PosCurvP.TargetPos;
        PosCurvV.TargetReach = 0;
}



/****************************************************************************************************/
/*Function Name: CanOpenPosUpdate(void)                                                            */
/*Description  : CanOpen 相关位置指令更新                                                           */
/*Attention    :                                                                                    */
/****************************************************************************************************/
void CanOpenPosParameterUpdate( void )
{
    double Kx;                                              /* 仙工控制器兼容步科速度比例系数      */
    LONG  PPSpd,MaxSpd;
    LONG  SpdAcc,SpdDec;
    if( ODDatArr[Profile_Acceleration].all >= ODDatArr[ Max_Acceleration ].all )
    {
        SpdAcc = ODDatArr[ Max_Acceleration ].all;
    }
    else
    {
        SpdAcc = ODDatArr[Profile_Acceleration].all;
    }
    /*----------------------------------------------------------------------------------------------*/
    if( ODDatArr[Profile_Deceleration].all >= ODDatArr[ Max_Deceleration ].all )
    {
        SpdDec = ODDatArr[ Max_Deceleration ].all;
    }
    else
    {
        SpdDec = ODDatArr[Profile_Deceleration].all;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 位置控制最大速度(p/s)   对象字典:  6081h                                                      */
    /*----------------------------------------------------------------------------------------------*/
    /*                6081 × 6091                                                                  */
    /* Speed(rpm) = --------------- × 60                                                           */
    /*                编码器分辨率                                                                  */
    /*----------------------------------------------------------------------------------------------*/
    /* 速度单位转换成脉冲单位                                                                        */
    /*               Speed(rpm) × 编码器分辨率                                                      */
    /* Speed(pps) = ---------------------------                                                     */
    /*                          60                                                                  */
    /*----------------------------------------------------------------------------------------------*/
    /* 简化后可以得到:                                                                              */
    /*                6081h × 6091h-1                                                               */
    /* Speed(pps) = -------------------------                                                       */
    /*                  6091h-2                                                                     */
    /*----------------------------------------------------------------------------------------------*/
    /* 需要将Speed(pps)转换成执行周期内脉冲数,执行周期为125us,则相应系数为:                            */
    /*           Speed(PPS) × 125            Speed(PPS)                                            */
    /* P/SCAN = ------------------------ = ------------                                             */
    /*           1000 × 1000   (S--->us)        8000                                               */
    /* 脉冲格式转换成Q15格式,于是有:                                                                 */
    /*      2^15        2^9                                                                         */
    /*   ---------- = ------                                                                        */
    /*      8000        125                                                                         */
    /*----------------------------------------------------------------------------------------------*/
    if((ODDatArr[Control_Word].all & 0x0800) == 0x0800 && CAN_EXFUNC0_4_EN)
    {
        PPSpd = ODDatArr[Target_Velocity_RPM].all;                 /*开环位置模式速度指令为【60FF】 */
    /*----------------------------------------------------------------------------------------------*/
    /*  Canopen 开环位置指令极性                                                                */
    /*----------------------------------------------------------------------------------------------*/
        if( (ODDatArr[Polarity].all & 0x80) == 0x0080 )            /* 位置指令极性                  */
            PPSpd = -PPSpd;
        else
            PPSpd =  PPSpd;
    }
    else
    {
        PPSpd = ODDatArr[Profile_Velocity_RPM].all;
    }

    
    if( CAN_EXFUNC0_6_EN )
    {
        /*  将速度转换系数改为上位机可修改  @20240508                                               */
        Kx =(double)(((LONG)Prm.CANSpdCoeffH << 16) + (USHORT)Prm.CANSpdCoeffL) / 100000000.0f;
        PPSpd = (LONG)((double)ODDatArr[Profile_Velocity_RPM].all * Kx);
    }
    MaxSpd = ODDatArr[Max_Profile_Velocity].all;                                //速度限制【0x607F】
    
    PPSpd = MlibLimitul(PPSpd,  MaxSpd, -MaxSpd);
    
    PosCurvP.ProfRefSpdQ15 = (INT64)((double)PPSpd * 4.096f);
    //PosCurvP.ProfRefSpdQ15 = (INT64)ODDatArr[Profile_Velocity_RPM].all *  512 / 125;
 
    /*----------------------------------------------------------------------------------------------*/
    /* 位置控制轮廓加速时间   对象字典:  【0x6083】                                                   */
    /*----------------------------------------------------------------------------------------------*/
    if( SpdAcc<=1 )
    {
        SpdAcc=1;
    }
    PosCurvP.AccBaseQ15 = (INT64)((double)SpdAcc * 8.0f / 15625.0f);
    if( PosCurvP.AccBaseQ15 <= 1 )
    {
        PosCurvP.AccBaseQ15 = 1;
    }

    /*----------------------------------------------------------------------------------------------*/
    /* 位置控制轮廓减速时间   对象字典:  【0x6084】                                                          */
    /*----------------------------------------------------------------------------------------------*/
    if( SpdDec <= 1 )
    {
        SpdDec = 1;
    }
    PosCurvP.DecBaseQ15 = (INT64)((double)SpdDec * 8.0f / 15625.0f);
    if( PosCurvP.DecBaseQ15 <= 1 )
    {
        PosCurvP.DecBaseQ15 = 1;
    }

    if(CAN_EXFUNC0_4_EN)
    {
        CanPosV.Ctrl_WordOld = ODDatArr[Control_Word].all;           /*  记录上一周期控制字         */
    }

    /*----------------------------------------------------------------------------------------------*/
    /* 目标位置赋值                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
    PosCurvV.PosRemain += PosCurvP.TargetPos;
    PosCurvV.PosSumIn  += PosCurvP.TargetPos;
    
    PosCurvV.TargetReach = 0;
}



/****************************************************************************************************/
/*Function_Name:CanOpen_ControlModeSel()                                                           */
/*Description  :                                                                                      */
/****************************************************************************************************/
void CanOpen_ControlModeSel(void)
{
    CinV.f.Sv.OTCheck = 0;                                      /* 限位开启                         */

    /*----------------------------------------------------------------------------------------------*/
    /* JOG手自动切换强制设置【6060】工作模式       @瑞博特手自动切换功能                            */
    /*----------------------------------------------------------------------------------------------*/
    if((CinV.f.Sv.ManualAutoMod == 1) && CAN_EXFUNC0_7_EN)
    {
        ODDatArr[Operation_Mode].byte.FirstByte = 1;
    }
    else
    {
        CanPOSJOGV.AutoJogStep = 0;                                        /* 手自动切换在回零时初始化状态机   */
    }

    switch( ODDatArr[Operation_Mode].byte.FirstByte )
    {
        /*------------------------------------------------------------------------------------------*/
        case 1:                                                 /* 轮廓位置                */
            ODDatArr[Operation_Mode_Display].byte.FirstByte = 1;
            CanOpen_ControlMode = 1;
            
            if(((ODDatArr[ Control_Word ].all)&(0x100))==0x100)
            {
              CanSpdV.SpdCmd = (INT64)((double)ContSMachine.SpdOutQ15 * 125.0f / 521.0f); /* 20220527 将轮廓位置速度赋值给轮廓速度模式*/
              CanSpdV.SpdCmd = CanSpdV.SpdCmd << 15;
            }
            else
            {
              CanSpdV.SpdCmd = PosCurvV.SpdOutQ15 * 125 / 521;      /* 20220527 将轮廓位置速度赋值给轮廓速度模式*/
              CanSpdV.SpdCmd = CanSpdV.SpdCmd << 15;
            }
            break;
        /*------------------------------------------------------------------------------------------*/
        case 3:                                                 /* 轮廓速度                */
            ODDatArr[Operation_Mode_Display].byte.FirstByte = 3;
            CanOpen_ControlMode = 0;
            AbsPosRecord = 0;
            break;
        /*------------------------------------------------------------------------------------------*/
        case 4:                                                 /* 轮廓转矩                */
            ODDatArr[Operation_Mode_Display].byte.FirstByte = 4;
            CanOpen_ControlMode = 2;
            AbsPosRecord = 0;
            break;
        /*------------------------------------------------------------------------------------------*/            
        case 6:                                                 /* 回零                             */
            ODDatArr[Operation_Mode_Display].byte.FirstByte = 6;
            CanPosV.AbsPosCmd = ODDatArr[Position_Actual_Value_MM].all;  /*绝对位置20220223 */
            CanOpen_ControlMode = 1;
            CinV.f.Sv.OTCheck = 1;                              /* 屏蔽限位处理                     */
            if(BinV.f.BaseEnable)
            {
                 if(Prm.b_prm0_06 & 0x0001 ==0x0001)
                {
                    if(CinV.f.Sv.PotIn==1)
                    {
                        KPI_WARNINGSET(WRN_POT);
                    }
                    else if(CinV.f.Sv.NotIn==1)
                    {
                        KPI_WARNINGSET(WRN_NOT);
                    }
                }
            }
            break;
        /*------------------------------------------------------------------------------------------*/            
        case 7:                                                 /* 插补            */
            ODDatArr[Operation_Mode_Display].byte.FirstByte = 7;
            CanPosV.AbsPosCmd = ODDatArr[Position_Actual_Value_MM].all;  /*绝对位置20240620 */
            CanOpen_ControlMode = 1;
            AbsPosRecord = 0;
            break;
        case 5:
            ODDatArr[Operation_Mode_Display].byte.FirstByte = 5;
            CanOpen_ControlMode = 7;
            AbsPosRecord = 0;

            break;
        default:
            CanOpen_ControlMode = 0;
            ODDatArr[Operation_Mode_Display].byte.FirstByte = ODDatArr[Operation_Mode].byte.FirstByte;                         /* ????(??)                   */
            break;
    }
    //  解决插补模式下6064有值，60C1=6064时电机飞车问题 @20240619
    if(ODDatArr[Operation_Mode].byte.FirstByte != 7)
    {
        CanIntMod.IntorPosOld = ODDatArr[Position_Actual_Value_MM].all;
    }
    /*----------------------------------------------------------------------------------------------*/
    /*  ?λ??????,λ?Р???￡???т?m                                                                     */
    /*----------------------------------------------------------------------------------------------*/
    if( CanOpen_ControlMode != 1 )
    {
        CanPosV.s32TargetPosOld = ODDatArr[Targe_Position_MM].all;
        
        CanPosV.AbsPosCmd       = ODDatArr[Position_Actual_Value_MM].all;
        CanPosV.PPStep = 0;
        PosCurGenerator_Clear();                    /* 20220509  轮廓位置复位 */
        //BpxEdgeClrSvcPositionManager( );            /* 20220510 清位置偏差*/
        ODDatArr[Follow_Error_Actual_Value].all=0;  /* 20220510 清位置偏差*/
    }

}

/*----------------------------------------------------------------------------------------------*/
/* 声明状态字和控制字的结构体变量                                                                       */
/*----------------------------------------------------------------------------------------------*/
CONTROLWORD_STRUCT ControlWord;
STATUSWORD_STRUCT  StatusWord;

UCHAR CanOpen_ControlStatus = 0;
UCHAR QuickStop_flag = 0;
void CanOpen402Status_ControlWordDeal(void)
{
  static UCHAR   CanErrRstStatus = 0;
  LONG ServoAlarm = 0;
  UCHAR CAControlStatus = 0;
    /*----------------------------------------------------------------------------------------------*/
    /* 使能按钮按钮关联控制字0x3F                                                                    */
    /*----------------------------------------------------------------------------------------------*/
    if((CinV.f.Seq.ServoOn) && (CAN_EXFUNC1_2_EN))
    {
        ODDatArr[Control_Word].all = 0x3F;
        if(CiA402StatusMachine == 1)
        {
            CanOpen_ControlStatus = 5;
        }
        else
        {
            CanOpen_ControlStatus = 4;
        }
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 急停按钮关联控制字0x0B                                                                        */
    /*----------------------------------------------------------------------------------------------*/
    if((CinV.f.Sv.EmcyStop) && CAN_EXFUNC0_12_EN )
    {
        ODDatArr[Control_Word].all = 0x0B;
      
    }
	/*----------------------------------------------------------------------------------------------*/
    /* 2. 获取当前的控制字的值                                                                            */
    /*----------------------------------------------------------------------------------------------*/
    ControlWord.w = ODDatArr[Control_Word].all;             //控制字
    StatusWord.w  = ODDatArr[Status_Word].all;              //状态字


    if(!CiA402StatusMachine)
    {
        /*----------------------------------------------------------------------------------------------*/
        /* 3. 状态机处理                                                                                 */
        /*----------------------------------------------------------------------------------------------*/
        switch(CanOpen_ControlStatus)
        {
            /*------------------------------------------------------------------------------------------*/
            case 0:                                             //【未准备好接通电源】
                StatusWord.w = 0;
                CanOpen_ControlStatus = 1;                      //状态转换1
                break;
            /*------------------------------------------------------------------------------------------*/
            case 1:                                             //【不可接通电源】
                /*--------------------------------------------------------------------------------------*/
                StatusWord.w &= 0x8000;
                StatusWord.f.SwitchOnDisable = 1;
                StatusWord.f.OperationEnable = 0;
                /*--------------------------------------------------------------------------------------*/
                if(((ControlWord.w & 0x0007) == 0x0006) && (CoutV.f.Seq.MainPowerOn == 1))
                {
                    CanOpen_ControlStatus = 2;                  //状态转换2
                }
                /*--------------------------------------------------------------------------------------*/
                break;
            /*------------------------------------------------------------------------------------------*/
            case 2:                                             //【准备好接通电源】--->关闭
                /*--------------------------------------------------------------------------------------*/
                StatusWord.w &= 0x8000;
                StatusWord.f.Rdy2SwitchOn = 1;
                StatusWord.f.QuickStop = 1;
                StatusWord.f.OperationEnable = 0;
                /*--------------------------------------------------------------------------------------*/
                if( (ControlWord.w & 0x000F) == 0x0007)
                {
                    CanOpen_ControlStatus = 3;                  //状态转换3

                    //----------------------------------------------------------------------------------
                    //  测试 @20240305
                    //----------------------------------------------------------------------------------i
                    if( CinV.f.Seq.ServoOffDecM == TRUE )
                    {
                        CinV.f.Seq.ServoOffDecM = FALSE;
                    }
                }
                /*--------------------------------------------------------------------------------------*/
                if(ControlWord.f.EnableVoltage == 0 || (ControlWord.w & 0x0006) == 0x0002)

                //if( ControlWord.f.EnableVoltage == 0 )
                {
                    CanOpen_ControlStatus = 1;                  //状态转换7
                }
                /*--------------------------------------------------------------------------------------*/
                if( CAN_EXFUNC0_1_EN )
                {
                    if( (ControlWord.w & 0x000F) == 0x0006 )
                    {
                        CanOpen_ControlStatus = 3;              //状态转换3
                    }
                }
                /*--------------------------------------------------------------------------------------*/
                break;
            /*------------------------------------------------------------------------------------------*/
            case 3:                                             //【开始供电】
                /*--------------------------------------------------------------------------------------*/
                StatusWord.w &= 0x8000;
                StatusWord.f.Rdy2SwitchOn       = 1;
                StatusWord.f.SwitchOn           = 1;
                StatusWord.f.QuickStop          = 1;

                StatusWord.f.OperationEnable    = 0;

                /*--------------------------------------------------------------------------------------*/
                if((ControlWord.w & 0x000F) == 0x000F)
                {
                    CanOpen_ControlStatus = 4;                  //状态转换4
                }
                /*--------------------------------------------------------------------------------------*/
                if((ControlWord.f.EnableVoltage == 0x0 ) || (ControlWord.w & 0x0006) == 0x0002)
                {
                    CanOpen_ControlStatus = 1;                  //状态转换10
                }
                if( CAN_EXFUNC0_1_DIS )
                {
                    /*--------------------------------------------------------------------------------------*/
                    if((ControlWord.f.EnableVoltage == 0x0 ) || (ControlWord.w & 0x0006) == 0x0002)
                    {
                        CanOpen_ControlStatus = 1;              //状态转换10
                    }
                }
                /*--------------------------------------------------------------------------------------*/
                break;
            /*------------------------------------------------------------------------------------------*/
            case 4:                                             //【开始运行】
                /*--------------------------------------------------------------------------------------*/
                StatusWord.w &= 0x9000;
                StatusWord.f.Rdy2SwitchOn = 1;
                StatusWord.f.SwitchOn = 1;
                StatusWord.f.OperationEnable = 1;
                StatusWord.f.QuickStop = 1;
    //          StatusWord.f.VoltEnabled = 1;

                /*--------------------------------------------------------------------------------------*/
                if((ControlWord.w & 0x000F) == 0x0007)
                    CanOpen_ControlStatus = 3;                  //状态转换5
                /*--------------------------------------------------------------------------------------*/
                if((ControlWord.w & 0x0007) == 0x0006)
                    CanOpen_ControlStatus = 2;                  //状态转换8
                /*--------------------------------------------------------------------------------------*/
                if(ControlWord.f.EnableVoltage == 0x0)
                    CanOpen_ControlStatus = 1;                  //状态转换9
                /*--------------------------------------------------------------------------------------*/
                if((ControlWord.w & 0x0006) == 0x0002)
                    CanOpen_ControlStatus = 5;                  //状态转换11
                /*--------------------------------------------------------------------------------------*/
                break;
            /*------------------------------------------------------------------------------------------*/
            case 5:                                             //【急停状态】
                /*--------------------------------------------------------------------------------------*/
                StatusWord.w &= 0x8000;
                StatusWord.f.Rdy2SwitchOn = 1;
                StatusWord.f.SwitchOn = 1;
                if((ControlWord.w & 0x0006) == 0x0002)
                    StatusWord.f.OperationEnable = 1;
    //			StatusWord.f.VoltEnabled = 1;
                if((ControlWord.w & 0x000F) == 0x0006)
                    CanOpen_ControlStatus = 2;					//状态转换8
                /*--------------------------------------------------------------------------------------*/
                if((ControlWord.w & 0x000F) == 0x000F)
                    CanOpen_ControlStatus = 4;                  //状态转换8
                /*--------------------------------------------------------------------------------------*/
                if(ControlWord.f.EnableVoltage == 0x0)
                    CanOpen_ControlStatus = 1;                  //状态转换12
                /*--------------------------------------------------------------------------------------*/
                break;
            /*------------------------------------------------------------------------------------------*/
            case 6:                                             //【出错】
                /*--------------------------------------------------------------------------------------*/
                StatusWord.w &= 0x8000;
                StatusWord.f.Fault = 1;
                StatusWord.f.OperationEnable = 0;
                /*--------------------------------------------------------------------------------------*/
                if(ControlWord.f.FaultReset == 0x1 || DIDOVar.DISt.AlmReset)
                {
                    CanOpen_ControlStatus = 1;                  //状态转换15
                }
                /*--------------------------------------------------------------------------------------*/
                break;
            /*------------------------------------------------------------------------------------------*/
            case 7:                                             // 【错误反应】
            case 8:
                StatusWord.w &= 0x8000;
                StatusWord.f.QuickStop = 0;                     // bit5 快速停机
                StatusWord.f.SwitchOnDisable = 1;               // bit6 伺服不可运行
                if((ControlWord.w & 0x0007) == 0x0006)
                {
                    CanOpen_ControlStatus = 2;
                }
                break;
            default:
                /*--------------------------------------------------------------------------------------*/
                StatusWord.w &= 0x8000;
                StatusWord.w |= 0x0F;
                /*--------------------------------------------------------------------------------------*/
                CanOpen_ControlStatus = 6;                      //状态转换14
                break;

        }
    }

    else if(CiA402StatusMachine)
    {
        CAControlStatus = CiA402_StatusMachine(CanOpen_ControlStatus);
        CanOpen_ControlStatus = CAControlStatus;
    }
    StatusWord.f.VoltEnabled = CoutV.f.Seq.MainPowerOn;
    /*----------------------------------------------------------------------------------------------*/
    /* 4. 故障复位                                                                                  */
    /*----------------------------------------------------------------------------------------------*/
    if(!CiA402StatusMachine)
    {
        if( CAN_EXFUNC0_1_DIS )
        {
            if(ControlWord.f.FaultReset == 0x1 || DIDOVar.DISt.AlmReset)
            {
                CanOpen_ControlStatus = 1;                  //状态转换15
            }
        }
        else
        {
            ;
        }
    }
    
    /*----------------------------------------------------------------------------------------------*/
    /* 5.快速停机 SDZ                                                                               */
    /*----------------------------------------------------------------------------------------------*/
#if 0   //20230803
    if( ( Prm.Mode & 0xF000 ) == 0x1000 )
    {
        if(ControlWord.f.QuickStop == 0)
        {
            CanOpen_ControlStatus = 8;
        }
    }
#endif
    /*----------------------------------------------------------------------------------------------*/
    /* 6. 更新状态字                                                                                 */
    /*----------------------------------------------------------------------------------------------*/
    StatusWord.f.Remote = 1;
    
    /*----------------------------------------------------------------------------------------------*/
    /* 7.故障信息 (Bit4)                                                                              */
    /*----------------------------------------------------------------------------------------------*/
    StatusWord.f.Fault = Alm.f.AlmFlag;
    /*----------------------------------------------------------------------------------------------*/
    /* 8.位置 or 速度到达 (Bit10)                                                                      */
    /*----------------------------------------------------------------------------------------------*/
    if( ODDatArr[Operation_Mode].byte.FirstByte == 1 ||
        ODDatArr[Operation_Mode].byte.FirstByte == 6||
        ODDatArr[Operation_Mode].byte.FirstByte == 7)

    {
        StatusWord.f.TargetReach = BoutV.f.Ctrl.Coin;
        /*------------------------------------------------------------------------------------------*/
        /* 若有错误码或快速停机，则位置未到达                                                       */
        /*------------------------------------------------------------------------------------------*/
        if((ODDatArr[Error_Code].all!=0)||(CanOpen_ControlStatus == 8))
        {
            StatusWord.f.TargetReach = 0;
        }
    }
    else if( ODDatArr[Operation_Mode].byte.FirstByte == 3 )
    {
        
        StatusWord.f.TargetReach = CoutV.f.Ctrl.ReachSpd;

    }
    else if(ODDatArr[Operation_Mode].byte.FirstByte == 4)
    {
        StatusWord.f.TargetReach = CanTorq.TorqReachFlg;
    }
    else
    {
        StatusWord.f.TargetReach = 0;
    }
    
    /*----------------------------------------------------------------------------------------------*/
    /* 限位开关(bit11)                                                                              */
    /*----------------------------------------------------------------------------------------------*/
   if( ODDatArr[Operation_Mode_Display].all == 6 )
    {
        switch( ODDatArr[Homing_Method].byte.FirstByte )
        {
            case 3:
            case 4:
            case 5:
            case 6:
            case 20:
            case 21:
            case 22:
            case 33:
            case 34:
            case 35:
                if( CinV.f.Sv.Pot == 0 && CinV.f.Sv.Not == 0 )
                {
                    StatusWord.f.InternalLimitActive = 0;
                }
                else
                {
                    StatusWord.f.InternalLimitActive = 1;
                }
                StatusWord.f.Warning = Alm.f.WrnFlag;
            break;
            default:
                StatusWord.f.InternalLimitActive = 0;
                StatusWord.f.Warning = 0;
            break;
        }
    }
    else
    {  
        if( CinV.f.Sv.Pot == 0 && CinV.f.Sv.Not == 0 )
        {
            StatusWord.f.InternalLimitActive = 0;
        }
        else
        {
            StatusWord.f.InternalLimitActive = 1;
        }
        StatusWord.f.Warning = Alm.f.WrnFlag;
    }

          
    /*----------------------------------------------------------------------------------------------*/
    /* 零速度信号 (Bit12)                                                                           */
    /*----------------------------------------------------------------------------------------------*/
    if( ODDatArr[Operation_Mode].byte.FirstByte == 1 ||
        ODDatArr[Operation_Mode].byte.FirstByte == 7  )
    {
        if( BinV.f.BaseEnable )
        {
            StatusWord.f.ZeroSpd = (ControlWord.w>>4)&0x0001;
        }
    }
    else if( ODDatArr[Operation_Mode].byte.FirstByte == 3 )
    {
        StatusWord.f.ZeroSpd = !CoutV.f.Ctrl.MotorMoving;
    }
    else
    {
        ;
    }

    
    /*----------------------------------------------------------------------------------------------*/
    /* 原点回归失败(Bit13)                                                                          */
    /*----------------------------------------------------------------------------------------------*/
    if( ( ODDatArr[Operation_Mode].byte.FirstByte == 1 )||
        ( ODDatArr[Operation_Mode].byte.FirstByte == 7 )  )
    {
        StatusWord.f.OperationModeSpeckfic = BoutV.f.PosFollowErFlg;
    }
    else if( ODDatArr[Operation_Mode].byte.FirstByte == 6 )
    {
        StatusWord.f.OperationModeSpeckfic = OrgControlBit.bit.OrgFail;
    }    
    else
    {
        StatusWord.f.OperationModeSpeckfic = 0;
    }

    /*----------------------------------------------------------------------------------------------*/
    /* 原点回归完成(Bit15)                                                                          */
    /*----------------------------------------------------------------------------------------------*/
    //StatusWord.f.HomeFind = OrgControlBit.bit.OrgDone;
    
    /*----------------------------------------------------------------------------------------------*/
    /*  更新对象字典                                                                                */
    /*----------------------------------------------------------------------------------------------*/
    ODDatArr[Status_Word].all = StatusWord.w;
	if(OrgControlBit.bit.OrgOkFlag == 1)
    {
        ODDatArr[Status_Word].all  |= 0x9000;    
    }
    if( CAN_EXFUNC1_0_EN )
    {
        Can_Orig_Status();
    }
    
    
    /*----------------------------------------------------------------------------------------------*/
    /*                                 CanOpen 控制伺服使能                                        */
    /*----------------------------------------------------------------------------------------------*/
        if( StatusWord.f.OperationEnable )
        {
            Prm.b_prm0_1 |= 0x0001;                                     /* 伺服使能 ON              */
        }
        else
        {
            Prm.b_prm0_1 &= 0xFFFE;                                     /* 伺服 OFF                 */
        }
    /*----------------------------------------------------------------------------------------------*/
    /*                                警报复位清除                                                  */
    /*----------------------------------------------------------------------------------------------*/
    CanErrRstStatus = (CanErrRstStatus << 1) & 0x03;
    if( ControlWord.f.FaultReset || DIDOVar.DISt.AlmReset)
    {
        CanErrRstStatus |= 0x01;
    }
    
    if( CanErrRstStatus == 0x01)                                     /* 故障清除                    */
    {
        //------------------------  控制字清810 ---------------------------------------------
        ServoAlarm = KpiGetAlarmInfo();
        if(ServoAlarm == 0x0810 || ServoAlarm == 0x0830 || ServoAlarm == 0x0860 || ServoAlarm == 0x0C21 \
                || ServoAlarm == 0x0820 || ServoAlarm == 0x0840)
        {
            EncCodeV.MEncClrCmd = 1;
        }
        KpiResetAlarmTable();
        CanVar.NMTV.f.ErrReset = 1;
        DIDOVar.DISt.AlmReset = 0;
    }

    if(ControlWord.f.SoftReset == 0x1 && Alm.f.AlmFlag )               //软复位
    {
        Prm.password = 0x33AA;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 对象字典【0x6040】 Bit4 控制位的沿信号检测处理                                                 */
    /*----------------------------------------------------------------------------------------------*/
    if(BinV.f.BaseEnable | CoutV.f.Sv.Ot)
    {
        CanPosV.OB6040Bit4Status = CanPosV.OB6040Bit4Status << 1;
        CanPosV.OB6040Bit4Status &= 0x03;
        if( ( ODDatArr[Control_Word].all & 0x0010 )  == 0x0010)
        {
            CanPosV.OB6040Bit4Status |= 0x01;
        }
    }
    else
    {
        CanPosV.OB6040Bit4Status = 0x00 ;
    }
    if( CAN_EXFUNC0_8_EN )
    {
        ODDatArr[Digitial_Input].all = DIDOVar.DigitInFilter | ( Prm.VirDI & Iprm.Imap.VirSet);
    }
    else
    {
    /*----------------------------------------------------------------------------------------------*/
    /*  数字量输入信号                                                                              */
    /*----------------------------------------------------------------------------------------------*/
        ODDatArr[Digitial_Input].all =  (BinV.f.Sv.ORGS<<2) | (CinV.f.Sv.Pot  << 1 ) | CinV.f.Sv.Not;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 数字量输出信号                                                                               */
    /*----------------------------------------------------------------------------------------------*/
    ODDatArr[Physical_Digitial_Output].all  = (1^CoutV.f.Seq.BrkReleasing);
}


/*   函数功能：标准协议状态机，根据控制字6040h处理状态字6041h           */
/*   函数名：CiA402_StatusMachine                                   */
/*   输入参数：ControlStatus:控制状态，等效状态机转换逻辑图中的状态标号 */


UCHAR CiA402_StatusMachine(UCHAR ControlStatus )
{
    /*----------------------------------------------------------------------------------------------*/
    /* 1.402 状态机处理                                                                             */
    /*
    参考文件：CiA?402-CANopenDrivesAndMotionControlProfile   （https://www.can-cia.org/）
    版本：28 March 2016
    Ⅰ、状态机转换逻辑图：
                                                                               13
                                                                                |
                                                                                ↓
                           | Start(0) |                            | Fault Reaction Active(7) |
                                ↓0                                              ↓14
                  | Not Ready to Switch On(1) |                            | Fault(8) |
                                ↓1                                              |
            ┍------→| Switch On Disabled(2) | ←---┐←-------------┐←-----15------┘
            |           ↓2             ↑7         |              |
            |   ┍--→| Ready to Switch On(3) |    10              |
            9   |       ↓3             ↑6         |              |
            |   8      | Switched On(4) | --------┘             12
            |   |       ↓4             ↑5                        |
            └---└---| Operation Enabled(5) |----11---→| Quick Stop Active(6) |
                                ↑                                |
                                └--------------16----------------┘
    ————————————————————————————————————————————————————————————————————————————————————————————————————————
    Ⅱ：控制字6040h：“状态转换命令”位：
                    | Fault Reset | Enable Oper. | Quick Stop | Enable Volt | Switch On |             |
        OPERATION   |    Bit 7    |    Bit 3     |   Bit 2    |    Bit 1    |   Bit 0   | Transitions |
        Shutdown    |      0      |       X      |      1     |      1      |     0     |    2,6,8    |
        Switch On   |      0      |       0      |      1     |      1      |     1     |3(switch on) |
     Disable Voltage|      0      |       X      |      X     |      0      |     X     |  7,9,10,12  |
        Quick Stop  |      0      |       X      |      0     |      1      |     X     |   7,10,11   |
   Disable Operation|      0      |       0      |      1     |      1      |     1     |      5      |
    Enable Operation|      0      |       1      |      1     |      1      |     1     |  3&4,4,16   |
       Fault Reset  |   Rising    |       X      |      X     |      X      |     X     |      15     |
    ————————————————————————————————————————————————————————————————————————————————————————————————————————
    Ⅲ、状态字6041h：
               Bit                        State
    | 6 | 5 | 3 | 2 | 1 | 0 |
    ——————————————————————————————————————————————————————
    | 0 | X | 0 | 0 | 0 | 0 | (1) Not Ready to Switch On
    | 1 | X | 0 | 0 | 0 | 0 | (2) Switch on Disabled
    | 0 | 1 | 0 | 0 | 0 | 1 | (3) Ready to Switch On
    | 0 | 1 | 0 | 0 | 1 | 1 | (4) Switched On
    | 0 | 1 | 0 | 1 | 1 | 1 | (5) Operation enabled
    | 0 | 0 | 0 | 1 | 1 | 1 | (6) Quick Stop Active
    | 0 | X | 1 | 1 | 1 | 1 | (7) Fault Reactive
    | 0 | X | 1 | 0 | 0 | 0 | (8) Fault
    ————————————————————————————————————————————————————————————————————————————————————————————————————————
    */
    /*----------------------------------------------------------------------------------------------*/
    /* 3.快速停机状态字问题解决                                                                      */
    /*----------------------------------------------------------------------------------------------*/
    if(ControlStatus == 6)
    {
        QuickStop_flag = 1;
    }
    else
    {
        QuickStop_flag = 0;
    }
    /*----------------------------------------------------------------------------------------------*/
    switch(ControlStatus)
    {
        /*------------------------------------------------------------------------------------------*/
        case 0:                                             //Start(0)
            StatusWord.w = 0x0000;
            ControlStatus = 1;                      //Transition 0: Startup => Not Ready to Switch ON
            break;
        /*------------------------------------------------------------------------------------------*/
        case 1:                                             //Not Ready to Switch ON(1)
            /*--------------------------------------------------------------------------------------*/
            StatusWord.w &= 0xFFB0;                         //1111 1111 1011 0000 清bit0~bit3和bit6
            /*--------------------------------------------------------------------------------------*/
            if(CoutV.f.Seq.MainPowerOn == 1)
            {
                ControlStatus = 2;                  //Transition 1: Not Ready to Switch ON => Switch On Disabled
            }
            /*--------------------------------------------------------------------------------------*/
            break;
        /*------------------------------------------------------------------------------------------*/
        case 2:                                             //Switch On Disabled(2)
            /*--------------------------------------------------------------------------------------*/
            StatusWord.w &= 0xFFB0;
            StatusWord.f.SwitchOnDisable= 1;
            /*--------------------------------------------------------------------------------------*/
            if((ControlWord.w & 0x008F) == 0x0006 || (ControlWord.w & 0x008F) == 0x000E)
            {
                ControlStatus = 3;                  //Transition 2: Switch On Disabled => Ready to Switch On
            }

            /*-----------------------------------非标------------------------------------------*/
            if( (ControlWord.w & 0x001F) == 0x001F )          // @20230803
            {
                ControlStatus = 3;                  //Transition 2: Switch On Disabled => Ready to Switch On
            }
            break;
        /*------------------------------------------------------------------------------------------*/
        case 3:                                             //Ready to Switch On(3)
            /*--------------------------------------------------------------------------------------*/
            StatusWord.w &= 0xFFB0;
            StatusWord.f.Rdy2SwitchOn = 1;
            StatusWord.f.QuickStop = 1;
            /*--------------------------------------------------------------------------------------*/
           // if((ControlWord.w & 0x008F) == 0x0007 || (ControlWord.w & 0x008F) == 0x000F)
            if((ControlWord.w & 0x008F) == 0x0007)
            {
                ControlStatus = 4;                  //Transition 3: Ready to Switch On => Switched On

                //----------------------------------------------------------------------------------
                //  测试 @20240305
                //----------------------------------------------------------------------------------i
                if( CinV.f.Seq.ServoOffDecM == TRUE )
                {
                    CinV.f.Seq.ServoOffDecM = FALSE;
                }
            }
            /*--------------------------------------------------------------------------------------*/
            if((ControlWord.f.FaultReset == 0) && ((ControlWord.f.EnableVoltage == 0) \
                                               || ((ControlWord.f.EnableVoltage == 1) \
                                               && (ControlWord.f.QuickStop == 0))))
            {
                ControlStatus = 2;                  //Transition 7: Ready to Switch On => Switch On Disabled
            }

            /*------------------------------------非标---------------------------------------------*/
            if( CAN_EXFUNC0_1_EN )
            {
                if( (ControlWord.w & 0x000F) == 0x0006 )
                {
                    ControlStatus = 4;              //状态转换3
                }
            }
            /*--------------------------------------------------------------------------------------*/
            break;
        /*------------------------------------------------------------------------------------------*/
        case 4:                                             //Switched On(4)
            /*--------------------------------------------------------------------------------------*/
            StatusWord.w &= 0xFFB0;
            StatusWord.f.Rdy2SwitchOn = 1;
            StatusWord.f.SwitchOn = 1;
            StatusWord.f.QuickStop = 1;
            /*--------------------------------------------------------------------------------------*/
            if((ControlWord.w & 0x008F) == 0x000F)
            {
                ControlStatus = 5;                  //Transition 4: Switched On => Operation Enable
            }
            /*--------------------------------------------------------------------------------------*/
            if((ControlWord.w & 0x008F) == 0x0006 || (ControlWord.w & 0x008F) == 0x008E)
            {
                ControlStatus = 3;                  //Transition 6: Switched On => Ready to Switch On
            }
            /*--------------------------------------------------------------------------------------*/
            if((ControlWord.f.FaultReset == 0) && ((ControlWord.f.EnableVoltage == 0) \
                                               || ((ControlWord.f.EnableVoltage == 1) \
                                               && (ControlWord.f.QuickStop == 0))))
            {
                ControlStatus = 2;                  //Transition 10: Switched On => Switch On Disabled
            }

            /*-------------------------------------非标------------------------------------------*/
            if( CAN_EXFUNC0_1_DIS )
            {
                /*--------------------------------------------------------------------------------------*/
                if((ControlWord.f.EnableVoltage == 0x0 ) || (ControlWord.w & 0x0006) == 0x0002)
                {
                    ControlStatus = 2;              //状态转换10
                }
            }
            /*--------------------------------------------------------------------------------------*/
            break;
        /*------------------------------------------------------------------------------------------*/
        case 5:                                             //Operation Enable(5)
            /*--------------------------------------------------------------------------------------*/
            StatusWord.w &= 0xFFB0;
            StatusWord.f.Rdy2SwitchOn = 1;
            StatusWord.f.SwitchOn = 1;
            StatusWord.f.OperationEnable = 1;
            StatusWord.f.QuickStop = 1;
            /*--------------------------------------------------------------------------------------*/
            if((ControlWord.w & 0x008F) == 0x0007)
            {
                ControlStatus = 4;                  //Transition 5: Operation Enable => Switched On
            }
            /*--------------------------------------------------------------------------------------*/
            if((ControlWord.w & 0x008F) == 0x0006 || (ControlWord.w & 0x008F) == 0x008E)
            {
                ControlStatus = 3;                  //Transition 8: Operation Enable => Ready to Switch On
            }
            /*--------------------------------------------------------------------------------------*/
            if((ControlWord.f.FaultReset == 0) && (ControlWord.f.EnableVoltage == 0))
            {
                ControlStatus = 2;                  //Transition 9: Operation Enable => Switch On Disabled
            }
            /*--------------------------------------------------------------------------------------*/
            if((ControlWord.f.FaultReset == 0) && (ControlWord.f.EnableVoltage == 1) && (ControlWord.f.QuickStop == 0))
            {
                ControlStatus = 6;                  //Transition 11: Operation Enable => Quick Stop Active
            }
            /*--------------------------------------------------------------------------------------*/
            break;
        /*------------------------------------------------------------------------------------------*/
        case 6:                                             //Quick Stop Active(6)
            /*--------------------------------------------------------------------------------------*/
            StatusWord.w &= 0xFFB0;
            StatusWord.f.Rdy2SwitchOn = 1;
            StatusWord.f.SwitchOn = 1;
            StatusWord.f.OperationEnable = 1;
            StatusWord.f.QuickStop = 0;
            /*--------------------------------------------------------------------------------------*/
            if((ControlWord.f.FaultReset == 0) && (ControlWord.f.EnableVoltage == 0))
            {
                ControlStatus = 2;                  //Transition 12: Quick Stop Active => Switch On Disabled
            }
            /*--------------------------------------------------------------------------------------*/
            if((ControlWord.w & 0x008F) == 0x000F)
            {
                ControlStatus = 5;                  //Transition 16: Quick Stop Active => Operation Enable
            }

            /*-------------------------------------非标--------------------------------------------*/
            if((ControlWord.w & 0x000F) == 0x0006)
                ControlStatus = 2;                  //状态转换8
            /*--------------------------------------------------------------------------------------*/
            break;
        /*------------------------------------------------------------------------------------------*/
        case 7:                                             //Fault Reaction Active(7)
            /*--------------------------------------------------------------------------------------*/
            StatusWord.w &= 0xFFB0;
            StatusWord.f.Rdy2SwitchOn = 1;
            StatusWord.f.SwitchOn = 1;
            StatusWord.f.OperationEnable = 1;
            StatusWord.f.Fault = 1;
            /*--------------------------------------------------------------------------------------*/
            ControlStatus = 8;                      //Transition 14: Fault Reaction Active => Fault
            /*--------------------------------------------------------------------------------------*/
            break;
        /*------------------------------------------------------------------------------------------*/
        case 8:                                             //Fault(8)
            /*--------------------------------------------------------------------------------------*/
            StatusWord.w &= 0xFFB0;
            StatusWord.f.Fault = 1;
            if( CAN_EXFUNC0_1_DIS )
            {
                if(ControlWord.f.FaultReset == 0x1)
                {
                    ControlStatus = 2;              //Transition 15: Fault => Switch On Disabled
                }
            }
            break;
        default:
            /*--------------------------------------------------------------------------------------*/
            StatusWord.w &= 0xFFB0;
            /*--------------------------------------------------------------------------------------*/
            ControlStatus = 7;                      //状态不存在也会跳转至Fault Reaction Active(7)
            break;

    }

    /*----------------------------------------------------------------------------------------------*/
    /* 2.故障触发，任意状态通过状态转换13切换至Fault Reaction Active(7)状态                           */
    /*----------------------------------------------------------------------------------------------*/
    if(Alm.f.AlmFlag == 1)
    {
        if(ControlStatus != 8)
        {
            ControlStatus = 7;                     //Transition 13: Any State => Fault Reaction Active
        }
    }
    else
    {
        ;
    }

    return ControlStatus;
}
