//==================================================================================================
//
// 定子磁链观测
//
//
//
// Time-stamp: <2012-2-9 16:21:31  author, 0000>
//
//==================================================================================================


#ifndef __M_FLUX_STATOR_OBSERVE_H__
#define __M_FLUX_STATOR_OBSERVE_H__



#include "main.h"
#include "m_control.h"



//================================================================================
struct FLUX_STATOR_OBSERVE_STR
{
    f32 falpha;                     // output: alpha flux
    f32 fbeta;                      // output: beta flux
    
    f32 yalpha;                     // alpha volt-sec
    f32 ybeta;                      // beta volt-sec
    f32 ialpha;                     // alpha drive current
    f32 ibeta;                      // beta drive current
    f32 wHw;                        // 硬件极点，A5-08
    f32 rs;                         // stator resistance
    f32 softwareCompPole;           // 软件补偿极点，A5-10
    f32 lowFrqComGain;              // Low Frequency compensation gain for scaling estimated flux
    f32 samplePeriod;               // sample period
    u16 spinStatusIsPllNotValid;    // (PLL_FREQUENCY_NOT_VALID == SpinningLoad.Status)
    u16 spinningLoadEnable;         // spinning load enable
    u16 isSpin;                     // (SPINNING_LOAD_STATE == DriveControl.State)
    struct PiDataType *pOutPllPi;   // &OutputProcessPllParams
    f32 speedReference;             // Speed Reference
    f32 ls;                         // stator inductance
    bool enable;                    // enable 
};
void FluxStatorObserve(struct FLUX_STATOR_OBSERVE_STR *p);

void FluxStatorObserveLC(void);
//================================================================================




#endif  //__M_FLUX_STATOR_OBSERVE_H__




