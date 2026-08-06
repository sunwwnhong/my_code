/*****************************************************************
*
*
*
*
*
*
*
*
*****************************************************************/

#ifndef __FUNCCODE_H__
#define __FUNCCODE_H__

#include "main.h"
//#include "m_main.h"
//#include "f_funcCode.h"
//#include "m_hw_cpu.c"
//#include "m_hw_adc.c"
//#include "m_hw_misc.c"
//#include <integer.h>
#include "publicDefine.h"
//获得功能码code在全部功能码中的index，即功能码在数组funcCode.all[]中的下标。
//根据FUNCCODE_ALL的定义，一个功能码的表示有4种办法，对应的获得index的办法：
//// 1.funcCode.all[i]----i
//// 2.funcCode.f5[7]----GetCodeIndex(funcCode.group.f5[7])
//// 3.group,grade----GetGradeIndex(group,grade)
//// 4.funcCode.code.maxFrq----GetCodeIndex(funcCode.code.maxFrq)

#define	GetCodeIndex(code)	         ((u16)((&(code)) - (&(funcCode.all[0]))))
#define	GetGradeIndex(group,grade)	  (funcCodeGradeSum[group] + (grade))
	
#define EEPROM_INDEX_USE_INDEX        4     // 功能参数使用EEPROM起始
//是否可写。1-当前可写，0-当前不可写
//#defineIsWritable(attribute)((ATTRIBUTE_READ_AND_WRITE==(attribute).bit.writable)
//||((ATTRIBUTE_READ_ONLY_WHEN_RUN==(attribute).bit.writable)&&(!runFlag.bit.run)))
//#define PLC_AI_NUMBER   1           //PLC AI端子个数
#define DSP_AO_NUMBER   3           //DSP控制AO 端子个数
#define DSP_AI_NUMBER   2           //DSP控制AI端子个数
#define PLC_AI_NUMBER   2           //PLC AI端子个数
#define	PLC_AO_NUMBER	 4         //PLC AO 端子个数

#define AI_NUMBER               3           // AI端子个数
#define AO_NUMBER               2          // AO端子个数
//=====================================================================
//功能码属性位定义
//
#define	ATTRIBUTE_UNIT_HZ_BIT	0
#define	ATTRIBUTE_UNIT_A_BIT	1
#define	ATTRIBUTE_UNIT_V_BIT	2

#define	ATTRIBUTE_READ_AND_WRITE		0	//(任何时候)可写
#define	ATTRIBUTE_READ_ONLY_WHEN_RUN	1	//运行时只读
#define	ATTRIBUTE_READ_ONLY_ANYTIME		2	//只读

// 多功能码组合属性
#define ATTRIBUTE_MULTI_LIMIT_SINGLE    0   // 单独的功能码
#define ATTRIBUTE_MULTI_LIMIT_DEC       1   // 多个功能码，十进制
#define ATTRIBUTE_MULTI_LIMIT_HEX       2   // 多个功能码，十六进制
struct	FUNC_ATTRIBUTE_BITS
{//bitsdescription
	Uint16 point:3;	// 2:0radixpoint,小数点
					// 0-无小数点，1-1位小数，...，4-4位小数
					// (0.0000-100,00.000-011,000.00-010,0000.0-001,00000-000)
	Uint16	unit:3;	// 5:3unit,单位
					// 1-hz,2-A,3-RPM,4-V,6-%;001-Hz,010-A,100-V
	Uint16	displayBits:3;	//8: 65个数码管要显示的位数。0-显示0位，1-显示1位，...，5-显示5位
	Uint16	upperLimit:1;	//9 1-参数由上限相关功能码限制
	Uint16	lowerLimit:1;	//10 1-参数由下限相关功能码限制，0-直接由下限限制
	Uint16	writable:2;		//12:11参数读写特性，00-可以读写,01-运行中只读，10-参数只读
	Uint16	signal:1;		//13符号，unsignal-0;signal-1
	//Uint16	noDisplay:1;	//14不显示
	Uint16    multiLimit:2;    // 15:14  该功能码为多个功能码的组合. 
                            //        00-单独功能码(非组合); 
                            //        01-十进制,  多个功能码的组合; 
                            //        10-十六进制,多个功能码的组合; 
};

union	FUNC_ATTRIBUTE
{
	Uint16	all;
	struct	FUNC_ATTRIBUTE_BITS	bit;
};
//=====================================================================

//=====================================================================
//功能码属性表：上限、下限、属性
//出厂值放在funcCodeInit中
typedef struct FUNCCODE_ATTRIBUTE_STRUCT
{
    Uint16                  lower;          // 下限
    Uint16                  upper;          // 上限
    Uint16                  init;           // 出厂值
    union FUNC_ATTRIBUTE    attribute;      // 属性

    Uint16                  eepromIndex;    // 对应EEPROM存储的index
} FUNCCODE_ATTRIBUTE;

extern const FUNCCODE_ATTRIBUTE funcCodeAttribute[];

//=====================================================================
//功能码的code的一些数据结构定义
struct	PLC_STRUCT
{
	Uint16	runTime;		//PLC第_段运行时间
	Uint16	accDecTimeSet;	//PLC第_段加减速时间选择
};
//=================================
//=====================================================================

//=================================
enum    MOTOR_SN
{
    MOTOR_SN_1,	//第1电机
    MOTOR_SN_2,	//第2电机
    MOTOR_SN_3,	//第3电机
    MOTOR_SN_4	//第4电机
};
//=================================
#define	MOTOR_TYPE_ACI_GENERAL	0//普通异步电机
#define	MOTOR_TYPE_ACI_INV		1//变频异步电机
#define	MOTOR_TYPE_PMSM 		2//永磁同步电机
struct	MOTOR_PARA_STRUCT_F
{
//电机基本参数
	Uint16 motorType;			//F1-00电机类型选择
	Uint16 ratingPower;			//F1-01电机额定功率
	Uint16 ratingVoltage;		//F1-02电机额定电压
	Uint16 ratingCurrent;		//F1-03电机额定电流
	Uint16 ratingFrq;			//F1-04电机额定频率
	Uint16 ratingSpeed;			//F1-05电机额定转速

//异步机调谐参数
	Uint16 statorResistance;	//F1-06异步机定子电阻
	Uint16 rotorResistance;		//F1-07异步机转子电阻
	Uint16 leakInductance;		//F1-08异步机漏感抗
	Uint16 mutualInductance;	//F1-09异步机互感抗
	Uint16 zeroLoadCurrent;		//F1-10异步机空载电流
    Uint16 IfModeRefCur;		//F1-11 IF模式设定电流 // LS_20240229
    Uint16 PMLowSpdIdAddCur;    //F1-12 同步机低速d轴注入电流 // LS_20240229
	Uint16 rsvdF11[5-2];        // LS_20240229
	
//同步机调谐参数
	Uint16 pmsmRs;				//F1-16同步机定子电阻
	Uint16 pmsmLd;				//F1-17同步机d轴电感
	Uint16 pmsmLq;				//F1-18同步机q轴电感
	Uint16 pmsmRsLdUnit;		//F1-19同步机电感电阻单位
	Uint16 pmsmCoeff;			//F1-20同步机反电动势系数
	Uint16 pmsmCheckTime;		//F1-21同步机输出缺相检测时间
	Uint16 pmsmPluseWidth;      //F1-22 同步机磁极位置辨识脉冲宽度
    Uint16 InitPosDetPulse;     //F1-23 同步机转子位置辨识脉冲大小 // CF-20 // LS_20221026
	Uint16 rsvdF12[3-1];
	Uint16 inertia;				//F1-26 惯量
};
#define MOTOR_PARA_DATA_LEN_F  sizeof (struct MOTOR_PARA_STRUCT_F)


struct	PG_PARA_STRUCT1
{
//PG卡参数
	Uint16	encoderPulse;		//F1-27编码器脉冲线数
	Uint16	pgType;				//F1-28编码器类型
	Uint16	fvcPgSrc;			//F1-29速度反馈PG卡选择,0-QEP1,1-QEP2(扩展)
	Uint16	encoderDir;			//F1-30编码器相序/主方向
	Uint16	encoderAngle;		//F1-31编码器安装角
	Uint16	uvwSignDir;			//F1-32UVW信号方向
	Uint16	uvwSignAngle;		//F1-33UVW信号零点位置角
	Uint16	encoderPole;		//F1-34旋变极对数
	Uint16	uvwSignPole;		//F1-35UVW极对数
	Uint16	encoderLossLimit;   //F1-36编码器丢失检测阈值
};
#define PG_PARA_DATA_LEN1  SIZEOF(struct PG_PARA_STRUCT1)

//=================================

//------------------------------------------------
struct SPEED_LOOP_MENU1
{
    Uint16  SpeedLoopKp;                //F2-00 速度环比例增益--低速
    Uint16  SpeedLoopTi;                //F2-01 速度环积分时间--低速
    Uint16  switchFrq1; 				//F2-02 切换频率1
	Uint16  speedLoopKp2;				//F2-03 速度环比例增益--高速
	Uint16  speedLoopTi2;				//F2-04 速度环积分时间--高速
	Uint16  switchFrq2;					//F2-05 切换频率2 
    Uint16  rsvd[2];                 	//F2-06~07 保留
	Uint16  SpeedLoopKf;				//F2-08 速度环KF增益
};
#define SPEED_LOOP_MENU_DATA_LEN1  SIZEOF(struct SPEED_LOOP_MENU1)

struct CURRENT_LOOP_MENU1
{
    Uint16 CurLoopKp;           //F2-13 电流环比例增益
    Uint16 CurLoopTi;           //F2-14 电流环积分增益
    Uint16 CurLoopKpDurBrake;   //F2-15 电流环比例增益(双频制动时)
    Uint16 CurLoopTiDurBrake;   //F2-16 电流环积分增益(双频制动时)
};
#define CURRENT_LOOP_MENU_DATA_LEN1  sizeof (struct CURRENT_LOOP_MENU1)

struct LOW_FREQUENCY_COMPENSATION_MEMU
{
    Uint16 LowFrqWo;            //A5-08 输出电压硬件参数
    Uint16 LowFrqComGain;       //A5-09 磁链观测低频系数
    Uint16 SWCompensatorPole;   //A5-10 磁链观测软件系数
};
#define LOW_FREQUENCY_COMPENSATION_MEMU_DATA_LEN1  sizeof(struct LOW_FREQUENCY_COMPENSATION_MEMU)

struct FLUX_CONTROL_MENU
{
	Uint16  FluxRegPropGain;            //F2-23 磁链环比例增益
	Uint16  FluxRegIntGain;             //F2-24 磁链环积分增益
	Uint16  FluxFilterTimeConst;        //F2-25 磁链滤波时间
	Uint16  FluxDemand;                 //F2-26 磁链给定值
	Uint16  FluxRampRate;               //F2-27 磁链斜坡时间
};
#define FLUX_CONTROL_MENU_DATA_LEN1  sizeof(struct FLUX_CONTROL_MENU)

struct	VC_PARA_F
{
	Uint16	spdCtrlDriveTorqueLimitSrc;	//F2-09速度控制(驱动)转矩上限源
	Uint16	spdCtrlDriveTorqueLimit;	//F2-10速度控制(驱动)转矩上限数字设定
	Uint16	spdCtrlEleTorqueLimitSrc;	//F2-11速度控制(发电)转矩上限源
	Uint16	spdCtrlEleTorqueLimit;	    //F2-12速度控制(发电)转矩上限数字设定	
};
#define VC_PARA_DATA_LEN  SIZEOF(struct VC_PARA_F)

//------------------------------------------------
//------------------------------------------------
//第2电机的功能码，包括电机参数、控制参数
struct	MOTOR_FC
{
	struct	MOTOR_PARA_STRUCT_F	motorPara;	//Ax-00Ax-26第2/3/4第1电机参数
	struct	PG_PARA_STRUCT1	pgPara;			//Ax-27Ax-36第1电机PG卡参数
	Uint16  rsvdAx0[3];                     //Ax-37Ax-39
	Uint16	tuneCmd;						//Ax-40调谐命令

    struct  SPEED_LOOP_MENU1  SpeedLoop;     //Ax-41~49 速度环参数
	struct   VC_PARA_F	vcPara;	                //Ax-50~53 第1电机矢量控制参数
    struct  CURRENT_LOOP_MENU1  CurrentLoopMenu;             //Ax-54~Ax-57 电流环参数 原A1组
	Uint16  rsvdAx3[6];                                     //Ax-58~63 保留	
//	struct  LOW_FREQUENCY_COMPENSATION_MEMU LowFrCompMenu;  //Ax-64~66
	struct  FLUX_CONTROL_MENU FluxContrlMenu;               //Ax-64~68
	Uint16  rsvdAx4[6];                                     //Ax-69~74 保留		

	Uint16	motorCtrlMode;					//Ax-75第2/3/4电机控制方式  /Ax-61第2/3/4电机控制方式
	Uint16	accDecTimeMotor;				//Ax-76第2/3/4电机加减速时间选择    -62第2/3/4电机加减速时间选择
	Uint16	torqueBoost;					//Ax-77转矩提升     //Ax-63转矩提升
	Uint16	antiVibrateGainMode;			//Ax-78振荡抑制增益模式 //Ax-64振荡抑制增益模式
	Uint16	antiVibrateGain;				//Ax-79振荡抑制增益 //Ax-65振荡抑制增益
};


//==============================================================================
struct OUTPUT_CONNECTION_MENU1
{
    //Uint16 FilterCTSecTurn;       // A1-02 磁链环前馈增益 Filter CT Secondary Turns 
    //Uint16 magneChainLoopFeedScale; // A1-02 磁链环前馈增益
    Uint16 FilterInd;               // A5-03 Filter Inductance   输出滤波器电感值
    Uint16 FilterCap;               // A5-04 Filter Capacitance  输出滤波器电容值
    Uint16 CableRes;                // A5-05 Cable Resistance    输出线缆电阻
    Uint16 CableInd;                // A5-06 Cable Inductance    输出线缆电感值
    Uint16 FilterDampGain;          // A5-07 Filter Damping Gain 输出滤波器阻尼增益
};
#define OUTPUT_CONNECTION_MENU_LEN1 (sizeof(struct OUTPUT_CONNECTION_MENU1)) 

//==============================================================================
// 电压、电流采样的参数设置
struct VOL_CUR_SAMPLE_PARA_STR
{
    Uint16 inVolReviseCoef;        // FF-06 输入电压校正系数
    Uint16 inCurReviseCoef;        // FF-07 输入电流校正系数
    Uint16 outVolReviseCoef;       // FF-08 输出电压校正系数
    Uint16 outCurReviseCoef;       // FF-09 输出电流校正系数
    Uint16 inVolResOhm;            // FF-10 输入电压采样电阻值
    Uint16 inCTRatio;              // FF-11 输入电流互感器变比
    Uint16 inCurResOhm;            // FF-12 输入电流采样电阻值
    Uint16 outVolResOhm;           // FF-13 输出电压采样电阻值
    Uint16 outCTRatio;             // FF-14 输出电流互感器变比
    Uint16 outCurResOhm;           // FF-15 输出电流采样电阻值 
};
#define VOL_CUR_SAMPLE_PARA_LEN1 (sizeof(struct VOL_CUR_SAMPLE_PARA_STR)) 
//==============================================================================
//==============================================================================
// 高转矩参数设置
struct HIGH_TORQUE_START_PARA
{
    Uint16 highTorqueStartMode;         // A5-11 高启动转矩模式使能
    Uint16 highTorqueCurSet;            // A5-12 高启动转矩模式电流给定
    Uint16 highTorqueRampTime;          // A5-13 高启动转矩模式电流斜坡时间
    Uint16 highTorquePllSetTime;        // A5-14 高启动转矩模式PLL建立时间
};
#define HIGH_TORQUE_START_PARA_LEN (sizeof(struct HIGH_TORQUE_START_PARA)) 
//==============================================================================
// 磁链环参数设置
struct MAGEN_CHAIN_LOOP_PARA
{
    Uint16 magenChainObserLimit;        // A5-15 磁链观测补偿限幅
    Uint16 magenChainCloseLoopFrq;      // A5-16 磁链闭环频率
    Uint16 magenChainOpenLoopIdCurSet;  // A5-17 磁链开环时励磁电流给定
};
#define MAGEN_CHAIN_LOOP_PARA_LEN1 (sizeof(struct MAGEN_CHAIN_LOOP_PARA)) 
//==============================================================================
// 变频器额定参数
struct DRIVE_RATING_PARA_STR
{
    Uint16 ratingInVol;            // FF-16 变频器额定输入电压
    Uint16 ratingInCur;            // FF-17 变频器额定输入电流
    Uint16 ratingOutVol;           // FF-18 变频器额定输出电压
    Uint16 ratingOutCur;           // FF-19 变频器额定输出电流
};
#define DRIVE_RATING_PARA_LEN1   (sizeof(struct DRIVE_RATING_PARA_STR))
//==============================================================================
struct	RAM_CODE_READ
{
	Uint16	addr;		//设定跳跃点
	Uint16	data;	    //设定跳跃幅度
};
//=================================
struct	AI_JUMP
{
	Uint16	point;		//设定跳跃点
	Uint16	arrange;	//设定跳跃幅度
};
//=================================

//=================================
struct ANALOG_CALIBRATE_CURVE  // 模拟量校正曲线，AIAO
{
    Uint16 before1;     // 校正前电压1
    Uint16 after1;      // 校正后电压1
    
    Uint16 before2;     // 校正前电压2
    Uint16 after2;      // 校正后电压2
};
//=================================
//=================================
typedef	struct	AO_PARA_STRUCT
{
	Uint16	offset;		//AO零偏系数
	Uint16	gain;		//AO增益
}AO_PARA;
//=================================
typedef	struct	DSP_AO_PARA_STRUCT
{
	Uint16	funcset;    //AO功能选择
	Uint16	gain;		//AO增益
//	Uint16  offset;     //AO零偏系数
}DSP_AO_PARA;

//=================================

//=================================
struct	ERROR_SCENE_STRUCT
{
	Uint16	errorFrq;				//第十次(最近一次)故障时频率
	Uint16	errorOutCurrent;		//第十次(最近一次)故障时输出电流
	Uint16	errorOutVoltage;	    //第十次(最近一次)故障时输出电压
	Uint16	errorInCurrent;			//第十次(最近一次)故障时输入电流
	Uint16	errorInVoltage;			//第十次(最近一次)故障时输入电压
	      	
	Uint16	errorInverterStatus;	//第十次(最近一次)故障时变频器状态
    Uint16  errorCoreErrorInfo;     // 第十次性能故障的提示信息 
	Uint16	rsvd;		            //保留
};
#define ERROR_SCENE_STRUCT_LEN  sizeof(struct ERROR_SCENE_STRUCT)
//=================================

//=================================
/*
#define	AI_NUMBER		2			//AI端子个数
#define DSP_AI_NUMBER   2           //DSP控制AI端子个数
#define PLC_AI_NUMBER   2           //PLC AI端子个数
       	         		 			
#define	AO_NUMBER		2			//AO端子个数
#define DSP_AO_NUMBER   3           //DSP控制AO 端子个数
#define	PLC_AO_NUMBER	4           //PLC AO 端子个数
*/
//#define DSP_AO_NUMBER   3           //DSP控制AO 端子个数
//#define DSP_AI_NUMBER   2           //DSP控制AI端子个数
#define	DI_TERMINAL_NUMBER	(60-1)  //物理DI端子 // LS_20221026
#define	DO_TERMINAL_NUMBER	(68)    //物理DO端子


#define	PLC_STEP_MAX	16			//PLC、多段指令段数

//=====================================================================
//EEPROM的使用长度，包括中间预留部分
//EEPROM地址分配，2010-08-13
// 0-保留，rsvd4All
// 1,2-EEPROM-CHK
// 3 -AIAOCHK
// 4-944-MD380使用
//945-1149-预留MD380使用
//1150-1329-IS380/MD380M使用
//其中,16-63-掉电记忆使用
#define	EEPROM_INDEX_USE_LENGTH	1655	//最后一个eeprom地址+1
//预留给其它使用的功能码index
#define	FUNCCODE_RSVD4ALL_INDEX	    (GetCodeIndex(funcCode.code.rsvd4All))
//#define	FUNCCODE_RSVD4ALL_INDEX	    (GetCodeIndex(200))    //funcCode.code.rsvd4All))
#define USER_PARA_SAVE_FLAG1   (1)
#define USER_PARA_SAVE_FLAG2   (0xFFFF - USER_PARA_SAVE_FLAG1)
#define	REM_P_OFF_MOTOR	5//性能使用的掉电记忆。包含在CORE_TO_FUNC_DISP_DATA_NUM里面



// 功能码的组数
#define FUNCCODE_GROUP_NUM  83  // 包括预留的组, 见funcCodeGradeCurrentMenuMode. 
// EEPROM中顺序: EEPROM_CHK, 掉电记忆, FF, FP, F0-FE, A0-AF, B0-BF, C0-CF
// 显示顺序:     F0-FE, FF, FP, A0-AF, B0-BF, C0-CF, EEPROM_CHK(不显示), 掉电记忆(不显示), U0-UF
// U0-UF不占用EEPROM空间

#define FUNCCODE_GROUP_F0   0       // F0组
#define FUNCCODE_GROUP_F1   1       // F1组
#define FUNCCODE_GROUP_FE   14      // FE组
#define FUNCCODE_GROUP_FF   15      // FF组
#define FUNCCODE_GROUP_FP   16      // FP组
#define FUNCCODE_GROUP_A0   17      // A0组
#define FUNCCODE_GROUP_A5   22      // A5组
#define FUNCCODE_GROUP_AA   27      // AA组
#define FUNCCODE_GROUP_AB   28      // AB组
#define FUNCCODE_GROUP_AE   31      // AE组
#define FUNCCODE_GROUP_AF   32      // AF组
#define FUNCCODE_GROUP_B0   33      // B0组
#define FUNCCODE_GROUP_B1   34      // B1组
#define FUNCCODE_GROUP_BF   48      // BF组
#define FUNCCODE_GROUP_C0   49      // C0组
#define FUNCCODE_GROUP_CC   61      // CC组 用户定制功能码组
#define FUNCCODE_GROUP_CF   64      // CF组
#define FUNCCODE_GROUP_U0   67      // U0组，显示
#define FUNCCODE_GROUP_U1   68      // U1组，显示
#define FUNCCODE_GROUP_U2   69      // U2组，显示
#define FUNCCODE_GROUP_U3   70      // U3组，显示
#define FUNCCODE_GROUP_U4   71
#define FUNCCODE_GROUP_U5   72
#define FUNCCODE_GROUP_U6   73
#define FUNCCODE_GROUP_U7   74
#define FUNCCODE_GROUP_U8   75
#define FUNCCODE_GROUP_U9   76
#define FUNCCODE_GROUP_UA   77
#define FUNCCODE_GROUP_UB   78
#define FUNCCODE_GROUP_UF   (FUNCCODE_GROUP_NUM - 1)    // UF，性能调试显示

//每组功能码的个数
//除FF组之外，每组预留2个功能码。为了在增加功能码时，尽量不用恢复出厂参数。
#define	F0NUM	( 31 )		//F0 基本功能组	
#define	F1NUM	( 41 )		//F1 电机参数
#define	F2NUM	( 34 )		//F2 矢量控制参数   //23
#define	F3NUM	( 16 )		//F3 V/F控制参数	
       	     	      		
#define	F4NUM	( 75 )		//F4 输入端子		
#define	F5NUM	( 76 )		//F5 输出端子		
#define	F6NUM	( 56 ) 		//F6 启停控制		
#define	F7NUM	( 36 )		//F7 键盘与显示	
       	     	      		
#define	F8NUM	( 100 )		//F8 辅助功能		
#define	F9NUM	( 100 )		//F9 故障记录	
#define	FANUM	( 29 )		//FA PID功能
#define	FBNUM	( 69 )		//Fb 保护设定		
       	     	      		
#define	FCNUM	( 52 )		//FC 多端速、PLC	
#define	FDNUM	( 12 )		//FD 通讯参数
#define	FENUM	( 32 )      //FE 用户参数
#define	FFNUM	( 28 )		//FF 厂家参数		
       	     	
#define	FPNUM	( 6 )		//FP用户密码,参数初始化	
       	     	
#define	A0NUM	( 9 )		//A0				
#define	A1NUM	( 8  )		//A1        
#define	A2NUM	( F1NUM+2+F2NUM+3)//A2		
#define	A3NUM	( A2NUM )	//A3		
#define	A4NUM	( A2NUM )	//A4		

#define	A5NUM	( 61 )		//A5        				
#define	A6NUM	( 91 )		//A6        // 模拟量及脉冲设定				
#define	A7NUM	( 1 )    	//a7			
#define A8NUM   (26)        // A8

#define	A9NUM	( 35 )		//A9
#define AANUM   ( 0+1 )     // AA
#define ABNUM   ( 0+1 )     // AB
                               
#define ACNUM   ( 36  )     // AC  // AI AO 校验
#define ADNUM   ( 0+1 )     // AD
#define AENUM   ( 0+1 )     // AE
#define AFNUM   ( 0+1 )     // AF

#define B0NUM   ( 50 )      // B0							
#define B1NUM   ( 50 )	    // B1						
#define B2NUM   ( 30 )      // B2							
#define B3NUM   ( 0+1 )     // B3
                                    
#define B4NUM   ( 0+1 )     // B4
#define B5NUM   ( 0+1 )     // B5
#define B6NUM   ( 0+1 )     // B6
#define B7NUM   ( 0+1 )     // B7
                                    
#define B8NUM   ( 0+1 )     // B8
#define B9NUM   ( 0+1 )     // B9
#define BANUM   ( 0+1 )     // BA
#define BBNUM   ( 0+1 )     // BB
                                   
#define BCNUM   ( 0+1 )     // BC
#define BDNUM   ( 0+1 )     // BD
#define BENUM   ( 0+1 )     // BE
#define BFNUM   ( 0+1 )     // BF

#define C0NUM   ( 56  )     // C0
#define C1NUM   ( 0+1 )     // C1
#define C2NUM   ( 0+1 )     // C2
#define C3NUM   ( 0+1 )     // C3

#define C4NUM   ( 0+1)      // C4
#define C5NUM   ( 0+1)      // C5
#define C6NUM   ( 0+1)      // C6
#define C7NUM   ( 0+1)      // C7

#define C8NUM   ( 0+1)      // C8
#define C9NUM   ( 0+1)      // C9
#define CANUM   ( 0+1)      // CA
#define CBNUM   ( 0+1)      // CB
                                
#define CCNUM   ( 32+0)     // CC   用户定制功能码组
#define CDNUM   ( 0+1 )     // CD
#define CENUM   ( 15  )     // CE
#define CFNUM   ( 40+0)     // CF

															//719-722//723-
#define	CHK_NUM	(  4 )	    //eepromCheckWord(2)，rsvd4All(1)放在这里的最前面,AIAOChk(1)也在这里
#define	REM_NUM	( 48 )		//掉电记忆，包括性能使用的掉电记忆。(包括性能的掉电记忆)
#define U0NUM   ( 100 )     // U0  显示使用，不占用EEPROM，尽量少的占用程序空间(无出厂值、上下限，但有属性)
#define U1NUM   ( 100 )     // U1
#define U2NUM   ( 100 )     // U2
#define U3NUM   ( 100 )     // U3

#define U4NUM     ( 100)    // U4
#define U5NUM     ( 100)    // U5
#define U6NUM     ( 100)    // U6
#define U7NUM     ( 100)    // U7

#define U8NUM     ( 91 )    // U8
#define U9NUM     (100)    // U9
#define UANUM     (60)      // UA
#define UBNUM     (90)      // UB

#define UCNUM     ( 0+1)    // UC
#define UDNUM     ( 0+1)    // UD
#define UENUM     ( 0+1)    // UE
#define UFNUM     ( 30 )    // UF 性能调试使用

#define FNUM_PARA      (F0NUM + F1NUM + F2NUM + F3NUM +     \
                        F4NUM + F5NUM + F6NUM + F7NUM +     \
                        F8NUM + F9NUM + FANUM + FBNUM +     \
                        FCNUM + FDNUM + FENUM + FFNUM +     \
                                                            \
                        FPNUM +                             \
                                                            \
                        A0NUM + A1NUM + A2NUM + A3NUM +     \
                        A4NUM + A5NUM + A6NUM + A7NUM +     \
                        A8NUM + A9NUM + AANUM + ABNUM +     \
                        ACNUM + ADNUM + AENUM + AFNUM +     \
                                                            \
                        B0NUM + B1NUM + B2NUM + B3NUM +     \
                        B4NUM + B5NUM + B6NUM + B7NUM +     \
                        B8NUM + B9NUM + BANUM + BBNUM +     \
                        BCNUM + BDNUM + BENUM + BFNUM +     \
                                                            \
                        C0NUM + C1NUM + C2NUM + C3NUM +     \
                        C4NUM + C5NUM + C6NUM + C7NUM +     \
                        C8NUM + C9NUM + CANUM + CBNUM +     \
                        CCNUM + CDNUM + CENUM + CFNUM       \
                        )                                   // 所有功能码，不包括显示
#define FNUM_EEPROM    (FNUM_PARA + CHK_NUM + REM_NUM)      // 需要存储在EEPROM中的所有参数

#define FNUM_ALL       (FNUM_EEPROM +                       \
                        U0NUM + U1NUM + U2NUM + U3NUM +     \
                        U4NUM + U5NUM + U6NUM + U7NUM +     \
                        U8NUM + U9NUM + UANUM + UBNUM +     \
                        UCNUM + UDNUM + UENUM + UFNUM       \
                       )                                    // 所有功能码、参数，包括显示
//=====================================================================
//
//功能码组，F0组，F1组,...
//
//eepromCheckWord放在最前面
//厂家参数、用户密码、用户定制菜单放在前面，防止增删功能码时被误修改。
//fc与eeprom有对应关系表，所以以上要求不需要了
//
//=====================================================================
struct	FUNCCODE_GROUP
{
	//======================================
	Uint16	f0[F0NUM];			//F0基本功能组
	Uint16	f1[F1NUM];			//F1电机参数
	Uint16	f2[F2NUM];			//F2矢量控制参数
	Uint16	f3[F3NUM];			//F3V/F控制参数
	
	//======================================
	Uint16	f4[F4NUM];			//F4输入端子
	Uint16	f5[F5NUM];			//F5输出端子
	Uint16	f6[F6NUM];			//F6启停控制
	Uint16	f7[F7NUM];			//F7键盘与显示
	
	//======================================
	Uint16	f8[F8NUM];			//F8辅助功能
	Uint16	f9[F9NUM];			//F9故障与保护
	Uint16	fa[FANUM];			//FA保护
	Uint16	fb[FBNUM];			//FBPID功能
	
	//======================================
	Uint16	fc[FCNUM];			//FC多端速、PLC
	Uint16	fd[FDNUM];			//FD双频制动
	Uint16	fe[FENUM];			//FE280有320没有的功能码
	Uint16	ff[FFNUM];			//FF厂家参数
	
	//======================================
	Uint16	fp[FPNUM];			//FP功能码管理
	
	//======================================
	Uint16	a0[A0NUM];			//A0
	Uint16	a1[A1NUM];			//A1
	Uint16	a2[A2NUM];			//A2
	Uint16	a3[A3NUM];			//A3
	
	//======================================
	Uint16	a4[A4NUM];			//A4
	Uint16	a5[A5NUM];			//A5
	Uint16	a6[A6NUM];			//A6
	Uint16	a7[A7NUM];			//A7
	//======================================
	Uint16	a8[A8NUM];			//A8
	Uint16  a9[A9NUM];          // A9
    Uint16  aa[AANUM];          // AA
    Uint16  ab[ABNUM];          // AB

//======================================
    Uint16  ac[ACNUM];          // AC
    Uint16  ad[ADNUM];          // AD
    Uint16  ae[AENUM];          // AE AIAO出厂校正
    Uint16  af[AFNUM];          // AF 功能码组隐藏
    
//======================================
	
	Uint16	b0[B0NUM];          // B0
	Uint16	b1[B1NUM];          // B1
    Uint16  b2[B2NUM];          // B2
    Uint16  b3[B3NUM];          // B3

//======================================
    Uint16  b4[B4NUM];          // B4
    Uint16  b5[B5NUM];          // B5
    Uint16  b6[B6NUM];          // B6
    Uint16  b7[B7NUM];          // B7

//======================================
    Uint16  b8[B8NUM];          // B8
    Uint16  b9[B9NUM];          // B9
    Uint16  ba[BANUM];          // BA
    Uint16  bb[BBNUM];          // BB

//======================================
    Uint16  bc[BCNUM];           // BC
    Uint16  bd[BDNUM];           // BD
    Uint16  be[BENUM];           // BE
    Uint16  bf[BFNUM];           // BF

//======================================
    Uint16  c0[C0NUM];           // C0
    Uint16  c1[C1NUM];           // C1
    Uint16  c2[C2NUM];           // C2
    Uint16  c3[C3NUM];           // C3

//======================================
    Uint16  c4[C4NUM];           // C4
    Uint16  c5[C5NUM];           // C5
    Uint16  c6[C6NUM];           // C6
    Uint16  c7[C7NUM];           // C7

//======================================
    Uint16  c8[C8NUM];           // C8
    Uint16  c9[C9NUM];           // C9
    Uint16  ca[CANUM];           // CA
    Uint16  cb[CBNUM];           // CB

//======================================
    Uint16  cc[CCNUM];           // CC   用户定制功能码组
    Uint16  cd[CDNUM];           // CD
    Uint16  ce[CENUM];           // CE
    Uint16  cf[CFNUM];           // CF

// 之前的功能码有上下限，属性；之后没有，节省空间
	
//之前的功能码有上下限，属性；之后没有，节省空间
	//======================================
	
	//======================================
	Uint16	fChk[CHK_NUM];		//eepromCheckWord
	
	//======================================
	Uint16	remember[REM_NUM];	//掉电记忆
	
	//之前的数据要放在EEPROM中
	//======================================

    //======================================
	Uint16	u0[U0NUM];			//A4
	Uint16	u1[U1NUM];			//A5
	Uint16	u2[U2NUM];			//A6
	Uint16	u3[U3NUM];			//A7
	//======================================

    //======================================
	Uint16	u4[U4NUM];			//A4
	Uint16	u5[U5NUM];			//A5
	Uint16	u6[U6NUM];			//A6
	Uint16	u7[U7NUM];			//A7
	//======================================
	//======================================
	Uint16	u8[U8NUM];			//A4
	Uint16	u9[U9NUM];			//A5
	Uint16	ua[UANUM];			//A6
	Uint16	ub[UBNUM];			//A7
	//======================================
	//======================================
	Uint16	uc[UCNUM];			//A4
	Uint16	ud[UDNUM];			//A5
	Uint16	ue[UENUM];			//A6
	Uint16	uf[UFNUM];			//A7
	//======================================

};


//=====================================================================
//
//功能码，F0-00,F0-01,...,F1-00,F1-01,...
//
//=====================================================================
struct	FUNCCODE_CODE
{

//======================================
// F0 基本功能组
    Uint16 inverterGpTypeDisp;      // F0-00  GP类型显示
    Uint16 motorCtrlMode;           // F0-01  (电机)控制方式
    Uint16 remote1Src;              // F0-02  远程1命令源选择
    Uint16 frqXSrc;                 // F0-03  主频率源X选择
    Uint16 frqYSrc;                 // F0-04  辅助频率源Y选择
    Uint16 frqYRangeBase;           // F0-05  辅助频率源Y范围选择
    Uint16 frqYRange;               // F0-06  辅助频率源Y范围
    Uint16 frqCalcSrc;              // F0-07  频率源选择
    Uint16 presetFrq;               // F0-08  预置频率
    Uint16 runDir;                  // F0-09  运行方向
    Uint16 maxFrq;                  // F0-10  最大频率
    Uint16 upperFrqSrc;             // F0-11  上限频率源
    Uint16 upperFrq;                // F0-12  上限频率数值设定
    Uint16 upperFrqOffset;          // F0-13  上限频率偏置
    Uint16 lowerFrq;                // F0-14  下限频率数值设定
    Uint16 carrierFrq;              // F0-15  载波频率
    Uint16 varFcByTem;              // F0-16  载波频率随温度调整
    Uint16 accTime1;                // F0-17  加速时间1
    Uint16 decTime1;                // F0-18  减速时间1
    Uint16 ShutDownFrq;             // F0-19  停机频率 // LS_20220420
    Uint16 ShutDownFrqHoldTime;     // F0-20  停机频率保持时间 // LS_20220425
    Uint16 frqYOffsetFc;            // F0-21  辅助频率源偏置的数字设定
    Uint16 frqPoint;                // F0-22  频率指令小数点
    Uint16 frqRemMode;              // F0-23  数字设定频率记忆选择
    enum MOTOR_SN motorSn;          // F0-24  电机选择
    Uint16 accDecBenchmark;         // F0-25  加减速时间基准频率
    Uint16 updnBenchmark;           // F0-26  运行时频率指令UP/DOWN基准
    Uint16 remote1RunFrqBind1;      // F0-27  远程1命令频率源绑定1
    Uint16 remote1RunFrqBind2;      // F0-28  远程1命令频率源绑定2
    Uint16 remote2Src;              // F0-29  远程2命令选择
    Uint16 remote2RunFrqBind;       // F0-30  远程2命令频率绑定

//======================================
//F1电机参数
    struct	MOTOR_PARA_STRUCT_F	motorParaM1;	//	F1-00	F1-26第1电机参数
    struct	PG_PARA_STRUCT1		pgParaM1;		//	f1-27	F1-36第1电机PG卡参数
    Uint16	tuneCmd;							//	F1-37	调谐选择
    Uint16  rsvdf1[3];              //F1-38~40 保留

//======================================
//F2矢量控制参数
    struct  SPEED_LOOP_MENU1  SpeedLoop;         //F2-00~08 速度环参数
    struct	VC_PARA_F	vcParaM1;	                //F2-09~12 第1电机矢量控制参数
    struct  CURRENT_LOOP_MENU1  CurrentLoopMenu; //F2-13~F2-16 电流环参数 原A1组
    
    // Uint16  rsvdF22[6];                         //F2-17~22 保留 // LS_20220421
    Uint16  StartDCBrakeCurrent;                //F2-17 启动直流制动电流/预励磁电流
    Uint16  StartDCBrakeDelay;                  //F2-18 启动直流制动时间/预励磁时间
    Uint16  StopDCBrakeStartFrq;                //F2-19 停机直流制动起始频率
    Uint16  StopDCBrakeCurrent;                 //F2-20 停机直流制动电流
    Uint16  StopDCBrakeDelay;                   //F2-21 停机直流制动时间
    Uint16  rsvdF22[1];                         //F2-22 保留 // LS_20220427
    
    struct  FLUX_CONTROL_MENU FluxContrlMenu;   //F2-23~F2-27
    Uint16  rsvdF26[6];                         //F2-28~33 保留

//======================================
//F3V/F控制参数
/* // LS_20220429
    Uint16	vfCurve;				//	F3-00	VF曲线设定
    Uint16	torqueBoost;			//	F3-01	转矩提升
    Uint16	boostCloseFrq;			//	F3-02	转矩提升截止频率
    Uint16	vfFrq1;					//	F3-03	多点VF频率点1
    Uint16	vfVol1;					//	F3-04	多点VF电压点1
    Uint16	vfFrq2;					//	F3-05	多点VF频率点2
    Uint16	vfVol2;					//	F3-06	多点VF电压点2
    Uint16	vfFrq3;					//	F3-07	多点VF频率点3
    Uint16	vfVol3;					//	F3-08	多点VF电压点3
    Uint16	slipCompCoef;			//	F3-09	转差补偿系数
    Uint16	vfOverMagGain;			//	F3-10	VF过励磁增益
    Uint16	antiVibrateGain;		//	F3-11	振荡抑制增益	      	                    	  	     	
    Uint16	antiVibrateGainMode;	//	F3-12	振荡抑制增益模式
    Uint16	vfVoltageSrc;			//	F3-13	VF分离的电压源
    Uint16	vfVoltageDigtalSet;		//	F3-14	VF分离的电压源数字设定
    Uint16	vfVoltageAccTime;		//	F3-15	VF分离的电压上升时间
*/
    Uint16	vfVoltageSrc;			//	F3-00	VF分离的电压源
    Uint16	vfVoltageDigtalSet;		//	F3-01	VF分离的电压源数字设定
    Uint16	vfVoltageAccTime;		//	F3-02	VF分离的电压上升时间
    Uint16	vfVoltageMax;		    //	F3-03	VF分离的最大输出电压限制
    Uint16	vfLPFCoef;		        //	F3-04	低通滤波器系数
    Uint16	vfHPFCoef;		        //	F3-05	高通滤波器系数
    Uint16	DACurAntiVibrateRatio;  //	F3-06	D轴电流振荡抑制比例
    Uint16	QACurAntiVibrateRatio;  //	F3-07	Q轴电流振荡抑制比例
    Uint16	vfAntiVibrateGain;	    //	F3-08	VF振荡抑制增益
    Uint16	vfVibrateFrqHigh;	    //	F3-09	VF振荡频率上限
    Uint16	vfVibrateFrqLow;		//	F3-10	VF振荡频率下限
    Uint16  rsvdF3[5];              //  F3-11~15 保留
//======================================
//F4输入端子
    Uint16	rsvdF4;                     //	F4-00 保留 // LS_20221026
    Uint16	diFunc[DI_TERMINAL_NUMBER];	//	F4-01--F4-59 DI1端子功能选择
    Uint16  f4rsvd[6];                  //  F4-60 - F4-65
    Uint16	diFilterTime;				//	F4-66 DI滤波时间
    Uint16  diDelay[4];                 //  F4-67-70 DI9-12延时时间
    Uint16  di16Func;                   //  F4-71 DI16端子替代选择
    Uint16  di17Func;                   //  F4-72 DI17端子替代选择
    Uint16	diControlMode;				//	F4-73 端子命令方式
    Uint16	diUpDownSlope;				//	F4-74 端子UP/DOWN速率，改为0.001Hz

//======================================
//F5输出端子

    Uint16	fmOutSelect;				//	F5-00	DO1输出选择
    Uint16	doFunc[DO_TERMINAL_NUMBER];	//	F5-01-F5-68 DO输出选择
    Uint16  doDelayTime[4];             //  F5-69-72

    Uint16  rsvdF5[3];                  //  F5-73 - 75   保留


//======================================
//F6启停控制
    Uint16	startMode;				//	F6-00  启动方式
    Uint16  startDelayTime;         //  F6-01  启动延时
    Uint16  DCBrakeEnable;          //  F6-02  直流制动使能 // LS_20220421
    Uint16  startFrq;               //  F6-03  启动频率
    Uint16  startFrqTime;           //  F6-04  启动频率保持时间
    Uint16  stopDelayTime;          //  F6-05  AFE 停止延时 // LS_20220513
    Uint16  rsvdF62[1];             //  F6-06   保留
    Uint16	accDecSpdCurve;			//	F6-07	加减速方式
    Uint16	sCurveStartPhaseTime;	//	F6-08	S曲线开始段时间比例
    Uint16	sCurveEndPhaseTime;		//	F6-09	S曲线结束段时间比例
    Uint16	stopMode;				//	F6-10	停机方式
    Uint16  EnableBraking;          //  F6-11   叠频制动使能
    Uint16  PulsationFrequency;     //  F6-12   叠频制动叠加频率
    Uint16  BrakePowerLoss;         //  F6-13   叠频制动功率损耗
    Uint16  VdLoss;                 //  F6-14   叠频制动d轴电压损耗
    Uint16  BrakingConstant;        //  F6-15   叠频制动常数
    Uint16	currentLevelSet;        //	F6-16   飞车启动电流设定
    Uint16	currentAccDecTime;      //	F6-17   飞车启动扫描频率加速时间
    Uint16	scanEndThreshold;       //	F6-18   飞车启动扫描结束磁通比例
    Uint16  phasePGain;             //  F6-19   同步切换相位比例增益
    Uint16  phaseIGain;             //  F6-20   同步切换相位积分增益
    Uint16  phaseOffset;            //  F6-21   同步切换相位偏移量
    Uint16  phaseErrorThreshold;    //  F6-22   同步切换相位保护值
    Uint16  frequencyOffset;        //  F6-23   同步切换频率偏移值
    Uint16  transferTimeout;        //  F6-24   切换超时时间
    Uint16  rsvdF625;               //  F6-25   
    Uint16	startDwellSet;          //	F6-26   启动时DWELL频率
    Uint16	srartDwellTime;         //	F6-27   启动时DWELL保持时间
    Uint16	stopDwellSet;           //	F6-28   停止时DWELL频率
    Uint16	stopDwellTime;          //	F6-29   停止时DWELL保持时间
	Uint16  transSel;               //  F6-30   切换方式选择
    Uint16  quickTransFrqInc;       //  F6-31   快速上切换频率增量
    Uint16  quickTransStopDelay;    //  F6-32   提前停机时间
    Uint16  netContCloseTime[4];    //  F6-33~36   工频接触器1-4合闸动作时间

    Uint16  OutContactCtrl;         //  F6-37  输出接触器控制 // LS_20220805
    Uint16  OutContactOnStartDelay; //  F6-38  输出接触器吸合后启动延时 // LS_20220805
    Uint16  rsvdF63[19-2];          //  F6-39 -- F6-55 保留
                                    
//======================================
//F7键盘与显示    
    Uint16 rsvdf700;                //	F7-00               
    Uint16 mfkKeyFunc;			    //	F7-01	MF.K键功能选择
    Uint16 stopKeyFunc;		        //	F7-02	STOP键功能
    Uint16 ledDispParaRun1;	        //	F7-03	LED运行显示参数1
    Uint16 ledDispParaRun2;	        //	F7-04	LED运行显示参数2	      	                	  	     	
    Uint16 ledDispParaStop;	        //	F7-05	LED停机显示参数
    Uint16 powerUpTimeAddup;	    //	F7-06	累计上电时间	      	                      	     	
    Uint16 runTimeAddup;		    //	F7-07	累计运行时间,单位:h
    Uint16 powerAddup;			    //	F7-08	累计耗电量千度
    Uint16 timeNowYear;             //  F7-09   年
    Uint16 timeNowMonDay;           //  F7-10   月日
    Uint16 timeNowHourMint;         //  F7-11   小时分钟
    Uint16 timeNowSec;              //  F7-12   秒
    Uint16 serialNumberL;           //  F7-13   序列号低4位
    Uint16 serialNumberH;           //  F7-14   序列号高4位
    Uint16 serialNumberHH;          //	F7-15	序列号高
    Uint16 serialNumberHHH;         //	F7-16	序列号高
    Uint16 inVolDisCoef;            //  F7-17   输入电压显示系数
    Uint16 inCurDisCoef;            //  F7-18   输入电流显示系数
    Uint16 outVolDisCoef;           //  F7-19   输出电压显示系数	
    Uint16 outCurDisCoef;           //  F7-20   输出电流显示系数
    Uint16 inPowerDisCoef;          //  F7-21   输入功率显示系数
    Uint16 outPowerDisCoef;         //  F7-22   输出功率显示系数
    Uint16 powerAddupH;             //  F7-23   累计耗电量千万度
    Uint16 efficiencyCoef;          //  F7-24   效率显示系数
    Uint16 f7baoliu[11];            //  F7-25-35
//======================================
//F8辅助功能
    Uint16 jogFrq;					//	F8-00	点动运行频率
    Uint16 jogAccTime;				//	F8-01	点动加速时间
    Uint16 jogDecTime;				//	F8-02	点动减速时间	
    Uint16 accTime2;				//	F8-03	加速时间2			
    Uint16 decTime2;				//	F8-04	减速时间2	
    Uint16 accTime3;				//	F8-05	加速时间3
    Uint16 decTime3;				//	F8-06	减速时间3
    Uint16 accTime4;				//	F8-07	加速时间4
    Uint16 decTime4;				//	F8-08	减速时间4
    Uint16 jumpFrq1;				//	F8-09	跳跃频率1

    Uint16 jumpFrq2;				//	F8-10	跳跃频率2
    Uint16 jumpFrqRange;			//	F8-11	跳跃频率幅度 
    Uint16 zeroSpeedDeadTime;       //  F8-12   正反转死区时间
    Uint16 antiReverseRun;			//	F8-13	反转控制,0-允许反转，1-禁止反转
    Uint16 lowerDeal;				//	F8-14	频率低于下限频率运行动作
    Uint16 droopCtrl;               //  F8-15   下垂控制
    Uint16 powerUpTimeArriveSet;    //	F8-16	设定上电时间
    Uint16 runTimeArriveSet;        //	F8-17	设定运行时间
    Uint16 startProtect;			//	F8-18	启动保护选择    
    Uint16 frqFdtValue;			    //	F8-19	频率检测值(FDT电平)

    Uint16 frqFdtLag;				//	F8-20	频率检测滞后值
    Uint16 frqArriveRange;			//	F8-21	频率到达检出幅度
    Uint16 jumpFrqMode;		        //	F8-22	加减速过程中跳跃频率是否有效  	
    Uint16 f8rsvd[1];	            //	F8-23
    Uint16 windMotorDelay; 		    //	F8-24	风机故障延时时间    
    Uint16 accTimefrqChgValue;		//	F8-25	加速时间1/2切换频率点
    Uint16 decTimefrqChgValue;		//	F8-26	减速时间1/2切换频率点
    Uint16 jogWhenRun;		        //	F8-27	端子点动优先  
    Uint16 frqFdt1Value;			//	F8-28	频率检测值(FDT1电平)
    Uint16 frqFdt1Lag;				//	F8-29	频率检测1滞后值

    Uint16 frqArriveValue1;		    //	F8-30	频率到达检测值1
    Uint16 frqArriveRange1;		    //	F8-31	频率到达检出1幅度
    Uint16 frqArriveValue2;		    //	F8-32	频率到达检测值2
    Uint16 frqArriveRange2;		    //	F8-33	频率到达检出2幅度          	                    	  	     	
    Uint16 oCurrentChkValue;		//	F8-34	零电流检测值
    Uint16 oCurrentChkTime;		    //	F8-35	零电流检测延迟时间
    Uint16 softOCValue;			    //	F8-36	软件过流点
    Uint16 softOCDelay;			    //	F8-37	软件过流检测延迟时间          	                    	  	     	
    Uint16 currentArriveValue1;	    //	F8-38	电流到达检测值1
    Uint16 currentArriveRange1;	    //	F8-39	电流到达检测1幅度

    Uint16 currentArriveValue2;	    //	F8-40	电流到达检测值1
    Uint16 currentArriveRange2;	    //	F8-41	电流到达检测1幅度
    Uint16 setTimeMode;             //  F8-42   定时功能选择
    Uint16 setTimeSource;           //  F8-43   定时时间设定选择
    Uint16 setTimeValue;            //  F8-44   设定运行时间
    Uint16 fanControl;              //  F8-45   风扇控制
    Uint16 fanControlTemp;          //  F8-46   风扇工作时温度
    Uint16 zeroSpeed;		        //	F8-47	
    Uint16 wakeUpFrq;               //  F8-48   唤醒频率
    Uint16 wakeUpTime;              //  F8-49   唤醒延迟时间

    Uint16 dormantFrq;              //  F8-50   休眠频率
    Uint16 dormantTime;             //  F8-51   休眠延迟时间
    Uint16 syncTransfer;            //	F8-52   切换选择
    Uint16 auxFuncSel_1;            //	F8-53   辅助功能选择1
    Uint16 auxFuncSel_2;		    //	F8-54   辅助功能选择2
    Uint16 volModify;		        //	F8-55   电压判定
    Uint16 UnderVol;		        //	F8-56   欠压点判定 // LS_20220421
    Uint16 auxFuncSel_3;		    //	F8-57   辅助功能选择3
    Uint16 highSwitchCloseDelay;    //  F8-58   合闸延时
    Uint16 inputVolFilter;          //  F8-59   输入电压滤波时间，0.01s
    
    Uint16 dehumidifierTime;        //  F8-60   除湿工作时间，1min
    Uint16 dehumidifierSpaceTime;   //  F8-61   除湿间隔时间，1hour
    Uint16 rsvdxx;                  //  F8-62   
    Uint16 frqSetRate;              //  F8-63   频率给定比例
    Uint16 autoRunAfterPowerOnTime; //  F8-64   掉电来电保持掉电前状态 0时不开启
    Uint16 specifiedFaultOutput;    //  F8-65   指定故障输出
    Uint16 autoBypassDelay;         //  F8-66   自动旁路延时
    Uint16 lineContactorOnTime;     //  F8-67   旁路柜工频接触器闭合时间
    Uint16 jumpFrq3;                //  F8-68   跳跃频率3
    Uint16 jump3FrqRange;           //  F8-69   跳跃频率3幅度
    
    Uint16 otherPasswordInfo;       //  F8-70   密码提示 71-74 有密码保护
    Uint16 inspectTimeSet;          //  F8-71   检修时间设定
    Uint16 rsvdf872[2];             //  F8-72 - 73 已用
    Uint16 rsvdEndF874;             //  F8-74   已用
    Uint16 brakeItSet;              //  F8-75   抱闸控制---转矩设定
    Uint16 brakeItFilterTime;       //  F8-76   抱闸控制---转矩滤波时间
    Uint16 brakeFrqSet;             //  F8-77   抱闸控制---频率设定
    Uint16 brakeFrqFilterTime;      //  F8-78   抱闸控制---频率滤波时间
    Uint16 heatWindOffTime;         //  F8-79   散热风机延时关闭时间
    Uint16 heatFaultDelay;          //  F8-80   散热风机故障延时时间
    
    Uint16 fcbFrq;                  //  F8-81   快速制动切换频率
    Uint16 fcbLimit;                //  F8-82   FCB进入阈值 退出阈值为该值的一半
    Uint16 fcbDecTime;              //  F8-83   FCB快速制动减速时间
    Uint16 brakeResTime;            //  F8-84   制动电阻累计接入时间阈值
    Uint16 brakeResRstTime;         //  F8-85   制动电阻工作清零时间

    Uint16 rsvdF8[14];              //  F8-86 - 99 保留

//======================================
//F9保护设定	
    Uint16	overloadMode;					//	F9-00	电机过载保护选择
    Uint16	overloadTime;					//	F9-01	电机过载保护时间
    Uint16	foreOverloadCoef;				//	F9-02	电机过载预警系数
    Uint16	overloadCoef;					//	F9-03   过载阈值
    Uint16	baoliuf9[2];                    //	F9-04   05
    Uint16	motorTripVoltage;	            //	F9-06   电机过压保护点
    Uint16	shortCheckMode;					//	F9-07	上电对地短路保护功能
    Uint16	errAutoRstNumClearTime;         //	F9-08   故障自动复位次数清零时间
    Uint16	errAutoRstNumMax;				//	F9-09	故障自动复位次数	      	                    			  	     	
    Uint16	errAutoRstRelayAct;				//	F9-10	故障自动复位期间故障继电器动作选择
    Uint16	errAutoRstSpaceTime;			//	F9-11	故障自动复位间隔时间,0.1s
    Uint16	inPhaseLossProtect;				//	F9-12	输入缺相保护选择
    Uint16	outPhaseLossProtect;			//	F9-13	输出缺相保护选择

    Uint16  inputCurrentImbalanceLimit;     //  F9-14   输入电流不平衡阈值
    Uint16	outputCurrentImbalanceLimit;    //	F9-15   输出电流不平衡阈值
    Uint16  inputGroundFaultLimit;          //  F9-16   输入对地短路故障阈值
    Uint16  inputVolImbalanceLimit;         //  F9-17   输入电压不平衡阈值
    Uint16  underVoltagePropGain;           //  F9-18
    Uint16  underVoltageIntegGain;          //  F9-19
    Uint16  cycProtectIntegGain;            //  F9-20
    Uint16  cycProtectLimit;                //  F9-21
    Uint16  excessLossIdle;                 //  F9-22
    Uint16  exdessLossRunning;              //  F9-23

    Uint16  xformerTapSetting;              //  F9-24
    Uint16  xformerThermalGain;             //  F9-25
    Uint16  xformerProtectionConst;         //  F9-26   
    Uint16	maxLoadInertia;                 //	F9-27
    Uint16  outputGroundFaultLimit;         //  F9-28   输出对地短路故障阈值
    Uint16  rsvdf929;        				//  F9-29   保留
    Uint16	invIOCSetpoint;					//	F9-30   过流点设定
    Uint16	invCurrentLimit;                //	F9-31   最大电流限制
    Uint16	load0MaxSpeed;                  //	F9-32
    Uint16	load10MaxSpeed;                 //	F9-33
    Uint16	load17MaxSpeed;                 //	F9-34
    Uint16	load25MaxSpeed;                 //	F9-35
    Uint16	load50MaxSpeed;                 //	F9-36
    Uint16	load100MaxSpeed;                //	F9-37	
    Uint16  offTransitoryKp;                //  F9-38
    Uint16  offTransitoryKi;                //  F9-39
    Uint16  motorStallFrq;                  //  F9-40 堵转频率
    Uint16  motorStallTime;                 //  F9-41 堵转时间
    Uint16  motorExcitCoef;                 //  F9-42 电机励磁故障保护阈值
    Uint16  motorExcitLimit;                //  F9-43 电机励磁故障检测时间
    Uint16  inputOv;						//  F9-44 凯撒--输入过压故障阈值
//    Uint16  rsvdf938[2];                    //  F9-45 - 46
    Uint16  invTempPreAlarm;                //  F9-45 UVW 高温预警阈值
    Uint16  invTempAlarm;                   //  F9-46 UVW 高温报警阈值
    
    Uint16	errorAction[5];					//	F9-47-F9-51 故障时保护动作选择1-5
    Uint16	oterErrAction[2];				//	F9-52-F9-53 故障指示选择1,2
    Uint16	errorRunFrqSrc;					//	F9-54	故障时继续运行频率选择
    Uint16	errorSecondFrq;					//	F9-55	异常备用频率设定
    Uint16	motorOtMode;					//	F9-56	电机温度传感器类型
    Uint16	motorOtProtect;					//	F9-57	电机过热保护阈值
    Uint16	motorOtCoef;					//	F9-58	电机过热预报警阈值
    Uint16  offTransiNoStopEnable;          //  F9-59   瞬停不停使能
    Uint16  recoverAccTime;                 //  F9-60   瞬停不停恢复加速时间
    Uint16  recoverDecTime;                 //  F9-61   瞬停不停恢复减速时间
    Uint16  rsvdf91;                        //  F9-62   
//    Uint16	pOffTransitoryNoStop;			//	F9-59	瞬停不停功能选择
//    Uint16	pOffTransitoryFrqDecSlope;		//	F9-60	瞬停自动减速切换频率点
//    Uint16	pOffVolBackTime;				//	F9-61	瞬停不停电压回升判断时间	      	                    			  	     	
//    Uint16	pOffThresholdVol;				//	F9-62	瞬停不停动作判断电压
    Uint16	loseLoadProtectMode;			//	F9-63	掉载保护选择
    Uint16	loseLoadLevel;					//	F9-64	掉载检出水平
    Uint16	loseLoadTime;					//	F9-65	掉载检出时间
    Uint16  rsvdf966;                       //  F9-66
    Uint16	osChkValue;						//	F9-67	过速度检测值
    Uint16	osChkTime;						//	F9-68	过速度检测时间
    Uint16	devChkValue;					//	F9-69	速度偏差过大检测值
    Uint16	devChkTime;						//	F9-70	速度偏差过大检测时间
    Uint16  windMotorDisableDelay;          //  F9-71   风机关闭延时时间
    Uint16  coreFuncSel[2];                 //  F9-72 73
    Uint16  specFaultEnable;              	//  F9-74   指定故障使能
    Uint16  specFauAutoRstNumMax;           //  F9-75   指定故障自动复位次数
    Uint16  allowWindFaultNum;              //  F9-76   允许风机故障数
    Uint16  invCurrentDerateLimit1;         //  F9-77   风机异常最大输出电流限制1
    Uint16  invCurrentDerateLimit2;         //  F9-78   风机异常最大输出电流限制2
    Uint16	errAutoRstStopRelayAct;         //  F9-79\

    Uint16  rsvdf976[20];                   //  F9-80 -99
    
//======================================
//FA PID功能
    Uint16	pidSetSrc;				//	FA-00	PID给定源
    Uint16	pidSet;					//	FA-01	PID数值给定,0.1%
    Uint16	pidFdbSrc;				//	FA-02	PID反馈源
    Uint16	pidDir;					//	FA-03	PID作用方向
    Uint16	pidDisp;				//	FA-04	PID给定反馈量程
    Uint16	pidKp;					//	FA-05	比例增益P
    Uint16	pidTi;					//	FA-06	积分时间I
    Uint16	pidTd;					//	FA-07	微分时间D
    Uint16	reverseCutOffFrq;		//	FA-08	PID反转截止频率
    Uint16	pidErrMin;				//	FA-09	PID偏差极限
    Uint16	pidDLimit;				//	FA-10	PID微分限幅
    Uint16	pidSetChangeTime;		//	FA-11	PID给定变化时间
    Uint16	pidFdbLpfTime;			//	FA-12	PID反馈滤波时间
    Uint16	pidOutLpfTime;			//	FA-13	PID输出滤波时间
    Uint16	pidSampleTime;			//	FA-14	PID采样周期(暂未做)
    Uint16	pidKp2;					//	FA-15	PID比例增益P2
    Uint16	pidTi2;					//	FA-16	PID积分时间I2
    Uint16	pidTd2;					//	FA-17	PID微分时间D2
    Uint16	pidParaChgCondition;	//	FA-18	PID参数切换条件
    Uint16	pidParaChgDelta1;		//	FA-19	PID参数切换偏差1
    Uint16	pidParaChgDelta2;		//	FA-20	PID参数切换偏差2
    Uint16	pidInit;				//	FA-21	PID初值
    Uint16	pidInitTime;			//	FA-22	PID初值保持时间
    Uint16	pidOutDeltaMax;			//	FA-23	PID两次输出之间偏差的最大值
    Uint16	pidOutDeltaMin;			//	FA-24	PID两次输出之间偏差的最小值
    Uint16	pidIAttribute;			//	FA-25	PID积分属性
    Uint16	pidFdbLoseDetect;		//	FA-26	PID反馈丢失检测值
    Uint16	pidFdbLoseDetectTime;	//	FA-27	PID反馈丢失检测时间
    Uint16	pidCalcMode;			//	FA-28	PID运算模式(停机是否运算).供水模式下，停机时PID也计算.

//======================================
//Fb故障记录
    Uint16	errorLatest6;					//	Fb-00	第六次故障类型	      	                    			  	     	
    Uint16	errorLatest7;					//	Fb-01	第七次故障类型
    Uint16	errorLatest8;					//	Fb-02	第八次故障类型
    Uint16	errorLatest9;					//	Fb-03	第九次故障类型
    Uint16	errorLatest10;					//	Fb-04	第十次(最近一次)故障类型

    struct	ERROR_SCENE_STRUCT	errorScene10;//  Fb-05--12
    Uint16	rsvdF90[2];                     //  Fb-13--14

    struct	ERROR_SCENE_STRUCT	errorScene9;//  Fb-15--22
    Uint16	rsvdF91[2];                     //  Fb-23--24

    struct	ERROR_SCENE_STRUCT	errorScene8;//	Fb-25	第八次故障时频率
    										//	Fb-26	第八次故障时输出电流
    										//	Fb-27	第八次故障时输出电压
    										//	Fb-28	第八次故障时输入电流
    										//	Fb-29	第八次故障时输入电压
    										  	     
    										//	Fb-30	第八次故障时变频器状态
    										//	Fb-31	第八次故障时时间
    										//	Fb-32	第八次故障时时间
    Uint16	rsvdF92[2];						//	Fb-33--34
                                              	
    struct	ERROR_SCENE_STRUCT	errorScene7;//	Fb-35--42第七次故障现场
    Uint16	rsvdF921[2];					//	Fb-43--44
          	                                  	
    struct	ERROR_SCENE_STRUCT	errorScene6;//	Fb-45--52第六次故障现场
    Uint16	rsvdF922[2];					//	Fb-53--54

    Uint16  errScene5;                      //  Fb-55   第五次故障类型
    Uint16  error5Info;                     //  Fb-56   第五次故障提示信息
    Uint16  errScene4;                      //  Fb-57   第四次故障类型
    Uint16  error4Info;                     //  Fb-58   第四次故障提示信息
    Uint16  errScene3;                      //  Fb-59   第三次故障类型
    Uint16  error3Info;                     //  Fb-60   第三次故障提示信息
    Uint16  errScene2;                      //  Fb-61   第二次故障类型
    Uint16  error2Info;                     //  Fb-62   第二次故障提示信息
    Uint16  errScene1;                      //  Fb-63   第一次故障类型
    Uint16  error1Info;                     //  Fb-64   第一次故障提示信息

    Uint16  cellErrorInfo[4];               //  Fb-65 - Fb-68

//======================================
//FC多端速、PLC
    Uint16	plcFrq[PLC_STEP_MAX];	//FC-00--FC-15多段指令0-多段指令15
    Uint16	plcRunMode;				//FC-16PLC运行方式
    Uint16	plcPowerOffRemMode;		//FC-17PLC掉电记忆选择
    struct	PLC_STRUCT	plcAttribute[PLC_STEP_MAX];//FC-18--FC-49PLC运行时间，加减速时间选择
    Uint16	plcTimeUnit;			//FC-50PLC运行时间单位
    Uint16	plcFrq0Src;				//FC-51多段指令0给定方式

//======================================
//FD 通讯参数
    Uint16	commBaudRate;			//FD-00 通讯波特率
    Uint16	commParity;				//FD-01 数据格式
    Uint16	commSlaveAddress;		//FD-02 本机地址
    Uint16	commDelay;				//FD-03 应答延迟
    Uint16	commRs485OverTime;	    //FD-04 RS485通讯超时时间
    Uint16	commProtocol;			//FD-05 通讯数据传送格式选择
    Uint16  commProtocolSec;       //FD-06 通信协议选择
    Uint16	rsvdFd1[1];		        //FD-07 保留
    Uint16	commProfibusOverTime;   //fd-08 profibus通讯超时时间

    Uint16	rsvdFd0[2];		        //FD-09 10 保留
    Uint16	multiframe;             //FD-11 // LS_20220712
//======================================
//FE 用户定制参数
    Uint16	userCustom[FENUM];      //FE-00~31

//======================================
//FF厂家参数
    Uint16	factoryPassword;		//FF-00 厂家密码
    Uint16	inverterType;			//FF-01 变频器机型
    Uint16	inverterCodeProtect;	//FF-02 FF-10 到 FF-23 参数保护
    Uint16	inverterPower;			//FF-03 变频器功率
    Uint16	FpgaPwmMode;		    //FF-04 发波方式 // LS_20231026      	                		
    Uint16	uvGainWarp;				//FF-05 UV两相电流采样增益偏差
    struct  VOL_CUR_SAMPLE_PARA_STR VolCurSamplePara;    //FF-06 - FF-15
    struct  DRIVE_RATING_PARA_STR DriveRatingPara;       //FF-16 - FF-19
    Uint16  AFEratingCur;           //FF-20 AFE额定电流
    Uint16  installedCells;         //FF-21 每相单元个数
    Uint16  cellAttribute;          //FF-22 单元型号
    Uint16  filterCTSecTurn;        //FF-23 输出滤波器电流霍尔变比
    Uint16  preChargeMode;          //FF-24 预充方案选择
    Uint16  sampBoardEn;            //FF-25 光纤版采样使能
    Uint16  HallDirection;          //FF-26 霍尔方向 // LS_20240229
    Uint16  DeadTime;               //FF-27 死区时间 // LS_20240229

//======================================
//FP用户密码,参数初始化
    Uint16	userPassword;			//FP-00 用户密码
    Uint16	paraInitMode;			//FP-01 参数初始化
    Uint16	funcParaView;		    //FP-02 显示属性
    Uint16	menuMode;		        //FP-03 菜单模式
    Uint16	userPasswordReadOnly;	//FP-04 只读用户密码
    Uint16	rsvdFp;					//FP-05 保留

//======================================
//A0转矩控制和限定参数
    Uint16	torqueCtrl;				//A0-00 转矩控制
    Uint16	driveUpperTorqueSrc;	//A0-01 驱动转矩上限源
    Uint16	brakeUpperTorqueSrc;	//A0-02 制动转矩上限源
    Uint16	driveUpperTorque;		//A0-03 驱动转矩上限
    Uint16	brakeUpperTorque;		//A0-04 制动转矩上限
    Uint16	torqueCtrlFwdMaxFrq;	//A0-05 转矩控制正向最大频率
    Uint16	torqueCtrlRevMaxFrq;	//A0-06 转矩控制反向最大频率
    Uint16	torqueCtrlAccTime;		//A0-07 转矩加速时间
    Uint16	torqueCtrlDecTime;		//A0-08 转矩减速时间

//======================================
//A1组参数
    Uint16 a1[A1NUM];
//======================================
//A2第2电机参数
    struct	MOTOR_FC	motorFcM2;	//	第2电机参数
  
//======================================                                	  	
//A3第2电机参数                   	  	
    struct	MOTOR_FC	motorFcM3;	//	第3电机参数

//======================================                                  	  	
//A4第2电机参数                   	  	
    struct	MOTOR_FC	motorFcM4;	//	第4电机参数

//======================================
//A5 控制优化参数
    Uint16 DeadTimeComp;                                    // A5-00 // LS_20230426
    Uint16 FeedForwardConstant;                             // A5-01 
    Uint16 magneChainLoopFeedScale;                         // A5-02
    struct OUTPUT_CONNECTION_MENU1 OutputConnectionM;       // A5-03 - A5-07
    struct LOW_FREQUENCY_COMPENSATION_MEMU LowFrCompMenu;   // A5-08 - A5-10
    struct HIGH_TORQUE_START_PARA highTorqueStartPara;      // A5-11 - 14
    struct MAGEN_CHAIN_LOOP_PARA magenChainLoopPara;        // A5-15 - 17
    Uint16 torqueLimitOtherEnable;                          // A5-18
    Uint16 npcKp;                                           // A5-19 中点控制Kp
    Uint16 npcKi;                                           // A5-20 中点控制KI
    Uint16 npcUpLimitSet;                                   // A5-21 中点控制上限
    Uint16 MidDevErThreshold;                               // A5-22 中点偏差过大阈值 // CF-23
    Uint16 halfGenVolOV;                                    // A5-23 半母线过压点设定
    Uint16 halfGenVolOL;                                    // A5-24 半母线超限点设定
    Uint16 genVolOV;                                        // A5-25 母线过压点设定
    Uint16 genVolOL;                                        // A5-26 母线超限点设定
    Uint16 overVolInhibitKp;                                // A5-27 过压抑制电压环Kp
    Uint16 overVolInhibitKi;                                // A5-28 过压抑制电压环Ki
    Uint16 fastTrackKp;                                     // A5-29 快速飞车启动锁相环比例增益
    Uint16 fastTrackKi;                                     // A5-30 快速飞车启动锁相环积分增益
    Uint16 fastTrackEndLimit;                               // A5-31 快速飞车启动结束阈值
    Uint16 SwObVolCoff;                                     // A5-32 软件观测电压系数 // CF-13 // LS_20221026
    Uint16 IfOrVectorSwitchFreq;                            // A5-33 IF模式与矢量控制切换频率 // CF-16 // LS_20221026
    Uint16 OlProtectCoff;                                   // A5-34 过载保护系数 // CF-17 // LS_20221026
    Uint16 AFELoadObserverEn;                               // A5-35 负载观测器使能 // CF-18 // LS_20221026
    Uint16 ObVolSel;                                        // A5-36 观测电压选择（1：软件观测 2：硬件观测）// CF-19 // LS_20221026
    Uint16 WeakFluxdepth;                                   // A5-37 弱磁深度 // CF-24 // LS_20221026
    Uint16 PmsmMtpaCtlEn;                                   // A5-38 同步机MTPA控制使能 // CF-18 // LS_20221026
    Uint16 AFEVolUnbalancedlimit;                           // A5-39 电网电压不平衡电流正负序解耦控制阈值 // CF-19 // LS_20221026
    Uint16 ErPNDevOrOutLackPhaseSel;                        // A5-40 中点偏差和输出缺相故障选择 // CF-20 // LS_20221129
    Uint16 SingleOrMultiMotorCurSel;                        // A5-41 单机并机电流选择 // CF-13 // LS_20221129
    Uint16 DispOutPowerAdjustCoff;                          // A5-42 输出功率显示系数 // CF-10 // LS_20221129
    Uint16 AFEBusVolMinLimit;                               // A5-43 AFE母线电压下限 // CF-12 // LS_20221129
    Uint16 AFEOutVolD;                                      // A5-44 AFE D轴输出电压 // CF-14 // LS_20221129
    Uint16 AFEExtraOutVolQ;                                 // A5-45 AFE Q轴附加输出电压 // CF-15 // LS_20221129
    Uint16 MatlabScopeEnable;                               // A5-46 MATLAB示波器使能 // CF-21 // LS_20221129
    Uint16 PmsmCoefBemSet;                                  // A5-47 同步机观测器反电动势系数 // CF-22 // LS_20221129
    Uint16 swPoleCoeff;                                     // A5-48 软件补偿极点系数 // CF-14 // LS_20221129
    Uint16 PR1PropGain;                                     // A5-49 比例谐振1比例增益 // LS_20221215
    Uint16 PR1IntegGain;                                    // A5-50 比例谐振1谐振增益 // LS_20221215
    Uint16 PR1BandWidth;                                    // A5-51 比例谐振1带宽 // LS_20221215
    Uint16 PR1CenterFreq;                                   // A5-52 比例谐振1中心频率 // LS_20221215
    Uint16 PR2PropGain;                                     // A5-53 比例谐振2比例增益 // LS_20221215
    Uint16 PR2IntegGain;                                    // A5-54 比例谐振2谐振增益 // LS_20221215
    Uint16 PR2BandWidth;                                    // A5-55 比例谐振2带宽 // LS_20221215
    Uint16 PR2CenterFreq;                                   // A5-56 比例谐振2中心频率 // LS_20221215
    Uint16 AfeMode;                                         // A5-57 整流运行方式 // LS_20230426
    Uint16 LAfeBusVolMaxLimit;                              // A5-58 母线电压回馈阈值上限 // LS_20230426
    Uint16 LAfeBusVolMinLimit;                              // A5-59 母线电压回馈阈值下限 // LS_20230426
    Uint16 LAfeDelayTime;                                   // A5-60 回馈延时时间 // LS_20230426

//======================================
//A6模拟量及脉冲设定
    Uint16 curveSet2P1[4];          // A6-00--A6-03  曲线1，2点，最大值，最小值
    Uint16 ai1FilterTime;           // A6-04  AI1滤波时间, 10ms

    Uint16 curveSet2P2[4];          // A6-05--A6-08  曲线2，2点
    Uint16 ai2FilterTime;           // A6-09  AI2滤波时间, 10ms

    Uint16 curveSet2P3[4];          // A6-10--A6-13  曲线3，2点

    Uint16	curveSet4P1[8];			//	A6-14--A6-21曲线4，4点，最大值，最小值，2个中间点
    Uint16	curveSet4P2[8];			//	A6-22--A6-29曲线5，4点

    struct	AI_JUMP	aiJumpSet[DSP_AI_NUMBER + AI_NUMBER + PLC_AI_NUMBER];	                                  
                                    //  A6-30 -41
    Uint16  rsvdA61[4 -2];             //  A6-42--45 // LS_TEST

    Uint16	ai1VoltageLimit;		//	A6-46	AI1输入电压下限
    Uint16	ai1VoltageUpper;		//	A6-47	AI1输入电压上限

    Uint16	aiCurveSrc;			    //	A6-48	AI设定曲线选择
    Uint16	aiCurveSrc2;			//	A6-49	AI设定曲线选择2   

    Uint16	aiLimitSrc;				//	A6-50	AI下限选择
    Uint16	aiLimitSrc2;			//	A6-51	AI下限选择2


    Uint16	aoFunc[DSP_AO_NUMBER + AO_NUMBER + PLC_AO_NUMBER];
                                    //	A6-52	AO1输出选择-DSP
                                    //	A6-53	AO2输出选择-DSP
                                    //	A6-54	AO3输出选择-DSP
                                    //	A6-55	AO4输出选择-ARM
                                    //	A6-56	AO5输出选择-ARM
                                    //	A6-57	AO6输出选择-PLC
                                    //	A6-58	AO7输出选择-PLC
                                    //	A6-59	AO8输出选择-PLC
                                    //	A6-60	AO9输出选择-PLC
    AO_PARA	aoPara[DSP_AO_NUMBER + AO_NUMBER + PLC_AO_NUMBER];				
                                    //DSP   //	A6-61	AO1零偏系数0
                                            //	A6-62	AO1增益1
                                            //	A6-63	AO2零偏系数2
                                            //	A6-64	AO2增益3
                                            //	A6-65	AO3零偏系数4
                                            //	A6-66	AO3增益5
                                            //ARM   //	A6-67	AO4零偏系数6
                                            //	A6-68	AO4增益7
                                            //	A6-69	AO5零偏系数8
                                            //	A6-70	AO5增益9
                                            //PLC   //	A6-71	AO6零偏系数10
                                            //	A6-72	AO6增益11
                                            //	A6-73	AO7零偏系数12
                                            //	A6-74	AO7增益13
                                            //	A6-75	AO8零偏系数14
                                            //	A6-76	AO8增益15
                                            //	A6-77	AO9零偏系数16
                                            //	A6-78	AO9增益17
    Uint16  aoOutMode;              // A6-79  AO输出类型选择

    Uint16  pulseInMin;             // A6-80  PULSE最小输入
    Uint16  pulseInSetMin;          // A6-81  PULSE最小输入对应设定
    Uint16  pulseInMax;             // A6-82  PULSE最大输入
    Uint16  pulseInSetMax;          // A6-83  PULSE最大输入设定
    Uint16  pulseInFilterTime;      // A6-84  PULSE滤波时间, 10ms
    Uint16  fmFuncSelect;           // A6-85  输出功能选择
    Uint16  fmpOutMaxFrq;           // A6-86  FMP输出最大频率
    Uint16  ai3FilterTime;          // A6-87  AI3滤波时间, 10ms
    Uint16  ai4FilterTime;          // A6-88  AI4滤波时间, 10ms    
    Uint16  plcFilterTime;          // A6-89  plcAI5/AI6滤波时间，1拍为8ms
    Uint16  aiOffSel;               // A6-90  Ai掉线相关处理

//======================================
//A7变频器参数
    Uint16  rsvdA7[A7NUM];                  //  A7-00 - A7-14
//======================================   
    Uint16 p2pEnable;               // A8-00 点对点通讯功能选择
    Uint16 p2pTypeSel;              // A8-01 主从选择
    Uint16 p2pFollowMasterCmd;      // A8-02 从机跟随主机命令 
    Uint16 p2pSendDataSel;          // A8-03 主机发送数据   0:同步转速  1:设定频率  
    
    Uint16 p2pRevOffsetTorque;      // A8-04 接受数据零偏
    Uint16 p2pRevGainTorque;        // A8-05 接收数据增益
    Uint16 p2pCommErrCheckTime;     // A8-06 点对点通讯中断检测时间
    Uint16 p2pCommSendCyc;          // A8-07 点对点通讯主机发送数据周期
    Uint16 p2pRevOffsetSpeed;       // A8-08 接受数据零偏
    Uint16 p2pRevGainSpeed;         // A8-09 接收数据增益

    Uint16 flyPreventCoef;          // A8-10 防飞车系数
    Uint16 windowFrq;               // A8-11 视窗频率
    Uint16 a8[A8NUM-12-2-3];        // A8-12 20 // LS_20221026 // LS_20240229
    Uint16 MsSlaveNum;              // A8-21 从机数量 // LS_20240229
    Uint16 MsSlaveMask;             // A8-22 从机故障报警屏蔽 // LS_20240229
    Uint16 MsSlaveFree;             // A8-23 从机故障报警级别 // LS_20240229
    Uint16 MsAlarmDelay;            // A8-24 主从报警延时 // LS_20221026
    Uint16 AfeCommMode;             // A8-25 四象限通讯方式 —— 0：端子，1：485 // LS_20221026
//======================================    
//A9 单元参数
    Uint16 bypassEnable;            //A9-00 旁路使能
    Uint16 minCells;                //A9-01 旁路时每相最小单元数
    Uint16 contactorSettlingTime;   //A9-02 旁路接触器吸合时间
    Uint16 maxBakEMFDecayTime;      //A9-03 最大反电势衰减时间
    Uint16 cellManualBypassL;       //A9-04 手动旁路设定A1-A6   16个
    Uint16 cellManualBypassH;       //A9-05 手动旁路设定B6-C9   11个
    Uint16 cellNum;                 //A9-06 设置查看的单元序号
    Uint16 cellInfoEnable;          //A9-07 afe单元读故障信息
    Uint16 prechargeDelayTime;      //A9-08 预充延时时间
    Uint16 prechargeServiceMode;    //A9-09 预充模式选择
    Uint16 prechargeServiceStart;   //A9-10 预充开始
    Uint16 rsvda911;                //A9-11 
    Uint16 rsvda912;                //A9-12 
    Uint16 cellBypassSel1;          //A9-13 单元旁路类型及自动复位属性选择1
    Uint16 cellBypassSel2;          //A9-14 单元旁路类型及自动复位属性选择2

    Uint16 prechargeAoSel;          // A9-15 预充模拟量选择
    Uint16 preChargeAutoDelay;      // A9-16 自动预充开始延时 // LS_20231205
    Uint16 preChargeOverTime;	    // A9-17 
    Uint16 preChargePoint;          // A9-18 第一段 第二段切换点
    Uint16 fStepPreChargeAccTime;   // A9-19 第一段预充加速时间
    Uint16 preChargePoint2;         // A9-20 第二段 第三段切换点
    Uint16 sStepPreChargeAccTime;   // A9-21 第二段预充加速时间
    Uint16 tStepPreChargeAccTime;	// A9-22 第三段预充加速时间
    Uint16 preChargeTime;           // A9-23 预充时间       
    Uint16 preChargeDecTime;        // A9-24 预充减速时间

    Uint16 siliconFrqSet;           // A9-25 可控硅脉冲频率
    Uint16 siliconRateSet;          // A9-26 可控硅脉冲占空比
    Uint16 siliconFilterTime;       // A9-27 可控硅反馈滤波时间
    Uint16 siliconFilterCnt;        // A9-28 可控硅反馈滤波次数
    Uint16 preCharInCurLimit;       // A9-29 预充电流检测阈值
    Uint16 simulatCelFat[2];        // A9-30 31 单元模拟故障--仅用于II代机演示自动旁路功能
    Uint16 losePhaseFilter;         // A9-32 单元输入缺相滤波
    Uint16 a9rsvd[2];               // A9-32-34 
//======================================    
    
    Uint16  aa[AANUM];               // AA
    Uint16  ab[ABNUM];               // AB

//======================================
// AC 采样阈值
// AC AIAO校正值
// AI1:DSP1; AI2:DSP2; AI3:ARM1; AI4:ARM2
    struct ANALOG_CALIBRATE_CURVE aiCalibrateCurve[DSP_AI_NUMBER+AI_NUMBER -1];    // AC-00 - AC-15, AI1/2/3/4校正曲线 // LS_TEST
    struct ANALOG_CALIBRATE_CURVE aoCalibrateCurve[DSP_AO_NUMBER+AO_NUMBER];	// AC-16 - AC-35, AO1/2/3/4/5校正曲线
//======================================    
    Uint16  ad[ADNUM];               // AD
    Uint16  ae[AENUM];               // AE
    Uint16  af[AFNUM];               // AF
    
//======================================
//B0 逻辑控制参数
    Uint16 torqueStartDirection;    // 00 启动方向
    Uint16 brakeOpenFrq;            // 01 松闸频率
    Uint16 brakeOpenCur;            // 02 松闸电流
    Uint16 brakeOpenTime;           // 03 松闸时间
    Uint16 brakeCloseFrq;           // 04 抱闸频率
    Uint16 brakeCloseTime;          // 05 抱闸时间
    Uint16 brakeCloseDelay;         // 06 抱闸延时
    Uint16 zeroSpeedBrakeDelay;     // 07 零速抱闸延时
    Uint16 brakeFdbCheck;           // 08 抱闸反馈检测
    Uint16 brakeFdbCheckDelay;      // 09 抱闸反馈延时
    Uint16 cmdReverseControl;       // 10 指令反向控制
    Uint16 restartDelay;            // 11 再启动等待时间
    Uint16 stopModify;              // 12 停车判断
    Uint16 logicErrAction[2];       // 13 14 故障动作选择

    Uint16 rsvdB0[B0NUM-15-30];     // B0-15 - B0-19 // LS_20230525  
    Uint16 UscompCutFre;            // B0-20 转矩提升截止频率
    Uint16 VF_UsCompGian;           // B0-21 自动转矩提升增益
    Uint16 ManualTorIncrGian;       // B0-22 手动转矩提升增益
    Uint16 VfShakEnable;            // B0-23 振荡抑制使能
    Uint16 vfshakIQSLpfK2;          // B0-24 Q轴振荡电流滤波
    Uint16 vfshakIQSLpfK1;          // B0-25 Q轴参考电流滤波
    Uint16 VfShakVotGianUpLmt;      // B0-26 振荡抑制增益调整上限
    Uint16 VfShakVotGianLowLmt;     // B0-27 振荡抑制增益调整下限
    Uint16 BusVolOverSatCtrEnable;  // B0-28 母线过压抑制使能
    Uint16 BusVolOverRef;           // B0-29 母线过压抑制点
    Uint16 BusVolOverPropGian;      // B0-30 母线过压抑制比例系数
    Uint16 BusVolOverInteGian;      // B0-31 母线过压抑制积分系数
    Uint16 BusVolOvFre;             // B0-32 母线过压抑制提升频率限幅
    Uint16 BusVolOverGianV;         // B0-33 母线过压抑制电压调节增益
    Uint16 BusVolOverGianf;         // B0-34 母线过压抑制频率调节增益
    Uint16 BusVolLowSatCtrEnable;   // B0-35 母线欠压抑制使能
    Uint16 BusVolLowRef;            // B0-36 母线欠压抑制点
    Uint16 BusVolLowPropGian;       // B0-37 母线欠压抑制比例系数
    Uint16 BusVolLowInteGian;       // B0-38 母线欠压抑制积分系数
    Uint16 BusVotLoFre;             // B0-39 母线欠压抑制下调频率限幅
    Uint16 BusVolLowGianV;          // B0-40 母线欠压抑制电压调节增益
    Uint16 BusVolLowGianf;          // B0-41 母线欠压抑制频率调节增益
    Uint16 OverCurSatCtrEnable;     // B0-42 过流抑制使能
    Uint16 OverCurRef;              // B0-43 过流抑制点
    Uint16 OverCurPropGian;         // B0-44 过流抑制比例系数
    Uint16 OverCurInteGian;         // B0-45 过流抑制积分系数
    Uint16 OverCurGain;             // B0-46 过流抑制调节增益
    Uint16 rsvdB0_1[3];             // B0-47 - B0-49
//======================================
//b1 整流参数
#if CM3000
    Uint16 caesarAFEControlMode;        // 00 工作模式选择
    Uint16 caesarAFEGenVoltageSet;      // 01 母线电压设定
    Uint16 caesarAFECarrierFrq;         // 02 载波频率
    Uint16 caesarAFEVolLoopKp;          // 03 电压环比例系数
    Uint16 caesarAFEVolLoopKi;          // 04 电压环积分系数
    Uint16 caesarAFECurLoopKp;          // 05 电流环比例系数
    Uint16 caesarAFECurLoopKi;          // 06 电流环积分系数
    Uint16 b107;
    Uint16 b108;
    Uint16 caesarAFECurUpperLimit;      // 09 整流器电流上限
    Uint16 b110;
    Uint16 b111;
    Uint16 caesarAFEGenVolCheckPoint;   // 12 整流器母线电压偏差过大检测值
    Uint16 caesarAFEGenVolCheckTime;    // 13 整流器母线电压偏差过大检测时间
    Uint16 b114;
    Uint16 b115;
    Uint16 caesarAFELowInputVol;        // 16 整流最低输入电压
    Uint16 caesarAFEPllKp;              // 17 锁相环比例增益
    Uint16 caesarAFEPllKi;              // 18 锁相环积分增益
    Uint16 caesarAFEActiveCurLimit;     // 19 整流有功电流上限
    Uint16 caesarAFEVFFrqSet;           // 20 VF频率设定
    Uint16 caesarAFEVFVolCoef;          // 21 VF电压比例系数
    Uint16 caesarAFECurLoopFilterTime;  // 22 电流环输出滤波时间
    Uint16 caesarAFE[22]; 
    Uint16 caesarAFECmdSrc;             // 45 命令源选择
    Uint16 caesarAFEInvStartDelay;      // 46 逆变单元启动延时时间
    Uint16 caesarAFEStopDelay;          // 47 回馈单元停机延时时间
    Uint16 caesarAFEb148[2];            // 48 49 保留
#else 
    Uint16 afeControlMode;           // 00 控制模式    
    Uint16 afeGenVoltageSet;         // 01 母线电压设定
    Uint16 afeIocSet;                // 02 软件过流点设定
    Uint16 afeUnpowCurSet;           // 03 无功电流设定
    Uint16 afeCarrierFrq;            // 04 载波频率
    Uint16 afeFrqSet;                // 05 VF 频率设定
    Uint16 afeVfVolScale;            // 06 VF 电压比例系数
    Uint16 afeInVolJudgeCoeff;       // 07 输入电压校正系数
    Uint16 afeVolJudgeCoeff;		 // 08 电压校正系数
    Uint16 afeCurJudgeCoeff;		 // 09 电流校正系数

    Uint16 afeVolLoopKp;             // 10 电压环比例系数
    Uint16 afeVolLoopKi;             // 11 电压环积分系数
    Uint16 afeCurLoopKp;             // 12 电流环比例系数
    Uint16 afeCurLoopKi;             // 13 电流环积分系数
    Uint16 afeMidpointKp;            // 14 中点控制比例系数
    Uint16 afeMidpointKi;            // 15 中点控制积分系数
    Uint16 afePowCurMax;             // 16 整流有功电流上限
    Uint16 afeMidpointOutMax;        // 17 中点控制输出上限
    Uint16 afeMidpointControlMode;   // 18 中点控制方式    
    Uint16 afeLoseInGenAdjust;       // 19 输入欠压设定
    
    Uint16 afeLoseInAdjust;          // 20 输入过压设定
    Uint16 afeUvSoftSet;             // 21 母线欠压软件保护点
    Uint16 afeOvSoftSet;             // 22 母线过压软件保护点
    Uint16 afePllSet;                // 23 锁相环设定
    Uint16 afeModuSet;               // 24 调制方式选择
    Uint16 afeZeroSet;               // 25 零漂处理方式选择
    Uint16 afeInputUnbalanceAdjust;	 // 26 输入不平衡判断阈值
    Uint16 afeAllRunEnable;          // 27 单元端子运行允许
    Uint16 afeRunDelay;              // 28 启动延时
    Uint16 afeStopDelay;             // 29 停车延时
    Uint16 afeMidpointSet;           // 30 afe中点偏差设定
    Uint16 rsvdB1[19];               // 31 -- 49 保留
#endif    
//======================================
// 岸用电源参数组
    Uint16 outVoltageSet;            // B2-00 输出电压设定值
    Uint16 outVolRampSet;            // B2-01 输出电压斜坡设定值
    Uint16 voltageLoopKp;            // B2-02 电压环比例系数
    Uint16 voltageLoopKi;            // B2-03 电压环积分系数
    Uint16 volLoopFilterTime;        // B2-04 电压环滤波时间
    Uint16 frqAbnoProtLimit;         // B2-05 频率异常保护阈值
    Uint16 outUvLimit;               // B2-06 输出欠压保护阈值
    Uint16 rsvdSts;                  // B2-07 保留
    Uint16 outVolCompenstCof;        // B2-08 输出电压补偿系数
    Uint16 reversePowerProtLimit;    // B2-09 逆功率保护阈值设定值
    Uint16 reversePowerLoopKp;       // B2-10 逆功率控制比例增益
    Uint16 reversePowerLoopKi;       // B2-11 逆功率控制积分增益
    Uint16 reversePowerUpperFrq;     // B2-12 逆功率控制上限频率值
    Uint16 transformationRatio;      // B2-13 隔离变压器变比（副边/原边）
    Uint16 parallelNetEbl;           // B2-14 并网使能选择
	Uint16 f0SrcSel;                 // B2-15 f0来源选择
	Uint16 f0SetValue;               // B2-16 f0功能码设定值
	Uint16 frqSlopeSet;              // B2-17 频率下垂斜率设定值
	Uint16 v0SrcSel;                 // B2-18 V0来源选择
	Uint16 v0SetValue;               // B2-19 V0功能码设定值
	Uint16 voltSlopeSet;             // B2-20 电压下垂斜率设定值
	Uint16 prePowerSet;              // B2-21 预设功率设定值
	Uint16 prePowerFactorSet;        // B2-22 预设功率因数设定值   
	Uint16 frqAddLimit;              // B2-23 频率补偿限制
	Uint16 voltAddLimit;             // B2-24 电压补偿限制
	Uint16 phaseSeqSel;              // B2-25 并网相序选择
	Uint16 closeLoopToOpenEbl;       // B2-26 闭环转开环使能
	Uint16 beforeAfterVolChangeEbl;  // B2-27 前后级电压控制切换使能
    Uint16 rsvdB2[2];                // 28 -- 29

    
    Uint16  b3[B3NUM];               // B3

//======================================
    Uint16  b4[B4NUM];               // B4
    Uint16  b5[B5NUM];               // B5
    Uint16  b6[B6NUM];               // B6
    Uint16  b7[B7NUM];               // B7
    
//======================================
    Uint16  b8[B8NUM];               // B8
    Uint16  b9[B9NUM];               // B9
    Uint16  ba[BANUM];               // BA
    Uint16  bb[BBNUM];               // BB

//======================================
    Uint16  bc[BCNUM];               // BC
    Uint16  bd[BDNUM];               // BD
    Uint16  be[BENUM];               // BE
    Uint16  bf[BFNUM];               // BF
    
//======================================

//======================================
#if(0)
//c0 黑匣子参数
    Uint16 sampleDataAddr[8];       // C0-00 07 通道信号源选择
    Uint16 rsvdc000[2];             // C0-08 09
    Uint16 sampleSpaceTime[8];      // C0-10 17 通道信号采样间隔
    Uint16 rsvdc001[4];             // C0-18 21
    Uint16 ramCodeRead[2];          // C0-22 23 通过MAP地址看RAM变量   
    
    Uint16 rsvdC034[31];            // C0-24 54
    Uint16 sysConfirmPara;          // C0-55 系统确认参数
#else
    Uint16 LocalIP[4];              // C0-00 ~ 03
    Uint16 LocalPort;               // C0-04
    Uint16 Gateway[4];              // C0-05 ~ 08
    Uint16 Subnet[4];               // C0-09 ~ 12
    Uint16 Mac[6];                  // C0-13 ~ 18

    Uint16 rsvdc000[3];             // C0-19 ~ 21
    Uint16 ramCodeRead[2];          // C0-22 23 通过MAP地址看RAM变量
    Uint16 rsvdc001[31];            // C0-24 ~ 54
    Uint16 sysConfirmPara;          // C0-55 系统确认参数
#endif

//======================================
    Uint16  c1[C1NUM];               // C1
    Uint16  c2[C2NUM];               // C2
    Uint16  c3[C3NUM];               // C3

//======================================
    Uint16  c4[C4NUM];               // C4
    Uint16  c5[C5NUM];               // C5
    Uint16  c6[C6NUM];               // C6
    Uint16  c7[C7NUM];               // C7

//======================================
    Uint16  c8[C8NUM];               // C8
    Uint16  c9[C9NUM];               // C9
    Uint16  ca[CANUM];               // CA
    Uint16  cb[CBNUM];               // CB

//======================================
    Uint16  cc[CCNUM];               // CC   用户定制功能码组
    Uint16  cd[CDNUM];               // CD

//CE======================================  
    Uint16 vfVolScale;              // 00 VF输出增益
    Uint16 loopPwmTime;             // 01 发波周期数
    Uint16 loopCurMode;             // 02 环流模式
    Uint16 loopIdRef;               // 03 励磁电流
    Uint16 loopCurSet;              // 04 电流给定
    Uint16 ceAO[3];                 // 05 - 07 模拟量输出参数
    Uint16 ce[2];					// CE-08 09
    Uint16 outputSelfDiagnose;		// CE-10 输出侧自检
    Uint16 ce2[4];					// CE-11 14
//CF======================================    
    Uint16  cf[CFNUM];               // CF
//======================================

//======================================
//eepromCheckWord
    Uint16	rsvd4All;			//保留，放在最前面
    Uint16	eepromCheckWord1;	//eepromCheckWord1
    Uint16	eepromCheckWord2;	//eepromCheckWord2
    Uint16	aiaoChkWord;		//AIAO出厂校正

//======================================
//REMEMBER掉电保存，共48个
    Uint16	extendType;				//FR-00extendType
    Uint16	plcStepRem;				//FR-01PLC当前step
    Uint16	plcTimeHighRem;			//FR-02PLC当前step运行的时间，高位
    Uint16	plcTimeLowRem;			//FR-03PLC当前step运行的时间，低位
    Uint16	dispParaRunBit;			//FR-04运行时LED显示参数的bit位值
    Uint16	dispParaStopBit;		//FR-05停机时LED显示参数的bit位置
    Uint16	runTimeAddupSec;		//FR-06累计运行时间的s(秒)
    Uint16	counterTicker;			//FR-07计数器输入的ticker
    Uint16	lengthTickerRemainder;	//FR-08长度计数器的tickerDelta的Remainder
    Uint16	frqComm;				//FR-09通讯修改频率值,100.00%-maxFrq
    Uint16	upDownFrqRem;			//FR-10UP/DOWN的频率
    Uint16	pmsmRotorPos;			//FR-11同步机转子位置
    Uint16	powerAddupInt;			//FR-12累计耗电量辅助计算
    Uint16	powerUpTimeAddupSec;	//FR-13累计上电时间的s(秒)
    Uint16  saveUserParaFlag1;      //FR-14  已保存用户参数标志1
    Uint16  saveUserParaFlag2;      //FR-15  已保存用户参数标志2
    Uint16	commFrq[5];				//FR-16~FR-20 通讯给定频率低位
    Uint16  setComm;                //21 通讯给定
    Uint16	commFrqSub[5];		    //FR-22~FR-26 通讯给定频率高位
    Uint16  fsDetailSerial;         //FR-27
    Uint16	rsvdRem1[15];			//预留 28-42
    Uint16	remPOffMotorCtrl[REM_P_OFF_MOTOR];//FR-43~FR-47性能使用的掉电记忆
//======================================
//======================================
    Uint16 u0[U0NUM];               // U0 显示

// U1
    Uint16	profuctionVersion;      //	U1-00	产品版本
    Uint16	armVersion;			    //	U1-01	ARM版本号
    Uint16	motorSoftVersion;       //	U1-02	DSP版本号
    Uint16	fpgaVersion;		    //	U1-03	FPGA版本号
    Uint16	plcVersion;		        //	U1-04	PLC产品号
    Uint16  hmiVersion;             //  U1-05   HMI产品版本号
    Uint16 u1[U1NUM - 6];           //  U1-06

//======================================	
    Uint16 u2[U2NUM];               // U2
    Uint16 u3[U3NUM];               // U3

//======================================
    Uint16 u4[U4NUM];               // U4
    Uint16 u5[U5NUM];               // U5
    Uint16 u6[U6NUM];               // U6
    Uint16 u7[U7NUM];               // U7

//======================================
    Uint16 u8[U8NUM];               // U8
    Uint16 u9[U9NUM];               // U9
    Uint16 ua[UANUM];               // UA
    Uint16 ub[UBNUM];               // UB

//======================================
    Uint16 uc[UCNUM];               // UC
    Uint16 ud[UDNUM];               // UD
    Uint16 ue[UENUM];               // UE
    Uint16 uf[UFNUM];               // UF, 显示，性能调试使用
//======================================

};


//=====================================================================
//
//功能码的定义。
//联合体，成员分别为数组，结构体，结构体
//于是，一个功能码的访问，有三种方式:
//funcCode.all[index]index=GetCodeIndex(funcCode.code.presetFrq);
//funcCode.group.f0[8]index=GetCodeIndex(funcCode.group.f0[8]);
//funcCode.code.presetFrq
//
//=====================================================================
typedef union FUNCCODE_ALL_UNION
{
    Uint16 all[FNUM_ALL];

    struct FUNCCODE_GROUP group;

    struct FUNCCODE_CODE code;
} FUNCCODE_ALL;

extern FUNCCODE_ALL funcCode;           // 功能码的RAM值


//=====================================================================
//有些功能码的上下限是其它某个功能码，这里是在funcCode中的index

//程序中使用的一些功能码的index
//=如果增加/删除了功能码，这里需要修改!


//请不要随意修改这两个值，否则EEPROM中的值会全部(包括FF组、FP组、各种记录)恢复出厂值。

#if (INV_MODEL == INV_1140)
#define	EEPROM_CHECK_WORD1	(0xA5A5)//EEPROM校验字1
#define	EEPROM_CHECK_WORD2	(0x5A5A)//EEPROM校验字2
#else
#define	EEPROM_CHECK_WORD1	(0x5A5A)//EEPROM校验字1
#define	EEPROM_CHECK_WORD2	(0xA5A5)//EEPROM校验字2
#endif

#define	COMPANY_PASSWORD			1531
#define	SUPER_USER_PASSWORD_1		1031
#define	SUPER_USER_PASSWORD_2		10086
#define	INVERTER_CODE_PASSWORD		5

#define MENU_MODE_MAX       5   // 菜单模式的最大值

#define MENU_INDEX_MAX      5   // 菜单序列的最大值
//=====================================================================
//有些功能码的上下限是其它某个功能码，这里是在funcCode中的index

//程序中使用的一些功能码的index
//=如果增加/删除了功能码，这里需要修改!
#define	FACTORY_PWD_INDEX				(GetCodeIndex(funcCode.code.factoryPassword))       // FF-00 厂家密码
#define	INV_TYPE_INDEX					(GetCodeIndex(funcCode.code.inverterType))          // FF-01 变频器机型
#define	INVERTER_CODE_PROTECT_INDEX    	(GetCodeIndex(funcCode.code.inverterCodeProtect))   // FF-02 参数保护
#define	RATING_POWER_INVERTER_INDEX		(GetCodeIndex(funcCode.code.inverterPower))         // FF-03 变频器功率
#define	FUNCCODE_FACTORY_START_INDEX	(GetCodeIndex(funcCode.group.ff[0]))                // FF组的开始
#define	FUNCCODE_FACTORY_END_INDEX		(GetCodeIndex(funcCode.group.ff[FFNUM-1]))          // FF组的结束
       	
#define	FC_MOTOR1_START_INDEX			(GetCodeIndex(funcCode.code.motorParaM1.motorType))         //第1电机参数的起始
#define	FC_MOTOR1_END_INDEX				(GetCodeIndex(funcCode.code.motorParaM1.inertia))           //第1电机参数的结束
#define	FC_MOTOR2_START_INDEX			(GetCodeIndex(funcCode.code.motorFcM2.motorPara.motorType)) //第2电机参数的起始
#define	FC_MOTOR2_END_INDEX				(GetCodeIndex(funcCode.code.motorFcM2.motorPara.inertia))   //第2电机参数的结束
#define	FC_MOTOR3_START_INDEX			(GetCodeIndex(funcCode.code.motorFcM3.motorPara.motorType)) //第3电机参数的起始
#define	FC_MOTOR3_END_INDEX				(GetCodeIndex(funcCode.code.motorFcM3.motorPara.inertia))   //第3电机参数的结束
#define	FC_MOTOR4_START_INDEX			(GetCodeIndex(funcCode.code.motorFcM4.motorPara.motorType)) //第4电机参数的起始
#define	FC_MOTOR4_END_INDEX				(GetCodeIndex(funcCode.code.motorFcM4.motorPara.inertia))   //第4电机参数的结束


#define	PRESET_FRQ_INDEX		(GetCodeIndex(funcCode.code.presetFrq))                     // F0-08 预置频率
#define	MAX_FRQ_INDEX			(GetCodeIndex(funcCode.code.maxFrq))                        // F0-10 最大频率
#define	UPPER_FRQ_INDEX			(GetCodeIndex(funcCode.code.upperFrq))                      // F0-12 上限频率
#define	LOWER_FRQ_INDEX			(GetCodeIndex(funcCode.code.lowerFrq))                      // F0-14 下限频率
#define	ACC_TIME1_INDEX			(GetCodeIndex(funcCode.code.accTime1))                      // F0-17 加速时间1
#define	DEC_TIME1_INDEX			(GetCodeIndex(funcCode.code.decTime1))                      // F0-18 减速时间1
#define	CARRIER_FRQ_INDEX		(GetCodeIndex(funcCode.code.carrierFrq))                    // F0-15 载波频率
       	
#define	RATING_POWER_INDEX		(GetCodeIndex(funcCode.code.motorParaM1.ratingPower))           // F1-01 电机额定功率
#define	RATING_VOL_INDEX		(GetCodeIndex(funcCode.code.motorParaM1.ratingVoltage))         // F1-02 电机额定电压
#define	RATING_CUR_INDEX		(GetCodeIndex(funcCode.code.motorParaM1.ratingCurrent))         // F1-03 电机额定电流

//#define	RATING_CUR_INDEX2		(GetCodeIndex(funcCode.code.motorFcM2.motorParaF.ratingCurrent)) // A2-03 第2电机额定电流
//#define	RATING_CUR_INDEX3		(GetCodeIndex(funcCode.code.motorFcM3.motorParaF.ratingCurrent)) // A3-03 第3电机额定电流
//#define	RATING_CUR_INDEX4		(GetCodeIndex(funcCode.code.motorFcM4.motorParaF.ratingCurrent)) // A4-03 第4电机额定电流
#define	RATING_FRQ_INDEX        (GetCodeIndex(funcCode.code.motorParaM1.ratingFrq))             // F1-04 电机额定频率
#define	MOTOR2_RATING_FRQ_INDEX (GetCodeIndex(funcCode.code.motorFcM2.motorPara.ratingFrq))     // A2-04 第2电机额定频率
#define	MOTOR3_RATING_FRQ_INDEX (GetCodeIndex(funcCode.code.motorFcM3.motorPara.ratingFrq))     // A3-04 第3电机额定频率
#define	MOTOR4_RATING_FRQ_INDEX (GetCodeIndex(funcCode.code.motorFcM4.motorPara.ratingFrq))     // A4-04 第4电机额定频率
#define	ZERO_LOAD_CURRENT_INDEX (GetCodeIndex(funcCode.code.motorParaM1.zeroLoadCurrent))       //F1-10空载电流
#define	STATOR_RESISTANCE_INDEX (GetCodeIndex(funcCode.code.motorParaM1.statorResistance))      //F1-06定子电阻

#define INV_IOC_SET_POINT_INDEX (GetCodeIndex(funcCode.code.invIOCSetpoint))                    //F9-30 过流点设定
#define INV_IOC_DEBUG_VALUE     200  // 一位小数点 变频器过流点小于等于20.0%时，变频器最大电流上限不受F9-30限制
       	
#define	ANTI_VIBRATE_GAIN_INDEX			(GetCodeIndex(funcCode.code.antiVibrateGain))           // F3-11 振荡抑制增益
#define	ANTI_VIBRATE_GAIN_MOTOR2_INDEX	(GetCodeIndex(funcCode.code.motorFcM2.antiVibrateGain)) // 振荡抑制增益
#define	ANTI_VIBRATE_GAIN_MOTOR3_INDEX	(GetCodeIndex(funcCode.code.motorFcM3.antiVibrateGain)) // 振荡抑制增益
#define	ANTI_VIBRATE_GAIN_MOTOR4_INDEX	(GetCodeIndex(funcCode.code.motorFcM4.antiVibrateGain)) // 振荡抑制增益
       	
#define	TUNE_CMD_INDEX_1			(GetCodeIndex(funcCode.code.tuneCmd))           //调谐
#define	TUNE_CMD_INDEX_2			(GetCodeIndex(funcCode.code.motorFcM2.tuneCmd)) //调谐
#define	TUNE_CMD_INDEX_3			(GetCodeIndex(funcCode.code.motorFcM3.tuneCmd)) //调谐
#define	TUNE_CMD_INDEX_4			(GetCodeIndex(funcCode.code.motorFcM4.tuneCmd)) //调谐
#define	OUTPUT_SELF_DIAGNOSE_INDEX	(GetCodeIndex(funcCode.code.outputSelfDiagnose))	//输出侧自检

#define	TORQUE_BOOST_INDEX			(GetCodeIndex(funcCode.code.torqueBoost))           // F3-01 转矩提升       	
#define	TORQUE_BOOST_MOTOR2_INDEX	(GetCodeIndex(funcCode.code.motorFcM2.torqueBoost)) // 第2电机转矩提升
#define	TORQUE_BOOST_MOTOR3_INDEX	(GetCodeIndex(funcCode.code.motorFcM3.torqueBoost)) // 第3电机转矩提升
#define	TORQUE_BOOST_MOTOR4_INDEX	(GetCodeIndex(funcCode.code.motorFcM4.torqueBoost)) // 第4电机转矩提升
       	

#define	CURVE1_MIN_INDEX		(GetCodeIndex(funcCode.code.curveSet2P1[0]))// A6-00 AI1最小输入
#define	CURVE1_MAX_INDEX		(GetCodeIndex(funcCode.code.curveSet2P1[2]))// A6-02 AI1最大输入
#define	CURVE2_MIN_INDEX		(GetCodeIndex(funcCode.code.curveSet2P2[0]))// A6-05 AI2最小输入
#define	CURVE2_MAX_INDEX		(GetCodeIndex(funcCode.code.curveSet2P2[2]))// A6-07 AI2最大输入
#define	CURVE3_MIN_INDEX		(GetCodeIndex(funcCode.code.curveSet2P3[0]))// A6-10 AI3最小输入
#define	CURVE3_MAX_INDEX		(GetCodeIndex(funcCode.code.curveSet2P3[2]))// A6-13 AI3最大输入

#define	CURVE4_MIN_INDEX		(GetCodeIndex(funcCode.code.curveSet4P1[0]))// A6-14 AI4最小输入
#define	CURVE4_INFLEX1_INDEX	(GetCodeIndex(funcCode.code.curveSet4P1[2]))// A6-16 AI4拐点1输入
#define	CURVE4_INFLEX2_INDEX	(GetCodeIndex(funcCode.code.curveSet4P1[4]))// A6-18 AI4拐点2输入
#define	CURVE4_MAX_INDEX		(GetCodeIndex(funcCode.code.curveSet4P1[6]))// A6-20 AI4最大输入
#define	CURVE5_MIN_INDEX		(GetCodeIndex(funcCode.code.curveSet4P2[0]))// A6-22 AI5最小输入
#define	CURVE5_INFLEX1_INDEX	(GetCodeIndex(funcCode.code.curveSet4P2[2]))// A6-24 AI5拐点1输入
#define	CURVE5_INFLEX2_INDEX	(GetCodeIndex(funcCode.code.curveSet4P2[4]))// A6-26 AI5拐点2输入
#define	CURVE5_MAX_INDEX		(GetCodeIndex(funcCode.code.curveSet4P2[6]))// A6-28 AI5最大输入
       	
       	
#define	ACC_TIME2_INDEX			(GetCodeIndex(funcCode.code.accTime2))      // F8-03加速时间2
#define	DEC_TIME2_INDEX			(GetCodeIndex(funcCode.code.decTime2))      // F8-04减速时间2
#define	ACC_TIME3_INDEX			(GetCodeIndex(funcCode.code.accTime3))      // F8-05加速时间3
#define	DEC_TIME3_INDEX			(GetCodeIndex(funcCode.code.decTime3))      // F8-06减速时间3
#define	ACC_TIME4_INDEX			(GetCodeIndex(funcCode.code.accTime4))      // F8-07加速时间4
#define	DEC_TIME4_INDEX			(GetCodeIndex(funcCode.code.decTime4))      // F8-08减速时间4
       	
#define	RUN_TIME_ADDUP_INDEX	(GetCodeIndex(funcCode.code.runTimeAddup))              // F7-07累计运行时间
#define	POWER_TIME_ADDUP_INDEX	(GetCodeIndex(funcCode.code.powerUpTimeAddup))          // F7-06累计上电时间
#define	POWER_ADDUPL_INDEX		(GetCodeIndex(funcCode.code.powerAddup))                // F7-08累计耗电量千度
#define	POWER_ADDUPH_INDEX		(GetCodeIndex(funcCode.code.powerAddupH))               // F7-23累计耗电量千万度
#define	POWER_UP_TIME_ARRIVE_INDEX	(GetCodeIndex(funcCode.code.powerUpTimeArriveSet))  // F8-16累计运行时间
#define	RUN_TIME_ARRIVE_INDEX	(GetCodeIndex(funcCode.code.runTimeArriveSet))          // F8-17累计运行时间
#define	AI1_LIMIT				(GetCodeIndex(funcCode.code.ai1VoltageLimit))           // A6-46AI保护下限
#define	AI1_UPPER				(GetCodeIndex(funcCode.code.ai1VoltageUpper))           // A6-47AI保护上限
#define	PID_PARA_CHG_DELTA1_MAX	(GetCodeIndex(funcCode.code.pidParaChgDelta2))          // FA-20PID参数切换偏差2
#define	PID_PARA_CHG_DELTA2_MIN	(GetCodeIndex(funcCode.code.pidParaChgDelta1))          // FA-19PID参数切换偏差1
#define	DORMANT_UPPER			(GetCodeIndex(funcCode.code.wakeUpFrq))                 // F8-48休眠频率上限
#define	WAKE_UP_LIMIT			(GetCodeIndex(funcCode.code.dormantFrq))                // F8-50唤醒频率下限
#define	ERROR_LATEST6_INDEX		(GetCodeIndex(funcCode.code.errorLatest6))              // Fb-00第六次故障类型
#define	LAST_ERROR_RECORD_INDEX	(GetCodeIndex(funcCode.code.cellErrorInfo[3]))          // FB-68最后一个故障记录
#define	OTHER_PASSWORD_INFO_INDEX   (GetCodeIndex(funcCode.code.otherPasswordInfo))     // F8-70 密码保护
#define QUICKUP_STOP_DELAY_INDEX    (GetCodeIndex(funcCode.code.quickTransStopDelay))   // F6-32 提前停机时间

#define SAVE_USER_PARA_PARA1    (GetCodeIndex(funcCode.code.saveUserParaFlag1))
#define SAVE_USER_PARA_PARA2    (GetCodeIndex(funcCode.code.saveUserParaFlag2))     
 	
#define	EEPROM_CHECK_INDEX1		(GetCodeIndex(funcCode.code.eepromCheckWord1))  // eepromCheckWord1
#define	EEPROM_CHECK_INDEX2		(GetCodeIndex(funcCode.code.eepromCheckWord2))  // eepromCheckWord2       	                    	
#define	AI_AO_CHK_FLAG			(GetCodeIndex(funcCode.code.aiaoChkWord))       // AIAO校正标志
#define	AI_AO_CALIB_START		(GetCodeIndex(funcCode.code.aiFactoryCalibrateCurve[0].before1))    //aiao厂家校正开始
#define	AI_AO_CALIB_STOP		(GetCodeIndex(funcCode.code.aoFactoryCalibrateCurve[0].after2))     //aiao厂家校正结束       	
#define	AI1_CALB_START			(GetCodeIndex(funcCode.code.aiFactoryCalibrateCurve[0].before1))
#define	AI2_CALB_STOP			(GetCodeIndex(funcCode.code.aiFactoryCalibrateCurve[1].after2))
#define	AO1_CALB_START			(GetCodeIndex(funcCode.code.aoFactoryCalibrateCurve[0].before1))
#define	AO1_CALB_STOP			(GetCodeIndex(funcCode.code.aoFactoryCalibrateCurve[0].after2))
#define	USER_PASSWORD_INDEX		(GetCodeIndex(funcCode.code.userPassword))          //FP-00用户密码

#define	ERROR_ACTION_START_INDEX	(GetCodeIndex(funcCode.code.errorAction[0]))	// F9-47 故障时保护动作选择
#define	ERROR_ACTION_END_INDEX		(GetCodeIndex(funcCode.code.errorAction[4]))	// F9-51 故障时保护动作选择
#define PULSE_IN_MIN_INDEX          (GetCodeIndex(funcCode.code.pulseInMin))		// A6-80 pulse最小输入
#define PULSE_IN_MAX_INDEX          (GetCodeIndex(funcCode.code.pulseInMax))		// A6-82 pulse最大输入

#define	INST_CELL_INDEX	            (GetCodeIndex(funcCode.code.installedCells))	// FF-21 每相单元个数 
#define SWITCH_FRQ_1				(GetCodeIndex(funcCode.code.SpeedLoop.switchFrq1))		// F2-02
#define SWITCH_FRQ_2				(GetCodeIndex(funcCode.code.SpeedLoop.switchFrq2))		// F2-05

#define M2_SWITCH_FRQ_1				(GetCodeIndex(funcCode.code.motorFcM2.SpeedLoop.switchFrq1))	// A2-43
#define M2_SWITCH_FRQ_2				(GetCodeIndex(funcCode.code.motorFcM2.SpeedLoop.switchFrq2))	// A2-46

#define M3_SWITCH_FRQ_1				(GetCodeIndex(funcCode.code.motorFcM3.SpeedLoop.switchFrq1))	// A3-43
#define M3_SWITCH_FRQ_2				(GetCodeIndex(funcCode.code.motorFcM3.SpeedLoop.switchFrq2))	// A3-46

#define M4_SWITCH_FRQ_1				(GetCodeIndex(funcCode.code.motorFcM4.SpeedLoop.switchFrq1))	// A4-43
#define M4_SWITCH_FRQ_2				(GetCodeIndex(funcCode.code.motorFcM4.SpeedLoop.switchFrq2))	// A4-46
//-------------------------------


#define	FC_GROUP_FACTORY	FUNCCODE_GROUP_FF//厂家参数组
#define	FC_GROUP_FC_MANAGE	FUNCCODE_GROUP_FP//功能码管理
#define	FC_START_GROUP		FUNCCODE_GROUP_F0//功能码组显示的第1组
#define USER_MENU_GROUP     FUNCCODE_GROUP_FE

//--------------------------------
//=====================================================================

#define TIME_UNIT_ACC_DEC_SPEED         100  // 加减速时间单位, ms

#if	defined	(FUNC_DEBUG_RAM)
#define	ACC_DEC_T_INIT1	((Uint32)2*TIME_UNIT_MS_PER_SEC/TIME_UNIT_ACC_DEC_SPEED)//加减速时间出厂值，2s，机型<=20
#define	ACC_DEC_T_INIT2	((Uint32)5*TIME_UNIT_MS_PER_SEC/TIME_UNIT_ACC_DEC_SPEED)//5s，机型>20
#else                  	
#define	ACC_DEC_T_INIT1	((Uint32)20*TIME_UNIT_MS_PER_SEC/TIME_UNIT_ACC_DEC_SPEED)//加减速时间出厂值，20s，机型<=20
#define	ACC_DEC_T_INIT2	((Uint32)50*TIME_UNIT_MS_PER_SEC/TIME_UNIT_ACC_DEC_SPEED)//50s，机型>20
#endif

#define	PRESET_FRQ			5000//预置频率
#define	RATING_FRQ_INIT		5000//电机额定频率
#define	INVERTER_TYPE_MAX	34



//功能码的时间单位
//注意，程序中为了减小不必要的计算和空间占用，部分使用了
//X*(TIME_UNIT_WAIT_STOP_BRAKE/RUN_CTRL_PERIOD)的方式
//而不是，(X*TIME_UNIT_WAIT_STOP_BRAKE)/RUN_CTRL_PERIOD
//之后修改这些时间单位，可能有必要修改。
#define	TIME_UNIT_SEC_PER_HOUR			3600        // 1hour=3600sec
#define	TIME_UNIT_MIN_PER_HOUR			60          // 1hour=60min
#define TIME_UNIT_SEC_PER_MIN           60          // 1min  = 60sec
#define	TIME_UNIT_MS_PER_SEC			1000        // 1s=1000ms
#define	TIME_UNIT_MS_PER_MIN			60000       // 1min=60000ms
#define TIME_UNIT_MS_PER_HOUR           3600000     // 每小时3600000ms


#define TIME_UNIT_VF_VOL_ACC_TIME       100  // VF分离的电压上升时间

#define	TIME_UNIT_AI_PULSE_IN_FILTER	10      //AI,pulseIn滤波时间,ms
#define	TIME_UNIT_START_FRQ_WAIT		100     //启动频率保持时间，ms
#define	TIME_UNIT_START_BRAKE			100     //启动直流制动时间，ms
#define	TIME_UNIT_WAIT_STOP_BRAKE		100     //停机直流制动等待时间，ms
#define	TIME_UNIT_STOP_BRAKE			100     //停机直流制动时间，ms
#define	TIME_UNIT_ZERO_SPEED_DEAD		100     //正反转死区时间
#define	TIME_UNIT_LOWER_STOP_DELAY		100     //频率低于下限频率时停机的延迟时间
#define	TIME_UNIT_SOFT_OC_DELAY			10      //软件过流点检测延迟时间
#define	TIME_UNIT_ZERO_CURRENT_DELAY	10      //软件过流点检测延迟时间
//#define	TIME_UNIT_PID_SET_CHANGE		100//PID给定变化时间
#define	TIME_UNIT_SWING_PERIOD			10      //摆频周期
#define	TIME_UNIT_sciCommOverTime		100     //通信超时时间
#define	TIME_UNIT_ERR_AUTO_RST_DELAY	100     //故障自动复位间隔时间，ms
#define	TIME_UNIT_ERR_AUTO_RST_CLR	(TIME_UNIT_SEC_PER_HOUR*100UL)//故障自动复位次数清除时间,0.1h
#define	TIME_UNIT_P_OFF_VOL_BACK		10      //瞬停不停电压回升判断时间
#define	TIME_UNIT_PLC					100     //PLC运行时间单位
#define	TIME_UNIT_WAKE_UP				100     //唤醒时间的单位
#define	TIME_UNIT_DORMANT				100     //休眠时间的单位
#define	TIME_UNIT_EXT_BRAKE_TIME		100     //外部报闸时间

#define TIME_UNIT_PID_SET_CHANGE        10      // PID给定变化时间
#define TIME_UNIT_PID_FILTER            10      // PID反馈，输出滤波时间
#define TIME_UNIT_PID_INIT              10      // PID初值保持时间
#define TIME_UNIT_PID_FDB_LOSE          100     // PID反馈丢失检测时间

//程序中一些模块的调用周期
#define	FUNC_DEAL_PERIOD		2       //功能程序处理周期，_ms
#define	RUN_CTRL_PERIOD			2       //命令源程序RunControl()处理周期，_ms
//#defi	neCOMM_DEAL_PERIOD2//通讯处理的周期
#define	ERROR_DEAL_PERIOD		2       //故障处理errorDeal()处理周期，_ms
#define	FRQ_SRC_PERIOD			2       //频率源程序frqSrc()处理周期，_ms
#define	PULSE_IN_CALC_PERIOD	2       //脉冲输入的计算周期
#define	AI_CALC_PERIOD			2       //AI的计算周期
#define	DI_CALC_PERIOD			2       //DI的计算周期
#define	DO_CALC_PERIOD			2       //DO的计算周期
#define	PID_CALC_PERIOD			2       //PID的计算周期
#define TIME_UNIT_CURRENT_CHK   10      // 电流检测时间单位
#define CORE_FUNC_PERIOD        2       // 性能到功能数据更新周期
#define RUN_TIME_CAL_PERIOD     2       // 运行时间统计周期
#define VF_CALC_PERIOD          2       // VF分离的计算周期

//=====================================================================
// STOP/RES键功能
#define FUNCCODE_stopKeyFunc_KEYBOARD   0   // 停机功能仅在键盘控制方式时有效
#define FUNCCODE_stopKeyFunc_ALL        1   // 均有效

//(电机)控制方式
#define	FUNCCODE_motorCtrlMode_SVC		0   // 无速度传感器矢量控制，SVC1 异步机
#define	FUNCCODE_motorCtrlMode_VC		1   // 有速度传感器矢量控制，异步机
#define	FUNCCODE_motorCtrlMode_SVC2		2   // 电压型开环矢量，SVC2，异步机
#define FUNCCODE_motorCtrlMode_VF       3   // 标准(纯粹的)VF，一般调试使用
#define FUNCCODE_motorCtrlMode_SinOnly  4   // 仅发送正弦波，FPGA发PWM，调试使用
#define FUNCCODE_motorCtrlMode_OLTM     5   // (开环)测试模式
#define FUNCCODE_motorCtrlMode_SM_SVC   6   // 无速度传感器矢量控制，励磁同步机
#define FUNCCODE_motorCtrlMode_SM_FVC   7   // 有速度传感器矢量控制，励磁同步机
#define FUNCCODE_motorCtrlMode_SMDC_SVC 8   // 无速度传感器矢量控制，直流无刷励磁同步机
#define FUNCCODE_motorCtrlMode_PMSM_SVC 9   // 永磁同步机SVC
#define FUNCCODE_motorCtrlMode_PMSM_FVC 10  // 永磁同步机FVC

//命令源选择    	
#define	FUNCCODE_runSrc_PANEL			0   //操作面板控制通道
#define	FUNCCODE_runSrc_DI				1   //端子命令通道
#define	FUNCCODE_runSrc_RS485           2   //串行口通信控制通道
#define	FUNCCODE_runSrc_PROFIBUS        3   //串行口通信控制通道
#define	FUNCCODE_runSrc_HMI				4   //串行口通信控制通道
#define	FUNCCODE_runSrc_PC				5   //串行口通信控制通道
#define	FUNCCODE_runSrc_CANLINK         6   //can通信控制通道
                                    	
//运行方向                          	
#define	FUNCCODE_runDir_NO_REVERSE		0   //方向一致
#define	FUNCCODE_runDir_REVERSE			1   //方向相反
                                    	
//V/F曲线设定                       	
#define	FUNCCODE_vfCurve_line			0   //直线V/F曲线
#define	FUNCCODE_vfCurve_multiPoint		1   //多点V/F曲线
#define	FUNCCODE_vfCurve_squre			2   //平方V/F曲线

//调谐选择
#define	FUNCCODE_tuneCmd_NONE			0   //无操作
#define	FUNCCODE_tuneCmd_STATIC_TUNE	1   //静止调谐
#define	FUNCCODE_tuneCmd_WHOLE_TUNE		2   //完整调谐
#define FUNCCODE_tuneCmd_PMSM_11        11  // 同步机
#define FUNCCODE_tuneCmd_PMSM_12        12  // 同步机
#define FUNCCODE_tuneCmd_PMSM_13        13  // 同步机

// 数值设定频率记忆设定
#define FUNCCODE_frqRemMode_POWEROFF_NO     0   // 掉电不记忆
#define FUNCCODE_frqRemMode_POWEROFF_YES    1   // 掉电记忆
#define FUNCCODE_frqRemMode_STOP_NO         0   // 停机不记忆
#define FUNCCODE_frqRemMode_STOP_YES        1   // 停机记忆

//端子命令方式
#define	FUNCCODE_diControlMode_2LINE1	0   //两线式1
#define	FUNCCODE_diControlMode_2LINE2	1   //两线式2
#define	FUNCCODE_diControlMode_3LINE1	2   //三线式1
#define	FUNCCODE_diControlMode_3LINE2	3   //三线式2

// 主辅频率源选择
#define FUNCCODE_frqXySrc_FC                0   // 功能码设定，掉电不记忆
#define FUNCCODE_frqXySrc_FC_P_OFF_REM      1   // 功能码设定，掉电记忆
#define FUNCCODE_frqXySrc_AI1               2   // AI1
#define FUNCCODE_frqXySrc_AI2               3   // AI2
#define FUNCCODE_frqXySrc_AI3               4   // AI3
#define FUNCCODE_frqXySrc_AI4               5   // AI4
#define FUNCCODE_frqXySrc_PULSE             6   // PULSE脉冲设定(DI5)
#define FUNCCODE_frqXySrc_MULTI_SET         7   // 多段指令
#define FUNCCODE_frqXySrc_PLC               8   // PLC
#define FUNCCODE_frqXySrc_PID               9   // PID
//#define FUNCCODE_frqXySrc_COMM              9   // 通讯设定
#define FUNCCODE_frqXySrc_PC                10   // 通讯设定
#define FUNCCODE_frqXySrc_RS485             11   // 通讯设定
#define FUNCCODE_frqXySrc_PROFIBUS          12   // 通讯设定
#define FUNCCODE_frqXySrc_HMI               13   // 通讯设定
#define FUNCCODE_frqXySrc_CAN               14   // 通讯设定

// 辅助频率源Y范围选择
#define FUNCCODE_frqYRangeBase_MAX_FRQ      0   // 相对于最大频率
#define FUNCCODE_frqYRangeBase_FRQ_X        1   // 相对于主频率源X

// 频率源(切换关系)选择
#define FUNCCODE_frqCalcSrc_X               0   // 主频率源X
#define FUNCCODE_frqCalcSrc_COMPOSE         1   // 主辅运算结果
#define FUNCCODE_frqCalcSrc_X_OR_Y          2   // 主 <--> 辅
#define FUNCCODE_frqCalcSrc_X_OR_COMPOSE    3   // 主 <--> 主辅运算结果
#define FUNCCODE_frqCalcSrc_Y_OR_COMPOSE    4   // 辅 <--> 主辅运算结果

// 主辅频率运算关系
#define FUNCCODE_frqCalcSrc_ADD             0   // 主 + 辅
#define FUNCCODE_frqCalcSrc_SUBTRATION      1   // 主 - 辅
#define FUNCCODE_frqCalcSrc_MAX             2   // MAX(主, 辅)
#define FUNCCODE_frqCalcSrc_MIN             3   // MIN(主, 辅)
#define FUNCCODE_frqCalcSrc_4               4   // 
#define FUNCCODE_frqCalcSrc_5               5   // 

// 上限频率源
#define FUNCCODE_upperFrqSrc_FC         0   // 功能码设定
#define FUNCCODE_upperFrqSrc_AI1        1   // AI1
#define FUNCCODE_upperFrqSrc_AI2        2   // AI2
#define FUNCCODE_upperFrqSrc_AI3        3   // AI3
#define FUNCCODE_upperFrqSrc_PULSE      4   // PULSE脉冲设定(DI5)
#define FUNCCODE_upperFrqSrc_COMM       5   // 通讯给定
#define FUNCCODE_upperFrqSrc_AI4        6   // AI4

// 启动方式
#define FUNCCODE_startMode_DIRECT_START             0   // 直接启动
#define FUNCCODE_startMode_SPINNING_LOAD_FORWARD    1   // 正向飞车启动
#define FUNCCODE_startMode_SPINNING_LOAD_BACKWARD   2   // 反向飞车启动
#define FUNCCODE_startMode_SPINNING_LOAD            3   // 正反向飞车启动

//停机方式
#define	FUNCCODE_stopMode_DEC_STOP		0   //减速停机
#define	FUNCCODE_stopMode_FREESTOP		1   //自由停机

//频率低于下限频率运行动作
#define	FUNCCODE_lowerDeal_RUN_LOWER	0   //以下限频率运行
#define	FUNCCODE_lowerDeal_DELAY_STOP	1   //延时停机
#define	FUNCCODE_lowerDeal_RUN_ZERO	    2	//零速运行

//设定运行时间到达动作选择
#define	FUNCCODE_runTimeOverAct_RUN		0   //继续运行
#define	FUNCCODE_runTimeOverAct_STOP	1   //停机

// 设定上电时间到达动作选择
#define FUNCCODE_powerUpTimeOverAct_RUN     0   // 继续运行
#define FUNCCODE_powerUpTimeOverAct_STOP    1   // 停机

// 多段指令0给定方式
#define FUNCCODE_plcFrq0Src_FC          0   // 功能码FC-00给定
#define FUNCCODE_plcFrq0Src_AI1         1   // AI1
#define FUNCCODE_plcFrq0Src_AI2         2   // AI2
#define FUNCCODE_plcFrq0Src_AI3         3   // AI3
#define FUNCCODE_plcFrq0Src_PULSE       4   // PULSE
#define FUNCCODE_plcFrq0Src_PID         5   // PID给定
#define FUNCCODE_plcFrq0Src_PRESET_FRQ  6   // 预置频率
#define FUNCCODE_plcFrq0Src_AI4         7   // AI4

// PLC运行方式
#define FUNCCODE_plcRunMode_ONCE_STOP   0   // 单次运行结束停机
#define FUNCCODE_plcRunMode_ONCE_RUN    1   // 单次运行结束保持终值
#define FUNCCODE_plcRunMode_REPEAT      2   // 一直循环

// PLC掉电记忆选择
#define FUNCCODE_plcPowerOffRemMode_NO_REM  0   // 掉电不记忆
#define FUNCCODE_plcPowerOffRemMode_REM     1   // 掉电记忆
// PLC停机记忆选择
#define FUNCCODE_plcStopRemMode_NO_REM  0   // 掉电不记忆
#define FUNCCODE_plcStopRemMode_REM     1   // 掉电记忆
// PLC运行时间单位
#define FUNCCODE_plcTimeUnit_S      0   // S(秒)
#define FUNCCODE_plcTimeUnit_H      1   // H(小时)

// MF.K键功能选择
#define FUNCCODE_mfkKeyFunc_NONE        0   // MF.K键功能无效
#define FUNCCODE_mfkKeyFunc_SWITCH		1   // 与操作面板通道切换
#define FUNCCODE_mfkKeyFunc_REVERSE		2   // 正反转切换
#define FUNCCODE_mfkKeyFunc_FWD_JOG		3   // 正转点动命令
#define FUNCCODE_mfkKeyFunc_REV_JOG		4   // 反转点动命令
#define FUNCCODE_mfkKeyFunc_CLOSEPWM	5   // 自由停车

// 故障时继续运行频率选择
#define ERR_RUN_FRQ_RUN		0  // 以当前运行频率运行
#define ERR_RUN_FRQ_AIM		1  // 以设定频率运行
#define ERR_RUN_FRQ_UPPER	2  // 以上限频率运行
#define ERR_RUN_FRQ_LOWER	3  // 以下限频率运行
#define ERR_RUN_FRQ_SECOND	4  // 以异常时备用频率运行

// PID给定源
#define FUNCCODE_pidSetSrc_FC               0   // 功能码设定
#define FUNCCODE_pidSetSrc_AI1              1   // AI1
#define FUNCCODE_pidSetSrc_AI2              2   // AI2
#define FUNCCODE_pidSetSrc_AI3              3   // AI3
#define FUNCCODE_pidSetSrc_PULSE            4   // PULSE
#define FUNCCODE_pidSetSrc_COMM             5   // 通讯
#define FUNCCODE_pidSetSrc_MULTI_SET        6   // 多段指令
#define FUNCCODE_pidSetSrc_AI4              7   // AI4

// PID反馈源
#define FUNCCODE_pidFdbSrc_AI1              0   // AI1
#define FUNCCODE_pidFdbSrc_AI2              1   // AI2
#define FUNCCODE_pidFdbSrc_AI3              2   // AI3
#define FUNCCODE_pidFdbSrc_AI1_SUB_AI2      3   // AI1-AI2
#define FUNCCODE_pidFdbSrc_PULSE            4   // PULSE
#define FUNCCODE_pidFdbSrc_COMM             5   // 通讯
#define FUNCCODE_pidFdbSrc_AI1_ADD_AI2      6   // AI1+AI2
#define FUNCCODE_pidFdbSrc_MAX_AI           7   // MAX(|AI1|, |AI2|)
#define FUNCCODE_pidFdbSrc_MIN_AI           8   // MIN(|AI1|, |AI2|)
#define FUNCCODE_pidFdbSrc_AI4              9   // AI4
// PID参数切换条件
#define FUNCCODE_pidParaChgCondition_NO         0   // 不切换
#define FUNCCODE_pidParaChgCondition_DI         1   // DI端子
#define FUNCCODE_pidParaChgCondition_PID_ERROR  2   // 根据偏差自动切换

// PID运算模式
#define FUNCCODE_pidCalcMode_NO             0   // 停机时不运算
#define FUNCCODE_pidCalcMode_YES            1   // 停机时运算

// 转矩上限源
#define FUNCCODE_upperTorqueSrc_FC      0   // 功能码设定
#define FUNCCODE_upperTorqueSrc_AI1     1   // AI1
#define FUNCCODE_upperTorqueSrc_AI2     2   // AI2
#define FUNCCODE_upperTorqueSrc_AI3     3   // AI3
#define FUNCCODE_upperTorqueSrc_PULSE   4   // PULSE
#define FUNCCODE_upperTorqueSrc_COMM    5   // 通讯
#define FUNCCODE_upperTorqueSrc_MIN_AI1_AI2 6  // min(ai1,ai2)
#define FUNCCODE_upperTorqueSrc_MAX_AI1_AI2 7  // max(ai1,ai2)
#define FUNCCODE_upperTorqueSrc_AI4     8   // AI4
#define FUNCCODE_upperTorqueSrc_CAN     9   // CAN

// PULSE最大输入对应设定方式
#define FUNCCODE_pulseInSetMaxMode_0      0   // F2-24
#define FUNCCODE_pulseInSetMaxMode_AI1    1   // AI1
#define FUNCCODE_pulseInSetMaxMode_AI2    2   // AI2


// VF曲线设定
#define FUNCCODE_vfCurve_Line               0   // 直线VF
#define FUNCCODE_vfCurve_DOT                1   // 多点VF
#define FUNCCODE_vfCurve_SQUARE             2   // 平方VF
#define FUNCCODE_vfCurve_ALL_SEPARATE       10  // VF完全分离模式
#define FUNCCODE_vfCurve_HALF_SEPARATE      11  // VF半分离模式
// vfVoltageSrc, VF分离的电压源
#define FUNCCODE_vfVoltageSrc_FC            0   // 功能码设定
#define FUNCCODE_vfVoltageSrc_AI1           1   // AI1
#define FUNCCODE_vfVoltageSrc_AI2           2   // AI2
#define FUNCCODE_vfVoltageSrc_AI3           3   // AI3
#define FUNCCODE_vfVoltageSrc_PULSE         4   // PULSE脉冲设定(DI5)
#define FUNCCODE_vfVoltageSrc_MULTI_SET     5   // 多段指令
#define FUNCCODE_vfVoltageSrc_PLC           6   // PLC
#define FUNCCODE_vfVoltageSrc_PID           7   // PID
#define FUNCCODE_vfVoltageSrc_COMM          8   // 通讯设定
#define FUNCCODE_vfVoltageSrc_AI4           9   // AI4
// 多功能端子输出选择
#define FUNCCODE_fmOutSelect_PULSE      1   // FMP脉冲输出
#define FUNCCODE_fmOutSelect_DO         0   // DO

// 加减速时间的单位
#define FUNCCODE_accDecTimeUnit_0POINT  0   // 0个小数点，1s
#define FUNCCODE_accDecTimeUnit_1POINT  1   // 1个小数点，0.1s
#define FUNCCODE_accDecTimeUnit_2POINT  2   // 2个小数点，0.01s

//键盘
#define KEYBOARD_TYPE_NORMAL            0   // 普通键盘
#define KEYBOARD_TYPE_LED               1   // 液晶键盘

//控制方式
#define CONTROL_MODE_LOCAL      0   // 本地
#define CONTROL_MODE_REMOTE1    1   // 远程1
#define CONTROL_MODE_REMOTE2    2   // 远程2

//旁路柜
#define NO_BYPASS_CABINET       0   // 无旁路柜
#define MANUAL_BYPASS_CABINET   1   // 手动旁路柜
#define AUTO_BYPASS_CABINET     2   // 自动旁路柜

//单元旁路选择 1~9 保留给有旁路属性的单元，10~19给无需旁路属性的单元
#define CELL_BYPASS_DISABLE     0x0   // 无旁路
#define CELL_BYPASS_MANUAL      0x1   // 手动旁路
#define CELL_BYPASS_AUTO        0x2   // 自动旁路
#define CELL_BYPASS_HANDWORK	0xA   // 手工旁路
//#define CELL_BYPASS_IGBT        0xB   // 电子旁路

// 单元属性
#define HD9X_CELL               0   // FF-22 单元属性: HD9X
#define HD9X_R_CELL             1   // FF-22 单元属性: HD9X-R 四象限回馈
#define SUPER_CELL              2   // FF-22 单元属性: 榴莲
#define HD9X_CELL_II            3   // FF-22 单元属性: II代机102A以下

// 单元旁路属性
#define CELL_BYPASS_A_DISABLE   0   // FF-22 单元属性: 不带旁路
#define CELL_BYPASS_A_ENABLE    1   // FF-22 单元属性: 带旁路

// 输出侧自检
#define OUTPUT_SELF_DIAGNOSE_NO_MOTOR	100		// 不带电机
#define OUTPUT_SELF_DIAGNOSE_WITH_MOTOR	1000	// 带电机

// 速度反馈PG卡选择
#define NATIVE_PG_CARD  0   // 0 - IO板自带PG卡
#define EXP_PG_CARD     1   // 1 - 扩展PG卡

#define ERR_AUTO_RST_MAX_NUM (funcCode.code.errAutoRstNumMax + 1)

#define HD90S_CARRIERFRQ_MAX    6000



#endif







