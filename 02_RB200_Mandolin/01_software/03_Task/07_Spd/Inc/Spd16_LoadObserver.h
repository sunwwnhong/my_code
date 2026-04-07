 /*
 * Spd16_LoadObserver.h
 *
 *  Created on: 2020Äê12ÔÂ1ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd16_LoadObserver_H
#define Spd16_LoadObserver_H
 
  
  
typedef struct {
      float x[2];                            
      float A[2][2];                         
	  float B[2];                  
      float q[2];                            
      float p[2][2];                         
      float gain[2];                         
       float Te_Old;
      float TL;
      float wm;
       float SpdFbk;                          
      float Te;                              
      float RatTrqCoeff;                     
       float  TlObsGain;                      
      LONG  TLObsFil;                        
      LONG  TLOberver;                       
      LONG  TlFilo;                          
 }TLOBSERVER;
 extern TLOBSERVER TlObs;
 extern void TlObs_Init( void );
extern void TlObs_Main( void );
 extern void TLObs_Gain( void );
extern void TLObs_TlFilo( void );
extern void RLS_Deal( double u, double y );
 
#endif
 
