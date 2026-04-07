  
  
  
  
  
  
 #include "Main.h"
 
  
  
  
  
  
  
  
 void IprmcalMotorOverrun( void )
{
	LONG work1;
 	 
 	work1 = Prm.RunOverTorq;
 	if( work1 > ( ULONG )Bprm.PerMaxTrq )
	{
		ChkAlmP.OvrTrqLevel = 0x01000000;
	}
	else
	{
		ChkAlmP.OvrTrqLevel = MlibScalKxgain( work1, 0x01000000, Bprm.PerMaxTrq, NULL, -24 );
	}
 	 
 	ChkAlmP.OvrSpdLevel = 0x01000000 * Prm.RunOverSpd / 100;
 	return;
}
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 void LpxCheckMotorOverrun( void )
{
 	LONG Condition0;
	LONG Condition1;
	LONG DetectTime;
      
     if( Prm.RunOverTorq == 0)
        return;
      
     Condition0 = ( StateM_Var.f.PwmEn && ( ChkAlmV.OvrChkCnt < KPI_SCANC_MS( 500 ) ) ) ? TRUE:FALSE;
      
     Condition1 = ( ( ChkAlmV.OvrChkCnt != 0 ) || ( CinK.AbsMotSpd >= 1677721 ) )? TRUE:FALSE;
    DetectTime = KPI_SCANC_MS( 20 );
      
      
      
	if( Condition0 )
	{
		if( Condition1 )
		{
			ChkAlmV.OvrChkCnt++;
		}
          
          
 		 
 		if( ( ( CinK.MotSpd ^ CinK.TrqRefMon ) < 0 )
			 && ( ( CinK.TrqRefMon ^ ChkAlmV.OvrTrqRef ) >= 0 )
			 && ( CinK.AbsTrqRefMon >= ChkAlmP.OvrTrqLevel )
			 && ( CinK.AbsMotSpd >= ChkAlmP.OvrSpdLevel ) && ( CinK.TrqRefMon != 0 )
		  ) 
		{
			if( CinK.AbsMotSpd >= ChkAlmV.OvrAbsMotSpd )		 
			{
				if( CinK.AbsMotSpd >= ChkAlmV.OvrPeakMotSpd )	 
				{
					if( ChkAlmV.OvrAlmCnt >= DetectTime )		 
					{           
						KPI_ALARMSET  ( ALM_RWF );				 
					}
					else
					{
						ChkAlmV.OvrAlmCnt++;					 
					}
				}
				else
				{
					ChkAlmV.OvrAlmCnt = 0;						 
				}
			}
			else
			{
				if( ChkAlmV.OvrAbsMotSpd > ChkAlmV.OvrPeakMotSpd ) 
				{
					ChkAlmV.OvrPeakMotSpd = ChkAlmV.OvrAbsMotSpd;
 				}
				ChkAlmV.OvrAlmCnt = 0;							 
			}
		}
		else
		{
			ChkAlmV.OvrAlmCnt = 0;								 
		}
	}
	ChkAlmV.OvrTrqRef	 = CinK.TrqRefMon;						 
	ChkAlmV.OvrAbsMotSpd = CinK.AbsMotSpd;						 
 	return;
 }
