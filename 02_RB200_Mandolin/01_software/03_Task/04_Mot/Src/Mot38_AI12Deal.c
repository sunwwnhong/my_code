#include "Main.h"

#define VoltageCoeff    11715L    //3.3V对应的AI输入电压值(mV)
ADCCHANNEL AdcV;
void ADCChan12AutoAdj( void );


/**********************************************************************************************/
/* Function_Name: AI12DataInit                                                             */
/* Description  : 模拟量输入参数初始化                                                           */
/**********************************************************************************************/
void AI12DataInit( void )
{
    MlibResetLONGMemory( &AdcV, sizeof(AdcV) );
}

/**********************************************************************************************/
/* Function_Name: AI1LPFilterInit                                                             */
/* Description  : 模拟量通道1滤波参数初始化                                                           */
/**********************************************************************************************/
void AI1LPFilterInit( void )
{
    AdcV.AI1LPFil = MlibPcalKf1gain( (LONG)Prm.AI1treffil * 1000, KPI_SACYCLEUS, 0 );
}

/**********************************************************************************************/
/* Function_Name: AI2LPFilterInit                                                             */
/* Description  : 模拟量通道2滤波参数初始化                                                           */
/**********************************************************************************************/
void AI2LPFilterInit( void )
{
    AdcV.AI2LPFil = MlibPcalKf1gain( (LONG)Prm.AI2treffil * 1000, KPI_SACYCLEUS, 0 );
}

/**********************************************************************************************/
/* Function_Name: ADCChannel1And2Deal                                                             */
/* Description  : 模拟量通道线性与校准处理（扭矩传感器监控用）                                                     */
/**********************************************************************************************/
void ADCChannel1And2Deal( void )
{
LONG kx;
    kx = (LONG)AMotVar[0].AIInput - 2048;

    kx = kx * VoltageCoeff / 2048;
#if 0
    if( kx > 10000 )                                                
      kx = 10000;
    else if( kx < -10000)
      kx = -10000;
    else
    {;}
#endif
    AdcV.AI1LPFilo = MlibLpfilter1( kx, AdcV.AI1LPFil, AdcV.AI1LPFilo );
    AdcV.ADCChannel10 = AdcV.AI1LPFilo;
    kx = AdcV.AI1LPFilo * Prm.AI1Gain / 100 - (SHORT)Prm.AI1Offset;
    if( kx > (LONG)Prm.AI1Zero)
      kx = kx - (LONG)Prm.AI1Zero;
    else if( kx < - (LONG)Prm.AI1Zero )
      kx = kx + (LONG)Prm.AI1Zero;
    else
      kx = 0;
    if( kx > 10000 )                                                
      kx = 10000;
    else if( kx < -10000)
      kx = -10000;
    else
    {}
    AdcV.ADCChannel11 = kx;

    ADCChan12AutoAdj( );                                    
}
/**********************************************************************************************/
/* Function_Name: ADCChan12AutoAdj                                                             */
/* Description  : 模拟量通道零点偏置校准（PnF1F校准开启）                                                */
/**********************************************************************************************/
void ADCChan12AutoAdj( void )
{
    LONG rc;
    if( AdcV.AI12AutoAdj == 0 )                             
        return;
    if( AdcV.AI12AutoAdj == 1 )
    {
        if( ++AdcV.AI12AutoAdjCnt < 1024 )
        {
            AdcV.AI1AutoSum += AdcV.AI1LPFilo;
        }
        else
        {
            Prm.AI1Offset = AdcV.AI1AutoSum >> 10;
            AdcV.AI12AutoAdj = 2;
        }
    }
    else if (AdcV.AI12AutoAdj == 2)
    {
        rc = RpiFunPrmNvmemUpdate(&pndef_AI1Offset);
        if(rc != TRUE)
        {
            return;
        }

        AdcV.AI12AutoAdj = 0;
        Prm.AutoAIAdj = 0;
    }
}
