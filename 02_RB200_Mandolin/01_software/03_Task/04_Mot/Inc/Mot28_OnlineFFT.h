/*
 * Mot28_OnlineFFT.h
 *
 *  Created on: 2018Äê 08ÔÂ13ÈÕ
 *      Author: zhuxc
 */
 #include "Main.h"   
 #ifndef Mot28_OnlineFFT_H
#define Mot28_OnlineFFT_H
  
  
typedef	struct	{
		USHORT	Freq;					 
		USHORT	Amp;					 
} FRQANAV;
 extern SHORT RpxOnFftAnalyze( SHORT *tracedata, LONG Sno, LONG Fmax_calc, LONG Fmin_calc, FRQANAV *ResSet, FRQANAV *AntSet );
 #endif
 
 
