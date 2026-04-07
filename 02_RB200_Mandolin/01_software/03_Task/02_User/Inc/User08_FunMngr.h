/****************************************************************************************************/
/*																									*/
/*																									*/
/*		User05_FunMngr.h : ÑaÖú™CÄÜ¶¨Áx¥Ø¥Ã¥À¥Õ¥¡¥¤¥ë												*/
/*																									*/
/*																									*/
/****************************************************************************************************/


#include "UserGroble.h"
#include "User02_Paramdef.h"
#ifndef __User08_FunMngr_H__
#define __User08_FunMngr_H__




extern void	RpxFunExecute(void);
extern USHORT	RpxFunSearchIdxOp(USHORT SrchNo, USHORT BaseIndex);
extern SHORT	RpxFunExeBeginPnl(USHORT Index);
extern void RpxFunExePnl(OPKEYFLG FPnlKeyMk, OPKEYFLG FPnlKeyBrk, OPKEYFLG FPnlKeyLvl,
                  USHORT Index,       LEDDSP *FPnlLed,     BLINKFLG *FOpBlnkKickFlg);
extern void	RpiFunLedSetStr(UCHAR *str_ptr, FUNEXE *pfexe, USHORT startdgt, USHORT length);
extern void	RpiFunLedSetValHex(USHORT data, FUNEXE *pfexe, USHORT startdgt, USHORT digit);
extern void	RpiFunLedSetFlag(USHORT data, FUNEXE *pfexe, USHORT startdgt, USHORT digit);
extern SHORT	RpxFunEndChkPnl(USHORT Index);
extern void	RpxFunFinishPnl(USHORT Index);
extern LONG RpiFunPrmWriteInhibitChk(void);
extern void	RpiFunLedSetBlnk(FUNEXE *pfexe, UCHAR blnkptn);
extern void	RpiFunLedSetValDec(USHORT, FUNEXE *pfexe, USHORT,USHORT, USHORT, SHORT);
extern void	RpiFunLedDispMonDecLong(ULONG ldata, FUNEXE *pfexe, USHORT dsp_pos,SHORT decimals, USHORT sign);
extern void	RpiFunLedDispMonDecWord(USHORT data, FUNEXE *pfexe, SHORT decimals, USHORT sign);
extern void	RpxFunFinishReg( USHORT FinishAll, USHORT FinishExeIdx, HMSGIF Hmsg );
extern LONG	RpxFunCheckTraceParaRun( HMSGIF Hmsg );
extern LONG	RpxFunExeBeginReg( USHORT RegData, USHORT ExeIdx, USHORT ChkTrcMode, HMSGIF Hmsg );
extern LONG	RpxFunExeReg( USHORT RegData, USHORT ExeIdx, HMSGIF Hmsg );
extern LONG	RpiFunPrmNvmemUpdate(CPRMDEF *PdefPtr);
extern void	RpiFunLedSetStatusBits(FUNEXE *pfexe);
extern void    RpiFunDataWriteDisableSet(UCHAR Type, UCHAR flg, FUNEXE *pfexe);
extern void RpiFunDoLedSetStr(USHORT DispData,FUNEXE *pfexe,UCHAR DisFlag);
#endif

