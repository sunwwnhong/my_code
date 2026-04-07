/*
 * Pr01_DICtrg.h
 *
 *  Created on: 2018年11月16日
 *      Author: zhuxc
 */


#ifndef Pr01_DICtrg_H
#define Pr01_DICtrg_H

#define MaxPathNum  15              //最大的路径数
   
/*--------------------------------------------------------------------------------------------------*/
/* 位置控制加减速时间                                                                               */
/*--------------------------------------------------------------------------------------------------*/
/* 单位为 rpm,转换成扫描周期内脉冲数                                                                */
/*             1rpm × Den × 125 us                                                                  */
/* ACC = -------------------------------                                                            */
/*        60 × 1000 × 1000  (min -->us)                                                             */
/* 转换成脉冲Q15格式,于是简化有:                                                                    */
/*     3000 × 20000 × 125       125                                                                 */
/* = ---------------------- = --------                                                              */
/*      60 × 1000 × 1000         1                                                                  */
/*--------------------------------------------------------------------------------------------------*/
//#define AccDecBasicSpd  3000              /* 加减速时间对应的最大速度值                               */
//#define EGearDen        20000             /* 定义电子齿轮的分母固定为20000                            */
//#define ACCDECCoeff     125               /* ((AccDecBasicSpd * EGearDen * 125) / 60000000 )          */
//LONG EGearDen;
//LONG ACCDECCoeff;
//extern LONG EGearDen;
//extern LONG ACCDECCoeff;

/*--------------------------------------------------------------------------------------------------*/
/*		PR模式——DI端子触发内部位置																	*/
/*--------------------------------------------------------------------------------------------------*/
typedef	union	{					    /* 硬件输入信号											    */
		struct	{						/* Bit信号定义											    */
		UINT	Pos0			:1;		/*  0 : 位置端子编号0                                       */
		UINT	Pos1	 	    :1;		/*  1 : 位置端子编号1                                       */
		UINT	Pos2 			:1;		/*  2 : 位置端子编号2                                       */
		UINT	Pos3 			:1;		/*  3 ：位置端子编号3                                       */
		UINT	Pos4 			:1;		/*  4 : 位置端子编号4                                       */
		UINT	Pos5 			:1;		/*  5 : 位置端子编号5(预留)                                 */
        /*------------------------------------------------------------------------------------------*/
		UINT	Rsv6 			:1;		/*  6 : 保留                                                */
		UINT	Rsv7 			:1;		/*  7 : 保留          									    */
		UINT	Rsv8 			:1;		/*  8 : 保留          									    */
		UINT	Rsv9 			:1;		/*  9 : 保留                                                */
		UINT	RsvA 			:1;		/*  A : 保留          									    */
		UINT	RsvB 			:1;		/*  B : 保留          									    */
		UINT	RsvC 			:1;		/*  C : 保留          									    */
		UINT	RsvD 			:1;		/*  D : 保留          									    */
		UINT	RsvE 			:1;		/*  E : 保留          									    */
		UINT	RsvF		    :1;		/*  F : 保留                                                */
        /*------------------------------------------------------------------------------------------*/
		} f;
	/*----------------------------------------------------------------------------------------------*/
		USHORT	w;						/* For SHORT Access										    */
}DIPOS;
/*--------------------------------------------------------------------------------------------------*/
typedef struct
{
    /*----------------------------------------------------------------------------------------------*/
    struct                              /* 位标志位定义                                             */
    {
        UINT    CTRG            :1;     /* 内部多段位置DI触发                                       */
        UINT    CMDOK           :1;     /* Pr指令发送完成                                           */
        UINT    TPOS            :1;     /* Pr指令发送完成且定位完成,不包含延时                      */
        UINT    MCOK            :1;     /* Pr指令发送完成且定位完成,包含延时                        */
        /*------------------------------------------------------------------------------------------*/
		UINT	Bit0 			:1;		/* Option-Bit0                                              */
		UINT	Bit1			:1;		/* Option-Bit1                                              */
		UINT	Bit2 		    :1;		/* Option-Bit2                                              */
		UINT	Bit3 		    :1;		/* Option-Bit3                                              */
        /*------------------------------------------------------------------------------------------*/
        UINT    NewPosFlag      :1;     /* 新的指令标志位                                           */
        UINT    PramUpdate      :1;     /* 参数更新标志                                             */
        UINT    PosSpdReachflag :1;     /* 位置速度到达标志                                         */
        UINT    PosCmdFinishFlag:1;     /* 某一段位移完成标志                                       */
        /*------------------------------------------------------------------------------------------*/
        UINT    PrDelayOKFlag   :1;     /* 延时完成标志                                             */
        UINT    PrDelayFlag     :1;     /* 延时标志位(定位模式)                                     */
        UINT    OverlapFlg      :1;     /* 位置重叠标志                                             */
        UINT    PosExeImmet     :1;     /* 外部触发立即执行                                         */
        UINT    PosExeFinishFlg :1;     /* 位置执行完成标志                                         */
        /*------------------------------------------------------------------------------------------*/
        UINT    Fun20           :1;
        UINT    Fun21           :1;       
        UINT    Fun22           :1;        
        UINT    Fun23           :1;        
        UINT    Fun24           :1;
        UINT    Fun25           :1;
        UINT    Fun26           :1;
        UINT    Fun27           :1;
        UINT    Fun28           :1;
        UINT    Fun29           :1;
        UINT    Fun2A           :1;
        UINT    Fun2B           :1;
        UINT    Fun2C           :1;
        UINT    Fun2D           :1;
        UINT    Fun2E           :1;
        UINT    Fun2F           :1;       
    }f;
    /*----------------------------------------------------------------------------------------------*/
    DIPOS DI;                           /* 内部触发多段位置端子状态                                 */
    /*----------------------------------------------------------------------------------------------*/
    UCHAR CTRG_Status;                  /* CTRG 信号状态监控                                        */
    UCHAR CTRG_Step;                    /* CTRG 步骤信号                                            */
    UCHAR CTRG_PosNum;                  /* CTRG 信号触发的位置编号                                  */
    UCHAR CurMode;                      /* 当前的模式                                               */
    UCHAR NewNum;                       /* 新的位置编号                                             */
    UCHAR PosNum;                       /* 位置编号                                                 */
    UCHAR PosNumOld;                    /* 位置编号                                                 */
    UCHAR PosType;                      /* 位置类型                                                 */
    UCHAR PosTypeOld;                   /* 位置类型                                                 */
    UCHAR PosOption;                    /* 位置可选项                                               */
    UCHAR PosOptionOld;                 /* 位置可选项                                               */
    UCHAR SpeedUnit;                    //速度单位
    UCHAR StopSign;                     //停机信号
    UCHAR Reserved1;
    /*----------------------------------------------------------------------------------------------*/
    USHORT PrAccTime;                   /* Pr加速时间                                               */
    USHORT PrDecTime;                   /* Pr减速时间                                               */
    ULONG  PrDelayTime;                 /* Pr延迟时间                                               */
    ULONG  PrDelayTimeOld;              /* Pr延迟时间                                               */
    USHORT PrSpd;                       /* Pr目标速度                                               */
    LONG   PrPos;                       /* Pr位置长度                                               */
    USHORT MonitorPosNum;               /* 当前执行的Pr号                                           */
//    USHORT PrCommShow;                  /* Pn806运行状态缓存(上一时刻，改Pn806时会用到该变量)     */
    /*----------------------------------------------------------------------------------------------*/
    LONG  PosFbkDelt;                   /* 编码器反馈脉冲数偏差（用户单位）                         */
    LLONG  PosCmdSum;                   /* 位置指令总数(绝对值)                                     */
    /*----------------------------------------------------------------------------------------------*/
    ULONG  PrDelayTimeCnt;              /* Pr位置计数器                                             */
//    ULONG  JumpDelayCnt;              /* 跳转延时                                                 */
    LONG   PrPosSpd_Q15Remain;          /* Pr位置指令速度余数                                        */
    /*----------------------------------------------------------------------------------------------*/
}PR_DICTRG;
extern PR_DICTRG Pr_DICtrgV;

/*----------------------------------------------------------------------------------------------*/
extern void PrModePrameterInit( void );                 //参数初始化

extern void Pr_DI_ConTrig(void);                        //运行端子触发
extern LONG PrModeSinglePos( void );                    //单段位置
extern LONG PosAndSpeedDeal(void);                      //Pr指令处理

extern void  PrPosStop(void);                           //Pr停机处理
extern void InnerPosInformation( USHORT Target );       //指令信息获取


extern HWSIN	Inx;

#endif
