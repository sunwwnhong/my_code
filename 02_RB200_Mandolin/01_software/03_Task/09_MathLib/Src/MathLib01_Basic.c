  
  
  
#include "MathLib01_Basic.h"
 
  
  
 LONG KpxBprmExpCal( SHORT  exp )
{
    LONG i,
         x;
    LONG ksx;
    LONG aexp;
    aexp = ( exp >= 0 )? exp:-exp;                               
     for( x = 1, i = 0; i < aexp; i++ )                           
    {
        x = 10 * x;                                              
    }
     if( exp >= 0 )                                               
    {
        ksx = MlibScalKxgain( x, 1, 1, NULL, -1 );               
    }
    else
    {
        ksx = MlibScalKxgain( 1, 1, x, NULL, -1 );               
    }
     return ( ksx );
}
 
  
  
 float FlibExpCal( SHORT exp )
{
     LONG    i, x;
    LONG    aexp;
    float   Output;
     if( exp > 128 )
    {
        aexp =  256L - exp;
    }
    else
    {
        aexp = exp;
    }
     for( x=1,i=0; i < aexp; i++ )                        
    {
        x = 10 * x;                                      
    }
     if( exp > 128 )                                      
    {
         Output = 1.0F / (float)x;                        
    }
    else
    {
        Output = (float)x;                               
    }
     return Output;
}
