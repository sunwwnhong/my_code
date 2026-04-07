  
  
 /****************************************************************************************************
*文件名:Seq05_DynamicBrakeSequence.c
*创建时间:2018.05.29
*版本说明:V1.0
*功能描述:动态制动序列
*****************************************************************************************************/
#include "Main.h"
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 void	LpxDynamicBrakeSequence( void )
{
  
  
	if( CoutV.f.Sv.BkBeReq && CoutV.f.Sv.OtBeReq )
	{
		CoutK.f.DbBeReq = TRUE;          
	}
	else
	{
		CoutK.f.DbBeReq = FALSE;         
	}
  
  
	switch( SvSeqV.DbStep )
	{
 		case 0:                                      
             PWM_Off();
           
			CoutK.f.PumpOnReq       = FALSE;
			CoutV.f.Sv.BaseEnable   = FALSE;       
 			SvSeqV.DbWait = 0;
 			 
			if( CoutV.StopMode == STOPMODE_FREERUN )             
			{
				CoutV.f.Sv.DbOn = FALSE;
				SvSeqV.DbStep++;
			}
 			else if( CoutV.StopMode == STOPMODE_DBSTOPFR )      
			{
				if( CinV.f.Sv.ScanCEncDataNG == TRUE )          
				{
					CoutV.f.Sv.DbOn = TRUE;
				}
				else
				{
					CoutV.f.Sv.DbOn = FALSE;
				}
				SvSeqV.DbStep++;
			}
 			 
			else                                               
			{
				CoutV.f.Sv.DbOn = TRUE;
				SvSeqV.DbStep = 6;
			}
			break;
          
		case 1:  
 		if(( CoutV.StopMode == STOPMODE_DBSTOPFR )&&( CinV.f.Sv.ScanCEncDataNG == TRUE ))
 		{										 
 			CoutV.f.Sv.DbOn = TRUE;				 
			CoutK.f.PumpOnReq = FALSE;			 
 		}										 
         else if( CoutV.StopMode == STOPMODE_FREERUN )         
        {
                CoutV.f.Sv.DbOn = FALSE;
                CoutK.f.PumpOnReq = FALSE;
                 SvSeqV.DbWait = 0;
                SvSeqV.DbStep++;        
        }
         else if( CoutV.f.Sv.MotStop )			 
        {
            CoutV.f.Sv.DbOn = FALSE;
            CoutK.f.PumpOnReq = FALSE;		     
             SvSeqV.DbWait = 0;
            SvSeqV.DbStep++;
        }
		break;
 		case 2:
             if( CoutV.StopMode == STOPMODE_DBSTOPDB )                     
            {
                CoutV.f.Sv.DbOn = TRUE;
                SvSeqV.DbWait = 0;
                SvSeqV.DbStep = 6;
            }
            else
            {
                  
                 if( CoutK.f.DbBeReq )                            
                {
                    if( Iprm.MosfetPumpFlag == 0 )
                    {
                          
                         CoutK.f.PumpOnReq = TRUE;
                        SvSeqV.DbWait = 0;
                        SvSeqV.DbStep++;
                    }
                    else
                    {
                          
                          
                        if( CinK.AbsMotSpd > Bprm.NorRatSpd )
                        {
                            KPI_WARNINGSET	( WRN_PUMP );	 
                        }
                        else
                        {
                            KPI_WARNINGCLR	( WRN_PUMP );	 
                            CoutK.f.PumpOnReq = TRUE;
                            SvSeqV.DbWait = 0;
                            SvSeqV.DbStep++;                        
                        }
                     }
                }
                  
                 else if(( CoutV.StopMode == STOPMODE_DBSTOPFR )&&( CinV.f.Sv.ScanCEncDataNG == TRUE ))
                {
                    SvSeqV.DbStep = 1;
                    KPI_WARNINGCLR	( WRN_PUMP );				 
                }
                else
                {
                    KPI_WARNINGCLR	( WRN_PUMP );				 
                }
            }
		break;
          
		case 3:  
          
             if( CoutK.f.DbBeReq == FALSE )
            {
                CoutK.f.PumpOnReq = FALSE;
                SvSeqV.DbWait = 0;
                SvSeqV.DbStep = 0;
            }
            else if( CinK.f.PumpOnComp == TRUE )
            {
                  
                 CoutK.f.PumpOnReq = FALSE;
                  
                PWM_On();
                 CoutV.f.Sv.BaseEnable = TRUE;
                SvSeqV.DbWait = 0;
                SvSeqV.DbStep ++;
            }
            break;
 	 
		case 4:  
 	 
 		if( CoutK.f.DbBeReq == FALSE )
		{
 			 
             PWM_Off();
			CoutV.f.Sv.BaseEnable = FALSE;
 			 
 			 
 			if( CoutV.StopMode == STOPMODE_FREERUN )
			{
				CoutV.f.Sv.DbOn = FALSE;
				SvSeqV.DbWait = 0;
				SvSeqV.DbStep = 2;
			}
 			else if( CoutV.StopMode == STOPMODE_DBSTOPFR )
            {
				if( CinV.f.Sv.ScanCEncDataNG == TRUE )		 
				{
					SvSeqV.DbWait = 0;						 
					SvSeqV.DbStep = 5;
				}
 				 
				else if( CoutV.f.Sv.MotStop )
				{
 					CoutV.f.Sv.DbOn = FALSE;
					SvSeqV.DbWait = 0;
					SvSeqV.DbStep = 1;
				}
				else
				{
					SvSeqV.DbWait = 0;
					SvSeqV.DbStep++;
				}
			}
 			else
			{
				SvSeqV.DbWait = 0;
				SvSeqV.DbStep++;
			}
		}
		break;
 	 
		case 5:  
 	 
 		 
 		 
 		if( CoutV.StopMode == STOPMODE_DBSTOPFR )
		{
			if( CinV.f.Sv.ScanCEncDataNG == TRUE )		 
			{
				CoutV.f.Sv.DbOn = TRUE;					 
			}
			else if( CoutV.f.Sv.MotStop )				 
			{
 				CoutV.f.Sv.DbOn = FALSE;
				SvSeqV.DbWait = 0;
				SvSeqV.DbStep = 1;
			}
			else
			{
				CoutV.f.Sv.DbOn = TRUE;			 
				SvSeqV.DbWait = 0;
				SvSeqV.DbStep = 1;
			}
		}
 		else if( CoutV.StopMode == STOPMODE_FREERUN )
		{
			CoutV.f.Sv.DbOn = FALSE;
			SvSeqV.DbWait = 0;
			SvSeqV.DbStep = 1;
		}
 		else
		{
			CoutV.f.Sv.DbOn = TRUE;
			SvSeqV.DbWait = 0;
			SvSeqV.DbStep++;
		}
		break;
          
		case 6:  
          
          
		if(((( CinV.f.Sv.ScanCEncDataNG == FALSE ) && CoutV.f.Sv.MotStop ) && CoutK.f.DbBeReq )
		   || ( CoutV.StopMode == STOPMODE_FREERUN )	 
		   || ( CoutV.StopMode == STOPMODE_DBSTOPFR ))	 
		{
			CoutV.f.Sv.DbOn = FALSE;
			SvSeqV.DbWait = 0;
			SvSeqV.DbStep = 2;
		}
		break;
          
		default:  
 		 
		break;
	}
  
  
		CoutK.f.BaseEnable = (CoutV.f.Sv.BaseEnable)? TRUE : FALSE;
  
  
#if 0
      
     if( Iprm.FATest2 == 1 )
    {
        if( ( Prm.FaTestControl & 0x0100 ) == 0x0100 )
        {
            DBOn();
        }
        else
        {
            DBOff();
        }
    }
    else
    {
        if( CoutV.f.Sv.DbOn )
        {
            DBOn();
        }
        else
        {
            DBOff();
        }
    }
#endif
 	return;
}
 
 
 
  
  
  
  
  
  
void	LpxChargePumpControl( void )
{
USHORT PumpTimeSet = Prm.MosPump & 0x00FF;
        if( PumpTimeSet < 10 )
            PumpTimeSet = 10;
		if( CoutK.f.PumpOnReq == TRUE )
		{
            if( Iprm.MosfetPumpFlag == 0x01 )
            {
                  
                 if( KioV.SvonRelayCnt > KPI_SCANB_MS( PumpTimeSet ) )
                {
                    if( KioV.SvonPumpCnt >= 1 )
                    {                        
                        KioV.f.PumpOnComp = TRUE;			             
                    }
                    else
                    {
                        KioV.SvonPumpCnt++;
                    }
                     Mosfet_PumpOff( );                                 
                }
                else
                {
                    KioV.SvonRelayCnt++;
                    Mosfet_PumpOn( );                                            
                 }
            }
            else
            {
                  
                 KioV.f.PumpOnComp = TRUE;			                     
            }
		}
  
 		else
		{
			KioV.SvonPumpCnt = 0;
			KioV.SvonRelayCnt = 0;
			KioV.f.PumpOnComp = FALSE;					     
		}
 		return;
}
 
