// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:19 $
//###########################################################################
//
// FILE:   DSP2833x_EPwm.c
//
// TITLE:  DSP2833x ePWM Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define EPWM_TIMER_TBPRD      3750 // 2500
#define  PWM_CLK_DIV          1

//---------------------------------------------------------------------------
// InitEPwm: 
//---------------------------------------------------------------------------
// This function initializes the ePWM(s) to a known state.
//
void InitEPwm(void)
{
	EALLOW;
	/////////////PWM1//////////////
//Set the Time-Base (TB) Module
     EPwm1Regs.CMPCTL.all = 0x0000;
	EPwm1Regs.TBPRD = EPWM_TIMER_TBPRD - 1; 
	EPwm1Regs.CMPB = 0;
	EPwm1Regs.TBPHS.all = 0;
	EPwm1Regs.TBCTL.all = 0xE012;
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = PWM_CLK_DIV;
	EPwm1Regs.TBCTL.bit.CLKDIV = PWM_CLK_DIV;
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
//Set the Counter-compare (CC) Module
	EPwm1Regs.CMPCTL.all = 0x0100;
	//EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	//EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm1Regs.TBCTR = 0;
	
//Set the Action-qualifier (AQ) Module
	EPwm1Regs.AQCTLA.all = 0;//0x0090;
	//EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;
	EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;

    /////////////PWM3//////////////
//Set the Time-Base (TB) Module
	EPwm3Regs.TBPRD = EPWM_TIMER_TBPRD - 1; 
	EPwm3Regs.CMPB = 0;
	EPwm3Regs.TBPHS.all = 0;
	EPwm3Regs.TBCTL.all = 0xE012;
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = PWM_CLK_DIV;
	EPwm3Regs.TBCTL.bit.CLKDIV = PWM_CLK_DIV;
	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;
//Set the Counter-compare (CC) Module
	EPwm3Regs.CMPCTL.all = 0x0100;
	//EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	//EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm3Regs.TBCTR = 0;
	
//Set the Action-qualifier (AQ) Module
	EPwm3Regs.AQCTLA.all = 0;//0x0090;
	//EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;
	EPwm3Regs.AQCTLB.bit.ZRO = AQ_SET;

	    /////////////PWM4//////////////
//Set the Time-Base (TB) Module
	EPwm4Regs.TBPRD = EPWM_TIMER_TBPRD - 1; 
	EPwm4Regs.CMPB = 0;
	EPwm4Regs.TBPHS.all = 0;
	EPwm4Regs.TBCTL.all = 0xE012;
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = PWM_CLK_DIV;
	EPwm4Regs.TBCTL.bit.CLKDIV = PWM_CLK_DIV;
	EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;
//Set the Counter-compare (CC) Module
	EPwm4Regs.CMPCTL.all = 0x0100;
	//EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	//EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm4Regs.TBCTR = 0;
	
//Set the Action-qualifier (AQ) Module
	EPwm4Regs.AQCTLA.all = 0;//0x0090;
	//EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR;
	EPwm4Regs.AQCTLB.bit.ZRO = AQ_SET;

//Set the Dead-Band Generator (DB) Module
//	EPwm1Regs.AQSFRC.all  = 0x0;
//	EPwm1Regs.AQCSFRC.all = 0x0;	
//	EPwm1Regs.DBCTL.all = 0x0007;
	//EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	//EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 
//	EPwm1Regs.DBFED = C_MAX_DB;
//	EPwm1Regs.DBRED = C_MAX_DB;
//Set the PWM-chopper (PC) Module
//Set the Trip-zone (TZ) Module
//    EPwm1Regs.TZCLR.all = 0x07;
//    EPwm1Regs.TZSEL.all = 0x0102;       // OHS1:TZ1;
                                        // CBC2:TZ2;
//    EPwm1Regs.TZCTL.all = 0x0005;
//    EPwm1Regs.TZEINT.all = 0x0004;

//Set the Event-trigger (ET) Module	
//	EPwm1Regs.ETCLR.bit.INT = 1;				//首先清除中断标志
//	EPwm1Regs.ETSEL.all = 0x0F09;
	//EPwm1Regs.ETSEL.bit.INTEN = 1;
	//EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
	//EPwm1Regs.ETSEL.bit.SOCAEN = 1;
	//EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTRD_CMPB;	//COMPAR_B的下降沿启动ADC
//	EPwm1Regs.ETPS.all = 0x0101;
	//EPwm1Regs.ETPS.bit.INTPRD = 1;
	//EPwm1Regs.ETPS.bit.SOCAPRD = 1;				//每一事件启动一次AD
/*
	/////////////PWM2//////////////
//Set the Time-Base (TB) Module
	EPwm2Regs.TBPRD = EPWM_TIMER_TBPRD; 
	EPwm2Regs.TBPHS.all = 0;
	EPwm2Regs.TBCTL.all = 0xE006;
    //EPwm2Regs.TBCTL.bit.FREE_SOFT = 3;
	//EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	//EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;
	//EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	//EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;	//以PWM1同步信号为输出同步信号
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = PWM_CLK_DIV;
	//EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP;
//Set the Counter-compare (CC) Module
	EPwm2Regs.CMPCTL.all = 0x0100;
	//EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	//EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	//EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	//EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm2Regs.CMPA.half.CMPA = EPWM_TIMER_TBPRD;
//Set the Action-qualifier (AQ) Module
	EPwm2Regs.AQCTLA.all = 0x0090;
	//EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
	//EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
//Set the Dead-Band Generator (DB) Module
	EPwm2Regs.AQSFRC.all  = 0x0;
	EPwm2Regs.AQCSFRC.all = 0x0;	
	EPwm2Regs.DBCTL.all = 0x0007;
	//EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	//EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 
//	EPwm2Regs.DBFED = C_MAX_DB;
//	EPwm2Regs.DBRED = C_MAX_DB;
//Set the PWM-chopper (PC) Module
//Set the Trip-zone (TZ) Module

    EPwm2Regs.TZSEL.all = 0x0102;       // OHS1:TZ1;
                                        // CBC2:TZ2;
    EPwm2Regs.TZCTL.all = 0x0005;
    EPwm2Regs.TZEINT.all = 0x0004;

//Set the Event-trigger (ET) Module	
    EPwm2Regs.ETSEL.all = 0;
    EPwm2Regs.ETPS.all  = 0;
    
	/////////////PWM3//////////////
//Set the Time-Base (TB) Module
	EPwm4Regs.TBPRD = EPWM_TIMER_TBPRD; 
	EPwm4Regs.TBPHS.all = 0;
	EPwm4Regs.TBCTL.all = 0xE036;
    //EPwm3Regs.TBCTL.bit.FREE_SOFT = 3;
	//EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	//EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;
	//EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	//EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;	//不产生同步信号
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = PWM_CLK_DIV;
	//EPwm3Regs.TBCTL.bit.PHSDIR = TB_UP;
//Set the Counter-compare (CC) Module
	EPwm4Regs.CMPCTL.all = 0x0100;
	//EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	//EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	//EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	//EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	//EPwm4Regs.CMPA.half.CMPA = C_INIT_PRD/2;
//Set the Action-qualifier (AQ) Module
	EPwm4Regs.AQCTLA.all = 0x0090;
	//EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
	//EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
//Set the Dead-Band Generator (DB) Module
	EPwm4Regs.AQSFRC.all  = 0x0;
	EPwm4Regs.AQCSFRC.all = 0x00;	
	EPwm4Regs.DBCTL.all = 0x0007;
	//EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	//EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 
	EPwm4Regs.DBFED = C_MAX_DB;
	EPwm4Regs.DBRED = C_MAX_DB;
//Set the PWM-chopper (PC) Module
//Set the Trip-zone (TZ) Module

    EPwm4Regs.TZSEL.all = 0x0102;       // OHS1:TZ1;
                                        // CBC2:TZ2;
    EPwm4Regs.TZCTL.all = 0x0005;
    EPwm4Regs.TZEINT.all = 0x0004;
*/
//Set the Event-trigger (ET) Module	
	EDIS;
 
}

//---------------------------------------------------------------------------
// Example: InitEPwmGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ePWM pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 

void InitEPwmGpio(void)
{
   InitEPwm1Gpio();
  // InitEPwm2Gpio();
   InitEPwm3Gpio();
   InitEPwm4Gpio();
  /*
#if DSP28_EPWM5    
   InitEPwm5Gpio();
#endif // endif DSP28_EPWM5
#if DSP28_EPWM6
   InitEPwm6Gpio();
#endif // endif DSP28_EPWM6 
*/
}

void InitEPwm1Gpio(void)
{
   EALLOW;
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   // GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)   
   GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;
/* Configure ePWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
// Comment out other unwanted lines.

   // GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
   
    EDIS;
}

void InitEPwm2Gpio(void)
{
   EALLOW;
	
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   // GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM3B)
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;
/* Configure ePWM-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM2 functional pins.
// Comment out other unwanted lines.

    //GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B
   
    EDIS;
}

void InitEPwm3Gpio(void)
{
   EALLOW;
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

  //  GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)
       
/* Configure ePWM-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM3 functional pins.
// Comment out other unwanted lines.

 //   GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B
	
    EDIS;
}


void InitEPwm4Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   // GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pull-up on GPIO7 (EPWM4B)
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;
/* Configure ePWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM4 functional pins.
// Comment out other unwanted lines.

   // GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B
	
    EDIS;
}


#if DSP28_EPWM5
void InitEPwm5Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;    // Enable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;    // Enable pull-up on GPIO9 (EPWM5B)

/* Configure ePWM-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM5 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B
	
    EDIS;
}
#endif // endif DSP28_EPWM5


#if DSP28_EPWM6
void InitEPwm6Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;    // Enable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up on GPIO11 (EPWM6B)

/* Configure ePWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B
	
    EDIS;
}
#endif // endif DSP28_EPWM6  

//---------------------------------------------------------------------------
// Example: InitEPwmSyncGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ePWM Synch pins
//

void InitEPwmSyncGpio(void)
{

   EALLOW;

/* Configure EPWMSYNCI  */
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pull-up on GPIO32 (EPWMSYNCI)    

/* Set qualification for selected pins to asynch only */
// This will select synch to SYSCLKOUT for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;   // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)    

/* Configure EPwmSync pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
// Comment out other unwanted lines.   

   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Enable pull-up on GPIO32 (EPWMSYNCI)    



/* Configure EPWMSYNC0  */

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pull-up on GPIO33 (EPWMSYNC0)    

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;   // Enable pull-up on GPIO33 (EPWMSYNC0)    

}



//---------------------------------------------------------------------------
// Example: InitTzGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 

void InitTzGpio(void)
{
   EALLOW;
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.
   GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
   GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;    // Enable pull-up on GPIO13 (TZ2)
   GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up on GPIO14 (TZ3)
   GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up on GPIO15 (TZ4)

   GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ5)
// GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ5)

   GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ6) 
// GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ6)  
   
/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.  
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;  // Asynch input GPIO13 (TZ2)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;  // Asynch input GPIO14 (TZ3)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (TZ4)

   GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ5)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ5)

   GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ6) 
// GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ6)  

   
/* Configure TZ pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be TZ functional pins.
// Comment out other unwanted lines.   
   GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
   GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // Configure GPIO13 as TZ2
   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;  // Configure GPIO14 as TZ3
   GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;  // Configure GPIO15 as TZ4

   GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ5
// GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ5

   GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ6               
// GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ6  

   EDIS;
}



//===========================================================================
// End of file.
//===========================================================================
