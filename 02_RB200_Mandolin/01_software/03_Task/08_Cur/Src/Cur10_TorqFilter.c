  
  
  
  
  
  
  
#include "Main.h"
 
TRQFIL TrqFil;
 
  
  
  
  
  
  
void PcalBaseTrqLpassFilter2( void )
{
	LONG hz = Prm.secfil;										 
	LONG qx = 10 * Prm.secq;									 
 	PcalLowfilter2( hz, qx, KPI_SACYCLEUS, TrqFil.P.Klpf2 );
 	return;
 }
 void	PcalBaseTrqLpassFilter3( USHORT Trqfil )
{
 		TrqFil.P.Klpf3 = MlibPcalKf1gain( 10*Trqfil, KPI_SACYCLEUS, 0 );
 		return;
}
 
  
  
 LONG	BaseTorqueFilter( LONG TrqRefi,	LONG TrqFBC, LONG TrqFFC )	
{
	LONG TrqRefx;
	LONG DisTrqRef1 = 0;										 
	LONG DisTrqRef2 = 0;										 
  
  
	AoutV.DisTrqRef3 = 0;                                        
    switch( TrqFil.V.TrqInputPos )
	{
 		case 0x01:												 
			DisTrqRef1 = TblExeV.TrqRef;
			break;
 		case 0x02:												 
			DisTrqRef2 = TblExeV.TrqRef;
			break;
 		case 0x03:                                               
			AoutV.DisTrqRef3 = TblExeV.TrqRef;
			break;
 		case 0x00:												 
		default:
			break;
	}
  
  
	if( BinV.f.BaseEnable == FALSE )
	{
		TrqFil.V.FilOut  	  = 0;
		TrqFil.V.FilOut3	  = 0;								 
		TrqFil.V.TrqFilClrCmd = FALSE;							 
		TrqFil.V.LpFil2[ 0 ]  = 0;
		TrqFil.V.LpFil2[ 1 ]  = 0;
		TrqFil.V.LpFil2[ 2 ]  = 0;
		TrqFil.V.LpFil2[ 3 ]  = 0;
		return ( 0 );
	}
  
 	else
	{
		if( ( BPI_GET_BASE_CTRLMODE( ) == CTRLMODE_TRQ ) && ( BoutV.ZctrlMode.b.zm == CTRLMODE_ZNONE ) )
		{
			return ( 0 );
		}
	}
      
     
    TrqRefx = MlibLimitul( (TrqRefi + DisTrqRef1), 0x01000000, -0x01000000 );
  
  
	if( TrqFil.V.TrqFilClrCmd == TRUE )  						 
	{
		TrqFil.V.FilOut  	  = TrqRefx;						 
		TrqFil.V.TrqFilClrCmd = FALSE;							 
	}
  
 	TrqFil.V.FilOut = MlibLpfilter1( TrqRefx, GselGains[ 0 ].Klpf, TrqFil.V.FilOut );
  
  
    TrqRefx = MlibLimitul( (TrqFil.V.FilOut + TrqFFC - TrqFBC + DisTrqRef2), 0x01000000, -0x01000000 );
  
  
 	if( Gprm.f.LpassFil3 == TRUE )								 
	{
		if( Gprm.f.TuningLess )  								 
		{
			TrqFil.V.FilOut3 = MlibLpfilter1( TrqRefx, TrqFil.P.Klpf3, TrqFil.V.FilOut3 );
			TrqRefx  		 = TrqFil.V.FilOut3;
		}
		else
		{
			TrqFil.V.FilOut3 = 0;
		}
	}
	else
	{
		TrqFil.V.FilOut3 = 0;
	}
  
  
	if( Gprm.f.LpassFil2 == FALSE )
	{
		TrqFil.V.LpFil2[ 0 ] = 0;
		TrqFil.V.LpFil2[ 1 ] = 0;
		TrqFil.V.LpFil2[ 2 ] = 0;
		TrqFil.V.LpFil2[ 3 ] = 0;
	}
	else
	{
		TrqRefx = MlibLowPassfilter2( TrqRefx, TrqFil.P.Klpf2, TrqFil.V.LpFil2 );
	}
     return( MlibLimitul( TrqRefx, 0x01000000, -0x01000000 ) );
}
 
  
  
 void BpiEnableCPUTorqueFilter( void )
{
	TrqFil.V.TrqFilDisable = FALSE;
	return;
}
  
  
  
void BpiDisableCPUTorqueFilter( void )
{
	TrqFil.V.TrqFilDisable = TRUE;
	return;
}
  
  
  
void BpiSetTrqInputPos( LONG  TrqInputPos )
{
	TrqFil.V.TrqInputPos = TrqInputPos;
	return;
}
 
