  
  
  
  
  
 #include "Main.h"
 
  
  
  
void PcalBasePositionPControl( USHORT  Posgn, LONG	GselNo )
{
	LONG kx,
		 sx;
     GselGains[ GselNo ].Kp      = MlibScalKskxkx( Hprm.Kpx, Posgn, 10, NULL, 24 );
	GselGains[ GselNo ].KpInv	= MlibScalKxgain( 1000000, 10, Posgn * KPI_SACYCLEUS, NULL, -24 );
 	 
 	 
 	 
 	kx = MlibScalKxgain( 1, 10, Posgn, &sx, 0 );
	kx = MlibPcalKxkxks( kx, 1, Hprm.Kpx, &sx, 0 );
	GselGains[ GselNo ].VirtualPosKp
	= MlibPcalKxgain( kx, Iprm.Egear.a, Iprm.Egear.b, &sx, 24 );
	return;
}
  
  
  
void PcalBasePositionIControl( void )
{
	PosCtrl.P.Kpi = ( Prm.pitfil )? MlibScalKxgain( 1, KPI_SACYCLEUS, 100 * Prm.pitfil, NULL, 24 ):0;
	return;
}
  
  
  
  
  
  
  
  
  
void PcalZeroPositionControl( USHORT  Posgn, LONG  GselNo )
{
	LONG kx,
		 sx;
 	kx = MlibScalKxksks( 0x01000000, Bprm.Kmotpls, Bprm.OvrSpd, &sx, 0 );
	kx						 = MlibPcalKxgain( kx, Posgn, 10, &sx, 24 );
	GselGains[ GselNo ].ZcKp = kx;
	return;
}
 
