  
  
  
  
  
 #include "Main.h"
 
  
  
  
 
  
 typedef	struct	{
		LONG	UvTrqLmt;					 
		USHORT	UvTrqLmtWait;				 
} TRQLMT;
 TRQLMT		TrqLmt;							 
 
  
  
 LONG	LpxUvTrqLmtControl( LONG );			 
 
void	BpxInitTorqueLimitControl( void );
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
void	BpxTorqueLimitControl( void )
{
LONG	FwTrqLmt    = 0;
LONG	RvTrqLmt    = 0;
LONG	UvTrqLmt    = 0;
LONG    HFwTrqLmt   = 0;
LONG    HRvTrqLmt   = 0;
  
  
		UvTrqLmt = LpxUvTrqLmtControl( CoutV.f.Sv.OtTrqLimit );
  
 		if( CoutV.f.Sv.OtTrqLimit == 1 )
		{
			FwTrqLmt = Gprm.EstopTrqLmt;
			RvTrqLmt = Gprm.EstopTrqLmt;
            BinV.f.Sv.PossErr = 0;
		}
        else if( CinV.f.Seq.ServoOffDec == 1 )
        {
			FwTrqLmt = Gprm.EstopTrqLmt;
			RvTrqLmt = Gprm.EstopTrqLmt;
            BinV.f.Sv.PossErr = 0;        
        }
  
 		else
		{
              
 			HFwTrqLmt = (BinV.f.Sv.TlimitSel) ? Gprm.RvIntTrqLmt : Gprm.FwIntTrqLmt; 
			HRvTrqLmt = HFwTrqLmt;
              
 			if( (BPI_GET_BASE_CTRLMODE() != CTRLMODE_TRQ) && (BPI_GET_BASE_CTRLMODE() != CTRLMODE_JOG) )
			{
                switch (Prm.torqlimt & 0x000F) 
                {
                      
                     case 0:
                    case 1:
                        FwTrqLmt = 0;
                        RvTrqLmt = 0;
                        BinV.f.Sv.PossErr = 0;
                        break;
                      
                     case 2:
                        FwTrqLmt = Gprm.FwIntTrqLmt;
                        RvTrqLmt = Gprm.FwIntTrqLmt;
                        BinV.f.Sv.PossErr = 0;
                        break;
                      
                     case 3:
                        FwTrqLmt = Gprm.FwIntTrqLmt;
                        RvTrqLmt = Gprm.RvIntTrqLmt;
                        BinV.f.Sv.PossErr = 0;
                        break;
                      
                     case 4:
                        FwTrqLmt = (BinV.f.Sv.TlimitSel)? Gprm.RvExtTrqLmt : Gprm.FwExtTrqLmt;
                        RvTrqLmt = FwTrqLmt;
                        BinV.f.Sv.PossErr = 0;
                        break;
                      
                     case 5:
                          
                          
                        if( PosMngV.dPcmda == 0 )
                        {
                            if( BinV.f.Sv.PossErr == 0 )
                            {
                                if( PosMngV.PosErrA.per32a <= Gprm.CoinLevel )
                                {
                                    BinV.f.Sv.PossErr = 1;
                                }
                                 FwTrqLmt = Gprm.FwIntTrqLmt;         
                                RvTrqLmt = FwTrqLmt;
                            }
                            else
                            {
                                FwTrqLmt = Gprm.RvIntTrqLmt;         
                                RvTrqLmt = FwTrqLmt;                       
                            }
                        }
                        else
                        {
                            BinV.f.Sv.PossErr = 0;
                              
                             FwTrqLmt = Gprm.FwIntTrqLmt;             
                            RvTrqLmt = FwTrqLmt;
                        }
                        if( ( PosMngV.PosErrA.per32a <= Gprm.CoinLevel ) && PosMngV.dPcmda == 0 )
                        {
                            FwTrqLmt = Gprm.RvIntTrqLmt;             
                            RvTrqLmt = FwTrqLmt;                       
                        }
                        else
                        {
                         }                    
                        break;
                     default:
                        FwTrqLmt = 0;
                        RvTrqLmt = 0;
                        BinV.f.Sv.PossErr = 0;
                        break;
                }
                  
                 if( Kprm.f.EtherCATNet == 1 )
                {
                      
                     FwTrqLmt = MlibMIN( Gprm.EthMaxPTorq,FwTrqLmt);
                    RvTrqLmt = MlibMIN( Gprm.EthMaxNTorq,RvTrqLmt);
                      
                     FwTrqLmt = MlibMIN( Gprm.EthMaxTorq,FwTrqLmt);
                    RvTrqLmt = MlibMIN( Gprm.EthMaxTorq,RvTrqLmt);
                }  
                else if( Kprm.f.CanOpenNet == 1 )
                {
                      
                     FwTrqLmt = MlibMIN( CanTorq.PosTorqLimt,FwTrqLmt);
                    RvTrqLmt = MlibMIN( CanTorq.NegTorqLimt,RvTrqLmt);
                      
                     FwTrqLmt = MlibMIN( CanTorq.MaxTorq,FwTrqLmt);
                    RvTrqLmt = MlibMIN( CanTorq.MaxTorq,RvTrqLmt);                
                }
                else
                {;}                
                  
                 FwTrqLmt = MlibMIN( FwTrqLmt, UvTrqLmt );
                RvTrqLmt = MlibMIN( RvTrqLmt, UvTrqLmt );
			}
            else
            {
                FwTrqLmt = MlibMIN( HFwTrqLmt,UvTrqLmt);
                RvTrqLmt = MlibMIN( HRvTrqLmt,UvTrqLmt);
                if( Kprm.f.EtherCATNet == 1 )
                {
                      
                     FwTrqLmt = MlibMIN( Gprm.EthMaxPTorq,FwTrqLmt);
                    RvTrqLmt = MlibMIN( Gprm.EthMaxNTorq,RvTrqLmt);
                      
                     FwTrqLmt = MlibMIN( Gprm.EthMaxTorq,FwTrqLmt);
                    RvTrqLmt = MlibMIN( Gprm.EthMaxTorq,RvTrqLmt);
                }
                else if( Kprm.f.CanOpenNet == 1 )
                {
                      
                     FwTrqLmt = MlibMIN( CanTorq.PosTorqLimt,FwTrqLmt);
                    RvTrqLmt = MlibMIN( CanTorq.NegTorqLimt,RvTrqLmt);
                      
                     FwTrqLmt = MlibMIN( CanTorq.MaxTorq,FwTrqLmt);
                    RvTrqLmt = MlibMIN( CanTorq.MaxTorq,RvTrqLmt);                
                }
                else
                {;}
            }
		}
  
 		BoutK.PosTrqLmt =  FwTrqLmt;					         
		BoutK.NegTrqLmt = -RvTrqLmt;					         
 #if(FLOAT_USE == 1)
        BoutK.PosTrqLmt_15000 = (LONG)( (float)BoutK.PosTrqLmt * 0.000894069672f );        
        BoutK.NegTrqLmt_15000 = (LONG)( (float)BoutK.NegTrqLmt * 0.000894069672f );        
#else
        BoutK.PosTrqLmt_15000 = MlibMulhigh32( BoutK.PosTrqLmt,  3840000 );        
        BoutK.NegTrqLmt_15000 = MlibMulhigh32( BoutK.NegTrqLmt,  3840000 );        
#endif
          
		return;
 }
  
  
  
void	BpxInitTorqueLimitControl( void )
{
    MlibResetSHORTMemory( &TrqLmt, sizeof( TrqLmt ) );
	return;
}
  
  
  
  
  
  
  
 #define		MAXTRQ_24BIT		0x1000000			 
 LONG	LpxUvTrqLmtControl( LONG OtTrqLmt )
{
		if ( (Iprm.f.UvTrqLmtCtrl == TRUE) && (OtTrqLmt == FALSE) )
		{
              
 			if ( KPI_WARNINGSTSCHK( WRN_UV ) == TRUE )
			{
				TrqLmt.UvTrqLmt = Gprm.UvTrqLmt;
 #if SVFSEL_NETIF_SCANA_CYCLE != 0 					 
				if( Iprm.f.CmdOpDeCycle625 )
				{
					TrqLmt.UvTrqLmtWait = KPI_SCANA_MS( Prm.UvTrqLmtOffFil );
				}
				else
#endif
 				{
					TrqLmt.UvTrqLmtWait = KPI_SCANB_MS( Prm.UvTrqLmtOffFil );				 
				}
			}
			else
			{
				if ( TrqLmt.UvTrqLmtWait == 0 )
				{
					TrqLmt.UvTrqLmt = MAXTRQ_24BIT;
				}
				else
				{
					TrqLmt.UvTrqLmtWait--;
					TrqLmt.UvTrqLmt += Gprm.DeltaUvTrqLmt;
				}
			}
		}
		else
		{
			TrqLmt.UvTrqLmt = MAXTRQ_24BIT;
			TrqLmt.UvTrqLmtWait = 0;
		}
		return TrqLmt.UvTrqLmt;
}
