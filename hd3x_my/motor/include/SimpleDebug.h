/***************************************************************
功能描述（Function Description）:该文件是简易调测模块的头文件
最后修改日期（Date）：2010.03.02
修改日志（History）:（以下记录为第一次转测试后，开始记录）
	作者 	时间 		更改说明
1 	x0131 	2010.03.02	初始版本
************************************************************/
#ifndef SIMPLE_DEBUG_H
#define SIMPLE_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "DataTypeDef.h"
#include "main.h"
/************************************************************
	基本的宏定义
************************************************************/
#define C_CPU_TYPE_DSP_28X	0	//
#define C_CPU_TYPE_STM_ARM	10	//

#define C_CPU_TYPE_SEL		C_CPU_TYPE_DSP_28X
//#define C_CPU_TYPE_SEL		C_CPU_TYPE_STM_ARM

#if(C_CPU_TYPE_SEL == C_CPU_TYPE_STM_ARM)
#define RAM_ADDRESS_BASE	0x20000000
#else
#define RAM_ADDRESS_BASE	0
#endif

#define	 FRAME_HEAD					0xA5	//帧头
#define  MAX_DEBUG_DATA				100		//一帧接收/发送数据最大个数
#define  MAX_SEND_DATA				60		//发送数据最大个数
#define  MAX_DEBUG_SAVE_INDEX		100		//调测时候固定输出数据的最大个数

// 调试可用的缓冲区大小
#define C_DEBUG_SAVE_BUFF_SIZE      10000   // 调试缓冲区大小
#define MAX_SCI_FIFO_NUM            16

/////////////////////////////////////////////////////////////////
//Cmd命令字定义
#define  REV_PC_CMD_STOP			0		//停止所有调测
#define  REV_PC_CMD_DEBUG			1		//启动数据保存
#define  REV_PC_CMD_TEST			2		//启动功能测试
#define  REV_PC_CMD_STATUS			3		//刷新显示驱动器状态
#define  REV_PC_CMD_TEST_STOP		4		//停止功能测试
//功能测试下的测试模式定义
#define  REV_PC_CMD_TORQUE			1		//力矩突变方式功能测试
#define  REV_PC_CMD_TORQUE_SIN		2		//力矩SIN方式功能测试
#define  REV_PC_CMD_SPEED			3		//速度突变方式功能测试
#define  REV_PC_CMD_SPEED_SIN		4		//速度SIN方式功能测试
//数据保存模式定义
#define  DEBUG_DATA_SAVE_BUFF_MODLE	0		//使用数据缓冲区的起停模式
#define  DEBUG_DATA_SAVE_RT_MODLE	1		//不使用数据缓冲区的实时模式
#define  DEBUG_DATA_SAVE_REFLUSH	2		//刷新缓冲区数据模式
//数据保存条件定义
#define  DEBUG_DATA_SAVE_NO_LIMIT	0		//任何时候可保存
#define  DEBUG_DATA_SAVE_RUN_LIMIT	1		//仅运行时候开始保存数据
//DSP返回数据命令字定义
#define  SEND_PC_CMD_DEBUG			0		//发送调试数据(低四位)
#define  SEND_PC_CMD_STATUS			1		//发送状态数据(低四位)
//DSP返回命令字的高四位作为数据曲线指示。

//通讯超时时间定义
#define  SCI_COMMU_TIME_OUT			100		//200ms超时(2ms间隔)

//定义模拟FIFO的深度
#define  SCI_FIFO_LENGTH			32  


/************************************************************
	数据结构定义
************************************************************/
typedef struct COMMU_TO_PC_STRUCT_DEF {
	u16	Head;					//帧头
	u16	Cmd;					//命令字
	u16	Length;					//数据长度
	u16	Data[MAX_DEBUG_DATA+1];	//数据缓冲区
	u16	Check;					//CRC校验和

	u16	Busy;					//为TRUE表示接收满或发送忙
	u16	Pointer;				//接收/发送指针（指向缓冲区）
	u16	Step;					//通讯步骤
	u16	Waite;					//超时时间计数
}COMMU_TO_PC_STRUCT;//和PC机通讯的帧结构

/////////////////////////////////////////////////////////////////
typedef struct DEBUG_SAVE_PROCESS_STRUCT_DEF {
    u16 SCIFuncSelApply;        //SCI端口功能选择，可以作为正式后台、调测后台用，=1为调测后台。
    u16	SaveStartFlag;			//开始记录数据的标志
	//数据保存/发送的参数
	u16	SaveModle;				//起停模式/连续模式/刷新显示BUFF（参数1）
	u16	SaveLimit;				//数据保存条件（参数2）
	u16	SaveStep;				//数据保存间隔（参数3）
	u16	* pDebugID1;			//第1个数据地址，为0不保存（参数4）
	u16	* pDebugID2;			//第2个数据地址，为0不保存（参数5）
	u16	* pDebugID3;			//第3个数据地址，为0不保存（参数6）
	u16	* pDebugID4;			//第4个数据地址，为0不保存（参数7）
	u16	CoffDebugID1;			//第1个数据地址，为0不保存（参数4）
	u16	CoffDebugID2;			//第2个数据地址，为0不保存（参数5）
	u16	CoffDebugID3;			//第3个数据地址，为0不保存（参数6）
	u16	CoffDebugID4;			//第4个数据地址，为0不保存（参数7）
	//数据保存/发送的实时参数
	u16	SavePointer;
	u16	SendPointer;
	u16	SaveStepCnt;
	u16	SaveParaNum;			//保存参数个数
	u16	SaveNum;				//已经保存的数据个数

	u16	BufferSize;				//缓冲区大小
	u32  (*pSaveLimit)();			//保存数据的条件
}DEBUG_SAVE_PROCESS_STRUCT;//保存数据的结构

typedef struct TEST_PROCESS_STRUCT_DEF {
	u16	TestStartFlag;			//开始功能测试的标志
	//功能测试的参数
	u16	TestModle;				//测试模式
	s16		TestAmp;				//幅度（参数1）
	u16	TestAddTime;			//上升时间（参数2）
	u16	TestFreq;				//频率（参数2）
	u16	TestTime;				//持续时间（参数3）
	//功能测试的实时参数
	s16		TestAmpPer;				//幅度（参数1）
	s16		TestRealAmp;			//实时给定值
	u16	TestRealAngle;
	u16	TestDeta;
	u32	TestRealTime;			//实时时间
	u16	TestMaxTime;
}TEST_PROCESS_STRUCT;//调测数据结构

typedef struct SCI_FIFO_STRUCT_DEF {
    s16  RecHardPointer;
    s16  RecFIFOPointer;
    s16  RecRemain;
    s16  RecFIFO[SCI_FIFO_LENGTH];	            //模拟接收和发送缓冲区
}SCI_FIFO_STRUCT;//调测数据结构


#if 1
typedef struct COMMU_PC_DATA_DEF {
	u16 gReservedDebugData;         /*按照地址方式*/
    u16 coreFrqAimHz;               /*设定频率*/
	u16 speedReference;		    /*运行频率*/
	u16 syncFrq;		/*同步频率*/
	u16 speedMotor;          /*反馈频率*/
	u16 spdRegError;              /*频率偏差*/
	u16 SlipFrequency;            /*转差频率*/
	
	u16 outCurrent;            /*线电流*/
	u16 outCurDatau;				/*U相电流*/
	u16 outCurDatav;                /*V相电流*/
	u16 outCurDataw;                /*W相电流*/
    u16 outVolDatau;        /*U相伏秒电压*/
    u16 outVolDatav;        /*V相伏秒电压*/ 
    u16 outVolDataw;        /*W相伏秒电压*/ 
	u16 iAlphaS;           /*Alph电流*/
	u16 iBetaS;           /*Beta电流*/
	u16 idFdbFil;                    /*励磁电流*/
	u16 iqFdbFil;                    /*力矩电流*/
	u16 idRefFil;			    /*设定励磁电流*/
	u16 iqRefFil;             /*设定力矩电流*/

	u16 cellGenVolAverFil;             /*母线电压*/

	u16 VdsRef;                  /*励磁电压*/
	u16 VqsRef;                  /*力矩电压*/
	u16 DeltaS;            /*同步旋转角度*/

	u16 ai1SampleFilNew;                   /*模拟量1*/
	u16 ai2SampleFilNew;                   /*模拟量2*/

	u16 coreCarrierFrqAct;        /*载波频率*/
	u16 FastLoopFrequency;                  /*载波周期*/
	u16 EncoderSpeed;        /*编码器反馈速度*/
	u16 svcSpeedEst;   /*SVC辨识速度*/
	u16 fluxAlphaS;              /*定子Alph磁通*/
	u16 fluxBetaS;              /*定子Beta磁通*/
	u16 fluxFdbFil;             /*定子磁通*/
	u16 deltaSPLL;       /*定子磁通相位*/
}COMMU_PC_DATA_DEF;//调测数据结构
extern COMMU_PC_DATA_DEF commuPCData;
#endif

/************************************************************
	基本函数定义和引用
************************************************************/
/////////////////////////////////////////////////////////////////
extern u16 gDebugSaveBuffer[];	//调试缓冲区
extern u16 * const gDebugSaveTable[];
extern u16 * const gDebugStatusTable[];
extern u16 const gDebugSaveTableCoff[];

extern COMMU_TO_PC_STRUCT			gRecePC;			//接收数据帧
extern COMMU_TO_PC_STRUCT			gSendPC;			//发送数据帧
extern DEBUG_SAVE_PROCESS_STRUCT	gDebugSaveInfo;		//调测数据保存
extern TEST_PROCESS_STRUCT			gTestInfo;			//功能测试
extern SCI_FIFO_STRUCT              gSCIFIFO;

extern void InitSetSciForPC(u16 BufferSize,u32 Baud,u32 (* pSaveLimitCall)());
extern void ResetCommuPCReg(void);
extern u32 SaveDataLimitDefault(void);
extern void CommunicatePC(void);
extern void SaveDebugData(u16 m_Flag);
extern u16 JudgeDebugTest(void);
extern s16  GetDebugTestData(void);
extern u16 DebugTestCommCal(u16 FcApply);

extern void UsartSendSCIIsr(void);
extern void UsartRecSCIIsr(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of definition

/******************************* END OF FILE***********************************/
