//----------------------------------------------------------//
// File Name		: .c	
// Description		: 系统中辅助函数处理
// Time				: 2011.03.02
// Editor			: xxxxx
// Co.				: xxxxx
//----------------------------------------------------------//

#ifndef F_PRECHARGE_H
#define F_PRECHARGE_H

// ----------------函数声明----------------------------------------------
extern void PrechargeStatusHandle(void);
// ----------------函数声明结束------------------------------------------

// 预充方式
#define PRECHARGE_CONTACTOR_PARALLELING_MODE    1   // 预充电阻和预充接触器串联，之后再和旁路接触器并联 此种可以分预充接触器
#define PRECHARGE_CONTACTOR_SERIES_MODE         2   // 预充电阻和旁路接触器并联之后，再和前级的预充接触器串联此种不可分预充接触器
#define PRECHARGE_BYPASS_CONTACTOR_ONLY_MODE    3   // 拓扑同方式1 预充接触器由电气合闸，反馈有效之后延时3s进行旁路处理
#define PRECHARGE_CONTACTOR_SERIES_AUTO_MODE    4   // 拓扑同方式1 自动预充 // LS_20231205

#define PRECHARGE_SEC_VOLT_REGULATOR_MODE       1   // HD92-R项目 副边调压器预充
#define PRECHARGE_SEC_RES_MODE                  2   // 电阻二次预充

#define PRECHARGE_UDC_LV_RES_MODE               1   // 凯撒四象限项目 先低压电阻预充后再合主回路

struct PRECHARGE_FLAG_BITS
{
    Uint16 prechageCmd:1;           // 0 启动接触器输出
    Uint16 LVContactorOn:1;         // 1 低压预充接触器
    Uint16 HVRelay:1;				// 2 高压继电器
    Uint16 volRegulatorRunCmd:1;    // 3 调压器运行命令
    
    Uint16 HVContactorOn:1;         // 4 合闸允许   预充合闸
    Uint16 HVContactorOff:1;        // 5 预充高压接触器分闸
    Uint16 change:1;                // 6 在投切过程不报故障
    Uint16 resBypassContactorOn:1;  // 7 一次侧预充电阻旁路接触器合闸 
    
    Uint16 resBypassContactorOff:1; // 8 一次侧预充电阻旁路接触器分闸
    Uint16 preCharging:1;           // 9 预充过程中
    Uint16 resBypassContStatus:1;	// 10 预充电阻旁路接触器状态
    Uint16 prechargeHVContStatus:1; // 11 预充接触器状态
    Uint16 prechargeLVContactStatus:1;  // 12 低压预充接触器状态
    Uint16 prechargeLvRes:1;        // 13 低压电阻预充状态
    Uint16 lvBypResContOn:1;        // 14 低压预充电阻旁路合闸
    Uint16 prechargeLvBypConStatus:1;   // 15 低压旁路电阻接触器状态
};
union PRECHARGE_FLAG
{
    Uint16 all;
    struct PRECHARGE_FLAG_BITS bit;
};

extern union PRECHARGE_FLAG preChargeFlag;

struct PRECHARGE_MODE_BITS
{
    Uint16 oncePrechargeMode:4;     // 0-3 一次侧预充方式
    Uint16 secPrechargeMode:4;      // 4-7 二次侧预充方式
    Uint16 udcPrechargeMode:4;      // 8-11 母线预充方式
    Uint16 rsvd:4;                  // 12-15 保留
};
union PRECHARGE_MODE
{
    Uint16 all;
    struct PRECHARGE_MODE_BITS bit;
};

extern union PRECHARGE_MODE preChargeMode;

#define PRECHARGE_MAX               4095        // 标幺值
extern Uint16 preChargeTmpCurrent;              // 4-20mA电流 0-4096 瞬时电流

extern Uint16 prechargeErr;

enum PRECHARGE_STATUS
{
	PRECHARGE_INIT_STATUS,					// 0 初始化
    PRECHARGE_WAIT_CMD_STATUS,				// 1 等待预充命令
    PRECHARGE_LV_CONTACOR_ON,               // 2 合低压接触器
    PRECHARGE_UDC_HV_RELAY_ON,              // 3 合高压继电器 凯撒四象限项目
    PRECHARGE_LV_RES_BYPASS_ON,             // 4 合低压旁路电阻接触器
    PRECHARGE_HV_CONTACOR_ON,               // 5 合高压(预充)接触器
    PRECHARGE_SEC_VOLT_ACC_STEP,            // 6 副边升压
    PRECHARGE_SEC_VOLT_DEC_STEP,            // 7 副边降压
    PRECHARGE_BUSBAR_DETECT,                // 8 母线电压检测    
    PRECHARGE_INPUT_VOLT_DETECT,		    // 9 输入电压检测
    PRECHARGE_LV_BOOST,                     // 10 两电阻串联升压
    PRECHARGE_LV_BOOST_BYPASS_RES,          // 11 一电阻升压
    PRECHARGE_HV_RES_BYPASS_CONTACTOR_ON,   // 12 原边高压预充 电阻旁路接触器合闸
    PRECHARGE_LV_RES_BYPASS_CONTACTOR_ON,   // 13 母线低压预充 电阻旁路接触器合闸
    PRECHARGE_UDC_STABLE_WAITING,           // 14 低压电阻旁路之后 等待母线稳定
    PRECHARGE_LV_CONTACTOR_OFF,             // 15 低压电阻旁路之后 等待母线稳定
    PRECHARGE_HV_SERIES_RES_OFF,            // 16 电阻支路接触器分闸
    PRECHARGE_LV_RES_BYPASS_OFF,            // 17 低压旁路电阻接触器分闸
    PRECHARGE_OVER_STATUS					// 18 完成
};
extern enum PRECHARGE_STATUS preChargeStatus;

#endif
//----------------------------END-------------------------//





