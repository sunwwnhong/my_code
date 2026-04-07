/***************************************************************************************************
*文件名:Lib01_ResetMemory.c
*创建时间:2017.03.03
*版本说明:V1.0
*功能描述:
****************************************************************************************************/
#include "Lib01_ResetMemory.h"
 
#ifdef RunRAM
#pragma CODE_SECTION(MlibResetLONGMemory, ".TI.ramfunc");
#endif
 
  
  
  
void    MlibResetSHORTMemory( void *mempx, LONG xlwd )
{
LONG    i;
         for( i=0; i<xlwd; i++ )
        {
            ((SHORT *)mempx)[i] = 0;
        }
        return;
}
 void    MlibResetLONGMemory( void *mempx, LONG xlwd )
{
LONG    i;
         for( i=0; i<xlwd; i++ )
        {
            ((LONG *)mempx)[i] = 0;
        }
        return;
}
