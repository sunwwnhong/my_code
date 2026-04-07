/*********** (C) COPYRIGHT 2024 Veichi Technology Co., Ltd**************************************
* File Name   : Mot15_Voltage.c
* Version     : V0.1
* Date        : 2024
* Description : 电压相关故障处理
***********************************************************************************************/
#include "Main.h"
 
VOLTKIOP VoltVar = {0,0,0,0,0,0,0,0,0,0,0};
 
void LpxDcPowerManager( void );
 
/*--------------------------------------------------------------------------------------------*/
/*  输入最大电压时主回路母线电压AD检测原始值 ( AD converter output at PnE70[V] Input )        */
/*  伺服驱动器AD检测的最大值对应的母线电压,采样范围为12位,根据实际进行调整                    */
/*--------------------------------------------------------------------------------------------*/
#define		VDTAD100		4095        // AC100V			 
#define		VDTAD200		4095 		// AC220V	 
#define		VDTAD400		4095 		// AC380V	 
#define		VDTAD24			4095 		// DC24V	 
#define		VDTAD48			4095 		// DC48V	 
#define     VDTAD72         4095        // DC72V   
#define     VDTAD36         4095		// DC36V   
  
  
/**********************************************************************************************/
/*	   驱动器和电机电压管理	   Amplifier and motor voltage management				   	      */
/*														    								  */
/*          特别注意事项:为了配合FPGA处理,电压检测均标幺为VdetMax                             */
/*          例如:AC220V驱动器的最大电压是500V,则将其标幺的范围为0-VdetMax                     */
/**********************************************************************************************/
typedef  	struct
{
    UCHAR  InVcd;		    // 输入电压代码			 
    UCHAR  OutVcd;			// 输出电压代码			 
    UCHAR  DcinType;		// 输入电压类型：0-AC;1-DC			 
    LONG   DcVolt;			// DC电压 [0.0001V],交流电压*根号2			 
    USHORT VdetMax;  		// 驱动器主电路检测的最大值		     
    USHORT VdetAdMax;		// 驱动器主电路检测的AD最大值			 
    USHORT AmpUnVolt;		// Un监测显示驱动器电压 [V]			 
    USHORT MotUnVolt;		// Un监测显示电机电压   [V]			 
}	 AMPVTBL;

const	AMPVTBL	AmpVtbl[7] = {
/*----- InVcd  OutVcd  DC/AC   DcVolt   VdetMax VdetAdMax AmpUnVolt MotUnVolt ----------------*/  
 	{	0x00,	0x00,	0,      1414214, 255,	VDTAD100,	100,		100,	},
 	{	0x01,	0x01,	0,      3111270, 255,	VDTAD200,	220,		220,	},
 	{	0x02,	0x02,	0,      5374012, 511,	VDTAD400,	380,		380,	},
 	{	0x03,	0x03,	1,      240000,  255,	VDTAD24,	24,			24,		},
 	{	0x04,	0x04,	1,      480000,  255,	VDTAD48,	48,			48,		},
    {   0x05,   0x05,   1,      720000,  255,   VDTAD72,    72,         72,     },
    {   0x06,   0x06,   1,      360000,  255,   VDTAD36,    36,         36,     },
};
 
 
 /**********************************************************************************************/
 /* Function_Name: BprmAmpMotVoltInfoCal                                                       */
 /* Description  : 伺服驱动器和电机电压信息处理         
           输入  ：
           输出  ：                    */
 /**********************************************************************************************/    
void BprmAmpMotVoltInfoCal( void )
{
UCHAR	Idx = (Prm.VoltType & 0x0F);

    /*--------------参数检验------------*/  
     if( Idx > 6 )
    {
		Idx = 1;									 
		KpiSetParamError( &pndef_VoltType );		     
    }
  
    /*--------------伺服驱动器的输入输出电压代码---------------------------------------*/
 	Bprm.MotVcode	  = Prm.typm_e.b.h & 0x0F;				     
	Bprm.MotUnVolt	  = AmpVtbl[ Bprm.MotVcode ].MotUnVolt;

	Bprm.AmpUnVolt    = AmpVtbl[ Idx ].AmpUnVolt;

	//Note: 选择电机和驱动器中额定较小的电压进行标幺化
	if(Bprm.MotUnVolt < Bprm.AmpUnVolt)
	{
	    Idx = Prm.typm_e.b.h & 0x0F;
	}

	Bprm.AmpUnVolt    = AmpVtbl[ Idx ].AmpUnVolt;
    Bprm.AmpInVcode   = AmpVtbl[ Idx ].InVcd;
    Bprm.AmpOutVcode  = AmpVtbl[ Idx ].OutVcd;
    /*--------------外部给驱动器输入的电压类型 DC or AC--------------------------------*/
    Bprm.AmpDcinType  = AmpVtbl[ Idx ].DcinType;
    Bprm.AmpDCVolt    = AmpVtbl[ Idx ].DcVolt;

    /*--------------驱动器直流电压的计算	voltage [V] -------------------------------*/
 	Bprm.Vdc = MlibScalKxgain( AmpVtbl[ Idx ].DcVolt, 1, 10000, NULL, -1 );
	Bprm.fVdc = (float)AmpVtbl[ Idx ].DcVolt / 10000.0f;

    /*---------------设置驱动器主电路检测最大值----------------------------------------*/
 	Bprm.VdetMax	  = AmpVtbl[ Idx ].VdetMax;
  
    /*---------------设置驱动器主电路检测的AD最大值------------------------------------*/
	Bprm.VdetAdMax	  = AmpVtbl[ Idx ].VdetAdMax;
  
  
#if(FLOAT_USE == 1)
    Bprm.VCOffset = (float)Prm.pnvoltgn * ((SHORT)Prm.pnzero) / Bprm.VdetMax;
    Bprm.VCGain   = (float)((0x100 + (SHORT)Prm.pngain)) / 256.0f;
#else
    Bprm.VCOffset = (ULONG)1024 * Prm.pnvoltgn / Bprm.VdetMax;
#endif
	return;
}
/****************************************************************************************************/
/*                                                                                                  */
/*      DC电源电压监视水平计算                                                                        */
/*                                                                                                  */
/****************************************************************************************************/
/*                                                                                                  */
/*  機 能 : ＤＣ電源腌殑監視レベルの計算を行う。                                                    */
/*              1) 过压检出值                                                                        */
/*              2) 再生制动开启值                                                                  */
/*              3) 再生制动关闭值                                                                  */
/*              4) 主回路欠压检测值                                                                 */
/*              5) 主回路欠压检测时间                                                               */
/****************************************************************************************************/
  
void	IprmcalVoltageCheckLevel( void )
{
LONG	s = 0;
float   fkx;
        /*------------------------------------------------------------------------------------------*/
        /*      过压(OV)水平的计算                                                                 */
        /*------------------------------------------------------------------------------------------*/
 		Iprm.OvLevel = (Prm.ovlvl * Bprm.VdetMax / Prm.pnvoltgn);
        /*------------------------------------------------------------------------------------------*/
        /*      欠压(UV)水平的计算                                                                 */
        /*------------------------------------------------------------------------------------------*/
 		Iprm.UvLevel = (Prm.uvlvl * Bprm.VdetMax / Prm.pnvoltgn);
		Iprm.UvWrnLevel = (Prm.UvWrnLvl * Bprm.VdetMax / Prm.pnvoltgn);								
        /*------------------------------------------------------------------------------------------*/
        /*      再生制动計算                                                                          */
        /*------------------------------------------------------------------------------------------*/
 		Iprm.RegOnLevel  = ( Prm.regonlvl * Bprm.VdetMax / Prm.pnvoltgn );
		Iprm.RegOffLevel = (( Prm.regonlvl - Prm.regoffhys ) * Bprm.VdetMax / Prm.pnvoltgn);
        /*------------------------------------------------------------------------------------------*/
        /*      AD変換方式で鐨匂した値の正規化定数                                                  */
        /*------------------------------------------------------------------------------------------*/
 #if(FLOAT_USE == 1)
		Iprm.VdetAdNorm = (float)Bprm.VdetMax / Bprm.VdetAdMax;
#else
        Iprm.VdetAdNorm = MlibPcalKxgain( Bprm.VdetMax, 1, Bprm.VdetAdMax, &s, 24 );
#endif
        /*------------------------------------------------------------------------------------------*/
        /*      AD 正規化定数 转换成实际值                                                          */
        /*------------------------------------------------------------------------------------------*/
 #if(FLOAT_USE == 1)
        Iprm.Kdcvolt = (float)Prm.pnvoltgn / (float)Bprm.VdetMax;
        Iprm.Kdcvolt1 = (float)Prm.pnvoltgn * 10.0f/ (float)Bprm.VdetMax;
#else
        Iprm.Kdcvolt = MlibScalKxgain( Prm.pnvoltgn, 1, Bprm.VdetMax, NULL, 24 );
#endif
        /*------------------------------------------------------------------------------------------*/
        /*      主回路検出ＡＤ用三重根低通滤波器滤波器定额参数计算                                   */
        /*------------------------------------------------------------------------------------------*/
 #if(FLOAT_USE == 1)
        VoltVar.VdetAdFil = FlibPcalKf1gain( Prm.vdetadfil, (2UL * KPI_SBCYCLEUS), 0 );
#else
        VoltVar.VdetAdFil = MlibPcalKf1gain( Prm.vdetadfil, (2UL * KPI_SBCYCLEUS), 0 );
#endif
        /*------------------------------------------------------------------------------------------*/
        /*      主回路电压转换成实际的电压值系数                                                    */
        /*------------------------------------------------------------------------------------------*/
         VoltVar.Kdcvolt = MlibScalKxgain( Prm.pnvoltgn, 1, Bprm.VdetMax, NULL, 24 );
         /*------------------------------------------------------------------------------------------*/
         /*      主回路母线电压率系数                                                                */
         /*------------------------------------------------------------------------------------------*/
 #if(FLOAT_USE == 1)

        //电压系数计算 标幺最大值->PnE10
        fkx = (float)Bprm.AmpDCVolt / 10000.0f;
        VoltVar.VdcRatioCoeff = fkx * Bprm.VdetMax / Prm.pnvoltgn;
#else
        s = MlibScalKskxkx( Bprm.Vdc, 1,    1,      NULL,   -24 );
        VoltVar.VdcRatioCoeff = MlibPcalKxgain( s, Bprm.VdetMax, Prm.pnvoltgn, NULL, 24 ) ;
 #endif
        /*------------------------------------------------------------------------------------------*/
        /*      PWM 最大输出电压幅值系数计算                                                        */
        /*------------------------------------------------------------------------------------------*/
         VoltVar.VdcMaxCoeff = MlibPcalKxgain( Prm.pnvoltgn, 524288, s * 11585, NULL, 24 ) ;
 		return;
 }
/****************************************************************************************************/
/*                                                                                                  */
/*      ＤＣ電源電圧検出処理 ( 実行周期 : 250us ) for SGDS & SGDX                                 */
/*                                                                                                  */
/*  機能１：主回路電圧検出方式によって検出関数を使い分ける。主回路電圧(KioV.DcVoltx)を作成する。   */
/*              ?ＰＷＭ?コンパレータ方式（固定追従方式）                                           */
/*              ?ＰＷＭ?コンパレータ方式（可変追従方式）                                           */
/*              ?Ａ／Ｄ変換方式                                                                        */
/*                                                                                                  */
/*  機能２: 過電圧検鐨勏主回路部品の保護のために行う。                                              */
/*          耐压最低的是主电路电容。                                                                */
/*          主电路电容器有爆炸的危险。                                                               */
/*          通常回生処理が働いて、過電圧レベルまでＤＣ電圧が上昇することはない。                  */
/*          回生処鐨勜路の不具鐨勣たは回生抵抗値の不整合等により過電圧になることがあり得る。        */
/*          フル出力で回生すょ殑電圧上昇が早いので、ScanBで処理する。                             */
/*          ＤＣ電圧レベルを監視して過電圧検出レベルを越えたら異常処理する。                        */
/*                                                                                                  */
/****************************************************************************************************/
void	LpxDetectDcVolt( void )
{
#if(FLOAT_USE == 1)
    float    AdRead;
    float    DcVoltx;
#else
    LONG	AdRead;
    LONG	DcVoltx;
    LONG    lkx;
#endif
 #ifdef CPU1
        AdRead = AMotVar[ 0 ].Mot_Udc;
        AdRead += 3.60722f;      
          
#endif

 #if(FLOAT_USE == 1)
        VoltVar.DcAdFilo[0] = FlibLpfilter1( AdRead,              VoltVar.VdetAdFil, VoltVar.DcAdFilo[0] );
        VoltVar.DcAdFilo[1] = FlibLpfilter1( VoltVar.DcAdFilo[0], VoltVar.VdetAdFil, VoltVar.DcAdFilo[1] );
        VoltVar.DcAdFilo[2] = FlibLpfilter1( VoltVar.DcAdFilo[1], VoltVar.VdetAdFil, VoltVar.DcAdFilo[2] );
#else
        VoltVar.DcAdFilo[0] = MlibLpfilter1( VoltVar.DcAdFili, VoltVar.VdetAdFil, VoltVar.DcAdFilo[0] );
        VoltVar.DcAdFilo[1] = MlibLpfilter1( VoltVar.DcAdFilo[0], VoltVar.VdetAdFil, VoltVar.DcAdFilo[1] );
        VoltVar.DcAdFilo[2] = MlibLpfilter1( VoltVar.DcAdFilo[1], VoltVar.VdetAdFil, VoltVar.DcAdFilo[2] );
#endif
 
#if(FLOAT_USE == 1)
        VoltVar.DcAdFili = VoltVar.DcAdFilo[2] * Iprm.VdetAdNorm;
#else
        VoltVar.DcAdFili = (SHORT)( MlibMulgain( (LONG)VoltVar.DcAdFilo[2], Iprm.VdetAdNorm ));
#endif
 
		DcVoltx = VoltVar.DcAdFili;
          
 		DcVoltx = DcVoltx + Bprm.VCOffset;       
		DcVoltx = DcVoltx * Bprm.VCGain;         
        VoltVar.DcVolt = ( DcVoltx < 0.0f )?  0 : DcVoltx;
        BinK.DcVolt = VoltVar.DcVolt;
          
 #if(FLOAT_USE == 1)
        BinK.TrcDcVolt =  DcVoltx * Iprm.Kdcvolt;
#else
        BinK.TrcDcVolt = ( MlibMulgain( (LONG)( BinK.DcVolt ), Iprm.Kdcvolt ) );
#endif
		BinK.UnDcVolt = BinK.TrcDcVolt;
          
          
         
          
 #ifdef CPU1
        ACRCom.UdcRatio = VoltVar.VdcRatioCoeff / (float)BinK.DcVolt;
         if(ACRCom.UdcRatio > 1.2f)
        {
            ACRCom.UdcRatio = 1.2f;
        }
        else if(ACRCom.UdcRatio < 0.9f)
        {
            ACRCom.UdcRatio = 0.9f;
        }
        else
        {;}
#endif
         LpxDcPowerManager( );                                         
 }
/****************************************************************************************************
Function_Name:LpxDcPowerManager
Description  :DC 电源管理
判断依据：	   1)母线电压大于(欠压点 + 一定电压滞环)
            && 2)母线电压稳定
            && 3)持续300ms
            && 4)判断母线电压稳定后再延时300ms，进入停机状态
*****************************************************************************************************/
void LpxDcPowerManager( void )
{
USHORT kx = 0;
    /*----------------------------------------------------------------------------------------------*/
    /*  在单板测试模式下,继电器不受电压控制                                                         */
    /*----------------------------------------------------------------------------------------------*/
     if( Iprm.FATest2 == 1 )
    {
        if( ( Prm.FaTestControl & 0x0004 ) == 0x0004 )
        {
            RelayOn();
        }
        else
        {
            RelayOff();
        }
        return;
    }
    /*----------------------------------------------------------------------------------------------*/
    /* 电压比较                                                                                     */
    /*----------------------------------------------------------------------------------------------*/
     if( Prm.VoltType == 1 || Prm.VoltType == 2 )
    {
        kx = Iprm.UvLevel + 16;
    }
    else
    {
        kx = Iprm.UvLevel;
    }
 	switch(VoltVar.UdcStep)
	{
 	/*------------------------------------------------------------------------------------------*/
    /* 相关变量初始化                                                                           */
    /*------------------------------------------------------------------------------------------*/
 		case 0:
			VoltVar.WaitTime = 0;
            CoutK.f.PowerOn  = FALSE;
			CoutK.f.PowerOnEep = FALSE;
			VoltVar.UdcStep ++;
			break;
    /*------------------------------------------------------------------------------------------*/
    /* 判断当前母线电压是否大于欠压点并且母线电压不再有变化?  需要有5V的滞环                    */
    /*------------------------------------------------------------------------------------------*/
 		case 1:
			if( ( VoltVar.DcVolt > kx ) && (VoltVar.DcVolt <= VoltVar.DcVoltOld) )
			{
			    /*----------------------------------------------------------------------------------*/
			    /* 电压不再有上升 (125ms)                                                           */
			    /*----------------------------------------------------------------------------------*/
 				if((VoltVar.WaitTime++) >= 1000)
				{
					VoltVar.UdcStep ++;                      
					VoltVar.WaitTime = 0;
				}
			}
			else
			{
			    /*----------------------------------------------------------------------------------*/
			    /* 电压继续在上升                                                                   */
			    /*----------------------------------------------------------------------------------*/
 				VoltVar.WaitTime    = 0;
				VoltVar.DcVoltOld   = VoltVar.DcVolt + 3;
                  
				/*----------------------------------------------------------------------------------*/
				/* 当电机继续上升的过程中,电压大于正常的电压                                          */
				/*----------------------------------------------------------------------------------*/
				if(VoltVar.DcVolt > Iprm.RegOffLevel)
				{
					VoltVar.UdcStep ++;                      
				}
			}
             CoutK.f.PowerOn  = FALSE;
			CoutK.f.PowerOnEep = FALSE;
			break;
		/*------------------------------------------------------------------------------------------*/
        /* 继电器吸合                                                                               */
        /*------------------------------------------------------------------------------------------*/
 		case 2:
            RelayOn();
            VoltVar.UdcStep ++;                              
			break;
        /*------------------------------------------------------------------------------------------*/
        /* 继电器吸合后延时一段时间给继电器,便于充分吸合                                            */
        /* 根据继电器的吸合时间(手册中获取),标称时间均 ≤20ms                                        */
        /* 为了保险起见,延时等待时间为 35ms                                                         */
        /*------------------------------------------------------------------------------------------*/
          
 		case 3:
			if( ( ++VoltVar.WaitTime ) >= 1000 )
			{
                 Iprm.VdetPrmOk = 1;                          /* 继电器吸合,再生制动可以动作,否则,    */
                                                              /* 如果继电器没有吸合,直接进行再生制动  */
                                                              /* 动作,充电电阻可能损坏                */
                                                              
 				VoltVar.WaitTime = 0;
                VoltVar.VdcLVAlmCnt = 0;                     /* 欠压故障计数值                       */
                VoltVar.VdcOVAlmCnt = 0;                     /* 过压压故障计数值                     */
                 VoltVar.UdcStep ++;                          
			}
            break;
        /*------------------------------------------------------------------------------------------*/
        /* 电压建立后( 继电器吸合后 ),对DC母线电压的欠压进行相应的监测                              */
        /*------------------------------------------------------------------------------------------*/
 		case 4:
             CoutK.f.PowerOn = TRUE;
			CoutK.f.PowerOnEep = TRUE;
			/*--------------------------------------------------------------------------------------*/
			/* 过压处理部分                                                                         */
			/*--------------------------------------------------------------------------------------*/
                          
            if( VoltVar.DcVolt > Iprm.OvLevel )
            {
				if( VoltVar.VdcOVAlmCnt > Iprm.OvdetAlmFilter )
				{
					KPI_ALARMSET( ALM_OV );
				}
				else
				{
					VoltVar.VdcOVAlmCnt++;                  /*超过设定的电压时,进行一个延时滤波处理 */
				}
			}
            else
            {
                VoltVar.VdcOVAlmCnt = 0;
            }
            /*--------------------------------------------------------------------------------------*/
            /* 欠压处理部分                                                                         */
            /*--------------------------------------------------------------------------------------*/
              
            if( VoltVar.DcVolt < Iprm.UvLevel )
            {
                /*----------------------------------------------------------------------------------*/
                /* 欠压故障                                                                         */
                /*----------------------------------------------------------------------------------*/
                 if( ++VoltVar.VdcLVAlmCnt > Prm.uvfil * 16 )
                {
                     VoltVar.VdcLVAlmCnt = 0;                   /* 清零欠压计数器值                 */
                     /*------------------------------------------------------------------------------*/
                     /* 伺服驱动器在不使能的情况下,不对欠压警告和故障进行检测                        */
                     /*------------------------------------------------------------------------------*/
                     if( BinV.f.BaseEnable )
                    {
                        KPI_ALARMSET( ALM_PUV );                 /* 欠压报警  Er.410                 */
                        KPI_WARNINGCLR( WRN_UV );                /* 清除欠压警告                     */
                    }
                     RelayOff( );                                 
                     Iprm.VdetPrmOk      = 0;                    /* 再生制动无效                     */
                    CoutK.f.PowerOn     = FALSE;
                    CoutK.f.PowerOnEep  = FALSE;                 /* 用于Eeprom                       */
                     VoltVar.UdcStep     = 0;
                }
            }
            else
            {
                VoltVar.VdcLVAlmCnt = 0;
                /*----------------------------------------------------------------------------------*/
                /*  欠压警告                                                                        */
                /*----------------------------------------------------------------------------------*/
                 if ( VoltVar.DcVolt < Iprm.UvWrnLevel )
                {
                    if( VoltVar.DcVolt != 0 )
                    {
                        KPI_WARNINGSET( WRN_UV );
                    }
                }
                 else
                {
                    KPI_WARNINGCLR( WRN_UV );
                }
            }
			break;
 		default:
			VoltVar.UdcStep = 0;
			break;
 	}
 	/*----------------------------------------------------------------------------------------------*/
    /* 主回路上电标志                                                                               */
    /*----------------------------------------------------------------------------------------------*/
     CoutV.f.Seq.MainPowerOn = (CoutK.f.PowerOn)? TRUE : FALSE;
}
 
  
 
