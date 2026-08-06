
#ifndef __F_IO_H__
#define __F_IO_H__


#include "funcCode.h"
//#include "f_funcCode.h"
/*
#define	AI_NUMBER		2			//AI端子个数
#define DSP_AI_NUMBER   2           //DSP控制AI端子个数
#define PLC_AI_NUMBER   2           //PLC AI端子个数
       	         		 			
#define	AO_NUMBER		2			//AO端子个数
#define DSP_AO_NUMBER   3           //DSP控制AO 端子个数
#define	PLC_AO_NUMBER	4           //PLC AO 端子个数
*/
/*
#define PLC_AI_NUMBER   2           //PLC AI端子个数
#define DSP_AO_NUMBER   3           //DSP控制AO 端子个数
#define DSP_AI_NUMBER   2           //DSP控制AI端子个数
#define PLC_AI_NUMBER   2           //PLC AI端子个数
#define	PLC_AO_NUMBER	4           //PLC AO 端子个数
*/
// ----------------函数声明----------------------------------------------
extern void DiDeal(void);
extern void DoDeal(void);
extern void AiCal(void);
extern void AiCalII(void);
extern void AoCal(void);
extern void AoCalII(void);
//extern void PulseInCalc(void);
extern void PulseInSample(void);
extern void PulseOutCalc(void);
extern void Delay(u16 delayNum);
//extern void SynTransferContactorDeal(void);
extern void ValidMotorProcess(void);
extern void MotorStatusIndicate(void);
extern void HighSwitchCloseEnable(void);
extern void HighSwitchOffDeal(void);

extern Uint16 cfGroup[];
// ----------------函数声明结束------------------------------------------
//#define HDO_PRD  TIM5->ARR
//#define HDO_CMP  TIM5->CCR1
///#define HDO_CTR  TIM5->CNT      
#define PULSE_OUT_CTR_PERIOD       (0xFFFF - 2)
/*
// IO板电源异常
#define IO_POWER_ERR        ((GPIOB->IDR&0x0002) == 0)      // PB1

#define IO_SPI_MISO         ((GPIOA->IDR&0x0080) == 0)
#define IO_SPI_MOSI_ON      GPIO_ResetBits(GPIOD, GPIO_Pin_12)
#define IO_SPI_MOSI_OFF     GPIO_SetBits(GPIOD, GPIO_Pin_12)
#define IO_SPI_CLK_ON	    GPIO_SetBits(GPIOG, GPIO_Pin_13)
#define IO_SPI_CLK_OFF	    GPIO_ResetBits(GPIOG, GPIO_Pin_13)
#define IO_SPI_SHL_ON	    GPIO_SetBits(GPIOG, GPIO_Pin_14)
#define IO_SPI_SHL_OFF	    GPIO_ResetBits(GPIOG, GPIO_Pin_14)

#define ARM_ENOC			GPIO_SetBits(GPIOD, GPIO_Pin_12)
#define IOC_RESET_ENABLE	GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define IOC_RESET_DISABLE	GPIO_SetBits(GPIOB, GPIO_Pin_7)

#define OX1_OFF  GPIO_SetBits(GPIOD, GPIO_Pin_11)
#define OX1_ON  GPIO_ResetBits(GPIOD, GPIO_Pin_11)

#define OX4_OFF  GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define OX4_ON  GPIO_ResetBits(GPIOA, GPIO_Pin_0)

#define SPI_OUT_HIGHZ_ON    GPIO_SetBits(GPIOG, GPIO_Pin_6)
#define SPI_OUT_HIGHZ_OFF   GPIO_ResetBits(GPIOG, GPIO_Pin_6)
//#define X_IN_1	((GPIOG->IDR&0x0800) == 0)
//#define X_IN_18	((GPIOA->IDR&0x0100) == 0)
*/
//#define X_IN_1	    (GpioDataRegs.GPBDAT.bit.GPIO48)
//#define X_IN_1	    (cfGroup[0])
//#define X_IN_18	((GPIOA->IDR&0x0100) == 0)
//======================================================================
// AO,FMP输出选择
#define AO_FMP_FUNC_NUMBER          13  // AO设定的个数
#define AO_FMP_FUNC_FRQ_SET         0   // 运行频率
#define AO_FMP_FUNC_FRQ_AIM         1   // 设定频率
#define AO_FMP_FUNC_OUT_CURRENT     2   // 输出电流
#define AO_FMP_FUNC_OUT_TORQUE      3   // 输出转矩
#define AO_FMP_FUNC_OUT_POWER       4   // 输出功率
#define AO_FMP_FUNC_OUT_VOLTAGE     5   // 输出电压
#define AO_FMP_FUNC_PULSE_IN        6   // PULSE脉冲输入
#define AO_FMP_FUNC_AI1             7   // AI1
#define AO_FMP_FUNC_AI2             8   // AI2
#define AO_FMP_FUNC_AI3             9   // AI3(扩展卡)
#define AO_FMP_FUNC_AI4             10   // AI4
#define AO_FMP_FUNC_COUNTER         11   // 计数值
#define AO_FMP_FUNC_COMM            12   // 通讯控制输出
#define AO_FMP_FUNC_SPEED           13   // 输出转速
#define AO_FMP_FUNC_OUT_CURRENT_1   14   // 输出电流  对应0~1000A
#define AO_FMP_FUNC_OUT_VOLTAGE_1   15   // 输出电压  对应0~1000V
#define AO_FMP_FUNC_ID_CUR          16   // 励磁电流IdRef 
#define AO_FMP_FUNC_IN_VOLTAGE      17   // 输入电压
#define AO_FMP_FUNC_IN_CURRENT      18   // 输入电流


//=====================================================================
// DI端子定义
#define DI_FUNC_NUMBER              34  // DI的功能选择数量，[0, DI_FUNC_NUMBER-1]
#define CLOSED_FUNC_LIMIT           1000 // 常开常闭互切

struct DI_FUNC1_BITS
{
    Uint16 noFunc:1;                // 0: 无功能
    Uint16 fwd:1;                   // 1: 正转运行FWD
    Uint16 rev:1;                   // 2: 反转运行REV
    Uint16 tripleLineCtrl:1;        // 3: 三线式运行控制
    Uint16 fwdJog:1;                // 4: 正向点动
    Uint16 revJog:1;                // 5: 反向点动
    Uint16 up:1;                    // 6: 端子UP
    Uint16 down:1;                  // 7: 端子DOWN

    Uint16 closePwm:1;              // 8:    自由停车，即封锁PWM输出
    Uint16 errorReset:1;            // 9:    故障复位
    Uint16 runPause:1;              // 10:   运行暂停
    Uint16 externalErrIn:1;         // 11:   外部故障输入
    Uint16 multiSet:4;              // 15:12 多段指令端子4，3，2，1

    Uint16 accDecTimeSrc:2;         // 17:16 加减速时间选择端子2，1
    Uint16 frqSrcSwitch:1;          // 18    频率源切换
    Uint16 clearUpDownFrq:1;        // 19    UP/DOWN设定清零
    Uint16 localOrRemote:1;         // 20    本地/远程
    Uint16 forbidAccDecSpd:1;       // 21    加减速禁止
    Uint16 pidPause:1;              // 22    PID暂停
    Uint16 resetPLC:1;              // 23    PLC状态复位

    Uint16 overTempAlarmOrErr:1;    // 24    过温报警(1代机告警，2代机过温)
    Uint16 overTempErr:1;           // 25    过温故障
    Uint16 doorLimit:1;             // 26    门限位
    Uint16 windMotorFdb:1;          // 27    变压器柜顶风机反馈
    Uint16 remote1OrRemote2:1;      // 28    远程1远程2

    Uint16 forbidTorqueCtrl:1;      // 29    转矩控制禁止
    Uint16 pulseIn:1;               // 30    脉冲输入
    Uint16 emgStop:1;               // 31    急停


};

union DI_FUNC1
{
    Uint32 all;
    struct DI_FUNC1_BITS bit;
};

struct DI_FUNC2_BITS
{

    Uint16 brake:1;                     // 32+0: 直流制动
    Uint16 powerOK:1;                   // 32+1: 控制电源掉电
    Uint16 frqOk:1;                     // 32+2: 频率设定起效端子
    Uint16 pidDirRev:1;                 // 32+3: PID作用方向取反端子
    Uint16 brakeFdb:1;                  // 32+4: 抱闸反馈
    Uint16 emgDisjunction:1;            // 32+5: 紧急分段
    Uint16 pidPauseI:1;                 // 32+6: PID积分暂停端子
    Uint16 frqXSrc2Preset:1;            // 32+7: 主频率源X与预置频率切换    
    Uint16 frqYSrc2Preset:1;            // 32+8: 辅频率源Y与预置频率切换
   
    Uint16 motorSnDi1:1;                // 41:  电机1选择端子   选择了该端子，电机选择功能码无效
    Uint16 motorSnDi2:1;                // 42:  电机2选择端子   选择了该端子，电机选择功能码无效
    Uint16 pidChg:1;                    // 43:  PID参数切换端子。0-PID1, 1-PID2

    Uint16 userError1:1;                // 44:  用户自定义故障1
    Uint16 userError2:1;                // 45:  用户自定义故障2
    Uint16 SpdTorqSwitch:1;             // 46:  速度控制/转矩控制切换
    Uint16 emergencyStop:1;             // 47:  紧急停车
    Uint16 invEnable:1;                 // 48: 变频器使能信号
    Uint16 decBrake:1;                  // 49: 减速直流制动
    Uint16 inletContactor1Fdb:1;        // 50: 旁路柜1进线接触器反馈
    Uint16 outletContactor1Fdb:1;       // 51: 旁路柜1出线接触器反馈
    Uint16 lineContactor1Fdb:1;         // 52: 旁路柜1工频接触器反馈


    Uint16 invContactFdb:1;             // 53 变频接触器反馈
    Uint16 netContactFdb:1;             // 54 工频接触器反馈
    Uint16 ScrErr:1;                    // 55 晶闸管故障 // LS_20220429
    
    Uint16 excitReady:1;                // 56: 励磁柜就绪
    Uint16 excitErr:1;                  // 57: 励磁柜故障

    Uint16 fwd2:1;                      // 58: 正转运行FWD2
    Uint16 rev2:1;                      // 59: 反转运行REV2
    Uint16 tripleLineCtrl2:1;           // 60: 三线式运行控制2

    Uint16 preCharge:1;                 // 61 预充命令
    Uint16 volRegulatorFault:1;         // 62 预充调压器故障
    
    Uint16 crossCurrentWindMotorFdb:1;  // 63 横流风机报警

};

union DI_FUNC2
{
    Uint32 all; // LS_20220509
    struct DI_FUNC2_BITS bit;
};

struct DI_FUNC3_BITS
{
    Uint16 OutContactFdb:1;             // 64: 输出接触器反馈 // LS_20220805
    Uint16 prechargeLVContactFdb:1;     // 65: 功率控制器接触器反馈
    Uint16 inletContactor2Fdb:1;        // 66: 旁路柜2进线接触器反馈
    Uint16 outletContactor2Fdb:1;       // 67: 旁路柜2出线接触器反馈
    Uint16 lineContactor2Fdb:1;         // 68: 旁路柜2工频接触器反馈
    Uint16 prechargeContactorFdb:1;     // 69: 预充接触器反馈
    Uint16 prechargeLvBypConFdb:1;      // 70: 旁路低压预充电阻接触器反馈
    Uint16 processRunEnable:1;          // 71: 工艺准备就绪
    Uint16 waterCoolingSysErr:1;        // 72: 水冷系统故障
    Uint16 breakerFdb:1;                // 73: 进线断路器反馈
    Uint16 upTransferAutoEnable:1;      // 74: 自动上切使能
    Uint16 upTransferCmd:1;             // 75: 同步上切指令  变频切工频指令
    Uint16 downTransferCmd:1;           // 76: 同步下切指令  工频切变频指令
    Uint16 dualInverters:1;             // 77: 双机状态  1:两台变频器 (双机并联专用)
    //Uint16 invContactManualControl:1;   // 78: 用以判断是否接触器故障 0 自动控制 判断
    Uint16 bypassResPrechargeFdb2:1;    // 78:预充电阻旁路接触器反馈2
    Uint16 reactorErr:1;                // 79: 电抗器过温故障
    
    Uint16 reactorFdb:1;                // 80: 电抗器接触器反馈
    Uint16 bypassResPrechargeFdb:1;     // 81: 预充电阻旁路接触器反馈1
    Uint16 excitRunStatus:1;            // 82: 励磁柜运行反馈
    Uint16 bypassCmd:1;                 // 83: 旁路柜上切指令
    Uint16 dischargeCmd:1;				// 84: 放电命令
    Uint16 line2InvCmd:1;               // 85: 旁路柜下切指令
    Uint16 windMotor1Fdb:1;             // 86: 风机2反馈		// 位置不能随便移动
    Uint16 windMotor2Fdb:1;             // 87: 风机3反馈
    Uint16 windMotor3Fdb:1;             // 88: 风机4反馈
    Uint16 windMotor4Fdb:1;             // 89: 风机5反馈
    Uint16 windMotor5Fdb:1;             // 90: 风机6反馈
    Uint16 windMotor6Fdb:1;             // 91: 风机7反馈
    Uint16 preChargeSwitchOff:1;        // 92: 预充分闸命令
    Uint16 motorSnDi3:1;                // 93: 电机3选择端子   选择了该端子，电机选择功能码无效
    Uint16 motorSnDi4:1;                // 94: 电机4选择端子   选择了该端子，电机选择功能码无效
    Uint16 invContact2Fdb:1;            // 95: 2#变频接触器反馈
};

union DI_FUNC3
{
    Uint32 all; // LS_20220509
    struct DI_FUNC3_BITS bit;
};

struct DI_FUNC4_BITS
{
    Uint16 netContact2Fdb:1;            // 96  2#工频接触器反馈 
    Uint16 invContact3Fdb:1;            // 97  3#变频接触器反馈
    Uint16 netContact3Fdb:1;            // 98  3#工频接触器反馈
    Uint16 invContact4Fdb:1;            // 99  4#变频接触器反馈
    Uint16 netContact4Fdb:1;            // 100 4#工频接触器反馈 
    Uint16 softStart1Run:1;             // 101 软启1启动
    Uint16 softStart2Run:1;             // 102 软启2启动
    Uint16 softStart3Run:1;             // 103 软启3启动
    Uint16 softStart4Run:1;             // 104 软启4启动
    Uint16 softStart1Stop:1;            // 105 软启1停机
    Uint16 softStart2Stop:1;            // 106 软启2停机
    Uint16 softStart3Stop:1;            // 107 软启3停机
    Uint16 softStart4Stop:1;            // 108 软启4停机
    Uint16 excitCloseEnable:1;          // 109 励磁合闸允许
    Uint16 bypCanbinet1Close:1;         // 110 旁路柜1变频侧合闸--KM1 KM2合闸
    Uint16 bypCanbinet2Close:1;         // 111 旁路柜2变频侧合闸--KM1 KM2合闸
    Uint16 line2InvCmd2:1;              // 112 旁路柜下切指令
    Uint16 earthKnifeSwitchFdb:1;       // 113 接地刀闸反馈
    Uint16 heatDehumidifyFdb:1;         // 114 加热除湿反馈
    Uint16 transformerOTAlarm:1;        // 115 隔离变压器过温报警
    Uint16 transformerOTError:1;        // 116 隔离变压器过温故障
    Uint16 transformerTopFanStatus:1;   // 117 隔离变压器柜顶风机电源状态
    Uint16 transformerFlowFanStatus:1;  // 118 隔离变压器横流风机电源状态
    Uint16 transformerSwitchStatus:1;   // 119 隔离变压器门限位开关状态
    Uint16 powerOutContactFdb:1;        // 120 输出接触器反馈
    Uint16 powerOutPreContactFdb:1;     // 121 输出预充接触器反馈
    Uint16 powerOutContactClose:1;      // 122 输出接触器合闸
    Uint16 powerFirstOutContactFdb1:1;  // 123 一级输出接触器状态反馈1
    Uint16 powerOutPreCharOTError:1;    // 124 输出预充电阻过温故障
    Uint16 powerOutPreCharOTAlarm:1;    // 125 输出预充电阻过温告警
    Uint16 powerFirstOutContactFdb2:1;  // 126 一级输出接触器状态反馈2
    Uint16 powerOutPreContactCmd:1;     // 127: 输出预充接触器合闸
};

union DI_FUNC4
{
    Uint32 all; // LS_20220509
    struct DI_FUNC4_BITS bit;
};

struct DI_FUNC5_BITS
{
    Uint16 heatFanFdb:1;                // 128  散热风机反馈
    Uint16 fcbCmd:1;                    // 129  FCB快速制动命令
    Uint16 fcbKnifeSwFdb:1;             // 130  FCB制动柜刀闸反馈
    Uint16 fcbContactorFdb:1;           // 131  FCB制动柜接触器反馈
    Uint16 fcbFan:1;                    // 132  FCB制动柜风机反馈
    Uint16 fcbOvTemp:1;                 // 133  FCB制动柜电阻超温故障
    Uint16 motorOverTemp:1;             // 134  电机超温反馈
    
    Uint16 cabinetPowerOn:1;            // 135 开关柜电源反馈
    Uint16 powerOutPreCtrlPowerFdb:1;   // 136  输出预充控制电状态反馈
    Uint16 powerOutLCLOTError:1;        // 137  岸电输出滤波柜电抗器过温故障 
    Uint16 powerOutLCLOTAlarm:1;        // 138  岸电输出滤波柜电抗器过温告警
    Uint16 powerrsvd2:2;                // 139 -140岸电保留
    Uint16 rsvd3:16;                    // 141-159  预留
};

union DI_FUNC5
{
    Uint32 all; // LS_20220509
    struct DI_FUNC5_BITS bit;
};

struct DI_FUNC
{
    union DI_FUNC1 f1;
    union DI_FUNC2 f2;
    union DI_FUNC3 f3;
    union DI_FUNC4 f4;
    union DI_FUNC5 f5;
};
extern struct DI_FUNC diFunc, diFuncSel;

//======================================================================
// DO 输出选择
#define DO_FUNC_NUMBER               65  // DO的功能选择数量, [0, DO_FUNC_NUMBER-1]
struct DO_FUNC1_BITS
{
    
    Uint16 noFunc:1;                // 0: 无功能  
    Uint16 run:1;                   // 1: 变频器运行中
    Uint16 error:1;                 // 2: 故障输出
    Uint16 frqFdtArrive:1;          // 3: 频率水平检测FDT到达
    Uint16 frqArrive:1;             // 4: 频率到达
    Uint16 zeroSpeedRun:1;          // 5: 零速运行中
    Uint16 motorPreOl:1;            // 6: 电机过载预报警
    Uint16 inverterPreOl:1;         // 7: 变频器过载预报警
    
    Uint16 counterSetArrive:1;      // 8:    设定计数脉冲值到达
    Uint16 counterPointArrive:1;    // 9:    指定计数脉冲值到达
    Uint16 lengthArrive:1;          // 10:   长度到达
    Uint16 plcEndLoop:1;            // 11    PLC循环完成
    Uint16 runTimeArrive:1;         // 12    运行时间到达
    Uint16 frqLimit:1;              // 13    频率限定中
    Uint16 torqueLimit:1;           // 14    转矩限定中
    Uint16 runReadyOk:1;            // 15    运行准备就绪
    
    Uint16 ai1GreaterThanAi2:1;     // 16    AI1 > AI2
    Uint16 upperFrqArrive:1;        // 17    上限频率到达
    Uint16 lowerFrqArrive:1;        // 18    下限频率到达
    Uint16 uv:1;                    // 19    欠压状态输出
    Uint16 commCtrl:1;              // 20    通讯控制
    Uint16 pcOk:1;                  // 21    定位完成
    Uint16 pcNear:1;                // 22    定位接近
    Uint16 zeroSpeedRun1:1;         // 23    零速运行中(停机有效)
    Uint16 powerUpTimeArrive:1;     // 24    上电时间到达
    Uint16 frqFdtArrive1:1;         // 25:   频率水平检测FDT1到达
    Uint16 frqArrive1:1;            // 26:   频率到达1
    Uint16 frqArrive2:1;            // 27:   频率到达2
    Uint16 currentArrive1:1;        // 28:   电流到达1
    Uint16 currentArrive2:1;        // 29:   电流到达2
    Uint16 setTimeArrive:1;         // 30:   定时到达
    Uint16 ai1limit:1;              // 31:   AI1输入超出上下限
};

union DO_FUNC1
{
    Uint32 all; // LS_20220509
    struct DO_FUNC1_BITS bit; 
};

struct DO_FUNC2_BITS
{
    
    Uint16 loseLoad:1;                // 32+0: 掉载中   
    Uint16 speedDir:1;                // 32+1: 转速方向
    Uint16 oCurrent:1;                // 32+2: 零电流状态输出
    Uint16 tempArrive:1;              // 32+3: 模块温度到达    
    Uint16 softOc:1;                  // 32+4: 软件过流输出
    
    Uint16 lowerFrqArrive:1;            // 32+5: 下限频率到达(与运行有关)
    Uint16 brakeOpen:1;                 // 32+6: 闸输出  释放抱闸
    Uint16 motorForeOT:1;               // 32+7: 电机过温预报警
    Uint16 highSwitchCloseEnable:1;     // 32+8: 高压合闸允许
    Uint16 highUrgencyDisjuction:1;     // 32+9: 高压跳闸
    
    Uint16 invContactOutput:1;          // +10 42: 变频器运行接触器
    Uint16 OutContact:1;                // +11 43: 输出接触器 // LS_20220805
    Uint16 MVPower:1;                   // +12 44: 高压电源正常
    Uint16 alarm:1;                     // +13 45: 系统报警输出   轻故障报警
    Uint16 HMIReset:1;                  // +14 46: HMI复位输出
    
    Uint16 outletContactorOff:1;        // +15 47: 旁路柜出线接触器分闸
    Uint16 rsvd:1;                      // +16 48: 留
    Uint16 excitCmd:1;                  // +17 49: 励磁柜投励命令

    Uint16 DSPControl1:1;               // 50
    Uint16 DSPControl2:1;               // 51

    Uint16 invContactOn:1;              // 52 变频接触器合闸    脉冲式
    Uint16 invContactOff:1;             // 53 变频接触器分闸
    Uint16 netContactOn:1;              // 54 工频接触器合闸
    Uint16 netContactOff:1;             // 55 工频接触器分闸
    
    Uint16 rsvd11:2;                    // 56 57 保留

    Uint16 volRegulatorRunCmd:1;        // 58 功率控制器运行命令    预充命令
    Uint16 prechargeLVContactOn:1;      // 59 功率控制器接触器控制  预充接触器
    Uint16 prechargeHVContOn:1;         // 60 预充高压接触器合闸

    Uint16 lineContactor1Close:1;       // 61 电机1自动切工频  工频接触器合闸输出,自动旁路切换接触器
    Uint16 windMotorAutoRun:1;          // 62 风机自动运行
    Uint16 prechargeHVContOff:1;        // 63 预充接触器分闸  预充完成后,真空接触器断开

};
union DO_FUNC2
{
    Uint32 all; // LS_20220509
    struct DO_FUNC2_BITS bit; 
};

struct DO_FUNC3_BITS
{
    Uint16 highUrgencyDisjuction2:1;    // 64+0 64: 开关柜2高压跳闸 
    Uint16 lineContactor2Close:1;       // 64+1 65: 电机2自动切工频
    Uint16 invStatus:1;                 // 64+2 66: 电机1变频指示
    Uint16 netStatus:1;                 // 64+3 67: 电机1工频指示

    Uint16 upTransferEnable:1;          // 68: 上切就绪
    Uint16 downTransferEnable:1;        // 69: 下切就绪
    Uint16 netInvContactUnfasten:1;     // 70: 同步切换接触器解锁 工变频接触器解锁
    Uint16 upTransferStatus:1;          // 71: 上切过程指示
    Uint16 downTransferStatus:1;        // 72: 下切过程指示
    Uint16 masterOffLine:1;             // 73: 主机掉线--------------双机并联专用
    Uint16 otherInvContactOff:1;        // 74: 断其它的变频接触器----双机并联专用

    Uint16 heater:1;                    // 75: 加热器开启
    Uint16 resBypassContactorOff:1;     // 76: 预充电阻旁路接触器分闸 一次预充分闸
    Uint16 resBypassContactorOn:1;      // 77: 预充电阻旁路接触器合闸 一次预充合闸
    Uint16 reactorBypassContactOff:1;   // 78: 电抗器旁路分闸 即将电抗器接入，仅限下切时允许
    Uint16 reactorBypassContactOn:1;    // 79: 电抗器旁路合闸 即旁路电抗器

    Uint16 motor2Inv:1;    				// 80: 电机2变频指示
    Uint16 motor2Net:1;    				// 81: 电机2工频指示
    Uint16 remote1OrRemote2:1;          // 82: 远程1/远程2指示 
    Uint16 highSwitchCloseEnable2:1;    // 83: 开关柜2合闸允许
    Uint16 specifiedFault:1;            // 84: 指定故障输出
    Uint16 doorOpenLightEnable:1;		// 85: 开门允许灯
    Uint16 dischargeStatus:1;           // 86: 放电指示
    Uint16 outletContactor1On:1;        // 87: 旁路柜1出线接触器合闸
    Uint16 inletContactorOff:1;         // 88: 旁路柜进线接触器分闸
    Uint16 lineContactor1Off:1;         // 89: 旁路柜1工频接触器分闸
    Uint16 outletContactor2On:1;        // 90: 旁路柜2出线接触器合闸
    Uint16 lineContactor2Off:1;         // 91: 旁路柜2工频接触器分闸

    Uint16 invContact2On:1;             // 92 2#变频接触器合闸
    Uint16 invContact2Off:1;            // 93 2#变频接触器分闸
    Uint16 netContact2On:1;             // 94 2#工频接触器合闸
    Uint16 netContact2Off:1;            // 95 2#工频接触器分闸
};

union DO_FUNC3
{
    Uint32 all; // LS_20220509
    struct DO_FUNC3_BITS bit; 
};

struct DO_FUNC4_BITS
{
    Uint16 invContact3On:1;             // 96  3#变频接触器合闸
    Uint16 invContact3Off:1;            // 97  3#变频接触器分闸
    Uint16 netContact3On:1;             // 98  3#工频接触器合闸
    Uint16 netContact3Off:1;            // 99  3#工频接触器分闸
    Uint16 invContact4On:1;             // 100 4#变频接触器合闸
    Uint16 invContact4Off:1;            // 101 4#变频接触器分闸
    Uint16 netContact4On:1;             // 102 4#工频接触器合闸
    Uint16 netContact4Off:1;            // 103 4#工频接触器分闸
    Uint16 netInvContactUnfasten2:1;    // 104 同步切换接触器解锁2
    Uint16 netInvContactUnfasten3:1;    // 105 同步切换接触器解锁3
    Uint16 netInvContactUnfasten4:1;    // 106 同步切换接触器解锁4
    Uint16 motor3Inv:1;                 // 107 电机3变频指示
    Uint16 motor3Net:1;                 // 108 电机3工频指示
    Uint16 motor4Inv:1;                 // 109 电机4变频指示
    Uint16 motor4Net:1;                 // 110 电机4工频指示

    Uint16 excitCloseOn:1;              // 111 励磁合闸
    Uint16 inletContactor1On:1;         // 112 旁路柜1进线接触器合闸
    Uint16 inletContactor2On:1;         // 113 旁路柜2进线接触器合闸
    Uint16 itFrqControl:1;              // 114 抱闸控制
    Uint16 outContactOff:1;             // 115 输出接触器分闸 - 岸用电源
    Uint16 HVRelayOn:1;                 // 116 高压继电器
    Uint16 outContactOn:1;              // 117 输出接触器合闸 - 岸用电源
    Uint16 outPreContactOff:1;          // 118 输出预充接触器分闸 - 岸用电源
    Uint16 outPreContactOn:1;           // 119 输出预充接触器合闸 - 岸用电源

    Uint16 motorFanRun:1;               // 120 电机散热风机控制

    Uint16 fcbStatusDisp:1;             // 121 FCB制动状态指示
    Uint16 dualFrqBrake:1;              // 122 双频制动状态指示
    Uint16 fcbContactorOn:1;            // 123 制动柜接触器合闸
    Uint16 fcbContactorOff:1;           // 124 制动柜接触器分闸
    Uint16 lvBypResContOn:1;            // 125 旁路低压预充电阻接触器控制

    Uint16 rsvdf4:2;                    // 126 - 127 保留
};

union DO_FUNC4
{
    Uint32 all; // LS_20220509
    struct DO_FUNC4_BITS bit; 
};

struct DO_FUNC
{
    union DO_FUNC1 f1;
    union DO_FUNC2 f2;
    union DO_FUNC3 f3;
    union DO_FUNC4 f4;
};

extern struct DO_FUNC doFunc; 

//--------------模拟量设定------------//
struct AI_DEAL
{
    Uint16 sample;          // 采样值，Q16
    
    int16 voltageOrigin;    // 校正前电压
    int16 voltage;          // 校正后电压
    
    int16 set;              // AI设定
};
extern struct AI_DEAL aiDeal[DSP_AI_NUMBER];

// 工变频接触器相关处理
struct RELAY_STATUS_BITS
{                                   // bits  description
    Uint16 invContactOn:1;          // 0 变频接触器输出 脉冲
    Uint16 invContactOff:1;         // 1 变频接触器断开
    Uint16 netContactOn:1;          // 2 工频接触器输出
    Uint16 netContactOff:1;         // 3 工频接触器断开
    Uint16 invContact:1;            // 4 变频接触器控制 电平
    Uint16 netContact:1;            // 5 工频接触器控制

    Uint16 invContactFdbAlarm:1;    // 6 变频接触器反馈报警
    Uint16 invContactFdbErr:1;      // 7 变频接触器反馈故障
    Uint16 netContactFdbAlarm:1;    // 8 工频接触器反馈报警
    Uint16 invContactStatus:1;      // 9 变频接触器目前状态
    Uint16 netContactStatus:1;      // 10 工频接触器目前状态

    Uint16 contactUnfasten:1;       // 11 接触器解锁
    Uint16 invContactOpenCmd:1;     // 12 切换电机时 变频接触器分闸
    Uint16 reactorContactStatus:1;  // 13 电抗器旁路接触器目前状态

    Uint16 rsvd:2;                  // 14-15 
};

union RELAY_STATUS 
{
   Uint16                   all;
   struct RELAY_STATUS_BITS   bit;
};

extern union RELAY_STATUS relayStatus;

//
//
typedef struct
{
    Uint16 humidityFlag:1;             // BIT00-01 除湿标志
    Uint16 rsvd1:15;                   // 保留
}HUMIDITY_CTRL_BITS;

typedef union
{
    Uint16                all; 
    HUMIDITY_CTRL_BITS    bit;
}HUMIDITY_CTRL_WORD;

typedef struct
{
    HUMIDITY_CTRL_WORD humidityCtrlWord;
    Uint16  humidityTime;          // 总时间
    Uint16  humidityCounter;       // 除湿计时
    
}HUMIDITY_CTRL;
extern HUMIDITY_CTRL humidityCtrl;
//======================================================================

#define CONTACT_OFF_STATUS  0
#define CONTACT_ON_STATUS   1

#define LOCK_PHASE_NO_OPER  0   // 无操作
#define LOCK_PHASE_SUCCESS  1   // 锁相成功
#define LOCK_PHASE_FAIL     2   // 锁相失败

#define PLC_AO_GROUP	4
#define PLC_AI_GROUP	4
#define PLC_TEMP_GROUP              4   // 1个4PT的温度拓展模块具备有4个通道的温度采样口

#define RELAY_DELAY_TIME 500

extern Uint16 plcDiData;
extern Uint16 plcDoData;
extern Uint16 plcAoData[PLC_AO_GROUP];
extern Uint16 plcAoDisp[PLC_AO_GROUP];
extern int16 plcTempData[PLC_TEMP_GROUP];
extern Uint16 aoDisp[AO_NUMBER+DSP_AO_NUMBER];
extern Uint16 dspAoCoef[DSP_AO_NUMBER];

extern Uint16 diPhyStatus, diPhyStatusSub, doPhyStatus, doPhyStatusSub, doPhyStatusSub2;
extern int16 pulseInSet;
extern Uint16 errAutoRstNum;
extern Uint16 spFaAutoRstNum;
extern Uint16 bypassCabinetSel;
///extern Uint16 pulseInFrqDisp;
extern Uint32 pulseInFrq;

#define DELTA_HUMIDITY_NORMAL 10

#endif











