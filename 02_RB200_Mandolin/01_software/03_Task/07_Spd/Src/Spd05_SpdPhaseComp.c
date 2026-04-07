  
  
  
  
  
 #include "Main.h"
 
 
  
  
 LONG LpxSpdRefPhaseComp( LONG  SpdRefx )
{
	LONG SpdRefComp;
      
      
	if( SpdCtrl.V.SpdRefFilClrCmd == TRUE )
	{
 		SpdCtrl.V.SpdRefPhLpfo	  = SpdRefx;
		SpdCtrl.V.SpdRefPhHpfTmp  = SpdRefx;
		SpdCtrl.V.SpdRefFilClrCmd = FALSE;
	}
      
      
	SpdCtrl.V.SpdRefPhLpfo = MlibLpfilter1( SpdRefx, SpdCtrl.P.SpdRefPhFil, SpdCtrl.V.SpdRefPhLpfo );
      
      
	SpdCtrl.V.SpdRefPhHpfo = MlibHpfilter1( SpdRefx, SpdCtrl.P.SpdRefPhFil, &SpdCtrl.V.SpdRefPhHpfTmp );
      
      
	if( ( Gprm.f.TuningLess ) && ( Gprm.f.TuningLessVComp == TRUE ))
	{
		SpdRefComp = SpdCtrl.V.SpdRefPhLpfo + MlibMulgain( SpdCtrl.V.SpdRefPhHpfo, SpdCtrl.P.SpdRefPhFilGn );
	}
	else
	{
		SpdRefComp = SpdRefx;
	}
 	return ( SpdRefComp );
}
  
  
  
LONG LpxSpdFFPhaseComp( LONG  SpdFFC )
{
	LONG SpdFFCComp;
 	 
 	if( SpdCtrl.V.SpdFFFilClrCmd == TRUE )
	{
		SpdCtrl.V.SpdFFFilClrCmd = FALSE;
 		switch( BPI_GET_BASE_CTRLMODE( ) )
		{
			case CTRLMODE_POS:						             
				SpdCtrl.V.SpdFFPhLpfo	= SpdFFC;
				SpdCtrl.V.SpdFFPhHpfTmp = SpdFFC;
				break;
			case CTRLMODE_SPD:						             
				SpdCtrl.V.SpdFFPhLpfo	= 0;
				SpdCtrl.V.SpdFFPhHpfTmp = 0;
				break;
			default:
				break;
		}
	}
 	 
 	SpdCtrl.V.SpdFFPhLpfo = MlibLpfilter1( SpdFFC, SpdCtrl.P.SpdFFPhFil, SpdCtrl.V.SpdFFPhLpfo );
      
      
	SpdCtrl.V.SpdFFPhHpfo = MlibHpfilter1( SpdFFC, SpdCtrl.P.SpdFFPhFil, &SpdCtrl.V.SpdFFPhHpfTmp );
      
      
	if( ( Gprm.f.TuningLess ) && ( Gprm.f.TuningLessVComp == TRUE ))
	{
		SpdFFCComp = SpdCtrl.V.SpdFFPhLpfo + MlibMulgain( SpdCtrl.V.SpdFFPhHpfo, SpdCtrl.P.SpdFFPhFilGn );
	}
	else
	{
		SpdFFCComp = SpdFFC;
	}
	return ( SpdFFCComp );
}
