//==================================================================================================
//
// 电流环
// 励磁电流环调节器，转矩电流环调节器
//
//
// Time-stamp: <2012-2-9 16:29:21  author, 0000>
//
//==================================================================================================


#ifndef __M_CURRENT_LOOP_H__
#define __M_CURRENT_LOOP_H__



#include "main.h"
#include "m_control.h"



//================================================================================
struct TORQUE_CURRENT_REG_STR
{
    f32 out;
    
    f32 reference;                  // reference input
    f32 feedback;                   // feedback input
    f32 propGain;                   // proportional gain
    f32 integGain;                  // integral gain
    f32 maxLimit;                   // maximium limit
    f32 speedReference;             // speed reference
    f32 motorSpeed;                 // motor speed
    f32 *iqGain;                    // iq gain 
    u16 *enable;                    // torque regulator enable
    bool globalEnable;              // global control enable
};
void TorqueCurrentReg(struct TORQUE_CURRENT_REG_STR *p);
//================================================================================



//================================================================================
struct MAGNETIZING_CURRENT_REG_STR
{
    f32 out;
    
    f32 reference;                  // reference input
    f32 feedback;                   // feedback input
    f32 fluxReference;              // flux reference
    f32 propGain;                   // proportional gain
    f32 integGain;                  // integral gain
    f32 maxLimit;                   // maximium limit
};
void MagnetizingCurrentReg(struct MAGNETIZING_CURRENT_REG_STR *p);
//================================================================================




#endif  //__M_CURRENT_LOOP_H__




