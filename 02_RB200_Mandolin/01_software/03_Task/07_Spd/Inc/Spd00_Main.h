/*
 * Spd00_Main.h
 *
 *  Created on: 2018Äê5ÔÂ2ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd00_Main_H
#define Spd00_Main_H
 #include "Main.h"
#include "Spd01_SpdCtrl.h"
#include "Spd02_SpdCmd.h"
#include "Spd03_SoftStart.h"
#include "Spd04_ZeroPosition.h"
#include "Spd05_SpdPhaseComp.h"
#include "Spd06_SpdPICoeff.h"
#include "Spd08_SpdStatus.h"
#include "Spd09_SpdPIMode.h"
#include "Spd10_VibrSuppress.h"
#include "Spd11_ResVibCtrl.h"
#include "Spd12_FricTrqCmp.h"
#include "Spd13_DisturbObserver.h"
#include "Spd14_SpdObserver.h"
#include "Spd15_Estimate.h"
#include "Spd16_LoadObserver.h"
 
  
 typedef	struct	{								 
		struct	{								 
		LONG	PI;								 
        LONG    SpdOffDec;                       
		LONG	KVrfFil;						 
		LONG	KVfbFil;						 
		LONG	KVintegFil;						 
        LONG    KdPffFil;
		LONG	SpdRefPhFil;					 
		LONG	SpdRefPhFilGn;					 
		LONG	SpdFFPhFil;						 
		LONG	SpdFFPhFilGn;					 
		} P;
 		struct {								 
		LONG	TrqRef;							 
        LONG    TrqFedFor;                       
		LONG	SpdFbFilo;						 
		LONG	PacOut;							 
		LONG	IacOut;							 
		LONG	Ivar64[2];						 
        LONG    SFSpdOld;                        
        LONG    FfFilo;                          
		LONG	SpdRefPhLpfo;					 
		LONG	SpdRefPhHpfo;					 
		LONG	SpdRefPhHpfTmp;					 
		LONG	SpdFFPhLpfo;					 
		LONG	SpdFFPhHpfo;					 
		LONG	SpdFFPhHpfTmp;					 
		UCHAR	SpdRefFilClrCmd;				 
		UCHAR	SpdFFFilClrCmd;					 
		} V;
} SPDCTRL;
 
  
 typedef	struct	{			                         
		struct	{			                         
          LONG	Kp;									 
		LONG	SpdLimit;							 
		} P;
 		struct {								     
		LONG	PosError;							 
		} V;
} ZXCTRL;
 extern SPDCTRL SpdCtrl;
extern ZXCTRL ZxCtrl;
 #endif
