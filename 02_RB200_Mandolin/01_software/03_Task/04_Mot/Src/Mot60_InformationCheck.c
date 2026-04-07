  
  
  
  
  
  
#include "Main.h"
 
#define BootCheck   0
  

  
void SystemCompileInf( void )
{
    SystemVar.Author = 510;
#ifdef CPU1
    Var_SnNum = SystemVar.SnNum;
    ODDatArr[ Serial_Num ].all   = SystemVar.SnNum;
#endif
}
