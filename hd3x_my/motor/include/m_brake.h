//==================================================================================================
//
// 制动，叠频制动
//
//
//
// Time-stamp: <2012-1-7 16:13:45  author, 0000>
//
//==================================================================================================



#ifndef __M_BRAKE_H__
#define __M_BRAKE_H__



#include "main.h"


#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中 
#define DEBUG_P_DUAL_FRQ_BRAKE  0
#elif 1                 // 程序放在RAM中调试 
#define DEBUG_P_DUAL_FRQ_BRAKE  0
#endif







//================================================================================
typedef struct
{
// 功能码
    u16 configBrakingEnable;        // braking enable
    f32 superposeFrq;               // 叠频制动叠加频率，omega
    f32 pLoss;                      // maximum power loss
    f32 vdLossMax;                  // vds loss maximum
    f32 brakingK;                   // braking constant

//---------------------------------------------------------
// 快环输入
    f32 fluxAlphaS;                 // stator flux alpha
    f32 fluxBetaS;                  // stator flux beta
    f32 iAlphaS;                    // stator current alpha
    f32 iBetaS;                     // stator current beta
    f32 fluxDS;                     // stator flux D axis
    f32 ids;                        // current measurement d axis
    f32 iqs;                        // current measurement q axis
    f32 frequency;                  // pll frequency
    
    f32 speedReference;             // speed reference
    f32 samplePeriod;               // smaple rate
//---------------------------------------------------------



//---------------------------------------------------------
// 快环输出
    f32 *idsFil;                    // filtered current measurement d axis
    f32 *iqsFil;                    // filtered current measurement d axis 
    f32 *fluxDSFil;                 // filtered flux d axis
    f32 *wsFil;                     // filtered motor speed
#if DEBUG_P_DUAL_FRQ_BRAKE
    f32 fluxdLossFil;               // Flux D loss filtered
    f32 fluxqLossFil;               // Flux Q loss filtered
    f32 idLossFil;                  // Id loss filtered
    f32 iqLossFil;                  // Iq loss filtered

// thetaLoss放在BrakingSyncFilter()中。
// 
    f32 sinThetaLoss;               // sin(thetaLoss)，
    f32 cosThetaLoss;               // cos(thetaLoss)
    
    f32 wLoss;                      // the loss frequency，omega
//---------------------------------------------------------



//---------------------------------------------------------
// 慢环输入
    f32 wsFilPu;                    // omega filtered，PU
    
    f32 motorSpeed;                 // motor speed
    f32 iqsRef;                     // iqs reference
    f32 iqsMax;                     // iqs maximum
    f32 iqsMin;                     // iqs minimum  
    f32 regenTorqueLimit;           // regeneration torque limit
    u16 stateIsNotMag;              // drive state is not MAGNETIZING_STATE ?
    f32 voltageClampLimit;          // peak voltage clamp limit
    f32 deadTimeComp;               // dead time compesation 
    f32 outVol;                     // 程序输出电压
    f32 inPrcEd;                    // InputProcess.Ed
    f32 MotorVoltageClampLimit;     // OutputProcess.MotorVoltageClampLimit
    f32 iRatedFrequency;            // OutputProcess.iRatedFrequency 
//---------------------------------------------------------


//---------------------------------------------------------
// 慢环输出
    f32 vdLoss;                     // Vd loss 
    f32 brakingLimit;               // Dual Frequency Braking Limit

    f32 pBrk;                       // Pbrk, braking power
    
// 指针
    bool *regenBraking;             // flag to enable regen braking for 6-step
    u16 *fluxSource;                // pointer to source of flux demand
    bool *braking;                  // pointer to braking flag
//---------------------------------------------------------

#endif

} DUAL_FRQ_BRAKE;
extern DUAL_FRQ_BRAKE dualFrqBrake;
//================================================================================





void DualFrequencyAndRegenBraking(DUAL_FRQ_BRAKE *p);
void BrakingSyncFilter(DUAL_FRQ_BRAKE *p);





#endif  //__M_BRAKE_H__


