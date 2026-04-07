/*
 * Cur04_MotorDecoup.h
 *
 *  Created on: 2018Äê1ÔÂ31ÈÕ
 *      Author: zhuxc
 */
 #ifndef Cur04_MotorDecoup_H
#define Cur04_MotorDecoup_H
    
extern LONG	PcalDqRxComp( KSGAIN Rx );
extern LONG	PcalDqLxComp( KSGAIN Lx );
extern LONG	PcalDqEmfComp( KSGAIN Emf );
 extern float FPcalDqRxComp( float );
extern float FPcalDqLxComp( float );
extern float FPcalDqEmfComp( float );
 
#endif
