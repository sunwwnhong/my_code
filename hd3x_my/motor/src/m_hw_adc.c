//==================================================================================================
//
// DSP芯片的AD初始化
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================
#include "main.h"
#include "m_main.h"
#include "test.h"
#include "m_speedSample.h"
#include "m_interface.h"
#include "m_macro_AO.h"
#include "m_interfaceModify.h"


#include "m_macro_error.h"

#include "Debug.h"
#include "SimpleDebug.h"


#define ADC_usDELAY  10000UL


//==============================================================================
//
// DSP的AD初始化
//
//==============================================================================
void InitAdc(void)
{
    DELAY_US(ADC_usDELAY);

    AdcRegs.ADCTRL1.bit.RESET = 1;
    DELAY_US(1);                    // 1us > 2个ADC clock

// *IMPORTANT*
    // The ADC_cal function, which  copies the ADC calibration values from TI reserved
    // OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
    // Boot ROM. If the boot ROM code is bypassed during the debug process, the
    // following function MUST be called for the ADC to function according
    // to specification. The clocks to the ADC MUST be enabled before calling this
    // function.
    // See the device data manual and/or the ADC Reference
    // Manual for more information.

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
    ADC_cal();
    EDIS;

    AdcRegs.ADCTRL3.all = 0x00E0;   // Power up bandgap/reference/ADC circuits
    DELAY_US(ADC_usDELAY);          // Delay before converting ADC channels

    AdcRegs.ADCST.all = 0x30;
    AdcRegs.ADCOFFTRIM.all = 0;
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 1;
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;          // 顺序采样模式

    AdcRegs.ADCTRL1.bit.CPS = 1;                // ADC时钟为12.5MHz = 50MHz/2/2 100 // ADC时钟为18.75MHz = 75MHz/2/2 100
                                                // 设置ADC时钟为7.5MHz = 30MHz/2/2  60
    AdcRegs.ADCTRL1.bit.ACQ_PS = 1;             // 采样时间 10*ADCCLK
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;           // 启停模式
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;           // 级联模式
    AdcRegs.ADCTRL2.bit.EXT_SOC_SEQ1 = 0;       // External signal start-of-conversion bit for SEQ1

   // AdcRegs.ADCMAXCONV.all = 15;                // 转换_+1通道
    AdcRegs.ADCMAXCONV.all = 15;
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;        // ADCINA0,   IU1
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 1;        // ADCINA1,   UdcUp
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 2;        // ADCINA2,   UR
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 3;        // ADCINA3,   UT
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 4;        // ADCINA4,   IW
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 5;        // ADCINA5,   INTER_U
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 6;        // ADCINA6, 
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 7;        // ADCINA7, 
    
    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 8;       // ADCINB0,  IV1
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 9;       // ADCINB1,  UdcDown
    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 10;       // ADCINB2, US
    AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 11;       // ADCINB3, NTC1
    AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 12;       // ADCINB4, NTC2
    AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 13;       // ADCINB5, NTC3
    AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 14;        // ADCINB6, AI1
    AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 15;        // ADCINB7, AI2
}












