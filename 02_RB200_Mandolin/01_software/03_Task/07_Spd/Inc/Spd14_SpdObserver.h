/*
 * Spd14_SpdObserver.h
 *
 *  Created on: 2018Äê9ÔÂ12ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd14_SpdObserver_H
#define Spd14_SpdObserver_H
 #define SPDOVS_PHASECOMP    1
 extern LONG ApxEhSpeedObserver( LONG , LONG );
extern LONG	ApxSpeedObserver( LONG , LONG );
extern void	LpxInitEhSpeedObserver( void );
extern void InitSpeedObserver( void );
extern void	IprmcalEhSpeedObserver( void );
extern void	PcalEhSpeedObserver( void );
 #endif
