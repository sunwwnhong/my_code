/**********************************************************************************************
* File Name   : Mot40_ALMDeal.c
* Version     : V0.1
* Date        : 2024
* Description : 故障处理
**********************************************************************************************/


#include "Main.h"
 
CHKALMP	ChkAlmP;
CHKALMV	ChkAlmV;
 
/****************************************************************************************************
Function_Name:CpxCheckAlarm
Description  :故障检测主函数
*****************************************************************************************************/
void	CpxCheckAlarm( void )
{
  	KpxCheckSencAlarm( );           // 电机侧编码器报警检测									 
    KpxSerialEncAlarmCheck( );      // 电机侧编码器过热报警监测                        
    LpxCheckHeatSinkAlm( );         // 模块温度和环境温度检测                        
    LpxCheckSvonCmdInvalid( );      // 外部使能无效标志位                        
    LpxCheckPerrOverFlow( );        // 位置偏差过大警告和警报                        
    LpxCheckSvonPerrOverFlow( );    // 伺服ON时位置偏差过大                       
    LpxCheckMotorOverrun( );        // 飞车故障保护
    LpxCheckMotorStall( );
    LpxCheckOverLoadAmpMot( );      // 电机&驱动器过载保护                        
    //LpxCheckRegeneOverLoad( );      // 再生过载保护 

	
    LpxCheckSemiFullPerrOverFlow( );	//全闭环误差检测故障
    //LpxCheckDbrakeOverLoad();  			// 动态制动保护处理
    KpxCheckAmpMotType( );				// 驱动器和电机的电压,容量匹配度检测
    //DriveTypeCheck();					// 驱动机型检测

    LpxServoStatusCheck( );				// 伺服驱动器运行状态监控     

    /*----------------------------------------------------------------------------------------------*/
    /*  检查 CN5的脉冲AB是否当做脉冲指令 && 当做全闭环反馈                                          */
    /*----------------------------------------------------------------------------------------------*/
    if( Iprm.POSSource == 1 && Kprm.f.FencUse == TRUE )
    {
        KPI_ALARMSET( ALM_PCMDSEL );
    }
}
 
 
 
