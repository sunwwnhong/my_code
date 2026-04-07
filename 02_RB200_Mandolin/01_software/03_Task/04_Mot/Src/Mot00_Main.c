/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot00_Main.c
* Version            : V0.1
* Date               : 2024
* Description        : 电机驱动(中断调度函数、初始化函数)
***********************************************************************************************/

#include "Main.h"
 
  
KNLV	KnlV;	    //程序运行时间相关变量
KNXV	KnxV;       //可以合并到KnlV
 
 
  
/**********************************************************************************************/
/* Function_Name: Mot00_Main_Init                                                             */
/* Description  : 初始化
                  main函数调用                                                               */
/**********************************************************************************************/
void Mot00_Main_Init(void)
{
    MotorEncType_Init( );              //根据电机编号，完成编码器配置和编码器EEP数据读取
 #ifdef CPU1
   // MotA_InitSec |= 0x00A00000;
#endif
 
    KpxSencInitMotorEncoder();              //编码器中的数据读取
 	
    BprmCommonMotorParamCal( );             //电机基础参数计算标幺化
	RmxSencInitParamCalc( );                //编码器参数的计算
    HprmCommonMotorParamCal( );             //电机通用中间参数计算
	IprmVarInit( );                         //根据Eeprom中的参数更新相应值
    BprmAmpMotVoltInfoCal();                //伺服驱动器和电机电压信息处理
    IprmcalVoltageCheckLevel();             //驱动器电机电压初始化
    RpiAllPrmCalcMain( );                   //功能码对应的数据更新(功能码表)
      
    SysBitDef2.f.IPMOC_Switch   = 1;        //PWM Lock 需要解锁,
    SysBitDef2.f.ACT244Lock     = 1;        //在这里解锁的目的是后面有自举
    ASIC_WR(MREG_Addr003F,SysBitDef2.w);
          
    CurrentLoopCoeff_Init();                //电流环系数初始化
    LpxTemperatur_Init();                   //温度变量初始化
     
	MoSpeedPrmInit( );		                //电机速度检测 & 滤波初始化
	BpiScanBInitMain( );			        //SCAN_B初始化
	CpiScanCInitMain( );	                //SCAN_C初始化
    CpxInitCheckSvVib( );                   //振动变量初始化
    SystemCompileInf( );                    //系统日期、时间初始化
    FactorTest_Init( );                     //工厂测试初始化
    MuxAxis485_Init( );                     //双轴485通讯初始化
    MIT_Init( );
}
 
  
  
  
  
/**********************************************************************************************/
/* Function_Name: KpiRstShortTimer                                                             */
/* Description  : 时间复位
                  Timer计算精度     : 125 us
                  Timer最大计数时间 : 8  sec                                                     */
/**********************************************************************************************/
USHORT	KpiRstShortTimer( USHORT *timer )
{
	*timer = (USHORT)(KnlV.ScanBcnt);
	return( 0 );
}
  

/**********************************************************************************************/
/* Function_Name: KpiGetShortTimer         */
/* Description  : 获取计时器值函数
                  Timer计算精度     : 125 us
                  Timer最大计数时间 : 8  sec                                              */
/**********************************************************************************************/
USHORT	KpiGetShortTimer( USHORT *timer )
{
USHORT	timex;
 	timex = (USHORT)(KnlV.ScanBcnt) - *timer;
	return( KPX_SBTIMER1MS( timex ) );
}
 
  
  
