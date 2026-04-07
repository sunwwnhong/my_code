//*************************************************************************************************
//文件名:APP00_Main.c
//创建时间:2021.06.15
//版本说明:V1.0
//功能描述:MCU初始化 主函数
//*************************************************************************************************




#include "Main.h"
#include "CLA02_Encode.h"
#ifdef CPU1
#include "USB00_Main.h"
#include "EtherCAT00_Main.h"
#endif

//*************************************************************************************************
//Function_Name:InitCPU10
//Description  :CPU 1 初始化(与功能码无关)
//*************************************************************************************************
void InitCPU10( void )
{
    Device_initGPIO();

    InitCpu1_GPIO( );           //   GPIO Init 轴1和轴2所有GPIO初始化

    InitCpu1_IIC( );            //   IIC Init

#ifdef CPU1
//    CPU1_USBInit( );          //   RB100无USB 初始化
    InitCpu1_IntSrc( );         //   系统中断信号源
    InitCpu1_DMA( );            //   DMA初始化
#endif
    //---------------------------------------------------------------------------------------------

    InitCpu1_Timer( );          //   计时器初始化
    InitCpu1_ScanA( );          //   系统任务A 初始化
    InitCpu1_ScanB( );          //   系统任务B 初始化
    InitCpu1_ScanC( );          //   系统任务C 初始化
    //---------------------------------------------------------------------------------------------
#ifdef CPU1

#endif
    return;
}

//*************************************************************************************************
//Function_Name:InitCPU11
//Description  :CPU 1 初始化(与功能码有关)
//*************************************************************************************************
void InitCPU11( void )
{
    InitCpu1_Can( );            //   系统 Can 初始化
    InitCpu1_Uart( );           //   系统 Uart 初始化
    InitCpu1_eQEP( );           //   系统 脉冲信号采集
    //---------------------------------------------------------------------------------------------


    if( (Prm.PosJump & 0x0f) == 0x02 )
    {
        InitCpu1_SPIB_HiZ( );
    }
    else
    {
        if( KTM5900_Load_En )
        {
            InitCpu1_SPIB( );
        }
        else
        {
            MT6709_init();
        }
    }




#ifdef CPU1
    InitCpu1_ADC( );            //   ADC Init
    InitCpu1_PWM( );            //   系统 PWM初始化



#endif
    return;
}

//*************************************************************************************************
//Function_Name:EtherCAT_Init
//Description  : EtherCat Init
//*************************************************************************************************
void InitC1_EtherCAT( void )
{
#ifdef CPU1

    if( Kprm.f.EtherCATNet == 0 )
    {
        return;                     // 非EtherCAT机型
    }
    else
    {
        InitCPu1_EtherCAT( );       //   EtherCAT 初始化
    }

#endif
}



//*************************************************************************************************
//
// CPU 复位
//
//*************************************************************************************************
void CPU_Reset( void )
{
#ifdef CPU1
//#define SYSCTL_SIMRESET_CPU1RSN   0x1U          // Generates a reset to CPU1
//#define SYSCTL_SIMRESET_XRSN      0x2U          // Generates a simulated XRSn
    EALLOW;
    SysCtl_simulateReset( SYSCTL_SIMRESET_XRSN );
    EDIS;
#endif
}
