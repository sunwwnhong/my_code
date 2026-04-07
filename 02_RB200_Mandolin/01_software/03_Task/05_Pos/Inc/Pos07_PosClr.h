/*
 * Pos07_PosClr.h
 *
 *  Created on: 2018Äê08ÔÂ06ÈÕ
 *      Author: zhuxc
 */
 #ifndef Pos07_PosClr_H
#define Pos07_PosClr_H
 typedef	struct	{								 
	struct {
		UINT	calcFlg			:1;				 
		UINT	coin_signal_d	:1;				 
	} f ;
	LONG	cmsub_in_d;							 
	USHORT	cnt;								 
	USHORT	cnt_buf;							 
	USHORT	OutCnt;								 
	USHORT	srare ;								 
} SETTLINGTIME;
 typedef	struct									 
{
		UCHAR	SettlingStart;					 
		CHAR	OverErrDir;						 
		UCHAR	CoinLatch;						 
		UCHAR	spare0;							 
		ULONG	SettlingTimer;					 
		LONG	OverShoot;						 
		LONG	DelayAlmToCoin;					 
		SETTLINGTIME	settlingtime;			 
        USHORT  CLRStatus;                       
} BIOXV;
 extern BIOXV BioxV;								 
extern  void PosClrDeal( void );
extern void BpxPerClrSignalProcedure( void );
extern void	BpxEdgeClrSvcPositionManager( void );
#endif
