/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
*
* File Name          : Seq01_MakeSeqSignal.h
*
* Version            : V0.1
* Date               : 2024
***********************************************************************************************/

 #ifndef Seq01_MakeSeqSignal_H
#define Seq01_MakeSeqSignal_H
 extern void	LpxMakeSequenceSignal( void );
extern void LpxCheckSvonCmdInvalid( void );
extern LONG CpiGetRoundServoControl( LONG NormalOpeDrv );
extern void CpiFreeRoundServoControl( void );
 #endif
