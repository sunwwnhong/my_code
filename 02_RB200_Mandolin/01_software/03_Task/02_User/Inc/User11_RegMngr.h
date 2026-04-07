/****************************************************************************************************/
/*																									*/
/*																									*/
/*		User11_RegMngr.h :                          											*/
/*																									*/
/*																									*/
/****************************************************************************************************/
#ifndef __User11_RegMngr_H__
#define __User11_RegMngr_H__

#include "main.h"
#include "UserGroble.h"

typedef	struct	{							/* 寄存器IF管理用变量									*/
		void	*Hmsg;						/* Message IF handle(写入权限管理＆操作应答用)			*/
} RIFMNGV;
/*--------------------------------------------------------------------------------------------------*/
typedef	struct	{							/* レジスタＩＦ管理用パラメータ							*/
	/*----------------------------------------------------------------------------------------------*/
		USHORT	FnFunTblEntNum;				/* 補助機能定義テーブル登録個数							*/
		USHORT	FunOpeRegDefTblEntNum;		/* 補助機能操作レジスタ定義テーブル登録個数				*/
		USHORT	FunOpeRegDefTblSrhIniW;		/* 補助機能操作レジスタ定義テーブル検索分割幅初期値		*/
} RIFMNGP;
/*--------------------------------------------------------------------------------------------------*/




extern RIFMNGV	RifMngV;					/* 寄存器IF管理用变量									*/
extern RIFMNGP	RifMngP;					/* 寄存器IF管理用参数									*/


extern void	RpxInitRegManager( void );
extern LONG	RpxGetOpeRegWriteHandle( void *Hmsg );
extern void	RpxFreeOpeRegWriteHandle( void *Hmsg );
extern LONG	RpxReadOpeRegister( LONG RegNo, LONG Number, USHORT *RdBuf, HMSGIF Hmsg );
extern LONG	RpxWriteOpeRegister( LONG RegNo, LONG Number, USHORT *WrBuf, HMSGIF Hmsg );
extern void	*RpxWriteTrcTdrvOpeRegEnd( void );
extern LONG	RpxReadEngRegister( LONG RegNo, LONG Number, USHORT *RdBuf, HMSGIF Hmsg );
extern LONG	RpxWriteEngRegister( LONG RegNo, LONG Number, USHORT *WrBuf, HMSGIF Hmsg );
extern void	RpxFreeOpeRegWriteHandleTrc( void *Hmsg );
#endif

