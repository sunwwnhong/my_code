/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Spd03_SoftStart.c
* Version            : V0.1
* Date               : 2024
* Description        : 零速钳位处理
***********************************************************************************************/


#include "Main.h"
 

  
/**********************************************************************************************/
/* Function_Name: ZeroPositionControl                                                        */
/* Description  : 零伺服控制
                  SCANA调用                                                   */
/**********************************************************************************************/
LONG ZeroPositionControl( LONG	dPosFbk )
{
	LONG SpdRef;
  
	/*  变量初始化：控制模式初次变更时 */
	if( BoutV.ZctrlMode.b.zmchg || ( BinV.f.BaseEnable == FALSE ) )
	{
		ZxCtrl.V.PosError = 0;
	}
	/*  零箝位控制   Zero clamp control*/
 	ZxCtrl.V.PosError -= dPosFbk;		//位置偏差计算
	SpdRef	= MlibMulgain( ZxCtrl.V.PosError, GselGains[ 0 ].ZcKp );    //位置控制运算（P控制）

	if( SpdRef == 0 )                                   //速度指令0时的修正
	{
		if( ZxCtrl.V.PosError > 0 )
		{
			SpdRef = 1;
		}
		else if( ZxCtrl.V.PosError < 0 )
        {
            SpdRef = -1;
        }
	}
 	else if( SpdRef > Gprm.ZclampMaxSpd )		// 速度指令上限
    {
        SpdRef = Gprm.ZclampMaxSpd;
    }
    else if( SpdRef < -Gprm.ZclampMaxSpd )	    // 速度指令下限
    {
        SpdRef = -Gprm.ZclampMaxSpd;
    }
 	return ( SpdRef );
}

/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/
