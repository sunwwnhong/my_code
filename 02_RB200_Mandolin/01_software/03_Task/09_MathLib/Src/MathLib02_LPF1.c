  
  
  
  
  	
 #include "MathLib02_LPF1.h"
 
 
  
  
  
LONG	MlibLpfilter1( LONG u, LONG k, LONG x )
{
LONG	wk1;
LONG	xx[2];
  
  
		if( k == 0 )
		{
			return( u );
		}
  
 		MUL3232( (u-x), k, xx );
		wk1 = (xx[1]<<8) + (((((ULONG)xx[0])>>23)+1)>>1);
 		if( wk1 == 0 )
		{
			return( x + ((u-x)>0) - ((u-x)<0) );
		}
		else
		{
			return( x + wk1 );
		}
}
 
  
  
 float   FlibLpfilter1( float u, float k, float x )
{
 float   ax;
float   wk1;
  
         if( k == 0.0f )
        {
            return( u );
        }
        ax = ( u - x );
        wk1 = ( ax * k );
        x = ( x + wk1 );
        return( x );
 }
 
  
  
 float FlibHpfilter1( float u, float k, float *z )
{
    if( k == 0.0f )
    {
        *z = 0;
    }
    else
    {
        *z = FlibLpfilter1( u, k, *z );
        u = u - *z;
    }
    return( u );
}
 
 
 
