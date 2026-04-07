  
  
  
  
  
 #include "Main.h"
 
  
  
 void PcalBaseSpeedFFControl( void )
{
LONG kx,sx;
#if 0
    kx  = MlibScalKskxkx( Bprm.OvrSpd, ( 100  + Prm.jrate ), 100, &sx, 0 );
	kx  = MlibPcalKxksks( kx, Bprm.Jmot, Bprm.MaxTrq, &sx, -1 );
    kx  = MlibScalKskxkx( kx, Prm.sfgn, 100, NULL, 24 );
#else
    kx  = MlibScalKskxkx( Bprm.OvrSpd, ( 100UL  + Prm.jrate ), 100, &sx, 0 );
	kx  = MlibPcalKxksks( kx, Bprm.Jmot, Bprm.MaxTrq, &sx, -1 );
    kx  = MlibScalKskxkx( kx, (ULONG)160 * Prm.sfgn, 1, NULL, 24 );   
#endif
    GselGains[ 0 ].SFCoeff = kx;
    GselGains[ 1 ].SFCoeff = kx;
}
  
  
  
void PcalBaseSpeedControl( USHORT  Loophz, USHORT  Pitime, USHORT  jrate, LONG	GselNo )
{
 	LONG kx,sx,Kvx;
  
  
  
  
  
 	kx  = MlibScalKskxkx( Bprm.OvrSpd, C2PAIE7, C10POW7, &sx, 0 );
	kx  = MlibPcalKxksks( kx, Bprm.Jmot, Bprm.MaxTrq, &sx, -1 );
	Kvx = kx;    
     SpdCtrl.P.PI = (Iprm.f.IPSpdControl)? MlibScalKxgain( 100 - (Prm.ipg_rwt & 0x00FF), 1, 100, NULL, 24) : 1;
 	 
 	 
	if( Iprm.f.IPSpdControl )									 
	{
          
 		GselGains[ GselNo ].Kv      = 1;
          
 		GselGains[ GselNo ].Kvi     = MlibScalKskxkx( GselGains[ GselNo ].Kv, KPI_SACYCLEUS, 10UL * Pitime, NULL, 24 );
         GselGains[ GselNo ].Kv2     = MlibScalKskxkx( Kvx, ( 100UL  + jrate ) * Loophz, 1000, NULL, 24 );
 		kx = MlibScalKxkxks( 1000, 1, Kvx, &sx, 0 );
		GselGains[ GselNo ].Kv2Inv  = MlibPcalKxgain( kx, 1, ( 100UL	+ jrate ) * Loophz, &sx, 24 );
	}
	else														 
	{
          
 		GselGains[ GselNo ].Kv  	= MlibScalKskxkx( Kvx, ( 100UL  + jrate ) * Loophz, 1000, NULL, 24 );
          
          
		GselGains[ GselNo ].Kvi		= MlibScalKskxkx( GselGains[ GselNo ].Kv, KPI_SACYCLEUS, 10UL * Pitime, NULL, 24 );
         GselGains[ GselNo ].Kv2     = 1;
		GselGains[ GselNo ].Kv2Inv  = 1;
	}
     PcalBaseSpeedFFControl();
 	return;
}
 
  
  
  
  
void PcalBaseTrqLpassFilter( USHORT  Trqfil1, LONG	GselNo )
{
	TrqFil.A.Klpf = MlibPcalKf1gain( 10UL * Prm.trqfil11, KPI_SACYCLEUS, 0 );
	GselGains[ GselNo ].Klpf = MlibPcalKf1gain( 10UL * Trqfil1, KPI_SACYCLEUS, 0 );
	return;
}
