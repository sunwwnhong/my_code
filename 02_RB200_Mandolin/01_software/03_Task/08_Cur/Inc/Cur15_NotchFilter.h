/*
 * Cur15_NotchFilter.h
 *
 *  Created on: 2018Äê07ÔÂ17ÈÕ
 *      Author: zhuxc
 */
 #ifndef Cur15_NotchFilter_H
#define Cur15_NotchFilter_H
 typedef struct
{
 	UCHAR Notch1EnFlag;                                  
    UCHAR Notch2EnFlag;                                  
    UCHAR Notch3EnFlag;                                  
    UCHAR Notch4EnFlag;                                  
     SHORT Notch1X[ 3 ];
    SHORT Notch1Y[ 3 ];
    SHORT Notch2X[ 3 ];
    SHORT Notch2Y[ 3 ];
    SHORT Notch3X[ 3 ];
    SHORT Notch3Y[ 3 ];
    SHORT Notch4X[ 3 ];
    SHORT Notch4Y[ 3 ];
 }NOTCH_P;   
extern NOTCH_P Notch_P;
 extern SHORT NotCh1Coeff[4];
extern SHORT NotCh2Coeff[4];
extern SHORT NotCh3Coeff[4];
extern SHORT NotCh4Coeff[4];
 extern void KpiPcalMicroNotchFilter2(LONG hz,LONG qx,LONG dx,LONG ts,SHORT *Buff);
extern SHORT NotchDeal( SHORT );
extern void IINotchFilter1_NCF( void );
extern void IINotchFilter2_NCF( void );
extern void IINotchFilter1_DPH( void );
extern void IINotchFilter2_DPH( void );
#endif
