/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name 		 : Enc08_EncSoftLimit.c
* Version			 : V0.1
* Date				 : 2024
* Description		 : 绝对位置软件限位处理
***********************************************************************************************/
#include "Enc08_EncSoftLimit.h"

/**********************************************************************************************/
/* Function_Name: IprmAbsPosSoftLimit         */
/* Description  : 绝对位置软件限位值计算
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void IprmAbsPosSoftLimit( void )
{
    LONG SMax;
    LONG SMin;
    INT64 EncMax;
    INT64 EncMin;
    INT64 Temp;


    if( (Prm.fcplsel & 0x0001) )
    {
        SMax = ULONGOF( Prm.SoftLimitMaxl, Prm.SoftLimitMaxh );    // 得到绝对位置限制单圈最大值
        SMin = ULONGOF( Prm.SoftLimitMinl, Prm.SoftLimitMinh );    // 得到绝对位置限制单圈最小值
        EncMax = (INT64)((SHORT)Prm.SoftLimitMMax) * ( 1UL << FencV.FencPulseBit ) + SMax;// 得到多圈位置限制最大值
        EncMin = (INT64)((SHORT)Prm.SoftLimitMMin) * ( 1UL << FencV.FencPulseBit ) + SMin;// 得到多圈位置限制最小值
    }
    else
    {
        SMax = ULONGOF( Prm.SoftLimitMaxl, Prm.SoftLimitMaxh );    // 得到绝对位置限制单圈最大值
        SMin = ULONGOF( Prm.SoftLimitMinl, Prm.SoftLimitMinh );    // 得到绝对位置限制单圈最小值
        EncMax = (INT64)((SHORT)Prm.SoftLimitMMax) * ( 1UL << (Prm.bit_dp.b.l & 0x00FF) ) + SMax;// 得到多圈位置限制最大值
        EncMin = (INT64)((SHORT)Prm.SoftLimitMMin) * ( 1UL << (Prm.bit_dp.b.l & 0x00FF )) + SMin;// 得到多圈位置限制最小值
    }
     /*** 若限位最大值小于最小值，则最大最小值对调 ***/
     if( EncMax < EncMin )
     {
        Temp  = EncMax;                                             
        EncMax = EncMin;
        EncMin = Temp;
     }
      
     /*** 将得到的结果赋值给绝对值软限位 ***/
     Iprm.AbsPosSoftLimitMax = EncMax;
     Iprm.AbsPosSoftLimitMin = EncMin;
     return;  
}
  
  
/**********************************************************************************************/
/* Function_Name: ABSPosLimitDeal         */
/* Description  : 绝对位置软件限位处理
                  调用：Scanc时序中调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void ABSPosLimitDeal( void )
{
    LONG	work;
    INT64   CurPosValue;
    LONG    Max;
    LONG    Min;
    UCHAR   Flag;

    /*** 若编码器不是绝对式编码器，则直接返回 ***/
    if( MencP.AbsoEncType != MENC_MABSO_TYPE )
    {
        CinV.f.Ctrl.AbsPosLimitPot = 0;
        CinV.f.Ctrl.AbsPosLimitNot = 0;
        return;
    }

    if( (!Kprm.f.FencUse) && (!Kprm.f.FencUseFlag) )
    {
        work = 1UL << (Prm.bit_dp.b.l & 0x00FF);   // 得到编码器一圈脉冲数
        CurPosValue = ((INT64)(SHORT)RoutV.ABSEncMValue * work) + RoutV.ABSEncSValue;// 根据当前多圈值和单圈角度得到多圈角度


    }
    else
    {
        CurPosValue = ((INT64)(SHORT)FencV.FencMPos * FencV.FencPulseNo) + FencV.FencAbsPos;// 根据当前多圈值和单圈角度得到多圈角度
    }
    /*** 软件限位有效：1、Pn030-Pn032限位有效 ***/
    if( Iprm.f.AbsPosLimit  == 1)
    {
        if( ( Iprm.AbsPosSoftLimitMax >= 0 && Iprm.AbsPosSoftLimitMin >= 0 ) || \
            ( Iprm.AbsPosSoftLimitMax < 0 && Iprm.AbsPosSoftLimitMin < 0 ))
        {
            if( (CurPosValue < Iprm.AbsPosSoftLimitMin) && (CurPosValue > Iprm.AbsPosSoftLimitMax) )
            {
                CinV.f.Ctrl.AbsPosLimitPot = 1;     // 最大限位标志置一
                CinV.f.Ctrl.AbsPosLimitNot = 1;     // 最小限位标志置一
            }
            else
            {
                CinV.f.Ctrl.AbsPosLimitPot = CurPosValue > Iprm.AbsPosSoftLimitMax ? 1 : 0;
                CinV.f.Ctrl.AbsPosLimitNot = CurPosValue < Iprm.AbsPosSoftLimitMin ? 1 : 0;
            }            
        }
        else
        {
             if( CurPosValue > Iprm.AbsPosSoftLimitMax )
            {
                  
                 CinV.f.Ctrl.AbsPosLimitPot = 1;
            }
            else if( CinV.f.Ctrl.AbsPosLimitPot == 1 && CurPosValue < ( Iprm.AbsPosSoftLimitMax - Prm.SoftLimitDelta ) )
            {
                  
                 CinV.f.Ctrl.AbsPosLimitPot = 0;
            }
             if( CurPosValue < Iprm.AbsPosSoftLimitMin )
            {
                  
                 CinV.f.Ctrl.AbsPosLimitNot = 1;
            }
            else if( CinV.f.Ctrl.AbsPosLimitNot == 1 && CurPosValue > ( Iprm.AbsPosSoftLimitMin + Prm.SoftLimitDelta) )
            {
                  
                 CinV.f.Ctrl.AbsPosLimitNot = 0;
            }
        }
    }
    else if( Iprm.f.AbsPosLimit  == 2 )
    {
        if( Kprm.f.CanOpenNet == 1 )
        {
            if( (ODDatArr[Min_Soft_Posi_Limit].sall == -2147483648 && ODDatArr[Max_Soft_Posi_Limit].sall == 2147483647) || \
                (ODDatArr[Max_Soft_Posi_Limit].sall == -2147483648 && ODDatArr[Min_Soft_Posi_Limit].sall == 2147483647)
              )
            {
                CinV.f.Ctrl.AbsPosLimitPot = 0;
                CinV.f.Ctrl.AbsPosLimitNot = 0;            
            }  
            else
            {
                  
                 Flag = ODDatArr[Min_Soft_Posi_Limit].sall < ODDatArr[Max_Soft_Posi_Limit].sall ? 0 : 1;
                if( Flag == 0 )
                {
                    Max = ODDatArr[Max_Soft_Posi_Limit].sall;
                    Min = ODDatArr[Min_Soft_Posi_Limit].sall;
                }
                else
                {
                    Max = ODDatArr[Min_Soft_Posi_Limit].sall;
                    Min = ODDatArr[Max_Soft_Posi_Limit].sall;  
                }
                  
                  
                    if( ( Max >=0 && Min >= 0 ) || ( Max  < 0 && Min < 0 ) )
                    {
                        if( (ODDatArr[Position_Actual_Value_MM].sall < Min) && (ODDatArr[Position_Actual_Value_MM].sall > Max ))
                        {
                            CinV.f.Ctrl.AbsPosLimitPot = 1;
                            CinV.f.Ctrl.AbsPosLimitNot = 1;
                        }
                        else
                        {
                            CinV.f.Ctrl.AbsPosLimitPot = ODDatArr[Position_Actual_Value_MM].sall > Max ? 1 : 0;
                            CinV.f.Ctrl.AbsPosLimitNot = ODDatArr[Position_Actual_Value_MM].sall < Min ? 1 : 0;
                        }
                    }
                    else
                    {
                        CinV.f.Ctrl.AbsPosLimitPot = ODDatArr[Position_Actual_Value_MM].sall > Max ? 1 : 0;
                        CinV.f.Ctrl.AbsPosLimitNot = ODDatArr[Position_Actual_Value_MM].sall < Min ? 1 : 0;
                    }        
            }
        }

        /*** EtherCAT机型 ***/
        else if( Kprm.f.EtherCATNet == 1 )
        {
            // 若限位值等于（-2^31）或者等于（2^31-1），则不执行限位
            if( (SoftPosLimit.aEntries[0] == -2147483648 && SoftPosLimit.aEntries[1] == 2147483647) || \
                (SoftPosLimit.aEntries[1] == -2147483648 && SoftPosLimit.aEntries[0] == 2147483647)
               )
                {
                    CinV.f.Ctrl.AbsPosLimitPot = 0;
                    CinV.f.Ctrl.AbsPosLimitNot = 0;            
                }
                else
                {
                     /*** 若最大限位值小于最小限位值，则对调两者位置 ***/
                     Flag = SoftPosLimit.aEntries[0] < SoftPosLimit.aEntries[1] ? 0 : 1;
                    if( Flag == 0 )
                    {
                        Max = SoftPosLimit.aEntries[1];
                        Min = SoftPosLimit.aEntries[0];
                    }
                    else
                    {
                        Max = SoftPosLimit.aEntries[0];
                        Min = SoftPosLimit.aEntries[1];  
                    }
                      
                      
                    if( ( Max >=0 && Min >= 0 ) || ( Max  < 0 && Min < 0 ) )
                    {
                        if( (s32PosActVal < Min) && (s32PosActVal > Max) )
                        {
                            CinV.f.Ctrl.AbsPosLimitPot = 1;
                            CinV.f.Ctrl.AbsPosLimitNot = 1;
                        }
                        else
                        {
                            CinV.f.Ctrl.AbsPosLimitPot = s32PosActVal > Max ? 1 : 0;
                            CinV.f.Ctrl.AbsPosLimitNot = s32PosActVal < Min ? 1 : 0;
                        }
                     }
                    else
                    {
                        CinV.f.Ctrl.AbsPosLimitPot = s32PosActVal > Max ? 1 : 0;
                        CinV.f.Ctrl.AbsPosLimitNot = s32PosActVal < Min ? 1 : 0;
                    }
                }
            }
            else
            {
                ;
            }
    }
    /*** 软件限位无效：不执行限位 ***/
    else
    {
        CinV.f.Ctrl.AbsPosLimitPot = 0;
        CinV.f.Ctrl.AbsPosLimitNot = 0;
    }
}
