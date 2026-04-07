/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd***************************************
* File Name          : Mot50_DIDO.c
* Version            : V0.1
* Date               : 2024
* Description        : 开关量输入(Input)输出(Output)管理
*****************************************************************************************************/
  

#include "Main.h"
 
DIGIT_DIDO DIDOVar;
#define	KPI_SO1BITNO		0
#define	KPI_SO2BITNO		1
#define	KPI_SO3BITNO		2
#define	KPI_SO4BITNO		3
#define	KPI_SO5BITNO		4
#define	KPI_SO6BITNO		5


  
#define	KPI_SIN_MAUTOMOD( x )       KPX_SINPUTBITX( x.dw, Iprm.Imap.ManualAutoMod) /*手动自动模式切换端子   */
void	DISeqInputMap_Init( void );
void	IprmcalSeqOutputMap( void );
 
/****************************************************************************************************/
/* Function_Name: DiHwFilter */ 
/* Description  : 数字量输入端子滤波处理
               调用：
               
                     */
/***************************************************************************************************/
void DiHwFilter(void)
{
    USHORT tmp = 0U;
    UCHAR i = 0U;
    for (i = 0; i < NUM_DIGITALIN_CHANNEL; i++)         // 4个数字量输入端子
    {
        tmp = 0x01 << i;
        if (((DIDOVar.DigitInNew) ^ (DIDOVar.DigitInFilter)) & tmp)
        {
             // 确认该位DI的状态已经改变(滤波)
            if (++DIDOVar.DigitInFilCnt[i] >= Gprm.XFilterTime)
            {
            	DIDOVar.DigitInFilter ^= tmp;
            }
        }
        else
        {
             // 没有改变，滤波计时器得清零                                                          
             DIDOVar.DigitInFilCnt[i] = 0;
        }
    }
      
    /* 虚拟信号给定 */
    tmp = Iprm.Imap.VirSet ^ 0xFFFF;
    tmp = (tmp & DIDOVar.DigitInFilter) | ( Prm.VirDI & Iprm.Imap.VirSet) ;
      
    /*  监控信号与逻辑信号(常开,常闭)关联  */
    DIDOVar.DigitStatusMon.dw = ( tmp << 1 ) & 0xFFFE;
      
      
#if 1
    if( Iprm.FATest2 == 0)
    {
        DIDOVar.DigitStatus.dw = ( tmp << 1 ) & 0xFFFE;
    }
#endif
 }
 
  
  
  
  
void ReadDIStatus(void)
{
    DIDOVar.DigitInNew = InputScan();
      
    /* 对输入端子信号进行相关的滤波处理 */
    DiHwFilter();
 }
  
  
/****************************************************************************************************/
/* Function_Name: KeyValueFeedBack  */ 
/* Description  : 反馈按键的键值
       调   用  ：   */
/****************************************************************************************************/
UCHAR KeyValueFeedBack(void)
{
    return (UCHAR)((DIDOVar.DigitInNew & 0x000F) ^ 0x0F);
}
 
  
/****************************************************************************************************/
/* Function_Name: KpiMonInputSignal  */
/* Description  : 输入信号显示处理，对应每一位置1
    调   用  ：IO口输入信号监控
                     */
/****************************************************************************************************/
ULONG	KpiMonInputSignal( void )
{
ULONG	monx = 0;
HWSIN	HwsIn;
    HwsIn.dw= DIDOVar.DigitStatusMon.dw ^ Iprm.Imap.OnOffSet;

    /*      输入信号监控   */
    if( KPX_MON_HWSIN00( HwsIn ) ){ monx |= 0x0001;}
    if( KPX_MON_HWSIN01( HwsIn ) ){ monx |= 0x0002;}
    if( KPX_MON_HWSIN02( HwsIn ) ){ monx |= 0x0004;}
    if( KPX_MON_HWSIN03( HwsIn ) ){ monx |= 0x0008;}
    if( KPX_MON_HWSIN04( HwsIn ) ){ monx |= 0x0010;}
    if( KPX_MON_HWSIN05( HwsIn ) ){ monx |= 0x0020;}
    if( KPX_MON_HWSIN06( HwsIn ) ){ monx |= 0x0040;}
    if( KPX_MON_HWSIN07( HwsIn ) ){ monx |= 0x0080;}
    if( KPX_MON_HWSIN08( HwsIn ) ){ monx |= 0x0100;}
    return( monx );
}
 
  
  
/****************************************************************************************************/
/* Function_Name:        原函数名 KpiMonOutputSignal   */ 
/* Description  : 输出信号显示处理
       调   用  ：IO口输出信号监视
                     	*/
/****************************************************************************************************/
ULONG	KpiMonOutputSignal( void )
{
ULONG	monx = 0;
	HWSOUT	HwsOut;
    HwsOut.dw = BoutK.UnOutSignal;
    if( KPX_MON_HWSOUT00( HwsOut ) ){ monx |= 0x01;}
    if( KPX_MON_HWSOUT01( HwsOut ) ){ monx |= 0x02;}
    if( KPX_MON_HWSOUT02( HwsOut ) ){ monx |= 0x04;}
    if( KPX_MON_HWSOUT03( HwsOut ) ){ monx |= 0x08;}
    if( KPX_MON_HWSOUT04( HwsOut ) ){ monx |= 0x10;}
  
    return( monx );
}
 
  
 /****************************************************************************************************/
 /* Function_Name: User20_DIDO_Init   */ 
 /* Description  : 输入输出信号初始化
        调   用  ：系统主函数初始化中调用
                         */
 /****************************************************************************************************/
 void User20_DIDO_Init( void )
{
    MlibResetSHORTMemory( &DIDOVar, sizeof(DIDOVar ) );     // 变量初始化        
    DISeqInputMap_Init( );        // 输入信号配置初始化                               
    IprmcalSeqOutputMap( );       // 输出信号配置初始化                               
}
 
  
/****************************************************************************************************/
/* Function_Name: DigitalInConfigErrorCheck  */ 
/* Description  : 对输入信号的最大值是否超限、功能是否重复进行检查
       调   用  ：
                     	*/
/****************************************************************************************************/
SHORT DigitalInConfigErrorCheck(void)
{
    SHORT   i, j;
    USHORT  uiArrayInput[NUM_DIGITALIN_CHANNEL];
    USHORT  *p = &Prm.insel1;
    USHORT  UpperLimit = pndef_insel1.UpperLimit & 0x0FF;
    USHORT  PortNum = 0;
     if( Kprm.f.EtherCATNet == 1 )
    {
        PortNum = 2;
    }
    else
    {
        PortNum = NUM_DIGITALIN_CHANNEL;
    }
      
    /* 对上限值进行检查 */
    for (i = 0; i < PortNum; i++)
    {
        uiArrayInput[i] = p[i] & 0x0FF;
        if( uiArrayInput[i] > UpperLimit)
        {
            return (FALSE);
        }
    }
    /* 对功能重复检查 */
    for (i = 0; i < PortNum - 1; i++)
    {
        for (j = i + 1; j < PortNum; j++)
        {
            if ((uiArrayInput[i] == uiArrayInput[j]) && (uiArrayInput[i] != 0))
            {
                return (FALSE);
            }
        }
    }
     return TRUE;
}
 
 
 /****************************************************************************************************/
 /* Function_Name:  DISeqInput1Map_Init  */ 
 /* Description  : 数字量输入端子-----X1 配置设置
        调   用  ： */
 /****************************************************************************************************/
 void DISeqInput1Map_Init( void )
{
LONG    rc;
    rc = DigitalInConfigErrorCheck( );          // 检查是否有重复功能分配                   
    if( rc == FALSE )
    {
        KPI_ALARMSET( ALM_XERROR );             // X端子配置重复
    }
    else
    {
        DBYTEX  *pImapx = &Iprm.Imap.UseLess;
        DBYTEX  Imapx;
        UCHAR	Selx = 0;
         /* 对前面设置的信号清除处理 */
        if( DIDOVar.DigitInSetStatus[0] != ( Prm.insel1 & 0x00FF ))
        {
            Selx = DIDOVar.DigitInSetStatus[0];
            Imapx.b.l = 0;
            Imapx.b.h = 0;            
            pImapx[Selx] = Imapx;
        }
        DIDOVar.DigitInSetStatus[0] = Prm.insel1 & 0x00FF;

        /* 输入端子 配置                                                                            */
        Imapx.b.l = KPI_SI0BITNO;
        Imapx.b.h = (Prm.insel1 & 0x0100)? 0x01 : 0x00;     // 通过功能码给定输入配置
        Iprm.Imap.OnOffSet &= 0xFFFD;                       // 常开 / 常闭设置(1111 1111 1111 1101)
        Iprm.Imap.OnOffSet |=  (Prm.insel1 & 0x0100)? 0x0002 : 0x00;
        Selx =  Prm.insel1 & 0x00FF;
        pImapx[Selx] = Imapx;

        /* 虚拟端子给定信号【强制某一信号为On】                                                     */
        rc = (0x0001 << 0 ) ^ 0xFFFF;
        Iprm.Imap.VirSet &= rc;
        Iprm.Imap.VirSet |= ((( Prm.insel1 >> 12 ) & 0x01 ) << 0 );
    }
}
  
  
/**********************************************************************************************/
/* Function_Name: DISeqInput2Map_Init  */ 
/* Description  : 数字量输入端子-----X2 配置设置
       调   用  ：*/
/**********************************************************************************************/
void DISeqInput2Map_Init( void )
{
LONG    rc;
    rc = DigitalInConfigErrorCheck( );      // 检查是否有重复功能分配                      
    if( rc == FALSE )
    {
        KPI_ALARMSET( ALM_XERROR );
    }
     else
    {
        DBYTEX  *pImapx = &Iprm.Imap.UseLess;
        DBYTEX  Imapx;
        UCHAR	Selx = 0;
          
         if( DIDOVar.DigitInSetStatus[1] != ( Prm.insel2 & 0x00FF ))
        {
            Selx = DIDOVar.DigitInSetStatus[1];
            Imapx.b.l = 0;
            Imapx.b.h = 0;            
            pImapx[Selx] = Imapx;
        }
        DIDOVar.DigitInSetStatus[1] = Prm.insel2 & 0x00FF;
          
        Imapx.b.l = KPI_SI1BITNO;
        Imapx.b.h = (Prm.insel2 & 0x0100)? 0x01 : 0x00;
        Iprm.Imap.OnOffSet &= 0xFFFB;
        Iprm.Imap.OnOffSet |=  (Prm.insel2 & 0x0100)? 0x0004 : 0x00;
        Selx =  Prm.insel2 & 0x00FF;
        pImapx[Selx] = Imapx;
          
        rc = (0x0001 << 1 ) ^ 0xFFFF;
        Iprm.Imap.VirSet &= rc;
        Iprm.Imap.VirSet |= ((( Prm.insel2 >> 12 ) & 0x01 ) << 1 );
    }
}
  
  
  
void DISeqInput3Map_Init( void )
{
LONG    rc;
      
  /*  if( Kprm.f.EtherCATNet == 1 )
    {
        return;
    }*/                                                         //20240814  EA机型X3端子无效
 
    rc = DigitalInConfigErrorCheck( );                           
    if( rc == FALSE )
    {
        KPI_ALARMSET( ALM_XERROR );
    }
    else
    {
        DBYTEX  *pImapx = &Iprm.Imap.UseLess;
        DBYTEX  Imapx;
        UCHAR	Selx = 0;
          
        if( DIDOVar.DigitInSetStatus[2] != ( Prm.insel3 & 0x00FF ))
        {
            Selx = DIDOVar.DigitInSetStatus[2];
            Imapx.b.l = 0;
            Imapx.b.h = 0;            
            pImapx[Selx] = Imapx;
        }
        DIDOVar.DigitInSetStatus[2] = Prm.insel3 & 0x00FF;
          
        Imapx.b.l = KPI_SI2BITNO;
        Imapx.b.h = (Prm.insel3 & 0x0100)? 0x01 : 0x00;
        Iprm.Imap.OnOffSet &= 0xFFF7;
        Iprm.Imap.OnOffSet |=  (Prm.insel3 & 0x0100)? 0x0008 : 0x00;
        Selx =  Prm.insel3 & 0x00FF;
        pImapx[Selx] = Imapx;
          
        rc = (0x0001 << 2 ) ^ 0xFFFF;
        Iprm.Imap.VirSet &= rc;
        Iprm.Imap.VirSet |= ((( Prm.insel3 >> 12 ) & 0x01 ) << 2 );
    }
}
  
  
  
void DISeqInput4Map_Init( void )
{
LONG    rc;
      
/*    if( Kprm.f.EtherCATNet == 1 )
    {
        return;
    }
*/                                                //20240814  EA机型X4端子无效
    rc = DigitalInConfigErrorCheck( );                           
    if( rc == FALSE )
    {
        KPI_ALARMSET( ALM_XERROR );
    }
     else
    {
        DBYTEX  *pImapx = &Iprm.Imap.UseLess;
        DBYTEX  Imapx;
        UCHAR	Selx = 0;
          
          
        if( DIDOVar.DigitInSetStatus[3] != ( Prm.insel4 & 0x00FF ))
        {
            Selx = DIDOVar.DigitInSetStatus[3];
            Imapx.b.l = 0;
            Imapx.b.h = 0;            
            pImapx[Selx] = Imapx;
        }
        DIDOVar.DigitInSetStatus[3] = Prm.insel4 & 0x00FF;
          
        Imapx.b.l = KPI_SI3BITNO;
        Imapx.b.h = (Prm.insel4 & 0x0100)? 0x01 : 0x00;
        Iprm.Imap.OnOffSet &= 0xFFEF;
        Iprm.Imap.OnOffSet |=  (Prm.insel4 & 0x0100)? 0x0010 : 0x00;
        Selx =  Prm.insel4 & 0x00FF;
        pImapx[Selx] = Imapx;
          
        rc = (0x0001 << 3 ) ^ 0xFFFF;
        Iprm.Imap.VirSet &= rc;        
        Iprm.Imap.VirSet |= ((( Prm.insel4 >> 12 ) & 0x01 ) << 3 );
    }
}
 
 
  
  
  
void DISeqInputMap_Init( void )
{
  
    MlibResetSHORTMemory( &Iprm.Imap, sizeof( Iprm.Imap ) );
    return;
}
  
/****************************************************************************************************/
/* Function_Name: DigitalOutConfigErrorCheck   */ 
/* Description  : 2.对输出信号是否超限、是否重复分配进行检查处理
                  调用：
                     	*/
/****************************************************************************************************/
USHORT DigitalOutConfigErrorCheck(void)
{
    SHORT   i, j;
    UCHAR OutputPortNum = 0;
      
      
    if( SystemVar.FpgaVer >= 3300 && SystemVar.FpgaVer <= 3399 )
    {
        OutputPortNum = NUM_DIGITALOUT_ETHERCAT_CHANNEL;
    }
    else
    {
        OutputPortNum = NUM_DIGITALOUT_CHANNEL;
    }
     USHORT  uiArrayInput[NUM_DIGITALOUT_CHANNEL];
    USHORT  *p = &Prm.outsel1;
    USHORT  UpperLimit = pndef_outsel1.UpperLimit & 0x0FF;

    
     /* 对上限值进行检查 */
    for (i = 0; i < OutputPortNum; i++)
    {
        uiArrayInput[i] = p[i] & 0x0FF;
        if( uiArrayInput[i] > UpperLimit)
        {
            return (FALSE);
        }
    }
      
    /* 对功能重复检查 */
    for (i = 0; i < OutputPortNum - 1; i++)
    {
        for (j = i + 1; j < OutputPortNum; j++)
        {
            if ((uiArrayInput[i] == uiArrayInput[j]) && (uiArrayInput[i] != 0))
            {
                if(uiArrayInput[i] != 0x10)         // 对特定重复的Y端子不进行检查                   
                {
                    return (FALSE);
                }
            }
        }
    }
    return TRUE;
}
 
  
  
/****************************************************************************************************/
/* Function_Name: DISeqOutput1Map_Init                                                              */ 
/* Description  : 数字量输出端子-----Y1 配置设置                                                    */
/****************************************************************************************************/
void DISeqOutput1Map_Init( void )
{
UCHAR   *pOmapx = &Iprm.Omap.UseLess;
UCHAR   Selx = 0;
USHORT  rc;


     /* 输出端子重复配置检查  */
    rc = DigitalOutConfigErrorCheck( );
    if( rc == FALSE )
    {
        KPI_ALARMSET( ALM_YERROR );
        return;
    }
      
    /*  前面设置的旧值清除 */
    if( DIDOVar.DigitOutSetStatus[0] != ( Prm.outsel1 & 0x00FF ) )
    {
        Selx = DIDOVar.DigitOutSetStatus[0];
        pOmapx[Selx] = 0;
    }
    DIDOVar.DigitOutSetStatus[0] = ( Prm.outsel1 & 0x00FF );

    
    /* 数字量输出端子映射处理部分 */
    Selx =  Prm.outsel1 & 0x00FF;
    pOmapx[Selx] = ( 1 << KPI_SO1BITNO );
      
    /* 数字量输出端子逻辑取反处理 */
    rc = (0x0001 << KPI_SO1BITNO ) ^ 0xFFFF;                     
    Iprm.Omap.RvsXor &= rc;
    Iprm.Omap.RvsXor  |= (((( Prm.outsel1 >> 8  ) ^ 0x01 ) & 0x01 ) << KPI_SO1BITNO );
      
    /* 数字量输出端子内部控制 */
    rc = (0x0001 << KPI_SO1BITNO ) ^ 0xFFFF;                     
    Iprm.Omap.VirDO &= rc;
    Iprm.Omap.VirDO   |= (((  Prm.outsel1 >> 12 ) & 0x01 ) << KPI_SO1BITNO );
}
  
  
  
void DISeqOutput2Map_Init( void )
{
UCHAR   *pOmapx = &Iprm.Omap.UseLess;
UCHAR   Selx = 0;
USHORT  rc;
      
    rc = DigitalOutConfigErrorCheck( );
    if( rc == FALSE )
    {
        KPI_ALARMSET( ALM_YERROR );
        return;
    }
      
    if( DIDOVar.DigitOutSetStatus[1] != ( Prm.outsel2 & 0x00FF ) )
    {
        Selx = DIDOVar.DigitOutSetStatus[1];
        pOmapx[Selx] = 0;
    }
    DIDOVar.DigitOutSetStatus[1] = ( Prm.outsel2 & 0x00FF );
      
    Selx =  Prm.outsel2 & 0x00FF;
    pOmapx[Selx] = ( 1 << KPI_SO2BITNO );
      
      
    rc = (0x0001 << KPI_SO2BITNO ) ^ 0xFFFF;                     
    Iprm.Omap.RvsXor &= rc;
    Iprm.Omap.RvsXor  |= (((( Prm.outsel2 >> 8  ) ^ 0x01 ) & 0x01 ) << KPI_SO2BITNO );
      
      
    rc = (0x0001 << KPI_SO2BITNO ) ^ 0xFFFF;                     
    Iprm.Omap.VirDO &= rc;
    Iprm.Omap.VirDO   |= (((  Prm.outsel2 >> 12 ) & 0x01 ) << KPI_SO2BITNO );
}
 
  
/****************************************************************************************************/
/* Function_Name: IprmcalSeqOutputMap   */ 
/* Description  : 端子输出映射处理
       调   用  ：主函数初始化中                                      */
/****************************************************************************************************/
void IprmcalSeqOutputMap( void )
{
ULONG	ulwk;
UCHAR   *pOmapx = &Iprm.Omap.UseLess;
UCHAR   Selx = 0;
USHORT  UpperLimit = pndef_outsel1.UpperLimit & 0x0FF;
      
    /* 数字量输出端子1映射处理部分 */
    Selx =  Prm.outsel1 & 0x00FF;
    if( Selx > UpperLimit)
    {
        KpiSetParamError( &pndef_outsel1 );
    }
    else
    {
        pOmapx[Selx] = ( 1 << KPI_SO1BITNO );
    }
      
    /* 数字量输出端子2映射处理部分 */
    Selx =  Prm.outsel2 & 0x00FF;
    if( Selx > UpperLimit)
    {
        KpiSetParamError( &pndef_outsel2 );
    }
    else
    {
        pOmapx[Selx] = ( 1 << KPI_SO2BITNO );
    }
 
    /* 数字量输出端子逻辑取反处理 */
    ulwk  = (((( Prm.outsel1 >> 8 ) ^ 0x01 ) & 0x01 ) << KPI_SO1BITNO );
    ulwk |= (((( Prm.outsel2 >> 8 ) ^ 0x01 ) & 0x01 ) << KPI_SO2BITNO );
    Iprm.Omap.RvsXor = ulwk;
    ulwk  = ((( Prm.outsel1 >> 12 ) & 0x01 ) << 0 );
    ulwk |= ((( Prm.outsel2 >> 12 ) & 0x01 ) << 1 );
    Iprm.Omap.VirDO = ulwk;
}
  
  
/****************************************************************************************************/
/* Function_Name: ScanCinputAptIf                              */
/* Description  : ScanC 中开关量输入信号更新     */
/****************************************************************************************************/
void ScanCinputAptIf( void )
{
HWSIN	Inx;
LONG lwk;
LONG SpdLevel;
  
    KPI_SIN_START( Inx );     /* 功能码获取相关的输入信号 */

    /* 紧急停机信号 */
    CinV.f.Sv.EmcyStop = KPI_SIN_EMST( Inx );
    if( CinV.f.Sv.EmcyStop )
    {
        KPI_WARNINGSET( WRN_EMSTOP );
    }
    else
    {
        KPI_WARNINGCLR( WRN_EMSTOP );
    }

    CinV.f.Sv.ExFault = KPI_SIN_ExFault( Inx );                      //外部故障信号
    if( CinV.f.Sv.ExFault && CAN_EXFUNC0_13_EN)
    {
        KPI_ALARMSET( ALM_ExFault );
    }
    if( CoutV.f.Seq.MainPowerOn)
    {
        if( DIDOVar.ServoOnDelay <= Prm.ServoOnDely )
        {
            DIDOVar.ServoOnDelay += 2;
            KPI_WARNINGCLR( WRN_SERVOON );
        }
        else
        {
            CinV.f.Seq.ServoOnTmp   =  KPI_SIN_SVON( Inx );     // 端子使能检测

            CinV.f.Sv.JOGP          =  KPI_SIN_JOGP( Inx );     // 正向点动
            CinV.f.Sv.JOGN          =  KPI_SIN_JOGN( Inx );     // 负向点动
            if( CinV.f.Sv.Pot == 1 && CinV.f.Sv.JOGP == 1 )
            {
                if((CinV.f.Sv.ManualAutoMod == 1) && CAN_EXFUNC0_7_EN)
                {
                    CinV.f.Sv.JOGP = 1;
                }
                else
                {
                    CinV.f.Sv.JOGP = 0;
                }
            }
            if( CinV.f.Sv.Not == 1 && CinV.f.Sv.JOGN == 1 )
            {
                if((CinV.f.Sv.ManualAutoMod == 1) && CAN_EXFUNC0_7_EN)
                {
                    CinV.f.Sv.JOGN = 1;
                }
                else
                {
                    CinV.f.Sv.JOGN = 0;
                }
            }
            if( Prm.b_prm0_1 & 0x0001)
            {
                CinV.f.Seq.ServoOnTmp |= 1;          // 内部强制使能
            }
            if( 1 == MuxAxis485_ServoOnoff())
            {
                CinV.f.Seq.ServoOnTmp |= 1;
            }
#if 0

             if( CoutV.f.Seq.PowerOffflg == 1 )
            {
                CinV.f.Seq.ServoOnTmp = 0;
                if( ++ CoutV.PowoffErrDly > 20 )
                {
                    KPI_ALARMSET( ALM_PWPHASE );
                }
            }
            else
            {
                CoutV.PowoffErrDly = 0;
            }
#endif
             /*  伺服Off时,减速停机选择 */
            if( Prm.offdec == 0 )
            {
                CinV.f.Seq.ServoOn      = CinV.f.Seq.ServoOnTmp;
                CoutV.ServoOffStatus    = 0;
                CinV.f.Seq.ServoOffDecM = 0;
            }
            else
            {

                CoutV.ServoOffStatus = CoutV.ServoOffStatus << 1;
                CoutV.ServoOffStatus = CoutV.ServoOffStatus & 0x03;
                if( CinV.f.Seq.ServoOnTmp == TRUE)
                {
                    CoutV.ServoOffStatus |= 0x01;
                    CoutV.ServoOffStatus = CoutV.ServoOffStatus & 0x03;
                }
                if( CinV.f.Seq.ServoOffDec == FALSE )
                {
                     /* 驱动器未进入到减速停机状态 */
                     if( CoutV.ServoOffStatus == 0x02 )
                    {
                        CinV.f.Seq.ServoOffDec  = 1;
                        CinV.f.Seq.ServoOffDecM = 1;
                        CinV.f.Seq.ServoOn      = 1;
                    }
                     else
                    {
                        CinV.f.Seq.ServoOn      = CinV.f.Seq.ServoOnTmp;
                    }
                }
                else
                {

#if 0
                    lwk = BoutV.SpdLdstpRefo;
                    lwk = (lwk >= 0)? lwk : -lwk;
                    if(  lwk <= 10 )
#else
                    SpdLevel = KpiSpeedLevelCal( 50, 0 );
                    lwk = BinK.MotSpd;
                    lwk = (lwk >= 0)? lwk : -lwk;
                    if(  lwk <= SpdLevel )
    #endif
                    {
                        CinV.f.Seq.ServoOffDec = 0;          /* 退出减速停机 */
                        BoutV.SpdReffinal = 0;
                    }
                }
            }
            if( Kprm.f.StandardType ==TRUE || Kprm.f.CanOpenNet == TRUE )
            {
                if( CinV.f.Sv.JOGP == TRUE && CinV.f.Sv.JOGN == TRUE )
                {
                    CinV.f.Sv.JOGFlag = 0;            // 外部端子点动无效
                    KPI_WARNINGSET( WRN_JOG );
                }
                else
                {
                    if(( CinV.f.Sv.JOGP == TRUE || CinV.f.Sv.JOGN == TRUE ) && RoutV.f.SensOnReq == 0 )
                    {
                        CinV.f.Sv.JOGFlag = 1;
                    }
                    else
                    {
                        CinV.f.Sv.JOGFlag = 0;
                    }
                    KPI_WARNINGCLR(WRN_JOG);
                }

                /* 在未给定使能的情况下如果点动亦可以进行 */
                if( CinV.f.Sv.JOGFlag )
                {
                    CinV.f.Seq.ServoOn |= 1;
                }
            }
            else
            {
                CinV.f.Sv.JOGFlag = 0;
            }
        }
     }
    else
    {
         /* 母线电压未建立完成时,外部有使能信号,则进行AL.940警告 */
        if( ((KPI_SIN_SVON( Inx )) == TRUE ) || (( Prm.b_prm0_1 & 0x0001 ) == 0x0001 ))
        {
            KPI_WARNINGSET( WRN_SERVOON );
        }
        CinV.f.Seq.ServoOn = 0;
        CinV.f.Sv.JOGP     = 0;
        CinV.f.Sv.JOGN     = 0;
        CinV.f.Sv.JOGFlag  = 0;
        KPI_WARNINGCLR(WRN_JOG);
    }

     /* 绝对位置软限位处理  2019.01.14    */
    ABSPosLimitDeal( );

    /* 超程检测开关 */
    CinV.f.Sv.PotIn = KPI_SIN_POT( Inx );
    CinV.f.Sv.NotIn = KPI_SIN_NOT( Inx );

    CinV.f.Sv.TMonTrg = KPI_SIN_TMONTRG( Inx );

    /* 在外部端子限位的基础上进行软限制限定 */
    CinV.f.Sv.ManualAutoMod = KPI_SIN_MAUTOMOD( Inx );
    CinV.f.Sv.PotIn |= CinV.f.Ctrl.AbsPosLimitPot;         // 正限位信号监测
    CinV.f.Sv.NotIn |= CinV.f.Ctrl.AbsPosLimitNot;         // 负限位信号监测
    CoutV.f.Sv.Pot = CinV.f.Sv.PotIn;
    CoutV.f.Sv.Not = CinV.f.Sv.NotIn;
    if( CinV.f.Sv.OTCheck == 1 )
    {
        CinV.f.Sv.Pot = 0;
        CinV.f.Sv.Not = 0;
    }
    else
    {
        CinV.f.Sv.Pot        = CinV.f.Sv.PotIn;             /* 正限位信号监测 */
        CinV.f.Sv.Not        = CinV.f.Sv.NotIn;             /* 负限位信号监测 */
    }

    CinV.f.Seq.AlmReset  = KPI_SIN_ALMRST( Inx );           // 故障复位信号监测
    CinV.f.Sv.SpdD       = KPI_SIN_SPDD( Inx );             // 速度方向
    CinV.f.Sv.SpdA       = KPI_SIN_SPDA( Inx );             // 速度选择 A
    CinV.f.Sv.SpdB       = KPI_SIN_SPDB( Inx );             // 速度选择 B
    CinV.f.Sv.BKSel      = KPI_SIN_BKSEL( Inx );

    if((Prm.prstsw & 0x000F ) != 0x0005 )
    {
        CinV.f.Sv.Csel   = KPI_SIN_CSEL( Inx );         // 控制模式选择
    }
    CinV.f.Sv.Csel2      = KPI_SIN_CSEL2( Inx );        // 控制方式选择2
    CinV.f.Sv.CTrig      = KPI_SIN_CTrig( Inx );        // 控制方式选择确认
    CinV.f.Sv.TorqD      = KPI_TRQ_SIGN( Inx );         // 转矩方向
    CinV.f.Sv.TorqA      = KPI_SIN_TORQA( Inx );        // 转矩选择 A
    CinV.f.Sv.TorqB      = KPI_SIN_TORQB( Inx );        // 转矩选择 B
    CinV.f.Sv.TCtrg      = KPI_SIN_TCTRG( Inx );        // 转矩触发
    CinV.f.Sv.TSLimit    = KPI_SIN_TSPDLIMIT( Inx );    // 转矩限制时速度限制
    CinV.f.Sv.Zclamp     = KPI_SIN_ZCLAMP( Inx );       // 零速钳位
    CoutV.f.Ctrl.JOGP    = CinV.f.Sv.JOGP;
    CoutV.f.Ctrl.JOGN    = CinV.f.Sv.JOGN;
    if(CAN_EXFUNC0_7_EN)
    {
        CinV.f.Sv.ManualAutoMod = KPI_SIN_MAUTOMOD( Inx );
    }

     if( Kprm.f.DIDOScanEn == 1)
    {
        CinV.f.Sv.Fun30      = KPI_SIN_FUN30( Inx );
        CinV.f.Sv.Fun31      = KPI_SIN_FUN31( Inx );
        CinV.f.Sv.Fun32      = KPI_SIN_FUN32( Inx );
        CinV.f.Sv.Fun33      = KPI_SIN_FUN33( Inx );
        CinV.f.Sv.Fun34      = KPI_SIN_FUN34( Inx );
        CinV.f.Sv.Fun35      = KPI_SIN_FUN35( Inx );
        CinV.f.Sv.Fun36      = KPI_SIN_FUN36( Inx );
        CinV.f.Sv.Fun37      = KPI_SIN_FUN37( Inx );
        CinV.f.Sv.Fun38      = KPI_SIN_FUN38( Inx );
        CinV.f.Sv.Fun39      = KPI_SIN_FUN39( Inx );
        CinV.f.Sv.Fun3A      = KPI_SIN_FUN3A( Inx );
        CinV.f.Sv.Fun3B      = KPI_SIN_FUN3B( Inx );
        CinV.f.Sv.Fun3C      = KPI_SIN_FUN3C( Inx );
        CinV.f.Sv.Fun3D      = KPI_SIN_FUN3D( Inx );
        CinV.f.Sv.Fun3E      = KPI_SIN_FUN3E( Inx );
        CinV.f.Sv.Fun3F      = KPI_SIN_FUN3F( Inx );
    }
}
  
  
/****************************************************************************************************/
/* Function_Name: LpxBoutputAptIf         */ 
/* Description  : ScanB模拟脉冲列IF输出处理
      调    用  ：IntScanB调用
   对应端子功能 ：定位完成、位置接近信号、指令脉冲输入倍率切换输出                  	*/
/****************************************************************************************************/
void	LpxBoutputAptIf( void )
{
HWSOUT	Outx;
    Outx.dw = 0;
    KPI_SOUT_COIN(   Outx, BoutV.f.Ctrl.Coin);          // 定位完成
    KPI_SOUT_NEAR(   Outx, BoutV.f.Sv.Near     );       // 位置接近信号
    KPI_SOUT_PSELA(  Outx, Iprm.PGAINSet == 1 ?
                      1 :BoutV.f.Sv.PselA    );         // 指令脉冲输入倍率切换输出
    BoutK.hw.dw = Outx.dw;
    return;
}
  
  
/****************************************************************************************************/
/* Function_Name: LpxCoutputAptIf                                                                   */
/* Description  : 输出信号处理
      调    用  ：IntScanC调用                                                                      */
/****************************************************************************************************/
void	LpxCoutputAptIf( void )
{
HWSOUT	Outx;
  
  
    Outx.dw = 0;
    KPI_SOUT_VCMP(    Outx, CoutV.f.Ctrl.ReachSpd      );       // 速度一致
    KPI_SOUT_TGON(    Outx, CoutV.f.Ctrl.MotorMoving   );		// 电机旋转信号
    KPI_SOUT_SVREADY( Outx, CoutV.f.Seq.ServoReady     );		// 伺服准备好
    KPI_SOUT_CLT(     Outx, BoutV.f.Ctrl.TrqClamp      );		// 转矩限制中
    KPI_SOUT_VLT(     Outx, BoutV.f.Ctrl.SpdClamp      );		// 速度限制中
    KPI_SOUT_BRAKE(   Outx, CoutV.f.Seq.BrkReleasing   );		// 制动信号
    KPI_SOUT_WARNING( Outx, Alm.f.WrnFlag              );		// 警告信号
    KPI_SOUT_ALARM(   Outx, Alm.f.AlmFlag              );		// 故障信号
    KPI_SOUT_TORREACH(Outx, BoutV.f.Ctrl.TorqReach     );       // 设定转矩到达

    if( Kprm.f.EtherCATNet )
    {
        KPI_SOUT_EtherCatY1(Outx,Obj60FE_01.f.Y1);
        KPI_SOUT_EtherCatY2(Outx,Obj60FE_01.f.Y2);
    }

    //------------------------------ 手自动手动模式JOGP JOGNY端子输出----------------
    if((CinV.f.Sv.ManualAutoMod == 1) && CAN_EXFUNC0_7_EN)
    {
        KPI_SOUT_JOGP(Outx, CoutV.f.Ctrl.JOGP     );                // 正向点动端子
        KPI_SOUT_JOGN(Outx, CoutV.f.Ctrl.JOGN     );                // 负向点动端子
    }

    KPI_SOUT_CMDOK(   Outx, Pr_DICtrgV.f.CMDOK         );          // 指令发送完成
    KPI_SOUT_TPOS(    Outx, Pr_DICtrgV.f.TPOS          );           // 指令定位完成
    KPI_SOUT_MCOK(    Outx, Pr_DICtrgV.f.MCOK          );           // 指令定位完成延时后

    KPI_SOUT_STO (  Outx,BoutV.f.Ctrl.SafetyStop       );           // STO引脚
    KPI_SOUT_ORGC(  Outx,CoutV.f.Ctrl.OrgC             );           // 原点回归完成


    if( Kprm.f.DIDOScanEn == 1)
    {
        KPI_SOUT_Fun20(    Outx,Pr_DICtrgV.f.Fun20         );
        KPI_SOUT_Fun21(    Outx,Pr_DICtrgV.f.Fun21         );
        KPI_SOUT_Fun22(    Outx,Pr_DICtrgV.f.Fun22         );
        KPI_SOUT_Fun23(    Outx,Pr_DICtrgV.f.Fun23         );
        KPI_SOUT_Fun24(    Outx,Pr_DICtrgV.f.Fun24         );
        KPI_SOUT_Fun25(    Outx,Pr_DICtrgV.f.Fun25         );
        KPI_SOUT_Fun26(    Outx,Pr_DICtrgV.f.Fun26         );
        KPI_SOUT_Fun27(    Outx,Pr_DICtrgV.f.Fun27         );
        KPI_SOUT_Fun28(    Outx,Pr_DICtrgV.f.Fun28         );
        KPI_SOUT_Fun29(    Outx,Pr_DICtrgV.f.Fun29         );
        KPI_SOUT_Fun2A(    Outx,Pr_DICtrgV.f.Fun2A         );
        KPI_SOUT_Fun2B(    Outx,Pr_DICtrgV.f.Fun2B         );
        KPI_SOUT_Fun2C(    Outx,Pr_DICtrgV.f.Fun2C         );
        KPI_SOUT_Fun2D(    Outx,Pr_DICtrgV.f.Fun2D         );
        KPI_SOUT_Fun2E(    Outx,Pr_DICtrgV.f.Fun2E         );
        KPI_SOUT_Fun2F(    Outx,Pr_DICtrgV.f.Fun2F         );
    }
    CoutK.hw.dw = Outx.dw;

         
    /*  Un00C : 指令脉冲计数器 [pulse]  */
    CoutV.f.Sv.PrefSign = (CinK.dPcmdCnt >= 0)? TRUE : FALSE;
    CoutRrst.UnPcmdCntr = CoutRrst.UnPcmdCntr + CinK.dPcmdCnt;


    if( 0 == CoutV.f.Seq.BrkReleasing )
    {
        MotorBK_On();
    }
    else
    {
        MotorBK_Off();
    }
    return;
}
  
  
/****************************************************************************************************/
/* Function_Name: YOutPutToFPGA  */ 
/* Description  : Y端子信号传送给FPGA侧处理
       调    用  ：IntScanB  */
/****************************************************************************************************/
void YOutPutToFPGA( void )
{
    ULONG kx,kx1;
     /* 将所有的输出信号进行处理成一个变量  */
    if( RoutV.OutModeFlg )
    {
         /* 强制输出模式  */
         kx = RoutV.ForceOutSig.dw ^ 0x3F;
    }
    else
    {
         /* 正常输出模式 */
         kx = ( BoutK.hw.dw | CoutK.hw.dw ) ^ Iprm.Omap.RvsXor;
    }
    kx ^= 0x00FF;
    kx1 = Iprm.Omap.VirDO ^ 0x003F;
    kx  = ( kx & kx1 ) | (Prm.VirDO & Iprm.Omap.VirDO);
      
    BoutK.UnOutSignal = (USHORT)kx;     // 传送给Un006（输入指令脉冲计数器）使用                         
    if( Iprm.FATest1 == 1 || Iprm.FATest2 == 1 )
    {
        kx = Prm.VirDO;
    }
      
    OutputScan( kx );
}
  
  
