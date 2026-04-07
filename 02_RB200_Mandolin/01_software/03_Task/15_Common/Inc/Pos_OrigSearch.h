/*
 * Pos_OrigSearch.h
 *
 *  Created on: 2018年07月06日
 *      Author: zhuxc
 */



#ifndef Pos_OrigSearch_H
#define Pos_OrigSearch_H

   

//变量定义
#define ORG_SPDH              0
#define ORG_SPDH_DEC          1
#define ORG_SPDL              2
#define ORG_SPDL_DEC          3
#define ORG_SWITCH_CHECK      4
#define ORG_OFFSET            5
#define ORG_CmdGen            6
#define ORG_OK                7
#define ORG_FAIL              8
#define ORG_SPDL_SECOND          9  //低速运行阶段
#define ORG_SPDL_DEC_SECOND      10  //低速减速阶段
#define ORG_SPDH_SPDL_DEC        11
#define ORG_OFFSET_SEC			12
#define ORG_LOW					13

//原点搜索方向定义
#define POS_DIR 0
#define NEG_DIR 1
//开关信号定义
#define Z_SIGN  0    //直接找Z脉冲
#define DI_SIGN 1    //以DI原点信号作为原点
#define OV_SIGN 2    //以限位信号作为原点
//开关沿定义
#define SWITCH_EDGE_POS 0   //以正方向上升沿为原点信号
#define SWITCH_EDGE_NEG 1   //以负方向上升沿为原点信号
//找到开关后开关状态定义
#define SWITCH_STA_OFF  0   //OFF状态
#define SWITCH_STA_ON   1   //ON状态
//开关off时原点回归方向 定义
#define START_DIR_POS   0   //正方向起动
#define START_DIR_NEG   1   //负方向起动
//是否以Z脉冲为原点定义
#define ORG_Z_NO        0   //不以Z脉冲为原点
#define ORG_Z_YES       1   //以Z脉冲为原点
//以Z脉冲为原点时 Z脉冲相对开关沿的位置
#define ORG_Z_DIR_POS   0   //正方向第一个Z脉冲
#define ORG_Z_DIR_NEG   1   //负方向第一个Z脉冲
//碰到限位报警选择
#define ORG_LIMIT_WARN  0   //碰到限位信号报警停止原点回归
#define ORG_LIMIT_POT   1   //碰到正限位反向，碰到负限位警告
#define ORG_LIMIT_NOT   2   //碰到负限位反向，碰到正限位警告

//原点高位判断方向       20211013
#define ORG_START_DIR_UNCHANGE 1 //与初始方向一致
#define ORG_START_DIR_CHANGE   0 //与初始方向相反
   
//原点开关动作四次   20211013
#define  Switch_Thir 0 //四次以下
#define  Switch_Four 1 //四次
   
//区分原点回归是脉冲型的还是Canopen型的
#define   Canopen_Type 0 //Canopen型或者EtherCAT型
#define   Pulse_Type   1 //脉冲型


//原点回归控制标志定义
struct OrgCtlBitStr
{
	//原点回归控制变量
	USHORT OrgSwithType:2;      //原点开关选择  0-以Z脉冲为参考点   1-以DI为参考点  2-以限位为参考点
	USHORT OrgStartDir:1;       //开关信号OFF时起始运行方向  0-正方向   1-负方向
	USHORT OrgSwithEdge:1;      //开关沿选择  0-正方向上升沿为原点信号   1-负方向上升沿为原点信号
	USHORT OrgSwithEndState:1;  //找到开关以后开关状态设定  0-OFF状态  1-ON状态
	USHORT OrgZEndFlg:1;        //以Z脉冲为原点标志  0-不以Z脉冲为原点  1-以Z脉冲为原点
	USHORT OrgZPulseDir:1;      //以Z脉冲为原点时第一个Z脉冲位置   0-开关沿正方向第一个Z脉冲  1-负方向
	USHORT OrgWarnFlg:2;        //以DI或Z脉冲为原点信号时 碰到限位是否报警 0-报警  1-正限位反向，负限位报警 2-负限位反向，正限位报警
	//原点回归完成标志
	USHORT OrgDone:1;           //原点回归完成
	USHORT OrgFail:1;           //原点回归失败
	USHORT OrgTrig:1;           //原点回归触发标志
        //保留
    USHORT OrgStart:1;   //开关信号ON时起始运动方向 0-与初始方向一致   1-与初始方向相反          20211013
      
    USHORT On_Off_Four:1;   //原点开关动作四次    0-四次以下  1-四次（7  11 23 27） 20211013
    
    USHORT Canopen_Pulse:1;   //0-Canopen型或者EtherCAT型    1-脉冲型  
    USHORT OrgOkFlag:1;

};
union OrgCtlBitUni
{
	USHORT all;
	struct OrgCtlBitStr bit;
};


typedef struct 
{
  //原点回归用输入信号
  USHORT OrgSignUp:1;     	         //bit0 原点信号上升沿
  USHORT OrgSignDown:1;   	         //bit1 原点信号下降沿
  USHORT OrgEnUp:1;       	         //bit2 原点回归使能信号上升沿
  USHORT PosLimUp:1;      	         //bit3 正限位上升沿
  USHORT PosLimDown:1;    	         //bit4 正限位信号下降沿
  USHORT NegLimUp:1;      	         //bit5 负限位信号上升沿
  USHORT NegLimDown:1;    	         //bit6 负限位信号下降沿
  USHORT ZPulseUp:1;      	         //bit7 Z脉冲信号上升沿
  USHORT ZPulseDown:1;    	         //bit8 Z脉冲信号下降沿
  //点位控制用输入信号		          
  USHORT PrTrigUp:1;      	         //bit9 点位触发功能上升沿
  USHORT PrStopUp:1;      	         //bit10 点位停止功能上升沿
  USHORT RSV:5;           	         //bit11-bit15 未使用
}OrgPrSignStr;
extern OrgPrSignStr OrgPrCtlBit;
//原点回归中间变量定义
typedef struct 
{
	USHORT  OrgStep;           //原点回归阶段
    LONG    OrgWaitTim;        //原点回归延时时间
	//原点回归相关数据变量
	LLONG   OrgSpdQ15;         //原点回归目标速度
	LLONG   OrgSpdHQ15;        //原点回归高速
	LLONG   OrgSpdLQ15;        //原点回归低速
	LLONG   OrgSpdLLowQ15;    //原点回归极低速  20211119
	LLONG   OrgAccDecBaseQ15;  //原点回归加减速时基
	LLONG   OrgCmdOutQ15;      //原点回归输出指令Q15格式
 	LONG    OrgTimer;          //原点回归计时器
	//原点回归位置指令输出
	LONG   OrgCmdOut;         //原点回归脉冲输出
	LONG   RemainPulsQ15;     //原点回归脉冲输出余数
	//零点脉冲值
	LONG   ZeroPosPulse;      //零点位置脉冲值
    
    UCHAR ExternOrgEnFlg;      //是否原点回归(1:进行原点回归 0：不动作)
    UCHAR ExternOrgEnStatus;   //原点回归状态（0已完成 1开始找原点 2刚完成 3正在找原点）
    UCHAR OrgCompStatus;       //原点回归完成状态(0：未完成 1：刚完成 2：即将找原点 3：原点回归完成)
}OrgStruct;
extern OrgStruct OrgStr;
extern USHORT DISignReach;                 //原点信号
extern USHORT PosLimit;                    //正限位信号
extern USHORT NegLimit;                    //负限位信号

extern USHORT DISignOld;                   //前一次原点回归信号
extern USHORT PosLimitOld;                 //前一次正限位信号
extern USHORT NegLimitOld;                 //前一次负限位信号
extern USHORT Z_FlgOld;                    //前一次Z信号

extern OrgStruct OrgStrDefault;
/*----------------------------------------------------------------------------------------------*/
extern union OrgCtlBitUni OrgControlBit;
extern void OrigSearch_ParamUpdate( void );   
extern LONG OrigSearch_Deal( void );
/*----------------------------------------------------------------------------------------------*/
extern void OrgStartStateCheck(void);
extern void HighSpdSearch(void);
extern void HighSpdDec(void);
extern void LowSpdSearch(void);
extern void LowSpdDec(void);
extern void OrgSwitchDirCheck(void);
extern void OrgZeroPosDeal(void);
extern void OrgZeroRun(void);
//extern void OrgZeroPosDeal(void);
//extern void OrgStateMachine(void);
extern void OrgOKDeal(void);
extern void OrgFailDeal(void);

extern void OrgStatusEEPReset(void);

extern USHORT OrgCtlBitTable[35];

extern LLONG OrgPosOffset;              //原点偏置值
extern LLONG PosOut;                    //脉冲输出值

extern USHORT  Dec_Flag ; //20211027

extern USHORT Flag_Dec;

extern void LowSpdSearch_SECOND(void);
extern void LowSpdDec_SECOND(void);
extern void HighLowSpdDec(void);
extern void Pr_OrgLoe(); //20211116
extern void Pr_OrgZeroPoDec(void);
extern USHORT Pulse_Type_High_Low_Dec;
#endif
