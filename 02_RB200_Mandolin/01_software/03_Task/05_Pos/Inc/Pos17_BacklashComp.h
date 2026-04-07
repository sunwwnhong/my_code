/*
 * Pos17_BacklashComp.h
 *
 *  Created on: 2020Äê8ÔÂ10ÈÕ
 *      Author: zhuxc
 */
 #ifndef Pos17_BacklashComp_H
#define Pos17_BacklashComp_H
 
#define SVFSEL_BLSH_COMMON_PROC 0
 
#define SVFSEL_STANDARD_BACKLASH 1
 
  
 typedef	struct	{								     
		struct {								     
		LONG	CompPulse;							 
		LONG	Kfil;								 
		LONG	KfilTmp;							 
		LONG	MaxCompPulse;						 
		ULONG	MaxCompRef;							 
		} P;
 		struct {								     
		LONG	Filo;								 
		LONG	LastFilo;							 
		LONG	Cmppls;								 
		LONG	Cmpgrrem;							 
		LONG	Cmppos;								 
		LONG	remx;								 
		} V;                                        
} BLSHCMP;
 extern BLSHCMP BlshCmp;
  
  
  
#define		BLSHCOMP_UPLIM		500000				         
#define		FOR_BACKLASH		0x00				         
#define		REV_BACKLASH		0x01				         
 
extern void	BpxCompensateBacklash( LONG *dPosRef, LONG *dPcmd );
extern void	PcalBlshCompensateAmount( void );
extern void PcalBlshCompensateTime( void );
#if ( SVFSEL_BLSH_COMMON_PROC )
extern void	IprmcalMaxBlshCompPulse( void );
#endif
extern void	BpxInitBlshCompensate( void );
extern void	BpxInvaildBlshCompensate( void );
 #endif
