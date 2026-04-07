/*
 * User12_FunOpeReg.h
 *
 *  Created on: 2017骞�08鏈�09鏃�
 *      Author: zhuxc
 */

#include "Mot28_OnlineFFT.h"
   
#ifndef __User12_FunOpeReg_H__
#define __User12_FunOpeReg_H__

#include "Main.h"
#include "UserGroble.h"
   

/*--------------------------------------------------------------------------------------------------*/
/*		銈兗銉堛儊銉ャ兗銉嬨兂銈般偍銉偄锛�2400H - 25FFH								Auto-tuning area            */
/*--------------------------------------------------------------------------------------------------*/
typedef	struct	{
		FRQANAV	VibmRf[3];				/* 0x2400 : 鍦ㄧ嚎鎸姩鐩戣绗�1鍏辨尟棰戠巼							*/
										/* 0x2401 : 鍦ㄧ嚎鎸姩鐩戣绗�1鍏辨尟鎸箙							*/
										/* 0x2402 : 鍦ㄧ嚎鎸姩鐩戣绗�2鍏辨尟棰戠巼							*/
										/* 0x2403 : 鍦ㄧ嚎鎸姩鐩戣绗�2鍏辨尟鎸箙							*/
										/* 0x2404 : 鍦ㄧ嚎鎸姩鐩戣绗�3鍏辨尟棰戠巼							*/
										/* 0x2405 : 鍦ㄧ嚎鎸姩鐩戣绗�3鍏辨尟鎸箙							*/
		FRQANAV	VibmAf;					/* 0x2406 : 鍦ㄧ嚎鎸姩鐩戣绗�1鍙嶅叡鎸鐜�						*/
										/* 0x2407 : 鍦ㄧ嚎鎸姩鐩戣绗�1鍙嶅叡鎸尟骞�						*/
	  /*--------------------------------------------------------------------------------------------*/
		USHORT	EzFftDetf;				/* 0x2410 : EasyFFT妫�鍑虹殑鍏辨尟棰戠巼,2娆hirp瀹屽悗寰楀嚭			*/
		USHORT	EzFftFil1;				/* 0x2411 : EasyFFT绗�1娈甸櫡娉㈡护娉㈠櫒棰戠巼						*/
		USHORT	EzFftFil2;				/* 0x2412 : EasyFFT绗�2娈甸櫡娉㈡护娉㈠櫒棰戠巼						*/
	  /*--------------------------------------------------------------------------------------------*/
		USHORT	Jrateid;				/* 0x2420 : 鍚屽畾鎱ｆ�с儮銉笺儭銉炽儓姣擨dentification of inertia moment ratio*/
} ATXREG;
extern ATXREG AtxReg;
   
/****************************************************************************************************/
/*																									*/
/*		銉偢銈广偪澶夋暟瀹氱京	Register variable definition											*/
/*																									*/
/****************************************************************************************************/
/*--------------------------------------------------------------------------------------------------*/
/*		銉偢銈广偪銉囥兗銈裤儞銉冦儓鍨嬪畾缇�	Register data bit type definition 							    */
/*--------------------------------------------------------------------------------------------------*/
typedef	union
{
	struct
	{
		UINT	Bit00		:1 ;
		UINT	Bit01		:1 ;
		UINT	Bit02		:1 ;
		UINT	Bit03		:1 ;
		UINT	Bit04		:1 ;
		UINT	Bit05		:1 ;
		UINT	Bit06		:1 ;
		UINT	Bit07		:1 ;
		UINT	Bit08		:1 ;
		UINT	Bit09		:1 ;
		UINT	Bit10		:1 ;
		UINT	Bit11		:1 ;
		UINT	Bit12		:1 ;
		UINT	Bit13		:1 ;
		UINT	Bit14		:1 ;
		UINT	Bit15		:1 ;
	} f ;
	USHORT	RegData ;
}OPEBIT ;



/*--------------------------------------------------------------------------------------------------*/
/*		鎿嶄綔銈ㄣ儶銈細2000H - 20FFH			Operation area: 2000H - 20FFH						    */
/*--------------------------------------------------------------------------------------------------*/
typedef	struct	{
		USHORT	OpeMode;				/* 0x2000 : 鎿嶄綔妯″紡										*/
		USHORT	OpeCmd;					/* 0x2001 : 鎿嶄綔瑷畾										*/
		USHORT	OpeEnd;					/* 0x2002 : 鎿嶄綔绲備簡										*/
		USHORT	AccLevel;				/* 0x2003 : Access level	鎸塒nE0D.0鍒濆鍖栵紝閫氳繃Fn010淇敼	*/
		USHORT	OpeMode2;				/* 0x2004 : 绗�2鎿嶄綔妯″紡		鍗冲綋鍓嶆鍦ㄨ繍琛岀殑Fn鍙�			*/
		USHORT	OpeCmd2;				/* 0x2005 : 绗紥鎿� 瑷畾 									*/
		USHORT	OpeModeTrc;				/* 0x2006 : 璺熻釜鎿嶄綔妯″紡锛�0:鏃狅紱0x2000:璺熻釜锛�0x200A:杩炵画璺熻釜*/
		USHORT	OpeCmdTrc;				/* 0x2007 : 璺熻釜鎿嶄綔璁惧畾									*/
/*--------------------------------------------------------------------------------------------------*/
		USHORT	SafetyTime;				/* 0x2008 : 瀹夊叏鍋滄鏃堕棿[s]锛屽JOG閫氫俊涓�鐩村彂鎸囦护鐨勯棿闅旀椂闂�	*/
		USHORT	VibmState;				/* 0x2017 : 鍦ㄧ嚎鎸姩鐩戣鐘舵��								*/
		USHORT	PrmWrtDis;				/* 0x2020 : 璁惧畾鍙傛暟鍐欏叆绂佹								*/
		USHORT	PrmAccess;				/* 0x2021 : 銉戙儵銉°兗銈裤偄銈偦銈归枊鏀�				鍙傛暟璁块棶寮�    */
        USHORT  PrmNo;                  /* 閫氳瀵勫瓨鍣ㄥ湴鍧�                                           */
        USHORT  CommType;                /* 閫氳绫诲瀷                                                 */
		USHORT	PjogState;				/* 0x2031 : 銉椼儹銈般儵銉狅吉锛姬閬嬭虎瀹屼簡纰鸿獚	Program JOG operation completion confirmation*/
		USHORT	JogState;				/* 0x2034 : JOG杩愯浆鐘舵��										*//* <V141> */
		USHORT	SpatMode;				/* 0x2050 : 1閿皟鏁存ā寮� 0:娉ㄩ噸绋冲畾鎬�(Kpzeta=100锛屽嵆Kv=Kp),1:娉ㄩ噸鍝嶅簲鎬�(Kpzeta=70锛屽嵆Kv=0.7Kp),2:鏈夋ā鍨嬭拷韪�(鍒濆鍊�),3:鏈夋ā鍨嬭拷韪笖鎶戝埗瓒呰皟			*/
		USHORT	SpatLevel;				/* 0x2051 : 1閿皟璋愬弽棣堝鐩奫0.1Hz]							*/
		USHORT	SpatFFLevel;			/* 0x2052 : 1閿皟璋愬墠棣堝鐩奫0.1Hz]锛屽垵濮嬪寲涓哄彉鏇村墠鐨勬ā鍨嬭拷韪帶鍒跺鐩奒pm(Pn141)	*/
		USHORT	SpatLvlChgState;		/* 0x2053 : 1瀵硅皟鏁寸數锟� 娴狀垈鐡匡拷 							*/
		USHORT	SpatANotchState;		/* 0x2054 : 1閿皟璋愯嚜鍔ㄩ櫡娉㈠櫒璁惧畾鐘舵��						*/
		USHORT	SpatAresState;			/* 0x2055 : 1瀵硅嚜鍔ㄨ皟璋怉鍨嬪畬鎴�								*//* <V113> */
		USHORT	EzFftMode;				/* 0x2060 : EasyFFT妯″紡										*/
		USHORT	EzFftState;				/* 0x2061 : EasyFFT瀹屼簡纰鸿獚,杩涜杩�2娆hirp鍚勬鍙嶅悗瀹屾垚鎴栧叾浠栫粨鏋�*/
		USHORT	EzFftTrq;				/* 0x2062 : EasyFFT杞煩鎸箙锛屽垵濮嬪寲鏃�=Prm.ezffttrq(Pn456)锛屾寜UP鎴朌OWN鍙皟	*/
		USHORT	AdatMode;				/* 0x2090 : 楂樼骇AT妯″紡	0锛氭帹绠楄浆鍔ㄦ儻閲忥紱1锛氫笉鎺ㄧ畻杞姩鎯噺	*/
		USHORT	AdatLevel;				/* 0x2091 : 楂樼骇鑷姩璋冭皭姘村钩 1:鏍囧噯;2:瀹氫綅瀵瑰簲;3:瀹氫綅瀵瑰簲(渚ч噸瓒呰皟)*/
		DWORDX	AdatMovep;				/* 0x2092 : 楂樼骇AT绉诲姩璺濈	[1000鎸囦护鍗曚綅]					*/
		USHORT	AdatState;				/* 0x2094 : 楂樼骇鑷姩璋冭皭鐘舵��								*/
		USHORT	AdatFilType;			/* 0x2095 : 楂樼骇AT婊ゆ尝鍣ㄧ被鍨嬶紝鐢ㄦ潵璁惧畾鍚勭婊ゆ尝涓嶬v涔嬮棿鐨勬瘮渚� 1:鏍囧噯;2:瀹氫綅瀵瑰簲(鍒濆鍊�);3:瀹氫綅瀵瑰簲(渚ч噸瓒呰皟)	*/
		USHORT  AdatDefault;            /*          楂樼骇AT 鐢ㄩ粯璁ゅ弬鏁版垨鑰呭綋鍓嶅弬鏁拌鲸璇�               */
        /*------------------------------------------------------------------------------------------*/
        USHORT	AvibMode;				/* 0x20A0 : A鍨嬫尟鍔ㄨ皟锟� 锛即鏌氾拷 							    */
		USHORT	AvibState;				/* 0x20A1 ; A鍨嬫尟鍔ㄦ锟� 鍒猴拷		 							    */
		USHORT	AvibFreq;				/* 0x20A2 : A鍨嬫姂鎸鐜� 鍒濆鍖�= Pn161锛屽垎鏋愬悗涓篎FT宄板�奸鐜�	*/
		USHORT	AvibGain;				/* 0x20A3 : A鍨嬮樆灏煎姛 鍒濆鍖�= Pn163		                    */
		USHORT	MdlVibFreq;				/* 0x20B0 : MFC鎸姩鎶� 鍒濆鍖�= Pn145		                    */
		USHORT	MdlVibState;			/* 0x20B1 : 鎸姩鎶戝埗鐢∕F 							        */
		USHORT	MdlVibFreq2;			/* 0x20B2 : 鎸姩鎶戝埗鍔熻兘璋冭皭棰戠巼2 		鍒濆鍖�= Pn14A		*/
		USHORT	MdlVibFil2;				/* 0x20B3 : 鎸姩鎶戝埗鍔熻兘锟� 绉板痉锟�2鏍℃ 	鍒濆鍖�= Pn14B		    */
		USHORT	MdlVibState2;			/* 0x20B4 : 鎸姩鎶戝埗鍔熻兘锟� 锟�2瀹屾垚纭 						    */
		USHORT	DatGnLevel;				/* 0x20E0 : 鍏嶈皟鏁村��	 	Pn170.2							*/
		USHORT	DatJratLevel;			/* 0x20E1 : 鍏嶈皟鏁磋礋杞藉��	Pn170.3							*/
        USHORT  EeClrStatus;            /*          缂栫爜鍣ㄧ姸鎬佸瘎瀛樺櫒                                */
        USHORT  EeWriteStatus;          /*          鏁版嵁鍐欏叆缂栫爜鍣ㄧ姸鎬�                              */
        USHORT  EepromErStatus;         /*          Eeprom 鎭㈠鍑哄巶鍊肩姸鎬�                           */
        USHORT  PoleFineTorq;           /*          纾佹瀬杈ㄨ瘑鏃剁數娴佸ぇ灏�                              */
        USHORT  PoleFineStatus;         /*          纾佹瀬杈ㄨ瘑鏃剁姸鎬�                                  */
} OPEREG;
extern	OPEREG	OpeReg;   
   
  /*------------------------------鎯噺杈ㄨ瘑鍙傛暟 20211201 BY MP --------------------------------------*/
 typedef	struct	{
        struct{
        UINT     Adjust_Mod    :2;  /* bit0-1   涓�閿皟鏈烘柟妗�                                        */
        UINT     Check_SevOn   :1;  /* bit3     涓鸿繘琛屾儻閲忚鲸璇嗘柟妗堬紝妫�娴嬩己鏈嶆槸鍚�                         */
        UINT     Inria_Wr      :1;  /* bit4     鎯噺杈ㄨ瘑缁撴灉鍐欏叆                                     */
        UINT     Parm_Rec      :1;  /* bit5     鍙傛暟鎭㈠鏍囧織浣�                                       */
        UINT     Overtrv       :1;  /* bit6     瓒呯▼鏍囧織浣�                                          */
        UINT     Inria_Over    :1;  /* bit7     鍗曟鎯噺杈ㄨ瘑缁撴潫鏍囧織浣�                              */
        UINT     Rigid_Sect    :5;  /* bit8-12     鍒氭�х瓑绾ч�夋嫨鏍囧織浣�                               */
        UINT     Rigid_Wr      :1;  /* bit13     鍒氭�х瓑绾у啓鍏ユ爣蹇椾綅                                 */
        UINT     Rigid_Over    :1;  /* bit2     鍗曟鍒氭�х瓑绾ф祴瀹氱粨鏉熸爣蹇椾綅                          */
        }Flag;                      /* 0x2240鐩稿叧鏍囧織浣�                                             */
        USHORT Jog_Spd;          /*    0x2241 JOG閫熷害                                               */
        USHORT Jog_AccTm;        /*    0x2242 JOG鍔犲噺閫熸椂闂�                                         */
        SHORT  Trv_Max;          /*    0x2243 琛岀▼鑼冨洿鏈�澶у��                                        */
        SHORT  Trv_Min;          /*    0x2244 琛岀▼鑼冨洿鏈�灏忓��                                        */
        SHORT  Trv_Now;          /*    0x2256 璁剧疆琛岀▼鑼冨洿鏃讹紝鐢垫満褰撳墠鐨勫閲忎綅缃�                    */
        SHORT  Stroke_Bar;       /*    0x2245 琛岀▼杞ㄨ抗鏉�                                            */
        USHORT Run_Mod;          /*    0x2246 杩愯妯″紡锛氬崟鍚戣繍鍔細姝ｆ銆佽礋璐燂紱寰�澶嶈繍鍔�;姝ｈ礋銆佽礋姝�   */
        USHORT Run_Cnt;          /*    0x2247 璇曡娆℃暟                                              */
        USHORT Turn_Num;         /*    0x2248 绉诲姩璺濈锛屼互鍦堜负鍗曚綅                                  */
        USHORT Interia_Ratio;    /*    0x2249 鎯噺姣�                                                */
        USHORT Inria_RatioSet;   /*    0x224A 涓嶈繘琛屾儻閲忚鲸璇嗘儻閲忔瘮璁惧畾                              */
        USHORT Rigid_Grade;      /*    0x224B 鍒氭�х瓑绾ц瀹�                                          */
        USHORT Rig_Runmod;       /*    0x224C 鍒氭�ф祴璇曡繍琛屾ā寮�                                      */
        USHORT Rig_MaxSpd;       /*    0x224D 鍒氭�ф祴璇曟渶澶ч�熷害                                      */
        USHORT Rig_TurnNum;      /*    0x224E 鍒氭�ф祴璇曠Щ鍔ㄨ窛绂�                                          */
        USHORT Rig_AccTm;        /*    0x224F 鍒氭�ф祴璇曞姞鍑忛�熸椂闂�                                         */
        USHORT Rig_AdjTm;        /*    0x2250 鏁村畾鏃堕棿                                                */
        USHORT Rig_OvShoot;      /*    0x2251 瓒呰皟閲�                                                  */
        
 }INERTIAREG;
 extern INERTIAREG InertiaReg;   


 typedef struct  {                       /* 鏈哄瀷淇℃伅瀹氫箟                                               */
         USHORT  EncType;                /* 缂栫爜鍣ㄧ被鍨�/鍒嗚鲸鐜�            Encoder type / resolution      */
         USHORT  RatTrq;                 /* 鐢垫満棰濆畾杞煩       [Nm,N]                                  */
         USHORT  TurnSet;               // Turn Setting
 } SVTREG;
extern SVTREG SvtReg;                    /* 姗熺ó瀹氱京銈ㄣ儶銈�              Model defined area              */
   
   
/****************************************************************************************************/
/*																									*/
/*		Write Register Function Prototype															*/
/*																									*/
/****************************************************************************************************/
/*--------------------------------------------------------------------------------------------------*/
/*		Function Return Code Definition																*/
/*--------------------------------------------------------------------------------------------------*/
#define REGWRF_COMPLETE			0x00			/* Write Complete									*/
#define REGWRF_DATAERROR		0x10			/* Write Data Error									*/
#define REGWRF_WRITEFAIL		0x20			/* Write Fail Error									*/
#define REGWRF_WRITEDISABLE		0x21			/* Write Disable Error								*/
#define REGWRF_ACCESSERROR		0x31			/* Write Access Error								*/
#define REGWRF_DATRNGERROR 		0x32			/* Write Data Range Error							*/

/****************************************************************************************************/
/*																									*/
/*		Operation Register Define Structure															*/
/*																									*/
/****************************************************************************************************/
/*--------------------------------------------------------------------------------------------------*/
/*		Operation Register Define Structure															*/
/*--------------------------------------------------------------------------------------------------*/
typedef struct _FORDEF {
	struct	{
	UINT	IsDbyte      :1;					/* DBYTE(1)/Other(0)								*/
	UINT	IsLong       :1;					/* LONG(1)/Other(0)									*/
	UINT	BgnData      :1;					/* BeginData(1)/Other(0)							*/
	UINT	EndData      :1;					/* EndData(1)/Other(0)								*/
	UINT	WithSign     :1;					/* WithSign(1)/WithoutSign(0)						*/
	UINT	ReadEnable   :1;					/* ReadEnable(1)/ReadDisable(0)						*/
	UINT	WriteEnable  :1;					/* WriteEnable(1)/WriteDisable(0)					*/
	UINT	Spare007     :1;					/* Spare											*/
	} Attr;										/* Attribute										*/
/*--------------------------------------------------------------------------------------------------*/
	USHORT	Rno;								/* Register No.										*/
	USHORT	IniVal;								/* Initial Value									*/
	DBYTEX	Llimit;								/* Lower Limit										*/
	DBYTEX	Ulimit;								/* Upper Limit										*/
	void*	VarAdr;								/* Variable Address									*/
/*--------------------------------------------------------------------------------------------------*/
	LONG	(*ReadRegFunc)						/* Read Data to Register Function					*/
			( const struct _FORDEF* pForDef, USHORT* pRdData, void* Hmsg );
	LONG	(*WriteRegFunc)						/* Write Data to Register Function					*/
			( const struct _FORDEF* pForDef, ULONG  WrData,  void* Hmsg );
} FORDEF;
typedef const FORDEF CFORDEF;					/* const Type Definition							*/

/****************************************************************************************************/
/*																									*/
/*		Operation Register Define Table Extern														*/
/*																									*/
/****************************************************************************************************/
extern  const FORDEF FunOpeRegDefTbl[];			/* OpeReg Define Table								*/
/*--------------------------------------------------------------------------------------------------*/
extern  const USHORT FunOpeRegDefTblEntNum;		/* OpeReg Define Table Entry Number					*/
/*--------------------------------------------------------------------------------------------------*/
extern  const USHORT FunOpeRegDefTblUserEntNum;	/* OpeReg Define Table Entry Number					*/
/*--------------------------------------------------------------------------------------------------*/
/*		Define Entry Number																			*/
/*--------------------------------------------------------------------------------------------------*/
#define FUNOPEREGDEFTBL_ENTNUM	FunOpeRegDefTblEntNum
/*--------------------------------------------------------------------------------------------------*/




LONG	RpxWriteTrcOpeRegister( CFORDEF* pForDef, ULONG  WrData,  void* Hmsg );
LONG	RpxWriteTdrvOpeRegister( CFORDEF* pForDef, ULONG WrData, void* Hmsg );
LONG	RpxWriteFunRegAccLevel( CFORDEF* pForDef, ULONG WrData, void* Hmsg );
LONG	RpxWriteFunRegSafetyTime( CFORDEF* pForDef, ULONG WrData, void* Hmsg );

#endif
