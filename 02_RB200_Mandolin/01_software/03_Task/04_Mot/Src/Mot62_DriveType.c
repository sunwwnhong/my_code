/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd***************************************
* File Name          : Mot62_DriveType.c
* Version            : V0.1
* Date               : 2024
* Description        : 机型识别
*****************************************************************************************************/

#include "Main.h"
 
  
/****************************************************************************************************/
/* Function_Name: DriveSeriesSet */
/* Description  : 机型设定，暂不用
                     */
/***************************************************************************************************/
void DriveSeriesSet( void )
{
    Iprm.ServoSeries = 1;
    return;
}
  
  
/****************************************************************************************************/
/* Function_Name: DriveTypeCheck */
/* Description  : 功率机型识别，仅适用于SD100机型
                     */
/***************************************************************************************************/
void DriveTypeCheck( void )
{
 #if ( OneMotorMode == 0 )
 	
     if( ( Prm.syssw2 & 0x4000 ) == 0x0000 )
    {
        if( DriverPowerType < 496 )                                      
        {
            if( Prm.drvno != 0x0050A )            
            {
                KPI_ALARMSET( ALM_NOTSUPPORT );
            }
        }
         else if( (DriverPowerType > 745) && (DriverPowerType < 1738) )      
        {
            if( Prm.drvno != 0x110A )            
            {
                KPI_ALARMSET( ALM_NOTSUPPORT );
            }
        }
         else if( (DriverPowerType > 1986) && (DriverPowerType < 2979) )      
        {
            if( Prm.drvno != 0x210A )            
            {
                KPI_ALARMSET( ALM_NOTSUPPORT );
            }
        }
         else if( (DriverPowerType > 3227) && (DriverPowerType < 4220) )      
        {
            if( Prm.drvno != 0x300A )            
            {
                KPI_ALARMSET( ALM_NOTSUPPORT );
            }
        }
         else if( (DriverPowerType > 5710) && (DriverPowerType < 6703) )      
        {
            if( Prm.drvno != 0x400A )            
            {
                KPI_ALARMSET( ALM_NOTSUPPORT );
            }
        }
         else if( (DriverPowerType > 6951) && (DriverPowerType < 7696) )      
        {
            if( Prm.drvno != 0x600A )            
            {
                KPI_ALARMSET( ALM_NOTSUPPORT );
            }
        }
         else if( (DriverPowerType > 7944) && (DriverPowerType < 8192) )      
        {
            if( Prm.drvno != 0x800A )            
            {
                KPI_ALARMSET( ALM_NOTSUPPORT );
            }
        }
         else
        {
            KPI_ALARMSET( ALM_NOTSUPPORT );
        }
    }
#endif
}
