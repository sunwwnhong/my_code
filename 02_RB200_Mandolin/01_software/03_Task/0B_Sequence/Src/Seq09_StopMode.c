  
  
 /****************************************************************************************************
*文件名:Seq09_StopMode.c
*创建时间:2018.05.22
*版本说明:V1.0
*功能描述:停机模式控制部分
*****************************************************************************************************/
#include "Main.h"
 
 
  
  
  
  
  
 #define	OTDBOP_NONE		0x00
#define	OTDBOP_DEF		0x01
#define	OTDBOP_FREE		0x02
void	LpxStopModeManager( void )
{
      
     if( SvSeqV.AlmStopMode > STOPMODE_ZEROSTOP )	     
    {
        CoutV.StopMode = SvSeqV.AlmStopMode;		     
    }
     else if( CoutV.f.Sv.BkBeReq == FALSE )			     
    {
        CoutV.StopMode = Iprm.StopMode;				     
    }
      
     else if( (CoutV.f.Sv.OtBeReq == FALSE) && (SvSeqV.OtDbopReq == OTDBOP_DEF) )
    {												     
        if( Iprm.StopMode == STOPMODE_DBSTOPDB)		     
        {											     
            CoutV.StopMode = STOPMODE_DBSTOPFR;		     
        }
        else
        {
            CoutV.StopMode = Iprm.StopMode;			     
        }
    }
      
    else if( (CoutV.f.Sv.OtBeReq == FALSE) && (SvSeqV.OtDbopReq == OTDBOP_FREE) )
    {												     
        CoutV.StopMode = STOPMODE_FREERUN;			     
    }
 	 
    else if( SvSeqV.f.AlmZeroStop )					     
    {
        CoutV.StopMode = SvSeqV.AlmStopMode;		     
    }
 	 
    else if( SvSeqV.f.BkZeroStop )					     
    {
        CoutV.StopMode = STOPMODE_ZEROSTOP;			     
    }
 	 
    else if( SvSeqV.f.OtZeroStop )					     
    {
        CoutV.StopMode = STOPMODE_ZEROSTOP;			     
    }
     else if( SvSeqV.f.ZcZeroStop )					     
    {
        CoutV.StopMode = STOPMODE_ZEROSTOP;			     
    }
 	 
    else											     
    {
        CoutV.StopMode = STOPMODE_NOTSTOP;			     
    }
 	 
    return;
 }
