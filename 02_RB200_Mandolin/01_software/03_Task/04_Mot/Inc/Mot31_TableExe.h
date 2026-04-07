/*
 * Mot31_TableExe.h
 *
 *  Created on: 2018Äê 08ÔÂ22ÈÕ
 *      Author: zhuxc
 */
 #ifndef Mot31_TableExe_H
#define Mot31_TableExe_H
  
  
typedef	struct	{						 
		UCHAR	TblPrmOk;				 
		UCHAR	TblMode;				 
		USHORT	CtrlMode;				 
 		UCHAR	TrqInputPos;			  
		UCHAR	TuneLessDisable;		  
		UCHAR	EGearDisable;			  
		UCHAR	PcmdFilDisable;			  
 		LONG	MotPulse;				 
		LONG	MtnLimit;				 
 		UCHAR	RefType;				 
		UCHAR	RefIpSft;				 
		USHORT	RefIpNum;				 
 		LONG	KoutDir;				 
		LONG   *RefOutPx;				 
} TBLEXEP;
#define	TBLREFTYPE_NOTPOS	0x00
#define	TBLREFTYPE_POSIP1	0x01
#define	TBLREFTYPE_POSIP2	0x02
#define	TBLREFTYPE_POSIP3	0x03
#define	TBLTRQIN_NONE			0x00
#define	TBLTRQIN_BEF_FIL		0x01
#define	TBLTRQIN_BEF_NTCHFIL	0x02
#define	TBLTRQIN_AFT_FIL		0x03
#define	TBLFUNCBIT_TUNELESS		0x0100
#define	TBLFUNCBIT_EGEAR		0x0200
#define	TBLFUNCBIT_PCMDFIL		0x0400
extern TBLEXEP	TblExeP;
 
  
  
typedef union	{						 
		struct	{						 
		UCHAR	zm;						 
		UCHAR	zmchg;					 
		UCHAR	zmlast;					 
		UCHAR	spare0;					 
		} b;
 		ULONG	dw;						 
} TBLZMD;
  
 typedef	struct	{						 
 		UCHAR	TblCmd;					 
		UCHAR	TblStep;                 
		USHORT	TblSamp;				 
		USHORT	TblIndx;				 
 		USHORT	MregCsw;				 
 		USHORT	ErrState;				 
		TBLZMD	TblZmd;					 
 	 
		LONG	MotMtn;					 
		LONG	MotPos;					 
 		LONG	TrqRef;					 
		LONG	SpdRef;					 
		LONG	dPosRef;				 
 	 
		LONG	InPosRef;				 
		LONG	IxPosRef;				 
		LONG	IxPosRem;				 
		LONG	WkPosRem;				 
} TBLEXEV;
 #define	TBLCMD_NOCMD		0x00
#define	TBLCMD_TABLESTART	0x01
#define	TBLCMD_TABLEDRIVE	0x02
#define	TBLCMD_TBLDRV_END	0x03
#define	TBLCMD_TBLDRV_ERR	0x0E
#define	TBLCMD_DRV_FOR		 1
#define	TBLCMD_DRV_REV		-1
#define	TBLCMD_STS_INIT		  0
#define	TBLCMD_STS_RUN		  1
#define	TBLCMD_STS_FINISH	  2
#define	TBLCMD_STS_POSLMT	100
#define	TBLCMD_STS_TRQLMT	101
#define	TBLCMD_STS_BB		102
#define	TBLCMD_STS_OT		103
#define	TBLCMD_STS_POWEROFF	104
#define	TBLCMD_STS_ALARM	105
#define	TBLCMD_STS_HWBB		106
 extern TBLEXEV TblExeV;
    
 extern void	*RpiPcalTableDriveParameter( void );
extern void	BpxTableDriveExecute( void );
extern LONG	RpiExecuteTableDrive( LONG TblDir );
 #endif
