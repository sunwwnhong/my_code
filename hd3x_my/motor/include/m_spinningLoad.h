//==================================================================================================
//
// 飞车启动
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#ifndef __M_SPINNING_LOAD_H__
#define __M_SPINNING_LOAD_H__


#include "main.h"



#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_SPINNING_LOAD   1
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_SPINNING_LOAD   0
#endif






//================================================================================
enum SpinningLoadModes
{
    SPINNING_LOAD_OFF,  // 0
    POSITIVE,           // 1
    NEGATIVE,           // 2
    BOTH                // 3
};

enum spinningLoadStatus
{
    SPINNING_LOAD_DONE,                 // 0
    SPINNING_LOAD_SCAN_IN_PROGRESS,     // 1
    SPINNING_LOAD_CURRENT_RAMP_UP,      // 2
    SPINNING_LOAD_CURRENT_RAMP_DOWN,    // 3
    SPINNING_LOAD_YES,                  // 4
    SPINNING_LOAD_NO,                   // 5
    PLL_FREQUENCY_VALID,                // 6
    PLL_FREQUENCY_NOT_VALID,            // 7
    SPINNING_LOAD_CURRENT_ERROR,        // 8
    FAST_SPINNING_LOAD_OBSERVER         // 9
};

struct SPINNING_LOAD_TYPE
{
    f32 SpeedReference;
    f32 FluxReference;
    
    u16 Mode;
    enum spinningLoadStatus Status;
    bool UseSpeedReference;
    bool UseFluxReference;
    bool PresetTorqueCurrentRegulator;
    bool PresetMagnetizingCurrentRegulator;
};
extern struct SPINNING_LOAD_TYPE SpinningLoad;

struct FAST_SPINNING_LOAD_TYPE
{    
    bool PresetPllParams;
    bool UseFluxFdbFastSpinningLoad;
    bool UseDeltasFastSpinningLoad;
};
extern struct FAST_SPINNING_LOAD_TYPE FastSpinningLoad;
//================================================================================



void SpinningLoadState(void);
void SpinningLoadControl(void);





#endif  // __M_SPINNING_LOAD_H__












