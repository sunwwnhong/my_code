/*
 * Cur18_WeakMagneticControl.h
 *
 *  Created on: 2018Äê09ÔÂ21ÈÕ
 *      Author: zhuxc
 */
 #ifndef Cur18_WeakMagneticControl_H
#define Cur18_WeakMagneticControl_H
 
  
 typedef	struct	{
		LONG	KpvBeforeDiv;			 
        float   fKpvBeforeDiv;           
		LONG	Kpv;					 
		LONG	KivBeforeDiv;			 
        float   fKivBeforeDiv;           
		LONG	Kiv;					 
 		LONG	IdrefLimTerm1;			 
		LONG	IdrefLimTerm23;			 
		LONG	IdrefLimTerm4;			 
 		float   fIdrefLimTerm1;          
        float   fIdrefLimTerm23;         
        float   fIdrefLimTerm4;          
 
		LONG	VdcSum;					 
        LONG    fVdcSum;                 
		SHORT	VMax;					 
		SHORT	IdrefLim;				 
		SHORT	KpvL;					 
		SHORT	KpvH;					 
		SHORT	KivL;					 
		SHORT	KivH;					 
		SHORT	VdcAsic;				 
        float   fVdcAsic;                
        float   fWFMaxI;                 
		SHORT	VdcAvgCnt;				 
		SHORT	VdcSumCnt;				 
        SHORT   WFUd;                    
        SHORT   WFUq;                    
        SHORT   WFU;                     
        SHORT   WFUqMax;                 
        LONG    WFInteg;                 
        LONG    KiIntegLimit;            
        LONG    KVdcAsic;                
        LONG    fKVdcAsic;               
 } WEAKENFIELD;
extern	WEAKENFIELD	WeakenField;
 extern void LpxWFPrmCalc( void );
extern void FLpxWFPrmCalc( void );
extern SHORT LpxWFIdCalc( void );
extern void PcalVFBKiLim( void );
extern void	PcalIdrefLimTerm1( USHORT vmax, USHORT vmaxid );
extern void     WFKVdc_Init( void );
extern void	PcalVFBKp( USHORT Kpv, USHORT Tiv );
extern void	PcalVFBKi( USHORT Kpv );
#endif
