  
  
  
  
  			
 #include "Main.h"
  
  
  
void	KaiOutputTrqRef( LONG TrqRef, LONG IdRef, LONG DisTrq )
{
    AinK.IdRef = (double)IdRef * 0.000894069672;
    AinK.IqRef = (double)TrqRef * 0.000894069672;
     BoutK.TrqRef = TrqRef;								     
  
     AinK.IqDist = (SHORT)( ((float)DisTrq) * 0.000894069672f );
 
     return;
}
