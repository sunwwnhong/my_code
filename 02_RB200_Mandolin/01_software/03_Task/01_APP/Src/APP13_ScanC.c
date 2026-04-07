//*************************************************************************************************
//文件名:APP13_ScanC.c
//创建时间:2022.07.11
//版本说明:V1.0
//功能描述:2ms中断
//*************************************************************************************************
#include "Main.h"

/****************************************************************************************************/
/*Function_Name:ScanCTask                                                                           */
/*Description  :任务C调度                                                                             */
/****************************************************************************************************/
__interrupt void SCANC_Task(void)
{
    ULONG StartTime;
    uint16_t TempPIEIER;
    TempPIEIER = PieCtrlRegs.PIEIER1.all; // Save PIEIER register for later
    IER |= 0x001;                         // Set global priority by adjusting IER
    IER &= 0x001;
    PieCtrlRegs.PIEIER1.all &= 0x0018;    // Set group priority by adjusting PIEIER1 to allow INT1.4 to interrupt current ISR
    PieCtrlRegs.PIEACK.all = 0xFFFF;      // Enable PIE interrupts
    asm("       NOP");                    // Wait one cycle
    EINT;                                 // Clear INTM to enable interrupts
    //---------------------------------------------------------------------------------------------
    KPX_RST_SCANC_STRTIME( StartTime );                     // ScanA 执行时间计时开始
    //---------------------------------------------------------------------------------------------
    //KPX_MOTA_RUN_LED_TOG();
    IntScanC( );


    //---------------------------------------------------------------------------------------------
    KPX_GET_SCANC_EXETIME( StartTime );                     // ScanA 执行时间结束
    //---------------------------------------------------------------------------------------------
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;
}

/****************************************************************************************************/
/*Function_Name:InitCpu1_ScanB                                                                      */
/*Description  :使用内部定时器触发中断                                                                    */
/****************************************************************************************************/
void InitCpu1_ScanC( void )
{

    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);
    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 1);
    //
    // ISRs for each CPU Timer interrupt
    //
    Interrupt_register(INT_TIMER0, &SCANC_Task);

    //
    // Initialize timer period:
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 200000UL - 1UL);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
    CPUTimer_setEmulationMode(CPUTIMER0_BASE, CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in configCPUTimer and initCPUTimers, the below settings must also
    // be updated.
    //
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);

    //
    // Enables CPU int1, int13, and int14 which are connected to CPU-Timer 0,
    // CPU-Timer 1, and CPU-Timer 2 respectively.
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    Interrupt_enable(INT_TIMER0);
}

/****************************************************************************************************/
/*  开启内部中断(2ms)                                                                                  */
/****************************************************************************************************/
void ScanCTask_Start( void )
{

    //
    // Starts CPU-Timer
    //
    CPUTimer_startTimer(CPUTIMER0_BASE);
}

