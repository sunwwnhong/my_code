//==================================================================================================
//
// 电机控制的主循环
//
//
//
// Time-stamp: <2011-3-10 14:59:47  author, 0000>
//
//==================================================================================================


#ifndef __M_MAIN_H__
#define __M_MAIN_H__



#include "main.h"
#include "m_output.h"



#define MAIN_LOOP_TIME_MS   2           // 主循环周期，ms
#define MAIN_LOOP_TIME      0.002       // 主循环周期，s

#define I_MAIN_LOOP_TIME_MS   0.5       // 主循环周期倒数，ms
#define I_MAIN_LOOP_TIME      500       // 主循环周期倒数，s


#define SLOW_LOOP_TIME_MS   2           // 慢环周期，ms
#define SLOW_LOOP_TIME      0.002       // 慢环周期，s


#define INPUT_BUS_FRQ       50.0        // 电网输入频率
//#define INPUT_BUS_FRQ       60.0        // 电网输入频率



//====================================================================
struct CORE_RUN_STATUS_BITS
{
    Uint16 run:1;           // (总的)运行标志。表示PWM正在发送
    Uint16 runReady:1;      // 运行准备就绪。


};
union CORE_RUN_STATUS
{
    Uint16 all;
    struct CORE_RUN_STATUS_BITS bit;
};
extern union CORE_RUN_STATUS coreRunStatus;
//====================================================================



extern union DSP_MAIN_COMMAND coreMainCmd;
extern union DSP_MAIN_COMMAND1 coreMainCmd1;
extern union DSP_SUB_COMMAND coreSubCmd;
extern union DSP_STATUS coreStatus;
extern union DSP_SUB_STATUS coreSubStatus;
extern union PG_PARA corePgPara; 


extern Uint16 coreErrorCode;
extern Uint16 coreAlarmCode;




//==============================================================================
struct DA_DATA
{
    u16 ao1Vol;     // AO1电压，百分比，Q15
    f32 ao1Offset;  // AO1零偏
    f32 ao1Gain;    // AO1增益

    u16 ao2Vol;
    f32 ao2Offset;
    f32 ao2Gain;

    u16 ao3Vol;
    f32 ao3Offset;
    f32 ao3Gain;
};
//==============================================================================






//==============================================================================
// 各种使能
//
struct MOTOR_CONTROL_OTHER_ENABLE_BITS
{                                   // bits  description
    u16 inVol:1;                    // 0    输入电网电压 1:有输入电压采样 0:没有输入电压采样
    
    u16 rsvd1:1;                    // 1       
    u16 rsvd2:1;                    // 2    speedRollbackenable    
    u16 rsvd3:1;                    // 3    
    u16 rsvd4:1;                    // 4    
    u16 rsvd5:1;                    // 5    
    u16 rsvd6:1;                    // 6    
    u16 rsvd7:1;                    // 7    
    u16 rsvd8:1;                    // 8     

    u16 fastSpinningLoad:1;         // 9    快速飞车启动

    u16 startLargeFlux:1;           // 10   启动时，增大励磁给定。

    u16 rsvd9:1;                    // 11   
    
    u16 piSelfTuneCurrentLoop:1;    // 12   PI参数自整定，电流环
    u16 piSelfTuneSpeedLoop:1;      // 13   PI参数自整定，速度环
    u16 piSelfTuneFluxLoop:1;       // 14   PI参数自整定，磁链环
    u16 magnetize:1;                // 15   预励磁
};
union MOTOR_CONTROL_OTHER_ENABLE
{
   u16                                      all;
   struct MOTOR_CONTROL_OTHER_ENABLE_BITS   bit;
};
extern union MOTOR_CONTROL_OTHER_ENABLE motorControlOtherEnable;
//==============================================================================

struct DecouplePLL_STR
{
    f32 dpos_fil;      // Input: stationary d-axis stator variable 
    f32 qpos_fil;       // Input: stationary q-axis stator variable 
    f32 dneg_fil;      // Input: rotating angle (pu) , 1PU = 2*pi
    f32 qneg_fil;          // Output: rotating d-axis stator variable 
    f32 angle_neg;          // Output: rotating q-axis stator variable 
    f32 angle_pos;
    f32 alpha_neg;
	f32 beta_neg;
    f32 alpha_pos;
	f32 beta_pos;
    f32 dpos;      // Input: stationary d-axis stator variable 
    f32 qpos;       // Input: stationary q-axis stator variable 
    f32 dneg;      // Input: rotating angle (pu) , 1PU = 2*pi
    f32 qneg;          // Output: rotating d-axis stator variable 	
};

#define PLUSE_TRIGGER_DELAY_MS 20       // 脉冲上升沿时间/ms
/*========================================================================================*
脉冲触发宏:
目的:控制工、变频接触器
输入:脉冲条件触发(stateReady)
    stateReady 0->1:触发
输出:
    stateCmd 0->1:脉冲信号输出，接触器动作
*=========================================================================================*/
#define PulseTriggerMacro(stateReady, stateReadyOld, ticker, stateCmd)      \
{                                                                           \
    if ((FALSE == stateReadyOld) && (TRUE == stateReady))                   \
    {                                                                       \
        stateCmd = TRUE;                                                    \
    }                                                                       \
                                                                            \
    if (stateCmd)                                                           \
    {                                                                       \
        ticker++;                                                           \
                                                                            \
        if (ticker >=                                                       \
            PLUSE_TRIGGER_DELAY_MS * I_MAIN_LOOP_TIME_MS)                   \
        {                                                                   \
            ticker = 0;                                                     \
            stateCmd = FALSE;                                               \
        }                                                                   \
    }                                                                       \
    stateReadyOld = stateReady;                                             \
}   

//==============================================================================





void Main0msMotor(void);
void Main05msMotorA(void);
void Main05msMotorB(void);
void Main05msMotorC(void);
void Main05msMotorD(void);



void InitSystem(void);



void MotorRunDeal(void);

void UpdateDataLog(void);









#endif  //__M_MAIN_H__


