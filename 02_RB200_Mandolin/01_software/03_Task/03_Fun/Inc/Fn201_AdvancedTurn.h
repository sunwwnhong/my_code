/*
 * Fn201_AdvancedTurn.h
 *
 *  Created on: 2017Äê6ÔÂ28ÈÕ
 *      Author: zhuxc
 */
 #ifndef Fn201_AdvancedTurn_H
#define Fn201_AdvancedTurn_H
 #define		TUNE_ANOTCH_MINKV		600
 extern void	FunRefInAdvAutoTuningEnd( FUNEXE *pfexe, UCHAR method );
extern LONG	FunRefInAdvAutoTuningBegin( FUNEXE *pfexe );
extern void	FunRefInAdvAutoTuningInit( void );
extern void	FunAdvAutoTuningInit( void );
extern LONG	FunAdvAutoTuningBegin( FUNEXE *pfexe );
extern void	FunAdvAutoTuningEnd( FUNEXE *pfexe, UCHAR method );
extern LONG	FunAdvAutoTuningExe( FUNEXE *pfexe );
extern void PcalOverShootErrDetLvl( void );
extern void	CpxAdvancedAutoTuning( LONG , ULONG );
#endif
