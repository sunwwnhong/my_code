 /*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Cur03_CurSamp.c
* Version            : V0.1
* Date               : 2024
* Description        : 电流采样处理
***********************************************************************************************/
  
  
  
  
#include "Main.h"
 
CURRENT_STRUCT_DEF CurrentSample = CURRENT_STRUCT_DEFAULT;
  
  
#define CurSamp_Max 8592        //电流零点偏置ADC最大值
#define CurSamp_Min 7792        //电流零点偏置ADC最小值
 
  
  
void PowerOffCheckTime( void )
{ 
 }
 
  
/**********************************************************************************************/
/* Function_Name: CurrentZeroCheck_U         */
/* Description  : 上电U相电流偏置过大判定
                                             */
/**********************************************************************************************/
void CurrentZeroCheck_U( float ZeroValue)
{
    if( ZeroValue > (float)CurSamp_Max || ZeroValue < (float)CurSamp_Min )
    {
        KPI_ALARMSET( ALM_CURAD_U );
        CurrentSample.CurFlg.f.ZeroErr = 1;          
    }
	else
	{
	  	CurrentSample.CurFlg.f.ZeroErr = 0;          
	}
}
  
/**********************************************************************************************/
/* Function_Name: CurrentZeroCheck_V         */
/* Description  : 上电V相电流偏置过大判定
                                             */
/**********************************************************************************************/
void CurrentZeroCheck_V(float ZeroValue)
{
    if(ZeroValue > (float)CurSamp_Max || ZeroValue < (float)CurSamp_Min)
    {
        KPI_ALARMSET( ALM_CURAD_V );
        CurrentSample.CurFlg.f.ZeroErr = 1;          
    }
	else
	{
	  	CurrentSample.CurFlg.f.ZeroErr = 0;          
	}
}
  
/**********************************************************************************************/
/* Function_Name: CurrentZeroCheck_W         */
/* Description  : 上电W相电流偏置过大判定
                                             */
/**********************************************************************************************/
void CurrentZeroCheck_W(float ZeroValue)
{
    if(ZeroValue > (float)CurSamp_Max || ZeroValue < (float)CurSamp_Min)
    {
        KPI_ALARMSET( ALM_CURAD_W );
        CurrentSample.CurFlg.f.ZeroErr = 1;          
    }
    else
    {
        CurrentSample.CurFlg.f.ZeroErr = 0;          
    }
}
#ifdef CPU1
  
/**********************************************************************************************/
/* Function_Name: MotA_CurrentZeroSet         */
/* Description  : 轴1和轴2电流偏置自校准，并获取电流偏置值
                                             */
/**********************************************************************************************/
void MotA_CurrentZeroSet(void)
{
float  Datatmp = 0.0f;
      
    LONG ADCSample_I12Cnt = 0;
    float ADCSample_IuSum = 0.0f;                   
    float ADCSample_IvSum = 0.0f;                   
    float ADCSample_IwSum = 0.0f;                   
    float ADCSample_DrvType = 0.0f;                 
    Acr_I[ 0 ].AdcUZero = 0.0f;
    Acr_I[ 0 ].AdcVZero = 0.0f;
    Acr_I[ 0 ].AdcWZero = 0.0f;
     while( ADCSample_I12Cnt < 1024)
    {
        KlibWaitus( 200 );
        ADCSample_IuSum     += AMotVar[ 0 ].Iuu;
        ADCSample_IvSum     += AMotVar[ 0 ].Ivv;
        ADCSample_IwSum     += AMotVar[ 0 ].Iww;
        ADCSample_DrvType   += AMotVar[ 0 ].DriveType;   
        ADCSample_I12Cnt ++;
    };
      
    Datatmp = ADCSample_IuSum / 1024.0f;
    CurrentZeroCheck_U( Datatmp );                           
    Acr_I[ 0 ].AdcUZero = Datatmp;
    CurrentSample.IuZero = Datatmp - 8192.0f;                
     Datatmp = ADCSample_IvSum / 1024.0f;
    CurrentZeroCheck_V( Datatmp );                           
    Acr_I[ 0 ].AdcVZero = Datatmp;
    CurrentSample.IvZero = Datatmp - 8192.0f;                
     Datatmp = ADCSample_IwSum / 1024.0f;
    CurrentZeroCheck_W( Datatmp );                           
    Acr_I[ 0 ].AdcWZero = Datatmp;
    CurrentSample.IwZero = Datatmp - 8192.0f;                
      
    CurrentSample.drivType = ADCSample_DrvType / 512.0f;    
     DriverPowerType = CurrentSample.drivType;                
     
    CurrentSample.CurFlg.f.ZeroOk = 1;                       
     if( Kprm.f.AxisNum == 0 )
    {
        return;
    }

}
#endif

 
  
  
