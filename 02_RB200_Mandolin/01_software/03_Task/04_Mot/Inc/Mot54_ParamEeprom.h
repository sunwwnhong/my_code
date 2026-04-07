/*
 * Mot54_ParamEeprom.h
 *
 *  Created on: 2017Äê7ÔÂ6ÈÕ
 *      Author: zhuxc
 */
 
#include "User02_Paramdef.h"
#ifndef Mot54_ParamEeprom_H
#define Mot54_ParamEeprom_H
 enum	EEPQUEID_DEF {                           
		EEPQUEID_TIMESTAMP		= 0,             
		EEPQUEID_ALARMOLINF		,                    
		EEPQUEID_ALARMTRACE		,                
		EEPQUEID_WRPRM_SCANC	,                
		EEPQUEID_WRPRM_ROUND	,                
		EEPQUEID_ALARMMON		,                
		EEPQUEID_OPTID			,                
		EEPQUEID_DEF_NUMBER		,                
};
 typedef	struct {								 
	UCHAR	Type;								 
	UCHAR	Spare;								 
	USHORT	WdNum;								 
	USHORT	Eaddr;								 
	USHORT	Xdata;								 
	USHORT *WdAdr;								 
} WRINFO;
 typedef	struct
{
	VUSHORT	ReqFlag;							 
	USHORT	Spare00;							 
 	UCHAR	Type;								 
	UCHAR	Spare;								 
	SHORT	WdNum;								 
	SHORT	WdCnt;								 
	USHORT	Eaddr;								 
	DWORDX	Wdata;								 
	USHORT	ChkSumx[2];							 
	WRINFO	WrtInfo[EEPQUEID_DEF_NUMBER];		 
} EEPWQUE;
 
  
  
 typedef	struct
{
	VUCHAR		QueId;							 
	VUCHAR		WrEepTmStampReq;				 
	VUCHAR		EepSemaphore;					 
	VUCHAR		WrEepStartOk;					 
	VUSHORT		PowerOffTime;					 
	VUSHORT		WrEepQueStep;					 
	VUSHORT		WrEepQueWait;					 
	VULONG		WrEepTmStamp;					 
#if ( EEPROM_COM_TYPE == EEPROM_COM_I2C )		 
	VUSHORT		I2CReadStep;					 
	VUSHORT		I2CWriteStep;					 
	VUSHORT		I2CData;						 
	VUSHORT		I2CSpare00;						 
#endif
} EEPMNG;
extern EEPMNG	EepMsg;
 
 extern EEPWQUE	EepromQueue; 
extern EEPINF	Eephdr;
void InitParameterFromEeprom( void );
void KpxScanWriteEepromQueue( void );
extern ULONG PanOperReadEepromPrm( CPRMDEF *prmdef );
extern LONG	KriAddEepromQueue( ULONG , void *prmdef, ULONG );
extern LONG	KriChkEepromQueue( ULONG );
extern LONG	KriReadEepromEngInfo( LONG , LONG , USHORT *ReadBuf, LONG *ErrNum );
extern LONG	KriWriteEepromEngInfo( LONG , LONG , USHORT *WriteBuf, LONG *ErrNum );
extern ULONG KriReadEepromPrm( CPRMDEF *prmdef );
extern USHORT KriReadEepromWord( USHORT );
extern LONG	GetEepromSemaphore( LONG );
extern void	FreeEepromSemaphore( void );
extern USHORT ReadEepromWord( ULONG );
extern void	WriteEepromWord( ULONG eaddr, USHORT wdata, LONG wait );
extern void	KpxResetEepromAlmTrc( void );
extern void     KpxResetEepromAlmMon(void);
extern void	LpxReadEepromData( USHORT EepAdr, USHORT* RdBufx, LONG RdNumx );
extern void TmStampSaveEn( void );
extern void	WriteEepromDisable( void );
extern void	WriteEepromEnable( void );

#endif
