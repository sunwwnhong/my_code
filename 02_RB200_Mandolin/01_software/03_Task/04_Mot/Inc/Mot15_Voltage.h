/*
 * Mot15_Voltage.h
 *
 *  Created on: 2017Äê4ÔÂ15ÈÕ
 *      Author: zhuxc
 */
 #ifndef Mot15_Voltage_H
#define Mot15_Voltage_H
 
  
  
  
  
 typedef	struct {
 		LONG	Kdcvolt;					 
		LONG	KVdcAsic;					 
        LONG    VdcMaxCoeff;                 
        USHORT  VdcRatio;                    
        USHORT  VdcMax;                      
 #if(FLOAT_USE == 1)
        float   DcAdFili;                    
        float   DcAdFilo[3];
        float   VdetAdFil;                   
        float   VdcRatioCoeff;               
#else
        LONG	DcAdFili;                    
		LONG	DcAdFilo[3];
        LONG    VdetAdFil;                   
        LONG    VdcRatioCoeff;               
#endif
         SHORT	DcVoltx;					 
        SHORT   DcVolt;                      
        SHORT   UnDcVolt;                    
         USHORT  UdcStep;                     
        USHORT  WaitTime;                    
        SHORT   DcVoltOld;                   
        USHORT  VdcOVAlmCnt;                 
        USHORT  VdcLVAlmCnt;                 
} VOLTKIOP;
extern VOLTKIOP VoltVar;
 extern void BprmAmpMotVoltInfoCal( void );
extern void	IprmcalVoltageCheckLevel( void );
extern void	LpxDetectDcVolt( void );
 #endif
