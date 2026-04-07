  
  
  
  
  
 #include "Main.h"
 
#define ABS( u )    (((u) >= 0.0f ) ? (u) : -(u))
 struct SpdSScure_Bits
{                        
    USHORT  ScurvCase       :3;
    USHORT  ScurvCaseChge   :1;
    USHORT  AccDir          :1;
    USHORT  Resverd         :11;  
};
 union SPDSSCURE_BITS {
    USHORT all;
    struct SpdSScure_Bits   bit;
};
 typedef struct
{
     float TACCCoeff;         
    float TDECCoeff;         
    float TASLCoeff;         
    float TDSLCoeff;         
     float Accelerate;        
    float JerkACC;
    float JerkDEC;
    float JerkTACC;
    float JerkTDEC;
     float TSLReg;
     float TurnSpd;
    float SpdScurvOut;
    float SpdScurvOutT;
    float SpdScureOld;       
    float HalfSpd;
    float O_1Base;           
     union SPDSSCURE_BITS SpsdSScBit;
}SSCURE_STRUCT;
 SSCURE_STRUCT SScureVar;
  
  
  
void SoftStart_Init( void )
{
    SScureVar.O_1Base = 0.1f * Iprm.fKspdlvl;
     SScureVar.SpdScureOld   = 0.0f;
    SScureVar.SpdScurvOut   = 0.0f;
    SScureVar.SpdScurvOutT  = 0.0f;
    SScureVar.TSLReg        = 0.0f;
}
  
  
  
void SoftSpd_Update( LONG Spd )
{
    SScureVar.SpdScureOld = Spd;
    SScureVar.SpdScurvOut = Spd;
    return;
}
 
  
  
 void PcalBaseSoftStartAcc( void )
{
#if 1
    float fx1,fx2,fx3;
    float VelBasic = 30000.0f * Iprm.fKspdlvl;            
     if( Prm.sfsts == 0 )                
    {
        if( Prm.sfsacc == 0 )
        {
            SScureVar.TACCCoeff = VelBasic;
        }
        else
        {
            SScureVar.TACCCoeff = VelBasic * fKPI_SACYCLEUS / ( 1000.0f * (float)Prm.sfsacc );
        }
        SScureVar.TASLCoeff = SScureVar.TACCCoeff;
    }
    else                                
    {
        fx1 = (float)Prm.sfsacc * 1000.0f / fKPI_SACYCLEUS;          
        fx2 = (float)Prm.sfsts * 1000.0f * 0.5f / fKPI_SACYCLEUS;           
        fx3 = fx2 * (fx2 + 1.0f) + fx1 * fx2;
         SScureVar.TASLCoeff = VelBasic / fx3;                        
        SScureVar.TACCCoeff = fx2 * SScureVar.TASLCoeff;             
    }
#endif
     return;
}
 
  
  
 void PcalBaseSoftStartDec( void )
{
#if 1
    float fx1,fx2,fx3;
    float VelBasic = 30000.0f * Iprm.fKspdlvl;            
     if( Prm.sfsts == 0 )                
    {
        if( Prm.sfsdec == 0 )
        {
            SScureVar.TDECCoeff = VelBasic;
        }
        else
        {
            SScureVar.TDECCoeff = VelBasic * fKPI_SACYCLEUS / ( 1000.0f * (float)Prm.sfsdec );
        }
        SScureVar.TDSLCoeff = SScureVar.TDECCoeff;
    }
    else                                
    {
        fx1 = (float)Prm.sfsdec * 1000.0f / fKPI_SACYCLEUS;          
        fx2 = (float)Prm.sfsts * 1000.0f * 0.5f / fKPI_SACYCLEUS;           
        fx3 = fx2 * (fx2 + 1.0f) + fx1 * fx2;
         SScureVar.TDSLCoeff = VelBasic / fx3;                        
        SScureVar.TDECCoeff = fx2 * SScureVar.TDSLCoeff;             
    }
#endif
     return;
 }
 
  
  
 
void PcalBaseSoftStartTs( void )
{
    float fx1,fx2,fx3;
    float VelBasic = 30000.0f * Iprm.fKspdlvl;            
     if( Prm.sfsts == 0 )                
    {
         if( Prm.sfsacc == 0 )
        {
            SScureVar.TACCCoeff = VelBasic;
        }
        else
        {
            SScureVar.TACCCoeff = VelBasic * fKPI_SACYCLEUS / ( 1000.0f * (float)Prm.sfsacc );
        }
        SScureVar.TASLCoeff = SScureVar.TACCCoeff;
         if( Prm.sfsdec == 0 )
        {
            SScureVar.TDECCoeff = VelBasic;
        }
        else
        {
            SScureVar.TDECCoeff = VelBasic * fKPI_SACYCLEUS / ( 1000.0f * (float)Prm.sfsdec );
        }
        SScureVar.TDSLCoeff = SScureVar.TDECCoeff;
    }
    else                                
    {
        fx1 = (float)Prm.sfsacc * 1000.0f / fKPI_SACYCLEUS;          
        fx2 = (float)Prm.sfsts * 1000.0f * 0.5f / fKPI_SACYCLEUS;           
        fx3 = fx2 * (fx2 + 1.0f) + fx1 * fx2;
         SScureVar.TASLCoeff = VelBasic / fx3;                        
        SScureVar.TACCCoeff = fx2 * SScureVar.TASLCoeff;             
         fx1 = (float)Prm.sfsdec * 1000.0f / fKPI_SACYCLEUS;          
        fx2 = (float)Prm.sfsts * 1000.0f * 0.5f / fKPI_SACYCLEUS;           
        fx3 = fx2 * (fx2 + 1.0f) + fx1 * fx2;
         SScureVar.TDSLCoeff = VelBasic / fx3;                        
        SScureVar.TDECCoeff = fx2 * SScureVar.TDSLCoeff;             
    }
}
  
  
 #define INCSPD_I        1    
#define DECSPD_I        3    
#define INCSPD_IV       2    
#define DECSPD_IV       4    
#define DEC_I_INC_IV    5    
#define DEC_IV_INC_I    6    
void ScurvCaseChang(float SpdScurvIn)
{
      
     SScureVar.SpsdSScBit.bit.ScurvCaseChge = 0;  
    if( SpdScurvIn >= 0.0f )
    {
        if( SScureVar.SpdScurvOut < 0.0f )    
        {
            if(SpdScurvIn == 0)
            {
                 SScureVar.SpsdSScBit.bit.ScurvCase = DECSPD_IV;
            }
            else
            {
                 SScureVar.SpsdSScBit.bit.ScurvCase = DEC_IV_INC_I;    
            }
            SScureVar.Accelerate    = SScureVar.JerkDEC;  
            SScureVar.HalfSpd       = (ABS(SScureVar.SpdScurvOut)) * 0.5f;   
        }
        else     
        {    
            if(SScureVar.SpdScurvOut <= SpdScurvIn)
            {    
                SScureVar.SpsdSScBit.bit.ScurvCase  = INCSPD_I;
                SScureVar.Accelerate                = SScureVar.JerkACC;
            }
            else
            {    
                SScureVar.SpsdSScBit.bit.ScurvCase = DECSPD_I;
                SScureVar.Accelerate = SScureVar.JerkDEC;
            }
            SScureVar.HalfSpd = (ABS(SScureVar.SpdScurvOut + SpdScurvIn)) * 0.5f;
        }
    }
    /*------------------------------------------------------------
    当前S型曲线速度指令为负时  判断电机实际转速方向 决定加减速象限
    --------------------------------------------------------------*/
    else
    {
         if( SScureVar.SpdScurvOut > 0.0f )      
        {
            SScureVar.SpsdSScBit.bit.ScurvCase = DEC_I_INC_IV;
            SScureVar.HalfSpd = (ABS(SScureVar.SpdScurvOut)) * 0.5f;       
            SScureVar.Accelerate = SScureVar.JerkDEC;        
        }
         else
        {
            if(SScureVar.SpdScurvOut >= SpdScurvIn)       
            {
                SScureVar.SpsdSScBit.bit.ScurvCase = INCSPD_IV;
                SScureVar.Accelerate = SScureVar.JerkACC;
            }
            else                                     
            {
                SScureVar.SpsdSScBit.bit.ScurvCase = DECSPD_IV;
                SScureVar.Accelerate = SScureVar.JerkDEC;
            }
            SScureVar.HalfSpd = (ABS(SScureVar.SpdScurvOut + SpdScurvIn)) * 0.5f;
        }
    }
    SScureVar.SpdScureOld = SpdScurvIn;      
}
 
/******************************************************************************
函数名:IncSpd
功  能:S曲线平滑处理——加速处理
******************************************************************************/
void IncSpd(float SpdScurvIn)
{
    USHORT SectorFlag = 0; 
    float DataTmp = 0.0f;
    if((SScureVar.TSLReg) < SScureVar.JerkTACC)
    {    
        if(SScureVar.SpdScurvOutT <= SScureVar.HalfSpd)
        {
            SectorFlag = 0;  
        }
        else
        {
            SectorFlag = 2;  
        }
    }
    else
    {
        if((SpdScurvIn - SScureVar.TurnSpd) > SScureVar.SpdScurvOutT)
        {
            SectorFlag = 1;  
        }
        else
        {
            SectorFlag = 2;  
        }
    }
     switch (SectorFlag)
    {
        case 0:
                 SScureVar.TSLReg += SScureVar.Accelerate;    
                SScureVar.TurnSpd += (SScureVar.TSLReg);
                SScureVar.SpdScurvOutT += (SScureVar.TSLReg);
                 if((SScureVar.TSLReg) > SScureVar.JerkTACC)
                {
                    DataTmp = SScureVar.TSLReg  - SScureVar.JerkTACC;
                    SScureVar.TSLReg = SScureVar.JerkTACC;
                     SScureVar.TurnSpd -= DataTmp;
                    SScureVar.SpdScurvOutT -= DataTmp;
                }
                if(SScureVar.SpdScurvOutT > SpdScurvIn)
                {
                    SScureVar.SpdScurvOutT = SpdScurvIn;
                }
                break;
        case 1:
                 SScureVar.SpdScurvOutT += (SScureVar.TSLReg);
                if(SScureVar.SpdScurvOutT > SpdScurvIn)
                    SScureVar.SpdScurvOutT = SpdScurvIn;
                break;
        case 2:
                 SScureVar.SpdScurvOutT += (SScureVar.TSLReg);
                if(SScureVar.SpdScurvOutT > SpdScurvIn || SScureVar.TSLReg == 0.0f )
                {
                    SScureVar.SpdScurvOutT = SpdScurvIn;
                }
                 if(SScureVar.TSLReg > SScureVar.Accelerate)
                {
                    SScureVar.TSLReg -= SScureVar.Accelerate;
                    if(SScureVar.TSLReg < 0.0f)
                    {
                        SScureVar.TSLReg = 0.0f;
                    }
                }
                else
                {
                    SScureVar.TSLReg = 0.0f;
                }
               break;
        default:
              break;
      }
}
/******************************************************************************
函数名:DecSpd
功  能:S曲线平滑处理——减速处理
******************************************************************************/
void DecSpd(float SpdScurvIn)
{
     USHORT SectorFlag = 0;
    if((SScureVar.TSLReg) < SScureVar.JerkTDEC)
    {
        if(SScureVar.SpdScurvOutT > SScureVar.HalfSpd)
        {
            SectorFlag = 0;  
        }
        else
        {
            SectorFlag = 2;
        }
    }
    else
    {
        if((SScureVar.TurnSpd + SpdScurvIn) > SScureVar.SpdScurvOutT)
        {
            SectorFlag = 2;
        }
        else
        {
            SectorFlag = 1;
        }
    }
     switch (SectorFlag)
    {
        case 0:
                 if((SScureVar.TSLReg) >= SScureVar.JerkTDEC)
                {
                    SScureVar.TSLReg = SScureVar.JerkTDEC;
                }
                else
                {
                    SScureVar.TSLReg += SScureVar.Accelerate;    
                }
                 SScureVar.TurnSpd += (SScureVar.TSLReg);
                SScureVar.SpdScurvOutT -= (SScureVar.TSLReg);
                if(SScureVar.SpdScurvOutT <= SpdScurvIn)
                {
                    SScureVar.SpdScurvOutT = SpdScurvIn;
                }
                break;
        case 1:  
                SScureVar.SpdScurvOutT -= (SScureVar.TSLReg);
                if(SScureVar.SpdScurvOutT <= SpdScurvIn || SScureVar.TSLReg == 0.0f)
                {
                    SScureVar.SpdScurvOutT = SpdScurvIn;
                }
                break;
        case 2:  
                SScureVar.SpdScurvOutT -= (SScureVar.TSLReg);
                if(SScureVar.SpdScurvOutT <= SpdScurvIn)
                {
                    SScureVar.SpdScurvOutT = SpdScurvIn;
                }
                if( SScureVar.TSLReg == 0.0f )
                {
                    SScureVar.SpdScurvOutT = SpdScurvIn;
                }
                 if(SScureVar.TSLReg >= SScureVar.Accelerate)
                {
                    SScureVar.TSLReg -= SScureVar.Accelerate;
                    if(SScureVar.TSLReg < 0.0f)
                    {
                        SScureVar.TSLReg = 0.0f;
                    }
                }
                else
                {
                    SScureVar.TSLReg = 0.0f;
                }
              break;
        default:
            break;
    }
}
 /******************************************************************************
函数名:SScureJudge
功  能:S曲线平滑处理
******************************************************************************/
LONG SScureCal(float SpdScurvIn)
{
    float DataTmp = ABS(SpdScurvIn - SScureVar.SpdScurvOut);
    if(DataTmp > SScureVar.O_1Base )  
    {
        SScureVar.SpdScurvOutT = ABS(SScureVar.SpdScurvOut);
        switch (SScureVar.SpsdSScBit.bit.ScurvCase)
        {
            case 1:  
                    IncSpd(SpdScurvIn);
                    SScureVar.SpdScurvOut = SScureVar.SpdScurvOutT;
                    SScureVar.SpsdSScBit.bit.AccDir = 0;
                    break;
            case 3:    
                    DecSpd(SpdScurvIn);
                    SScureVar.SpdScurvOut = SScureVar.SpdScurvOutT;
                    SScureVar.SpsdSScBit.bit.AccDir = 1;
                    break;
            case 2:   
                    IncSpd(-SpdScurvIn);
                    SScureVar.SpdScurvOut = -SScureVar.SpdScurvOutT;
                    SScureVar.SpsdSScBit.bit.AccDir = 1;
                    break;
            case 4:  
                    DecSpd(-SpdScurvIn);
                    SScureVar.SpdScurvOut = -SScureVar.SpdScurvOutT;
                    SScureVar.SpsdSScBit.bit.AccDir = 0;
                    break;
            case 5:  
                    if(SScureVar.SpsdSScBit.bit.ScurvCaseChge == 0)
                    {    
                        DecSpd(0);
                        SScureVar.SpdScurvOut = SScureVar.SpdScurvOutT;
                        if(SScureVar.SpdScurvOut == 0)
                        {
                            SScureVar.SpsdSScBit.bit.ScurvCaseChge = 1;
                            SScureVar.TSLReg        = 0.0f;
                            SScureVar.TurnSpd       = 0.0f;
                            SScureVar.Accelerate    = SScureVar.JerkACC;
                            SScureVar.HalfSpd       = ABS(SpdScurvIn) * 0.5f;
                        }
                        SScureVar.SpsdSScBit.bit.AccDir = 1;
                    }
                    else
                    {
                        IncSpd(-SpdScurvIn);
                        SScureVar.SpdScurvOut           = -SScureVar.SpdScurvOutT;
                        SScureVar.SpsdSScBit.bit.AccDir = 1;
                    }
                    break;
            case 6:  
                    if(SScureVar.SpsdSScBit.bit.ScurvCaseChge == 0)
                    {    
                        DecSpd( 0.0f );
                        SScureVar.SpdScurvOut = -SScureVar.SpdScurvOutT;
                        if(SScureVar.SpdScurvOut == 0)
                        {
                            SScureVar.SpsdSScBit.bit.ScurvCaseChge = 1;
                            SScureVar.TSLReg        = 0.0f;
                            SScureVar.TurnSpd       = 0.0f;
                            SScureVar.Accelerate    = SScureVar.JerkACC;
                            SScureVar.HalfSpd       = ABS(SpdScurvIn) * 0.5f;
                        }
                        SScureVar.SpsdSScBit.bit.AccDir = 0;
                    }
                    else
                    {
                        IncSpd(SpdScurvIn);
                        SScureVar.SpdScurvOut           = SScureVar.SpdScurvOutT;
                        SScureVar.SpsdSScBit.bit.AccDir = 0;
                    }
                    break;
            default:
                    break;
      }
    }
    else
    {
        SScureVar.TSLReg        = 0.0f;
        SScureVar.SpdScurvOut   = SpdScurvIn;
    }
     return SScureVar.SpdScurvOut;
}
 
  
  
 LONG BaseSoftStartSpdRef( LONG	SpdRef, LONG  SpdRefx )
{
        float DataTmp = 0;
         DataTmp = (float)SpdRef - SScureVar.SpdScureOld;
        DataTmp = DataTmp > 0.0f ? DataTmp : (-DataTmp);
        if( DataTmp > SScureVar.O_1Base )
        {
              
             SScureVar.JerkACC  = SScureVar.TASLCoeff;
            SScureVar.JerkTACC = SScureVar.TACCCoeff;
             SScureVar.JerkDEC  = SScureVar.TDSLCoeff;
            SScureVar.JerkTDEC = SScureVar.TDECCoeff;
              
            ScurvCaseChang( SpdRef );
            SScureVar.TSLReg     = 0.0f;
            SScureVar.TurnSpd    = 0.0f;
        }
         SpdRefx = SScureCal( SpdRef );
 	return ( SpdRefx );
}
