/*
 * Seq00_Main.h
 *
 *  Created on: 2018Äê5ÔÂ22ÈÕ
 *      Author: zhuxc
 */
 #ifndef Seq00_Main_H
#define Seq00_Main_H
 #include "Seq01_MakeSeqSignal.h"
#include "Seq02_MechaBrakeSequence.h"
#include "Seq03_OverTravelSequence.h"
 #include "Seq05_DynamicBrakeSequence.h"
 #include "Seq08_ZeroClamp.h"
#include "Seq09_StopMode.h"
#include "Seq10_ControlMode.h"
 
  
  
  
  
 typedef	struct
{
		USHORT	Spare1;						 
} SVSEQP;
  
 typedef	struct
{
		struct {							 
		UINT	AlmZeroStop		:1;			 
		UINT	AlmZstopFinish	:1;			 
 		UINT	OtZeroStop		:1;			 
		UINT	OtZeroClamp		:1;			 
 		UINT	Brake			:1;			 
		UINT	BkZeroStop		:1;			 
 		UINT	ZcReqSignal		:1;			 
		UINT	ZcZeroStop		:1;			 
		UINT	ZcZeroClamp		:1;			 
 		} f;
 		UCHAR	AlmStopMode;				  
		UCHAR	OperateAlmStopMode;			  
		UCHAR	Dummy[2];					  
 		USHORT	OtStep;						 
		USHORT	OtWait;						 
		USHORT	OtOnCnt;					 
		USHORT	OtOffCnt;					 
		USHORT	OtDbopReq;					 
#if ( CCSW_NETID != NETID_NONE )
		USHORT	CtrlMode2;					  
#endif
 		USHORT	BkStep;						 
		USHORT	BkWait;						 
 		USHORT	ZcStep;						 
		USHORT	ZcWait;						 
 		USHORT	DbStep;						 
		USHORT	DbWait;						 
  
 	 
		USHORT	OtWarngWaitCnt;				 
 		UCHAR	AmStep;						  
		UCHAR	AmLtSig;					  
 } SVSEQV;
extern SVSEQV SvSeqV;
 
extern void CpxServoSequence( void );
 #endif
