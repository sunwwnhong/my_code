 /**********************************************************************************************
* File Name   : Mot43_DBBrakeProtect.c
* Version     : V0.1
* Date        : 2024
* Description : 功率相关故障处理-DB过载（暂时未用）
**********************************************************************************************/

  
  
#include "Main.h"
 
 
/************************************************************************************************/
/* Function_Name: LpxCheckDbrakeOverLoad                              */
/* Description  : DB过载保护
          故障码：730-DB过载故障；921-DB过载警告
          参数码：PnE0E-内置动态制动(DB)抵抗容量      [ % ]
                  PnE1C.03 DB制动保护开关             [   ]
          输入  ：DB过载保护 模块API输入接口
          输出  ：DB过载保护 模块API输出接口                       */
/************************************************************************************************/
void LpxCheckDbrakeOverLoad( void )
{
	LONG x;
	LONG DbPower;
  
    /*-----------------判断是否有内置动态刹车（DB），无则退出-----------------------------------*/
    if( ChkAlmP.DbolPowBase == 0 )
        return;
  
    /*-----------------判断动态制动保护开关是否关闭，关闭则退出    0-开启；1-关闭---------------*/
    if( (Prm.syssw2 & 0x0004) == 0x0004 )
    {
        return;
    }
  
    /*------------------------------------------------------------------------------------------*/
    /*      DB功率计算     Built-in DB resistor existence check  内置DB电阻存在检查             */
    /*                   PowerMax * Speed * Speed                                               */
    /*      DbPower  = --------------------------- = Kdbpower * (Speed>>9) * (Speed>>9)         */
    /*                     SpdLevel * SpdLevel                                                  */
    /*------------------------------------------------------------------------------------------*/
	if( CoutV.f.Sv.DbOn )
	{     
		if( CinK.AbsMotSpd >= ChkAlmP.DbolSpdLevel )
		{
			DbPower = ChkAlmP.DbolPowMax;
		}
		else
		{
			x		= ( CinK.AbsMotSpd>>9 );
			DbPower = MlibMulgainSx48( ( x * x ), ChkAlmP.Kdbpower );
		}
	}
	else
	{
		DbPower  	   = 0;
		ChkAlmV.DbHeat = 0;
	}
  
  
	ChkAlmV.DbolPowSum += ( DbPower - ChkAlmP.DbolPowBase );

 	if( ChkAlmV.DbolPowSum > 0x40000000 )
	{
		ChkAlmV.DbolPowSum = 0x40000000;
	}
	if( ChkAlmV.DbolPowSum < 0 )
	{
		ChkAlmV.DbolPowSum = 0;
	}
  
    /*-----------------------------------DB过载检查---------------------------------------------*/
	if( ChkAlmV.DbolPowSum >= ChkAlmP.DbolAlmLevel )
	{
		KPI_ALARMSET  ( ALM_DBOL );  				 
	}
  
    /*------------------------------------------------------------------------------------------*/
    /*      Un00B : DB电阻耗电用数据（10sec DB耗电平均值）  CoutV.UnMeanDbPower                 */
    /*      Un144 : DB负载累加值    （2ms   DB功耗值）      CoutV.UnDBPower                     */
    /*------------------------------------------------------------------------------------------*/
    CoutV.UnDbPower = MlibScalKxgain( ChkAlmV.DbolPowSum, 1000, ChkAlmP.DbolAlmLevel, NULL, -30 );
	CoutV.TrcDbPower	= CoutV.UnDbPower;
  
  
    if( ChkAlmV.DbolPowSum >= (ChkAlmP.DbolAlmLevel >> 1) )
    {
        KPI_WARNINGSET	( WRN_DBOL_LVL );
    }
    else
    {
        KPI_WARNINGCLR	( WRN_DBOL_LVL );						 
    }
     return;
}
 
  
/************************************************************************************************/
/* Function_Name: PcalDbrakeOverLoadLevel                              */
/* Description  : DB过载功率计算（1.DB过载允许功率，2.DB过载报警级别）
          输入  ：DB过载计算 模块API输入接口
          输出  ：DB过载计算 模块API输出接口                       */
/************************************************************************************************/
void PcalDbrakeOverLoadLevel( void )
{
	LONG kx,
		 sx,
		 cx;
  
	if( Prm.dbres == 0 )		// 设定值为0的情况
	{
		ChkAlmP.DbolPowBase = Prm.wdb;		    // DB抵抗容量（默认）
	}
	else if( ( Prm.dbres * 10 ) <= Prm.ampw )	// 伺服驱动器功率以内的情况
    {
        ChkAlmP.DbolPowBase = ( Prm.dbres * 50000 ) / Prm.ampw;
    }
    else
    {
        KpiSetParamError( &pndef_dbres );		 // 参数设定异常
        return;
    }
	/*--------------------------------------------------------------------------------------------------*/
	/*   DB过载阈值计算                                                                                 */
	/*      SGDS : AlmLevel = ((PowBase * 2) * 429 * 1000 ) / SCCYCLEMS                                 */
	/*       ΣⅡ : AlmLevel = ((PowBase * 2) * 429 * 1000000 ) / SCCYCLEUS / 65536                      */
	/*      说明 :  1) 伺服额定输出持续100ms时报警                                                      */
	/*              2) DB允许功率* 2连续100sec报警                                                      */
	/*              3) DB允许功率* 2连续报警500sec                                                      */
	/*              4) 如果是500sec的话，就会溢出，所以改为429sec                                       */
	/*--------------------------------------------------------------------------------------------------*/
 	ChkAlmP.DbolAlmLevel = ChkAlmP.DbolPowBase * ( ( 2 * 429000 ) / KPI_SCCYCLEMS );

 	/*--------------------------------------------------------------------------------------------------*/
 	/*      ＤＢ消費電力ょ殑算するための绥殑。消費電力が飽和する変極点の速度                            */
 	/*                                                                                                  */
 	/*                          (Bprm.MotR + ((DBR/1000)/sqrt(3))) * 2^24                               */
 	/*      SVOS :  SpdLevel = ---------------------------------------------                            */
 	/*                            Bprm.MotL * (PoleNo/2) * Bprm.OvrSpd                                  */
 	/*                                                                                                  */
 	/*                          (MotR + DBR/sqrt(3))/1000 * (60/(2*PAI)) * 15000                        */
 	/*       ΣⅡ :  SpdLevel = ---------------------------------------------------                       */
 	/*                              (MotL/100000) * (PoleNo/2) * nos                                    */
 	/*--------------------------------------------------------------------------------------------------*/
	kx = MlibScalKskxkx( Bprm.MotR, 173205, 1, NULL, -30 ) + ( Prm.dbr * 100 );
	kx						= MlibScalKxgain( kx, 1, 173205, &sx, 0 );
	kx						= MlibPcalKxkxks( kx, 1, Bprm.Keangle, &sx, 0 );
	kx						= MlibPcalKxkxks( kx, 1, Bprm.MotLdb, &sx, 0 );
	kx = MlibPcalKxkxks( kx, 0x01000000, Bprm.OvrSpd, &sx, -30 );
	ChkAlmP.DbolSpdLevel	= kx;
  
	/*--------------------------------------------------------------------------------------------------*/
	/*      DB过载饱和功率的计算                                                                        */
	/*                      |       Bprm.MotEmf       |^2     DBR      5000     (PAI + 3*sqrt(3) /2)    */
	/*      SVOS : PowMax = |-------------------------|    * ------ * ------ * -------------------      */
	/*                      | (Bprm.MotL * (PoleNo/2))|       1000     AMPW            PAI              */
	/*                                                                                                  */
	/*                      |((MotEmf/10000)*(60/(2PAI)|^2     DBR     5000     (PAI + 3*sqrt(3))       */
	/*      ΣⅡ  : PowMax = |--------------------------|   * ------ * ------ * -------------------      */
	/*                      |((MotL/100000)*(PoleNo/2) |       1000    AMPW          PAI                */
	/*                                                                                                  */
	/*                    = (MotEmf*22263/PoleNo/MotL)^2 / AMPW * DBR >> 10                             */
	/*                                                                                                  */
	/*      ΣⅡ : Soft    = (MotEmf*13061/PoleNo/MotL)^2 / AMPW * DBR >> 10                             */
	/*--------------------------------------------------------------------------------------------------*/
	/*      补 充1: PAI+3*sqrt(3)/2是考虑了3相量的系数                  MotEmf电动势                    */
	/*      补 充2: 因为计算和预算不一致，所以先1/2（从Sigma2继承.）                                    */
	/*--------------------------------------------------------------------------------------------------*/
	/*      旋转型：Bprm.Keangle = PoleNo / 2       : Motor[rad] ---> Eangle[rad]                       */
	/*      直线型：Bprm.Keangle = PAI / PolePitch  : Motor[ m ] ---> Eangle[rad]                       */
	/*--------------------------------------------------------------------------------------------------*/
	cx = (Kprm.AmpType == AMPTYPE_ROTARY)? 50000 : 290531;
 	kx = MlibScalKxgain( 1, 5 * 5739669, 3141593, &sx, 0 );
	kx						= MlibPcalKxgain( kx, Prm.dbr, Prm.ampw, &sx, 0 );
	kx						= MlibPcalKxkxks( kx, 1, Bprm.Keangle, &sx, 0 );
	kx						= MlibPcalKxkxks( kx, 1, Bprm.Keangle, &sx, 0 );
	kx = MlibPcalKxksks( kx, Bprm.MotEmf, Bprm.MotLdb, &sx, 0 );
	kx = MlibPcalKxksks( kx, Bprm.MotEmf, Bprm.MotLdb, &sx, 0 );
	kx						= MlibPcalKxgain( kx, cx, 100000, &sx, -30 );
	ChkAlmP.DbolPowMax		= kx;
  
	/*--------------------------------------------------------------------------------------------------*/
	/*      DB功率增益的计算                                                                            */
	/*                      PowerMax * 2^18                                                             */
	/*      Kdbpower = ------------------------                                                         */
	/*                   SpdLevel * SpdLevel                                                            */
	/*                                                                                                  */
	/*                   PowerMax * Speed * Speed                                                       */
	/*      DbPower  = --------------------------- = Kdbpower * (Speed>>9) * (Speed>>9)                 */
	/*                     SpdLevel * SpdLevel                                                          */
	/*--------------------------------------------------------------------------------------------------*/
	kx = MlibScalKxgain( 1, ChkAlmP.DbolPowMax, ChkAlmP.DbolSpdLevel, &sx, 0 );
	kx = MlibPcalKxgain( kx, ( 1UL<<18 ), ChkAlmP.DbolSpdLevel, &sx, 48 );
	ChkAlmP.Kdbpower		= kx;
 
	return;
 }
