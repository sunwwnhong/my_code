/*
 * Spd12_FricTrqCmp.h
 *
 *  Created on: 2018Äê8ÔÂ23ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd12_FricTrqCmp_H
#define Spd12_FricTrqCmp_H
 typedef struct
{
    KSGAIN	FricCoefPos;
	KSGAIN	FricCoefNeg;
    LONG	FricSpdMax;
    LONG	FricCmpTrq;
} FRICTRQCMP;
 extern FRICTRQCMP FricTrqCmp;
 
 #endif
