/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
*
* File Name          : Mot05_VarDef.h
*
* Version            : V0.1
* Date               : 2024
***********************************************************************************************/

#include "Main.h"
#include "MlibSvc.h"
#ifndef Mot05_VarDef_H
#define Mot05_VarDef_H
#include "Mot50_DIDO.h"
#define NETID_NONE				0
#define SFTID_EXIST				1   
  
/*******************************************ID设置 考虑删除*************************************/
#define	CCSW_HWID				HWID_SGDV			    // Hardware ID
#define	CCSW_MPID				MPID_SGDX				// MicroProgram ID
#define	CCSW_CPUID				CPUID_STM32F745			// CPU ID
#define	CCSW_EEPID				EEPID_AT24C64N			// EEPROM ID
#define	CCSW_MENCID				MENCID_SERIAL			// 支持的编码器类型
#define	CCSW_NETID			NETID_NONE
#define	CCSW_CMDID			CMDID_NONE			        // Network ID
#define	CCSW_SFTID			SFTID_EXIST				    // Command ID
#define	CCSW_FBKID			FBKID_EXIST                 // Safety ID
  
#define CCSW_ADTYPE			ADTYPE_SGDS				    // Current A/D Type
#define	CCSW_ADINIT			ADINIT_STANDARD				// Current A/D Initialize Type
#define	CCSW_MSGTYPE		MSGTYPE_MEMOBUS			    // Message Protocol Type
#define	CCSW_BTPRG			SGDV_BOOT					// SGDV BootProgram

/*******************************************顺序控制指令*************************************/
typedef struct	CMD_SEQBITS_ {
	UINT	ServoOn			:1;
    UINT    ServoOnTmp      :1;             // 伺服On 时信号临时保存
    UINT    ServoOffDec     :1;             // 伺服OFF 减速停机标志
	UINT	SenserOn		:1;
	UINT	AlmReset		:1;
	UINT	WrnReset		:1;
	UINT	PolDetect		:1;
	UINT	BrkRelease		:1;
	UINT	EnbExtPTrqLmt	:1;
	UINT	EnbExtNTrqLmt	:1;
 	UINT	PositiveOT		:1;
	UINT	NegativeOT		:1;
 	UINT	ActModOn		:1;
    UINT    ServoOffDecM    :1;           // 伺服OFF 减速停机标志
	UINT	ReservedEx		:2;
} CMD_SEQBITS;

/*******************************************控制指令*************************************/
typedef struct	CMD_CTRLBITS_ {
	UINT	ModSel			:2;
	UINT	EnbPCtrl		:1;
	UINT	ClrPosErr		:1;
	UINT	ClrPosIntg		:1;
	UINT	Reserved57		:3;
 	UINT	SelBank			:4;
    UINT	AbsPosLimitPot  :1;
    UINT    AbsPosLimitNot  :1;
	UINT	Reserved1215	:2;
} CMD_CTRLBITS;

/*******************************************锁存命令*************************************/
 typedef struct	CMD_LTBITS_ {
	UINT	SelEncCphs		:1;
	UINT	SelEncExt1		:1;
	UINT	SelEncExt2		:1;
	UINT	SelEncExt3		:1;
	UINT	ReqCPhase		:1;
	UINT	ReqExtSig1		:1;
	UINT	ReqExtSig2		:1;
	UINT	ReqExtSig3		:1;
} CMD_LTBITS;
 
typedef struct	RSP_SEQBITS_ {
    UINT    AlmDetected     :1;     //未用
    UINT    WrnDetected     :1;     //未用
    UINT    AlmResetComp    :1;     //未用
    UINT    WrnResetComp    :1;     //未用
    UINT    ServoOnComp     :1;     //未用
    UINT    SensOnComp      :1;     //未用
    UINT    PolDetComp      :1;     //未用
    UINT    BrkReleasing    :1;     //抱闸输出

    UINT    MainPowerOn     :1;     //主电源上电
    UINT    ServoReady      :1;     //伺服准备好
    UINT    MotorReady      :1;     //未用
    UINT    PowerOffflg     :1;     //伺服下电
    UINT    Reserve         :4;
} RSP_SEQBITS;


 typedef struct	RSP_LTBITS_ {
	UINT	CPhaseReqLvl	:1;
	UINT	ExtSig1ReqLvl	:1;
	UINT	ExtSig2ReqLvl	:1;
	UINT	ExtSig3ReqLvl	:1;
	UINT	CPhaseComp		:1;
	UINT	ExtSig1Comp		:1;
	UINT	ExtSig2Comp		:1;
	UINT	ExtSig3Comp		:1;
} RSP_LTBITS;
 typedef struct	RSP_SIGNLBITS_ {
	UINT	DEC_Sig			:1;
	UINT	P_OT_Sig		:1;
	UINT	N_OT_Sig		:1;
	UINT	EXT1_Sig		:1;
	UINT	EXT2_Sig		:1;
	UINT	EXT3_Sig		:1;
	UINT	EMG_Sig			:1;
}RSP_SIGNLBITS;   
 
typedef struct
{
    union {
    UCHAR	CData;
        struct {
        UINT	Prm			:1;
        UINT	PrmReg		:1;
        UINT	OpeReg		:1;
        UINT	OpeRegAll	:1;
        UINT	EngReg		:1;
        UINT	TrcReg		:1;
        UINT	SPrmReg		:1;
        UINT	Spare1		:1;
        } f;
    } FunA;
    union {
    UCHAR	CData;
        struct {
        UINT	Prm			:1;
        UINT	PrmReg		:1;
        UINT	OpeReg		:1;
        UINT	OpeRegAll	:1;
        UINT	EngReg		:1;
        UINT	TrcReg		:1;
        UINT	SPrmReg		:1;
        UINT	Spare1		:1;
        } f;
    } FunB;
} RNDWRTD;
extern	RNDWRTD		RndWrtDisable;
  
  
  
  
  
  
  
enum	BITNO_BIN {
		BITNO_BI_Inhibit            = 0x00,
		BITNO_BI_DecSignal          ,
		BITNO_BI_Pcl				,
		BITNO_BI_Ncl		        ,
		BITNO_BI_GainSel0			,
		BITNO_BI_GainSel1	        ,
		BITNO_BI_Psel               ,
		BITNO_BI_SpareBit07         ,
};
  
  
typedef	struct	{
    CMD_CTRLBITS	Ctrl;               // 控制指令
    CMD_SEQBITS		Seq;                // 顺序控制指令
    CMD_LTBITS		Lt;                 // 锁存请求     未用
/*----------------------------------------------------------------------------------------------*/
    struct {
        UINT	Inhibit 			:1; /* 0x00 : INHIBIT Signal                                */
        UINT	DecSignal           :1; /* 0x01 : DEC Signal    减速用限位开关输入信号                 */
        UINT	TlimitSel			:1; /* 0x02 : 转矩限制选择                                     */
        UINT	PossErr 	        :1; /* 0x03 : 位置偏差标志                                   */
        UINT	GainSel0            :1; /* 0x04 : 增益切换                                      */
        UINT	GainSel1            :1; // 0x05 : 增益编号
        UINT	Psel                :1; // 0x06 : 指令脉冲输入倍频切换(/PSEL)
        UINT	PerClrSignal        :1; // 0x07 : 脉冲偏差清除
        UINT	LstCphaLatch        :1; // 0x08 : 上次C相锁存请求级别
        UINT	LstExt1Latch        :1; // 0x09 : 上次外部锁存1请求级别
        UINT	LstExt2Latch        :1; // 0x0A : 上次外部锁存2请求级别
        UINT	LstExt3Latch        :1; // 0x0B : 上次外部锁存3请求级别
        UINT	OrgPulseEn          :1; // 0x0C : 原点回零脉冲开关
        UINT	ORGEn               :1; // 0x0D : 原点使能
        UINT	ORGS                :1; // 0x0E : 原点开关
        UINT	SpareBit0F          :1; /* 0x0F : Reserved                                      */
        UINT	SpareBit10          :1; /* 0x10 : Reserved                                      */
        UINT	SpareBit11          :1; /* 0x11 : Reserved                                      */
        UINT	SamePeriodFlg	    :1; // 0x12 : 正在同步的标志
        UINT	CmdUpdate	        :1; // 0x13 : 同步控制：命令更新请求
        UINT	RspUpdate          	:1; // 0x14 : 同步控制：响应创建请求
        UINT    SpareBit15          :1; /* 0x15 : Reserved                                      */
        UINT    SpareBit16          :1; /* 0x16 : Reserved                                      */
        UINT    SpareBit17          :1; /* 0x17 : Reserved                                      */
/*----------------------------------------------------------------------------------------------*/
        UINT    SpareBit18          :1; /* 0x18 : Reserved                                      */
        UINT    SpareBit19          :1; /* 0x19 : Reserved                                      */
        UINT    SpareBit1A          :1; /* 0x1A : Reserved                                      */
        UINT    SpareBit1B          :1; /* 0x1B : Reserved                                      */
        UINT    SpareBit1C          :1; /* 0x1C : Reserved                                      */
        UINT    SpareBit1D          :1; /* 0x1D : Reserved                                      */
        UINT    SpareBit1E          :1; /* 0x1E : Reserved                                      */
        UINT    SpareBit1F          :1; /* 0x1F : Reserved                                      */
    } Sv ;
    UCHAR	BaseEnable;         // 使能标志:伺服控制用使能状态
    UCHAR	PerClrCmd;          // 位置偏差清除指令:伺服OFF、报警、电平清除
    UCHAR	PerClrSignal;       // 位置偏差清除电平信号有效,仅电平模式且与设定电平一致时为1
    UCHAR	PicvClrCmd;         // 位置积分控制值清除命令
} BINF;
  
 #define	NETREQ_CYCLE_NUMMAX		4000/125		/* NET要求最大等待周期（传输周期/控制周期）       */
                                                  
typedef	struct
{
    BINF	f;                  /* 位信号                                              */
    BINF	fl;                 /* 位信号上回值                                          */
    USHORT	NetCtrlMcmd;        // 来自控制模式信息的指令
    UCHAR	GselNum;            /* 手动增益切换的增益号   从IO口读取                      */
    LONG	TrqRef;             /* 转矩指令                 [2^24/MaxTrq]          */
    LONG	TrqFFC;             /* 模拟量输入转矩前馈指令  [2^24/MaxTrq]               */
    LONG	SpdRef;             /* 速度指令                 [2^24/OvrSpd]               */
    LONG	SpdFFC;             /* 模拟量输入速度前馈指令  [2^24/OvrSpd]               */

    LONG	SpdLmt;             // 速度制限         [2^24/OvrSpd]
    LONG	PosTrqLmt;          // 正向扭矩限制
    LONG	NegTrqLmt;          // 反向扭矩限制
    LONG	SpdRefAd;           // 速度指令AD输入         [2^24/OvrSpd]
    LONG	TrqRefAd;           // 转矩指令AD输入         [2^24/MaxTrq]
    LONG	FwTrqLmt;           /* Forward Torque Limit     [2^24/MaxTrq]               */
    LONG	RvTrqLmt;           /* Reverse Torque Limit     [2^24/MaxTrq]               */
    LONG    OTStatus;           // OT状态
 } BINV;
 typedef struct	{
	UINT	ExeMode			    :2;
	UINT	Coin			    :1;
	UINT	MotorMoving		    :1;
	UINT	ReachSpd		    :1;
	UINT	SpdClamp		    :1;
	UINT	TrqClamp		    :1;
	UINT	OpEnabled		    :1;
	UINT	SafetyStop		    :1;
    UINT    TorqReach           :1;
    UINT    Spare               :1;
    UINT    OrgC                :1;
    UINT    JOGP                :1;
    UINT    JOGN                :1;
	UINT	Reserved		    :2;
} RSP_CTRLBITS;
  
 typedef	struct	{
    RSP_CTRLBITS	Ctrl;                /* 控制状态                                             */
    struct {
        UINT	Den					:1;  /* 0x00 : Den Signal 位置指令传输完成(滤波后指令为0) */
        UINT	Near		        :1;  /* 0x01 : Near Signal 定位接近                         */
        UINT	PgAphase	        :1;  /* 0x02 : PgAphase Signal                              */
        UINT	PgBphase	        :1;  /* 0x03 : PgBphase Signal                              */
        UINT	PgCphase	        :1;  /* 0x04 : PgCphase Signal C相检出/未检出 固定750us，非位置模式由于清零只有125us    */
        UINT	PselA               :1;  /* 0x05 : 指令脉冲输入倍频切换响应(/PSELA )             */
        UINT	LowVel              :1;
        UINT	SpareBit07          :1;
    } Sv ;
    UCHAR	PerClrCmd;                  // 位置偏差清除指令:伺服OFF、报警、外部电平、时序控制  */
    UCHAR	PerClrEdge;                 /* 位置误差清除命令                 */
    UCHAR	OrgSrchFinish;              /* 原点搜索完毕，仅在原点搜索模式中完成时设TRUE         */
    UCHAR	SvonSpdLmtFlag;             /* 伺服使能时速度限制中Flag                               */
    UCHAR	BiasONFlag;                 /* 速度偏差ONFlag                               */
    UCHAR	ModeSWFlag;                 /* 自动P/PI控制切换Flag,TRUE:P控制,FALSE:PI控制           */
    UCHAR    PConActFlag;               // P控制动作中Flag                                   */
    UCHAR   InertiaTuning;              // 惯量辨识中Flag                                        */
    UCHAR   MFCModel;                   /* 执行中MFC模型                                     */
    UCHAR   TrcPerrClr;                 /* Position Error Clear Input On                        */
    UCHAR   CoinLatch;                  /* COIN锁存(无位置指令后任一次定位完成)                    */
    UCHAR   neri_calc_on;               /* 速度积分动作停止判断                               */
    UCHAR   MfcStop;                    /* MFC停止，辅助功能和Table运转时设置                    */
    UCHAR   OTStatus;                   /* 超程限位处理                                         */
    UCHAR   PosFollowErFlg;             /* 总线用位置偏差过大标志位                             */
} BOUTF;
  
  
  
/*  控制模式定义 */
typedef	union	{							 
    struct	{
#if 0
    UCHAR	cm;
    UCHAR	cx;
    UCHAR	zm;
    UCHAR	ot;
#else
    uint32_t cm : 8;        /* 基本控制模式                                           */
    uint32_t cx : 8;        /* 扩展控制模式                                           */
    uint32_t zm : 8;        /* 零控制模式                                            */
    uint32_t ot : 8;        /* OT发生标志                                           */
#endif
    } b;
    LONG	dw;             /* 控制模式编辑用(Copy,etc)                                */
    USHORT	us[2];          /* 控制模式编辑用(Copy,etc)                                */
} CTRLMD;   

/*      零控制模式定义     */
typedef	union	{
    struct	{
#if 0
    UCHAR   zm;
    UCHAR   zmchg;
    UCHAR   spare0;
    UCHAR   spare1;
#else
    uint32_t zm     : 8;        /* 零控制模式                                    */
    uint32_t zmchg  : 8;        /* 零控制模式变化信息                              */
    uint32_t spare0 : 8;
    uint32_t spare1 : 8;
#endif
    } b;
    ULONG	dw;
    USHORT	us[2];
} ZCTRMD;

/*      控制模式切换定义  */
typedef	struct	{
    LONG	dPosFbki;           /* 位置增量值 [pulse]            */
    LONG	CmdErr;             /* 位置偏差修正后 [指令単位]                           */
} CTRL_CHANGE;
 
typedef	struct
{
    BOUTF	f;                      /* 位信号                                               */
    CTRLMD	CtrlMode;               /* Control Mode                                         */
    CTRLMD	CtrlModeLst;            /* Last Control Mode                                    */
    CTRLMD	CtrlModeChg;            /* Control Mode Change Info                            */
    ZCTRMD	ZctrlMode;              /* Zero Control Mode = BoutV.CtrlMode                   */
    LONG	TrqRefBeforeComp;       /* 补偿前转矩指令      [2^24/MaxTrq]           */

    UCHAR   CSELStatus;             /* 控制模式状态监控                                     */
    /*  伺服位置指令变量 */
    LONG	dPcmdFilo;              /* 位置指令：位置指令过滤器输出       [Pulse/Scan]        */
    /*  虚拟位置偏差                                                                              */
    LONG	VirtualPositionError[2];/*虚拟位置偏差[指令単位]          */
    LONG	FbPositionFB[2];        /* 反馈位置         */
    LONG	SpdFbki_l;              /* 前回反馈速度    [2^24/OvrSpd]              */
    LONG	SpdFbki_a;              /* 平均反馈速度    [2^24/OvrSpd]          */
    /*  伺服基本控制变量    */
    LONG    dPosRefi;                   /* 位置控制：位置指令差分输入        [Pulse/Scan]        */
    LONG    dPosFbki;                   /* 位置控制：位置反馈差分输入        [Pulse/Scan]        */
    LONG    PosFbki;                    /* 位置控制：位置ＦＢ                [Pulse]             */
    LONG    SpdRefp;                    /* 位置控制：速度指令输出          [2^24/OvrSpd]       */
    LONG    CompdPosRefi;               /* 位置控制：位置指令差分输入(ScanB->ScanA)  [Pulse/Scan]*/
    LONG    CompdPcmda;                 /* 位置控制：位置指令増分値输入(ScanB->ScanA)[指令単位]   */
    LONG    SpdFFCx;                    // 扩展控制：速度FF补偿              [2^24/OvrSpd]       */
    LONG    SpdFBCx;                    /* 扩展控制：速度FB补偿              [2^24/OvrSpd]       */
    LONG    SpdRfFilo;                  /* 速度控制：速度指令滤波器输出       [2^24/OvrSpd]       */
    float   fSpdRfFilo;
    LONG    SpdRefi;                    /* 速度控制：速度指令输入          [2^24/OvrSpd]       */
    LONG    SpdComp;                    /* 速度控制: 力矩波动补偿           [2^24/OvrSpd]     */
    LONG    SpdRefo;                    /* 速度控制：速度指令软起动输出       [2^24/OvrSpd]       */
    LONG    SpdLdstpRefo;               /* 速度控制: 减速停机时速度缓存     [2^24/OvrSpd]       */
    LONG    SpdFbki;                    /* 速度控制：速度FB输入              [2^24/OvrSpd]       */
    LONG    SpdObsFbki;                 /* 速度控制：速度FB输入（OBS后）    [2^24/OvrSpd]       */
    LONG    SpdReffinal;                /* 速度指令                                             */
    LONG    SpdRefSum;                  /* 速度控制：指令速度(Ref+FF)        [2^24/OvrSpd]       */
    LONG    TrqRefs;                    /* 速度控制：扭矩指令输出          [2^24/MaxTrq]       */
    LONG    TrqFFCx;                    /* 扩展控制：扭矩FF补偿              [2^24/MaxTrq]       */
    LONG    TrqFFCOffSet;               /* 扩展控制：扭矩FF补偿              [2^24/MaxTrq]       */
    LONG    TrqFBCx;                    /* 扩展控制：扭矩FB补偿              [2^24/MaxTrq]       */
    LONG    TrqRefi;                    /* 转矩过滤器：转矩指令输入         [2^24/MaxTrq]       */
    LONG    TrqRefo;                    /* 转矩过滤器：转矩指令输出         [2^24/MaxTrq]       */
    LONG    OverTrq;                    /* 转矩控制：速度限制用剩余转矩       [2^24/MaxTrq]       */
    USHORT  RefRenewalCnt;              /* ScanＡ位置指令更新处理用                               */
    SHORT   MpfPhaseOffset;             /* 磁极检出电角度偏置角           [65536/360deg]      */

    /*  监控变量（Un监控、模拟监控、etc） */
    LONG    UnSpdRef;                   /* Un001  : 速度指令                [2^24/OvrSpd]       */
    LONG    AmonSpdRef;                 /* AnaMon : 速度指令(速度ＦＦ含) [2^24/OvrSpd]       */
    LONG    AmonTrqRef;                 /* AnaMon : 扭矩指令（重力补偿后） [2^24/MaxTrq]       */
    LONG    AmonPosErra;                /* AnaMon : 位置偏差                [指令単位]          */
    LONG    AmonPosErrx;                /* AnaMon : 位置偏差                [ＦＢ単位]          */
    LONG    AmondPosCmd;                /* AnaMon : 位置指令差分          [指令单位/125us]    */
#if 0
    LONG	AmonMfcTrqRef;
    LONG	AmonMfcPosErr;
    LONG	AmonMfcPffCmd;
    LONG	AmonMfcTffCmd;
#endif
    LONG    AmonDisTrq;                 /* AnaMon : 干扰扭矩(重力补偿后) [2^24/MaxTrq]       */
    LONG    AmonResVib;                 /* AnaMon : 减振速度                [2^24/OvrSpd]       */
    LONG    AmonSpdObs;                 /* AnaMon : 速度估算値               [2^24/OvrSpd]       */
    LONG    AmonSpdEvObs;               /* AnaMon : 速度估算値               [2^24/OvrSpd]       */
    LONG    AmondAbvFilo;               /* AnaMon : 制动后位置指令速度   [2^24/OvrSpd]       */
    LONG    AmonActGain;                /* AnaMon : 有效增益                                    */
    LONG    ActGain;                    /* Un014  : 当前使用增益段，增益切换时设置 1:当前使用第1增益,2:当前使用第2增益   */
    LONG    AmonTrqComp;                /* AnaMon : 齿槽补偿转矩          [2^24/MaxTrq]       */
    LONG    AmonIdRef;                  /* AnaMon : d軸電流指令              [15000/MaxTrq]      */
    LONG    AmonMotorLessTestMdlSpd;    /* AnaMon : 无电机模式电机速度       [rad/s]             */


    /*----------------------------------------------------------------------------------------------*/
    LONG    TrcObsAvSpdErr;             /* Trace  : 振动检测用减振差速度  [2^24/OvrSpd]       */
    LONG    TrcCompTrqRef;              /* Trace  : 干扰输入前扭矩指令       [2^24/MaxTrq]       */
    LONG    TrcCtrlTrqRef;              /* Trace  : 扭矩指令    [2^24/MaxTrq]       */
    LONG    TrcMotPhase;                /* Trace  : 电流相位                [65536/360deg]      */
    ULONG   ExtInState;                 /* 外部锁存器内部输入状态(Ext1,Ext2,Ext3)              */
    /*----------------------------------------------------------------------------------------------*/
    ULONG   UnSettlingTime;             /* Un105  : 整定时间                [0.1ms]             */
    LONG    UnMaxOverShoot;             /* Un106  : 最大超调量               [指令単位]          */
#if(FLOAT_USE == 1)
    float   UnCoinOffTimer;             /* Un10B  : 无位置指令后且定位完成后又进入不完成状态时间[ms]  */
#else
    ULONG	UnCoinOffTimer;
#endif
    LONG    UnVibSpd;                   /* Un10C  : 振动检测用差速度        [2^24/OvrSpd]       */
    LONG    UnMpfMovePosP;              /* Un080  : 磁极检测正方向最大移动量[0.01mm]            */
    LONG    UnMpfMovePosN;              /* Un081  : 磁极检测反向最大移动量[0.01mm]         */
    LONG    UnMpFindingTime;            /* Un082  : 磁极检测所需时间        [0.1s]              */
    /*----------------------------------------------------------------------------------------------*/
    LONG    obs_vib_out;                /* 振动波形（监视输出用）                                  */
    USHORT  OutSettlingTime;            /* 整定時間出力                                           */
    /*  控制切换变量   */
    CTRL_CHANGE	CtrlChange;

    LONG    BlshCmpAmountPls;           // 间隙修正量差分值
} BOUTV;
  
/*      ScanB 特殊输出变量    */
typedef struct
{
        LONG    MaxSpdErr;                  /* Alarm  : 振动检出用差速度最大値 [2^24/OvrSpd]       */
        LONG    MinSpdErr;                  /* Alarm  : 振动检出用差速度最小値 [2^24/OvrSpd]       */
        LONG    MaxSpdErr2;                 /* Fn用   : 振动检出用差速度最大値  [2^24/OvrSpd]       */
        LONG    MinSpdErr2;                 /* Fn用   : 振动检出用差速度最小値  [2^24/OvrSpd]       */
        LONG    UnMaxSpdErr;                /* Un10C  : 振动检出用差速度最大値 [2^24/OvrSpd]       */
        LONG    UnMinSpdErr;                /* Un10C  : 振动检出用差速度最小値 [2^24/OvrSpd]       */
} BORST;
  
/*      ScanB 输入变量定义    */
typedef struct
{
    /*----------------------------------------------------------------------------------------------*/
    struct	{
    UCHAR	ScanB250us;
    UCHAR	MotCposOk;
    UCHAR	FencCposOk;
    UCHAR	FencCphPass;
    UCHAR	PerClrSignal;       /* Perr  Clear Signal   IO读取的原始值                        */
    UCHAR	PerClrEdge;         /* Perr  Clear Edge Signal  在查询中断中产生                */
    UCHAR	TrcPcmdInon;
    UCHAR	TrcPcmdSign;
    UCHAR	Acon;               /* AC ON Signal                                             */
    UCHAR	ClrEnableFlg;
    UCHAR   Reserved;
    } f;
    /*----------------------------------------------------------------------------------------------*/
    LONG    MotPos;                 /* 电机位置 (Ring)              [32bitRingPulse]            */
    LONG    dMotPos;                /* 电机位置增量                   [pulse/ScanB]               */
    LONG    MotSpd;                 // 电机速度                     [2^24/OvrSpd]
    LONG    AbsMotSpd;              /* 电机速度绝对值              [2^24/OvrSpd]               */
    /*----------------------------------------------------------------------------------------------*/
    LONG    FencPos;                /* Fenc  Position (Ring)        [32bitRingPulse]            */
    LONG    FencPosUnit;
    LONG    dFencPos;               /* Delta Fenc Position          [pulse/ScanB]               */
    LONG    FencSpd;                /* 全闭环外部编码器速度           [2^24/OvrSpd]       <V158>  */
 
    SHORT   PcmdHwCntr;             /* 脉冲指令                                 */
    SHORT   ClrLatchRefPos;         /* 边沿位置偏差清除时锁存的位置指令，仅查询中设置          */
    LONG    dPcmdInputHwCntr;       /* Latch Delta Pulse Command of Position Egde Clear         */
    LONG    dPcmdHwCntr;            /* 脉冲指令增量                       */
    /*----------------------------------------------------------------------------------------------*/
    LONG    DcVolt;                 /* 主回路母线电压  ScanB中每250us读一次AD采样值滤波并调零   */
    LONG    UnDcVolt;               /* Un140 : 主回路母线电压          [V]                     */
    LONG    TrcDcVolt;              /* Trace : 主回路母线电压          [V]                     */
    LONG    TrcDcVoltFili;          /* Trace : 主回路母线电压          [V]                     */
    SHORT   IqRefMon;               /* q轴电流指令监控             [15000/Imax]                */
    SHORT   IdRefMon;               /* d轴电流指令监控             [15000/Imax]                */
    LONG    TrqRefMon;              /* 转矩指令监控                   [2^24/MaxTrq]               */
    LONG    TrqRefMon_a;            /* 转矩指令监控(平均值)          [2^24/MaxTrq]               */
    LONG    TrqRefo_a;              /* 平均扭矩指令输出             [2^24/MaxTrq]               */
    LONG    TrqRefFilMon;           /* 干扰前扭矩指令（监控）      [2^24/MaxTrq]               */

    /*----------------------------------------------------------------------------------------------*/
    LONG    UnPfbkCntr2;            /* Un013 : FB脉冲计数器      [指令単位]      */
    LONG    RemCntr2;               /* Un013 :  [指令単位]     */
    LONG    RemCntr3;               /* 电机反馈脉冲数                   [光学尺反馈单位]        */
    LONG    RemCntr4;               /* 电机反馈脉冲数(EtherCAT 电子齿轮比)                      */
	LONG    RemCntr5;
    LONG    RemCntr6;
    /*------------------------------------------------------------------------------------------*/
    HWSIN   UnInSignal;             /* 输入信号(监视用)    ScanB 每250us输入硬件原始值经滤波后     */
    HWSOUT  UnOutSignal;            /* 输出信号(监视用)    ScanB 输出硬件原始值^ KPX_HWSOUTXOR        */
    /*----------------------------------------------------------------------------------------------*/
    USHORT  ORGFinishFlg;
    USHORT  ORGFinishMode;
} BINK;
  
/*      ScanB 输出变量定义    */
typedef struct
{
/*--------------------------------------------------------------------------------------------------*/
        HWSOUT  hw;                     /* ＨＷ输出信号                                               */
        USHORT  UnOutSignal;            /*  Y 输出信号监控                                          */
    /*----------------------------------------------------------------------------------------------*/
        struct {
        UCHAR   PerClrEdge;             /* Position Egde Clear Input                                */
        UCHAR   Spare01;                /* Spare01                                                  */
        UCHAR   Spare02;                /* Spare02                                                  */
        UCHAR   Spare03;                /* Spare03                                                  */
        } f;
    /*----------------------------------------------------------------------------------------------*/
        LONG    IdRef;                  /* d-Axis Current Reference     [15000/MaxCur]              */
        LONG    TrqRef;                 /* Torque Reference Output      [2^24/MaxTrq]               */
        LONG    PcmdRingCntr;           /* Pulse Command Ring Counter   [pulse]                     */
        LONG    ClrPcmdPastCntr;        /* Last Pulse Command of Position Egde Clear                */
        LONG    ClrFbPos;               /* Motor Position of Position Egde Clear                    */
        SHORT   MpfPhaseOffset;         /* 磁极检测相位偏移         [65536/360deg]              */
    /*----------------------------------------------------------------------------------------------*/
        LONG    PosTrqLmt;              /* Positive Torque Limit        [2^24/MaxTrq]               */
        LONG    NegTrqLmt;              /* Negative Torque Limit        [2^24/MaxTrq]               */
        LONG    PosTrqLmt_15000;        /* Positive Torque Limit        [15000/MaxTrq]              */
        LONG    NegTrqLmt_15000;        /* Negative Torque Limit        [15000/MaxTrq]              */
/*--------------------------------------------------------------------------------------------------*/
} BOUTK;
 
/**************************************ScanC 输入输出信号定义****************************************/

/*      ScanC 输入位信号定义 */
typedef struct  {
        CMD_CTRLBITS    Ctrl;               /* 控制指令                                             */
        CMD_SEQBITS     Seq;                /* 序列控制指令                                   */
        CMD_LTBITS      Lt;                 /* 锁存要求                                             */
    /*----------------------------------------------------------------------------------------------*/
        struct {
            UINT    Pot                 :1; /* 0x00 : P-OT Signal                                   */
            UINT    Not                 :1; /* 0x01 : N-OT Signal                                   */
            UINT    Csel                :1; /* 0x02 : C-SEL Signal 模式切换                         */
            UINT    Zclamp              :1; /* 0x03 : ZCLAMP Signal                                 */
            UINT    SpdD                :1; /* 0x04 : SPD-D Signal  内部速度方向                  */
            UINT    SpdA                :1; /* 0x05 : SPD-A Signal                                  */
            UINT    SpdB                :1; /* 0x06 : SPD-B Signal                                  */
            UINT    ABSEn               :1; /* 0x07 : SEN Signal    绝对值编码器初始数据请求        */
    /*----------------------------------------------------------------------------------------------*/
            UINT    FanAlm              :1; /* 0x08 : FANALM Signal                                 */
            UINT    ScanCEncDataNG      :1; /* 0x09 : ScanC用编码器数据无效的标志(0:有效/1:无效)   */
            UINT    TlimitSel           :1; /* 0x0A : TLSel Signal                                  */
            UINT    TorqD               :1; /* 0x0B : 转矩方向                                      */
            UINT    PoleDetect          :1; /* 0x0C : P-DET Signal  磁极检出                        */
            UINT    CycleSt             :1; /* 0x0D : Cycle Start                                   */
            UINT    TorqA               :1; /* 0x0E : Torq-A Signal                                 */
            UINT    TorqB               :1; /* 0x0F : Torq-B Signal                                 */
            UINT    TCtrg               :1; /* 0x10 : T-CTRG signal                                 */
    /*----------------------------------------------------------------------------------------------*/
            UINT    JOGP                :1; /* 0x11 : 正向点动                                      */
            UINT    JOGN                :1; /* 0x12 : 负向点动                                      */
            UINT    JOGFlag             :1; /* 0x13 : 端子点动标志                                  */
            UINT    OTCheck             :1; /* 0x14 : 超程检测开关                                    */
            UINT    SpareBit15          :1; /* 0x15 : Spare                                         */
            UINT    FencS          		:1; /* 0x16 : 全闭环控制时位置反馈指令源选择               */
            UINT    TSLimit             :1; /* 0x17 : 转矩速度限制选择                              */
    /*----------------------------------------------------------------------------------------------*/
            UINT    PotIn               :1; /* 0x18 : 正向限位输入                                    */
            UINT    NotIn               :1; /* 0x19 : 负向限位                                      */
            UINT    EmcyStop            :1; /* 0x1A : 紧急停机                                      */
            UINT    Csel2               :1; /* 0x1B : 模式选择                                      */
            UINT    CTrig               :1; /* 0x1C : 模式确认                                      */
            UINT    TDIR                :1; /* 0x1D : 转矩方向                                      */
            UINT    TMonTrg             :1; /* 0x1E : 转矩监控触发                                    */
            UINT    BKSel               :1; /* 0x1F : Spare                                         */
    /*----------------------------------------------------------------------------------------------*/
            UINT    ManualAutoMod       :1;
            UINT    ExFault             :1;                 // 外部故障信号  @20240809
    /*----------------------------------------------------------------------------------------------*/
            UINT    Fun30               :1;
            UINT    Fun31               :1;
            UINT    Fun32               :1;            
            UINT    Fun33               :1;            
            UINT    Fun34               :1;            
            UINT    Fun35               :1;            
            UINT    Fun36               :1;            
            UINT    Fun37               :1;
            UINT    Fun38               :1;            
            UINT    Fun39               :1;            
            UINT    Fun3A               :1;            
            UINT    Fun3B               :1;
            UINT    Fun3C               :1;
            UINT    Fun3D               :1;
            UINT    Fun3E               :1;
            UINT    Fun3F               :1;            
    } Sv ;
} CINF;

 
/*      ScanC 输入信号定义 */
typedef union
{
    struct {
        UINT    Pot                 :1;     /* 0x00 : P-OT  Signal Mask Bit                         */
        UINT    Not                 :1;     /* 0x01 : N-OT  Signal Mask Bit                         */
        UINT    Estp                :1;     /* 0x02 : E-STP Signal Mask Bit                         */
        UINT    SpareBit03          :1;     /* 0x03 : Spare                                         */
        UINT    SpareBit04          :1;     /* 0x04 : Spare                                         */
        UINT    SpareBit05          :1;     /* 0x05 : Spare                                         */
        UINT    SpareBit06          :1;     /* 0x06 : Spare                                         */
        UINT    SpareBit07          :1;     /* 0x07 : Spare                                         */
        UINT    SpareBit08          :1;     /* 0x08 : Spare                                         */
    /*----------------------------------------------------------------------------------------------*/
    } b;
    ULONG       MaskUL ;                    /* Mask Data                                            */
} CINSIGMSK;
  
/*      ScanC 输入信号定义 */
typedef struct
{
/*--------------------------------------------------------------------------------------------------*/
        CINF    f;                          /* 位信号                                              */
/*----------------------------------------------------------------------------------------------*/
        LONG    FwTrqLmt;                   /* Forward Torque Limit     [2^24/MaxTrq]               */
        LONG    RvTrqLmt;                   /* Reverse Torque Limit     [2^24/MaxTrq]               */
/*--------------------------------------------------------------------------------------------------*/
} CINV;
 
/*      ScanC 输出位信号定义 */
typedef struct  {                           /* 位 信号                                             */
        RSP_CTRLBITS    Ctrl;               /* 控制状态                                             */
        RSP_SEQBITS     Seq;                /* 时序控制状态                                           */
        RSP_LTBITS      Lt;                 /* Latch状态                                          */
        RSP_SIGNLBITS   InSig;              /* 输入信号状态                                           */
    /*----------------------------------------------------------------------------------------------*/
        struct {
            UINT    SpareBit00          :1; /* 0x00 : Spare                                         */
            UINT    MotStop             :1; /* 0x01 : 电机停止信号 速度低于一定值时为turn      */
            UINT    ChargeOk            :1; /* 0x02 : DC Charge Complete 上电后，主回路母线电压超过欠压值180ms      */
            UINT    SvonReq             :1; /* 0x03 : Servo ON Request                              */
            UINT    OtBeReq             :1; /* 0x04 : OT时序允许伺服使能                            */
            UINT    BkBeReq             :1; /* 0x05 : 抱闸信号请求的伺服通电状态,0:不使能,1:使能  */
            UINT    DbOn                :1; /* 0x06 : 请求DB ON Flag，0:动态制动器OFF,1:动态制动器ON。仅在动态制动时序中变化 */
            UINT    BaseEnable          :1; /* 0x07 : Base Enable Flag，除无电机测试模式外总是伴随着往ASIC写使能       */
    /*----------------------------------------------------------------------------------------------*/
            UINT    Ot                  :1; /* 0x08 : Over Travel Flag  发生与指令方向同向的超程(无需使能)  */
            UINT    Pot                 :1; /* 0x09 : P-Side Over Travel Flag                       */
            UINT    Not                 :1; /* 0x0A : N-Side Over Travel Flag                       */
            UINT    BBSvcRefClrReq      :1; /* 0x0B : Servo Control Ref. Clear Request Flag         */
            UINT    SvReadyPhaseIgnore  :1; /* 0x0C : 伺服准备就绪 (Ignore Phase)                 */
            UINT    MpoleFinding        :1; /*未用 0x0D : Motor Pole Finding Flag 磁极检出中       未用  */
            UINT    SensOnReq           :1; /*未用 0x0E : Sens ON Request 1:向伺服请求绝对值数据 0:请求警报代码  */
            UINT    SpareBit0F          :1; /* 0x0F : Spare                                         */
    /*----------------------------------------------------------------------------------------------*/
            UINT    Vrefon              :1; /*显示用 0x10 : Speed  Reference Input On                      */
            UINT    Trefon              :1; /*显示用 0x11 : Torque Reference Input On                      */
            UINT    Prefon              :1; /* 0x12 : Pulse  Reference Input On                     */
            UINT    PerrClr             :1; /*显示用 0x13 : 位置清除信号     Input On    仅位置模式下= 位置偏差清除电平信号有效,仅电平模式且与设定电平一致时为1       */
            UINT    PrefSign            :1; /*显示用0x14 : Pulse  Reference Sign  (plus:1, minus:0)        */
            UINT    RegeAlmSignal       :1; /*未用 0x15 : 再生异常检出信号                                */
            UINT    VibDetFlg           :1; /*Fn201用 0x16 : Vibration detected Flag (振动检出标志,最大速度误差大于阀值)     */
            UINT    LowFreqVibDetFlg    :1; /*显示用 0x17 : Low Frequency Vibration detected Flag          *//* <V111> */
    /*----------------------------------------------------------------------------------------------*/
            UINT    PumpDbDriveOk       :1; /* 未用0x18 : 允许DB制动用ChargePump驱动                 */
            UINT    HwbbState           :1; /* 未用 0x19 : Hard-wired Baseblock Status    判断时序及面板状态显示 1:HBB   */
            UINT    LackOneBbon         :1; /* 未用0x1A : One BBON Signal Input Only  仅警报 A.Eb1用  *//* <V064> */
            UINT    SpareBit1B          :1; /* 未用0x1B : BBON1 Signal Inverted (Low Active)安全端子/HWBB1输入ON(1:正常上灯亮)   */
            UINT    SpareBit1C          :1; /* 未用0x1C : BBON2 Signal Inverted (Low Active)安全端子/HWBB2输入ON(1:正常上灯亮)   */
            UINT    GateDrvDefect       :1; /* 未用0x1D : Gate Drive Defect Status Flag   仅警报 A.B40用，有HWBB时不需要    */
            UINT    OtTrqLimit          :1; /* 0x1E : OT Sequence Torque Limit Request 行程限位时请求以Pn406作为转矩限制  */
            UINT    PWMEn               :1; /* 显示用0x1F : Spare                                          */
    /*----------------------------------------------------------------------------------------------*/
            UINT    AlmReady            :1; /* 0x20 : ForceSet AlmReady Status Flag         */
            UINT    ScalWrEnableRes     :1; /* 未用0x21 : Scale Write Enable Response             */
            UINT    ScaleWrMoniStart    :1; /* 未用0x22 : Scale Write Result Monitor          */
            UINT    SvonRef             :1; /* 0x23 : Servo ON Request(S-ON,P-DET)      */
            UINT    PoleDetClr          :1; /* 未用0x24 : Pole Detect Complete flag clear             */
#if defined(MCCSW_SGDVCMOP)
            UINT    Pls                 :1; /* 未用0x25 : P-LS    Soft Limit Flag                         */
            UINT    Nls                 :1; /* 未用0x26 : N-LS    Soft Limit Flag                         */
#else
            UINT    SpareBit25          :1; /* 0x25 : Spare                                         */
            UINT    SpareBit26          :1; /* 0x26 : Spare                                         */
#endif
            UINT    SpareBit27          :1; /* 0x27 : Spare                                         */
        }Sv ;
} COUTF;

  
/*********************************************警报时监控变量*****************************************/
//初始化从EEPROM读取最近一次警报监控变量
typedef	struct
{
    /*---------------------------------------·-------------------------------------------------------*/
    SHORT   MotSpd;                 /* d电机位置差分(2ms)             [min-1/mm/s]            */
    SHORT   SpdRef;                 /* 速度指令                         [min-1/mm/s]            */
    SHORT   TrqRef;                 /* 转矩指令                     [%]                     */
    SHORT   PcmdSpd;                /* 位置指令差分(2ms)              [min-1/mm/s]            */
    LONG    PosErr;                 /* 位置偏差输出(四舍五入)                                 */
    /*----------------------------------------------------------------------------------------------*/
    ULONG   InterSignal;            /* 内部信号(监控)                                     */
    ULONG   InSignal;               /* 输入信号(监控)                                     */
    ULONG   OutSignal;              /* 输入信号(监控)                                     */
    /*----------------------------------------------------------------------------------------------*/
    SHORT   DcVoltage;              /* 主回路母線电压                  [V]                     */
    SHORT   IFBMon;                 /* 电流反馈有效值                  [%]                     */
    USHORT  MotLoad;                /* 电机负载                         [%]                     */
    USHORT  RgPower;                /* 回生消費電力                       [%]                     */
    USHORT  DbPower;                /* DB功耗                             [%]                     */
    USHORT  MaxMotLoad10s;          /* 最大累计负荷率                  [%（周期10s）]          */
    USHORT  JLRatio;                /* 惯量比          [%]                     */
    /*----------------------------------------------------------------------------------------------*/
    USHORT  EncComErrCnt;           /* 串行编码器通信异常次数                          */
    /*----------------------------------------------------------------------------------------------*/
    USHORT  AlmCode;                /* 最近一次警报代码                                         */
    ULONG   TmStamp;                /* 报警时间戳                                    */
} ALMLTMON;
  
/*  ScanC 输出变量定义 */
typedef	struct
{
    /*--------------------------------------------------------------------------------------------------*/
    COUTF   f;                          /* 位信号                                              */
    /*----------------------------------------------------------------------------------------------*/
    CTRLMD  CtrlMcmd;                   /* 控制模式 to ScanB                        */


    UCHAR   StopMode;                   /* Stop Mode 仅在LpxStopModeManager()中设置              */
    UCHAR   ServoOffStatus;             /* 伺服Off状态寄存器                                    */
/*----------------------------------------------------------------------------------------------*/
    LONG    ModeSwAcc;                  /* Motor Acceleration fow ModeSw    [NorSpd/ScanC]      */
    LONG    ModeSwSpd;                  /* Motor Speed for ModeSwAcc Cal.   [2^24/OverSpd]      */
    /*----------------------------------------------------------------------------------------------*/
    USHORT  EstimatJrat;                /* 负载惯量比辨识结果                [%]                 */
    USHORT  PowoffErrDly;               /* 掉电延迟输出                                         */
    /*----------------------------------------------------------------------------------------------*/
    USHORT  UnMeanRgPower;              /* Un00A : 回生消費電力平均値        [%]                 */
    USHORT  UnMeanDbPower;              /* Un00B : DB电阻消耗电力平均值      [%]                 */
    SHORT   UnHeatSinkTemp;             /* Un014 : 散热片温度                [0.1deg]            */
    SHORT   UnHeatMotTemp;              /* Un014 : 电机温度                [0.1deg]            */
    USHORT  UnEnvirTemp;                /* Un015 : 环境温度                 [0.1deg]            */

    LONG    UnSpeedRef;                   /* Un016  : 速度给定，负载端单位 rpm              */
    LONG    UnSpeedFbk;                   /* Un017  : 速度反馈，负载端单位 rpm              */
    LONG    UnTorqueRef;                  /* Un018  : 力矩给定，负载端单位 N·m              */
    LONG    UnTorqueFbk;                  /* Un019  : 力矩反馈，负载端单位 N·m              */

    USHORT  UnRgPower;                  /* Un143 : 再生功耗值                [%]                 */
    USHORT  UnDbPower;                  /* Un144 : DB电阻功耗值          [%]                 */
    /*----------------------------------------------------------------------------------------------*/
    LONG    UnTrqRef;                   /* Un002 : 内部转矩指令               [2^24/MaxTrq]       */
    LONG    UnMotAngle;                 /* Un003 : 旋转角1（脉冲）         [pulse]             */
    LONG    UnMotPhase;                 /* Un004 : 旋转角2（电角度）            [deg]               */
    LONG    UnMotSpdx;                  // Un000 : 电机速度(test用)          [2^24/OvrSpd]       */
    LONG    UnMotSpd;                   /* Un000 : 电机速度(监视用)            [pulse/64ms]        */
    LONG    UnFencSpd;                  /* Un022 : 电机速度(监视用)            [pulse/64ms]        */
    LONG    UnPfbk64ms;                 /* Un000 : 电机速度(监视用)            [pulse/64ms]        */
    LONG    UnPcmd64ms;                 /* Un007 : 位置指令脉冲速度         [pulse/64ms]        */
    ULONG   UnIsqrSum;                  /* Un009 : 累计负荷率                [(15000/MaxTrq)/10sec]*/

    ULONG   UnIsqrSum1;
    ULONG   Intera;
    ULONG   Friction;
    LONG    UnFpos100ms;                /*  : フルクＦＢパルス速度        [pulse/100ms]           */
    LONG    UnFencrpm100ms;                /*  : フルクＦＢパルス速度        [0.1rpm]           */
    LONG    UnFposError;                /* Un023 : 光学尺和电机编码器的反馈位置偏差             */
    LONG    UnFposUserError;            /* Un024 : 光学尺和电机编码器的反馈位置偏差             */
    LONG    UnFposCompValue;

    LONG    UnRvibFrequency;            /* Un107 : 低频晃动频率               [0.1Hz]             */
    ULONG   UnCrntDet;                  /* Un141 : 电流有效值(反馈)            [(15000/MAXTRQ)^2]  */
    ULONG   UnCrntLatch;
    ULONG   UnCrntRef;                  /* Un142 : 瞬时负载率(电流有效值指令)[(15000/MAXTRQ)^2] */
    ULONG   UnIsqrSumMax;               /* Un145 : 累计负载率最大值         [(15000/MaxTrq)/10sec]*/
    /*----------------------------------------------------------------------------------------------*/
    LONG    TrcRgPower;                 /* Trace : 再生功耗值            [%]                 */
    LONG    TrcDbPower;                 /* Trace : DB电阻功耗值s             [%]                 */
    /*----------------------------------------------------------------------------------------------*/
    ALMLTMON AlmLtMon;                  /* 警报发生时的监视,初始化从EEPROM读取最近一次警报监控变量*/
/*----------------------------------------------------------------------------------------------*/
    ULONG   AlmWrnCode;                 /*       :  警报/警告代码                 */
    USHORT  NormalOpeDrive;             /* 伺服on无效报警检测/非检测FLAG 由各辅助功能设置      */

} COUTV;
  
/*      ScanC 特殊输出变量定义 */
typedef	struct
{
    LONG    UnPcmdCntr;                 /* Un00C : 指令脉冲计数器          [pulse]             */
    LONG    UnPfbkCntr;                 /* Un016 : ＦＢ脉冲计数器          [pulse]             */
    LONG    UnPfbkCntr2;                /* Un013 : ＦＢ脉冲计数               [指令単位]          */
	/*------------------------------------------------------------------------------------------*/
    LONG    UnPfbkCntr3;                /* 电机编码器反馈                  [光学尺单位]        */
    LONG    UnPfbkCntr4;                /* 电机编码器反馈                   [光学尺单位]        */
    LONG    RemCntr3;                   /* 电机编码器反馈余数                [光学尺单位]        */
    LONG    RemCntr4;                   /* 光学尺反馈[用户单位]             [用户单位]          */
/*------------------------------------------------------------------------------------------*/
    LONG    UnFenseCnt1;
    LONG    UnFenseCnt2;
} CORST;
 
/****************************************输入端子功能配置寄存器*****************************************/
typedef struct {
        UCHAR   Mode;
        UCHAR   Spare;
        DBYTEX  Gsel2;
        USHORT  Sen;
        DBYTEX  UseLess;
        DBYTEX  Svon;                   /* 输入信号0x01: /S-ON      伺服使能                        */
        DBYTEX  Pot;                    /* 输入信号0x02:  P-OT      禁止正转                        */
        DBYTEX  Not;                    /* 输入信号0x03:  N-OT      禁止反转                        */
        DBYTEX  AlmRst;                 /* 输入信号0x04: /ALMRST    报警复位                        */
        DBYTEX  Pcon;                   /* 输入信号0x05: /P-CON     P动作                         */
        DBYTEX  TlimitSel;              /* 输入信号0x06: /TL-Sel    外部转矩限制选择                */
        DBYTEX  Reser1;                 /* 输入信号0x07: /ABSEn     绝对值编码器DI/DO 请求          */
        DBYTEX  SpdD;                   /* 输入信号0x08: /SPD-Dir   速度方向                        */
        DBYTEX  SpdA;                   /* 输入信号0x09: /SPD-A     内部速度选择A                 */
        DBYTEX  SpdB;                   /* 输入信号0x0A: /SPD-B     内部速度选择B                 */
        DBYTEX  Csel;                   /* 输入信号0x0B: /C-S       控制方式切换                  */
        DBYTEX  Zclamp;                 /* 输入信号0x0C: /ZCL P     零位固定                        */
        DBYTEX  Inhibit;                /* 输入信号0x0D: /INHIBIT   脉冲禁止                        */
        DBYTEX  Gsel1;                  /* 输入信号0x0E: /G-S 1     增益切换                        */
        DBYTEX  TrqSign;                /* 输入信号0x0F: /T-SIGN    转矩方向                        */
        DBYTEX  Psel;                   /* 输入信号0x10: /PSEL      指令脉冲倍率切换                */
        DBYTEX  CLR;                    /* 输入信号0x11: /CLR       脉冲偏差清除                  */
        DBYTEX  TORQA;                  /* 输入信号0x12: /TORQ-A    转矩限制A                       */
        DBYTEX  TORQB;                  /* 输入信号0x13: /TORQ-B    转矩限制B                       */
        DBYTEX  TCTRG;                  /* 输入信号0x14: /T-CTRG    转矩触发                        */
        DBYTEX  SPDLIMIT;               /* 输入信号0x15: /T—SPDSEL  速度限制                        */
        DBYTEX  FencS;                  /* 输入信号0x16: /FENC      位置反馈源选择                 */
        DBYTEX  JOGP;                   /* 输入信号0x17: JOGP                                       */
        DBYTEX  JOGN;                   /* 输入信号0x18: JOGN                                       */
        DBYTEX  EmcyStop;               /* 输入信号0x19: 紧急停机                                   */
        DBYTEX  Csel2;                  /* 输入信号0x1A: /C-S2 控制模式选择2                      */
        DBYTEX  CTrig;                  /* 输入信号0x1B: /C-Trig 控制模式确认信号                   */
        DBYTEX  TmonTrg;                /* 输入信号0x1C: Un00A监控    触发                          */
        DBYTEX  Reser7;                 /* 输入信号0x1D: 预留                                         */
        DBYTEX  ManualAutoMod;          /* 输入信号0x1E: 预留                                          */
        DBYTEX  BKSel;                  /* 输入信号0x1F: 预留                                          */
/*--------------------------------------------------------------------------------------------------*/
        DBYTEX  CTRG;                   /* 输入信号0x20: 内部位置触发选择                           */
        DBYTEX  POS0;                   /* 输入信号0x21: 内部位置0                                  */
        DBYTEX  POS1;                   /* 输入信号0x22: 内部位置1                                  */
        DBYTEX  POS2;                   /* 输入信号0x23: 内部位置2                                  */
        DBYTEX  POS3;                   /* 输入信号0x24: 内部位置3                                  */
        DBYTEX  POS4;                   /* 输入信号0x25: 内部位置4                                  */
        DBYTEX  POS5;                   /* 输入信号0x26: 内部位置5                                  */
        DBYTEX  ORGEN;                  /* 输入信号0x27: 原点回归使能                                 */
        DBYTEX  ORGS;                   /* 输入信号0x28: 原点信号                                   */
        DBYTEX  ExFault;                /* 输入信号0x29: 外部故障信号                                         */
        DBYTEX  Reserved2;              /* 输入信号0x2A:                                            */
        DBYTEX  Reserved3;              /* 输入信号0x2B:                                            */
        DBYTEX  Reserved4;              /* 输入信号0x2C:                                            */
        DBYTEX  Reserved5;              /* 输入信号0x2D:                                            */
        DBYTEX  Reserved6;              /* 输入信号0x2E:                                            */
        DBYTEX  Reserved7;              /* 输入信号0x2F:                                            */
/*--------------------------------------------------------------------------------------------------*/
        DBYTEX  Fun30;                  /* 输入信号0x30:                                            */
        DBYTEX  Fun31;                  /* 输入信号0x31:                                            */
        DBYTEX  Fun32;                  /* 输入信号0x32:                                            */
        DBYTEX  Fun33;                  /* 输入信号0x33:                                            */
        DBYTEX  Fun34;                  /* 输入信号0x34:                                            */
        DBYTEX  Fun35;                  /* 输入信号0x35:                                            */
        DBYTEX  Fun36;                  /* 输入信号0x36:                                            */
        DBYTEX  Fun37;                  /* 输入信号0x37:                                            */
        DBYTEX  Fun38;                  /* 输入信号0x38:                                            */
        DBYTEX  Fun39;                  /* 输入信号0x39:                                            */
        DBYTEX  Fun3A;                  /* 输入信号0x3A:                                            */
        DBYTEX  Fun3B;                  /* 输入信号0x3B:                                            */
        DBYTEX  Fun3C;                  /* 输入信号0x3C:                                            */
        DBYTEX  Fun3D;                  /* 输入信号0x3D:                                            */
        DBYTEX  Fun3E;                  /* 输入信号0x3E:                                            */
        DBYTEX  Fun3F;                  /* 输入信号0x3F:                                            */
/*--------------------------------------------------------------------------------------------------*/
        USHORT  VirSet;                 /* 虚拟端子选择设置                                         */
        USHORT  OnOffSet;               /* 常开,常闭设置                                            */

} IMAP;
  
/****************************************状态管理输出映射*****************************************/
typedef struct {
    UCHAR   UseLess;                /* 无效信号                                                 */
    UCHAR   Svrdy;                  /* 输出信号分配 0x01: /S-RDY                                  */
    UCHAR   Coin;                   /* 输出信号分配 0x02: /COIN                                   */
    UCHAR   Vcmp;                   /* 输出信号分配 0x03: /V-CMP                                  */
    UCHAR   Tgon;                   /* 输出信号分配 0x04: /TGON                                   */
    UCHAR   Clt;                    /* 输出信号分配 0x05: /CLT                                    */
    UCHAR   Vlt;                    /* 输出信号分配 0x06: /VLT                                    */
    UCHAR   Bk;                     /* 输出信号分配 0x07: /BK                                     */
    UCHAR   Warn;                   /* 输出信号分配 0x08: /WARN                                   */
    UCHAR   Near;                   /* 输出信号分配 0x09: /NEAR                                   */
    UCHAR   PselA;                  /* 输出信号分配 0x0A: /PSELA 指令脉冲输入倍率切换输出信号   */
    UCHAR   Alarm;                  /* 输出信号分配 0x0B: /Alarm                                */
    UCHAR   TorReach;               /* 输出信号分配 0x0C: /TorR 力矩到达                        */
    UCHAR   EtherCatY1;             /* EtherCAt Y1  0x0D: / E_Y1                                */
    UCHAR   EtherCatY2;             /* EtherCAt Y2  0x0E: / E_Y2                                */
    UCHAR   JOGP;               /* 正向点动JOG输出  0x0F: /                                */
    UCHAR   JOGN;               /* 反向点动JOG输出  0x10: /                               */
    /*------------------------------------------------------------------------------------------*/
    UCHAR   CMDOK;                  /* PR 0x11指令发送完成标志位                                */
    UCHAR   TPOS;                   /* PR 0x12指令完成                                          */
    UCHAR   MCOK;                   /* PR 0x13指令定位完成                                      */
    /*------------------------------------------------------------------------------------------*/
    UCHAR   STO;                /* 0x14 STO输出                                               */
    UCHAR   ORGC;                   /* 0x15 原点回归完成                                        */
    UCHAR   Reserved16;             /* 0x16                                                     */
    UCHAR   Reserved17;             /* 0x17                                                     */
    UCHAR   Reserved18;             /* 0x18                                                     */
    UCHAR   Reserved19;             /* 0x19                                                     */
    UCHAR   Reserved1A;             /* 0x1A                                                     */
    UCHAR   Reserved1B;             /* 0x1B                                                     */
    UCHAR   Reserved1C;             /* 0x1C                                                     */
    UCHAR   Reserved1D;             /* 0x1D                                                     */
    UCHAR   Reserved1E;             /* 0x1E                                                     */
    UCHAR   Reserved1F;             /* 0x1F                                                     */
    /*------------------------------------------------------------------------------------------*/
    UCHAR   Fun20;                  /* 0x20                                                     */
    UCHAR   Fun21;                  /* 0x21                                                     */
    UCHAR   Fun22;                  /* 0x22                                                     */
    UCHAR   Fun23;                  /* 0x23                                                     */
    UCHAR   Fun24;                  /* 0x24                                                     */
    UCHAR   Fun25;                  /* 0x25                                                     */
    UCHAR   Fun26;                  /* 0x26                                                     */
    UCHAR   Fun27;                  /* 0x27                                                     */
    UCHAR   Fun28;                  /* 0x28                                                     */
    UCHAR   Fun29;                  /* 0x29                                                     */
    UCHAR   Fun2A;                  /* 0x2A                                                     */
    UCHAR   Fun2B;                  /* 0x2B                                                     */
    UCHAR   Fun2C;                  /* 0x2C                                                     */
    UCHAR   Fun2D;                  /* 0x2D                                                     */
    UCHAR   Fun2E;                  /* 0x2E                                                     */
    UCHAR   Fun2F;                  /* 0x2F                                                     */
    /*------------------------------------------------------------------------------------------*/
    ULONG   RvsXor;                 /* 出力信号割付 0x11: 出力信号反転                          */
    USHORT  VirDO;                  /* 虚拟输出端口配置                                         */
} OMAP;
  
/****************************************参数变量定义*****************************************/
/*      初始参数定义   */
typedef	struct
{
    /*--------------------------------------------------------------------------------------------------*/
    struct  {                               /* 位参数                              */
            /*------------------------------------------------------------------------------------------*/
            UINT    BatWrnMode      :1;     /* 绝对值编码器电池欠电压时警报/警告选择                  */
            UINT    MulTSingT       :1;     /* 绝对值编码器多圈型号当做单圈使用                         */
            UINT    SpdDetMaFil     :1;     /*                            */
            UINT    AbsPosLimit     :2;     /*                                       */

            UINT    SpdIctrlKeep    :1;     /* 速度控制积分保持                                         */

            UINT    G2AlmStopMode   :1;     /* G2警报的停止方式与停止方式与Pn005.0相同                     */
            UINT    OtStopWarn      :1;     /* 超程(OT)警告检出选择             Pn005.3                 */
            UINT    BKsel           :1;     /* 抱闸输出方式选择                 */

            UINT    FencDir         :1;     /* 光学尺反馈脉冲信号方向                                   */
            UINT    FencSource      :1;     /* 光学尺切入选择                                           */

            UINT    INCEncType      :1;     /* 增量式编码器类型                                         */
/*------------------------------------------------------------------------------------------*/
            UINT    RvsDir          :1;     /* 旋转方向选择，0:正,1:反，初始化由Pn000.0设置             */
            UINT    MulTSing        :1;     /* 单圈绝对值                                                */
            UINT    WrnOutSel       :1;     /* 警告代码输出选择 */
            UINT    EepPrmWrite     :1;     /* EEPROM参数写入允许                                     */
            UINT    RegRxIn         :1;     /* 内置再生电阻   Prm.E0C & 0x0001                            */
            UINT    Dcbus           :1;     /* 主回路母线电压以DC电源输入 Pn001.2 : AC/DC电源输入的选择    */
            UINT    Ac3Phase        :1;     /* 以3相电源输入来使用三相输入规格伺服 仅缺相检查用    Pn00B.2 */
            UINT    DetectAcOn2     :1;     /* 电源缺相检测方式 PnE0C & 0x0008                          */
            UINT    OhdetPort       :1;     /* 散热器过热检测方式(0:IO口/1:AD) Prm.PnE0C & 0x0800     */
            UINT    DbTriack        :1;     /* DB方式三端双向可控硅              DB方法可控硅         */
            UINT    PerClrEdge      :1;     /* 位置偏差清除信号边缘选择 0:电平，1:边沿                   */
            UINT    PerClrMecha     :1;     /* 位置偏差修正的基准（以机械位置为基准的修正位置） */

            UINT    AutoRun         :1;     /* 试验用自动运转模式                                        */
            UINT    BoardSel        :1;     /* 选择控制基板                                               */
            UINT    TrefTrqFF       :1;     /* 将T-REF用作转矩前馈输入 Pn002.0==2                        */
            UINT    TrefTrqLmt      :1;     /* 将T-REF用作外部模拟量转矩限制，Pn002.0==1             */
            UINT    TrefTrqLmtCL    :1;     /* 限制信号(P-CL,N-CL)有效时，将T-REF用作外部转矩限制输入Pn002.0==3    */
            UINT    VrefSpdLmt      :1;     /* 使用速度指令作为外部速度限制                           */
            UINT    PosConvMode     :1;     /* 马达位置指令单位变换模式设定                               */
            UINT    CtrlSW3Step     :1;     /* 控制切换选择设定,仅通信式有效                              */
            UINT    ComCycleFil     :1;     /* 通信周期移动平均选择设定                                 */
            UINT    OptBkControl    :1;     /* 制动器指令选择设定            */
            UINT    IPSpdControl    :1;     /* 速度环控方法选择 0:PI控制;1:I-P控制              */
            UINT    CmdPDT          :1;     /* 指令预测选择设定                                         */
            UINT    VrefSpdFF       :1;     /* 位置控制时将速度指令V-REF用作速度前馈输入  Pn207.1     */
            UINT    OvrSpdLimit     :1;     /* 使用电机最高速度/过速检测速度和Pn407两者中最小值作为限速  */
            UINT    CtrlModeCspdPos :1;     /* SGDB兼容模式转换：内部速度/位置控制 是否需要速度先减速到0再切换到位置模式(仅默认IO配置有效)      */
            UINT    CspdChangeCtrl  :1;     /* SGDB兼容模式转换控制：内部速度模式切换到其他模式(速度、位置、转矩控制)时，当SPD-A和SPD-B同时OFF时就进行模式切换，而不需要通过Csel信号切换(仅默认IO配置有效)   */
            UINT    EhVobs          :1;     /* 相位补偿速度观测器选择设置    免调整无效且Pn10B.3==5        */
            UINT    SemiFullSelect  :1;     /* 半关闭/全关闭选择设置                      */
            UINT    ConnectOptMotUse:1;     /* 半封闭编码器使用方法    Semi-closed encoder usage*/
            UINT    OpeDspMode      :1;     /* 操作器参数显示选择 仅初始化 = Pn00B.0                 */
            UINT    CmdOpenCollector:1;     /* 集电极开路信号用位置指令输入滤波器 Pn200.3==1 控制IO输出  */
            UINT    DbOHeatCheck    :1;     //
            UINT    Vobs            :1;     /* 速度FB修正功能设定                                       */
            UINT    CarrChange      :1;     /* 载波频率切换标志 [0:OFF,1:ON]                            */
            UINT    CarrState       :1;     /* 载波频率切换状态 [0:Norm,1:High]         */
            UINT    MpKvvFlg        :1;     /* 主电路电压校正功能选择  [0:OFF,1:ON] PnE39 bit2         */
            UINT    StandAloneMode  :1;     /* 独立模式选择                               */
            UINT    CmdOpSupport    :1;     /* 指令选配件插件对应选择                              */
            UINT    SftOpSupport    :1;     /* 安全选配卡对应选择                        */
            UINT    FbkOpSupport    :1;     /* 反馈选配卡对应选择    PnE09.bit2      */
            UINT    TuningLess      :1;     /* 免调整功能，仅初始化时根据Pn170.0设置，转矩模式无效        */
            UINT    TuningLessVComp :1;     /* 免调整控制有效时的速度指令相位超前补偿                  */
            UINT    STOSupport      :1;     /* STO 端子板                                                  */
            UINT    ULType          :1;     /* 机型选择                                                 */
            UINT    PsFulcSelect    :1;     /* 全闭环控制时使用外部编码器速度作为速度反馈，Pn22A.3设置  */
            UINT    UvTrqLmtCtrl    :1;     /* 主回路电压下降报警时转矩限制选择，Pn008.1             */
            UINT    PoleDetectEnd   :1;     /* 電流零位相位置保存実行フラグ   [0:未完、1:完了]         */
            UINT    InstEnvMon      :1;     /* 安装环境监控有效 PnE0C & 0x8000                      */
            UINT    SnglPhBaseDerate:1;     /* 单相电源输入时放大器过载基极电流延时射击有效               */
    } f;
    USHORT VrefSpdLmtSEL;
    /*----------------------------------------------------------------------------------------------*/
    INT64    AbsPosSoftLimitMax;    /* 绝对值软限位最大值                                       */
    INT64    AbsPosSoftLimitMin;    /* 绝对值软限位最小值                                       */
    /*----------------------------------------------------------------------------------------------*/
    USHORT  CtrlMode;               /* 控制模式                                                 */
    USHORT  CtrlModeA;              /* 控制模式A                                                */
    USHORT  CtrlModeB;              /* 控制模式B                                                */
    USHORT  CtrlModeC;              /* 控制模式C                                                */
    USHORT  CtrlModeInit;           /* 初始控制模式                                             */
    /*----------------------------------------------------------------------------------------------*/
    USHORT  SPDSource;              /* 速度指令源选择                                          */
    USHORT  POSSource;              /* 位置指令源选择                                          */
    USHORT  TORSource;              /* 转矩指令源选择                                          */
    /*----------------------------------------------------------------------------------------------*/
    IMAP    Imap;                   /* 输入信号                                                 */
    OMAP    Omap;                   /* 输出信号                                                 */
    UCHAR   OffStopMode;            /* 伺服OFF发生时减速停机的方式                              */
    UCHAR   StopMode;               /* 伺服OFF与发生G1警报时的停止方式   Pn006.1                 */
    UCHAR   OtStopMode;             /* 超程(OT)时的停机方式             Pn007.X                 */
    UCHAR   OtPErrorclr;            /* 超程(OT)时脉冲偏差清除方式                               */
    USHORT  PPolarity;              /* 外部脉冲方向更改                                         */

    EGEAR   Egear;                  // 位置指令电子齿轮         */
    EGEAR   Egear0;                 /* 位置指令电子齿轮（电子齿轮无效时）                            */
    EGEAR   sfgear;                 /* 齿轮结构                         */
    EGEAR   Ethfgear;               /* EtherCat 给定的电子齿轮比                */
    EGEAR   CANgear;
    /*----------------------------------------------------------------------------------------------*/
	CHAR    DirSign;                /* 回転モード演算用(+1/-1)      Rotation mode for operation */
    UCHAR   PcmdFilter;             /* 位置指令滤波器选择设定，Pn207.0，已经没用了                */
    UCHAR   BacklashDir;            /* 齿隙补正方向选择设定,Pn230.0                               */
    UCHAR   BacklashEn;             /* 齿隙补偿开关                                             */
    UCHAR   PGAINSet;               /* 外部脉冲倍率切换                                         */
    UCHAR   FanContMode;            /* 风扇控制模式                                             */
    UCHAR   PerClrMode;             /* 位置偏差清除动作选择设置 Pn200.2                         */
    UCHAR   PerClrSigSel;           /* 位置偏差清除信号形态选择设定   Pn200.1                     */
    UCHAR   PerClrLvlSel;           /* 位置偏差清除信号电平选择设置,1:高电平清除,2:低电平,0:沿 */
    UCHAR   ABSEncMOVSel;           /* 绝对值编码器多圈溢出监测开关                             */
    /*------------------------------------------------------------------------------------------*/
    UCHAR   IncEncHallSel;          /* 霍尔角度使用方法                                         */
    UCHAR   IncEncZlachSel;         /* Z信号锁存值                                              */
    UCHAR   IncEncResSel;           /* 增量式编码器分辨率使用                                   */
    UCHAR   IncEncType;             /* 增量式编码器类型                                         */
    UCHAR   IncPowerFlag;           /* 增量式编码器电源使用标志                                 */
    /*------------------------------------------------------------------------------------------*/
    UCHAR   MosfetPumpFlag;         /* 单管自举开关                                             */
    UCHAR   CurICSel;               /* 电流采样IC选择(0:C796;1:AM1305)                          */
    UCHAR   FATest1;
    UCHAR   FATest2;
    UCHAR    VdetMode;               /* 主电路母线电压检测方式  PnE0C.2 (AD)                    */
    UCHAR   VdcdetAlmFilter;        /* 主回路检测异常报警滤波器             (1=250us)           */
    UCHAR   OvdetAlmFilter;         /* 过电压报警滤波器 (1=250us)   */
    UCHAR   RegStartFilter;         /* 再生动作开始过滤器    (1=250us)           */
    UCHAR   RegStopFilter;          /* 再生动作开始过滤器    (1=250us)       */
    UCHAR   RgSumSel;               /* 再生过载检测用初始值比例选择                           */
    UCHAR   RlyDbWay;               /* 突入/DB控制方法选择设置    PnE0C.bit4,bit5                 */
    UCHAR   MFC_type;               /* MFC处理类型选择Pn14F.0==1:SGDV_TYPE(默认提高分辨率), 0:SGDX_TYPE      */
    UCHAR   TuningLessType;         /* 免调整类型Pn14F.1，0:鲁棒性(无滤波器)；1:低噪音(有滤波器)*/
    UCHAR   TuningLessEx;           // 免调整新调整部分开关
    /*----------------------------------------------------------------------------------------------*/
    USHORT   MosfetType;             /* 驱动器硬件版本                                           */

    USHORT  VdetPrmOk;              /* 主回路检测相关参数OK  (1=OK)                              */
    USHORT  OvLevel;                /* 主回路过压报警阀值 PnE71      [Vmax/255]                  */
    USHORT  UvLevel;                /* 主回路欠压报警阀值 PnE73      [Vmax/255]                  */
    USHORT  Uv2Level;               /* UV2（DB制动用ChargePump驱动允许电压）检测电平           */
    USHORT	RegOnLevel;			  /* 回生电阻器闭合电压 PnE72      [Vmax/255]                  */
    USHORT	RegOffLevel;		  /* 回生电阻器段开电压 (PnE72 - PnE78)[Vmax/255]              */
    USHORT	UvWrnLevel;			  /* 主回路欠压警告检测水平 PnE7B    [Vmax/255]                */
    #if(FLOAT_USE == 1)
    float   VdetAdNorm;            /* 主回路检测AD值变换到标幺值的系数                         */
    float    Kdcvolt;              /* 主回路母线电压转成V单位系数                              */
    float   Kdcvolt1;
    #else
    LONG    VdetAdNorm;
    LONG    Kdcvolt;
    #endif
    LONG    MaxSpd;                 /* 系统最大运行速度                                         */
    LONG    EthCatMaxSpd;           /* EtherCat 系统最大运行速度                                */
    /*----------------------------------------------------------------------------------------------*/
    USHORT  TuningLessMode;         /* 免调整模式                                                */
    /*----------------------------------------------------------------------------------------------*/
    USHORT  SvCycleUs;              /* 伺服控制周期[us]       125                                 */
    LONG    SvCycleNs;              /* 伺服控制周期[ns]                                           */
    /*----------------------------------------------------------------------------------------------*/
    KSGAIN  PcmdOvrSpd;             /* 位置指令过速(ＯＳ)           [pulse/SvCycle]             */
/*----------------------------------------------------------------------------------------------*/
    LONG    Kposlvl;                /* Position Level Cal. Factor   [CmdPulse --> FbkPulse]     */
    LONG    Kspdlvl;                /* Speed    Level Cal. Factor   [0.1r/min,mm/s --> NorSpd]  */
    LONG    Ktrqlvl;                /* Torque   Level Cal. Factor   [0.01% --> 2^24/MaxTrq]     */
    LONG    Ktrqlvls;               /* Torque   Level Cal. Factor   [0.01% --> 15000/MaxTrq]    */
    float   fKspdlvl;
    float   fKtrqlvl;
    float   fKtrqlvls;

    /*----------------------------------------------------------------------------------------------*/
    LONG    Knorspd;                /* Normal. Speed Trans Factor   [r/min,mm/s --> NorSpd]     */
    LONG    Knortrq;                /* Normal. Torque Trans Factor  [%RatedTorque --> NorTrq]   */
    LONG    Kmonspd;                /* Monitor Speed Trans Factor   [NorSpd  --> r/min,mm/s]    */
    LONG    Kmonspd1;               /* Monitor Speed Trans Factor   [NorSpd  --> r/min,mm/s]    */
    LONG    Kmonspdrads;
    float   fKmonspd;
    float   fKmonspd1;

    LONG    Kmontrq;                /* Monitor Torque Trans Factor  [NorTrq  --> %RatedTorque]  */
    LONG    kmontrq1;
    LONG    kmontrq2;
    float   fKmontrq;
    float   fkmontrq1;
    float   fkmontrq2;
    float   fKmoncrnt;

    LONG    Kmoncrnt;               /* Monitor Current Trans Factor [NorCurrent->%RatedCurrent] */
    LONG    Kmonpfbkspd;            /* Monitor PfbkSpd Trans Factor [p/64ms  --> r/min,mm/s]    */


    #if(FLOAT_USE == 1)
    float   fKmoncrntA;             /* 电流监控转换系数s [NorCurrent-> 0.1A]         */

    float   fKmonpcmdspd;           /* Monitor PcmdSpd Trans Factor [p/64ms  --> r/min,mm/s]    */
    float   fKmonpcmdspd2ms;        /* Monitor PcmdSpd Trans Factor [p/2ms   --> r/min,mm/s]    */
    float   fKnorpulsspd;           /* Monitor PulsSpd Trans Factor [p/ScanB --> 2^24/OvrSpd]   */
    #else
    LONG    KmoncrntA;

    LONG    Kmonpcmdspd;
    LONG    Kmonpcmdspd2ms;
    LONG    Knorpulsspd;
    #endif
    /*----------------------------------------------------------------------------------------------*/
    LONG    SpdDetectUnit;          /* 速度检测分辨率  [0.1r/min/pulse],[0.1mm/s/pulse]        */
    /*----------------------------------------------------------------------------------------------*/
    LONG    TrefonLevel;            /* 扭矩指令输入ON电平               [2^24/MaxTrq]*/
    LONG    OrgSrchSpeed;           /* 原点搜索速度   初始化时固定为60rpm    [2^24/OvrSpd]           */
    /*----------------------------------------------------------------------------------------------*/
    USHORT  SpdFbLpassFil;          /* 电机静音用速度FBLPF设定[0.01ms]*/
    /*------------------------------------------------------------------------------------------*/
    USHORT  iCHausAdj;             /* iCHaus芯片配置                                     */
    USHORT  ServoSeries;            /* 伺服系列     0:SD710                                     */
                                   /*              1:SD100                                     */
} IPRMDAT;
 
  
/*      公共参数定义：可在线更改的公共参数（用于多个模块）    */
typedef	struct
{
/*--------------------------------------------------------------------------------------------------*/
    struct	{
        UINT    NotchFil2       :1;     /* 第2段陷波滤器使用/不使用        */
        UINT    LpassFil2       :1;     /* 第2段2次转矩滤波器使用/不使用 Pn40F<5000                  */
        UINT    LpassFil3       :1;     /* 转矩补偿后1次滤波器(CPU)使用／不使用                        */
        UINT    Dobs            :1;     /* 干扰观测器选择设定,即摩擦补偿功能，Pn408.3                */
        UINT    AresVibControl  :1;     /* A型减振控制设定Pn170.0==0且Pn160.0==1时有效         */
        UINT    PosStbCtrl      :1;
        UINT    AvffFilter      :1;     /* 振动抑制滤波器设置 Pn140.0==1且Pn140.1==2 时有效          */
        UINT    MFCFF           :1;     /* 同时使用MFC和外部模拟量输入速度前馈/转矩前馈 Pn140.3     */
        UINT    VelRippleComp   :1;     /* 齿槽转矩补偿功能设定 Pn423.0                               */
        UINT    RipCmpThreshold :1;     /* 齿槽转矩补偿                                             */
        UINT    TuningLess      :1;     // 免调整功能，初始化时根据Pn170.0设置，转矩模式无效,部分辅助功能启动时会设为无效,接收辅助功能后再变为原值
        UINT    TuningLessVComp :1;     /* 免调整相位超前补偿设定Pn170.1，0:用作速度控制，1:将上位装置用于位置控制    */
        UINT    AtGsel          :1;     /* 自动增益切换选择设置, 初始化时Pn139.0设置                */
        UINT    PdetEnable      :1;     /* 基于参数的磁极检测设定  */
    } f;
    /*----------------------------------------------------------------------------------------------*/
    UCHAR   MSW;                    /* 模式开关切换条件选择(P/PI自动切换)，Pn10B.0             */
    UCHAR   MFCModel;               /* MFC机械模型设置, Pn240.10=01时,ONE_MASS, Pn140.10=11或21时,ONE_BASE   */
    /*----------------------------------------------------------------------------------------------*/
    UCHAR   AtGselTrgA;             /* 自动增益切换条件A选择设定    Pn139.1                     */
    /*----------------------------------------------------------------------------------------------*/
    LONG    MSWTrqLevel;            /* 模式开关转矩电平 [2^24/MaxTrq]*/
    LONG    MSWSpdLevel;            /* 模式开关速度电平  [2^24/OvrSpd]*/
    LONG    MSWAccLevel;            /* 模式开关加速度电平 [NorSpd/ScanC]*/
    LONG    MSWErrLevel;            /* 模式开关偏差电平  [Pulse, mm]*/
    /*----------------------------------------------------------------------------------------------*/
	LONG    FenseSpdLevel;          /* 全闭环速度阈值                                           */
	LONG    CoinLevel;              /* 定位完成宽度       Pn262                    [指令単位]     */
    LONG    NearLevel;              /* Near信号宽度     Pn260                    [指令単位]     */
    LONG    VcmpSpdLevel;           /* 速度一致検出幅  Pn320                    [2^24/OvrSpd]  */
    LONG    EthVcmpSpdLevel;        /* 速度一致检出幅值(EtherCat 机型)                          */
    LONG    EthVcmpSpdWrmLev;        /* 速度一致检出幅值(EtherCat 机型)                          */
    LONG    TgonSpdLevel;           /* 电机旋转检测水平 Pn317                    [2^24/OvrSpd]  */
    LONG    LowSpdLevel;           /* 电机速度增益切换阈值                    [2^24/OvrSpd]  */
    LONG    EthTgonSpdLevel;        /* 电机旋转检测幅值(EtherCAT 机型)                          */
    LONG    VibCheckLevel;          /* 振动检测阀值，=3*Pn187(振动检出值)*Pn186(振动灵敏度%) 默认381300    [2^24/OvrSpd]   */
    LONG    VibCheckLevelForTunLess;/* 自动陷波用振动监测水平 固定60.4rpm         [2^24/OvrSpd]  */
    LONG    JstVibCheckLevel;       // 惯量辨识中振动检出水平 Pn325(不看见250rpm)[2^24/OvrSpd]    */
    /*----------------------------------------------------------------------------------------------*/
    LONG    BkonSpdLevel;           /* 制动指令输出速度阀值(Pn507)                 [2^24/OvrSpd]  */
    USHORT  BkonWaitTime;           /* 伺服OFF-制动器指令等待时间(Pn508)               [ms]    */
    USHORT  BkonDelayTime;          /* 制动器指令-伺服OFF延迟时间(Pn506)               [ms]    */
    LONG    ZclampSpdLevel;         /* 零速箝位速度阀值(Pn501)                  [2^24/OvrSpd]   */
    LONG    ZclampMaxSpd;
    /*----------------------------------------------------------------------------------------------*/
    LONG    PerAlmLevel;            /* 位置偏差过大警报值(Pn520)                 [指令単位]  */
    LONG    PerWrnLevel;            /* 位置偏差过大警告值(Pn520*Pn51E%)              [指令単位]  */
    LONG    SvonPerAlmLevel;        /* 伺服ON时位置偏差过大报警水平Pn526         [指令単位]  */
    LONG    SvonPerWrnLevel;        /* 伺服ON时位置偏差过大警告水平Pn526*Pn528%      [指令単位]  */
    LONG    SvonSpdLmtLevel;        /* 伺服ON时速度限制等级(Pn529)                [2^24/OvrSpd]  */
    LONG    SvonSpdLmtValue;        /* 伺服ON时速度限制值(Pn529/10)              [2^24/OvrSpd]  */
    /*----------------------------------------------------------------------------------------------*/
	ULONG   fpgoverLevel;           /* モータ-負荷位置間偏差過大検出レベル           [指令単位]  */
		                                        /* Load position between the deviation excess detection level*/
	ULONG   fpgclcLevel;            /* 混合偏差过大清除阈值                                     */

    SHORT   XFilterTime;            /* 外部输入信号滤波时间                                     */
    /*----------------------------------------------------------------------------------------------*/
    LONG    FwIntTrqLmt;            /* 正转内部转矩限制 Pn402                    [2^24/MaxTrq]  */
    LONG    RvIntTrqLmt;            /* 反转内部转矩限制 Pn403                    [2^24/MaxTrq]  */
    LONG    FwExtTrqLmt;            /* 正转外部转矩限制 Pn404                    [2^24/MaxTrq]  */
    LONG    RvExtTrqLmt;            /* 反转外部转矩限制 Pn405                    [2^24/MaxTrq]  */
    LONG    EstopTrqLmt;            /* 紧急停止(行程限位)转矩 Pn406                [2^24/MaxTrq]  */
	LONG    UvTrqLmt;               /* 主电路电压下降时转矩限制,由Pn424设置         [2^24/MaxTrq]  */
    LONG    DeltaUvTrqLmt;          /* 主回路电压恢复时转矩限制增量                [2^24/MaxTrq]  */
    LONG    TrqObjReach1;           /* 转矩到达设定值1                         [2^24/MaxTrq]  */
    LONG    TrqObjReach2;           /* 转矩到达设定值2                         [2^24/MaxTrq]  */
    LONG    TReachSpdLevel;         /* 目标转矩到达速度阈值                      [2^24/MaxTrq]    */
    LONG    EthMaxTorq;             /* EtherCat 限定最大转矩                   [2^24/MaxTrq]  */
    LONG    EthMaxPTorq;            /* EtherCat 正向最大转矩                   [2^24/MaxTrq]  */
    LONG    EthMaxNTorq;            /* EtherCat 负向最大转矩                   [2^24/MaxTrq]  */
    LONG    EthMaxSpd;              /* EtherCat 最大运行速度                                    */
    /*----------------------------------------------------------------------------------------------*/
    LONG    RemVibDetWidth;         /* 残留振动(低频晃动)频率检出幅值,Pn560*Pn522 [pls]       */
    LONG    RemVibFil;              /* 残留振动(低频晃动)频率检出用位置偏差滤波频率,固定500    [Hz]*/
    /*----------------------------------------------------------------------------------------------*/
    LONG    OvsErrDetLvl;           /* 允许的超调量   Pn522*Pn561                     [指令単位]  */
} GPRMDAT;
 
  
  
  
/****************************************Kernel I/O服务变量定义*****************************************/
/*      本地变量定义   */
/*      Kernel I/O服务参数定义    */
typedef	struct {
    LONG    Kpcmpd;                     /* Pcmpd Calculate Gain                                 */
    LONG    Kpcmpd2;                    /* Pcmpd Calculate Gain ( bug modify value)             */
    float   fKpcmpd;
    float   fKpcmpd2;
} KIOP;

/*      Kernel I/O服务参数定义    */
typedef	struct {
    /*----------------------------------------------------------------------------------------------*/
    struct {
    UCHAR   PumpOnComp;             /* Charge Pump Complete                                     */
    UCHAR   PastInputClrEdge;       /*                              */
    UCHAR   LastPcov;               /* 中间电位异常信号（正逻辑）上次值                         */
    UCHAR    RegAlmMotStop;          /* 再生过载警报发生后电机停止检测标志                */
    } f;
    /*----------------------------------------------------------------------------------------------*/
    LONG    MotPosA;                    /* 电机位置 for ScanA           [pulse]             */
    LONG    MotPosB;                    /* 电机位置 for ScanB           [pulse]             */
    LONG    MotPosC;                    /* 电机位置 for ScanC           [pulse]             */
    /*----------------------------------------------------------------------------------------------*/
    LONG    PcmdCntrC;                  /* 脉冲计数 for ScanC   [pulse]             */
    /*----------------------------------------------------------------------------------------------*/
    UCHAR   RegStartCnt;                /* 再生动作开始等待计数器                          */
    UCHAR   RegStopCnt;                 /* 再生动作结束等待计数器                          */
    UCHAR   RegOn;                      /* Regene.Tr On Flag                                */
    UCHAR   RegDuty;                    /* 再生制动占空比                                    */
    SHORT   RegOnCount[2];              /* 再生晶体管ON时间计数器[125us]                  */
    /*----------------------------------------------------------------------------------------------*/
    USHORT  SvonPumpCnt;                /* Charge pump for before Base-Enable                   */
    USHORT  SvonRelayCnt;               /*                      */
	
	LONG    FencPosB;                   /* Fenc  Position (Ring)        [32bitRingPulse]        */		
    /*----------------------------------------------------------------------------------------------*/
    LONG    MotSpdSumB;                 /* Motor Speed Sum for ScanB                            */
    LONG    MotSpdCntB;                 /* Motor Speed Cnt for ScanB                            */
    LONG    MotSpdSumC;                 /* Motor Speed Sum for ScanC                            */
    LONG    MotSpdCntC;                 /* Motor Speed Cnt for ScanC                            */

    /*----------------------------------------------------------------------------------------------*/
    LONG    FencSpdSumB;                 /* Motor Speed Sum for ScanB                            */
    LONG    FencSpdCntB;                 /* Motor Speed Cnt for ScanB                            */
    LONG    FencSpdSumC;                 /* Motor Speed Sum for ScanC                            */
    LONG    FencSpdCntC;                 /* Motor Speed Cnt for ScanC                            */
/*----------------------------------------------------------------------------------------------*/
} KIOV;
 
extern KIOP	KioP;							 
extern KIOV	KioV;							 
 
  
  
  
/********************************Round 输入输出变量定义**********************************************/
/*      Round 输入变量定义    */
typedef struct
{
/*--------------------------------------------------------------------------------------------------*/
        struct {
        UINT    BaseEnable      :1;         /* Base Enable Flag，仅在APL_Main()中=CoutV.f.Sv.BaseEnable(真使能)    */
        UINT    SftRstReq       :1;         /* 软件复位要求,通过辅助功能Fn030设置，在Round中处理   */
        UINT    Spare02         :1;         /* Spare02                                              */
        UINT    Spare03         :1;         /* Spare03                                              */
        } f;
    /*----------------------------------------------------------------------------------------------*/
        USHORT  Sample00;                   /* Sample Variable                                      */
        USHORT  Sample01;                   /* Sample Variable                                      */
/*--------------------------------------------------------------------------------------------------*/
} RINV;
 
/*     Round 输出变量定义    */
typedef	struct
{
    /*--------------------------------------------------------------------------------------------------*/
    struct {
        UINT	RndReady 		:1;         /* Round Ready  执行过第一次ROUND后为TRUE               */
        UINT	SvonReq 		:1;         /* Round ServoOn Request，由辅助功能写入伺服使能开关指令*/
        UINT	SensOnReq		:1;         /* Round SensOn Request，由辅助功能写入绝对位置请求       */
        UINT	TuningRun		:1;         /* 伺服调整中                                            */
        UINT	TuningPctrlRun	:1;         /* 伺服位置控制调整中                                    */
        UINT	TuningFuncRun	:1;         /* 伺服调整辅助功能中,仅免调整Fn200开始和结束设置1或0    */
        UINT	PdetReq			:1;         /* 磁极检出请求伺服ON, 仅Fn080设置             */
        UINT	ActiveFFtOn		:1;         /* 仅Fn200调整刚性发生高频音时，按DATA/SHIFT键强制要求FFT*/
        UINT	TunLessCtrlOffSts	:1;     /* 免调整强制无效标志                                    */
    } f;
    /*----------------------------------------------------------------------------------------------*/
    USHORT  CtrlMcmd;                   /* 由辅助功能设置的控制模式指令 --> 然后在ScanC的模式控制中如果有辅助功能传给最终的模式CoutV.CtrlMcmd.us[0]  */
    USHORT  Spare001;                   /* Spare for alignment                                  */
    LONG    JogSpeed;                   /* JOG速度指令 +:正转、-:反转                            */
    /*----------------------------------------------------------------------------------------------*/
    SHORT   MencMultiTurn;              /* 0xE600 : 绝对值编码器多圈值(仅Fn2002中锁存)           */
    ULONG   MencIncPulse;               /* 0xE601 : 绝对值编码器单圈值(仅Fn2002中锁存)           */
    ULONG   MencIncPulseOri;            /* 0xE601 : 绝对值编码器单圈值(仅Fn2002中锁存)           */
    /*----------------------------------------------------------------------------------------------*/
    ULONG   ABSEncSValue;               /* 0xE010: 绝对值编码器一圈内置                         */
    ULONG   ABSEncSValueOri;            /* 0xE010: 绝对值编码器一圈内置                         */
    SHORT   ABSEncMValue;               /* 0xE010: 绝对值编码器多圈值                           */
    LONG    ScaleAbsPosL;               /* 0xE603 : 绝对值编码器绝对位置(下位)                  */
    LONG    ScaleAbsPosH;               /* 0xE605 : 绝对值编码器绝对位置(上位)                  */
    LONG    MechAbsPosL;                /* 0xE607 : 机械绝对位置(上位)                          */
    LONG    MechAbsPosH;                /* 0xE609 : 机械绝对位置(下位)                          */
    /*----------------------------------------------------------------------------------------------*/
    UCHAR   OutModeFlg;                 /* 强制输出模式标志 Fn200E使用                            */
    HWSOUT  ForceOutSig;                /* 强制输出信号数据                                 */
    /*----------------------------------------------------------------------------------------------*/
    UCHAR   ScaleWrMoniState;           /* Scale Write Result Monitor Status                    */
    SHORT   ScaleOrgSetAgFlg;           /* 0xC029 : 绝对值线性标尺原点位置设定允许状态   */
    LONG    ScaleOrgSetCH;              /* 绝对值线性标尺原点位置设定执行通道        */
    /*--------------------------------------------------------------------------------------------------*/
} ROUTV;
 
  
extern	RINV	RinV;
extern	ROUTV	RoutV;						 
 
  
  
 
/*      ScanC 输入变量定义    */
typedef	struct
{
    /*----------------------------------------------------------------------------------------------*/
    struct {
        UCHAR	SvonEnable;     /* ServoOn Enable   执行过第一次KpxInputScanC()后为TRUE     */
        UCHAR	PumpOnComp;     /* Charge Pump Complete                                     */
        UCHAR	EncReady;       /* 编码器 Ready, 连接且已向上位装置输出绝对位置               */
        UCHAR   Pcov;           /* 中间电位异常信号（正逻辑）                                */
    } f;
    /*----------------------------------------------------------------------------------------------*/
    LONG    MotPos;                 /* Motor Position (Ring)    [pulse]                         */
    LONG    dMotPos;                /* Delta Motor Position     [pulse/ScanC]                   */
    LONG    MotSpd;                 /* 2ms内平均Motor Speed        [2^24/OvrSpd]                   */
    LONG    FencSpd;                 /* 2ms内平均负载端 Speed        [2^24/OvrSpd]                   */
    LONG    AbsMotSpd;              /* Absolute Motor Speed     [2^24/OvrSpd]                   */
    /*----------------------------------------------------------------------------------------------*/
    LONG    PcmdCntr;               /* Pulse Command Counter    [pulse]                         */
    LONG    dPcmdCnt;               /* 脉冲增量指令       [pulse]                         */
    /*----------------------------------------------------------------------------------------------*/
    LONG    TrqRefMon;              /* Torque Reference         [2^24/MaxTrq]                   */
    LONG    AbsTrqRefMon;           /* Absolute Torque Ref      [2^24/MaxTrq]                   */
    /*----------------------------------------------------------------------------------------------*/
    SHORT   IdRefMon;               /* d轴电流指令监控     [15000/Imax]                    */
    SHORT   IqRefMon;               /* q轴电流指令监控     [15000/Imax]                    */
    /*----------------------------------------------------------------------------------------------*/
    SHORT   IqFbMon;                /* q轴电流FB监控         [15000/Imax]                */
    SHORT   IdFbMon;                /* d轴电流FB监控         [15000/Imax]                */
    /*----------------------------------------------------------------------------------------------*/
    SHORT   DcVolt;                 /* 主回路母线电压  KpxInputScanC()中 DcVolt= BinK.DcVolt    */
    SHORT   dRegOnCount;            /* Delta Regene.Tr On Count [Count/ScanC]， ScanC周期统计再生晶体管在内ON(125us)的次数,如一直打开为16        */
} CINK;
  
/*      ScanC 输出变量定义    */
typedef	struct
{
    /*--------------------------------------------------------------------------------------------------*/
    HWSOUT  hw;                     /* HW输出信号                                           */
    /*----------------------------------------------------------------------------------------------*/
    struct {
        UINT  AlmRst          :1;     /* Alarm Reset                                              */
        UINT    PumpOnReq       :1;     /* Charge Pump Control Request to Kernel                    */
        UINT    PumpOnDBReq     :1;     /* DBCharge Pump Control Request to Kernel (SJDE)未用         */
        UINT    Acon            :1;     /* AC交流电源接通  主回路AC电源输入正常(规定时间内只要有一次即可)，DC模式下为FALSE      */
        UINT    PowerOn         :1;     /* 控制板主电源ON信号，AC电源ON后主回路母线电压超过欠压值180ms，且电机停止状态持续到240ms  */
        UINT    PowerOnEep      :1;     /* 主電源ＯＮ信号(Eeprom管理用)   AC电源ON后主回路母线电压超过欠压值240ms，否则一旦欠压为FALSE   */
        UINT    SvonReq         :1;     /* Servo ON Request                                         */
        UINT    DbBeReq         :1;     /* DbSequence BaseEnable Request    DB时序请求伺服使能      */
        UINT    MotStop         :1;     /* Motor Stop Signal                                        */
        UINT    BaseEnable      :1;     /* Base Enable  真实使能                                    */
        UINT    Ot              :1;     /* OT State Signal  发生与指令方向同向的超程(无需使能)      */
        UINT    HwbbState       :1;     /* Hard-wired Baseblock Status 硬件基极封锁 HWBB 仅测试电流调零用     */

        UCHAR    RndSvControl;           /* Round Servo Control Flag 由辅助功能设置                 */
    } f;
 } COUTK;
  
 
extern	CINK	CinK;					 
extern	COUTK	CoutK;					 
  
 
  
/****************************************中间参数定义*****************************************/
  
typedef	struct
{
    /*--------------------------------------------------------------------------------------------------*/
    KSGAIN  Kpx;                    /* Position Control Gain                                    */
    KSGAIN  Kvx;                    /* Speed    Control Gain                                    */
    KSGAIN  Kpvx;                   /* Position-Speed Control Gain for MFC & Predictive Control */
    KSGAIN  Kmotspd;                /* Motor Speed Cal. Gain  [pulse/sec] --> [2^24/OvrSpd]     */
    KSGAIN  KmotspdFC;              /* Motor Speed Cal. Gain  [pulse/sec] --> [2^24/OvrSpd]     */
/*--------------------------------------------------------------------------------------------------*/
    float   fKvx;
    float   fKpx;
    float   fKmotspd;
	float   fKmotspdFC;
  
} HPRMDAT;
extern	HPRMDAT	Hprm;					 
 
 
 
extern IPRMDAT Iprm;
extern GPRMDAT Gprm;
extern BINV	BinV;
extern BOUTV BoutV;							 
extern BORST BoutRrst;
extern BINK	BinK;					         
extern BOUTK	BoutK;					     
extern CINV CinV;							   
extern COUTV CoutV;							 
extern CORST CoutRrst;
extern void VarDef_Init( void );
extern void IprmVarInit( void );
extern void HprmCommonMotorParamCal( void );
extern void	IprmcalUnitTransFacter( void );
extern void	IprmcalPcmdOvrSpd( void );
extern void	IprmcalBitParam000( void );
#endif
