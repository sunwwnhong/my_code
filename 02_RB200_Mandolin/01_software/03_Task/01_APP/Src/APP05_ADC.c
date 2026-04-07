//*************************************************************************************************
//文件名:APP05_ADC.c
//创建时间:2022.07.11
//版本说明:V1.0
//功能描述:ADC定时器初始化
//*************************************************************************************************
#include "Main.h"

#ifdef CPU1

#define ADC_Interrupt_En    1

#if (ADC_Interrupt_En == 1)
#define INT_myADC0_1 INT_ADCA1
volatile uint16_t adcAResult0;
volatile uint16_t adcBResult0;
volatile uint16_t adcDResult0;
#endif

//#define ADC_Resolution          ADC_RESOLUTION_12BIT          /* ADC 采样分辨率*/
//#define SampleClkNum            8                              /* 采样时钟数    */
#define ADC_Resolution          ADC_RESOLUTION_16BIT            /* ADC 采样分辨率*/
//#define SampleClkNum            50                              /* 采样时钟数    */
#define ADC_TRIGGER_SOURCE1     ADC_TRIGGER_EPWM4_SOCA          /* MotA 触发源  */
#define ADC_TRIGGER_SOURCE2     ADC_TRIGGER_EPWM8_SOCB          /* MotB 触发源  */
#define myADC0_BASE             ADCA_BASE                       /* ADC 通道A   */
#define myADC1_BASE             ADCB_BASE                       /* ADC 通道B   */
#define myADC2_BASE             ADCC_BASE                       /* ADC 通道D   */

/****************************************************************************************************/
/*                                                                                                  */
/*  ADC初始化                                                                                         */
/*                                                                                                  */
/****************************************************************************************************/
void ADC_init()
{
uint32_t SampleClkNum = 80UL;
     //ADC采样时间配置
    if( ( Prm.syssw2 & 0x0100 )  ==  0x0000 )
    {
        SampleClkNum = 75UL;
    }
    else
    {
        SampleClkNum = 300UL;//400
    }

    //ADC0通道采集阵列：【MotA】U 相电流、【MotA】U 相电流、【MotA】模块温度、芯片温度、【MotB】U 相电流、【MotB】U 相电流
    //myADC0 initialization
    // ADC Initialization: Write ADC configurations and power up the ADC
    // Configures the analog-to-digital converter module prescaler.
    ADC_setPrescaler(myADC0_BASE, ADC_CLK_DIV_4_0);
    // Configures the analog-to-digital converter resolution and signal mode.
    ADC_setMode(myADC0_BASE, ADC_Resolution, ADC_MODE_SINGLE_ENDED);
    // Sets the timing of the end-of-conversion pulse
    ADC_setInterruptPulseMode(myADC0_BASE, ADC_PULSE_END_OF_CONV);
    // Powers up the analog-to-digital converter core.
    ADC_enableConverter(myADC0_BASE);
    // Delay for 1ms to allow ADC time to power up
    DEVICE_DELAY_US(1000);

    // SOC Configuration: Setup ADC EPWM channel and trigger settings
    // Disables SOC burst mode.
    ADC_disableBurstMode(myADC0_BASE);
    // Sets the priority mode of the SOCs.
    ADC_setSOCPriority(myADC0_BASE, ADC_PRI_ALL_ROUND_ROBIN);
    // Start of Conversion 0 Configuration
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN1, SampleClkNum);       // 【MotA】U 相电流
    //ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN1, 150UL);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 1 Configuration
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN1, SampleClkNum);       // 【MotA】U 相电流
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 2 Configuration
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN5, SampleClkNum);       // 【MotA】模块温度
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 3 Configuration
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN5, SampleClkNum);      //  芯片温度
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 4 Configuration
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN5, SampleClkNum);       // 【MotB】U 相电流
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 5 Configuration
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN5, SampleClkNum);       // 【MotB】U 相电流
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER5, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 6 Configuration
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN2, SampleClkNum);       // 【MotB】U 相电流
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER6, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 7 Configuration
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN13, SampleClkNum);       // 【MotB】U 相电流
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER7, ADC_INT_SOC_TRIGGER_NONE);
    // ADC Interrupt 1 Configuration
    //      SOC/EOC number  : 2
    //      Interrupt Source: enabled
    //      Continuous Mode : disabled

#if 1
    //ADCA中断1配置
    if( ( Prm.syssw2 & 0x0100 )  ==  0x0000 )
    {
        //在采集完成第一个U相电流触发中断
        ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    }
    else
    {
        //在采集完成第二个U相电流触发中断
        ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER1);
    }

    ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    ADC_disableContinuousMode(myADC0_BASE, ADC_INT_NUMBER1);
#endif

#if 1
    /*
    //ADCA中断2配置
    if( ( Prm.syssw2 & 0x0100 )  ==  0x0000 )
    {
        ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER4);
    }
    else
    {
        ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER5);
    }

    ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER2);
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER2);
    ADC_disableContinuousMode(myADC0_BASE, ADC_INT_NUMBER2);*/
#endif
    //---------------------------------------------------------------------------------------------
    //ADC1通道采集阵列：【MotA】V 相电流、【MotA】V 相电流、【MotA】母线电压、驱动器机型、【MotB】V 相电流、【MotB】V 相电流、【MotB】母线电压
    
    //myADC1 initialization
    // ADC Initialization: Write ADC configurations and power up the ADC
    // Configures the analog-to-digital converter module prescaler.
    ADC_setPrescaler(myADC1_BASE, ADC_CLK_DIV_4_0);
    // Configures the analog-to-digital converter resolution and signal mode.
    ADC_setMode(myADC1_BASE, ADC_Resolution, ADC_MODE_SINGLE_ENDED);
    // Sets the timing of the end-of-conversion pulse
    ADC_setInterruptPulseMode(myADC1_BASE, ADC_PULSE_END_OF_CONV);
    // Powers up the analog-to-digital converter core.
    ADC_enableConverter(myADC1_BASE);
    // Delay for 1ms to allow ADC time to power up
    DEVICE_DELAY_US(500);

    // SOC Configuration: Setup ADC EPWM channel and trigger settings
    // Disables SOC burst mode.
    ADC_disableBurstMode(myADC1_BASE);
    // Sets the priority mode of the SOCs.
    ADC_setSOCPriority(myADC1_BASE, ADC_PRI_ALL_ROUND_ROBIN);
    // Start of Conversion 0 Configuration
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN0, SampleClkNum);       // 【MotA】V 相电流
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 1 Configuration
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN0, SampleClkNum);       // 【MotA】V 相电流
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 2 Configuration
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN5, SampleClkNum);      //  【MotA】母线电压
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 3 Configuration
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN5, SampleClkNum);      //  【MotA】驱动器机型
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 4 Configuration
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN5, SampleClkNum);      //  【MotB】V 相电流
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 5 Configuration
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN5, SampleClkNum);      //  【MotB】V 相电流
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER5, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 6 Configuration
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN3, SampleClkNum);      //  【MotB】 母线电压
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER6, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 7 Configuration
    ADC_setupSOC(myADC1_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN2, SampleClkNum);      //  【MotB】V 相电流
    ADC_setInterruptSOCTrigger(myADC1_BASE, ADC_SOC_NUMBER7, ADC_INT_SOC_TRIGGER_NONE);
    //---------------------------------------------------------------------------------------------
    //myADC2 initialization
    // ADC Initialization: Write ADC configurations and power up the ADC
    // Configures the analog-to-digital converter module prescaler.
    ADC_setPrescaler(myADC2_BASE, ADC_CLK_DIV_4_0);
    // Configures the analog-to-digital converter resolution and signal mode.
    ADC_setMode(myADC2_BASE, ADC_Resolution, ADC_MODE_SINGLE_ENDED);
    // Sets the timing of the end-of-conversion pulse
    ADC_setInterruptPulseMode(myADC2_BASE, ADC_PULSE_END_OF_CONV);
    // Powers up the analog-to-digital converter core.
    ADC_enableConverter(myADC2_BASE);
    // Delay for 1ms to allow ADC time to power up
    DEVICE_DELAY_US(500);


    //ADC2通道采集阵列：【MotA】W 相电流、【MotA】W 相电流、母线电压、母线电压、【MotB】W 相电流、【MotB】W 相电流
    // SOC Configuration: Setup ADC EPWM channel and trigger settings
    // Disables SOC burst mode.
    ADC_disableBurstMode(myADC2_BASE);
    // Sets the priority mode of the SOCs.
    ADC_setSOCPriority(myADC2_BASE, ADC_PRI_ALL_ROUND_ROBIN);
    // Start of Conversion 0 Configuration
    ADC_setupSOC(myADC2_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN2, SampleClkNum);       // 【MotA】W 相电流
    ADC_setInterruptSOCTrigger(myADC2_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 1 Configuration
    ADC_setupSOC(myADC2_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN2, SampleClkNum);       // 【MotA】W 相电流
    ADC_setInterruptSOCTrigger(myADC2_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 2 Configuration
    ADC_setupSOC(myADC2_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN3, SampleClkNum);      //  母线电压
    ADC_setInterruptSOCTrigger(myADC2_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
    // Start of Conversion 3 Configuration
    ADC_setupSOC(myADC2_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SOURCE1, ADC_CH_ADCIN3, SampleClkNum);      //  母线电压
    ADC_setInterruptSOCTrigger(myADC2_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
//    // Start of Conversion 4 Configuration
//    ADC_setupSOC(myADC2_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SOURCE2, ADC_CH_ADCIN2, SampleClkNum);       // 【MotB】W 相电流
//    ADC_setInterruptSOCTrigger(myADC2_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
//    // Start of Conversion 5 Configuration
//    ADC_setupSOC(myADC2_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SOURCE2, ADC_CH_ADCIN2, SampleClkNum);       // 【MotB】W 相电流
//    ADC_setInterruptSOCTrigger(myADC2_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_NONE);
//    // Start of Conversion 6 Configuration
//    ADC_setupSOC(myADC2_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SOURCE2, ADC_CH_ADCIN3, SampleClkNum);       // 【MotB】模块温度
//    ADC_setInterruptSOCTrigger(myADC2_BASE, ADC_SOC_NUMBER5, ADC_INT_SOC_TRIGGER_NONE);

}

#if (ADC_Interrupt_En == 1)
/****************************************************************************************************/
/*                                                                                                  */
/*  ADC A Interrupt 1 ISR                                                                           */
/*                                                                                                  */
/****************************************************************************************************/
/*
__interrupt void adcA1ISR(void)
{


    //
    // Store results
    //
    //KPX_MOTA_RUN_LED_TOG();


    adcAResult0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
    adcBResult0 = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0);
    adcDResult0 = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER0);

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}*/
#endif

/****************************************************************************************************/
/*                                                                                                  */
/*  ADC初始化                                                                                         */
/*                                                                                                  */
/****************************************************************************************************/
void ADCINT_init( )
{
#if (ADC_Interrupt_En == 1)
    // Interrupt Setings for INT_myADC0_1
    //Interrupt_register(INT_myADC0_1, &adcA1ISR);
    //Interrupt_enable(INT_myADC0_1);
#endif
}

void ASYSCTL_init()
{
    // asysctl initialization
    // Enables the temperature sensor output to the ADC.
    ASysCtl_enableTemperatureSensor();
    DEVICE_DELAY_US(500);
}

/****************************************************************************************************/
/*                                                                                                  */
/*  ADC初始化                                                                                         */
/*                                                                                                  */
/****************************************************************************************************/
void InitCpu1_ADC( void )
{
    EALLOW;

    ASYSCTL_init();
    ADC_init();
    ADCINT_init();

    EDIS;
}

#endif


