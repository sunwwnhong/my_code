#ifndef __F_FUNCCODE_DEAL_H__
#define __F_FUNCCODE_DEAL_H__

#define DEBUG_F_RESTORE_COMPANY_PARA_DEAL   1

// ----------------函数声明----------------------------------------------
extern void ClearRecordDeal(void);
extern void LimitOtherCodeDeal(Uint16 index);
extern Uint16 GetFuncCodeInit(Uint16 index, Uint16 type);
extern void InitFuncCode(void);
extern void SysInvTpyeParaDeal(void);
// ----------------函数声明结束------------------------------------------

// 恢复出厂参数，清除记录
// 所需要的一些index宏定义

//====================================================
//
// 恢复出厂参数，某些参数不需要恢复
//
//====================================================

// 某些连续的功能码不需要恢复
#define INIT_EXCEPT_SERIES_S_0  GetCodeIndex(funcCode.group.ff[0])          // FF 厂家参数
#define INIT_EXCEPT_SERIES_E_0  GetCodeIndex(funcCode.group.ff[FFNUM-1])

#define INIT_EXCEPT_SERIES_S_1  GetCodeIndex(funcCode.group.fp[0])          // FP 功能码管理
#define INIT_EXCEPT_SERIES_E_1  GetCodeIndex(funcCode.group.fp[FPNUM-1])

#define INIT_EXCEPT_SERIES_S_2  FC_MOTOR1_START_INDEX           // 第1电机参数
#define INIT_EXCEPT_SERIES_E_2  FC_MOTOR1_END_INDEX

#define INIT_EXCEPT_SERIES_S_3  FC_MOTOR2_START_INDEX           // 第2电机参数
#define INIT_EXCEPT_SERIES_E_3  FC_MOTOR2_END_INDEX

#define INIT_EXCEPT_SERIES_S_6  FC_MOTOR3_START_INDEX           // 第3电机参数
#define INIT_EXCEPT_SERIES_E_6  FC_MOTOR3_END_INDEX

#define INIT_EXCEPT_SERIES_S_7  FC_MOTOR4_START_INDEX           // 第4电机参数
#define INIT_EXCEPT_SERIES_E_7  FC_MOTOR4_END_INDEX

#define INIT_EXCEPT_SERIES_S_4  GetCodeIndex(funcCode.group.ac[0])          // AE AIAO出厂校正
#define INIT_EXCEPT_SERIES_E_4  GetCodeIndex(funcCode.group.ac[ACNUM-1])

#define INIT_EXCEPT_SERIES_S_5  GetCodeIndex(funcCode.code.errorLatest6)    // 第一次故障类型
#define INIT_EXCEPT_SERIES_E_5  LAST_ERROR_RECORD_INDEX                     // 最后一个故障记录

#define INIT_EXCEPT_SERIES_S_8  GetCodeIndex(funcCode.code.timeNowYear)     // 时间开始
#define INIT_EXCEPT_SERIES_E_8  GetCodeIndex(funcCode.code.timeNowSec)      // 时间结束

#define INIT_EXCEPT_SERIES_S_9  (GetCodeIndex(funcCode.code.inspectTimeSet))     // 密码保护的范围 
#define INIT_EXCEPT_SERIES_E_9  (GetCodeIndex(funcCode.code.rsvdEndF874))   

#if HD72
#define INIT_EXCEPT_SERIES_S_10 (GetCodeIndex(funcCode.code.cbcCounterProtectPoint))  // 逐波限流功能码
#define INIT_EXCEPT_SERIES_E_10 (GetCodeIndex(funcCode.code.cbcCellRecoverTimeIntervel))
#endif

// 某些单独的功能码不需要恢复
#define INIT_EXCEPT_SINGLE_0    GetCodeIndex(funcCode.code.runTimeAddup)        // 累计运行时间
#define INIT_EXCEPT_SINGLE_1    GetCodeIndex(funcCode.code.runTimeAddupSec)     // 累计运行时间
#define INIT_EXCEPT_SINGLE_2    GetCodeIndex(funcCode.code.powerUpTimeAddup)    // 累计运行时间
#define INIT_EXCEPT_SINGLE_3    GetCodeIndex(funcCode.code.powerUpTimeAddupSec) // 累计运行时间
#define INIT_EXCEPT_SINGLE_4    GetCodeIndex(funcCode.code.powerAddup)          // 累计耗电量千度
#define INIT_EXCEPT_SINGLE_5    GetCodeIndex(funcCode.code.serialNumberL)       // 产品序列号低位
#define INIT_EXCEPT_SINGLE_6    GetCodeIndex(funcCode.code.serialNumberH)       // 产品序列号高位
#define INIT_EXCEPT_SINGLE_7    GetCodeIndex(funcCode.code.powerAddupH)         // 累计耗电量千万度
#define INIT_EXCEPT_SINGLE_8    GetCodeIndex(funcCode.code.powerAddupInt)       // 累计耗电量千度小数部分
#define INIT_EXCEPT_SINGLE_9    GetCodeIndex(funcCode.code.LowFrCompMenu.LowFrqWo)  // 输出电压硬件系数
//#define INIT_EXCEPT_SINGLE_10   GetCodeIndex(funcCode.code.preChargeMode)       // 预充方式
#define INIT_EXCEPT_SINGLE_11   GetCodeIndex(funcCode.code.minCells)            // 旁路时每相最小单元数
#define INIT_EXCEPT_SINGLE_12   GetCodeIndex(funcCode.code.sysConfirmPara)      // 确认参数

//====================================================
//
// 清除记录
//
//====================================================
// 某些连续的功能码清除记录
#define CLEAR_RECORD_SERIES_S_0  GetCodeIndex(funcCode.code.errorLatest6)        // 第一次故障类型
#define CLEAR_RECORD_SERIES_E_0  LAST_ERROR_RECORD_INDEX                          // 最后一个故障记录

// 某些单独的功能码清除记录
#define CLEAR_RECORD_SINGLE_0    GetCodeIndex(funcCode.code.runTimeAddup)        // 累计运行时间
#define CLEAR_RECORD_SINGLE_1    GetCodeIndex(funcCode.code.runTimeAddupSec)     // 累计运行时间的s
#define CLEAR_RECORD_SINGLE_2    GetCodeIndex(funcCode.code.powerUpTimeAddup)    // 累计上电时间
#define CLEAR_RECORD_SINGLE_3    GetCodeIndex(funcCode.code.powerUpTimeAddupSec) // 累计上电时间的s
#define CLEAR_RECORD_SINGLE_4    GetCodeIndex(funcCode.code.powerAddup)          // 累计耗电量千度低位
#define CLEAR_RECORD_SINGLE_5    GetCodeIndex(funcCode.code.powerAddupInt)       // 累计耗电量千度小数部分 
#define CLEAR_RECORD_SINGLE_6    GetCodeIndex(funcCode.code.powerAddupH)          // 累计耗电量千万度高位

enum SYS_INV_PARA_STATUS
{
    NONE_DEAL,
    NEW_DEAL_START,
    PARA_DEALING,
    PARA_DEAL_FINISH
};
extern enum SYS_INV_PARA_STATUS sysInvParaStatus;

struct SYS_INVERTER_TYPE_BITS
{
    Uint16 bypass:1;        // 旁路配置  0-DN / 1-DB
    Uint16 rsvd:3;          // 保留
    Uint16 rateInput:8;     // 额定输入电压 + 额定功率
    Uint16 sysType:4;       // 系统类型 0 - HD90; 1 - HD90S
};

union SYS_INVERTER_TYPE
{
    Uint16 all;
    struct SYS_INVERTER_TYPE_BITS bit;
};
extern union SYS_INVERTER_TYPE sysInvType;

#if (HD90_AFE | CM3000)
#define INV_CURRENT_LIMIT_VALUE     2000  // 200.0%
#else
#define INV_CURRENT_LIMIT_VALUE     1500  // 150.0%
#endif

#endif

//----------------END---------------//

