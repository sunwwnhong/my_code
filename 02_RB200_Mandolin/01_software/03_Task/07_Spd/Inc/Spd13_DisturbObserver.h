/*
 * Spd13_DisturbObserver.h
 *
 *  Created on: 2018Äê8ÔÂ23ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd13_DisturbObserver_H
#define Spd13_DisturbObserver_H
 
#define DIDOVS 1
  
  
typedef	struct	{								 
 		LONG	Ks;								 
		LONG	Kj;								 
		LONG	Ksj;							 
		LONG	Kd;								 
		LONG	Klpf;							 
} DOBSP;
  
  
typedef struct  {                                
         float    fKs;                            
        float    fKj;                            
        float    fKsj;                           
        float    fKd;                            
        float    fKlpf;                          
        LONG    Ks;                              
        LONG    Ksj;                             
} FDOBSP;
typedef	struct	{								 
 		DOBSP	P[3];							 
		struct {								 
 		LONG	Ivar64[2];						 
		LONG	SpdObs;							 
		LONG	DisTrq;							 
		LONG	Hpftmp;							 
		LONG	DTrqLpfo;						 
 		LONG	DisTrqCmp;						 
		UCHAR	enable;							 
		UCHAR	LstEnable;						 
		} V;
} DOBS;
 
typedef struct  {                                
         FDOBSP   P[3];                           
        struct {                                 
         float    Ivar64[2];                         
        float    SpdObs;                          
        float    DisTrq;                          
        float    Hpftmp;                          
        float    DTrqLpfo;                        
         float    DisTrqCmp;                       
        USHORT   enable;                          
        USHORT   LstEnable;                       
        } V;
} FDOBS;
 extern DOBS Dobs;
extern FDOBS FDobs;
extern void	BpxInitDisturbObserver( void );
extern void	PcalDisturbObserver( USHORT, USHORT, USHORT, USHORT, USHORT, SHORT, USHORT, LONG );
extern void	ApxDisturbObserver( LONG , LONG );
extern void	PcalDisturbObserverSW( void );
 #endif
