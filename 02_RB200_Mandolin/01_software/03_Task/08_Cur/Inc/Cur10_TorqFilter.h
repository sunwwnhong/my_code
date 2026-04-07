/*
 * Cur10_TorqFilter.h
 *
 *  Created on: 2018Äê3ÔÂ30ÈÕ
 *      Author: zhuxc
 */
 #ifndef Cur10_TorqFilter_H
#define Cur10_TorqFilter_H
  
  
  
 typedef	struct	{								 
 		struct {								 
		LONG	Klpf;							 
		LONG	Ktrflpf;						 
		} A;
 		struct {								 
		LONG	Klpf2[4];						 
		LONG	Ktrflpf;						 
		LONG	Klpf3;							 
		} P;
 		struct {								 
		LONG	FilOut;							 
		LONG	FilOut3;						 
		LONG	LpFil2[4];						 
		UCHAR	TrqFilClrCmd;					 
		UCHAR	TrqFilDisable;					 
		UCHAR	TrqInputPos;					 
		} V;
} TRQFIL;
extern TRQFIL TrqFil;
 
extern void PcalBaseTrqLpassFilter2( void );
extern void	PcalBaseTrqLpassFilter3( USHORT Trqfil );
extern LONG	BaseTorqueFilter( LONG TrqRefi,	LONG TrqFBC, LONG TrqFFC );
extern void BpiEnableCPUTorqueFilter( void );
extern void BpiDisableCPUTorqueFilter( void );
extern void BpiSetTrqInputPos( LONG  TrqInputPos );
 #endif
