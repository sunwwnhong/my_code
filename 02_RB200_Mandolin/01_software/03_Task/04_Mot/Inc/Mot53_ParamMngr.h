/*
 * Mot53_ParamMange.h
 *
 *  Created on: 2017Äê5ÔÂ15ÈÕ
 *      Author: zhuxc
 */
 #ifndef Mot53_ParamMngr_H
#define Mot53_ParamMngr_H
 #include "Main.h"
#include "SvOption.h"
#include "User02_Paramdef.h"
 
#define	PCHK_NONE				0x00
#define	PCHK_ACCS_LVL			0x01
#define	PCHK_WORD_ORDER			0x02
#define PCHK_INHIBIT			0x04
#define	PCHK_RONLY				0x08
#define	PCHK_MTR_TYPE			0x10
#define	PCHK_AMP_TYPE			0x20
#define	PCHK_OPEDSP				0x40
#define	PCHK_ALL				0xFF
#define	PCHK_DEF				PCHK_MTR_TYPE | PCHK_WORD_ORDER
#define	PCHK_READ				PCHK_DEF | PCHK_ACCS_LVL
#define	PCHK_WRITE				PCHK_READ | PCHK_INHIBIT | PCHK_RONLY
 #define OPEDSP_SETUPPRM			0x0000
#define OPEDSP_ALLPRM			0x0001
  
 #define	PERR_NO					0x0001                               
#define	PERR_DFIT				0x0002
#define	PERR_SIZE				0x0003
#define	PERR_LEVEL				0x0004
#define	PERR_RONLY				0x0005
#define	PERR_MTR_TYPE			0x0006
#define	PERR_AMP_TYPE			0x0007
#define	PERR_CALC				0x0008
#define	PERR_RANGE				0x0009
#define	PERR_FOUND				0x000A
#define PERR_INH				0x000B
#define PERR_PRMCOPY			0x000C
#define PERR_WRITE_HANDLE		0x000D
#define	PERR_OPEDSP				0x000E
 #define	PRM_EEPROM_RAM_NO_DIFF	0x0020
#define	PRM_EEPROM_WRITE_WAIT	0x0021
#define	PRM_EEPROM_WRITE_FAIL	0x0022
  
  
  
  
#define ACCLVL_USER1			1			 
#define ACCLVL_USER2			2			 
#define ACCLVL_SYSTEM			3			 
  
 #define REG_ACCLVL_USER1		0			 
#define REG_ACCLVL_USER2		1			 
#define REG_ACCLVL_SYSTEM		2			 
  
  
typedef struct
{
	USHORT	inhibit;
	USHORT	level;
	USHORT	org_inhi;
	USHORT	OpeDspMode;
} ACCESS;
 typedef	struct {							 
	UCHAR	Type;								 
	UCHAR	WdNum;								 
	USHORT	Eaddr;								 
	ULONG	Wdata;								 
} PWQENT;
 #define	RpiSetAccsLvl( acc, lvl )		((acc)->level = lvl)
 
extern ACCESS Access;
 
typedef struct {
		void	*Hmsg;								 
         USHORT  APRMWrDiff;                          
} PRMMNGV;
extern PRMMNGV		PrmMngV;
 extern  LONG RpxGetPrmWriteHandle( void *Hmsg );
extern void RpxFreePrmWriteHandle( void *Hmsg );
extern USHORT	RpxPrmSearchIdxOp( USHORT SrchNo, USHORT BaseIndex);
extern ULONG RpxPrmRamDigitInc(USHORT Index, ULONG Data, USHORT Digit);
extern ULONG RpxPrmRamDigitDec(USHORT Index, ULONG Data, USHORT Digit);
extern ULONG RpiPrmDataDigitInc(ULONG Data, USHORT Digit, ULONG UpperLimit, UCHAR Base, UCHAR IsLong, UCHAR Sign);
extern ULONG RpiPrmDataDigitDec(ULONG Data, USHORT Digit, ULONG LowerLimit, UCHAR Base, UCHAR IsLong, UCHAR Sign);
extern USHORT	RpxPrmGetDecimals( PRMDEF *pPrmDef );
extern ULONG RpiPrmUpperLimit(CPRMDEF *PdefPtr);
extern ULONG RpiPrmLowerLimit(CPRMDEF *PdefPtr);
extern ULONG RpxPrmLowerLimitIdx(USHORT Index);
extern ULONG RpxPrmUpperLimitIdx(USHORT Index);
extern LONG RpxPrmReadIdx(USHORT Index, ULONG *ResData, UCHAR CheckType);
extern LONG RpxPrmWriteRamIdx(USHORT Index, ULONG Data, UCHAR CheckType, HMSGIF Hmsg);
extern LONG RpxPrmUpdateEepromIdx(USHORT Index);
extern LONG RpxReadPrmRegister(LONG RegNo, LONG Number, USHORT *RdBuf, HMSGIF Hmsg);
extern LONG RpxWritePrmRegister(LONG RegNo, LONG Number, USHORT *RdBuf, HMSGIF Hmsg);
extern LONG	RpiPrmWriteRamForFn(CPRMDEF *PdefPtr, ULONG Data, HMSGIF Hmsg);
extern LONG	RpiPrmUpdateNvmem(CPRMDEF *PdefPtr);
extern void	RpiAllPrmCalcMain( void );
extern LONG	RpiPrmReadNvmem(CPRMDEF *PdefPtr, ULONG *ResData);
extern LONG	RpiPrmRead(CPRMDEF *PdefPtr, ULONG *ResData);
extern void	RpiPrmInitUserParameter( void );
 #endif
