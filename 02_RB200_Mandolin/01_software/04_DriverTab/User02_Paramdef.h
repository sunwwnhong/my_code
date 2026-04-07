/****************************************************************************************************/
/*																									*/
/*																									*/
/*		User02_Paramdef.h : 参数定义头文件															*/
/*																									*/
/*																									*/
/****************************************************************************************************/
/*																									*/
/*																									*/
/*		1. 参数结构体定义																			*/
/*																									*/
/*		2. 参数设定结构体定义																		*/
/*																									*/
/*		3. 标准参数计算函数																			*/
/*																									*/
/*		4. 参数定义Extern声明																		*/
/*																									*/
/*		5. 参数管理表Extern声明																		*/
/*																									*/
/*																									*/
/*																									*/
/*																									*/
/*																									*/
/*																									*/
/************** Copyright (C) ××× Electric Corporation *******************************************/
/*																									*/
/*		2026.3/.17 : Made by Excel Macro															*/
/*																									*/
/*																									*/
/****************************************************************************************************/


#ifndef __User02_ParamDef_H__
#define __User02_ParamDef_H__



#define ARM_Version			3458

#include "Base_Def.h"





/****************************************************************************************************/
/*																									*/
/*		EEPROM Information Data																		*/
/*																									*/
/****************************************************************************************************/
/*--------------------------------------------------------------------------------------------------*/
/*		Eeprom Information Data Structure															*/
/*--------------------------------------------------------------------------------------------------*/
typedef struct	{
	USHORT	SysChkSum;							/* System Check Sum									*/
	USHORT	UsrChkSum;							/* User   Check Sum									*/
	USHORT	DefChkSum;							/* Default User Check Sum							*/
	USHORT	SvTypeId;							/* Servo Type ID									*/
	USHORT	YecFmtId;							/* Yec Format ID									*/
	USHORT	VenderId;							/* Vender ID										*/
} EEPINF;
/*--------------------------------------------------------------------------------------------------*/
/*		EEPROM Base Address and Size Definition														*/
/*--------------------------------------------------------------------------------------------------*/
#define EEPADR_HEADER		0x0000
#define EEPADR_SYSCHK		0x0000
#define EEPADR_USRCHK		0x0001
#define EEPADR_DEFCHK		0x0002
#define EEPADR_TYPEID		0x0003
#define EEPADR_YFMTID		0x0004
#define EEPADR_VNDRID		0x0005
/*--------------------------------------------------------------------------------------------------*/
#define EEPADR_PARAM		0x0006
#define EEPADR_BLANK		0x05FC
#define EEPADR_RSVD		0x0720
#define EEPADR_FENCECOMP		0x0726
#define EEPADR_ALMMON		0x07AA
#define EEPADR_TSTAMP		0x07C9
#define EEPADR_ALMTRC		0x07CB
#define EEPADR_ALMOLI		0x07EA
#define EEPADR_BOOTINF		0x07EB
#define EEPADR_EEPEND		0x07EF
/*--------------------------------------------------------------------------------------------------*/
#define EEPADR_SUMSTR		0x0000
#define EEPADR_SUMEND		0x071F
/*--------------------------------------------------------------------------------------------------*/
#define Param_HEADER		0x0006
#define Param_PARAM		0x05F6
#define Param_BLANK		0x0124
#define Param_RSVD		0x0006
#define Param_FENCECOMP		0x0084
#define Param_ALMMON		0x001F
#define Param_TSTAMP		0x0002
#define Param_ALMTRC		0x001F
#define Param_ALMOLI		0x0001
#define Param_BOOTINF		0x0005
#define Param_Sum		0x07F0
/*--------------------------------------------------------------------------------------------------*/



/****************************************************************************************************/
/*																									*/
/*		EXCEL表通用定义																				*/
/*																									*/
/****************************************************************************************************/
/*--------------------------------------------------------------------------------------------------*/
/*		表示時の底																					*/
/*--------------------------------------------------------------------------------------------------*/
#define DSPDEF_BASENBL			0				/* 属性：按位表示									*/
#define DSPDEF_BASEDEC			1				/* 属性：10进制表示									*/
#define DSPDEF_BASEHEX			2				/* 属性：16进制表示									*/
#define DSPDEF_BASEBIT			3				/* 属性：2进制表示									*/
/*--------------------------------------------------------------------------------------------------*/
/*		是否为有符号数																				*/
/*--------------------------------------------------------------------------------------------------*/
#define DSPDEF_W_SIGN			TRUE			/* 有符号											*/
#define DSPDEF_NOSIGN			FALSE			/* 无符号											*/
/*--------------------------------------------------------------------------------------------------*/
/*		访问等级(注意：0 は使用不可)																*/
/*--------------------------------------------------------------------------------------------------*/
#define ACCLVL_USER1			1				/* User1											*/
#define ACCLVL_USER2			2				/* User2											*/
#define ACCLVL_SYSTEM			3				/* System											*/
/*--------------------------------------------------------------------------------------------------*/



/****************************************************************************************************/
/*																									*/
/*		参数定义结构体定义																			*/
/*																									*/
/****************************************************************************************************/
/*--------------------------------------------------------------------------------------------------*/
/*		参数定义结构体																				*/
/*--------------------------------------------------------------------------------------------------*/
typedef struct	{
	struct	{
		UINT	IsLong     : 1;					/* 是否为Long型参数(TRUE/FALSE)						*/
		UINT	WordOrder  : 1;					/* 是否为LONG型参数的高位字(1/0)					*/
		UINT	AdjustPrm  : 1;					/* 调整参数?(ADJUST/NORMAL)							*/
		UINT	NeedReboot : 1;					/* 重新上电生效(NEEDBOOT/NON_BOOT)					*/
		UINT	Place      : 1;					/* 存储地方(BOTH_RAM_EEPROM/ONLY_RAM)				*/
		UINT	Base       : 2;					/* 显示进制(DEC/HEX/NBL)							*/
		UINT	Sign       : 1;					/* 有无符号表示(W_SIGN/NOSIGN)						*/
		UINT	Decimals   : 3;					/* 小数点以下位数(0-4)								*/
		UINT	ChgDpLsm   : 1;					/* 小数点位置变更(低速马达)							*/
		UINT	ReadOnly   : 1;					/* Read only(WRITABLE/READONLY)						*/
		UINT	AdjOpeIn   : 1;					/* 操作员输入调整(TRUE/FALSE)						*/
	/*----------------------------------------------------------------------------------------------*/
		UINT	SpareBits  : 2;					/* 预备												*/
		UINT	FormatRev  : 8;					/* FORMAT_ID改版履歴 1byteデータで使用しますので配置変更しないでください(??????????内16?23bitに定義されていること)	*/
		UINT	Unit       : 8;					/* 単位 (Reserved)									*/
	} Attr;										/* パラメータ属性									*/
/*--------------------------------------------------------------------------------------------------*/
	UCHAR	ChkSpUse;							/* 操作器参数显示选择(高：4bit)/专用使用确认(低：4bit) 	*/
	UCHAR	AccessLevel;						/* 访问等级(1:User1, 2:User2, 3:System)				*/
	USHORT	EepromAddr;							/* EEPROM地址ス + 属性(DefaultPrm無し)				*/
/*--------------------------------------------------------------------------------------------------*/
	LONG	(*FuncPtr)( ULONG Cmd, ULONG Data, ULONG Digit );	/* 处理函数指针    タ				*/
	USHORT	*RamPtr;							/* RAM存储地址指针									*/
	USHORT	LowerLimit;							/* 下限值											*/
	USHORT	UpperLimit;							/* 上限值											*/
} PRMDEF;
typedef const PRMDEF CPRMDEF;					/* const パラメータ定義								*/
/*--------------------------------------------------------------------------------------------------*/
/*		参数管理表结构																				*/
/*--------------------------------------------------------------------------------------------------*/
typedef struct	{
	USHORT	PnNo;								/* Pn番号											*/
	CPRMDEF	*PrmDefPtr;							/* 参数定义指针										*/
} PRMTBL;
typedef const PRMTBL CPRMTBL;					/* const 参数管理表									*/
/*--------------------------------------------------------------------------------------------------*/
/*		PRMDEF Version																				*/
/*--------------------------------------------------------------------------------------------------*/
#define PRMDEF_VERSION			0x0001			/* PRMDEF Version									*/
#define PRMTBL_VERSION			0x0001			/* PRMTBL Version									*/
/*--------------------------------------------------------------------------------------------------*/
/*		参数类别																					*/
/*--------------------------------------------------------------------------------------------------*/
#define PRMDEF_ADJUST			TRUE			/* 调整参数											*/
#define PRMDEF_NORMAL			FALSE			/* 常规参数											*/
/*--------------------------------------------------------------------------------------------------*/
/*		参数变更否是否需要重新上电?																	*/
/*--------------------------------------------------------------------------------------------------*/
#define PRMDEF_NEEDBOOT			TRUE			/* 需要重新上电										*/
#define PRMDEF_NON_BOOT			FALSE			/* 不需要重新上电									*/
/*--------------------------------------------------------------------------------------------------*/
/*		参数存储地址																				*/
/*--------------------------------------------------------------------------------------------------*/
#define PRMDEF_RAM_EEPROM		TRUE			/* RAM和EEPROM										*/
#define PRMDEF_ONLY_RAM			FALSE			/* 仅RAM											*/
/*--------------------------------------------------------------------------------------------------*/
/*		读写属性																					*/
/*--------------------------------------------------------------------------------------------------*/
#define PRMDEF_READONLY			TRUE			/* 只读												*/
#define PRMDEF_WRITABLE			FALSE			/* 可写												*/
/*--------------------------------------------------------------------------------------------------*/
/*		EEPROM地址属性定义(PRMDEF.EepromAddr)														*/
/*--------------------------------------------------------------------------------------------------*/
#define PRMDEF_EEPADRMSK		0x0FFF			/* Address mask										*/
#define PRMDEF_NODEFTPRM		0x8000			/* 没有定义的缺省参数								*/
/*--------------------------------------------------------------------------------------------------*/
/*		单位(Reserved)																				*/
/*--------------------------------------------------------------------------------------------------*/
#define UNIT_NONE				0x00			/* No Unit											*/
#define UNIT_TIME_SEC			0x01			/* time [sec]										*/
#define UNIT_TIME_MS			0x02			/* time [ms]										*/
#define UNIT_TIME_US			0x03			/* time [us]										*/
#define UNIT_SECINV				0x04			/* [1/s]											*/
#define UNIT_FREQ				0x05			/* Frequency [Hz]									*/
#define UNIT_PERCENT			0x06			/* percent (Numerical value 0-100)					*/
#define UNIT_ROT_SPEED			0x07			/* Speed [min-1]									*/
#define UNIT_LIN_SPEED			0x08			/* Speed [mm/s]										*/
#define UNIT_ROT_ACCEL			0x09			/* Acceleration [r/min/s]							*/
#define UNIT_LIN_ACCEL			0x0A			/* Acceleration [mm/s^2]							*/
#define UNIT_REFPULS			0x0B			/* length [Pulse]									*/
#define UNIT_ENCPULS			0x0C			/* length [Pulse]									*/
#define UNIT_PPR				0x0D			/* others [Pulse/rev]								*/
#define UNIT_REVOLUTION			0x0E			/* length revolution [rev]							*/
#define UNIT_REFPULS_SPD		0x0F			/* Pulse Speed [P/s]								*/
#define UNIT_ENCPULS_PITCH		0x10			/* length [Pulse/Pitch]								*/
#define UNIT_VOLT_PER_SPD		0x11			/* Voltage [V] per rate speed						*/
#define UNIT_VOLT_PER_TRQ		0x12			/* Voltage [V] per rate torque						*/
#define UNIT_VOLTAGE			0x13			/* Voltage [V]										*/
#define UNIT_CURRENT			0x14			/* Current [A]										*/
#define UNIT_RESIST				0x15			/* Resistance [Ohm]									*/
#define UNIT_WATTAGE			0x16			/* Wattage [W]										*/
/*--------------------------------------------------------------------------------------------------*/
/*		参数指令计算重新定义																		*/
/*--------------------------------------------------------------------------------------------------*/
#define PNCAL_PRMCAL			0x00			/* 参数计算(初始化和面板调节参数时)					*/
#define PNCAL_ADJINCDATA		0x01			/* Adjust Increment Data							*/
#define PNCAL_ADJDECDATA		0x02			/* Adjust Decrement Data							*/
#define PNCAL_PRMCALFROMREG		0x03			/* 参数计算(USB和485写入数据时)						*/
#define PNCAL_COMPRMEEPROM_WR	0x04			/* 参数Eeprom写入									*/
/*--------------------------------------------------------------------------------------------------*/



/****************************************************************************************************/
/*																									*/
/*		参数设定数据结构体定义																		*/
/*																									*/
/****************************************************************************************************/
typedef struct
{
	USHORT	b_prm0_0;			/* Pn000 : 功能选择应用开关0										*/
	USHORT	b_prm0_1;			/* Pn001 : 伺服使能开关												*/
	USHORT	motdir;				/* Pn002 : 电机旋转方向												*/
	USHORT	mondef;				/* Pn003 : 接通电源时的监视显示										*/
	USHORT	b_prm0_04;			/* Pn004 : 伺服OFF&Gr.1故障时停机方式								*/
	USHORT	b_prm0_05;			/* Pn005 : Gr.2故障时停机方式										*/
	USHORT	b_prm0_06;			/* Pn006 : 警告检出													*/
	USHORT	b_prm0_07;			/* Pn007 : 超程(OT)停机方式											*/
	USHORT	brktim;				/* Pn008 : 静止时,伺服Off时电磁制动器抱闸输出信号延时				*/
	USHORT	brkwai;				/* Pn009 : 旋转时,伺服off时电磁制动器抱闸输出信号延时				*/
	USHORT	brkspd;				/* Pn00A : 旋转时,电磁制动器抱闸解除时电机速度设定					*/
	USHORT	brkOnDly;			/* Pn00B : 电磁制动器抱闸解除延时									*/
	USHORT	b_prm0_0C;			/* Pn00C : 功能选择应用开关C										*/
	USHORT	b_prm0_0D;			/* Pn00D : 功能选择应用开关D										*/
	USHORT	b_prm0_0E;			/* Pn00E : 功能选择应用开关E										*/
	USHORT	b_prm0_F;			/* Pn00F : 功能选择应用开关F										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	PcmdFTime;			/* Pn011 : 外部脉冲信号滤波时间										*/
	USHORT	regres;				/* Pn012 : 外接制动电阻功率											*/
	USHORT	regresvalue;		/* Pn013 : 外接制动电阻阻值											*/
	USHORT	ServoOnDely;		/* Pn014 : 驱动器上电使能延时时间									*/
	USHORT	olwarlvl;			/* Pn015 : 电机过载警告值											*/
	USHORT	mtbastrq_drt;		/* Pn016 : 电机过载检出基极电流降额设定								*/
	USHORT	snglph_base_drt;	/* Pn017 : 选择单相电源输入时伺服单元过载检测电流降额百分比			*/
	USHORT	dbres;				/* Pn019 : DB电阻功率												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	fcplsel;			/* Pn020 : 全闭环功能开关1											*/
	USHORT	fcplsel2;			/* Pn021 : 全闭环功能开关2											*/
	USHORT	FensFiltTime;		/* Pn022 : 全闭环光学尺滤波时间										*/
	USHORT	fcplsnl;			/* Pn023 : 光学尺电子齿轮分子[N](低16位)							*/
	USHORT	fcplsnh;			/* Pn024 : 光学尺电子齿轮分子[N](高16位)							*/
	USHORT	fcplsml;			/* Pn025 : 光学尺电子齿轮分母[M](低16位)							*/
	USHORT	fcplsmh;			/* Pn026 : 光学尺电子齿轮分母[M](高16位)							*/
	USHORT	fpgoverlv2l;		/* Pn027 : 混合偏差过大设定值(低16位)								*/
	USHORT	fpgoverlv2h;		/* Pn028 : 混合偏差过大设定值(高16位)								*/
	USHORT	fpgoverclrl;		/* Pn029 : 混合偏差清零设定(L)										*/
	USHORT	fpgoverclrh;		/* Pn02A : 混合偏差清零设定(H)										*/
	USHORT	FenseSel;			/* Pn02B : 半闭环 & 全闭环切换开关									*/
	USHORT	Meth2ComV;			/* Pn02C : 全闭环方式2补偿偏差最小阈值								*/
	USHORT	FensSpdlv;			/* Pn02D : 全闭环方式2补偿速度最大阈值								*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	SoftLimitMaxl;		/* Pn030 : 绝对位置限制单圈最大值(低16位)							*/
	USHORT	SoftLimitMaxh;		/* Pn031 : 绝对位置限制单圈最大值(高16位)							*/
	USHORT	SoftLimitMMax;		/* Pn032 : 绝对位置限制多圈最大值									*/
	USHORT	SoftLimitMinl;		/* Pn033 : 绝对位置限制单圈最小值(低16位)							*/
	USHORT	SoftLimitMinh;		/* Pn034 : 绝对位置限制单圈最小值(高16位)							*/
	USHORT	SoftLimitMMin;		/* Pn035 : 绝对位置限制多圈最小值									*/
	USHORT	SoftLimitDelta;		/* Pn036 : 绝对位置软限位滞环										*/
	USHORT	offdec;				/* Pn039 : 伺服Off时减速时间										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	absEncuse;			/* Pn040 : 绝对值编码器的使用方法									*/
	USHORT	absEncalm;			/* Pn041 : 绝对值编码器电池欠压时的警报/警告选择					*/
	USHORT	UvModeSel;			/* Pn045 : 主回路（DC）欠电压时功能选择								*/
	USHORT	UvTrqLmt;			/* Pn046 : 主回路电压下降时转矩限制									*/
	USHORT	UvTrqLmtOffFil;		/* Pn047 : 主回路电压下降时转矩限制解除时间							*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	torqlimt;			/* Pn050 : 转矩限制方式选择											*/
	USHORT	tlmtf;				/* Pn051 : 内部正转转矩限制											*/
	USHORT	tlmtr;				/* Pn052 : 内部反转转矩限制											*/
	USHORT	emgtrq;				/* Pn053 : 紧急停止转矩												*/
	USHORT	outlmtf;			/* Pn054 : 外部正转转矩限制											*/
	USHORT	outlmtr;			/* Pn055 : 外部反转转矩限制											*/
	USHORT	RunOverTorq;		/* Pn056 : 飞车检测转矩阈值											*/
	USHORT	RunOverSpd;			/* Pn057 : 飞车检测速度阈值											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	pgrat;				/* Pn070 : 编码器分频脉冲数(4倍频前)								*/
	USHORT	SerEncSel;			/* Pn076 : 串行编码器单圈分辨率调整									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Address;			/* Pn080 : 485通信地址												*/
	USHORT	Mode;				/* Pn081 : 485通信格式												*/
	USHORT	EtherCatAddr;		/* Pn082 : EtherCAT 站点别名										*/
	USHORT	EtherCatType;		/* Pn083 : EtherCAT 主机类型										*/
	USHORT	SycnhErr;			/* Pn084 : EtherCAT 同步计数偏差上限								*/
	USHORT	ComSaveEeprom;		/* Pn085 : 通讯写入功能码是否存入Eeprom								*/
	USHORT	EtherCATConfig;		/* Pn086 : EtherCAT 配置											*/
	USHORT	addmapEn;			/* Pn087 : 485通讯寄存器地址映射开关								*/
	USHORT	addmap1s;			/* Pn088 : 1#寄存器映射源地址										*/
	USHORT	addmap1e;			/* Pn089 : 1#寄存器映射目的地址										*/
	USHORT	addmap2s;			/* Pn08A : 2#寄存器映射源地址										*/
	USHORT	addmap2e;			/* Pn08B : 2#寄存器映射目的地址										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	jrate;				/* Pn100 : 转动惯量比												*/
	USHORT	loophz;				/* Pn101 : 速度环比例增益											*/
	USHORT	pitime;				/* Pn102 : 速度环积分时间常数										*/
	USHORT	posgn;				/* Pn103 : 位置环比例增益											*/
	USHORT	trqfil11;			/* Pn104 : 第1第1转矩指令滤波器										*/
	USHORT	loophz2;			/* Pn105 : 第2速度环比例增益										*/
	USHORT	pitime2;			/* Pn106 : 第2速度环积分时间常数									*/
	USHORT	posgn2;				/* Pn107 : 第2位置环比例增益										*/
	USHORT	trqfil12;			/* Pn108 : 第1第2转矩滤指令滤波器									*/
	USHORT	tunmode;			/* Pn10A : 调整模式选择												*/
	USHORT	rigidity;			/* Pn10B : 刚性等级													*/
	USHORT	interpolation;		/* Pn10C : 插补模式选择												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	gnsw1;				/* Pn110 : 自动增益切换类方式选择开关								*/
	USHORT	gnswfil1;			/* Pn112 : 增益切换过渡时间1										*/
	USHORT	gnswfil2;			/* Pn113 : 增益切换过渡时间2										*/
	USHORT	gnswwait1;			/* Pn114 : 增益切换等待时间1										*/
	USHORT	gnswwait2;			/* Pn115 : 增益切换等待时间2										*/
	USHORT	LowSpdLevel;		/* Pn116 : 速度阈值增益切换值										*/
	USHORT	SpdSwitch;			/* Pn117 : 速度阈值参考												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	pitfil;				/* Pn120 : 位置积分时间常数											*/
	USHORT	ffgn;				/* Pn121 : 位置前馈增益												*/
	USHORT	fffil;				/* Pn122 : 位置前馈滤波时间											*/
	USHORT	sfgn;				/* Pn123 : 速度前馈增益												*/
	USHORT	sffil;				/* Pn124 : 速度前馈滤波时间											*/
	USHORT	fbfil;				/* Pn125 : 速度反馈滤波时间常数										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	gnmode;				/* Pn130 : 速度环的控制方法(PI/IP)									*/
	USHORT	mdswlv;				/* Pn132 : 速度环P/PI切换条件(转矩指令)								*/
	USHORT	mswrf;				/* Pn133 : 速度环P/PI切换条件(速度指令)								*/
	USHORT	mswacc;				/* Pn134 : 速度环P/PI切换条件(加速度)								*/
	USHORT	msplvl;				/* Pn135 : 速度环P/PI切换条件(位置偏差)								*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	mfvibsw;			/* Pn140 : A型抑振控制选择开关										*/
	USHORT	avibgn;				/* Pn141 : A型抑振增益修正											*/
	USHORT	avibfrq;			/* Pn142 : A型频抑振频率											*/
	USHORT	avibdamp;			/* Pn143 : A型抑振阻尼增益											*/
	USHORT	avibfil1;			/* Pn144 : A型抑振滤波时间常数1修									*/
	USHORT	avibfil2;			/* Pn145 : A型抑振滤波时间常数2修									*/
	USHORT	pstbfrq;			/* Pn146 : 第2中频抑振频率											*/
	USHORT	pstbdamp;			/* Pn147 : 第2中频抑振衰减增益										*/
	USHORT	Nntchfil1;			/* Pn14A : II型陷波滤波器1频率										*/
	USHORT	Nntchdamp1;			/* Pn14B : II型陷波滤波器1深度										*/
	USHORT	Nntchfil2;			/* Pn14C : II型陷波滤波器2频率										*/
	USHORT	Nntchdamp2;			/* Pn14D : II型陷波滤波器2深度										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	tfuncsw;			/* Pn150 : 转矩类开关												*/
	USHORT	anotchsw;			/* Pn151 : 陷波滤波器调整开关										*/
	USHORT	vibdetlvl;			/* Pn152 : 自动陷波共振检测灵敏度									*/
	USHORT	ntchfil1;			/* Pn153 : 陷波滤波器1频率											*/
	USHORT	ntchq1;				/* Pn154 : 陷波滤波器1Q值											*/
	USHORT	ntchdamp1;			/* Pn155 : 陷波滤波器1深度											*/
	USHORT	ntchfil2;			/* Pn156 : 陷波频滤波2器率											*/
	USHORT	ntchq2;				/* Pn157 : 陷波滤波器2Q值											*/
	USHORT	ntchdamp2;			/* Pn158 : 陷波滤波器2深度											*/
	USHORT	ntchfil3;			/* Pn159 : 陷波频滤波3器率											*/
	USHORT	ntchq3;				/* Pn15A : 陷波滤波器3Q值											*/
	USHORT	ntchdamp3;			/* Pn15B : 陷波滤波器3深度											*/
	USHORT	ntchfil4;			/* Pn15C : 陷波频滤波4器率											*/
	USHORT	ntchq4;				/* Pn15D : 陷波滤波器4Q值											*/
	USHORT	ntchdamp4;			/* Pn15E : 陷波滤波器4深度											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	dobgn;				/* Pn161 : 摩擦补偿增益												*/
	USHORT	dobgn2;				/* Pn162 : 第2摩擦补偿增益											*/
	USHORT	dtrqgn;				/* Pn163 : 摩擦补偿系数												*/
	USHORT	dlpfil;				/* Pn164 : 摩擦补偿频率修正											*/
	USHORT	dobjgn;				/* Pn165 : 摩擦补偿增益修正											*/
	USHORT	evoben;				/* Pn166 : 速度观测器开关											*/
	USHORT	evobgn;				/* Pn167 : 速度观测器增益											*/
	USHORT	evobjgn;			/* Pn168 : 速度观测器惯量修正值										*/
	USHORT	evoblpf;			/* Pn169 : 速度观测器滤波时间修正值									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	fricmaxspd;			/* Pn170 : 摩擦转矩补偿截止速度										*/
	USHORT	friccoefpos;		/* Pn171 : 摩擦转矩正向补偿系数										*/
	USHORT	friccoefneg;		/* Pn172 : 摩擦转矩反向补偿系数										*/
	USHORT	DatLevel;			/* Pn175 : 免调整类控制开关											*/
	USHORT	TunLessGain;		/* Pn17A : 免调整扰动观测器增益										*/
	USHORT	TunLessStiff;		/* Pn17B : 免调整惯量修正系数										*/
	USHORT	TunLessTrqLpf;		/* Pn17C : 免调整扰动转矩低通滤波器时间常数							*/
	USHORT	TunLessVfbLpf;		/* Pn17D : 免调整速度FB低通滤波器时间常数							*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	vibsel;				/* Pn185 : 振动检测选择												*/
	USHORT	vibsens;			/* Pn186 : 振动检测灵敏度											*/
	USHORT	vibnorm;			/* Pn187 : 振动检测值												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	ovserrdetlvl;		/* Pn192 : 高级调谐过程中位置超调检出灵敏度(相对定位完成)			*/
	USHORT	adatgmax;			/* Pn193 : 探索最大增益时最大增益设置值								*/
	USHORT	gcomptrq;			/* Pn195 : 重力补偿值												*/
	USHORT	pqfriqcomptrq;		/* Pn196 : 正向库伦摩擦补偿值										*/
	USHORT	nqfriqcomptrq;		/* Pn197 : 负向库伦摩擦补偿值										*/
	USHORT	vfrigcomptrq;		/* Pn198 : 粘性摩擦补偿值											*/
	USHORT	spdhys;				/* Pn199 : 补偿滞环速度												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	prstsw;				/* Pn200 : 位置指令源选择											*/
	USHORT	PulseType;			/* Pn201 : 外部脉冲输入类型											*/
	USHORT	posctrl;			/* Pn202 : 位置控制开关												*/
	USHORT	MulFrq;				/* Pn203 : 指令脉冲输入倍率											*/
	USHORT	ratb2l;				/* Pn204 : 电子齿轮比分子(低16位)									*/
	USHORT	ratb2h;				/* Pn205 : 电子齿轮比分子(高16位)									*/
	USHORT	rata2l;				/* Pn206 : 电子齿轮比分母(低16位)									*/
	USHORT	rata2h;				/* Pn207 : 电子齿轮比分母(高16位)									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	expbias1;			/* Pn210 : 位置指令加减速滤波器偏置									*/
	USHORT	expfil;				/* Pn211 : 位置指令低通滤波时间常数									*/
	USHORT	mafil;				/* Pn212 : 位置指令滑动平均滤波时间									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	cmctrlexsw;			/* Pn220 : 齿隙补偿控制开关											*/
	USHORT	blcm2l;				/* Pn221 : 齿隙补偿量(低16位)										*/
	USHORT	blcm2h;				/* Pn222 : 齿隙补偿量(高16位)										*/
	USHORT	blfiltime;			/* Pn223 : 齿隙补偿时间常数											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	mdlsw_1;			/* Pn230 : 低频振动抑制选择											*/
	USHORT	mdlsw_2;			/* Pn231 : 低频振动抑制功能自动调整选择								*/
	USHORT	remdetw;			/* Pn232 : 低频振动检出灵敏度(相对定位完成)							*/
	USHORT	mdlantfrq;			/* Pn233 : 低频振动抑制1频率A										*/
	USHORT	mdlresfrq;			/* Pn234 : 低频振动抑制1频率B										*/
	USHORT	ff_frq;				/* Pn235 : 低频振动抑制2频率										*/
	USHORT	ff_fil;				/* Pn236 : 低频振动抑制2补正										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	mdlsw;				/* Pn240 : 模型追踪控制选择											*/
	USHORT	mdlgn;				/* Pn241 : 模型追踪控制增益											*/
	USHORT	mdlzeta;			/* Pn242 : 模型追踪控制增益补正										*/
	USHORT	mdlvff;				/* Pn243 : 模型追踪控制速度前馈增益									*/
	USHORT	mdlptff;			/* Pn244 : 模型追踪控制偏置(正转方向)								*/
	USHORT	mdlntff;			/* Pn245 : 模型追踪控制偏置(反转方向)								*/
	USHORT	mdlgn2;				/* Pn246 : 第2模型追踪控制增益										*/
	USHORT	mdlzeta2;			/* Pn247 : 第2模型追踪控制增益补正									*/
	USHORT	mfctype;			/* Pn248 : 控制类开关												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	nearlv2l;			/* Pn260 : NEAR信号宽度(低16位)										*/
	USHORT	nearlv2h;			/* Pn261 : NEAR信号宽度(高16位)										*/
	USHORT	coinlv2l;			/* Pn262 : 位置到达范围(低16位)										*/
	USHORT	coinlv2h;			/* Pn263 : 位置到达范围(高16位)										*/
	USHORT	overlv2l;			/* Pn264 : 位置偏差最大容忍值(低16位)								*/
	USHORT	overlv2h;			/* Pn265 : 位置偏差最大容忍值(高16位)								*/
	USHORT	overwrnlv;			/* Pn266 : 位置偏差过大警告设定										*/
	USHORT	svonoverlv2l;		/* Pn267 : 伺服ON时位置偏差过大警报阀值								*/
	USHORT	svonoverlv2h;		/* Pn268 : 伺服ON时位置偏差过大警报阀值(高16位)						*/
	USHORT	svonoverwrnlv;		/* Pn269 : 伺服ON时位置偏差过大警告阀值								*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	svonspdlmtlv;		/* Pn270 : 伺服ON时速度限制值										*/
	USHORT	PulseSel;			/* Pn271 : 脉冲倍率选择开关											*/
	USHORT	prstsw_1;			/* Pn272 : 滞留脉冲清零模式											*/
	USHORT	prstsw_2;			/* Pn273 : 位置偏差清除方式选择										*/
	USHORT	cmfilsw_3;			/* Pn274 : 定位完成信号(/Coin)输出时序								*/
	USHORT	revlimit;			/* Pn276 : 单向旋转多圈上限值										*/
	USHORT	revovDir;			/* Pn277 : 旋转圈数上限开启方向										*/
	USHORT	srevlimitL;			/* Pn278 : 单向旋转单圈上限值L										*/
	USHORT	srevlimitH;			/* Pn279 : 单向旋转单圈上限值H										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	orgmode;			/* Pn290 : 原点回归模式设定											*/
	USHORT	orgspdhight;		/* Pn291 : 原点回归高速速度											*/
	USHORT	orgspdlow;			/* Pn292 : 原点回归低速速度											*/
	USHORT	orgdecacc;			/* Pn293 : 原点回归加减速时间										*/
	USHORT	orgoffsetL;			/* Pn294 : 原点位置偏置L											*/
	USHORT	orgoffsetH;			/* Pn295 : 原点位置偏置H											*/
	USHORT	orgMpos;			/* Pn296 : 绝对位置零点多圈值										*/
	USHORT	orgSposL;			/* Pn297 : 绝对位置零点单圈值L										*/
	USHORT	orgSposH;			/* Pn298 : 绝对位置零点单圈值H 										*/
	USHORT	orgovtime;			/* Pn299 : 原点回归超时设定											*/
	USHORT	orgstatus;			/* Pn29A : 原点回归多圈回归状态										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	spdSource;			/* Pn300 : 速度指令源												*/
	USHORT	spdcmd;				/* Pn301 : 速度指令方向												*/
	USHORT	srfil;				/* Pn302 : 速度指令低通滤波时间										*/
	USHORT	speed0;				/* Pn304 : 内部速度0												*/
	USHORT	speed1;				/* Pn305 : 内部速度1												*/
	USHORT	speed2;				/* Pn306 : 内部速度2												*/
	USHORT	speed3;				/* Pn307 : 内部速度3												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	sfsacc;				/* Pn310 : 速度指令梯形加速时间										*/
	USHORT	sfsdec;				/* Pn311 : 速度指令梯形减速时间										*/
	USHORT	sfsts;				/* Pn312 : 速度指令梯形减速时间										*/
	USHORT	clamp;				/* Pn313 : 零速箝位速度阀值											*/
	USHORT	clampMaxSpd;		/* Pn314 : 零速箝位补偿最大速度										*/
	USHORT	tgonlv;				/* Pn317 : 转动判断阈值												*/
	USHORT	MaxSpd;				/* Pn318 : 电机最高速度												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	vcmplv;				/* Pn320 : 速度一致范围												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	b_prm400;			/* Pn400 : 转矩控制开关1											*/
	USHORT	secfil;				/* Pn401 : 转矩指令2阶低通滤波器截止频率							*/
	USHORT	secq;				/* Pn402 : 转矩指令2阶低通滤波器Q値									*/
	USHORT	trqcmddirtype;		/* Pn403 : 转矩控制开关2											*/
	USHORT	treffil;			/* Pn404 : 转矩指令滤波时间											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	intrqcmd1;			/* Pn410 : 内部转矩指令1											*/
	USHORT	intrqcmd2;			/* Pn411 : 内部转矩指令2											*/
	USHORT	intrqcmd3;			/* Pn412 : 内部转矩指令3											*/
	USHORT	intrqcmd4;			/* Pn413 : 内部转矩指令4											*/
	USHORT	ntqspdlimt1;		/* Pn415 : 转矩控制模式时内部速度限制								*/
	USHORT	ntqspdlimt2;		/* Pn416 : 转矩控制模式时内部速度限制								*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	torqcmd1;			/* Pn420 : 转矩到达设定值											*/
	USHORT	torqcmd2;			/* Pn421 : 转矩到达设定值											*/
	USHORT	torqcmdtimewindow;	/* Pn422 : 转矩到达时间窗口											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	trqcmddirtype1;		/* Pn430 : 转矩控制开关1											*/
	USHORT	monitortime;		/* Pn435 : Un00A监控滤波时间										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	jogspd;				/* Pn500 : 点动速度													*/
	USHORT	pjogsw;				/* Pn502 : 程序JOG运行模式											*/
	USHORT	pjogdistl;			/* Pn503 : 程序JOG移动距离											*/
	USHORT	pjogdisth;			/* Pn504 : 程序JOG移动距离(高16位)									*/
	USHORT	pjogacctm;			/* Pn505 : 程序JOG加减速时间										*/
	USHORT	pjogwaittm;			/* Pn506 : 程序JOG等待时间											*/
	USHORT	pjognum;			/* Pn507 : 程序JOG移动次数											*/
	USHORT	pjogrotspd;			/* Pn508 : 程序JOG移动速度											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	CurIntrig;			/* Pn510 : 电流内部信号触发											*/
	USHORT	CurType;			/* Pn511 : 电流内部信号类型											*/
	USHORT	CurAmp;				/* Pn512 : 电流给定幅值												*/
	USHORT	CurFreq;			/* Pn513 : 电流给定频率												*/
	USHORT	CurOffSet;			/* Pn514 : 电流给定偏移量											*/
	USHORT	SpdIntrig;			/* Pn515 : 速度内部信号触发											*/
	USHORT	SpdType;			/* Pn516 : 速度内部信号类型											*/
	USHORT	SpdAmp;				/* Pn517 : 速度给定幅值												*/
	USHORT	SpdFreq;			/* Pn518 : 速度给定频率												*/
	USHORT	SpdOffSet;			/* Pn519 : 速度给定偏移量											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	CurLimtHard;		/* Pn520 : 堵转电流硬保护设定										*/
	USHORT	LimtTHard;			/* Pn521 : 堵转硬保护时间设定										*/
	USHORT	SpdLimtHard;		/* Pn522 : 堵转硬保护转速设定										*/
	USHORT	CurLimtSoft;		/* Pn523 : 堵转电流软保护设定										*/
	USHORT	LimtTSoft;			/* Pn524 : 堵转软保护时间设定										*/
	USHORT	SpdLimtSoft;		/* Pn525 : 堵转软保护转速设定										*/
	USHORT	StallEn;			/* Pn526 : 堵转保护开启												*/
	USHORT	Pn527;				/* Pn527 : 预留参数7												*/
	USHORT	Pn528;				/* Pn528 : 预留参数8												*/
	USHORT	Pn529;				/* Pn529 : 预留参数9												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Pn530;				/* Pn530 : 预留参数10												*/
	USHORT	Pn531;				/* Pn531 : 预留参数11												*/
	USHORT	Pn532;				/* Pn532 : 预留参数12												*/
	USHORT	Pn533;				/* Pn533 : 预留参数13												*/
	USHORT	Pn534;				/* Pn534 : 预留参数14												*/
	USHORT	Pn535;				/* Pn535 : 预留参数15												*/
	USHORT	Pn536;				/* Pn536 : 预留参数16												*/
	USHORT	Pn537;				/* Pn537 : 预留参数17												*/
	USHORT	Pn538;				/* Pn538 : 预留参数18												*/
	USHORT	Pn539;				/* Pn539 : 预留参数19												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Pn540;				/* Pn540 : 预留参数20												*/
	USHORT	Pn541;				/* Pn541 : 预留参数21												*/
	USHORT	Pn542;				/* Pn542 : 预留参数22												*/
	USHORT	Pn543;				/* Pn543 : 预留参数23												*/
	USHORT	Pn544;				/* Pn544 : 预留参数24												*/
	USHORT	Pn545;				/* Pn545 : 预留参数25												*/
	USHORT	Pn546;				/* Pn546 : 预留参数26												*/
	USHORT	Pn547;				/* Pn547 : 预留参数27												*/
	USHORT	Pn548;				/* Pn548 : 预留参数28												*/
	USHORT	Pn549;				/* Pn549 : 预留参数29												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Pn550;				/* Pn550 : 预留参数30												*/
	USHORT	Pn551;				/* Pn551 : 预留参数31												*/
	USHORT	Pn552;				/* Pn552 : 预留参数32												*/
	USHORT	Pn553;				/* Pn553 : 预留参数33												*/
	USHORT	Pn554;				/* Pn554 : 预留参数34												*/
	USHORT	Pn555;				/* Pn555 : 预留参数35												*/
	USHORT	Pn556;				/* Pn556 : 预留参数36												*/
	USHORT	Pn557;				/* Pn557 : 预留参数37												*/
	USHORT	Pn558;				/* Pn558 : 预留参数38												*/
	USHORT	Pn559;				/* Pn559 : 预留参数39												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	MIT_Volmax;			/* Pn560 : MIT_Volmax												*/
	USHORT	MIT_Volmin;			/* Pn561 : MIT_Volmin												*/
	USHORT	CANTimeOut;			/* Pn562 : CAN超时时间												*/
	USHORT	MIT_Curmax;			/* Pn563 : MIT_Curmax												*/
	USHORT	MIT_Curmin;			/* Pn564 : MIT_Curmin												*/
	USHORT	AccRads;			/* Pn565 : 加速度设定												*/
	USHORT	KtSetEn;			/* Pn566 : Kt转矩系数调整使能										*/
	USHORT	KtSet;				/* Pn567 : Kt转矩系数修正值											*/
	USHORT	KpPos;				/* Pn568 : 位置环Kp													*/
	USHORT	KdPos;				/* Pn569 : 位置环Kd													*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	KpSpd;				/* Pn570 : 速度环Kp													*/
	USHORT	KiSpd;				/* Pn571 : 速度环Ki													*/
	USHORT	KpCur;				/* Pn572 : 电流环Kp													*/
	USHORT	KiCur;				/* Pn573 : 电流环Ki													*/
	USHORT	MIT_KpMax;			/* Pn574 : MIT_KpMax												*/
	USHORT	MIT_KpMin;			/* Pn575 : MIT_KpMin												*/
	USHORT	MIT_KdMax;			/* Pn576 : MIT_KdMax												*/
	USHORT	MIT_KdMin;			/* Pn577 : MIT_KdMin												*/
	USHORT	MIT_Trefmax;		/* Pn578 : MIT_Trefmax												*/
	USHORT	MIT_Trefmin;		/* Pn579 : MIT_Trefmin												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	MIT_Posmax;			/* Pn580 : MIT_Posmax												*/
	USHORT	MIT_Posmin;			/* Pn581 : MIT_Posmin												*/
	USHORT	MIT_Spdmax;			/* Pn582 : MIT_Spdmax												*/
	USHORT	MIT_Spdmin;			/* Pn583 : MIT_Spdmin												*/
	USHORT	PosAOffSetL;		/* Pn584 : 电机编码器单圈调零补偿L									*/
	USHORT	PosAOffSetH;		/* Pn585 : 电机编码器单圈调零补偿H									*/
	USHORT	CANMIT;				/* Pn586 : CAN协议选择												*/
	USHORT	MIT_Trq;			/* Pn587 : MIT转矩前馈												*/
	USHORT	MIT_Sitam;			/* Pn588 : MIT给定角度												*/
	USHORT	MIT_WmRef;			/* Pn589 : MIT给定角速度											*/
	USHORT	MIT_PosFil;			/* Pn58A : MIT位置输出滤波时间常数									*/
	USHORT	MIT_Tref;			/* Pn58B : MIT转矩指令滤波时间常数									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	MIT_Kp;				/* Pn590 : MIT Kp系数												*/
	USHORT	MIT_Kd;				/* Pn591 : MIT Kd系数												*/
	USHORT	MIT_RateA;			/* Pn592 : 减速机分子												*/
	USHORT	MIT_RateB;			/* Pn593 : 减速机分母												*/
	USHORT	MutiBOffSet;		/* Pn594 : 负载编码器多圈调零补偿									*/
	USHORT	PosBOffSetL;		/* Pn595 : 负载编码器单圈调零补偿L									*/
	USHORT	PosBOffSetH;		/* Pn596 : 负载编码器单圈调零补偿H									*/
	USHORT	Pn597;				/* Pn597 : ICHAUS上电故障开启										*/
	USHORT	EncDelay;			/* Pn598 : 编码器上电检测延时时间									*/
	USHORT	Pn599;				/* Pn599 : 负载编码器单圈线性位置补偿方案							*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	XFilTime;			/* Pn600 : 开关量输入信号X滤波时间									*/
	USHORT	insel1;				/* Pn601 : 开关量1输入配置											*/
	USHORT	insel2;				/* Pn602 : 开关量2输入配置											*/
	USHORT	insel3;				/* Pn603 : 开关量3输入配置											*/
	USHORT	insel4;				/* Pn604 : 开关量4输入配置											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	outsel1;			/* Pn611 : 开关量1输出配置											*/
	USHORT	outsel2;			/* Pn612 : 开关量2输出配置											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	AI1treffil;			/* Pn620 : 模拟量AI1低通滤波时间									*/
	USHORT	AI2treffil;			/* Pn621 : 模拟量AI2低通滤波时间									*/
	USHORT	AI1Offset;			/* Pn622 : 模拟量AI1硬件漂移矫正									*/
	USHORT	AI2Offset;			/* Pn623 : 模拟量AI2硬件漂移矫正									*/
	USHORT	AI1Gain;			/* Pn624 : 模拟量AI1增益											*/
	USHORT	AI2Gain;			/* Pn625 : 模拟量AI2增益											*/
	USHORT	AI1Zero;			/* Pn626 : 模拟量AI1零点阈值										*/
	USHORT	AI2Zero;			/* Pn627 : 模拟量AI2零点阈值										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	VirDI;				/* Pn630 : 虚拟输入端子(X)状态给定									*/
	USHORT	VirDO;				/* Pn631 : 虚拟输出端子(Y)状态给定									*/
	USHORT	Trobe1Filtime;		/* Pn632 : EtherCat探针1(X5)滤波时间								*/
	USHORT	Trobe2Filtime;		/* Pn633 : EtherCat探针2(X6)滤波时间								*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	AATDist;			/* Pn702 : 惯量辨识可动范围											*/
	USHORT	PnB24;				/* Pn705 : 惯量辨识初始值											*/
	USHORT	JstVibValve;		/* Pn706 : 惯量辨识中振动检出水平(旋转)								*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	EstimateTime;		/* Pn711 : 在线参数辨识时间											*/
	USHORT	EstimateSpd;		/* Pn712 : 在线参数辨识速度阈值										*/
	USHORT	EstimateGain;		/* Pn713 : 在线参数辨识收敛增益										*/
	USHORT	TlObssw;			/* Pn715 : 负载转矩观测器开关										*/
	USHORT	TlObsIntero;		/* Pn716 : 负载转矩观测器惯量比										*/
	USHORT	TlObsfriction;		/* Pn717 : 负载转矩观测器粘滞摩擦系数								*/
	USHORT	TlObsGain;			/* Pn718 : 负载转矩观测器增益										*/
	USHORT	TlObsLowfilt;		/* Pn719 : 负载转矩观测器低通滤波器									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	swpminfrq;			/* Pn720 : 扫频开始频率												*/
	USHORT	swpmaxfrq;			/* Pn721 : 扫频结束频率												*/
	USHORT	detfrqlmt;			/* Pn722 : 检出共振频率下限值										*/
	USHORT	ezffttrq;			/* Pn723 : 扫描转矩指令振幅											*/
	USHORT	ezfftsw;			/* Pn724 : 与FFT相关的功能开关										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	RippleCompSw;		/* Pn740 : 速度脉动补偿开关											*/
	USHORT	RippleCompSpd;		/* Pn741 : 速度脉动补偿有效速度										*/
	USHORT	RippleCompGain;		/* Pn742 : 速度脉动补偿增益											*/
	USHORT	RippleCompFreq1;	/* Pn743 : 速度脉动补偿第1成分频率(相对电角度)						*/
	USHORT	RippleCompTrq1;		/* Pn744 : 速度脉动补偿第1成分振幅値								*/
	USHORT	RippleCompPhase1;	/* Pn745 : 速度脉动补偿第1成分位相									*/
	USHORT	RippleCompFreq2;	/* Pn746 : 速度脉动补偿第2成分频率(相对电角度)						*/
	USHORT	RippleCompTrq2;		/* Pn747 : 速度脉动补偿第2成分振幅値								*/
	USHORT	RippleCompPhase2;	/* Pn748 : 速度脉动补偿第2成分位相									*/
	USHORT	RippleCompFreq3;	/* Pn749 : 速度脉动补偿第3成分频率(相对电角度)						*/
	USHORT	RippleCompTrq3;		/* Pn74A : 速度脉动补偿第3成分振幅値								*/
	USHORT	RippleCompPhase3;	/* Pn74B : 速度脉动补偿第3成分位相									*/
	USHORT	RippleCompFreq4;	/* Pn74C : 速度脉动补偿第4成分频率(相对电角度)						*/
	USHORT	RippleCompTrq4;		/* Pn74D : 速度脉动补偿第4成分振幅値								*/
	USHORT	RippleCompPhase4;	/* Pn74E : 速度脉动补偿第4成分位相									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	WearkSw;			/* Pn755 : 弱磁控制功能开关											*/
	USHORT	kv;					/* Pn756 : 弱磁控制回路比例增益										*/
	USHORT	tv;					/* Pn757 : 弱磁控制回路积分时间常数									*/
	USHORT	idlim;				/* Pn758 : 弱磁控制回路积分极限										*/
	USHORT	vmax;				/* Pn759 : 弱磁控制电圧指令阈值										*/
	USHORT	vmaxid;				/* Pn75A : 弱磁控制时最大弱磁电流									*/
	USHORT	vpnavg;				/* Pn75B : 弱磁控制时DC电压滤波时间									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	poweroffchk;		/* Pn77F : 外部电源检测开关											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	powerofffiltime;	/* Pn780 : 外部电源检测滤波时间										*/
	USHORT	ovlvl;				/* Pn781 : 过压检测水平												*/
	USHORT	regonlvl;			/* Pn782 : 再生电压阀值												*/
	USHORT	regoffhys;			/* Pn783 : 再生关闭滞环宽度											*/
	USHORT	uvlvl;				/* Pn784 : 主回路欠压检测值											*/
	USHORT	uvfil;				/* Pn785 : 主回路欠压检测时间										*/
	USHORT	UvWrnLvl;			/* Pn786 : 主回路欠压警告检测值										*/
	USHORT	MaxspdTun;			/* Pn788 : 电机最高转速微调											*/
	USHORT	Icmu;				/* Pn78E : ICMU编码器开关											*/
	USHORT	PosJump;			/* Pn78F : 磁编码器控制开关											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	MotorNum;			/* Pn790 : 电机型号													*/
	USHORT	EncoderType;		/* Pn791 : 编码器类型												*/
	USHORT	EncZeroPhase;		/* Pn792 : 编码器零位												*/
	USHORT	PosOutputs2l;		/* Pn793 : 位置传感器分辨率											*/
	USHORT	PosOutputs2h;		/* Pn794 : 位置传感器分辨率(高16位）								*/
	USHORT	IncEncBit;			/* Pn795 : 增量式编码器控制开关										*/
	USHORT	Testpassword;		/* Pn79E : 整机/单板测试模式密匙									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	PrCmdSet;			/* Pn800 : 内部位置指令设定											*/
	USHORT	PrModeSet;			/* Pn802 : 内部多段位置运行模式										*/
	USHORT	PrEndSet;			/* Pn803 : 多段位置终点路径											*/
	USHORT	PrStartSet;			/* Pn804 : 顺序运行起始路径											*/
	USHORT	PrCommSet;			/* Pn806 : Pr指令通讯参数											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	PathPlan1L;			/* Pn810 : 路径1控制字L												*/
	USHORT	PathPlan1H;			/* Pn811 : 路径1控制字H												*/
	USHORT	PathPlan2L;			/* Pn812 : 路径1资料L												*/
	USHORT	PathPlan2H;			/* Pn813 : 路径1资料H												*/
	USHORT	PathPlan3L;			/* Pn814 : 路径2控制字L												*/
	USHORT	PathPlan3H;			/* Pn815 : 路径2控制字H												*/
	USHORT	PathPlan4L;			/* Pn816 : 路径2资料L												*/
	USHORT	PathPlan4H;			/* Pn817 : 路径2资料H												*/
	USHORT	PathPlan5L;			/* Pn818 : 路径3控制字L												*/
	USHORT	PathPlan5H;			/* Pn819 : 路径3控制字H												*/
	USHORT	PathPlan6L;			/* Pn81A : 路径3资料L												*/
	USHORT	PathPlan6H;			/* Pn81B : 路径3资料H												*/
	USHORT	PathPlan7L;			/* Pn81C : 路径4控制字L												*/
	USHORT	PathPlan7H;			/* Pn81D : 路径4控制字H												*/
	USHORT	PathPlan8L;			/* Pn81E : 路径4资料L												*/
	USHORT	PathPlan8H;			/* Pn81F : 路径4资料H												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	PathPlan9L;			/* Pn820 : 路径5控制字L												*/
	USHORT	PathPlan9H;			/* Pn821 : 路径5控制字H												*/
	USHORT	PathPlan10L;		/* Pn822 : 路径5资料L												*/
	USHORT	PathPlan10H;		/* Pn823 : 路径5资料H												*/
	USHORT	PathPlan11L;		/* Pn824 : 路径6控制字L												*/
	USHORT	PathPlan11H;		/* Pn825 : 路径6控制字H												*/
	USHORT	PathPlan12L;		/* Pn826 : 路径6资料L												*/
	USHORT	PathPlan12H;		/* Pn827 : 路径6资料H												*/
	USHORT	PathPlan13L;		/* Pn828 : 路径7控制字L												*/
	USHORT	PathPlan13H;		/* Pn829 : 路径7控制字H												*/
	USHORT	PathPlan14L;		/* Pn82A : 路径7资料L												*/
	USHORT	PathPlan14H;		/* Pn82B : 路径7资料H												*/
	USHORT	PathPlan15L;		/* Pn82C : 路径8控制字L												*/
	USHORT	PathPlan15H;		/* Pn82D : 路径8控制字H												*/
	USHORT	PathPlan16L;		/* Pn82E : 路径8资料L												*/
	USHORT	PathPlan16H;		/* Pn82F : 路径8资料H												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	PathPlan17L;		/* Pn830 : 路径9控制字L												*/
	USHORT	PathPlan17H;		/* Pn831 : 路径9控制字H												*/
	USHORT	PathPlan18L;		/* Pn832 : 路径9资料L												*/
	USHORT	PathPlan18H;		/* Pn833 : 路径9资料H												*/
	USHORT	PathPlan19L;		/* Pn834 : 路径10控制字L											*/
	USHORT	PathPlan19H;		/* Pn835 : 路径10控制字H											*/
	USHORT	PathPlan20L;		/* Pn836 : 路径10资料L												*/
	USHORT	PathPlan20H;		/* Pn837 : 路径10资料H												*/
	USHORT	PathPlan21L;		/* Pn838 : 路径11控制字L											*/
	USHORT	PathPlan21H;		/* Pn839 : 路径11控制字H											*/
	USHORT	PathPlan22L;		/* Pn83A : 路径11资料L												*/
	USHORT	PathPlan22H;		/* Pn83B : 路径11资料H												*/
	USHORT	PathPlan23L;		/* Pn83C : 路径12控制字L											*/
	USHORT	PathPlan23H;		/* Pn83D : 路径12控制字H											*/
	USHORT	PathPlan24L;		/* Pn83E : 路径12资料L												*/
	USHORT	PathPlan24H;		/* Pn83F : 路径12资料H												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	PathPlan25L;		/* Pn840 : 路径13控制字L											*/
	USHORT	PathPlan25H;		/* Pn841 : 路径13控制字H											*/
	USHORT	PathPlan26L;		/* Pn842 : 路径13资料L												*/
	USHORT	PathPlan26H;		/* Pn843 : 路径13资料H												*/
	USHORT	PathPlan27L;		/* Pn844 : 路径14控制字L											*/
	USHORT	PathPlan27H;		/* Pn845 : 路径14控制字H											*/
	USHORT	PathPlan28L;		/* Pn846 : 路径14资料L												*/
	USHORT	PathPlan28H;		/* Pn847 : 路径14资料H												*/
	USHORT	PathPlan29L;		/* Pn848 : 路径15控制字L											*/
	USHORT	PathPlan29H;		/* Pn849 : 路径15控制字H											*/
	USHORT	PathPlan30L;		/* Pn84A : 路径15资料L												*/
	USHORT	PathPlan30H;		/* Pn84B : 路径15资料H												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	AccDecT0;			/* Pn890 : 加/减速时间(编号#0)										*/
	USHORT	AccDecT1;			/* Pn891 : 加/减速时间(编号#1)										*/
	USHORT	AccDecT2;			/* Pn892 : 加/减速时间(编号#2)										*/
	USHORT	AccDecT3;			/* Pn893 : 加/减速时间(编号#3)										*/
	USHORT	AccDecT4;			/* Pn894 : 加/减速时间(编号#4)										*/
	USHORT	AccDecT5;			/* Pn895 : 加/减速时间(编号#5)										*/
	USHORT	AccDecT6;			/* Pn896 : 加/减速时间(编号#6)										*/
	USHORT	AccDecT7;			/* Pn897 : 加/减速时间(编号#7)										*/
	USHORT	DelayT0;			/* Pn898 : 位置到达后延时时间(编号#0)								*/
	USHORT	DelayT1;			/* Pn899 : 位置到达后延时时间(编号#1)								*/
	USHORT	DelayT2;			/* Pn89A : 位置到达后延时时间(编号#2)								*/
	USHORT	DelayT3;			/* Pn89B : 位置到达后延时时间(编号#3)								*/
	USHORT	DelayT4;			/* Pn89C : 位置到达后延时时间(编号#4)								*/
	USHORT	DelayT5;			/* Pn89D : 位置到达后延时时间(编号#5)								*/
	USHORT	DelayT6;			/* Pn89E : 位置到达后延时时间(编号#6)								*/
	USHORT	DelayT7;			/* Pn89F : 位置到达后延时时间(编号#7)								*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Spd0;				/* Pn8A0 : 内部目标速度设定(编号#0)									*/
	USHORT	Spd1;				/* Pn8A1 : 内部目标速度设定(编号#1)									*/
	USHORT	Spd2;				/* Pn8A2 : 内部目标速度设定(编号#2)									*/
	USHORT	Spd3;				/* Pn8A3 : 内部目标速度设定(编号#3)									*/
	USHORT	Spd4;				/* Pn8A4 : 内部目标速度设定(编号#4)									*/
	USHORT	Spd5;				/* Pn8A5 : 内部目标速度设定(编号#5)									*/
	USHORT	Spd6;				/* Pn8A6 : 内部目标速度设定(编号#6)									*/
	USHORT	Spd7;				/* Pn8A7 : 内部目标速度设定(编号#7)									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Tpdo1;				/* PnA00 : TPDO1映射组												*/
	USHORT	Tpdo1Map1L;			/* PnA01 : TPDO1映射1L												*/
	USHORT	Tpdo1Map1H;			/* PnA02 : TPDO1映射1H												*/
	USHORT	Tpdo1Map2L;			/* PnA03 : TPDO1映射2L												*/
	USHORT	Tpdo1Map2H;			/* PnA04 : TPDO1映射2H												*/
	USHORT	Tpdo1Map3L;			/* PnA05 : TPDO1映射3L												*/
	USHORT	Tpdo1Map3H;			/* PnA06 : TPDO1映射3H												*/
	USHORT	Tpdo1Map4L;			/* PnA07 : TPDO1映射4L												*/
	USHORT	Tpdo1Map4H;			/* PnA08 : TPDO1映射4H												*/
	USHORT	Tpdo1StationL;		/* PnA09 : TPDO1映射站号L											*/
	USHORT	Tpdo1StationH;		/* PnA0A : TPDO1映射站号H											*/
	USHORT	Tpdo1Type;			/* PnA0B : TPDO1传输类型											*/
	USHORT	Tpdo1InTime;		/* PnA0C : TPDO1禁止时间											*/
	USHORT	Tpdo1EventTime;		/* PnA0D : TPDO1事件时间											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Tpdo2;				/* PnA10 : TPDO2映射组												*/
	USHORT	Tpdo2Map1L;			/* PnA11 : TPDO2映射1L												*/
	USHORT	Tpdo2Map1H;			/* PnA12 : TPDO2映射1H												*/
	USHORT	Tpdo2Map2L;			/* PnA13 : TPDO2映射2L												*/
	USHORT	Tpdo2Map2H;			/* PnA14 : TPDO2映射2H												*/
	USHORT	Tpdo2Map3L;			/* PnA15 : TPDO2映射3L												*/
	USHORT	Tpdo2Map3H;			/* PnA16 : TPDO2映射3H												*/
	USHORT	Tpdo2Map4L;			/* PnA17 : TPDO2映射4L												*/
	USHORT	Tpdo2Map4H;			/* PnA18 : TPDO2映射4H												*/
	USHORT	Tpdo2StationL;		/* PnA19 : TPDO2映射站号L											*/
	USHORT	Tpdo2StationH;		/* PnA1A : TPDO2映射站号H											*/
	USHORT	Tpdo2Type;			/* PnA1B : TPDO2传输类型											*/
	USHORT	Tpdo2InTime;		/* PnA1C : TPDO2禁止时间											*/
	USHORT	Tpdo2EventTime;		/* PnA1D : TPDO2事件时间											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Tpdo3;				/* PnA20 : TPDO3映射组												*/
	USHORT	Tpdo3Map1L;			/* PnA21 : TPDO3映射1L												*/
	USHORT	Tpdo3Map1H;			/* PnA22 : TPDO3映射1H												*/
	USHORT	Tpdo3Map2L;			/* PnA23 : TPDO3映射2L												*/
	USHORT	Tpdo3Map2H;			/* PnA24 : TPDO3映射2H												*/
	USHORT	Tpdo3Map3L;			/* PnA25 : TPDO3映射3L												*/
	USHORT	Tpdo3Map3H;			/* PnA26 : TPDO3映射3H												*/
	USHORT	Tpdo3Map4L;			/* PnA27 : TPDO3映射4L												*/
	USHORT	Tpdo3Map4H;			/* PnA28 : TPDO3映射4H												*/
	USHORT	Tpdo3StationL;		/* PnA29 : TPDO3映射站号L											*/
	USHORT	Tpdo3StationH;		/* PnA2A : TPDO3映射站号H											*/
	USHORT	Tpdo3Type;			/* PnA2B : TPDO3传输类型											*/
	USHORT	Tpdo3InTime;		/* PnA2C : TPDO3禁止时间											*/
	USHORT	Tpdo3EventTime;		/* PnA2D : TPDO3事件时间											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Tpdo4;				/* PnA30 : TPDO4映射组												*/
	USHORT	Tpdo4Map1L;			/* PnA31 : TPDO4映射1L												*/
	USHORT	Tpdo4Map1H;			/* PnA32 : TPDO4映射1H												*/
	USHORT	Tpdo4Map2L;			/* PnA33 : TPDO4映射2L												*/
	USHORT	Tpdo4Map2H;			/* PnA34 : TPDO4映射2H												*/
	USHORT	Tpdo4Map3L;			/* PnA35 : TPDO4映射3L												*/
	USHORT	Tpdo4Map3H;			/* PnA36 : TPDO4映射3H												*/
	USHORT	Tpdo4Map4L;			/* PnA37 : TPDO4映射4L												*/
	USHORT	Tpdo4Map4H;			/* PnA38 : TPDO4映射4H												*/
	USHORT	Tpdo4StationL;		/* PnA39 : TPDO4映射站号L											*/
	USHORT	Tpdo4StationH;		/* PnA3A : TPDO4映射站号H											*/
	USHORT	Tpdo4Type;			/* PnA3B : TPDO4传输类型											*/
	USHORT	Tpdo4InTime;		/* PnA3C : TPDO4禁止时间											*/
	USHORT	Tpdo4EventTime;		/* PnA3D : TPDO4事件时间											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	RPDO1;				/* PnA40 : RPDO1映射组												*/
	USHORT	RPDO1Map1L;			/* PnA41 : RPDO1映射1L												*/
	USHORT	RPDO1Map1H;			/* PnA42 : RPDO1映射1H												*/
	USHORT	RPDO1Map2L;			/* PnA43 : RPDO1映射2L												*/
	USHORT	RPDO1Map2H;			/* PnA44 : RPDO1映射2H												*/
	USHORT	RPDO1Map3L;			/* PnA45 : RPDO1映射3L												*/
	USHORT	RPDO1Map3H;			/* PnA46 : RPDO1映射3H												*/
	USHORT	RPDO1Map4L;			/* PnA47 : RPDO1映射4L												*/
	USHORT	RPDO1Map4H;			/* PnA48 : RPDO1映射4H												*/
	USHORT	RPDO1StationL;		/* PnA49 : RPDO1映射站号L											*/
	USHORT	RPDO1StationH;		/* PnA4A : RPDO1映射站号H											*/
	USHORT	RPDO1Type;			/* PnA4B : RPDO1传输类型											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	RPDO2;				/* PnA50 : RPDO2映射组												*/
	USHORT	RPDO2Map1L;			/* PnA51 : RPDO2映射1L												*/
	USHORT	RPDO2Map1H;			/* PnA52 : RPDO2映射1H												*/
	USHORT	RPDO2Map2L;			/* PnA53 : RPDO2映射2L												*/
	USHORT	RPDO2Map2H;			/* PnA54 : RPDO2映射2H												*/
	USHORT	RPDO2Map3L;			/* PnA55 : RPDO2映射3L												*/
	USHORT	RPDO2Map3H;			/* PnA56 : RPDO2映射3H												*/
	USHORT	RPDO2Map4L;			/* PnA57 : RPDO2映射4L												*/
	USHORT	RPDO2Map4H;			/* PnA58 : RPDO2映射4H												*/
	USHORT	RPDO2StationL;		/* PnA59 : RPDO2映射站号L											*/
	USHORT	RPDO2StationH;		/* PnA5A : RPDO2映射站号H											*/
	USHORT	RPDO2Type;			/* PnA5B : RPDO2传输类型											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	RPDO3;				/* PnA60 : RPDO3映射组												*/
	USHORT	RPDO3Map1L;			/* PnA61 : RPDO3映射1L												*/
	USHORT	RPDO3Map1H;			/* PnA62 : RPDO3映射1H												*/
	USHORT	RPDO3Map2L;			/* PnA63 : RPDO3映射2L												*/
	USHORT	RPDO3Map2H;			/* PnA64 : RPDO3映射2H												*/
	USHORT	RPDO3Map3L;			/* PnA65 : RPDO3映射3L												*/
	USHORT	RPDO3Map3H;			/* PnA66 : RPDO3映射3H												*/
	USHORT	RPDO3Map4L;			/* PnA67 : RPDO3映射4L												*/
	USHORT	RPDO3Map4H;			/* PnA68 : RPDO3映射4H												*/
	USHORT	RPDO3StationL;		/* PnA69 : RPDO3映射站号L											*/
	USHORT	RPDO3StationH;		/* PnA6A : RPDO3映射站号H											*/
	USHORT	RPDO3Type;			/* PnA6B : RPDO3传输类型											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	RPDO4;				/* PnA70 : RPDO4映射组												*/
	USHORT	RPDO4Map1L;			/* PnA71 : RPDO4映射1L												*/
	USHORT	RPDO4Map1H;			/* PnA72 : RPDO4映射1H												*/
	USHORT	RPDO4Map2L;			/* PnA73 : RPDO4映射2L												*/
	USHORT	RPDO4Map2H;			/* PnA74 : RPDO4映射2H												*/
	USHORT	RPDO4Map3L;			/* PnA75 : RPDO4映射3L												*/
	USHORT	RPDO4Map3H;			/* PnA76 : RPDO4映射3H												*/
	USHORT	RPDO4Map4L;			/* PnA77 : RPDO4映射4L												*/
	USHORT	RPDO4Map4H;			/* PnA78 : RPDO4映射4H												*/
	USHORT	RPDO4StationL;		/* PnA79 : RPDO4映射站号L											*/
	USHORT	RPDO4StationH;		/* PnA7A : RPDO4映射站号H											*/
	USHORT	RPDO4Type;			/* PnA7B : RPDO4传输类型											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	EmcyEnL;			/* PnA80 : EmcyEnL													*/
	USHORT	EmcyEnH;			/* PnA81 : EmcyEnH													*/
	USHORT	HeartConsumerL;		/* PnA82 : HeartConsumerL											*/
	USHORT	HeartConsumerH;		/* PnA83 : HeartConsumerH											*/
	USHORT	HeartProducter;		/* PnA84 : HeartProducter											*/
	USHORT	Guardtime;			/* PnA85 : Guardtime												*/
	USHORT	lifetime;			/* PnA86 : lifetime													*/
	USHORT	CanControl;			/* PnA87 : CAN 控制寄存器											*/
	USHORT	CanControl2;		/* PnA88 : CAN 功能控制寄存器2										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Cia402Test;			/* PnB00 : CiA402控制模拟功能										*/
	USHORT	CANSpdCoeffL;		/* PnB02 : CAN速度转换系数L											*/
	USHORT	CANSpdCoeffH;		/* PnB03 : CAN速度转换系数H											*/
	USHORT	B04;				/* PnB04 : 预留														*/
	USHORT	B05;				/* PnB05 : 预留														*/
	USHORT	B06;				/* PnB06 : 预留														*/
	USHORT	B07;				/* PnB07 : 预留														*/
	USHORT	B08;				/* PnB08 : 预留														*/
	USHORT	B09;				/* PnB09 : 预留														*/
	USHORT	B0A;				/* PnB0A : 预留														*/
	USHORT	B0B;				/* PnB0B : 预留														*/
	USHORT	B0C;				/* PnB0C : 预留														*/
	USHORT	B0D;				/* PnB0D : 预留														*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	OBJ_605A;			/* PnB11 : [605Ah]快速停机方式选择									*/
	USHORT	OBJ_605D;			/* PnB12 : [605Dh]暂停方式选择										*/
	USHORT	OBJ_6060;			/* PnB13 : [6060h]模式选择											*/
	USHORT	OBJ_6065_L;			/* PnB14 : [6065h]位置偏差过大阈值L									*/
	USHORT	OBJ_6065_H;			/* PnB15 : [6065h]位置偏差过大阈值H									*/
	USHORT	OBJ_6067_L;			/* PnB16 : [6067h]位置到达阈值L										*/
	USHORT	OBJ_6067_H;			/* PnB17 : [6067h]位置到达阈值H										*/
	USHORT	OBJ_6068_L;			/* PnB18 : [6068h]位置到达时间窗口L									*/
	USHORT	OBJ_6068_H;			/* PnB19 : [6068h]位置到达时间窗口H									*/
	USHORT	OBJ_606D;			/* PnB1A : [606Dh]速度到达阈值										*/
	USHORT	OBJ_606E;			/* PnB1B : [606Eh]速度到达时间窗口									*/
	USHORT	OBJ_606F;			/* PnB1C : [606Fh]零速阈值											*/
	USHORT	OBJ_6070;			/* PnB1D : [6070h]零速时间窗口										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	OBJ_6072;			/* PnB21 : [6072h]最大转矩											*/
	USHORT	OBJ_607C_L;			/* PnB24 : [607Ch]原点偏置L											*/
	USHORT	OBJ_607C_H;			/* PnB25 : [607Ch]原点偏置H											*/
	USHORT	OBJ_607D_01_L;		/* PnB26 : [607Dh_01]软件绝对位置限制最小值L						*/
	USHORT	OBJ_607D_01_H;		/* PnB27 : [607Dh_01]软件绝对位置限制最小值H						*/
	USHORT	OBJ_607D_02_L;		/* PnB28 : [607Dh_02]软件绝对位置限制最大值L						*/
	USHORT	OBJ_607D_02_H;		/* PnB29 : [607Dh_02]软件绝对位置限制最大值H						*/
	USHORT	OBJ_607E;			/* PnB2A : [607Eh]指令极性											*/
	USHORT	OBJ_607F_L;			/* PnB2C : [607Fh]最大轮廓速度L										*/
	USHORT	OBJ_607F_H;			/* PnB2D : [607Fh]最大轮廓速度H										*/
	USHORT	OBJ_6080_L;			/* PnB2E : [6080h]最大电机速度L										*/
	USHORT	OBJ_6080_H;			/* PnB2F : [6080h]最大电机速度H										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	OBJ_6081_L;			/* PnB30 : [6081h]位置轮廓速度L										*/
	USHORT	OBJ_6081_H;			/* PnB31 : [6081h]位置轮廓速度H										*/
	USHORT	OBJ_6083_L;			/* PnB32 : [6083h]轮廓加速度L										*/
	USHORT	OBJ_6083_H;			/* PnB33 : [6083h]轮廓加速度H										*/
	USHORT	OBJ_6084_L;			/* PnB34 : [6084h]轮廓减速度L										*/
	USHORT	OBJ_6084_H;			/* PnB35 : [6084h]轮廓减速度H										*/
	USHORT	OBJ_6085_L;			/* PnB36 : [6085h]快速停机减速度L									*/
	USHORT	OBJ_6085_H;			/* PnB37 : [6085h]快速停机减速度H									*/
	USHORT	OBJ_6087_L;			/* PnB38 : [6087h]转矩斜坡时间L										*/
	USHORT	OBJ_6087_H;			/* PnB39 : [6087h]转矩斜坡时间H										*/
	USHORT	OBJ_6091_01_L;		/* PnB3A : [6091h_1]电机分辨率L										*/
	USHORT	OBJ_6091_01_H;		/* PnB3B : [6091h_1]电机分辨率H										*/
	USHORT	OBJ_6091_02_L;		/* PnB3C : [6091h_2]轴分辨率L										*/
	USHORT	OBJ_6091_02_H;		/* PnB3D : [6091h_2]轴分辨率H										*/
	USHORT	OBJ_6098;			/* PnB3E : [6098h]回零方式											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	OBJ_6099_01_L;		/* PnB40 : [6099h_1]搜索减速点信号速度L								*/
	USHORT	OBJ_6099_01_H;		/* PnB41 : [6099h_1]搜索减速点信号速度H								*/
	USHORT	OBJ_6099_02_L;		/* PnB42 : [6099h_2]搜索原点信号速度L								*/
	USHORT	OBJ_6099_02_H;		/* PnB43 : [6099h_2]搜索原点信号速度H								*/
	USHORT	OBJ_609A_L;			/* PnB44 : [609Ah]回零加速度L										*/
	USHORT	OBJ_609A_H;			/* PnB45 : [609Ah]回零加速度H										*/
	USHORT	OBJ_60B0_L;			/* PnB46 : [60B0h]位置偏置L											*/
	USHORT	OBJ_60B0_H;			/* PnB47 : [60B0h]位置偏置H											*/
	USHORT	OBJ_60B1_L;			/* PnB48 : [60B1h]转速偏置L											*/
	USHORT	OBJ_60B1_H;			/* PnB49 : [60B1h]转速偏置H											*/
	USHORT	OBJ_60B2_L;			/* PnB4A : [60B2h]转矩偏置											*/
	USHORT	OBJ_60B2_H;			/* PnB4B : [60B2h]转矩偏置H											*/
	USHORT	OBJ_60B8;			/* PnB4C : [60B8h]探针功能											*/
	USHORT	OBJ_60C1_01_L;		/* PnB4E : [60C1h]插补位置绝对位置L									*/
	USHORT	OBJ_60C1_01_H;		/* PnB4F : [60C1h]插补位置绝对位置H									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	OBJ_60C2_01;		/* PnB50 : [60C2_1h]插补周期值										*/
	USHORT	OBJ_60C2_02;		/* PnB51 : [60C2_2h]插补周期时间单位								*/
	USHORT	OBJ_60C5_L;			/* PnB52 : [60C5h]最大加速度L										*/
	USHORT	OBJ_60C5_H;			/* PnB53 : [60C5h]最大加速度H										*/
	USHORT	OBJ_60C6_L;			/* PnB54 : [60C6h]最大减速度L										*/
	USHORT	OBJ_60C6_H;			/* PnB55 : [60C6h]最大减速度H										*/
	USHORT	OBJ_60E0;			/* PnB56 : [60E0h]正向转矩限制值									*/
	USHORT	OBJ_60E1;			/* PnB57 : [60E1h]负向转矩限制值									*/
/*--------------------------------------------------------------------------------------------------*/
	DBYTEX	typm_e_1;			/* PnC00 : 高8位:编码器类型(4bit)|电机输入电压代码(4bit),低8位:电机类型	*/
	USHORT	encver_1;			/* PnC01 : 编码器软件版本											*/
	USHORT	motw_1;				/* PnC02 : 电机容量													*/
	DBYTEX	bit_dp_1;			/* PnC03 : 高字节:位置数据点位置，低字节:编码器位数					*/
	USHORT	limmlt_1;			/* PnC04 : 多回转限位，单圈为0										*/
	DBYTEX	vrat_max_1;			/* PnC05 : 高8位: 最高转速，低8位: 额定转速							*/
	DBYTEX	oslv_pol_1;			/* PnC06 : 高8位: 极数，低8位: OS检测水平							*/
	USHORT	rattrq_1;			/* PnC07 : 额定转矩 [0.01Nm]										*/
	USHORT	maxtrq_1;			/* PnC08 : 最大扭矩百分比											*/
	USHORT	irat_1;				/* PnC09 : 电机额定电流												*/
	USHORT	imax_1;				/* PnC0A : 电机瞬时最大电流 										*/
	USHORT	emfcmp_1;			/* PnC0B : 电动势(EMF)常数											*/
	USHORT	jmot_1;				/* PnC0C : 转子惯量													*/
	USHORT	motr_1;				/* PnC0D : 电枢绕组电阻												*/
	USHORT	motl_1;				/* PnC0E : 电枢电感													*/
	USHORT	bastrq_1;			/* PnC0F : 电机过载检测的基极电流									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	midtrq_1;			/* PnC10 : 电机过载检测的中间电流									*/
	USHORT	midolt_1;			/* PnC11 : 电机中间电流运行时过载检测时间							*/
	USHORT	mtrq2_1;			/* PnC12 : 电机过载检测的最大电流									*/
	USHORT	mtolt2_1;			/* PnC13 : 电机最大电流运行时过载检测时间							*/
	USHORT	phscmpM1_1;			/* PnC14 : 相位补偿1(补偿值，启动速度)								*/
	USHORT	ppitch_1;			/* PnC15 : 极距														*/
	USHORT	motlq0_1;			/* PnC16 : q轴电感LQ0												*/
	USHORT	motlq1_1;			/* PnC17 : q轴电感Lq1												*/
	USHORT	exp_trat_jmot_1;	/* PnC18 : 高8位：转子惯量指数，低8位：额定转矩指数					*/
	USHORT	exp_motw_spd_1;		/* PnC19 : 高8位：转速指数低，8位：额定输出指数						*/
	USHORT	fbit_fdp_1;			/* PnC1A : 全闭环编码器比特数, 位置数据点位置						*/
	USHORT	poleoffset_1;		/* PnC1B : 编码器偏移角												*/
	USHORT	motresfrq_1;		/* PnC1C : 电机共振抑制陷波滤波器的频率 							*/
	USHORT	phscmpM2_1;			/* PnC1D : 相角修正值												*/
	USHORT	flg_wf_1;			/* PnC1E : Flag														*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	drvno;				/* PnE00 : 驱动器型号												*/
	USHORT	ampw;				/* PnE01 : 伺服驱动器功率											*/
	USHORT	VoltType;			/* PnE02 : 伺服驱动器输入电压										*/
	USHORT	irats;				/* PnE03 : 伺服驱动器额定电流(峰值)									*/
	USHORT	imaxs;				/* PnE04 : 伺服驱动器最大电流(峰值)									*/
	USHORT	TempOH;				/* PnE05 : 模块温度故障检测阀值										*/
	DBYTEX	ibs_md;				/* PnE06 : 高位:驱动器过载检测中间电流,低位:驱动器过载检测基极电流	*/
	DBYTEX	imdt_mxt;			/* PnE07 : 高位:驱动器过载检测最大电流时间,低位:驱动器过载检测中间电流时间	*/
	DBYTEX	ratbt_mt;			/* PnE08 : 高位:电机过载检测中间电流微调,低位:电机过载检测基极电流微调	*/
	DBYTEX	ratmtt_2;			/* PnE09 : 高位:过载检测最大电流微调,低位:电机中间电流运行时过载检测时间微调	*/
	DBYTEX	ratmt2_os;			/* PnE0A : 高位:OS检测水平微调,低位:电机最大电流运行时过载检测时间微调	*/
	USHORT	reger;				/* PnE0B : 内置再生制动电阻阻值										*/
	USHORT	wre;				/* PnE0C : 内置再生抵抗容量											*/
	USHORT	dbr;				/* PnE0D : ＤＢ抵抗値												*/
	USHORT	wdb;				/* PnE0E : ＤＢ抵抗容量(默认)										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	pnvoltgn;			/* PnE10 : P-N电压检测水平(硬件能检测到的最大电压)					*/
	USHORT	vdetadfil;			/* PnE11 : P-N电压AD检测低通滤波器时间常数							*/
	USHORT	pnzero;				/* PnE12 : P-N电圧検出零調											*/
	USHORT	pngain;				/* PnE13 : P-N电圧検出增益											*/
	USHORT	vdefilsw;			/* PnE14 : 主电路检测滤波器选择开关 								*/
	USHORT	almmsk1;			/* PnE15 : 警报屏蔽1												*/
	USHORT	almmsk2;			/* PnE16 : 警报屏蔽2												*/
	USHORT	MosPump;			/* PnE17 : 单管参数													*/
	USHORT	syssw1;				/* PnE1B : 系统开关1												*/
	USHORT	syssw2;				/* PnE1C : 系统开关2												*/
	USHORT	syssw3;				/* PnE1D : 系统开关3												*/
	USHORT	spgfail;			/* PnE1E : 串行编码器通讯失败容许次数								*/
	USHORT	ifil;				/* PnE1F : 噪声抑制截止频率											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	ignd;				/* PnE20 : 电流环增益(D)											*/
	USHORT	ignq;				/* PnE21 : 电流环增益(Q)											*/
	USHORT	kid;				/* PnE22 : 电流环积分时间常数(D) 									*/
	USHORT	kiq;				/* PnE23 : 电流环积分时间常数(Q) 									*/
	USHORT	limintd;			/* PnE24 : 电流环积分限制值(D)										*/
	USHORT	limintq;			/* PnE25 : 电流环积分限制值(Q)										*/
	USHORT	shant1;				/* PnE28 : 电流检测增益1											*/
	USHORT	vrevgn;				/* PnE29 : 电压补偿增益 											*/
	USHORT	pwmf;				/* PnE2A : 载波频率													*/
	USHORT	odt_c;				/* PnE2B : 死区补偿增益 | 死区时间									*/
	USHORT	ObsGain;			/* PnE2C : 电流预测增益												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	ad_prm3;			/* PnE32 : 驱动器过流保护滤波时间常数								*/
	USHORT	ad_prm4;			/* PnE33 : 驱动器过流保护值											*/
	USHORT	phscmp;				/* PnE34 : 位相補償													*/
	USHORT	mtovcnt;			/* PnE39 : 多圈数据溢出计数器										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	ipg_rwt;			/* PnE44 : 下位:i-P制御割合, 上位:暴走失控检测扭矩					*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	fbfil2;				/* PnEA8 : 第2速度反馈滤波时间常数									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	MLess_vrat_max;		/* PnEE0 : 无电机测试功能假想马达速度								*/
	USHORT	MLess_oslv_pol;		/* PnEE1 : 无电机测试功能假想马达ＯＳ検出阈值, 磁极数				*/
	USHORT	Mless_jmot;			/* PnEE2 : 无电机测试功能假想马达转子惯量							*/
	USHORT	Mless_exp_spd_jmot;	/* PnEE3 : 无电机测试功能假想马达指数参数							*/
	USHORT	Mless_PlantModel;	/* PnEE4 : 无电机测试功能假想负载模型								*/
	USHORT	Dm;					/* PnEE5 : 无电机测试功能假想电机摩擦系数							*/
	USHORT	Dl;					/* PnEE6 : 无电机测试功能假想负载摩擦系数							*/
	USHORT	frml;				/* PnEE7 : 无电机测试功能假想负载共振频率 							*/
	USHORT	ztrml;				/* PnEE8 : 无电机测试功能假想负载振动阻尼系数						*/
	USHORT	jbrate;				/* PnEE9 : 无电机测试功能假想机台惯量比								*/
	USHORT	fnb;				/* PnEEA : 无电机测试功能假想机台无阻尼振动频率						*/
	USHORT	zb;					/* PnEEB : 无电机测试功能假想机台振动阻尼系数						*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	VfAccTime;			/* PnEF3 : I/F加减速时间											*/
	USHORT	VfSetFreq;			/* PnEF4 : I/F设定频率												*/
	USHORT	VfSetVolt;			/* PnEF5 : I/F设定电流												*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	EncErrClr;			/* Pn07F : 编码器多圈和故障清除										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Estimatesw;			/* Pn710 : 在线参数辨识开关											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	FaTestControl;		/* Pn79D : 厂家测试用标志											*/
	USHORT	password;			/* Pn79F : 厂家密码													*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	SnL;				/* Pn7A0 : SN低位													*/
	USHORT	SnH;				/* Pn7A1 : SN高位													*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	OBJ_6040;			/* PnB10 : [6040h]控制字											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	OBJ_6071;			/* PnB20 : [6071h]目标转矩											*/
	USHORT	OBJ_607A_L;			/* PnB22 : [607Ah]目标位置L											*/
	USHORT	OBJ_607A_H;			/* PnB23 : [607Ah]目标位置H											*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	OBJ_60FF_L;			/* PnB58 : [60FFh]目标速度 L										*/
	USHORT	OBJ_60FF_H;			/* PnB59 : [60FFh]目标速度H											*/
/*--------------------------------------------------------------------------------------------------*/
	DBYTEX	typm_e;				/* PnF00 : 高8位:编码器类型(4bit)|电机输入电压代码(4bit),低8位:电机类型	*/
	USHORT	encver;				/* PnF01 : 编码器软件版本											*/
	USHORT	motw;				/* PnF02 : 电机容量													*/
	DBYTEX	bit_dp;				/* PnF03 : 高字节:位置数据点位置，低字节:编码器位数					*/
	USHORT	limmlt;				/* PnF04 : 多回转限位，单圈为0										*/
	DBYTEX	vrat_max;			/* PnF05 : 高8位: 最高转速，低8位: 额定转速							*/
	DBYTEX	oslv_pol;			/* PnF06 : 高8位: 极数，低8位: OS检测水平							*/
	USHORT	rattrq;				/* PnF07 : 额定转矩 [0.01Nm]										*/
	USHORT	maxtrq;				/* PnF08 : 最大扭矩百分比											*/
	USHORT	irat;				/* PnF09 : 电机额定电流												*/
	USHORT	imax;				/* PnF0A : 电机瞬时最大电流 										*/
	USHORT	emfcmp;				/* PnF0B : 电动势(EMF)常数											*/
	USHORT	jmot;				/* PnF0C : 转子惯量													*/
	USHORT	motr;				/* PnF0D : 电枢绕组电阻												*/
	USHORT	motl;				/* PnF0E : 电枢电感													*/
	USHORT	bastrq;				/* PnF0F : 电机过载检测的基极电流									*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	midtrq;				/* PnF10 : 电机过载检测的中间电流									*/
	USHORT	midolt;				/* PnF11 : 电机中间电流运行时过载检测时间							*/
	USHORT	mtrq2;				/* PnF12 : 电机过载检测的最大电流									*/
	USHORT	mtolt2;				/* PnF13 : 电机最大电流运行时过载检测时间							*/
	USHORT	phscmpM1;			/* PnF14 : 相位补偿1(补偿值，启动速度)								*/
	USHORT	ppitch;				/* PnF15 : 极距														*/
	USHORT	motlq0;				/* PnF16 : q轴电感LQ0												*/
	USHORT	motlq1;				/* PnF17 : q轴电感Lq1												*/
	USHORT	exp_trat_jmot;		/* PnF18 : 高8位：转子惯量指数，低8位：额定转矩指数					*/
	USHORT	exp_motw_spd;		/* PnF19 : 高8位：转速指数低，8位：额定输出指数						*/
	USHORT	fbit_fdp;			/* PnF1A : 全闭环编码器比特数, 位置数据点位置						*/
	USHORT	poleoffset;			/* PnF1B : 编码器偏移角												*/
	USHORT	motresfrq;			/* PnF1C : 电机共振抑制陷波滤波器的频率 							*/
	USHORT	phscmpM2;			/* PnF1D : 相角修正值												*/
	USHORT	flg_wf;				/* PnF1E : Flag														*/
	USHORT	AutoAIAdj;			/* PnF1F : 模拟量自动校准											*/
} PRMDATA;
/*--------------------------------------------------------------------------------------------------*/



/****************************************************************************************************/
/*																									*/
/*		标准参数计算函数																			*/
/*																									*/
/****************************************************************************************************/
LONG	pncal_StdDummy( ULONG Cmd, ULONG Data, ULONG Digit );	/* 标准参数计算函数					*/



/****************************************************************************************************/
/*																									*/
/*		参数定义Extern声明																			*/
/*																									*/
/****************************************************************************************************/
extern	const	PRMDEF	pndef_b_prm0_0;
extern	const	PRMDEF	pndef_b_prm0_1;
extern	const	PRMDEF	pndef_motdir;
extern	const	PRMDEF	pndef_mondef;
extern	const	PRMDEF	pndef_b_prm0_04;
extern	const	PRMDEF	pndef_b_prm0_05;
extern	const	PRMDEF	pndef_b_prm0_06;
extern	const	PRMDEF	pndef_b_prm0_07;
extern	const	PRMDEF	pndef_brktim;
extern	const	PRMDEF	pndef_brkwai;
extern	const	PRMDEF	pndef_brkspd;
extern	const	PRMDEF	pndef_brkOnDly;
extern	const	PRMDEF	pndef_b_prm0_0C;
extern	const	PRMDEF	pndef_b_prm0_0D;
extern	const	PRMDEF	pndef_b_prm0_0E;
extern	const	PRMDEF	pndef_b_prm0_F;
extern	const	PRMDEF	pndef_PcmdFTime;
extern	const	PRMDEF	pndef_regres;
extern	const	PRMDEF	pndef_regresvalue;
extern	const	PRMDEF	pndef_ServoOnDely;
extern	const	PRMDEF	pndef_olwarlvl;
extern	const	PRMDEF	pndef_mtbastrq_drt;
extern	const	PRMDEF	pndef_snglph_base_drt;
extern	const	PRMDEF	pndef_dbres;
extern	const	PRMDEF	pndef_fcplsel;
extern	const	PRMDEF	pndef_fcplsel2;
extern	const	PRMDEF	pndef_FensFiltTime;
extern	const	PRMDEF	pndef_fcplsnl;
extern	const	PRMDEF	pndef_fcplsnh;
extern	const	PRMDEF	pndef_fcplsml;
extern	const	PRMDEF	pndef_fcplsmh;
extern	const	PRMDEF	pndef_fpgoverlv2l;
extern	const	PRMDEF	pndef_fpgoverlv2h;
extern	const	PRMDEF	pndef_fpgoverclrl;
extern	const	PRMDEF	pndef_fpgoverclrh;
extern	const	PRMDEF	pndef_FenseSel;
extern	const	PRMDEF	pndef_Meth2ComV;
extern	const	PRMDEF	pndef_FensSpdlv;
extern	const	PRMDEF	pndef_SoftLimitMaxl;
extern	const	PRMDEF	pndef_SoftLimitMaxh;
extern	const	PRMDEF	pndef_SoftLimitMMax;
extern	const	PRMDEF	pndef_SoftLimitMinl;
extern	const	PRMDEF	pndef_SoftLimitMinh;
extern	const	PRMDEF	pndef_SoftLimitMMin;
extern	const	PRMDEF	pndef_SoftLimitDelta;
extern	const	PRMDEF	pndef_offdec;
extern	const	PRMDEF	pndef_absEncuse;
extern	const	PRMDEF	pndef_absEncalm;
extern	const	PRMDEF	pndef_UvModeSel;
extern	const	PRMDEF	pndef_UvTrqLmt;
extern	const	PRMDEF	pndef_UvTrqLmtOffFil;
extern	const	PRMDEF	pndef_torqlimt;
extern	const	PRMDEF	pndef_tlmtf;
extern	const	PRMDEF	pndef_tlmtr;
extern	const	PRMDEF	pndef_emgtrq;
extern	const	PRMDEF	pndef_outlmtf;
extern	const	PRMDEF	pndef_outlmtr;
extern	const	PRMDEF	pndef_RunOverTorq;
extern	const	PRMDEF	pndef_RunOverSpd;
extern	const	PRMDEF	pndef_pgrat;
extern	const	PRMDEF	pndef_SerEncSel;
extern	const	PRMDEF	pndef_EncErrClr;
extern	const	PRMDEF	pndef_Address;
extern	const	PRMDEF	pndef_Mode;
extern	const	PRMDEF	pndef_EtherCatAddr;
extern	const	PRMDEF	pndef_EtherCatType;
extern	const	PRMDEF	pndef_SycnhErr;
extern	const	PRMDEF	pndef_ComSaveEeprom;
extern	const	PRMDEF	pndef_EtherCATConfig;
extern	const	PRMDEF	pndef_addmapEn;
extern	const	PRMDEF	pndef_addmap1s;
extern	const	PRMDEF	pndef_addmap1e;
extern	const	PRMDEF	pndef_addmap2s;
extern	const	PRMDEF	pndef_addmap2e;
extern	const	PRMDEF	pndef_jrate;
extern	const	PRMDEF	pndef_loophz;
extern	const	PRMDEF	pndef_pitime;
extern	const	PRMDEF	pndef_posgn;
extern	const	PRMDEF	pndef_trqfil11;
extern	const	PRMDEF	pndef_loophz2;
extern	const	PRMDEF	pndef_pitime2;
extern	const	PRMDEF	pndef_posgn2;
extern	const	PRMDEF	pndef_trqfil12;
extern	const	PRMDEF	pndef_tunmode;
extern	const	PRMDEF	pndef_rigidity;
extern	const	PRMDEF	pndef_interpolation;
extern	const	PRMDEF	pndef_gnsw1;
extern	const	PRMDEF	pndef_gnswfil1;
extern	const	PRMDEF	pndef_gnswfil2;
extern	const	PRMDEF	pndef_gnswwait1;
extern	const	PRMDEF	pndef_gnswwait2;
extern	const	PRMDEF	pndef_LowSpdLevel;
extern	const	PRMDEF	pndef_SpdSwitch;
extern	const	PRMDEF	pndef_pitfil;
extern	const	PRMDEF	pndef_ffgn;
extern	const	PRMDEF	pndef_fffil;
extern	const	PRMDEF	pndef_sfgn;
extern	const	PRMDEF	pndef_sffil;
extern	const	PRMDEF	pndef_fbfil;
extern	const	PRMDEF	pndef_gnmode;
extern	const	PRMDEF	pndef_mdswlv;
extern	const	PRMDEF	pndef_mswrf;
extern	const	PRMDEF	pndef_mswacc;
extern	const	PRMDEF	pndef_msplvl;
extern	const	PRMDEF	pndef_mfvibsw;
extern	const	PRMDEF	pndef_avibgn;
extern	const	PRMDEF	pndef_avibfrq;
extern	const	PRMDEF	pndef_avibdamp;
extern	const	PRMDEF	pndef_avibfil1;
extern	const	PRMDEF	pndef_avibfil2;
extern	const	PRMDEF	pndef_pstbfrq;
extern	const	PRMDEF	pndef_pstbdamp;
extern	const	PRMDEF	pndef_Nntchfil1;
extern	const	PRMDEF	pndef_Nntchdamp1;
extern	const	PRMDEF	pndef_Nntchfil2;
extern	const	PRMDEF	pndef_Nntchdamp2;
extern	const	PRMDEF	pndef_tfuncsw;
extern	const	PRMDEF	pndef_anotchsw;
extern	const	PRMDEF	pndef_vibdetlvl;
extern	const	PRMDEF	pndef_ntchfil1;
extern	const	PRMDEF	pndef_ntchq1;
extern	const	PRMDEF	pndef_ntchdamp1;
extern	const	PRMDEF	pndef_ntchfil2;
extern	const	PRMDEF	pndef_ntchq2;
extern	const	PRMDEF	pndef_ntchdamp2;
extern	const	PRMDEF	pndef_ntchfil3;
extern	const	PRMDEF	pndef_ntchq3;
extern	const	PRMDEF	pndef_ntchdamp3;
extern	const	PRMDEF	pndef_ntchfil4;
extern	const	PRMDEF	pndef_ntchq4;
extern	const	PRMDEF	pndef_ntchdamp4;
extern	const	PRMDEF	pndef_dobgn;
extern	const	PRMDEF	pndef_dobgn2;
extern	const	PRMDEF	pndef_dtrqgn;
extern	const	PRMDEF	pndef_dlpfil;
extern	const	PRMDEF	pndef_dobjgn;
extern	const	PRMDEF	pndef_evoben;
extern	const	PRMDEF	pndef_evobgn;
extern	const	PRMDEF	pndef_evobjgn;
extern	const	PRMDEF	pndef_evoblpf;
extern	const	PRMDEF	pndef_fricmaxspd;
extern	const	PRMDEF	pndef_friccoefpos;
extern	const	PRMDEF	pndef_friccoefneg;
extern	const	PRMDEF	pndef_DatLevel;
extern	const	PRMDEF	pndef_TunLessGain;
extern	const	PRMDEF	pndef_TunLessStiff;
extern	const	PRMDEF	pndef_TunLessTrqLpf;
extern	const	PRMDEF	pndef_TunLessVfbLpf;
extern	const	PRMDEF	pndef_vibsel;
extern	const	PRMDEF	pndef_vibsens;
extern	const	PRMDEF	pndef_vibnorm;
extern	const	PRMDEF	pndef_ovserrdetlvl;
extern	const	PRMDEF	pndef_adatgmax;
extern	const	PRMDEF	pndef_gcomptrq;
extern	const	PRMDEF	pndef_pqfriqcomptrq;
extern	const	PRMDEF	pndef_nqfriqcomptrq;
extern	const	PRMDEF	pndef_vfrigcomptrq;
extern	const	PRMDEF	pndef_spdhys;
extern	const	PRMDEF	pndef_prstsw;
extern	const	PRMDEF	pndef_PulseType;
extern	const	PRMDEF	pndef_posctrl;
extern	const	PRMDEF	pndef_MulFrq;
extern	const	PRMDEF	pndef_ratb2l;
extern	const	PRMDEF	pndef_ratb2h;
extern	const	PRMDEF	pndef_rata2l;
extern	const	PRMDEF	pndef_rata2h;
extern	const	PRMDEF	pndef_expbias1;
extern	const	PRMDEF	pndef_expfil;
extern	const	PRMDEF	pndef_mafil;
extern	const	PRMDEF	pndef_cmctrlexsw;
extern	const	PRMDEF	pndef_blcm2l;
extern	const	PRMDEF	pndef_blcm2h;
extern	const	PRMDEF	pndef_blfiltime;
extern	const	PRMDEF	pndef_mdlsw_1;
extern	const	PRMDEF	pndef_mdlsw_2;
extern	const	PRMDEF	pndef_remdetw;
extern	const	PRMDEF	pndef_mdlantfrq;
extern	const	PRMDEF	pndef_mdlresfrq;
extern	const	PRMDEF	pndef_ff_frq;
extern	const	PRMDEF	pndef_ff_fil;
extern	const	PRMDEF	pndef_mdlsw;
extern	const	PRMDEF	pndef_mdlgn;
extern	const	PRMDEF	pndef_mdlzeta;
extern	const	PRMDEF	pndef_mdlvff;
extern	const	PRMDEF	pndef_mdlptff;
extern	const	PRMDEF	pndef_mdlntff;
extern	const	PRMDEF	pndef_mdlgn2;
extern	const	PRMDEF	pndef_mdlzeta2;
extern	const	PRMDEF	pndef_mfctype;
extern	const	PRMDEF	pndef_nearlv2l;
extern	const	PRMDEF	pndef_nearlv2h;
extern	const	PRMDEF	pndef_coinlv2l;
extern	const	PRMDEF	pndef_coinlv2h;
extern	const	PRMDEF	pndef_overlv2l;
extern	const	PRMDEF	pndef_overlv2h;
extern	const	PRMDEF	pndef_overwrnlv;
extern	const	PRMDEF	pndef_svonoverlv2l;
extern	const	PRMDEF	pndef_svonoverlv2h;
extern	const	PRMDEF	pndef_svonoverwrnlv;
extern	const	PRMDEF	pndef_svonspdlmtlv;
extern	const	PRMDEF	pndef_PulseSel;
extern	const	PRMDEF	pndef_prstsw_1;
extern	const	PRMDEF	pndef_prstsw_2;
extern	const	PRMDEF	pndef_cmfilsw_3;
extern	const	PRMDEF	pndef_revlimit;
extern	const	PRMDEF	pndef_revovDir;
extern	const	PRMDEF	pndef_srevlimitL;
extern	const	PRMDEF	pndef_srevlimitH;
extern	const	PRMDEF	pndef_orgmode;
extern	const	PRMDEF	pndef_orgspdhight;
extern	const	PRMDEF	pndef_orgspdlow;
extern	const	PRMDEF	pndef_orgdecacc;
extern	const	PRMDEF	pndef_orgoffsetL;
extern	const	PRMDEF	pndef_orgoffsetH;
extern	const	PRMDEF	pndef_orgMpos;
extern	const	PRMDEF	pndef_orgSposL;
extern	const	PRMDEF	pndef_orgSposH;
extern	const	PRMDEF	pndef_orgovtime;
extern	const	PRMDEF	pndef_orgstatus;
extern	const	PRMDEF	pndef_spdSource;
extern	const	PRMDEF	pndef_spdcmd;
extern	const	PRMDEF	pndef_srfil;
extern	const	PRMDEF	pndef_speed0;
extern	const	PRMDEF	pndef_speed1;
extern	const	PRMDEF	pndef_speed2;
extern	const	PRMDEF	pndef_speed3;
extern	const	PRMDEF	pndef_sfsacc;
extern	const	PRMDEF	pndef_sfsdec;
extern	const	PRMDEF	pndef_sfsts;
extern	const	PRMDEF	pndef_clamp;
extern	const	PRMDEF	pndef_clampMaxSpd;
extern	const	PRMDEF	pndef_tgonlv;
extern	const	PRMDEF	pndef_MaxSpd;
extern	const	PRMDEF	pndef_vcmplv;
extern	const	PRMDEF	pndef_b_prm400;
extern	const	PRMDEF	pndef_secfil;
extern	const	PRMDEF	pndef_secq;
extern	const	PRMDEF	pndef_trqcmddirtype;
extern	const	PRMDEF	pndef_treffil;
extern	const	PRMDEF	pndef_intrqcmd1;
extern	const	PRMDEF	pndef_intrqcmd2;
extern	const	PRMDEF	pndef_intrqcmd3;
extern	const	PRMDEF	pndef_intrqcmd4;
extern	const	PRMDEF	pndef_ntqspdlimt1;
extern	const	PRMDEF	pndef_ntqspdlimt2;
extern	const	PRMDEF	pndef_torqcmd1;
extern	const	PRMDEF	pndef_torqcmd2;
extern	const	PRMDEF	pndef_torqcmdtimewindow;
extern	const	PRMDEF	pndef_trqcmddirtype1;
extern	const	PRMDEF	pndef_monitortime;
extern	const	PRMDEF	pndef_jogspd;
extern	const	PRMDEF	pndef_pjogsw;
extern	const	PRMDEF	pndef_pjogdistl;
extern	const	PRMDEF	pndef_pjogdisth;
extern	const	PRMDEF	pndef_pjogacctm;
extern	const	PRMDEF	pndef_pjogwaittm;
extern	const	PRMDEF	pndef_pjognum;
extern	const	PRMDEF	pndef_pjogrotspd;
extern	const	PRMDEF	pndef_CurIntrig;
extern	const	PRMDEF	pndef_CurType;
extern	const	PRMDEF	pndef_CurAmp;
extern	const	PRMDEF	pndef_CurFreq;
extern	const	PRMDEF	pndef_CurOffSet;
extern	const	PRMDEF	pndef_SpdIntrig;
extern	const	PRMDEF	pndef_SpdType;
extern	const	PRMDEF	pndef_SpdAmp;
extern	const	PRMDEF	pndef_SpdFreq;
extern	const	PRMDEF	pndef_SpdOffSet;
extern	const	PRMDEF	pndef_CurLimtHard;
extern	const	PRMDEF	pndef_LimtTHard;
extern	const	PRMDEF	pndef_SpdLimtHard;
extern	const	PRMDEF	pndef_CurLimtSoft;
extern	const	PRMDEF	pndef_LimtTSoft;
extern	const	PRMDEF	pndef_SpdLimtSoft;
extern	const	PRMDEF	pndef_StallEn;
extern	const	PRMDEF	pndef_Pn527;
extern	const	PRMDEF	pndef_Pn528;
extern	const	PRMDEF	pndef_Pn529;
extern	const	PRMDEF	pndef_Pn530;
extern	const	PRMDEF	pndef_Pn531;
extern	const	PRMDEF	pndef_Pn532;
extern	const	PRMDEF	pndef_Pn533;
extern	const	PRMDEF	pndef_Pn534;
extern	const	PRMDEF	pndef_Pn535;
extern	const	PRMDEF	pndef_Pn536;
extern	const	PRMDEF	pndef_Pn537;
extern	const	PRMDEF	pndef_Pn538;
extern	const	PRMDEF	pndef_Pn539;
extern	const	PRMDEF	pndef_Pn540;
extern	const	PRMDEF	pndef_Pn541;
extern	const	PRMDEF	pndef_Pn542;
extern	const	PRMDEF	pndef_Pn543;
extern	const	PRMDEF	pndef_Pn544;
extern	const	PRMDEF	pndef_Pn545;
extern	const	PRMDEF	pndef_Pn546;
extern	const	PRMDEF	pndef_Pn547;
extern	const	PRMDEF	pndef_Pn548;
extern	const	PRMDEF	pndef_Pn549;
extern	const	PRMDEF	pndef_Pn550;
extern	const	PRMDEF	pndef_Pn551;
extern	const	PRMDEF	pndef_Pn552;
extern	const	PRMDEF	pndef_Pn553;
extern	const	PRMDEF	pndef_Pn554;
extern	const	PRMDEF	pndef_Pn555;
extern	const	PRMDEF	pndef_Pn556;
extern	const	PRMDEF	pndef_Pn557;
extern	const	PRMDEF	pndef_Pn558;
extern	const	PRMDEF	pndef_Pn559;
extern	const	PRMDEF	pndef_MIT_Volmax;
extern	const	PRMDEF	pndef_MIT_Volmin;
extern	const	PRMDEF	pndef_CANTimeOut;
extern	const	PRMDEF	pndef_MIT_Curmax;
extern	const	PRMDEF	pndef_MIT_Curmin;
extern	const	PRMDEF	pndef_AccRads;
extern	const	PRMDEF	pndef_KtSetEn;
extern	const	PRMDEF	pndef_KtSet;
extern	const	PRMDEF	pndef_KpPos;
extern	const	PRMDEF	pndef_KdPos;
extern	const	PRMDEF	pndef_KpSpd;
extern	const	PRMDEF	pndef_KiSpd;
extern	const	PRMDEF	pndef_KpCur;
extern	const	PRMDEF	pndef_KiCur;
extern	const	PRMDEF	pndef_MIT_KpMax;
extern	const	PRMDEF	pndef_MIT_KpMin;
extern	const	PRMDEF	pndef_MIT_KdMax;
extern	const	PRMDEF	pndef_MIT_KdMin;
extern	const	PRMDEF	pndef_MIT_Trefmax;
extern	const	PRMDEF	pndef_MIT_Trefmin;
extern	const	PRMDEF	pndef_MIT_Posmax;
extern	const	PRMDEF	pndef_MIT_Posmin;
extern	const	PRMDEF	pndef_MIT_Spdmax;
extern	const	PRMDEF	pndef_MIT_Spdmin;
extern	const	PRMDEF	pndef_PosAOffSetL;
extern	const	PRMDEF	pndef_PosAOffSetH;
extern	const	PRMDEF	pndef_CANMIT;
extern	const	PRMDEF	pndef_MIT_Trq;
extern	const	PRMDEF	pndef_MIT_Sitam;
extern	const	PRMDEF	pndef_MIT_WmRef;
extern	const	PRMDEF	pndef_MIT_PosFil;
extern	const	PRMDEF	pndef_MIT_Tref;
extern	const	PRMDEF	pndef_MIT_Kp;
extern	const	PRMDEF	pndef_MIT_Kd;
extern	const	PRMDEF	pndef_MIT_RateA;
extern	const	PRMDEF	pndef_MIT_RateB;
extern	const	PRMDEF	pndef_MutiBOffSet;
extern	const	PRMDEF	pndef_PosBOffSetL;
extern	const	PRMDEF	pndef_PosBOffSetH;
extern	const	PRMDEF	pndef_Pn597;
extern	const	PRMDEF	pndef_EncDelay;
extern	const	PRMDEF	pndef_Pn599;
extern	const	PRMDEF	pndef_XFilTime;
extern	const	PRMDEF	pndef_insel1;
extern	const	PRMDEF	pndef_insel2;
extern	const	PRMDEF	pndef_insel3;
extern	const	PRMDEF	pndef_insel4;
extern	const	PRMDEF	pndef_outsel1;
extern	const	PRMDEF	pndef_outsel2;
extern	const	PRMDEF	pndef_AI1treffil;
extern	const	PRMDEF	pndef_AI2treffil;
extern	const	PRMDEF	pndef_AI1Offset;
extern	const	PRMDEF	pndef_AI2Offset;
extern	const	PRMDEF	pndef_AI1Gain;
extern	const	PRMDEF	pndef_AI2Gain;
extern	const	PRMDEF	pndef_AI1Zero;
extern	const	PRMDEF	pndef_AI2Zero;
extern	const	PRMDEF	pndef_VirDI;
extern	const	PRMDEF	pndef_VirDO;
extern	const	PRMDEF	pndef_Trobe1Filtime;
extern	const	PRMDEF	pndef_Trobe2Filtime;
extern	const	PRMDEF	pndef_AATDist;
extern	const	PRMDEF	pndef_PnB24;
extern	const	PRMDEF	pndef_JstVibValve;
extern	const	PRMDEF	pndef_Estimatesw;
extern	const	PRMDEF	pndef_EstimateTime;
extern	const	PRMDEF	pndef_EstimateSpd;
extern	const	PRMDEF	pndef_EstimateGain;
extern	const	PRMDEF	pndef_TlObssw;
extern	const	PRMDEF	pndef_TlObsIntero;
extern	const	PRMDEF	pndef_TlObsfriction;
extern	const	PRMDEF	pndef_TlObsGain;
extern	const	PRMDEF	pndef_TlObsLowfilt;
extern	const	PRMDEF	pndef_swpminfrq;
extern	const	PRMDEF	pndef_swpmaxfrq;
extern	const	PRMDEF	pndef_detfrqlmt;
extern	const	PRMDEF	pndef_ezffttrq;
extern	const	PRMDEF	pndef_ezfftsw;
extern	const	PRMDEF	pndef_RippleCompSw;
extern	const	PRMDEF	pndef_RippleCompSpd;
extern	const	PRMDEF	pndef_RippleCompGain;
extern	const	PRMDEF	pndef_RippleCompFreq1;
extern	const	PRMDEF	pndef_RippleCompTrq1;
extern	const	PRMDEF	pndef_RippleCompPhase1;
extern	const	PRMDEF	pndef_RippleCompFreq2;
extern	const	PRMDEF	pndef_RippleCompTrq2;
extern	const	PRMDEF	pndef_RippleCompPhase2;
extern	const	PRMDEF	pndef_RippleCompFreq3;
extern	const	PRMDEF	pndef_RippleCompTrq3;
extern	const	PRMDEF	pndef_RippleCompPhase3;
extern	const	PRMDEF	pndef_RippleCompFreq4;
extern	const	PRMDEF	pndef_RippleCompTrq4;
extern	const	PRMDEF	pndef_RippleCompPhase4;
extern	const	PRMDEF	pndef_WearkSw;
extern	const	PRMDEF	pndef_kv;
extern	const	PRMDEF	pndef_tv;
extern	const	PRMDEF	pndef_idlim;
extern	const	PRMDEF	pndef_vmax;
extern	const	PRMDEF	pndef_vmaxid;
extern	const	PRMDEF	pndef_vpnavg;
extern	const	PRMDEF	pndef_poweroffchk;
extern	const	PRMDEF	pndef_powerofffiltime;
extern	const	PRMDEF	pndef_ovlvl;
extern	const	PRMDEF	pndef_regonlvl;
extern	const	PRMDEF	pndef_regoffhys;
extern	const	PRMDEF	pndef_uvlvl;
extern	const	PRMDEF	pndef_uvfil;
extern	const	PRMDEF	pndef_UvWrnLvl;
extern	const	PRMDEF	pndef_MaxspdTun;
extern	const	PRMDEF	pndef_Icmu;
extern	const	PRMDEF	pndef_PosJump;
extern	const	PRMDEF	pndef_MotorNum;
extern	const	PRMDEF	pndef_EncoderType;
extern	const	PRMDEF	pndef_EncZeroPhase;
extern	const	PRMDEF	pndef_PosOutputs2l;
extern	const	PRMDEF	pndef_PosOutputs2h;
extern	const	PRMDEF	pndef_IncEncBit;
extern	const	PRMDEF	pndef_FaTestControl;
extern	const	PRMDEF	pndef_Testpassword;
extern	const	PRMDEF	pndef_password;
extern	const	PRMDEF	pndef_SnL;
extern	const	PRMDEF	pndef_SnH;
extern	const	PRMDEF	pndef_PrCmdSet;
extern	const	PRMDEF	pndef_PrModeSet;
extern	const	PRMDEF	pndef_PrEndSet;
extern	const	PRMDEF	pndef_PrStartSet;
extern	const	PRMDEF	pndef_PrCommSet;
extern	const	PRMDEF	pndef_PathPlan1L;
extern	const	PRMDEF	pndef_PathPlan1H;
extern	const	PRMDEF	pndef_PathPlan2L;
extern	const	PRMDEF	pndef_PathPlan2H;
extern	const	PRMDEF	pndef_PathPlan3L;
extern	const	PRMDEF	pndef_PathPlan3H;
extern	const	PRMDEF	pndef_PathPlan4L;
extern	const	PRMDEF	pndef_PathPlan4H;
extern	const	PRMDEF	pndef_PathPlan5L;
extern	const	PRMDEF	pndef_PathPlan5H;
extern	const	PRMDEF	pndef_PathPlan6L;
extern	const	PRMDEF	pndef_PathPlan6H;
extern	const	PRMDEF	pndef_PathPlan7L;
extern	const	PRMDEF	pndef_PathPlan7H;
extern	const	PRMDEF	pndef_PathPlan8L;
extern	const	PRMDEF	pndef_PathPlan8H;
extern	const	PRMDEF	pndef_PathPlan9L;
extern	const	PRMDEF	pndef_PathPlan9H;
extern	const	PRMDEF	pndef_PathPlan10L;
extern	const	PRMDEF	pndef_PathPlan10H;
extern	const	PRMDEF	pndef_PathPlan11L;
extern	const	PRMDEF	pndef_PathPlan11H;
extern	const	PRMDEF	pndef_PathPlan12L;
extern	const	PRMDEF	pndef_PathPlan12H;
extern	const	PRMDEF	pndef_PathPlan13L;
extern	const	PRMDEF	pndef_PathPlan13H;
extern	const	PRMDEF	pndef_PathPlan14L;
extern	const	PRMDEF	pndef_PathPlan14H;
extern	const	PRMDEF	pndef_PathPlan15L;
extern	const	PRMDEF	pndef_PathPlan15H;
extern	const	PRMDEF	pndef_PathPlan16L;
extern	const	PRMDEF	pndef_PathPlan16H;
extern	const	PRMDEF	pndef_PathPlan17L;
extern	const	PRMDEF	pndef_PathPlan17H;
extern	const	PRMDEF	pndef_PathPlan18L;
extern	const	PRMDEF	pndef_PathPlan18H;
extern	const	PRMDEF	pndef_PathPlan19L;
extern	const	PRMDEF	pndef_PathPlan19H;
extern	const	PRMDEF	pndef_PathPlan20L;
extern	const	PRMDEF	pndef_PathPlan20H;
extern	const	PRMDEF	pndef_PathPlan21L;
extern	const	PRMDEF	pndef_PathPlan21H;
extern	const	PRMDEF	pndef_PathPlan22L;
extern	const	PRMDEF	pndef_PathPlan22H;
extern	const	PRMDEF	pndef_PathPlan23L;
extern	const	PRMDEF	pndef_PathPlan23H;
extern	const	PRMDEF	pndef_PathPlan24L;
extern	const	PRMDEF	pndef_PathPlan24H;
extern	const	PRMDEF	pndef_PathPlan25L;
extern	const	PRMDEF	pndef_PathPlan25H;
extern	const	PRMDEF	pndef_PathPlan26L;
extern	const	PRMDEF	pndef_PathPlan26H;
extern	const	PRMDEF	pndef_PathPlan27L;
extern	const	PRMDEF	pndef_PathPlan27H;
extern	const	PRMDEF	pndef_PathPlan28L;
extern	const	PRMDEF	pndef_PathPlan28H;
extern	const	PRMDEF	pndef_PathPlan29L;
extern	const	PRMDEF	pndef_PathPlan29H;
extern	const	PRMDEF	pndef_PathPlan30L;
extern	const	PRMDEF	pndef_PathPlan30H;
extern	const	PRMDEF	pndef_AccDecT0;
extern	const	PRMDEF	pndef_AccDecT1;
extern	const	PRMDEF	pndef_AccDecT2;
extern	const	PRMDEF	pndef_AccDecT3;
extern	const	PRMDEF	pndef_AccDecT4;
extern	const	PRMDEF	pndef_AccDecT5;
extern	const	PRMDEF	pndef_AccDecT6;
extern	const	PRMDEF	pndef_AccDecT7;
extern	const	PRMDEF	pndef_DelayT0;
extern	const	PRMDEF	pndef_DelayT1;
extern	const	PRMDEF	pndef_DelayT2;
extern	const	PRMDEF	pndef_DelayT3;
extern	const	PRMDEF	pndef_DelayT4;
extern	const	PRMDEF	pndef_DelayT5;
extern	const	PRMDEF	pndef_DelayT6;
extern	const	PRMDEF	pndef_DelayT7;
extern	const	PRMDEF	pndef_Spd0;
extern	const	PRMDEF	pndef_Spd1;
extern	const	PRMDEF	pndef_Spd2;
extern	const	PRMDEF	pndef_Spd3;
extern	const	PRMDEF	pndef_Spd4;
extern	const	PRMDEF	pndef_Spd5;
extern	const	PRMDEF	pndef_Spd6;
extern	const	PRMDEF	pndef_Spd7;
extern	const	PRMDEF	pndef_Tpdo1;
extern	const	PRMDEF	pndef_Tpdo1Map1L;
extern	const	PRMDEF	pndef_Tpdo1Map1H;
extern	const	PRMDEF	pndef_Tpdo1Map2L;
extern	const	PRMDEF	pndef_Tpdo1Map2H;
extern	const	PRMDEF	pndef_Tpdo1Map3L;
extern	const	PRMDEF	pndef_Tpdo1Map3H;
extern	const	PRMDEF	pndef_Tpdo1Map4L;
extern	const	PRMDEF	pndef_Tpdo1Map4H;
extern	const	PRMDEF	pndef_Tpdo1StationL;
extern	const	PRMDEF	pndef_Tpdo1StationH;
extern	const	PRMDEF	pndef_Tpdo1Type;
extern	const	PRMDEF	pndef_Tpdo1InTime;
extern	const	PRMDEF	pndef_Tpdo1EventTime;
extern	const	PRMDEF	pndef_Tpdo2;
extern	const	PRMDEF	pndef_Tpdo2Map1L;
extern	const	PRMDEF	pndef_Tpdo2Map1H;
extern	const	PRMDEF	pndef_Tpdo2Map2L;
extern	const	PRMDEF	pndef_Tpdo2Map2H;
extern	const	PRMDEF	pndef_Tpdo2Map3L;
extern	const	PRMDEF	pndef_Tpdo2Map3H;
extern	const	PRMDEF	pndef_Tpdo2Map4L;
extern	const	PRMDEF	pndef_Tpdo2Map4H;
extern	const	PRMDEF	pndef_Tpdo2StationL;
extern	const	PRMDEF	pndef_Tpdo2StationH;
extern	const	PRMDEF	pndef_Tpdo2Type;
extern	const	PRMDEF	pndef_Tpdo2InTime;
extern	const	PRMDEF	pndef_Tpdo2EventTime;
extern	const	PRMDEF	pndef_Tpdo3;
extern	const	PRMDEF	pndef_Tpdo3Map1L;
extern	const	PRMDEF	pndef_Tpdo3Map1H;
extern	const	PRMDEF	pndef_Tpdo3Map2L;
extern	const	PRMDEF	pndef_Tpdo3Map2H;
extern	const	PRMDEF	pndef_Tpdo3Map3L;
extern	const	PRMDEF	pndef_Tpdo3Map3H;
extern	const	PRMDEF	pndef_Tpdo3Map4L;
extern	const	PRMDEF	pndef_Tpdo3Map4H;
extern	const	PRMDEF	pndef_Tpdo3StationL;
extern	const	PRMDEF	pndef_Tpdo3StationH;
extern	const	PRMDEF	pndef_Tpdo3Type;
extern	const	PRMDEF	pndef_Tpdo3InTime;
extern	const	PRMDEF	pndef_Tpdo3EventTime;
extern	const	PRMDEF	pndef_Tpdo4;
extern	const	PRMDEF	pndef_Tpdo4Map1L;
extern	const	PRMDEF	pndef_Tpdo4Map1H;
extern	const	PRMDEF	pndef_Tpdo4Map2L;
extern	const	PRMDEF	pndef_Tpdo4Map2H;
extern	const	PRMDEF	pndef_Tpdo4Map3L;
extern	const	PRMDEF	pndef_Tpdo4Map3H;
extern	const	PRMDEF	pndef_Tpdo4Map4L;
extern	const	PRMDEF	pndef_Tpdo4Map4H;
extern	const	PRMDEF	pndef_Tpdo4StationL;
extern	const	PRMDEF	pndef_Tpdo4StationH;
extern	const	PRMDEF	pndef_Tpdo4Type;
extern	const	PRMDEF	pndef_Tpdo4InTime;
extern	const	PRMDEF	pndef_Tpdo4EventTime;
extern	const	PRMDEF	pndef_RPDO1;
extern	const	PRMDEF	pndef_RPDO1Map1L;
extern	const	PRMDEF	pndef_RPDO1Map1H;
extern	const	PRMDEF	pndef_RPDO1Map2L;
extern	const	PRMDEF	pndef_RPDO1Map2H;
extern	const	PRMDEF	pndef_RPDO1Map3L;
extern	const	PRMDEF	pndef_RPDO1Map3H;
extern	const	PRMDEF	pndef_RPDO1Map4L;
extern	const	PRMDEF	pndef_RPDO1Map4H;
extern	const	PRMDEF	pndef_RPDO1StationL;
extern	const	PRMDEF	pndef_RPDO1StationH;
extern	const	PRMDEF	pndef_RPDO1Type;
extern	const	PRMDEF	pndef_RPDO2;
extern	const	PRMDEF	pndef_RPDO2Map1L;
extern	const	PRMDEF	pndef_RPDO2Map1H;
extern	const	PRMDEF	pndef_RPDO2Map2L;
extern	const	PRMDEF	pndef_RPDO2Map2H;
extern	const	PRMDEF	pndef_RPDO2Map3L;
extern	const	PRMDEF	pndef_RPDO2Map3H;
extern	const	PRMDEF	pndef_RPDO2Map4L;
extern	const	PRMDEF	pndef_RPDO2Map4H;
extern	const	PRMDEF	pndef_RPDO2StationL;
extern	const	PRMDEF	pndef_RPDO2StationH;
extern	const	PRMDEF	pndef_RPDO2Type;
extern	const	PRMDEF	pndef_RPDO3;
extern	const	PRMDEF	pndef_RPDO3Map1L;
extern	const	PRMDEF	pndef_RPDO3Map1H;
extern	const	PRMDEF	pndef_RPDO3Map2L;
extern	const	PRMDEF	pndef_RPDO3Map2H;
extern	const	PRMDEF	pndef_RPDO3Map3L;
extern	const	PRMDEF	pndef_RPDO3Map3H;
extern	const	PRMDEF	pndef_RPDO3Map4L;
extern	const	PRMDEF	pndef_RPDO3Map4H;
extern	const	PRMDEF	pndef_RPDO3StationL;
extern	const	PRMDEF	pndef_RPDO3StationH;
extern	const	PRMDEF	pndef_RPDO3Type;
extern	const	PRMDEF	pndef_RPDO4;
extern	const	PRMDEF	pndef_RPDO4Map1L;
extern	const	PRMDEF	pndef_RPDO4Map1H;
extern	const	PRMDEF	pndef_RPDO4Map2L;
extern	const	PRMDEF	pndef_RPDO4Map2H;
extern	const	PRMDEF	pndef_RPDO4Map3L;
extern	const	PRMDEF	pndef_RPDO4Map3H;
extern	const	PRMDEF	pndef_RPDO4Map4L;
extern	const	PRMDEF	pndef_RPDO4Map4H;
extern	const	PRMDEF	pndef_RPDO4StationL;
extern	const	PRMDEF	pndef_RPDO4StationH;
extern	const	PRMDEF	pndef_RPDO4Type;
extern	const	PRMDEF	pndef_EmcyEnL;
extern	const	PRMDEF	pndef_EmcyEnH;
extern	const	PRMDEF	pndef_HeartConsumerL;
extern	const	PRMDEF	pndef_HeartConsumerH;
extern	const	PRMDEF	pndef_HeartProducter;
extern	const	PRMDEF	pndef_Guardtime;
extern	const	PRMDEF	pndef_lifetime;
extern	const	PRMDEF	pndef_CanControl;
extern	const	PRMDEF	pndef_CanControl2;
extern	const	PRMDEF	pndef_Cia402Test;
extern	const	PRMDEF	pndef_CANSpdCoeffL;
extern	const	PRMDEF	pndef_CANSpdCoeffH;
extern	const	PRMDEF	pndef_B04;
extern	const	PRMDEF	pndef_B05;
extern	const	PRMDEF	pndef_B06;
extern	const	PRMDEF	pndef_B07;
extern	const	PRMDEF	pndef_B08;
extern	const	PRMDEF	pndef_B09;
extern	const	PRMDEF	pndef_B0A;
extern	const	PRMDEF	pndef_B0B;
extern	const	PRMDEF	pndef_B0C;
extern	const	PRMDEF	pndef_B0D;
extern	const	PRMDEF	pndef_OBJ_6040;
extern	const	PRMDEF	pndef_OBJ_605A;
extern	const	PRMDEF	pndef_OBJ_605D;
extern	const	PRMDEF	pndef_OBJ_6060;
extern	const	PRMDEF	pndef_OBJ_6065_L;
extern	const	PRMDEF	pndef_OBJ_6065_H;
extern	const	PRMDEF	pndef_OBJ_6067_L;
extern	const	PRMDEF	pndef_OBJ_6067_H;
extern	const	PRMDEF	pndef_OBJ_6068_L;
extern	const	PRMDEF	pndef_OBJ_6068_H;
extern	const	PRMDEF	pndef_OBJ_606D;
extern	const	PRMDEF	pndef_OBJ_606E;
extern	const	PRMDEF	pndef_OBJ_606F;
extern	const	PRMDEF	pndef_OBJ_6070;
extern	const	PRMDEF	pndef_OBJ_6071;
extern	const	PRMDEF	pndef_OBJ_6072;
extern	const	PRMDEF	pndef_OBJ_607A_L;
extern	const	PRMDEF	pndef_OBJ_607A_H;
extern	const	PRMDEF	pndef_OBJ_607C_L;
extern	const	PRMDEF	pndef_OBJ_607C_H;
extern	const	PRMDEF	pndef_OBJ_607D_01_L;
extern	const	PRMDEF	pndef_OBJ_607D_01_H;
extern	const	PRMDEF	pndef_OBJ_607D_02_L;
extern	const	PRMDEF	pndef_OBJ_607D_02_H;
extern	const	PRMDEF	pndef_OBJ_607E;
extern	const	PRMDEF	pndef_OBJ_607F_L;
extern	const	PRMDEF	pndef_OBJ_607F_H;
extern	const	PRMDEF	pndef_OBJ_6080_L;
extern	const	PRMDEF	pndef_OBJ_6080_H;
extern	const	PRMDEF	pndef_OBJ_6081_L;
extern	const	PRMDEF	pndef_OBJ_6081_H;
extern	const	PRMDEF	pndef_OBJ_6083_L;
extern	const	PRMDEF	pndef_OBJ_6083_H;
extern	const	PRMDEF	pndef_OBJ_6084_L;
extern	const	PRMDEF	pndef_OBJ_6084_H;
extern	const	PRMDEF	pndef_OBJ_6085_L;
extern	const	PRMDEF	pndef_OBJ_6085_H;
extern	const	PRMDEF	pndef_OBJ_6087_L;
extern	const	PRMDEF	pndef_OBJ_6087_H;
extern	const	PRMDEF	pndef_OBJ_6091_01_L;
extern	const	PRMDEF	pndef_OBJ_6091_01_H;
extern	const	PRMDEF	pndef_OBJ_6091_02_L;
extern	const	PRMDEF	pndef_OBJ_6091_02_H;
extern	const	PRMDEF	pndef_OBJ_6098;
extern	const	PRMDEF	pndef_OBJ_6099_01_L;
extern	const	PRMDEF	pndef_OBJ_6099_01_H;
extern	const	PRMDEF	pndef_OBJ_6099_02_L;
extern	const	PRMDEF	pndef_OBJ_6099_02_H;
extern	const	PRMDEF	pndef_OBJ_609A_L;
extern	const	PRMDEF	pndef_OBJ_609A_H;
extern	const	PRMDEF	pndef_OBJ_60B0_L;
extern	const	PRMDEF	pndef_OBJ_60B0_H;
extern	const	PRMDEF	pndef_OBJ_60B1_L;
extern	const	PRMDEF	pndef_OBJ_60B1_H;
extern	const	PRMDEF	pndef_OBJ_60B2_L;
extern	const	PRMDEF	pndef_OBJ_60B2_H;
extern	const	PRMDEF	pndef_OBJ_60B8;
extern	const	PRMDEF	pndef_OBJ_60C1_01_L;
extern	const	PRMDEF	pndef_OBJ_60C1_01_H;
extern	const	PRMDEF	pndef_OBJ_60C2_01;
extern	const	PRMDEF	pndef_OBJ_60C2_02;
extern	const	PRMDEF	pndef_OBJ_60C5_L;
extern	const	PRMDEF	pndef_OBJ_60C5_H;
extern	const	PRMDEF	pndef_OBJ_60C6_L;
extern	const	PRMDEF	pndef_OBJ_60C6_H;
extern	const	PRMDEF	pndef_OBJ_60E0;
extern	const	PRMDEF	pndef_OBJ_60E1;
extern	const	PRMDEF	pndef_OBJ_60FF_L;
extern	const	PRMDEF	pndef_OBJ_60FF_H;
extern	const	PRMDEF	pndef_typm_e_1;
extern	const	PRMDEF	pndef_encver_1;
extern	const	PRMDEF	pndef_motw_1;
extern	const	PRMDEF	pndef_bit_dp_1;
extern	const	PRMDEF	pndef_limmlt_1;
extern	const	PRMDEF	pndef_vrat_max_1;
extern	const	PRMDEF	pndef_oslv_pol_1;
extern	const	PRMDEF	pndef_rattrq_1;
extern	const	PRMDEF	pndef_maxtrq_1;
extern	const	PRMDEF	pndef_irat_1;
extern	const	PRMDEF	pndef_imax_1;
extern	const	PRMDEF	pndef_emfcmp_1;
extern	const	PRMDEF	pndef_jmot_1;
extern	const	PRMDEF	pndef_motr_1;
extern	const	PRMDEF	pndef_motl_1;
extern	const	PRMDEF	pndef_bastrq_1;
extern	const	PRMDEF	pndef_midtrq_1;
extern	const	PRMDEF	pndef_midolt_1;
extern	const	PRMDEF	pndef_mtrq2_1;
extern	const	PRMDEF	pndef_mtolt2_1;
extern	const	PRMDEF	pndef_phscmpM1_1;
extern	const	PRMDEF	pndef_ppitch_1;
extern	const	PRMDEF	pndef_motlq0_1;
extern	const	PRMDEF	pndef_motlq1_1;
extern	const	PRMDEF	pndef_exp_trat_jmot_1;
extern	const	PRMDEF	pndef_exp_motw_spd_1;
extern	const	PRMDEF	pndef_fbit_fdp_1;
extern	const	PRMDEF	pndef_poleoffset_1;
extern	const	PRMDEF	pndef_motresfrq_1;
extern	const	PRMDEF	pndef_phscmpM2_1;
extern	const	PRMDEF	pndef_flg_wf_1;
extern	const	PRMDEF	pndef_drvno;
extern	const	PRMDEF	pndef_ampw;
extern	const	PRMDEF	pndef_VoltType;
extern	const	PRMDEF	pndef_irats;
extern	const	PRMDEF	pndef_imaxs;
extern	const	PRMDEF	pndef_TempOH;
extern	const	PRMDEF	pndef_ibs_md;
extern	const	PRMDEF	pndef_imdt_mxt;
extern	const	PRMDEF	pndef_ratbt_mt;
extern	const	PRMDEF	pndef_ratmtt_2;
extern	const	PRMDEF	pndef_ratmt2_os;
extern	const	PRMDEF	pndef_reger;
extern	const	PRMDEF	pndef_wre;
extern	const	PRMDEF	pndef_dbr;
extern	const	PRMDEF	pndef_wdb;
extern	const	PRMDEF	pndef_pnvoltgn;
extern	const	PRMDEF	pndef_vdetadfil;
extern	const	PRMDEF	pndef_pnzero;
extern	const	PRMDEF	pndef_pngain;
extern	const	PRMDEF	pndef_vdefilsw;
extern	const	PRMDEF	pndef_almmsk1;
extern	const	PRMDEF	pndef_almmsk2;
extern	const	PRMDEF	pndef_MosPump;
extern	const	PRMDEF	pndef_syssw1;
extern	const	PRMDEF	pndef_syssw2;
extern	const	PRMDEF	pndef_syssw3;
extern	const	PRMDEF	pndef_spgfail;
extern	const	PRMDEF	pndef_ifil;
extern	const	PRMDEF	pndef_ignd;
extern	const	PRMDEF	pndef_ignq;
extern	const	PRMDEF	pndef_kid;
extern	const	PRMDEF	pndef_kiq;
extern	const	PRMDEF	pndef_limintd;
extern	const	PRMDEF	pndef_limintq;
extern	const	PRMDEF	pndef_shant1;
extern	const	PRMDEF	pndef_vrevgn;
extern	const	PRMDEF	pndef_pwmf;
extern	const	PRMDEF	pndef_odt_c;
extern	const	PRMDEF	pndef_ObsGain;
extern	const	PRMDEF	pndef_ad_prm3;
extern	const	PRMDEF	pndef_ad_prm4;
extern	const	PRMDEF	pndef_phscmp;
extern	const	PRMDEF	pndef_mtovcnt;
extern	const	PRMDEF	pndef_ipg_rwt;
extern	const	PRMDEF	pndef_fbfil2;
extern	const	PRMDEF	pndef_MLess_vrat_max;
extern	const	PRMDEF	pndef_MLess_oslv_pol;
extern	const	PRMDEF	pndef_Mless_jmot;
extern	const	PRMDEF	pndef_Mless_exp_spd_jmot;
extern	const	PRMDEF	pndef_Mless_PlantModel;
extern	const	PRMDEF	pndef_Dm;
extern	const	PRMDEF	pndef_Dl;
extern	const	PRMDEF	pndef_frml;
extern	const	PRMDEF	pndef_ztrml;
extern	const	PRMDEF	pndef_jbrate;
extern	const	PRMDEF	pndef_fnb;
extern	const	PRMDEF	pndef_zb;
extern	const	PRMDEF	pndef_VfAccTime;
extern	const	PRMDEF	pndef_VfSetFreq;
extern	const	PRMDEF	pndef_VfSetVolt;
extern	const	PRMDEF	pndef_usrchk;
extern	const	PRMDEF	pndef_syschk;
extern	const	PRMDEF	pndef_typm_e;
extern	const	PRMDEF	pndef_encver;
extern	const	PRMDEF	pndef_motw;
extern	const	PRMDEF	pndef_bit_dp;
extern	const	PRMDEF	pndef_limmlt;
extern	const	PRMDEF	pndef_vrat_max;
extern	const	PRMDEF	pndef_oslv_pol;
extern	const	PRMDEF	pndef_rattrq;
extern	const	PRMDEF	pndef_maxtrq;
extern	const	PRMDEF	pndef_irat;
extern	const	PRMDEF	pndef_imax;
extern	const	PRMDEF	pndef_emfcmp;
extern	const	PRMDEF	pndef_jmot;
extern	const	PRMDEF	pndef_motr;
extern	const	PRMDEF	pndef_motl;
extern	const	PRMDEF	pndef_bastrq;
extern	const	PRMDEF	pndef_midtrq;
extern	const	PRMDEF	pndef_midolt;
extern	const	PRMDEF	pndef_mtrq2;
extern	const	PRMDEF	pndef_mtolt2;
extern	const	PRMDEF	pndef_phscmpM1;
extern	const	PRMDEF	pndef_ppitch;
extern	const	PRMDEF	pndef_motlq0;
extern	const	PRMDEF	pndef_motlq1;
extern	const	PRMDEF	pndef_exp_trat_jmot;
extern	const	PRMDEF	pndef_exp_motw_spd;
extern	const	PRMDEF	pndef_fbit_fdp;
extern	const	PRMDEF	pndef_poleoffset;
extern	const	PRMDEF	pndef_motresfrq;
extern	const	PRMDEF	pndef_phscmpM2;
extern	const	PRMDEF	pndef_flg_wf;
extern	const	PRMDEF	pndef_AutoAIAdj;
/*--------------------------------------------------------------------------------------------------*/



/****************************************************************************************************/
/*																									*/
/*		参数管理表Extern声明																		*/
/*																									*/
/****************************************************************************************************/
#if		OPENSW_PRMDEF >= 1
#pragma location =".PnPrmTbl"
#endif
extern  const PRMTBL PnPrmTbl[];				/* パラメータ管理テーブル							*/
#if		OPENSW_PRMDEF >= 1
#pragma location =default
#endif
/*--------------------------------------------------------------------------------------------------*/
extern  const USHORT PnPrmTblEntNum;			/* パラメータ管理テーブル登録個数					*/
/*--------------------------------------------------------------------------------------------------*/
#if		OPENSW_PRMDEF >= 1
#pragma location =".PnPrmTblUser"
#endif
extern  const PRMTBL PnPrmTblUser[];			/* パラメータ管理テーブル							*/
#if		OPENSW_PRMDEF >= 1
#pragma location =default
#endif
/*--------------------------------------------------------------------------------------------------*/
extern  const USHORT PnPrmTblUserEntNum;		/* パラメータ管理テーブル登録個数					*/
/*--------------------------------------------------------------------------------------------------*/
/*		Define Entry Number																			*/
/*--------------------------------------------------------------------------------------------------*/
#if		OPENSW_PRMDEF == 0
#define PNPRMTBL_ENTNUM		PnPrmTblEntNum
#else
#define PNPRMTBL_ENTNUM		(PnPrmTblEntNum + PnPrmTblUserEntNum)
#endif
/*--------------------------------------------------------------------------------------------------*/


#endif







/***************************************** end of file **********************************************/
