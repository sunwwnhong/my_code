/*
 * Fn203_OnePrmTuning.h
 *
 *  Created on: 2018Äê8ÔÂ23ÈÕ
 *      Author: zhuxc
 */
 #ifndef Fn203_OnePrmTuning_H
#define Fn203_OnePrmTuning_H
 
extern void	FunOneParamTuningInit( void );
extern LONG FunOneParamTuningBegin(FUNEXE *);
extern LONG FunOneParamTuningExe(FUNEXE *);
extern void FunOneParamTuningEnd(FUNEXE *, UCHAR);
 extern void	RpiRegSetOnePrmTuningLevel( USHORT );
extern void	RpiRegSetOnePrmTuningFfLevel( USHORT );
 #endif
 
