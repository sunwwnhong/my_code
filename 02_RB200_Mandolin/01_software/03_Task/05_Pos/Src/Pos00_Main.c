/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Pos00_Main.c
* Version            : V0.1
* Date               : 2023
* Description        : 位置控制器
***********************************************************************************************/
  
#include "Main.h"
 
POSMNGV PosMngV;
POSCTRL PosCtrl;
 

/**********************************************************************************************/
/* Function_Name: InitBasePositionControl                                                          */
/* Description  : 位置控制变量初始化                                                          */
/**********************************************************************************************/
void InitBasePositionControl( void )
{
    MlibResetLONGMemory( &PosCtrl.V, (sizeof(PosCtrl.V)) / 2 );
    return;
}
 
  
/**********************************************************************************************/
/* Function_Name: BasePositionControl                                                          */
/* Description  :位置PID控制
           输入：
           输出：SpdRefx:速度指令给定输出
                 PosErr：位置误差                                                             */
/**********************************************************************************************/



//#ifdef RunRAM
//#pragma CODE_SECTION(BasePositionControl, ".TI.ramfunc");
//#endif

LONG BasePositionControl( LONG dPosRef, LONG dPosFbk, LONG PerClrCmd, LONG IcvClrCmd,LONG PerClrEdge )
{
	LONG SpdRefx;
  
	//位置偏差信号有效时，对误差进行清除
	if( PerClrCmd )
	{
		PosCtrl.V.PerIvar64[ 0 ] = 0;
		PosCtrl.V.PerIvar64[ 1 ] = 0;
		PosCtrl.V.LastPacOut	 = 0;
		return ( 0 );
	}
	//位置偏差计算，减速停机时，将不会更新位置误差
 	if( !( BoutV.ZctrlMode.b.zm == CTRLMODE_DSTOP ) )
	{
		PosMngV.PosErr = MlibPerrcalx( dPosRef, dPosFbk, PosMngV.Per64 );
	}
  
 	//比例环节计算
	PosCtrl.V.PacOut = MlibMulgain( PosMngV.PosErr, GselGains[ 0 ].Kp );
  
	//积分环节计算
	if( BinV.f.BaseEnable == FALSE )							 
	{
		PosCtrl.V.PerIvar64[ 0 ] = 0;
		PosCtrl.V.PerIvar64[ 1 ] = 0;
		PosCtrl.V.IacOut		 = 0;
	}
	else
    {
		if( PosCtrl.P.Kpi == 0 )
		{
			PosCtrl.V.IacOut = ( ( PosCtrl.V.PerIvar64[ 1 ] + 1 ) >>1 );
		}
		else
		{
			PosCtrl.V.IacOut = MlibIntegral( PosCtrl.V.PacOut, PosCtrl.P.Kpi, PosCtrl.V.PerIvar64 );
		}
    }

	//位置环输出计算
 	SpdRefx = PosCtrl.V.PacOut + PosCtrl.V.IacOut;
  
 	//位置误差不为0时，对位置最小调节输出进行最小值限制
	if( SpdRefx == 0 )                                           
	{
		if( PosMngV.PosErr > 0 )
		{
			SpdRefx = 1;
		}
		else
		{
			if( PosMngV.PosErr < 0 )
			{
				SpdRefx = -1;
			}
		}
	}
  
	//位置环输出限幅处理
    SpdRefx = MlibLimitul(SpdRefx,Iprm.MaxSpd, -Iprm.MaxSpd);
    if( Kprm.f.EtherCATNet == 1)
    {
        SpdRefx = MlibLimitul(SpdRefx,  Iprm.EthCatMaxSpd,    -Iprm.EthCatMaxSpd);
    }
    else if( Kprm.f.CanOpenNet == 1 )
    {    
        SpdRefx = MlibLimitul(SpdRefx,  CanSpdV.MaxSpdLimt,    -CanSpdV.MaxSpdLimt);    
    }
    else
    {;}
 	PosCtrl.V.SpdRef = MlibLimitul( SpdRefx, Bprm.NorMaxSpd, -Bprm.NorMaxSpd );
	return ( PosCtrl.V.SpdRef );
 }
  
  

  
/**********************************************************************************************/
/* Function_Name: InitPosCtrlModeVar                                                     */
/* Description  : 位置控制模式切换初次变量初始化
                  BpxYecServoControl调用                                  */
/**********************************************************************************************/
void InitPosCtrlModeVar( void )
{
 	switch( BoutV.CtrlModeLst.b.cm )		//上次基本控制模式
 	{
		case CTRLMODE_SPD:				    //从速度控制模式切换过来
 			BoutV.SpdRfFilo = BoutV.SpdRefo;		//速度指令滤波器输出
 																 
 			//内部速度模式切换至位置模式，清除速度指令滤波值
 			if( ( BoutV.CtrlModeLst.us[ 0 ] == CTRLMODE_CSPD ) || ( Iprm.f.CtrlSW3Step == TRUE ) )
			{
				BoutV.SpdRfFilo = 0;
			}
			RpiANotchDisableReqSet( );          //自动陷波分析强制无效
 			break;
 		case CTRLMODE_TRQ:			        //从转矩控制模式切换过来
 			BoutV.SpdRfFilo = 0;			//速度指令滤波器输出
 			if( Gprm.f.Dobs )               //  DOB有效
			{													 
 				TrqFil.V.TrqFilClrCmd = TRUE;	//转矩指令滤波积分初始化
			}													 
  
			if( RoutV.f.TunLessCtrlOffSts == FALSE )		//免调整强制无效
			{
				Gprm.f.TuningLess = Iprm.f.TuningLess;      //免调整速度相位超前滤波器初始化
			}													 
 																 
 			SpdCtrl.V.SpdRefFilClrCmd = TRUE;		        //速度指令相位超前补偿滤波器初始化
			SpdCtrl.V.SpdFFFilClrCmd  = TRUE;			    //速度FF相位超前补偿滤波器初始化
 			RpiANotchDisableReqSet( );                      //自动陷波分析强制无效
			break;
	}
 	return;
}
