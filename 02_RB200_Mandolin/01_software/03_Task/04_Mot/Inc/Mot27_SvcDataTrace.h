/*
 * Mot27_SvcDataTrace.h
 *
 *  Created on: 2018Äê 08ÔÂ13ÈÕ
 *      Author: zhuxc
 */
 #ifndef Mot27_SvcDataTrace_H
#define Mot27_SvcDataTrace_H
  
  
  
#define	SVCTRC_BUFMAX		200			 
  
 typedef	struct	{						 
 		UCHAR	TrcCmd;					 
		UCHAR	TrcInt;					 
		USHORT	TrcNum;					 
		LONG	*TrcVarA;				 
 		USHORT	TrcSamp;				 
		USHORT	TrcIndx;				 
		SHORT	TrcBufA[SVCTRC_BUFMAX];	 
		SHORT	TrcTrgLvl;				 
} SVCTRCV;
  
 #define SVCTRC_NOCMD		0x00		 
#define	SVCTRC_TRCEXE		0x10		 
#define	SVCTRC_TRCEND		0x1F		 
  
 extern	SVCTRCV	SvcTrcV;				 
  
 extern void	BpxSvcDtraceExecute( void );
 #endif
