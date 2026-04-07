/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot12_MoSenclf.c
* Version            : V0.1
* Date               : 2024
* Description        : 编码器位置读取和分频输出处理
***********************************************************************************************/


#include "Main.h"
#include "CLA03_TFormat.h"
 
#define	TIMBASECLK		20								            /* 编码器时钟频率[MHz]: 20 MHz             */
#define	SAENCCLKNUM		(KPI_SACYCLENS*TIMBASECLK/1000)	            /* 编码器运行周期的时钟数: 62.5us=1250      */
#define	ENCLCHCLKNUM	50								            /* 编码器latch周期(2.5[us])的时钟数        */
#define Enc2P5MTime     0                                           /* 编码器启动滞后时间(相对于ARM)[us]        */
#define Enc4P0MTime     25                                          /* 编码器启动滞后时间(相对于ARM)[us]        */
#define EncBound2P5M    (Enc2P5MTime * FPGA_CLKMHZ)                 /* 转换为FPGA时钟单位                       */
#define EncBound4P0M    (Enc4P0MTime * FPGA_CLKMHZ)                 /* 转换为FPGA时钟单位                       */
 
volatile LONG PULSEIN = 0;
volatile LONG PULSEOUT = 0;
  
/*--------------------------------------------------------------------------------------------------*/
/*      编码器位置信息的处理部分程序功能                                                            */
/*--------------------------------------------------------------------------------------------------*/
void	LpxSencComErrorProc( LONG RcvPosX, LONG AccErr );	   /* 串行编码器通信異常処理             */
  
  
MENCP	MencP;										          /* 电机编码器：固定数据                */
MENCV	MencV;										          /* 电机编码器：可变数据                */
 
 
/*--------------------------------------------------------------------------------------------------*/
/*      扫描处理函数                                                                                  */
/*--------------------------------------------------------------------------------------------------*/
void RmxReadSencPosition( void );				            /* 旋转型:串行式编码器位置信息读取          */
void RmxReadErrPosition(void);                              /* 旋转型:读取的位置信息错误处理            */
void RmxSencInitParamCalc( void );                          /* 编码器参数的计算                         */
LONG LpxTimeBasesMotPosCalc(						     
			LONG RcvPosX,							     
			LONG LastMotPosX,						     
			UCHAR MposSftR );						     
  

/**********************************************************************************************/
/* Function_Name: KpxSencInitMotorEncoder         */
/* Description  : 根据编码器类型，初始化编码器相关接口函数和变量
                  调用：上电初始化调用一次
                  输入：
                  输出：   */
/**********************************************************************************************/
void	KpxSencInitMotorEncoder( void )
{
     /*--------------------------------------------------------------------------------------------------*/
     /*      根据编码器类型来确定位置读取的入口                                                           */
     /*--------------------------------------------------------------------------------------------------*/
    MencV.f.PhaseReady = TRUE;                                       /* 电机相位已知                 */
      
    /*** 若电机类型为虚拟电机，则位置读取函数使用(虚拟电机位置读取函数) ***/
    if( ((Prm.b_prm0_0 >> 12) & 0x000F ) == 0x0002 )
    {
        MencP.KpiReadMencPosition = RmxReadMotorLessPosition;
        return;
    }

    /*** 若电机编码器为增量编码器，则位置读取函数使用(增量编码器位置读取函数) ***/
    if(Prm.MotorNum >= MotorNumMin && Prm.MotorNum < MotorNumMax)
    {
        MencV.f.PhaseReady = FALSE;                                 
        KPI_ALARMSET( ALM_PRM );
        MencP.KpiReadMencPosition = RmxReadErrPosition;
    }
    else
    {
        switch(Prm.EncoderType)
        {
            case 2:     // 多摩川17bit绝对式编码器
            case 3:     // 多摩川23bit绝对式编码器
			case 11:
            case 13:	// IC-Haus编码器
                MencP.KpiReadMencPosition = RmxReadSencPosition;
                MencP.EncPulseTimeBasic = (((ULONG)KPI_SACYCLENS - 3000 - Enc2P5MTime * 1000) / 1000) * TIMBASECLK;
                break;
            case 4:     // 尼康20位单圈编码器（2.5M）
            case 5:     // 尼康20位单圈编码器（2.5M）
            case 6:     // 尼康24位单圈编码器（4M）
            case 7:     // 尼康24位多圈编码器（4M）
                MencP.KpiReadMencPosition = RmxReadSencPosition;
                MencP.EncPulseTimeBasic = (((ULONG)KPI_SACYCLENS - 3000 - Enc2P5MTime * 1000) / 1000) * TIMBASECLK;
                break;
            case 8:     // 10000线串行编码器
            default:
                 MencV.f.PhaseReady = FALSE;
                 KPI_ALARMSET( ALM_PRM );
                 MencP.KpiReadMencPosition = RmxReadErrPosition;
            break;
         }    
    }
    /*** 增量式编码器和绝对值编码器变量初始化,用于驱动器底层使用的编码器类型代码使用 ***/
 	switch(Prm.EncoderType)
	{
 		case 2: // 多摩川17bit绝对式编码器
		  	MencP.AbsoEncType = MENC_MABSO_TYPE;		// 绝对值类型编码器
			MencP.FATypeCode  = 0x01;					// 多摩川
			break;
 		case 3: // 多摩川23bit绝对式编码器
		  	MencP.AbsoEncType = MENC_MABSO_TYPE;		// 绝对值类型编码器
			MencP.FATypeCode  = 0x01;					// 多摩川
			break;
 		case 4: // 尼康20位单圈编码器（2.5M）
		case 6: // 尼康24位单圈编码器（4M）
		  	MencP.AbsoEncType = MENC_INCRE_TYPE;		// 增量式类型编码器
			MencP.FATypeCode  = 0x02;					// 尼康
			break;
 		case 5: // 尼康20位多圈编码器（2.5M）
		case 7: // 尼康24位多圈编码器（4M）
		  	MencP.AbsoEncType = MENC_MABSO_TYPE;		// 绝对值类型编码器
		  	MencP.FATypeCode  = 0x02;					// 尼康
		  	break;
        case 8:  // 10000线串行编码器
            MencP.AbsoEncType = MENC_INCRE_TYPE;	    // 增量式类型编码器
			MencP.FATypeCode  = 0x00;                   // 其他
			break;
         case 11:	// IC-Haus编码器
            MencP.AbsoEncType = MENC_MABSO_TYPE;
            MencP.FATypeCode  = 0x01;
            break;
         case 13:   // 昆泰芯编码器
             MencP.AbsoEncType = MENC_MABSO_TYPE;
             MencP.FATypeCode  = 0x01;
             break;
 		default:
            MencP.AbsoEncType = MENC_INCRE_TYPE;					 
            break;
	}
}
 
  
/**********************************************************************************************/
/* Function_Name: RmxSencInitParamCalc         */
/* Description  : 旋转型：编码器初始参数的计算
                  调用：上电初始化调用一次
                  输入：
                  输出：   */
/**********************************************************************************************/
void	RmxSencInitParamCalc( void )
{
float fkx;
LONG	kx,sx;
UCHAR   BitNo  = Prm.bit_dp.b.l;

    if( BitNo == 0 )
    {
        BitNo = 23;
    }

    /*** 增量式编码器 ***/
 	if(Prm.MotorNum >= MotorNumMin && Prm.MotorNum < MotorNumMax)
	{
        if( Iprm.IncEncResSel == 0)
        {
            MencP.PulseNo = 10000;      // 编码器分辨率选择为0（厂家默认），则分辨率为10000
        }
        else
        {
            /*** 编码器分辨率选择通过Pn793配置 ***/
            MencP.PulseNo = ULONGOF( Prm.PosOutputs2l, Prm.PosOutputs2h );  //根据配置得到分辨率
            if( MencP.PulseNo == 0 )
            {
                KpiSetParamError( &pndef_PosOutputs2l );
            }
        }
 	}
 	/*** 绝对式编码器 ***/
   	else									
	{
   	    /*** 1圈 = 2^BitNo   为了扩转为32bit,相应的移位量为 32 - BitNo ***/
        MencP.MposSftR = 32 - BitNo;
        MencP.PulseNo = ( 1UL << BitNo );
        MencP.PulseNoDiv600 = (float)MencP.PulseNo / 600.0f;
        MencP.PulseNoDiv60  = (float)MencP.PulseNo / 60.0f;
	}
 	/*** 电机相位角度(电角度)计算,一个脉冲对应的角度(4096 <=> 360°) ***/
    /*----------------------------------------------------------------------------------------------*/
    /*                         4096 * (PoleNo/2)                PulseNo  : [pulse/rev]              */
    /*          Kmotphase   = -------------------               MotPhase : [4096 /360deg]           */
    /*                             PulseNo                                                          */

    MencP.Kmotphase = MlibScalKxgain( 4096, ((Prm.oslv_pol.b.h) >> 1), MencP.PulseNo, NULL, 24 );
    MencP.fKmotphase = 4096.0f * (Prm.oslv_pol.b.h) / (2.0f * MencP.PulseNo);
  
    /*** 旋转型电机参数计算 ***/
    BprmRotaryMotorParamCal ( );		
  
    /*** 编码器的脉冲数转换成速度 ***/
#if(FLOAT_USE == 1)
    fkx = (float)C2PAIE7 / (float)Bprm.MotPulse;
    fkx = fkx / (float)C10POW7;
    fkx  = (float)0x1000000 * fkx / Bprm.fOvrSpd;
    MencP.fMotspdA = fkx * 1000000000.0f/ (float)KPI_SACYCLENS;
#else
    kx = MlibScalKxgain( C2PAIE7, 1, Bprm.MotPulse, &sx,  0 );
    kx = MlibPcalKxgain( kx, 1,  C10POW7, &sx, -1 );
    kx  = MlibScalKxksks( 0x1000000, kx, Bprm.OvrSpd, &sx, -1 );
    MencP.MotspdA = MlibScalKskxkx( kx, 1000000000UL, KPI_SACYCLENS, NULL, 24 );
#endif
  /*    安川标准编码器                                                                                 */
  /*                                                                                                  */
  /*                    MaxTrq * 2^32 *  Ts  *  Ts            MaxTrq * Ts * Ts                        */
  /*      AccErrLvl = ------------------------------ * Cx  = ------------------- * Cx                 */
  /*                     Jmot * 2*PAI * 10^9 * 10^9           Jmot * 1462918079                       */
  /*                                                                                                  */
  /*      MaxTrq [Nm],[N]                 : 最大转矩                                                  */
  /*      Jmot   [kgm^2],[kg]             : 转动惯量                                                  */
  /*      Kfbpls [rad/pulse],[m/pulse]    : 反馈脉冲变换系数                                          */
  /*      Ts     [ns]                     : 演算周期                                                  */
  /*      Cx     [-]                      : 安全係数 (=400.000)                                       */
  /*                                                                                                  */
  /*      ※安全系数是旋转型SGDS的约400倍                                                             */
  /*                                                                                                  */
  /*--------------------------------------------------------------------------------------------------*/
  /*  反馈选择方案                                                                                  */
  /*                                                                                                  */
  /*                    MaxTrq * PulseNo * Ts  *  Ts               MaxTrq * PulsNo * Ts * Ts          */
  /*      AccErrLvl = ------------------------------------ * Cx = ---------------------------- * Cx   */
  /*                    Jmot * 2 * PAI * 10^9 * 10^9                Jmot * 2 * PAI * 10^18            */
  /*                                                                                                  */
  /*      MaxTrq [Nm],[N]                 : 最大トルク                                             */
  /*      Jmot   [kgm^2],[kg]             : モータイナーシャ                                          */
  /*      Kfbpls [rad/pulse],[m/pulse]    : ＦＢパルス変換係数                                     */
  /*      Ts     [ns]                     : 演算周期                                                  */
  /*      Cx     [-]                      : 安全係数 (=400.000)                                       */
  /*                                                                                                  */
  /*      ※安全系数是旋转型SGDS的约400倍。                                                            */
  /*      ※在反馈选项中，2n次方不是2^32/rev，而是编码器脉冲单位                                    */
  /*      　ScanA中的比较处理也与以往不同，转换为编码器脉冲单位                                       */
  /*      　下溢水平时，加速度是4。                                                                   */
  /*                                                                                                  */
  /*--------------------------------------------------------------------------------------------------*/
 		 
    kx = MlibScalKxgain( KPI_SACYCLENS, KPI_SACYCLENS, 1462918, &sx,  0 );
    kx = MlibPcalKxksks( kx, Bprm.MaxTrq, Bprm.Jmot, &sx,   0 );
    kx = MlibPcalKxgain( kx, 400000,        1000000,   &sx, -30 );
    MencP.AccErrLvl = kx;

    MencP.f.DivOut = TRUE;  // 分频脉冲输出标志置一（未用）
    return;
}
  
  
  
  
/**********************************************************************************************/
/* Function_Name: RmxReadSencPosition         */
/* Description  : 旋转型：串行编码器位置数据的读取
                  调用：位置读取调用，其函数指针在上电初始化中赋值给编码器位置读取函数指针
                  首先从CLB模块接收到的位置数据,ARM侧再从CLB侧寄存器读取
                  输入：
                  输出：   */
/**********************************************************************************************/


//#ifdef RunRAM
//#pragma CODE_SECTION(RmxReadSencPosition, ".TI.ramfunc");
//#endif
USHORT Ctek5900RegData, KTM59WTDATA, KTM59WTADDR, KTM59MSTEP;
void RmxReadSencPosition( void )
{
LONG	lwk1;
LONG	RcvPosX;
LONG	MotPosX;
LONG	LastMotPosX = MencV.MotPosX[0];
DWORDX	RxPosL_wk;
SHORT	RxPosH_wk;
LONG	dMotPos;
ULONG  kx0;
 
      /*** 写电机编码器Eeprom 或者电机参数读写的过程中不对位置信息的读取 ***/    

     if(EncCodeV.DataWriteToEeprom == 1 || EncCodeV.MEncClrCmd == 1)
    {
        MencV.f.PosCmpEnable = FALSE;                
        MencV.f.AccChkEnable = FALSE;                
		MencV.f.PosFirstReadFlag = FALSE;			 
        MRevV.MROVCheckFlag = 0;
        MRevV.MRFlag = 0;
        MencV.MstErrCnt = 0;
        MencV.ComErrCnt = 0;
        return;
    }

	if (Prm.EncoderType == 11)
	{
	   if(!Iprm.iCHausAdj)
	   {
	       icMuPosAGet();
	   }
	   else
	   {
	       return;
	   }
	}
	else if(Prm.EncoderType == 13)
   {

	    MotEncoder_ST_MT_Get();

	    if(Kprm.f.FencUse)
	    {
            if( KTM5900_Load_En )
            {
                CTek5900_PosRead();
            }
            else
            {
                MT6709_ST_MT_Get();
            }
       }
   }

          
    /*** 接收未完时，串行编码器接收信息异常时处理 ***/
    if(MencV.EncStatus.f.TMout & MencV.f.AccChkEnable )
    {
        ++MencV.ComErrCnt;                  // Count up Error Counter
        MencV.f.SeRxErr = TRUE;             // 编码器数据无效
        LpxSencComErrorProc( 0, FALSE );    // 旋转型串行编码器通信异常处理

    }
    /*** 接收完成时 : 串行编码器接收信息完成处理 ***/
    else
    {
        /*** 读取接收数据 ***/
        RxPosL_wk		 = MencV.RxPosL[0];
        RxPosH_wk		 = MencV.RxPosH[0];

		if (Prm.EncoderType == 11)
		{
		    kx0 =  icMu_Pos_A;
		    kx0 &= 0x0FFFFFF;
		}
		else if(Prm.EncoderType == 13)
		{
		    kx0 =  MotEncoder_V.Single;    //TODO
		}

        MencV.RxPosL[0].w.l = (USHORT)kx0;
        MencV.RxPosL[0].w.h = (USHORT)(kx0 >> 16);
		// 相位方向调整单圈位置
        if( MotorPhaseV.ZeroPhaseDir )
        {
            MencV.RxPosL[0].dw = MencP.PulseNo - MencV.RxPosL[0].dw - 1;
            MencV.RxPosLOri[0].dw = MencP.PulseNo - MencV.RxPosLOri[0].dw - 1;
        }
              
		/*** 单圈值和多圈值临时保存 ***/
        RoutV.MencIncPulse = MencV.RxPosL[0].dw;        // 一圈内脉冲数
		
		if (Prm.EncoderType == 11)
		{
			RoutV.ABSEncMValue = MultiPos_A;                // TODO
	        MencV.RxMPos   = MultiPos_A;                    // TODO
		}
		else
		{
	        RoutV.ABSEncMValue = MotEncoder_V.Multi;                // TODO
	        MencV.RxMPos   = RoutV.ABSEncMValue;                    // TODO
		}
        MRevOverCheck( MencV.RxMPos );                  // 多圈溢出监测

        /*** 根据电机方向调整单圈值和多圈值 ***/
        if( Iprm.f.RvsDir == 0)
        {
            RoutV.ABSEncSValue = RoutV.MencIncPulse;
            RoutV.ABSEncMValue = MencV.RxMPos;
        }
        else
        {
            RoutV.ABSEncSValue = MencP.PulseNo - RoutV.MencIncPulse;
            RoutV.ABSEncMValue = -( MencV.RxMPos + 1 );
        }
        MRevDeal( RoutV.ABSEncMValue );     // 多圈值处理

        /*** 上次单圈值更新 ***/
        MencV.RxPosL[1]     = RxPosL_wk;
        MencV.RxPosH[1]     = RxPosH_wk;

        RcvPosX = ( MencV.RxPosL[0].Long << MencP.MposSftR);    // 位置标幺为2^32

        /***判断是否是第一次进入,如果是第一次进入则进行相关的变量清零处理
            刚开始前面读取的几个数据肯定为不正确的数据,需要进行丢弃处理
            针对此处的问题,在FPGA侧同步之后,延时了 1ms                  ***/
        if( MencV.f.PosFirstReadFlag == FALSE)
        {
            MencV.MotPosX[0] = MencV.MotPosX[1]						= RcvPosX;
            MencV.RcvPosX[0] = MencV.RcvPosX[1] = MencV.RcvPosX[2]	= RcvPosX;
            MencV.f.PosFirstReadFlag = TRUE;
            MencV.ComErrCnt = 0;
            return;
        }

        /*** 加速度计算 ***/
        if( MencV.f.AccChkEnable == FALSE )     // 刚刚进入时的不能进行比较,可能异常
        {
            /*** 计算加速度 ***/
            lwk1 = 0;
            MencV.AccChkWaitCnt ++;
            if (MencV.AccChkWaitCnt > 3)
            {
                MencV.f.AccChkEnable = TRUE;
            }
            MencV.RcvPosX[0] = MencV.RcvPosX[1] = MencV.RcvPosX[2] = RcvPosX;
            MencV.ComErrCnt = 0;
        }
        else
        {
             /*** 计算加速度 ***/
             lwk1 = (RcvPosX - MencV.RcvPosX[0]) - (MencV.RcvPosX[0] - MencV.RcvPosX[1]);
             if( (lwk1 > MencP.AccErrLvl) || (lwk1 < -MencP.AccErrLvl) )
            {
              lwk1 = ((RcvPosX - MencV.RcvPosX[1])>>1) - (MencV.RcvPosX[1] - MencV.RcvPosX[2]);
            }
        }
        /*** 加速度异常时 : 串行编码器异常通讯处理 ***/
        if( (lwk1 > MencP.AccErrLvl) || (lwk1 < -MencP.AccErrLvl) || MencV.MagicErrFlg == 1)
        {
            ++MencV.AccErrCnt;
            MencV.f.SeRxErr = TRUE;
            if( MencV.MagicErrFlg == 0 )
            {
                LpxSencComErrorProc( RcvPosX, TRUE );
            }
            else
            {
                LpxSencComErrorProc( 0, FALSE );
            }
        }
        else
        {
            /*** 加速度正常时 :复位相关错误标志和计数，并锁存前几次的位置结果 ***/
            MencV.MstErrCnt   = 0;
            MencV.f.SeRxErr   = FALSE;
            MencV.f.EncDataNG = FALSE;
            MencV.RcvPosX[2]  = MencV.RcvPosX[1];
            MencV.RcvPosX[1]  = MencV.RcvPosX[0];
            MencV.RcvPosX[0]  = RcvPosX;
        }
    }
    /*** 変化時刻按照计时器位置補正処理(变化时刻计时器的位置补正处理) ***/
    if( MencV.f.PosCmpEnable == FALSE )
    {
        /*** 第一次时不进行位置预测补偿 ***/
        MotPosX = MencV.RcvPosX[0];
        MencV.f.PosCmpEnable = TRUE;    // 位置修正执行许可,初始化为0，读过一次位置后为1
    }
    else
    {
        /*** 位置预测补偿 ***/
        MotPosX = LpxTimeBasesMotPosCalc( MencV.RcvPosX[0], MencV.MotPosX[0], MencP.MposSftR );
    }
    MencV.MotPosX[1] = MencV.MotPosX[0];    // 上次补正后的位置
    MencV.MotPosX[0] = MotPosX;             // 当前补正后的位置

    MencV.SingTurn = ((ULONG)MotPosX) >> MencP.MposSftR;    // 单圈绝对位置显示处理(补偿后)

    /*** 计算脉冲变化量累加计数 ***/
    dMotPos = (MencV.MotPosX[0] - LastMotPosX ) >> MencP.MposSftR;
    MencV.MotPos   = MencV.MotPos + dMotPos;
    MencV.MotAbsPos = MencV.MotAbsPos + dMotPos;

    /*** 电机相位的计算处理 ***/
#if(FLOAT_USE == 1)
    lwk1 = (LONG)((float)MencV.SingTurn * MencP.fKmotphase);
    lwk1 = lwk1 - ((lwk1 >> 12) << 12 );
#else
    lwk1 = MlibMulgainNolim( MencV.SingTurn, MencP.Kmotphase );
    lwk1 = lwk1 % 4096;
#endif

    MencV.MotPhaseI =  lwk1;        // 原始角度值
    lwk1 += MotorPhaseV.OffsetAng;  // 偏置角处理
    if( lwk1 >=4096 )
    {
        lwk1 -= 4096;
    }
    MencV.MotPhase =  lwk1;         // 电机电角度[4096 对应360°]
}
 
LONG	LpxTimeBasesMotPosCalc( LONG RcvPosX, LONG LastMotPosX, UCHAR MposSftR )
{
LONG	MotPosCmp;
LONG	HenkaItiTimer;
		MotPosCmp = ((ULONG)RcvPosX) >> MposSftR;
#if 1
		if( MencV.f.SeRxErr == FALSE )
		{       
			HenkaItiTimer = MencP.EncPulseTimeBasic;
 			if( HenkaItiTimer <= SAENCCLKNUM )
			{
				MotPosCmp = MotPosCmp + (((float)((RcvPosX - LastMotPosX)>>MposSftR ) * (float)HenkaItiTimer) / (float)SAENCCLKNUM);
                MotPosCmp = (MotPosCmp <              0)? (MotPosCmp + MencP.PulseNo) : MotPosCmp;
                MotPosCmp = (MotPosCmp >= MencP.PulseNo)? (MotPosCmp - MencP.PulseNo) : MotPosCmp;
			}
 		}
#endif
		return( MotPosCmp << MposSftR );
}
 
  
  
 void RmxReadErrPosition(void)
{
	return;
}
 
  
/**********************************************************************************************/
/* Function_Name: APL_SencComErrorProc         */
/* Description  : 旋转型：旋转型串行编码器通信异常处理
               调用：串行编码器位置读取函数中调用
               输入：
               输出：   */
/**********************************************************************************************/
void	LpxSencComErrorProc( LONG RcvPosX, LONG AccErr )
{
  
    /*** 警告时处理：警报设定 ***/
    if( MencV.MstErrCnt > Prm.spgfail )             // 检查错误计数器
    {
        if( MencV.ComErrCnt >= MencV.AccErrCnt )	// 错误类型判断(通信 or 加速度)
        {
            MencV.f.EncDataNG = TRUE;				// 置位编码器数据没有准备好
            KPI_ALARMSET( ALM_PGCOM  );				// A.C90 : 编码器通信異常
            StateM_Var.f.EncError = 1;
            MencV.MstErrCnt = 0;
        }
        else if( ! KPI_ALARMCHK( ALM_PGCOM ) )
        {
            MencV.f.EncDataNG = TRUE;				// 编码器数据无效
            KPI_ALARMSET( ALM_PGCOM1 );				// A.C91 : 编码器通信異常(加速度)
            MencV.MstErrCnt  = 0;
        }
    }
    /*** 非报警时的处理:用上次值进行插值运算 ***/
    else
    {
        MencV.RcvPosX[2]  = MencV.RcvPosX[1];	    // 上上回值更新
        MencV.RcvPosX[1]  = MencV.RcvPosX[0];		// 上回值更新
        if( AccErr )
        {
            // 加速度异常：加速度异常时不插值
            MencV.RcvPosX[0] = RcvPosX;
        }
        else
        {
            // 数据读取异常：使前面角度推算当前角度
            MencV.RcvPosX[0] += (MencV.RcvPosX[1] - MencV.RcvPosX[2]);
        }

        // 加速度 or 通讯异常计数
        ++MencV.MstErrCnt;
											 
              
        if( (StateM_Var.f.PhaseStudy == 1) ||   \
                (( Prm.b_prm0_0 & 0x000F ) == 0x0007))
        {
            MencV.MstErrCnt = 0;
        }
    }

    /*** 编码器数据无效时的处理 ***/
    if( MencV.f.EncDataNG == TRUE )
    {
        if( BinV.f.BaseEnable == FALSE )
        {
            MencV.RxPosL[1]  = MencV.RxPosL[0];			// 上回值更新
            MencV.RxPosH[1]  = MencV.RxPosH[0];			// 上回值更新
            MencV.RcvPosX[2] = MencV.RcvPosX[1];		// 上上回值更新
            MencV.RcvPosX[1] = MencV.RcvPosX[0];		// 上回值更新
        }
    }
    return;
}
 
