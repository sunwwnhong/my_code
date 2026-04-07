/*
 * Spd03_SoftStart.h
 *
 *  Created on: 2018Äê5ÔÂ14ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd03_SoftStart_H
#define Spd03_SoftStart_H
 extern LONG BaseSoftStartSpdRef( LONG	SpdRef, LONG  SpdRefx );
extern void PcalBaseSoftStartAcc( void );
extern void PcalBaseSoftStartDec( void );
extern void PcalBaseSoftStartTs( void );
extern void SoftStart_Init( void );
extern void SoftSpd_Update( LONG Spd );
 #endif
