//*************************************************************************************************
//文件名:APP27_PWM.c
//创建时间:2021.07.11
//版本说明:V1.0
//功能描述:PWM初始化配置
//**************************************************************************************************
#include "Main.h"

#ifdef CPU1

#define myEPWM1_BASE EPWM1_BASE
#define myEPWM2_BASE EPWM2_BASE
#define myEPWM3_BASE EPWM3_BASE
#define myEPWM4_BASE EPWM4_BASE
#define myEPWM5_BASE EPWM5_BASE
#define myEPWM6_BASE EPWM6_BASE
#define myEPWM7_BASE EPWM7_BASE
#define myEPWM8_BASE EPWM8_BASE


#define OCChannelNum 1

/****************************************************************************************************/
/*                                                                                                  */
/*  PWM 引脚定义初始化                                                                                  */
/*                                                                                                  */
/****************************************************************************************************/
void PWMPin_init()
{
    //---------------------------------------------------------------------------------------------
    // if GPIO_QUAL_6SAMPLE:  50ns (10 × 5ns) × Period
    // if GPIO_QUAL_3SAMPLE:  20ns (4 × 5ns) × Period
    USHORT Period = 50;                     // 过流信号滤波
    //---------------------------------------------------------------------------------------------
    // 电机A
    //---------------------------------------------------------------------------------------------
    //GPIO_setMasterCore(0, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_0_EPWM1A);       //EPWM1
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(0, GPIO_QUAL_SYNC);

    //GPIO_setMasterCore(1, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_1_EPWM1B);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(1, GPIO_QUAL_SYNC);

    //GPIO_setMasterCore(2, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_2_EPWM2A);       //EPWM2
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(2, GPIO_QUAL_SYNC);

    //GPIO_setMasterCore(3, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_3_EPWM2B);
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(3, GPIO_QUAL_SYNC);

    //GPIO_setMasterCore(4, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_4_EPWM3A);       //EPWM3
    GPIO_setPadConfig(4, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(4, GPIO_QUAL_SYNC);

    //GPIO_setMasterCore(5, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_5_EPWM3B);
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(5, GPIO_QUAL_SYNC);


    GPIO_setDirectionMode(7, GPIO_DIR_MODE_IN);        // 短路
    GPIO_setPadConfig(7, GPIO_PIN_TYPE_PULLUP);
    GPIO_setMasterCore(7, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_7_GPIO7);
    GPIO_setQualificationMode(7, GPIO_QUAL_6SAMPLE);   // 滤波系数
    GPIO_setQualificationPeriod(7,Period);             // 滤波时钟

    XBAR_setInputPin(INPUTXBAR_BASE, XBAR_INPUT1, 7);

    //---------------------------------------------------------------------------------------------
    // 电机B
    //---------------------------------------------------------------------------------------------

    GPIO_setPinConfig(GPIO_8_EPWM5A);       //EPWM5
    GPIO_setPadConfig(8, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(8, GPIO_QUAL_SYNC);
    GPIO_setMasterCore(8, GPIO_CORE_CPU1);

//    GPIO_writePin( 8,0 );    // 引脚Off
//    GPIO_setPinConfig(GPIO_8_GPIO8);                          // 引脚#
//    GPIO_setDirectionMode(8, GPIO_DIR_MODE_OUT);               // Output
//    GPIO_setPadConfig(8, GPIO_PIN_TYPE_STD);                   // Open Drain
//    GPIO_setMasterCore(8, GPIO_CORE_CPU1);
}

//*************************************************************************************************
//
//  OC & SC 信号处理  【MotA】
//
//*************************************************************************************************
__interrupt void epwm1TZISR(void)
{
    uint16_t TzStatus = 0;

    //
    // Read TZ1 or TZ2 flag
    //

    // 只有在自举或者运行时间检测
    TzStatus = HWREGH(EPWM1_BASE + EPWM_O_TZFLG) & 0x0005U;

    if( 0x0005 == TzStatus )
    {
        if( SysBitDef.f.ServoOnOff == 1 )
        {
            MotA_PWM_Lock();                // ACT244封锁
            StateM_Var.f.MotA_OC = 1;       // 电机过流
        }
    }
    else
    {
        EPWM_clearTripZoneFlag(EPWM1_BASE,(EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST));
        EPWM_clearTripZoneFlag(EPWM2_BASE, EPWM_TZ_FLAG_OST);
        EPWM_clearTripZoneFlag(EPWM3_BASE, EPWM_TZ_FLAG_OST);
    }

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
}


/****************************************************************************************************/
/*                                                                                                  */
/*  PWM 中断信号处理                                                                                   */
/*                                                                                                  */
/****************************************************************************************************/
__interrupt void epwm1ISR(void)
{

    //
    // Clear INT flag for this timer
    //

    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);
    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}


/****************************************************************************************************/
/*                                                                                                  */
/*  PWM 中断信号处理                                                                                   */
/*                                                                                                  */
/****************************************************************************************************/
__interrupt void epwm4ISR(void)
{
    //
    // Clear INT flag for this timer
    //
    //TEST6_TG;

    //KPX_MOTA_RUN_LED_TOG();
    EPWM_clearEventTriggerInterruptFlag(EPWM4_BASE);

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

volatile USHORT nUMCNT = 0;
/****************************************************************************************************/
/*                                                                                                  */
/*  PWM 中断信号处理                                                                                   */
/*                                                                                                  */
/****************************************************************************************************/
__interrupt void epwm8ISR(void)
{

    nUMCNT ++;
    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(EPWM8_BASE);

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

/****************************************************************************************************/
/*                                                                                                  */
/*  PWM 中断信号处理                                                                                   */
/*                                                                                                  */
/****************************************************************************************************/
__interrupt void epwm5ISR(void)
{
    //
    // Clear INT flag for this timer
    //

    EPWM_clearEventTriggerInterruptFlag(EPWM5_BASE);

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

/****************************************************************************************************/
/*                                                                                                  */
/*  EPWM功能定义初始化                                                                                  */
/*                                                                                                  */
/****************************************************************************************************/
void EPWM_init()
{
uint32_t PWMPriod = 0;
uint32_t ACRTime  = 0;            // 1000 * 5ns = 5us
uint32_t DeadTime = 0;
    /*----------------------------------------------------------------------------------------------*/
    /* 1. PWM Period count                                                                          */
    /*----------------------------------------------------------------------------------------------*/
    PWMPriod = PcalPwmFrequency( Prm.pwmf );    //根据载波频率计算PWM周期计数值

    /*----------------------------------------------------------------------------------------------*/
    /* 2. Dead time  【100MHz】                                                                      */
    /*----------------------------------------------------------------------------------------------*/
    DeadTime = (LONG)(Prm.odt_c & 0x00FF) * 1000 / FPGA_CLKns;
    if(DeadTime < 100)                      // @100MHz,最小死区时间设定1.5us
    {
        DeadTime = 100;
    }

    /*----------------------------------------------------------------------------------------------*/
    /* 3. ACR execute time  【100MHz】                                                               */
    /*----------------------------------------------------------------------------------------------*/
    // 运算时间和电流采样时间
    if( ( Prm.syssw2 & 0x0100 )  ==  0x0000 )
    {
        ACRTime = 1000UL;      /*0.01us*/
    }
    else
    {
        ACRTime = 300UL;      /*0.01us*/
    }

    //---------------------------------------------------------------------------------------------
    // 4. PWM1配置【MotA】
    //---------------------------------------------------------------------------------------------
    // Initially disable Free/Soft Bits
    EPWM_setEmulationMode(myEPWM1_BASE, EPWM_EMULATION_FREE_RUN);
    // PWM 时钟分频
    EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_1,EPWM_HSCLOCK_DIVIDER_1);
    // 装载方式-立即
    EPWM_setPeriodLoadMode(myEPWM1_BASE,EPWM_PERIOD_DIRECT_LOAD);
    // 【周期值】
    EPWM_setTimeBasePeriod(myEPWM1_BASE, PWMPriod);
    EPWM_setTimeBaseCounter(myEPWM1_BASE, 0);
    // 【相移】
	EPWM_disablePhaseShiftLoad(myEPWM1_BASE);
    EPWM_setPhaseShift(myEPWM1_BASE, 0); 
	EPWM_enablePhaseShiftLoad(myEPWM1_BASE);
    // 计数模式 Up-Down
    EPWM_setTimeBaseCounterMode(myEPWM1_BASE,EPWM_COUNTER_MODE_UP_DOWN);
    // 同步输出脉冲信号源
    EPWM_enableSyncOutPulseSource(myEPWM1_BASE,EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO);
    // 设置初期占空比 【0%】
    EPWM_setCounterCompareValue(myEPWM1_BASE,EPWM_COUNTER_COMPARE_A,0);
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE,EPWM_COUNTER_COMPARE_A,EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    // 动作限定模块
    EPWM_setActionQualifierActionComplete(myEPWM1_BASE,EPWM_AQ_OUTPUT_A,(EPWM_ActionQualifierEventAction)(EPWM_AQ_OUTPUT_LOW_UP_CMPA |EPWM_AQ_OUTPUT_HIGH_DOWN_CMPA));
    // 死区延迟方式
    EPWM_setRisingEdgeDeadBandDelayInput(myEPWM1_BASE,EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(myEPWM1_BASE,EPWM_DB_INPUT_EPWMA);
    // 【死区时间】200*10ns=2.0us, EPWMCLK=100MHz
    EPWM_setRisingEdgeDelayCount(myEPWM1_BASE, DeadTime);
    EPWM_setFallingEdgeDelayCount(myEPWM1_BASE, DeadTime);

    EPWM_setDeadBandDelayMode(myEPWM1_BASE, EPWM_DB_RED, true);
    EPWM_setDeadBandDelayMode(myEPWM1_BASE, EPWM_DB_FED, true);
    EPWM_setDeadBandDelayPolarity(myEPWM1_BASE, EPWM_DB_RED,EPWM_DB_POLARITY_ACTIVE_HIGH);
    EPWM_setDeadBandDelayPolarity(myEPWM1_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);

    //过流配置TZ,过流时的PWM状态
    // TZ1/TZ2
    EPWM_setTripZoneAction(myEPWM1_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW);
    EPWM_setTripZoneAction(myEPWM1_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW);
    //TZ信号源
    EPWM_enableTripZoneSignals(myEPWM1_BASE, EPWM_TZ_SIGNAL_OSHT1);
#if(OCChannelNum == 1)
    EPWM_enableTripZoneSignals(myEPWM1_BASE, EPWM_TZ_SIGNAL_OSHT1);
#else
    EPWM_enableTripZoneSignals(myEPWM1_BASE, EPWM_TZ_SIGNAL_OSHT1);
    EPWM_enableTripZoneSignals(myEPWM1_BASE, EPWM_TZ_SIGNAL_OSHT2);
#endif

    EPWM_enableTripZoneInterrupt(myEPWM1_BASE, EPWM_TZ_INTERRUPT_OST);

    //EPWM_setCountModeAfterSync(myEPWM1_BASE,EPWM_COUNT_MODE_UP_AFTER_SYNC);

    EPWM_enableSyncOutPulseSource(myEPWM1_BASE, EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO);
	
	//保证同步SCANA与PWM之间相位值同步 syhu @20251112
    ECAP_enableLoadCounter(ECAP1_BASE);
    ECAP_enableLoadCounter(ECAP2_BASE);
    ECAP_startCounter(ECAP1_BASE);
    ECAP_startCounter(ECAP2_BASE);

    //---------------------------------------------------------------------------------------------
    // 5. PWM2配置【MotA】
    //---------------------------------------------------------------------------------------------
    // Initially disable Free/Soft Bits
    //EPWM_setEmulationMode(myEPWM2_BASE, EPWM_EMULATION_FREE_RUN);
    // PWM 时钟分频
    EPWM_setClockPrescaler(myEPWM2_BASE, EPWM_CLOCK_DIVIDER_1,EPWM_HSCLOCK_DIVIDER_1);
    // 装载方式-立即
    EPWM_setPeriodLoadMode(myEPWM2_BASE,EPWM_PERIOD_DIRECT_LOAD);
    // 【周期值】
    EPWM_setTimeBasePeriod(myEPWM2_BASE, PWMPriod);
    EPWM_setTimeBaseCounter(myEPWM2_BASE, 0);
    // 【相移】
    EPWM_disablePhaseShiftLoad(myEPWM2_BASE);
    EPWM_setPhaseShift(myEPWM2_BASE, 0);
	EPWM_enablePhaseShiftLoad(myEPWM2_BASE);
    // 计数模式 Up-Down
    EPWM_setTimeBaseCounterMode(myEPWM2_BASE,EPWM_COUNTER_MODE_UP_DOWN);
    // 设置初期占空比 【0%】
    EPWM_setCounterCompareValue(myEPWM2_BASE,EPWM_COUNTER_COMPARE_A,0);
    EPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE,EPWM_COUNTER_COMPARE_A,EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    // 动作限定模块
    EPWM_setActionQualifierActionComplete(myEPWM2_BASE,EPWM_AQ_OUTPUT_A,(EPWM_ActionQualifierEventAction)(EPWM_AQ_OUTPUT_LOW_UP_CMPA |EPWM_AQ_OUTPUT_HIGH_DOWN_CMPA));
    // 死区延迟方式
    EPWM_setRisingEdgeDeadBandDelayInput(myEPWM2_BASE,EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(myEPWM2_BASE,EPWM_DB_INPUT_EPWMA);
    // 死区时间
    EPWM_setRisingEdgeDelayCount(myEPWM2_BASE, DeadTime);
    EPWM_setFallingEdgeDelayCount(myEPWM2_BASE, DeadTime);

    EPWM_setDeadBandDelayMode(myEPWM2_BASE, EPWM_DB_RED, true);
    EPWM_setDeadBandDelayMode(myEPWM2_BASE, EPWM_DB_FED, true);
    EPWM_setDeadBandDelayPolarity(myEPWM2_BASE, EPWM_DB_RED,EPWM_DB_POLARITY_ACTIVE_HIGH);
    EPWM_setDeadBandDelayPolarity(myEPWM2_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);
    //过流配置TZ,过流时的PWM状态
    EPWM_setTripZoneAction(myEPWM2_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW);
    EPWM_setTripZoneAction(myEPWM2_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW);
    //TZ信号源
#if(OCChannelNum == 1)
    EPWM_enableTripZoneSignals(myEPWM2_BASE, EPWM_TZ_SIGNAL_OSHT1);
#else
    EPWM_enableTripZoneSignals(myEPWM2_BASE, EPWM_TZ_SIGNAL_OSHT1);
    EPWM_enableTripZoneSignals(myEPWM2_BASE, EPWM_TZ_SIGNAL_OSHT2);
#endif

    //基于PWM1脉冲源进行同步
    EPWM_setSyncInPulseSource(myEPWM2_BASE, EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM1);

    //---------------------------------------------------------------------------------------------
    //6. PWM3配置【MotA】
    //---------------------------------------------------------------------------------------------
    //EPWM_setEmulationMode(myEPWM3_BASE, EPWM_EMULATION_FREE_RUN);
    // PWM 时钟分频
    EPWM_setClockPrescaler(myEPWM3_BASE, EPWM_CLOCK_DIVIDER_1,EPWM_HSCLOCK_DIVIDER_1);
    // 装载方式-立即
    EPWM_setPeriodLoadMode(myEPWM3_BASE,EPWM_PERIOD_DIRECT_LOAD);
    // 【周期值】
    EPWM_setTimeBasePeriod(myEPWM3_BASE, PWMPriod);
    EPWM_setTimeBaseCounter(myEPWM3_BASE, 0);
    // 【相移】
    EPWM_disablePhaseShiftLoad(myEPWM3_BASE);
    EPWM_setPhaseShift(myEPWM3_BASE, 0);
	EPWM_enablePhaseShiftLoad(myEPWM3_BASE);
    // 计数模式 Up-Down
    EPWM_setTimeBaseCounterMode(myEPWM3_BASE,EPWM_COUNTER_MODE_UP_DOWN);
    // 设置初期占空比 【0%】
    EPWM_setCounterCompareValue(myEPWM3_BASE,EPWM_COUNTER_COMPARE_A,0);
    EPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE,EPWM_COUNTER_COMPARE_A,EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    // 动作限定模块
    EPWM_setActionQualifierActionComplete(myEPWM3_BASE,EPWM_AQ_OUTPUT_A,(EPWM_ActionQualifierEventAction)(EPWM_AQ_OUTPUT_LOW_UP_CMPA |EPWM_AQ_OUTPUT_HIGH_DOWN_CMPA));
    // 死区延迟方式
    EPWM_setRisingEdgeDeadBandDelayInput(myEPWM3_BASE,EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(myEPWM3_BASE,EPWM_DB_INPUT_EPWMA);
    // 死区时间
    EPWM_setRisingEdgeDelayCount(myEPWM3_BASE, DeadTime);
    EPWM_setFallingEdgeDelayCount(myEPWM3_BASE, DeadTime);

    EPWM_setDeadBandDelayMode(myEPWM3_BASE, EPWM_DB_RED, true);
    EPWM_setDeadBandDelayMode(myEPWM3_BASE, EPWM_DB_FED, true);
    EPWM_setDeadBandDelayPolarity(myEPWM3_BASE, EPWM_DB_RED,EPWM_DB_POLARITY_ACTIVE_HIGH);
    EPWM_setDeadBandDelayPolarity(myEPWM3_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);
    //过流配置TZ,过流时的PWM状态
    EPWM_setTripZoneAction(myEPWM3_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW);
    EPWM_setTripZoneAction(myEPWM3_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW);
    //TZ信号源
#if(OCChannelNum == 1)
    EPWM_enableTripZoneSignals(myEPWM3_BASE, EPWM_TZ_SIGNAL_OSHT1);
#else
    EPWM_enableTripZoneSignals(myEPWM3_BASE, EPWM_TZ_SIGNAL_OSHT2);
#endif

    //基于PWM1脉冲源进行同步
    EPWM_setSyncInPulseSource(myEPWM3_BASE, EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM1);

    /*----------------------------------------------------------------------------------------------*/
    /* 7. PWM4配置                                                                                   */
    /*----------------------------------------------------------------------------------------------*/
    //EPWM_setEmulationMode(myEPWM4_BASE, EPWM_EMULATION_FREE_RUN);
    // PWM 时钟分频
    EPWM_setClockPrescaler(myEPWM4_BASE, EPWM_CLOCK_DIVIDER_1,EPWM_HSCLOCK_DIVIDER_1);
    // 装载方式-立即
    EPWM_setPeriodLoadMode(myEPWM4_BASE,EPWM_PERIOD_DIRECT_LOAD);
    // 【周期值】
    EPWM_setTimeBasePeriod(myEPWM4_BASE, PWMPriod );
    EPWM_setTimeBaseCounter(myEPWM4_BASE, 0);
    // 【相移】
    EPWM_disablePhaseShiftLoad(myEPWM4_BASE);
    EPWM_setPhaseShift(myEPWM4_BASE, ACRTime);      // 相移时间
    EPWM_enablePhaseShiftLoad(myEPWM4_BASE);
    // 计数模式 Up-Down
    EPWM_setTimeBaseCounterMode(myEPWM4_BASE,EPWM_COUNTER_MODE_UP_DOWN);

    //基于PWM1脉冲源进行同步
    EPWM_setSyncInPulseSource(myEPWM4_BASE, EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM1);

    EPWM_setClockPrescaler(myEPWM5_BASE, EPWM_CLOCK_DIVIDER_1,EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(myEPWM5_BASE, 6250);
    EPWM_setTimeBaseCounter(myEPWM5_BASE, 0);
    EPWM_setTimeBaseCounterMode(myEPWM5_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_disablePhaseShiftLoad(myEPWM5_BASE);
    EPWM_setPhaseShift(myEPWM5_BASE, 0);
    EPWM_setCounterCompareValue(myEPWM5_BASE, EPWM_COUNTER_COMPARE_A, 0);
    EPWM_setCounterCompareShadowLoadMode(myEPWM5_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

#endif

    //---------------------------------------------------------------------------------------------
    // 13. ADC 采样触发【MotA】
    //---------------------------------------------------------------------------------------------
    // 关闭SOC 触发
    EPWM_disableADCTrigger(myEPWM4_BASE, EPWM_SOC_A);
    // Configure the SOC to occur on the first up-count event
    if( ( Prm.syssw2 & 0x0100 )  ==  0x0000 )
    {
        //PWM 零点和中点更新
        EPWM_setADCTriggerSource(myEPWM4_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ETSOCAMIX);
    }
    else
    {
        //PWM中点更新
        EPWM_setADCTriggerSource(myEPWM4_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_PERIOD);
    }

    EPWM_setADCTriggerEventPrescale(myEPWM4_BASE, EPWM_SOC_A, 1);
    EPWM_setCountModeAfterSync(myEPWM4_BASE,EPWM_COUNT_MODE_UP_AFTER_SYNC);
    //
    // Set the local ePWM module clock divider to /1
    //
    EPWM_setClockPrescaler(myEPWM4_BASE,EPWM_CLOCK_DIVIDER_1,EPWM_HSCLOCK_DIVIDER_1);
    //
    // Freeze the counter
    //
    EPWM_setTimeBaseCounterMode(myEPWM4_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
    EPWM_setTimeBaseCounterMode(myEPWM4_BASE, EPWM_COUNTER_MODE_UP_DOWN);

}



/****************************************************************************************************/
/*                                                                                                  */
/*  OC 和SC 信号                                                                                      */
/*                                                                                                  */
/****************************************************************************************************/
void INTERRUPT_init(){

    // MotorA
    Interrupt_register(INT_EPWM1_TZ, &epwm1TZISR);
    Interrupt_enable(INT_EPWM1_TZ);

}


/****************************************************************************************************/
/*                                                                                                  */
/*  同步初始化                                                                                         */
/*                                                                                                  */
/****************************************************************************************************/
void SYNC_init()
{
    SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT);
    // SOCA
    SysCtl_enableExtADCSOCSource(0);
}

/****************************************************************************************************/
/*                                                                                                  */
/*  PWM初始化                                                                                         */
/*                                                                                                  */
/****************************************************************************************************/
void InitCpu1_PWM( void )
{

    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    
    INTERRUPT_init( );
    SYNC_init( );
    EPWM_init( );


    EPWM_forceTripZoneEvent( EPWM1_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent( EPWM2_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent( EPWM3_BASE, EPWM_TZ_FORCE_EVENT_OST);

    PWMPin_init( );

}


