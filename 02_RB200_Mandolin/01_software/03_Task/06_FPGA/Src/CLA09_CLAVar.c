/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : CLA09_CLAVar.c
* Version            : V0.1
* Date               : 2024
* Description        : CLA与CPU1共享RAM地址配置，CPU1与CPU2共享RAM地址配置
***********************************************************************************************/

  
  
#include "Main.h"


//CLA与CPU共用参数
 #ifdef CPU1
 CLA1_CPU1VAR A1ToC1V;
#pragma DATA_SECTION(A1ToC1V,"Cla1ToCpuMsgRAM");
 A2C_MotAVAR AMotVar[2];  //轴1的电机参数
#pragma DATA_SECTION(AMotVar,"Cla1ToCpuMsgRAM");
 volatile ACRP Acr_P[2];  //轴1和轴2的ACR参数
volatile ACRV Acr_V;      //轴1和轴2的ACR电流环路变量
volatile ACRPCom ACRCom;                
volatile ACR_I Acr_I[2];   //轴1和轴2的电流偏置参数
volatile uint16_t ACR_Smachine;   //轴1/2电流控制器状态 0x01 轴1PWM使能  0x02 轴2PWM使能      
volatile uint16_t ACR_Flag;              
#pragma DATA_SECTION(Acr_P,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(Acr_V,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(ACRCom,"CpuToCla1MsgRAM");
 #pragma DATA_SECTION(Acr_I,"CpuToCla1MsgRAM");
 #pragma DATA_SECTION(ACR_Smachine,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(ACR_Flag,"CpuToCla1MsgRAM");

CLA_GVARDef CLAV;
#pragma DATA_SECTION(CLAV,"Cla1DataRam");

// CLA_VARDef LClaV;
//#pragma DATA_SECTION(LClaV,"Cla1DataRam");
#endif


 #ifdef CPU1





#endif

  
USBRECBUF UsbRecBuf;
//#pragma DATA_SECTION(UsbRecBuf,"MSGRAM_CPU1_TO_CPU2");
USBTRSBUF UsbTrsBuf;
//#pragma DATA_SECTION(UsbTrsBuf,"MSGRAM_CPU2_TO_CPU1");

SINV StateM_Var;
SYSTEMBITDEF SysBitDef;                                              
SYSTEMBITDEF1 SysBitDef1;
SYSTEMBITDEF2 SysBitDef2;


uint16_t DriverPowerType = 0;
uint32_t Var_SnNum = 0;
uint32_t EtherCatSyncTimeus = 0;


void ACR_B2A( void );
 
volatile uint16_t DMATestData[32];
  
/**********************************************************************************************/
/* Function_Name: CLAVar_Init         */
/* Description  : CLA交互数据初始化
            调用：初始化
            输入：
            输出：   */
/**********************************************************************************************/
void CLAVar_Init( void )
{
    Acr_V = (struct ACRV) {0};
    MlibResetLONGMemory( &Acr_P,        sizeof(Acr_P) / 2 );
#ifdef CPU1
    MlibResetLONGMemory( &UsbRecBuf,    sizeof(UsbRecBuf) / 2 );
    //CPU12Var1.w = 0;
    ACR_Smachine = 0;
#endif
    return;
}
  
  


 
/**********************************************************************************************/
/* Function_Name: Err_OC_Reset         */
/* Description  : OC故障复位处理
            调用：故障复位时调用
            输入：
            输出：   */
/**********************************************************************************************/
void Err_OC_Reset( void )
{
#ifdef CPU1
    StateM_Var.f.MotA_OC = 0;
#endif
}
 
 
 
 
