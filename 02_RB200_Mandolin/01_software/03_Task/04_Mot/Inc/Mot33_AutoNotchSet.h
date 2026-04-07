/*
 * Mot33_AutoNotchSet.h
 *
 *  Created on: 2018Äê 08ÔÂ25ÈÕ
 *      Author: zhuxc
 */
 
 #ifndef Mot33_AutoNotchSet_H
#define Mot33_AutoNotchSet_H
 #define		OPTUNE_STS_NOTCH_INIT		0x00
#define		OPTUNE_STS_NOTCH1_OK		0x01
#define		OPTUNE_STS_NOTCH2_OK		0x02
#define		OPTUNE_STS_NOTCHQ1_ERR		0x04
#define		OPTUNE_STS_NOTCHQ2_ERR		0x08
#define		OPTUNE_STS_NT_NODETECT		0
#define		OPTUNE_STS_NT_DETECT		1
#define		OPTUNE_STS_NT_NOENABLE		2
#define		OPTUNE_STS_NT_DET_ERR		3
#define		OPTUNE_STS_NT1_NODETECT		0
#define		OPTUNE_STS_NT1_COMP			1
#define		OPTUNE_STS_NT1_NG			2
#define		OPTUNE_STS_NT2_NODETECT		0
#define		OPTUNE_STS_NT2_COMP			1
#define		OPTUNE_STS_NT2_NG			2
#define		OPTUNE_PSTS_NODETECT		0
#define		OPTUNE_PSTS_NT1_COMP		1
#define		OPTUNE_PSTS_NT2_COMP		2
 extern void RpiANotchFftReqSet( void );
extern void RpiResetStatusANotch1( void );
extern void RpiResetStatusANotch2( void );
extern UCHAR RpiGetANotchPreStat( void );
extern void RpiANotchDisableReqSet( void );
extern void PcalAnotchOnePrmCalc( USHORT , USHORT );
extern USHORT RpiGetSpatANotchState( void );
extern void RpiANotchTrqFilCalc( HMSGIF  Hmsg );
extern void RpxAnotchRound( void );
 #endif
