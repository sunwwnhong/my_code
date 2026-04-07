 /*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Cur09_MotorPhase.c
* Version            : V0.1
* Date               : 2024
* Description        : 电机相位计算
***********************************************************************************************/

#include "Main.h"
 
MOTORPHASE MotorPhaseV = MOTORPHASEV_DEFAULT;
  
  
/**********************************************************************************************/
/* Function_Name: IprmcalMotorPhaseInit       */
/* Description  : 电机相位计算初始化
                  调用：初始化调用一次
                  输入：
                  输出：   */
/**********************************************************************************************/
void IprmcalMotorPhaseInit(void)
{
SHORT DataTmp;

    /*** 零点磁极位置正代表相位方向正，负代表相位方向反 ***/
    DataTmp = (SHORT)Prm.EncZeroPhase;
    if( DataTmp < 0)
    {
        MotorPhaseV.ZeroPhaseDir = 1;
        DataTmp = -DataTmp;
    }
    else
    {
        MotorPhaseV.ZeroPhaseDir = 0;
    }
    Iprm.IncPowerFlag = 0;

    /*icHaus 在外部校准时无法读取电机参数，关节模组电机代码自动匹配电机参数*/
 	if((Prm.MotorNum & 0x1000)== 0x1000 )
	{
 	   /*** 零点磁极位置正代表相位方向正，负代表相位方向反 ***/
        DataTmp = (SHORT)Prm.EncZeroPhase;
        if( DataTmp < 0)
        {
            MotorPhaseV.ZeroPhaseDir = 1;
            DataTmp = -DataTmp;
        }
        else
        {
            MotorPhaseV.ZeroPhaseDir = 0;
        }      
 #if(FLOAT_USE == 1)
        MotorPhaseV.OffsetAng = (ULONG)((float)DataTmp * 11.37777778f);
#else
		MotorPhaseV.OffsetAng = (ULONG)DataTmp * 4096 / 360;
#endif
	}
 	 /*** 其他类型编码器处理 ***/
 	else															 
	{
	  	MotorPhaseV.OffsetAng = 0;
		KPI_ALARMSET( ALM_PGUVW );							         		
	}
}
  
  
/**********************************************************************************************/
/* Function_Name: MotorPhaseCnt_Deg         */
/* Description  : 电机相位计算（360°）
                  调用：暂时未调用
                  输入：MencV.MotPhase ,Iprm.f.RvsDir, CoutV.UnMotPhase
                  输出：       */
/**********************************************************************************************/
void MotorPhaseCnt_Deg(void)
{
LONG lwk;
#if(FLOAT_USE == 1)
    lwk = (float)MencV.MotPhase * 0.087890625f;
#else
    lwk = ((( MencV.MotPhase * 360 ) >> 11 ) + 1 ) >> 1;
#endif
    if( Iprm.f.RvsDir ){ lwk = 360 - lwk;}  // 旋转方向选择，0:正,1:反，初始化由Pn000.0设置
    CoutV.UnMotPhase = lwk;
}
