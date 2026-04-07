/*
 * Spd11_ResVibCtrl.h
 *
 *  Created on: 2018Äê8ÔÂ11ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd11_ResVibCtrl_H
#define Spd11_ResVibCtrl_H
  
  
typedef	struct	{								 
#if (FLOAT_USE == 1)
        struct	{								 
        float   fKs;                             
        float   fKj;                             
        float   fKlpf;                            
        float   fKhpf;                            
		} P;
 		struct {								 
        float   fIvar64[2];                      
        float   fSpdObs;                         
        float   fAvSpdErr;                       
        float   fLastSpdErr;
        float   fAvSpdErrbfFil;                  
        float   fAvSpdFbk;                       
        float   fAvSpdErr2;                      
        float   fHpftmp;                         
		} V;
#else
        struct  {                                
        LONG    Ks;                              
        LONG    Kj;                              
        LONG    Klpf;                            
        LONG    Khpf;                            
        } P;
         struct {                                 
        LONG    Ivar64[2];                       
        LONG    SpdObs;                          
        LONG    AvSpdFbk;                        
        LONG    LastSpdErr;
        LONG    AvSpdErr;                        
        LONG    AvSpdErrbfFil;                   
        LONG    AvSpdErr2;                       
        LONG    Hpftmp;                          
        } V;
#endif
 } DETVIB;
 extern DETVIB DetVib;
 extern void IprmcalVibrationDetect( void );
extern void BpiResetMaxMinSpeedError( void );
extern void	BpiResetMaxMinSpeedError2( void );
extern void BpxVibrationDetect( void );
extern void BpxInitVibrationDetect( void );
extern void	PcalVibrationDetectJGain( void );
extern void	BpiPcalVibrationDetect2( void );
extern void	BpiPcalVibrationDetect( LONG ObsGain, LONG Lpf, LONG Hpf );
 #endif
 
 
 
 
 
