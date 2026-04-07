/*
 * Mot26_TurnLib.h
 *
 *  Created on: 2018Äê 08ÔÂ11ÈÕ
 *      Author: zhuxc
 */
 #include "Svoption.h"
 #ifndef Mot26_TurnLib_H
#define Mot26_TurnLib_H
  
  
  
#define  	TUNE_FREQ_SEARCHINIT	  0  			 
 #define  	TUNE_FREQ_SEARCHEND  	  1  			 
 #define  	TUNE_FREQ_SEARCH		  2  			 
#define  	TUNE_FREQ_SEARCHERR  	  -1			 
 #define  	TUNE_MDLZETA			  1000			 
 #define  	TUNE_MFCKTFF			  1000			 
 #define  	TUNE_MFCKVFF			  1000			 
 													 
 #define		TUNE_MFCKVFF2			900               
#define  	TUNE_DTRQGN  			  85			 
 #define  	TUNE_DOBJGN  			  100			 
#define  	TUNE_DOBGNRATIO  		  100			 
  
#define  	TUNE_PI_TIKV			  636620		 
 #define  	TUNE_IP_TIKV			  318310		 
#define  	TUNE_IP_KPTI			  250000		 
  
#define  	TUNE_ANOTCH_DECA		  10			 
#define  	TUNE_ANOTCH_Q_MIN		  50			 
#define  	TUNE_ANOTCH_Q_MAX		  300			 
#define  	TUNE_ANOTCH_Q_MAX_DET	  500			 
 #define  	TUNE_MAX_DLPFIL  		  4000			 
 													 
 #define  	TUNE_RESFRQ_KV			  100			 
 #define  	TUNE_ANTFRQ_KV			  100			 
#define  	TUNE_ANTFRQ_NTQ1		  100			 
#define  	TUNE_ANTFRQ_NTQ2		  100			 
 #define  	AVIB_FRQ_MIN			  100			 
#define  	AVIB_FRQ_MAX			  1000			 
 #define 	AVIBDAMPGN				180		         
  
  
typedef  struct
{
 	USHORT NotchSw;
 	USHORT TrqFil;
	USHORT NotchFil1;
	USHORT NotchFil2;
	USHORT NotchQ1;
	USHORT NotchQ2;
} TRQFILV;
 
typedef  struct
{
	TRQFILV Fil;
} ANOTCHV;
  
typedef  struct
{
	USHORT KvrateTf;								 
	USHORT KvrateTfonNt;							 
	USHORT KvrateQ;  								 
	USHORT J1Tf;									 
	USHORT J1TfonNt;								 
 													 
 	USHORT J1Q;  									 
	USHORT TfMin;									 
	USHORT NotchQMin;                                
} ANOTCHP;
  
extern ANOTCHP	ANotchP;
extern ANOTCHV	ANotchV;
 extern SHORT TuneVibrationTrace( UCHAR, SHORT );
extern void	TuneFilGainCalbyFilType( UCHAR );
extern USHORT TuneKvFuncTi( USHORT );
extern USHORT TuneKvFuncKp( USHORT , USHORT );
extern USHORT TuneKvFuncDobsgn( USHORT );
extern SHORT TuneNotchQ( USHORT , USHORT , UCHAR , HMSGIF );
extern void	TuneDobsActive( HMSGIF Hmsg );
extern SHORT TuneNotchFilSet( USHORT, USHORT, USHORT, USHORT, HMSGIF );
extern SHORT TuneATypeResSet( USHORT, USHORT, HMSGIF );
extern void TuneMfcActive( HMSGIF );
extern void TuneMfcActiveStMode( HMSGIF );
extern SHORT TuneAdatSetMdlCtrlGain( LONG , HMSGIF );
extern USHORT	TuneMfcKpmCalcAntFreq( USHORT AntFreq );
 #endif
