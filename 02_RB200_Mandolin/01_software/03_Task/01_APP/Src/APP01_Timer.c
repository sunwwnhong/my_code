//*************************************************************************************************
//文件名:APP01_Timer.c
//创建时间:2022.07.11
//版本说明:V1.0
//功能描述:定时器初始化
//*************************************************************************************************
#include "Main.h"


/****************************************************************************************************/
/*Function_Name:InitCpu1_Timer                                                                      */
/*Description  :CPU1 定时器初始化                                                                      */
/****************************************************************************************************/
void InitCpu1_Timer(void)
{

    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);
    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 1);  //19
    //
    // ISRs for each CPU Timer interrupt
    //
//    Interrupt_register(INT_TIMER0, &SCANC_Task);

    //
    // Initialize timer period:
    //
//    CPUTimer_setPeriod(CPUTIMER0_BASE, 24999);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
//    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);
    CPUTimer_setEmulationMode(CPUTIMER1_BASE, CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(CPUTIMER1_BASE);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in configCPUTimer and initCPUTimers, the below settings must also
    // be updated.
    //
    CPUTimer_enableInterrupt(CPUTIMER1_BASE);

    //
    // Enables CPU int1, int13, and int14 which are connected to CPU-Timer 0,
    // CPU-Timer 1, and CPU-Timer 2 respectively.
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
//    Interrupt_enable(INT_TIMER0);

     //
     // Starts CPU-Timer 0, CPU-Timer 1, and CPU-Timer 2.
     //
     CPUTimer_startTimer(CPUTIMER1_BASE);

    return;
}

//
// initCPUTimers - This function initializes all three CPU timers
// to a known state.
//
void initCPUTimers(void)
{
    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);
    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);
    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER1_BASE);

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);
}


