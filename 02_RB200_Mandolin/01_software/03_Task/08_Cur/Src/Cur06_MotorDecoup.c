  
  
  
  
  
 #include "Main.h"
  
LONG	PcalDqRxComp( KSGAIN Rx )
{
LONG	kx,sx;
		kx = MlibScalKskxkx( Rx, 35791,       1,        &sx,   0 );
		kx = MlibPcalKxksks( kx, Bprm.MaxCur, Bprm.Vdc, &sx, -24 );
		return( kx );
}
float   FPcalDqRxComp( float Rx )
{
float   fkx;
        fkx = Rx * 35791.0f;
        fkx = fkx * Bprm.fMaxCur / Bprm.fVdc;
        fkx = fkx / ((float)(1UL << 15));
        return( fkx );
}
  
LONG	PcalDqLxComp( KSGAIN Lx )
{
LONG	kx,sx;
		kx = MlibScalKsksks( Bprm.OvrSpd, Bprm.MaxCur,  Bprm.Vdc,   &sx,   0 );
		kx = MlibPcalKxkskx( kx,          Lx,           1,          &sx,   0 );
        kx = MlibPcalKxkskx( kx,          Bprm.Keangle,	1,		    &sx,   0 );
		kx = MlibPcalKxgain( kx,          4886,        1,           &sx, -24 );
		return( kx );
}
 float   FPcalDqLxComp( float Lx )
{
float   fkx;
        fkx = Bprm.fOvrSpd * Bprm.fMaxCur / Bprm.fVdc;
        fkx = fkx * Lx;
        fkx = fkx * Bprm.fKeangle;
        fkx = fkx * 78187.49353f;
        fkx = fkx / ((float)(1UL << 30));
        return( fkx );
}
  
LONG	PcalDqEmfComp( KSGAIN Emf )
{
LONG	kx,sx;
		kx = MlibScalKsksks( Emf, Bprm.OvrSpd, Bprm.Vdc, &sx,   0 );
        kx = MlibPcalKxgain( kx,  20664,     1,        &sx, -24 ); 
		return( kx );
}
float FPcalDqEmfComp( float Emf )
{
float   fkx;
        fkx = Emf * Bprm.fOvrSpd / Bprm.fVdc;
        fkx = fkx * 50616.675f;
        fkx = fkx / ((float)(1UL << 15));
        return( fkx );
}
