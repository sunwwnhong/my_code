//==================================================================================================
//
// 性能状态处理
// 空闲、励磁、正常运行、调谐、同步切换、飞车启动等处理
//
//
//
// Time-stamp: <2012-2-19 4:55:59  author, 0000>
//
//==================================================================================================


#ifndef __M_STATE_CONTROL_H__
#define __M_STATE_CONTROL_H__



#include "main.h"



//==============================================================================
enum States
{
    IDLE_STATE,             // 0  空闲状态
    MAGNETIZING_STATE,      // 1  励磁状态
    SPINNING_LOAD_STATE,    // 2  飞车启动状态
    AUTO_TUNE_STATE,        // 3  调谐状态
    RUN_STATE,              // 4  正常运行状态
    STOP_STATE,             // 5  停车状态
    COAST_STATE,            // 6  自由停车状态
    UP_TRANSFER_STATE,      // 7  上切换状态
    DOWN_TRANSFER_STATE,     // 8  下切换状态
    ROTOR_INITIAL_STATE
};

struct  DriveControlType
{
    u16 Mode;
    enum States State;
};
extern struct DriveControlType DriveControl;
//==============================================================================






void StateControl(void);







#endif  //__M_STATE_CONTROL_H__


