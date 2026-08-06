//==================================================================================================
//
// 故障处理
//
//
//
// Time-stamp: <2011-9-5 14:09:23  author, 0000>
//
//==================================================================================================


#ifndef __M_ERROR_H__
#define __M_ERROR_H__



#include "main.h"




//==============================================================================
// 故障信息
#define ERROR_NONE                      0       // 0  -- 无
#define ERROR_INVERTER_UNIT             1       // 1  -- 逆变单元保护
#define ERROR_OC_ACC_SPEED              2       // 2  -- 加速过电流
#define ERROR_OC_DEC_SPEED              3       // 3  -- 减速过电路
#define ERROR_OC_CONST_SPEED            4       // 4  -- 恒速过电流
#define ERROR_OV_ACC_SPEED              5       // 5  -- 加速过电压
#define ERROR_OV_DEC_SPEED              6       // 6  -- 减速过电压
#define ERROR_OV_CONST_SPEED            7       // 7  -- 恒速过电压
#define ERROR_BUFFER_RES                8       // 8  -- 缓冲电阻过载故障
#define ERROR_UV                        9       // 9  -- 欠压故障
#define ERROR_OL_INVERTER               10      // 10 -- 变频器过载
#define ALARM_OL_MOTOR                  11      // 11 -- 电机过载
#define ALARM_LOSE_PHASE_INPUT          12      // 12 -- 输入缺相
#define ALARM_LOSE_PHASE_OUTPUT         13      // 13 -- 输出缺相
#define ERROR_OT_IGBT                   14      // 14 -- 散热器过热
#define ERROR_EXTERNAL                  15      // 15 -- 外部故障
#define ERROR_COMM                      16      // 16 -- 通讯(超时)故障
#define ERROR_CONTACTOR                 17      // 17 -- 接触器故障
#define ERROR_CURRENT_SAMPLE            18      // 18 -- 电流检测故障
#define ERROR_TUNE                      19      // 19 -- 电机调谐故障
#define ERROR_ENCODER                   20      // 20 -- 编码器故障
#define ERROR_EEPROM                    21      // 21 -- EEPORM读写故障
#define ERROR_22                        22      // 22 -- 变频器硬件故障
#define ERROR_MOTOR_SHORT_TO_GND        23      // 23 -- 电机对地阻抗偏小故障
#define ERROR_MOTOR_MAGNET              24      // 24 -- 电机励磁故障
#define ERROR_25                        25      // 25 -- 电机过热
#define ERROR_RUN_TIME_OVER             26      // 26 -- 运行时间到达

#define ERROR_USER_1                    27      // 27 -- 用户自定义故障1
#define ERROR_USER_2                    28      // 28 -- 用户自定义故障2
#define ERROR_POWER_UP_TIME_OVER        29      // 29 -- 上电时间到达
#define ALARM_LOSE_LOAD                 30      // 30 -- 掉载
#define ERROR_FDB_LOSE                  31      // 31 -- 运行时PID反馈丢失
#define ERROR_TRANSFORMER_SHORT_TO_GND  32      // 32 -- 输入对地阻抗偏小
#define ERROR_INPUT_TD_OL               34      // 34 -- 输入变压器过载
#define ERROR_INPUT_OL                  35      // 35 -- 变频器空载输入电流异常
#define ALARM_INPUT_CUR_IMBALANCE       36      // 36 -- 输入电流不对称
#define ERROR_INPUT_VOL_BIG             37      // 37 -- 输入电压超过额定30%
#define ALARM_OUTPUT_CUR_IMBALANCE      38      // 38 -- 输出电流不对称
#define ERROR_CBC                       40      // 40 -- 逐波限流故障
#define ERROR_SWITCH_MOTOR_WHEN_RUN     41      // 41 -- 运行时切换电机
#define ERROR_DEV                       42      // 42 -- 速度偏差过大
#define ERROR_OS                        43      // 43 -- 电机超速度
#define ERROR_MOTOR_OT                  45      // 45 -- 电机过温故障
#define ALARM_INIT_POSITION             51      // 51 -- 磁极位置检测失败
#define ALARM_SPEED_DETECT              52      // 52 -- 零点位置辨识失败
#define ALARM_UVW_FDB                   53      // 53 -- uvw信号反馈错误
#define ERROR_MOTOR_OV                  55      // 55 -- 电机过压
#define ERROR_PG_PARA_ERROR             90      // 90 -- 编码器线数设定错误
#define ERROR_PG_LOST                   91      // 91 -- 未接编码器
#define ERROR_INPUT_ONE_CYCLE           93      // 93 -- 系统无功功率过大故障
#define ERROR_BYPASS_CELL_OVER          94      // 94 -- 旁路最小单元数超限
#define ERROR_CIRC_PHASE_FRQ            96      // 96 -- 环流输入输出相位幅值错误
#define EROR_EXCESSIVE_LOSS             97      // 97 -- 变频器损耗过大
#define ERROR_PROGRAM_LOGIC             99      // 99 -- 程序执行逻辑错误
#define ERROR_OV_INPUT                  102     // 102-- 输入电压过压
#define ERROR_UNPC_VOL                  104     // 104-- 中点电压偏差过大
#define ERROR_AD_SAMPLE                 124     // 124-- AD7606 采样故障
#define ERROR_HARDWAREOV                125     // 124-- 硬件过压故障
#define ERROR_RSVD                      9999    // 保留
//==============================================================================




extern Uint16 coreErrorCode;



#define FAULT_HANDLER_FREQ  500                 // 故障检测时间_ms
#define HYSTERISIS_LEVEL    (FAULT_HANDLER_FREQ/MAIN_LOOP_TIME_MS)
void Hysterisis(bool alarmState, s16 *alarmTicker, bool *state);

//==============================================================================
struct MOTOR_OVERLOAD_PROTECT                                      
{
    u16 enable;                         // F9-00 开启电机直接反时限过载保护
    f32 time;                           // F9-01 电机过载时间，功能码单位s
    f32 predictCoef;                    // F9-02 电机过载保护预警系数
    f32 olCoef;                         // F9-03 电机过载保护阈值
    
    f32 thermal;                        // 电机实际当前累加热量总值
    s16 predict;
    f32 td;                             // 发热时间常数
};
extern struct MOTOR_OVERLOAD_PROTECT motorOlProtect;


struct TRANSFORMER_OVERLOAD_PROTECT
{
    s16 enable;                         // 变压器过载保护使能
    f32 olCoef;                         // 变压器过载保护阈值
    f32 time;                           // 变压器过载保护时间，单位:s
    f32 heatDecTime;                    // 变压器散热时间:heatDecTime持续降额运行，才可允许下次1.2/1.5倍持续过载50s
    f32 thermal;                        // 变压器实际当前累加热量总值
    f32 td;                             // 变压器热容
    s16 error;                          // 变压器过载保护动作标记
};

struct CELL_CUR_Tim
{
    f32 cur;                            // 电流，过载电流
    f32 time;                           // 时间，过载时间
};

struct SAMPLE_PHASE_DELAY
{
    f32 inVolDisp;     // 输入电压相序显示使用
    f32 outVolDisp;    // 输出电压相序显示使用
    f32 inCurDisp;     // 输入电流相序显示使用
    f32 outCurDisp;    // 输出电流相序显示使用
};

struct CELL_OVERLOAD_PROTECT
{
    s16 enable;                         // 单元过载使能
    f32 heat;                           // 单元每拍累加的热量
    s16 td;                             // 单元热容
    f32 thermal;                        // 单元实际当前累加热量总值
    f32 cellCur;                        // 由输出电流值折算出的对应单元额定电流的标幺值
    f32 olTime;                         // 不同电流对应的时间表
    s16 predict;                        // 单元过载预报警
};

enum TRANSFORMER_OL_MODE
{
    NO_TRANSFORMER_PROTECT,          // 0
    CUR_TIME_INVERATIO_CURVE,        // 1 == 变压器过载保护方式选择 电流时间反比例:反时限过载曲线
    CUR_TIME_INVERATIO_TABLE         // 2 == 变压器过载保护方式选择 电流时间反比例:反时限过载表
};

struct PHASE_LOSS_STR
{
    f32 cur;                        // 缺相程序计算对象
    s16 phaseLossicker;             // 缺相程序计数器
    u16 phaseLossState;             // 缺相程序计算结果：1缺相 0不缺相
};

enum ENCODERLOSS_DETECT_MODE
{
    ENCODERLOSS_DETECT_BEGIN,       // 0 2s内编码器故障检测
    ENCODERLOSS_DETECT_CONTINUE,    // 1 2s后编码器故障检测
    ENCODERLOSS_DETECT_END          // 2 编码器故障检测结束
};
//==============================================================================

#endif  //__M_ERROR_H__


