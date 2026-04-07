  
  
  
  
  
 #include "Main.h"
 
  
  
  
  
  
  
  
  
void	RpiCheckRoundTask( void )
{
 
 		return;
 }
  
  
  
LONG	RpiClearRoundReady( void )
{
 		KPI_DI( );
		if( CoutV.f.Sv.SvonReq == FALSE )
		{
			RoutV.f.RndReady = FALSE;
			KPI_EI( );
			return( TRUE );
		}
		else
		{
			KPI_EI( );
			return( FALSE );
		}
 }
