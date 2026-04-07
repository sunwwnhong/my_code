/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
*
* File Name 		 : User10_MonMngr.h
*
* Version			 : V0.1
* Date				 : 2024
***********************************************************************************************/
#ifndef __User10_MonMngr_H__
#define __User10_MonMngr_H__

#include "Main.h"

/*--------------------------------------------------------------------------------------------------*/
/*		Servo Monitor Check Flag																	*/
/*--------------------------------------------------------------------------------------------------*/
#define	MCHK_NONE		0x00
#define	MCHK_ACCS_LVL	0x01
#define	MCHK_MTR_TYPE	0x02																		
#define	MCHK_DEF		MCHK_MTR_TYPE																
/*--------------------------------------------------------------------------------------------------*/
#define	MERR_NO			0x0001
#define	MERR_LEVEL		0x0004
#define	MERR_CHKSPUSE	0x0005

extern  const USHORT UnMonTblEntNum;
extern  const USHORT UnRegTblEntNum;
#define UNMONTBL_ENTNUM		UnMonTblEntNum
#define UNREGTBL_ENTNUM		UnRegTblEntNum

/*** 根据功能码编号来进行相关的索引查找 ***/
extern  USHORT	RpxMonSearchIdxOp( USHORT	SrchNo, USHORT	BaseIndex );
extern void	RpxInitMonManager( void );  // 监控功能码初始化处理
/*** 监视器数据读取处理(定义指定) ***/
LONG	RpiMonRead( MONDEF *UnDefPtr, ULONG *ResData, UCHAR	CheckType );
void	RpxMonClearVarIdx( USHORT	Index );    // 根据索引号，复位清零索引号指定的监视器变量
/*** 监视器寄存器读取函数 ***/
LONG	RpxReadMonRegister( LONG RegNo, LONG Number, USHORT	*RdBuf,	HMSGIF	Hmsg );
LONG	RpiMonSearch(USHORT	SrchNo, USHORT BaseIndex, USHORT *FindIndex, UCHAR CheckType);


#endif
