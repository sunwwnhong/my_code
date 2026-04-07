  
  
  
  
  
 #include "Main.h"
 
float  FPcalDqAcrKp( LONG Gain, float Lx )
{
float   fkx;
        fkx =  Gain * 100.0f;
        fkx = fkx * Lx / Bprm.fVdc;
        fkx = fkx * Bprm.fMaxCur;
        fkx = fkx * 51471.85352f / 750000.0f;
         return( fkx );
}
 
float   FPcalDqAcrKi( LONG Ti, float Kp )
{
float    fkx;
        if( Ti == 0 )
        {
            fkx = 0.0f;
        }
         else
        {
            fkx = (float)FPGA_CLKns * (float)CurrentLoopVar.PWM_Priod / 10.0f;
             if( ( Prm.syssw2 & 0x0100 )  ==  0x0100 )
            {
                 fkx *= 2.0f;
            }
             fkx = Kp * fkx / ((float)Ti * 1000.0f);
        }
        return( fkx );
}
