  
  
  
  
  
 #include "Main.h"
 
  
  
  
LONG KpiTorqueLevelCal( LONG  Torque, LONG	LvlSel )
{
	LONG x;
 	if( LvlSel == 0 )        
	{
#if(FLOAT_USE == 1)
	    x = (float)Torque * Iprm.fKtrqlvl;               
#else
		x = MlibMulgain( Torque, Iprm.Ktrqlvl );         
#endif
	}
	else
	{
#if(FLOAT_USE == 1)
	    x = (float)Torque * Iprm.fKtrqlvls;              
#else
		x = MlibMulgain( Torque, Iprm.Ktrqlvls );        
#endif
	}
 	return ( x );
 }
 
  
  
 LONG KpiNorTorqueCal( LONG	Torque )
{
	LONG x;
 	x = MlibMulgain( Torque, Iprm.Knortrq );
	return ( x );
 }
  
  
 INT64 EtherCatTorCmd = 0;
LONG EtherCatTargetTorq = 0;
INT64 TorqRatio = 0;
UCHAR ETorFlag = 0;
LONG KpiEtherCatInputTrqRef(void)
{
LONG TorqCmd;
LONG Ratio = 0;
      
     Ratio = (LONG)u32TorqueSlope * 256 / 125;
     if( s8ModeofOP == 10 )                                           
    {
          
         TorqCmd = s16TargTorq + s16TorqueOffset;
    }
    else if( s8ModeofOP == 4 )                                       
    {
          
         if( BinV.f.BaseEnable )
        {
              
             if( u32TorqueSlope == 0 )                               
                u32TorqueSlope = 1;
              
             if( s16TargTorq > 5000 )        EtherCatTargetTorq = 163840000;
            else if( s16TargTorq < -5000 )  EtherCatTargetTorq = -163840000;
            else EtherCatTargetTorq = (LONG)s16TargTorq * 32768;        
 			if( EtherCatTorCmd <=  EtherCatTargetTorq )
            {
                EtherCatTorCmd += Ratio;
                if( EtherCatTorCmd >  EtherCatTargetTorq ) EtherCatTorCmd = EtherCatTargetTorq;
            }
            else
            {
                EtherCatTorCmd -= Ratio;
                if( EtherCatTorCmd <  EtherCatTargetTorq ) EtherCatTorCmd = EtherCatTargetTorq;
            }
              
              
            TorqCmd = (SHORT)( EtherCatTorCmd >> 15 );
        }
        else
        {
            EtherCatTorCmd = 0;
            TorqCmd = 0;
        }
    }
    else
    {
        TorqCmd = 0;
    }
      
    LONG x = MlibMulgain( CinK.TrqRefMon, Iprm.Kmontrq );
     x = s16TargTorq - x * 10;
     if( x < 10 &&  x > - 10 )            
    {
        ETorFlag = 1;
    }
    else
    {
        ETorFlag = 0;
    }
      
    TorqCmd = KpiTorqueLevelCal( TorqCmd * 10, 0 );
      
     if( (u8Polarity & 0x20) == 0x20 )
    {
        TorqCmd = -TorqCmd;
    }
     return TorqCmd;
}
