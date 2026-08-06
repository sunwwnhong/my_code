//==================================================================================================
//
// 频率源处理
// 这里借用了这个名字，还包括flux给定的处理
//
//
// Time-stamp: <2012-2-19 5:24:03  author, 0000>
//
//==================================================================================================


#ifndef __M_FREQUENCY_SOURCE_H__
#define __M_FREQUENCY_SOURCE_H__



#include "main.h"





//==============================================================================
struct CommandGeneratorType
{
    bool FluxAtSetPoint;                // flux at setpoint flag
    
    f32 SpeedReference;                 // speed reference, rad/sec
    f32 SpeedReferencePU;               // Speed reference Per Unit
    
    f32 RawFluxDemand;                  // raw flux demand
    f32 FluxRampOutput;                 // flux ramp output
    f32 EnergySaverOutput;              // energy saver output
    f32 FieldWeakeningOutput;           // field weakening output，斜坡之前，斜坡的目标值
    f32 FluxReference;                  // flux reference
    
};
extern struct CommandGeneratorType CommandGenerator;
//==============================================================================



extern int16 coreFrq;
extern int32 coreFrqHz;
extern int32 coreFrqAimHz;



void CommandGeneratorControl(void);




f32 TorqueTest(f32 maxLimit, f32 minLimit);


#endif  //__M_FREQUENCY_SOURCE_H__






