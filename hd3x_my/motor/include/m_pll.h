//==================================================================================================
//
// 锁相环
//
//
//
// Time-stamp: <2012-2-10 10:26:02  author, 0000>
//
//==================================================================================================


#ifndef __M_PLL_H__
#define __M_PLL_H__



#include "main.h"
#include "m_control.h"





//================================================================================
struct PHASE_LOCK_LOOP_STR
{
    f32 frequency;                  // output: Frequency in Radians/Second
    f32 angle;                      // output: Angle in Radians

    f32 input;                      // Input
    f32 sampleRate;                 // sample rate
    f32 seed;                       // seed
    bool enable;                    // enable
    
    bool moduloFlag;                // output: 表明相角超过2*pi
    
    struct PiDataType *pllParams;   // structure containing gains and limits
};
void PhaseLockLoop(struct PHASE_LOCK_LOOP_STR *p);
//================================================================================






#endif  //__M_PLL_H__




