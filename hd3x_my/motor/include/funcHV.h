
#ifndef __F_FUNC_HV_H__
#define __F_FUNC_HV_H__

// ----------------函数声明---------------------------------------------- 
extern void SystemPowerDeal(void);
// ----------------函数声明结束------------------------------------------
#define NORMAL_HIGH_VOLTAGE         funcCode.code.DriveRatingPara.ratingInVol

#define HV_ON_JUDGMENT_THRESHOLD    funcCode.code.volModify
#define HV_OFF_JUDGMENT_THRESHOLD   funcCode.code.UnderVol // ((Uint32)funcCode.code.volModify * funcCode.code.volModify / 100) // LS_20220620

#define CONTROL_POWER_WAIT_TIME     5000        // 5S	控制电上电延时 
//----------------------------------------// 
struct POWER_STATUS_BITS
{
    Uint16 powerOffFlag:1;          // 0 用于断电瞬间记录一次运行状态
    Uint16 bUvReset:1;              // 1 用于高压上电后的复位
    Uint16 bSecondCellCheck:1;      // 2 短时重新得电 不检测igbt和接触器
    Uint16 bpowerDeclined:1;        // 3 输入电压跌落标记

    Uint16 bHighVoltage:1;          // 4 高压电源在线 凯撒根据母线电压计算
    Uint16 udcCreatOT:1;			// 5 母线电压建立超时
    Uint16 bUdcOff:1;			    // 6 母线电压掉线
    Uint16 rechargeEnable:1;        // 7 低压穿越预充电阻接入指示 0 - 电阻接入主回路  1 - 正常

    Uint16 HiVoltAtTestMode:1;      // 8 测试模式上高压 // LS_20240229
    Uint16 rsvd:7;                 	// 9-15 
};
union POWER_STATUS
{
    Uint16 all;
    struct  POWER_STATUS_BITS bit;
};
extern union POWER_STATUS powerStatus;

extern Uint32 uvUdc; 

enum VOLTAGE_STEP
{
    VOLTAGE_STEP_NORMAL,        // 输入电压在85%~120%
    VOLTAGE_STEP_DERATE_LOW,    // 输入电压在63.75%~85%
    VOLTAGE_STEP_DERATE_HIGH,   // 输入电压在20%~63.75%
    VOLTAGE_STEP_DERATE_MOST,   // 输入电压在0%~20%
    VOLTAGE_STEP_HIGH_OVER      // 输入电压在120%~130%
};
extern enum VOLTAGE_STEP volChangeStep;

//======================合闸延时时间计时相关的处理====================//
typedef struct
{                                          // bits  description
    Uint16 highSwitchCloseDelayFlag:1; // 0 合闸允许开启标志
    Uint16 rsvd1:15;                    // 1-15 保留
}HIGH_SWITCH_CLOSE_BITS;

typedef union
{
    Uint16                all; 
    HIGH_SWITCH_CLOSE_BITS    bit;
}HIGH_SWITCH_CLOSE_WORD;

typedef struct
{
    HIGH_SWITCH_CLOSE_WORD highswitchcloseWord;
    Uint16  highSwitchCloseDelayTime;          // 合闸延时时时间
    Uint16  highSwitchCloseDelayCounter;       /// 合闸延时时间计时
    
}HIGH_SWITCH_CLOSE_CTRL;
extern HIGH_SWITCH_CLOSE_CTRL highswitchcloseCtrl;

#endif











