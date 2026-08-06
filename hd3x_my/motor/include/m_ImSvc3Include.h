/***************************************************************
文件功能：开环矢量控制
文件版本：VERSION 1.0
最新更新：2009.09.27
************************************************************/
#ifndef MOTOR_SVC_INCLUDE_H
#define MOTOR_SVC_INCLUDE_H

#ifdef __cplusplus
extern "C" {
#endif

//#include "MotorInclude.h"
#include "m_main.h"

/************************************************************
	工程使用的新定义变量类型
************************************************************/
typedef	long long 				llong;
typedef	unsigned int			Uint;
typedef	unsigned long			Ulong;
typedef	unsigned long long 		Ullong;

/************************************************************/


//取绝对值的函数(适用所有数据类型)
//#define abs(x)  	((x>0)?(x):-(x))
//取大值函数(适用所有数据类型)
#define Max(x,y)	((x>y)?(x):(y))
//取小值函数(适用所有数据类型)
#define Min(x,y)	((x<y)?(x):(y))

/***********************结构体定义***************************/
typedef struct SVC_FLUX_CAL_STRUCT_DEF {
	long 	FilterTime;
	Uint 	SampleTime;
	int		LrDivLm;    //Q14 
	int		LLeak;      //Q14
    int     LmDivLr;    //Q14
    int     LmFreq;     //Q9
}SVC_FLUX_CAL_STRUCT;	//计算磁通用的变量集合

typedef struct FLUX_STRUCT_DEF {
	Uint	Amp;
	Uint	Theta;
}FLUX_STRUCT;	//磁通观测结果用的变量集合

//加的定义结构体
typedef struct MT_STRUCT_DEF{
	int  	M;      // Q12
	int  	T;
}MT_STRUCT;	//MT轴系下的电流、电压结构

typedef struct MT_STRUCT_Q24_DEF{
    long    M;
    long    T;
}MT_STRUCT_Q24;

typedef struct ROTOR_SPEED_STRUCT_DEF {
	int 	SpeedApply;			//实际使用转子速度
	int 	SpeedEncoder;		// 通过编码器检测到的转子频率, 传动比折算后
	long     SpeedTemp;          // 折算前编码器测速值
	long    SpeedEncoderQ24;  // 通过编码器检测到的转子频率, 传动比折算后Q24
	
	//SVC测速变量
	int		SvcSynSpeed;
	int		SvcWs;
	int		SvcRotorSpeed;
    
    Uint    TransRatio;         //电机测速传动比
	Uint	FirstCnt;
	Uint    StartCnt;
	Uint    RunCnt;
	Uint    SVCSpeedStaDetFlag; //SVC速度失速检测标志
	

    // chzq18110
	long    SpeedFeed;              //速度检测值  Q24格式
    Uint    PulseNum;               //测速用的编码器线速
    Ulong   Pos;                    //当前位置
    Ulong   Time;                   //当前时间
    int     DetaPos;                //位置偏差
    Ulong   DetaTime;               //时间偏差
    Ulong   DetaTimeAdd;            //第一次捕捉到脉冲需要增加的时间
    Uint    CapTimeLast;            //用于记录上次读取位置时的捕获值
    Uint    PrescaFlag;
    Uint    ChangeFlag;    
    Uint    FreThreshold;             //测速执行次数计数

    Uint    SpeedLoopRunTimes;     //用于SVC2速度环执行时间

	int     FreWindow;            //主从控制时视窗频率

}ROTOR_SPEED_STRUCT;	//速度反馈部分数据结构

typedef struct ALPHABETA_STRUCT_DEF{
	long  	Alph;
	long  	Beta;
}ALPHABETA_STRUCT;//定子两相坐标轴电流、电压结构
/*
// // 以下为和电机控制相关设定参数定义数据结构 
typedef struct BASE_PAR_STRUCT_DEF {
	Ulong 	FullFreq01;				                    // Full freq, SI, 0.01Hz;
	Uint    FullFreq;                                   // SI, 小数点与功能基值一致，用于将功能传递的实际值转换为标么值
	Uint 	MaxFreq;				                    //最大频率 format: point
	Uint 	FcSet;					                    //设定载波频率		
	Uint 	FcSetApply;				                    //实际载波频率	
	Uint    VcDoubleCtrlFlag;						//	中断中两次控制标志
}BASE_PAR_STRUCT;	                                //基本运行信息结构

typedef struct BASE_COMMAND_STRUCT_DEF {
	//union MAIN_COMMAND_UNION_DEF Command;	            //主命令字结构
	int 	FreqSet;				                    // 功能传递的设定频率
	int     FreqSet0;
	int     FreqSetApply;                               // 驱动实际使用的设定频率
	//int		FreqSetBak;				                    //最新的非0给定速度
	int 	FreqSyn;			                        //实际速度（同步速度）
    int     FreqSynFilter;                              //实际输出同步频率的滤波值，用于弱磁区计算
	int     FreqWs;                                   // 矢量时计算的转差12
	long    FreqWsQ24;									//矢量时计算的转差Q24
	int 	FreqDesired;			                    //目标速度
	int     FreqToFunc;                                 //反馈给功能模块的速度，标么值表示
	                                                    // 现在反馈速度分为变频器运行频率和编码器测速                                                        
    int     FreqFeed;
	long 	FreqReal;				                    // 实际设定频率(非标么值表示),单位0.01Hz
	Uint    RotorFreqReal;                            // 转子频率,单位0.01Hz	
                                                        	// 功能传递的频率值转换为0.01Hz时的系数
    long    FreqRealFilt;
                                                        
	Uint    pu2siCoeff;                          //标么值频率基值单位与程序中使用的实际频率单位不同，存在一个转换系数
	                                                    // 1Hz 转化为功能小数点的系数              
	Uint    si2puCoeff;                          //程序中的实际频率转换为标么值频率，需要的校正系数。    

	long 	FreqSetStep;            //设定频率每载波周期变化步长,Q23
	long 	PosSet;                 //设定频率的积分(设定电角度),Q24
    //Uint	SpeedFalg;				//加减速标志
}BASE_COMMAND_STRUCT;  
*/


typedef struct ANGLE_STRUCT_DEF {
	long 	StepPhase;			//步长角度（计算出来）
	long 	StepPhaseApply;		//步长角度（实际使用）
	long 	IMPhase; 			//M轴角度			
	int 	OutPhase; 			//PWM角度
	int  	CompPhase;			//相位延迟补偿角度
	int		SinIM;				//M轴的正弦值
	int		CosIM;				//M轴的余弦值
}ANGLE_STRUCT;

// // 驱动部分调试用数据结构
typedef struct MOTOR_DEBUG_DATA_RECEIVE_STRUCT_DEF{
    int     TestData0;
    int     TestData1;
    int     TestData2;
    int     TestData3;
    int     TestData4;
    int     TestData5;
    int     TestData6;
    int     TestData7;
    int     TestData8;
    int     TestData9;
    int     TestData10;
    int     TestData11;
    int     TestData12;
    int     TestData13;
    int     TestData14;
    int     TestData15;
    int     TestData16;
    int     TestData17;
    int     TestData18;
    int     TestData19;   
    int     TestData20;
    int     TestData21;
    int     TestData22;
    int     TestData23;
    int     TestData24;
    int     TestData25;
    int     TestData26;
    int     TestData27;
    int     TestData28;
    int     TestData29;
}MOTOR_DEBUG_DATA_RECEIVE_STRUCT;   //性能调试数据接收

typedef struct AMPTHETA_STRUCT_DEF{
	Uint  	Amp;				//Q12
	int  	Theta;				//Q15
	int     ThetaFilter;        //Q15 ----DBcomp
	int     PowerAngle;         // 功率因素角
}AMPTHETA_STRUCT;//极坐标表示的电流、电压结构

typedef struct UVW_STRUCT_DEF_Q24{					
	long  	U;					//Q24格式，以电机额定值为标么值基值
	long  	V;
	long  	W;
}UVW_STRUCT_Q24;	//定子三相坐标轴电流

/************************************************************
	结构定义
************************************************************/
typedef struct PID_STRUCT_DEF {
	long 	Total;			//积分累加值
	long 	Out;			//输出值
	int  	Max;			//最大值限制
	int  	Min;			//最小值限制
	int  	Deta;			//偏差值
	int  	KP;				//KP增益
	int  	KI;				//KI增益
	int  	KD;				//KD增益

    Uint    QP;             // KP的放大倍数 KP = KP << QP
    Uint    QI;             // KI的放大倍数
    Uint    QD;             // KD的放大倍数
}PID_STRUCT;//PID计算用的数据结构(无量纲数据结构)

typedef struct VC_INFO_STRUCT_DEF {
	Uint 	ASRKpLow;				//低频速度环KP
	Uint 	ASRTILow;				//低频速度环TI
	Uint 	ASRKpHigh;				//高频速度环KP
	Uint 	ASRTIHigh;				//高频速度环TI
	Uint 	ASRSwitchLow;			//低频切换频率
	Uint 	ASRSwitchHigh;			//高频切换频率

    Uint    AcrImKp;        // 同步机和异步机电流环参数
    Uint    AcrImKi;        // M 轴电流环积分
    Uint    AcrItKp;        // T轴电流环增益
    Uint    AcrItKi;        // T轴电流环积分
    Uint    EstImKp;        // 辨识后的M 轴电流环比例
    Uint    EstImKi;        // 辨识后的M 轴电流环积分
    Uint    EstItKp;        // 辨识后的T轴电流环比例
    Uint    EstItKi;        // 辨识后的T轴电流环积分
    Uint    SvcMode;
    
    Uint    VcOverExcGain;              //矢量过励磁增益  
	Uint    VcOverExcMode;   //矢量过励磁模式
	Uint    VcOverExcRatio;    //矢量模式下过励磁输出系数
	
	Uint 	TorqueLimit;	   //VC正向转矩设定F2-10
	Uint 	VCWsCoff;		  //VC转差补偿
	Uint 	VCWsCoffGet;	  //VC转差补偿
	Uint    VCSpeedFilter;	 //VC速度环滤波时间
	Uint 	VCTorqFilter;		//SVC转矩滤波系数	
	int     TorMasToFol;        //主机传送给从机的转矩
	long    AsrOut;                //速度环转矩输出
	int      MaxTorqueCoff;  //F2-21,弱磁自动调整增益，主要影响深度弱磁最大力矩

	Uint 	SVCTorqueUp;			// SVC转矩提升增益
	Uint 	SVCTorqueUpLim;		// SVC转矩提升截至频率
	Uint     OppTorqueLimEnable;  //反向转矩使能选择，默认不使能，由F2-22选择
}VC_INFO_STRUCT;	//和矢量控制相关的参数设置数据结构

typedef struct IM_FLUX_DATA_DEF
{
	long     VoltOut;
    long     VoltOutTotal;
    long     VoltOutPI;
	long     VoltOutLpf;
	long     SynFreqPer;
	int     FluxWeakFlag;
	int     FluxWeakNum;
	int     PhaseOut;
    int     OverModule;
	long     PhaseTotal;
	long     Kp;
	long     Ki;
    int      OutFlag;
	long     WsSetQ;
	long     ImLpf;
	int		ImLpfQ12;
	int		VoltAmpLpf;
}IM_FLUX_DATA;



/************************************************************/
/*******************供外部引用变量声明***********************/
extern MT_STRUCT                gABVoltSet;	    	//αβ坐标轴下定子实际输出电压
                                                    
//extern ALPHABETA_STRUCT		    gABFluxS;		//αβ坐标轴下定子磁通
//extern ALPHABETA_STRUCT		    gABFluxR;		//αβ坐标轴下转子磁通
//extern ALPHABETA_STRUCT		    gABFluxR_obs;	    //αβ坐标轴下转子磁通观测值
//extern ALPHABETA_STRUCT		    gABFluxS_obs;	    //αβ坐标轴下转子磁通观测值
//extern ALPHABETA_STRUCT		    gABFluxR_cmd;
//extern PID_STRUCT               gWs_Obs_PID;

//extern SVC_FLUX_CAL_STRUCT		gCalFlux;		
//extern PID_STRUCT_LONG          gVoltSVCCalPID;
//extern PID_STRUCT               gSvcVoltAdj;
extern FLUX_STRUCT              gFluxR;
extern FLUX_STRUCT              gFluxS;
extern MT_STRUCT_Q24           	gIMTQ24_obs;  //除转速估计外，需供电流控制函数使用
extern MT_STRUCT_Q24           	gIMTQ12_obs;  //除转速估计外，需供电流控制函数使用
extern SVC_FLUX_CAL_STRUCT		gCalFlux;

extern MT_STRUCT                		gABVoltRatio;   	
extern ALPHABETA_STRUCT			gABFluxS_LowFilter;	//αβ坐标轴下定子磁通给定值
extern ALPHABETA_STRUCT			gABFluxS_comp;	    //αβ坐标轴下定子磁通观测补偿值：该变量应定义为全局变

extern int                      gSVCNEWMKP;           // M轴电流环比例系数    
extern int                      gSVCNEWMKI;           // M轴电流环积分系数
extern int                      gSVCNEWSpeedFilter;   // svcnew速度滤波系数

//	同频波动滤波
typedef struct  {
	long  PutIn_Q24;
	long  Delta_Q24;
	long  PutOut_Q24;
	long  PutOut_II_Q24;
	long  PutOutLast_Q24;
	long  PutOut_I_Q24;
	long  Ts_Q24;
	long  K1_Q0;
	long  K2_Q4;
	long  FreqSyn_Mpy100;
	void  (*calc)(void *);   
}P_FILTER;

#define P_FILTER_DEF {0,0,0,0,0,0,0,0,0,0,\
	(void (*)(void *))PFilter}
extern P_FILTER gPfilter_ObsIT;
void PFilter(P_FILTER *p);

/************************************************************/
/*******************供外部引用函数声明***********************/
void ResetSVC(void);
void CalcABVolt(void);
void SVCCalFlux_380(void);        
void SvcCalOutVolt_380(void);
void SVCCalRotorSpeed_380(void);
void ResetSVCNEW(void);
void PreparesvcnewPar(void);
void svcnewCalFlux(void);
void svcnewCalRotorSpeed(void);
void svcnewCalOutVolt(void);


//外加的函数声明
extern void CalImLpf(void);
extern void CalWsAndSynFreq(void);
extern void SystemParChg2Ms(void);
extern void ChangeMotorPar(void);
extern void IMSVCNEWParaChange(void);
//extern void IMMotorParaChange(void);
extern void ResetSVCNEW(void);
extern void PrepareSVCNEWPar(void);
extern void SVCNEWCalFlux(void);
extern void SVCNEWCalRotorSpeed(void);
extern void CalcABVolt(void);
extern void ChangeCurrent(void);
extern void AsynPWMAngleCal(void);
extern void CalOutputPhase(void);
extern void SVCNEWCalOutVolt(void);
extern f32 CalIMSet(void);


#ifdef __cplusplus
}
#endif /* extern "C" */
#endif  // end of definition

