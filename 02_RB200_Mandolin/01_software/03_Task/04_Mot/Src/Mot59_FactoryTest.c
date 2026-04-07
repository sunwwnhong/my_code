  
  
  
  
  
  
#include "Main.h"
 
  
typedef union	{
        UINT    W;
        struct
        {
            UINT	PWM_UH			:1;          
            UINT	PWM_UL          :1;	         
            UINT	PWM_VH          :1;	         
            UINT	PWM_VL		    :1;          
            UINT    PWM_WH          :1;          
            UINT	PWM_WL	        :1;          
            UINT	Enc_OutA		:1;          
            UINT	Enc_OutB        :1;	         
            UINT	Enc_OutZ        :1;	         
            UINT    Enc_OutEn       :1;          
            UINT	PWM_EN          :6;	         
		} f; 
}FACTORYTEST;
 FACTORYTEST FactV;
  
  
  
void FactorTest_Init( void )
{
    FactV.W = 0x003F;
    ASIC_WR(MREG_Addr003D,FactV.W);
}
  
  
  
void FactoryTest( void )
{
FACTORYTEST PWMTestSet;
    PWMTestSet.W = 0;
     if( Iprm.FATest2 == 0 )                                  
    {
         if( FactV.f.PWM_EN != 0 )
        {
            FactV.W = 0x003F;                                
            ASIC_WR(MREG_Addr003D,FactV.W);
        }
         return;
    }
      
     PWMTestSet.W = ( Prm.FaTestControl >> 10 ) & 0x003F;
      
      
    if( ( Prm.FaTestControl & 0x0108 ) == 0x0008 )
    {
          
         
          
         if( PWMTestSet.f.PWM_UH == 1 && PWMTestSet.f.PWM_UL == 1 )
        {
            FactV.f.PWM_UH = 1;
            FactV.f.PWM_UL = 1;
        }
        else if( PWMTestSet.f.PWM_UH == 0 && PWMTestSet.f.PWM_UL == 0 )
        {
            FactV.f.PWM_UH = 1;
            FactV.f.PWM_UL = 1;        
        }
        else if( PWMTestSet.f.PWM_UH == 1 )
        {
            FactV.f.PWM_UH = 0;
            FactV.f.PWM_UL = 1;
        }
        else
        {
            FactV.f.PWM_UH = 1;
            FactV.f.PWM_UL = 0;        
        }
          
         if( PWMTestSet.f.PWM_VH == 1 && PWMTestSet.f.PWM_VL == 1 )
        {
            FactV.f.PWM_VH = 1;
            FactV.f.PWM_VL = 1;
        }
        else if( PWMTestSet.f.PWM_VH == 0 && PWMTestSet.f.PWM_VL == 0 )
        {
            FactV.f.PWM_VH = 1;
            FactV.f.PWM_VL = 1;        
        }
        else if( PWMTestSet.f.PWM_VH == 1 )
        {
            FactV.f.PWM_VH = 0;
            FactV.f.PWM_VL = 1;
        }
        else
        {
            FactV.f.PWM_VH = 1;
            FactV.f.PWM_VL = 0;        
        }        
          
         if( PWMTestSet.f.PWM_WH == 1 && PWMTestSet.f.PWM_WL == 1 )
        {
            FactV.f.PWM_WH = 1;
            FactV.f.PWM_WL = 1;
        }
        else if( PWMTestSet.f.PWM_WH == 0 && PWMTestSet.f.PWM_WL == 0 )
        {
            FactV.f.PWM_WH = 1;
            FactV.f.PWM_WL = 1;        
        }
        else if( PWMTestSet.f.PWM_WH == 1 )
        {
            FactV.f.PWM_WH = 0;
            FactV.f.PWM_WL = 1;
        }
        else
        {
            FactV.f.PWM_WH = 1;
            FactV.f.PWM_WL = 0;        
        }
         FactV.f.Enc_OutEn = 0;
        FactV.f.PWM_EN = 0x2A;
    }
      
     else
    {
        FactV.f.PWM_EN    = 0;
        FactV.f.Enc_OutEn = 1;
          
         if( PWMTestSet.f.PWM_UL == 0 )                                   
            FactV.f.Enc_OutA = 0;
        else
            FactV.f.Enc_OutA = 1;
         if( PWMTestSet.f.PWM_VL == 0 )                                   
            FactV.f.Enc_OutB = 0;
        else
            FactV.f.Enc_OutB = 1;
         if( PWMTestSet.f.PWM_WL == 0 )                                   
            FactV.f.Enc_OutZ = 0;
        else
            FactV.f.Enc_OutZ = 1;
     }
      
     ASIC_WR(MREG_Addr003D,FactV.W);
 }
