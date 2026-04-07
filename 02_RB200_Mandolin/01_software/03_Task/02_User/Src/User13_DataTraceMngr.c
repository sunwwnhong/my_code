/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : User13_DataTraceMngr.c
* Version            : V0.1
* Date               : 2024
* Description        : 数据跟踪操作管理
***********************************************************************************************/

#include "Main.h"



TRCBUF	Trcbuf;
TRCEXEP	TrcExeP;
TRCEXEV	TrcExeV;
TRCREG	TrcReg;								/* 跟踪控制数据寄存器									*/
TRCVARX	TrcVarX;
#define	TBLFUNCBIT_EGEAR		0x0200      /* 电子齿轮比											*/


/****************************************************************************************************/
/*																									*/
/*		数据跟踪表，索引管理参数定义																*/
/*																									*/
/****************************************************************************************************/
typedef	struct	{
		USHORT	TrcVarTblEntNum;					/* 数值触发追踪定义表登记个数                    */
		USHORT	TrcVarTblSrhIniW;					/* 数值触发轨迹定义表检索分割宽度初始值	    */
/*--------------------------------------------------------------------------------------------------*/
		USHORT	TrcBitTblEntNum;					/* 比特触发轨迹定义表登记个数			*/
		USHORT	TrcBitTblSrhIniW;					/* 比特触发轨迹定义表检索分割宽度初始值	*/
} TRCMNGP;
/*--------------------------------------------------------------------------------------------------*/
typedef	struct	{
		USHORT	TrcOpeRegWrtCnt;					/* 参数计算执行检查用,当TrcReg中有变量写入，就++，用来更新参数	*/
		USHORT	TdrvOpeRegWrtCnt;					/* 参数计算执行检查用							*/
} TRCMNGV;
/*--------------------------------------------------------------------------------------------------*/
TRCMNGP	TrcMngP;									/* 追踪管理参数						*/
TRCMNGV	TrcMngV;									/* 追踪管理数据变量						*/
/*--------------------------------------------------------------------------------------------------*/
#define	DTRCBUF_REGNO		0x4000					/* 数据跟踪缓冲器开头寄存器编号		*/
/*--------------------------------------------------------------------------------------------------*/
#define TRCVARTBL_ENTNUM	TrcVarTblEntNum
#define TRCBITTBL_ENTNUM    TrcBitTblEntNum



/**********************************************************************************************/
/* Function_Name: RpxInitDtrcManager         */
/* Description  : 数据采集管理初始化处理
                  调用：初始化调用一次
                  输入：
                  输出：   */
/**********************************************************************************************/
void	RpxInitDtrcManager( void )
{
LONG	EntNum;
/*备注:后续可以优化此部分,加快索引速度  2017.08.10 zhuxc                                            */
/*--------------------------------------------------------------------------------------------------*/
/*** 数值触发，索引用变量初始化 ***/
/*--------------------------------------------------------------------------------------------------*/
		EntNum = TRCVARTBL_ENTNUM;
		TrcMngP.TrcVarTblEntNum = (USHORT)EntNum;
		/*** 找出最高非0bit位置，并1移位这么多。为后续索引算法准备 ***/
		TrcMngP.TrcVarTblSrhIniW = (1 << MlibSrhbiton( EntNum - 1, SRH_FROM_MSB ));
/*--------------------------------------------------------------------------------------------------*/
/*	bit触发，索引用变量初始化  */
/*--------------------------------------------------------------------------------------------------*/
		EntNum = TRCBITTBL_ENTNUM;
		TrcMngP.TrcBitTblEntNum = (USHORT)EntNum;
		TrcMngP.TrcBitTblSrhIniW = (1 << MlibSrhbiton( EntNum - 1, SRH_FROM_MSB ));
/*--------------------------------------------------------------------------------------------------*/
/*		数据追踪管理数据变量重置														*/
/*--------------------------------------------------------------------------------------------------*/
		MlibResetSHORTMemory( &TrcMngV, sizeof(TrcMngV) );
/*--------------------------------------------------------------------------------------------------*/
/*		数据跟踪参数计算																*/
/*--------------------------------------------------------------------------------------------------*/
		RpiPcalDataTraceParameter( );				/* 数据追踪执行结构体参数计算			    */
		RpiPcalTableDriveParameter( );				/* 表运行执行参数计算			*/
/*--------------------------------------------------------------------------------------------------*/
		return;
}


/**********************************************************************************************/
/* Function_Name: RpxStopDataTrace         */
/* Description  : 单次数据跟踪停止处理
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
LONG	RpxStopDataTrace( void )
{

		TrcExeV.TrcCmd = TRCCMD_NOCMD;
		TrcExeV.OpmRun = FALSE;
		TrcExeV.Opened = FALSE;
		return( REGIF_COMPLETE );

}


/**********************************************************************************************/
/* Function_Name: RpxSetDataTraceMode         */
/* Description  : 数据跟踪模式设定处理
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
LONG	RpxSetDataTraceMode( USHORT mode )
{

		if ( TrcExeV.Opened == TRUE )           /* 数据追踪功能是否已经开放?*/
		{
			return ( REGIF_FOPEERR1 );
		}
		else
		{
			TrcExeV.Opened = TRUE;
			TrcExeV.OpmRun = TRUE;
			return( REGIF_COMPLETE );
		}
}



/**********************************************************************************************/
/* Function_Name: RpxWriteTrcOpeRegister         */
/* Description  : 跟踪操作寄存器TrcReg写入处理
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
LONG	RpxWriteTrcOpeRegister( CFORDEF* pForDef, ULONG WrData, void* Hmsg )
{

/*--------------------------------------------------------------------------------------------------*/
/*		寄存器数据写入																		*/
/*--------------------------------------------------------------------------------------------------*/
		if( pForDef->Attr.IsLong )
		{
			*(ULONG*)(pForDef->VarAdr) = WrData;
		}
		else
		{
			*(USHORT*)(pForDef->VarAdr) = (USHORT)WrData;
		}
/*--------------------------------------------------------------------------------------------------*/
        /*** 参数计算执行检查用,当TrcReg中有变量写入，就++，用来更新参数 ***/
		TrcMngV.TrcOpeRegWrtCnt++;   
/*--------------------------------------------------------------------------------------------------*/
        /* 数据采集操作寄存器中采样间隔有更新，TrcMngV.TdrvOpeRegWrtCnt就++                                             */
		if( pForDef->VarAdr == (void*)&TrcReg.SampIntv )
        {
            TrcMngV.TdrvOpeRegWrtCnt++;   // Table表计算，写入标志++；TrcReg.SampIntv用于了Table的计算过程
        }
/*--------------------------------------------------------------------------------------------------*/
		return( REGWRF_COMPLETE );
}





/**********************************************************************************************/
/* Function_Name: LpxSearchTrcVarTbl         */
/* Description  : 数据追踪对象变量表搜索处理;检索原理和辅助寄存器的检索原理一样。
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
LONG	LpxSearchTrcVarTbl( LONG SelNo )
{
LONG	i,w;
LONG	EntNum;
const	TVXDEF* TvxTbl;

/*--------------------------------------------------------------------------------------------------*/
/*		设置检索用数据																			*/
/*--------------------------------------------------------------------------------------------------*/
		TvxTbl = TrcVarTbl;
		EntNum = TrcMngP.TrcVarTblEntNum;
		w = TrcMngP.TrcVarTblSrhIniW;
/*--------------------------------------------------------------------------------------------------*/
/*		设置搜索开始索引																			*/
/*--------------------------------------------------------------------------------------------------*/		
		i = ( SelNo >= TvxTbl[w].SelNo )? (EntNum - w) : 0;
/*--------------------------------------------------------------------------------------------------*/
/*		表格搜索																				*/
/*--------------------------------------------------------------------------------------------------*/
		for( w = w>>1; w > 0; w = w>>1 )
		{
			if( SelNo >= TvxTbl[i+w].SelNo ){ i = i + w;}
		}
/*--------------------------------------------------------------------------------------------------*/
/*		搜索结果检查																			*/
/*--------------------------------------------------------------------------------------------------*/
		if( SelNo == TvxTbl[i].SelNo )
		{
			return( i );
		}
		else
		{
			return( -1 );
		}
}

/**********************************************************************************************/
/* Function_Name: LpxSearchTrcBitTbl         */
/* Description  : I/O追踪对象变量表搜索处理;检索原理和辅助寄存器的检索原理一样。
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
LONG	LpxSearchTrcBitTbl( LONG SelNo )
{
LONG	i,w;
LONG	EntNum;
const	TBXDEF* TbxTbl;

/*--------------------------------------------------------------------------------------------------*/
/*		设置检索用数据																			*/
/*--------------------------------------------------------------------------------------------------*/
		TbxTbl = TrcBitTbl;										/* 定义表指针				*/
		EntNum = TrcMngP.TrcBitTblEntNum;						/* 定义表登录个数				*/
		w = TrcMngP.TrcBitTblSrhIniW;							/* 分割宽度初始值设定					*/
/*--------------------------------------------------------------------------------------------------*/
/*		设置搜索开始索引																			*/
/*--------------------------------------------------------------------------------------------------*/
		i = ( SelNo >= TbxTbl[w].SelNo )? (EntNum - w) : 0;		/* 搜索开始索引设置				*/
/*--------------------------------------------------------------------------------------------------*/
/*		表格搜索																				*/
/*--------------------------------------------------------------------------------------------------*/
		for( w = w>>1; w > 0; w = w>>1 )						/* 搜索Loop						*/
		{
			if( SelNo >= TbxTbl[i+w].SelNo ){ i = i + w;}		/* 比较& Index更新					*/
		}
/*--------------------------------------------------------------------------------------------------*/
/*		搜索结果检查																			*/
/*--------------------------------------------------------------------------------------------------*/
		if( SelNo == TbxTbl[i].SelNo )
		{
			return( i );										/* 搜索完成							*/
		}
		else
		{
			return( -1 );										/* 搜索失败				*/
		}
}

/**********************************************************************************************/
/* Function_Name: LpxPcalMotSpeedCalGain2         */
/* Description  : 电机速度增益的计算(每次采样)
                  调用：需要时调用
                  输入：
                  输出：   */
/****************************************************************************************************/
/*																									*/
/*							1																		*/
/*		Kx = ----------------------------										 					*/
/*				 TrcExeP.DataSampIntv 																*/
/*																									*/
/****************************************************************************************************/
LONG	LpxPcalMotSpeedCalGain2( void )
{
LONG	kx;

		kx = MlibScalKxgain( 1, 1, TrcExeP.DataSampIntv, NULL, 24 );
		return( kx );
}

/**********************************************************************************************/
/* Function_Name: LpxPcalMotSpeedCalGain         */
/* Description  : 电机速度增益的计算(每次采样)
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
/*																									*/
/*							Hprm.Kmotspd * 1000000													*/
/*		Kmotspd = ------------------------------------------					 					*/
/*					 KPI_SBCYCLEUS * TrcExeP.DataSampIntv 											*/
/*																									*/
/****************************************************************************************************/
LONG	LpxPcalMotSpeedCalGain( void )
{
LONG	kx,plsno;

        if( Kprm.f.FencUse )
        {
            plsno = Hprm.KmotspdFC;
        }
        else
        {
            plsno = Hprm.Kmotspd;
        }

		kx = MlibScalKskxkx( plsno, 1000000,  (KPI_SBCYCLEUS * TrcExeP.DataSampIntv),  NULL, 24 );
		return( kx );
}

/**********************************************************************************************/
/* Function_Name: LpxPcalPcmdSpeedCalGain         */
/* Description  : 位置指令速度运算增益的计算(每采样)
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
/*																									*/
/*							Egear.b * Hprm.Kmotspd * 1000000										*/
/*		Kpcmdspd = ---------------------------------------------------								*/
/*					 Egear.a * KPI_SBCYCLEUS * TrcExeP.DataSampIntv 								*/
/*																									*/
/****************************************************************************************************/
LONG	LpxPcalPcmdSpeedCalGain( LONG EgearDisable )
{
LONG	kx,sx,plsno;

        plsno = Hprm.Kmotspd;

		if(EgearDisable)
		{
			kx = MlibScalKskxkx( plsno, 1, 1, &sx,  0 );
		}
		else
		{
			kx = MlibScalKskxkx( plsno, Iprm.Egear.b, Iprm.Egear.a, &sx,  0 );
		}
		kx = MlibPcalKxgain( kx, 1000000, (KPI_SBCYCLEUS * TrcExeP.DataSampIntv), &sx, 24 );
		return( kx );
}


/**********************************************************************************************/
/* Function_Name: LpxPcalTraceObject         */
/* Description  : 根据地址信息索引对应跟踪index，然后设置对应通道Tno的目标跟踪信息。
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
LONG	LpxPcalTraceObject( LONG Tno )
{
LONG	i,j;
LONG	x,y;
TRCOBJ	*TrcObj = &TrcExeP.TrcObj[Tno];
/*--------------------------------------------------------------------------------------------------*/
/*		数据通道采集检查: 若此通道缓存指针为0，说明通道未使能，不进行数据跟踪，对应变量都清零			*/
/*--------------------------------------------------------------------------------------------------*/
		if( TrcObj->TrcBuf == NULL )
		{
			TrcObj->TrcExe = 0x00;
			TrcObj->VarAdr = NULL;
			TrcObj->BtvAdr = NULL;
			TrcObj->VxGain = 0;
			return( TRUE );
		}
/*--------------------------------------------------------------------------------------------------*/
/*		数值数据追踪对象设定																		*/
/*--------------------------------------------------------------------------------------------------*/
		/*------------------------------------------------------------------------------------------*/
		/* 监控通道数据对应的地址: 高8位:I/O对象，低8位:数据对象										*/
		/*------------------------------------------------------------------------------------------*/
		i = TrcReg.TrcSel[Tno] & 0xFF;
		if( (j = LpxSearchTrcVarTbl( i )) >= 0 )
		{
			TrcObj->VarAdr = (LONG*)TrcVarTbl[j].VarAdr;    // 跟踪对象指定地址，当TrcSel低8位为0x7F或FF时使用
            /*--------------------------------------------------------------------------------------*/
			if( TrcObj->VarAdr == &TrcVarX.MotSpdSmp )
			{
				TrcObj->VxGain = LpxPcalMotSpeedCalGain2( );
			}
            /*--------------------------------------------------------------------------------------*/
			else if( TrcObj->VarAdr == &TrcVarX.dPosRefSmp )
			{
				TrcObj->VxGain = LpxPcalMotSpeedCalGain( );
			}
            /*--------------------------------------------------------------------------------------*/
			else if( TrcObj->VarAdr == &TrcVarX.dPosCmdSmp )
			{
				TrcObj->VxGain = LpxPcalPcmdSpeedCalGain(TrcReg.TblFuncSel & TBLFUNCBIT_EGEAR);
			}
            /*--------------------------------------------------------------------------------------*/
			else
			{
				TrcObj->VxGain = 0;
			}
            /*--------------------------------------------------------------------------------------*/
			/***
			            1)数据类型自身的对齐值：基本数据类型的自身对齐值，等于sizeof(基本数据类型)。

			            2)指定对齐值：#pragma pack (value)时的指定对齐值value。

			            3)结构体或者类的自身对齐值：其成员中自身对齐值最大的那个值。

			            4)数据成员、结构体和类的有效对齐值：自身对齐值和指定对齐值中较小的那个值。

			            有效对齐值N是最终用来决定数据存放地址方式的值，最重要。有效对齐N，就是表示“对齐在N上”，
			            也就是说该数据的"存放起始地址%N=0".而数据结构中的数据变量都是按定义的先后顺序来排放的。
			            第一个数据变量的起始地址就是 数据结构的起始地址。结构体的成员变量要对齐排放，结构体本身
			            也要根据自身的有效对齐值圆整(就是结构体成员变量占用总长度需要是对结构体有效对齐值的整 数倍)

			            5)这里采用long型指针去访问变量，因为要统一赋值到一个指针，当存在不同类型指针时，只能转换到一种上。

			            6)这里采用long型，因为大部分跟踪数据都是long型数据，对个别16bit型数据，采用内存对齐操作处理。

			        ***/
			switch( TrcVarTbl[j].VxType )
			{
                case XTRCDEF_TxSHORT:
                    /*** 将变量地址数据转换到long型，若地址为4的倍数，则说明数据本身是对齐的，
                                 不需要对地址进行额外处理，直接赋值给long*型地址即可 ***/
                     if( ((LONG)TrcObj->VarAdr & 0x03) == 0x00 )
                     {
                        TrcObj->VxSftL = TrcVarTbl[j].VxSftL + 16;
                        TrcObj->VxSftR = TrcVarTbl[j].VxSftR + 16;
                     }
                     /*** 若地址不为4的倍数，则数据右移16bit，地址4的余数去掉，这里是字，所以余数应该是2. ***/
                     else
                     {
                        TrcObj->VxSftL = TrcVarTbl[j].VxSftL;
                        TrcObj->VxSftR = TrcVarTbl[j].VxSftR + 16;
                        /*** 这里的，(LONG)强制类型转换，转换的是地址变量类型；(LONG*)强制类型转换，
                                        转换的是地址变量所指向的指针类型 ***/
                        TrcObj->VarAdr = (LONG*)((LONG)TrcObj->VarAdr & (~0x03));  // 地址减2，所以，这里数据要右移16bit
                     }
                     break;
                default:
                     TrcObj->VxSftL = TrcVarTbl[j].VxSftL;  //long型数据的话，不需要额外处理。
                     TrcObj->VxSftR = TrcVarTbl[j].VxSftR;
                     break;
			}
		}
		/*** 没检索到地址，则采用虚设变量 ***/
		else
		{
			TrcObj->VarAdr = &ReadDummy.Long;
			TrcObj->VxSftL = 0;
			TrcObj->VxSftR = 0;
			TrcObj->VxGain = 0;
			TrcObj->TrcExe = 0x00;
			return( FALSE );
		}
		
		 /*** 若地址不是4倍数，也采用虚设变量。这里不会，因为前面已经对齐了 ***/
		if( (LONG)TrcObj->VarAdr & 0x01 )    // 地址是否正确20230101
		{
			TrcObj->VarAdr = &ReadDummy.Long;
			TrcObj->VxSftL = 0;
			TrcObj->VxSftR = 0;
			TrcObj->VxGain = 0;
			TrcObj->TrcExe = 0x00;
			return( FALSE );
		}
		/*------------------------------------------------------------------------------------------*/
		/*** 监控的IO地址: 这里采用uchar型指针去访问变量，这样不用考虑内存对齐的问题，同
		    时找bit位数也很方便。 ***/
		/*------------------------------------------------------------------------------------------*/
		i = (TrcReg.TrcSel[Tno] >> 8) & 0xFF;  // 高8bit，IO对象地址
		if( (j = LpxSearchTrcBitTbl( i )) >= 0 )
		{
			x = TrcBitTbl[j].BitNo >> 4;        // 8bit的整数个数，也即字节数
			y = TrcBitTbl[j].BitNo & 0x0F;      // 8bit的余数，也即字节中的位置
			TrcObj->BtvAdr = (UCHAR*)TrcBitTbl[j].VarAdr + x;   // 这里访问采用字节地址，所以加上x
			TrcObj->BtvBit = (1 << y);          // 在整数字节获得地址后，再左移余数
		}

		/*** 没有找到变量，全部清零 ***/
		else
		{
			TrcObj->BtvAdr = NULL;
			TrcObj->BtvBit = 0x00;
			TrcObj->TrcExe = 0x00;
			return( FALSE );
		}
		/*** 该通道可以触发 ***/
		TrcObj->TrcExe = 0x01;
		return( TRUE );
}

/**********************************************************************************************/
/* Function_Name: RpiPcalDataTraceParameter         */
/* Description  : 数据跟踪运行参数计算处理
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void	*RpiPcalDataTraceParameter( void )
{
LONG	i;
LONG	x,y;

		TrcExeP.TrcPrmOk = FALSE;						/* 数据追踪参数OK清零		*/
/*--------------------------------------------------------------------------------------------------*/
/*		跟踪区域 Size																				*/
/*--------------------------------------------------------------------------------------------------*/
		if ( TrcReg.AreaSize > TrcReg.MaxAreaSize )
		{
			return( &TrcReg.AreaSize );
		}
/*--------------------------------------------------------------------------------------------------*/
/*		数据跟踪：上下限数据																	*/
/*--------------------------------------------------------------------------------------------------*/
		if( TrcReg.DataSize <= 1 )						/* 短数据跟踪16bit，取15位有符号								*/
		{
			TrcExeP.UpperLmt =  16383;
			TrcExeP.LowerLmt = -16384;
		}
		else											/* 长数据跟踪32bit，取31位有符号								*/
		{
			TrcExeP.UpperLmt =  1073741823;
			TrcExeP.LowerLmt = -1073741824;
		}
/*--------------------------------------------------------------------------------------------------*/
		/*** 数据跟踪：位设置
		    I/O数据采集为真时，最高位置1；I/O数据采集为假时，最高位清0 ***/
/*--------------------------------------------------------------------------------------------------*/
		if( TrcReg.DataSize <= 1 )						/* 短数据跟踪16bit				*/
		{
			TrcExeP.TrcBitSet = 0x8000;
			TrcExeP.TrcBitClr = ~TrcExeP.TrcBitSet;
		}
		else											/* 长数据跟踪32bit						*/
		{
			TrcExeP.TrcBitSet = 0x80000000;
			TrcExeP.TrcBitClr = ~TrcExeP.TrcBitSet;
		}
/*--------------------------------------------------------------------------------------------------*/
/*		跟踪数据通道数据个数；通道数据个数=总的缓冲个数(16bit)/通道个数/(2(32bit)或1(16bit))						*/
/*--------------------------------------------------------------------------------------------------*/
		x = TrcReg.TrcMode.b.l;
		if( (x < 1) || (x > 4) )
		{
			return( &TrcReg.TrcMode );            // 通道个数小于1或大于4，报警异常
		}
		y = (TrcReg.DataSize <= 1)? x : (2*x);
		TrcExeP.TrcDnum = (USHORT)(TrcReg.AreaSize / y);        //每个通道采集的数据个数
        
/*--------------------------------------------------------------------------------------------------*/
/*		预触发位置合法性检查																		*/
/*--------------------------------------------------------------------------------------------------*/
		if( TrcReg.PtrgDnum >= TrcExeP.TrcDnum )
		{
			return( &TrcReg.PtrgDnum );
		}
        
		/*** Trace data buffer；数据跟踪执行结构体获取各个通道跟踪数据缓存区起始地址 ***/
		    /*** 数据跟踪的大小:16位or32位，(UCHAR*)(&Trcbuf)强制转换为了8bit类型，Trcbuf是16bit，
		    所以，这里个数多乘了2. ***/
		x = (TrcReg.DataSize <= 1)? (1 * TrcExeP.TrcDnum) : (2 * TrcExeP.TrcDnum);
		switch( TrcReg.TrcMode.b.l )
		{
            case 1:     /* 开启1个通道 */
                    TrcExeP.TrcObj[0].TrcBuf = (UCHAR*)(&Trcbuf) + 0;
                    TrcExeP.TrcObj[1].TrcBuf = NULL;
                    TrcExeP.TrcObj[2].TrcBuf = NULL;
                    TrcExeP.TrcObj[3].TrcBuf = NULL;
                    break;
            case 2:     /* 开启2个通道 */
                    TrcExeP.TrcObj[0].TrcBuf = (UCHAR*)(&Trcbuf) + 0;
                    TrcExeP.TrcObj[1].TrcBuf = (UCHAR*)(&Trcbuf) + x;
                    TrcExeP.TrcObj[2].TrcBuf = NULL;
                    TrcExeP.TrcObj[3].TrcBuf = NULL;
                    break;
            case 3:     /* 开启3个通道 */
                    TrcExeP.TrcObj[0].TrcBuf = (UCHAR*)(&Trcbuf) +  0;
                    TrcExeP.TrcObj[1].TrcBuf = (UCHAR*)(&Trcbuf) + (1*x);
                    TrcExeP.TrcObj[2].TrcBuf = (UCHAR*)(&Trcbuf) + (2*x);
                    TrcExeP.TrcObj[3].TrcBuf = NULL;
                    break;
            case 4:     /* 开启4个通道 */
                    TrcExeP.TrcObj[0].TrcBuf = (UCHAR*)(&Trcbuf) +  0;
                    TrcExeP.TrcObj[1].TrcBuf = (UCHAR*)(&Trcbuf) + (1*x);
                    TrcExeP.TrcObj[2].TrcBuf = (UCHAR*)(&Trcbuf) + (2*x);
                    TrcExeP.TrcObj[3].TrcBuf = (UCHAR*)(&Trcbuf) + (3*x);
                    break;
            default:
                    return( &TrcReg.TrcMode );
		}
/*--------------------------------------------------------------------------------------------------*/
/*		跟踪数据取样间隔，最大64；获取采样间隔																			*/
/*--------------------------------------------------------------------------------------------------*/
		if(TrcReg.SampIntv > 64)		/* 溢出的取样间隔 2^(30-24)=64								*/
		{
			TrcExeP.DataSampIntv = 64;
		}
		else
		{
			TrcExeP.DataSampIntv = TrcReg.SampIntv;
		}
/*--------------------------------------------------------------------------------------------------*/
/*		数据采集，索引确定跟踪对象。对总共四个通道都进行处理					                    					*/
/*--------------------------------------------------------------------------------------------------*/
		for( i=0; i < 4; i++ )
		{
			if( LpxPcalTraceObject( i ) == FALSE )
			{
				return( &TrcReg.TrcSel[i] );
			}
		}
/*--------------------------------------------------------------------------------------------------*/
/*		数据采集，索引确定跟踪对象。对总共四个通道都进行处理																				*/
/*--------------------------------------------------------------------------------------------------*/
		x = TrcReg.TrgSel & 0x0F;                         // 触发通道
		y = TrcReg.TrgLevel.Long;                       /* 触发值                                   */
		if( (1 <= x)&&(x <= 4) )						/* 数值水平触发器							*/
		{
			TrcExeP.TrgEdge  = (TrcReg.TrgSel >> 4) & 0x0F;   // 触发类型
			TrcExeP.TrgBufx  = TrcExeP.TrcObj[x-1].TrcBuf;    // 对应触发通道[x]的数据缓冲指针
			TrcExeP.TrgVsft  = (TrcReg.DataSize <= 1)? 17 : 1;// 触发跟踪数据移位 LONG:1; SHORT:17
			TrcExeP.TrgLevel = TrcReg.TrgLevel.Long;          // 触发值
			/*** 触发类型为0或触发数据通道指针为0，则触发通道为0；否则为所选通道。TrgBufx == NULL用来确定触发通道已经开启 ***/
			TrcExeP.TrgSel   = ((TrcExeP.TrgEdge == 0x00)||(TrcExeP.TrgBufx == NULL))? 0 : (UCHAR)x;
		}

		/*** 比特触发器，此情况下，y = TrcReg.TrgLevel.Long表示触发通道 ***/
		else if( (x == 9)&&(1 <= y)&&(y <= 4) )			/* 比特触发器								*/
		{
			TrcExeP.TrgEdge  = (TrcReg.TrgSel >> 4) & 0x0F;    // 触发类型
			TrcExeP.TrgBufx  = TrcExeP.TrcObj[y-1].TrcBuf;     // 对应触发通道[y]的数据缓冲指针
			TrcExeP.TrgVsft  = 0;
			TrcExeP.TrgLevel = 0;                              // bit触发，只在0和1变化，触发值固定为0即可。
			/*** 触发类型为0或触发数据通道指针为0，则触发通道为0；否则为所选通道。TrgBufx == NULL用来确定触发通道已经开启 ***/
			TrcExeP.TrgSel   = ((TrcExeP.TrgEdge == 0x00)||(TrcExeP.TrgBufx == NULL))? 0 : (UCHAR)x;
		}
		else											/* 无触发通道									*/
		{
			TrcExeP.TrgEdge  = 0;
			TrcExeP.TrgBufx  = NULL;
			TrcExeP.TrgVsft  = 0;
			TrcExeP.TrgLevel = 0;
			TrcExeP.TrgSel   = 0;
		}
/*--------------------------------------------------------------------------------------------------*/
		/*** 触发器条件設定：若为多触发，则对第二触发控制参数也按照上述一样的方法，不再重复注释 ***/
/*--------------------------------------------------------------------------------------------------*/
		if( (TrcReg.MTrgMode == 1) || (TrcReg.MTrgMode == 2) )	/* 多触发对应						*/
		{
			x = TrcReg.MTrgSel & 0x0F;
			y = TrcReg.MTrgLevel.Long;
			if( (1 <= x)&&(x <= 4) )							/* 数值级触发器					*/
			{
				TrcExeP.MTrgEdge  = (TrcReg.MTrgSel >> 4) & 0x0F;
				TrcExeP.MTrgBufx  = TrcExeP.TrcObj[x-1].TrcBuf;
				TrcExeP.MTrgVsft  = (TrcReg.DataSize <= 1)? 17 : 1;
				TrcExeP.MTrgLevel = TrcReg.MTrgLevel.Long;
				TrcExeP.MTrgSel   = ((TrcExeP.MTrgEdge == 0x00)||(TrcExeP.MTrgBufx == NULL))? 0 : (UCHAR)x;
			}
			else if( (x == 9)&&(1 <= y)&&(y <= 4) )				/* 比特触发器，此情况下，y = TrcReg.TrgLevel.Long表示触发通道						*/
			{
				TrcExeP.MTrgEdge  = (TrcReg.MTrgSel >> 4) & 0x0F;
				TrcExeP.MTrgBufx  = TrcExeP.TrcObj[y-1].TrcBuf;
				TrcExeP.MTrgVsft  = 0;
				TrcExeP.MTrgLevel = 0;
				TrcExeP.MTrgSel   = ((TrcExeP.MTrgEdge == 0x00)||(TrcExeP.MTrgBufx == NULL))? 0 : (UCHAR)x;
			}
			else												/* 无触发通道					*/
			{
				TrcExeP.MTrgEdge  = 0;
				TrcExeP.MTrgBufx  = NULL;
				TrcExeP.MTrgVsft  = 0;
				TrcExeP.MTrgLevel = 0;
				TrcExeP.MTrgSel   = 0;
			}
		}

		// 无多触发通道，第二触发控制参数
		else
		{
				TrcExeP.MTrgEdge  = 0;
				TrcExeP.MTrgBufx  = NULL;
				TrcExeP.MTrgVsft  = 0;
				TrcExeP.MTrgLevel = 0;
				TrcExeP.MTrgSel   = 0;
		}
/*--------------------------------------------------------------------------------------------------*/
/*		数据跟踪参数计算完毕																		*/
/*--------------------------------------------------------------------------------------------------*/
		TrcExeP.TrcPrmOk = TRUE;						/* 数据跟踪参数计算完毕		*/
		return( NULL );									/* 参数计算完成返回				*/

}

/**********************************************************************************************/
/* Function_Name: RpxWriteTrcTdrvOpeRegEnd         */
/* Description  : 跟踪操作寄存器TrcReg存在写入，则进行跟踪参数重新计算；若采样间隔改变，进行表运转变量计算
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void	*RpxWriteTrcTdrvOpeRegEnd( void )
{
void	*rc = NULL;
/*--------------------------------------------------------------------------------------------------*/
/*		数据采集参数条件处理																		*/
/*--------------------------------------------------------------------------------------------------*/
		if( TrcMngV.TrcOpeRegWrtCnt > 0 )
		{
			rc = RpiPcalDataTraceParameter( );
		}
/*--------------------------------------------------------------------------------------------------*/
/*		写入计算成功，采样间隔改变或表运转操作寄存器写入：表运转变量计算																	*/
/*--------------------------------------------------------------------------------------------------*/
		if( (TrcMngV.TdrvOpeRegWrtCnt > 0) && (rc == NULL) )
		{
			rc = RpiPcalTableDriveParameter( );
		}
/*--------------------------------------------------------------------------------------------------*/
/*		新写入标志清零            															*/
/*--------------------------------------------------------------------------------------------------*/
		TrcMngV.TrcOpeRegWrtCnt = 0;
		TrcMngV.TdrvOpeRegWrtCnt = 0;
/*--------------------------------------------------------------------------------------------------*/
		return( rc );

}


/****************************************************************************************************/
/* Function_Name: RpxWriteTdrvOpeRegister         */
/* Description  : 表运转操作寄存器写入处理
                  调用：需要时调用
                  输入：
                  输出：   */
/****************************************************************************************************/
LONG	RpxWriteTdrvOpeRegister( CFORDEF* pForDef, ULONG WrData, void* Hmsg )
{

/*--------------------------------------------------------------------------------------------------*/
/*		寄存器数据写入																		*/
/*--------------------------------------------------------------------------------------------------*/
		if( pForDef->Attr.IsLong )
		{
			*(ULONG*)(pForDef->VarAdr) = WrData;
		}
		else
		{
			*(USHORT*)(pForDef->VarAdr) = (USHORT)WrData;
		}
/*--------------------------------------------------------------------------------------------------*/
		TrcMngV.TdrvOpeRegWrtCnt++;  //表运转操作寄存器写入,则加1
		/*** 表运作操作的功能选择变量，有写入，则TrcOpeRegWrtCnt加1 ***/
		if( pForDef->VarAdr == (void*)&TrcReg.TblFuncSel ){ TrcMngV.TrcOpeRegWrtCnt++;}
/*--------------------------------------------------------------------------------------------------*/
		return( REGWRF_COMPLETE );
}



/**********************************************************************************************/
/* Function_Name: LpxResetDataTraceVarX         */
/* Description  : 数据追踪专用变量复位处理
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void	LpxResetDataTraceVarX( void )
{

		TrcVarX.dPosCmdSmp  = 0;
		TrcVarX.MotSpdSmp   = 0;
		TrcVarX.dPosRefSmp  = 0;
		return;
}




/**********************************************************************************************/
/* Function_Name: RpxStartDataTrace         */
/* Description  : 单次数据追踪启动处理
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
LONG	RpxStartDataTrace( USHORT mode )
{

/*--------------------------------------------------------------------------------------------------*/
/*		单次数据跟踪开始检查																		*/
    /*** 若跟踪命令不是连续跟踪，或者跟踪不在执行中 ***/
/*--------------------------------------------------------------------------------------------------*/
		if ( (TrcExeV.TrcCmd != TRCCMD_CONTTRACE) || (TrcExeV.OpmRun != TRUE) )
		{
			if( TrcExeV.TrcCmd != TRCCMD_NOCMD )
			{
				return( REGIF_FOPEERR1 );               // 则此时，若跟踪命令不为空，则报错。
			}
			else if( TblExeV.TblCmd != TBLCMD_NOCMD )
			{
				return( REGIF_FOPEERR1 );               // 则此时，若表运行命令不为空，则报错。
			}
			else if( TrcExeP.TrcPrmOk != TRUE )
			{
				return( REGIF_DAMTHERR2 );              // 则此时，参数计算未完成，则报错。
			}
		}
/*--------------------------------------------------------------------------------------------------*/
/*		单次追踪开始处理																	*/
/*--------------------------------------------------------------------------------------------------*/
		TrcReg.TrcState = 0;							/* 追踪执行状态重置					*/
		LpxResetDataTraceVarX( );						/* 数据跟踪专用变量复位处理					*/
		TrcExeP.TrcObj[0].TrcExe &= 0x0F;				/* 溯源CH0执行许可					*/
		TrcExeV.TrcCmd = mode;							/* 单次追踪执行指令						*/

		return( REGIF_COMPLETE );

}

/**********************************************************************************************/
/* Function_Name: RpxStartRingTrace         */
/* Description  : 连续数据追踪启动处理
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
LONG	RpxStartRingTrace( void )
{

/*--------------------------------------------------------------------------------------------------*/
/*		连续追踪开始检查																*/
/*--------------------------------------------------------------------------------------------------*/
		if( TrcExeV.TrcCmd != TRCCMD_NOCMD )
		{
			return( REGIF_FOPEERR1 );
		}
		else if( TblExeV.TblCmd != TBLCMD_NOCMD )
		{
			return( REGIF_FOPEERR1 );
		}
		else if( TrcExeP.TrcPrmOk != TRUE )
		{
			return( REGIF_DAMTHERR2 );
		}
/*--------------------------------------------------------------------------------------------------*/
/*		连续追踪开始处理																	*/
/*--------------------------------------------------------------------------------------------------*/
		TrcReg.TrcState = 0;							/* 追踪执行状态重置				*/
		TrcReg.RngTrcIdx = 0;							/* 连续追踪写入位置复位			*/
		TrcReg.RngTrcCnt = 0;							/* 连续追踪写入次数重置			*/
		LpxResetDataTraceVarX( );						/* 数据追踪专用变量复位处理		*/
		TrcExeP.TrcObj[0].TrcExe &= 0x0F;				/* 溯源CH0执行许可					*/
		TrcExeV.TrcCmd = TRCCMD_RINGTRACE;				/* 连续追踪执行指令					*/
		return( REGIF_COMPLETE );

}

volatile USHORT ReadNum = 0;
volatile USHORT UsbAddr = 0;

/**********************************************************************************************/
/* Function_Name: RpxReadTraceRegister         */
/* Description  : 追踪寄存器读取：读取的直接就是追踪缓存结构体数据
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
LONG	RpxReadTraceRegister( LONG RegNo, LONG Number, USHORT *RdBuf, HMSGIF Hmsg )
{
LONG	i;
USHORT	*SrcBuf;
LONG	TrcNum = TrcReg.AreaSize;
LONG	RegNox = RegNo - DTRCBUF_REGNO;

        //-----------------------------------------------------------------------------------------
        //		寄存器地址范围检查
        //-----------------------------------------------------------------------------------------
		if( RegNox >= TrcNum )
		{
			Hmsg->ErrRno = (USHORT)RegNo;				        // 异常寄存器编号
			return( REGIF_REGNOERR );					        // 寄存器编号异常(无REG编号)
		}
		if( (RegNox + Number) > TrcNum )
		{
			Hmsg->ErrRno = (USHORT)(RegNo - RegNox + TrcNum);	// 异常寄存器编号
			return( REGIF_REGNOERR );					        // 寄存器编号异常（超出REG范围）
		}

	    //-----------------------------------------------------------------------------------------
		//    寄存器数据读出
	    //-----------------------------------------------------------------------------------------
		SrcBuf = (USHORT*)(&Trcbuf) + RegNox;			        // 读取数据源源地址
		for( i = 0; i < Number; i++ )
		{
			RdBuf[2 * i ]       = (SrcBuf[i] >> 8);				// 寄存器数据读出
			RdBuf[2 * i + 1]    =  SrcBuf[i] & 0x00FF;          // 寄存器数据读出
		}
        //-----------------------------------------------------------------------------------------
		return( REGIF_COMPLETE );						// 寄存器数据读取完成

}





/**********************************************************************************************/
/* Function_Name: RpxWriteTraceRegister         */
/* Description  : 追踪寄存器相关写入：写入的直接就是追踪缓存结构体数据
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
LONG	RpxWriteTraceRegister( LONG RegNo, LONG Number, USHORT *WrBuf, HMSGIF Hmsg )
{
LONG	i;
USHORT	*DesBuf;
LONG	TrcNum = TrcReg.AreaSize;	/* <V120> */
LONG	RegNox = RegNo - DTRCBUF_REGNO;

/*--------------------------------------------------------------------------------------------------*/
/*		操作寄存器写入权取得          																*/
/*--------------------------------------------------------------------------------------------------*/
		if( RpxGetOpeRegWriteHandle( Hmsg ) != TRUE )
		{
			return( REGIF_FOPEERR1 );					/* 不可处理(其他信道操作模式占有中)		*/
		}
/*--------------------------------------------------------------------------------------------------*/
/*		写入寄存器数量检查 (写入范围是否有溢出)													*/
/*--------------------------------------------------------------------------------------------------*/
		if( RegNox >= TrcNum )
		{
			Hmsg->ErrRno = (USHORT)RegNo;				/* 异常寄存器编号						*/
			return( REGIF_REGNOERR );
		}
		if( (RegNox + Number) > TrcNum )
		{
			Hmsg->ErrRno = (USHORT)(RegNo - RegNox + TrcNum);	/* 异常寄存器编号				*/
			return( REGIF_REGNOERR );
		}
/*--------------------------------------------------------------------------------------------------*/
/*		寄存器写入																		            */
/*--------------------------------------------------------------------------------------------------*/
		DesBuf = (USHORT*)(&Trcbuf) + RegNox;			/* 写入源指针设定					*/
		for( i=0; i < Number; i++ )
		{
			DesBuf[i] = WrBuf[i];						/* 寄存器数据写入					*/
		}
/*--------------------------------------------------------------------------------------------------*/
/*		操作寄存器写入权释放																<V615>	*/
/*--------------------------------------------------------------------------------------------------*/
		RpxFreeOpeRegWriteHandleTrc( Hmsg ) ;
/*--------------------------------------------------------------------------------------------------*/
		return( REGIF_COMPLETE );						/* 寄存器数据写入完成				*/

}



/**********************************************************************************************/
/* Function_Name: LPX_DATATRACE         */
/* Description  : 数据跟踪执行宏定义
                  本ch通道，数据跟踪计算成功情况下（ch正确配置了数据跟踪），执行数据记录，否则不执行
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
//若增益不等于0，则跟踪数据乘以增益*/
//跟踪数据，先左移再右移。
//跟踪数据，限幅处理,限制的范围：short型：15bit有符号，long型：31bit有符号。
//若增益等于0，则跟踪数据不用乘增益
//跟踪数据，先左移再右移。完成结构体属性中的左右移位处理。不同于后面exe中的移位处理。
//BtvBit：比特(I/O)跟踪变量选择(mask)，即地址中的某位，取出数据后&；BtvAdr：监控的IO跟踪变量；两者相与，获取对应的监控位。
//I/O数据采集为真时，最高位置1，举例：USHORT型|0x8000
//I/O数据采集为假时，最高位清0，举例：USHORT型&~0x8000
//将数据缓存到对应的缓存区域。
#define	LPX_DATATRACE( ch, type )																\
		Tobjpx = &TrcExeP.TrcObj[ch];															\
		if( Tobjpx->TrcExe == 0x01 )															\
		{																						\
			if( Tobjpx->VxGain != 0 )															\
			{																					\
				Data = MlibMulgainNolim( *Tobjpx->VarAdr, Tobjpx->VxGain );						\
				Data = ( Data << Tobjpx->VxSftL) >> Tobjpx->VxSftR;								\
				Data = MlibLIMITUL( Data, TrcExeP.UpperLmt, TrcExeP.LowerLmt );					\
			}																					\
			else																				\
			{																					\
				Data = ((*Tobjpx->VarAdr) << Tobjpx->VxSftL) >> Tobjpx->VxSftR;					\
				Data = MlibLIMITUL( Data, TrcExeP.UpperLmt, TrcExeP.LowerLmt );					\
			}																					\
			if( Tobjpx->BtvAdr != NULL )														\
			{																					\
				if( (*Tobjpx->BtvAdr) & Tobjpx->BtvBit )										\
				{																				\
					Data = (Data | TrcExeP.TrcBitSet);											\
				}																				\
				else																			\
				{																				\
					Data = (Data & TrcExeP.TrcBitClr);											\
				}																				\
			}																					\
			((type *)Tobjpx->TrcBuf)[Idx] = (type)Data;											\
		}



/**********************************************************************************************/
/* Function_Name: LpxDataTraceProcedure         */
/* Description  : 触发下的数据跟踪执行
                  调用：需要时调用
                  输入：Idx：表示数据不断的刷新的次数变量
                  输出：   */
/**********************************************************************************************/



//#ifdef RunRAM
//#pragma CODE_SECTION(LpxDataTraceProcedure, ".TI.ramfunc");
//#endif

void	LpxDataTraceProcedure( LONG Idx )
{
LONG	Data;
TRCOBJ	*Tobjpx;

/*--------------------------------------------------------------------------------------------------*/
/*		Trace data																					*/
/*--------------------------------------------------------------------------------------------------*/
		if( TrcReg.DataSize <= 1 )
		{
			LPX_DATATRACE( 0, SHORT );							/* Data Trace CH0					*/
			LPX_DATATRACE( 1, SHORT );							/* Data Trace CH1					*/
			LPX_DATATRACE( 2, SHORT );							/* Data Trace CH2					*/
			LPX_DATATRACE( 3, SHORT );							/* Data Trace CH3					*/
			TrcExeV.TrgVar[0] = ((SHORT*)TrcExeP.TrgBufx)[Idx];	/* 更新第一触发通道数据				*/
			TrcExeV.MTrgVar[0] = ((SHORT*)TrcExeP.MTrgBufx)[Idx];/* 更新第二触发通道数据				*/
		}
/*--------------------------------------------------------------------------------------------------*/
/*		Long trace data																				*/
/*--------------------------------------------------------------------------------------------------*/
		else
		{
			LPX_DATATRACE( 0, LONG );							/* Data Trace CH0					*/
			LPX_DATATRACE( 1, LONG );							/* Data Trace CH1					*/
			LPX_DATATRACE( 2, LONG );							/* Data Trace CH2					*/
			LPX_DATATRACE( 3, LONG );							/* Data Trace CH3					*/
			TrcExeV.TrgVar[0] = ((LONG*)TrcExeP.TrgBufx)[Idx];	/* 更新第一触发通道数据				*/
			TrcExeV.MTrgVar[0] = ((LONG*)TrcExeP.MTrgBufx)[Idx];/* 更新第二触发通道数据				*/
		}
/*--------------------------------------------------------------------------------------------------*/
		return;
}



/**********************************************************************************************/
/* Function_Name: LpxDataTraceCheckTrigger1         */
/* Description  : 带触发器的数据跟踪功能：触发选择变量为第一触发源
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
//#ifdef RunRAM
//#pragma CODE_SECTION(LpxDataTraceCheckTrigger1, ".TI.ramfunc");
//#endif

LONG	LpxDataTraceCheckTrigger1( void )
{
LONG	Data0;
LONG	Data1;

/*--------------------------------------------------------------------------------------------------*/
/*		位触发检查    																		*/
/*--------------------------------------------------------------------------------------------------*/
		if( TrcExeP.TrgSel == 0x09 )
		{
	        /*** 异或找出改变的bit，并用TrcBitSet确认到唯一标志bit ***/
			Data0 = (TrcExeV.TrgVar[0] ^ TrcExeV.TrgVar[1]) & TrcExeP.TrcBitSet;
            /*--------------------------------------------------------------------------------------*/
			if( Data0 == 0 )								/* 位状态没有变化，直接返回触发无效			*/
			{
				return( FALSE );
			}
            /*--------------------------------------------------------------------------------------*/
			if( TrcExeP.TrgEdge & 0x01 )					/* 上升沿判断：变化情况下，当前的状态必然为高。若为高，则返回触发成功     			*/
			{
				if( TrcExeV.TrgVar[0] & TrcExeP.TrcBitSet )
				{
					return( TRUE );
				}
			}
            /*--------------------------------------------------------------------------------------*/
			if( TrcExeP.TrgEdge & 0x02 )					/* 下降沿判断：变化情况下，前一个的状态必然为高。若为高，则返回触发成功        		*/
			{
				if( TrcExeV.TrgVar[1] & TrcExeP.TrcBitSet )
				{
					return( TRUE );
				}
			}
		}
/*--------------------------------------------------------------------------------------------------*/
/*		数值水平触发检查： 0无触发；1:上升沿；2:下降沿；3:边沿变化；4:电平以上；5:电平以下					*/
/*--------------------------------------------------------------------------------------------------*/
		else if( TrcExeP.TrgSel != 0x00 )    // 触发通道非零，则必然有一个数值触发通道
		{
		    /*** 左移位：左边舍弃，右边补零。
		                 右移位：分两种：逻辑右移和算术右移。大部分编译器是算术右移，这里也是。
		                 逻辑右移：右边丢弃，左边补零。
		                 算术右移：右边丢弃，左边填充原符号位。
		                 这里左右移位处理后，实现了：仅仅取数据的低15bit有符号或低31bit有符号数。 ***/
			Data0 = (LONG)(TrcExeV.TrgVar[0] << TrcExeP.TrgVsft) >> TrcExeP.TrgVsft;  // 触发跟踪数据左移 LONG:1; SHORT:17
			Data1 = (LONG)(TrcExeV.TrgVar[1] << TrcExeP.TrgVsft) >> TrcExeP.TrgVsft;
            /*--------------------------------------------------------------------------------------*/
			if( TrcExeP.TrgEdge == 0x04 )					/* 等级触发：(以上) 					*/
			{
				if( Data0 >= TrcExeP.TrgLevel )
				{
					return( TRUE );
				}
			}
            /*--------------------------------------------------------------------------------------*/
			if( TrcExeP.TrgEdge == 0x05 )					/* 等级触发：(以下)					*/
			{
				if( Data0 <= TrcExeP.TrgLevel )
				{
					return( TRUE );
				}
			}
            /*--------------------------------------------------------------------------------------*/
            /* 为了同步实现触发方式3：边沿变化，采用与bit0、1的AND处理*/
            /*--------------------------------------------------------------------------------------*/
			if( TrcExeP.TrgEdge & 0x01 )					/* 上升沿				*/
			{
				if( (Data1 < TrcExeP.TrgLevel) && (Data0 >= TrcExeP.TrgLevel) )
				{
					return( TRUE );
				}
			}
            /*--------------------------------------------------------------------------------------*/
			if( TrcExeP.TrgEdge & 0x02 )					/* 下降沿				*/
			{
				if( (Data1 > TrcExeP.TrgLevel) && (Data0 <= TrcExeP.TrgLevel) )
				{
					return( TRUE );
				}
			}
		}
/*--------------------------------------------------------------------------------------------------*/
		return( FALSE );
}


/**********************************************************************************************/
/* Function_Name: LpxDataTraceCheckTrigger2         */
/* Description  : 带触发器的数据跟踪功能：触发选择变量为第二触发源
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/

//#ifdef RunRAM
//#pragma CODE_SECTION(LpxDataTraceCheckTrigger2, ".TI.ramfunc");
//#endif
LONG	LpxDataTraceCheckTrigger2( void )
{
LONG	Data0;
LONG	Data1;

/*--------------------------------------------------------------------------------------------------*/
/*		位触发检查																	*/
/*--------------------------------------------------------------------------------------------------*/
		if( TrcExeP.MTrgSel == 0x09 )
		{
		    /*异或找出改变的bit，并用TrcBitSet确认到唯一标志bit*/
			Data0 = (TrcExeV.MTrgVar[0] ^ TrcExeV.MTrgVar[1]) & TrcExeP.TrcBitSet;
		/*------------------------------------------------------------------------------------------*/
			/*** 位状态没有变化，直接返回触发无效 ***/
			if( Data0 == 0 )
			{
				return( FALSE );
			}
		/*------------------------------------------------------------------------------------------*/
	        /*** 上升沿判断：变化情况下，当前的状态必然为高。若为高，则返回触发成功 ***/
			if( TrcExeP.MTrgEdge & 0x01 )
			{
				if( TrcExeV.MTrgVar[0] & TrcExeP.TrcBitSet )
				{
					return( TRUE );
				}
			}
		/*------------------------------------------------------------------------------------------*/
	        /*** 下降沿判断：变化情况下，前一个的状态必然为高。若为高，则返回触发成功 ***/
			if( TrcExeP.MTrgEdge & 0x02 )
			{
				if( TrcExeV.MTrgVar[1] & TrcExeP.TrcBitSet )
				{
					return( TRUE );
				}
			}
		}
/*--------------------------------------------------------------------------------------------------*/
/*		数值水平触发检查： 0无触发；1:上升沿；2:下降沿；3:边沿变化；4:电平以上；5:电平以下				*/
/*--------------------------------------------------------------------------------------------------*/
		else if( TrcExeP.MTrgSel != 0x00 )    // 触发通道非零，则必然有一个数值触发通道
		{
		    /*** 左移位：左边舍弃，右边补零。
		                 右移位：分两种：逻辑右移和算术右移。大部分编译器是算术右移，这里也是。
		                 逻辑右移：右边丢弃，左边补零。
		                 算术右移：右边丢弃，左边填充原符号位。
		                 这里左右移位处理后，实现了：仅仅取数据的低15bit有符号或低31bit有符号数。 ***/
			Data0 = (LONG)(TrcExeV.MTrgVar[0] << TrcExeP.MTrgVsft) >> TrcExeP.MTrgVsft;  // 触发跟踪数据左移 LONG:1; SHORT:17
			Data1 = (LONG)(TrcExeV.MTrgVar[1] << TrcExeP.MTrgVsft) >> TrcExeP.MTrgVsft;
		/*------------------------------------------------------------------------------------------*/
			if( TrcExeP.MTrgEdge == 0x04 )					/* 等级触发：(以上)					*/
			{
				if( Data0 >= TrcExeP.MTrgLevel )
				{
					return( TRUE );
				}
			}
		/*------------------------------------------------------------------------------------------*/
			if( TrcExeP.MTrgEdge == 0x05 )					/* 等级触发：(以下) 					*/
			{
				if( Data0 <= TrcExeP.MTrgLevel )
				{
					return( TRUE );
				}
			}
		/*------------------------------------------------------------------------------------------*/
		/* 为了同步实现触发方式3：边沿变化，采用与bit0、1的AND处理*/
		/*------------------------------------------------------------------------------------------*/
			if( TrcExeP.MTrgEdge & 0x01 )					/* 上升沿					*/
			{
				if( (Data1 < TrcExeP.MTrgLevel) && (Data0 >= TrcExeP.MTrgLevel) )
				{
					return( TRUE );
				}
			}
		/*------------------------------------------------------------------------------------------*/
			if( TrcExeP.MTrgEdge & 0x02 )					/* 下降沿					*/
			{
				if( (Data1 > TrcExeP.MTrgLevel) && (Data0 <= TrcExeP.MTrgLevel) )
				{
					return( TRUE );
				}
			}
		}
/*--------------------------------------------------------------------------------------------------*/
		return( FALSE );

}



/**********************************************************************************************/
/* Function_Name: LpxDataTraceCheckTrigger         */
/* Description  : 数据采集触发检查处理
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
//#ifdef RunRAM
//#pragma CODE_SECTION(LpxDataTraceCheckTrigger, ".TI.ramfunc");
//#endif

LONG	LpxDataTraceCheckTrigger( void )
{
LONG	x,y;

/*--------------------------------------------------------------------------------------------------*/
/*		触发条件1																			        */
/*--------------------------------------------------------------------------------------------------*/
		if(TrcExeP.TrgSel == 0x00)
		{
			x = TRUE;
		}
		else
		{
			x = LpxDataTraceCheckTrigger1( );
		}
/*--------------------------------------------------------------------------------------------------*/
/*		触发条件2																			        */
/*--------------------------------------------------------------------------------------------------*/
		if(TrcExeP.MTrgSel == 0x00)
		{
			y = TRUE;
		}
		else
		{
			y = LpxDataTraceCheckTrigger2( );
		}
/*--------------------------------------------------------------------------------------------------*/
/*		多个触发条 ?检查    																		*/
/*--------------------------------------------------------------------------------------------------*/
		if(TrcReg.MTrgMode == 1)						/* AND 触发								    */
		{
			return( x & y );
		}
		/*------------------------------------------------------------------------------------------*/
		else if(TrcReg.MTrgMode == 2)					/* OR  触发									*/
		{
			return( x | y );
		}
		/*------------------------------------------------------------------------------------------*/
		else											/* 单一条件触发								*/
		{
			return( x );
		}
}


/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/
