/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name   : Mot56_STO.c
* Version     : V0.1
* Date        : 2024
* Description : STO处理
***********************************************************************************************/
  
#include "Main.h"
 


void STO_FaultReset( void );
/****************************************************************************************************/
/*                                                                                                  */
/*      转矩输出封锁（125us SCANB）                                                                             */
/*                                                                                                  */
/****************************************************************************************************/
void STO_FaultOutOff( void )
{


    if( STO_EN )
    {/* 软硬件开启 */
        if( (STO1_Status != 0) || (STO2_Status != 0) )
        {/* MCU的STO封波 0:正常  1:封波 */
            BoutV.f.Ctrl.SafetyStop = 1;
            if( STO_ALM_WRN )           // 0：故障     1：警告
            {/* 开启不使能时报警告 */
                if( BinV.f.BaseEnable )
                {/* 使能 */
                    KPI_ALARMSET( ALM_STOError );
                }
                else
                {
                    KPI_WARNINGSET( WRN_STO );
                }
            }
            else
            {
                KPI_ALARMSET( ALM_STOError );
            }
        }
        else
        {
            STO_FaultReset();
            BoutV.f.Ctrl.SafetyStop = 0;
            KPI_WARNINGCLR( WRN_STO );
        }
    }
    else
    {
        BoutV.f.Ctrl.SafetyStop = 0;
    }
}

/****************************************************************************************************/
/*                                                                                                  */
/*      STO故障自复位（125us SCANB）                                                                             */
/*                                                                                                  */
/****************************************************************************************************/
void STO_FaultReset( void )
{
    //故障复位
    if( STO_24VAlmResetMode && !STO_ALM_WRN )
    {/* 无硬件封波信号且开启自动复位信号 */
        if( (STO1_Status == 0)  && (STO2_Status == 0) && BoutV.f.Ctrl.SafetyStop )
        {/* 24V断开复位与报24V断开报警才可进行 */
            DIDOVar.DISt.AlmReset = 1;        /* 故障复位     */
        }
    }
}

/*******************************************File End*******************************************/

