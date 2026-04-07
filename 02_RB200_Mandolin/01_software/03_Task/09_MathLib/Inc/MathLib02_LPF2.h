/*
 * MathLib02_LPF2.h
 *
 *  Created on: 2018Äê4ÔÂ17ÈÕ
 *      Author: zhuxc
 */
 #ifndef MathLib02_LPF2_H
#define MathLib02_LPF2_H
 #include "Main.h"
 extern LONG MlibLowPassfilter2( LONG  u, LONG	k[ 4 ], LONG  z[ 4 ] );
extern LONG PcalLowfilter2( LONG  hz, LONG  qx, LONG  ts, LONG  kn[ 4 ] );
 
#endif
