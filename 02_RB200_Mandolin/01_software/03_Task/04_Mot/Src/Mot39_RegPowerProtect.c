  
  
  
  
  
 #include "Main.h"
 
#define SVFSEL_REGCTRL 1
  
  
  
  
  
  
  
  
  
void IprmcalRegenePowerGain( void )
{
	LONG kx,
		 sx;
	LONG Vdcsqr;
    ULONG Resis;
  
  
	if( Bprm.AmpDcinType == 1 )  						 
	{
		Vdcsqr = 0;  									 
	}
	else												 
	{
		Vdcsqr = Prm.regonlvl * Prm.regonlvl;			 
	}
  
      
    if( Prm.regres == 0)
    {
       Resis = Prm.reger;                 
    }
     else
    {
        Resis = Prm.regresvalue;          
    }
  
  
  
  
  
	kx = MlibScalKxgain( Vdcsqr, KPI_SBCYCLEUS, ( KPI_SCCYCLEUS * Resis ), &sx, 0 );
	kx = MlibPcalKxgain( kx, 5000, Prm.ampw, &sx, 24 );
	ChkAlmP.Krgpower = kx;
	return;
}
 
  
  
  
  
  
  
void PcalRegeneOverLoadLevel( void )
{
	LONG kx,
		 sx;
  
  
  
  
	if( Prm.regres == 0 )										 
	{
          
         if( Prm.drvno == 0x055A && Iprm.MosfetPumpFlag == 0x0)
        {
            ChkAlmP.RgolPowBase = ( Prm.wre + 380 ) * 50000 / 100000;
        }
        else
        {
            ChkAlmP.RgolPowBase = Prm.wre * 50000 / 100000;
        }
	}
 	else                                                         
    {
        ChkAlmP.RgolPowBase = ( Prm.regres * 50000 ) / Prm.ampw;
    }
  
  
  
  
  
  
  
  
  
  
  
	kx = MlibScalKxgain( ChkAlmP.RgolPowBase, ( 2UL * 100 * 1000 ), KPI_SCCYCLEMS, NULL, -30 );
	ChkAlmP.RgolAlmLevel	= kx;
  
  
  
  
  
#if 1
	kx = MlibScalKxgain( 100, 1, ChkAlmP.RgolPowBase, &sx, 0 );
#else
	kx = MlibScalKxgain( 100, 1, ChkAlmP.RgolAlmLevel, &sx, 0 );    
#endif
	kx = MlibPcalKxgain( kx, 1, KPI_SCANC_MS( 10000 ), &sx, 24 );
	ChkAlmP.Kunrgpower		= kx;
 	return;
}
 
  
  
  
  
  
  
  
 void LpxCheckRegeneOverLoad( void )
{
	LONG RegPower;
  
  
    if( ChkAlmP.RgolAlmLevel == 0 )
    {
        return;
    }
      
     if( Iprm.f.RegRxIn == FALSE )
        return;
  
  
    RegPower = MlibMulgain30( CinK.dRegOnCount, ChkAlmP.Krgpower );
  
  
          
 		ChkAlmV.RgolPowSum += ( RegPower - ChkAlmP.RgolPowBase );
		if( ChkAlmV.RgolPowSum < 0 )
		{
			ChkAlmV.RgolPowSum = 0;
		}
 		if( ChkAlmV.RgolPowSum >= ChkAlmP.RgolAlmLevel )
		{
			KPI_ALARMSET  ( ALM_RGOL );  				 
        }
 		if( ChkAlmV.RgolPowSum >= ( ChkAlmP.RgolAlmLevel >> 1 ) )
		{
            KPI_WARNINGSET	( WRN_RGOLF );
		}
		else
		{
			KPI_WARNINGCLR	( WRN_RGOLF );						 
		}
  
  
	CoutV.UnRgPower = MlibScalKxgain( ChkAlmV.RgolPowSum, 1000, ChkAlmP.RgolAlmLevel, NULL, -30 );
     CoutV.TrcRgPower	= CoutV.UnRgPower;
	ChkAlmV.RgPowerSum += RegPower;
  
 	if( ++ChkAlmV.RgMeanCycle >= KPI_SCANC_MS( 10000 ) )
	{
		CoutV.UnMeanRgPower = ( USHORT )MlibMulgain( ChkAlmV.RgPowerSum, ChkAlmP.Kunrgpower );
		ChkAlmV.RgPowerSum	= 0;
		ChkAlmV.RgMeanCycle = 0;
	}
	return;
}
 
  
  
  
  
  
  
  
  
  
  
  
void	LpxRegeneControl( void )
{       
         if( Iprm.FATest1 == 1 || Iprm.FATest2 == 1)
        {
            if( ( Prm.FaTestControl & 0x0002 ) == 0x0002 )
            {
                BKOn();
            }
            else
            {
                BKOff( );
            }
            return;
        }
  
  
		if( Iprm.VdetPrmOk == FALSE )
        {
            BKOff( );
            return;                                          
        }			
  
 		if( KPI_ALARMCHK( ALM_RGOL ) )
		{
			if( KioV.f.RegAlmMotStop || CoutV.f.Sv.MotStop )
			{
				KioV.f.RegAlmMotStop = TRUE;
			}
			else
			{
				KioV.f.RegAlmMotStop = FALSE;
			}
		}
		else
		{
			KioV.f.RegAlmMotStop = FALSE;
		}
  
  
		if( BinK.DcVolt > Iprm.RegOnLevel )				     
		{
			KioV.RegStopCnt = 0;						     
			if( KioV.RegStartCnt > Iprm.RegStartFilter )	 
			{
				KioV.RegOn = TRUE;							 
			}
			else
			{
				KioV.RegStartCnt++;							 
			}
		}
		else
		{
			KioV.RegStartCnt = 0;						     
			if( BinK.DcVolt < Iprm.RegOffLevel )		     
			{
				if( KioV.RegStopCnt > Iprm.RegStopFilter )	 
				{
					KioV.RegOn = FALSE;					     
				}
				else
				{
					KioV.RegStopCnt++;					     
				}
			}
		}
  
  
  
  
 		if( (KioV.RegOn) && (!Iprm.f.Dcbus) &&(!KioV.f.RegAlmMotStop) )
		{
            KioV.RegDuty ++;
             if( KioV.RegDuty >= 5 )
            {
                KioV.RegDuty = 0;
            }
             if( KioV.RegDuty < 4 )
            {
                if( Prm.regonlvl == 0 )
                {
                    BKOff();
                    KpiSetParamError( &pndef_regonlvl ); 
                }
                else
                {
                    BKOn();							              
                }
                 if( KioV.RegOn )
                {
                    KioV.RegOnCount[0] += 2;				   
                }
            }
            else if( KioV.RegDuty < 5 )
            {
                BKOff();
            }
 		}
		else
		{
            BKOff();            						     
            KioV.RegDuty = 0;
		}
		return;
}
