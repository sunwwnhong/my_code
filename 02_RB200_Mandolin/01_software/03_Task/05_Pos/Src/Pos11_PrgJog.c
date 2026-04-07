  
  
  
  
  
 #include "Main.h"
 
PJOGV	PJogV;
PCMKPV	PJogPcmk;
 #define		LMTLOWSPEED	200                           
  
  
  
void	PrgJogReset( void )
{
	PJogV.Var.AbsPosCmd = 0;
	MlibResetSHORTMemory( &PJogPcmk.V, sizeof( PJogPcmk.V ) );
}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
void CpxPrgJogPosSequence( void )
{
  
  
    if( BoutV.CtrlMode.us[0] != CTRLMODE_PJOG )
    {
        return;
    }
  
  
     if( Alm.f.AlmFlag || CoutV.f.Sv.HwbbState || !CoutV.f.Seq.MainPowerOn ||
        ((PJogV.Var.State == PJOG_START) && (CoutV.f.Sv.Ot)) )
    {
        PJogV.Var.SeqPtr = 7;
    }
    else if( PJogV.Var.RoutCmd == PJOGCMD_ABORT )                                
    {
        PJogV.Var.SeqPtr = 6;
    }
    else if( (PJogV.Var.State == PJOG_START) && (!CoutV.f.Sv.BaseEnable) )       
    {
        PJogV.Var.SeqPtr = 6;
    }
     if( PJogV.Var.RoutCmd == PJOGCMD_INIT )
    {
        PJogV.Var.SeqPtr = 0;
        PJogV.Var.CoutCmd = PJOGCMD_INIT;
        PJogV.Var.State = PJOG_INIT;
    }
  
  
    switch ( PJogV.Var.SeqPtr )
    {
  
 		case 0 :
            if( PJogV.Var.RoutCmd == PJOGCMD_START && CoutV.f.Sv.BaseEnable )
			{
				PJogV.Var.MCntr = 0;
				KpiRstLongTimer(&PJogV.Var.TimeWork);
 				if( (PJogV.Cnst.MTimes == 0) && ((PJogV.Cnst.Pattern == 2) || (PJogV.Cnst.Pattern == 3)) )
				{
					PJogV.Var.SeqPtr = 7;
				}
				else
				{
					PJogV.Var.SeqPtr = 1;
				}
 				PJogV.Var.State = PJOG_START;
			}
			break;
  
         case 1 :
            if( KpiGetLongTimer(&PJogV.Var.TimeWork) >= (ULONG)PJogV.Cnst.WaitTime )
			{
				PrgJogReset();
				PJogV.Var.CoutCmd = PJOGCMD_START;
				if( PJogV.Cnst.Pattern & 0x01 )
					PJogV.Var.AbsPosCmd = -PJogV.Cnst.Distance;              
				else
					PJogV.Var.AbsPosCmd = PJogV.Cnst.Distance;               
				PJogV.Var.SeqPtr = 2;
			}
			break;
  
 		case 2 :
          if( PJogPcmk.V.calendf )         
				PJogV.Var.SeqPtr = 3;
			break;
  
 		case 3 :
			if( (++PJogV.Var.MCntr >= PJogV.Cnst.MTimes) && (PJogV.Cnst.MTimes != 0) )
			{
				PJogV.Var.SeqPtr = 5;                                
			}
			else
			{
				KpiRstLongTimer(&PJogV.Var.TimeWork);                
				PJogV.Var.SeqPtr = 4;                                
			}
			break;
  
         case 4 :
			if( KpiGetLongTimer(&PJogV.Var.TimeWork) >= (ULONG)PJogV.Cnst.WaitTime )
			{
				switch ( PJogV.Cnst.Pattern )
				{
                      
 					case 0 :
						PJogV.Var.AbsPosCmd += PJogV.Cnst.Distance;
						break;
                      
 					case 1 :
						PJogV.Var.AbsPosCmd -= PJogV.Cnst.Distance;
						break;
					case 2 :
						if( PJogV.Var.MCntr < (PJogV.Cnst.MTimes>>1) )
							PJogV.Var.AbsPosCmd += PJogV.Cnst.Distance;
						else
							PJogV.Var.AbsPosCmd -= PJogV.Cnst.Distance;
						break;
					case 3 :
						if( PJogV.Var.MCntr < (PJogV.Cnst.MTimes>>1) )
							PJogV.Var.AbsPosCmd -= PJogV.Cnst.Distance;
						else
							PJogV.Var.AbsPosCmd += PJogV.Cnst.Distance;
						break;
					case 4 :
						if( PJogV.Var.MCntr & 0x01 )
							PJogV.Var.AbsPosCmd -= PJogV.Cnst.Distance;
						else
							PJogV.Var.AbsPosCmd += PJogV.Cnst.Distance;
						break;
					case 5 :
						if( PJogV.Var.MCntr & 0x01 )
							PJogV.Var.AbsPosCmd += PJogV.Cnst.Distance;
						else
							PJogV.Var.AbsPosCmd -= PJogV.Cnst.Distance;
						break;
					default :
						break;
				}
                  
 				if( PJogV.Cnst.Pattern < 6 )
					PJogV.Var.SeqPtr = 2;
				else
					PJogV.Var.SeqPtr = 5;
 			}
			break;            
 		case 5 :	 
			PJogV.Var.State = PJOG_END;
			PJogV.Var.CoutCmd = PJOGCMD_INIT;
			PJogV.Var.SeqPtr = 0;
			break;
 		case 6 :	 
			PrgJogReset();			 
			PJogV.Var.CoutCmd = PJOGCMD_ABORT;
			PJogV.Var.State = PJOG_ABORT;
			PJogV.Var.SeqPtr = 0;
			break;
 		case 7 :	 
			PrgJogReset();			 
			PJogV.Var.CoutCmd = PJOGCMD_ABORT;
			PJogV.Var.State = PJOG_ERROR;
			PJogV.Var.SeqPtr = 0;
			break;
 		default :
			break;
     }
     OpeReg.PjogState = (PJogV.Var.State & 0x0F);	           
}
 
  
  
 void PcalPjogSw( void )
{
      
 	if( PJogV.Var.State == PJOG_START )
        PJogV.Var.RoutCmd = PJOGCMD_ABORT;
      
      
	PJogV.Cnst.Pattern = (CHAR) ( Prm.pjogsw & 0x000F );
      
      
	PJogV.Cnst.RevDir = ( PJogV.Cnst.Pattern & 0x01 )? TRUE : FALSE;
      
      
	PJogV.Cnst.MTimes = ( PJogV.Cnst.Pattern < 2 )? Prm.pjognum : ( Prm.pjognum << 1 );
}
  
  
  
void PcalPjogDistance( void )
{
	if( PJogV.Var.State == PJOG_START )
        PJogV.Var.RoutCmd = PJOGCMD_ABORT;
	PJogV.Cnst.Distance = ((ULONG)Prm.pjogdisth << 16) + Prm.pjogdistl;
}
  
  
  
void PcalPjogRotspd( void )
{ 
LONG	PjogSpdP1;
LONG	PjogSpdP2;
LONG	kx1, sx1;
LONG	kx2;
 	if( Kprm.AmpType == AMPTYPE_ROTARY )
	{
		PjogSpdP1 = 10UL * Prm.pjogrotspd;
 		if( PJogV.Var.State == PJOG_START )
            PJogV.Var.RoutCmd = PJOGCMD_ABORT;
          
 		PJogV.Cnst.MaxSpd = KpiSpeedLevelCal( PjogSpdP1, 0 );
          
          
		PJogV.Cnst.AccTime = ( Prm.pjogacctm == 0 )? 2000UL : ( Prm.pjogacctm * 1000UL );    
        PJogV.Cnst.DecTime = ( Prm.pjogacctm == 0 )? 2000UL : ( Prm.pjogacctm * 1000UL );    
		MlibPcalaPcmdMaker( PJogV.Cnst.MaxSpd,               
                           PJogV.Cnst.AccTime,               
                           PJogV.Cnst.DecTime,               
                           Iprm.SvCycleUs,                   
                           &PJogPcmk.P );
          
          
 		kx1 = MlibScalKxgain( Iprm.Egear.a, 100, Iprm.Egear.b, &sx1, -1 );
        kx2 = MlibPcalKxgain( Bprm.XfbPulse1, PjogSpdP1, 60UL * 10000UL, NULL, -24 );
		PjogSpdP2 = MlibScalKskskx( kx1, kx2, 1, NULL, -24 );
		if( PjogSpdP2 < LMTLOWSPEED )
		{
			PJogV.Cnst.PrmUnMatch = TRUE;
		}
		else
		{
			PJogV.Cnst.PrmUnMatch = FALSE;
		}
	}
	return;
}
  
  
  
void PcalPjogAcctime( void )
{
	if( PJogV.Var.State == PJOG_START )
        PJogV.Var.RoutCmd = PJOGCMD_ABORT;
	PJogV.Cnst.AccTime = ( Prm.pjogacctm == 0 )? 2000 : ( Prm.pjogacctm * 1000UL );
 	MlibPcalaPcmdMaker( PJogV.Cnst.MaxSpd, PJogV.Cnst.AccTime, PJogV.Cnst.AccTime, Iprm.SvCycleUs, &PJogPcmk.P );
	return;
}
  
  
  
void PcalPjogWaitTime( void )
{
	if( PJogV.Var.State == PJOG_START )
        PJogV.Var.RoutCmd = PJOGCMD_ABORT;
	if( Prm.pjogwaittm < 2 )
        PJogV.Cnst.WaitTime = 0;
	else
        PJogV.Cnst.WaitTime = Prm.pjogwaittm - 2;		 
}
  
  
  
void PcalPjogNum( void )
{
	if( PJogV.Var.State == PJOG_START )
        PJogV.Var.RoutCmd = PJOGCMD_ABORT;
	PJogV.Cnst.MTimes = ( PJogV.Cnst.Pattern < 2 )? Prm.pjognum : ( Prm.pjognum << 1 );
}
  
  
  
  
  
  
 void	IprmcalPrgJog( void )
{
		MlibIpcalPcmdMaker( Iprm.PcmdOvrSpd, Bprm.NorMaxSpd, Bprm.NorOvrSpd, FALSE, &PJogPcmk.P );
		if( Iprm.PcmdOvrSpd == 0x7FFFFF )
		{
			PJogV.Cnst.PrmUnMatch2 = TRUE;
		}
        else
        {
			PJogV.Cnst.PrmUnMatch2 = FALSE;        
        }
		return;
}
