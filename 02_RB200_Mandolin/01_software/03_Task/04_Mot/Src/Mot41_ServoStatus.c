/**********************************************************************************************
* File Name   : Mot41_ServoStatus.c
* Version     : V0.1
* Date        : 2024
* Description : 伺服状态判定
**********************************************************************************************/

#include "Main.h"
 

 
/****************************************************************************************************
Function_Name:LpxServoStatusCheck
Description  :伺服状态判定
*****************************************************************************************************/
void LpxServoStatusCheck( void )
{
USHORT	CurAlarm = 0;
    CurAlarm = KpiGetAlarmInfo();
     if(Alm.f.AlmFlag)              // 故障时显示故障代码,优先级最高                                    
    {
        KnlV.ServoStatus = 3;       // 伺服驱动器出现故障                             
    }
    else if( CurAlarm != 0 )
    {
        KnlV.ServoStatus = 2;       // 伺服驱动器出现警告                             
    }
    else
    {
        if( CoutV.f.Sv.BaseEnable )
            KnlV.ServoStatus = 1;   // 伺服驱动器 ON                             
        else
            KnlV.ServoStatus = 0;   // 伺服驱动器 OFF                             
    }
}


