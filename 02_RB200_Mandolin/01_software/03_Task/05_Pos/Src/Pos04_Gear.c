  
  
  
  
  
 #include "Main.h"
 
  
  
 void	IprmcalElectronicGear( void )
{
ULONG	Rata;
ULONG	Ratb;
  
 		Rata = ULONGOF( Prm.rata2l, Prm.rata2h );                        
		Ratb = ULONGOF( Prm.ratb2l, Prm.ratb2h );                        
         if( Ratb == 0 )
        {
            Ratb = MencP.PulseNo;
        }
 		MlibPcalKegear( Rata, Ratb, &Iprm.Egear );
 		MlibPcalKegear( 1, 1, &Iprm.Egear0 );
 		return;
}
  
  
  
void KpxEgearCheck( void )
{
ULONG	Rata;
ULONG	Ratb;
 double Ratio = 0.0f;
  
  
        if( BinV.f.BaseEnable == 0 )
            return;
  
  
		Rata = ULONGOF( Prm.rata2l, Prm.rata2h );                        
		Ratb = ULONGOF( Prm.ratb2l, Prm.ratb2h );                        
         if( Ratb == 0 )
        {
            Ratb = MencP.PulseNo;
        }
         Ratio = (float)Ratb / (float)Rata;
         if( Ratio > 64000.0 || Ratio < 0.001 )
        {
             KPI_ALARMSET( ALM_GEAR );
             return;
        }
        return;
}
  
  
  
void KpxEgearCoeffDeal( void )
{
    IprmcalElectronicGear();                                     
      
     IprmcalUnitTransFacter();
    PcalPcmdExpFilBias( );
    PcalBasePositionPControl( Prm.posgn, 1 );
    PcalBasePositionPControl( Prm.posgn2, 2 );
    PcalTuningLessOnePrmCalc( );
    PcalPjogRotspd( );
    IprmcalPcmdOvrSpd();
    IprmcalPrgJog( );
     MencP.FirstFlag = 0;
}
