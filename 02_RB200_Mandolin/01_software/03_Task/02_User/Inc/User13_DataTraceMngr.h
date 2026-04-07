/****************************************************************************************************/
/*																									*/
/*																									*/
/*		User13_DataTraceMngr.h :                          											*/
/*																									*/
/*																									*/
/****************************************************************************************************/
#ifndef __User13_DataTraceMngr_H__
#define __User13_DataTraceMngr_H__


/*--------------------------------------------------------------------------------------------------*/
/*		テーブル運転実行指令定義				Table operation execution command definition		        */
/*--------------------------------------------------------------------------------------------------*/
#define	TBLCMD_NOCMD		0x00		/* 没有指令													*/
#define	TBLCMD_TABLESTART	0x01		/* Table運転処理開始指令									        */
#define	TBLCMD_TABLEDRIVE	0x02		/* Table運転実行開始指令									        */
#define	TBLCMD_TBLDRV_END	0x03		/* Table運転実行正常終了									        */
#define	TBLCMD_TBLDRV_ERR	0x0E		/* Table運転実行異常終了									        */





/*--------------------------------------------------------------------------------------------------*/
typedef	struct
{
#ifdef CPU1
		USHORT	trace0[0x0800];
		USHORT	trace1[0x0800];
		USHORT	trace2[0x0800];
        USHORT	trace3[0x0800];
#endif

#ifdef CPU2
        USHORT  trace0[0x0800];
        USHORT  trace1[0x0800];
        USHORT  trace2[0x0800];
        USHORT  trace3[0x0800];
#endif

} TRCBUF;
extern	TRCBUF	Trcbuf;
/*--------------------------------------------------------------------------------------------------*/
/*		トレース実行制御用変数定義		Trace execution control for variable definition	            */
/*--------------------------------------------------------------------------------------------------*/
typedef	struct	{					/* 跟踪実行制御用変数定義									*/
		UCHAR	TrcCmd;					/* 跟踪执行指令0：停止；1：启动单发跟踪；2：启动循环实时跟踪；3：启动连续跟踪*/
		UCHAR	Opened;	 			/* 追踪功能已经开放											*/
		UCHAR	OpmRun;					/* 跟踪操作模式执行中(OpeMode制御用)						*/
		UCHAR	TrcStep;				/* 跟踪时序步骤												*/
		USHORT	TrcSamp;				/* トレースサンプリング					Trace sampling      */
		USHORT	TrcIndx;				/* トレースインデクス					Trace index 		*/
		LONG	TrgVar[2];				/* 跟踪触发变量(今回値,前回値)								*/
		LONG	MTrgVar[2];				/* 跟踪触发检查变量(今回値,前回値)多触发对应				*/
} TRCEXEV;
extern	TRCEXEV	TrcExeV;
/*--------------------------------------------------------------------------------------------------*/
typedef	struct	{
        DBYTEX	TrcMode;                /* 0x2100 : 高位:跟踪模式;低位 ǖ朗�     					*/
		USHORT	DataSize;               /* 0x2101 : 跟踪数据大小，1:16位数据，2:高精度32位数据		*/
		USHORT	AreaSize;               /* 0x2102 : 跟踪区域Size,仅初始化为3072						*/
		USHORT	SampIntv;               /* 0x2103 : 跟踪取样间隔设置值								*/
		USHORT	MaxAreaSize;            /* 0x2107 : 跟踪区域最大尺寸，仅初始化为sizeof(Trcbuf)/2=3072*/
		USHORT	TrcSel[4];              /* 0x2110 : 追踪对象选择，高8位:I/O对象，低8位:数据对象		*/
		USHORT	PtrgDnum;               /* 0x2200 : 预触发数据数，%									*/
		USHORT	TrgSel;                 /* 0x2201 : 触发类型bit1 触发数据通道选择0:无通道; 1~4数据通道；9:bit数据触发，触发通道由TrcReg.TrgLevel.Long设置。  bit1 0:无触发；1:上升沿；2:下降沿；3:边沿变化；4:电平以上；5:电平以下	*/
		DWORDX	TrgLevel;               /* 0x2202 : 触发值A											*/
		USHORT	TrgPoint;               /* 0x2204 : 触发点位置										*/
		USHORT	TrcState;               /* 0x2205 : 跟踪状态 0:;1:采集中，包括预采集;2:;3:采集结束	*/
        USHORT  InterEnc;
		USHORT  RngTrcIdx;              /* 0x2206 : 连续追踪写入位置								*/
		USHORT  RngTrcCnt;              /* 0x2207 : 连续追踪写入循环次数							*/
		USHORT	MTrgMode;               /* 0x2208 : 多触发模式 0:触发信号A；1：触发信号A AND B； 2：触发信号A OR B	*/
		USHORT	MTrgSel;                /* 0x2209 : 触发条件2										*/
		DWORDX	MTrgLevel;              /* 0x220A : 触发等级2										*/
		USHORT	TblMode;                /* 0x2300 : Table运转控制模式								*/
		USHORT	TblLimit;               /* 0x2301 : Table运转允许旋转量(移动量)圈数限制				*/
		USHORT	TblState;               /* 0x2302 : Table运转状态									*/
		USHORT	TblFuncSel;             /* 0x2303 : Table运转功能选择，低8位扭矩输入位置，bit8免调整无效，bit9电子齿轮无效，bit10位置指令滤波器无效	*//* <V120> */
} TRCREG;
extern TRCREG	TrcReg;					/* 跟踪控制数据寄存器									    */



/****************************************************************************************************/
/*																									*/
/*		データトレース実行用変数定義																        */
/*	Data trace execution for variable definition													*/
/****************************************************************************************************/
/*																									*/
/*	Data Trace / table operation run for variables, Round: DtrcMngr.c and ScanB: is managed (writing)*/
/*	 by DtrcExec.c, the other module, it is possible to see only.							      */
/*																									*/
/****************************************************************************************************/
/*--------------------------------------------------------------------------------------------------*/
/*		トレース対象定義		Traced definition										                */
/*--------------------------------------------------------------------------------------------------*/
typedef	struct	{						/* トレース対象定義						Traced definition   */
		UCHAR	TrcExe;					/* 跟踪执行控制标志(0鐨�:実行,その他:不実行)				*/
		UCHAR	VxSftL;					/* 数值跟踪变量左移位数，即地址取出的数左移后输出			*/
		UCHAR	VxSftR;					/* 数值跟踪变量右移位数，即地址取出的数右移后输出			*/
		UCHAR	BtvBit;					/* 比特(I/O)跟踪变量选择(mask)，即地址中的某位，取出数据后&	*/
		LONG	VxGain;					/* 数値トレース演算ゲイン	Numeric trace calculation gain	*/
		LONG	*VarAdr;				/* 数值跟踪变量地址，根据跟踪对象TrcReg.TrcSel低8位查表TrcVarTbl[]得到数据地址	*/
		UCHAR	*BtvAdr;				/* 比特(I/O)跟踪变量地址，根据跟踪对象TrcReg.TrcSel高8位查表TrcBitTbl[]得到数据地址									*/
		void	*TrcBuf;				/* 跟踪数据存储缓冲，根据采样数据个数对应Trcbuf的不同位置	*/
} TRCOBJ;
/*--------------------------------------------------------------------------------------------------*/
/*		トレース実行パラメータ定義			Trace execution parameter definitions                       */
/*--------------------------------------------------------------------------------------------------*/
typedef	struct	{						/* トレース実行パラメータ定義		Trace execution parameter definitions*/
		UCHAR	TrcPrmOk;				/* 跟踪参数计算完毕											*/
		UCHAR	TrgSel;					/* 跟踪触发第几通道选择。0:无通道; 1~4通道					    */
		UCHAR	TrgEdge;				/* 跟踪触发边缘指定											*/
		UCHAR	TrgVsft;				/* 触发跟踪数据左移 SHORT:1; LONG:17						    */
		UCHAR	MTrgSel;				/* トレーストリガ選択			(マルチトリガ対応)			        */
		                                /* Trace trigger selection  (Multi-trigger response)        */
		UCHAR	MTrgEdge;				/* トレーストリガエッジ指定		(マルチトリガ対応)			        */
		                                /* Trace trigger edge specification (Multi-trigger response)*/
		UCHAR	MTrgVsft;				/* トレーストリガデータシフト	(マルチトリガ対応)			        */
		                                /* Trace trigger data shift (Multi-trigger response)        */
		USHORT	TrcDnum;				/* 跟踪数据个数，3072/通道数/是否是LONG						*/
		USHORT	DataSampIntv;			/* 跟踪数据取样间隔实际使用值 <=64							*/
	/*----------------------------------------------------------------------------------------------*/
		LONG	UpperLmt;				/* 跟踪数据上限												*/
		LONG	LowerLmt;				/* 跟踪数据下限												*/
		ULONG	TrcBitSet;				/* I/O数据采集为真时，最高位置0，USHORT型|0x8000			*/
		ULONG	TrcBitClr;				/* I/O数据采集为假时，最高位清0，USHORT型&~0x8000			*/
		LONG	TrgLevel;				/* 触发数值													*/
		LONG	MTrgLevel;				/* トレーストリガレベル			(マルチトリガ対応)			*/
		                                /* Trace trigger level      ()                      */
		void	*TrgBufx;				/* 跟踪触发数据缓冲器,根据TrcReg.TrgSel的bit0选择第几通道	*/
		void	*MTrgBufx;				/* トレーストリガデータバッファ	(マルチトリガ対応)			*/
		                                /*Trace trigger data buffer ()                      */
		TRCOBJ	TrcObj[4];				/* 跟踪变量信息												*/
} TRCEXEP;

extern	TRCEXEP	TrcExeP;





/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/*		トレース専用変数定義				Trace only variable definition				                */
/*--------------------------------------------------------------------------------------------------*/
typedef	struct	{
		LONG	dPosCmdSmp;				/* サンプリング毎位置指令差分(指令速度演算用)				*/
		                                /* Sampling every position command difference (for command speed operation)*/
//		LONG	dMotPosSmp;				/* サンプリング毎モータ位置差分(モータ速度演算用)			*/
		LONG	MotSpdSmp;				/* サンプリング毎モータ速度積算(モータ速度演算用)			*/
		                                /* Sampling every motor speed calculation (for the motor speed operation)*/
		LONG	dPosRefSmp;				/* サンプリング毎位置指令差分(位置环前指令速度计算用)		*/
		                                /* Sampling every position command difference       */
		                               /*(for position 环前 command speed computation)       */
		                                /* Sampling every load speed integrated (for load speed operation)*/
} TRCVARX;
extern	TRCVARX	TrcVarX;				/* トレース専用変数(平均値,etc)		Trace-only variables*/


extern LONG	RpxStopDataTrace( void );
extern LONG	RpxSetDataTraceMode( USHORT mode );
extern LONG	RpxStartDataTrace( USHORT mode );
extern LONG	RpxStartRingTrace( void );
extern LONG	RpxWriteTraceRegister( LONG RegNo, LONG Number, USHORT *WrBuf, HMSGIF Hmsg );
extern LONG	RpxReadTraceRegister( LONG RegNo, LONG Number, USHORT *RdBuf, HMSGIF Hmsg );
extern void	RpxInitDtrcManager( void );
extern void	*RpiPcalDataTraceParameter( void );
extern void	LpxResetDataTraceVarX( void );
extern LONG	LpxDataTraceCheckTrigger( void );
extern void	LpxDataTraceProcedure( LONG Idx );
#endif
