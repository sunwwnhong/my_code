//*************************************************************************************************
//文件名:APP06_QEP.c
//创建时间:2022.07.11
//版本说明:V1.0
//功能描述:QEP 信号初始化
//*************************************************************************************************
#include "Main.h"

/****************************************************************************************************/
/*                                                                                                  */
/*  QEP 相关GPIO引脚定义                                                                               */
/*                                                                                                  */
/****************************************************************************************************/
void InitGPIO_QEP( void )
{
#ifdef CPU1
    /*----------------------------------------------------------------------------------------------*/
    /*  QEP1 GPIO 引脚                                                                               */
    /*----------------------------------------------------------------------------------------------*/
    uint32_t SysClkdiv = 1;

    GPIO_setAnalogMode(207, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(208, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_207_EQEP2_A);
    GPIO_setPinConfig(GPIO_208_EQEP2_B);
    //GPIO_setPinConfig(GPIO_103_EQEP2_INDEX);
    GPIO_setPadConfig(207, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPadConfig(208, GPIO_PIN_TYPE_PULLUP);
    //GPIO_setPadConfig(103, GPIO_PIN_TYPE_PULLUP);

    GPIO_setQualificationPeriod(207, SysClkdiv);         // Qual period=SYSCLKOUT/2
    GPIO_setQualificationPeriod(208, SysClkdiv);         // Qual period=SYSCLKOUT/2
    //GPIO_setQualificationPeriod(103, SysClkdiv);         // Qual period=SYSCLKOUT/2
    GPIO_setQualificationMode(207, GPIO_QUAL_SYNC);   // 6 samples
    GPIO_setQualificationMode(208, GPIO_QUAL_SYNC);   // 6 samples




#endif
}


/****************************************************************************************************/
/*                                                                                                  */
/*  QEP初始化(外部脉冲输入和ABZ编码器)                                                                                         */
/*                                                                                                  */
/****************************************************************************************************/
void InitCpu1_eQEP( void )
{
    InitGPIO_QEP( );
    /*----------------------------------------------------------------------------------------------*/
    EALLOW;

    uint16_t PulsePolarSet_A = 0;
    uint16_t PulsePolarSet_B = 0;

#ifdef CPU1
    /*----------------------------------------------------------------------------------------------*/
    /* Disable, clear all flags and interrupts                                                      */
    /*----------------------------------------------------------------------------------------------*/
    EQEP_disableInterrupt(EQEP2_BASE,
        (EQEP_INT_GLOBAL            | EQEP_INT_POS_CNT_ERROR      | EQEP_INT_PHASE_ERROR        | EQEP_INT_DIR_CHANGE      |
        EQEP_INT_WATCHDOG           | EQEP_INT_UNDERFLOW          | EQEP_INT_OVERFLOW           | EQEP_INT_POS_COMP_READY  |
        EQEP_INT_POS_COMP_MATCH     | EQEP_INT_STROBE_EVNT_LATCH  | EQEP_INT_INDEX_EVNT_LATCH   | EQEP_INT_UNIT_TIME_OUT   |
        EQEP_INT_QMA_ERROR));
    EQEP_clearInterruptStatus(EQEP2_BASE,
        (EQEP_INT_GLOBAL            | EQEP_INT_POS_CNT_ERROR      | EQEP_INT_PHASE_ERROR        | EQEP_INT_DIR_CHANGE      |
        EQEP_INT_WATCHDOG           | EQEP_INT_UNDERFLOW          | EQEP_INT_OVERFLOW           | EQEP_INT_POS_COMP_READY  |
        EQEP_INT_POS_COMP_MATCH     | EQEP_INT_STROBE_EVNT_LATCH  | EQEP_INT_INDEX_EVNT_LATCH   | EQEP_INT_UNIT_TIME_OUT   |
        EQEP_INT_QMA_ERROR));

    /*----------------------------------------------------------------------------------------------*/
    /* Set the strobe input source of the eQEP module.                                              */
    /*----------------------------------------------------------------------------------------------*/
    EQEP_setStrobeSource(EQEP2_BASE,EQEP_STROBE_FROM_GPIO);

    //---------------------------------------------------------------------------------------------
    // 设置脉冲类型设置
    //---------------------------------------------------------------------------------------------
    uint16_t PulseTypeSet = 0;
    EQEP_QMAMode QMAMode;

    PulseTypeSet = EQEP_CONFIG_QUADRATURE | EQEP_CONFIG_2X_RESOLUTION;
    QMAMode = EQEP_QMA_MODE_BYPASS;
    PulsePolarSet_A = 1;
    PulsePolarSet_B = 0;


    /*----------------------------------------------------------------------------------------------*/
    EQEP_setInputPolarity(EQEP2_BASE,PulsePolarSet_A,PulsePolarSet_B,true,false);
    EQEP_setDecoderConfig(EQEP2_BASE, ( PulseTypeSet | EQEP_CONFIG_NO_SWAP | EQEP_CONFIG_IGATE_DISABLE));

    // Set the emulation mode of the eQEP module.
    EQEP_setEmulationMode(EQEP2_BASE,EQEP_EMULATIONMODE_RUNFREE);
    // Configures eQEP module position counter unit.
    EQEP_setPositionCounterConfig(EQEP2_BASE,EQEP_POSITION_RESET_IDX,65535U);
    // Sets the current encoder position.
    EQEP_setPosition(EQEP2_BASE,0U);
    // Enables the eQEP module unit timer.
    EQEP_enableUnitTimer(EQEP2_BASE,1000000U);
    // Disables the eQEP module watchdog timer.
    EQEP_disableWatchdog(EQEP2_BASE);
    // Configures the quadrature modes in which the position count can be latched.
    EQEP_setLatchMode(EQEP2_BASE,(EQEP_LATCH_UNIT_TIME_OUT|EQEP_LATCH_RISING_STROBE|EQEP_LATCH_FALLING_INDEX));
    // Set the quadrature mode adapter (QMA) module mode.
    EQEP_setQMAModuleMode(EQEP2_BASE,QMAMode);
    // Enables individual eQEP module interrupt sources.
    EQEP_enableInterrupt(EQEP2_BASE,(EQEP_INT_UNIT_TIME_OUT|EQEP_INT_INDEX_EVNT_LATCH));
    // Configures the mode in which the position counter is initialized.
    EQEP_setPositionInitMode(EQEP2_BASE,(EQEP_INIT_DO_NOTHING));
    // Sets the software initialization of the encoder position counter.
    EQEP_setSWPositionInit(EQEP2_BASE,true);
    // Sets the init value for the encoder position counter.
    EQEP_setInitialPosition(EQEP2_BASE,500U);
    // Enables the eQEP module.
    EQEP_enableModule(EQEP2_BASE);

#endif

    EDIS;

}

/****************************************************************************************************/
/*                                                                                                  */
/*  QEP 位置读取                                                                                      */
/*                                                                                                  */
/****************************************************************************************************/
uint16_t eQEP1Cnt( void )
{
    uint16_t kx = HWREG(EQEP1_BASE + EQEP_O_QPOSCNT);
    return kx;
}

/****************************************************************************************************/
/*                                                                                                  */
/*  QEP 位置读取（ABZ编码器）                                                                                      */
/*                                                                                                  */
/****************************************************************************************************/
uint16_t eQEP2Cnt( void )
{
    uint16_t kx = HWREG(EQEP2_BASE + EQEP_O_QPOSCNT);
    return kx;
}


