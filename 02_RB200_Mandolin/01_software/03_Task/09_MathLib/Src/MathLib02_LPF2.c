  
  
  
  
  
 #include "MathLib02_LPF2.h"
  
  
  
LONG PcalLowfilter2( LONG  hz, LONG  qx, LONG  ts,				 
 																 
						LONG  kn[ 4 ] )							 
{
	LONG ka,
		 sa,
		 kb,
		 sb,
		 kc,
		 sc;
	LONG kx,
		 sx,
		 ky,
		 sy;
 	 
 	 
	if( hz > 2000 )
	{
		hz = ( LONG )( ( SHORT )hz * ( SHORT )( 3 * hz - 1894 ) + 11788000 ) / 10000;
	}
 	sc		= 15;
	kc		= MlibPcalKxgain( hz * hz, ts * ts, 773019, &sc, 0 );
 	sb		= 0;
	kb		= MlibPcalKxgain( hz, ts, qx, &sb, 0 );
	kb		= MlibPcalKxgain( kb, 125664, 10000000, &sb, 0 );	 
 	kx		= MlibPcalKxaddx( 4UL<<24, 24, kc, sc, &sx );  		 
	ky		= MlibPcalKxsubx( 4UL<<24, 24, kc, sc, &sy );  		 
	sy		= sy - 1;
	ka		= MlibPcalKxaddx( kx, sx, kb, sb, &sa );			 
	kb		= MlibPcalKxsubx( kx, sx, kb, sb, &sb );			 
 	kn[ 0 ] = MlibPcalKxdivx( kc, sc, ka, sa, 24 );  			 
	kn[ 1 ] = MlibPcalKxdivx( ky, sy, ka, sa, 24 );  			 
	kn[ 2 ] = MlibPcalKxdivx( kb, sb, ka, sa, 24 );  			 
	kn[ 3 ] = MlibPcalKxdivx( kc, ( sc - 1 ), ka, sa, 24 );  	 
 	return ( 0 );
 }
  
  
 LONG MlibLowPassfilter2( LONG  u, LONG	k[ 4 ], LONG  z[ 4 ] )
{
	LONG x[ 6 ];
 	x[ 0 ] = MlibMulgain29( u, k[ 0 ] );
	x[ 1 ] = MlibMulgain29( z[ 0 ], k[ 3 ] );
	x[ 2 ] = MlibMulgain29( z[ 1 ], k[ 0 ] );
	x[ 3 ] = MlibMulgain29( z[ 2 ], k[ 1 ] );
	x[ 4 ] = MlibMulgain29( z[ 3 ], k[ 2 ] );
	x[ 5 ] = x[ 0 ] + x[ 1 ] + x[ 2 ] + x[ 3 ] - x[ 4 ];
 	z[ 3 ] = z[ 2 ];
	z[ 2 ] = x[ 5 ];
	z[ 1 ] = z[ 0 ];
	z[ 0 ] = u;
 	return ( x[ 5 ] );
 }
 
 
