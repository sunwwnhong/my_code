/*
 * Cur00_Main.h
 *
 *  Created on: 2018Äê1ÔÂ31ÈÕ
 *      Author: zhuxc
 */
 #ifndef Cur00_Main_H
#define Cur00_Main_H
 #include "Main.h"
  
  
#include "Cur00_Main.h"
#include "Cur01_TorqCtrl.h"
#include "Cur02_CurCmd.h"
#include "Cur03_CurSamp.h"
#include "Cur05_CurPID.h"
#include "Cur06_MotorDecoup.h"
#include "Cur09_MotorPhase.h"
#include "Cur10_TorqFilter.h"
#include "Cur11_RippleComp.h"
#include "Cur12_TorqRefOut.h"
#include "Cur13_OverTorq.h"
#include "Cur14_ZeroPhase.h"
#include "Cur15_NotchFilter.h"
#include "Cur16_TrqLimit.h"
#include "Cur17_OLMonitor.h"
#include "Cur18_WeakMagneticControl.h"
#include "Cur19_PhaseCompGainCnt.h"
#include "Cur21_VF.h"
#include "Cur22_FrictionComp.h"
 
#if( FPGAUse == 1 )
#define FPGA_CLKMHZ     80                            
#define FPGA_CLKns      125                           
#else
#define FPGA_CLKMHZ     200                           
#define FPGA_CLKns      50                           
#endif
 
 typedef struct
{
    SHORT PWM_Priod;                                     
    SHORT PWM_PriodMax;                                  
    SHORT PWM_PriodMin;                                  
    USHORT PWM_DeadTime;                                 
    ULONG EmfCompCoeff;                                  
    LONG  EmfCompLimit;                                  
     USHORT CurrentCoeff;                                 
 }CURRENTLOOPVAR;
extern CURRENTLOOPVAR CurrentLoopVar;
 
  
 typedef	struct	{								     
		struct	{								     
            LONG	OverTrqLoopGain[3];				 
            LONG	OverTrqIntegGain[3];			 
		} P;
 		struct {								     
            LONG	SpdLimit;						 
            LONG	OverTrqIntegBuf[2];
		} V;
             
} TRQCTRL;
extern TRQCTRL TrqCtrl;
 extern void CurrentLoopCoeff_Init( void );
extern LONG KpiMonCurrentCal( LONG  Current );
extern LONG KpiMonCurrentCal1( LONG  Current );
extern LONG KpiMonTorqueCal( LONG	Torque );
extern LONG PcalPwmFrequency(USHORT PWMF);
 #endif
