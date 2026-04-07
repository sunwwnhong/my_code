/*
 * MathLib02_LPF1.h
 *
 *  Created on: 2018Äê4ÔÂ17ÈÕ
 *      Author: zhuxc
 */
 #ifndef MathLib02_LPF1_H
#define MathLib02_LPF1_H
 #include "Main.h"
 extern LONG	MlibLpfilter1( LONG u, LONG k, LONG x );
 extern float FlibLpfilter1( float u, float k, float x );
extern float FlibHpfilter1( float u, float k, float *z );
 #endif
