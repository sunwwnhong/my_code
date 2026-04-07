/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                   */
/*						                    2019 ~	        					                    */
/****************************************************************************************************/
/*文件名:Pr04_SeveralPos.c                                                                          */
/*创建时间: 2019.9.5                                                                                */
/*版本说明: V1.0                                                                                    */
/*功能描述: 通过输入端子来选择所需要的位置     	                                                    */			
/****************************************************************************************************/
#include "Main.h"




/****************************************************************************************************/
/*																									*/
/*		位置切换时状态操作            																*/
/*                                                  												*/
/****************************************************************************************************/
void PrPosSwitch(void)
{
    Pr_DICtrgV.CTRG_Step    = 1;                        // 进入更新加减速等指令步骤 
    /*--------------------------------------------------------------------------------------*/
    /* 新的目标模式是定速模式                                                               */
    /*--------------------------------------------------------------------------------------*/
    if( Pr_DICtrgV.PosType == 0x01 )
    {
        Pr_DICtrgV.CurMode      = 1;                    //进入定速模式 
        Pr_DICtrgV.f.PosSpdReachflag=0;
    }
    /*--------------------------------------------------------------------------------------*/
    /*  新的目标模式是定位模式                                                              */
    /*--------------------------------------------------------------------------------------*/
    else
    {
        Pr_DICtrgV.CurMode      = 0;                    //进入定位模式
        PosCurvV.TargetReach    = 0;
    }
}

/****************************************************************************************************/
/*																									*/
/*		单次多段位置指令处理时序逻辑 																*/
/*                                                  												*/
/****************************************************************************************************/
LONG PrModeSeveralPos( void )
{
    LONG KX;
    UCHAR ReTrigDealFlag;
    if(Pr_DICtrgV.StopSign)
    {
        if(Pr_DICtrgV.CTRG_Status == 0x01 || Prm.PrCommSet==1)
        {
           ReTrigDealFlag = (Prm.PrModeSet>>4) & 0x0F;
           if(ReTrigDealFlag)
                Pr_DICtrgV.NewNum = 1;                               // 从第1段位置开始 
            Pr_DICtrgV.f.NewPosFlag = 1;                             // 新的位置标志                     
            Pr_DICtrgV.f.PramUpdate = 0; 
            Pr_DICtrgV.StopSign     = 0;                            //停机指令状态
            PosCurvV.TargetReach    = 0;                            //开始新的位置
        }
    }
    
    if( Pr_DICtrgV.f.NewPosFlag )
    {        
        if( !Pr_DICtrgV.f.PramUpdate )
        {
            InnerPosInformation( Pr_DICtrgV.NewNum );           /* 相关参数的计算处理               */
            Pr_DICtrgV.f.PramUpdate = 1;                        /* 相关的参数已经更新               */
        }
        if(Pr_DICtrgV.PrDelayTimeOld>0)
        {
            if(Pr_DICtrgV.f.PrDelayOKFlag)
            {
                PrPosSwitch();
                /*------------------------------------------------------------------------------------*/     
                if(Pr_DICtrgV.NewNum < Prm.PrEndSet)
                {
                    Pr_DICtrgV.NewNum++;
                    Pr_DICtrgV.f.PramUpdate = 0;                //可以规划下一次的参数
                }
                else
                {
                    Pr_DICtrgV.NewNum = 1;
                    Pr_DICtrgV.f.NewPosFlag = 0;                // 一轮已执行完，电机停止运行 
                }
            }
        }
        /****************************无延时情况下重叠处理*************************/
        else
        {
            if(PosCurvV.PosBlock==3 || Pr_DICtrgV.f.PrDelayOKFlag)
            {
                PrPosSwitch();
                /*------------------------------------------------------------------------------------*/ 
                if(Pr_DICtrgV.NewNum < Prm.PrEndSet)
                {
                    Pr_DICtrgV.NewNum++;
                    Pr_DICtrgV.f.PramUpdate = 0;                //可以规划下一次的参数
                }
                else
                {
                    Pr_DICtrgV.NewNum = 1;
                    Pr_DICtrgV.f.NewPosFlag = 0;                // 指令已经执行,相关标志清零 
                }
            }
        }
    }
    PrPosStop();
    KX=PosAndSpeedDeal();
    return KX;
}

/****************************************************************************************************/
/*																									*/
/*		循环多段位置指令处理时序逻辑 																*/
/*                                                  												*/
/****************************************************************************************************/
LONG PrModeCirclePos( void )                  
{
    LONG KX;
    UCHAR ReTrigDealFlag;
    if(Pr_DICtrgV.StopSign)
    {
        if( Pr_DICtrgV.CTRG_Status == 0x01 || Prm.PrCommSet==1)
        {
           ReTrigDealFlag = (Prm.PrModeSet>>4) & 0x0F;
           if(ReTrigDealFlag)
           {
                Pr_DICtrgV.NewNum = 1;                              // 从第1段位置开始 
           }
            Pr_DICtrgV.f.NewPosFlag = 1;                            // 新的位置标志                     
            Pr_DICtrgV.f.PramUpdate = 0; 
            Pr_DICtrgV.StopSign     = 0;
            PosCurvV.TargetReach    = 0;                            //开始新的位置，清除定位完成信号
        }
    }
    
    if( Pr_DICtrgV.f.NewPosFlag )
    {        
        if( !Pr_DICtrgV.f.PramUpdate )
        {
            InnerPosInformation( Pr_DICtrgV.NewNum );           /* 相关参数的计算处理               */
            Pr_DICtrgV.f.PramUpdate = 1;                        /* 相关的参数已经更新               */
        }
        if(Pr_DICtrgV.PrDelayTimeOld>0)
        {
            if(Pr_DICtrgV.f.PrDelayOKFlag)
            {
                PrPosSwitch();
                /*------------------------------------------------------------------------------------*/     
                if(Pr_DICtrgV.NewNum < Prm.PrEndSet)
                {
                    Pr_DICtrgV.NewNum++;
                    Pr_DICtrgV.f.PramUpdate = 0;                //可以规划下一次的参数
                }
                else
                {
                    Pr_DICtrgV.NewNum = 1;
                    Pr_DICtrgV.f.PramUpdate = 0;
                }
            }
        }
        /****************************无延时情况下重叠处理*************************/
        else
        {
            if(PosCurvV.PosBlock==3 || Pr_DICtrgV.f.PrDelayOKFlag)
            {
                PrPosSwitch();
                /*------------------------------------------------------------------------------------*/ 
                if(Pr_DICtrgV.NewNum < Prm.PrEndSet)
                {
                    Pr_DICtrgV.NewNum++;
                    Pr_DICtrgV.f.PramUpdate = 0;                //可以规划下一次的参数
                }
                else
                {
                    Pr_DICtrgV.NewNum = 1;                      //继续从第1段开始运行
                    Pr_DICtrgV.f.PramUpdate = 0;
                }
            }
        }
    }
    PrPosStop();
    KX=PosAndSpeedDeal();
    return KX;
}
/****************************************************************************************************/
/*																									*/
/*		顺序多段位置指令处理时序逻辑 																*/
/*                                                  												*/
/****************************************************************************************************/
LONG PrModeSequencePos( void )           //顺序运行多段位置
{
    LONG KX;
    UCHAR ReTrigDealFlag;
    if(Pr_DICtrgV.StopSign)
    {
        if( Pr_DICtrgV.CTRG_Status == 0x01 || Prm.PrCommSet==1)
        {
           ReTrigDealFlag = (Prm.PrModeSet>>4) & 0x0F;
           if(ReTrigDealFlag)
                Pr_DICtrgV.NewNum = 1;                              // 从第1段位置开始 
            Pr_DICtrgV.f.NewPosFlag = 1;                            // 新的位置标志                     
            Pr_DICtrgV.f.PramUpdate = 0; 
            Pr_DICtrgV.StopSign     = 0;
            PosCurvV.TargetReach    = 0;                            //开始新的位置，清除定位完成信号
        }
    }
    if( Pr_DICtrgV.f.NewPosFlag )
    {        
        if( !Pr_DICtrgV.f.PramUpdate )
        {
            InnerPosInformation( Pr_DICtrgV.NewNum );           /* 相关参数的计算处理               */
            Pr_DICtrgV.f.PramUpdate = 1;                        /* 相关的参数已经更新               */
        }
        
        if(!Prm.PrStartSet || Prm.PrStartSet>Prm.PrEndSet)      //Pn804=0或Pn804>Pn803    
        {
            /*-------------------------------段与段之间无等待时间-----------------------------------*/ 
            if(Pr_DICtrgV.NewNum < Prm.PrEndSet)
            {
                if(PosCurvV.PosBlock==3||Pr_DICtrgV.f.PrDelayOKFlag)
                {
                    PrPosSwitch();
                    Pr_DICtrgV.NewNum++;
                    Pr_DICtrgV.f.PramUpdate = 0;                //可以规划下一次的参数
                }
            }
            else
            {
                //if(Pr_DICtrgV.f.PrDelayOKFlag)
                if(( PosCurvV.PosBlock == 3 || Pr_DICtrgV.f.PrDelayOKFlag ) && \
                (Pr_DICtrgV.NewNum <= Prm.PrEndSet ))
                {
                    PrPosSwitch();
                    Pr_DICtrgV.NewNum++;
                    Pr_DICtrgV.f.PramUpdate = 0;                //可以规划下一次的参数
                    Pr_DICtrgV.f.NewPosFlag = 0;                //停止运行
                }       
            }
            
        }
        
        else                                                    // Pn804<=Pn803
        {
            if(PosCurvV.PosBlock==3 || Pr_DICtrgV.f.PrDelayOKFlag)
            {
                PrPosSwitch();
                /*--------------------------------------------------------------*/ 
                if(Pr_DICtrgV.NewNum < Prm.PrEndSet)
                {
                    Pr_DICtrgV.NewNum++;
                    Pr_DICtrgV.f.PramUpdate = 0;                //可以规划下一次的参数
                }
                else
                {
                    Pr_DICtrgV.NewNum = Prm.PrStartSet;
                    Pr_DICtrgV.f.PramUpdate = 0;                //可以规划下一次的参数
                }
            }
        }
    }
    PrPosStop();
    KX=PosAndSpeedDeal();
    return KX;

}
