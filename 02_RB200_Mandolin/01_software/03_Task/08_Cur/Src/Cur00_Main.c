/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Cur00_Main.c
* Version            : V0.1
* Date               : 2024
* Description        : 电流环控制主程序
***********************************************************************************************/
  
#include "Cur00_Main.h"
 CURRENTLOOPVAR CurrentLoopVar;
TRQCTRL TrqCtrl;
 
LONG PcalLDidt( KSGAIN Le );
float FPcalLDidt( float Le );
LONG PcalDqAcrFilter( LONG Tf );
float FPcalDqAcrFilter( LONG Tf );
  

/**********************************************************************************************/
/* Function_Name: CurrentLoopCoeff_Init         */
/* Description  : 电流环路
                  SCANA调用：转矩模式下相关变量初始化
                  输入：
                  输出：滤波后转矩指令    */
/**********************************************************************************************/
void CurrentLoopCoeff_Init( void )
{
LONG kx;

 #if( FPGAUse == 1 )
USHORT CurShant = 0;
     if( ( Prm.syssw2 & 0x0200 )  ==  0x0200 )
        SysBitDef2.f.IFbkType = 1;
    else
        SysBitDef2.f.IFbkType = 0;
     if( SysBitDef2.f.AcrType == 1 )
    {
        if( ( Prm.syssw2 & 0x0400 )  ==  0x0000 )
            SysBitDef2.f.NoiseFil = 0;
        else
            SysBitDef2.f.NoiseFil = 1;
    }
    else
    {
        SysBitDef2.f.NoiseFil = 0;
    }
     if( Iprm.CurICSel == 0 )
    {
        CurShant = Prm.shant1;
    }
    else
    {
        CurShant = Prm.shant2; 
    }
    CurrentLoopVar.CurrentCoeff = CurShant;
     ASIC_WR(MREG_Addr003F,SysBitDef2.w);                             
     kx = PcalPwmFrequency(Prm.pwmf);
     CurrentLoopVar.PWM_Priod    = kx;
    LpxSetPrmToASIC( MREG_Addr0100, kx, 0 );
    kx = (LONG)(Prm.odt_c & 0x00FF) * 1000 / FPGA_CLKns;
 #if FPGA_CLK
    if(kx < 120) 
        kx = 120;
#else
    if(kx < 150) 
        kx = 150;    
#endif
     CurrentLoopVar.PWM_DeadTime = kx;
    LpxSetPrmToASIC( MREG_Addr0101, kx,  0 );
#else
    /*** PWM周期计数值与死区计数值配置，CLA计算中用 ***/
    kx = PcalPwmFrequency( Prm.pwmf );
    CurrentLoopVar.PWM_Priod    = kx;
 #ifdef CPU1
    ACRCom.PWMPeriod = (float)kx / 16384.0f;
#endif
     kx = (LONG)(Prm.odt_c & 0x00FF) * 1000 / FPGA_CLKns;
    //最小死区时间设置1.5us
     if(kx < 300)     
    {
        kx = 300;
    }
    CurrentLoopVar.PWM_DeadTime = kx;
 #endif
 
#if( FPGAUse == 1 )
    LpxSetPrmToASIC( MREG_Addr0104, PcalDqRxComp( Bprm.MotR ), 1 );
    LpxSetPrmToASIC( MREG_Addr0105, PcalDqLxComp( Bprm.MotLd ), 1 );
    LpxSetPrmToASIC( MREG_Addr0106, PcalDqLxComp( Bprm.MotLq ), 1 );
    CurrentLoopVar.EmfCompCoeff = PcalDqEmfComp( Bprm.MotEmf );
    CurrentLoopVar.EmfCompLimit = (ULONG)Bprm.NorRatSpd1 * CurrentLoopVar.EmfCompCoeff >> 15;
    if( CurrentLoopVar.EmfCompLimit > 15000 ) CurrentLoopVar.EmfCompLimit = 15000;
#else

    /*** DQ轴电感、电阻与反电势系数标幺计算 ***/
    Acr_P[0].RxComp       = FPcalDqRxComp( Bprm.fMotR );
    Acr_P[0].LdComp       = FPcalDqLxComp( Bprm.fMotLd );
    Acr_P[0].LqComp       = FPcalDqLxComp( Bprm.fMotLq );
    Acr_P[0].EmfCompCoeff = FPcalDqEmfComp( Bprm.fMotEmf );
#endif
 #if( FPGAUse == 1 )
    LpxSetPrmToASIC( MREG_Addr0109, PcalDqAcrKp( Prm.ignd, Bprm.MotLd ), 1 );
	LpxSetPrmToASIC( MREG_Addr010A, PcalDqAcrKp( Prm.ignq, Bprm.MotLq ), 1 );
	LpxSetPrmToASIC( MREG_Addr010B, PcalDqAcrKi( Prm.kid, CurrentLoopVar.DKp ), 1 );
	LpxSetPrmToASIC( MREG_Addr010C, PcalDqAcrKi( Prm.kiq, CurrentLoopVar.QKp ), 1 );
#else
	/*** DQ轴电流环PI增益标幺计算 ***/
	Acr_P[0].Cur_DKp = FPcalDqAcrKp( Prm.ignd, Bprm.fMotLd );
	Acr_P[0].Cur_QKp = FPcalDqAcrKp( Prm.ignq, Bprm.fMotLq );
	Acr_P[0].Cur_DKi = FPcalDqAcrKi( Prm.kid, Acr_P[0].Cur_DKp );
	Acr_P[0].Cur_QKi = FPcalDqAcrKi( Prm.kiq, Acr_P[0].Cur_QKp );
#endif
 #if( FPGAUse == 1 )
    LpxSetPrmToASIC( MREG_Addr010D, Prm.limintd, 1 );
    LpxSetPrmToASIC( MREG_Addr010E, Prm.limintq, 1 );
#else
    /*** DQ轴电流限制值处理 ***/
    Acr_P[0].DQKiLimitMax = (float)Prm.limintd;
    Acr_P[0].DQKiLimitMin = -Acr_P[0].DQKiLimitMax;
#endif
 #ifdef CPU1
#if( FPGAUse == 1 )
    if( Iprm.MosfetPumpFlag == 0x01 )
    {
         if( Iprm.MosfetPumpFlag == 1 )
        {
             ukx = ((ULONG)1000000 * 10 / Prm.pwmf)  * 1000 / FPGA_CLKns;
            if( Iprm.ServoSeries == 1 )
            {
                ukx = ukx * 60 / 1000;                   
            }
            else
            {
                ukx = ukx * 49 / 1000;                   
            }
            if( ukx < CurrentLoopVar.PWM_DeadTime )
            {
                ukx = CurrentLoopVar.PWM_DeadTime;
            }
              
            CurrentLoopVar.PWM_PriodMax = CurrentLoopVar.PWM_Priod - ukx;
            LpxSetPrmToASIC( MREG_Addr010F, CurrentLoopVar.PWM_PriodMax, 1 );
            CurrentLoopVar.PWM_PriodMin = CurrentLoopVar.PWM_DeadTime;
            LpxSetPrmToASIC( MREG_Addr0110, CurrentLoopVar.PWM_PriodMin, 1 );
        }
        else
        {   
            CurrentLoopVar.PWM_PriodMax = CurrentLoopVar.PWM_Priod - CurrentLoopVar.PWM_DeadTime;
            LpxSetPrmToASIC( MREG_Addr010F, CurrentLoopVar.PWM_PriodMax, 1 );
            CurrentLoopVar.PWM_PriodMin = CurrentLoopVar.PWM_DeadTime;
            LpxSetPrmToASIC( MREG_Addr0110, CurrentLoopVar.PWM_PriodMin, 1 );
        }
    }
    else
    {
          
         CurrentLoopVar.PWM_PriodMax = CurrentLoopVar.PWM_Priod - CurrentLoopVar.PWM_DeadTime;
        LpxSetPrmToASIC( MREG_Addr010F, CurrentLoopVar.PWM_PriodMax, 1 );
         CurrentLoopVar.PWM_PriodMin = CurrentLoopVar.PWM_DeadTime;
        LpxSetPrmToASIC( MREG_Addr0110, CurrentLoopVar.PWM_PriodMin, 1 );
    }
#else
    /*** 根据自举状态和使能状态，分别计算PWM发波限制值计算处理 ***/
    ULONG ukx = 0;

    if( Iprm.MosfetPumpFlag == 1 )
    {
        ukx = 10000000000.0f / (float)Prm.pwmf / (float)FPGA_CLKns;

        if( ( Prm.syssw2 & 0x0100 )  ==  0x0000 )
        {
             ukx = 7.5f * 1000.0f * 10.0f / (float)FPGA_CLKns;
         }
        else
        {
             ukx = 4.0f * 1000.0f * 10.0f / (float)FPGA_CLKns;
        }
        if( ukx < CurrentLoopVar.PWM_DeadTime )
        {
            ukx = CurrentLoopVar.PWM_DeadTime;
        }
        //ACRCom.PWMPeriodMax = CurrentLoopVar.PWM_Priod - ukx;
        ACRCom.PWMPeriodMax = CurrentLoopVar.PWM_Priod - CurrentLoopVar.PWM_DeadTime;
        ACRCom.PWMPeriodMin = CurrentLoopVar.PWM_DeadTime;
        ACRCom.ADCSample    = CurrentLoopVar.PWM_Priod - ukx - 100;
        ACRCom.PWMPeriodMax1 = CurrentLoopVar.PWM_Priod - CurrentLoopVar.PWM_DeadTime;
    }
    else
    {
        ACRCom.PWMPeriodMax = CurrentLoopVar.PWM_Priod - CurrentLoopVar.PWM_DeadTime;
        ACRCom.PWMPeriodMax1 = ACRCom.PWMPeriodMax;
        ACRCom.PWMPeriodMin = CurrentLoopVar.PWM_DeadTime;
        ACRCom.ADCSample    = CurrentLoopVar.PWM_Priod - CurrentLoopVar.PWM_DeadTime - 100;
    }
 #endif
#endif
 #if( FPGAUse == 1 )
    LpxSetPrmToASIC( MREG_Addr0114, (USHORT)Prm.ad_prm3, 1 );            
    kx = (ULONG)Prm.ad_prm4 * (CurShant << 2) / Prm.imaxs;
    kx = 32767 + kx;
    LpxSetPrmToASIC( MREG_Addr0113, kx, 0 );
#endif

    /*** 电机瞬时最大电流大于驱动器最大电流下，电流转换系数1&2的计算 ***/
    if( Prm.imax >= Prm.imaxs )
    {
#if( FPGAUse == 1 )
          
         kx = (ULONG)30720000 / CurShant;
        LpxSetPrmToASIC( MREG_Addr0115, kx, 1 );
          
         kx = (ULONG)17736200 / CurShant;
        LpxSetPrmToASIC( MREG_Addr0116, kx, 1 );
#else
        Acr_P[0].Cur_Coeff1 = 15000.0f / (float)Prm.shant1;
        Acr_P[0].Cur_Coeff2 = 8660.254038f / (float)Prm.shant1;
#endif
    }
    /*** 电机瞬时最大电流小于驱动器最大电流下，电流转换系数1&2的计算 ***/
    else
    {
#if( FPGAUse == 1 )
        LONG sx;
        kx = MlibScalKxgain( 15000  , 2048      , CurShant, &sx,   0 );
        kx = MlibPcalKxgain( kx     , Prm.imaxs , Prm.imax , &sx, -24 );
        LpxSetPrmToASIC( MREG_Addr0115, kx, 0 );
         kx = MlibScalKxgain( 5000   , 3547      ,     CurShant,   &sx,   0 );
        kx = MlibPcalKxgain( kx     ,  Prm.imaxs, Prm.imax, &sx, -24 );
        LpxSetPrmToASIC( MREG_Addr0116, kx, 0 );
#else
        float fx;
        fx = 15000.0f * 1.0f / (float)Prm.shant1;
        fx = fx *(float)Prm.imaxs / (float)Prm.imax;
        Acr_P[0].Cur_Coeff1 = fx;
        fx = 5000.0f * 1.731933594f / (float)Prm.shant1;
        fx = fx * (float)Prm.imaxs / (float)Prm.imax;
        Acr_P[0].Cur_Coeff2 = fx;
#endif
    }
    /*** 电流相位相关系数计算 ***/
    LpxPcalPcmpCalGain( );
 #if( FPGAUse == 1 )
    kx = PcalLDidt( Bprm.MotLd );
    LpxSetPrmToASIC( MREG_Addr0130, kx,1 );
    kx = PcalDqAcrFilter( Prm.ifil );
    LpxSetPrmToASIC( MREG_Addr0131, kx,1 );
    kx = (ULONG)8192 * ( Prm.vrevgn ) / 100;
	LpxSetPrmToASIC( MREG_Addr0132, (USHORT)kx,1 );
#else
	/*** 电流互耦di/dt系数，电压补偿增益、ud、uq轴滤波系数计算 ***/
	Acr_P[0].DDidt = FPcalLDidt( Bprm.fMotLd );
	Acr_P[0].QDidt = FPcalLDidt( Bprm.fMotLq );
	Acr_P[0].VCompGain = (float)Prm.vrevgn / 100.0f;
	Acr_P[0].DQFilter = FPcalDqAcrFilter( Prm.ifil );
#endif
	/*** 弱磁控制系数计算 ***/
    WFKVdc_Init( );
 
#ifdef CPU1
    /*** 电流采样放置设置，暂时用1 ***/
    if( ( Prm.syssw2 & 0x0100 )  ==  0x0000 )
    {
        ACR_Flag = 0;
    }
    else
    {
        ACR_Flag = 1;
    }
#endif
}
  
/**********************************************************************************************/
/* Function_Name: PcalPwmFrequency         */
/* Description  : 周期计数值计算
               输入： PWMF 载波频率Hz
               输出： PWM周期计数值  */
/**********************************************************************************************/
LONG PcalPwmFrequency(USHORT PWMF)
{
LONG	Tc = 0;
    if(PWMF == 10667)
    {
        Tc = 9375;
    }
    else if(PWMF == 5333)
    {
        Tc = 18748;
    }
    else
    {
        Tc = (float)FPGA_CLKMHZ * 500000.0f / (float)PWMF;
    }
    return( Tc );
}
  
  
/**********************************************************************************************/
/* Function_Name: KpiMonTorqueCal         */
/* Description  : 转矩监控参数计算
               输入：Torque：转矩标幺值
               输出： 转矩%   */
/**********************************************************************************************/
LONG KpiMonTorqueCal( LONG	Torque )
{
    LONG x;
    x = MlibMulgain( Torque, Iprm.Kmontrq );
    return ( x );
}
 
  
/**********************************************************************************************/
/* Function_Name: KpiMonTorqueCal1         */
/* Description  : 转矩监控参数计算（总线对象字典计算用）
               输入：Torque：转矩标幺值
               输出： 转矩0.1%   */
/**********************************************************************************************/
LONG KpiMonTorqueCal1( LONG	Torque )
{
    LONG x;
    x = MlibMulgain( Torque, Iprm.kmontrq1 );
    return ( x );
}
 
  
  
/**********************************************************************************************/
/* Function_Name: KpiMonTorqueCal1         */
/* Description  : 电流转矩监控参数计算
               输入：Current：负载电流值（标幺值）
               输出： 电流%   */
/**********************************************************************************************/
LONG KpiMonCurrentCal( LONG  Current )
{
    LONG x;
#if(FLOAT_USE == 1)
    x = (float)Current * Iprm.fKmoncrnt;
#else
    x = MlibMulgain( Current, Iprm.Kmoncrnt );
#endif
    return ( x );
 }
  
  
/**********************************************************************************************/
/* Function_Name: KpiMonCurrentCal1         */
/* Description  : 电流转矩监控参数计算
               输入：Current：负载电流值（标幺值）
               输出： 电流 0.1%   */
/**********************************************************************************************/
LONG KpiMonCurrentCal1( LONG  Current )
{
#if(FLOAT_USE == 1)
    float fx;
    fx = Iprm.fKmoncrntA * AinK.IeeMonitor / (float)Prm.shant1;
    //fx1 = AinK.IeeMonitor  * 102.4f * (float)Iprm.fKmoncrntA / (float)Prm.irat  ;
    //fx1 = fx * 1414.0f / (float)Prm.irat  ;
    CoutV.UnCrntDet = (LONG)fx;  //转换为%

    return ( (LONG)fx );
#else
    ULONG x;
    x = (ULLONG)Iprm.KmoncrntA * AinK.CurrentTmp / Prm.shant1;
    x = x >> 11;
    return ( x );
#endif
 }
  
  
/**********************************************************************************************/
/* Function_Name: PcalLDidt         */
/* Description  : di/dt系数计算
               输入：Le：电感值（标幺值）
               输出： di/dt系数   */
/**********************************************************************************************/
LONG	PcalLDidt( KSGAIN Le )
{
LONG	kx,sx;
ULONG   ScanTimens;
    if( SysBitDef2.f.AcrType == 0 )
        ScanTimens = (ULONG)FPGA_CLKns * CurrentLoopVar.PWM_Priod / 10;
    else
        ScanTimens = 15625;
    kx = MlibScalKskskx( Le,   Bprm.MaxCur,  15000,          &sx,   0 );
    kx = MlibPcalKxkxks( kx,   16384UL*256,    Bprm.Vdc,       &sx,   0 );
    kx = MlibPcalKxgain( kx,   1000000000,   ScanTimens,     &sx, -24 );
    return( kx );
}


/**********************************************************************************************/
/* Function_Name: FPcalLDidt         */
/* Description  : di/dt系数计算（浮点）
               输入：Le：电感值（标幺值）
               输出： di/dt系数   */
/**********************************************************************************************/
float FPcalLDidt( float Le )
{
float   fkx;
float   ScanTimens = (float)FPGA_CLKns * CurrentLoopVar.PWM_Priod / 10.0f;
    if( ( Prm.syssw2 & 0x0100 )  ==  0x0100 )
    {
        ScanTimens *= 2.0f;
    }
    fkx = Le * Bprm.fMaxCur / 15000.0f;
    fkx = fkx * 16384.0f / Bprm.fVdc;
    fkx = fkx * 1000000000.0f / ScanTimens;
    return( fkx );
}
 

/**********************************************************************************************/
/* Function_Name: KpiPcalMicroLpassFilter1         */
/* Description  : 低通滤波系数计算（暂未用）
               输入：
               输出：   */
/**********************************************************************************************/
void	KpiPcalMicroLpassFilter1(				 
		LONG	tf,								 
		LONG	ts,								 
		VUSHORT *MpReg	)						 
{
LONG	kf;
    kf = MlibScalKxgain( ts, (1<<14), (ts + tf), NULL, -24 );
    ASIC_WR( MpReg[0], (USHORT)kf );
    return;
}
 
  
/**********************************************************************************************/
/* Function_Name: PcalDqAcrFilter         */
/* Description  : 低通滤波系数计算（暂未用）
               输入：
               输出：   */
/**********************************************************************************************/
LONG	PcalDqAcrFilter( LONG Tf )
{
LONG	kx;
LONG    KPI_MACYCLE_ns;
    if( SysBitDef2.f.AcrType == 0 )
    {
        KPI_MACYCLE_ns = FPGA_CLKns * CurrentLoopVar.PWM_Priod;
        kx = MlibScalKxgain( KPI_MACYCLE_ns, 16384, ((1000UL*Tf) + KPI_MACYCLE_ns), NULL, -24 );
        if( kx == 0 )
        {
            kx = 16384;
        }
        return( kx );
    }
    else
    {
        kx = MlibScalKxgain( 15625, 16384, ((1000UL * Tf) + 15625UL), NULL, -24 );
        if( kx == 0 )
        {
            kx = 16384;
        }
        return( kx );
    }
}
 
  
/**********************************************************************************************/
/* Function_Name: FPcalDqAcrFilter         */
/* Description  : 低通滤波系数计算（浮点）
               输入： ud，uq给定值
               输出： ud，uq滤波后  */
/**********************************************************************************************/
float FPcalDqAcrFilter( LONG Tf )
{
float fkx;
    fkx = (float)CurrentLoopVar.PWM_Priod * (float)FPGA_CLKns * 0.1;
    if( ( Prm.syssw2 & 0x0100 )  ==  0x0100 )
    {
        fkx *= 2.0f;
    }
    fkx = FlibPcalKf1gain( (Tf * 1000), fkx, 0x0010 );
    return fkx;
}
 
 
 
 
  
 
 
 
