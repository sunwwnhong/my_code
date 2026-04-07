
#ifndef SvOption_H
#define SvOption_H

typedef	struct	_MSGIF {
	USHORT  *CmdBuf;
	USHORT  *ResBuf;
	LONG  (*StxFunc)( UCHAR *, USHORT );
	void  (*ResFunc)( struct _MSGIF * );
	USHORT	RcvLen;
	USHORT	RcvBufSize;
	USHORT	SndBufSize;
	USHORT	FunSts;
	USHORT	FunExeIdx;
	USHORT	FnStsToOpi;
	USHORT	FunResHold;
	USHORT	ErrRno;
	USHORT	LstErrRno;
	USHORT	AccsLvl;
	USHORT	ComPortType;
	ULONG	ComTimeLong;

} MSGIF;
typedef	MSGIF*	HMSGIF;
/*--------------------------------------------------------------------------------------------------*/
typedef struct
{
	UCHAR	LedCode[5];
	UCHAR	LedBlnkSw[5];
} LEDDSP;
/*--------------------------------------------------------------------------------------------------*/
typedef	struct
{
	UINT	mode		:1;                              /* 按键Mode标志位                          */
	UINT	up			:1;                              /* 按键Up标志位                            */
    UINT	shup		:1;
	UINT	down		:1;                              /* 按键Down标志位                          */
    UINT	shdown		:1;
    UINT    shift       :1;                              /* 按键Shift标志位                         */
	UINT	set		    :1;                              /* 按键Set标志位                           */
	UINT	rst		    :1;                              /* 按键Rest标志位                          */
    UINT    data        :1;                              /* 按键数据标志位                           */
}	OPKEYFLG;
/*--------------------------------------------------------------------------------------------------*/
typedef	struct
{
	UINT	PrmEewrite	:1;                              /* 按键数据标志位                           */
	UINT	read		:1;
	UINT	write		:1;
	UINT	no_op		:1;                              /* 禁止操作状态显示                         */
	UINT	error		:1;                              /* 错误状态显示                            */
	UINT	done		:1;
	UINT	end			:1;
}	BLINKFLG;

/*--------------------------------------------------------------------------------------------------*/
/*		補助鐨勡の実行構造体																		*/
/*--------------------------------------------------------------------------------------------------*/
typedef struct
{
	struct {									/* 補助機能管理用(FunMngr)							*/
		UCHAR	Executing;						/* 正在执行标志										*/
		UCHAR	PrmInhibit;						/* 参数禁止写入Flag									*/
		USHORT	FuncIdx;						/* The management table index						*/
		LEDDSP	LedDspData;						/* LED显示用数据缓冲器								*/
		USHORT	RCode;							/* 执行辅助功能的return返回值						*/
	} Mngr;										/*													*/
/*--------------------------------------------------------------------------------------------------*/
	struct										/* 補助機能アプリ側で参照/操作できるメンバ			*/
	{
		HMSGIF	Hmsg;							/* 使用元识别handle									*/
		OPKEYFLG FKeyMk;						/* 按键MAKE(OFF->ON)标志							*/
		OPKEYFLG FKeyLvl;						/* 按键水平标志										*/
		USHORT	FMsgCmd;						/* Message Command									*/
		UCHAR	CmdCode;						/* 指令码											*/
		UCHAR	Spare00;						/* Spare											*/
	/*----------------------------------------------------------------------------------------------*/
		UCHAR	Refer;							/* 执行状况flag	 0:执行前，1:执行中，2:执行完		*/
		UCHAR	DPos;							/* 闪烁位数:个、十、百、千							*/
		UCHAR	LPos;							/* 闪烁行数											*/
		UCHAR	FKeepCmdCode;					/* 由辅助功能设置面板需长按标志，如JOG正反转，此时只要面板按键不都为0就可以一直保持，通信式时每次都会清，因此要一直写	*/
		BLINKFLG PnlBlinkKick;					/* 面板闪烁标志										*/
        BLINKFLG LcdBlinkKick;					/* LCD闪烁标志										*/
	/*----------------------------------------------------------------------------------------------*/
		UCHAR	State;							/* 运行状态											*/
		ULONG	LongTimer;						/* 補助機能実行処理時間計測用						*/
	}App;
} FUNEXE;


typedef	struct _MONDEF {
	UINT	IsLong     : 1;						/* 数据为16位或32位      							*/
	UINT	Base       : 2;						/* 表示数据类型(DEC/HEX/BIT)						*/
	UINT	Sign       : 1;						/* 表示有无符号(W_SIGN:有/NOSIGN:無)			    */
	UINT	Decimals   : 3;						/* 小数点位数(0-4)								    */
	UINT	ValClr     : 1;						/* モニタ変数クリア(DISABLE/ENABLE)					*/
	UINT	GType      : 2;						/* GTYPE_VAL(変量)/GTYPE_CONST(常量)				*/
	UINT	NoneDisp   : 1;						/* 无效时none显     								*/
	UINT	SpareBits  : 5;						/* 予備												*/
/*--------------------------------------------------------------------------------------------------*/
	UCHAR	ChkSpUse;							/* 専用使用(COMMON/ROTARY/LINEAR/etc)				*/
	UCHAR	AccessLevel;						/* 用户权限(USR1/USR2/etc)					        */
/*--------------------------------------------------------------------------------------------------*/
	ULONG	(*FuncPtr)( struct _MONDEF * );		/* モニタデータ演算関数							    */
/*--------------------------------------------------------------------------------------------------*/
	union	{									/* モニタ変数定義									*/
	ULONG	Ulong;								/* 定義用(変数初鐨劘は、最初のメンバが有効)			*/
	LONG	*Plong;								/* LONG変淑殑のポインタ								*/
	ULONG	*Pulong;							/* ULONG変淑殑のポインタ							*/
	SHORT	*Pshort;							/* SHORT変淑殑のポインタ							*/
	USHORT	*Pushort;							/* USHORT変淑殑のポインタ							*/
	} Var;										/* モニタ鐨匌へのポインタ							*/
/*--------------------------------------------------------------------------------------------------*/
	union	{									/* モニタ演算ゲイン定義								*/
	ULONG	Ulong;								/* 定義用(変数初鐨劘は、最初のメンバが有効)			*/
	LONG	*Plong;								/* LONGゲイ鐨勜のポインタ							*/
	ULONG	*Pulong;							/* ULONGゲイ鐨勜のポインタ							*/
	SHORT	Short[2];							/* SHORTゲイン : Var*Short[0]/Short[1]				*/
	USHORT	Ushort[2];							/* USHORTゲイン : Var*Ushort[0]/Ushort[1]			*/
	} Gain;										/* モニタョ殑ンへのポインタまたは定数				*/
} MONDEF;

/*--------------------------------------------------------------------------------------------------*/
/*		Alarm Table																					*/
/*--------------------------------------------------------------------------------------------------*/
typedef struct	{
		USHORT	AlmCode;						/* 当前警报代码(上电时从EEPROM读取10个)				*/
		UCHAR	AlmAttr;						/* 警报属性											*/
		UCHAR	StopMode;						/* 位1表示过载种类;位0警报时的停机方法,F表示G1警报根据Pn001.0设置,1表示G2报警	*/
		UCHAR	AlmCodeOut;						/* 警报代码IO输出信号								*/
		UCHAR	AlmLedOut;						/* 警报LED输出信号，需要开宏，没用					*/
		UCHAR	AlmAttrEx;						/* 警报扩展属性，MCCSW_SGDVM3专用					*/
} ALMDEF;
typedef  struct
{
	USHORT AlmId;								/*	 < 警报ID >									    */
	USHORT Spare;								/*	 < 予備(Alignment調整用) >						*/
	ALMDEF AlmDef;								/*	 < 警报定义,即AlmDefTbl[id] >					*/
	ULONG  TmStamp;  						    /*	 < 警报记录时间戳 >								*/
} ALMTBL;
/*--------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------*/
/*		ChkSpUse Bit Definition																		*/
/*--------------------------------------------------------------------------------------------------*/
#define	KPI_CHKSPUSE_COMMON		0x01	/* ChkSpUse Bit for Common									*/
#define	KPI_CHKSPUSE_ROTARY		0x02	/* ChkSpUse Bit for Roatry Motor							*/
#define	KPI_CHKSPUSE_LINEAR		0x04	/* ChkSpUse Bit for Linear Motor							*/
#define	KPI_CHKSPUSE_FENC		0x08	/* ChkSpUse Bit for FullClosedEncoder						*/
#define	KPI_CHKSPUSE_SAFETY		0x10	/* ChkSpUse Bit for SafetyOptionModule						*/
//#define	KPI_LCDOPEDSPSEL_SETUP	0x10/* ChkSpUse Bit for SetUpParameter Display					*/
//#define	KPI_LCDOPEDSPSEL_TUNING	0x20/* ChkSpUse Bit for TuningParameter Display					*/
#define	KPI_LCDOPEDSPSEL_SETUP	0x40	/* ChkSpUse Bit for SetUpParameter Display		用户用参数	*/
#define	KPI_LCDOPEDSPSEL_TUNING	0x80	/* ChkSpUse Bit for TuningParameter Display		调谐用参数	*/
/*--------------------------------------------------------------------------------------------------*/


extern MSGIF PopMsg; 
extern MSGIF UsbMsg;


#endif
