/*
 * Fn204_ATypeVibTuning.h
 *
 *  Created on: 2018Äê8ÔÂ10ÈÕ
 *      Author: zhuxc
 */
 #ifndef Fn204_ATypeVibTuning_H
#define Fn204_ATypeVibTuning_H
 extern LONG FunAtypeVibTuningBegin( FUNEXE * );
extern LONG FunAtypeVibTuningExe( FUNEXE * );
extern void FunAtypeVibTuningEnd( FUNEXE *, UCHAR );
extern void	FunAtypeVibTuningInit( void );
 extern void RpiRegSetAtypeVibTuningFrequency( USHORT Frq );
extern void	RpiRegSetAtypeVibTuningGain( USHORT Gain );
 
#endif
