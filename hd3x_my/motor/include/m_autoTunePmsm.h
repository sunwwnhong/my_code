//==================================================================================================
//
// 调谐。
// 辨识参数:
// 1. 定子电阻
// 2. 漏感 
// 3. 空载电流
// 4. 惯量
//
//
//
// Time-stamp: <2016-4-20 16:51:25  Shengfang.Fan, 13048>
//
//==================================================================================================



#include "main.h"





struct RotorPositionPwmPara
{
    u16 pwmU:1;           // 0    U相输出
    u16 pwmV:1;           // 1    V相输出
    u16 pwmW:1;           // 2    W相输出
    u16 pwmEn:1;          // 3    PWM 使能    1: 使能      0: 不使能
    u16 mode:1;           // 4    PWM 模式    1: 1/0电平   0: 1/-1电平
    u16 tuneEn:1;         // 5    磁极初始位置识别使能           1: 使能  0: 不使能
    u16 state:1;          // 6    是否处于磁极初始位置识别状态   1: 是    0: 不是
    u16 finishFlg:1;      // 7    磁极初始位置识别完成标志       1: 完成  0: 未完成
    u16 pulsewidth:8;     // 9-15 PWM 脉宽    单位10us
};
union ROTOR_POSITION_REG
{
    u16 all;
    struct RotorPositionPwmPara bit;
};
extern union ROTOR_POSITION_REG RotorPositionPwmReg;



extern void AutoTuneStatePmsm(void);
extern void AutoTuneControlPmsm(void);
extern void AutoTuneStage1FastDeal1Pmsm(void);
extern void AutoTuneStage1FastDeal2Pmsm(void); 








