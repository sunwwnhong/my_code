/*
 * Mot32_JatOffLine.h
 *
 *  Created on: 2018Äê 08ÔÂ25ÈÕ
 *      Author: zhuxc
 */
 
#ifndef Mot32_JatOffLine_H
#define Mot32_JatOffLine_H
 extern void	BpxJatOfflineCalc( void );
extern void	CpxJatOfflineCalc( void );
extern void	CpiEndJatOffLine( HMSGIF Hmsg );
extern SHORT CpiInitJatOffLine( SHORT , LONG , HMSGIF);
extern SHORT CpiGetJatErrStatus( void );             
extern SHORT GetJatStatus( void );                   
extern SHORT CpiGetJatExeErrStatus( void );          
extern SHORT CpiGetJatCompStatus( void );            
extern void	CpiSetEstimateJrat( HMSGIF );
#endif
