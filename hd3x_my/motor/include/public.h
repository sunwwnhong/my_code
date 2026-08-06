
#ifndef __F_PUBLIC_H__
#define __F_PUBLIC_H__

#include "publicDefine.h"
//#include "stm32f10x.h"
#include "DSP28x_Project.h"
#include "IQmathLib.h"
#include "C28x_FPU_FastRTS.h"




// ----------------函数声明---------------------------------------------- 
extern u16 GetNumberDigit(Uint16 digit[5], Uint16 number, Uint16 mode);
extern void GetNumberDigit1(Uint16 digit[5], Uint16 number);
extern void GetNumberDigit2(Uint16 digit[5], Uint16 number);

// ----------------函数声明结束------------------------------------------
//======================================================================

#define DECIMAL     0
#define HEX         1

#define DIAGNOSE_DISABLE_TIME       5000

extern u16 IsUpEdgeValid(Uint16 signal, Uint16 signalBak);
extern u16 IsDownEdgeValid(Uint16 signal, Uint16 signalBak);
extern u16 IsInputVoltageOn(Uint16 voltageModifyThreshold);
/*
// 两点(x1,y1), (x2,y2), 求第三点(x, y)的y
// 请确保: x1 < x2
typedef struct
{
    void (*calc)(void *);     // Pointer to calculation functon
    
    int16 mode;               // 1，表示x和y不限幅；0，限幅

    int32 x1;
    int32 y1;                 // (x1,y1)
    int32 x2;
    int32 y2;                 // (x2,y2)

    int32 x;                  // 需要求解点(x,y)的x, 输入
    int32 y;                  // 需要求解点(x,y)的y, 输出
} LINE_STRUCT;


void LineCalc(LINE_STRUCT *p);
#define LINE_STRTUCT_DEFALUTS       \
{                                   \
    (void (*)(void *))LineCalc      \
}
extern void LineCalc(LINE_STRUCT *p);
//-------------------------------------------//
*/
typedef struct
{
    void (*calc)(void *);         // Pointer to calculation functon

    int32 t;                      // 滤波时间

    int32 in;                     // 输入
    int32 out;                    // 输出

    int32 outOld;                 // 上一次的输出
    int32 remainder;              // 运算过程中的余数
} LowPassFilter;


extern void LpfCalc(LowPassFilter *p);

#define LPF_DEFALUTS            \
{                               \
    (void (*)(void *))LpfCalc   \
}

//-----------------------------------------------------
// 直线变化的计算：加减速，PID给定的计算
// 已知从 0 到 最大值maxValue 的变化时间为 tickerAll，
// 每次新的计算，remainder应该清零，但是影响很小。
//
/*
typedef struct
{
    void (*calc)(void *);       // 函数指针

    int32 maxValue;             // 最大值
    int32 aimValue;             // 目标值
    int32 curValue;             // 当前值

    Uint32 tickerAll;           // 从0到最大值的ticker
    int32 remainder;            // 计算delta的余值
} LINE_CHANGE_STRUCT;



#define LINE_CHANGE_STRTUCT_DEFALUTS       \
{                                          \
    (void (*)(void *))LineChangeCalc       \
}
extern LINE_CHANGE_STRUCT frqLine;

void LineChangeCalc(LINE_CHANGE_STRUCT *p);
*/

//================================================//
// ---------辅助标记---------//
struct AUX_FLAG_BITS
{
    Uint16 powerOK:1;               // 0 控制电源掉电
    Uint16 highUrgencyDisjuction:1; // 1 高压紧急分断
    Uint16 specPasswordPassed:1;    // 2 特殊密码解锁成功
    Uint16 powerOnTimeErr:1;        // 3 上电时间到达 1故障 0报警
    Uint16 armDspDataErr:1;         // 4 交互数据出错
    Uint16 inspectTimeArriveErr:1;  // 5 检修运行时间到
    Uint16 antiRunStop:1;           // 6 反转禁止
    Uint16 plcInitFinish:1;         // 7 PLC初始化完成
    Uint16 runTimeArriveErr:1;      // 8 运行时间到达 1故障 0 报警
    Uint16 dspInitFinish:1;         // 9 DSP初始化完成 上电5秒计时，计时完成才启用dsp交互过来的coreMaxFrqBypass
    Uint16 runFlagBeforeErr:1;      // 10 故障前运行状态
    Uint16 excitErr:1;     			// 11 励磁柜故障
    Uint16 controlPowerErr:1;       // 12 控制电源故障
    Uint16 newKernel:1;             // 13 二代新控制板
    Uint16 cellOvTempDisjuction:1;  // 14 多个单元持续过温故障需跳高压标记  1-跳高压
    Uint16 preChargeCmd:1;          // 15 预充命令

    Uint16 bypassAimFrqEnable:1;    // 16 降额运行中
    Uint16 manualBypassEnable:1;    // 17 手动控制自动旁路柜 需要停机 
    Uint16 runFlagForBypass:1;      // 18 用自动旁路柜手动切工频前运行状态
    Uint16 fpgaDspDataErr:1;      	// 19 DSP连续3个载波周期未给FPGA写SIN值-交互数据出错
    Uint16 cellFibreErrReadOver:1;  // 20 HMI已读单元光纤误码标志
    Uint16 bEncoderErr:1;           // 21 码盘故障标记
    Uint16 sliconErr:1;             // 22 可控硅故障
    Uint16 igbt3XErr:1;             // 23 3x igbt故障
    Uint16 highSwitchCloseDelay:1;  // 24 合闸延时状态
    Uint16 prechargeResOffCmd:1;    // 25 电阻预充柜 分闸命令
    Uint16 invContactCloseCmd:1;    // 26 手动闭合变频接触器命令-通讯给定
    Uint16 aiOffAlarm:1;            // 27 模拟量断线报警
    Uint16 dehumidifierOver:1;      // 28 系统除湿完成
    Uint16 manualLine2InvCmd:1;     // 29 手动给定--自动旁路柜下切命令
    Uint16 line2InvSpinning:1;      // 30 自动旁路柜下切强制飞车标记
    Uint16 reactorContAlarm:1;     	// 31 电抗器旁路接触器报警

};

union AUX_FLAG
{
    Uint32 all;
    struct AUX_FLAG_BITS bit;
};
extern union AUX_FLAG auxFlag;


#define BACK_EMF_OK             0       // 不判断反电势 或者 反电势已衰减到安全范围以内
#define BACK_EMF_TOO_HIGH       1       // 启动时判断到反电势大于变频器最大输出电压能力
struct AUX_FLAG_SUB_BITS
{
    Uint16 backEmfStatus:1;         // 0 反电势未衰减到可承受范围内
    Uint16 controlPowerAlarm:1;     // 1 控制电压报警
    Uint16 manualLine2InvCmd2:1;    // 2 自动旁路柜下切命令2
    Uint16 outputVolEnough:1;       // 3 变频器最大输出电压满足需求
    Uint16 rePowerStatus:1;         // 4 逆功率状态 1-处于逆功率状态中
    Uint16 volOpenLoopFlag:1;       // 5 岸电控制模式 0:闭环状态 1:开环状态
    Uint16 sourceShortErr:1;        // 6 岸电-输出绝缘下降故障 0-无效或报警；1-故障
    Uint16 downTransRunReady:1;     // 7 快速下切启动就绪
    Uint16 line2InvRunReady:1;      // 8 自动旁路柜下切启动就绪
    Uint16 fanAlarmEnable:1;        // 9 风机报警有效
    Uint16 recovAccDecTimeEnable:1; // 10 高低压穿越恢复时加减速时间有效
    Uint16 lvrtOverTime:1;          // 11 低压穿越超时 1-已超时
    Uint16 fibreReadOver:1;         // 12 FPGA交互的光纤误码已经更新
    Uint16 skipFrqEnable:1;         // 13 二代机25/50HZ跳跃频率有效
    Uint16 outContorClose:1;        // 14 输出接触器合闸命令(岸电)
    Uint16 outContorOff:1;          // 15 输出接触器分闸命令(岸电)
    
    Uint16 rsvd:16;                 // 16 - 31
};

union AUX_FLAG_SUB
{
    Uint32 all;
    struct AUX_FLAG_SUB_BITS bit;
};
extern union AUX_FLAG_SUB auxFlagSub;

enum POWER_ON_STATUS
{
    POWER_ON_WAIT,              // 等待上电准备OK。
    POWER_ON_CORE_OK,           // (性能)上电准备OK。母线电压建立完毕，上电对地短路检测完毕
    POWER_ON_FUNC_WAIT_OT       // 功能等待时间超时。功能的等待时间超过_时间，性能上电准备还没有完毕。
}; 
extern enum POWER_ON_STATUS powerOnStatus;

//extern struct MOTOR_FC motorFc;
//extern enum MOTOR_SN motorSn;

// ---------辅助标记---------//
struct FOR_HMI_FLAG_BITS
{
    Uint16 commStatus:5;            // 0-4 通讯状态
    Uint16 antiRev:1;               // 5 反转禁止
    Uint16 superPasswordPassed:1;   // 6 密码校验通过
    Uint16 derateRun:1;             // 7 系统降额

    Uint16 canStatus:1;             // 8 can通讯状态
    Uint16 prechargeEnable:1;       // 9 系统有预充
    Uint16 decimation:1;            // 10 系统降频

    Uint16 commFlag:1;              // 11 用于给HMI判定通讯是否正确的标记
    Uint16 cellMode:4;              // 12-15 单元类型
};

union FOR_HMI_FLAG
{
    Uint16 all;
    struct FOR_HMI_FLAG_BITS bit;
};
extern union FOR_HMI_FLAG forHmiFlag;

// ---------辅助功能---------//
// 不可随意更改顺序
struct FUNC_AUX_SEL_BITS
{
    Uint16 errForDisjuction:1;      // 0: 有故障即跳高压 0:有效
    Uint16 dspDataErr:1;            // 1: DSP数据不更新报故障 1:不报故障
    Uint16 invContactCloseSrc:1;    // 2: 手动合变频接触器命令源 默认0: 端子, 1:HMI
    Uint16 srcChangeRunOn:1;        // 3: 命令源切换继续运行 0:有效
    Uint16 errAutoSaveRunCmd:1;     // 4: 故障复位时候 记录运行命令 自动复位后重新运行
    Uint16 derateRun:1;             // 5: 降额运行 1:derate
    Uint16 cellBlockEnable:1;       // 6: 单元阻断故障检测 0-开启；1-屏蔽
    Uint16 noIOPowerErr:1;          // 7: io板电源故障 1不报 0报故障
    Uint16 windRunEnable:1;         // 8: 风机开启使能
    Uint16 preChargeCmdMode:1;      // 9: 预充命令方式 0脉冲式  1电平式(命令失效接触器分闸)
    Uint16 afeCodeModifyDisable:1;  // 10 afe单元在通讯异常时不能更改功能码
    Uint16 preChargeSrc:1;          // 11 预充命令源 端子或HMI 默认0为hmi
    Uint16 synMotorKM1Sel:1;        // 12 同步机的KM1分闸特殊处理
    Uint16 localFrqSrc:1;           // 13 本地频率源 0:HMI 功能码1:F0-03
    Uint16 l3BypassNoCheck:1;       // 14 不检测旁路接触器
    
    Uint16 rsvd:1;                  // 15 保留
};

union FUNC_AUX_SEL
{
    Uint16 all;
    struct FUNC_AUX_SEL_BITS bit;
};
extern union FUNC_AUX_SEL funcAuxSel;

// ---------辅助功能2---------//
// 不可随意更改顺序
struct FUNC_AUX_SEL2_BITS
{
    Uint16 bypassAutoSpinning:1;    // 0 旁路后强制飞车启动 0有效 1关闭
    Uint16 transferAlarm:1;         // 1 是否报同步切换报警 0:报故障
    Uint16 uvAlarm:1;               // 2 欠压为报警 1有效 0故障
    Uint16 rsvd1:1;                 // 3 保留
    Uint16 runningBlockEnable:1;    // 4 是否报运行中阻断故障 0:不报故障 1:报故障
	Uint16 DP:1;                    // 5 使用DP卡
	Uint16 figureOrPercentage:1;    // 6 客户485和Profibus使用数值给定/百分比给定 默认0:数值给定
    Uint16 secondarySupplyPower:1;  // 7 柜顶风机由变压器副边绕组供电 1有效
    Uint16 sampleBoardEnable:1;     // 8 采样板 0 - 不使用  1-使用
    Uint16 siliconErrEbl:1;         // 9 可控硅故障使能 0:使能 1:不使能 (目前万泰项目设置为1)
    Uint16 err23Sel:1;              // 10 23号故障选择 0:先警告后故障(无接地电阻)  1:直接故障(有接地电阻)
    Uint16 rsvd:5;                  // 11-15
};

union FUNC_AUX_SEL2
{
    Uint16 all;
    struct FUNC_AUX_SEL2_BITS bit;
};
extern union FUNC_AUX_SEL2 funcAuxSel2;
 
// 系统日志 给上位机和HMI用
struct SYSTEM_LOG_FLAG_BITS
{
    Uint16 localOrRemote:2;         // bit0-1 0:本地 1:远程1 2:远程2
    Uint16 runSrc:4;                // bit2-5 远程命令源 功能码的值
    Uint16 run:1;                   // 6:   运行
    Uint16 stop:1;                  // 7:   停止
    Uint16 reset:1;                 // 8:   故障复位
    Uint16 eStop:1;                 // 9:   急停
    Uint16 eDisjuction:1;           // 10:  紧急分断
    Uint16 tune:1;                  // 11:  调谐
    Uint16 power:1;                 // 12:  高压电源
    Uint16 autoErrRun:1;            // 13:  故障复位自启动
    Uint16 softStart:1;             // 14:  软起完成停机

    Uint16 rsvd:1;
};

union SYSTEM_LOG_FLAG
{
    Uint16 all;
    struct SYSTEM_LOG_FLAG_BITS bit;
};
extern union SYSTEM_LOG_FLAG systemLogFlag;

struct AUX_CMD_FOR_FPGA_BITS
{
	Uint16 reset:1;	                // 0 - 保留
	Uint16 rsvd1:1;					// 1 - FPGA复位命令
    Uint16 rsvd2:2;                 // 2 - 3 其中BIT3双机并联已用
    Uint16 watchdogReset:1;         // 4 - 给FPGA的看门狗复位 两个情况: 1)上电初始的5秒或单元自检时直接给复位，使得F48不报出；2)报出F48故障，故障自复位
	
	Uint16 rsvd:11;					// 5-15 保留
};

union AUX_CMD_FOR_FPGA
{
	Uint16 all;
    struct AUX_CMD_FOR_FPGA_BITS bit;
};
extern union AUX_CMD_FOR_FPGA auxCmdForFpga;

struct SYS_CONFIRM_PARA_BITS
{
    Uint16 highSwitchCloseEnable:1; // 0 合闸允许确认

    Uint16 rsvd:15;                 // 1-15
};

union SYS_CONFIRM_PARA
{
    Uint16 all;
    struct SYS_CONFIRM_PARA_BITS bit;
};
extern union SYS_CONFIRM_PARA sysConfirmPara;

#define GET16BIT(in, bit) (((in) & (0x01U<<(bit))) >> (bit))    /*读取in的bit位*/
#define GET32BIT(in, bit) (((in) & (0x01UL<<(bit))) >> (bit))   /*读取in的bit位*/

extern u16 FAN_ON;    // 风机开启标记

#endif











