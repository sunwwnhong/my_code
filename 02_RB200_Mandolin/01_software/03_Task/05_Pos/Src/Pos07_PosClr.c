  
  
  
  
  
 #include "Main.h"
 
BIOXV BioxV;
 
  
  
  
void	BpxEdgeClrSvcPositionManager( void )
{
  
 		BoutV.AmondPosCmd  = 0;								 
 		 
		MlibResetLONGMemory( &PosMngV.PosErrA, (sizeof(PosMngV.PosErrA)) / 2 );	 
		PosMngV.dPcmdEgear = 0;								 
		PosMngV.dPcmdEgrem = 0;								 
		PosMngV.dPcmda = 0;									 
		PosMngV.PosErr = 0;									 
		PosMngV.Per64[0] = 0;								 
		PosMngV.Per64[1] = 0;								 
		PosMngV.LastdPcmda = 0;								 
 #if ( SVFSEL_BLSH_COMMON_PROC )
		MlibResetLONGMemory( &BlshCmp.V, (sizeof(BlshCmp.V) / 2));	 
#endif
 		PosCtrl.V.PerIvar64[0] = 0;							 
		PosCtrl.V.PerIvar64[1] = 0;							 
		PosCtrl.V.LastPacOut = 0;							 
#if (FLOAT_USE == 1)
		PosCtrl.V.fdPFfFilo = 0.0f;                          
#else
		PosCtrl.V.dPFfFilo = 0;								 
#endif
		BoutV.dPosRefi = 0;									 
		BoutV.CompdPosRefi = 0;								 
		BoutV.CompdPcmda = 0;								 
  
  
		BpxInitPcmdFilter( );								 
#if( MODELFOLLOW_CTRL != 0 )
		BpxInitMfcModelControl( );							 
#endif
 		return;
 }
  
  
  
void BpxPerClrSignalProcedure( void )
{
 		 
 		BpxEdgeClrSvcPositionManager( );
 		return;
}
 
  
  
  
#define	DELAY_ALM_TO_COIN	KPI_SCANB_MS( 10 )
void PosClrDeal( void )
{
      
     BioxV.CLRStatus = BioxV.CLRStatus << 1;
    BioxV.CLRStatus &= 0x0003;
    if( BinV.f.Sv.PerClrSignal )
        BioxV.CLRStatus |= 0x01;
     if( Iprm.PerClrSigSel == 0x00 )                  
    {
        BinV.f.PerClrSignal = ( BinV.f.Sv.PerClrSignal )? TRUE : FALSE;
    }
     else if( Iprm.PerClrSigSel == 0x01 )             
    {
        BinV.f.PerClrSignal = ( BioxV.CLRStatus == 0x0001 ) ? TRUE : FALSE;
    }
     else if( Iprm.PerClrSigSel == 0x03 )             
    {
        BinV.f.PerClrSignal = ( BioxV.CLRStatus == 0x0002 ) ? TRUE : FALSE;
    }
     else                                             
    {
        BinV.f.PerClrSignal = ( BinV.f.Sv.PerClrSignal ) ? FALSE : TRUE;
    }
      
      
    if( Iprm.OtPErrorclr != 0 )
    {
        BinV.OTStatus = ( BinV.OTStatus << 1 ) & 0x03;
        if( CinV.f.Sv.Pot == TRUE || CinV.f.Sv.Not == TRUE )
        {
            BinV.OTStatus += 1;
        }
         if( BinV.OTStatus == 0x01 )
        {
            if( CinV.f.Sv.Pot == TRUE && PosMngV.PosErrA.per32s > 0 )
            {
                BinV.f.PerClrSignal = TRUE;
            }
            else if(  CinV.f.Sv.Not == TRUE && PosMngV.PosErrA.per32s < 0 )
            {
                BinV.f.PerClrSignal = TRUE;
            }
            else
            {}
        }
        else
        {
            BinV.f.PerClrSignal = FALSE;
        }
     }
  
  
  
  
    switch( Iprm.PerClrMode )
    {
        case 0x00:	 
            if( Alm.f.AlmFlag )						 
            {
                if( BioxV.DelayAlmToCoin > DELAY_ALM_TO_COIN )	 
                {
                    BinV.f.PerClrCmd = TRUE;		 
                }
                else
                {
                    BioxV.DelayAlmToCoin++;			 
                    BinV.f.PerClrCmd = (BinV.f.PerClrSignal)? TRUE : FALSE; 
                }
            }
            else if( CoutV.f.Sv.BBSvcRefClrReq )	 
            {
                BinV.f.PerClrCmd = TRUE;			 
                BioxV.DelayAlmToCoin = 0;			 
            }
            else									 
            {
                BinV.f.PerClrCmd = (BinV.f.PerClrSignal)? TRUE : FALSE;
                BioxV.DelayAlmToCoin = 0;			 
            }
            break;
 		case 0x01:	 
            BinV.f.PerClrCmd = (BinV.f.PerClrSignal)? TRUE : FALSE;
            break;
		case 0x02:	 
            if( Alm.f.AlmFlag )						 
            {
                if( BioxV.DelayAlmToCoin > DELAY_ALM_TO_COIN )	 
                {
                    BinV.f.PerClrCmd = TRUE;		 
                }
                else
                {
                    BioxV.DelayAlmToCoin++;			 
                    BinV.f.PerClrCmd = (BinV.f.PerClrSignal)? TRUE : FALSE; 
                }
            }
            else									 
            {
                BinV.f.PerClrCmd = (BinV.f.PerClrSignal)? TRUE : FALSE;
                BioxV.DelayAlmToCoin = 0;			 
            }
            break;
         case 0x03:	 
					BinV.f.PerClrCmd = FALSE;
					break;
 		default  :	 
					BinV.f.PerClrCmd = FALSE;
					break;
 		}
}
