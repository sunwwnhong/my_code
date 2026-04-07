/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name 		 : Mot35_MotorRunOver.c
* Version			 : V0.1
* Date				 : 2024
* Description		 : 故障保护--速度类故障
***********************************************************************************************/
   
#include "Main.h"

/**********************************故障参数结构体定义****************************************/
typedef struct
{
    LONG    CurLimtHard;
    LONG    LimtTHard;
    LONG    SpdLimtHard;
    LONG    HardCount;
    LONG    CurLimtSoft;
    LONG    LimtTSoft;
    LONG    SpdLimtSoft;
    LONG    SoftCount;
} MOTORSTALLP;

MOTORSTALLP MotorStall;
  
/**********************************************************************************************/
/* Function_Name: IprmcalMotorOverrun                                                         */
/* Description  : 飞车监控参数计算
                  失控监测转矩阈值和速度阈值的计算
   相关的功能码 ：Pn056 飞车检测转矩阈值
                  Pn057 飞车检测速度阈值                                                      */
/**********************************************************************************************/
void IprmcalMotorStall( void )
{

    MotorStall.CurLimtHard = KpiTorqueLevelCal( 10UL * Prm.CurLimtHard, 1 );
    MotorStall.LimtTHard   = (ULONG)Prm.LimtTHard / 2UL;
    MotorStall.SpdLimtHard = KpiSpeedLevelCal( Prm.SpdLimtHard, 1 );

    MotorStall.CurLimtSoft = KpiTorqueLevelCal( 10UL * Prm.CurLimtSoft, 1 );
    MotorStall.LimtTSoft   = (ULONG)Prm.LimtTSoft / 2UL;
    MotorStall.SpdLimtSoft = KpiSpeedLevelCal( Prm.SpdLimtSoft, 1 );

}
  
   
 /**********************************************************************************************/
 /* Function_Name: Fun_MotOverRun      原函数LpxCheckMotorOverrun                              */
 /* Description  : 飞车故障保护
                   电机电缆(U、V、W相)因接线错误导致失控的检测。
                   Er.C10 飞车故障                                                             */
 /**********************************************************************************************/
void LpxCheckMotorStall( void )
{
    // 判断飞车保护功能是否开启（0-未开启）
    if ( (Prm.StallEn == 0) || (BinV.f.BaseEnable == FALSE))
        return;

    if( MlibABS(CinK.AbsMotSpd) <= MotorStall.SpdLimtHard )
    {
        if( CoutV.UnCrntRef > MotorStall.CurLimtHard)
        {
            MotorStall.HardCount ++;
            if( MotorStall.HardCount >= MotorStall.LimtTHard)
            {
                MotorStall.HardCount = 0;
                KPI_ALARMSET( ALM_SOM_STALL );
            }
        }
        else
        {
            MotorStall.HardCount = 0;
        }
    }

    if( MlibABS(CinK.AbsMotSpd) <= MotorStall.SpdLimtSoft )
    {
        if( CoutV.UnCrntRef > MotorStall.CurLimtSoft)
        {
            MotorStall.SoftCount ++;
            if( MotorStall.SoftCount >= MotorStall.LimtTSoft)
            {
                MotorStall.SoftCount = 0;
                KPI_WARNINGSET( WRN_STALL );
            }
        }
        else
        {
            MotorStall.SoftCount = 0;
        }
    }

    return;
}
 
/******************************************File End********************************************/

