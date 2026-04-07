/*
 * Spd01_SpdCtrl.h
 *
 *  Created on: 2018Äê5ÔÂ14ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd01_SpdCtrl_H
#define Spd01_SpdCtrl_H
 extern LONG BaseSpeedControl( LONG  SpdRef, LONG  SpdFbk, LONG  SpdFFC, LONG  SpdFBC, LONG  dPosFbk );
                                          
 										 
 										 
 extern LONG BaseLinDecStopSpdRef( LONG SpdRefo );
extern void PcalBaseSoftOffDec( void );
 #endif
