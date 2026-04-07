/*
 * Fn205_MFCVibTuning.h
 *
 *  Created on: 2018Äê8ÔÂ31ÈÕ
 *      Author: zhuxc
 */
 #ifndef Fn205_MFCVibTuning_H
#define Fn205_MFCVibTuning_H
 #define VIBSUPPRESS_FIL2 1                                   
 extern void FunVibMfcTuningInit( void );
extern LONG FunVibMfcTuningBegin( FUNEXE *pfexe );
extern void FunVibMfcTuningEnd( FUNEXE *pfexe, UCHAR method );
extern LONG FunVibMfcTuningExe( FUNEXE *pfexe );
extern void RpiRegSetVibMfcTuningFrequency( USHORT Frq );
extern void	RpiRegSetMdlVibFreq2( USHORT Frq2 );
extern void	RpiRegSetMdlVibFil2( USHORT Fil );
 #endif
