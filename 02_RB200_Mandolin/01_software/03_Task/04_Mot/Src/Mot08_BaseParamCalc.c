  
  
  
  
  
 #include "Main.h"
 
 
  
  
  
LONG KpiMonSpeedCal( LONG  Speed )
{
LONG x;
#if(FLOAT_USE == 1)
    if( Speed >= 0 )
    {
        x = (float)Speed * Iprm.fKmonspd + 0.5f;
    }
    else
    {
        x = (float)Speed * Iprm.fKmonspd - 0.5f;
    }
#else
	x = MlibMulgainSx48( Speed, Iprm.Kmonspd );
#endif
	return ( x );
}
  
  
  
LONG KpiMonSpeedCal1( LONG  Speed )
{
LONG x;
	x = MlibMulgainSx48( Speed, Iprm.Kmonspd1 );
	return ( x );
}
 
  
  
