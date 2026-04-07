/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Cur14_ZeroPhase.c
* Version            : V0.1
* Date               : 2024
* Description        : 电机磁极辨识
***********************************************************************************************/
  
#include "Main.h"
 
ZEROPHASE_STRUCT ZeroPhaseV;
 
  
/**********************************************************************************************/
/* Function_Name: ZeroPhaseInit         */
/* Description  : 电机零点搜索相关结构体复位
                  调用：Fn运行环节调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void ZeroPhaseInit( void )
{
    MlibResetSHORTMemory( &ZeroPhaseV, sizeof(ZeroPhaseV) );
}
  
/**********************************************************************************************/
/* Function_Name: ZeroPhaseDeal         */
/* Description  : SD100磁极辨识处理
                  磁场定向按照设定电流从-90°调整至-30°，再调整至-90°，根据实际位置的增量方向，确定相序；
                  根据锁定固定相位的绝对位置获取编码器偏移角。
                  调用：Fn运行环节调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void ZeroPhaseDeal( void )
{
SHORT lwk;
SHORT   AngTemp = ( ULONG)MencV.MotPhaseI * 360 / 4096;
    /*获取原始电角度的值*/
    while( AngTemp <  0    )   AngTemp += 360;
    while( AngTemp >= 360 )   AngTemp -= 360;
    /*开启磁场定向电角度偏置学习*/
    if( ZeroPhaseV.FirstFlag == 0 )
    {
        ZeroPhaseV.FirstFlag = 1;
        ZeroPhaseV.AngleSum = 0;
        ZeroPhaseV.AngleOld = AngTemp;
        return;
    }
    /*** 电角度移动总角度记录：16K频率获取delt角度，并进行跨周期情况处理，delt累加得到实际移动电气角度 ***/
     lwk = AngTemp - ZeroPhaseV.AngleOld;
    if( lwk > 180)
    {
        ZeroPhaseV.AngleSum +=( lwk - 360 );
    }
    else if( lwk < -180)
    {
        ZeroPhaseV.AngleSum +=( lwk + 360 );
    }
    else
    {
        ZeroPhaseV.AngleSum += lwk;
    }
     ZeroPhaseV.AngleOld = AngTemp; // 锁存本拍角度值，给下拍delt计算做准备。

     /*磁场定向状态机处理*/
     switch(ZeroPhaseV.Step)
    {
         /*磁场定向状态机初始化*/
         case 0:
            ZeroPhaseV.PhaseCurOut      = 0;            //零电流
            ZeroPhaseV.Angle            = 3072;         //磁场定向270°
            ZeroPhaseV.DelayCnt         = 0;                 
            ZeroPhaseV.PhaseOld         = Prm.EncZeroPhase;    // 搜索前编码器零位角度
            MotorPhaseV.ZeroPhaseDir    = 0;             // 搜索相位运行方向
            ZeroPhaseV.Step             = 1;
            break;
         /*磁场定向注入电流过程，抱闸、自举等待后，磁场定向电流逐步增加，每4ms电流增加0.1%，增加到磁极辨识电流为止*/
         case 1:
            if( ++ZeroPhaseV.DelayCnt > 64 )
            {
                ZeroPhaseV.DelayCnt = 0;
                ZeroPhaseV.PhaseCurOut += 1;
                if( ZeroPhaseV.PhaseCurOut >= ZeroPhaseV.PhaseCurCmd )
                {
                    ZeroPhaseV.PhaseCurOut = ZeroPhaseV.PhaseCurCmd;
                    ZeroPhaseV.Step         = 2;             
                }
            }
            ZeroPhaseV.WaitStillStep = 0;   // 静止状态判断步骤-状态归零
            break;
         /*磁场定向维持状态， */
         case 2:
              
             switch( ZeroPhaseV.WaitStillStep )
            {
                 case 0:
                    ZeroPhaseV.AngleSumOld  = ZeroPhaseV.AngleSum;   // 静止状态判断步骤-锁存首次移动电气角度
                    ZeroPhaseV.DelayCnt     = 0;                             
                    ZeroPhaseV.WaitStillStep = 1;                            
                    break;
                 /*磁场定向维持0.5s，定位位置抖动在5°以内，执行下一步*/
                 case 1:
                    if( ++ZeroPhaseV.DelayCnt > 8000 )                      
                    {
                        ZeroPhaseV.DelayCnt = 0;
                        lwk = ZeroPhaseV.AngleSumOld  - ZeroPhaseV.AngleSum;
                        lwk = (lwk >= 0)? lwk : -lwk;                      
                        if( lwk > 5 )  // 若0.5s前后移动电气角度偏差大于5度，则返回重新判断
                        {
                            ZeroPhaseV.WaitStillStep = 0;
                        }
                        else   // 若0.5s前后移动电气角度偏差小等于5度，则进入下一步
                        {
                            ZeroPhaseV.WaitStillStep = 2;
                        }
                    }
                    break;
                 /*磁场定向维持1s，定位位置抖动在5°以内，执行下一步*/
                 case 2:
                    if( ++ZeroPhaseV.DelayCnt > 8000 )                      
                    {
                        ZeroPhaseV.DelayCnt = 0;
                        lwk = ZeroPhaseV.AngleSumOld  - ZeroPhaseV.AngleSum;
                        lwk = (lwk >= 0)? lwk : -lwk;                      
                         if( lwk > 5 )
                        {
                            ZeroPhaseV.WaitStillStep = 0;
                        }
                         else
                        {
                              
                             ZeroPhaseV.WaitStillStep = 2;
                            ZeroPhaseV.AngleSum = 0;                    
                            ZeroPhaseV.Step     = 3;                    
                        }
                     }
                    break;
                }
            break;

         /*磁场定向角度1记录*/
         case 3:
            ZeroPhaseV.Angle1 = AngTemp;                     
            ZeroPhaseV.Step     = 4;                         
            break;
         /*磁场定向角度偏移处理 16K情况下，每10ms搜索角度增加1，增加从-90度增加到-30度。*/
         case 4:
            if( ++ZeroPhaseV.DelayCnt > 160 )
            {
                ZeroPhaseV.DelayCnt = 0;
                ZeroPhaseV.Angle += 1;

                /*增量式编码器电角度逐步增加3个360°，最终在定向角度330°*/
                 if(Prm.MotorNum >= MotorNumMin && Prm.MotorNum < MotorNumMax)
                {
                    if( ZeroPhaseV.Angle >= (4096 * 3 + 3755 ))  
                    {
                        ZeroPhaseV.Angle    = 4096 * 3 + 3755;
                        ZeroPhaseV.Step     = 5;                 
                    }
                }
                 /*绝对定向角度330°*/
                 else
                {
                    if( ZeroPhaseV.Angle >= 3755 )               
                    {
                        ZeroPhaseV.Angle    = 3755;
                        ZeroPhaseV.Step     = 5;
                    }                
                }
             }
            break;
         /*磁场定向方向判定：16K情况下，等待1S，判编码器方向，实际运行60度，查看反馈情况*/
         case 5:
            if( ++ZeroPhaseV.DelayCnt > 16000 )                  
            {
                ZeroPhaseV.DelayCnt = 0;
                 /*正向移动超过30°，相位方向同向*/
                if( ZeroPhaseV.AngleSum > 30)
                {
                      
                    MotorPhaseV.ZeroPhaseDir = 0;
                    ZeroPhaseV.Step     = 6;
                }
				/*反向定向超出30°，相位方向反同*/
                else if( ZeroPhaseV.AngleSum < -30)
                {
                      
                    MotorPhaseV.ZeroPhaseDir = 1;
                    ZeroPhaseV.Step     = 6;
                }
                 /*在-30°~30度之间偏移，采用之前EEP存储的电气偏移量*/
                else
                {
                     ZeroPhaseV.Step     = 20;            
                }
                 ZeroPhaseV.AngleSum = 0;     // 移动电气角度清零
            }
            break;
         /*磁场定向反向定向等待：16K情况下，等待10ms*/
         case 6:     
            if( ++ZeroPhaseV.DelayCnt > 160 )
            {
                ZeroPhaseV.DelayCnt = 0;
                ZeroPhaseV.Step = 7;
            }
            break;
         /*磁场定向反向定向至270°：16K情况下，每10ms搜索角度减小1，从-30度减小到-90度*/
         case 7:
            if( ++ZeroPhaseV.DelayCnt > 160 )
            {
                ZeroPhaseV.DelayCnt = 0;
                ZeroPhaseV.Angle -= 1;
                if( ZeroPhaseV.Angle <= 3072 )          
                {
                    ZeroPhaseV.Angle    = 3072;
                    ZeroPhaseV.Step     = 8;            
                }
            }
            break;
         /*磁场定定向角度记录：16K情况下，等待0.5s，若编码器和电气角度方向相反，则更新锁存当前电气角度。*/
         case 8:
            if( ++ZeroPhaseV.DelayCnt > 8000 )          
            {
                ZeroPhaseV.DelayCnt = 0;
                  
                 if( MotorPhaseV.ZeroPhaseDir == 1)
                {
                    ZeroPhaseV.Angle1 = AngTemp;        
                }
                 ZeroPhaseV.Step     = 9;            
            }
            break;
         /*磁场定向电流逐步减小至0：16K情况下，每4ms电流减小0.1%，减小到0电流为止。*/
         case 9:
            if( ++ZeroPhaseV.DelayCnt > 64 )
            {
                ZeroPhaseV.DelayCnt = 0;
                ZeroPhaseV.PhaseCurOut -= 1;
                if( ZeroPhaseV.PhaseCurOut <= 1 )
                {
                    ZeroPhaseV.PhaseCurOut = 0;
                    ZeroPhaseV.Step         = 10;             
                }
            }
            break;
        /*偏置角度记录*/
        case 10:
        case 20:
            /*偏移-25度~25°，学习方向不确定，则采用之前EEP存储的结果，偏移值记录维持不变*/
            if( ZeroPhaseV.Step == 20)
            {
                  
                if( ZeroPhaseV.PhaseOld > 0)
                {
                    MotorPhaseV.ZeroPhaseDir = 0;
                    MotorPhaseV.OffsetAng = ZeroPhaseV.PhaseOld * 4096 / 360;
                }
                else
                {
                    MotorPhaseV.ZeroPhaseDir = 1;
                    MotorPhaseV.OffsetAng = -ZeroPhaseV.PhaseOld * 4096 / 360;
                }
                ZeroPhaseV.Angle1 = ZeroPhaseV.PhaseOld;
                KPI_ALARMSET(ALM_PFINDSTOP);
            }
            /*反向偏移移动25°以上，偏移量学习结果是物理偏移量的负数，使用时，原始电气角度加此值即可*/
            else
            {
                  
                 ZeroPhaseV.Angle1 = 360 - ZeroPhaseV.Angle1;
                 MotorPhaseV.OffsetAng = ZeroPhaseV.Angle1 * 4096 / 360;
                 if( MotorPhaseV.ZeroPhaseDir == 1)
                {
                      
                     ZeroPhaseV.Angle1 = -ZeroPhaseV.Angle1;       
                }
            }
            ZeroPhaseV.PhaseCurOut = 0;
            ZeroPhaseV.Step = 11;
            break;
         default:
            break;
    }
}
