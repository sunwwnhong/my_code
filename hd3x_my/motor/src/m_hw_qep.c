//==================================================================================================
//
// QEP的初始化
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#include "m_interfaceModify.h"









int16 qepTickerSum;
Uint32 qepPeriodSum;
Uint16 noQepTickerSum;

void InitEQep1Gpio(void);
void InitEQep2Gpio(void);




void InitEQep1Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;   // Enable pull-up on GPIO20 (EQEP1A)
    GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;   // Enable pull-up on GPIO21 (EQEP1B)
    GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;   // Enable pull-up on GPIO22 (EQEP1S)
//    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;   // Enable pull-up on GPIO23 (EQEP1I)


// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPBQSEL2.bit.GPIO50 = 0;   // Sync to SYSCLKOUT GPIO20 (EQEP1A)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO51 = 0;   // Sync to SYSCLKOUT GPIO21 (EQEP1B)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO53 = 0;   // Sync to SYSCLKOUT GPIO22 (EQEP1S)
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 0;   // Sync to SYSCLKOUT GPIO23 (EQEP1I)

/* Configure eQEP-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eQEP1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 1;   // Configure GPIO20 as EQEP1A
    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 1;   // Configure GPIO21 as EQEP1B
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 1;   // Configure GPIO22 as EQEP1S
//    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;   // Configure GPIO23 as EQEP1I


    EDIS;
}




void InitEQep2Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;    // Enable pull-up on GPIO24 (EQEP2A)
//    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;    // Enable pull-up on GPIO25 (EQEP2B)
//    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;    // Enable pull-up on GPIO26 (EQEP2I)
//    GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;    // Enable pull-up on GPIO27 (EQEP2S)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0;  // Sync to SYSCLKOUT GPIO24 (EQEP2A)
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;  // Sync to SYSCLKOUT GPIO25 (EQEP2B)
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0;  // Sync to SYSCLKOUT GPIO26 (EQEP2I)
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 0;  // Sync to SYSCLKOUT GPIO27 (EQEP2S)

/* Configure eQEP-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eQEP2 functional pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 2;   // Configure GPIO24 as EQEP2A
//    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 2;   // Configure GPIO25 as EQEP2B
//    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 2;   // Configure GPIO26 as EQEP2I
//    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 2;   // Configure GPIO27 as EQEP2S

    EDIS;
}




volatile struct EQEP_REGS *pEQepRegsFvc = &EQep1Regs;
//=====================================================================
//
// 速度采样的QEP初始化
//
//=====================================================================
void InitFvcEqep(void)
{


    pEQepRegsFvc->QUPRD = 1;

    pEQepRegsFvc->QDECCTL.bit.QSRC = 00;     // quadrature count mode
    //pEQepRegsFvc->QDECCTL.bit.QSRC = 01; // Direction-count mode (QCLK = xCLK, QDIR = xDIR)
    pEQepRegsFvc->QDECCTL.bit.XCR = 0;      // 2x resolution: Count the rising/falling edge
    pEQepRegsFvc->QDECCTL.bit.SWAP = 0;     //
    pEQepRegsFvc->QDECCTL.bit.QAP = 0;
    pEQepRegsFvc->QDECCTL.bit.QBP = 0;
    pEQepRegsFvc->QDECCTL.bit.QIP = 0;

    pEQepRegsFvc->QEPCTL.bit.FREE_SOFT = 2;
    pEQepRegsFvc->QEPCTL.bit.PCRM = 1; // reset on maximum postion
    pEQepRegsFvc->QEPCTL.bit.UTE = 1;  // Unit Timeout Enable
    pEQepRegsFvc->QEPCTL.bit.QCLM = 1; // Latch on unit time out
    pEQepRegsFvc->QPOSMAX = 0xFFFFFFFF;
    pEQepRegsFvc->QEPCTL.bit.QPEN = 1; // QEP enable

    //pEQepRegsFvc->QCAPCTL.bit.UPPS = 2;  // QCLK/4
    pEQepRegsFvc->QCAPCTL.bit.UPPS = 1;  // QCLK/2
    pEQepRegsFvc->QCAPCTL.bit.CCPS = 4;  // SYSCLKOUT/16
    pEQepRegsFvc->QCAPCTL.bit.CEN = 1;   // QEP Capture Enable
}


int16 period;
//==============================================================================
//
// 速度采样计算
// 0ms调用
//
//==============================================================================
void pulseInSampleFvcQep(void)
{            
    DINT;
    if (pEQepRegsFvc->QEPSTS.bit.COEF)
    {
        pEQepRegsFvc->QEPSTS.bit.COEF = 1;

        period++;
    }
    if (pEQepRegsFvc->QEPSTS.bit.UPEVNT)
    {
        pEQepRegsFvc->QEPSTS.bit.UPEVNT = 1;    // clear
        qepPeriodSum += pEQepRegsFvc->QCPRD;    // 时间

        if (pEQepRegsFvc->QEPSTS.bit.QDF)   // 正向
            qepTickerSum++;     // 捕获次数
        else
            qepTickerSum--;
    }
    EINT;
}


u16   fvcOld;
extern union DSP_MAIN_COMMAND1 coreMainCmd1;
//==============================================================================
//
// PG卡更改
// 2ms调用
//
//==============================================================================
void FvcQepChange(void)
{
    u16 tmp;

//    tmp = corePgPara.elem.fvcPgSrc;
    tmp = coreMainCmd1.bit.pgLocation;
    
    if (tmp != fvcOld)
    {
        if (tmp == 0)      // 0-IO板的QEP
        {
            pEQepRegsFvc = &EQep1Regs;
        }
        else    // 1-主控板的扩展PG
        {
            pEQepRegsFvc = &EQep2Regs;
        }

        InitFvcEqep();
        
        fvcOld = tmp;
    }

}








