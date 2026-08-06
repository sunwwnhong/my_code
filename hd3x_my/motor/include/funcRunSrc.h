
#ifndef __F_RUN_CMD_H__
#define __F_RUN_CMD_H__


#include "m_interfacePublic.h"
#include "funcCode.h"
// ----------------函数声明----------------------------------------------
extern void SetTimeRun(void);
extern void RunTimeCal(void);
extern void RunSrcDeal(void);
extern void UpdateBenchTime(void);
// ----------------函数声明结束------------------------------------------

// 加减速
#define CONST_SPEED     0       // 恒速
#define ACC_SPEED       1       // 加速
#define DEC_SPEED       2       // 减速

// 加减速方式
#define FUNCCODE_accDecSpdCurve_LINE        0   // 直线加减速
#define FUNCCODE_accDecSpdCurve_S_CURVE_A   1   // S曲线1，普通二次方
#define FUNCCODE_accDecSpdCurve_S_CURVE_B   2   // S曲线2，参考三菱S曲线B
#define ACC_DEC_LINE    FUNCCODE_accDecSpdCurve_LINE
#define ACC_DEC_SA      FUNCCODE_accDecSpdCurve_S_CURVE_A
#define ACC_DEC_SB      FUNCCODE_accDecSpdCurve_S_CURVE_B


extern Uint16 runSrc;
extern u16 bAntiReverseRun;
extern int32 frqAimOld4Dir;
extern u16 runDirPanelOld;   // 操作面板的old运行方向
extern Uint16 accDecFrqPrcFlag;   // 键盘UP/DOWN修改频率标志

extern u16 frqCalcSrc;
extern u16 frqCalcSrcOld;
extern u16 bStopPlc; 
extern u16 plcStep;
extern u16 plcStepOld;
extern Uint16 tuneCmd;

extern Uint16 bStart;
extern Uint16 timeBench;
extern Uint16 bFrqCurAimChg;
extern Uint16 setRunLostTime;
extern Uint16 setRunTimeAim;               // 设定定时运行时间

extern u16 controlModeForHmi;
extern Uint16 startModeTmp;
extern Uint16 bErrLevelStop;
extern Uint16 stopModeForHmi;
extern Uint16 diControlMode;
extern Uint16 diagnoseCmd;
extern Uint16 outputSelfDiagnoseStatus;
// ====================================================================
// 调谐过程中状态
#define TUNE_STEP_WAIT      0           // 正在辨识，性能没有任何指令
#define TUNE_STEP_ACC       50          // 辨识过程中加速
#define TUNE_STEP_DEC       51          // 辨识过程中减速
#define TUNE_STEP_END       100         // 辨识结束。保存结果，减速停机。
#define TUNE_STEP_STOP      10000       // 辨识过程中停止 自由停车 和DSP交互没关系

//=====================================================================
// runCmd，运行命令字
//
#define FORWARD_DIR         0   // 正方向
#define REVERSE_DIR         1   // 反方向

#define RUN_CMD_NO_JOG      0   // 无点动命令
#define RUN_CMD_FWD_JOG     1   // 正向点动
#define RUN_CMD_REV_JOG     2   // 反向点动
#define RUN_CMD_FWD_REV_JOG 3   // 既有正向点动命令，又有反向点动命令

#define RUN_CMD_TUNE_NO     0   // 没有调谐命令
#define RUN_CMD_TUNE_STATIC 1   // 静态调谐命令
#define RUN_CMD_TUNE_WHOLE  2   // 完全调谐命令

struct RUN_CMD_BITS
{                               // bits  description
    Uint16 common0:1;           // 0     +, 普通运行命令(非点动、调谐)，中间值，且保留下次使用
    Uint16 common:1;            // 1     -, 逻辑处理之后的普通运行命令(非点动、调谐)
    Uint16 jog:2;               // 3:2   -, 0-no jog, 1-jog
    Uint16 tune:2;              // 5:4   -, 0-no tune; 1-static tune; 2-whole tune

    Uint16 dir:1;               // 6     +, 0-fwd, 1-rev. 表示运行方向，不包括点动方向

    Uint16 pause:1;             // 7     -, 运行暂停
    
    Uint16 freeStop:1;          // 8     -,
    Uint16 hurryStop:1;         // 9     ?, 目前暂未使用

    Uint16 otherStop:1;         // 10    +, 其他情况的停机/非默认停机，强制保护
    Uint16 startProtect:1;      // 11    +, 启动保护

    Uint16 errorReset:1;        // 12    -, 故障复位
//-----------

    Uint16 rsvd:2;              // 15:13
};

union RUN_CMD
{
    Uint16              all;
    struct RUN_CMD_BITS bit;
};
/*
union DSP_MAIN_COMMAND
{
    Uint16                       all;
    struct DSP_MAIN_COMMAND_BITS bit;
};

extern union DSP_MAIN_COMMAND dspMainCmd;
*/
//=====================================================================

//=====================================================================
// dspMainCmd1, 转递给性能的主命令字1，运行中不可更改
//
/*
struct DSP_MAIN_COMMAND1_BITS
{                               // bits  description
    Uint16 pgLocation:2;        // 1:0,  速度反馈PG选择. 0：本地PG，1：扩展PG2：PULSE脉冲输入（DI5）
    Uint16 fvcPgLogic:1;        // 2,    速度反馈PG卡，AB相序. 1-B超前A.
    Uint16 deadCompMode:3;      // 5:3,  死区补偿模式选择. 0－死区补偿模式0；1－死区补偿模式1
    Uint16 modulationMode:1;    // 6     调制方式，0-异步调制，1-同步调制
    Uint16 newKernel:1;         // 7     I代板II代板选择 1:II代板 0:I代板 
    Uint16 quickTranUp:1;       // 8     快速上切换工频闭合有效
    Uint16 frqPoint:2;          // 10:9  频率指令小数点。0: 1Hz；1：0.1Hz；2：0.01Hz
    Uint16 speedTrack:2;        // 12:11 0－无效，1－正向飞车启动，2－反向飞车启动， 3-正反向飞车启动
    Uint16 shortGnd:1;          // 13    上电对地短路检测标志

    Uint16 rsvd2:2;             // 14 - 15 保留（主从机）
};

union DSP_MAIN_COMMAND1
{
    Uint16                       all;
    struct DSP_MAIN_COMMAND1_BITS bit;
};

extern union DSP_MAIN_COMMAND1 dspMainCmd1;
*/
//=====================================================================


extern union RUN_CMD runCmd;

//=====================================================================
// dspMainCmd, 转递给性能的主命令字
//
/*
struct DSP_MAIN_COMMAND_BITS
{                               // bits  description
    Uint16 run:1;               // 0,    0:stop, 1:run
    Uint16 startBrake:1;        // 1,    start brake
    Uint16 stopBrake:1;         // 2,    stop brake
    Uint16 motorCtrlMode:4;     // 6:5:4:3   00-SVC, 01-VC, 10-VF
    Uint16 startFlux:1;         // 7:    预励磁
    Uint16 torqueCtrl:1;        // 8     转矩控制
    Uint16 accDecStatus:2;      // 10:9   00 恒速； 01 加速； 10 减速. //! 目前转差补偿使用了该标志
    Uint16 spdLoopI1:1;         // 11     速度环积分分离
    Uint16 syncTransfer:2;      // 13:12 0-none；1-Up(变频->工频)；2-Down
#if CM3000_4_QUADRANT_AFE
    Uint16 codeAB:2;            // 14 15, 0-codeA, 1-codeB 2-codeC
#else
    Uint16 codeAB:1;            // 14, 0-codeA, 1-codeB
    Uint16 rsvd:1;              // 15:14 保留
#endif
};

union DSP_MAIN_COMMAND
{
    Uint16                       all;
    struct DSP_MAIN_COMMAND_BITS bit;
};

extern union DSP_MAIN_COMMAND dspMainCmd;
//=====================================================================

//=====================================================================
// dspMainCmd1, 转递给性能的主命令字1，运行中不可更改
//
struct DSP_MAIN_COMMAND1_BITS
{                               // bits  description
    Uint16 pgLocation:2;        // 1:0,  速度反馈PG选择. 0：本地PG，1：扩展PG，2：PULSE脉冲输入（DI5）
    Uint16 fvcPgLogic:1;        // 2,    速度反馈PG卡，AB相序. 1-B超前A.
    Uint16 deadCompMode:3;      // 5:3,  死区补偿模式选择. 0－死区补偿模式0；1－死区补偿模式1
    Uint16 modulationMode:1;    // 6     调制方式，0-异步调制，1-同步调制
    Uint16 newKernel:1;         // 7     I代板II代板选择 1:II代板 0:I代板 
    Uint16 quickTranUp:1;       // 8     快速上切换工频闭合有效
    Uint16 frqPoint:2;          // 10:9  频率指令小数点。0: 1Hz；1：0.1Hz；2：0.01Hz
    Uint16 speedTrack:2;        // 12:11 0－无效，1－正向飞车启动，2－反向飞车启动， 3-正反向飞车启动
    Uint16 shortGnd:1;          // 13    上电对地短路检测标志

    Uint16 rsvd2:2;             // 14 - 15 保留（主从机）
};

union DSP_MAIN_COMMAND1
{
    Uint16                       all;
    struct DSP_MAIN_COMMAND1_BITS bit;
};

extern union DSP_MAIN_COMMAND1 dspMainCmd1;
//=====================================================================
*/

//=====================================================================
// dspSubCmd, 转递给性能的辅命令字
//
struct DSP_SUB_COMMAND_BITS_F
{                                       // bits  description
    Uint16 errorDealing:1;              // 0,    1:ERROR TALK, 功能正在进行故障处理
    Uint16 outPhaseLossProtect:1;       // 1,    输出缺相保护
    Uint16 inPhaseLossProtect:1;        // 2,    输入缺相保护
    Uint16 overloadMode:2;              // 3 4,    电机过载保护使能
    Uint16 loseLoadProtectMode:1;       // 5,    输出掉载保使能标志
    //Uint16 poffTransitoryNoStop:1;      // 5,    瞬停不停使能
    Uint16 cbc:1;                       // 6,    逐波限流功能使能标志
    Uint16 varFcByTem:1;                // 7     载波频率随温度调整
    Uint16 dualFrqBrakeEnable:1;        // 8     叠频制动使能

    Uint16 invContactFdb:1;             // 9    变频接触器反馈
    Uint16 netContactFdb:1;             // 10     变频工频接触器反馈
    Uint16 motorContactFeedback:1;      // 11     电机接触器反馈
    Uint16 afeMode00:1;                 // 12     仅检测00模式
    Uint16 encoderErrMotorCtrlMode:2;   // 13 14  编码器故障时切换成SVC1 2或停机

    Uint16 highStartingEnable:1;        // 15 高转矩启动使能
    
};

union DSP_SUB_COMMAND_F
{
    Uint16                      all;
    struct DSP_SUB_COMMAND_BITS_F bit;
};

extern union DSP_SUB_COMMAND_F dspSubCmd_F;
  extern union DSP_SUB_COMMAND dspSubCmd;
#define ERROR_DEALING dspSubCmd_F.bit.errorDealing
//=====================================================================
//=====================================================================
// 性能传递给功能的状态字
//
struct DSP_STATUS_BITS_F
{                                   // bits  description
    Uint16 runEnable:1;		        // 0     1-初始化完成，可以运行标志
    Uint16 rsvd:1;                  // 1     母线电压欠压故障标志  0-欠压  1-不欠压
    Uint16 run:1;                   // 2     运行/停机状态标志
    Uint16 coreErrorResetEnd:1;     // 3     性能故障复位完成
    Uint16 speedTrackEnd:1;         // 4     转速跟踪结束标志
    Uint16 inverterPreOl:1;         // 5     变频器过载预报警标志
    Uint16 motorPreOl:1;            // 6     电机过载预报警标志
    Uint16 forbidAccDecSpd:1;       // 7     DSP给的加减速禁止标志，1-有效
    Uint16 outAirSwitchOff:1;       // 8     变频器输出空开断开标志，即掉载标志
    Uint16 codeAB:1;                // 9     0-codeA, 1-codeB
    Uint16 invContact:1;            // 10   变频接触器
    Uint16 netContact:1;            // 11   工频接触器
    Uint16 upChangeOver:1;          // 12   上切完成标记
    Uint16 downChangeOver:1;        // 13   下切完成标记
    Uint16 motorContact:1;          // 14   电机接触器输出
    Uint16 exciteCmd:1;             // 15   同步机励磁命令
};
union DSP_STATUS_F 
{
   Uint16 all;
   struct DSP_STATUS_BITS_F   bit;
};

extern union DSP_STATUS_F dspStatus_F;

//-----------------------------------------------------
//=====================================================================
// 性能传递给功能的辅助状态字
//
struct DSP_SUB_STATUS_BITS_F
{                                   // bits  description
    Uint16 accDecStatus:2;          // 1:0   0 恒速； 1 加速； 2 减速

    Uint16 invContactOff:1;         // 2 变频接触器释放
    Uint16 netContactOn:1;          // 3 工频接触器吸合
    Uint16 netContactOff:1;         // 4 工频接触器释放

    Uint16 overLoad:1;              // 5 负载太重 需要减小风门
    Uint16 lockPhase:2;             // 6-7 0 不管 1:成功 2:失败
    Uint16 bNetContactCurrent:1;    // 8 工频有电流
    Uint16 cellVolFluct:1;          // 9 母线电压波动标记
    Uint16 speedRollBack:1;         // 10 速度换RollBack标记---HMI日志用

    Uint16 encoderAlarm:1;          // 11   FVC编码器信号正常判断标记 1:报警 0:正常

    Uint16 outContactClose:1;       // 12 输出接触器合闸(岸用电源)
    
    Uint16 rsvd:3;                  // 15:13  保留
};

/*
union DSP_SUB_STATUS 
{
   Uint16                       all;
   struct DSP_SUB_STATUS_BITS   bit;
};

extern union DSP_SUB_STATUS dspSubStatus, dspSubStatusBak;
*/
struct DSP_EXTRA_STATUS_BITS
{
    Uint16 resversePowerStatus:1;   // 0 岸用电源模式状态字-逆功率状态  0:正常状态，1:逆功率状态
    Uint16 volOpenLoopFlag:1;       // 1 岸电控制模式 0:闭环状态 1:开环状态

    Uint16 rsvd:14;                 // 2 - 15 保留
};
union DSP_EXTRA_STATUS
{
    Uint16  all;
    struct DSP_EXTRA_STATUS_BITS   bit;
};

extern union DSP_EXTRA_STATUS dspExtStatus;

//-------------------------------------------//

//调谐参数
struct AUTO_TUNE_PARA_STRUCT_F
{
    Uint16 rs;              //  0 F1-06  定子电阻
    Uint16 rr;              //  1 F1-07  转子电阻
    Uint16 l0;              //  2 F1-08  漏感
    Uint16 lm;              //  3 F1-09  互感
    Uint16 iNoLoad;         //  4 F1-10  空载电流
    Uint16 pmsmRs;          //  5 F1-16  同步机定子电阻
    Uint16 pmsmLd;          //  6 F1-17  同步机d轴电感
    Uint16 pmsmLq;          //  7 F1-18  同步机q轴电感
    Uint16 rsvd1;           //  8 
    Uint16 pmsmCoeff;       //  9 F1-20  同步机反电动势系数
    struct CURRENT_LOOP_MENU1 CurrentLoopMenu;   //10~13 F2-13 - F2-16电流环相关参数
//    Uint16 acrKp;           // 10 F2-13  电流环比例增益
//    Uint16 acrKi;           // 11 F2-14  电流环积分增益
//    Uint16 acrKpBrake;      // 12 F2-15  电流环比例增益(叠频制动时)
//    Uint16 acrKiBrake;      // 13 F2-16  电流环积分增益(叠频制动时)
    Uint16 rsvd2;           // 14 
    Uint16 encoderDir;      // 15 编码器相序/主方向
    Uint16 rtPos;           // 16 编码器安装角度
    Uint16 uvGainWarp;      // 17 FF-05  UV两相增益偏差
    Uint16 rsvd5;           // 18 
    Uint16 inertia;         // 19 F1-26  惯量
    Uint16 rsvd[9];         // 20-28
    Uint16 crc;             // 29
};
#define AUTO_TUNE_PARA_LEN_F (sizeof(struct AUTO_TUNE_PARA_STRUCT_F))
union AUTO_TUNE_PARA_F
{
    Uint16 all[AUTO_TUNE_PARA_LEN_F];
    struct AUTO_TUNE_PARA_STRUCT_F code;
};

extern union AUTO_TUNE_PARA_F autoTunePara_F;


//=====================================================================
// runFlag, 变频器运行过程中的状态字
//
struct RUN_FLAG_BITS
{                               // bits  description
    Uint16 run:1;               // 0    (总的)运行标志
    
    Uint16 common:1;            // 1    普通运行(非点动、非调谐)
    Uint16 jog:1;               // 2    点动运行
    Uint16 tune:1;              // 3    调谐运行

    Uint16 jogWhenRun:1;        // 4    运行中点动
    
    Uint16 accDecStatus:2;      // 6:5  0 恒速； 1 加速； 2 减速


// 之下的bit位在shutdown时不要清除
    Uint16 plc:1;               // 7     PLC运行
    Uint16 pid:1;               // 8     PID运行
    Uint16 torque:1;            // 9     转矩控制
    
    Uint16 dir:1;               // 10    设定频率方向(功能码F0-12运行方向之前), 0-fwd, 1-rev
    Uint16 curDir:1;            // 11    当前运行频率方向, 0-fwd, 1-rev
    Uint16 dirReversing:1;      // 12    正在反向标志, 0-当前没有反向, 1-正在反向
    Uint16 dirFinal:1;          // 13    设定频率方向(功能码F0-12运行方向之后), 0-fwd, 1-rev
    Uint16 servo:1;             // 14
    Uint16 diagnose:1;			// 15    自检

};

union RUN_FLAG
{
    Uint16               all;
    struct RUN_FLAG_BITS bit;
};

extern union RUN_FLAG runFlag, runFlagBck;

//-----------------------------------------------------
// runStatus，当前运行状态/步骤
//
enum RUN_STATUS
{
    RUN_STATUS_WAIT,        	// 等待启动
    RUN_STATUS_ZERO,        	// 零频运行
    RUN_STATUS_START,       	// 启动
    RUN_STATUS_NORMAL,      	// (正常)运行
    RUN_STATUS_STOP,        	// 停机
    RUN_STATUS_JOG,         	// 点动运行

    RUN_STATUS_POS_CTRL,    	// 位置控制
    
    RUN_STATUS_TUNE,        	// 调谐运行
    RUN_STATUS_DI_BRAKE_DEC,  	// DI端子直流制动频率减速
    RUN_STATUS_DI_BRAKE,      	// DI端子的直流制动(非启动直流制动和停机直流制动)
    RUN_STATUS_LOSE_LOAD,     	// 掉载运行
    RUN_STATUS_SHUT_DOWN,		// shut down, 关断
    RUN_STATUS_DIAGNOSE			// 自检
};
extern enum RUN_STATUS runStatus;
//-----------------------------------------------------

//-----------------------------------------------------
enum START_RUN_STATUS
{
    START_RUN_STATUS_SPINNING_LOAD,         // 转速跟踪
    START_RUN_STATUS_PRE_FLUX,              // 预励磁
    START_RUN_STATUS_HOLD_START_FRQ,        // 启动频率保持
    START_RUN_STATUS_BRAKE_OPEN_WAIT,       // 启动等待开抱闸
    START_RUN_STATUS_BRAKE_OPEN_DELAY      // 开抱闸延时
};
#define START_RUN_STATUS_INIT           START_RUN_STATUS_SPINNING_LOAD
extern enum START_RUN_STATUS startRunStatus;
//-----------------------------------------------------

//-----------------------------------------------------
enum STOP_RUN_STATUS
{
    STOP_RUN_STATUS_DEC_STOP,           // 减速停车
    STOP_RUN_STATUS_WAIT_BRAKE,         // 减速停车等待抱闸
    STOP_RUN_STATUS_BRAKE               // 停机直流制动
};
#define STOP_RUN_STATUS_INIT            STOP_RUN_STATUS_DEC_STOP
extern enum STOP_RUN_STATUS stopRunStatus;



//-----------------------------------------------------
struct AUX_RUN_CMD_BITS
{
	Uint16 brakeOpen:1;             // 0    开抱闸
	Uint16 brakeClose:1;            // 1    关闭抱闸
	Uint16 runFlagBeforeErr:1;      // 2    故障前运行状态
	Uint16 runDirBeforeErr:1;       // 3    故障前运行方向
	Uint16 errAutoResetFlag:1;      // 4    故障自动复位标记
	Uint16 runFlagBeforePowerOff:1; // 5    高压断电前运行状态
	Uint16 runDirBeforePowerOff:1;  // 6    高压断电前运行方向
	Uint16 bPowerOnAutoRunEnable:1; // 7    断电后重新得电 自启动运行允许
	
    Uint16 rsvd:8;
};

union AUX_RUN_CMD
{
	Uint16 all;
	struct AUX_RUN_CMD_BITS bit; 
};

extern union AUX_RUN_CMD auxRunCmd;

//extern Uint16 vfSeprateVolAim;        // VF分离的电压的目标值
//extern Uint16 vfSeparateVol;           // VF分离输出电压

extern Uint16 RectifierSwitch; // LS_20220325
// LS_20220805
#define OUT_CONTACTOR_ABNORMAL_TIME     500 // 200 // 200ms // LS_20230207
extern Uint16 OutContactStatus;
extern Uint16 OutContactTimer;

#endif











#ifndef __F_RUN_CMD_H__
#define __F_RUN_CMD_H__

// ----------------函数声明----------------------------------------------
extern void SetTimeRun(void);
extern void RunTimeCal(void);
extern void RunSrcDeal(void);
extern void UpdateBenchTime(void);
// ----------------函数声明结束------------------------------------------

// 加减速
#define CONST_SPEED     0       // 恒速
#define ACC_SPEED       1       // 加速
#define DEC_SPEED       2       // 减速

// 加减速方式
#define FUNCCODE_accDecSpdCurve_LINE        0   // 直线加减速
#define FUNCCODE_accDecSpdCurve_S_CURVE_A   1   // S曲线1，普通二次方
#define FUNCCODE_accDecSpdCurve_S_CURVE_B   2   // S曲线2，参考三菱S曲线B
#define ACC_DEC_LINE    FUNCCODE_accDecSpdCurve_LINE
#define ACC_DEC_SA      FUNCCODE_accDecSpdCurve_S_CURVE_A
#define ACC_DEC_SB      FUNCCODE_accDecSpdCurve_S_CURVE_B


extern Uint16 runSrc;
extern u16 bAntiReverseRun;
extern int32 frqAimOld4Dir;
extern u16 runDirPanelOld;   // 操作面板的old运行方向
extern Uint16 accDecFrqPrcFlag;   // 键盘UP/DOWN修改频率标志

extern u16 frqCalcSrc;
extern u16 frqCalcSrcOld;
extern u16 bStopPlc; 
extern u16 plcStep;
extern u16 plcStepOld;
extern Uint16 tuneCmd;

extern Uint16 bStart;
extern Uint16 timeBench;
extern Uint16 bFrqCurAimChg;
extern Uint16 setRunLostTime;
extern Uint16 setRunTimeAim;               // 设定定时运行时间

//extern u16 controlModeForHmi;
extern Uint16 startModeTmp;
extern Uint16 bErrLevelStop;
extern Uint16 stopModeForHmi;
extern Uint16 diControlMode;
extern Uint16 diagnoseCmd;
extern Uint16 outputSelfDiagnoseStatus;
// ====================================================================
// 调谐过程中状态
#define TUNE_STEP_WAIT      0           // 正在辨识，性能没有任何指令
#define TUNE_STEP_ACC       50          // 辨识过程中加速
#define TUNE_STEP_DEC       51          // 辨识过程中减速
#define TUNE_STEP_END       100         // 辨识结束。保存结果，减速停机。
#define TUNE_STEP_STOP      10000       // 辨识过程中停止 自由停车 和DSP交互没关系

//=====================================================================
// runCmd，运行命令字
//
#define FORWARD_DIR         0   // 正方向
#define REVERSE_DIR         1   // 反方向

#define RUN_CMD_NO_JOG      0   // 无点动命令
#define RUN_CMD_FWD_JOG     1   // 正向点动
#define RUN_CMD_REV_JOG     2   // 反向点动
#define RUN_CMD_FWD_REV_JOG 3   // 既有正向点动命令，又有反向点动命令

#define RUN_CMD_TUNE_NO     0   // 没有调谐命令
#define RUN_CMD_TUNE_STATIC 1   // 静态调谐命令
#define RUN_CMD_TUNE_WHOLE  2   // 完全调谐命令

struct RUN_CMD_BITS
{                               // bits  description
    Uint16 common0:1;           // 0     +, 普通运行命令(非点动、调谐)，中间值，且保留下次使用
    Uint16 common:1;            // 1     -, 逻辑处理之后的普通运行命令(非点动、调谐)
    Uint16 jog:2;               // 3:2   -, 0-no jog, 1-jog
    Uint16 tune:2;              // 5:4   -, 0-no tune; 1-static tune; 2-whole tune

    Uint16 dir:1;               // 6     +, 0-fwd, 1-rev. 表示运行方向，不包括点动方向

    Uint16 pause:1;             // 7     -, 运行暂停
    
    Uint16 freeStop:1;          // 8     -,
    Uint16 hurryStop:1;         // 9     ?, 目前暂未使用

    Uint16 otherStop:1;         // 10    +, 其他情况的停机/非默认停机，强制保护
    Uint16 startProtect:1;      // 11    +, 启动保护

    Uint16 errorReset:1;        // 12    -, 故障复位
//-----------

    Uint16 rsvd:2;              // 15:13
};

union RUN_CMD
{
    Uint16              all;
    struct RUN_CMD_BITS bit;
};
/*
union DSP_MAIN_COMMAND
{
    Uint16                       all;
    struct DSP_MAIN_COMMAND_BITS bit;
};

extern union DSP_MAIN_COMMAND dspMainCmd;
*/
//=====================================================================

//=====================================================================
// dspMainCmd1, 转递给性能的主命令字1，运行中不可更改
//
/*
struct DSP_MAIN_COMMAND1_BITS
{                               // bits  description
    Uint16 pgLocation:2;        // 1:0,  速度反馈PG选择. 0：本地PG，1：扩展PG，2：PULSE脉冲输入（DI5）
    Uint16 fvcPgLogic:1;        // 2,    速度反馈PG卡，AB相序. 1-B超前A.
    Uint16 deadCompMode:3;      // 5:3,  死区补偿模式选择. 0－死区补偿模式0；1－死区补偿模式1
    Uint16 modulationMode:1;    // 6     调制方式，0-异步调制，1-同步调制
    Uint16 newKernel:1;         // 7     I代板II代板选择 1:II代板 0:I代板 
    Uint16 quickTranUp:1;       // 8     快速上切换工频闭合有效
    Uint16 frqPoint:2;          // 10:9  频率指令小数点。0: 1Hz；1：0.1Hz；2：0.01Hz
    Uint16 speedTrack:2;        // 12:11 0－无效，1－正向飞车启动，2－反向飞车启动， 3-正反向飞车启动
    Uint16 shortGnd:1;          // 13    上电对地短路检测标志
    Uint16 rsvd2:2;             // 14 - 15 保留（主从机）
};

union DSP_MAIN_COMMAND1
{
    Uint16                       all;
    struct DSP_MAIN_COMMAND1_BITS bit;
};

extern union DSP_MAIN_COMMAND1 dspMainCmd1;
*/
//=====================================================================


extern union RUN_CMD runCmd;

//=====================================================================
// dspMainCmd, 转递给性能的主命令字
//
/*
struct DSP_MAIN_COMMAND_BITS
{                               // bits  description
    Uint16 run:1;               // 0,    0:stop, 1:run
    Uint16 startBrake:1;        // 1,    start brake
    Uint16 stopBrake:1;         // 2,    stop brake
    Uint16 motorCtrlMode:4;     // 6:5:4:3   00-SVC, 01-VC, 10-VF
    Uint16 startFlux:1;         // 7:    预励磁
    Uint16 torqueCtrl:1;        // 8     转矩控制
    Uint16 accDecStatus:2;      // 10:9   00 恒速； 01 加速； 10 减速. //! 目前转差补偿使用了该标志
    Uint16 spdLoopI1:1;         // 11     速度环积分分离
    Uint16 syncTransfer:2;      // 13:12 0-none；1-Up(变频->工频)；2-Down
#if CM3000_4_QUADRANT_AFE
    Uint16 codeAB:2;            // 14 15, 0-codeA, 1-codeB 2-codeC
#else
    Uint16 codeAB:1;            // 14, 0-codeA, 1-codeB
    Uint16 rsvd:1;              // 15:14 保留
#endif
};

union DSP_MAIN_COMMAND
{
    Uint16                       all;
    struct DSP_MAIN_COMMAND_BITS bit;
};

extern union DSP_MAIN_COMMAND dspMainCmd;
//=====================================================================

//=====================================================================
// dspMainCmd1, 转递给性能的主命令字1，运行中不可更改
//
struct DSP_MAIN_COMMAND1_BITS
{                               // bits  description
    Uint16 pgLocation:2;        // 1:0,  速度反馈PG选择. 0：本地PG，1：扩展PG，2：PULSE脉冲输入（DI5）
    Uint16 fvcPgLogic:1;        // 2,    速度反馈PG卡，AB相序. 1-B超前A.
    Uint16 deadCompMode:3;      // 5:3,  死区补偿模式选择. 0－死区补偿模式0；1－死区补偿模式1
    Uint16 modulationMode:1;    // 6     调制方式，0-异步调制，1-同步调制
    Uint16 newKernel:1;         // 7     I代板II代板选择 1:II代板 0:I?
    Uint16 quickTranUp:1;       // 8     快速上切换工频闭合有效
    Uint16 frqPoint:2;          // 10:9  频率指令小数点。0: 1Hz；1：0.1Hz；2：0.01Hz
    Uint16 speedTrack:2;        // 12:11 0－无效，1－正向飞车启动，2－反向飞车启动， 3-正反向飞车启动
    Uint16 shortGnd:1;          // 13    上电对地短路检测标志

    Uint16 rsvd2:2;             // 14 - 15 保留（主从机）
};

union DSP_MAIN_COMMAND1
{
    Uint16                       all;
    struct DSP_MAIN_COMMAND1_BITS bit;
};

extern union DSP_MAIN_COMMAND1 dspMainCmd1;
//=====================================================================


//=====================================================================
// dspSubCmd, 转递给性能的辅命令字
//
struct DSP_SUB_COMMAND_BITS_F
{                                       // bits  description
    Uint16 errorDealing:1;              // 0,    1:ERROR TALK, 功能正在进行故障处理
    Uint16 outPhaseLossProtect:1;       // 1,    输出缺相保护
    Uint16 inPhaseLossProtect:1;        // 2,    输入缺相保护
    Uint16 overloadMode:2;              // 3 4,    电机过载保护使能
    Uint16 loseLoadProtectMode:1;       // 5,    输出掉载保护使能标志
    //Uint16 poffTransitoryNoStop:1;      // 5,    瞬停不停使能
    Uint16 cbc:1;                       // 6,    逐波限流功能使能标志
    Uint16 varFcByTem:1;                // 7     载波频率随温度调整
    Uint16 dualFrqBrakeEnable:1;        // 8     叠频制动使能

    Uint16 invContactFdb:1;             // 9    变频接触器反馈
    Uint16 netContactFdb:1;             // 10     变频工频接触器反馈
    Uint16 motorContactFeedback:1;      // 11     电机接触器反馈
    Uint16 afeMode00:1;                 // 12     仅检测00模式
    Uint16 encoderErrMotorCtrlMode:2;   // 13 14  编码器故障时切换成SVC1 2或停机

    Uint16 highStartingEnable:1;        // 15 高转矩启动使能
    
};

union DSP_SUB_COMMAND_F
{
    Uint16                      all;
    struct DSP_SUB_COMMAND_BITS_F bit;
};

extern union DSP_SUB_COMMAND_F dspSubCmd;
*/
//#define ERROR_DEALING dspSubCmd.bit.errorDealing
//=====================================================================
//=====================================================================
// 性能传递给功能的状态字
//
struct DSP_STATUS_BITSF
{                                   // bits  description
    Uint16 runEnable:1;		        // 0     1-初始化完成，可以运行标志
    Uint16 rsvd:1;                  // 1     母线电压欠压故障标志  0-欠压  1-不欠压
    Uint16 run:1;                   // 2     运行/停机状态标志
    Uint16 coreErrorResetEnd:1;     // 3     性能故障复位完成
    Uint16 speedTrackEnd:1;         // 4     转速跟踪结束标志
    Uint16 inverterPreOl:1;         // 5     变频器过载预报警标志
    Uint16 motorPreOl:1;            // 6     电机过载预报警标志
    Uint16 forbidAccDecSpd:1;       // 7     DSP给的加减速禁止标志，1-有效
    Uint16 outAirSwitchOff:1;       // 8     变频器输出空开断开标志，即掉载标志
    Uint16 codeAB:1;                // 9     0-codeA, 1-codeB
    Uint16 invContact:1;            // 10   变频接触器
    Uint16 netContact:1;            // 11   工频接触器
    Uint16 upChangeOver:1;          // 12   上切完成标记
    Uint16 downChangeOver:1;        // 13   下切完成标记
    Uint16 motorContact:1;          // 14   电机接触器输出
    Uint16 exciteCmd:1;             // 15   同步机励磁命令
};
union DSP_STATUSF 
{
   Uint16                   all;
   struct DSP_STATUS_BITSF   bit;
};

extern union DSP_STATUSF dspStatusF;
/*
//-----------------------------------------------------
//=====================================================================
// 性能传递给功能的辅助状态字
//
struct DSP_SUB_STATUS_BITS
{                                   // bits  description
    Uint16 accDecStatus:2;          // 1:0   0 恒速； 1 加速； 2 减速

    Uint16 invContactOff:1;         // 2 变频接触器释放
    Uint16 netContactOn:1;          // 3 工频接触器吸合
    Uint16 netContactOff:1;         // 4 工频接触器释放

    Uint16 overLoad:1;              // 5 负载太重 需要减小风门
    Uint16 lockPhase:2;             // 6-7 0 不管 1:成功 2:失败
    Uint16 bNetContactCurrent:1;    // 8 工频有电流
    Uint16 cellVolFluct:1;          // 9 母线电压波动标记
    Uint16 speedRollBack:1;         // 10 速度换RollBack标记---HMI日志用

    Uint16 encoderAlarm:1;          // 11   FVC编码器信号正常判断标记 1:报警 0:正常

    Uint16 outContactClose:1;       // 12 输出接触器合闸(岸用电源)
    
    Uint16 rsvd:3;                  // 15:13  保留
};
*/
/*
union DSP_SUB_STATUS 
{
   Uint16                       all;
   struct DSP_SUB_STATUS_BITS   bit;
};

extern union DSP_SUB_STATUS dspSubStatus, dspSubStatusBak;
*/
struct DSP_EXTRA_STATUS_BITS
{
    Uint16 resversePowerStatus:1;   // 0 岸用电源模式状态字-逆功率状态  0:正常状态，1:逆功率状态
    Uint16 volOpenLoopFlag:1;       // 1 岸电控制模式 0:闭环状态 1:开环状态

    Uint16 rsvd:14;                 // 2 - 15 保留
};
union DSP_EXTRA_STATUS
{
    Uint16  all;
    struct DSP_EXTRA_STATUS_BITS   bit;
};

extern union DSP_EXTRA_STATUS dspExtStatus;

//-------------------------------------------//

//调谐参数
struct AUTO_TUNE_PARA_STRUCT_F
{
    Uint16 rs;              //  0 F1-06  定子电阻
    Uint16 rr;              //  1 F1-07  转子电阻
    Uint16 l0;              //  2 F1-08  漏感
    Uint16 lm;              //  3 F1-09  互感
    Uint16 iNoLoad;         //  4 F1-10  空载电流
    Uint16 pmsmRs;          //  5 F1-16  同步机定子电阻
    Uint16 pmsmLd;          //  6 F1-17  同步机d轴电感
    Uint16 pmsmLq;          //  7 F1-18  同步机q轴电感
    Uint16 rsvd1;           //  8 
    Uint16 pmsmCoeff;       //  9 F1-20  同步机反电动势系数
    struct CURRENT_LOOP_MENU1 CurrentLoopMenu;   //10~13 F2-13 - F2-16电流环相关参数
//    Uint16 acrKp;           // 10 F2-13  电流环比例增益
//    Uint16 acrKi;           // 11 F2-14  电流环积分增益
//    Uint16 acrKpBrake;      // 12 F2-15  电流环比例增益(叠频制动时)
//    Uint16 acrKiBrake;      // 13 F2-16  电流环积分增益(叠频制动时)
    Uint16 rsvd2;           // 14 
    Uint16 encoderDir;      // 15 编码器相序/主方向
    Uint16 rsvd4;           // 16 
    Uint16 uvGainWarp;      // 17 FF-05  UV两相增益偏差
    Uint16 rsvd5;           // 18 
    Uint16 inertia;         // 19 F1-26  惯量
    Uint16 rsvd[9];         // 20-28
    Uint16 crc;             // 29
};
#define AUTO_TUNE_PARA_LEN_F (sizeof(struct AUTO_TUNE_PARA_STRUCT_F))
union AUTO_TUNE_PARA_F
{
    Uint16 all[AUTO_TUNE_PARA_LEN_F];
    struct AUTO_TUNE_PARA_STRUCT_F code;
};

extern union AUTO_TUNE_PARA_F autoTunePara_F;


//=====================================================================
// runFlag, 变频器运行过程中的状态字
//
struct RUN_FLAG_BITS
{                               // bits  description
    Uint16 run:1;               // 0    (总的)运行标志
    
    Uint16 common:1;            // 1    普通运行(非点动、非调谐)
    Uint16 jog:1;               // 2    点动运行
    Uint16 tune:1;              // 3    调谐运行

    Uint16 jogWhenRun:1;        // 4    运行中点动
    
    Uint16 accDecStatus:2;      // 6:5  0 恒速； 1 加速； 2 减速


// 之下的bit位在shutdown时不要清除
    Uint16 plc:1;               // 7     PLC运行
    Uint16 pid:1;               // 8     PID运行
    Uint16 torque:1;            // 9     转矩控制
    
    Uint16 dir:1;               // 10    设定频率方向(功能码F0-12运行方向之前), 0-fwd, 1-rev
    Uint16 curDir:1;            // 11    当前运行频率方向, 0-fwd, 1-rev
    Uint16 dirReversing:1;      // 12    正在反向标志, 0-当前没有反向, 1-正在反向
    Uint16 dirFinal:1;          // 13    设定频率方向(功能码F0-12运行方向之后), 0-fwd, 1-rev
    Uint16 servo:1;             // 14
    Uint16 diagnose:1;			// 15    自检

};

union RUN_FLAG
{
    Uint16               all;
    struct RUN_FLAG_BITS bit;
};

extern union RUN_FLAG runFlag, runFlagBck;

//-----------------------------------------------------
// runStatus，当前运行状态/步骤
//
enum RUN_STATUS
{
    RUN_STATUS_WAIT,        	// 等待启动
    RUN_STATUS_ZERO,        	// 零频运行
    RUN_STATUS_START,       	// 启动
    RUN_STATUS_NORMAL,      	// (正常)运行
    RUN_STATUS_STOP,        	// 停机
    RUN_STATUS_JOG,         	// 点动运行

    RUN_STATUS_POS_CTRL,    	// 位置控制
    
    RUN_STATUS_TUNE,        	// 调谐运行
    RUN_STATUS_DI_BRAKE_DEC,  	// DI端子直流制动频率减速
    RUN_STATUS_DI_BRAKE,      	// DI端子的直流制动(非启动直流制动和停机直流制动)
    RUN_STATUS_LOSE_LOAD,     	// 掉载运行
    RUN_STATUS_SHUT_DOWN,		// shut down, 关断
    RUN_STATUS_DIAGNOSE			// 自检
};
extern enum RUN_STATUS runStatus;
//-----------------------------------------------------

//-----------------------------------------------------
enum START_RUN_STATUS
{
    START_RUN_STATUS_SPINNING_LOAD,         // 转速跟踪
    START_RUN_STATUS_PRE_FLUX,              // 预励磁
    START_RUN_STATUS_HOLD_START_FRQ,        // 启动频率保持
    START_RUN_STATUS_BRAKE_OPEN_WAIT,       // 启动等待开抱闸
    START_RUN_STATUS_BRAKE_OPEN_DELAY      // 开抱闸延时
};
#define START_RUN_STATUS_INIT           START_RUN_STATUS_SPINNING_LOAD
extern enum START_RUN_STATUS startRunStatus;
//-----------------------------------------------------

//-----------------------------------------------------
enum STOP_RUN_STATUS
{
    STOP_RUN_STATUS_DEC_STOP,           // 减速停车
    STOP_RUN_STATUS_WAIT_BRAKE,         // 减速停车等待抱闸
    STOP_RUN_STATUS_BRAKE               // 停机直流制动
};
#define STOP_RUN_STATUS_INIT            STOP_RUN_STATUS_DEC_STOP
extern enum STOP_RUN_STATUS stopRunStatus;



//-----------------------------------------------------
struct AUX_RUN_CMD_BITS
{
	Uint16 brakeOpen:1;             // 0    开抱闸
	Uint16 brakeClose:1;            // 1    关闭抱闸
	Uint16 runFlagBeforeErr:1;      // 2    故障前运行状态
	Uint16 runDirBeforeErr:1;       // 3    故障前运行方向
	Uint16 errAutoResetFlag:1;      // 4    故障自动复位标记
	Uint16 runFlagBeforePowerOff:1; // 5    高压断电前运行状态
	Uint16 runDirBeforePowerOff:1;  // 6    高压断电前运行方向
	Uint16 bPowerOnAutoRunEnable:1; // 7    断电后重新得电 自启动运行允许
	
    Uint16 rsvd:8;
};

union AUX_RUN_CMD
{
	Uint16 all;
	struct AUX_RUN_CMD_BITS bit; 
};

extern union AUX_RUN_CMD auxRunCmd;

//extern Uint16 vfSeprateVolAim;        // VF分离的电压的目标值
//extern Uint16 vfSeparateVol;           // VF分离输出电压


#endif












