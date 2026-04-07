/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 ? All right Reserved                                   */
/*											2019 ~													*/
/****************************************************************************************************/
/*文件名:Pr05_OrgS.c                                                                                */
/*创建时间: 2019.9.3                                                                              */
/*版本说明: V1.0                                                                                    */
/*功能描述: 原点回归                                                                                */
/****************************************************************************************************/
#include "Main.h"


/*---------------------------------------------------------------------------------------------*/
/*
MencP.PulseNo           :单圈编码器指令，24位编码器对应16777216
RoutV.ABSEncSValue      :单圈编码器位置，实时位置（62.5us更新一次）
CoutRrst.UnPfbkCntr2    :编码器反馈脉冲数（增量式）
*/
/*---------------------------------------------------------------------------------------------*/
//参数定义
UCHAR   OrgFirstFlg = 0;    //第一次原点回归标志
LLONG   ZeroPosPulse = 0;   //零点位置脉冲值
USHORT  OrgType = 0;        //原点回归类型
UCHAR   OrgEnStatus = 0;    //原点回归使能信号（0：低电平  1：上升沿  2：下降沿  3高电平）

USHORT PrOrgCtlBitTable[14] =
{/*0      1        2       3      4        5       6      */
0x0091, 0x011D, 0x00B1, 0x017D, 0x0082, 0x010E, 0x00E2,   //6
0x012E, 0x00A0, 0x0164, 0x0085, 0x0003, 0x0003, 0x0003,   //13
};

//=========================================================================
//函数名称：OrgEnCheck()原点回归使能判断
//函数功能：根据功能码P290判断原点回归使能方式
//=========================================================================
USHORT OrgSearchDelay = 0;
void OrgEnCheck(void)
{
    USHORT OrgCtlWrdBit8 = 0;               //原点回归总开关
//    USHORT PosNum = 0;                      //段位段号
    UCHAR  DI_TrigMode=0;                   //DI触发方式选择  0：上升沿触发  1：高低电平（低电平强制停止）
    static UCHAR OrgCtlWrdBit8_Old;
    

    //判断Pn290的低4位是否为2，为2的情况下，第一次servo on立即进行原点回归 
    OrgCtlWrdBit8 = Prm.orgmode & 0x000F;
    DI_TrigMode = ( Prm.orgmode >> 8 ) & 0x000F;
    if(OrgCtlWrdBit8 == 2)
    {
#if 1
        if( OrgSearchDelay < 100 )
        {
            OrgSearchDelay ++;
        }
        else
        {
            if(!OrgFirstFlg)
            {
                Prm.b_prm0_1 |= 0x0001;     //使能驱动器
                OrgStr.ExternOrgEnFlg = 1;
                OrgFirstFlg = 1;
            }
        }
#else        
        if(!OrgFirstFlg)
        {
            OrgStr.ExternOrgEnFlg = 1;
            Prm.b_prm0_1 |= 0x0001;     //使能驱动器
        }
#endif        
        if( Prm.PrCommSet == 1000 )
        {
            OrgStr.ExternOrgEnFlg = 0;
            Prm.PrCommSet = 10000;
            OrgControlBit.bit.OrgDone = 1;
            OrgStr.OrgCompStatus = 3;
        }
    }
    else if(OrgCtlWrdBit8 == 3 && OrgFirstFlg)
    {
        Prm.orgmode &= 0xFFF0;
        Prm.orgmode |= 0x0001;
        if(OrgCtlWrdBit8_Old!=3)
        {
            OrgStr.ExternOrgEnFlg = 1;
        }
    }
    else if( (!OrgCtlWrdBit8) || Prm.PrCommSet == 1000 )
    {
        OrgStr.ExternOrgEnFlg = 0;
        if(Prm.PrCommSet == 1000)
        {
            Prm.PrCommSet = 10000;
            OrgControlBit.bit.OrgDone = 1;
            OrgStr.OrgCompStatus = 3;
        }
        OrgFirstFlg = 1;                        //第一次伺服上电标志位
        return;
    }
    
    OrgCtlWrdBit8_Old = OrgCtlWrdBit8;
    if(DI_TrigMode == 0)
    {
         if(OrgEnStatus == 0x03)            //高电平
         {
            OrgStr.ExternOrgEnFlg = 0; 
            OrgControlBit.bit.OrgDone = 1;
            OrgStr.OrgCompStatus = 3;
         }
         else if(OrgEnStatus == 0x02)       //下降沿
         {
            OrgStr.ExternOrgEnFlg = 1;
         }
         
         else if(OrgEnStatus == 0x0)
         {
            OrgStr.ExternOrgEnFlg = 1;
         }
    }
    else if(DI_TrigMode == 1)
    {
         //HomeStart信号上升沿触发原点使能
        if(OrgEnStatus == 0x01)
        {
            OrgStr.ExternOrgEnFlg = 1;
        }
    }
    else if(DI_TrigMode == 2)
    {
        if(OrgEnStatus == 0x02)
        {
            OrgStr.ExternOrgEnFlg = 1;
        }
    }
    else
    {
         if(OrgEnStatus == 0x03)            //上升沿
         {
            OrgStr.ExternOrgEnFlg = 1; 
         }
         else if(OrgEnStatus == 0x00)       //低电平
         {
            OrgStr.ExternOrgEnFlg = 0;
            OrgControlBit.bit.OrgDone = 1;
            OrgStr.OrgCompStatus = 3;
         }
    }
    
    //通讯触发原点回归
    if(Prm.PrCommSet == 0)
    {
        OrgStr.ExternOrgEnFlg = 1;          //原点回归功能开启
    }
    
    if( BinV.f.BaseEnable == 0 && OrgCtlWrdBit8 != 2 )
    {
        OrgStr.ExternOrgEnFlg = 0;          //原点回归功能开启
    }
    
    if( (Prm.orgmode & 0x000F) != 0x0002 )
    {
        OrgFirstFlg = 1;                        //第一次伺服上电标志位
    }
    /*----------------回零标志置1，ScanB中处理原点位置脉冲---------------------*/  
    if(OrgStr.ExternOrgEnFlg)
    {
        Prm.PrCommSet = 10000;
    }
    BinV.f.Sv.OrgPulseEn = OrgStr.ExternOrgEnFlg ;
//    CinV.f.Sv.OTCheck    = OrgStr.ExternOrgEnFlg ;
}

//=========================================================================
//函数名称：OrgParaInitial()原点回归初始化
//函数功能：进行原点回归参数输出化
//=========================================================================
USHORT RotaryDirection;
void OrgParaInitial(void)
{ 
    //  UCHAR DelayNum = 0;//延时时间选择
    LLONG DateTemp1 = 0;   //数据计算临时变量1
    LLONG DateTemp2 = 0;   //数据计算临时变量2
      
    RotaryDirection = (Prm.b_prm0_0 >> 4)&0x0f;
    //原点回归控制参数初始化
    OrgType = (Prm.orgmode>>4) & 0x000F;

    if(OrgType > 10)
    {
        OrgStr.OrgStep = ORG_FAIL;
        return;
    }
    OrgControlBit.all = PrOrgCtlBitTable[OrgType];

    //原点回归完成标志位清零
    OrgControlBit.bit.OrgDone = 0;
    OrgControlBit.bit.OrgFail = 0;
    //原点回归使能参数初始化 状态过渡到高速原点搜索
    
    PrSpeed_AccDec_CoefCount();         //计算加减速基值
    //加减速基值Q15格式计算
    OrgStr.OrgAccDecBaseQ15 = (ACCDECCoeffQ15>>3) /(Prm.orgdecacc+1);
    //回原点高速速度值给定
    DateTemp1 = (SHORT)Prm.orgspdhight;
    OrgStr.OrgSpdHQ15 = (DateTemp1*(ACCDECCoeffQ15))/30000;
    //回原点低速速度值给定
    DateTemp2 = (SHORT)Prm.orgspdlow;
    OrgStr.OrgSpdLQ15 = (DateTemp2*ACCDECCoeffQ15)/30000;
    //延时时间段号选择
    //  DelayNum = (Var_N039.Var801&0x7000)>>12;
    //  OrgStr.OrgWaitTim = (ULONG)*(&Var_N039.Var890 + DelayNum)*50;
    //初始化原点回归状态切换
    if(OrgType == 10)
    {
        OrgStr.OrgStep = ORG_OFFSET;  
    }
    else
    {
        OrgStartStateCheck();
    }

}

//=========================================================================
//     函数名称：OrgZeroPosDeal()零点位置运行
//     函数功能：原点位置和零点位置不重合情况下，运行到零点位置
//=========================================================================
//LLONG OrgPosOffset = 0;               //原点偏置值
UCHAR ZeroRunSpeed= 0;
UCHAR LimtUseFlag = 0;                  //绝对值回零限位有效标志
void Pr_OrgZeroPosDeal(void)
{
    
    LONG    ZposDelta = 0;              //Z脉冲移动距离计算值
    LLONG   MotFbkPos = 0;              //电机反馈单圈位置（用户单位）
    LLONG   OrgPosOffset_temp;          //绝对值回零的脉冲数
    LLONG   OrgPosSet;
    LLONG   MotPosFbk;
    LONG    EncNum;
    LONG    EncDen;
    LONG    DataTmp = 0;
    
    MotFbkPos = (LLONG)RoutV.ABSEncSValue * EGearDen / MencP.PulseNo;
    
    OrgPosOffset = (LLONG)( ( (LONG)Prm.orgoffsetH << 16) + (USHORT)Prm.orgoffsetL );
    if(!OrgPosOffset)
    {
        if(OrgControlBit.bit.OrgSwithType == Z_SIGN)
        {
            ZeroRunSpeed = SpeedHigh;
        }
        else
        {
            ZeroRunSpeed = SpeedLow;    //原点偏置为0，最后低速运行到Z脉冲
        }
    }
    else
    {
        ZeroRunSpeed = SpeedHigh;       //原点偏置不为0，最后高速运行到偏置点
    }
    
    if( OrgType < 10 )
    {
        //Z脉冲位置计算
        if(OrgControlBit.bit.OrgZEndFlg == ORG_Z_YES)
        {
          //正方向找第一个Z脉冲为原点
          if(OrgControlBit.bit.OrgZPulseDir == ORG_Z_DIR_POS)
          {
              if(RotaryDirection == 0)
              {
                  ZposDelta = EGearDen - MotFbkPos;
              }
              else
              {
                  ZposDelta = -(LLONG)MotFbkPos;
              }
          }
          //反方向找第一个Z脉冲为原点
          else if(OrgControlBit.bit.OrgZPulseDir == ORG_Z_DIR_NEG)
          { 
              if(RotaryDirection == 0)
              {
                  ZposDelta = -(LLONG)MotFbkPos;
              }
              else
              {
                  ZposDelta = EGearDen - MotFbkPos;
              }
          }
        }
        else if(OrgControlBit.bit.OrgZEndFlg == ORG_Z_NO)
          ZposDelta = 0;
        //需要走的位置总量计算，去除脉冲偏差
        if(RotaryDirection == 0)
        {
            OrgPosOffset = OrgPosOffset + ZposDelta - BoutV.AmonPosErra;
        }
        else
        {
            OrgPosOffset = OrgPosOffset - ZposDelta - BoutV.AmonPosErra;
        }
    }
    else
    {
      
#if 0      
        OrgPosOffset_temp   = (LLONG)( (SHORT)Prm.orgMpos - RoutV.ABSEncMValue ) * EGearDen;
        OrgPosOffset_temp  += (LLONG)( ( Prm.orgSposH << 16 ) + Prm.orgSposL ) * EGearDen / MencP.PulseNo;
        OrgPosOffset_temp  -=  MotFbkPos;
#else
        EncNum = ( (ULONG)Prm.ratb2h << 16 ) + Prm.ratb2l;         /* 分子   */
        if( EncNum == 0 )
        {
            EncNum = MencP.PulseNo;
        }
        EncDen = ( (ULONG)Prm.rata2h << 16 ) + Prm.rata2l;         /* 分母   */
        /*------------------------------------------------------------------------------------------*/
        /* 用户原点设定值                                                                           */
        /*------------------------------------------------------------------------------------------*/
        DataTmp = ( (ULONG)Prm.orgSposH << 16 ) + Prm.orgSposL;
        OrgPosSet = ( (LLONG)(SHORT)Prm.orgMpos ) * MencP.PulseNo + DataTmp ;

        /*------------------------------------------------------------------------------------------*/
        /* 电机编码器实际反馈值                                                                     */
        /*------------------------------------------------------------------------------------------*/
        MotPosFbk = (LLONG)RoutV.ABSEncMValue  * MencP.PulseNo + RoutV.ABSEncSValue;
        /*------------------------------------------------------------------------------------------*/
        /* 给定和反馈值偏差                                                                         */
        /*------------------------------------------------------------------------------------------*/
        OrgPosOffset_temp = OrgPosSet - MotPosFbk;
        
        /*------------------------------------------------------------------------------------------*/
        /* 偏差转换成用户单位                                                                       */
        /*------------------------------------------------------------------------------------------*/
        OrgPosOffset_temp = OrgPosOffset_temp * EncDen / EncNum;
#endif        
        
        OrgPosOffset       +=  OrgPosOffset_temp;       
        
        OrgPosOffset_temp   = OrgPosOffset << 15;

        if( ( OrgPosOffset_temp > OrgStr.OrgSpdHQ15 ) || ( OrgPosOffset_temp < -OrgStr.OrgSpdHQ15 ) )
        {
            ZeroRunSpeed    =  SpeedHigh;   //绝对值回零，高速找原点
        }
        else
        {
            ZeroRunSpeed    =  SpeedLow;    //绝对值回零位置过小，会错过原点
        }
        /*------------------------------------------------------------------------------------------*/
        if(Prm.b_prm0_0D & 0x3000 == 0)
        {
            LimtUseFlag = 1;
        }
        else
        {
            LimtUseFlag = 0;
        }
    }
    //状态切换
    OrgStr.OrgStep = ORG_ZERO;
    OrgStr.OrgCmdOutQ15 = 0;
    PosOut = 0;                             //中间变量，找零点之前先将该变量清零
}
//==================================================================================================
//     函数名称：Pr_OrgZeroPoDec()计算减速点与零点距离
//     函数功能：从减速点运行到零点位置的距离   ORG_OFFSET_SEC
//==================================================================================================
LLONG ZposDelta = 0; //20211117
void Pr_OrgZeroPoDec(void)
{
     LLONG   MotFbkPos = 0;              //电机反馈单圈位置（用户单位）
    
     MotFbkPos = (LLONG)RoutV.ABSEncSValue * EGearDen / MencP.PulseNo;
                           
     if(OrgControlBit.bit.OrgZPulseDir == ORG_Z_DIR_POS)
      {
          if(((Prm.b_prm0_0 >> 4)&0x0f) == 0)
           {
                ZposDelta = EGearDen - MotFbkPos;
            }
           else
            {
                ZposDelta = -(LLONG)MotFbkPos;
             }
        }
       //反方向找第一个Z脉冲为原点
       else if(OrgControlBit.bit.OrgZPulseDir == ORG_Z_DIR_NEG)
       { 
           if(((Prm.b_prm0_0 >> 4)&0x0f) == 0)
            {
                 ZposDelta = -(LLONG)MotFbkPos;
             }
           else
             {
                 ZposDelta = EGearDen - MotFbkPos;
              }
         }
     
       ZposDelta=ZposDelta-BoutV.AmonPosErra;
       OrgStr.OrgStep = ORG_LOW;
       PosOut = 0;                             //中间变量，找零点之前先将该变量清  
}


//==================================================================================================
//     函数名称：Pr_OrgLoe()找Z    ORG_LOW
//     函数功能：从减速点运行到零点位置
//==================================================================================================
LLONG PosRemFirst = 0;                   //剩余脉冲值
void Pr_OrgLoe()
{   
    LLONG PosSpdOutDe = 0;                //位置指令速度输出
    
    OrgPosOffset = (LLONG)( ( (LONG)Prm.orgoffsetH << 16) + (USHORT)Prm.orgoffsetL );
    //剩余脉冲计算
    
    PosRemFirst = ( ZposDelta <<15 ) - PosOut;
    
    if(PosRemFirst < 0)                      //剩余脉冲正负判断
    {
        PosRemFirst = -PosRemFirst;
     }
    
    if(LimtUseFlag)                    //绝对值回零速度较快，加入超程保护
    { 
        if(NegLimit == 1||PosLimit == 1)
        {
            OrgStr.OrgStep = ORG_FAIL;
            return;
         }
    }
       
     if(PosRemFirst <= OrgStr.OrgSpdLQ15)
      {
          if(!OrgPosOffset)
          {  
             OrgStr.OrgCmdOutQ15 = ( ZposDelta <<15 ) - PosOut;
                    
             OrgStr.OrgStep = ORG_OK;//状态切换
                    
             PosOut = 0;             //变量清零
          }
          else
          {
              OrgStr.OrgCmdOutQ15 = ( ZposDelta <<15 ) - PosOut;
                    
              OrgStr.OrgStep = ORG_OFFSET;//状态切换
                    
              PosOut = 0;             //变量清零
          } 
       }
     else
       {                    
          if((OrgType==2)||(OrgType==7)||(OrgType==8))
               PosSpdOutDe = OrgStr.OrgSpdLQ15;             
          if((OrgType==3)||(OrgType==6)||(OrgType==9))
               PosSpdOutDe = -OrgStr.OrgSpdLQ15;
         }
    

      PosOut += PosSpdOutDe;                    //输出脉冲统计 
      OrgStr.OrgCmdOutQ15 = PosSpdOutDe;        //脉冲输出
}
//=========================================================================
//     函数名称：OrgZeroRun()零点位置运行
//     函数功能：从原点位置运行到零点位置
//=========================================================================
//LLONG PosOut = 0;          //脉冲输出值  zhuxc0610
void Pr_OrgZeroRun()
{
    LLONG PosRem = 0;                   //剩余脉冲值
    LLONG PosSpdOut = 0;                //位置指令速度输出
    
    //剩余脉冲计算
    PosRem = ( OrgPosOffset <<15 ) - PosOut;
    
    if(PosRem < 0)                      //剩余脉冲正负判断
    {
        PosRem = -PosRem;
    }
    if(LimtUseFlag)                    //绝对值回零速度较快，加入超程保护
    { 
        if(NegLimit == 1||PosLimit == 1)
        {
            OrgStr.OrgStep = ORG_FAIL;
            return;
        }
    }
    
    switch(ZeroRunSpeed)                //判断是否完成
    {
        case SpeedHigh:
            {
                if(PosRem <= OrgStr.OrgSpdHQ15)
                {
                    OrgStr.OrgCmdOutQ15 = (OrgPosOffset<<15) - PosOut;
                    
                    OrgStr.OrgStep = ORG_OK;//状态切换
                    
                    PosOut = 0;             //变量清零
                }
                else
                {
                    
                    if(OrgPosOffset < 0)    //判断目标速度正负
                        PosSpdOut = -OrgStr.OrgSpdHQ15;
                    else
                        PosSpdOut = OrgStr.OrgSpdHQ15;
                }
                break;
            }   
        case SpeedLow:
            {
                if(PosRem <= OrgStr.OrgSpdLQ15)
                {
                    OrgStr.OrgCmdOutQ15 = (OrgPosOffset<<15) - PosOut;
                    
                    OrgStr.OrgStep = ORG_OK;//状态切换
                    
                    PosOut = 0;             //变量清零
                }
                else
                {
                    
                    if(OrgPosOffset < 0)    //判断目标速度正负
                        PosSpdOut = -OrgStr.OrgSpdLQ15;
                    else
                        PosSpdOut = OrgStr.OrgSpdLQ15;
                }
                break;
            }
           default:
              break;
    }
    PosOut += PosSpdOut;                    //输出脉冲统计 
    OrgStr.OrgCmdOutQ15 = PosSpdOut;        //脉冲输出
}
//=========================================================================
//函数名称：OrgOKDeal()
//函数功能：原点回归完成 参数清零
//=========================================================================
void Pr_OrgOKDeal(void)
{
    LONG OrgOffsetTemp = 0;                                                             //原点偏置值
    
    CinV.f.Sv.OTCheck = 0 ;                                                             //打开限位

    OrgStr = OrgStrDefault;
    OrgStr.ExternOrgEnFlg = 0;
    OrgOffsetTemp = (LLONG)(LLONG)(((LONG)Prm.orgoffsetH<<16)+(USHORT)Prm.orgoffsetL);  //原点偏赋值
    //原点回归完成标志置1
    OrgControlBit.bit.OrgDone = 1;
    //判断Pn002正反向
    if(RotaryDirection == 0)
    {
        ZeroPosPulse = CoutRrst.UnPfbkCntr2+PosCurvV.PosRemain - OrgOffsetTemp; //初始位置赋值
        PosCurvV.PosCmdOut = -PosCurvV.PosRemain;                               //增量脉冲计数器清零 
    }
    else
    {
        ZeroPosPulse = CoutRrst.UnPfbkCntr2-PosCurvV.PosRemain+OrgOffsetTemp;   //初始位置赋值
        PosCurvV.PosCmdOut = PosCurvV.PosRemain;                                //增量脉冲计数器清零
    }
    PosOut = 0;
    
    Pr_DICtrgV.PosCmdSum = 0;                                                   //找到原点后，点位的绝对位置置0
    Pr_DICtrgV.PosFbkDelt = CoutRrst.UnPfbkCntr2;                               //原点回归结束时的反馈脉冲（用户单位）
}
//==================================================================================================
//     函数名称：OrgFailDeal()原点回归失败处理
//     函数功能：原点回归失败后，如果错误清楚，则重新进行原点回归
//==================================================================================================
void Pr_OrgFailDeal(void)
{
    
    OrgControlBit.bit.OrgFail = 1;              //原点回归失败标志
    //原点回归控制清零
    OrgStr = OrgStrDefault;   
    OrgStr.ExternOrgEnFlg = 0;
    PosOut = 0;
    CinV.f.Sv.OTCheck = 0 ;                     //打开限位
}

//=========================================================================
//函数名称：OrgStateMachine()原点回归状态机
//函数功能：原点回归不同状态间切换
//=========================================================================
void Pr_OrgStateMachine(void)
{
    //原点回归状态机执行
    switch( OrgStr.OrgStep )
    {

        case ORG_SPDH:
        {
            //高速搜索原点
            HighSpdSearch();
            break;
        }
        case ORG_SPDH_DEC:
        {
            //高速减速
            HighSpdDec();
            break;
        }
/*----------------------------------------------------------------------------------------------*/
        case ORG_SPDL_SECOND:                                          /* 低速搜索原点                     */
          { 
             LowSpdSearch_SECOND();
             break;
          }
        
        case ORG_SPDL_DEC_SECOND:                                            /* 低速减速            */
          {  
             LowSpdDec_SECOND();
             break;
          }
        case ORG_SPDH_SPDL_DEC:                                      /* 高速减速                         */
          {  
             HighLowSpdDec();
             break;
          }
        case ORG_LOW:
        {
            Pr_OrgLoe();
            break;
         }
        case ORG_OFFSET_SEC:
        {
            Pr_OrgZeroPoDec();
            break;
         }
/*----------------------------------------------------------------------------------------------*/ 
        case ORG_SPDL:
        {
            //低速搜索原点
            LowSpdSearch();
            break;
        }
        case ORG_SPDL_DEC:
        {
            //低速减速
            LowSpdDec();
            break;
        }
        case ORG_SWITCH_CHECK:
        {
            //开关量信号状态确认
            OrgSwitchDirCheck();
            break;
        }
        case ORG_OFFSET:
        {
            //从原点运行到零点位置
            Pr_OrgZeroPosDeal();
            break;
        }
        case ORG_ZERO:
        {
            Pr_OrgZeroRun();
            break;
        }
        case ORG_OK:
        {
            //原点回归完成 参数清零
            Pr_OrgOKDeal();
            break;
        }
        case ORG_FAIL:
        {
            Pr_OrgFailDeal();
        }
        default:
            break;
    }
}
//=================================================================================
//  子函数：    F_OrgFunction() 原点回归功能函数
//  子函数功能：原点回归位置规划
//  函数运行时间：125us
//=================================================================================
void F_OrgFunction(void)
{
    
    if( OrgStr.ExternOrgEnStatus == 0x01 )
    {
        OrgParaInitial();               //参数初始化、状态机切换到原点搜索状态
    }
    /******************************限位警告检出************************************/
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
    //原点回归状态机执行
    Pr_OrgStateMachine();
    //脉冲指令输出计算    zhuxc
    OrgStr.OrgCmdOut = (OrgStr.OrgCmdOutQ15 + OrgStr.RemainPulsQ15)>>15;
    OrgStr.RemainPulsQ15 = OrgStr.OrgCmdOutQ15 + OrgStr.RemainPulsQ15   \
                    - (OrgStr.OrgCmdOut<<15);
    AinK.ORGDelta = OrgStr.OrgCmdOut;
}
//=================================================================================
//  子函数：    OrgDiCheck() 原点信号检测
//  子函数功能：根据DI端子检测原点信号和原点使能信号
//=================================================================================


void OrgDiCheck(void)
{
    
//    if(CoutV.f.Ctrl.OrgC)
//    {
//        Prm.orgmode &= 0x0FFF;
//        Prm.orgmode |= 0x2000;                          //原点回归成功
//    }
//    else
//    {
//        if(OrgControlBit.bit.OrgFail)
//        {
//            Prm.orgmode |= 0x3000;                      //原点回归失败
//        }
//        else if(OrgStr.ExternOrgEnStatus ==0x03)
//        {
//            Prm.orgmode &= 0x0FFF;
//            Prm.orgmode |= 0x1000;                      //原点回归进行中
//        }
//        else if(OrgStr.ExternOrgEnStatus == 0x00)
//        {
//            Prm.orgmode &= 0x0FFF;                      //未进行原点回归或是终止原点回归
//        }
//    }

    PosLimit = CinV.f.Sv.PotIn;            //正限位
    NegLimit = CinV.f.Sv.NotIn;            //负限位
                   
    /*------------------------------------------------------------------------------------------*/
    /* 原点回归状态                                                                              */
    /*------------------------------------------------------------------------------------------*/
   
    OrgStr.ExternOrgEnStatus = ( OrgStr.ExternOrgEnStatus<<1 ) & 0x03;
    OrgStr.ExternOrgEnStatus|=   OrgStr.ExternOrgEnFlg;
    

    DISignReach = BinV.f.Sv.ORGS;                   //0x28  原点信号位
    
    
    /*----------------------------------------------------------------------------------------------*/
    /* 只有在原点回归端子使能时才能有效 @20210610                                                   */
    /*----------------------------------------------------------------------------------------------*/
    if( (Prm.orgmode & 0x000F) == 0x0001 )
    {
        OrgEnStatus = ( OrgEnStatus<<1 ) & 0x03;        //0x27  原点回归使能
        OrgEnStatus|= BinV.f.Sv.ORGEn;    }
    else
    {
        OrgEnStatus = 0;    
    }

    
    /*-------------------------------------------------------------------------------------*/
    if(OrgStr.ExternOrgEnStatus == 0x01)
    {
        CinV.f.Sv.OTCheck = 1 ;         //屏蔽限位
    }
    else if(OrgStr.ExternOrgEnStatus == 0x02)
    {
        CinV.f.Sv.OTCheck = 0 ;         //打开限位
    }

    /*-------------------------------------------------------------------------------------*/
    
    /*------------------------------------------------------------------------------------------*/
    /* 原点信号沿触发状态判断                                                                   */
    /*------------------------------------------------------------------------------------------*/
    if(DISignReach == 1 && DISignOld == 0)
    {
        OrgPrCtlBit.OrgSignUp = 1;
        OrgPrCtlBit.OrgSignDown = 0;
    }
    else if(DISignReach == 0 && DISignOld == 1)
    {
        OrgPrCtlBit.OrgSignUp = 0;
        OrgPrCtlBit.OrgSignDown = 1;
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
    
    //前一拍赋值
    DISignOld = DISignReach;
    
    NegLimitOld = NegLimit;
    PosLimitOld = PosLimit;
}

//=================================================================================
//  子函数：    OrgOutput() 原点回归完成输出
//  子函数功能：输出原点回归状态（完成/没完成）
//=================================================================================
void OrgOutput(void)
{
    static ULONG OrgTimeCnt;
    ULONG OrgOverTime = 0;
    /*------------------------原点回归状态监测-----------------------*/
    if( ( !BinV.f.BaseEnable )  && \
        ( !CoutV.f.Sv.Ot ) && \
        ( !OrgStr.ExternOrgEnFlg ))
    {
        OrgStr.OrgCompStatus      = 3;
        OrgStr.ExternOrgEnFlg     = 0;
        OrgControlBit.bit.OrgDone = 1;
        OrgTimeCnt                = 0;
        return;
    }
    
    OrgStr.OrgCompStatus=( OrgStr.OrgCompStatus << 1 ) & 0x03;
    OrgStr.OrgCompStatus |= OrgControlBit.bit.OrgDone;
  
    if(OrgStr.OrgCompStatus == 0x01)
    {
        CoutV.f.Ctrl.OrgC = 1;
    }
    else if(OrgStr.OrgCompStatus == 0x02 || OrgStr.OrgCompStatus == 0x00)
    {
        CoutV.f.Ctrl.OrgC = 0;
    }
    /*-------------------------原点回归计时-------------------------*/
    if( (Prm.orgmode & 0xF000) == 0x0000)
    {
        OrgOverTime = Prm.orgovtime;
    }
    else if( (Prm.orgmode & 0xF000) == 0x1000)
    {
        OrgOverTime =(ULONG)Prm.orgovtime * 10;
    }
    else if( (Prm.orgmode & 0xF000) == 0x2000)
    {
        OrgOverTime =(ULONG)Prm.orgovtime * 100;
    }
    
    if(!OrgControlBit.bit.OrgDone && Prm.orgovtime>0)
    {
        OrgTimeCnt +=2;                             //2ms中断中执行
    }
    else
    {
        OrgTimeCnt=0;
    }

    if(OrgTimeCnt > OrgOverTime)
    {   
        OrgControlBit.bit.OrgFail = 1 ;             //原点回归失败
        KPI_ALARMSET( ALM_ORGOVTIME );              //故障Er8A1
    }
}

//===========================================================================
// No more.
//===========================================================================
