/*
 * Mot55_ErrorDeal.h
 *
 *  Created on: 2017Äê7ÔÂ10ÈÕ
 *      Author: zhuxc
 */
#include "Main.h"
#include "Svoption.h"
#ifndef Mot55_ErrorDeal_H
#define Mot55_ErrorDeal_H
    
void    KpiSetAlarm( ULONG id );                 
void    KpiSetWarning( ULONG id );               
void	KpiClearWarning( ULONG id );             
    
#define KPX_ALMTBLMAX 10                         
#define	KPX_ALMTRCMAX 10                      
  
 #define ALMDEF_ATTR_WARNING		0x01			 
#define ALMDEF_ATTR_NOEEPROM	0x02			 
#define ALMDEF_ATTR_COMALARM	0x04			 
#define ALMDEF_ATTR_NOTRESET	0x08			 
#define ALMDEF_OLINFO_RGOL		0x02
  
#define KPI_ALARMCHK( id )		( (Alm.AlmSet[id>>5] & (ULONG)(1UL<<((id)&0x1F))) != 0 )
#define KPI_ALARMMSKCHK( id )	( (Alm.AlmSetMsk[id>>5] & (ULONG)(1UL<<((id)&0x1F))) != 0 )
#define KPI_ALARMSETCHK( id )	(  KPI_ALARMCHK(id) || KPI_ALARMMSKCHK(id) )
#define KPI_ALARMMSK( id )		if( !(KPI_ALARMMSKCHK(id)) ){ KpiAlarmMask(id);}
#define KPI_ALARMSET( id )		if( !(KPI_ALARMSETCHK(id)) ){ KpiSetAlarm(id);}
  
#define KPI_WARNINGCHK( id )	( (Alm.WrnSet[(id)>>5] & (ULONG)(1UL<<((id)&0x1F))) != 0 )
#define KPI_WARNINGSTSCHK( id )	( (Alm.WrnSts[(id)>>5] & (ULONG)(1UL<<((id)&0x1F))) != 0 )
#define KPI_WARNINGMSKCHK( id )	( (Alm.WrnSetMsk[(id)>>5] & (ULONG)(1UL<<((id)&0x1F))) != 0 )
#define KPI_WARNINGSETCHK( id )	(  KPI_WARNINGMSKCHK(id) )
#define KPI_WARNINGMSK( id )	if( !(KPI_WARNINGMSKCHK(id)) ){ KpiWarningMask(id);}
#define KPI_WARNINGSET( id )	if( !(KPI_WARNINGSETCHK(id)) ){ KpiSetWarning(id);}
#define KPI_WARNINGCLR( id )	if(  (KPI_WARNINGSTSCHK(id)) ){ KpiClearWarning(id);}
  
typedef struct	{
		UCHAR	OnFlag;
		UCHAR	Spare;
		USHORT	AlmCode;
		ULONG	TmStamp;
} ALMINF;
  
 typedef struct	{
	UCHAR  OnFlag;								 
	UCHAR  Spare[ 3 ];							 
	ALMDEF AlmDef;							     
	ULONG  TmStamp;  						 
} ALMTRC;
 typedef union
{
		USHORT	w;
		struct
		{
		    USHORT Idx :8;
		    USHORT Cnt :8;
		} b;
} ATRCHD;
 typedef struct	{
		USHORT	TrcAddCnt;
		USHORT	EepWrtCnt;
} ATRCNT;
 typedef	struct	{
		UCHAR	ErrFlag;
		UCHAR	ErrCount;
		USHORT	ErrPrmNo;
} PRMERR;
  
 typedef  struct
{
	ATRCHD TrcHdr;								 
	USHORT AlmCode;  						     
	ULONG  TmStamp;  						     
	USHORT OLInfo;								 
	USHORT OLFlag;								 
 } AEEPBF;
#define ALM_BITTBL_NUM 5
#define WRN_BITTBL_NUM 3
 typedef	struct	{
		UCHAR	AlmResetFlg;
		UCHAR	Spare00;
		USHORT	ResetAlmId;
} APPL;
typedef	struct	{
    UCHAR	AlmCnt;
    UCHAR	WrnCnt;
    UCHAR	AlmEepRst;
    UCHAR	AlmRstLast;
 	ALMTBL	AlmTbl[ KPX_ALMTBLMAX ];			 
  
    ALMTRC	AlmTrc[ KPX_ALMTBLMAX ];			 
     ALMTRC *AlmTrcSp;							 
 	AEEPBF	AlmEepBuf;							 
     ULONG	AlmSetx[ ALM_BITTBL_NUM ];           
     ULONG	AlmRstMsk[ ALM_BITTBL_NUM ];		 
                                                  
     ULONG	WrnSetx[ WRN_BITTBL_NUM ];			 
     ULONG	WrnRstMsk[ WRN_BITTBL_NUM ];		 
                                                  
    ULONG	AmpWrnChk[ WRN_BITTBL_NUM ];		 
     ULONG	ComWrnChk[ WRN_BITTBL_NUM ];		 
     ATRCHD	AlmTrcHdr;                           
    ATRCNT	AlmTrcCnt;                           
} KALM;
  
 typedef  struct
{
	struct
	{											 
		UCHAR AlmReady;  					     
 		UCHAR AlmFlag;							 
		UCHAR WrnFlag;							 
		UCHAR AmpAlarm;  					     
		UCHAR AmpWarning;						 
		UCHAR ComWarning;						 
		UCHAR MencDataNG;						 
		UCHAR NetAlarm;  					     
		UCHAR NetWarning;						 
		UCHAR PosDataNG;						 
		UCHAR ErrResetFlg;						 
	}	  f;
 	UCHAR		StopMode;						 
  
	USHORT		AlmCode;						 
	USHORT		AlmOLInfo;						 
 	USHORT		OpWrnCode;						 
	USHORT		OpWrnTimer;  				     
	ULONG		AlmWrnCode;  				     
 	PRMERR		PrmErrInfo;  				     
  
	ULONG		AlmSet[ ALM_BITTBL_NUM ];		 
 												 
	ULONG		AlmSetMsk[ ALM_BITTBL_NUM ];	 
  
	ULONG		WrnSts[ WRN_BITTBL_NUM ];		 
 	ULONG		WrnSet[ WRN_BITTBL_NUM ];		 
	ULONG		WrnSetMsk[ WRN_BITTBL_NUM ];	 
 	APPL		Appl;							 
 } ALM;
extern KALM Kalm;
extern ALM Alm;
 
extern void AlarmManager_Init( void );
extern void AlarmManager(void);
extern void KriResetParamError( void );
extern void KpiAlarmManager( void );
extern void KpiResetAlarmTable( void );
extern LONG KpiGetAlarmTraceInfo( ALMINF  *AlmInfo, LONG  MaxInfo );
extern void KpiSetParamError( CPRMDEF	*PrmDef );
extern UCHAR	KpiGetOtherAlarmChk( USHORT );
extern void KpiSetWarningMask( ULONG, ULONG );
extern void KpiWarningMask( ULONG );
extern void KpiResetAlarmTrace( void );
extern ULONG KpiGetAlarmTraceTmStamp( LONG);
extern USHORT KpiGetAlarmTraceAlmCode( LONG);
extern void ErrFlag_Update( void );
 #endif
