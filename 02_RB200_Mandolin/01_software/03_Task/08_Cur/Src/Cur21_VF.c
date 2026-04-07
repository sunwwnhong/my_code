/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Cur21_VF.c
* Version            : V0.1
* Date               : 2024
* Description        : IF模式控制
***********************************************************************************************/

#include "Main.h"
 
#define KPI_SACYCLEFS 16000                                  
  
 
VFCTRL  VfCtrl;         //IF控制结构体
 
/**********************************************************************************************/
/* Function_Name: PcalVfSoftStartAcc         */
/* Description  : V/F加减速时间计算
                  调用位置：PnEF3 : V/F加减速时间-参数设定预处理函数
                  输入：
                  输出：   */
/**********************************************************************************************/
void    PcalVfSoftStartAcc( void )
{
    VfCtrl.P.VfTimeAcc = (ULONG)Prm.VfAccTime * ( KPI_SACYCLEFS / 10 );
    return;
}
 
/**********************************************************************************************/
/* Function_Name: PcalVfVSet         */
/* Description  : V/F设定电压-计算
                  调用位置：PnEF5 : V/F设定电压  -参数设定预处理函数
                  输入：
                  输出：   */
/**********************************************************************************************/
void    PcalVfVSet( void )
{
    VfCtrl.P.IFSetCur = (float)Prm.VfSetVolt * 10.0f * Iprm.fKtrqlvl;
    return;
}
  
  
/**********************************************************************************************/
/* Function_Name: SoftStartVfRef         */
/* Description  : V/F 角度 & 电压生成
                  调用位置：SCANA -CTRLMODE_VF模式下的VF运行指令产生
                  输入：
                  输出： VfCtrl.IFCurOut 电流输出矢量大小
                       VfCtrl.V.MotPhase 电流电气角度  */
/**********************************************************************************************/
void SoftStartVfRef( void )
{
    SHORT VfSetFreq;

    /*** 伺服未使能情况下，清零Vd频率和大小，复位VF控制结构体并函数返回 ***/
    if( BinV.f.BaseEnable == FALSE )
    {
        MlibResetSHORTMemory( &VfCtrl.V, sizeof(VfCtrl.V) );
        return;
    }
	else
    {
        if((Brake_V.Step != 3) && (CoutV.f.Seq.BrkReleasing == 0))
        {
             MlibResetSHORTMemory( &VfCtrl.V, sizeof(VfCtrl.V) );
             return;
        }
    }
      
      
    /*** 计算SCANA下单位施加的电流矢量大小 ***/
    switch( VfCtrl.V.If_I_Step )
    {
        /*** 电流增量计算准备 ***/
        case 0:
            VfCtrl.P.I_Acc   = VfCtrl.P.IFSetCur / (float)VfCtrl.P.VfTimeAcc;    
            VfCtrl.IFCurOut     = 0.0f;                                          
            VfCtrl.V.If_I_Step ++;                                               
        break;
        /*** 电流累加处理 ***/
        case 1:
            VfCtrl.IFCurOut += VfCtrl.P.I_Acc;                                   
            if( VfCtrl.IFCurOut >= VfCtrl.P.IFSetCur )
            {
                VfCtrl.IFCurOut = VfCtrl.P.IFSetCur;
                VfCtrl.V.If_I_Step ++;                  
            }
            break;
         case 2:
         break;
         default:
         break;
    }
      
      
    /*** 计算SCANA下单位hz下对应运行的delt电气角度 ***/
    switch( VfCtrl.V.If_A_Step )
    {
        /*** 角度增量计算准备 ***/
        case 0:
            VfSetFreq = (SHORT)Prm.VfSetFreq;
            VfCtrl.P.fKTheta = (float)VfSetFreq * 4096.0f / 160000.0f / (float)VfCtrl.P.VfTimeAcc;
            VfCtrl.IFFreOut     = 0.0f;                          
            VfCtrl.V.MotPhase   = 0;                             
            VfCtrl.V.I_Timer    = 0;                             
            VfCtrl.V.If_A_Step ++;                               
        break;
        /*** 角度累加处理 ***/
        case 1:
            if( VfCtrl.V.I_Timer < VfCtrl.P.VfTimeAcc )
            {
                VfCtrl.V.I_Timer++;
            }
            VfCtrl.IFFreOut = (float)VfCtrl.V.I_Timer * VfCtrl.P.fKTheta;
            VfCtrl.V.MotPhase += VfCtrl.IFFreOut;
            if( VfCtrl.V.MotPhase >= 4096 )
                VfCtrl.V.MotPhase -= 4096;
            else if( VfCtrl.V.MotPhase < 0)
                VfCtrl.V.MotPhase += 4096;
        break;
     }
}

/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/
