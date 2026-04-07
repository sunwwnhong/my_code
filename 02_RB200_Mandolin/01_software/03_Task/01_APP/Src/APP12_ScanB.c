//*************************************************************************************************
//文件名:APP12_ScanB.c
//创建时间:2022.07.11
//版本说明:V1.0
//功能描述:125us 中断初始化
//*************************************************************************************************
#include "Main.h"


#define EXIT2_Pin       91
#define GPIO_CFG_EXIT2  GPIO_91_GPIO91


//---------------------------------------------------------------------------------------------
//
// 任务B调度
//
//---------------------------------------------------------------------------------------------
__interrupt void SCANB_Task(void)
{
    ULONG StartTime;
    uint16_t TempPIEIER;
    TempPIEIER = PieCtrlRegs.PIEIER1.all; // Save PIEIER register for later
    IER |= 0x001;                         // Set global priority by adjusting IER
    IER &= 0x001;
    PieCtrlRegs.PIEIER1.all &= 0x0008;    // Set group priority by adjusting PIEIER1 to allow INT1.4 to interrupt current ISR
    PieCtrlRegs.PIEACK.all = 0xFFFF;      // Enable PIE interrupts
    asm("       NOP");                    // Wait one cycle
    EINT;                                 // Clear INTM to enable interrupts
    //---------------------------------------------------------------------------------------------
    KPX_RST_SCANB_STRTIME( StartTime );                     // ScanA 执行时间计时开始
    //---------------------------------------------------------------------------------------------
    //KPX_MOTA_RUN_LED_TOG();
    IntScanB( );

    //---------------------------------------------------------------------------------------------
    KPX_GET_SCANB_EXETIME( StartTime );                     // ScanA 执行时间结束
    //---------------------------------------------------------------------------------------------
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;
    //---------------------------------------------------------------------------------------------
}

/****************************************************************************************************/
/*Function_Name:InitCpu1_ScanB                                                                      */
/*Description  :使用内部定时器触发中断                                                                    */
/****************************************************************************************************/
void InitCpu1_ScanB( void )
{
    EALLOW;
    // 中断信号引脚配置
#ifdef CPU1
    GPIO_setPinConfig(GPIO_CFG_EXIT2);
    GPIO_setDirectionMode(EXIT2_Pin, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(EXIT2_Pin, GPIO_PIN_TYPE_PULLUP);
    GPIO_setMasterCore(EXIT2_Pin, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(EXIT2_Pin, GPIO_QUAL_6SAMPLE);
#endif
    // 中断信号配置
#ifdef CPU1
    GPIO_setInterruptType(GPIO_INT_XINT2, GPIO_INT_TYPE_RISING_EDGE);
#endif
    GPIO_setInterruptPin(EXIT2_Pin, GPIO_INT_XINT2);
    GPIO_enableInterrupt(GPIO_INT_XINT2);

    Interrupt_register(INT_XINT2, &SCANB_Task);

    EDIS;
}

/****************************************************************************************************/
/*  开启内部中断(125us)                                                                                */
/****************************************************************************************************/
void ScanBTask_Start( void )
{
    Interrupt_enable(INT_XINT2);
}

