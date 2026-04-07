/*
 * Pos01_PosCmdMange.h
 *
 *  Created on: 2018Äê5ÔÂ21ÈÕ
 *      Author: zhuxc
 */
 #ifndef Pos01_PosCmdMange_H
#define Pos01_PosCmdMange_H
 extern void	BpxSvcPosCommandManager( void );
extern void PosRefRenewal( void );
extern LONG KpiPositionLevelCal( LONG	Position );
extern void	LpxSvPositionManager( void );
extern LONG SvonSpeedLimit( LONG  SpdRefi );
extern void	BpxInitSvcPositionManager( void );
extern void	BpiEnableEgear( void );
extern void	BpiDisableEgear( void );
extern void	MlibPerrcala( LONG pcmda, LONG pfbka, EGEAR *egear, PERRA *perra );
 #endif
