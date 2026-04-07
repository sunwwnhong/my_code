//*************************************************************************************************
//文件名:APP03_INT.c
//创建时间:2022.07.11
//版本说明:V1.0
//功能描述:中断信号源
//*************************************************************************************************
#include "Main.h"


#define myECAP0_BASE ECAP1_BASE
#define myECAP1_BASE ECAP2_BASE

/****************************************************************************************************/
/*Function_Name:ECAP0_init                                                                          */
/*Description  : ECAP 初始化                                                                          */
/****************************************************************************************************/
void ECAP0_init()
{
    //myECAP0 initialization
    // Stops Time stamp counter.
    ECAP_stopCounter(myECAP0_BASE);
    // Sets eCAP in APWM mode.
    ECAP_enableAPWMMode(myECAP0_BASE);
    // Set eCAP APWM period.
    ECAP_setAPWMPeriod(myECAP0_BASE,12499U);
    // Set eCAP APWM on or off time count.
    ECAP_setAPWMCompare(myECAP0_BASE,6250);
    // Set eCAP APWM polarity.
    ECAP_setAPWMPolarity(myECAP0_BASE,ECAP_APWM_ACTIVE_HIGH);

    // Disable counter loading with phase shift value.
    ECAP_disableLoadCounter(myECAP0_BASE);
    // Sets a phase shift value count.
    ECAP_setPhaseShiftCount(myECAP0_BASE,9375U);

//    ECAP_enableLoadCounter(myECAP0_BASE);
    // Configures Sync out signal mode.
    ECAP_setSyncOutMode(myECAP0_BASE,ECAP_SYNC_OUT_SYNCI);
    // Configures emulation mode.
    ECAP_setEmulationMode(myECAP0_BASE,ECAP_EMULATION_STOP);
    // Set up the source for sync-in pulse..
    //ECAP_setSyncInPulseSource(myECAP0_BASE,ECAP_SYNC_IN_PULSE_SRC_DISABLE);
    ECAP_setSyncInPulseSource(myECAP0_BASE,ECAP_SYNC_IN_PULSE_SRC_ETHERCAT_SYNC0);
	
	//保证同步SCANA与PWM之间相位值同步 syhu @20251112
    ECAP_setPhaseShiftCount(myECAP0_BASE,0);
    ECAP_enableLoadCounter(myECAP0_BASE);
}

/****************************************************************************************************/
/*Function_Name:ECAP1_init                                                                          */
/*Description  : ECAP 初始化                                                                          */
/****************************************************************************************************/
void ECAP1_init()
{
    //myECAP0 initialization
    // Stops Time stamp counter.
    ECAP_stopCounter(myECAP1_BASE);
    // Sets eCAP in APWM mode.
    ECAP_enableAPWMMode(myECAP1_BASE);
    // Set eCAP APWM period.
    ECAP_setAPWMPeriod(myECAP1_BASE,24999U);
    // Set eCAP APWM on or off time count.
    ECAP_setAPWMCompare(myECAP1_BASE,12499);
    // Set eCAP APWM polarity.
    ECAP_setAPWMPolarity(myECAP1_BASE,ECAP_APWM_ACTIVE_HIGH);
    // Sets a phase shift value count.
    ECAP_setPhaseShiftCount(myECAP1_BASE,0U);
    // Disable counter loading with phase shift value.
    ECAP_disableLoadCounter(myECAP1_BASE);
    // Configures Sync out signal mode.
    ECAP_setSyncOutMode(myECAP1_BASE,ECAP_SYNC_OUT_SYNCI);
    // Configures emulation mode.
    ECAP_setEmulationMode(myECAP1_BASE,ECAP_EMULATION_STOP);
    // Set up the source for sync-in pulse..
    ECAP_setSyncInPulseSource(myECAP1_BASE,ECAP_SYNC_IN_PULSE_SRC_ETHERCAT_SYNC0);
	
	//保证同步SCANA与PWM之间相位值同步 syhu @20251112
    ECAP_setPhaseShiftCount(myECAP1_BASE,0);
    ECAP_enableLoadCounter(myECAP1_BASE);
}


//*************************************************************************************************
//Function_Name:IntS_init
//Description  : A :Generate 16KHz 脉冲信号 50%
//               B :Generate  8KHz 脉冲信号 50%
//*************************************************************************************************
void InitCpu1_IntSrc( void )
{
    EALLOW;

    //---------------------------------------------------------------------------------------------
    //
    // OUTPUTXBAR3 -> myOUTPUTXBAR0 Pinmux
    //
   // GPIO_setPinConfig( GPIO_26_OUTPUTXBAR3 );
    GPIO_setAnalogMode(203, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig( GPIO_203_OUTPUTXBAR3 );
    ECAP0_init();
    //
    //myOUTPUTXBAR0 initialization
    //
    XBAR_setOutputLatchMode(OUTPUTXBAR_BASE, XBAR_OUTPUT3, false);
    XBAR_invertOutputSignal(OUTPUTXBAR_BASE, XBAR_OUTPUT3, false);

    //Mux configuration
    XBAR_setOutputMuxConfig(OUTPUTXBAR_BASE, XBAR_OUTPUT3, XBAR_OUT_MUX00_ECAP1_OUT);
    XBAR_enableOutputMux(OUTPUTXBAR_BASE, XBAR_OUTPUT3, XBAR_MUX00);
    //---------------------------------------------------------------------------------------------
    //
    // OUTPUTXBAR4 -> myOUTPUTXBAR0 Pinmux
    //

   // GPIO_setPinConfig( GPIO_27_OUTPUTXBAR4 );
    GPIO_setAnalogMode(204, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig( GPIO_204_OUTPUTXBAR4 );
    ECAP1_init();
    //
    //myOUTPUTXBAR0 initialization
    //
    XBAR_setOutputLatchMode(OUTPUTXBAR_BASE, XBAR_OUTPUT4, false);
    XBAR_invertOutputSignal(OUTPUTXBAR_BASE, XBAR_OUTPUT4, false);

    //Mux configuration
    XBAR_setOutputMuxConfig(OUTPUTXBAR_BASE, XBAR_OUTPUT4, XBAR_OUT_MUX02_ECAP2_OUT);
    XBAR_enableOutputMux(OUTPUTXBAR_BASE, XBAR_OUTPUT4, XBAR_MUX02);

    //---------------------------------------------------------------------------------------------
    EDIS;
}





//*************************************************************************************************
//Function_Name:InitCpu1_Start
//Description  : 系统任务调度启动以及同步
//*************************************************************************************************
void InitCpu1_Start( void )
{

#ifdef CPU1
    CLA_init( );        //打开协处理器
#endif
#ifdef CPU1
    // 62.5us & 125us 任务调度计数器开启
	//保证同步SCANA与PWM之间相位值同步 syhu @20251112 
	//    ECAP_enableLoadCounter(myECAP0_BASE);
	//    ECAP_enableLoadCounter(myECAP1_BASE);
	//    ECAP_startCounter(myECAP0_BASE);
	//    ECAP_startCounter(myECAP1_BASE);



    // PWM 启动
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //---------------------------------------------------------------------------------------------
    // SOC_A 启动 Enabling SOCA and putting the counter in up-count mode
    //---------------------------------------------------------------------------------------------
    EPWM_enableADCTrigger(EPWM4_BASE, EPWM_SOC_A);

#endif

#ifdef CPU1
    MotA_CurrentZeroSet( );
    //MotA_InitSec |= 0xAB000000;
#endif

    //---------------------------------------------------------------------------------------------
    // 驱动器功率等级检查
    //---------------------------------------------------------------------------------------------
    //DriveTypeCheck( );  //RB200暂不包含功率检查
    //---------------------------------------------------------------------------------------------
    // 任务A开启
    ScanATask_Start( );
    // 任务B启动
    ScanBTask_Start( );
    // 任务C启动
    ScanCTask_Start( );
}



