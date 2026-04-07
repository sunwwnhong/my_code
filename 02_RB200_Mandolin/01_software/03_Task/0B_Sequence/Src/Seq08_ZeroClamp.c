  
  
 /****************************************************************************************************
*文件名:Seq08_ZeroClamp.c
*创建时间:2018.05.22
*版本说明:V1.0
*功能描述:零速钳位
*****************************************************************************************************/
#include "Main.h"
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 #define	ZCLAMP_MARGIN	12710						 
 void	LpxZeroClampSequence( void )
{
LONG	lwk;
  
  
  
  
  
  
          
		if( CinV.f.Sv.Zclamp && (BoutV.CtrlMode.b.cm == CTRLMODE_SPD) && (!CoutK.f.RndSvControl) )
		{
			lwk = MlibABS( BoutV.SpdRefo );
			if( lwk < ( Gprm.ZclampSpdLevel + ZCLAMP_MARGIN) )
			{
				if( lwk < Gprm.ZclampSpdLevel )
				{
					SvSeqV.f.ZcReqSignal = TRUE;
				}
			}
			else
			{
				SvSeqV.f.ZcReqSignal = FALSE;
			}
		}
		else
		{
			SvSeqV.f.ZcReqSignal = FALSE;
		}
  
  
	if( (SvSeqV.f.ZcReqSignal) ||				 
		(TblExeV.TblZmd.b.zm == CTRLMODE_ZCLMP)) 
	{
		if( (CoutV.f.Sv.MotStop) ||				 
			(SvSeqV.f.ZcZeroClamp))				 
		{
			SvSeqV.f.ZcZeroClamp = TRUE ;		 
			SvSeqV.f.ZcZeroStop = FALSE ;		 
		}
		else
		{
			SvSeqV.f.ZcZeroClamp = FALSE ;		 
			SvSeqV.f.ZcZeroStop = TRUE ;		 
		}
	}
	else
	{
			SvSeqV.f.ZcZeroClamp = FALSE ;		 
			SvSeqV.f.ZcZeroStop = FALSE ;		 
	}
 
    return;
 }
