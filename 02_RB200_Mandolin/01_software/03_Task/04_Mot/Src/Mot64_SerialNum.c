#include "Main.h"

USHORT  SnHoldFlg = 0;

#define SNNUM_FUNC 1

void SnRead(void)
{
#if SNNUM_FUNC
    USHORT  SnLRead;
    USHORT  SnHRead;

    SnLRead = ReadEepromWord(EEPADR_SERVOINF);
    SnHRead = ReadEepromWord(EEPADR_SERVOINF+1);
    SystemVar.SnNum = (ULONG)SnLRead + ((ULONG)SnHRead << 16);
#endif
}

void SnWriteEn(void)
{
#if SNNUM_FUNC
   ULONG  data;
   data = (ULONG)Prm.SnL  + ((ULONG)Prm.SnH << 16);
   if(data != 0 )
   {
       SnHoldFlg = 1;
   }
#endif
}


void SnHoldUpdate( void )
{
#if SNNUM_FUNC
    USHORT  data;

    if(SnHoldFlg == 1)
    {
        GetEepromSemaphore( WAIT );
        WriteEepromEnable( );
        data = Prm.SnL;

        WriteEepromWord( EEPADR_SERVOINF , data, WAIT );
        data = Prm.SnH;

        WriteEepromWord( EEPADR_SERVOINF + 1 , data, WAIT );


        SystemVar.SnNum = (ULONG)Prm.SnL  + ((ULONG)Prm.SnH << 16);
        Prm.SnL = 0;
        Prm.SnH = 0;
        SnHoldFlg = 0;

        WriteEepromDisable( );
        FreeEepromSemaphore( );
        return;
    }
#endif
}
