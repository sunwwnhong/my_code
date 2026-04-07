  
  
  
  
  
 #include "Main.h"
 
#define	AVFILCALCYCLE	KPI_SBCYCLENS			     
#define	C10POW9			1000000000				     
#define	MAXOMEGA2		(127323954/AVFILCALCYCLE)	 
#define	SUMX_LIM		0x3FFFFFFF				     
  
  
  
  
 typedef	struct	{
		UCHAR	FilSel;							     
		UCHAR	FilChgDisable;					     
		UCHAR	FilStop;						     
		UCHAR	SpareByte[1];					     
} FILMNG;
  
 typedef	struct	{								     
		struct	{								     
		LONG	Kf[2];								 
		LONG	Pbias[2];							 
		} P;
 		struct	{								     
		LONG	Filo;								 
		PEXFV	Pexfvar;							 
		} V;
} EXPFIL;
  
  
typedef	struct	{								     
		LONG	Kff1;								 
		LONG	Kff2;								 
		LONG	Kff3;								 
		UCHAR	enable;								 
} AVFFP;
typedef	struct	{								     
		AVFFP	P;									 
		AVFFP	Pexe;								 
 		struct {								     
		LONG	rem1;								 
		LONG	rem2;								 
		LONG	rem3;								 
		LONG	wkbf1;								 
		LONG	wkbf2;								 
		LONG	FilioErr[2];						 
		LONG	Buf;								 
		LONG	Filo;								 
		} V;
} AVFFFIL;
  
 typedef	struct	{								     
		LONG	Kff1;								 
		LONG	Kff2;								 
		LONG	Kff3;								 
} ABVCP;
typedef	struct	{								     
		ABVCP	P;									 
 		struct {								     
		LONG	Status;								 
		LONG	rem1;								 
		LONG	rem2;								 
		LONG	rem3;								 
		LONG	wkbf1;								 
		LONG	wkbf2;								 
		LONG	FilioErr[2];						 
		LONG	FiliSum[2];							 
		LONG	Buf;								 
		LONG	Filo;								 
		} V;
} ABVCTRL;
  
 #define INPTSHAPFIL_BUFNUM	256					     
  
 typedef	struct	{								     
		LONG	PmafNum;							 
		LONG	ImafSft;							 
		LONG	Coeff;								 
		UCHAR	enable;								 
} INPTSHPP;
typedef	struct	{								     
		INPTSHPP	P;								 
		INPTSHPP	Pexe;							 
 		struct	{								     
		LONG	pcmdinx;							 
		LONG	pcmdiny;							 
		LONG	SigmaIdx;							 
		LONG	Filo;								 
		PMAFV	Pmafvar;							 
		PIMFV	Pimfvar;							 
		} V;
		LONG	Inbuf[ INPTSHAPFIL_BUFNUM ];
} INPTSHPFIL;
 #define MAFIL_BUFNUM		256					     
 FILMNG		FilMng;								     
EXPFIL		ExpFil;								     
MAFIL		MaFil;								     
LONG		Pmafbuf[ MAFIL_BUFNUM ];			     
AVFFFIL		Avff;								     
ABVCTRL		Abv;								     
#if( INPUTSHAPING_FIL != 0 )
INPTSHPFIL	InptShp;							     
#endif
  
  
  
void	BpxInitPcmdFilter( void )
{
    MlibResetLONGMemory( &FilMng,   (sizeof(FilMng)) / 2   );
    MlibResetLONGMemory( &ExpFil.V, (sizeof(ExpFil.V)) / 2 );
    MlibResetLONGMemory( &MaFil.V,  (sizeof(MaFil.V)) / 2  );
    MlibResetLONGMemory( &Avff.V,   (sizeof(Avff.V)) / 2   );
    MlibResetLONGMemory( &Abv.V,    (sizeof(Abv.V)) / 2    );
#if( INPUTSHAPING_FIL != 0 )
    MlibResetLONGMemory( &InptShp.V,(sizeof(InptShp.V)) / 2 );
	InptShp.Pexe = InptShp.P;
#endif
    ExpFil.P.Kf[0] = ExpFil.P.Kf[1];
    ExpFil.P.Pbias[0] = ExpFil.P.Pbias[1];
    MaFil.P.PmafNum[0] = MaFil.P.PmafNum[1];
    MaFil.P.ImafSft[0] = MaFil.P.ImafSft[1];
    Avff.Pexe = Avff.P;
	return;
}
 
  
  
 void	PcalPcmdExpFilBias( void )
{
LONG	kx;
LONG	sx;
		kx = MlibScalKxgain( Prm.expbias1, Iprm.Egear.b, Iprm.Egear.a, &sx, 0 );
		kx = MlibPcalKxgain( kx, Iprm.SvCycleUs, 1000000, &sx, 0 );
		ExpFil.P.Pbias[1] = (sx<=31)? (kx>>sx) : 0;
		return;
 }
  
  
  
void	PcalPcmdExpFilter( USHORT PrmTime, LONG Flag )
{
LONG	Unit = ( !Flag ) ? 10 : 100;
LONG	PrmTimeUs = PrmTime * Unit;
LONG	kx,sx;		 
 
  
 #if 0
        if( Kprm.f.EtherCATNet == 1 )
        {
            PrmTimeUs += ( EtherCatSyncTimeus );
        }
        else if( Kprm.f.CanOpenNet == 1 )
        {
            PrmTimeUs += ( CanOpenSyncTimeus );
        }
        else
        {
            ;
        }
#endif
  
  
  
  
  
  
  
  
 		kx = MlibScalKxkxks( SUMX_LIM, 100, Bprm.KMotSpdConv, &sx, 0 );
		kx = MlibPcalKxgain( kx, 1, Bprm.MaxVel*100, &sx, -24 );
		PrmTimeUs = ( kx < PrmTimeUs ) ? kx : PrmTimeUs ;
 		if( PrmTimeUs <= Iprm.SvCycleUs )		 
		{
			ExpFil.P.Kf[1] = 1;
		}
		else									 
		{
			ExpFil.P.Kf[1] = MlibScalKxgain( Iprm.SvCycleUs, 1, PrmTimeUs, NULL, 24 );
		}
  
		return;
 }
  
  
  
void	PcalPcmdMoveAvergeFilter( USHORT PrmTime, LONG Flag )
{
LONG	i,x;
LONG	MaTimeUs;
        MaTimeUs= (Flag==0)? (10UL * PrmTime) : (100UL * PrmTime);		 
  
  
        if( Kprm.f.EtherCATNet == 1 )
        {
            MaTimeUs += EtherCatSyncTimeus;
        }
        else if( Kprm.f.CanOpenNet == 1 )
        {
            MaTimeUs += CanOpenSyncTimeus;
        }
        else
        {
            ;
        }
  
  
        if( MaTimeUs <= ((LONG)MAFIL_BUFNUM * Iprm.SvCycleUs) )        
		{
			MaFil.P.ImafSft[1] = 0;
			MaFil.P.PmafNum[1] = MaTimeUs / Iprm.SvCycleUs;
              
              
			if( MaFil.P.PmafNum[1] < 1 )
            {
                MaFil.P.PmafNum[1] = 1;
            }
		}
  
  
  
		else
		{
			x = (LONG)MAFIL_BUFNUM * Iprm.SvCycleUs;    		 
			for( i=1; i < 5; i++ )								 
			{													 
				if( (x << i) >= MaTimeUs ){ break;}				 
			}													 
 			MaFil.P.ImafSft[1] = (UCHAR)i;
			MaFil.P.PmafNum[1] = MaTimeUs / (Iprm.SvCycleUs << i);
			if( MaFil.P.PmafNum[1] > MAFIL_BUFNUM ){ MaFil.P.PmafNum[1] = MAFIL_BUFNUM;}
		}
 		return;
}
  
  
  
LONG	LpxLongMaFilter( LONG pcmdin )
{
LONG	pcmdfilo;
  
  
		MaFil.V.pcmdinx += pcmdin;
		if( ++MaFil.V.index >= (1 << MaFil.P.ImafSft[0]) )
		{
			MaFil.V.pcmdiny = MlibPcmdMafil(
								MaFil.V.pcmdinx,
								MaFil.P.PmafNum[0],
								&MaFil.V.Pmafvar,
								&Pmafbuf[0]			);
 			MaFil.V.index   = 0;
			MaFil.V.pcmdinx = 0;
		}
  
 		pcmdfilo = MlibPcmdImafil(
					MaFil.V.pcmdiny,
					MaFil.P.ImafSft[0],
					MaFil.V.index,
					&MaFil.V.Pimfvar	);
 		return( pcmdfilo );
 }
 
  
  
 void	PcalPcmdAvffFilter( void )
{
AVFFP	wrkp;
LONG	u1;
LONG	s, sx;
LONG	kx;
LONG	wk;
LONG	omega2;
LONG	scantime = AVFILCALCYCLE;							 
 
  
         if( (Prm.mdlsw & 0x0F) == 0x0000 )
        {
            wrkp.enable = Prm.ff_frq != 2000 ? TRUE : FALSE;
        }
        else
        {
            wrkp.enable = Gprm.f.AvffFilter;
        }
		u1 = Prm.ff_fil;
 
		wk = (LONG)Prm.ff_frq * (LONG)Prm.ff_fil;			             
		omega2 = MlibMIN( wk, ((ULONG)MAXOMEGA2 * 1000UL) );			 
 
		wrkp.Kff1 = MlibScalKxgain( u1 * u1, 1, 10000, NULL, 24 );
 
		kx = MlibScalKxgain( omega2, scantime, C10POW9, &s , 0 );
		kx = MlibPcalKxgain( kx, 1, 1000000000, &s , 0 );
		sx = s;
 		wrkp.Kff2 = MlibPcalKxgain( kx, 3141593, 1, &s , 24 );			 
		wrkp.Kff3 = MlibPcalKxgain( kx, 12566371, 1, &sx , 24 );		 
  
  
		KPI_DI();		 
		Avff.P = wrkp;
		KPI_EI();		 
 		return;
}
 
  
  
 void PcalPcmdAvffFilterSel( void )
{
UCHAR	ucwk;
 		ucwk = (Prm.mdlsw >> 4) & 0x0F;
 		switch( ucwk )
		{
            case 0x00:						     
            case 0x01:
                Gprm.f.AvffFilter = FALSE;
                break;
            case 0x02:						     
                Gprm.f.AvffFilter = TRUE;
                break;
            default :	KpiSetParamError( &pndef_mdlsw ); break;
		}
 		 
 		 
		ucwk = Prm.mdlsw & 0x0F;
		switch( ucwk )
		{
            case 0x00:						     
                Gprm.f.AvffFilter = FALSE;	     
                break;
		}
 		PcalPcmdAvffFilter();		             
 		return;
 }
 #if( VIBSUPPRESS_FIL2 != 0 )
  
  
  
  
  
  
 LONG	BpxPcmdAvffFilter( LONG dPcmd )
{
LONG	AvffFili;
LONG	AvffFilo;
LONG	x1,x2,x3;
LONG	wk = 0;
  
  
	if(BoutV.CtrlModeLst.b.cm != CTRLMODE_POS)		 
	{
		Avff.Pexe.enable = 0;						 
	}
  
  
    if((dPcmd == 0)									 
        && (Avff.V.Buf == 0))						 
    {
        Avff.Pexe = Avff.P;							 
    }
     AvffFili = dPcmd;								 
  
  
	if( Avff.Pexe.enable )
	{	 
		x1 = MlibPfbkxremNolim( AvffFili, Avff.Pexe.Kff1, & Avff.V.rem1 );
		x2 = MlibPfbkxremNolim( Avff.V.wkbf1, Avff.Pexe.Kff2, &Avff.V.rem2 );
		x3 = MlibPfbkxremNolim( Avff.V.wkbf2, Avff.Pexe.Kff3, &Avff.V.rem3 );
 		Avff.V.wkbf1 += (x1 - x3 - AvffFili);
		Avff.V.wkbf2 += (x1 - x3 + x2);
 		AvffFilo = x1 - x3;							 
  
  
		Avff.V.Buf = MlibPerrcalx( AvffFili, AvffFilo, Avff.V.FilioErr );
		if( Avff.V.Buf != 0 )
        {
            BoutV.f.Sv.Den = FALSE;                  
        }
  
  
		if( (AvffFilo == 0)	&& (Avff.V.wkbf1 == 0) && (Avff.V.wkbf2 == 0) )	
		{									 
		    MlibResetSHORTMemory( &Avff.V, sizeof(Avff.V) );		 
		}
  
  
		wk += AvffFilo;											 
		Avff.V.Filo = wk;										 
	}
	else
	{	 
		wk = AvffFili;											 
		Avff.V.Filo = wk;
	}
	return( wk );
}
 #endif
 
  
  
  
  
  
  
 LONG	PcmdMoveAvergeFilter( LONG pcmdin )			 
{
  
  
		if( MaFil.P.ImafSft[0] == 0 )
		{
			MaFil.V.Filo = MlibPcmdMafil(				 
								pcmdin,
								MaFil.P.PmafNum[0],
								&MaFil.V.Pmafvar,
								&Pmafbuf[0]			);
		}
		else
		{
 			MaFil.V.Filo = LpxLongMaFilter( pcmdin );	 
		}
  
 		if( (pcmdin | MaFil.V.pcmdinx | MaFil.V.Pmafvar.zcntx | MaFil.V.Pimfvar.zcntx) == 0 )
		{
			MaFil.P.PmafNum[0] = MaFil.P.PmafNum[1];	 
			MaFil.P.ImafSft[0] = MaFil.P.ImafSft[1];	 
		}
		else
		{
			BoutV.f.Sv.Den = FALSE;						 
			FilMng.FilChgDisable = TRUE;				 
		}
 		return( MaFil.V.Filo );
 }
  
  
  
LONG	PcmdExpFilter( LONG pcmdin )				 
{
          
          
		if ( ( pcmdin == 0 ) && ( PosMngV.PosErrA.per32s == 0 ) )
		{												 
			ExpFil.P.Kf[0] = ExpFil.P.Kf[1];			 
			ExpFil.P.Pbias[0] = ExpFil.P.Pbias[1];		 
			if( ExpFil.P.Kf[0] == 1 )					 
			{
				ExpFil.P.Pbias[0] = 0;
			}
		}
		else
		{
			FilMng.FilChgDisable = TRUE;				 
		}
          
 		ExpFil.V.Pexfvar.sumx = ExpFil.V.Pexfvar.sumx + pcmdin;
		if ( MlibAbs32( ExpFil.V.Pexfvar.sumx ) > ExpFil.P.Pbias[0] )
		{
			ExpFil.V.Filo = MlibMulkxBiasrem( ExpFil.V.Pexfvar.sumx,
											  ExpFil.P.Kf[0],
											 &ExpFil.V.Pexfvar.remx,
											  ExpFil.P.Pbias[0]			);
		}
		else
		{
			ExpFil.V.Filo = ExpFil.V.Pexfvar.sumx;
		}
		ExpFil.V.Pexfvar.sumx = ExpFil.V.Pexfvar.sumx - ExpFil.V.Filo;
          
 		if ( ( pcmdin != 0 ) || ( ExpFil.V.Pexfvar.sumx != 0 ) )
		{
			BoutV.f.Sv.Den = FALSE;						 
		}
 		return( ExpFil.V.Filo );
 }
 
  
  
 LONG	BpxPcmdFilter( LONG pcmdin )
{
LONG	pcmdout;
LONG	orgpcmdin;
  
  
		if ( FilMng.FilStop == TRUE )
		{
			orgpcmdin = pcmdin;
			pcmdin = 0;
		}
		else
		{
			orgpcmdin = 0;
		}
  
 		pcmdout = PcmdMoveAvergeFilter( pcmdin);
  
          
		pcmdout = PcmdExpFilter( pcmdout );
 		pcmdout += orgpcmdin;
		return( pcmdout );
}
 
 
  
  
 void	BpiStopPcmdFilter( void )
{
		FilMng.FilStop = TRUE;
		return;
}
 
  
  
 void	BpiRunPcmdFilter( void )
{
		FilMng.FilStop = FALSE;
		return;
}
