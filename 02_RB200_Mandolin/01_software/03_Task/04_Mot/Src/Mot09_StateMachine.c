  
  
  
  
  
 #include "Main.h"
 
  
  
void StateMachine_Init(void)
{
    MlibResetSHORTMemory( &StateM_Var, sizeof(StateM_Var) );       
    SysBitDef.w = 0;
 }
