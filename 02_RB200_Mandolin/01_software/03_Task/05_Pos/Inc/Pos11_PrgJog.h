/*
 * Pos11_PrgJog.h
 *
 *  Created on: 2018Äê08ÔÂ14ÈÕ
 *      Author: zhuxc
 */
 #include "Main.h"
 #ifndef Pos11_PrgJog_H
#define Pos11_PrgJog_H
 
  
 #define	PJOG_INIT	0x00				 
#define	PJOG_ABORT	0x10				 
#define	PJOG_START	0x01				 
#define	PJOG_AFTER	0x11				 
#define	PJOG_END	0x02				 
#define	PJOG_ERROR	0x03				 
  
  
#define	PJOGCMD_NONE	0x00			 
#define	PJOGCMD_INIT	0x01			 
#define	PJOGCMD_ABORT	0x02			 
#define	PJOGCMD_START	0x03			 
  
  
  
  
 typedef	struct
{
		struct							 
		{
			LONG	Distance;			 
			LONG	MaxSpd;				 
			LONG	AccTime;			 
            LONG	DecTime;			 
			USHORT	WaitTime;			 
			USHORT	MTimes;				 
			CHAR	Pattern;			 
			CHAR	RevDir;				 
			CHAR	PrmUnMatch;			 
			CHAR	PrmUnMatch2;		 
		} Cnst;
 		struct							 
		{
			LONG	AbsPosCmd;			 
			ULONG	TimeWork;			 
			USHORT	DispTime;			 
			USHORT	MCntr;				 
			USHORT	SeqPtr;				 
 			UCHAR	RoutCmd;			 
			UCHAR	CoutCmd;			 
			UCHAR	State;				 
		} Var;
} PJOGV;
  
 extern	PJOGV	PJogV;					 
extern	PCMKPV	PJogPcmk;				 
 extern void CpxPrgJogPosSequence( void );	     
extern void	PrgJogReset( void );         
 extern void PcalPjogSw( void );
extern void PcalPjogDistance( void );
extern void PcalPjogRotspd( void );
extern void PcalPjogAcctime( void );
extern void PcalPjogWaitTime( void );
extern void PcalPjogNum( void );
extern void	IprmcalPrgJog( void );
#endif
