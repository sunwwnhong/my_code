//==================================================================================================
//
// ËÙ¶È»·
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#ifndef __M_SPEED_LOOP_H__
#define __M_SPEED_LOOP_H__



#include "main.h"
#include "m_control.h"



#define MINIMUM_LIMIT     1
#define MAXIMUM_LIMIT     2



//================================================================================
struct SPEED_REGULATOR_STR
{
    f32 out;                        // regulated speed output
    f32 speedReference;             // speedReference
    f32 wr;                         // speed feedback
    f32 maxLimit;                   // maximum limit
    f32 minLimit;                   // minimum limit
    f32 propGain;                   // proportional gain
    f32 kf;                         // kf gain
    f32 integGain;                  // integral gain
    
    u16 *speedRollback;             // speed rollback flag
    bool enable;                    // global enable
};
void SpeedRegulator(struct SPEED_REGULATOR_STR *p);
//================================================================================


//================================================================================
struct CELL_VOLTAGE_REGULATOR_STR
{
    f32 out;                        // regulated  output
    f32 celVoltageFdb;              // celVoltageFdb
    f32 celVoltageRef;              // celVoltageRef 
    f32 celVoltageDelta;            // celVoltageDelta
    f32 maxLimit;                   // maximum limit
    f32 minLimit;                   // minimum limit
    f32 propGain;                   // proportional gain
    f32 integGain;                  // integral gain
    f32 accumulator;                // integr
    f32 lastInput;                  // lastInput
    s16 enable; 

};
void CellVoltageRegulator(struct CELL_VOLTAGE_REGULATOR_STR *p);
//================================================================================

#endif  //__M_SPEED_LOOP_H__




