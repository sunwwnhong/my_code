//----------------------------------------------------------//
// File Name		: funcCommWithDSP.c	
// Description		: 和DSP的交互数据处理
// Time				: 2011.03.02
// Editor			: xxxxx
// Co.				: xxxxx
//----------------------------------------------------------//

#ifndef __F_FUNC_COMM_WITH_DSP_H__
#define __F_FUNC_COMM_WITH_DSP_H__


// ----------------函数声明---------------------------------------------- 
extern void UpdateDataFunc2Core2ms(void);
extern void UpdateDataCore2Func(void); 
extern void UpdateDispData(void);
// ----------------函数声明结束------------------------------------------
#define MOTOR_ALARM_NUM_MAX     16

#define Bank1_SRAM3_ADDR    ((Uint32)0x68000000)  
extern u16 *fpgaRam;
#define ARM_READ_TUNE_DATA_ADDR_OFFSET  0           //读地址偏移量 调谐
#define ARM_READ_ADDR_OFFSET            30          //读地址偏移量
#define ARM_WRITE_ADDR_OFFSET           512         //写地址偏移量

// 读150个字
/*
struct MOTOR_PARA_STRUCT_ARM
{
    // 电机基本参数
    u16 motorType;               // F1-00  电机类型选择
    u16 ratingPower;             // F1-01  电机额定功率
    u16 ratingVoltage;           // F1-02  电机额定电压
    u16 ratingCurrent;           // F1-03  电机额定电流
    u16 ratingFrq;               // F1-04  电机额定频率
    u16 ratingSpeed;             // F1-05  电机额定转速

    // 异步机调谐参数
    u16 statorResistance;        // F1-06  异步机定子电阻
    u16 leakInductance;          // F1-08  异步机漏感抗
    u16 zeroLoadCurrent;         // F1-10  异步机空载电流

    u16 inertia;                 // F1-26  惯量
};
//#define MOTOR_PARA_DATA_ARM_LEN  SIZEOF(struct MOTOR_PARA_STRUCT_ARM)

struct SYN_MOTOR_PARA_STRUCT_ARM
{
    //同步机调谐参数
	Uint16 pmsmRs;				//F1-16同步机定子电阻
	Uint16 pmsmLd;				//F1-17同步机d轴电感
	Uint16 pmsmLq;				//F1-18同步机q轴电感
	Uint16 pmsmCoeff;			//F1-20同步机反电动势系数
};

struct PG_PARA_STRUCT_ARM
{
    // PG卡参数
    u16 encoderPulse;            // F1-27    编码器脉冲线数
    u16 pgType;                  // F1-28    编码器类型
    u16 encoderAngle;            // F1-31    编码器安装角
    u16 uvwSignDir;              // F1-32    UVW信号方向
    u16 uvwSignAngle;            // F1-33    UVW信号零点位置角
    u16 encoderPole;             // F1-34    旋变极对数
    u16 encoderLossLimit;        // F1-36    速度反馈PG断线检测时间==>编码器丢失检测阈值
};
*/
/*
//======================================================================
// 功能->性能的交互数据
#define F2C_DEBUG_PARA_LEN      25  // CF组，功能给性能，调试使用的参数
#define F2C_TEST_PARA_LEN       10  // CE组，调测使用的参数
#if HD72
// 岸用电源专用
#define F2C_SHORE_POWER_PARA_LEN  12   // A5-27~A5-39 
#endif

struct FUNC_TO_CORE_SLOW_DATA_A_STRUCT
{
    u16 upperTorque;         // 0    转矩限定，速度控制的电动转矩
    u16 frqCurAim2Core;      // 1    当前目标频率. 减速(停机)时为0
    u16 carrierFrq;          // 2    载波频率，单元开关频率
    u16 maxFrq;              // 3    最大频率
    u16 upperTorqueRegen;    // 4    速度控制的发电转矩
    u16 curSampleDelayComp;  // 5   电流检测延时补偿
    u16 motorTripVoltage;    // 6   电机过压保护点
    u16 spinningLoadPara[3]; // 7-9 飞车启动参数 F6-16 - 18
    u16 SyncTransferMenu[6]; // 10-15 同步切换
    u16 invIOCSetpoint;      // 16 F9-30 过流点设定
    u16 invCurrentLimit;     // 17 F9-31 

    struct MOTOR_PARA_STRUCT_ARM motorParaArm;  // 18-27 F1-00 - F1-26 电机参数，注意与功能码顺序不完全不一致，目前10个
    struct PG_PARA_STRUCT_ARM pgParaArm;        // 28-34 F1-27 - F1-36 PG卡参数，目前7个

    u16 SpeedLoopMenu[9];                	// 35-43 F2-00 - F2-08 速度环参数
    u16 CurrentLoopMenu[4];              	// 44-47 F2-13 - F2-16 电流环参数
    u16 LowFrequencyCompensationMenu[3]; 	// 48-50 A5-08 - A5-10 
    u16 FluxContrlMenu[5];               	// 51-55 F2-26 - F2-30
    u16 overLoadPara[3];                 	// 56-58 F9-01 - F9-03
    u16 uvGainWarp;                      	// 59 FF-05 UV两相增益偏差
    u16 cellBypassCmdArmL;               	// 60 单元0-15的旁路命令
    u16 cellBypassCmdArmH;               	// 61 单元16-29的旁路命令
    u16 cellCheckFlag;                   	// 62 单元检测标记

    u16 CellMenu[4];                     	// 63-66 
    u16 zeroSpeed;                       	// 67 F8-47
    u16 protectMenu[15];                 	// 68-82 F9-14 - F9-28, F9-15输出电流不平衡阈值, F9-17保留，F9-27保留
    u16 BrakingMenu[4];                  	// 83-86 F6-12 - F6-15
    u16 VolCurSampleMenu[10];            	// 87-96 FF-06 - FF-15
    
    u16 DriveRatingMenu[4];              	// 97-100 FF-16 - FF-19
    u16 DeadTimeComp;                    	// 101  A5-00
    u16 bypassMode;         			 	// 102 单元旁路方式
    u16 offTransitoryMenu[2];            	// 103-104
    u16 outputSelfDiagnose;					// 105 机侧自检
    u16 overVolInhibitKp;                   // 106 过压抑制电压环Kp 
    u16 overVolInhibitKi;                   // 107 过压抑制电压环Ki
    u16 transFrqInc;                        // 108 切换频率增量
    u16 auxFlag;                            // 109 辅助状态字
#if HD72
    u16 CounterProtectPoint;                // 110   逐波限流计数峰值保护点
    u16 CCAccValue;                         // 111   CC发生时累加值
    u16 CBCRecoverTimes;                    // 112   逐波限流恢复时间
    u16 CBCCellRecoverTime;                 // 113   逐波限流单元恢复时间间隔   
    u16 rsvd[6];						 	// 114-119
#else
    u16 fastTrackMenu[3];                   // 110-112
    u16 rsvd[3];						 	// 113-115
	struct SYN_MOTOR_PARA_STRUCT_ARM synMotorParaArm;	// 116-119
#endif
};

struct FUNC_TO_CORE_SLOW_DATA_B_STRUCT
{
    u16 FeedForwardConstant;                // 0  A5-01   电流环前馈增益
    u16 fluxLoopFeedForwardGain;            // 1  A5-02   磁链环前馈增益
    u16 OutputConnectionMenu[6];            // 2-7 FF-23, A5-03 - A5-07
    u16 HighStartingTorqueMenu[3];          // 8-10 A5-12 - A5-14
    u16 fluxCompLimit;                      // 11  A5-15 磁链观测补偿限幅
    u16 fluxLoopCloseFrq;                   // 12  A5-16 磁链闭环频率
    u16 fluxOpenIdRef;                      // 13  A5-17 磁链开环时励磁电流给定
    u16 motorControlOtherEnable;            // 14  A5-18 各种使能
    u16 npcKp[4];                           // 15-18 A5-19 -- A5-22
    u16 halfGenVolOV;                       // 19 A5-23 半母线过压点设定
    u16 halfGenVolOL;                       // 20 A5-24 半母线超限点设定
    u16 coreFunc[2];                        // 21-22  F9-72、73
    u16 windowFrq;                          // 23  负荷分配，视窗
    u16 aoData[9];                          // 24-32
    u16 ceTestPara[F2C_TEST_PARA_LEN];      // 33-42 测试参数，在CE[]
    u16 debugParaCF[F2C_DEBUG_PARA_LEN];    // 43-67 功能给性能的调试参数，目前为25个，在CF[]
    u16 flowSampleAddr[6];                  // 68-73 C0-00~C0-06
    u16 motorStall[2];                      // 74-75 F9-40~F9-41
    u16 motorExcitation[2];                 // 76-77 F9-42~F9-43
    u16 rsvd_slow[20];                      // 78-97
    u16 genVolOV;                           // 98 A5-25 母线过压点设定
    u16 genVolOL;                           // 99 A5-26 母线超限点设定
#if HD72
    u16 outVoltageSet;                      // 100 岸用电源 输出电压设定值
    u16 outVolRampSet;                      // 101 岸用电源 输出电压斜坡设定值
    u16 voltageLoopKp;                      // 102 岸用电源 电压环比例系数 
    u16 voltageLoopKi;                      // 103 岸用电源 电压环积分系数
    u16 volLoopFilterTime;                  // 104 岸用电源 电压环滤波时间
    u16 frqAbnoProtLimit;                   // 105 岸用电源 频率异常保护阈值
    u16 outUvLimit;                         // 106 岸用电源 输出欠压保护阈值
    u16 rsvdSts;                            // 107 岸用电源 保留
    u16 outVolCompenstCof;                  // 108 岸用电源 输出电压补偿系数
    u16 reversePowerProtLimit;              // 109 岸用电源 逆功率保护阈值设定值
    u16 reversePowerLoopKp;                 // 110 岸用电源 逆功率控制比例增益
    u16 reversePowerLoopKi;                 // 111 岸用电源 逆功率控制积
    u16 reversePowerUpperFrq;               // 112 岸用电源 逆功率控制上限频率值
	u16 powerSourcePhase;                   // 113 岸用电源 电网相序0:正序 1:负序
    u16 closeToOpenEbl;                     // 114 岸用电源 闭环转开环使能
    u16 VoltageChangeEbl;                   // 115 岸用电源 前后级电压控制切换使能
    u16 outFrqSet;                          // 116 岸用电源 最终输出频率设定值
    u16 transfomerRatio;                    // 117 岸用电源 隔离变压器变比（副边/原边）
    u16 rsvd[2];							// 118-119 保留2个
#else    
    u16 rsvd[20];							// 100-119 保留20个
#endif
};

struct FUNC_TO_CORE_SLOW_DATA_C_STRUCT
{
    u16 b1AFECode[45];                      // 0-44     b1组整流参数0-44
    u16 rsvd[75];                           // 45-119    保留
};

#define FUNC_TO_CORE_SLOW_DATA_A_LEN  (SIZEOF(struct FUNC_TO_CORE_SLOW_DATA_A_STRUCT))
#define FUNC_TO_CORE_SLOW_DATA_B_LEN  (SIZEOF(struct FUNC_TO_CORE_SLOW_DATA_B_STRUCT))
#define FUNC_TO_CORE_SLOW_DATA_C_LEN  (SIZEOF(struct FUNC_TO_CORE_SLOW_DATA_C_STRUCT))

union FUNC_TO_CORE_SLOW_DATA
{
    u16 all[FUNC_TO_CORE_SLOW_DATA_A_LEN];

    struct FUNC_TO_CORE_SLOW_DATA_A_STRUCT codeA;
    struct FUNC_TO_CORE_SLOW_DATA_B_STRUCT codeB;
    struct FUNC_TO_CORE_SLOW_DATA_C_STRUCT codeC;
};


struct FUNC_TO_CORE_DATA_STRUCT
{
    u16 mainCmd;             // 0    主命令字
    u16 frq2Core;            // 1    实时速度给定
    u16 mainCmd1;            // 2    主命令字1
    u16 subCmd;              // 3    辅助命令字
    u16 tuneCmd;             // 4    调谐选择
    u16 vfSeparateVol;       // 5   VF分离时的输出电压
    u16 vfCurve;             // 6   VF曲线选择

    u16 ovGain;              // 7    过压失速增益
    u16 ovPoint;             // 8    过压失速保护电压
    u16 ocGain;              // 9    过流失速增益
    u16 ocPoint;             // 10   过流失速保护电流

    u16 masterTorque;        // 11   负荷分配，主从控制 主机输出转矩
    u16 masterSpeedMotor;    // 12   负荷分配，主机同步频率
    
    u16 rsvd_Fast[10];       // 13-22 预留10个

//===以上，每1拍传递1次
//===以下，每3拍传递1次
    union FUNC_TO_CORE_SLOW_DATA slowData;  // 23-142 共120个

//============
    u16 flag;                // 143 arm标记位
    u16 crc;                 // 144
    u16 rsvdEnd;             // 145 任何时候都不用这个数据且放到最后
};
#define FUNC_TO_CORE_DATA_LEN  SIZEOF(struct FUNC_TO_CORE_DATA_STRUCT)

union FUNC_TO_CORE_DATA
{
    u16 all[FUNC_TO_CORE_DATA_LEN];

    struct FUNC_TO_CORE_DATA_STRUCT code;
};
*/
/*
//=====================================================================
// 性能->功能的交互数据


//==============================================================================
// 性能->功能的交互数据
#define CORE_TO_FUNC_DEBUG_PARA_LEN     15  // 性能给功能，调试使用的参数
// 请确保 sizeof(struct CORE_TO_FUNC_SLOW_DATA_A_STRUCT)与
// sizeof(struct CORE_TO_FUNC_SLOW_DATA_B_STRUCT) 两者一样。
struct CORE_TO_FUNC_SLOW_DATA_A_STRUCT
{
    u16 currentPu;                  // 0    电流标幺值，当电机额定电流与变频器的额定电流相差较大时，可能与电机额定电流不同.
    u16 ai1Sample;                  // 1    AI1的采样值，已经滤波
    u16 ai2Sample;                  // 2    AI2的采样值，已经滤波
    u16 inputCurrent;               // 3    输入电流
    u16 coreMaxFrqBypass;           // 4    旁路运行最大频率限制

    u16 motorSoftVersion;           // 5    DSP软件版本号
    u16 FPGAVersion;                // 6    FPGA 软件版本号

    u16 cellBypassFdbL;             // 7    单元0-15旁路完成标记
    u16 cellBypassFdbH;             // 8    单元16-29旁路完成标记
    u16 cellBypassEnableL;          // 9    允许旁路的单元标记 0-15
    u16 cellBypassEnableH;          // 10   允许旁路的单元标记 16-29

    u16 coreErrorCode;              // 11   Ux-00   性能产生的故障
    u16 fastLoopClks;               // 12   Ux-01   快环花销的时钟周期，0.1us
    u16 mainLoopUs;                 // 13   Ux-02   主循环花销的时间，1us
    u16 coreCarrierFrqAct;          // 14   Ux-03   (单元的)(实际使用的)载波频率，0.1Hz
    u16 fastLoopFrequency;          // 15   Ux-04   快环频率(整机载波频率)，Hz
    u16 inputSAct;                  // 16   Ux-05   输入视在功率，单位0.1kVA
    u16 inputPowerAct;              // 17   Ux-06   输入功率，单位0.1kW
    u16 outputPowerAct;             // 18   Ux-07   输出功率，单位0.1kW
    u16 driveLosses;                // 19   Ux-08   变频器损耗，0.1%
    u16 coreInfo0[1];               // 20   Ux-09   无单位

    u16 debugParaUF[CORE_TO_FUNC_DEBUG_PARA_LEN];    // 21-35 #使用UF[]组

    u16 idCurrent;                  // 36   励磁电流
    u16 generatrixVolErr;           // 37   正负母线电压偏差
    u16 reactivePower;              // 38   无功功率
    u16 outputSelfDiagnoseStatus;	// 39 	机侧自检状态
    u16 dspExtStatus;               // 40   扩展状态字--岸用电源占用两个BIT
    u16 maxCellGenVol;              // 41   当前所有单元母线电容最大值
    u16 rsvd[7];                   	// 42-48 保留
};
#define CORE_TO_FUNC_SLOW_DATA_A_LEN  (SIZEOF(struct CORE_TO_FUNC_SLOW_DATA_A_STRUCT))

struct CORE_TO_FUNC_SLOW_DATA_B_STRUCT
{
    
    u16 coreInfo1[10];              // 00-09  Ux-10 - UA-19   无单位
    u16 coreInfo2[10];              // 10-19  Ux-20 - UA-29   0.1%
    u16 coreInfo3[10];              // 20-29  Ux-30 - UA-39   0.1%
    u16 coreInfo4[10];              // 30-39  Ux-40 - UA-49   0.1%
    u16 aPhaseVol;                  // 40     UA-50   1V
    u16 bPhaseVol;                  // 41     UA-51   1V
    u16 cPhaseVol;                  // 42     UA-52   1V
    u16 aPhaseCur;                  // 43     UA-53   0.1A
    u16 bPhaseCur;                  // 44     UA-54   0.1A
    u16 cPhaseCur;                  // 45     UA-55   0.1A
    u16 rsvd[3];					// 40-48  保留
    
};

#define CORE_TO_FUNC_SLOW_DATA_B_LEN  (SIZEOF(struct CORE_TO_FUNC_SLOW_DATA_B_STRUCT))


union CORE_TO_FUNC_SLOW_DATA
{
    u16 all[CORE_TO_FUNC_SLOW_DATA_A_LEN];

    struct CORE_TO_FUNC_SLOW_DATA_A_STRUCT codeA;
    struct CORE_TO_FUNC_SLOW_DATA_B_STRUCT codeB;
};



struct CORE_TO_FUNC_DATA_STRUCT
{
    u16 dspStatus;              // 0    状态
    u16 motorCtrlTuneStatus;    // 1    参数辨识状态字
    
    u16 errorCodeFromCore;      // 2    性能故障代码
    u16 alarmCodeFromCore;      // 3    性能告警代码
    u16 coreErrorInfo;          // 4    故障提示信息
    u16 coreAlarmInfo[MOTOR_ALARM_NUM_MAX]; // 5-20 报警提示信息157-168

    u16 dspSubStatus;           // 21   辅助状态字 

    u16 syncFrq;                // 22   同步频率
    u16 speedMotor;             // 23   输出频率
    u16 encoderFdb;             // 24   编码器反馈频率，PU值
    
    u16 outVoltage;             // 25   输出电压
    u16 generatrixVoltage;      // 26   母线电压
    u16 torqueCurrent;          // 27   转矩电流，基值是传递过来的“实际使用的电流基值”
    u16 itDisp;                 // 28   输出转矩
    u16 outCurrent;             // 29   输出电流
    u16 outPower;               // 30   输出功率
    u16 inputPower;             // 31   输入功率，Q12，PU值。1PU=输入额定电流*输入额定电压*sqrt(3)。
    u16 inputVoltage;           // 32   输入电压
    u16 inputFrq;               // 33   输入电压的频率
//    u16 autoTunePara[AUTO_TUNE_PARA_LEN];            // 32-61 调谐参数，目前为30个。顺序见AUTO_TUNE_PARA_LEN定义
// 单独出来了。

    u16 cellBlockStatus;        // 34   单元block状态
    u16 cellStatus;             // 35   单元状态1
    u16 cellStatusL;            // 36   单元状态2
    u16 cellVolVer;             // 37   单元版本号,电压
    u16 rsvd38;                 // 38   
    u16 currentOc;              // 39   三相最大输出电流 范围0~1000
	u16 sampleFastT;            // 40   快环数据采样个数--黑匣子数据
	u16 phaseDifferAbs;         // 41   输出与输入相位差的绝对值-用于快速上切换  Q12
	u16 outVoltage1;            // 42   输出电压(岸电使用)输出变压器后侧采样实际电压      
	u16 rsvd1[8];               // 43-50   保留
    
//===以上，每1拍传递1次
//---------------------------------------------------------------------
//===以下，每2拍传递1次

    union CORE_TO_FUNC_SLOW_DATA slowData;  // 51-99 共49个

//=============================================
    u16 sampleD[6][12];         // 100-171 快环交互数据
    
    u16 flag;                   // 172
    u16 crc;                    // 173
    u16 rsvdEnd;                // 174  任何时候都不用这个数据且放到最后

};
*/
//#define CORE_TO_FUNC_DATA_LEN  (sizeof(struct CORE_TO_FUNC_DATA_STRUCT)/(sizeof(u16)))
//#define CORE_TO_FUNC_DATA_LEN  (SIZEOF(struct CORE_TO_FUNC_DATA_STRUCT))
//union CORE_TO_FUNC_DATA
//{
//    u16 all[CORE_TO_FUNC_DATA_LEN];

//    struct CORE_TO_FUNC_DATA_STRUCT code;
//};

//extern union CORE_TO_FUNC_DATA c2fData;
//==============================================================================

//=======================================================//
// 性能与功能的交互

#define NET_FRQ_FOR_EU			5000	// 中国、东南亚、欧洲等，用：50Hz
#define NET_FRQ_FOR_USA			6000	// 美国、加拿大、日本等，用：60HZ

extern Uint16 motorCtrlTuneStatus;
extern Uint16 PGErrorFlag;
extern int16 outPower;         // 单位为1KW
extern Uint16 loadSpeedDisp;
extern Uint16 pidFuncFdbDisp;
extern Uint16 frqFdb;
extern Uint16 pmsmRotorPos;
extern Uint16 enCoderPosition;
extern int16 gPhiRtDisp;
extern Uint16 ABZPos;
extern Uint16 errorInfo;
extern Uint16 pidFuncRefDisp;
extern Uint16 frq2Core;
extern u16 softOcDoFlag; //用以做软件过流输出
extern int32 frqFdbTmp;
extern Uint16 outCurrentDispOld;
extern Uint16 inputCurrentDispOld;
extern Uint16 ai1Sample,ai2Sample;
extern Uint16 errorsCodeFromMotor;
extern Uint16 alarmCodeFromMotor;
extern Uint16 motorErrInfor;
extern Uint16 motorAlarmInfor[16];
extern Uint16 torqueCurrent;
extern Uint16 currentPu;
extern Uint16 inputVoltageDisp;
extern Uint16 inputCurrentDisp;
extern Uint16 inputCurrent;
extern Uint16 inputVoltage;
extern int16 inputPowerDisp1;
extern int16 inputPowerF;
extern Uint16 brakeUpperTorque;
extern Uint16 coreMaxFrqBypass;
extern Uint16 frqRunDisp;
extern Uint16 outVoltageDisp;
extern Uint16 outCurrentDisp;       // 输出电流，实际值，
extern Uint16 currentOcDisp;
extern int16 itDisp;
extern Uint16 generatrixVoltage;    // 单位: 0.1V
extern Uint16 syncFrq;
extern Uint16 motorSoftVersion,FPGAVersion;
extern Uint16 bTuneDataReady;
extern Uint16 idCurrent;            // 励磁电流显示
extern Uint16 generatrixVolErr;
extern int16 reactivePowerDisp;

#define OFF_TRANSITORY_NONE     0   // 无瞬停不停
#define OFF_TRANSITORY_INVOL_OK 1   // 瞬停不停输入电压恢复
#define OFF_TRANSITORY_NO_INVOL 2   // 瞬停不停掉高压期间
extern Uint16 frqAdjustFlag;
extern Uchar interfaceDataErr;

extern Uint16 outVoltageTmp;
extern Uint16 outVoltageTmp1;
extern Uint16 maxCellGenVol;
extern int32 outPowerFromDsp; // LS_20221128
#if HD72
extern int16 reactivePowerF;
#endif

extern Uint16 outCurrentDispU; // LS_20221116
extern Uint16 outCurrentDispV;
extern Uint16 outCurrentDispW;

#endif













//----------------------------END-------------------------//



