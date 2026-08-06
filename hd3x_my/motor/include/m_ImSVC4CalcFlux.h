#ifndef IMSVC_CONTROL_INCLUDE_H
#define IMSVC_CONTROL_INCLUDE_H
#ifdef __cplusplus
extern "C" {
#endif

//#include "m_math.h"
#include "m_main.h"

//#define labs(x)					( ((x) > (long)(0)) ? (x) : (-x) )
//#define __IQsat(A, max, min)    (GetMax( GetMin(A, max), min ))
//#define  __IQsat(A, max, min)    (GetMax( GetMin(A, max), min ))

typedef	unsigned int			Uint;
typedef	unsigned long			Ulong;
typedef	unsigned long long 		Ullong;


typedef struct IMSVC_DATA_DEF
{	
//电机参数
    long Rs;//Q15,定子电阻，真实值
	long Rr;//Q15,定子电阻，真实值
	long Rs0;//Q15,真实值
	long Rr0;//Q15,真实值
	long L0;//Q20,漏感,真实值
	long L00;//Q20,漏感,真实值
	long LrVLm;//Q10,真实值
	long LmVLr;//Q10,真实值
	long EstPerTr;//Q10,转子时间常数倒数，真实值
	long LmSet0;//Q20,互感,真实值
	long LmSet;//Q20,互感,真实值

	long I0Q;//Q12，电机空载电流
	long FullFreq;//变频器最大频率，真实值，单位0.1HZ

	long VoltCoef;  // 电压变换系数--用于将Q12标么值变换为Q15真实值
	long CurrCoef;  // 电流变换系数--用于将Q12标么值变换为Q12真实值

//电机的电压、电流
	long UdQ;//Q12，D轴电压
	long UqQ;//Q12，Q轴电压
	long Ud;//Q15，D轴电压，真实值
	long Uq;//Q15，Q轴电压，真实值

	long IdQ;//Q12，D轴电流
	long IqQ;//Q12，D轴电流
	
	
	long Id;//Q12，D轴电流，真实值
	long Id1;//Q12，D轴电流，真实值
	long Iq;//Q12，Q轴电流，真实值
	long Iq1;//Q12，D轴电流，真实值
	
	long IqQLpf;//Q20，Q轴电流给定滤波值

//观测器中间变量
	long Ed;//Q15，D轴反电动势，真实值
	long Eq;//Q15，Q轴反电动势，真实值
	long Ed1;//Q15，D轴反电动势，真实值
	long g1;//观测系数
	long g2;//观测系数
	long Kb;//观测系数
	long Kc;//观测系数
	long Kf;//观测系数

	
	
//观测器磁场变量
	long VMPhi;//Q15，观测的磁场强度，真实值
	long VMPhiL;//100*Q15，磁场强度积分值，真实值		
	
	long VMPhiMax;//Q15，磁场强度最大限制，真实值
	long VMPhiMin;//Q15，磁场强度最小限制，真实值
	long VMPhase32;//Q32,2^32=360度，磁场角度
	int  VMPhaseS;//Q16,2^16=360度，磁场角度
	long KAngel;//

//观测器使用的速度变量	
	long OmgEMax;//Q8，限定OmgE1的最大同步频率，真实值，单位RAD/S
	long OmgE1;//Q8，无滤波的观测的同步频率，观测器使用的速度值，真实值，单位RAD/S

//转速输出变量
	long OmgE;//Q8,EqLpf/VMPhiLpf得到的同步频率，用于计算WrQ，真实值，单位RAD/S
	long WrQ;//Q24,速度调节器使用的速度反馈
    long OmgE1Lpf;//Q8,OmgE1的滤波
	long WeQ;//Q15,OmgE1Lpf的标幺值，同步转速

	long Wr;


    
	long IqLpf;//Q12，Q轴电流滤波值，真实值，计算转差用
	long OmgSL;//Q8，转差频率，真实值，单位RAD/S
	long OmgSLQ;//Q8，显示用的转差频率
	long OmgFliter;//同步频率滤波
	long OmgSLFliter;//转差滤波

	
	long VMPhiLpf;//Q23，用于计算转差、同步频率的磁场强度滤波值，真实值	
	long EqLpf;//Q15，Eq的滤波值，gImSVC.EqLpf = (long long)gImSVC.OmgE * gImSVC.VMPhiLpf>>16;

	int  Direction;
	long PhiRef;
	long PhiRef0;      // Q15
	long FwKp;//磁场调节器KP
	long FwKi;//磁场调节器KI
	long ImSet;//Q12，磁场调节器输出的D轴电流给定
	long ImOpenSet;

	int OmgEMode;//0全程SVC、无特殊处理，1、发电不计算转差，2调频，3开环控制，
	int SVCFlag;//0，其它控制；1，SVC控制
	int EnableCalcFlux;//0，不执行磁场观测；1，执行磁场观测
	int FCMode;//0，低速载波；1，高速载波
	int FluxWeakFlag;//弱磁标志，0，没有弱磁；1，弱磁
	int SpeedCheck;//转速追踪标志

//开环控制时，限制最小输出电流控制变量
	long TorqMax;//Q12，最大转矩电流限定值
	long ImSetLpf;
	long ITSet0;//Q12，转矩电流给定
	long IMSet0;//Q12，励磁电流给定

	long WeQForSwitch;//Q15，用于判断开环闭环是否切换的同步频率
	long FsSetQ;//Q15，设定的运行目标频率
	long WeQOpen;//Q15，磁场定向同步转速
	long PhaseOpen;
	long FsSetQ24;//Q24，设定的运行目标频率

	int FsCmdMode;//其它,速度PI给定频率采用功能给定的值。F1F1，采用FsSetQ24
	int SwitchStep; // "2" 进行VF控制  0切换为SVC
	int SwitchEnable;
	int SwitchFreq;//切换频率0.1HZ
/////////////////////////////////////////////////
	long FcSet;//载波频率，单位0.1KHZ

	int  FunctionCode[15];
	int  TestData[10];
    long RatedWs;           // 额定滑差 0.01hz
    long VCWsCoff;          // 滑差系数
    int  PreFluxFlag;       // 启动预励磁过程 "1"允许预励磁
    long PreImLimit;        // 启动预励磁时励磁电流限幅
    long PreItLimit;        // 启动预励磁时力矩电流限幅
    long ImLimit;           // 正常运行时励磁电流限幅
    long ItLimit;           // SVC控制时预励磁阶段对力矩限幅
    int  CoefLimitEn;       // 当磁通弱时加入电流环模型

}IMSVC_CONTROL_DATA;

typedef struct IM_TUNE_RS_DEF
{

    long Rs;
	long Rs0;
	long UdQ;
	long UqQ;
	long IdQ;
	long IqQ;


	long MotorVolt;
	long InvCurrent;
	long InvVolt;
	unsigned int EstCoefSave;
	long EstCoef;
	long Um;
	long Kp;
	long Ki;
	int  EstTime;
	int  EstTime1;
	int  EstEnable;
	int  EstStep;
	int  EstOver;
	unsigned int  FcSet;
	int  TuneFlag;
	unsigned int PWMPeriod;

}IM_TUNE_RS_DATA;

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

	long 	FreqSetStep;            /*设定频率每载波周期变化步长,Q23*/
	long 	PosSet;                 /*设定频率的积分(设定电角度),Q24*/
    //Uint	SpeedFalg;				//加减速标志
}BASE_COMMAND_STRUCT;  

typedef struct MOTOR_STRUCT_DEF {
    Uint    MotorType;              //0－普通异步电机；1－变频异步电机；2－永磁同步电机
    Uint    LastMotorType;          //存储上一拍功能传递的电机机型，用于某些在电机类型改变时，需要修正的变量
	Uint 	Power;					//电机功率					单位0.1KW
	Uint 	Votage;					//电机电压					单位1V
	Uint 	CurrentGet;				//功能传递的电机电流			单位由机型确定
	Uint 	Frequency;				//电机频率					
	Uint 	FreqPer;				//标么值电机频率
	Uint 	Current;				//驱动程序选用的电流基值(可能和实际电机电流不等)					
	Uint	CurBaseCoff;			//电流基值的放大倍数
}MOTOR_STRUCT;                   //电机基本信息结构

typedef struct MOTOR_EXTERN_STRUCT_DEF {
    Uint    UnitCoff;                           //电机参数转换系数 机型小于22，为1；大于22，为10
	Uint 	R1;						            //定子相电阻		 机型小于22，单位0.001欧姆，大于22，0.0001欧姆
	Uint 	R2;						            //转子相电阻		 机型小于22，单位0.001欧姆，大于22，0.0001欧姆
	Uint 	L0;						            //漏感			 机型小于22，单位0.01mH，大于22，单位0.001mH
	Uint 	LM;						            //互感			 机型小于22，单位0.1mH，大于22，单位0.01mH
	Uint 	I0;						            //空载电流		 机型小于22，单位0.01A，大于22，单位0.1A
	Uint    IoVsFreq;                           //弱磁区反比速度变化的空载电流，只计算它的标么值
	Uint 	Rpm;					            //电机转速		 单位1rpm
    Uint    RatedComp;	                        //额定转差率       0.01Hz, pu
	Uint 	Poles;					            //电机极数
	Uint 	L1;						            //定子相电感		 机型小于22，单位0.1mH，大于22，单位0.01mH
	Uint 	L2;						            //转子相电感		 机型小于22，单位0.1mH，大于22，单位0.01mH
      //Uint    RsPm;                               // 同步机定子电阻
	//Uint 	LD;						            //同步机D轴电感     机型 <22，单位0.01mH，机型 >22，单位0.001mH
	//Uint 	LQ;						            //同步机Q轴电感     机型 <22，单位0.01mH，机型 >22，单位0.001mH
	//Uint    BemfVolt;                               // 同步机反电动势电压， 可以计算出转子磁链
	//Uint    FluxRotor;                              // 同步机转子磁链  Q12
    Uint    FluxRotor1;
    Uint    ItRated;                                // 额定力矩电流，pm im共用
    Uint    FluxLeakCurveGain;
	Uint	Tr;
}MOTOR_EXTERN_STRUCT;   //电机扩展信息结构




extern IMSVC_CONTROL_DATA gImSVC;
extern IM_TUNE_RS_DATA gImTuneRs;

extern BASE_PAR_STRUCT			gBasePar;	    //基本运行参数
extern BASE_COMMAND_STRUCT		gMainCmd;		//主命令
extern MOTOR_STRUCT 			gMotorInfo;	    //电机信息
extern MOTOR_EXTERN_STRUCT		gMotorExtInfo;	//电机扩展信息（实际值表示）
extern MOTOR_EXTERN_STRUCT		gMotorExtPer;	//电机扩展信息（标么值表示）


extern void Modulo2PI(f32 *angle);
extern void ImSVC4CalcUI();
extern void ImSVCCalcFlux();
extern void CalcImSVCOmg();
extern void CalcSvcEstCoef();
extern void PrepareSVC4Par();
extern void IMMotorParaChangeSVC34();
extern void ChangeMotorParSVC34();
extern void ReSetImSVC4Data();
extern f32 FieldWeakeningIMSVC4(f32 input);

#ifdef __cplusplus
}
#endif
#endif 
 





