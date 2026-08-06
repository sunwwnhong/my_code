//==================================================================================================
//
// Peak Reduction
// 当输出电压超过限制时，叠加三次谐波或者过调制，提高电压输出。
//
//
// Time-stamp: <2012-2-9 16:50:30  author, 0000>
//
//==================================================================================================


#ifndef __M_PEAK_REDUCTION_H__
#define __M_PEAK_REDUCTION_H__



#include "main.h"



//================================================================================
struct PEAK_REDUCTION_STR
{
    f32 ea;                         // ea output
    f32 eb;                         // eb output
    f32 ec;                         // ec output
    
    f32 aref;                       // a input
    f32 bref;                       // b input
    f32 cref;                       // c input
    f32 speedRef;                   // speed reference
    f32 biasGain;                   // bias gain
    f32 peakReductMax;              // max peak reduction gain
    f32 peakReductKi;               // peak reduction integral gain
    f32 peakReductA;                // phase a gain
    f32 peakReductB;                // phase b gain
    f32 peakReductC;                // phase c gain
    bool enable;                    // global enable
};
void PeakReductionCalc(struct PEAK_REDUCTION_STR *p);
//================================================================================




#endif  //__M_PEAK_REDUCTION_H__








