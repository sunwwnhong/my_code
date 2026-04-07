//*************************************************************************************************
//
//                           Copyright (C) ××× Electric Corporation
//                                  版权所有 · All right Reserved
//											2019 ~
//*************************************************************************************************
//文件名:EtherCAT01_ET1100.c
//创建时间:2019.06.26
//版本说明:V1.0
//功能描述:EtherCAT ESC--38x 相关配置
//*************************************************************************************************
#include "Main.h"
#include "f2838x_cpu1_hw.h"
#include "applInterface.h"

volatile USHORT Eth_InitError = 0;


//*************************************************************************************************
//
// CLB Configurations
//
//*************************************************************************************************
void InitCPu1_EtherCAT( void )
{
#ifdef CPU1
    //
    // Initialize device hardware and EtherCAT slave controller
    //
    if( 0xFFFFU == HW_Init() )
    {
        KPI_ALARMSET( ALM_EET_ESC0 );
        return;
    }

    //
    // Initialize Slave Stack
    //
    MainInit();

    //
    //Create basic mapping
    //
    APPL_GenerateMapping(&nPdInputSize,&nPdOutputSize);
    bRunApplication = TRUE;

#endif
    return;
}
