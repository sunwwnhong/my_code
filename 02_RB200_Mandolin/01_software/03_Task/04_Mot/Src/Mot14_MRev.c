  
  
  
  
  
 #include "Main.h"
 
 MREVDEALP MRevV;
 
  
  
 
void MRevDealInit( void )
{
    MRevV.MrPulseBase = (INT64)Prm.revlimit * MencP.PulseNo + \
                        ULONGOF( Prm.srevlimitL, Prm.srevlimitH );
}
 
  
  
 void MRevOverCheck( SHORT InData )
{
LONG  lkx = 0;
      
     if( Iprm.ABSEncMOVSel == FALSE )
    {
        return;
    }
      
     if(( Prm.revovDir & 0x0001 ) == 0x0001 )
    {
        return;
    }
      
     if( MRevV.MROVCheckFlag < 3 )
    {
        MRevV.MROVCheckOLd = InData;
        MRevV.MROVCheckFlag ++;
    }
    else
    {
        if( Iprm.f.MulTSingT == 0 && MencP.AbsoEncType == MENC_MABSO_TYPE)
        {
            lkx = (LONG)InData - (LONG)MRevV.MROVCheckOLd;
            if( lkx > 40000 || lkx < -40000 )
            {
                KPI_ALARMSET( ALM_ENCMTOV );
            }
            MRevV.MROVCheckOLd = InData;
        }
    }
 }
  
  
  
#if 1
void MRevDeal( SHORT InData )
{
SHORT skx = 0;
INT64 llkx = 0;
SHORT RevTimes = (SHORT)Prm.mtovcnt;
     if(( Prm.revovDir & 0x0001 ) == 0x0000 )
    {
        MRevV.MRFlag = 0;
        return;
    }
     if( MRevV.MRFlag < 3 )
    {
        MRevV.MRFlag ++;
        MRevV.MRevOld = InData;
        if( MRevV.MRFlag == 2 )
        {
            if( RevTimes == 0 )
            {
                MRevV.MRRemain = InData;
            }
            else
            {
                MRevV.MRRemain = RevTimes * 65536 + InData;
            }
        }
        return;
    }
      
     if( InData == -32768 && MRevV.MRevOld == 32767 )
    {
          
         Prm.mtovcnt ++;
        MRevV.MROVFlag = 1;                                  
    }
    if( InData == 32767 && MRevV.MRevOld == -32768 )
    {
          
         Prm.mtovcnt --;
        MRevV.MROVFlag = 1;                                  
    }
    skx = InData - MRevV.MRevOld;
    MRevV.MRRemain += skx;
      
      
    MRevV.MRevOld = (USHORT)InData;
      
      
    llkx = ((INT64)MRevV.MRRemain) * MencP.PulseNo + RoutV.ABSEncSValue;
     if( ( Prm.revovDir & 0x0010 ) == 0x0000 )
    {
        MRevV.MRPulse =  llkx % ( MRevV.MrPulseBase );
    }
    else
    {
        MRevV.MRPulse =  llkx;
    }
      
    MRevV.MRPulseL = MRevV.MRPulse & 0xFFFFFFFF;                          
    MRevV.MRPulseH = (MRevV.MRPulse >> 32) & 0xFFFFFFFF;                  
}
#endif
 
  
  
  
void MRRevCntSaved( void )
{
LONG rc;
    if( MRevV.MROVFlag )
    {
          
         rc = RpiFunPrmNvmemUpdate(&pndef_mtovcnt);
        if(rc != TRUE)
        {
            return;
        }
        MRevV.MROVFlag = 0;
    }
 }
